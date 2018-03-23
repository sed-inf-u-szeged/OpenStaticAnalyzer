/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#ifndef _CPP_EXT_M_H_
#define _CPP_EXT_M_H_

#define  CMSG_THE_NODE_LOADED common::WriteMsg::mlDDDebug,"The %d node loaded(%s) \n"
#define  CMSG_THE_NODE_HAVE_BEEN_DESTROYED common::WriteMsg::mlDDDebug, "The node %u have been destroyed.\n"
#define  CMSG_SELECTOR_FUNCTION_IS_CHANGED common::WriteMsg::mlDebug,"Selector function is changed \n"
#define  CMSG_NODE_CREATED_THE_MIRROR_OF common::WriteMsg::mlDDDDebug,"The %d node created the mirror of %d node in the src.\n"
#define  CMSG_NODE_PARENT_IS common::WriteMsg::mlDDDDebug,"The %d node parent is %d node in the src.\n"
#define  CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE common::WriteMsg::mlDebug,"The pre order has touched a node twice. (id %d type %s)\n"
#define  CMSG_HAS_ALREADY_PARENT_THE_PARENT_WAS common::WriteMsg::mlDDDebug," The %d (%s) has already parent. The parent was %d (%s). The new parent is %d (%s) \n "
#define  CMSG_SHOW_HEX_VALUE common::WriteMsg::mlDDDebug, " [%X] "
#define  CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN common::WriteMsg::mlDDDebug, "Get the node hash of %u node ["
#define  CMSG_GET_THE_NODE_HASH_OF_NODE_END common::WriteMsg::mlDDDebug, " =(%X) ] \n"
#define  CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP common::WriteMsg::mlDDDebug, "The hash generator found circle ] \n"
#define  CMSG_REMOVE_FORWARD_EDGE_FORM common::WriteMsg::mlDDDebug, "remove forward edge form %u to %u \n"

#define CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST "You must give a factory at first."
#define CMSG_EX_DON_T_HAVE_ANY_VISITOR "Don't have any visitor."
#define CMSG_EX_MISSING_FILE_TYPE_INFORMATION "Missing file type information."
#define CMSG_EX_WRONG_FILE_TYPE_INFORMATION "Wrong file type information."
#define CMSG_EX_MISSING_API_VERSION_INFORMATION "Missing API version information."
#define CMSG_EX_WRONG_API_VERSION(APVER_REQ, APVER_FOUND) "Wrong API version (" + APVER_REQ + " required, " + APVER_FOUND + " found)."
#define CMSG_EX_MISSING_BINARY_VERSION_INFORMATION "Missing binary version information."
#define CMSG_EX_WRONG_BINARY_VERSION(BINVER_REQ, BINVER_FOUND) "Wrong binary version (" + BINVER_REQ + " required, " + BINVER_FOUND + " found)."
#define CMSG_EX_INVALID_ASSOCIATION_CLASS_TYPE(TYPE) "Invalid association class type (" + TYPE + ")."
#define CMSG_EX_INVALID_NODE_ID(ID) "Invalid NodeId (" + Common::toString(ID) + ")"
#define CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST "You must enable the reverse edge first"
#define CMSG_EX_THE_NODE_DOES_NOT_EXISTS "The node does not exists"
#define CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST "Next element does not exist"
#define CMSG_EX_THE_LOADED_FILTER_DOES_NOT_MATCH_TO_THE_CURRENT  "The loaded filter does not match to the current ASG"
#define CMSG_EX_INVALID_NODE_KIND "Invalid node kind"
#define CMSG_EX_INVALID_EDGE_KIND "Invalid edge kind"
#define CMSG_EX_THE_ITERATOR_IS_INVALID "The iterator is invalid."
#define CMSG_EX_CAN_T_SET_ASSOCIATION_EDGE(EDGEKIND) "Can't set association edge by this method (edgeKind: " + Common::toString( EDGEKIND ) + ")"
#define CMSG_EX_THE_NODE_IS_NULL "The node is null"
#define CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH "The factory of nodes does not match"
#define CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST "The end point of the edge does not exist."
#define CMSG_EX_CAN_T_SET_EDGE_TO_NULL "Can't set edge to null (If you want it call the remove function)"
#define CMSG_EX_THE_EDGE_IS_NULL "The edge is null"
#define CMSG_EX_IN_CASE_THE_NODE_HAS_MORE_RANGES "In case the node has more ranges you must not use this method!"
#define CMSG_EX_THE_NODE_HAS_THE_SAME_ATTRIBUTES(ID,ATTRIBUTENAME) "The node id" +Common::toString(ID) + " has the same attributes (" + ATTRIBUTENAME + ")."
#define CMSG_EX_THE_EDGE_HAVE_THE_SAME_STRING_REPRESENTATION(ID_1,ID_2,ID_3,STR)  "The %s edges id" + Common::toString(ID_1) + " and id" + Common::toString(ID_2) + " of node id" + Common::toString(ID_3) + " have the same string representation (" + STR + ")."
#define CMSG_EX_NO_REVERSE_EDGE_INFORMATION_FOR(ID) "No reverse edge information for NodeId ("+ Common::toString(ID) + ")"
#define CMSG_EX_WRONG_NODE_KIND_FOR "Wrong node kind for '" #name "'."
#define CMSG_EX_NUMBER_IS_OUT_OF_RANGE(NUMBER) "number (" + NUMBER + ") is out of range [0x0, 0xFFFFFF]"
#define CMSG_EX_UNTIL_NO_STRTABLE_IS_SET_THE_SETPATH "Until no strTable is set the setPath() can not be used!"
#define CMSG_EX_NEITHER_NEXT_NOR_PREVIOUS_HAVE_BEEN_CALLED "Neither next() nor previous() have been called, or remove() or add() have been called after the last call to next() or previous()."
#define CMSG_EX_THE_ITERATION_HAS_NOT_NEXT_ELEMENT "The iteration has not next element"
#define CMSG_EX_THE_ITERATION_HAS_NOT_PREVIOUS_ELEMENT "The iteration has not previous element"
#define CMSG_EX_HEADER_DATA_ALREADY_LOADED(type) "The ASG file already contains a " + common::toString(type) + " type header data. You can not give another of this type."


