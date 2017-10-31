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
  Binary::Binary(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Expression(_id, _factory),
    m_hasLeftOperand(0),
    m_hasRightOperand(0)
  {
  }

  Binary::~Binary() {
  }

  void Binary::clone(const Binary& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Expression::clone(other, false);

    m_hasLeftOperand = other.m_hasLeftOperand;
    m_hasRightOperand = other.m_hasRightOperand;
  }

  void Binary::prepareDelete(bool tryOnVirtualParent){
    removeLeftOperand();
    removeRightOperand();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Expression::prepareDelete(false);
  }

  expr::Expression* Binary::getLeftOperand() const {
    expr::Expression *_node = NULL;
    if (m_hasLeftOperand != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasLeftOperand));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expr::Expression* Binary::getRightOperand() const {
    expr::Expression *_node = NULL;
    if (m_hasRightOperand != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasRightOperand));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Binary::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBinary_HasLeftOperand:
        setLeftOperand(edgeEnd);
        return true;
      case edkBinary_HasRightOperand:
        setRightOperand(edgeEnd);
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
    if (expr::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Binary::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBinary_HasLeftOperand:
        removeLeftOperand();
        return true;
      case edkBinary_HasRightOperand:
        removeRightOperand();
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
    if (expr::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Binary::setLeftOperand(NodeId _id) {
    expr::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasLeftOperand) {
        removeParentEdge(m_hasLeftOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLeftOperand, m_id, edkBinary_HasLeftOperand);
      }
      m_hasLeftOperand = _node->getId();
      if (m_hasLeftOperand != 0)
        setParentEdge(factory->getPointer(m_hasLeftOperand), edkBinary_HasLeftOperand);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLeftOperand, this->getId(), edkBinary_HasLeftOperand);
    } else {
      if (m_hasLeftOperand) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Binary::setLeftOperand(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeftOperand(_node->getId());
  }

  void Binary::removeLeftOperand() {
      if (m_hasLeftOperand) {
        removeParentEdge(m_hasLeftOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLeftOperand, m_id, edkBinary_HasLeftOperand);
      }
      m_hasLeftOperand = 0;
  }

  void Binary::setRightOperand(NodeId _id) {
    expr::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasRightOperand) {
        removeParentEdge(m_hasRightOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRightOperand, m_id, edkBinary_HasRightOperand);
      }
      m_hasRightOperand = _node->getId();
      if (m_hasRightOperand != 0)
        setParentEdge(factory->getPointer(m_hasRightOperand), edkBinary_HasRightOperand);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasRightOperand, this->getId(), edkBinary_HasRightOperand);
    } else {
      if (m_hasRightOperand) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Binary::setRightOperand(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRightOperand(_node->getId());
  }

  void Binary::removeRightOperand() {
      if (m_hasRightOperand) {
        removeParentEdge(m_hasRightOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRightOperand, m_id, edkBinary_HasRightOperand);
      }
      m_hasRightOperand = 0;
  }

  double Binary::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Binary& node = dynamic_cast<const Binary&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Binary::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Binary::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::Binary", strlen("expr::Binary"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Binary::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Expression::sort(false);
  }

  void Binary::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasLeftOperand);
    binIo.writeUInt4(m_hasRightOperand);

  }

  void Binary::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Expression::load(binIo,false);

    m_hasLeftOperand =  binIo.readUInt4();
    if (m_hasLeftOperand != 0)
      setParentEdge(factory->getPointer(m_hasLeftOperand),edkBinary_HasLeftOperand);

    m_hasRightOperand =  binIo.readUInt4();
    if (m_hasRightOperand != 0)
      setParentEdge(factory->getPointer(m_hasRightOperand),edkBinary_HasRightOperand);

  }


}


}}}
