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
  Property::Property(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_method(false),
    m_shorthand(false),
    m_computed(false),
    m_kind(pkInit),
    m_hasValue(0),
    m_hasKey(0)
  {
  }

  Property::~Property() {
  }

  void Property::prepareDelete(bool tryOnVirtualParent){
    removeValue();
    removeKey();
    base::Positioned::prepareDelete(false);
  }

  NodeKind Property::getNodeKind() const {
    return ndkProperty;
  }

  PropertyKind Property::getKind() const {
    return m_kind;
  }

  bool Property::getMethod() const {
    return m_method;
  }

  bool Property::getShorthand() const {
    return m_shorthand;
  }

  bool Property::getComputed() const {
    return m_computed;
  }

  void Property::setKind(PropertyKind _kind) {
    m_kind = _kind;
  }

  void Property::setMethod(bool _method) {
    m_method = _method;
  }

  void Property::setShorthand(bool _shorthand) {
    m_shorthand = _shorthand;
  }

  void Property::setComputed(bool _computed) {
    m_computed = _computed;
  }

  base::Positioned* Property::getValue() const {
    base::Positioned *_node = NULL;
    if (m_hasValue != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Property::getKey() const {
    expression::Expression *_node = NULL;
    if (m_hasKey != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasKey));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Property::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkProperty_HasValue:
        setValue(edgeEnd);
        return true;
      case edkProperty_HasKey:
        setKey(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Property::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkProperty_HasValue:
        removeValue();
        return true;
      case edkProperty_HasKey:
        removeKey();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Property::setValue(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression) || Common::getIsBaseClassKind(_node->getNodeKind(), ndkPattern)) {
        if (m_hasValue) {
          removeParentEdge(m_hasValue);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasValue, m_id, edkProperty_HasValue);
        }
        m_hasValue = _node->getId();
        if (m_hasValue != 0)
          setParentEdge(factory->getPointer(m_hasValue), edkProperty_HasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasValue, this->getId(), edkProperty_HasValue);
      } else {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasValue) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Property::setValue(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValue(_node->getId());
  }

  void Property::removeValue() {
      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkProperty_HasValue);
      }
      m_hasValue = 0;
  }

  void Property::setKey(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasKey) {
        removeParentEdge(m_hasKey);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasKey, m_id, edkProperty_HasKey);
      }
      m_hasKey = _node->getId();
      if (m_hasKey != 0)
        setParentEdge(factory->getPointer(m_hasKey), edkProperty_HasKey);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasKey, this->getId(), edkProperty_HasKey);
    } else {
      if (m_hasKey) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Property::setKey(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setKey(_node->getId());
  }

  void Property::removeKey() {
      if (m_hasKey) {
        removeParentEdge(m_hasKey);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasKey, m_id, edkProperty_HasKey);
      }
      m_hasKey = 0;
  }

  void Property::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Property::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Property::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Property& node = dynamic_cast<const Property&>(base);
      double matchAttrs = 0;
      if(node.getKind() == getKind()) ++matchAttrs;
      if(node.getMethod() == getMethod()) ++matchAttrs;
      if(node.getShorthand() == getShorthand()) ++matchAttrs;
      if(node.getComputed() == getComputed()) ++matchAttrs;
      return matchAttrs / (4 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Property::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Property::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Property", strlen("expression::Property"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Property::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_method) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_shorthand) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_computed) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUByte1(m_kind);

    binIo.writeUInt4(m_hasValue);
    binIo.writeUInt4(m_hasKey);

  }

  void Property::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_computed = boolValues & 1;
    boolValues >>= 1;
    m_shorthand = boolValues & 1;
    boolValues >>= 1;
    m_method = boolValues & 1;
    boolValues >>= 1;
    m_kind = (PropertyKind)binIo.readUByte1();

    m_hasValue =  binIo.readUInt4();
    if (m_hasValue != 0)
      setParentEdge(factory->getPointer(m_hasValue),edkProperty_HasValue);

    m_hasKey =  binIo.readUInt4();
    if (m_hasKey != 0)
      setParentEdge(factory->getPointer(m_hasKey),edkProperty_HasKey);

  }


}


}}}
