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

#ifndef _GRAPH_PINC_M_H_
#define _GRAPH_PINC_M_H_

#define CMSG_EX_ATTRIBUTE_NOT_EXIST                 " Attribute does not exist"
#define CMSG_EX_EDGEITERATOR_NOT_EXIST              " EdgeIterator does not exist"
#define CMSG_EX_ATTRIBUTEITERATOR_NOT_EXIST         " AttributeIterator does not exist"
#define CMSG_EX_ATTRIBUTEINT_NOT_EXIST              " AttributeInt does not exist"
#define CMSG_EX_ATTRIBUTEFLOAT_NOT_EXIST            " AttributeFloat does not exist"
#define CMSG_EX_ATTRIBUTESTRING_NOT_EXIST           " AttributeString does not exist"
#define CMSG_EX_EDGE_NOT_EXIST                      " Edge does not exist"
#define CMSG_EX_NODE_NOT_EXIST                      " Node does not exist"
#define CMSG_EX_EDGETYPESET_NOT_EXIST               " EdgeTypeSet does not exist"
#define CMSG_EX_GRAPH_NOT_EXIST                     " Graph does not exist"
#define CMSG_EX_NODEITERATOR_NOT_EXIST              " NodeIterator does not exist"
#define CMSG_EX_NODETYPESET_NOT_EXIST               " EdgeTypeSet does not exist"
#define CMSG_EX_INVALID_ATTRIBUTE_NO_NAME           "Invalid attribute does not have name"
#define CMSG_EX_INVALID_ATTRIBUTE_NO_CONTEXT        "Invalid attribute does not have context"
#define CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE          "Invalid attribute does not have value"
#define CMSG_EX_INVALID_NODE_NO_ATTRIBUTE           "Invalid node does not have attribute"
#define CMSG_EX_INVALID_NODE_NO_OUT_EDGES           "Invalid node does not have out edges"
#define CMSG_EX_INVALID_NODE_NO_TYPE                "Invalid node does not have type"
#define CMSG_EX_INVALID_NODE_NO_UID                 "Invalid node does not have UID"
#define CMSG_EX_ATTRIBUTE_ALREADY_EXIST             "Attribute already exists"
#define CMSG_EX_INVALID_ITERATOR                    "The iterator is invalid"
#define CMSG_EX_ERROR_CALL_ORDER                    "Neither next() nor previous() have been called, or remove() or add() have been called after the last call to next() or previous()."
#define CMSG_EX_ITERATOR_NOT_PREVIUS_ELEMENT        "The iteration does not have previous element"
#define CMSG_EX_ITERATOR_NOT_NEXT_ELEMENT           "The iteration does not have next element"
#define CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE    "Cannot delete an attribute of invalidNode"
#define CMSG_EX_NO_ADD_ATTRIBUTE_TO_INVALID_NODE    "Cannot add an attribute to an invalidNode"
#define CMSG_EX_NO_ADD_INVALID_ATTRIBUTE_TO_NODE    "Cannot add invalidAttribute to node"
#define CMSG_EX_NO_ADD_ATTRIBUTE_TO_INVALID_ATTRIBUTE "Cannot add attribute to invalidAttribute"
#define CMSG_EX_NO_ADD_INVALID_ATTRIBUTE_TO_ATTRIBUTE "Cannot add invalidAttribute to attribute"
#define CMSG_EX_CANT_ADD_TYPE(TYPE)                 "Cannot add " + TYPE + " type node"
#define CMSG_EX_NODE_ALREADY_EXIST                  "Node is already exist"
#define CMSG_EX_NODE_ALREADY_EXIST_WITH_ID( UID)    "Node " + UID + " already exist"
#define CMSG_EX_CANT_ADD_DIRECTIONAL( TYPE, SRCTYPE, DSTTYPE) "Cannot add directional " + TYPE + " type edge from " + SRCTYPE + " to " + DSTTYPE + " type node"
#define CMSG_EX_CANT_ADD_REVERSE( TYPE, SRCTYPE, DSTTYPE) "Cannot add reverse " + TYPE + " type edge from " + SRCTYPE + " to " + DSTTYPE + " type node"
#define CMSG_EX_CANT_ADD_BIDIRECTIONAL( TYPE, SRCTYPE, DSTTYPE) "Can't add bidirectional " + TYPE + " type edge from " + SRCTYPE + " to " + DSTTYPE + " type node"
#define CMSG_EX_WRONG_ATTRIBUTE_FOUND               "Wrong attribute found"
#define CMSG_EX_WRONG_ATTRIBUTE_NOT_FOUND           "Attribute not found: "
#define CMSG_EX_WRONG_HEADER_INFORMATION            "Wrong header information (UniqueName missing)"
#define CMSG_EX_WRONG_LINE_LENGTH                   "Line length is not equal to header length"
#define CMSG_EX_UNEXCPECTED_END_OF_LINE             "Unexpected end of file"
#define CMSG_EX_NO_ADD_ATTRIBUTE_TO_INVALID_EDGE    "Cannot add attribute to invalidEdge"
#define CMSG_EX_NO_ADD_INVALID_ATTRIBUTE_TO_EDGE    "Cannot add invalidAttribute to edge"
#define CMSG_EX_CANT_ADD_ATTRIBUTE_TO_EDGE( NAME, DSTTYPE) "Cannot add attribute: " + NAME + " to " + DSTTYPE + " edge"
#define CMSG_EX_CANT_ADD_ATTRIBUTE_TO_NODE( NAME, DSTTYPE) "Cannot add attribute: " + NAME + " to " + DSTTYPE + " node"
#define CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_EDGE    "Cannot delete an attribute of invalidEdge"
#define CMSG_EX_INVALID_EDGE_HASNOT_ATTRIBUTE       "Invalid edge does not have attribute"
#define CMSG_EX_INVALID_EDGE_HASNOT_PAIR            "Invalid edge does not have pair"
#define CMSG_EX_INVALID_EDGE_HASNOT_FROMNODE        "Invalid edge does not have fromNode"
#define CMSG_EX_INVALID_EDGE_HASNOT_TONODE          "Invalid edge does not have toNode"
#define CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE  "Tag has been found outside of the root node"
#define CMSG_EX_WRONG_GROUP_FOUNDED                 "Wrong group found: " 
#define CMSG_EX_WRONG_EDGE_FOUNDED                  "Wrong edge found: " 
#define CMSG_EX_WRONG_NODEGROUP_FOUNDED             "Wrong nodegroup found: "
#define CMSG_EX_WRONG_NODE_FOUNDED                  "Wrong node found: "
#define CMSG_EX_NODEGROUP_DOESNOT_FOUND             "Nodegroup is not found: "
#define CMSG_EX_EDGE_DOESNOT_FOUND                  "Edge is not found: "
#define CMSG_EX_NODE_DOESNOT_FOUND                  "Node is not found: "
#define CMSG_EX_TAG_NO_CAN_RECOGNIZE                "Tag cancot be recongnized: "
#define CMSG_EX_ATTRIBUTEGROUP_DOESNOT_FOUND        "Attributegroup is not found: "
#define CMSG_EX_WRONG_XML_FORMAT                    "Wrong XML format"
#define CMSG_EX_INVALID_ATTRIBUTE_FOUND             "Invalid attribute found"
#define CMSG_EX_UNHANDLED_ATTRIBUTE_TYPE_FOUND      "Unhandled attribute type found"

#endif
