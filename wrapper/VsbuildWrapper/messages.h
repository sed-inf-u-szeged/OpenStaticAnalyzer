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

#ifndef _VSBUILDWRAPPER_MESSAGE_H_
#define _VSBUILDWRAPPER_MESSAGE_H_

#define CMSG_VSBUILD_WRAPPER_BIN_DIR_NOT_SET              WriteMsg::mlError, "[ERROR][VSBUILDWRAPPER] ERROR: WRAPPER_BIN_DIR environment variable is not set.\n"
#define CMSG_VSBUILD_ORIG_TOOL_NOT_FOUND                  WriteMsg::mlError, "[ERROR][VSBUILDWRAPPER] The original %s tool is not found\n"
#define CMSG_VSBUILD_WRONG_TOOL_NAME                      WriteMsg::mlError, "[ERROR][VSBUILDWRAPPER] Wrong file name, the name should be \"devenv.exe\" or \"msbuild.exe\".\n"

#endif