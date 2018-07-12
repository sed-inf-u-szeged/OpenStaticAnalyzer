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

#ifndef _GRAPHMERGE_MESSAGES_H
#define _GRAPHMERGE_MESSAGES_H

//main.cpp messages
#define CMSG_NO_INPUT_FILE          common::WriteMsg::mlError,    "Error: No input file\n"
#define CMSG_NO_OUTPUT_FILE         common::WriteMsg::mlError,    "Error: No output file was specified\n"
#define CMSG_LOAD_FILE              common::WriteMsg::mlNormal,   "Loading: %s\n"
#define CMSG_MERGE_FILE             common::WriteMsg::mlNormal,   "Merging: %s\n"
#define CMSG_SAVE_FILE              common::WriteMsg::mlNormal,   "Saving: %s\n"
#define CMSG_MISSING_POSITION_ATTR  common::WriteMsg::mlNormal,   "Missing position attribute from node: %s\n"
#define CMSG_MISSING_LONGNAME_ATTR  common::WriteMsg::mlNormal,   "Missing longname attribute from node: %s\n"
#define CMSG_MISSING_NAME_ATTR      common::WriteMsg::mlNormal,   "Missing name attribute from node: %s\n"

#endif
