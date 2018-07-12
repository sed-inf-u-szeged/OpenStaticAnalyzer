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

#ifndef _FX2G_M_H_
#define _FX2G_M_H_

//ConvertRule.cpp messages
#define CMSG_FX2GRAPH_ERROR_DURING_INIT                          WriteMsg::mlError, "Error: Initialization error: '%s'\n"
#define CMSG_XERCES_ERROR                                        WriteMsg::mlError, "ERROR: Error during XERCES initialization! :\n Exception message is: \n %s \n"
#define CMSG_FILE_PARSE_ERROR                                    WriteMsg::mlError, "ERROR: Exception at parse %s file: %s\n"

//MetricTree.cpp messages
#define CMSG_FREE_VERSION_MESSAGE                                 WriteMsg::mlNormal,   "There is no valid license!\n"
#define CMSG_FXCOP2GRAPH_USING_CONFIG                          WriteMsg::mlNormal,   "Using configuration: \"%s\"\n"
#define CMSG_FXCOP2GRAPH_LOADING_LIM                           WriteMsg::mlNormal,   "Loading LIM ASG file \"%s\"\n"
#define CMSG_FXCOP2GRAPH_LOADING_LIM_FILTER                    WriteMsg::mlNormal,   "Loading filter file \"%s\"\n"
#define CMSG_FXCOP2GRAPH_FILTER_FILE_IS_DEPRECATED             WriteMsg::mlWarning,  "Warning: Filter file (%s) is older than the input file. Filter file is not used.\n"
#define CMSG_FXCOP2GRAPH_LOAD_LIM_EXCEPTION                    WriteMsg::mlError,    "Error: LIM ASG file (%s) cannot be loaded: %s : %s\n"
#define CMSG_FXCOP2GRAPH_LOAD_FILTER_EXCEPTION                 WriteMsg::mlError,    "Error: Filter file (%s) cannot be loaded: %s : %s\n"
#define CMSG_FXCOP2GRAPH_NO_NODE_FOUND_AT_PATH                 WriteMsg::mlWarning,  "Warning: Warning '%s' cannot be added as no node found at [path:%s line:%d col:%d endline:%d endcol:%d]\n"
#define CMSG_FXCOP2GRAPH_WARNING_ALREADY_ADDED                 WriteMsg::mlWarning,  "Warning: Warning '%s' has already been added. (node:%s path:%s line:%d col:%d endline:%d endcol:%d text:'%s')\n"
#define CMSG_FXCOP2GRAPH_NO_SOURCEINFO_FOUND                   WriteMsg::mlWarning,  "Warning: Sourc info cannot be found in the BugInstance\n"
#define CMSG_FXCOP2GRAPH_NOT_FOUND_IN_LIM                       WriteMsg::mlWarning,  "Warning: The \"%s\" path cannot be found in the LIM.\n"
#define CMSG_FXCOP2GRAPH_UNABLE_TO_APPEND_TO_FILE               WriteMsg::mlError,    "Error: Unable to append to file:\"%s\"\n"

#define CMSG_FXCOP2GRAPH_MISSING_LIM                           WriteMsg::mlError,    "Error: No LIM file is given!\n"
#define CMSG_FXCOP2GRAPH_MISSING_ASG                           WriteMsg::mlError,    "Error: No java ASG file is given!\n"
#define CMSG_FXCOP2GRAPH_RULE_EXCEPTION                        WriteMsg::mlWarning,  "Warning: %s\n"
#define CMSG_FXCOP2GRAPH_MISSIG_RUL(RULEID)                            WriteMsg::mlWarning,  "Warning: Unsupported rule! (id: " +RULEID+ ")\n"

#endif