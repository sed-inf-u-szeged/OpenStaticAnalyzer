/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#include "csharp/inc/csharp.h"
#include "common/inc/StringSup.h"
#include <set>
#include <string>

using namespace columbus::io;

namespace columbus { namespace csharp { namespace asg {

const std::map< std::string, VisitorGraphml::NodeCompareFunc> VisitorGraphml::compareTable = VisitorGraphml::create_map();

VisitorGraphml::VisitorGraphml(columbus::io::GraphmlIO& io, std::set< std::string>& edgeFilter, unsigned int maxDrawingDepth) : io(io), edgeCounter(0), idsToDrawedNodes(), maxDrawingDepth(maxDrawingDepth), edgeFilter( edgeFilter), nodeFilter(),visitCrossEdge( maxDrawingDepth == 0), isColorWhite(false), nodeTypeAttributeFilter(),isGroupingTreeNodes(false),nodeTypeFilter(){
}

VisitorGraphml::~VisitorGraphml() {
}

VisitorGraphml::NodeCompareFunc VisitorGraphml::getCompareFunctionToNode( std::string& nodeName)
{
  std::map< std::string, NodeCompareFunc>::const_iterator foundFunction = compareTable.find( nodeName);
  if ( foundFunction != compareTable.end())
    return foundFunction->second;
  else
    return NULL;
}

void VisitorGraphml::setStartPoint( NodeId startPoint)
{
  idsToDrawedNodes.insert( std::make_pair( startPoint, false));
}

void VisitorGraphml::setIsWhiteColor( bool isWhite)
{
  isColorWhite = isWhite;
}

void VisitorGraphml::setIsGroupingTreeNodes( bool groupingTreeNodes)
{
  isGroupingTreeNodes = groupingTreeNodes;
}

void VisitorGraphml::setIsEnableCrossEdge( bool isVisitCrossEdge)
{
  visitCrossEdge = isVisitCrossEdge;
}

void VisitorGraphml::addToFilterNodeTypeAttributes( std::string str)
{
  nodeTypeAttributeFilter.insert(str);
}

void VisitorGraphml::addToFilterNodeType( std::string str)
{
  nodeTypeFilter.insert(str);
}

void VisitorGraphml::filterNodeTypeMatch( std::string pattern)
{
  std::set<std::string> types = getNodeTypeSet();
  for(std::set< std::string>::iterator it = types.begin();it!=types.end();++it)
    if(it->find(pattern)!=std::string::npos)
      nodeTypeFilter.insert(*it);
}

static const std::string getSourcePositionContent(const SourcePosition& attr) {
  std::string content;
  content += "endColumn : " + common::toString(attr.getEndColumn()) + ", ";
  content += "endLine : " + common::toString(attr.getEndLine()) + ", ";
  content += "fileName : " + attr.getFileName() + ", ";
  content += "startColumn : " + common::toString(attr.getStartColumn()) + ", ";
  content += "startLine : " + common::toString(attr.getStartLine()) + "";
  return content;
}

static void compositeContentFormatter(std::string& content) {
  if(content.size()==0) return;
  std::string formattedcontent = "";
  size_t pos = content.find("file : ,");
  if(pos != std::string::npos){
    size_t from = content.rfind('\n',pos);
    size_t to = content.find('\n',pos);
    content.erase(from,to-from);
  }
  int depth = 0;
  for(std::string::iterator it = content.begin(); it != content.end(); ++it){
    if(*it==','){
      std::string repl = "\n";
      for(int i=0;i<depth;++i)
        repl += "  ";
      int k = 1;
      while(it+k != content.end() && *(it+k)==' ')
        ++k;
      it += k-1;
      formattedcontent += repl;
    }else if(*it=='['){
      depth++;
      std::string repl = "\n";
      for(int i=0;i<depth;++i)
        repl += "  ";
      formattedcontent += repl;
    }else if(*it==']'){
      depth--;
      continue;
    }else{
      formattedcontent += *it;
    }
  }
  if(*(formattedcontent.end()-1)=='\n'){
    *(formattedcontent.end()-1) = ' ';
  }
  content = formattedcontent;
}

void VisitorGraphml::addAttributeToContent(const base::Base& node, std::string& content, bool callVirtualBase) {
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Base") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "id : " + common::toString(node.getId()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const base::Positioned& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Positioned") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "position : [" + getSourcePositionContent(node.getPosition()) + "]\n";
}

void VisitorGraphml::addAttributeToContent(const expression::AliasQualifiedNameSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::NameSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AliasQualifiedNameSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::AnonymousFunctionExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AnonymousFunctionExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::AnonymousMethodExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::AnonymousFunctionExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AnonymousMethodExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::AnonymousObjectCreationExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AnonymousObjectCreationExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::ArrayCreationExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ArrayCreationExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ArrayTypeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::TypeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ArrayTypeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::AssignmentExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AssignmentExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::AwaitExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AwaitExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::BaseExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::InstanceExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::BaseExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::BinaryExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::BinaryExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::CastExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::CastExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::CheckedExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::CheckedExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ConditionalAccessExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ConditionalAccessExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ConditionalExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ConditionalExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::DefaultExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::DefaultExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ElementAccessExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ElementAccessExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ElementBindingExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ElementBindingExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::GenericNameSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::SimpleNameSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::GenericNameSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::IdentifierNameSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::SimpleNameSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::IdentifierNameSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ImplicitArrayCreationExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ImplicitArrayCreationExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ImplicitElementAccessSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ImplicitElementAccessSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::InitializerExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::InitializerExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::InstanceExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::InstanceExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::InterpolatedStringExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::InterpolatedStringExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::InvocationExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::InvocationExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::LambdaExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::AnonymousFunctionExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::LambdaExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::LiteralExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::LiteralExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "token : " + node.getToken() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::MakeRefExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::MakeRefExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::MemberAccessExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::MemberAccessExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::MemberBindingExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::MemberBindingExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::NameSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::TypeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::NameSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::NullableTypeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::TypeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::NullableTypeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ObjectCreationExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ObjectCreationExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::OmittedArraySizeExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::OmittedArraySizeExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::OmittedTypeArgumentSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::TypeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::OmittedTypeArgumentSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ParenthesizedExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ParenthesizedExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ParenthesizedLambdaExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::LambdaExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ParenthesizedLambdaExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::PointerTypeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::TypeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::PointerTypeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::PostfixUnaryExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::PostfixUnaryExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::PredefinedTypeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::TypeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::PredefinedTypeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::PrefixUnaryExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::PrefixUnaryExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::QualifiedNameSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::NameSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::QualifiedNameSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::QueryExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::QueryExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::RefTypeExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::RefTypeExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::RefValueExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::RefValueExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::SimpleLambdaExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::LambdaExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::SimpleLambdaExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::SimpleNameSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::NameSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::SimpleNameSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::SizeOfExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::SizeOfExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::StackAllocArrayCreationExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::StackAllocArrayCreationExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ThisExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::InstanceExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ThisExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::TypeOfExpressionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::TypeOfExpressionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::TypeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const expression::ExpressionSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::TypeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::BlockSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::BlockSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::BreakStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::BreakStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::CheckedStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::CheckedStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ContinueStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ContinueStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::DoStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::DoStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::EmptyStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::EmptyStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ExpressionStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ExpressionStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::FixedStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::FixedStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ForEachStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ForEachStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const statement::ForStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ForStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::GotoStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::GotoStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::IfStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::IfStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::LabeledStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::LabeledStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const statement::LocalDeclarationStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::LocalDeclarationStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::LockStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::LockStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ReturnStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ReturnStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::StatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::StatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::SwitchStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::SwitchStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ThrowStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ThrowStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::TryStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::TryStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::UnsafeStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::UnsafeStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::UsingStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::UsingStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::WhileStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::WhileStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::YieldStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const statement::StatementSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::YieldStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::AccessorDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AccessorDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::AccessorListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AccessorListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::AnonymousObjectMemberDeclaratorSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AnonymousObjectMemberDeclaratorSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ArgumentListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseArgumentListSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ArgumentListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ArgumentSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ArgumentSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ArrayRankSpecifierSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ArrayRankSpecifierSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ArrowExpressionClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ArrowExpressionClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::AttributeArgumentListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AttributeArgumentListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::AttributeArgumentSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AttributeArgumentSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::AttributeListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AttributeListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::AttributeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AttributeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::AttributeTargetSpecifierSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::AttributeTargetSpecifierSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::BaseArgumentListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseArgumentListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BaseCrefParameterListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseCrefParameterListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BaseFieldDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseFieldDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BaseListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BaseMethodDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseMethodDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BaseParameterListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseParameterListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BasePropertyDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BasePropertyDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BaseTypeDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseTypeDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::BaseTypeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BaseTypeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BracketedArgumentListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseArgumentListSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BracketedArgumentListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::BracketedParameterListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseParameterListSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::BracketedParameterListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CaseSwitchLabelSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::SwitchLabelSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CaseSwitchLabelSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CatchClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CatchClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CatchDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CatchDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CatchFilterClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CatchFilterClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ClassDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::TypeDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ClassDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ClassOrStructConstraintSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::TypeParameterConstraintSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ClassOrStructConstraintSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CompilationUnitSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CompilationUnitSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ConstructorConstraintSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::TypeParameterConstraintSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ConstructorConstraintSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ConstructorDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseMethodDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ConstructorDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::ConstructorInitializerSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ConstructorInitializerSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ConversionOperatorDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseMethodDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ConversionOperatorDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ConversionOperatorMemberCrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberCrefSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ConversionOperatorMemberCrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CrefBracketedParameterListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseCrefParameterListSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CrefBracketedParameterListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CrefParameterListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseCrefParameterListSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CrefParameterListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CrefParameterSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CrefParameterSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::CrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::CrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::DefaultSwitchLabelSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::SwitchLabelSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::DefaultSwitchLabelSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::DelegateDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::DelegateDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::DestructorDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseMethodDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::DestructorDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::ElseClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ElseClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::EnumDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseTypeDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::EnumDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::EnumMemberDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::EnumMemberDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::EqualsValueClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::EqualsValueClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::EventDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BasePropertyDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::EventDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::EventFieldDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseFieldDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::EventFieldDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ExplicitInterfaceSpecifierSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ExplicitInterfaceSpecifierSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ExternAliasDirectiveSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ExternAliasDirectiveSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::FieldDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseFieldDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::FieldDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::FinallyClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::FinallyClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::FromClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::QueryClauseSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::FromClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::GlobalStatementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::GlobalStatementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::GroupClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::SelectOrGroupClauseSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::GroupClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::IncompleteMemberSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::IncompleteMemberSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::IndexerDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BasePropertyDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::IndexerDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::IndexerMemberCrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberCrefSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::IndexerMemberCrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::InterfaceDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::TypeDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::InterfaceDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::InterpolatedStringContentSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::InterpolatedStringContentSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::InterpolatedStringTextSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::InterpolatedStringContentSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::InterpolatedStringTextSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::InterpolationAlignmentClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::InterpolationAlignmentClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::InterpolationFormatClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::InterpolationFormatClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::InterpolationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::InterpolatedStringContentSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::InterpolationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::JoinClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::QueryClauseSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::JoinClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::JoinIntoClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::JoinIntoClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::LetClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::QueryClauseSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::LetClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::MemberCrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::CrefSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::MemberCrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::MemberDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::MemberDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::MethodDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseMethodDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::MethodDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::NameColonSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::NameColonSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::NameEqualsSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::NameEqualsSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::NameMemberCrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberCrefSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::NameMemberCrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::NamespaceDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::NamespaceDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::OperatorDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseMethodDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::OperatorDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::OperatorMemberCrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::MemberCrefSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::OperatorMemberCrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::OrderByClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::QueryClauseSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::OrderByClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::OrderingSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::OrderingSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ParameterListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseParameterListSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ParameterListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ParameterSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ParameterSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::PropertyDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BasePropertyDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::PropertyDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::QualifiedCrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::CrefSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::QualifiedCrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::QueryBodySyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::QueryBodySyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::QueryClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::QueryClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::QueryContinuationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::QueryContinuationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::SelectClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::SelectOrGroupClauseSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::SelectClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::SelectOrGroupClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::SelectOrGroupClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::SimpleBaseTypeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseTypeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::SimpleBaseTypeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::StructDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::TypeDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::StructDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::SwitchLabelSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::SwitchLabelSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::SwitchSectionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::SwitchSectionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::SyntaxToken& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::SyntaxToken") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeArgumentListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeArgumentListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeConstraintSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::TypeParameterConstraintSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeConstraintSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeCrefSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::CrefSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeCrefSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::BaseTypeDeclarationSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeParameterConstraintClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeParameterConstraintClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeParameterConstraintSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeParameterConstraintSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeParameterListSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeParameterListSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::TypeParameterSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::TypeParameterSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::UsingDirectiveSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::UsingDirectiveSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::VariableDeclarationSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::VariableDeclarationSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::VariableDeclaratorSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::VariableDeclaratorSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "identifier : " + node.getIdentifier() + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::WhereClauseSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::QueryClauseSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::WhereClauseSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlAttributeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlAttributeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlCDataSectionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlNodeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlCDataSectionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlCommentSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlNodeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlCommentSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlCrefAttributeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlAttributeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlCrefAttributeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlElementEndTagSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlElementEndTagSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlElementStartTagSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlElementStartTagSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlElementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlNodeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlElementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlEmptyElementSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlNodeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlEmptyElementSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlNameAttributeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlAttributeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlNameAttributeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlNameSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlNameSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlNodeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlNodeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlPrefixSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlPrefixSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlProcessingInstructionSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlNodeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlProcessingInstructionSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlTextAttributeSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlAttributeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlTextAttributeSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::XmlTextSyntax& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::XmlNodeSyntax&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::XmlTextSyntax") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::visit(const expression::AliasQualifiedNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AliasQualifiedNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::AliasQualifiedNameSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getAlias() || node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::AliasQualifiedNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AliasQualifiedNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::AnonymousMethodExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AnonymousMethodExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::AnonymousMethodExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getParameterList())
      hasChildNode = true;
    if(node.getBody())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::AnonymousMethodExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AnonymousMethodExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AnonymousObjectCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::AnonymousObjectCreationExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getInitializersIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AnonymousObjectCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ArrayCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrayCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ArrayCreationExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getInitializer() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ArrayCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrayCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ArrayTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrayTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ArrayTypeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getElementType() || !node.getRankSpecifiersIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ArrayTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrayTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::AssignmentExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AssignmentExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::AssignmentExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getLeft() || node.getRight())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::AssignmentExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AssignmentExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::AwaitExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AwaitExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::AwaitExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::AwaitExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AwaitExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::BaseExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BaseExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::BaseExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::BaseExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BaseExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::BinaryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BinaryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::BinaryExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getLeft() || node.getRight())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::BinaryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BinaryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::CastExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::CastExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::CastExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::CastExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::CastExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::CheckedExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::CheckedExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::CheckedExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::CheckedExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::CheckedExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ConditionalAccessExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ConditionalAccessExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ConditionalAccessExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getWhenNotNull())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ConditionalAccessExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ConditionalAccessExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ConditionalExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ConditionalExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ConditionalExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getCondition() || node.getWhenFalse() || node.getWhenTrue())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ConditionalExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ConditionalExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::DefaultExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::DefaultExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::DefaultExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::DefaultExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::DefaultExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ElementAccessExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ElementAccessExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ElementAccessExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList() || node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ElementAccessExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ElementAccessExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ElementBindingExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ElementBindingExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ElementBindingExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ElementBindingExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ElementBindingExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::GenericNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::GenericNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::GenericNameSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getTypeArgumentList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::GenericNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::GenericNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::IdentifierNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::IdentifierNameSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::IdentifierNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ImplicitArrayCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ImplicitArrayCreationExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getInitializer())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ImplicitArrayCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ImplicitElementAccessSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ImplicitElementAccessSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ImplicitElementAccessSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ImplicitElementAccessSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ImplicitElementAccessSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::InitializerExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::InitializerExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::InitializerExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getExpressionsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::InitializerExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::InitializerExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::InterpolatedStringExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::InterpolatedStringExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::InterpolatedStringExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getContentsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::InterpolatedStringExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::InterpolatedStringExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::InvocationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::InvocationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::InvocationExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList() || node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::InvocationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::InvocationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::LiteralExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::LiteralExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::LiteralExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::LiteralExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::LiteralExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::MakeRefExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MakeRefExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::MakeRefExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::MakeRefExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MakeRefExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::MemberAccessExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MemberAccessExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::MemberAccessExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::MemberAccessExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MemberAccessExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::MemberBindingExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MemberBindingExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::MemberBindingExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::MemberBindingExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MemberBindingExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::NullableTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NullableTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::NullableTypeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getElementType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::NullableTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NullableTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ObjectCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ObjectCreationExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList() || node.getInitializer() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ObjectCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::OmittedArraySizeExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::OmittedArraySizeExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::OmittedArraySizeExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::OmittedArraySizeExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::OmittedArraySizeExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::OmittedTypeArgumentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::OmittedTypeArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::OmittedTypeArgumentSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::OmittedTypeArgumentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::OmittedTypeArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ParenthesizedExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ParenthesizedExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ParenthesizedExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ParenthesizedExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ParenthesizedExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ParenthesizedLambdaExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ParenthesizedLambdaExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getParameterList())
      hasChildNode = true;
    if(node.getBody())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ParenthesizedLambdaExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::PointerTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PointerTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::PointerTypeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getElementType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::PointerTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PointerTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::PostfixUnaryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PostfixUnaryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::PostfixUnaryExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getOperand())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::PostfixUnaryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PostfixUnaryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::PredefinedTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PredefinedTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::PredefinedTypeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::PredefinedTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PredefinedTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::PrefixUnaryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PrefixUnaryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::PrefixUnaryExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getOperand())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::PrefixUnaryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PrefixUnaryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::QualifiedNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::QualifiedNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::QualifiedNameSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getLeft() || node.getRight())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::QualifiedNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::QualifiedNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::QueryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::QueryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::QueryExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getBody() || node.getFromClause())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::QueryExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::QueryExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::RefTypeExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::RefTypeExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::RefTypeExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::RefTypeExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::RefTypeExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::RefValueExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::RefValueExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::RefValueExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::RefValueExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::RefValueExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::SimpleLambdaExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SimpleLambdaExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::SimpleLambdaExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getParameter())
      hasChildNode = true;
    if(node.getBody())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::SimpleLambdaExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SimpleLambdaExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::SizeOfExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SizeOfExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::SizeOfExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::SizeOfExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SizeOfExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::StackAllocArrayCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::StackAllocArrayCreationExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::StackAllocArrayCreationExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::ThisExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ThisExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::ThisExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::ThisExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ThisExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const expression::TypeOfExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TypeOfExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("expression::TypeOfExpressionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const expression::TypeOfExpressionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TypeOfExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::BlockSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::BlockSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getStatementsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::BlockSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::BreakStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BreakStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::BreakStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::BreakStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BreakStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::CheckedStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::CheckedStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::CheckedStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getBlock())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::CheckedStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::CheckedStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::ContinueStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ContinueStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::ContinueStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::ContinueStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ContinueStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::DoStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::DoStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::DoStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getCondition() || node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::DoStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::DoStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::EmptyStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::EmptyStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::EmptyStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::EmptyStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::EmptyStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::ExpressionStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ExpressionStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::ExpressionStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::ExpressionStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ExpressionStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::FixedStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::FixedStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::FixedStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getDeclaration() || node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::FixedStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::FixedStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::ForEachStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForEachStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::ForEachStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getStatement() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::ForEachStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForEachStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::ForStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::ForStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getCondition() || node.getDeclaration() || !node.getIncrementorsIsEmpty() || !node.getInitializersIsEmpty() || node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::ForStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::GotoStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::GotoStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::GotoStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::GotoStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::GotoStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::IfStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::IfStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::IfStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getCondition() || node.getElse() || node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::IfStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::IfStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::LabeledStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LabeledStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::LabeledStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::LabeledStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LabeledStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::LocalDeclarationStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LocalDeclarationStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::LocalDeclarationStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getDeclaration())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::LocalDeclarationStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LocalDeclarationStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::LockStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LockStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::LockStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::LockStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LockStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::ReturnStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ReturnStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::ReturnStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::ReturnStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ReturnStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::SwitchStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::SwitchStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::SwitchStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || !node.getSectionsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::SwitchStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::SwitchStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::ThrowStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ThrowStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::ThrowStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::ThrowStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ThrowStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::TryStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::TryStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::TryStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getBlock() || !node.getCatchesIsEmpty() || node.getFinally())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::TryStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::TryStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::UnsafeStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::UnsafeStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::UnsafeStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getBlock())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::UnsafeStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::UnsafeStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::UsingStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::UsingStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::UsingStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getDeclaration() || node.getExpression() || node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::UsingStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::UsingStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::WhileStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::WhileStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::WhileStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getCondition() || node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::WhileStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::WhileStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const statement::YieldStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::YieldStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("statement::YieldStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const statement::YieldStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::YieldStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AccessorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AccessorDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || node.getBody())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AccessorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AccessorListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AccessorListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AccessorListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAccessorsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AccessorListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AccessorListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AnonymousObjectMemberDeclaratorSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AnonymousObjectMemberDeclaratorSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getNameEquals())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AnonymousObjectMemberDeclaratorSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ArgumentListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getArgumentsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ArgumentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ArgumentSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getNameColon())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ArgumentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ArrayRankSpecifierSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArrayRankSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ArrayRankSpecifierSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getSizesIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ArrayRankSpecifierSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArrayRankSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ArrowExpressionClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ArrowExpressionClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ArrowExpressionClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AttributeArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AttributeArgumentListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getArgumentsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AttributeArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AttributeArgumentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AttributeArgumentSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getNameColon() || node.getNameEquals())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AttributeArgumentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AttributeListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AttributeListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributesIsEmpty() || node.getTarget())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AttributeListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AttributeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList() || node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::AttributeTargetSpecifierSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeTargetSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::AttributeTargetSpecifierSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::AttributeTargetSpecifierSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::AttributeTargetSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::BaseListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::BaseListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::BaseListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getTypesIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::BaseListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::BaseListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::BracketedArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::BracketedArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::BracketedArgumentListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getArgumentsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::BracketedArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::BracketedArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::BracketedParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::BracketedParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::BracketedParameterListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getParametersIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::BracketedParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::BracketedParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CaseSwitchLabelSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CaseSwitchLabelSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CaseSwitchLabelSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getValue())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CaseSwitchLabelSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CaseSwitchLabelSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CatchClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CatchClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CatchClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getBlock() || node.getDeclaration() || node.getFilter())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CatchClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CatchClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CatchDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CatchDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CatchDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CatchDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CatchDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CatchFilterClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CatchFilterClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CatchFilterClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getFilterExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CatchFilterClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CatchFilterClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ClassDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ClassDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ClassDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getConstraintClausesIsEmpty() || !node.getMembersIsEmpty() || node.getTypeParameterList())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBaseList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ClassDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ClassDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ClassOrStructConstraintSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ClassOrStructConstraintSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ClassOrStructConstraintSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ClassOrStructConstraintSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ClassOrStructConstraintSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CompilationUnitSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CompilationUnitSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CompilationUnitSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || !node.getExternsIsEmpty() || !node.getMembersIsEmpty() || !node.getUsingsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CompilationUnitSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CompilationUnitSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ConstructorConstraintSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConstructorConstraintSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ConstructorConstraintSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ConstructorConstraintSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConstructorConstraintSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ConstructorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConstructorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ConstructorDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getInitializer())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBody() || node.getParameterList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ConstructorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConstructorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ConstructorInitializerSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConstructorInitializerSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ConstructorInitializerSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ConstructorInitializerSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConstructorInitializerSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ConversionOperatorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConversionOperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ConversionOperatorDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpressionBody() || node.getType())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBody() || node.getParameterList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ConversionOperatorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConversionOperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ConversionOperatorMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConversionOperatorMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ConversionOperatorMemberCrefSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getParameters() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ConversionOperatorMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CrefBracketedParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CrefBracketedParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CrefBracketedParameterListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getParametersIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CrefBracketedParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CrefBracketedParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CrefParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CrefParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CrefParameterListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getParametersIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CrefParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CrefParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::CrefParameterSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CrefParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::CrefParameterSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::CrefParameterSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::CrefParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::DefaultSwitchLabelSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::DefaultSwitchLabelSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::DefaultSwitchLabelSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::DefaultSwitchLabelSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::DefaultSwitchLabelSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::DelegateDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::DelegateDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::DelegateDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || !node.getConstraintClausesIsEmpty() || node.getParameterList() || node.getReturnType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::DelegateDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::DelegateDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::DestructorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::DestructorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::DestructorDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || node.getBody() || node.getParameterList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::DestructorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::DestructorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ElseClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ElseClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ElseClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ElseClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ElseClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::EnumDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EnumDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::EnumDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getMembersIsEmpty())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBaseList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::EnumDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EnumDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::EnumMemberDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EnumMemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::EnumMemberDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || node.getEqualsValue())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::EnumMemberDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EnumMemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::EqualsValueClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EqualsValueClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::EqualsValueClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getValue())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::EqualsValueClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EqualsValueClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::EventDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EventDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::EventDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getAccessorList() || !node.getAttributeListsIsEmpty() || node.getExplicitInterfaceSpecifier() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::EventDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EventDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::EventFieldDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EventFieldDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::EventFieldDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || node.getDeclaration())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::EventFieldDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::EventFieldDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ExplicitInterfaceSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ExplicitInterfaceSpecifierSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ExplicitInterfaceSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ExternAliasDirectiveSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ExternAliasDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ExternAliasDirectiveSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ExternAliasDirectiveSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ExternAliasDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::FieldDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::FieldDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::FieldDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || node.getDeclaration())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::FieldDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::FieldDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::FinallyClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::FinallyClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::FinallyClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getBlock())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::FinallyClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::FinallyClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::FromClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::FromClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::FromClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::FromClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::FromClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::GlobalStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::GlobalStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::GlobalStatementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getStatement())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::GlobalStatementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::GlobalStatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::GroupClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::GroupClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::GroupClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getByExpression() || node.getGroupExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::GroupClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::GroupClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::IncompleteMemberSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::IncompleteMemberSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::IncompleteMemberSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::IncompleteMemberSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::IncompleteMemberSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::IndexerDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::IndexerDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::IndexerDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpressionBody() || node.getParameterList())
      hasChildNode = true;
    if(node.getAccessorList() || !node.getAttributeListsIsEmpty() || node.getExplicitInterfaceSpecifier() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::IndexerDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::IndexerDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::IndexerMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::IndexerMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::IndexerMemberCrefSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getParameters())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::IndexerMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::IndexerMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::InterfaceDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterfaceDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::InterfaceDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getConstraintClausesIsEmpty() || !node.getMembersIsEmpty() || node.getTypeParameterList())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBaseList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::InterfaceDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterfaceDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::InterpolatedStringTextSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolatedStringTextSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::InterpolatedStringTextSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::InterpolatedStringTextSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolatedStringTextSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::InterpolationAlignmentClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolationAlignmentClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::InterpolationAlignmentClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getValue())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::InterpolationAlignmentClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolationAlignmentClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::InterpolationFormatClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolationFormatClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::InterpolationFormatClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::InterpolationFormatClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolationFormatClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::InterpolationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::InterpolationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getAlignmentClause() || node.getExpression() || node.getFormatClause())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::InterpolationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::InterpolationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::JoinClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::JoinClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::JoinClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getInExpression() || node.getInto() || node.getLeftExpression() || node.getRightExpression() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::JoinClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::JoinClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::JoinIntoClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::JoinIntoClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::JoinIntoClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::JoinIntoClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::JoinIntoClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::LetClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::LetClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::LetClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::LetClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::LetClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::MethodDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::MethodDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::MethodDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getConstraintClausesIsEmpty() || node.getExplicitInterfaceSpecifier() || node.getExpressionBody() || node.getReturnType())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBody() || node.getParameterList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::MethodDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::MethodDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::NameColonSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NameColonSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::NameColonSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::NameColonSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NameColonSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::NameEqualsSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NameEqualsSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::NameEqualsSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::NameEqualsSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NameEqualsSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::NameMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NameMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::NameMemberCrefSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName() || node.getParameters())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::NameMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NameMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::NamespaceDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NamespaceDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::NamespaceDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getExternsIsEmpty() || !node.getMembersIsEmpty() || node.getName() || !node.getUsingsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::NamespaceDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::NamespaceDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::OperatorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::OperatorDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpressionBody() || node.getReturnType())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBody() || node.getParameterList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::OperatorDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::OperatorMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OperatorMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::OperatorMemberCrefSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getParameters())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::OperatorMemberCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OperatorMemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::OrderByClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OrderByClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::OrderByClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getOrderingsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::OrderByClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OrderByClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::OrderingSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OrderingSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::OrderingSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::OrderingSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::OrderingSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ParameterListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getParametersIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::ParameterSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::ParameterSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty() || node.getDefault() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::ParameterSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::PropertyDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::PropertyDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::PropertyDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpressionBody() || node.getInitializer())
      hasChildNode = true;
    if(node.getAccessorList() || !node.getAttributeListsIsEmpty() || node.getExplicitInterfaceSpecifier() || node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::PropertyDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::PropertyDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::QualifiedCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::QualifiedCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::QualifiedCrefSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getContainer() || node.getMember())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::QualifiedCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::QualifiedCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::QueryBodySyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::QueryBodySyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::QueryBodySyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getClausesIsEmpty() || node.getContinuation() || node.getSelectOrGroup())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::QueryBodySyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::QueryBodySyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::QueryContinuationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::QueryContinuationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::QueryContinuationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getBody())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::QueryContinuationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::QueryContinuationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::SelectClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SelectClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::SelectClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getExpression())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::SelectClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SelectClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::SimpleBaseTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SimpleBaseTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::SimpleBaseTypeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::SimpleBaseTypeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SimpleBaseTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::StructDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::StructDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::StructDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getConstraintClausesIsEmpty() || !node.getMembersIsEmpty() || node.getTypeParameterList())
      hasChildNode = true;
    if(!node.getAttributeListsIsEmpty() || node.getBaseList())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::StructDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::StructDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::SwitchSectionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SwitchSectionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::SwitchSectionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getLabelsIsEmpty() || !node.getStatementsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::SwitchSectionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SwitchSectionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::SyntaxToken& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SyntaxToken") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::SyntaxToken");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::SyntaxToken& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::SyntaxToken") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::TypeArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::TypeArgumentListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getArgumentsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::TypeArgumentListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::TypeConstraintSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeConstraintSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::TypeConstraintSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::TypeConstraintSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeConstraintSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::TypeCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::TypeCrefSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::TypeCrefSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::TypeParameterConstraintClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeParameterConstraintClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::TypeParameterConstraintClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getConstraintsIsEmpty() || node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::TypeParameterConstraintClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeParameterConstraintClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::TypeParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::TypeParameterListSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::TypeParameterListSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::TypeParameterSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::TypeParameterSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributeListsIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::TypeParameterSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::TypeParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::UsingDirectiveSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::UsingDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::UsingDirectiveSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getAlias() || node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::UsingDirectiveSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::UsingDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::VariableDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::VariableDeclarationSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getType() || !node.getVariablesIsEmpty())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::VariableDeclarationSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::VariableDeclaratorSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::VariableDeclaratorSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::VariableDeclaratorSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getArgumentList() || node.getInitializer())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::VariableDeclaratorSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::VariableDeclaratorSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::WhereClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::WhereClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::WhereClauseSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getCondition())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::WhereClauseSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::WhereClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlCDataSectionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlCDataSectionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlCDataSectionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlCDataSectionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlCDataSectionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlCommentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlCommentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlCommentSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlCommentSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlCommentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlCrefAttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlCrefAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlCrefAttributeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getCref())
      hasChildNode = true;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlCrefAttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlCrefAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlElementEndTagSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlElementEndTagSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlElementEndTagSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlElementEndTagSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlElementEndTagSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlElementStartTagSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlElementStartTagSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlElementStartTagSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributesIsEmpty() || node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlElementStartTagSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlElementStartTagSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlElementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlElementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlElementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getContentIsEmpty() || node.getEndTag() || node.getStartTag())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlElementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlElementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlEmptyElementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlEmptyElementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlEmptyElementSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(!node.getAttributesIsEmpty() || node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlEmptyElementSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlEmptyElementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlNameAttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlNameAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlNameAttributeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getIdentifier())
      hasChildNode = true;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlNameAttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlNameAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlNameSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getPrefix())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlNameSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlPrefixSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlPrefixSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlPrefixSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlPrefixSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlPrefixSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlProcessingInstructionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlProcessingInstructionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlProcessingInstructionSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlProcessingInstructionSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlProcessingInstructionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlTextAttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlTextAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlTextAttributeSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    bool hasChildNode = false;
    if(node.getName())
      hasChildNode = true;
    if(hasChildNode){
      io.writeGroupNodeBegin(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }else{
      io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
    }
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlTextAttributeSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlTextAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(lastVisitedNodeId != node.getId())
      io.writeGroupNodeEnd();
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void VisitorGraphml::visit(const structure::XmlTextSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlTextSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("structure::XmlTextSyntax");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
    if(node.getParent() && (edgeKindStack.begin() == edgeKindStack.end() || (edgeKindStack.begin() != edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())))){
      std::string edgename = Common::toString(node.getParentEdgeKind());
      io.writeGroupNodeBegin(Common::toString(node.getParent()->getId())+edgename.substr(edgename.find('_')), edgename.substr(edgename.find('_')+1), "", titleBGColor, "", titleBGColor);
      edgeKindStack.push_front(node.getParentEdgeKind());
      parentNodeStack.push_front(node.getParent()->getId());
    }
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }else{
    io.writeNode(Common::toString(node.getId()), title, content, titleBGColor, "", fillColor);
  }
  lastVisitedNodeId = node.getId();
}

