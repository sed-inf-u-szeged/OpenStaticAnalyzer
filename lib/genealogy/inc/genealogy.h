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

#ifndef _GENEALOGY_H_
#define _GENEALOGY_H_

/**
* \file GENEALOGY.h
* \brief Header can be used for precompiled header.
*/
#include <list>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <boost/crc.hpp>

#include "Forwards.h"

// externals
#include "AsgCommon.h"
#include "strtable/inc/RefDistributorStrTable.h"
#include "csi/inc/csi.h"
#include "Exception.h"

#include "Constant.h"
#include "Types.h"
#include "GenealogyException.h"
#include "ListIterator.h"
#include "Common.h"
#include "ReverseEdges.h"


 /***********************NODES******************/
#include "nodes/Base.h"
#include "nodes/Project.h"
#include "nodes/Trackable.h"
#include "nodes/Component.h"
#include "nodes/SourceCodeElement.h"
#include "nodes/System.h"
#include "nodes/Clone.h"
#include "nodes/StructuralClone.h"
#include "nodes/DataElement.h"
#include "nodes/CaseLabel.h"
#include "nodes/CloneClass.h"
#include "nodes/CloneInstance.h"
#include "nodes/DataClumpsClass.h"
#include "nodes/DataClumps.h"
#include "nodes/SwitchStatementClass.h"
#include "nodes/SwitchStatement.h"


#include "Factory.h"

#include "visitors/Visitor.h"
#include "visitors/VisitorAbstractNodes.h"
#include "visitors/VisitorGraphml.h"
#include "visitors/VisitorGENEALOGYML.h"
#include "visitors/VisitorReverseEdges.h"
#include "visitors/VisitorSave.h"
#include "visitors/VisitorSubtreeCollector.h"
#include "visitors/VisitorSimpleEdge.h"

#include "algorithms/Algorithm.h"
#include "algorithms/AlgorithmPreorder.h"

#endif

