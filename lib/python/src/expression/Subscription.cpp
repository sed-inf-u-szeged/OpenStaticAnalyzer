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
  Subscription::Subscription(NodeId _id, Factory *_factory) :
    Unary(_id, _factory),
    m_hasSlicing(0)
  {
  }

  Subscription::~Subscription() {
  }

  void Subscription::prepareDelete(bool tryOnVirtualParent){
    removeSlicing();
    expression::Unary::prepareDelete(false);
  }

  NodeKind Subscription::getNodeKind() const {
    return ndkSubscription;
  }

  expression::Slicing* Subscription::getSlicing() const {
    expression::Slicing *_node = NULL;
    if (m_hasSlicing != 0)
      _node = dynamic_cast<expression::Slicing*>(factory->getPointer(m_hasSlicing));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Subscription::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSubscription_HasSlicing:
        setSlicing(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Unary::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Subscription::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSubscription_HasSlicing:
        removeSlicing();
        return true;
      default:
        break;
    }
    if (expression::Unary::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Subscription::setSlicing(NodeId _id) {
    expression::Slicing *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Slicing*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSlicing) {
        removeParentEdge(m_hasSlicing);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSlicing, m_id, edkSubscription_HasSlicing);
      }
      m_hasSlicing = _node->getId();
      if (m_hasSlicing != 0)
        setParentEdge(factory->getPointer(m_hasSlicing), edkSubscription_HasSlicing);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSlicing, this->getId(), edkSubscription_HasSlicing);
    } else {
      if (m_hasSlicing) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Subscription::setSlicing(expression::Slicing *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSlicing(_node->getId());
  }

  void Subscription::removeSlicing() {
      if (m_hasSlicing) {
        removeParentEdge(m_hasSlicing);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSlicing, m_id, edkSubscription_HasSlicing);
      }
      m_hasSlicing = 0;
  }

  void Subscription::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Subscription::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Subscription::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Subscription::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Subscription::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Subscription", strlen("expression::Subscription"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Subscription::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Unary::save(binIo,false);

    binIo.writeUInt4(m_hasSlicing);

  }

  void Subscription::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Unary::load(binIo,false);

    m_hasSlicing =  binIo.readUInt4();
    if (m_hasSlicing != 0)
      setParentEdge(factory->getPointer(m_hasSlicing),edkSubscription_HasSlicing);

  }


}


}}}
