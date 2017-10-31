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

#ifndef _GENEALOGY_TYPES_H_
#define _GENEALOGY_TYPES_H_

/**
* \file Types.h
* \brief Contains declaration of internal types.
*/

namespace columbus { namespace genealogy { 
  enum CloneType {
    ctkType1,
    ctkType2,
    ctkType3,
    ctkType4,
    ctkLAST
  };

  enum CloneSmellType {
    cstNone,
    cstAppearing,
    cstDisappearing,
    cstMoving,
    cstLAST
  };

  enum DataClumpsKind {
    dckNone,
    dckParameterList,
    dckClassFields,
    dckLocalVariables,
    dckMixed,
    dckLAST
  };

  enum NodeKind {
    ndkBase,
    ndkProject,
    ndkTrackable,
    ndkComponent,
    ndkSourceCodeElement,
    ndkSystem,
    ndkClone,
    ndkStructuralClone,
    ndkCloneClass,
    ndkCloneInstance,
    ndkDataClumpsClass,
    ndkDataClumps,
    ndkDataElement,
    ndkSwitchStatementClass,
    ndkSwitchStatement,
    ndkCaseLabel,
    ndkLAST
  };

  enum EdgeKind {
    edkProject_Systems,
    edkTrackable_Prev,
    edkTrackable_Next,
    edkSystem_Components,
    edkSystem_CloneClasses,
    edkSystem_Smells,
    edkSystem_Next,
    edkSystem_Prev,
    edkCloneClass_NextNeighbours,
    edkCloneClass_PrevNeighbours,
    edkCloneClass_Items,
    edkCloneInstance_Intersects,
    edkCloneInstance_Component,
    edkCloneInstance_CloneClass,
    edkDataClumpsClass_Items,
    edkDataClumps_DataClumpsClass,
    edkDataClumps_Items,
    edkDataElement_Component,
    edkSwitchStatementClass_Items,
    edkSwitchStatement_SwitchStatementClass,
    edkSwitchStatement_Items,
    edkCaseLabel_Component,
    edkLAST
  };


}}
#endif

