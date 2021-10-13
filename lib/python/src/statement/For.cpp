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

namespace statement { 
  For::For(NodeId _id, Factory *_factory) :
    Iteration(_id, _factory),
    m_isAsync(false),
    m_hasExpressionList(0),
    m_hasTargetList(0)
  {
  }

  For::~For() {
  }

  void For::prepareDelete(bool tryOnVirtualParent){
    removeExpressionList();
    removeTargetList();
    statement::Iteration::prepareDelete(false);
  }

  NodeKind For::getNodeKind() const {
    return ndkFor;
  }

  bool For::getIsAsync() const {
    return m_isAsync;
  }

  void For::setIsAsync(bool _isAsync) {
    m_isAsync = _isAsync;
  }

  expression::ExpressionList* For::getExpressionList() const {
    expression::ExpressionList *_node = NULL;
    if (m_hasExpressionList != 0)
      _node = dynamic_cast<expression::ExpressionList*>(factory->getPointer(m_hasExpressionList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::TargetList* For::getTargetList() const {
    statement::TargetList *_node = NULL;
    if (m_hasTargetList != 0)
      _node = dynamic_cast<statement::TargetList*>(factory->getPointer(m_hasTargetList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool For::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFor_HasExpressionList:
        setExpressionList(edgeEnd);
        return true;
      case edkFor_HasTargetList:
        setTargetList(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::Iteration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool For::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFor_HasExpressionList:
        removeExpressionList();
        return true;
      case edkFor_HasTargetList:
        removeTargetList();
        return true;
      default:
        break;
    }
    if (statement::Iteration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void For::setExpressionList(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasExpressionList, m_id, edkFor_HasExpressionList);
      }
      m_hasExpressionList = _node->getId();
      if (m_hasExpressionList != 0)
        setParentEdge(factory->getPointer(m_hasExpressionList), edkFor_HasExpressionList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpressionList, this->getId(), edkFor_HasExpressionList);
    } else {
      if (m_hasExpressionList) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void For::setExpressionList(expression::ExpressionList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionList(_node->getId());
  }

  void For::removeExpressionList() {
      if (m_hasExpressionList) {
        removeParentEdge(m_hasExpressionList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpressionList, m_id, edkFor_HasExpressionList);
      }
      m_hasExpressionList = 0;
  }

  void For::setTargetList(NodeId _id) {
    statement::TargetList *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::TargetList*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasTargetList) {
        removeParentEdge(m_hasTargetList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTargetList, m_id, edkFor_HasTargetList);
      }
      m_hasTargetList = _node->getId();
      if (m_hasTargetList != 0)
        setParentEdge(factory->getPointer(m_hasTargetList), edkFor_HasTargetList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTargetList, this->getId(), edkFor_HasTargetList);
    } else {
      if (m_hasTargetList) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void For::setTargetList(statement::TargetList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTargetList(_node->getId());
  }

  void For::removeTargetList() {
      if (m_hasTargetList) {
        removeParentEdge(m_hasTargetList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTargetList, m_id, edkFor_HasTargetList);
      }
      m_hasTargetList = 0;
  }

  void For::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void For::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double For::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const For& node = dynamic_cast<const For&>(base);
      double matchAttrs = 0;
      if(node.getIsAsync() == getIsAsync()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void For::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType For::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::For", strlen("statement::For"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void For::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Iteration::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isAsync) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasExpressionList);
    binIo.writeUInt4(m_hasTargetList);

  }

  void For::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Iteration::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isAsync = boolValues & 1;
    boolValues >>= 1;

    m_hasExpressionList =  binIo.readUInt4();
    if (m_hasExpressionList != 0)
      setParentEdge(factory->getPointer(m_hasExpressionList),edkFor_HasExpressionList);

    m_hasTargetList =  binIo.readUInt4();
    if (m_hasTargetList != 0)
      setParentEdge(factory->getPointer(m_hasTargetList),edkFor_HasTargetList);

  }


}


}}}
