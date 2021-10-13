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
  Raise::Raise(NodeId _id, Factory *_factory) :
    SimpleStatement(_id, _factory),
    m_hasType(0),
    m_hasValue(0),
    m_hasTraceback(0),
    m_hasException(0),
    m_hasCause(0)
  {
  }

  Raise::~Raise() {
  }

  void Raise::prepareDelete(bool tryOnVirtualParent){
    removeType();
    removeValue();
    removeTraceback();
    removeException();
    removeCause();
    statement::SimpleStatement::prepareDelete(false);
  }

  NodeKind Raise::getNodeKind() const {
    return ndkRaise;
  }

  expression::Expression* Raise::getType() const {
    expression::Expression *_node = NULL;
    if (m_hasType != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Raise::getValue() const {
    expression::Expression *_node = NULL;
    if (m_hasValue != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Raise::getTraceback() const {
    expression::Expression *_node = NULL;
    if (m_hasTraceback != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTraceback));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Raise::getException() const {
    expression::Expression *_node = NULL;
    if (m_hasException != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasException));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Raise::getCause() const {
    expression::Expression *_node = NULL;
    if (m_hasCause != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasCause));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Raise::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRaise_HasType:
        setType(edgeEnd);
        return true;
      case edkRaise_HasValue:
        setValue(edgeEnd);
        return true;
      case edkRaise_HasTraceback:
        setTraceback(edgeEnd);
        return true;
      case edkRaise_HasException:
        setException(edgeEnd);
        return true;
      case edkRaise_HasCause:
        setCause(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Raise::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRaise_HasType:
        removeType();
        return true;
      case edkRaise_HasValue:
        removeValue();
        return true;
      case edkRaise_HasTraceback:
        removeTraceback();
        return true;
      case edkRaise_HasException:
        removeException();
        return true;
      case edkRaise_HasCause:
        removeCause();
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Raise::setType(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasType) {
        removeParentEdge(m_hasType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasType, m_id, edkRaise_HasType);
      }
      m_hasType = _node->getId();
      if (m_hasType != 0)
        setParentEdge(factory->getPointer(m_hasType), edkRaise_HasType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasType, this->getId(), edkRaise_HasType);
    } else {
      if (m_hasType) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setType(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void Raise::removeType() {
      if (m_hasType) {
        removeParentEdge(m_hasType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasType, m_id, edkRaise_HasType);
      }
      m_hasType = 0;
  }

  void Raise::setValue(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkRaise_HasValue);
      }
      m_hasValue = _node->getId();
      if (m_hasValue != 0)
        setParentEdge(factory->getPointer(m_hasValue), edkRaise_HasValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasValue, this->getId(), edkRaise_HasValue);
    } else {
      if (m_hasValue) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setValue(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValue(_node->getId());
  }

  void Raise::removeValue() {
      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkRaise_HasValue);
      }
      m_hasValue = 0;
  }

  void Raise::setTraceback(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasTraceback) {
        removeParentEdge(m_hasTraceback);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTraceback, m_id, edkRaise_HasTraceback);
      }
      m_hasTraceback = _node->getId();
      if (m_hasTraceback != 0)
        setParentEdge(factory->getPointer(m_hasTraceback), edkRaise_HasTraceback);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTraceback, this->getId(), edkRaise_HasTraceback);
    } else {
      if (m_hasTraceback) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setTraceback(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTraceback(_node->getId());
  }

  void Raise::removeTraceback() {
      if (m_hasTraceback) {
        removeParentEdge(m_hasTraceback);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTraceback, m_id, edkRaise_HasTraceback);
      }
      m_hasTraceback = 0;
  }

  void Raise::setException(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasException) {
        removeParentEdge(m_hasException);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasException, m_id, edkRaise_HasException);
      }
      m_hasException = _node->getId();
      if (m_hasException != 0)
        setParentEdge(factory->getPointer(m_hasException), edkRaise_HasException);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasException, this->getId(), edkRaise_HasException);
    } else {
      if (m_hasException) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setException(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setException(_node->getId());
  }

  void Raise::removeException() {
      if (m_hasException) {
        removeParentEdge(m_hasException);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasException, m_id, edkRaise_HasException);
      }
      m_hasException = 0;
  }

  void Raise::setCause(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasCause) {
        removeParentEdge(m_hasCause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCause, m_id, edkRaise_HasCause);
      }
      m_hasCause = _node->getId();
      if (m_hasCause != 0)
        setParentEdge(factory->getPointer(m_hasCause), edkRaise_HasCause);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasCause, this->getId(), edkRaise_HasCause);
    } else {
      if (m_hasCause) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setCause(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCause(_node->getId());
  }

  void Raise::removeCause() {
      if (m_hasCause) {
        removeParentEdge(m_hasCause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCause, m_id, edkRaise_HasCause);
      }
      m_hasCause = 0;
  }

  void Raise::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Raise::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Raise::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Raise::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Raise::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Raise", strlen("statement::Raise"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Raise::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleStatement::save(binIo,false);

    binIo.writeUInt4(m_hasType);
    binIo.writeUInt4(m_hasValue);
    binIo.writeUInt4(m_hasTraceback);
    binIo.writeUInt4(m_hasException);
    binIo.writeUInt4(m_hasCause);

  }

  void Raise::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleStatement::load(binIo,false);

    m_hasType =  binIo.readUInt4();
    if (m_hasType != 0)
      setParentEdge(factory->getPointer(m_hasType),edkRaise_HasType);

    m_hasValue =  binIo.readUInt4();
    if (m_hasValue != 0)
      setParentEdge(factory->getPointer(m_hasValue),edkRaise_HasValue);

    m_hasTraceback =  binIo.readUInt4();
    if (m_hasTraceback != 0)
      setParentEdge(factory->getPointer(m_hasTraceback),edkRaise_HasTraceback);

    m_hasException =  binIo.readUInt4();
    if (m_hasException != 0)
      setParentEdge(factory->getPointer(m_hasException),edkRaise_HasException);

    m_hasCause =  binIo.readUInt4();
    if (m_hasCause != 0)
      setParentEdge(factory->getPointer(m_hasCause),edkRaise_HasCause);

  }


}


}}}
