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
  Starred::Starred(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_hasValue(0)
  {
  }

  Starred::~Starred() {
  }

  void Starred::prepareDelete(bool tryOnVirtualParent){
    removeValue();
    expression::Expression::prepareDelete(false);
  }

  NodeKind Starred::getNodeKind() const {
    return ndkStarred;
  }

  expression::Expression* Starred::getValue() const {
    expression::Expression *_node = NULL;
    if (m_hasValue != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Starred::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkStarred_HasValue:
        setValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Starred::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkStarred_HasValue:
        removeValue();
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Starred::setValue(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkStarred_HasValue);
      }
      m_hasValue = _node->getId();
      if (m_hasValue != 0)
        setParentEdge(factory->getPointer(m_hasValue), edkStarred_HasValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasValue, this->getId(), edkStarred_HasValue);
    } else {
      if (m_hasValue) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Starred::setValue(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValue(_node->getId());
  }

  void Starred::removeValue() {
      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkStarred_HasValue);
      }
      m_hasValue = 0;
  }

  void Starred::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Starred::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Starred::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Starred::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Starred::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Starred", strlen("expression::Starred"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Starred::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasValue);

  }

  void Starred::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    m_hasValue =  binIo.readUInt4();
    if (m_hasValue != 0)
      setParentEdge(factory->getPointer(m_hasValue),edkStarred_HasValue);

  }


}


}}}