void VisitorGraphml::visitEnd(const structure::XmlTextSyntax& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::XmlTextSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin()!=edgeKindStack.end() && (*(edgeKindStack.begin()) != node.getParentEdgeKind() || *(parentNodeStack.begin()) != node.getParent()->getId())){
      io.writeGroupNodeEnd();
      edgeKindStack.pop_front();
      parentNodeStack.pop_front();
    }
  }
}

void  VisitorGraphml::visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AliasQualifiedNameSyntax_Alias") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AliasQualifiedNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AliasQualifiedNameSyntax_Alias", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AliasQualifiedNameSyntax_Alias", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AliasQualifiedNameSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AliasQualifiedNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::SimpleNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AliasQualifiedNameSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AliasQualifiedNameSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AnonymousFunctionExpressionSyntax_Body") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AnonymousFunctionExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousFunctionExpressionSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousFunctionExpressionSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AnonymousMethodExpressionSyntax_ParameterList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AnonymousMethodExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousMethodExpressionSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousMethodExpressionSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AnonymousObjectCreationExpressionSyntax_Initializers") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AnonymousObjectCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AnonymousObjectMemberDeclaratorSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousObjectCreationExpressionSyntax_Initializers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousObjectCreationExpressionSyntax_Initializers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrayCreationExpressionSyntax_Initializer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ArrayCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::InitializerExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayCreationExpressionSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayCreationExpressionSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrayCreationExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ArrayCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ArrayTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayCreationExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayCreationExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrayTypeSyntax_ElementType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ArrayTypeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayTypeSyntax_ElementType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayTypeSyntax_ElementType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrayTypeSyntax_RankSpecifiers") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ArrayTypeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArrayRankSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayTypeSyntax_RankSpecifiers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayTypeSyntax_RankSpecifiers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentExpressionSyntax_EventAccessorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AssignmentExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_EventAccessorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_EventAccessorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentExpressionSyntax_Left") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AssignmentExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_Left", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_Left", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentExpressionSyntax_OverloadedOperatorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AssignmentExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentExpressionSyntax_Right") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AssignmentExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_Right", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpressionSyntax_Right", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AwaitExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AwaitExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AwaitExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AwaitExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BinaryExpressionSyntax_Left") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::BinaryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpressionSyntax_Left", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpressionSyntax_Left", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BinaryExpressionSyntax_OverloadedOperatorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::BinaryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BinaryExpressionSyntax_Right") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::BinaryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpressionSyntax_Right", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpressionSyntax_Right", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CastExpressionSyntax_ConversionOperatorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::CastExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ConversionOperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CastExpressionSyntax_ConversionOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CastExpressionSyntax_ConversionOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CastExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::CastExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CastExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CastExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CastExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::CastExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CastExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CastExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CheckedExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::CheckedExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CheckedExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CheckedExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalAccessExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalAccessExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalAccessExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalAccessExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalAccessExpressionSyntax_WhenNotNull") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalAccessExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalAccessExpressionSyntax_WhenNotNull", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalAccessExpressionSyntax_WhenNotNull", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalExpressionSyntax_Condition") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpressionSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpressionSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalExpressionSyntax_WhenFalse") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpressionSyntax_WhenFalse", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpressionSyntax_WhenFalse", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalExpressionSyntax_WhenTrue") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpressionSyntax_WhenTrue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpressionSyntax_WhenTrue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DefaultExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::DefaultExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DefaultExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DefaultExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ElementAccessExpressionSyntax_AccessorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ElementAccessExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementAccessExpressionSyntax_AccessorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementAccessExpressionSyntax_AccessorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ElementAccessExpressionSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ElementAccessExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::BracketedArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementAccessExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementAccessExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ElementAccessExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ElementAccessExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementAccessExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementAccessExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ElementBindingExpressionSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ElementBindingExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::BracketedArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementBindingExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ElementBindingExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("GenericNameSyntax_TypeArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::GenericNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::TypeArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "GenericNameSyntax_TypeArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "GenericNameSyntax_TypeArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IdentifierNameSyntax_AccessorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IdentifierNameSyntax_AccessorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IdentifierNameSyntax_AccessorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IdentifierNameSyntax_Declaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IdentifierNameSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IdentifierNameSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ImplicitArrayCreationExpressionSyntax_Initializer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ImplicitArrayCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::InitializerExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ImplicitArrayCreationExpressionSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ImplicitArrayCreationExpressionSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ImplicitElementAccessSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ImplicitElementAccessSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::BracketedArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ImplicitElementAccessSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ImplicitElementAccessSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InitializerExpressionSyntax_Expressions") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::InitializerExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InitializerExpressionSyntax_Expressions", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InitializerExpressionSyntax_Expressions", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InterpolatedStringExpressionSyntax_Contents") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::InterpolatedStringExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::InterpolatedStringContentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolatedStringExpressionSyntax_Contents", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolatedStringExpressionSyntax_Contents", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InvocationExpressionSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::InvocationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InvocationExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InvocationExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InvocationExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::InvocationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InvocationExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InvocationExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InvocationExpressionSyntax_MethodCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::InvocationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::MethodDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InvocationExpressionSyntax_MethodCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InvocationExpressionSyntax_MethodCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MakeRefExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MakeRefExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MakeRefExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MakeRefExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MemberAccessExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MemberAccessExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberAccessExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberAccessExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MemberAccessExpressionSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MemberAccessExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::SimpleNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberAccessExpressionSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberAccessExpressionSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MemberBindingExpressionSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MemberBindingExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::SimpleNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberBindingExpressionSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberBindingExpressionSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NullableTypeSyntax_ElementType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::NullableTypeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NullableTypeSyntax_ElementType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NullableTypeSyntax_ElementType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ObjectCreationExpressionSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ObjectCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ObjectCreationExpressionSyntax_ConstructorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ObjectCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ConstructorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_ConstructorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_ConstructorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ObjectCreationExpressionSyntax_Initializer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ObjectCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::InitializerExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ObjectCreationExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ObjectCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectCreationExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ParenthesizedExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ParenthesizedExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ParenthesizedExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ParenthesizedExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ParenthesizedLambdaExpressionSyntax_ParameterList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ParenthesizedLambdaExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ParenthesizedLambdaExpressionSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ParenthesizedLambdaExpressionSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PointerTypeSyntax_ElementType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::PointerTypeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PointerTypeSyntax_ElementType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PointerTypeSyntax_ElementType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PostfixUnaryExpressionSyntax_Operand") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::PostfixUnaryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PostfixUnaryExpressionSyntax_Operand", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PostfixUnaryExpressionSyntax_Operand", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PostfixUnaryExpressionSyntax_OverloadedOperatorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::PostfixUnaryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PostfixUnaryExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PostfixUnaryExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PrefixUnaryExpressionSyntax_Operand") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::PrefixUnaryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PrefixUnaryExpressionSyntax_Operand", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PrefixUnaryExpressionSyntax_Operand", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PrefixUnaryExpressionSyntax_OverloadedOperatorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::PrefixUnaryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PrefixUnaryExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PrefixUnaryExpressionSyntax_OverloadedOperatorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QualifiedNameSyntax_Left") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::QualifiedNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::NameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedNameSyntax_Left", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedNameSyntax_Left", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QualifiedNameSyntax_Right") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::QualifiedNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::SimpleNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedNameSyntax_Right", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedNameSyntax_Right", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QueryExpressionSyntax_Body") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::QueryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::QueryBodySyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryExpressionSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryExpressionSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QueryExpressionSyntax_FromClause") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::QueryExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::FromClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryExpressionSyntax_FromClause", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryExpressionSyntax_FromClause", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("RefTypeExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::RefTypeExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "RefTypeExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "RefTypeExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("RefValueExpressionSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::RefValueExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "RefValueExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "RefValueExpressionSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("RefValueExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::RefValueExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "RefValueExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "RefValueExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SimpleLambdaExpressionSyntax_Parameter") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::SimpleLambdaExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SimpleLambdaExpressionSyntax_Parameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SimpleLambdaExpressionSyntax_Parameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SizeOfExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::SizeOfExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SizeOfExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SizeOfExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("StackAllocArrayCreationExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::StackAllocArrayCreationExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "StackAllocArrayCreationExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "StackAllocArrayCreationExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeOfExpressionSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::TypeOfExpressionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeOfExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeOfExpressionSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeSyntax_OriginalDefinition") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::MemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeSyntax_OriginalDefinition", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeSyntax_OriginalDefinition", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BlockSyntax_Statements") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BlockSyntax_Statements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BlockSyntax_Statements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CheckedStatementSyntax_Block") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::CheckedStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CheckedStatementSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CheckedStatementSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DoStatementSyntax_Condition") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::DoStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DoStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DoStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DoStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::DoStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DoStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DoStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExpressionStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ExpressionStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExpressionStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExpressionStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("FixedStatementSyntax_Declaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::FixedStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "FixedStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "FixedStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("FixedStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::FixedStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "FixedStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "FixedStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForEachStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForEachStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForEachStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForEachStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForEachStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForEachStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForEachStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForEachStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForEachStatementSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForEachStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForEachStatementSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForEachStatementSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatementSyntax_Condition") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatementSyntax_Declaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatementSyntax_Incrementors") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Incrementors", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Incrementors", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatementSyntax_Initializers") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Initializers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Initializers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("GotoStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::GotoStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "GotoStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "GotoStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IfStatementSyntax_Condition") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::IfStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IfStatementSyntax_Else") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::IfStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ElseClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatementSyntax_Else", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatementSyntax_Else", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IfStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::IfStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LabeledStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::LabeledStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LabeledStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LabeledStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LocalDeclarationStatementSyntax_Declaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::LocalDeclarationStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LocalDeclarationStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LocalDeclarationStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LockStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::LockStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LockStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LockStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LockStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::LockStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LockStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LockStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ReturnStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ReturnStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ReturnStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ReturnStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::SwitchStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchStatementSyntax_Sections") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::SwitchStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::SwitchSectionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatementSyntax_Sections", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatementSyntax_Sections", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ThrowStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ThrowStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ThrowStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ThrowStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TryStatementSyntax_Block") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::TryStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatementSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatementSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TryStatementSyntax_Catches") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::TryStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CatchClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatementSyntax_Catches", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatementSyntax_Catches", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TryStatementSyntax_Finally") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::TryStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::FinallyClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatementSyntax_Finally", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatementSyntax_Finally", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UnsafeStatementSyntax_Block") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::UnsafeStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UnsafeStatementSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UnsafeStatementSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UsingStatementSyntax_Declaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::UsingStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingStatementSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UsingStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::UsingStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UsingStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::UsingStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("WhileStatementSyntax_Condition") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::WhileStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatementSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("WhileStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::WhileStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("YieldStatementSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::YieldStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "YieldStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "YieldStatementSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AccessorDeclarationSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AccessorDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AccessorDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AccessorDeclarationSyntax_Body") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AccessorDeclarationSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AccessorDeclarationSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AccessorListSyntax_Accessors") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AccessorListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AccessorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AccessorListSyntax_Accessors", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AccessorListSyntax_Accessors", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AnonymousObjectMemberDeclaratorSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AnonymousObjectMemberDeclaratorSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousObjectMemberDeclaratorSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousObjectMemberDeclaratorSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AnonymousObjectMemberDeclaratorSyntax_NameEquals") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AnonymousObjectMemberDeclaratorSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::NameEqualsSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousObjectMemberDeclaratorSyntax_NameEquals", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AnonymousObjectMemberDeclaratorSyntax_NameEquals", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArgumentSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ArgumentSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArgumentSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArgumentSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArgumentSyntax_NameColon") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ArgumentSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::NameColonSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArgumentSyntax_NameColon", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArgumentSyntax_NameColon", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrayRankSpecifierSyntax_Sizes") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ArrayRankSpecifierSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayRankSpecifierSyntax_Sizes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayRankSpecifierSyntax_Sizes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrowExpressionClauseSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrowExpressionClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrowExpressionClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeArgumentListSyntax_Arguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeArgumentListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentListSyntax_Arguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentListSyntax_Arguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeArgumentSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeArgumentSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeArgumentSyntax_NameColon") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeArgumentSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::NameColonSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentSyntax_NameColon", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentSyntax_NameColon", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeArgumentSyntax_NameEquals") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeArgumentSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::NameEqualsSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentSyntax_NameEquals", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeArgumentSyntax_NameEquals", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeListSyntax_Attributes") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeListSyntax_Attributes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeListSyntax_Attributes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeListSyntax_Target") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeTargetSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeListSyntax_Target", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeListSyntax_Target", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::AttributeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::NameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseArgumentListSyntax_Arguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseArgumentListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArgumentSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseArgumentListSyntax_Arguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseArgumentListSyntax_Arguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseCrefParameterListSyntax_Parameters") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseCrefParameterListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CrefParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseCrefParameterListSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseCrefParameterListSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseFieldDeclarationSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseFieldDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseFieldDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseFieldDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseFieldDeclarationSyntax_Declaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseFieldDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseFieldDeclarationSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseFieldDeclarationSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseListSyntax_Types") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::BaseTypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseListSyntax_Types", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseListSyntax_Types", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseMethodDeclarationSyntax_AccessedEnumMembers") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseMethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::EnumMemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_AccessedEnumMembers", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_AccessedEnumMembers", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseMethodDeclarationSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseMethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseMethodDeclarationSyntax_Body") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseMethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseMethodDeclarationSyntax_ParameterList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseMethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseMethodDeclarationSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseParameterListSyntax_Parameters") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseParameterListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseParameterListSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseParameterListSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BasePropertyDeclarationSyntax_AccessorList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BasePropertyDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AccessorListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_AccessorList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_AccessorList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BasePropertyDeclarationSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BasePropertyDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BasePropertyDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ExplicitInterfaceSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BasePropertyDeclarationSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BasePropertyDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BasePropertyDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseTypeDeclarationSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseTypeDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseTypeDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseTypeDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseTypeDeclarationSyntax_BaseList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseTypeDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::BaseListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseTypeDeclarationSyntax_BaseList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseTypeDeclarationSyntax_BaseList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BaseTypeSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::BaseTypeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseTypeSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BaseTypeSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CaseSwitchLabelSyntax_Value") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CaseSwitchLabelSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CaseSwitchLabelSyntax_Value", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CaseSwitchLabelSyntax_Value", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CatchClauseSyntax_Block") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CatchClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClauseSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClauseSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CatchClauseSyntax_Declaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CatchClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CatchDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClauseSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClauseSyntax_Declaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CatchClauseSyntax_Filter") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CatchClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CatchFilterClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClauseSyntax_Filter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClauseSyntax_Filter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CatchDeclarationSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CatchDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CatchFilterClauseSyntax_FilterExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CatchFilterClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchFilterClauseSyntax_FilterExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchFilterClauseSyntax_FilterExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CompilationUnitSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CompilationUnitSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CompilationUnitSyntax_Externs") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CompilationUnitSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ExternAliasDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_Externs", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_Externs", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CompilationUnitSyntax_Members") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CompilationUnitSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::MemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CompilationUnitSyntax_Usings") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CompilationUnitSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::UsingDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_Usings", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CompilationUnitSyntax_Usings", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConstructorDeclarationSyntax_Initializer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ConstructorDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ConstructorInitializerSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConstructorDeclarationSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConstructorDeclarationSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConstructorInitializerSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ConstructorInitializerSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConstructorInitializerSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConstructorInitializerSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConstructorInitializerSyntax_ConstructorCall") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ConstructorInitializerSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ConstructorDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConstructorInitializerSyntax_ConstructorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConstructorInitializerSyntax_ConstructorCall", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConversionOperatorDeclarationSyntax_ExpressionBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ConversionOperatorDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConversionOperatorDeclarationSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ConversionOperatorDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConversionOperatorMemberCrefSyntax_Parameters") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ConversionOperatorMemberCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CrefParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConversionOperatorMemberCrefSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ConversionOperatorMemberCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorMemberCrefSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConversionOperatorMemberCrefSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CrefParameterSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::CrefParameterSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CrefParameterSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CrefParameterSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DelegateDeclarationSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::DelegateDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DelegateDeclarationSyntax_ConstraintClauses") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::DelegateDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::TypeParameterConstraintClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_ConstraintClauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_ConstraintClauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DelegateDeclarationSyntax_ParameterList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::DelegateDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DelegateDeclarationSyntax_ReturnType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::DelegateDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_ReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DelegateDeclarationSyntax_ReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ElseClauseSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ElseClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ElseClauseSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ElseClauseSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("EnumDeclarationSyntax_Members") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::EnumDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::EnumMemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "EnumDeclarationSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "EnumDeclarationSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("EnumMemberDeclarationSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::EnumMemberDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "EnumMemberDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "EnumMemberDeclarationSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("EnumMemberDeclarationSyntax_EqualsValue") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::EnumMemberDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::EqualsValueClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "EnumMemberDeclarationSyntax_EqualsValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "EnumMemberDeclarationSyntax_EqualsValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("EqualsValueClauseSyntax_Value") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::EqualsValueClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "EqualsValueClauseSyntax_Value", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "EqualsValueClauseSyntax_Value", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExplicitInterfaceSpecifierSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ExplicitInterfaceSpecifierSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::NameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExplicitInterfaceSpecifierSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExplicitInterfaceSpecifierSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("FinallyClauseSyntax_Block") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::FinallyClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "FinallyClauseSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "FinallyClauseSyntax_Block", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("FromClauseSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::FromClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "FromClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "FromClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("FromClauseSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::FromClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "FromClauseSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "FromClauseSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("GlobalStatementSyntax_Statement") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::GlobalStatementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "GlobalStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "GlobalStatementSyntax_Statement", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("GroupClauseSyntax_ByExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::GroupClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "GroupClauseSyntax_ByExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "GroupClauseSyntax_ByExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("GroupClauseSyntax_GroupExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::GroupClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "GroupClauseSyntax_GroupExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "GroupClauseSyntax_GroupExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IncompleteMemberSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::IncompleteMemberSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IncompleteMemberSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IncompleteMemberSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IncompleteMemberSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::IncompleteMemberSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IncompleteMemberSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IncompleteMemberSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IndexerDeclarationSyntax_ExpressionBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::IndexerDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IndexerDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IndexerDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IndexerDeclarationSyntax_ParameterList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::IndexerDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::BracketedParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IndexerDeclarationSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IndexerDeclarationSyntax_ParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IndexerMemberCrefSyntax_Parameters") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::IndexerMemberCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CrefBracketedParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IndexerMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IndexerMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InterpolationAlignmentClauseSyntax_Value") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::InterpolationAlignmentClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationAlignmentClauseSyntax_Value", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationAlignmentClauseSyntax_Value", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InterpolationSyntax_AlignmentClause") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::InterpolationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::InterpolationAlignmentClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationSyntax_AlignmentClause", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationSyntax_AlignmentClause", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InterpolationSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::InterpolationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("InterpolationSyntax_FormatClause") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::InterpolationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::InterpolationFormatClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationSyntax_FormatClause", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "InterpolationSyntax_FormatClause", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("JoinClauseSyntax_InExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::JoinClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_InExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_InExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("JoinClauseSyntax_Into") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::JoinClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::JoinIntoClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_Into", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_Into", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("JoinClauseSyntax_LeftExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::JoinClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_LeftExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_LeftExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("JoinClauseSyntax_RightExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::JoinClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_RightExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_RightExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("JoinClauseSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::JoinClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "JoinClauseSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LetClauseSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::LetClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LetClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LetClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodDeclarationSyntax_ConstraintClauses") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::MethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::TypeParameterConstraintClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ConstraintClauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ConstraintClauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodDeclarationSyntax_ExplicitInterfaceSpecifier") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::MethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ExplicitInterfaceSpecifierSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ExplicitInterfaceSpecifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ExplicitInterfaceSpecifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodDeclarationSyntax_ExpressionBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::MethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodDeclarationSyntax_ReturnType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::MethodDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDeclarationSyntax_ReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NameColonSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NameColonSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NameColonSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NameColonSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NameEqualsSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NameEqualsSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NameEqualsSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NameEqualsSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NameMemberCrefSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NameMemberCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NameMemberCrefSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NameMemberCrefSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NameMemberCrefSyntax_Parameters") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NameMemberCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CrefParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NameMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NameMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NamespaceDeclarationSyntax_Externs") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NamespaceDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ExternAliasDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Externs", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Externs", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NamespaceDeclarationSyntax_Members") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NamespaceDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::MemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NamespaceDeclarationSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NamespaceDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::NameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NamespaceDeclarationSyntax_Usings") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::NamespaceDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::UsingDirectiveSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Usings", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NamespaceDeclarationSyntax_Usings", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("OperatorDeclarationSyntax_ExpressionBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "OperatorDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "OperatorDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("OperatorDeclarationSyntax_ReturnType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::OperatorDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "OperatorDeclarationSyntax_ReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "OperatorDeclarationSyntax_ReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("OperatorMemberCrefSyntax_Parameters") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::OperatorMemberCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CrefParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "OperatorMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "OperatorMemberCrefSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("OrderByClauseSyntax_Orderings") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::OrderByClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::OrderingSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "OrderByClauseSyntax_Orderings", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "OrderByClauseSyntax_Orderings", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("OrderingSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::OrderingSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "OrderingSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "OrderingSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ParameterSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ParameterSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ParameterSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ParameterSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ParameterSyntax_Default") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ParameterSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::EqualsValueClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ParameterSyntax_Default", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ParameterSyntax_Default", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ParameterSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ParameterSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ParameterSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ParameterSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PropertyDeclarationSyntax_ExpressionBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::PropertyDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ArrowExpressionClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDeclarationSyntax_ExpressionBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PropertyDeclarationSyntax_Initializer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::PropertyDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::EqualsValueClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDeclarationSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDeclarationSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QualifiedCrefSyntax_Container") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::QualifiedCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedCrefSyntax_Container", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedCrefSyntax_Container", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QualifiedCrefSyntax_Member") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::QualifiedCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::MemberCrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedCrefSyntax_Member", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QualifiedCrefSyntax_Member", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QueryBodySyntax_Clauses") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::QueryBodySyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::QueryClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryBodySyntax_Clauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryBodySyntax_Clauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QueryBodySyntax_Continuation") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::QueryBodySyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::QueryContinuationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryBodySyntax_Continuation", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryBodySyntax_Continuation", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QueryBodySyntax_SelectOrGroup") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::QueryBodySyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::SelectOrGroupClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryBodySyntax_SelectOrGroup", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryBodySyntax_SelectOrGroup", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("QueryContinuationSyntax_Body") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::QueryContinuationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::QueryBodySyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryContinuationSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "QueryContinuationSyntax_Body", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SelectClauseSyntax_Expression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::SelectClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SelectClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SelectClauseSyntax_Expression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchSectionSyntax_Labels") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::SwitchSectionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::SwitchLabelSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchSectionSyntax_Labels", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchSectionSyntax_Labels", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchSectionSyntax_Statements") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::SwitchSectionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::StatementSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchSectionSyntax_Statements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchSectionSyntax_Statements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeArgumentListSyntax_Arguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeArgumentListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeArgumentListSyntax_Arguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeArgumentListSyntax_Arguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeConstraintSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeConstraintSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeConstraintSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeConstraintSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeCrefSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeCrefSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeCrefSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeCrefSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeDeclarationSyntax_ConstraintClauses") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::TypeParameterConstraintClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeDeclarationSyntax_ConstraintClauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeDeclarationSyntax_ConstraintClauses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeDeclarationSyntax_Members") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::MemberDeclarationSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeDeclarationSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeDeclarationSyntax_Members", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeDeclarationSyntax_TypeParameterList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::TypeParameterListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeDeclarationSyntax_TypeParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeDeclarationSyntax_TypeParameterList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeParameterConstraintClauseSyntax_Constraints") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeParameterConstraintClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::TypeParameterConstraintSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterConstraintClauseSyntax_Constraints", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterConstraintClauseSyntax_Constraints", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeParameterConstraintClauseSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeParameterConstraintClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterConstraintClauseSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterConstraintClauseSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeParameterListSyntax_Parameters") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeParameterListSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::TypeParameterSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterListSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterListSyntax_Parameters", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeParameterSyntax_AttributeLists") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::TypeParameterSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::AttributeListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeParameterSyntax_AttributeLists", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UsingDirectiveSyntax_Alias") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::UsingDirectiveSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::NameEqualsSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingDirectiveSyntax_Alias", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingDirectiveSyntax_Alias", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UsingDirectiveSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::UsingDirectiveSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::NameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingDirectiveSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UsingDirectiveSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("VariableDeclarationSyntax_Type") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TypeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarationSyntax_Type", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("VariableDeclarationSyntax_Variables") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::VariableDeclarationSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::VariableDeclaratorSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarationSyntax_Variables", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarationSyntax_Variables", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("VariableDeclaratorSyntax_ArgumentList") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::VariableDeclaratorSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::BracketedArgumentListSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclaratorSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclaratorSyntax_ArgumentList", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("VariableDeclaratorSyntax_Initializer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::VariableDeclaratorSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::EqualsValueClauseSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclaratorSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclaratorSyntax_Initializer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("WhereClauseSyntax_Condition") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::WhereClauseSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ExpressionSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "WhereClauseSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "WhereClauseSyntax_Condition", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlAttributeSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlAttributeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlAttributeSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlAttributeSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlCrefAttributeSyntax_Cref") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlCrefAttributeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::CrefSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlCrefAttributeSyntax_Cref", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlCrefAttributeSyntax_Cref", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlElementEndTagSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlElementEndTagSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementEndTagSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementEndTagSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlElementStartTagSyntax_Attributes") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlElementStartTagSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementStartTagSyntax_Attributes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementStartTagSyntax_Attributes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlElementStartTagSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlElementStartTagSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementStartTagSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementStartTagSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlElementSyntax_Content") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlElementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlNodeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementSyntax_Content", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementSyntax_Content", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlElementSyntax_EndTag") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlElementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlElementEndTagSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementSyntax_EndTag", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementSyntax_EndTag", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlElementSyntax_StartTag") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlElementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlElementStartTagSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementSyntax_StartTag", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlElementSyntax_StartTag", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlEmptyElementSyntax_Attributes") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlEmptyElementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlAttributeSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlEmptyElementSyntax_Attributes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlEmptyElementSyntax_Attributes", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlEmptyElementSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlEmptyElementSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlEmptyElementSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlEmptyElementSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlNameAttributeSyntax_Identifier") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlNameAttributeSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::IdentifierNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlNameAttributeSyntax_Identifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlNameAttributeSyntax_Identifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlNameSyntax_Prefix") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlPrefixSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlNameSyntax_Prefix", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlNameSyntax_Prefix", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("XmlProcessingInstructionSyntax_Name") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::XmlProcessingInstructionSyntax") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::XmlNameSyntax") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlProcessingInstructionSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "XmlProcessingInstructionSyntax_Name", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}


}}}
