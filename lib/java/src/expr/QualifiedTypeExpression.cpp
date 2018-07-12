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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expr { 
  QualifiedTypeExpression::QualifiedTypeExpression(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    TypeExpression(_id, _factory),
    m_hasQualifierType(0),
    m_hasSimpleType(0)
  {
  }

  QualifiedTypeExpression::~QualifiedTypeExpression() {
  }

  void QualifiedTypeExpression::clone(const QualifiedTypeExpression& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::TypeExpression::clone(other, false);

    m_hasQualifierType = other.m_hasQualifierType;
    m_hasSimpleType = other.m_hasSimpleType;
  }

  void QualifiedTypeExpression::prepareDelete(bool tryOnVirtualParent){
    removeQualifierType();
    removeSimpleType();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::TypeExpression::prepareDelete(false);
  }

  NodeKind QualifiedTypeExpression::getNodeKind() const {
    return ndkQualifiedTypeExpression;
  }

  expr::TypeExpression* QualifiedTypeExpression::getQualifierType() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasQualifierType != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasQualifierType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expr::SimpleTypeExpression* QualifiedTypeExpression::getSimpleType() const {
    expr::SimpleTypeExpression *_node = NULL;
    if (m_hasSimpleType != 0)
      _node = dynamic_cast<expr::SimpleTypeExpression*>(factory->getPointer(m_hasSimpleType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool QualifiedTypeExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQualifiedTypeExpression_HasQualifierType:
        setQualifierType(edgeEnd);
        return true;
      case edkQualifiedTypeExpression_HasSimpleType:
        setSimpleType(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expr::TypeExpression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool QualifiedTypeExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQualifiedTypeExpression_HasQualifierType:
        removeQualifierType();
        return true;
      case edkQualifiedTypeExpression_HasSimpleType:
        removeSimpleType();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expr::TypeExpression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void QualifiedTypeExpression::setQualifierType(NodeId _id) {
    expr::TypeExpression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::TypeExpression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasQualifierType) {
        removeParentEdge(m_hasQualifierType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasQualifierType, m_id, edkQualifiedTypeExpression_HasQualifierType);
      }
      m_hasQualifierType = _node->getId();
      if (m_hasQualifierType != 0)
        setParentEdge(factory->getPointer(m_hasQualifierType), edkQualifiedTypeExpression_HasQualifierType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasQualifierType, this->getId(), edkQualifiedTypeExpression_HasQualifierType);
    } else {
      if (m_hasQualifierType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QualifiedTypeExpression::setQualifierType(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setQualifierType(_node->getId());
  }

  void QualifiedTypeExpression::removeQualifierType() {
      if (m_hasQualifierType) {
        removeParentEdge(m_hasQualifierType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasQualifierType, m_id, edkQualifiedTypeExpression_HasQualifierType);
      }
      m_hasQualifierType = 0;
  }

  void QualifiedTypeExpression::setSimpleType(NodeId _id) {
    expr::SimpleTypeExpression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::SimpleTypeExpression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSimpleType) {
        removeParentEdge(m_hasSimpleType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSimpleType, m_id, edkQualifiedTypeExpression_HasSimpleType);
      }
      m_hasSimpleType = _node->getId();
      if (m_hasSimpleType != 0)
        setParentEdge(factory->getPointer(m_hasSimpleType), edkQualifiedTypeExpression_HasSimpleType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSimpleType, this->getId(), edkQualifiedTypeExpression_HasSimpleType);
    } else {
      if (m_hasSimpleType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QualifiedTypeExpression::setSimpleType(expr::SimpleTypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSimpleType(_node->getId());
  }

  void QualifiedTypeExpression::removeSimpleType() {
      if (m_hasSimpleType) {
        removeParentEdge(m_hasSimpleType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSimpleType, m_id, edkQualifiedTypeExpression_HasSimpleType);
      }
      m_hasSimpleType = 0;
  }

  void QualifiedTypeExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void QualifiedTypeExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double QualifiedTypeExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const QualifiedTypeExpression& node = dynamic_cast<const QualifiedTypeExpression&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void QualifiedTypeExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType QualifiedTypeExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::QualifiedTypeExpression", strlen("expr::QualifiedTypeExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void QualifiedTypeExpression::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    TypeExpression::sort(false);
  }

  void QualifiedTypeExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    TypeExpression::save(binIo,false);

    binIo.writeUInt4(m_hasQualifierType);
    binIo.writeUInt4(m_hasSimpleType);

  }

  void QualifiedTypeExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    TypeExpression::load(binIo,false);

    m_hasQualifierType =  binIo.readUInt4();
    if (m_hasQualifierType != 0)
      setParentEdge(factory->getPointer(m_hasQualifierType),edkQualifiedTypeExpression_HasQualifierType);

    m_hasSimpleType =  binIo.readUInt4();
    if (m_hasSimpleType != 0)
      setParentEdge(factory->getPointer(m_hasSimpleType),edkQualifiedTypeExpression_HasSimpleType);

  }


}


}}}
