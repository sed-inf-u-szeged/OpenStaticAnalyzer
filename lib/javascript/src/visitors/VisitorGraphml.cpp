/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
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

#include "javascript/inc/javascript.h"
#include "common/inc/StringSup.h"
#include <set>
#include <string>

using namespace columbus::io;

namespace columbus { namespace javascript { namespace asg {

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

static const std::string getRangeContent(const Range& range) {
  std::string content;
  content += "path : " + range.getPath() + ", ";
  content += "line : " + common::toString(range.getLine()) + ", ";
  content += "col : " + common::toString(range.getCol()) + ", ";
  content += "endLine : " + common::toString(range.getEndLine()) + ", ";
  content += "endCol : " + common::toString(range.getEndCol());
  content += ", ";
  content += "wideLine : " + common::toString(range.getWideLine()) + ", ";
  content += "wideCol : " + common::toString(range.getWideCol()) + ", ";
  content += "wideEndLine : " + common::toString(range.getWideEndLine()) + ", ";
  content += "wideEndCol : " + common::toString(range.getWideEndCol());
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
  content += "id : " + Common::toString(node.getId()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const base::Comment& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Comment") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "text : " + node.getText() + "\n";
  content += "type : " + Common::toString(node.getType()) + "\n";
  content += "location : " + Common::toString(node.getLocation()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const base::Named& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Named") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "name : " + node.getName() + "\n";
}

void VisitorGraphml::addAttributeToContent(const base::Positioned& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Positioned") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "position : [" + getRangeContent(node.getPosition()) + "]\n";
}

void VisitorGraphml::addAttributeToContent(const base::Program& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Program") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "sourceType : " + Common::toString(node.getSourceType()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const base::System& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::System") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::ClassDeclaration& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const declaration::Declaration&>(node), content, false);
  addAttributeToContent(static_cast<const structure::Class&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::ClassDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::Declaration& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::Declaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::ExportAllDeclaration& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const declaration::Declaration&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::ExportAllDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::ExportDefaultDeclaration& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const declaration::Declaration&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::ExportDefaultDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::ExportNamedDeclaration& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const declaration::ModuleDeclaration&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::ExportNamedDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::FunctionDeclaration& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Function&>(node), content, false);
  addAttributeToContent(static_cast<const declaration::Declaration&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::FunctionDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::ImportDeclaration& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const declaration::ModuleDeclaration&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::ImportDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::ModuleDeclaration& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::ModuleDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const declaration::VariableDeclaration& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const declaration::Declaration&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::VariableDeclaration") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "kind : " + Common::toString(node.getKind()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const declaration::VariableDeclarator& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("declaration::VariableDeclarator") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ArrayExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ArrayExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ArrowFunctionExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  addAttributeToContent(static_cast<const statement::Function&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ArrowFunctionExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "expression : " + std::string(node.getExpression() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::AssignmentExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AssignmentExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "operator : " + Common::toString(node.getOperator()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::AwaitExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::AwaitExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::BigIntLiteral& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Literal&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::BigIntLiteral") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "bigint : " + node.getBigint() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::BinaryExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::BinaryExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "operator : " + Common::toString(node.getOperator()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::BooleanLiteral& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Literal&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::BooleanLiteral") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "value : " + std::string(node.getValue() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::CallExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  addAttributeToContent(static_cast<const expression::ChainElement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::CallExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ChainElement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ChainElement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "optional : " + std::string(node.getOptional() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::ChainExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ChainExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ClassExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  addAttributeToContent(static_cast<const structure::Class&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ClassExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ConditionalExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ConditionalExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::Expression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::Expression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::FunctionExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  addAttributeToContent(static_cast<const statement::Function&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::FunctionExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "expression : " + std::string(node.getExpression() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::Identifier& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  addAttributeToContent(static_cast<const statement::Pattern&>(node), content, false);
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::Identifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ImportExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ImportExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::Literal& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::Literal") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "raw : " + node.getRaw() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::LogicalExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::LogicalExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "operator : " + Common::toString(node.getOperator()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::MemberExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  addAttributeToContent(static_cast<const statement::Pattern&>(node), content, false);
  addAttributeToContent(static_cast<const expression::ChainElement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::MemberExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "computed : " + std::string(node.getComputed() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::MetaProperty& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::MetaProperty") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::NewExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::NewExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::NullLiteral& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Literal&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::NullLiteral") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::NumberLiteral& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Literal&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::NumberLiteral") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "value : " + common::toString(node.getValue()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::ObjectExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ObjectExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::PrivateIdentifier& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::PrivateIdentifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::Property& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::Property") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "kind : " + Common::toString(node.getKind()) + "\n";
  content += "method : " + std::string(node.getMethod() ? "true" : "false") + "\n";
  content += "shorthand : " + std::string(node.getShorthand() ? "true" : "false") + "\n";
  content += "computed : " + std::string(node.getComputed() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::RegExpLiteral& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Literal&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::RegExpLiteral") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "pattern : " + node.getPattern() + "\n";
  content += "flags : " + node.getFlags() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::SequenceExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::SequenceExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::SpreadElement& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::SpreadElement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::StringLiteral& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Literal&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::StringLiteral") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "value : " + node.getValue() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::Super& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::Super") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::TaggedTemplateExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::TaggedTemplateExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::TemplateElement& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::TemplateElement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "tail : " + std::string(node.getTail() ? "true" : "false") + "\n";
  content += "cooked : " + node.getCooked() + "\n";
  content += "value : " + node.getValue() + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::TemplateLiteral& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::TemplateLiteral") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::ThisExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::ThisExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const expression::UnaryExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::UnaryExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "operator : " + Common::toString(node.getOperator()) + "\n";
  content += "prefix : " + std::string(node.getPrefix() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::UpdateExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::UpdateExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "operator : " + Common::toString(node.getOperator()) + "\n";
  content += "prefix : " + std::string(node.getPrefix() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const expression::YieldExpression& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const expression::Expression&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("expression::YieldExpression") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "delegate : " + std::string(node.getDelegate() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const statement::ArrayPattern& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Pattern&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ArrayPattern") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::AssignmentPattern& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Pattern&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::AssignmentPattern") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::BlockStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::BlockStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::BreakStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::BreakStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::CatchClause& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::CatchClause") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ContinueStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ContinueStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::DebuggerStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::DebuggerStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::DoWhileStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::WhileStatement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::DoWhileStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::EmptyStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::EmptyStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ExpressionStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ExpressionStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ForInStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ForInStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ForOfStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::ForInStatement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ForOfStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "await : " + std::string(node.getAwait() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const statement::ForStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ForStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::Function& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::Function") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "generator : " + std::string(node.getGenerator() ? "true" : "false") + "\n";
  content += "async : " + std::string(node.getAsync() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const statement::IfStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::IfStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::LabeledStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::LabeledStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ObjectPattern& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Pattern&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ObjectPattern") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::Pattern& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::Pattern") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::RestElement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Pattern&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::RestElement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ReturnStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ReturnStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::Statement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::Statement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::SwitchCase& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::SwitchCase") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::SwitchStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::SwitchStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::ThrowStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::ThrowStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::TryStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::TryStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::WhileStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::WhileStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const statement::WithStatement& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  addAttributeToContent(static_cast<const statement::Statement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("statement::WithStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::Class& node, std::string& content, bool callVirtualBase) {
  if (callVirtualBase) {
    addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  }
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::Class") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ClassBody& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ClassBody") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ExportSpecifier& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::ModuleSpecifier&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ExportSpecifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ImpSpecifier& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::ModuleSpecifier&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ImpSpecifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ImportDefaultSpecifier& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::ImpSpecifier&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ImportDefaultSpecifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ImportNamespaceSpecifier& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::ImpSpecifier&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ImportNamespaceSpecifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::ImportSpecifier& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const structure::ImpSpecifier&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ImportSpecifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::MethodDefinition& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::MethodDefinition") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "kind : " + Common::toString(node.getKind()) + "\n";
  content += "computed : " + std::string(node.getComputed() ? "true" : "false") + "\n";
  content += "static : " + std::string(node.getStatic() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const structure::ModuleSpecifier& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::ModuleSpecifier") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const structure::PropertyDefinition& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Positioned&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("structure::PropertyDefinition") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "computed : " + std::string(node.getComputed() ? "true" : "false") + "\n";
  content += "static : " + std::string(node.getStatic() ? "true" : "false") + "\n";
}

void VisitorGraphml::visit(const base::Comment& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::Comment") == nodeTypeFilter.end())))
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
  std::string title("base::Comment");
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

void VisitorGraphml::visitEnd(const base::Comment& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::Comment") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const base::Program& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::Program") == nodeTypeFilter.end())))
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
  std::string title("base::Program");
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
    if(!node.getBodyIsEmpty())
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

void VisitorGraphml::visitEnd(const base::Program& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::Program") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const base::System& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::System") == nodeTypeFilter.end())))
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
  std::string title("base::System");
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
    if(!node.getProgramsIsEmpty())
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

