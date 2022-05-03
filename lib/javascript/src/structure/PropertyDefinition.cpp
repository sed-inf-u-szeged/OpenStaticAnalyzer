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

namespace structure { 
  PropertyDefinition::PropertyDefinition(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_computed(false),
    m_static(false),
    m_hasKey(0),
    m_hasValue(0)
  {
  }

  PropertyDefinition::~PropertyDefinition() {
  }

  void PropertyDefinition::prepareDelete(bool tryOnVirtualParent){
    removeKey();
    removeValue();
    base::Positioned::prepareDelete(false);
  }

  NodeKind PropertyDefinition::getNodeKind() const {
    return ndkPropertyDefinition;
  }

  bool PropertyDefinition::getComputed() const {
    return m_computed;
  }

  bool PropertyDefinition::getStatic() const {
    return m_static;
  }

  void PropertyDefinition::setComputed(bool _computed) {
    m_computed = _computed;
  }

  void PropertyDefinition::setStatic(bool _static) {
    m_static = _static;
  }

  base::Positioned* PropertyDefinition::getKey() const {
    base::Positioned *_node = NULL;
    if (m_hasKey != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasKey));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* PropertyDefinition::getValue() const {
    expression::Expression *_node = NULL;
    if (m_hasValue != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool PropertyDefinition::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPropertyDefinition_HasKey:
        setKey(edgeEnd);
        return true;
      case edkPropertyDefinition_HasValue:
        setValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool PropertyDefinition::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPropertyDefinition_HasKey:
        removeKey();
        return true;
      case edkPropertyDefinition_HasValue:
        removeValue();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void PropertyDefinition::setKey(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (_node->getNodeKind() == ndkPrivateIdentifier || Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression)) {
        if (m_hasKey) {
          removeParentEdge(m_hasKey);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasKey, m_id, edkPropertyDefinition_HasKey);
        }
        m_hasKey = _node->getId();
        if (m_hasKey != 0)
          setParentEdge(factory->getPointer(m_hasKey), edkPropertyDefinition_HasKey);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasKey, this->getId(), edkPropertyDefinition_HasKey);
      } else {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasKey) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PropertyDefinition::setKey(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setKey(_node->getId());
  }

  void PropertyDefinition::removeKey() {
      if (m_hasKey) {
        removeParentEdge(m_hasKey);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasKey, m_id, edkPropertyDefinition_HasKey);
      }
      m_hasKey = 0;
  }

  void PropertyDefinition::setValue(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkPropertyDefinition_HasValue);
      }
      m_hasValue = _node->getId();
      if (m_hasValue != 0)
        setParentEdge(factory->getPointer(m_hasValue), edkPropertyDefinition_HasValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasValue, this->getId(), edkPropertyDefinition_HasValue);
    } else {
      if (m_hasValue) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PropertyDefinition::setValue(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValue(_node->getId());
  }

  void PropertyDefinition::removeValue() {
      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkPropertyDefinition_HasValue);
      }
      m_hasValue = 0;
  }

  void PropertyDefinition::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void PropertyDefinition::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double PropertyDefinition::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const PropertyDefinition& node = dynamic_cast<const PropertyDefinition&>(base);
      double matchAttrs = 0;
      if(node.getComputed() == getComputed()) ++matchAttrs;
      if(node.getStatic() == getStatic()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void PropertyDefinition::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType PropertyDefinition::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::PropertyDefinition", strlen("structure::PropertyDefinition"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void PropertyDefinition::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_computed) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_static) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasKey);
    binIo.writeUInt4(m_hasValue);

  }

  void PropertyDefinition::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_static = boolValues & 1;
    boolValues >>= 1;
    m_computed = boolValues & 1;
    boolValues >>= 1;

    m_hasKey =  binIo.readUInt4();
    if (m_hasKey != 0)
      setParentEdge(factory->getPointer(m_hasKey),edkPropertyDefinition_HasKey);

    m_hasValue =  binIo.readUInt4();
    if (m_hasValue != 0)
      setParentEdge(factory->getPointer(m_hasValue),edkPropertyDefinition_HasValue);

  }


}


}}}
