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

using namespace std;


namespace columbus { namespace genealogy { 
VisitorGENEALOGYML::VisitorGENEALOGYML(std::ofstream& targetStream,
                                       const std::string& _projectName,
                                       bool _noId,
                                       bool _noLineInfo) : ofs(targetStream), noId(_noId), noLineInfo(_noLineInfo), projectName(_projectName)
{
}

VisitorGENEALOGYML::~VisitorGENEALOGYML() {
}

void VisitorGENEALOGYML::beginVisit() {
  ofs << "<?xml version='1.0' encoding=\"utf-8\"?>\n";
  ofs << "<!DOCTYPE Project SYSTEM 'genealogy-1.3.19.dtd'>\n";
  ofs << "<Project name='" << projectName << "'"
      << ">\n";
}

void VisitorGENEALOGYML::finishVisit() {
  ofs << "<Filtered id='id1'/>\n";
  ofs << "</Project>\n";
}

void VisitorGENEALOGYML::visit(const Project& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<Project";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const Project& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</Project>\n";
}

void VisitorGENEALOGYML::visit(const Trackable& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<Trackable";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const Trackable& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</Trackable>\n";
}

void VisitorGENEALOGYML::visit(const Component& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<Component";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const Component& node , bool callVirtualBase) {
}

void VisitorGENEALOGYML::visit(const SourceCodeElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<SourceCodeElement";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const SourceCodeElement& node , bool callVirtualBase) {
}

void VisitorGENEALOGYML::visit(const System& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<System";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const System& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</System>\n";
}

void VisitorGENEALOGYML::visit(const Clone& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<Clone";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const Clone& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</Clone>\n";
}

void VisitorGENEALOGYML::visit(const StructuralClone& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<StructuralClone";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const StructuralClone& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</StructuralClone>\n";
}

void VisitorGENEALOGYML::visit(const CloneClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<CloneClass";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const CloneClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</CloneClass>\n";
}

void VisitorGENEALOGYML::visit(const CloneInstance& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<CloneInstance";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const CloneInstance& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</CloneInstance>\n";
}

void VisitorGENEALOGYML::visit(const DataClumpsClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<DataClumpsClass";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const DataClumpsClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</DataClumpsClass>\n";
}

void VisitorGENEALOGYML::visit(const DataClumps& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<DataClumps";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const DataClumps& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</DataClumps>\n";
}

void VisitorGENEALOGYML::visit(const DataElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<DataElement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const DataElement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</DataElement>\n";
}

void VisitorGENEALOGYML::visit(const SwitchStatementClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<SwitchStatementClass";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const SwitchStatementClass& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</SwitchStatementClass>\n";
}

void VisitorGENEALOGYML::visit(const SwitchStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<SwitchStatement";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const SwitchStatement& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</SwitchStatement>\n";
}

void VisitorGENEALOGYML::visit(const CaseLabel& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<CaseLabel";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorGENEALOGYML::visitEnd(const CaseLabel& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</CaseLabel>\n";
}

void VisitorGENEALOGYML::visitProject_Systems(const Project& begin, const System& end) {
  createIndentation();
  ofs << "<Project_Systems>\n";
  incDepth();
}

void VisitorGENEALOGYML::visitEndProject_Systems(const Project& begin, const System& end) {
  decDepth();
  createIndentation();
  ofs << "</Project_Systems>\n";
}

void VisitorGENEALOGYML::visitTrackable_Prev(const Trackable& begin, const Trackable& end) {
  createIndentation();
  ofs << "<Trackable_Prev ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndTrackable_Prev(const Trackable& begin, const Trackable& end) {
}

void VisitorGENEALOGYML::visitTrackable_Next(const Trackable& begin, const Trackable& end) {
  createIndentation();
  ofs << "<Trackable_Next ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndTrackable_Next(const Trackable& begin, const Trackable& end) {
}

void VisitorGENEALOGYML::visitSystem_Components(const System& begin, const Component& end) {
  createIndentation();
  ofs << "<System_Components>\n";
  incDepth();
}

void VisitorGENEALOGYML::visitEndSystem_Components(const System& begin, const Component& end) {
  decDepth();
  createIndentation();
  ofs << "</System_Components>\n";
}

void VisitorGENEALOGYML::visitSystem_CloneClasses(const System& begin, const CloneClass& end) {
  createIndentation();
  ofs << "<System_CloneClasses>\n";
  incDepth();
}

void VisitorGENEALOGYML::visitEndSystem_CloneClasses(const System& begin, const CloneClass& end) {
  decDepth();
  createIndentation();
  ofs << "</System_CloneClasses>\n";
}

void VisitorGENEALOGYML::visitSystem_Smells(const System& begin, const StructuralClone& end) {
  createIndentation();
  ofs << "<System_Smells>\n";
  incDepth();
}

void VisitorGENEALOGYML::visitEndSystem_Smells(const System& begin, const StructuralClone& end) {
  decDepth();
  createIndentation();
  ofs << "</System_Smells>\n";
}

void VisitorGENEALOGYML::visitSystem_Next(const System& begin, const System& end) {
  createIndentation();
  ofs << "<System_Next ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndSystem_Next(const System& begin, const System& end) {
}

void VisitorGENEALOGYML::visitSystem_Prev(const System& begin, const System& end) {
  createIndentation();
  ofs << "<System_Prev ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndSystem_Prev(const System& begin, const System& end) {
}

void VisitorGENEALOGYML::visitCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) {
  createIndentation();
  ofs << "<CloneClass_NextNeighbours ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) {
}

void VisitorGENEALOGYML::visitCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) {
  createIndentation();
  ofs << "<CloneClass_PrevNeighbours ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) {
}