void VisitorGraphml::visitEnd(const base::System& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::System") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::ClassDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ClassDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::ClassDeclaration");
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
    if(node.getBody() || node.getSuperClass() || node.getIdentifier())
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

void VisitorGraphml::visitEnd(const declaration::ClassDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ClassDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::ExportAllDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ExportAllDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::ExportAllDeclaration");
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
    if(node.getSource() || node.getExported())
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

void VisitorGraphml::visitEnd(const declaration::ExportAllDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ExportAllDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::ExportDefaultDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ExportDefaultDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::ExportDefaultDeclaration");
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

void VisitorGraphml::visitEnd(const declaration::ExportDefaultDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ExportDefaultDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::ExportNamedDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ExportNamedDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::ExportNamedDeclaration");
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
    if(node.getDeclaration() || !node.getSpecifiersIsEmpty() || node.getSource())
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

void VisitorGraphml::visitEnd(const declaration::ExportNamedDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ExportNamedDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::FunctionDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::FunctionDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::FunctionDeclaration");
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
    if(!node.getParamsIsEmpty() || node.getBody() || node.getIdentifier())
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

void VisitorGraphml::visitEnd(const declaration::FunctionDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::FunctionDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::ImportDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ImportDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::ImportDeclaration");
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
    if(!node.getSpecifiersIsEmpty() || node.getSource())
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

void VisitorGraphml::visitEnd(const declaration::ImportDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ImportDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::ModuleDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ModuleDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::ModuleDeclaration");
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

void VisitorGraphml::visitEnd(const declaration::ModuleDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::ModuleDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::VariableDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::VariableDeclaration") == nodeTypeFilter.end())))
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
  std::string title("declaration::VariableDeclaration");
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
    if(!node.getDeclarationsIsEmpty())
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

void VisitorGraphml::visitEnd(const declaration::VariableDeclaration& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::VariableDeclaration") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const declaration::VariableDeclarator& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::VariableDeclarator") == nodeTypeFilter.end())))
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
  std::string title("declaration::VariableDeclarator");
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
    if(node.getIdentifier() || node.getInit())
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

void VisitorGraphml::visitEnd(const declaration::VariableDeclarator& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("declaration::VariableDeclarator") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ArrayExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrayExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ArrayExpression");
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
    if(!node.getElementsIsEmpty())
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

void VisitorGraphml::visitEnd(const expression::ArrayExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrayExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ArrowFunctionExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrowFunctionExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ArrowFunctionExpression");
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
    if(!node.getParamsIsEmpty() || node.getBody() || node.getIdentifier())
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

void VisitorGraphml::visitEnd(const expression::ArrowFunctionExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ArrowFunctionExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::AssignmentExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AssignmentExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::AssignmentExpression");
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

void VisitorGraphml::visitEnd(const expression::AssignmentExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AssignmentExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::AwaitExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AwaitExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::AwaitExpression");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const expression::AwaitExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::AwaitExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::BigIntLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BigIntLiteral") == nodeTypeFilter.end())))
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
  std::string title("expression::BigIntLiteral");
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

void VisitorGraphml::visitEnd(const expression::BigIntLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BigIntLiteral") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::BinaryExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BinaryExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::BinaryExpression");
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

void VisitorGraphml::visitEnd(const expression::BinaryExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BinaryExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::BooleanLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BooleanLiteral") == nodeTypeFilter.end())))
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
  std::string title("expression::BooleanLiteral");
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

void VisitorGraphml::visitEnd(const expression::BooleanLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::BooleanLiteral") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::CallExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::CallExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::CallExpression");
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
    if(node.getCallee() || !node.getArgumentsIsEmpty())
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

void VisitorGraphml::visitEnd(const expression::CallExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::CallExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ChainElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ChainElement") == nodeTypeFilter.end())))
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
  std::string title("expression::ChainElement");
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

void VisitorGraphml::visitEnd(const expression::ChainElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ChainElement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ChainExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ChainExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ChainExpression");
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

void VisitorGraphml::visitEnd(const expression::ChainExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ChainExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ClassExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ClassExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ClassExpression");
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
    if(node.getBody() || node.getSuperClass() || node.getIdentifier())
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

void VisitorGraphml::visitEnd(const expression::ClassExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ClassExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ConditionalExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ConditionalExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ConditionalExpression");
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
    if(node.getAlternate() || node.getConsequent() || node.getTest())
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

void VisitorGraphml::visitEnd(const expression::ConditionalExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ConditionalExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::FunctionExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::FunctionExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::FunctionExpression");
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
    if(!node.getParamsIsEmpty() || node.getBody() || node.getIdentifier())
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

void VisitorGraphml::visitEnd(const expression::FunctionExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::FunctionExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::Identifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
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
  std::string title("expression::Identifier");
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

void VisitorGraphml::visitEnd(const expression::Identifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ImportExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ImportExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ImportExpression");
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
    if(node.getSource())
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

void VisitorGraphml::visitEnd(const expression::ImportExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ImportExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::LogicalExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::LogicalExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::LogicalExpression");
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

void VisitorGraphml::visitEnd(const expression::LogicalExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::LogicalExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::MemberExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MemberExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::MemberExpression");
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
    if(node.getProperty() || node.getObject())
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

void VisitorGraphml::visitEnd(const expression::MemberExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MemberExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::MetaProperty& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MetaProperty") == nodeTypeFilter.end())))
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
  std::string title("expression::MetaProperty");
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
    if(node.getMeta() || node.getProperty())
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

void VisitorGraphml::visitEnd(const expression::MetaProperty& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::MetaProperty") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::NewExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NewExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::NewExpression");
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
    if(node.getCallee() || !node.getArgumentsIsEmpty())
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

void VisitorGraphml::visitEnd(const expression::NewExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NewExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::NullLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NullLiteral") == nodeTypeFilter.end())))
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
  std::string title("expression::NullLiteral");
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

void VisitorGraphml::visitEnd(const expression::NullLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NullLiteral") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::NumberLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NumberLiteral") == nodeTypeFilter.end())))
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
  std::string title("expression::NumberLiteral");
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

void VisitorGraphml::visitEnd(const expression::NumberLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::NumberLiteral") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ObjectExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ObjectExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ObjectExpression");
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
    if(!node.getPropertiesIsEmpty())
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

void VisitorGraphml::visitEnd(const expression::ObjectExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ObjectExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::PrivateIdentifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PrivateIdentifier") == nodeTypeFilter.end())))
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
  std::string title("expression::PrivateIdentifier");
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

void VisitorGraphml::visitEnd(const expression::PrivateIdentifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::PrivateIdentifier") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::Property& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::Property") == nodeTypeFilter.end())))
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
  std::string title("expression::Property");
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
    if(node.getValue() || node.getKey())
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

void VisitorGraphml::visitEnd(const expression::Property& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::Property") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::RegExpLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::RegExpLiteral") == nodeTypeFilter.end())))
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
  std::string title("expression::RegExpLiteral");
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

void VisitorGraphml::visitEnd(const expression::RegExpLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::RegExpLiteral") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::SequenceExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SequenceExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::SequenceExpression");
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

void VisitorGraphml::visitEnd(const expression::SequenceExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SequenceExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::SpreadElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SpreadElement") == nodeTypeFilter.end())))
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
  std::string title("expression::SpreadElement");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const expression::SpreadElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::SpreadElement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::StringLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::StringLiteral") == nodeTypeFilter.end())))
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
  std::string title("expression::StringLiteral");
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

void VisitorGraphml::visitEnd(const expression::StringLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::StringLiteral") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::Super& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::Super") == nodeTypeFilter.end())))
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
  std::string title("expression::Super");
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

void VisitorGraphml::visitEnd(const expression::Super& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::Super") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::TaggedTemplateExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TaggedTemplateExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::TaggedTemplateExpression");
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
    if(node.getTag() || node.getQuasi())
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

void VisitorGraphml::visitEnd(const expression::TaggedTemplateExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TaggedTemplateExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::TemplateElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TemplateElement") == nodeTypeFilter.end())))
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
  std::string title("expression::TemplateElement");
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

void VisitorGraphml::visitEnd(const expression::TemplateElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TemplateElement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::TemplateLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TemplateLiteral") == nodeTypeFilter.end())))
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
  std::string title("expression::TemplateLiteral");
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
    if(!node.getQuasisIsEmpty() || !node.getExpressionsIsEmpty())
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

void VisitorGraphml::visitEnd(const expression::TemplateLiteral& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::TemplateLiteral") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::ThisExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ThisExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::ThisExpression");
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

void VisitorGraphml::visitEnd(const expression::ThisExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::ThisExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::UnaryExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::UnaryExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::UnaryExpression");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const expression::UnaryExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::UnaryExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::UpdateExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::UpdateExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::UpdateExpression");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const expression::UpdateExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::UpdateExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const expression::YieldExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::YieldExpression") == nodeTypeFilter.end())))
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
  std::string title("expression::YieldExpression");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const expression::YieldExpression& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("expression::YieldExpression") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ArrayPattern& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ArrayPattern") == nodeTypeFilter.end())))
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
  std::string title("statement::ArrayPattern");
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
    if(!node.getElementsIsEmpty())
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

void VisitorGraphml::visitEnd(const statement::ArrayPattern& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ArrayPattern") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::AssignmentPattern& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::AssignmentPattern") == nodeTypeFilter.end())))
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
  std::string title("statement::AssignmentPattern");
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

void VisitorGraphml::visitEnd(const statement::AssignmentPattern& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::AssignmentPattern") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::BlockStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BlockStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::BlockStatement");
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
    if(!node.getBodyIsEmpty())
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

void VisitorGraphml::visitEnd(const statement::BlockStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BlockStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::BreakStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BreakStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::BreakStatement");
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
    if(node.getLabel())
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

void VisitorGraphml::visitEnd(const statement::BreakStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::BreakStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::CatchClause& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::CatchClause") == nodeTypeFilter.end())))
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
  std::string title("statement::CatchClause");
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
    if(node.getParam() || node.getBody())
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

void VisitorGraphml::visitEnd(const statement::CatchClause& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::CatchClause") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ContinueStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ContinueStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::ContinueStatement");
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
    if(node.getLabel())
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

void VisitorGraphml::visitEnd(const statement::ContinueStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ContinueStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::DebuggerStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::DebuggerStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::DebuggerStatement");
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

void VisitorGraphml::visitEnd(const statement::DebuggerStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::DebuggerStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::DoWhileStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::DoWhileStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::DoWhileStatement");
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
    if(node.getBody() || node.getTest())
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

void VisitorGraphml::visitEnd(const statement::DoWhileStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::DoWhileStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::EmptyStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::EmptyStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::EmptyStatement");
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

void VisitorGraphml::visitEnd(const statement::EmptyStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::EmptyStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ExpressionStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ExpressionStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::ExpressionStatement");
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

void VisitorGraphml::visitEnd(const statement::ExpressionStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ExpressionStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ForInStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForInStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::ForInStatement");
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
    if(node.getRight() || node.getBody() || node.getLeft())
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

void VisitorGraphml::visitEnd(const statement::ForInStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForInStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ForOfStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForOfStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::ForOfStatement");
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
    if(node.getRight() || node.getBody() || node.getLeft())
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

void VisitorGraphml::visitEnd(const statement::ForOfStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForOfStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ForStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::ForStatement");
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
    if(node.getBody() || node.getTest() || node.getUpdate() || node.getInit())
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

void VisitorGraphml::visitEnd(const statement::ForStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ForStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::Function& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::Function") == nodeTypeFilter.end())))
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
  std::string title("statement::Function");
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
    if(!node.getParamsIsEmpty() || node.getBody() || node.getIdentifier())
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

void VisitorGraphml::visitEnd(const statement::Function& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::Function") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::IfStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::IfStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::IfStatement");
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
    if(node.getTest() || node.getConsequent() || node.getAlternate())
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

void VisitorGraphml::visitEnd(const statement::IfStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::IfStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::LabeledStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LabeledStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::LabeledStatement");
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
    if(node.getLabel() || node.getBody())
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

void VisitorGraphml::visitEnd(const statement::LabeledStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::LabeledStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ObjectPattern& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ObjectPattern") == nodeTypeFilter.end())))
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
  std::string title("statement::ObjectPattern");
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
    if(!node.getPropertiesIsEmpty())
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

void VisitorGraphml::visitEnd(const statement::ObjectPattern& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ObjectPattern") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::RestElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::RestElement") == nodeTypeFilter.end())))
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
  std::string title("statement::RestElement");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const statement::RestElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::RestElement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ReturnStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ReturnStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::ReturnStatement");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const statement::ReturnStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ReturnStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::SwitchCase& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::SwitchCase") == nodeTypeFilter.end())))
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
  std::string title("statement::SwitchCase");
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
    if(node.getTest() || !node.getConsequentIsEmpty())
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

void VisitorGraphml::visitEnd(const statement::SwitchCase& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::SwitchCase") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::SwitchStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::SwitchStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::SwitchStatement");
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
    if(node.getDiscriminant() || !node.getCasesIsEmpty())
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

void VisitorGraphml::visitEnd(const statement::SwitchStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::SwitchStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::ThrowStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ThrowStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::ThrowStatement");
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
    if(node.getArgument())
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

void VisitorGraphml::visitEnd(const statement::ThrowStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::ThrowStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::TryStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::TryStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::TryStatement");
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
    if(node.getBlock() || node.getFinalizer() || node.getHandler())
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

void VisitorGraphml::visitEnd(const statement::TryStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::TryStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::WhileStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::WhileStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::WhileStatement");
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
    if(node.getBody() || node.getTest())
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

void VisitorGraphml::visitEnd(const statement::WhileStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::WhileStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const statement::WithStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::WithStatement") == nodeTypeFilter.end())))
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
  std::string title("statement::WithStatement");
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
    if(node.getObject() || node.getBody())
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

void VisitorGraphml::visitEnd(const statement::WithStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("statement::WithStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const structure::ClassBody& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ClassBody") == nodeTypeFilter.end())))
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
  std::string title("structure::ClassBody");
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
    if(!node.getBodyIsEmpty())
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

void VisitorGraphml::visitEnd(const structure::ClassBody& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ClassBody") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const structure::ExportSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ExportSpecifier") == nodeTypeFilter.end())))
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
  std::string title("structure::ExportSpecifier");
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
    if(node.getExported())
      hasChildNode = true;
    if(node.getLocal())
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

void VisitorGraphml::visitEnd(const structure::ExportSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ExportSpecifier") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const structure::ImportDefaultSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ImportDefaultSpecifier") == nodeTypeFilter.end())))
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
  std::string title("structure::ImportDefaultSpecifier");
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
    if(node.getLocal())
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

void VisitorGraphml::visitEnd(const structure::ImportDefaultSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ImportDefaultSpecifier") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const structure::ImportNamespaceSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ImportNamespaceSpecifier") == nodeTypeFilter.end())))
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
  std::string title("structure::ImportNamespaceSpecifier");
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
    if(node.getLocal())
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

void VisitorGraphml::visitEnd(const structure::ImportNamespaceSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ImportNamespaceSpecifier") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const structure::ImportSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ImportSpecifier") == nodeTypeFilter.end())))
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
  std::string title("structure::ImportSpecifier");
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
    if(node.getImported())
      hasChildNode = true;
    if(node.getLocal())
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

