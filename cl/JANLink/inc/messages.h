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

#ifndef _JANLINK_MESSAGES_H_
#define _JANLINK_MESSAGES_H_

//EXCEPTIONS
#define CMSG_EX_NODE_HAS_NOT_BEEN_BUILT_INTO_THE_NEW_ASG(ID)    "The node id" + Common::toString(ID) + " has not been built into the new ASG."
#define CMSG_EX_NODE_NOT_EXIST(ID)                              "The node id" + Common::toString(ID) + " does not exist."
#define CMSG_EX_CANNOT_CAST_NODE_TO(ID, KIND, TO)               "Cannot cast node (id:" + Common::toString(ID) + ", kind:" + Common::toString(KIND) + ") to type '" + TO + "'"
#define CMSG_EX_WRONG_PARAMETER_NODE(ID)                        "Wrong Parameter node (" + Common::toString(ID) + ")"

//Normal messages
#define CMSG_LOAD_FILE              WriteMsg::mlNormal, "Loading file: \"%s\"\n"
#define CMSG_SAVING_MERGED_ASG      WriteMsg::mlNormal, "Saving merged ASG file: \"%s\"\n"
#define CMSG_SAVING_FILTER_FILE     WriteMsg::mlNormal, "Saving filter file: \"%s\"\n"
#define CMSG_SAVING_MERGED_JML      WriteMsg::mlNormal, "Saving merged JML file: \"%s\"\n"
#define CMSG_LOAD_HEADER            WriteMsg::mlNormal, "Loading ASG header: \"%s\"\n"
#define CMSG_SKIP_DUPLICATE         WriteMsg::mlNormal, "Skipping duplicated ASG \"%s\" (timestamp: \"%s\", previous ASG: \"%s\")\n"
#define CMSG_SAVING_NEW_LIST        WriteMsg::mlNormal, "Saving new list file: \"%s\"\n"

//WARNING messages
#define CMSG_CANNOT_OPEN_FILE       WriteMsg::mlWarning, "Warning: Cannot open file: \"%s\"\n"

//ERROR messages
#define CMSG_CANNOT_OPEN_FLTP       WriteMsg::mlError, "Error: Cannot open fltp file (\"%s\")\n"
#define CMSG_NO_INPUT_FILES         WriteMsg::mlError, "Error: No input files."
#define CMSG_NO_INPUT_LOADED        WriteMsg::mlError, "Error: No files have been successfully loaded\n"
#define CMSG_MISSING_TIMESTAMP      WriteMsg::mlError, "Error: No \"TimeStamp\" data found in header: \"%s\"\n"
#define CMSG_NO_OUTPUT_FILE         WriteMsg::mlError, "Error: No output file has been set."
#define CMSG_WRONG_NODE_AT_LINKING_EDGES    WriteMsg::mlError, "Error: Wrong edge %s node (id:%u, kind:%s, expected:%s) at method %s()"

#endif
