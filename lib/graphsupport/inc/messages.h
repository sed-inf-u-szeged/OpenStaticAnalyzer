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

#ifndef _GRAPHSUPPORT_MESSAGES_H_
#define _GRAPHSUPPORT_MESSAGES_H_

#define CMSG_EX_GRAPH_NOT_EXIST                       ": Graph does not exist"
#define CMSG_EX_FOUND_MORE_METRIC_ATTRIBUTE( ATTRNAME, UID) "Found 2 or more " + ATTRNAME + " metric attributes in " + UID + " node"
#define CMSG_EX_WRONG_ATTRIBUTE_TYPE                  "Wrong attribute type!"
#define CMSG_EX_UNHANDLED_ASG_TYPE(ASG)               "Unhandled ASG type (" + ASG + ")"
#define CMSG_EX_INVALID_PRIORITY_VALUE(VAL)           "Invalid priority value:" + VAL


#define CMSG_STAT_HEADER_IMPACTED                     "Impacted"
#define CMSG_STAT_HEADER_NAME                         "Name"
#define CMSG_STAT_HEADER_PATH                         "Path"
#define CMSG_STAT_HEADER_LINE                         "Line"
#define CMSG_STAT_HEADER_DESCRIPTION                  "Description"

#define CMSG_SARIF_OUT_OF_DATE(UID, ATYPE, NAME, CONTEXT)   "Tried to get '" + NAME + "' attribute with conxtext of '" + CONTEXT + "' and a type of '" + ATYPE + "' in " + UID + " node|Attribute"

#endif
