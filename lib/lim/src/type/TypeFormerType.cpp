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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace type { 
  TypeFormerType::TypeFormerType(NodeId _id, Factory *_factory) :
    TypeFormer(_id, _factory),
    m_refersTo(0)
  {
  }

  TypeFormerType::~TypeFormerType() {
  }

  void TypeFormerType::clone(const TypeFormerType& other, bool tryOnVirtualParent) {
    type::TypeFormer::clone(other, false);

    m_refersTo = other.m_refersTo;
  }

  void TypeFormerType::prepareDelete(bool tryOnVirtualParent){
    removeRefersTo();
    type::TypeFormer::prepareDelete(false);
  }

  NodeKind TypeFormerType::getNodeKind() const {
    return ndkTypeFormerType;
  }

  base::Base* TypeFormerType::getRefersTo() const {
    base::Base *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<base::Base*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TypeFormerType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeFormerType_RefersTo:
        setRefersTo(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::TypeFormer::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool TypeFormerType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeFormerType_RefersTo:
        removeRefersTo();
        return true;
      default:
        break;
    }
    if (type::TypeFormer::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeFormerType::setRefersTo(NodeId _id) {
    base::Base *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Base*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (_node->getNodeKind() == ndkSimpleType || _node->getNodeKind() == ndkGenericParameter || _node->getNodeKind() == ndkMethodGenericInstance || Common::getIsBaseClassKind(_node->getNodeKind(), ndkClass)) {
        if (m_refersTo) {
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_refersTo, m_id, edkTypeFormerType_RefersTo);
        }
        m_refersTo = _node->getId();
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkTypeFormerType_RefersTo);
      } else {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_refersTo) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeFormerType::setRefersTo(base::Base *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void TypeFormerType::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkTypeFormerType_RefersTo);
      }
      m_refersTo = 0;
  }

  void TypeFormerType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeFormerType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeFormerType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TypeFormerType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TypeFormerType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::TypeFormerType", strlen("type::TypeFormerType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeFormerType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    TypeFormer::save(binIo,false);

    binIo.writeUInt4(m_refersTo);

  }

  void TypeFormerType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    TypeFormer::load(binIo,false);

    m_refersTo =  binIo.readUInt4();

  }


}


}}}
