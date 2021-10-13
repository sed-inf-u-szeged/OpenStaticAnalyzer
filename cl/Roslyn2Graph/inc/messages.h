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

#ifndef _ROSLYN2GRAPH_MESSAGE_H_
#define _ROSLYN2GRAPH_MESSAGE_H_

#define CMSG_NO_INPUT_DIR                                       WriteMsg::mlError,    "\nNo input directory was given!\n\n"
#define CMSG_NO_LIM_FILE                                        WriteMsg::mlError,    "\nNo lim file was given!\n\n"
#define CMSG_NO_OUTPUT_FILE                                     WriteMsg::mlError,    "\nNo output file was given!\n\n"
#define CMSG_FAILED_TO_OPEN_FILE                                WriteMsg::mlError,    "File %s can't be opened!\n"
#define CMSG_XERCES_ERROR                                       WriteMsg::mlError,    "ERROR: Error during XERCES initialization! :\n Exception message is: \n %s \n"

#define CMSG_ORIGINAL_RULE_NOT_EXIST                            WriteMsg::mlWarning,  "Original rule is not exists: %s\n"
#define CMSG_RULE_NOT_DEFINED                                   WriteMsg::mlWarning,  "Rule is not defined: %s\n"
#define CMSG_RULE_NO_NAME                                       WriteMsg::mlWarning,  "Rule %s does not have name!\n"
#define CMSG_FILE_NOT_EXISTS                                    WriteMsg::mlWarning,  "File does not exists: %s \n"

#define CMSG_WRITING_RULES_TO_GRAPH                             WriteMsg::mlNormal,   "Writing rules to graph\n"
#define CMSG_AGGREGATING_WARNINGS                               WriteMsg::mlNormal,   "Aggregating warnings\n"
#define CMSG_CREATING_GROUP_METRICS                             WriteMsg::mlNormal,   "Creating group metrics\n"
#define CMSG_PROCESSING_FILE                                    WriteMsg::mlNormal,   "Processing file: %s\n"
#define CMSG_SKIPPING_DUPLICATE_WARNING                         WriteMsg::mlNormal,   "Skipped duplicate warning: %s\n"
#define CMSG_WRITING_STAT_FILE                                  WriteMsg::mlNormal,   "Writing stat file\n"
#define CMSG_FINISHED                                           WriteMsg::mlNormal,   "Finished\n"

#define CMSG_EX_UNKNOWN_COMPONENT                               "\nCould not find component in the graph! "

#endif
