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

#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#define  CMSG_THE_NODE_LOADED                           common::WriteMsg::mlDDDebug,  "DDDebug: The %d node is loaded(%s)\n"
#define  CMSG_THE_NODE_HAVE_BEEN_DESTROYED              common::WriteMsg::mlDDDebug,  "DDDebug: The node %u has been destroyed\n"
#define  CMSG_SELECTOR_FUNCTION_IS_CHANGED              common::WriteMsg::mlDebug,    "Debug: Selector function is changed\n"
#define  CMSG_NODE_CREATED_THE_MIRROR_OF                common::WriteMsg::mlDDDDebug, "DDDDebug: The %d node created the mirror of %d node in the src\n"
#define  CMSG_NODE_PARENT_IS                            common::WriteMsg::mlDDDDebug, "DDDDebug: The parent of the %d node is %d node in the src\n"
#define  CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE    common::WriteMsg::mlDebug,    "Debug: The pre order has touched a node twice (id: %d, type: %s)\n"
#define  CMSG_HAS_ALREADY_PARENT_THE_PARENT_WAS         common::WriteMsg::mlDDDebug,  "DDDebug: The %d (%s) already has a parent. The parent was %d (%s). The new parent is %d (%s)\n"
#define  CMSG_SHOW_HEX_VALUE                            common::WriteMsg::mlDDDebug,  " [%X] "
#define  CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN           common::WriteMsg::mlDDDebug,  "DDDebug: Get the node hash of %u node ["
#define  CMSG_GET_THE_NODE_HASH_OF_NODE_END             common::WriteMsg::mlDDDebug,  " =(%X) ] \n"
#define  CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP            common::WriteMsg::mlDDDebug,  "The hash generator found a circle ] \n"
#define  CMSG_REMOVE_FORWARD_EDGE_FORM                  common::WriteMsg::mlDDDebug,  "DDDebug: Removing forward edge (form: %u, to: %u)\n"
#define  CMSG_SORT_DUPLICATED_EDGE_NAMES_AT_NODE        common::WriteMsg::mlWarning,  "Warning: Duplicated string representation is found while sorting the '%s' edges of node %u (%s): %s\n"
#define  CMSG_SORT_DUPLICATED_EDGE_DATA                 common::WriteMsg::mlWarning,  "Warning:   End point: %u (%s)\n"

#define CMSG_CANNOT_OPEN_FILE                           common::WriteMsg::mlWarning, "Warning: Cannot open file: \"%s\"\n"
#define CMSG_STAGE_JSML_DUMP                            common::WriteMsg::mlNormal,  "Creating jsml dump ... "
#define CMSG_STAGE_DONE                                 common::WriteMsg::mlNormal,  "done\n"

#define CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST        "A factory must be given first"
#define CMSG_EX_DON_T_HAVE_ANY_VISITOR                  "Do not have any visitor"
#define CMSG_EX_MISSING_FILE_TYPE_INFORMATION           "Missing file type information"
#define CMSG_EX_WRONG_FILE_TYPE_INFORMATION             "Wrong file type information"
#define CMSG_EX_MISSING_API_VERSION_INFORMATION         "Missing API version information"
#define CMSG_EX_WRONG_API_VERSION(APVER_REQ, APVER_FOUND) "Wrong API version (" + APVER_REQ + " required, " + APVER_FOUND + " found)"
#define CMSG_EX_MISSING_BINARY_VERSION_INFORMATION      "Missing binary version information"
#define CMSG_EX_WRONG_BINARY_VERSION(BINVER_REQ, BINVER_FOUND) "Wrong binary version (" + BINVER_REQ + " required, " + BINVER_FOUND + " found)"
#define CMSG_EX_INVALID_ASSOCIATION_CLASS_TYPE(TYPE)    "Invalid association class type (" + TYPE + ")"
#define CMSG_EX_INVALID_NODE_ID(ID)                     "Invalid NodeId (" + Common::toString(ID) + ")"
#define CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST  "The reverse edge must be enabled first"
#define CMSG_EX_THE_NODE_DOES_NOT_EXISTS                "The node does not exist"
#define CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST             "Next element does not exist"
#define CMSG_EX_THE_LOADED_FILTER_DOES_NOT_MATCH_TO_THE_CURRENT "The loaded filter does not match to the current ASG"
#define CMSG_EX_INVALID_NODE_KIND_VALUE(NODEKIND)       "Invalid node kind (" + Common::toString(NODEKIND) + ")"
#define CMSG_EX_INVALID_NODE_KIND                       "Invalid node kind"
#define CMSG_EX_INVALID_EDGE_KIND                       "Invalid edge kind"
#define CMSG_EX_THE_ITERATOR_IS_INVALID                 "The iterator is invalid"
#define CMSG_EX_CAN_T_SET_ASSOCIATION_EDGE(EDGEKIND)    "Cannot set the association edge by this method (edgeKind: " + Common::toString( EDGEKIND ) + ")"
#define CMSG_EX_THE_NODE_IS_NULL                        "The node is null"
#define CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH     "The factory of the nodes does not match"
#define CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST "The end point of the edge does not exist"
#define CMSG_EX_CAN_T_SET_EDGE_TO_NULL                  "Cannot set the edge to null (if it is necessary the remove function should be called)"
#define CMSG_EX_THE_EDGE_IS_NULL                        "The edge is null"
#define CMSG_EX_IN_CASE_THE_NODE_HAS_MORE_RANGES        "In case the node has more ranges you must not use this method"
#define CMSG_EX_THE_NODE_HAS_THE_SAME_ATTRIBUTES(ID, ATTRIBUTENAME) "The node id" + Common::toString(ID) + " has the same attributes (" + ATTRIBUTENAME + ")"
#define CMSG_EX_NO_REVERSE_EDGE_INFORMATION_FOR(ID)     "No reverse edge information for NodeId ("+ Common::toString(ID) + ")"
#define CMSG_EX_WRONG_NODE_KIND_FOR                     "Wrong node kind for '" #name "'"
#define CMSG_EX_UNTIL_NO_STRTABLE_IS_SET_THE_SETPATH    "The setPath() can not be used until setting strTable"
#define CMSG_EX_NEITHER_NEXT_NOR_PREVIOUS_HAVE_BEEN_CALLED "Neither next() nor previous() have been called, or remove() or add() have been called after the last call to next() or previous()"
#define CMSG_EX_THE_ITERATION_HAS_NOT_NEXT_ELEMENT      "The iteration does not have next element"
#define CMSG_EX_THE_ITERATION_HAS_NOT_PREVIOUS_ELEMENT  "The iteration does not have previous element"
#define CMSG_EX_HEADER_DATA_ALREADY_LOADED(type) "The ASG file already contains a " + common::toString(type) + " type header data. You can not give another of this type."

#endif