void VisitorGENEALOGYML::visitCloneClass_Items(const CloneClass& begin, const CloneInstance& end) {
  createIndentation();
  ofs << "<CloneClass_Items>\n";
  incDepth();
}

void VisitorGENEALOGYML::visitEndCloneClass_Items(const CloneClass& begin, const CloneInstance& end) {
  decDepth();
  createIndentation();
  ofs << "</CloneClass_Items>\n";
}

void VisitorGENEALOGYML::visitCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) {
  createIndentation();
  ofs << "<CloneInstance_Intersects ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) {
}

void VisitorGENEALOGYML::visitCloneInstance_Component(const CloneInstance& begin, const Component& end) {
  createIndentation();
  ofs << "<CloneInstance_Component ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndCloneInstance_Component(const CloneInstance& begin, const Component& end) {
}

void VisitorGENEALOGYML::visitCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) {
  createIndentation();
  ofs << "<CloneInstance_CloneClass ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) {
}

void VisitorGENEALOGYML::visitDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) {
  createIndentation();
  ofs << "<DataClumpsClass_Items ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) {
}

void VisitorGENEALOGYML::visitDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) {
  createIndentation();
  ofs << "<DataClumps_DataClumpsClass ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) {
}

void VisitorGENEALOGYML::visitDataClumps_Items(const DataClumps& begin, const DataElement& end) {
  createIndentation();
  ofs << "<DataClumps_Items>\n";
  incDepth();
}

void VisitorGENEALOGYML::visitEndDataClumps_Items(const DataClumps& begin, const DataElement& end) {
  decDepth();
  createIndentation();
  ofs << "</DataClumps_Items>\n";
}

void VisitorGENEALOGYML::visitDataElement_Component(const DataElement& begin, const Component& end) {
  createIndentation();
  ofs << "<DataElement_Component ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndDataElement_Component(const DataElement& begin, const Component& end) {
}

void VisitorGENEALOGYML::visitSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) {
  createIndentation();
  ofs << "<SwitchStatementClass_Items ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) {
}

void VisitorGENEALOGYML::visitSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) {
  createIndentation();
  ofs << "<SwitchStatement_SwitchStatementClass ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) {
}

void VisitorGENEALOGYML::visitSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) {
  createIndentation();
  ofs << "<SwitchStatement_Items>\n";
  incDepth();
}

void VisitorGENEALOGYML::visitEndSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchStatement_Items>\n";
}

void VisitorGENEALOGYML::visitCaseLabel_Component(const CaseLabel& begin, const Component& end) {
  createIndentation();
  ofs << "<CaseLabel_Component ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorGENEALOGYML::visitEndCaseLabel_Component(const CaseLabel& begin, const Component& end) {
}

void VisitorGENEALOGYML::createIndentation() {
  if (depth)
    ofs << std::string(depth, '\t');
}

