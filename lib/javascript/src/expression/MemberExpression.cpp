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
  MemberExpression::MemberExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    Pattern(_id, _factory),
    ChainElement(_id, _factory),
    m_computed(false),
    m_hasProperty(0),
    m_hasObject(0)
  {
  }

  MemberExpression::~MemberExpression() {
  }

  void MemberExpression::prepareDelete(bool tryOnVirtualParent){
    removeProperty();
    removeObject();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
    statement::Pattern::prepareDelete(false);
    expression::ChainElement::prepareDelete(false);
  }

  NodeKind MemberExpression::getNodeKind() const {
    return ndkMemberExpression;
  }

  bool MemberExpression::getComputed() const {
    return m_computed;
  }

  void MemberExpression::setComputed(bool _computed) {
    m_computed = _computed;
  }

  base::Positioned* MemberExpression::getProperty() const {
    base::Positioned *_node = NULL;
    if (m_hasProperty != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasProperty));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  base::Positioned* MemberExpression::getObject() const {
    base::Positioned *_node = NULL;
    if (m_hasObject != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasObject));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool MemberExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMemberExpression_HasProperty:
        setProperty(edgeEnd);
        return true;
      case edkMemberExpression_HasObject:
        setObject(edgeEnd);
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
    if (statement::Pattern::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (expression::ChainElement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool MemberExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMemberExpression_HasProperty:
        removeProperty();
        return true;
      case edkMemberExpression_HasObject:
        removeObject();
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
    if (statement::Pattern::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (expression::ChainElement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MemberExpression::setProperty(NodeId _id) {
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

      if (Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression) || _node->getNodeKind() == ndkPrivateIdentifier) {
        if (m_hasProperty) {
          removeParentEdge(m_hasProperty);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasProperty, m_id, edkMemberExpression_HasProperty);
        }
        m_hasProperty = _node->getId();
        if (m_hasProperty != 0)
          setParentEdge(factory->getPointer(m_hasProperty), edkMemberExpression_HasProperty);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasProperty, this->getId(), edkMemberExpression_HasProperty);
      } else {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasProperty) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MemberExpression::setProperty(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setProperty(_node->getId());
  }

  void MemberExpression::removeProperty() {
      if (m_hasProperty) {
        removeParentEdge(m_hasProperty);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasProperty, m_id, edkMemberExpression_HasProperty);
      }
      m_hasProperty = 0;
  }

  void MemberExpression::setObject(NodeId _id) {
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

      if (_node->getNodeKind() == ndkSuper || Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression)) {
        if (m_hasObject) {
          removeParentEdge(m_hasObject);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasObject, m_id, edkMemberExpression_HasObject);
        }
        m_hasObject = _node->getId();
        if (m_hasObject != 0)
          setParentEdge(factory->getPointer(m_hasObject), edkMemberExpression_HasObject);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasObject, this->getId(), edkMemberExpression_HasObject);
      } else {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasObject) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MemberExpression::setObject(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setObject(_node->getId());
  }

  void MemberExpression::removeObject() {
      if (m_hasObject) {
        removeParentEdge(m_hasObject);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasObject, m_id, edkMemberExpression_HasObject);
      }
      m_hasObject = 0;
  }

  void MemberExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MemberExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MemberExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const MemberExpression& node = dynamic_cast<const MemberExpression&>(base);
      double matchAttrs = 0;
      if(node.getOptional() == getOptional()) ++matchAttrs;
      if(node.getComputed() == getComputed()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void MemberExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType MemberExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::MemberExpression", strlen("expression::MemberExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MemberExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    Pattern::save(binIo,false);

    ChainElement::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_computed) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasProperty);
    binIo.writeUInt4(m_hasObject);

  }

  void MemberExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    Pattern::load(binIo,false);

    ChainElement::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_computed = boolValues & 1;
    boolValues >>= 1;

    m_hasProperty =  binIo.readUInt4();
    if (m_hasProperty != 0)
      setParentEdge(factory->getPointer(m_hasProperty),edkMemberExpression_HasProperty);

    m_hasObject =  binIo.readUInt4();
    if (m_hasObject != 0)
      setParentEdge(factory->getPointer(m_hasObject),edkMemberExpression_HasObject);

  }


}


}}}