// AlgorithmCFG

    // common debug
#define CMSG_CPP_PRINT_DEBUG_D                  common::WriteMsg::mlDebug, "%s"
#define CMSG_CPP_PRINT_DEBUG_DD                 common::WriteMsg::mlDDebug, "%s"
#define CMSG_CPP_PRINT_DEBUG_DDD                common::WriteMsg::mlDDDebug, "%s"
#define CMSG_CPP_PRINT_DEBUG_DDDD               common::WriteMsg::mlDDDDebug, "%s"
    // edge handling
#define CMSG_CPP_INSERT_EDGE                    common::WriteMsg::mlDDDebug, "insert edge from %d to %d (%s, %s, %s)\n"
#define CMSG_CPP_ERASE_EDGE                     common::WriteMsg::mlDDDebug, "erase edge from %d to %d\n"
#define CMSG_CPP_ERASE_SUCC_EDGES               common::WriteMsg::mlDDDebug, "erase succeeding edges of %d\n"
    // exceptions
#define CMSG_CPP_THROW_NODE                     common::WriteMsg::mlDDDebug, "  throw node id: %d\n"
#define CMSG_CPP_THROW_KEEP_SEARCHING           common::WriteMsg::mlDDDebug, "  [%d] still has no thrown type, keep on searching!\n"
#define CMSG_CPP_THROW_NO_EXCEPTION             common::WriteMsg::mlDDDebug, "  ThrowExpression [%d]: no exception has been thrown!\n"
#define CMSG_CPP_THROW_NO_INCOMING_EDGE         common::WriteMsg::mlDDDebug, "  ThrowExpression [%d]: no incoming edge of the containing handler!\n"
#define CMSG_CPP_THROW_NO_HANDLER_FOUND         common::WriteMsg::mlDDDebug, "  ThrowExpression [%d]: we reached the top and have found no handler!\n"
    // basic block building
