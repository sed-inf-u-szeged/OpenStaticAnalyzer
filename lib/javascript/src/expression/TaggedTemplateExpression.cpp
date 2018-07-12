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
  TaggedTemplateExpression::TaggedTemplateExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    m_hasTag(0),
    m_hasQuasi(0)
  {
  }

  TaggedTemplateExpression::~TaggedTemplateExpression() {
  }

  void TaggedTemplateExpression::prepareDelete(bool tryOnVirtualParent){
    removeTag();
    removeQuasi();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind TaggedTemplateExpression::getNodeKind() const {
    return ndkTaggedTemplateExpression;
  }

  expression::Expression* TaggedTemplateExpression::getTag() const {
    expression::Expression *_node = NULL;
    if (m_hasTag != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTag));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TemplateLiteral* TaggedTemplateExpression::getQuasi() const {
    expression::TemplateLiteral *_node = NULL;
    if (m_hasQuasi != 0)
      _node = dynamic_cast<expression::TemplateLiteral*>(factory->getPointer(m_hasQuasi));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TaggedTemplateExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTaggedTemplateExpression_HasTag:
        setTag(edgeEnd);
        return true;
      case edkTaggedTemplateExpression_HasQuasi:
        setQuasi(edgeEnd);
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

  bool TaggedTemplateExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTaggedTemplateExpression_HasTag:
        removeTag();
        return true;
      case edkTaggedTemplateExpression_HasQuasi:
        removeQuasi();
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

  void TaggedTemplateExpression::setTag(NodeId _id) {
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

      if (m_hasTag) {
        removeParentEdge(m_hasTag);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTag, m_id, edkTaggedTemplateExpression_HasTag);
      }
      m_hasTag = _node->getId();
      if (m_hasTag != 0)
        setParentEdge(factory->getPointer(m_hasTag), edkTaggedTemplateExpression_HasTag);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTag, this->getId(), edkTaggedTemplateExpression_HasTag);
    } else {
      if (m_hasTag) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TaggedTemplateExpression::setTag(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTag(_node->getId());
  }

  void TaggedTemplateExpression::removeTag() {
      if (m_hasTag) {
        removeParentEdge(m_hasTag);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTag, m_id, edkTaggedTemplateExpression_HasTag);
      }
      m_hasTag = 0;
  }

  void TaggedTemplateExpression::setQuasi(NodeId _id) {
    expression::TemplateLiteral *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::TemplateLiteral*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasQuasi) {
        removeParentEdge(m_hasQuasi);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasQuasi, m_id, edkTaggedTemplateExpression_HasQuasi);
      }
      m_hasQuasi = _node->getId();
      if (m_hasQuasi != 0)
        setParentEdge(factory->getPointer(m_hasQuasi), edkTaggedTemplateExpression_HasQuasi);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasQuasi, this->getId(), edkTaggedTemplateExpression_HasQuasi);
    } else {
      if (m_hasQuasi) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TaggedTemplateExpression::setQuasi(expression::TemplateLiteral *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setQuasi(_node->getId());
  }

  void TaggedTemplateExpression::removeQuasi() {
      if (m_hasQuasi) {
        removeParentEdge(m_hasQuasi);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasQuasi, m_id, edkTaggedTemplateExpression_HasQuasi);
      }
      m_hasQuasi = 0;
  }

  void TaggedTemplateExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TaggedTemplateExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TaggedTemplateExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TaggedTemplateExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TaggedTemplateExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::TaggedTemplateExpression", strlen("expression::TaggedTemplateExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TaggedTemplateExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasTag);
    binIo.writeUInt4(m_hasQuasi);

  }

  void TaggedTemplateExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    m_hasTag =  binIo.readUInt4();
    if (m_hasTag != 0)
      setParentEdge(factory->getPointer(m_hasTag),edkTaggedTemplateExpression_HasTag);

    m_hasQuasi =  binIo.readUInt4();
    if (m_hasQuasi != 0)
      setParentEdge(factory->getPointer(m_hasQuasi),edkTaggedTemplateExpression_HasQuasi);

  }


}


}}}
