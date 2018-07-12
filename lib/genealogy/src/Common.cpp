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
#include "genealogy/inc/messages.h"
#include <sstream>

namespace columbus { namespace genealogy { 
namespace Common {

bool getIsTrackable(const Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTrackable ||
    ndk == ndkSystem ||
    ndk == ndkClone ||
    ndk == ndkCloneClass ||
    ndk == ndkCloneInstance ||
    ndk == ndkStructuralClone ||
    ndk == ndkDataClumpsClass ||
    ndk == ndkDataClumps ||
    ndk == ndkSwitchStatementClass ||
    ndk == ndkSwitchStatement;
}

bool getIsSourceCodeElement(const Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSourceCodeElement ||
    ndk == ndkDataElement ||
    ndk == ndkCaseLabel;
}

bool getIsClone(const Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClone ||
    ndk == ndkCloneClass ||
    ndk == ndkCloneInstance;
}

bool getIsStructuralClone(const Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStructuralClone ||
    ndk == ndkDataClumpsClass ||
    ndk == ndkDataClumps ||
    ndk == ndkSwitchStatementClass ||
    ndk == ndkSwitchStatement;
}

bool getIsComposite(const Base& node) {
  return !getIsNotComposite(node);
}

bool getIsNotComposite(const Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTrackable ||
    ndk == ndkClone ||
    ndk == ndkCloneInstance ||
    ndk == ndkStructuralClone ||
    ndk == ndkDataClumpsClass ||
    ndk == ndkSwitchStatementClass ||
    ndk == ndkComponent ||
    ndk == ndkSourceCodeElement ||
    ndk == ndkDataElement ||
    ndk == ndkCaseLabel;
}

const std::string toString(NodeId id) {
  std::stringstream s;
  s << id;
  return s.str();
}

bool getIsBaseClassKind(NodeKind what, NodeKind base) {
  NodeKind type = what;
  if (type == base)
    return true;
  switch (type) {
      case ndkBase:
        return false;
      case ndkProject:
        return getIsBaseClassKind(ndkBase, base);
      case ndkTrackable:
        return getIsBaseClassKind(ndkBase, base);
      case ndkComponent:
        return getIsBaseClassKind(ndkBase, base);
      case ndkSourceCodeElement:
        return getIsBaseClassKind(ndkBase, base);
      case ndkSystem:
        return getIsBaseClassKind(ndkTrackable, base);
      case ndkClone:
        return getIsBaseClassKind(ndkTrackable, base);
      case ndkStructuralClone:
        return getIsBaseClassKind(ndkTrackable, base);
      case ndkCloneClass:
        return getIsBaseClassKind(ndkClone, base);
      case ndkCloneInstance:
        return getIsBaseClassKind(ndkClone, base);
      case ndkDataClumpsClass:
        return getIsBaseClassKind(ndkStructuralClone, base);
      case ndkDataClumps:
        return getIsBaseClassKind(ndkStructuralClone, base);
      case ndkDataElement:
        return getIsBaseClassKind(ndkSourceCodeElement, base);
      case ndkSwitchStatementClass:
        return getIsBaseClassKind(ndkStructuralClone, base);
      case ndkSwitchStatement:
        return getIsBaseClassKind(ndkStructuralClone, base);
      case ndkCaseLabel:
        return getIsBaseClassKind(ndkSourceCodeElement, base);
      default:
        return false;
  }
  return false;
}

const std::string toString(CloneType kind) {
  switch (kind) {
    case ctkType1: return "ctkType1";
    case ctkType2: return "ctkType2";
    case ctkType3: return "ctkType3";
    case ctkType4: return "ctkType4";
    default: throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(CloneSmellType kind) {
  switch (kind) {
    case cstNone: return "cstNone";
    case cstAppearing: return "cstAppearing";
    case cstDisappearing: return "cstDisappearing";
    case cstMoving: return "cstMoving";
    default: throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(DataClumpsKind kind) {
  switch (kind) {
    case dckNone: return "dckNone";
    case dckParameterList: return "dckParameterList";
    case dckClassFields: return "dckClassFields";
    case dckLocalVariables: return "dckLocalVariables";
    case dckMixed: return "dckMixed";
    default: throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(NodeKind kind) {
  switch (kind) {
    case ndkBase: return "ndkBase";
    case ndkProject: return "ndkProject";
    case ndkTrackable: return "ndkTrackable";
    case ndkComponent: return "ndkComponent";
    case ndkSourceCodeElement: return "ndkSourceCodeElement";
    case ndkSystem: return "ndkSystem";
    case ndkClone: return "ndkClone";
    case ndkStructuralClone: return "ndkStructuralClone";
    case ndkCloneClass: return "ndkCloneClass";
    case ndkCloneInstance: return "ndkCloneInstance";
    case ndkDataClumpsClass: return "ndkDataClumpsClass";
    case ndkDataClumps: return "ndkDataClumps";
    case ndkDataElement: return "ndkDataElement";
    case ndkSwitchStatementClass: return "ndkSwitchStatementClass";
    case ndkSwitchStatement: return "ndkSwitchStatement";
    case ndkCaseLabel: return "ndkCaseLabel";
    default: throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(EdgeKind kind) {
  switch (kind) {
    case edkProject_Systems: return "edkProject_Systems";
    case edkTrackable_Prev: return "edkTrackable_Prev";
    case edkTrackable_Next: return "edkTrackable_Next";
    case edkSystem_Components: return "edkSystem_Components";
    case edkSystem_CloneClasses: return "edkSystem_CloneClasses";
    case edkSystem_Smells: return "edkSystem_Smells";
    case edkSystem_Next: return "edkSystem_Next";
    case edkSystem_Prev: return "edkSystem_Prev";
    case edkCloneClass_NextNeighbours: return "edkCloneClass_NextNeighbours";
    case edkCloneClass_PrevNeighbours: return "edkCloneClass_PrevNeighbours";
    case edkCloneClass_Items: return "edkCloneClass_Items";
    case edkCloneInstance_Intersects: return "edkCloneInstance_Intersects";
    case edkCloneInstance_Component: return "edkCloneInstance_Component";
    case edkCloneInstance_CloneClass: return "edkCloneInstance_CloneClass";
    case edkDataClumpsClass_Items: return "edkDataClumpsClass_Items";
    case edkDataClumps_DataClumpsClass: return "edkDataClumps_DataClumpsClass";
    case edkDataClumps_Items: return "edkDataClumps_Items";
    case edkDataElement_Component: return "edkDataElement_Component";
    case edkSwitchStatementClass_Items: return "edkSwitchStatementClass_Items";
    case edkSwitchStatement_SwitchStatementClass: return "edkSwitchStatement_SwitchStatementClass";
    case edkSwitchStatement_Items: return "edkSwitchStatement_Items";
    case edkCaseLabel_Component: return "edkCaseLabel_Component";
    default: throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

bool getIsValid(NodeId id) {
  return id > 1;
}

double SimilarityMinimum = 0.1;

double getSimilarityMinimum() {
  return SimilarityMinimum;
}

void setSimilarityMinimum(double value) {
  SimilarityMinimum = value;
}

double SimilarityMinForStrings = 0.0;

double getSimilarityMinForStrings() {
  return SimilarityMinForStrings;
}

void setSimilarityMinForStrings(double value) {
  SimilarityMinForStrings = value;
}

double SimilarityMinForEdges = 0.0;

double getSimilarityMinForEdges() {
  return SimilarityMinForEdges;
}

void setSimilarityMinForEdges(double value) {
  SimilarityMinForEdges = value;
}

} // Common 

}}
