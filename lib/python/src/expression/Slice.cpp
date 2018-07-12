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
  Slice::Slice(NodeId _id, Factory *_factory) :
    Slicing(_id, _factory),
    m_hasLowerBound(0),
    m_hasStride(0),
    m_hasUpperBound(0)
  {
  }

  Slice::~Slice() {
  }

  void Slice::prepareDelete(bool tryOnVirtualParent){
    removeLowerBound();
    removeStride();
    removeUpperBound();
    expression::Slicing::prepareDelete(false);
  }

  NodeKind Slice::getNodeKind() const {
    return ndkSlice;
  }

  expression::Expression* Slice::getLowerBound() const {
    expression::Expression *_node = NULL;
    if (m_hasLowerBound != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasLowerBound));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Slice::getStride() const {
    expression::Expression *_node = NULL;
    if (m_hasStride != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasStride));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Slice::getUpperBound() const {
    expression::Expression *_node = NULL;
    if (m_hasUpperBound != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasUpperBound));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Slice::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSlice_HasLowerBound:
        setLowerBound(edgeEnd);
        return true;
      case edkSlice_HasStride:
        setStride(edgeEnd);
        return true;
      case edkSlice_HasUpperBound:
        setUpperBound(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Slicing::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Slice::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSlice_HasLowerBound:
        removeLowerBound();
        return true;
      case edkSlice_HasStride:
        removeStride();
        return true;
      case edkSlice_HasUpperBound:
        removeUpperBound();
        return true;
      default:
        break;
    }
    if (expression::Slicing::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Slice::setLowerBound(NodeId _id) {
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

      if (m_hasLowerBound) {
        removeParentEdge(m_hasLowerBound);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLowerBound, m_id, edkSlice_HasLowerBound);
      }
      m_hasLowerBound = _node->getId();
      if (m_hasLowerBound != 0)
        setParentEdge(factory->getPointer(m_hasLowerBound), edkSlice_HasLowerBound);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLowerBound, this->getId(), edkSlice_HasLowerBound);
    } else {
      if (m_hasLowerBound) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Slice::setLowerBound(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLowerBound(_node->getId());
  }

  void Slice::removeLowerBound() {
      if (m_hasLowerBound) {
        removeParentEdge(m_hasLowerBound);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLowerBound, m_id, edkSlice_HasLowerBound);
      }
      m_hasLowerBound = 0;
  }

  void Slice::setStride(NodeId _id) {
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

      if (m_hasStride) {
        removeParentEdge(m_hasStride);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasStride, m_id, edkSlice_HasStride);
      }
      m_hasStride = _node->getId();
      if (m_hasStride != 0)
        setParentEdge(factory->getPointer(m_hasStride), edkSlice_HasStride);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasStride, this->getId(), edkSlice_HasStride);
    } else {
      if (m_hasStride) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Slice::setStride(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setStride(_node->getId());
  }

  void Slice::removeStride() {
      if (m_hasStride) {
        removeParentEdge(m_hasStride);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasStride, m_id, edkSlice_HasStride);
      }
      m_hasStride = 0;
  }

  void Slice::setUpperBound(NodeId _id) {
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

      if (m_hasUpperBound) {
        removeParentEdge(m_hasUpperBound);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasUpperBound, m_id, edkSlice_HasUpperBound);
      }
      m_hasUpperBound = _node->getId();
      if (m_hasUpperBound != 0)
        setParentEdge(factory->getPointer(m_hasUpperBound), edkSlice_HasUpperBound);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasUpperBound, this->getId(), edkSlice_HasUpperBound);
    } else {
      if (m_hasUpperBound) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Slice::setUpperBound(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setUpperBound(_node->getId());
  }

  void Slice::removeUpperBound() {
      if (m_hasUpperBound) {
        removeParentEdge(m_hasUpperBound);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasUpperBound, m_id, edkSlice_HasUpperBound);
      }
      m_hasUpperBound = 0;
  }

  void Slice::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Slice::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Slice::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Slice::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Slice::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Slice", strlen("expression::Slice"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Slice::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Slicing::save(binIo,false);

    binIo.writeUInt4(m_hasLowerBound);
    binIo.writeUInt4(m_hasStride);
    binIo.writeUInt4(m_hasUpperBound);

  }

  void Slice::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Slicing::load(binIo,false);

    m_hasLowerBound =  binIo.readUInt4();
    if (m_hasLowerBound != 0)
      setParentEdge(factory->getPointer(m_hasLowerBound),edkSlice_HasLowerBound);

    m_hasStride =  binIo.readUInt4();
    if (m_hasStride != 0)
      setParentEdge(factory->getPointer(m_hasStride),edkSlice_HasStride);

    m_hasUpperBound =  binIo.readUInt4();
    if (m_hasUpperBound != 0)
      setParentEdge(factory->getPointer(m_hasUpperBound),edkSlice_HasUpperBound);

  }


}


}}}
