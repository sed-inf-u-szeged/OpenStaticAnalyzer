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

#include "genealogy/inc/genealogy.h"
#include "common/inc/StringSup.h"
#include <set>
#include <string>

using namespace columbus::io;

namespace columbus { namespace genealogy { 

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

void VisitorGraphml::addAttributeToContent(const Base& node, std::string& content, bool callVirtualBase) {
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("Base") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "id : " + common::toString(node.getId()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const Project& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("Project") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "project : " + node.getProject() + "\n";
}

void VisitorGraphml::addAttributeToContent(const Trackable& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("Trackable") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const Component& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("Component") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "location : " + node.getLocation() + "\n";
  content += "name : " + node.getName() + "\n";
  content += "code : " + common::toString(node.getCode()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const SourceCodeElement& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Base&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("SourceCodeElement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "path : " + node.getPath() + "\n";
  content += "line : " + common::toString(node.getLine()) + "\n";
  content += "col : " + common::toString(node.getCol()) + "\n";
  content += "endLine : " + common::toString(node.getEndLine()) + "\n";
  content += "endCol : " + common::toString(node.getEndCol()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const System& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Trackable&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("System") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "age : " + common::toString(node.getAge()) + "\n";
  content += "version : " + node.getVersion() + "\n";
  content += "name : " + node.getName() + "\n";
  content += "limFileLocation : " + node.getLimFileLocation() + "\n";
  content += "firstFreeID : " + common::toString(node.getFirstFreeID()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const Clone& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Trackable&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("Clone") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "uniqueName : " + node.getUniqueName() + "\n";
  content += "cloneSmellType : " + Common::toString(node.getCloneSmellType()) + "\n";
  content += "isVirtual : " + std::string(node.getIsVirtual() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const StructuralClone& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Trackable&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("StructuralClone") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "uniqueName : " + node.getUniqueName() + "\n";
  content += "fullyQualifiedName : " + node.getFullyQualifiedName() + "\n";
}

void VisitorGraphml::addAttributeToContent(const CloneClass& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Clone&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("CloneClass") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "fingerprint : " + node.getFingerprint() + "\n";
  content += "instances : " + common::toString(node.getInstances()) + "\n";
  content += "length : " + common::toString(node.getLength()) + "\n";
  content += "headNodeKind : " + common::toString(node.getHeadNodeKind()) + "\n";
  content += "cvCiSmells : " + common::toString(node.getCvCiSmells()) + "\n";
  content += "ca : " + common::toString(node.getCa()) + "\n";
  content += "risk : " + common::toString(node.getRisk()) + "\n";
  content += "gain : " + common::toString(node.getGain()) + "\n";
  content += "effort : " + common::toString(node.getEffort()) + "\n";
  content += "cco : " + common::toString(node.getCco()) + "\n";
  content += "ce : " + common::toString(node.getCe()) + "\n";
  content += "clloc : " + common::toString(node.getClloc()) + "\n";
  content += "cv : " + common::toString(node.getCv()) + "\n";
  content += "ncrad : " + common::toString(node.getNcrad()) + "\n";
  content += "type : " + Common::toString(node.getType()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const CloneInstance& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const Clone&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("CloneInstance") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "path : " + node.getPath() + "\n";
  content += "line : " + common::toString(node.getLine()) + "\n";
  content += "col : " + common::toString(node.getCol()) + "\n";
  content += "endLine : " + common::toString(node.getEndLine()) + "\n";
  content += "endCol : " + common::toString(node.getEndCol()) + "\n";
  content += "cvMetricVariability : " + common::toString(node.getCvMetricVariability()) + "\n";
  content += "ca : " + common::toString(node.getCa()) + "\n";
  content += "cco : " + common::toString(node.getCco()) + "\n";
  content += "ce : " + common::toString(node.getCe()) + "\n";
  content += "cv : " + common::toString(node.getCv()) + "\n";
  content += "risk : " + common::toString(node.getRisk()) + "\n";
  content += "rootNodes : " + node.getRootNodes() + "\n";
  content += "rootBegin : " + common::toString(node.getRootBegin()) + "\n";
  content += "rootLength : " + common::toString(node.getRootLength()) + "\n";
  content += "F2_OrdinalNumber : " + common::toString(node.getF2_OrdinalNumber()) + "\n";
  content += "F3_HeadNodeUniqueName : " + node.getF3_HeadNodeUniqueName() + "\n";
  content += "F4_AncestorUniqueName : " + node.getF4_AncestorUniqueName() + "\n";
  content += "F5_L1 : " + common::toString(node.getF5_L1()) + "\n";
  content += "F5_L2 : " + common::toString(node.getF5_L2()) + "\n";
  content += "F5_L3 : " + common::toString(node.getF5_L3()) + "\n";
  content += "F6_LexicalStructure : " + node.getF6_LexicalStructure() + "\n";
}

void VisitorGraphml::addAttributeToContent(const DataClumpsClass& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const StructuralClone&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("DataClumpsClass") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const DataClumps& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const StructuralClone&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("DataClumps") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "kind : " + Common::toString(node.getKind()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const DataElement& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const SourceCodeElement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("DataElement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "asgId : " + common::toString(node.getAsgId()) + "\n";
  content += "name : " + node.getName() + "\n";
  content += "type : " + common::toString(node.getType()) + "\n";
}

void VisitorGraphml::addAttributeToContent(const SwitchStatementClass& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const StructuralClone&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("SwitchStatementClass") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
}

void VisitorGraphml::addAttributeToContent(const SwitchStatement& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const StructuralClone&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("SwitchStatement") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "hasDefaultLabel : " + std::string(node.getHasDefaultLabel() ? "true" : "false") + "\n";
}

void VisitorGraphml::addAttributeToContent(const CaseLabel& node, std::string& content, bool callVirtualBase) {
  addAttributeToContent(static_cast<const SourceCodeElement&>(node), content, false);
  if ( !((nodeTypeAttributeFilter.empty()) || ( nodeTypeAttributeFilter.find("CaseLabel") != nodeTypeAttributeFilter.end())))
  {
    return;
  }
  content += "caseValue : " + node.getCaseValue() + "\n";
  content += "nodeId : " + common::toString(node.getNodeId()) + "\n";
}

void VisitorGraphml::visit(const Project& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Project") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("Project");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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
    if(!node.getSystemsIsEmpty())
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

void VisitorGraphml::visitEnd(const Project& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Project") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const Trackable& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Trackable") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("Trackable");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const Trackable& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Trackable") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const Component& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Component") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("Component");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const Component& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Component") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const SourceCodeElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("SourceCodeElement") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("SourceCodeElement");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const SourceCodeElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("SourceCodeElement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const System& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("System") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("System");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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
    if(!node.getComponentsIsEmpty() || !node.getCloneClassesIsEmpty() || !node.getSmellsIsEmpty())
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

void VisitorGraphml::visitEnd(const System& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("System") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const Clone& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Clone") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("Clone");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const Clone& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("Clone") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const StructuralClone& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("StructuralClone") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("StructuralClone");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const StructuralClone& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("StructuralClone") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const CloneClass& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("CloneClass");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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
    if(!node.getItemsIsEmpty())
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

void VisitorGraphml::visitEnd(const CloneClass& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const CloneInstance& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("CloneInstance") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("CloneInstance");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const CloneInstance& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("CloneInstance") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const DataClumpsClass& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("DataClumpsClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("DataClumpsClass");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const DataClumpsClass& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("DataClumpsClass") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const DataClumps& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("DataClumps") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("DataClumps");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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
    if(!node.getItemsIsEmpty())
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

void VisitorGraphml::visitEnd(const DataClumps& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("DataClumps") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const DataElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("DataElement") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("DataElement");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const DataElement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("DataElement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const SwitchStatementClass& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("SwitchStatementClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("SwitchStatementClass");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const SwitchStatementClass& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("SwitchStatementClass") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const SwitchStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("SwitchStatement") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("SwitchStatement");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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
    if(!node.getItemsIsEmpty())
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

void VisitorGraphml::visitEnd(const SwitchStatement& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("SwitchStatement") == nodeTypeFilter.end())))
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

void VisitorGraphml::visit(const CaseLabel& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("CaseLabel") == nodeTypeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0) 
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( node.getId());
    if ( foundDrawedNode != idsToDrawedNodes.end())
      if (foundDrawedNode->second)
        return;
      else
        foundDrawedNode->second = true;
    else
      return;
  }
  std::string content;
  std::string title("CaseLabel");
  std::string titleBGColor("#ccccff");
  std::string fillColor("#ccffff");
  addAttributeToContent(node, content, true);
  compositeContentFormatter(content);
  if(isGroupingTreeNodes){ 
    if(edgeKindStack.begin() != edgeKindStack.end() && *(edgeKindStack.begin()) != node.getParentEdgeKind() && node.getParent() && *(parentNodeStack.begin()) == node.getParent()->getId()){
      io.writeGroupNodeEnd();
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

void VisitorGraphml::visitEnd(const CaseLabel& node, bool callVirtualBase) {
  if ( !((nodeTypeFilter.empty()) || ( nodeTypeFilter.find("CaseLabel") == nodeTypeFilter.end())))
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

void  VisitorGraphml::visitProject_Systems(const Project& begin, const System& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Project_Systems") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("Project") == nodeTypeFilter.end() && nodeTypeFilter.find("System") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Project_Systems", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Project_Systems", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTrackable_Prev(const Trackable& begin, const Trackable& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Trackable_Prev") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("Trackable") == nodeTypeFilter.end() && nodeTypeFilter.find("Trackable") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Trackable_Prev", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Trackable_Prev", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitTrackable_Next(const Trackable& begin, const Trackable& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("Trackable_Next") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("Trackable") == nodeTypeFilter.end() && nodeTypeFilter.find("Trackable") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "Trackable_Next", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "Trackable_Next", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSystem_Components(const System& begin, const Component& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("System_Components") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("System") == nodeTypeFilter.end() && nodeTypeFilter.find("Component") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Components", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Components", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSystem_CloneClasses(const System& begin, const CloneClass& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("System_CloneClasses") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("System") == nodeTypeFilter.end() && nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "System_CloneClasses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "System_CloneClasses", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSystem_Smells(const System& begin, const StructuralClone& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("System_Smells") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("System") == nodeTypeFilter.end() && nodeTypeFilter.find("StructuralClone") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Smells", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Smells", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSystem_Next(const System& begin, const System& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("System_Next") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("System") == nodeTypeFilter.end() && nodeTypeFilter.find("System") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Next", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Next", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSystem_Prev(const System& begin, const System& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("System_Prev") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("System") == nodeTypeFilter.end() && nodeTypeFilter.find("System") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Prev", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "System_Prev", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CloneClass_NextNeighbours") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end() && nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneClass_NextNeighbours", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneClass_NextNeighbours", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CloneClass_PrevNeighbours") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end() && nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneClass_PrevNeighbours", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneClass_PrevNeighbours", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCloneClass_Items(const CloneClass& begin, const CloneInstance& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CloneClass_Items") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end() && nodeTypeFilter.find("CloneInstance") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneClass_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneClass_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CloneInstance_Intersects") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("CloneInstance") == nodeTypeFilter.end() && nodeTypeFilter.find("CloneInstance") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneInstance_Intersects", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneInstance_Intersects", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCloneInstance_Component(const CloneInstance& begin, const Component& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CloneInstance_Component") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("CloneInstance") == nodeTypeFilter.end() && nodeTypeFilter.find("Component") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneInstance_Component", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneInstance_Component", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CloneInstance_CloneClass") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("CloneInstance") == nodeTypeFilter.end() && nodeTypeFilter.find("CloneClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneInstance_CloneClass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CloneInstance_CloneClass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DataClumpsClass_Items") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("DataClumpsClass") == nodeTypeFilter.end() && nodeTypeFilter.find("DataClumps") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DataClumpsClass_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DataClumpsClass_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DataClumps_DataClumpsClass") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("DataClumps") == nodeTypeFilter.end() && nodeTypeFilter.find("DataClumpsClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DataClumps_DataClumpsClass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DataClumps_DataClumpsClass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDataClumps_Items(const DataClumps& begin, const DataElement& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DataClumps_Items") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("DataClumps") == nodeTypeFilter.end() && nodeTypeFilter.find("DataElement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DataClumps_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DataClumps_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitDataElement_Component(const DataElement& begin, const Component& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("DataElement_Component") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("DataElement") == nodeTypeFilter.end() && nodeTypeFilter.find("Component") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "DataElement_Component", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "DataElement_Component", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchStatementClass_Items") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("SwitchStatementClass") == nodeTypeFilter.end() && nodeTypeFilter.find("SwitchStatement") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatementClass_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatementClass_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchStatement_SwitchStatementClass") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("SwitchStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("SwitchStatementClass") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_SwitchStatementClass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_SwitchStatementClass", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) {
  if(isGroupingTreeNodes)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("SwitchStatement_Items") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("SwitchStatement") == nodeTypeFilter.end() && nodeTypeFilter.find("CaseLabel") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "SwitchStatement_Items", 1, GraphmlIO::ls_line, GraphmlIO::at_diamond, GraphmlIO::at_none);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}

void  VisitorGraphml::visitCaseLabel_Component(const CaseLabel& begin, const Component& end) {
  if (!visitCrossEdge)
    return;
  if ( (this->getDepth() >= maxDrawingDepth) && ( maxDrawingDepth > 0))
    return;
  if ( !((edgeFilter.empty()) || ( edgeFilter.find("CaseLabel_Component") != edgeFilter.end())))
  {
    return;
  }
  if ( maxDrawingDepth > 0)
  {
    std::map<NodeId, bool>::iterator foundDrawedNode = idsToDrawedNodes.find( begin.getId());
    if ( foundDrawedNode == idsToDrawedNodes.end())
      return;
  }
  if ( !((nodeTypeFilter.empty()) || (nodeTypeFilter.find("CaseLabel") == nodeTypeFilter.end() && nodeTypeFilter.find("Component") == nodeTypeFilter.end())))
  {
    return;
  }
  if(isGroupingTreeNodes)
    io.writeEdgeBuffer(Common::toString(begin.getId()), Common::toString(end.getId()), "CaseLabel_Component", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  else
    io.writeEdge(Common::toString(begin.getId()), Common::toString(end.getId()), "CaseLabel_Component", 1, GraphmlIO::ls_line, GraphmlIO::at_none, GraphmlIO::at_standard);
  idsToDrawedNodes.insert( std::make_pair( end.getId(),false));
}


}}
