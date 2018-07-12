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

#ifndef _EXEWRAPPER_MESSAGES_H_
#define _EXEWRAPPER_MESSAGES_H_

#define CMSG_EXEWRAPPER_WRAPPER_BIN_DIR_NOT_SET               WriteMsg::mlError, "[ERROR][EXEWRAPPER] WRAPPER_BIN_DIR environment variable is not set.\n"
#define CMSG_EXEWRAPPER_WRAPPER_WORK_DIR_NAME_NOT_SET         WriteMsg::mlError, "[ERROR][EXEWRAPPER] WRAPPER_WORK_DIR_NAME environment variable is not set.\n"
#define CMSG_EXEWRAPPER_ORIG_TOOL_NOT_FOUND                   WriteMsg::mlError, "[ERROR][EXEWRAPPER] Not found the original program:%s\n"
#define CMSG_EXEWRAPPER_TOOL_RETURNED                         "ERROR: Wrapper tool returned with exit code"
#define CMSG_EXEWRAPPER_ORIG_TOOL_FAILED                      "WARNING: Original tool failed!"
#define CMSG_EXEWRAPPER_NO_NEED_TO_RUN_WRAPPER                "WARNING: No need to run wrapper tool because of filter or configuration!"

#endif
