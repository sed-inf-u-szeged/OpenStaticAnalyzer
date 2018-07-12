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

#include "lim/inc/lim.h"
#include "common/inc/StringSup.h"
#include <set>
#include <string>

using namespace columbus::io;

namespace columbus { namespace lim { namespace asg {

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

void VisitorGraphml::addAttributeToContent(const base::Comment& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Comment") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "text : " + node.getText() + "\n";
}

void VisitorGraphml::addAttributeToContent(const base::Component& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Component") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "TLLOC : " + common::toString(node.getTLLOC()) + "\n";
  content += "TLOC : " + common::toString(node.getTLOC()) + "\n";
  content += "analysisTime : " + Common::toString(node.getAnalysisTime()) + "\n";
  content += "changesetID : " + node.getChangesetID() + "\n";
  content += "shortName : " + node.getShortName() + "\n";
}

void VisitorGraphml::addAttributeToContent(const base::ControlFlowBlock& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::ControlFlowBlock") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const base::Named& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("base::Named") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "name : " + node.getName() + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::Attribute& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Member&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Attribute") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const logical::AttributeAccess& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::AttributeAccess") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "accesses : " + node.getAccesses() + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::Class& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Scope&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Class") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "classKind : " + Common::toString(node.getClassKind()) + "\n";
  content += "isAbstract : " + std::string(node.getIsAbstract() ? "true" : "false") + "\n";
  content += "objectSize : " + common::toString(node.getObjectSize()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::ClassGeneric& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Class&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::ClassGeneric") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const logical::ClassGenericInstance& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Class&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::ClassGenericInstance") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "isRealInstance : " + std::string(node.getIsRealInstance() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::ClassGenericSpec& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::ClassGeneric&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::ClassGenericSpec") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const logical::Friendship& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Friendship") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "grants : " + node.getGrants() + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::GenericParameter& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::GenericParameter") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "genericParameterKind : " + Common::toString(node.getGenericParameterKind()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::Member& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Member") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "accessibility : " + Common::toString(node.getAccessibility()) + "\n";
  content += "commentLines : " + common::toString(node.getCommentLines()) + "\n";
  content += "demangledName : " + node.getDemangledName() + "\n";
  content += "isCompilerGenerated : " + std::string(node.getIsCompilerGenerated() ? "true" : "false") + "\n";
  content += "isStatic : " + std::string(node.getIsStatic() ? "true" : "false") + "\n";
  content += "language : " + Common::toString(node.getLanguage()) + "\n";
  content += "mangledName : " + node.getMangledName() + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::Method& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Scope&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Method") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "distinctOperands : " + common::toString(node.getDistinctOperands()) + "\n";
  content += "distinctOperators : " + common::toString(node.getDistinctOperators()) + "\n";
  content += "isAbstract : " + std::string(node.getIsAbstract() ? "true" : "false") + "\n";
  content += "isVirtual : " + std::string(node.getIsVirtual() ? "true" : "false") + "\n";
  content += "methodKind : " + Common::toString(node.getMethodKind()) + "\n";
  content += "nestingLevel : " + common::toString(node.getNestingLevel()) + "\n";
  content += "nestingLevelElseIf : " + common::toString(node.getNestingLevelElseIf()) + "\n";
  content += "numberOfBranches : " + common::toString(node.getNumberOfBranches()) + "\n";
  content += "numberOfStatements : " + common::toString(node.getNumberOfStatements()) + "\n";
  content += "totalOperands : " + common::toString(node.getTotalOperands()) + "\n";
  content += "totalOperators : " + common::toString(node.getTotalOperators()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::MethodCall& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::MethodCall") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "calls : " + node.getCalls() + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::MethodGeneric& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Method&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::MethodGeneric") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const logical::MethodGenericInstance& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Method&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::MethodGenericInstance") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "isRealInstance : " + std::string(node.getIsRealInstance() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::MethodGenericSpec& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::MethodGeneric&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::MethodGenericSpec") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const logical::Package& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Scope&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Package") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "packageKind : " + Common::toString(node.getPackageKind()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::Parameter& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Parameter") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "paramKind : " + Common::toString(node.getParamKind()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const logical::Scope& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const logical::Member&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("logical::Scope") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "LLOC : " + common::toString(node.getLLOC()) + "\n";
  content += "LOC : " + common::toString(node.getLOC()) + "\n";
  content += "TLLOC : " + common::toString(node.getTLLOC()) + "\n";
  content += "TLOC : " + common::toString(node.getTLOC()) + "\n";
  content += "isAnonymous : " + std::string(node.getIsAnonymous() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const physical::FSEntry& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("physical::FSEntry") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const physical::File& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const physical::FSEntry&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("physical::File") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "CLOC : " + common::toString(node.getCLOC()) + "\n";
  content += "LLOC : " + common::toString(node.getLLOC()) + "\n";
  content += "LOC : " + common::toString(node.getLOC()) + "\n";
  content += "numberOfBranches : " + common::toString(node.getNumberOfBranches()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const physical::FileSystem& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Named&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("physical::FileSystem") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const physical::Folder& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const physical::FSEntry&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("physical::Folder") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const type::SimpleType& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::SimpleType") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "simpleTypeKind : " + Common::toString(node.getSimpleTypeKind()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const type::Type& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::Type") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "refers : " + node.getRefers() + "\n";
}

void VisitorGraphml::addAttributeToContent(const type::TypeFormer& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const base::Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::TypeFormer") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const type::TypeFormerArray& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const type::TypeFormer&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::TypeFormerArray") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const type::TypeFormerMethod& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const type::TypeFormer&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::TypeFormerMethod") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const type::TypeFormerNonType& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const type::TypeFormer&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::TypeFormerNonType") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const type::TypeFormerPointer& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const type::TypeFormer&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::TypeFormerPointer") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "pointerKind : " + Common::toString(node.getPointerKind()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const type::TypeFormerType& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const type::TypeFormer&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("type::TypeFormerType") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
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

