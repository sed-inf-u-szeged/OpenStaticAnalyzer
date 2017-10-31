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

#ifndef _WRAPPER_ENVIRONMENT_COMMON_H_
#define _WRAPPER_ENVIRONMENT_COMMON_H_

#include <common/inc/StringSup.h>

#define WRAPPERSECTION                          "WRAPPER"                                     ///< Wrapper environment section

#define WRAPPER_WORKING_DIR                     "WRAPPER_WORKING_DIR"                         ///< Path of the wrapper working directory.

#define WRAPPER_ML                              "WRAPPER_ML"                                  ///< Message level value.

#define WRAPPER_LOG_FILE                        "WRAPPER_LOG_FILE"                            ///< Name of the logfile. It is generated into the log directory. 

#define WRAPPED_TO_WRAPPER                      "WRAPPEDTOOL_TO_WRAPPERTOOL"                  ///< Names of the wrapped tools and the wrapper tools in pairs. 

#define STARTWRAPPERSECTION                     "START"                                       ///< Config file section for start options

#define STOPWRAPPERSECTION                      "STOP"                                        ///< Config file section for stop options

#define OTHER_START_TOOLS                       "OTHER_START_TOOLS"                           ///< Other scripts and programs. Separated by semicolon. The StartWrapper script has to call them.

#define OTHER_STOP_TOOLS                        "OTHER_STOP_TOOLS"                            ///< Other scripts and programs. Separated by semicolon. The StopWrapper script has to call them.

#define WRAPPEDTOOL_LOGGING                     "WRAPPEDTOOL_LOGGING"                         ///< -setwrappedlog

#define WRAPPERTOOL_LOGGING                     "WRAPPERTOOL_LOGGING"                         ///< -setwrapperlog

#define WRAPPEDTOOL_RUN                         "WRAPPEDTOOL_RUN"                             ///< -setwrappedrun

#define WRAPPERTOOL_RUN_FIRST                   "WRAPPERTOOL_RUN_FIRST"                       ///< -setwrapperfirst

#define WRAPPERTOOL_ALWAYS_RUN                  "WRAPPERTOOL_ALWAYS_RUN"                      ///< -setwrapperalwaysrun

#define WRAPPERTOOL_EXTRA_PARAM                 "WRAPPERTOOL_EXTRA_PARAM"                     ///< -setwrapperextraparam

#define WRAPPEDTOOL_EXTRA_PARAM_AFTER_PARAM     "WRAPPEDTOOL_EXTRA_PARAM_AFTER_PARAM"         ///< -setwrappedextraparamafterparam

#define WRAPPEDTOOL_EXTRA_PARAM_TO_BEGIN        "WRAPPEDTOOL_EXTRA_PARAM_TO_BEGIN"            ///< -setwrappedextraparambegin

#define WRAPPEDTOOL_EXTRA_PARAM_TO_END          "WRAPPEDTOOL_EXTRA_PARAM_TO_END"              ///< -setwrappedextraparamend

#define WRAPPEDTOOL_REMOVE_PARAM                "WRAPPEDTOOL_REMOVE_PARAM"                    ///< -setwrappedremoveparam

#define WRAPPERTOOL_DIRECTORY_FILTER            "WRAPPERTOOL_DIRECTORY_FILTER"                ///< -setwrapperdirectoryfilter

#define WRAPPEDTOOL_PARAM_FILTER                "WRAPPEDTOOL_PARAM_FILTER"                    ///< -setwrappedparamfilter

#define WRAPPEDTOOL_RETURN_SUCCESSFUL           "WRAPPEDTOOL_RETURN_SUCCESSFUL"               ///< -setwrappedreturn

#define CHANGE_ORIGINAL                         "CHANGE_ORIGINAL"                             ///< it is set to 1 if there is full path wrappering

#define ORIGINAL_TOOL                           "ORIGINAL_TOOL"                               ///< -setoriginal

#define NUMBER_OF_WRAPPER_EXTRA_PARAMS          "NUMBER_OF_WRAPPER_EXTRA_PARAMS"              ///< it is set to number of extra params

#define NUMBER_OF_WRAPPED_PARAMS_AFTER_PARAMS   "NUMBER_OF_WRAPPED_PARAMS_AFTER_PARAMS"       ///< it is set to number of wrapped params that put after other param

#define NUMBER_OF_WRAPPED_PARAMS_BEGIN          "NUMBER_OF_WRAPPED_PARAMS_BEGIN"              ///< it is set ot number of wrapped params that put at the begin of the paramlist.

#define NUMBER_OF_WRAPPED_PARAMS_END            "NUMBER_OF_WRAPPED_PARAMS_END"                ///< it is set ot number of wrapped params that put at the end of the paramlist.

#define NUMBER_OF_REMOVE_PARAMS                 "NUMBER_OF_REMOVE_PARAMS"                     ///< it is set to number of wrapped params that need to be removed

#define WRAPPER_ENVIRONMENT_CONFIG              "wrapper_environment_config.ini"              ///< it is the name of the wrapper environment config file

#define WRAPPER_CAN_CAUSE_ERROR                 "WRAPPER_CAN_CAUSE_ERROR"                     ///< if it is set then a wrapper program error overrides the return value of the original command.


#endif