string VisitorGENEALOGYML::chk(string s) {
  string::size_type pos = (string::size_type)-1;
  while ((pos = s.find("&", pos + 1)) != string::npos)
    s.replace(pos, 1, "&amp;");

  while ((pos = s.find("<", pos + 1)) != string::npos)
    s.replace(pos,1, "&lt;");

  while ((pos = s.find(">", pos + 1)) != string::npos)
    s.replace(pos,1, "&gt;");

  while ((pos = s.find("'", pos + 1)) != string::npos)
    s.replace(pos,1,"&apos;");

  while ((pos = s.find("\"", pos + 1)) != string::npos)
    s.replace(pos,1,"&quot;");

  while ((pos = s.find("\r", pos + 1)) != string::npos)
    s.replace(pos,1, "&#13;");

  while ((pos = s.find("\n", pos + 1)) != string::npos)
    s.replace(pos,1, "&#10;");

  while ((pos = s.find("\t", pos + 1)) != string::npos)
    s.replace(pos,1, "&#09;");

  return s;
}

void VisitorGENEALOGYML::writeAttributes(const Base& node,bool composite, bool bWithParent /*= true*/ ) {
  if (!composite) {
    ofs << " id='";
    if (!noId)
      ofs << "id" << node.getId();
    ofs << "'";

  }
  if (!composite) {
    ofs << " parent='";
    if (!noId)
      ofs << "id" << (node.getParent() ? node.getParent()->getId() : 0);
    ofs << "'";

  }
  if (!composite) {
  }
}

void VisitorGENEALOGYML::writeAttributes(const Project& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Base&)node,composite,false);

  if (!composite) {
    ofs << " project='" << chk(node.getProject()) << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const Trackable& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Base&)node,composite,false);

}

