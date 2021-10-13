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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  MetaProperty::MetaProperty(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    m_hasMeta(0),
    m_hasProperty(0)
  {
  }

  MetaProperty::~MetaProperty() {
  }

  void MetaProperty::prepareDelete(bool tryOnVirtualParent){
    removeMeta();
    removeProperty();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind MetaProperty::getNodeKind() const {
    return ndkMetaProperty;
  }

  expression::Identifier* MetaProperty::getMeta() const {
    expression::Identifier *_node = NULL;
    if (m_hasMeta != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasMeta));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Identifier* MetaProperty::getProperty() const {
    expression::Identifier *_node = NULL;
    if (m_hasProperty != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasProperty));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool MetaProperty::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMetaProperty_HasMeta:
        setMeta(edgeEnd);
        return true;
      case edkMetaProperty_HasProperty:
        setProperty(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool MetaProperty::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMetaProperty_HasMeta:
        removeMeta();
        return true;
      case edkMetaProperty_HasProperty:
        removeProperty();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MetaProperty::setMeta(NodeId _id) {
    expression::Identifier *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Identifier*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasMeta) {
        removeParentEdge(m_hasMeta);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasMeta, m_id, edkMetaProperty_HasMeta);
      }
      m_hasMeta = _node->getId();
      if (m_hasMeta != 0)
        setParentEdge(factory->getPointer(m_hasMeta), edkMetaProperty_HasMeta);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasMeta, this->getId(), edkMetaProperty_HasMeta);
    } else {
      if (m_hasMeta) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MetaProperty::setMeta(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setMeta(_node->getId());
  }

  void MetaProperty::removeMeta() {
      if (m_hasMeta) {
        removeParentEdge(m_hasMeta);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasMeta, m_id, edkMetaProperty_HasMeta);
      }
      m_hasMeta = 0;
  }

  void MetaProperty::setProperty(NodeId _id) {
    expression::Identifier *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Identifier*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasProperty) {
        removeParentEdge(m_hasProperty);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasProperty, m_id, edkMetaProperty_HasProperty);
      }
      m_hasProperty = _node->getId();
      if (m_hasProperty != 0)
        setParentEdge(factory->getPointer(m_hasProperty), edkMetaProperty_HasProperty);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasProperty, this->getId(), edkMetaProperty_HasProperty);
    } else {
      if (m_hasProperty) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MetaProperty::setProperty(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setProperty(_node->getId());
  }

  void MetaProperty::removeProperty() {
      if (m_hasProperty) {
        removeParentEdge(m_hasProperty);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasProperty, m_id, edkMetaProperty_HasProperty);
      }
      m_hasProperty = 0;
  }

  void MetaProperty::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MetaProperty::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MetaProperty::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void MetaProperty::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType MetaProperty::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::MetaProperty", strlen("expression::MetaProperty"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MetaProperty::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasMeta);
    binIo.writeUInt4(m_hasProperty);

  }

  void MetaProperty::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    m_hasMeta =  binIo.readUInt4();
    if (m_hasMeta != 0)
      setParentEdge(factory->getPointer(m_hasMeta),edkMetaProperty_HasMeta);

    m_hasProperty =  binIo.readUInt4();
    if (m_hasProperty != 0)
      setParentEdge(factory->getPointer(m_hasProperty),edkMetaProperty_HasProperty);

  }


}


}}}
