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

#ifndef _CLANGSUPPORT_MESSAGES_H_
#define _CLANGSUPPORT_MESSAGES_H_

#define CMSG_DIFFERENT_NUMBER_OF_VISITED_NODES  common::WriteMsg::mlDebug, "Debug: Different number of nodes were visited during the preorder and postorder visit! (Pre:%lu Post:%lu)\n"
#define CMSG_MISSING_NODE_FORM_POSTORDER        common::WriteMsg::mlDebug, "Debug: Missing node from postorder list: %p (0x%08X) "

#define CMSG_EX_MERGE_FAILED                    "Failed to merge the preorder and postorder list!"
#define CMSG_FAILED_TO_LOAD_FILTER_FILE         common::WriteMsg::mlWarning, "Warning: Failed to load filter file: %s\n"



#endif
