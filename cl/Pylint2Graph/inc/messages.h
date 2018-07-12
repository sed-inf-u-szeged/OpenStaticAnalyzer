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

#ifndef _PYLINT2GRAPH_MESSAGES_H_
#define _PYLINT2GRAPH_MESSAGES_H_

#define CMSG_WRONG_INPUT                                        WriteMsg::mlError,    "Error: Exactly 1 input text file is required, which contains the pylint rule violations.\n"
#define CMSG_RUNPYLINT_OPTION_ERROR                             WriteMsg::mlError,    "Error: When using -runpylint, the -pythonBinary, -pylintdir, -pylintrc, -projectbasedir and -pylintout options also must be specified\n"
#define CMSG_CANNOT_OPEN_FILE                                   WriteMsg::mlError,    "Error: Cannot open file: %s\n"
#define CMSG_PYTHON_BIN_ERROR                                   WriteMsg::mlError,    "Error: Python 2.7/3.x binary is not specified correctly.\n"

// PylintRunner.cpp
#define CMSG_ERROR_ENVSET_FAILURE                               WriteMsg::mlError,    "Error: Failed to set '%s' environment variable!\n"
#define CMSG_PYLINT_NO_INPUT                                    WriteMsg::mlWarning,  "Warning: There are no input packages to analyze.\n"
#define CMSG_PYLINT_NON_ZERO_EXIT                               WriteMsg::mlError,    "Error: pylint returned non-zero exit code: %d.\n"

// PylintRulMaker.cpp
#define CMSG_PYLINTRULMAKER_REGEXP_ERROR                        WriteMsg::mlDebug,    "Debug: Cannot recognize rule definition:\n  %s\n"

// Pylint2Graph.cpp
#define CMSG_PYLINT2GRAPH_USING_CONFIG                          WriteMsg::mlNormal,   "Using configuration: \"%s\"\n"
#define CMSG_PYLINT2GRAPH_LOADING_LIM                           WriteMsg::mlNormal,   "Loading LIM ASG file \"%s\"\n"
#define CMSG_PYLINT2GRAPH_LOADING_LIM_FILTER                    WriteMsg::mlNormal,   "Loading filter file \"%s\"\n"
#define CMSG_PYLINT2GRAPH_FILTER_FILE_IS_DEPRECATED             WriteMsg::mlWarning,  "Warning: Filter file (%s) is older than the input file. Filter file is not used.\n"
#define CMSG_PYLINT2GRAPH_LOAD_LIM_EXCEPTION                    WriteMsg::mlError,    "Error: LIM ASG file (%s) cannot be loaded: %s : %s\n"
#define CMSG_PYLINT2GRAPH_LOAD_FILTER_EXCEPTION                 WriteMsg::mlError,    "Error: Filter file (%s) cannot be loaded: %s : %s\n"
#define CMSG_PYLINT2GRAPH_MISSING_RULE                          WriteMsg::mlWarning,  "Warning: There is no rule named '%s' in the rul file, this warning will be ignored: path:%s line:%d text:'%s'\n"
#define CMSG_PYLINT2GRAPH_NO_NODE_FOUND_AT_PATH                 WriteMsg::mlWarning,  "Warning: Warning '%s' cannot be added as no node found at [path:%s line:%d col:%d endline:%d endcol:%d]\n"
#define CMSG_PYLINT2GRAPH_WARNING_ALREADY_ADDED                 WriteMsg::mlWarning,  "Warning: Warning '%s' has already been added. (node:%s path:%s line:%d col:%d endline:%d endcol:%d text:'%s')\n"
#define CMSG_PYLINT2GRAPH_REGEXP_ERROR                          WriteMsg::mlDebug,    "Debug: Cannot recognize rule violation:\n  %s\n"

#endif
