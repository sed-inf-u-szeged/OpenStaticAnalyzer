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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  StringConversion::StringConversion(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_hasExpressionList(0)
  {
  }

  StringConversion::~StringConversion() {
  }

  void StringConversion::prepareDelete(bool tryOnVirtualParent){
    removeExpressionList();
    expression::Expression::prepareDelete(false);
  }

  NodeKind StringConversion::getNodeKind() const {
    return ndkStringConversion;
  }

  expression::ExpressionList* StringConversion::getExpressionList() const {
    expression::ExpressionList *_node = NULL;
    if (m_hasExpressionList != 0)
      _node = dynamic_cast<expression::ExpressionList*>(factory->getPointer(m_hasExpressionList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool StringConversion::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkStringConversion_HasExpressionList:
        setExpressionList(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool StringConversion::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkStringConversion_HasExpressionList:
        removeExpressionList();
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void StringConversion::setExpressionList(NodeId _id) {
    expression::ExpressionList *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ExpressionList*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasExpressionList) {
        removeParentEdge(m_hasExpressionList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpressionList, m_id, edkStringConversion_HasExpressionList);
      }
      m_hasExpressionList = _node->getId();
      if (m_hasExpressionList != 0)
        setParentEdge(factory->getPointer(m_hasExpressionList), edkStringConversion_HasExpressionList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpressionList, this->getId(), edkStringConversion_HasExpressionList);
    } else {
      if (m_hasExpressionList) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void StringConversion::setExpressionList(expression::ExpressionList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionList(_node->getId());
  }

  void StringConversion::removeExpressionList() {
      if (m_hasExpressionList) {
        removeParentEdge(m_hasExpressionList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpressionList, m_id, edkStringConversion_HasExpressionList);
      }
      m_hasExpressionList = 0;
  }

  void StringConversion::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void StringConversion::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double StringConversion::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void StringConversion::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType StringConversion::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::StringConversion", strlen("expression::StringConversion"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void StringConversion::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasExpressionList);

  }

  void StringConversion::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    m_hasExpressionList =  binIo.readUInt4();
    if (m_hasExpressionList != 0)
      setParentEdge(factory->getPointer(m_hasExpressionList),edkStringConversion_HasExpressionList);

  }


}


}}}