void VisitorGraphml::visit(const base::Component& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::Component") == nodeTypeFilter.end())))
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
  std::string title("base::Component");
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

void VisitorGraphml::visitEnd(const base::Component& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::Component") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const base::ControlFlowBlock& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::ControlFlowBlock") == nodeTypeFilter.end())))
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
  std::string title("base::ControlFlowBlock");
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

void VisitorGraphml::visitEnd(const base::ControlFlowBlock& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("base::ControlFlowBlock") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::Attribute& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Attribute") == nodeTypeFilter.end())))
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
  std::string title("logical::Attribute");
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

void VisitorGraphml::visitEnd(const logical::Attribute& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Attribute") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::AttributeAccess& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::AttributeAccess") == nodeTypeFilter.end())))
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
  std::string title("logical::AttributeAccess");
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

void VisitorGraphml::visitEnd(const logical::AttributeAccess& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::AttributeAccess") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::Class& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Class") == nodeTypeFilter.end())))
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
  std::string title("logical::Class");
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

void VisitorGraphml::visitEnd(const logical::Class& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Class") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::ClassGeneric& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::ClassGeneric") == nodeTypeFilter.end())))
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
  std::string title("logical::ClassGeneric");
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
    if(!node.getGenericParameterIsEmpty())
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

void VisitorGraphml::visitEnd(const logical::ClassGeneric& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::ClassGeneric") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::ClassGenericInstance& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::ClassGenericInstance") == nodeTypeFilter.end())))
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
  std::string title("logical::ClassGenericInstance");
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

void VisitorGraphml::visitEnd(const logical::ClassGenericInstance& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::ClassGenericInstance") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::ClassGenericSpec& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::ClassGenericSpec") == nodeTypeFilter.end())))
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
  std::string title("logical::ClassGenericSpec");
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
    if(!node.getGenericParameterIsEmpty())
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

void VisitorGraphml::visitEnd(const logical::ClassGenericSpec& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::ClassGenericSpec") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::Friendship& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Friendship") == nodeTypeFilter.end())))
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
  std::string title("logical::Friendship");
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

void VisitorGraphml::visitEnd(const logical::Friendship& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Friendship") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::GenericParameter& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::GenericParameter") == nodeTypeFilter.end())))
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
  std::string title("logical::GenericParameter");
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

void VisitorGraphml::visitEnd(const logical::GenericParameter& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::GenericParameter") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::Method& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end())))
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
  std::string title("logical::Method");
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
    if(!node.getControlFlowBlockIsEmpty() || !node.getParameterIsEmpty())
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

void VisitorGraphml::visitEnd(const logical::Method& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::MethodCall& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodCall") == nodeTypeFilter.end())))
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
  std::string title("logical::MethodCall");
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

void VisitorGraphml::visitEnd(const logical::MethodCall& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodCall") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::MethodGeneric& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodGeneric") == nodeTypeFilter.end())))
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
  std::string title("logical::MethodGeneric");
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
    if(!node.getGenericParameterIsEmpty())
      hasChildNode = true;
    if(!node.getControlFlowBlockIsEmpty() || !node.getParameterIsEmpty())
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

void VisitorGraphml::visitEnd(const logical::MethodGeneric& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodGeneric") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::MethodGenericInstance& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodGenericInstance") == nodeTypeFilter.end())))
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
  std::string title("logical::MethodGenericInstance");
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
    if(!node.getControlFlowBlockIsEmpty() || !node.getParameterIsEmpty())
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

