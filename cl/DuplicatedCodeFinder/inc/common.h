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

#ifndef __CLONES_COMMON_H
#define __CLONES_COMMON_H

#define DUMP_CSV_NEEDED

#include <fstream>
#include <iostream>
#include <string>
#include <map>   
#include <time.h> 
#include <limits>
#include <lim2graph/inc/Lim2GraphConverter.h>

//BOOST
#include<boost/lexical_cast.hpp>
#include<boost/algorithm/string.hpp>
#include<boost/filesystem.hpp>

#ifdef SCHEMA_JAVA
  #include "java/inc/java.h"
  #define LANGUAGE_NAMESPACE java::asg
#elif defined SCHEMA_PYTHON
  #include "python/inc/python.h"
  #define LANGUAGE_NAMESPACE python::asg
#endif

#define BASE_NAMESPACE base
#define TOGRAPH columbus::lim2graph
#define GET_LINE_OF_POSITIONS          getPosition().getLine()
#define GET_COLUMN_OF_POSITIONS        getPosition().getCol()
#define GET_END_LINE_OF_POSITIONS      getPosition().getEndLine()
#define GET_END_COLUMN_OF_POSITIONS    getPosition().getEndCol()
#define GET_FILE_KEY_OF_POSITIONS      getPosition().getPathKey()
#define GET_END_FILE_KEY_OF_POSITIONS  getPosition().getPathKey()

#define GENEALOGY

#include "types.h"
#include "csi/inc/csi.h"
#include "ErrorCodes.h"
#include "common/inc/FileSup.h"
#include "common/inc/StringSup.h"
#include "common/inc/Stat.h"
#include "strtable/inc/StrTable.h"
#include "lim/inc/lim.h"
#include "Config.h"
#include "ClonePositioned.h"
#include "Visitors/CloneVisitorBase.h"
#include "Visitors/CoverageVisitorBase.h"
#include "Visitors/PCoverageVisitor.h"
#include "Visitors/JCoverageVisitor.h"
#include "Visitors/NamedVisitor.h"
#include "Interval.h"
#include "AbstractFilter.h"
#include "Aligner.h"
#include "CloneLengthFilter.h"
#include "RepeatingLinesFilter.h"
#include "CloneOccuranceFilter.h"
#include "Visitors/DistanceVisitor.h"

extern Config config;

#endif
