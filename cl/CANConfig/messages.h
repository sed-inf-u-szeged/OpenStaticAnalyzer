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

#ifndef _CANCONFIG_M_H_
#define _CANCONFIG_M_H_

#define CMSG_COMMAND_EXECUTION_FAILED WriteMsg::mlError, "Execution of the command [%s] is failed!\n"
#define CMSG_LOAD_PREDEFINED_MACROS_FAILED WriteMsg::mlError, "Failed to load the file [%s] containing the predefined macros!\n"
#define CMSG_LOAD_COMPILER_OUTPUT_FAILED WriteMsg::mlError, "Failed to load the temporary file [%s] with the redirected output of the compiler!\n"
#define CMSG_UNDETERMINED_GCC_VERSION WriteMsg::mlWarning, "Can not determine the version of the gcc! [%s]\n"
#define CMSG_ERROR_OPEN_FILE WriteMsg::mlError, "Can not open file [%s] for writing!\n"
#define CMSG_ERROR_CREATE_FILE WriteMsg::mlError, "Can not create file [%s]!\n"
#define CMSG_OUTPUT_DIRECTORY_PARAMETER_IS_SETED WriteMsg::mlWarning, "Output directory parameter is already set to [%s]\n"
#define CMSG_COMPILER_IS_SETED WriteMsg::mlWarning, "Compiler is already set to [%s]\n"

#endif