#define CMSG_CPP_BUILD_BB                       common::WriteMsg::mlDDebug, "starting to build basic blocks for ICFG %d\n"
#define CMSG_CPP_LEADER_ADD                     common::WriteMsg::mlDDebug, "    leader added: %d\n"
#define CMSG_CPP_EXTRA_LEADER_ADD               common::WriteMsg::mlDDebug, "    node %d is added to extra leaders\n"
#define CMSG_CPP_LEADER_ADD_TO_BB               common::WriteMsg::mlDDebug, "    node(leader) %d is added to bb %d\n"
#define CMSG_CPP_LEADER                         common::WriteMsg::mlDDebug, "    leader: %d\n"
#define CMSG_CPP_POSSIBLE_LEADER                common::WriteMsg::mlDDebug, "    possible leader: %d\n"
#define CMSG_CPP_ADD_CALL_EDGE_TO_ENTRY         common::WriteMsg::mlDDebug, "    call edge from bb %d to the ENTRY of function %d\n"
#define CMSG_CPP_ADD_CALL_EDGE_FROM_EXIT        common::WriteMsg::mlDDebug, "    call edge from the EXIT of function %d to bb %d\n"
#define CMSG_CPP_ADD_CONTROL_EDGE               common::WriteMsg::mlDDebug, "    control edge from bb %d to bb %d\n"
#define CMSG_CPP_ADD_CONTROL_EDGE_FROM_ENTRY    common::WriteMsg::mlDDebug, "    control edge from bb ENTRY to bb %d\n"
#define CMSG_CPP_ADD_CONTROL_EDGE_TO_EXIT       common::WriteMsg::mlDDebug, "    control edge from bb %d to bb EXIT\n"
    // destructors
#define CMSG_CPP_DESTRUCT_AT_END_OF_FILE        common::WriteMsg::mlDDDebug, "  destruct at end of file\n"
#define CMSG_CPP_DESTRUCT_AT_END_OF_BLOCK       common::WriteMsg::mlDDDebug, "  destruct at end of block\n"
#define CMSG_CPP_DESTRUCT_AT_RETURN             common::WriteMsg::mlDDDebug, "  destruct at return\n"
#define CMSG_CPP_DESTRUCT_AT_GOTO               common::WriteMsg::mlDDDebug, "  destruct at goto\n"
#define CMSG_CPP_DESTRUCT_AT_THROW              common::WriteMsg::mlDDDebug, "  destruct at throw\n"
#define CMSG_CPP_DESTRUCT_AT_END_OF_TRY_BLOCK   common::WriteMsg::mlDDDebug, "  destruct at end of try block\n"
#define CMSG_CPP_DESTRUCT_TEMP_OBJECT           common::WriteMsg::mlDDDebug, "  destruct at end of TemporaryInitExpression\n"
#define CMSG_CPP_DESTRUCT_LOCAL_STATIC_OBJECTS  common::WriteMsg::mlDDDebug, "  destruct local static objects\n"
#define CMSG_CPP_DESTRUCT_GLOBAL_OBJECTS        common::WriteMsg::mlDDDebug, "  destruct global objects\n"
#define CMSG_CPP_DESTRUCT_NODE                  common::WriteMsg::mlDDDebug, "    destruct node (%d)\n"
#define CMSG_CPP_NO_DESTRUCTOR_FOUND            common::WriteMsg::mlDDDebug, "    no destructor function\n"
#define CMSG_CPP_CREATE_NEW_ASG_NODE            common::WriteMsg::mlDDDebug, "    node (%d) created, cfg factory new size is %d\n"
    // icfg-s
#define CMSG_CPP_CREATE_SYSTEM_ICFG             common::WriteMsg::mlDebug, "  create systemICFG\n"
#define CMSG_CPP_CREATE_GLOBAL_START_ICFG       common::WriteMsg::mlDebug, "    create globalStartICFG\n"
#define CMSG_CPP_CONNECT_TO_MAIN                common::WriteMsg::mlDebug, "    connect to main's ICFG\n"
#define CMSG_CPP_CREATE_GLOBAL_END_ICFG         common::WriteMsg::mlDebug, "    create globalEndICFG\n"
    // visitors