void VisitorGraphml::visitEnd(const logical::MethodGenericInstance& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodGenericInstance") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::MethodGenericSpec& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodGenericSpec") == nodeTypeFilter.end())))
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
  std::string title("logical::MethodGenericSpec");
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
    if(!node.getGenericParameterIsEmpty())
      hasChildNode = true;
    if(!node.getControlFlowBlockIsEmpty() || !node.getParameterIsEmpty())
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

void VisitorGraphml::visitEnd(const logical::MethodGenericSpec& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::MethodGenericSpec") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::Package& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Package") == nodeTypeFilter.end())))
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
  std::string title("logical::Package");
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

void VisitorGraphml::visitEnd(const logical::Package& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Package") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const logical::Parameter& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Parameter") == nodeTypeFilter.end())))
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
  std::string title("logical::Parameter");
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

void VisitorGraphml::visitEnd(const logical::Parameter& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("logical::Parameter") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const physical::File& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("physical::File") == nodeTypeFilter.end())))
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
  std::string title("physical::File");
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

void VisitorGraphml::visitEnd(const physical::File& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("physical::File") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const physical::FileSystem& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("physical::FileSystem") == nodeTypeFilter.end())))
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
  std::string title("physical::FileSystem");
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
    if(!node.getFSEntryIsEmpty())
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

void VisitorGraphml::visitEnd(const physical::FileSystem& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("physical::FileSystem") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const physical::Folder& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("physical::Folder") == nodeTypeFilter.end())))
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
  std::string title("physical::Folder");
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
    if(!node.getContainsIsEmpty())
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

void VisitorGraphml::visitEnd(const physical::Folder& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("physical::Folder") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const type::SimpleType& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::SimpleType") == nodeTypeFilter.end())))
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
  std::string title("type::SimpleType");
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

void VisitorGraphml::visitEnd(const type::SimpleType& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::SimpleType") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const type::Type& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
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
  std::string title("type::Type");
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

void VisitorGraphml::visitEnd(const type::Type& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const type::TypeFormerArray& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerArray") == nodeTypeFilter.end())))
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
  std::string title("type::TypeFormerArray");
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

void VisitorGraphml::visitEnd(const type::TypeFormerArray& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerArray") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const type::TypeFormerMethod& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerMethod") == nodeTypeFilter.end())))
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
  std::string title("type::TypeFormerMethod");
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

void VisitorGraphml::visitEnd(const type::TypeFormerMethod& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerMethod") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const type::TypeFormerNonType& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerNonType") == nodeTypeFilter.end())))
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
  std::string title("type::TypeFormerNonType");
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

void VisitorGraphml::visitEnd(const type::TypeFormerNonType& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerNonType") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const type::TypeFormerPointer& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerPointer") == nodeTypeFilter.end())))
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
  std::string title("type::TypeFormerPointer");
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

void VisitorGraphml::visitEnd(const type::TypeFormerPointer& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerPointer") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const type::TypeFormerType& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerType") == nodeTypeFilter.end())))
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
  std::string title("type::TypeFormerType");
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

void VisitorGraphml::visitEnd(const type::TypeFormerType& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("type::TypeFormerType") == nodeTypeFilter.end())))
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

