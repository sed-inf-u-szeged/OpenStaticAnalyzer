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
  TypeCast::TypeCast(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Unary(_id, _factory),
    m_hasTypeOperand(0)
  {
  }

  TypeCast::~TypeCast() {
  }

  void TypeCast::clone(const TypeCast& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Unary::clone(other, false);

    m_hasTypeOperand = other.m_hasTypeOperand;
  }

  void TypeCast::prepareDelete(bool tryOnVirtualParent){
    removeTypeOperand();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Unary::prepareDelete(false);
  }

  NodeKind TypeCast::getNodeKind() const {
    return ndkTypeCast;
  }

  expr::TypeExpression* TypeCast::getTypeOperand() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasTypeOperand != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasTypeOperand));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TypeCast::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeCast_HasTypeOperand:
        setTypeOperand(edgeEnd);
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
    if (expr::Unary::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TypeCast::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeCast_HasTypeOperand:
        removeTypeOperand();
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
    if (expr::Unary::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeCast::setTypeOperand(NodeId _id) {
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

      if (m_hasTypeOperand) {
        removeParentEdge(m_hasTypeOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTypeOperand, m_id, edkTypeCast_HasTypeOperand);
      }
      m_hasTypeOperand = _node->getId();
      if (m_hasTypeOperand != 0)
        setParentEdge(factory->getPointer(m_hasTypeOperand), edkTypeCast_HasTypeOperand);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTypeOperand, this->getId(), edkTypeCast_HasTypeOperand);
    } else {
      if (m_hasTypeOperand) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeCast::setTypeOperand(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTypeOperand(_node->getId());
  }

  void TypeCast::removeTypeOperand() {
      if (m_hasTypeOperand) {
        removeParentEdge(m_hasTypeOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTypeOperand, m_id, edkTypeCast_HasTypeOperand);
      }
      m_hasTypeOperand = 0;
  }

  void TypeCast::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeCast::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeCast::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const TypeCast& node = dynamic_cast<const TypeCast&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void TypeCast::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TypeCast::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::TypeCast", strlen("expr::TypeCast"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeCast::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Unary::sort(false);
  }

  void TypeCast::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Unary::save(binIo,false);

    binIo.writeUInt4(m_hasTypeOperand);

  }

  void TypeCast::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Unary::load(binIo,false);

    m_hasTypeOperand =  binIo.readUInt4();
    if (m_hasTypeOperand != 0)
      setParentEdge(factory->getPointer(m_hasTypeOperand),edkTypeCast_HasTypeOperand);

  }


}


}}}