#define CMSG_CPP_VISIT_FILE_SCOPE               common::WriteMsg::mlDebug, "\n\nvisit FileScope (id: %d)"
#define CMSG_CPP_VISITEND_FILE_SCOPE            common::WriteMsg::mlDebug, "\n\nvisitEnd FileScope (id: %d)\n"
#define CMSG_CPP_VISIT_FUNCTION_SCOPE           common::WriteMsg::mlDebug, "visit FunctionScope (id: %d) of Function (id: %d, name: %s, location: %s)\n"
#define CMSG_CPP_VISITEND_FUNCTION_SCOPE        common::WriteMsg::mlDebug, "visitEnd FunctionScope (id: %d) of Function (id: %d, name: %s, location: %s)\n"
#define CMSG_CPP_VISIT_BLOCK                    common::WriteMsg::mlDebug, "visit Block (id: %d)\n"
#define CMSG_CPP_VISITEND_BLOCK                 common::WriteMsg::mlDebug, "visitEnd Block (id: %d)\n"
    // labels
#define CMSG_CPP_ORIG_JUMP_LOCATION             common::WriteMsg::mlDDDDebug, "  label (original jump location): %d\n"
#define CMSG_CPP_NEW_JUMP_LOCATION              common::WriteMsg::mlDDDDebug, "  new jump location: %d\n"
#define CMSG_CPP_PROCESS_LABEL_STMNTS           common::WriteMsg::mlDDDDebug, "  post process to arrange the label statements (modify the jump locations)\n"
    // other
#define CMSG_CPP_GATHER_FUNC_CALLS_START        common::WriteMsg::mlDebug, "gather the function calls for functionScope %d ..."
#define CMSG_CPP_GATHER_FUNC_CALLS_END          common::WriteMsg::mlDebug, "  done!\n"
#define CMSG_CPP_SUSPICIOUS_DI                  common::WriteMsg::mlDebug,"  suspicious case: why has DI %d been generated?\n"
    // error
#define CMSG_CPP_PRINT_ERROR                    common::WriteMsg::mlError, "%s"
#define CMSG_CPP_NODE_NOT_FOUND                 common::WriteMsg::mlError, "Node id %d is not found!\n"
#define CMSG_CPP_UNHANDLED_REDIRECTING_EDGE     common::WriteMsg::mlError, "Unhandled case when redirecting the in edges: [%d -> %d]\n"
#define CMSG_CPP_NO_FUNCTION_FOUND              common::WriteMsg::mlError, "    No function belongs to node %d\n"
#define CMSG_CPP_NO_ASSOC_FUNCTION              common::WriteMsg::mlError, "No associated Function for FunctionScope: \n"
#define CMSG_CPP_THROW_POINTS_TO_NONHANDLER     common::WriteMsg::mlError, "  The throw node points to a non-handler!\n"
#define CMSG_CPP_GET_PARENT_LIFETIME_ERROR      common::WriteMsg::mlError, "    destructAtEndOfTryBlock: getParentLifetime() error\n"
#define CMSG_CPP_GET_LIFETIME_ERROR             common::WriteMsg::mlError, "    destructAtEndOfTryBlock: getLifetime() error\n"
    // basic block building
#define CMSG_CPP_BB_REM_HANDLERS                common::WriteMsg::mlDDebug, "  step 0.1. remove the handler nodes and set the new leaders instead of them\n"
#define CMSG_CPP_BB_REM_THROWS                  common::WriteMsg::mlDDebug, "  step 0.2. remove the throw nodes\n"
#define CMSG_CPP_BB_PHANTOM_NODES               common::WriteMsg::mlDDebug, "  step 0.3 handle the phantom entry and exit(s)\n"
#define CMSG_CPP_BB_CHECK_OUT_EDGES             common::WriteMsg::mlDDebug, "  step 1. collect the leaders by checking the outgoing egdes\n"
#define CMSG_CPP_BB_CHECK_IN_EDGES              common::WriteMsg::mlDDebug, "  step 2. collect the leaders by checking the ingoing egdes\n"
#define CMSG_CPP_BB_ADD_LABELS_TO_LEADERS       common::WriteMsg::mlDDebug, "  step 3. put the 'label nodes' into the leaders\n"
#define CMSG_CPP_BB_ADD_DESTRUCTORS_TO_LEADERS  common::WriteMsg::mlDDebug, "  step 3.5. put the destructors' CallExpressions into the leaders\n"
#define CMSG_CPP_BB_EXTRA_LEADERS               common::WriteMsg::mlDDebug, "  step 3.6. define extra leader nodes because of the static init edges\n"
#define CMSG_CPP_BB_CREATE_BBS                  common::WriteMsg::mlDDebug, "  step 4. create the basic blocks\n"
#define CMSG_CPP_BB_INSERT_CALL_EDGES           common::WriteMsg::mlDDebug, "  step 5. insert the call edges between the blocks\n"
#define CMSG_CPP_BB_INSERT_CONTROL_EDGES        common::WriteMsg::mlDDebug, "  step 6. insert the control edges between the blocks\n"
#define CMSG_CPP_BB_EDGE_FROM_ENTRY_TO_EXIT     common::WriteMsg::mlDDebug, "    control edge from bb ENTRY to bb EXIT\n"
#define CMSG_CPP_BB_REM_UNNECESSARY_NODES       common::WriteMsg::mlDDebug, "  step 7. remove unnecessary nodes\n"
    // dump nodeinfo