void VisitorGENEALOGYML::writeAttributes(const Component& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Base&)node,composite,false);

  if (!composite) {
    ofs << " location='" << chk(node.getLocation()) << "'";
  }
  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
  if (!composite) {
    ofs << " code='" << node.getCode() << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const SourceCodeElement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Base&)node,composite,false);

  if (!composite) {
    ofs << " path='" << chk(node.getPath()) << "'";
  }
  if (!composite) {
    ofs << " line='" << node.getLine() << "'";
  }
  if (!composite) {
    ofs << " col='" << node.getCol() << "'";
  }
  if (!composite) {
    ofs << " endLine='" << node.getEndLine() << "'";
  }
  if (!composite) {
    ofs << " endCol='" << node.getEndCol() << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const System& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Trackable&)node,composite,false);

  if (!composite) {
    ofs << " age='" << node.getAge() << "'";
  }
  if (!composite) {
    ofs << " version='" << chk(node.getVersion()) << "'";
  }
  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
  if (!composite) {
    ofs << " limFileLocation='" << chk(node.getLimFileLocation()) << "'";
  }
  if (!composite) {
    ofs << " firstFreeID='" << node.getFirstFreeID() << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const Clone& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Trackable&)node,composite,false);

  if (!composite) {
    ofs << " uniqueName='" << chk(node.getUniqueName()) << "'";
  }
  if (!composite) {
    ofs << " cloneSmellType='" << Common::toString(node.getCloneSmellType()) << "'";
  }
  if (!composite) {
    ofs << " isVirtual='" << (node.getIsVirtual() ? "true" : "false") << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const StructuralClone& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Trackable&)node,composite,false);

  if (!composite) {
    ofs << " uniqueName='" << chk(node.getUniqueName()) << "'";
  }
  if (!composite) {
    ofs << " fullyQualifiedName='" << chk(node.getFullyQualifiedName()) << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const CloneClass& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Clone&)node,composite,false);

  if (!composite) {
    ofs << " fingerprint='" << chk(node.getFingerprint()) << "'";
  }
  if (!composite) {
    ofs << " instances='" << node.getInstances() << "'";
  }
  if (!composite) {
    ofs << " length='" << node.getLength() << "'";
  }
  if (!composite) {
    ofs << " headNodeKind='" << node.getHeadNodeKind() << "'";
  }
  if (!composite) {
    ofs << " cvCiSmells='" << node.getCvCiSmells() << "'";
  }
  if (!composite) {
    ofs << " ca='" << node.getCa() << "'";
  }
  if (!composite) {
    ofs << " risk='" << node.getRisk() << "'";
  }
  if (!composite) {
    ofs << " gain='" << node.getGain() << "'";
  }
  if (!composite) {
    ofs << " effort='" << node.getEffort() << "'";
  }
  if (!composite) {
    ofs << " cco='" << node.getCco() << "'";
  }
  if (!composite) {
    ofs << " ce='" << node.getCe() << "'";
  }
  if (!composite) {
    ofs << " clloc='" << node.getClloc() << "'";
  }
  if (!composite) {
    ofs << " cv='" << node.getCv() << "'";
  }
  if (!composite) {
    ofs << " ncrad='" << node.getNcrad() << "'";
  }
  if (!composite) {
    ofs << " type='" << Common::toString(node.getType()) << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const CloneInstance& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((Clone&)node,composite,false);

  if (!composite) {
    ofs << " path='" << chk(node.getPath()) << "'";
  }
  if (!composite) {
    ofs << " line='" << node.getLine() << "'";
  }
  if (!composite) {
    ofs << " col='" << node.getCol() << "'";
  }
  if (!composite) {
    ofs << " endLine='" << node.getEndLine() << "'";
  }
  if (!composite) {
    ofs << " endCol='" << node.getEndCol() << "'";
  }
  if (!composite) {
    ofs << " cvMetricVariability='" << node.getCvMetricVariability() << "'";
  }
  if (!composite) {
    ofs << " ca='" << node.getCa() << "'";
  }
  if (!composite) {
    ofs << " cco='" << node.getCco() << "'";
  }
  if (!composite) {
    ofs << " ce='" << node.getCe() << "'";
  }
  if (!composite) {
    ofs << " cv='" << node.getCv() << "'";
  }
  if (!composite) {
    ofs << " risk='" << node.getRisk() << "'";
  }
  if (!composite) {
    ofs << " rootNodes='" << chk(node.getRootNodes()) << "'";
  }
  if (!composite) {
    ofs << " rootBegin='" << node.getRootBegin() << "'";
  }
  if (!composite) {
    ofs << " rootLength='" << node.getRootLength() << "'";
  }
  if (!composite) {
    ofs << " F2_OrdinalNumber='" << node.getF2_OrdinalNumber() << "'";
  }
  if (!composite) {
    ofs << " F3_HeadNodeUniqueName='" << chk(node.getF3_HeadNodeUniqueName()) << "'";
  }
  if (!composite) {
    ofs << " F4_AncestorUniqueName='" << chk(node.getF4_AncestorUniqueName()) << "'";
  }
  if (!composite) {
    ofs << " F5_L1='" << node.getF5_L1() << "'";
  }
  if (!composite) {
    ofs << " F5_L2='" << node.getF5_L2() << "'";
  }
  if (!composite) {
    ofs << " F5_L3='" << node.getF5_L3() << "'";
  }
  if (!composite) {
    ofs << " F6_LexicalStructure='" << chk(node.getF6_LexicalStructure()) << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const DataClumpsClass& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((StructuralClone&)node,composite,false);

}

void VisitorGENEALOGYML::writeAttributes(const DataClumps& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((StructuralClone&)node,composite,false);

  if (!composite) {
    ofs << " kind='" << Common::toString(node.getKind()) << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const DataElement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((SourceCodeElement&)node,composite,false);

  if (!composite) {
    ofs << " asgId='" << node.getAsgId() << "'";
  }
  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
  if (!composite) {
    ofs << " type='" << node.getType() << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const SwitchStatementClass& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((StructuralClone&)node,composite,false);

}

void VisitorGENEALOGYML::writeAttributes(const SwitchStatement& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((StructuralClone&)node,composite,false);

  if (!composite) {
    ofs << " hasDefaultLabel='" << (node.getHasDefaultLabel() ? "true" : "false") << "'";
  }
}

void VisitorGENEALOGYML::writeAttributes(const CaseLabel& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((SourceCodeElement&)node,composite,false);

  if (!composite) {
    ofs << " caseValue='" << chk(node.getCaseValue()) << "'";
  }
  if (!composite) {
    ofs << " nodeId='" << node.getNodeId() << "'";
  }
}


}}
