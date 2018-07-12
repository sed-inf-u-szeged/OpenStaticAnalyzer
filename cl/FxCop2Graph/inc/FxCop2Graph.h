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

#ifndef _FXCOP2GRAPH_H_
#define _FXCOP2GRAPH_H_

#include <string>
#include <list>
#include <iostream>
#include <algorithm>

#include <graph/inc/graph.h>
#include <graphsupport/inc/GraphRangeIndexer.h>
#include <strtable/inc/RefDistributorStrTable.h>
#include <lim/inc/lim.h>
#include <rul/inc/RulHandler.h>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <common/inc/WriteMessage.h>
#include <boost/filesystem.hpp>

#include "messages.h"


#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <lim2graph/inc/Lim2GraphConverter.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/MetricSum.h>
#include <graphsupport/inc/GraphConstants.h>
#include <graphsupport/inc/RulBuilder.h>
#include <graphsupport/inc/GraphConstants.h>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>

#include <boost/filesystem.hpp>
#include "Config.h"

#endif