#define CMSG_CPP_DUMP_NODEINFO                  common::WriteMsg::mlNormal, "nodeId: %d\n  edgeLabel: %s\n  isStaticInit: %s\n  isLeader: %s\n"
    // dump control edges
#define CMSG_CPP_DUMP_CONTROL_EDGES_1           common::WriteMsg::mlDebug, "%s:\n"
#define CMSG_CPP_DUMP_CONTROL_EDGES_2           common::WriteMsg::mlDebug, "  %d  ["
#define CMSG_CPP_DUMP_CONTROL_EDGES_3           common::WriteMsg::mlDebug, "(%d, %s, %s, %s)"
#define CMSG_CPP_DUMP_CONTROL_EDGES_4           common::WriteMsg::mlDebug, "]\n"
#define CMSG_CPP_DUMP_CONTROL_EDGES_5           common::WriteMsg::mlDebug, "\n"
    // dump call edges
#define CMSG_CPP_DUMP_CALL_EDGES_1              common::WriteMsg::mlDebug, "    called function nodes: "
#define CMSG_CPP_DUMP_CALL_EDGES_2              common::WriteMsg::mlDebug, "%d, "
#define CMSG_CPP_DUMP_CALL_EDGES_3              common::WriteMsg::mlDebug, "\n    caller nodes: "
#define CMSG_CPP_DUMP_CALL_EDGES_4              common::WriteMsg::mlDebug, "%d, "
#define CMSG_CPP_DUMP_CALL_EDGES_5              common::WriteMsg::mlDebug, "\n"
    // dump dynamic inits
#define CMSG_CPP_DUMP_DYNAMIC_INITS_1           common::WriteMsg::mlDebug, "    dis content: "
#define CMSG_CPP_DUMP_DYNAMIC_INITS_2           common::WriteMsg::mlDebug, " "
#define CMSG_CPP_DUMP_DYNAMIC_INITS_3           common::WriteMsg::mlDebug, "\n"

// AlgorithmCG

#define CMSG_CPP_SEARCH_ADDRESSINFO             common::WriteMsg::mlDebug, "    search addressInfo for node %d\n"
// az alg fejlesztes alatt van

// VisitorDU

#define CMSG_CPP_ADDRESSINFO_ALLOC_ERROR        "Cannot allocate memory for AddressInfo"
#define CMSG_CPP_OPERATIONINFO_ALLOC_ERROR      "Cannot allocate memory for OperationInfo"
#define CMSG_CPP_ASG_BUILD_ERROR                "ASG build error"

// VisitorOfSymbol

#define CMSG_CPP_DOUBLE_SYMBOL                  common::WriteMsg::mlWarning, "Double symbol in one file %s with %u ID\n"
#define CMSG_CPP_MISSING_TEMPLATE               common::WriteMsg::mlDDebug, "Missing associatedTemplate edge for %u\n"
#define CMSG_CPP_MISSING_PARENT                 common::WriteMsg::mlError, "Missing parent for %u\n"
#define CMSG_CPP_MISSING_ATYPE_EDGE             common::WriteMsg::mlError, "Missing associatedType edge for %u\n"
#define CMSG_CPP_MISSING_ATEMPLATE_EDGE         common::WriteMsg::mlError, "Missing AssociatedTemplate edge for %u\n"

#endif