void VisitorGraphml::visitEnd(const structure::ImportSpecifier& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::ImportSpecifier") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const structure::MethodDefinition& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::MethodDefinition") == nodeTypeFilter.end())))
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
  std::string title("structure::MethodDefinition");
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
    if(node.getKey() || node.getValue())
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

void VisitorGraphml::visitEnd(const structure::MethodDefinition& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::MethodDefinition") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const structure::PropertyDefinition& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::PropertyDefinition") == nodeTypeFilter.end())))
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
  std::string title("structure::PropertyDefinition");
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
    if(node.getKey() || node.getValue())
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

void VisitorGraphml::visitEnd(const structure::PropertyDefinition& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("structure::PropertyDefinition") == nodeTypeFilter.end())))
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

void  VisitorGraphml::visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Positioned_Comments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Comment") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Positioned_Comments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Positioned_Comments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitProgram_HasBody(const base::Program& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Program_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::Program") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Program_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Program_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSystem_HasPrograms(const base::System& begin, const base::Program& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("System_HasPrograms") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::System") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Program") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "System_HasPrograms", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "System_HasPrograms", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExportAllDeclaration_HasSource") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ExportAllDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Literal") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportAllDeclaration_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportAllDeclaration_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExportAllDeclaration_HasExported(const declaration::ExportAllDeclaration& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExportAllDeclaration_HasExported") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ExportAllDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportAllDeclaration_HasExported", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportAllDeclaration_HasExported", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExportDefaultDeclaration_HasDeclaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ExportDefaultDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportDefaultDeclaration_HasDeclaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportDefaultDeclaration_HasDeclaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExportNamedDeclaration_HasDeclaration") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ExportNamedDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("declaration::Declaration") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportNamedDeclaration_HasDeclaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportNamedDeclaration_HasDeclaration", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExportNamedDeclaration_HasSpecifiers") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ExportNamedDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ExportSpecifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportNamedDeclaration_HasSpecifiers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportNamedDeclaration_HasSpecifiers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExportNamedDeclaration_HasSource") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ExportNamedDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Literal") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportNamedDeclaration_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportNamedDeclaration_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ImportDeclaration_HasSpecifiers") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ImportDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ImpSpecifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportDeclaration_HasSpecifiers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportDeclaration_HasSpecifiers", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ImportDeclaration_HasSource") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::ImportDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Literal") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportDeclaration_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportDeclaration_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("VariableDeclaration_HasDeclarations") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::VariableDeclaration") == nodeTypeFilter.end() && nodeTypeFilter.find("declaration::VariableDeclarator") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclaration_HasDeclarations", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclaration_HasDeclarations", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("VariableDeclarator_HasIdentifier") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::VariableDeclarator") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Pattern") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarator_HasIdentifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarator_HasIdentifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("VariableDeclarator_HasInit") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("declaration::VariableDeclarator") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarator_HasInit", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "VariableDeclarator_HasInit", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrayExpression_HasElements") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ArrayExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayExpression_HasElements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayExpression_HasElements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentExpression_HasLeft") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AssignmentExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpression_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpression_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentExpression_HasRight") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AssignmentExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpression_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentExpression_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AwaitExpression_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::AwaitExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AwaitExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AwaitExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BinaryExpression_HasLeft") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::BinaryExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpression_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpression_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BinaryExpression_HasRight") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::BinaryExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpression_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BinaryExpression_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CallExpression_HasCallee") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::CallExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CallExpression_HasCallee", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CallExpression_HasCallee", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CallExpression_HasArguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::CallExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CallExpression_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CallExpression_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCallExpression_Calls(const expression::CallExpression& begin, const statement::Function& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CallExpression_Calls") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::CallExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Function") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CallExpression_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CallExpression_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitChainExpression_HasExpression(const expression::ChainExpression& begin, const expression::ChainElement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ChainExpression_HasExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ChainExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::ChainElement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ChainExpression_HasExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ChainExpression_HasExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalExpression_HasAlternate") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpression_HasAlternate", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpression_HasAlternate", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalExpression_HasConsequent") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpression_HasConsequent", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpression_HasConsequent", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ConditionalExpression_HasTest") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ConditionalExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpression_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ConditionalExpression_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Identifier_RefersTo") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Identifier_RefersTo", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Identifier_RefersTo", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitImportExpression_HasSource(const expression::ImportExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ImportExpression_HasSource") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ImportExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportExpression_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportExpression_HasSource", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LogicalExpression_HasLeft") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::LogicalExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LogicalExpression_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LogicalExpression_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LogicalExpression_HasRight") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::LogicalExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LogicalExpression_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LogicalExpression_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MemberExpression_HasProperty") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MemberExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberExpression_HasProperty", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberExpression_HasProperty", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MemberExpression_HasObject") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MemberExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberExpression_HasObject", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MemberExpression_HasObject", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MetaProperty_HasMeta") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MetaProperty") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MetaProperty_HasMeta", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MetaProperty_HasMeta", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MetaProperty_HasProperty") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::MetaProperty") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MetaProperty_HasProperty", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MetaProperty_HasProperty", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NewExpression_HasCallee") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::NewExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NewExpression_HasCallee", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NewExpression_HasCallee", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NewExpression_HasArguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::NewExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NewExpression_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NewExpression_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNewExpression_Calls(const expression::NewExpression& begin, const statement::Function& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("NewExpression_Calls") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::NewExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Function") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "NewExpression_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "NewExpression_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ObjectExpression_HasProperties") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::ObjectExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectExpression_HasProperties", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectExpression_HasProperties", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Property_HasValue") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::Property") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Property_HasValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Property_HasValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Property_HasKey") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::Property") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Property_HasKey", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Property_HasKey", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SequenceExpression_HasExpressions") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::SequenceExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SequenceExpression_HasExpressions", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SequenceExpression_HasExpressions", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SpreadElement_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::SpreadElement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SpreadElement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SpreadElement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TaggedTemplateExpression_HasTag") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::TaggedTemplateExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TaggedTemplateExpression_HasTag", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TaggedTemplateExpression_HasTag", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TaggedTemplateExpression_HasQuasi") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::TaggedTemplateExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TemplateLiteral") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TaggedTemplateExpression_HasQuasi", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TaggedTemplateExpression_HasQuasi", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TemplateLiteral_HasQuasis") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::TemplateLiteral") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::TemplateElement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TemplateLiteral_HasQuasis", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TemplateLiteral_HasQuasis", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TemplateLiteral_HasExpressions") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::TemplateLiteral") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TemplateLiteral_HasExpressions", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TemplateLiteral_HasExpressions", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UnaryExpression_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::UnaryExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UnaryExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UnaryExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("UpdateExpression_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::UpdateExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "UpdateExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "UpdateExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("YieldExpression_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("expression::YieldExpression") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "YieldExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "YieldExpression_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ArrayPattern_HasElements") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ArrayPattern") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Pattern") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayPattern_HasElements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ArrayPattern_HasElements", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentPattern_HasLeft") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::AssignmentPattern") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Pattern") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentPattern_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentPattern_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AssignmentPattern_HasRight") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::AssignmentPattern") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentPattern_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AssignmentPattern_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BlockStatement_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::BlockStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BlockStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BlockStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("BreakStatement_HasLabel") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::BreakStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "BreakStatement_HasLabel", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "BreakStatement_HasLabel", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CatchClause_HasParam") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::CatchClause") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Pattern") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClause_HasParam", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClause_HasParam", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CatchClause_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::CatchClause") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockStatement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClause_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CatchClause_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ContinueStatement_HasLabel") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ContinueStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ContinueStatement_HasLabel", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ContinueStatement_HasLabel", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExpressionStatement_HasExpression") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ExpressionStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExpressionStatement_HasExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExpressionStatement_HasExpression", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForInStatement_HasRight") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForInStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForInStatement_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForInStatement_HasRight", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForInStatement_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForInStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForInStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForInStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForInStatement_HasLeft") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForInStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForInStatement_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForInStatement_HasLeft", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatement_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatement_HasTest") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatement_HasUpdate") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasUpdate", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasUpdate", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ForStatement_HasInit") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ForStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasInit", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ForStatement_HasInit", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Function_HasParams") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::Function") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Pattern") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Function_HasParams", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Function_HasParams", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Function_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::Function") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Function_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Function_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Function_HasIdentifier") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::Function") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Function_HasIdentifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Function_HasIdentifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IfStatement_HasTest") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::IfStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatement_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatement_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IfStatement_HasConsequent") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::IfStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatement_HasConsequent", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatement_HasConsequent", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("IfStatement_HasAlternate") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::IfStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatement_HasAlternate", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "IfStatement_HasAlternate", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LabeledStatement_HasLabel") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::LabeledStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LabeledStatement_HasLabel", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LabeledStatement_HasLabel", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("LabeledStatement_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::LabeledStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "LabeledStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "LabeledStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ObjectPattern_HasProperties") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ObjectPattern") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectPattern_HasProperties", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ObjectPattern_HasProperties", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("RestElement_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::RestElement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Pattern") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "RestElement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "RestElement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ReturnStatement_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ReturnStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ReturnStatement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ReturnStatement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchCase_HasTest") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::SwitchCase") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchCase_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchCase_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchCase_HasConsequent") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::SwitchCase") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchCase_HasConsequent", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchCase_HasConsequent", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchStatement_HasDiscriminant") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::SwitchStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_HasDiscriminant", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_HasDiscriminant", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchStatement_HasCases") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::SwitchStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::SwitchCase") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_HasCases", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_HasCases", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ThrowStatement_HasArgument") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::ThrowStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ThrowStatement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ThrowStatement_HasArgument", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TryStatement_HasBlock") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::TryStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockStatement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatement_HasBlock", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatement_HasBlock", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TryStatement_HasFinalizer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::TryStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::BlockStatement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatement_HasFinalizer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatement_HasFinalizer", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TryStatement_HasHandler") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::TryStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::CatchClause") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatement_HasHandler", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TryStatement_HasHandler", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("WhileStatement_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::WhileStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("WhileStatement_HasTest") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::WhileStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatement_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "WhileStatement_HasTest", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("WithStatement_HasObject") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::WithStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "WithStatement_HasObject", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "WithStatement_HasObject", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("WithStatement_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("statement::WithStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("statement::Statement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "WithStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "WithStatement_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Class_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::Class") == nodeTypeFilter.end() && nodeTypeFilter.find("structure::ClassBody") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Class_HasSuperClass") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::Class") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_HasSuperClass", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_HasSuperClass", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Class_HasIdentifier") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::Class") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_HasIdentifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_HasIdentifier", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClassBody_HasBody(const structure::ClassBody& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ClassBody_HasBody") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ClassBody") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassBody_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassBody_HasBody", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ExportSpecifier_HasExported") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ExportSpecifier") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportSpecifier_HasExported", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ExportSpecifier_HasExported", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ImportSpecifier_HasImported") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ImportSpecifier") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportSpecifier_HasImported", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ImportSpecifier_HasImported", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodDefinition_HasKey") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::MethodDefinition") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDefinition_HasKey", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDefinition_HasKey", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodDefinition_HasValue") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::MethodDefinition") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::FunctionExpression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDefinition_HasValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodDefinition_HasValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ModuleSpecifier_HasLocal") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::ModuleSpecifier") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Identifier") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ModuleSpecifier_HasLocal", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ModuleSpecifier_HasLocal", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPropertyDefinition_HasKey(const structure::PropertyDefinition& begin, const base::Positioned& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PropertyDefinition_HasKey") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::PropertyDefinition") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Positioned") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDefinition_HasKey", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDefinition_HasKey", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitPropertyDefinition_HasValue(const structure::PropertyDefinition& begin, const expression::Expression& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("PropertyDefinition_HasValue") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("structure::PropertyDefinition") == nodeTypeFilter.end() && nodeTypeFilter.find("expression::Expression") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDefinition_HasValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "PropertyDefinition_HasValue", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}


}}}