void  VisitorGraphml::visitComponent_Contains(const base::Component& begin, const base::Component& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Component_Contains") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::Component") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Component") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Component_Contains", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Component_Contains", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitComponent_HasFiles(const base::Component& begin, const physical::File& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Component_HasFiles") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::Component") == nodeTypeFilter.end() && nodeTypeFilter.find("physical::File") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Component_HasFiles", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Component_HasFiles", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ControlFlowBlock_Calls") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::ControlFlowBlock") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ControlFlowBlock_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ControlFlowBlock_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ControlFlowBlock_Pred") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::ControlFlowBlock") == nodeTypeFilter.end() && nodeTypeFilter.find("base::ControlFlowBlock") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ControlFlowBlock_Pred", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ControlFlowBlock_Pred", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Named_DependsOn") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("base::Named") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Named") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Named_DependsOn", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Named_DependsOn", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Attribute_Calls") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Attribute") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::MethodCall") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Attribute_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Attribute_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Attribute_HasType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Attribute") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Attribute_HasType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Attribute_HasType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("AttributeAccess_Attribute") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::AttributeAccess") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Attribute") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeAccess_Attribute", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "AttributeAccess_Attribute", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Class_GrantsFriendship") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Class") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Friendship") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_GrantsFriendship", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_GrantsFriendship", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClass_IsSubclass(const logical::Class& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Class_IsSubclass") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Class") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_IsSubclass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Class_IsSubclass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ClassGeneric_HasGenericParameter") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::ClassGeneric") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::GenericParameter") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGeneric_HasGenericParameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGeneric_HasGenericParameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ClassGenericInstance_HasArguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::ClassGenericInstance") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGenericInstance_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGenericInstance_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ClassGenericSpec_HasArguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::ClassGenericSpec") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGenericSpec_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGenericSpec_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("ClassGenericSpec_Specialize") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::ClassGenericSpec") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::ClassGeneric") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGenericSpec_Specialize", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "ClassGenericSpec_Specialize", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Friendship_Friend") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Friendship") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Scope") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Friendship_Friend", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Friendship_Friend", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("GenericParameter_HasParameterConstraint") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::GenericParameter") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "GenericParameter_HasParameterConstraint", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "GenericParameter_HasParameterConstraint", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_Aggregated(const logical::Member& begin, const logical::Member& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_Aggregated") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Aggregated", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Aggregated", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_BelongsTo(const logical::Member& begin, const base::Component& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_BelongsTo") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Component") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_BelongsTo", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_BelongsTo", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_CompilationUnit") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("physical::File") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_CompilationUnit", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_CompilationUnit", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_Declares(const logical::Member& begin, const logical::Member& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_Declares") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Declares", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Declares", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_HasComment(const logical::Member& begin, const base::Comment& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_HasComment") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Comment") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_HasComment", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_HasComment", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_Instance(const logical::Member& begin, const logical::Member& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_Instance") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Instance", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Instance", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_IsContainedIn") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("physical::File") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_IsContainedIn", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_IsContainedIn", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_LanguageVariant") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_LanguageVariant", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_LanguageVariant", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_Uses(const logical::Member& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_Uses") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Uses", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Uses", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMember_Variant(const logical::Member& begin, const logical::Member& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Member_Variant") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Variant", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Member_Variant", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_AccessesAttribute") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::AttributeAccess") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_AccessesAttribute", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_AccessesAttribute", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_Calls") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::MethodCall") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Calls", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_CanThrow(const logical::Method& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_CanThrow") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_CanThrow", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_CanThrow", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_HasControlFlowBlock") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("base::ControlFlowBlock") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_HasControlFlowBlock", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_HasControlFlowBlock", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_HasParameter") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Parameter") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_HasParameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_HasParameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_Instantiates(const logical::Method& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_Instantiates") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Instantiates", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Instantiates", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_Returns(const logical::Method& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_Returns") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Returns", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Returns", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethod_Throws(const logical::Method& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Method_Throws") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Throws", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Method_Throws", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodCall_Method") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::MethodCall") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Method") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodCall_Method", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodCall_Method", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodGeneric_HasGenericParameter") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::MethodGeneric") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::GenericParameter") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGeneric_HasGenericParameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGeneric_HasGenericParameter", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodGenericInstance_HasArguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::MethodGenericInstance") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGenericInstance_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGenericInstance_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodGenericSpec_HasArguments") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::MethodGenericSpec") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGenericSpec_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGenericSpec_HasArguments", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("MethodGenericSpec_Specialize") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::MethodGenericSpec") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::MethodGeneric") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGenericSpec_Specialize", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "MethodGenericSpec_Specialize", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitParameter_HasType(const logical::Parameter& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Parameter_HasType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Parameter") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Parameter_HasType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Parameter_HasType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitScope_HasMember(const logical::Scope& begin, const logical::Member& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Scope_HasMember") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("logical::Scope") == nodeTypeFilter.end() && nodeTypeFilter.find("logical::Member") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Scope_HasMember", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Scope_HasMember", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFile_HasComment(const physical::File& begin, const base::Comment& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("File_HasComment") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("physical::File") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Comment") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "File_HasComment", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "File_HasComment", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFile_Includes(const physical::File& begin, const physical::File& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("File_Includes") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("physical::File") == nodeTypeFilter.end() && nodeTypeFilter.find("physical::File") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "File_Includes", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "File_Includes", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("FileSystem_HasFSEntry") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("physical::FileSystem") == nodeTypeFilter.end() && nodeTypeFilter.find("physical::FSEntry") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "FileSystem_HasFSEntry", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "FileSystem_HasFSEntry", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Folder_Contains") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("physical::Folder") == nodeTypeFilter.end() && nodeTypeFilter.find("physical::FSEntry") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Folder_Contains", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Folder_Contains", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Type_HasTypeFormer") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("type::Type") == nodeTypeFilter.end() && nodeTypeFilter.find("type::TypeFormer") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Type_HasTypeFormer", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Type_HasTypeFormer", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeFormerMethod_HasParameterType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("type::TypeFormerMethod") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeFormerMethod_HasParameterType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeFormerMethod_HasParameterType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeFormerMethod_HasReturnType") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("type::TypeFormerMethod") == nodeTypeFilter.end() && nodeTypeFilter.find("type::Type") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeFormerMethod_HasReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeFormerMethod_HasReturnType", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("TypeFormerType_RefersTo") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("type::TypeFormerType") == nodeTypeFilter.end() && nodeTypeFilter.find("base::Base") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeFormerType_RefersTo", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "TypeFormerType_RefersTo", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}


}}}
