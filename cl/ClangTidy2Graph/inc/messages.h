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

#ifndef _CLANGTIDY2GRAPH_MESSAGE_H_
#define _CLANGTIDY2GRAPH_MESSAGE_H_

#define CMSG_NO_INPUT_FILE                                      WriteMsg::mlError,    "\nNo input file was given!\n\n"
#define CMSG_NO_OUTPUT_FILE                                     WriteMsg::mlError,    "\nNo output file was given!\n\n"
#define CMSG_FAILED_TO_OPEN_FILE                                WriteMsg::mlError,    "File %s can't be opened!\n"
#define CMSG_UNABLE_TO_ADD_WARNING_AT_LOCATION                  WriteMsg::mlWarning,  "Unable to add warning at location: %s(%d)\n"
#define CMSG_WRONG_XML_FORMAT_VERSION                           WriteMsg::mlWarning,  "The given error list XML file has wrong format version number!\n"
#define CMSG_ORIGINAL_RULE_NOT_EXIST                            WriteMsg::mlWarning,  "Original rule is not exists: %s\n"
#define CMSG_RULE_NOT_DEFINED                                   WriteMsg::mlWarning,  "Rule is not defined: %s\n"
#define CMSG_RULE_NO_NAME                                       WriteMsg::mlWarning,  "Rule %s does not have name!\n"
#define CMSG_FILE_NOT_EXISTS  

#endif
