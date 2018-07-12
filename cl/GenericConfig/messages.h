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

#ifndef _GENCFG_MESSAGES_H_
#define _GENCFG_MESSAGES_H_

#define CMSG_GENCFG_CL_ERROR                              WriteMsg::mlError,   "Error: %s"
#define CMSG_GENCFG_FILTER_CANNOT_BE_LOADED               WriteMsg::mlError,   "Error: The path of the config file must be given\n"
#define CMSG_GENCFG_ERROR_OPEN_FILE                       WriteMsg::mlError,   "Error: The options or a source file must be given\n"
#define CMSG_GENCFG_IO_ERROR                              WriteMsg::mlError,   "Error: Cannot open file: \"%s\"\n"
#define CMSG_GENCFG_SKIPPREFIX_OR_SKIPLINE_CANT_BE_USED   WriteMsg::mlWarning, "Warning: -skipprefix and -skipline options can be used only if source file is defined\n"
#define CMSG_GENCFG_WRONG_ARG_FORMAT                      WriteMsg::mlError,   "Error: Skipping argument because of wrong format (the proper format is: section/option=value)\n"
#define CMSG_GENCFG_ERR_REWRITE_OPTION                    WriteMsg::mlError,   "Error: Error while rewriting the '%s' option (section/option=value)\n"

#endif
