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

#ifndef ANALYZER_WRAPPER_CONFOG_H
#define ANALYZER_WRAPPER_CONFOG_H

#include <common/inc/StringSup.h>

#define ALLSECTION                        "ALL"                         ///< Section in the config file for all tool.

#define COMPILERSECTION                   "compiler"                    ///< Section in the config file for compiler tool.

#define LINKERSECTION                     "linker"                      ///< Section in the config file for linker tool.

#define ARCHIVESECTION                    "archive"                     ///< Section in the config file for archive tool.

#define OUTPUT_DIR                        "OUTPUT_DIR"                  ///< -outputDir

#define LINK_FILTER_FILE                  "LINK_FILTER_FILE"            ///< -linkerFilterFile

#define LINKING_MODE                      "LINKING_MODE"                ///< -linkingMode

#define NEED_TO_RUN                       "NEED_TO_RUN"                 ///< -needToRun

#define INST_MODE                         "INST_MODE"                   ///< -needToRun

#define NEED_STAT                         "NEED_STAT"                   ///< -needStat

#define CONFIG_DIR                        "CONFIG_DIR"                  ///< -configDir

#define PARAM_TO_SKIP                     "PARAM_TO_SKIP"               ///< -paramToSkip

#define NUM_OF_PARAM_TO_SKIP              "NUM_OF_PARAM_TO_SKIP"        ///< it is set to number of params that need to be skipped.

#define EXTRA_PARAM                       "EXTRA_PARAM"                 ///< -setExtraParam

#define NUM_OF_EXTRA_PARAM                "NUM_OF_EXTRA_PARAM"          ///< it is set to number of extra params

#define MESSAGE_LEVEL                     "MESSAGE_LEVEL"               ///< -messageLevel

#define TOOL_MESSAGE_LEVEL                "TOOL_MESSAGE_LEVEL"          ///< -toolMessageLevel

#define ENABLE_COMPILER_INSTRUMENT        "ENABLE_COMPILER_INSTRUMENT"  ///< -enableCompilerInstrument

#define PREPARE_FOR_INSTRUMENT            "PREPARE_FOR_INSTRUMENT"      ///< -prepareCompilerInstrument

#define RUN_CPPCHECK                      "RUN_CPPCHECK"                ///< -runCppcheck

#define ANALYZER_WRAPPER_CONFIG           "analyzer_wrapper_config.ini" ///< the name of the analyzer wrapper config file

#endif
