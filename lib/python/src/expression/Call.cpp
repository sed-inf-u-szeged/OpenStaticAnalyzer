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
  Call::Call(NodeId _id, Factory *_factory) :
    Unary(_id, _factory),
    m_hasArgumentList(0),
    m_refersTo(0)
  {
  }

  Call::~Call() {
  }

  void Call::prepareDelete(bool tryOnVirtualParent){
    removeArgumentList();
    removeRefersTo();
    expression::Unary::prepareDelete(false);
  }

  NodeKind Call::getNodeKind() const {
    return ndkCall;
  }

  expression::ArgumentList* Call::getArgumentList() const {
    expression::ArgumentList *_node = NULL;
    if (m_hasArgumentList != 0)
      _node = dynamic_cast<expression::ArgumentList*>(factory->getPointer(m_hasArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::CompoundStatement* Call::getRefersTo() const {
    statement::CompoundStatement *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<statement::CompoundStatement*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Call::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCall_HasArgumentList:
        setArgumentList(edgeEnd);
        return true;
      case edkCall_RefersTo:
        setRefersTo(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Unary::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Call::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCall_HasArgumentList:
        removeArgumentList();
        return true;
      case edkCall_RefersTo:
        removeRefersTo();
        return true;
      default:
        break;
    }
    if (expression::Unary::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Call::setArgumentList(NodeId _id) {
    expression::ArgumentList *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ArgumentList*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasArgumentList) {
        removeParentEdge(m_hasArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasArgumentList, m_id, edkCall_HasArgumentList);
      }
      m_hasArgumentList = _node->getId();
      if (m_hasArgumentList != 0)
        setParentEdge(factory->getPointer(m_hasArgumentList), edkCall_HasArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasArgumentList, this->getId(), edkCall_HasArgumentList);
    } else {
      if (m_hasArgumentList) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Call::setArgumentList(expression::ArgumentList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgumentList(_node->getId());
  }

  void Call::removeArgumentList() {
      if (m_hasArgumentList) {
        removeParentEdge(m_hasArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasArgumentList, m_id, edkCall_HasArgumentList);
      }
      m_hasArgumentList = 0;
  }

  void Call::setRefersTo(NodeId _id) {
    statement::CompoundStatement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::CompoundStatement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (_node->getNodeKind() == ndkFunctionDef || _node->getNodeKind() == ndkClassDef) {
        if (m_refersTo) {
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_refersTo, m_id, edkCall_RefersTo);
        }
        m_refersTo = _node->getId();
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkCall_RefersTo);
      } else {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_refersTo) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Call::setRefersTo(statement::CompoundStatement *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void Call::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkCall_RefersTo);
      }
      m_refersTo = 0;
  }

  void Call::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Call::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Call::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Call::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Call::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Call", strlen("expression::Call"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Call::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Unary::save(binIo,false);

    binIo.writeUInt4(m_hasArgumentList);
    binIo.writeUInt4(m_refersTo);

  }

  void Call::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Unary::load(binIo,false);

    m_hasArgumentList =  binIo.readUInt4();
    if (m_hasArgumentList != 0)
      setParentEdge(factory->getPointer(m_hasArgumentList),edkCall_HasArgumentList);

    m_refersTo =  binIo.readUInt4();

  }


}


}}}
