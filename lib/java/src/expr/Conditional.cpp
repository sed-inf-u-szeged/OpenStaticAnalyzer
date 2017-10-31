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
  Conditional::Conditional(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Expression(_id, _factory),
    m_colonPosition(),
    m_hasCondition(0),
    m_hasTrueExpression(0),
    m_hasFalseExpression(0)
  {
    m_colonPosition.posInfo.path = 0;
    m_colonPosition.posInfo.line = 0;
    m_colonPosition.posInfo.col = 0;
    m_colonPosition.posInfo.endLine = 0;
    m_colonPosition.posInfo.endCol = 0;
    m_colonPosition.posInfo.wideLine = 0;
    m_colonPosition.posInfo.wideCol = 0;
    m_colonPosition.posInfo.wideEndLine = 0;
    m_colonPosition.posInfo.wideEndCol = 0;
  }

  Conditional::~Conditional() {
  }

  void Conditional::clone(const Conditional& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Expression::clone(other, false);

    m_colonPosition.posInfo = other.m_colonPosition.posInfo;
    m_hasCondition = other.m_hasCondition;
    m_hasTrueExpression = other.m_hasTrueExpression;
    m_hasFalseExpression = other.m_hasFalseExpression;
  }

  void Conditional::prepareDelete(bool tryOnVirtualParent){
    removeCondition();
    removeTrueExpression();
    removeFalseExpression();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Expression::prepareDelete(false);
  }

  NodeKind Conditional::getNodeKind() const {
    return ndkConditional;
  }

  const Range Conditional::getColonPosition() const {
    return Range(factory->getStringTable(), m_colonPosition.posInfo);
  }

  int Conditional::compareByColonPosition(const Conditional& other) const {
    if (m_colonPosition.posInfo.path != other.m_colonPosition.posInfo.path) {
      return (m_colonPosition.posInfo.path < other.m_colonPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideLine != other.m_colonPosition.posInfo.wideLine) {
      return (m_colonPosition.posInfo.wideLine < other.m_colonPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideCol != other.m_colonPosition.posInfo.wideCol) {
      return (m_colonPosition.posInfo.wideCol < other.m_colonPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideEndLine != other.m_colonPosition.posInfo.wideEndLine) {
      return (m_colonPosition.posInfo.wideEndLine > other.m_colonPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideEndCol != other.m_colonPosition.posInfo.wideEndCol) {
      return (m_colonPosition.posInfo.wideEndCol > other.m_colonPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Conditional::setColonPosition(const Range& _colonPosition) {
    m_colonPosition.posInfo = _colonPosition.positionInfo;
    if (_colonPosition.strTable != &factory->getStringTable())
      m_colonPosition.posInfo.path = factory->getStringTable().set(_colonPosition.getPath());
  }

  expr::Expression* Conditional::getCondition() const {
    expr::Expression *_node = NULL;
    if (m_hasCondition != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasCondition));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expr::Expression* Conditional::getTrueExpression() const {
    expr::Expression *_node = NULL;
    if (m_hasTrueExpression != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasTrueExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expr::Expression* Conditional::getFalseExpression() const {
    expr::Expression *_node = NULL;
    if (m_hasFalseExpression != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasFalseExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Conditional::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConditional_HasCondition:
        setCondition(edgeEnd);
        return true;
      case edkConditional_HasTrueExpression:
        setTrueExpression(edgeEnd);
        return true;
      case edkConditional_HasFalseExpression:
        setFalseExpression(edgeEnd);
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

  bool Conditional::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConditional_HasCondition:
        removeCondition();
        return true;
      case edkConditional_HasTrueExpression:
        removeTrueExpression();
        return true;
      case edkConditional_HasFalseExpression:
        removeFalseExpression();
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

  void Conditional::setCondition(NodeId _id) {
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

      if (m_hasCondition) {
        removeParentEdge(m_hasCondition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkConditional_HasCondition);
      }
      m_hasCondition = _node->getId();
      if (m_hasCondition != 0)
        setParentEdge(factory->getPointer(m_hasCondition), edkConditional_HasCondition);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasCondition, this->getId(), edkConditional_HasCondition);
    } else {
      if (m_hasCondition) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Conditional::setCondition(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCondition(_node->getId());
  }

  void Conditional::removeCondition() {
      if (m_hasCondition) {
        removeParentEdge(m_hasCondition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkConditional_HasCondition);
      }
      m_hasCondition = 0;
  }

  void Conditional::setTrueExpression(NodeId _id) {
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

      if (m_hasTrueExpression) {
        removeParentEdge(m_hasTrueExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTrueExpression, m_id, edkConditional_HasTrueExpression);
      }
      m_hasTrueExpression = _node->getId();
      if (m_hasTrueExpression != 0)
        setParentEdge(factory->getPointer(m_hasTrueExpression), edkConditional_HasTrueExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTrueExpression, this->getId(), edkConditional_HasTrueExpression);
    } else {
      if (m_hasTrueExpression) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Conditional::setTrueExpression(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTrueExpression(_node->getId());
  }

  void Conditional::removeTrueExpression() {
      if (m_hasTrueExpression) {
        removeParentEdge(m_hasTrueExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTrueExpression, m_id, edkConditional_HasTrueExpression);
      }
      m_hasTrueExpression = 0;
  }

  void Conditional::setFalseExpression(NodeId _id) {
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

      if (m_hasFalseExpression) {
        removeParentEdge(m_hasFalseExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFalseExpression, m_id, edkConditional_HasFalseExpression);
      }
      m_hasFalseExpression = _node->getId();
      if (m_hasFalseExpression != 0)
        setParentEdge(factory->getPointer(m_hasFalseExpression), edkConditional_HasFalseExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFalseExpression, this->getId(), edkConditional_HasFalseExpression);
    } else {
      if (m_hasFalseExpression) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Conditional::setFalseExpression(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFalseExpression(_node->getId());
  }

  void Conditional::removeFalseExpression() {
      if (m_hasFalseExpression) {
        removeParentEdge(m_hasFalseExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFalseExpression, m_id, edkConditional_HasFalseExpression);
      }
      m_hasFalseExpression = 0;
  }

  void Conditional::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Conditional::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Conditional::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Conditional& node = dynamic_cast<const Conditional&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Conditional::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Conditional::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::Conditional", strlen("expr::Conditional"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Conditional::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Expression::sort(false);
  }

  void Conditional::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Expression::save(binIo,false);

    factory->getStringTable().setType(m_colonPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_colonPosition.posInfo.path);
    binIo.writeUInt4(m_colonPosition.posInfo.line);
    binIo.writeUInt4(m_colonPosition.posInfo.col);
    binIo.writeUInt4(m_colonPosition.posInfo.endLine);
    binIo.writeUInt4(m_colonPosition.posInfo.endCol);
    binIo.writeUInt4(m_colonPosition.posInfo.wideLine);
    binIo.writeUInt4(m_colonPosition.posInfo.wideCol);
    binIo.writeUInt4(m_colonPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_colonPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasCondition);
    binIo.writeUInt4(m_hasTrueExpression);
    binIo.writeUInt4(m_hasFalseExpression);

  }

  void Conditional::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Expression::load(binIo,false);

    m_colonPosition.posInfo.path = binIo.readUInt4();
    m_colonPosition.posInfo.line = binIo.readUInt4();
    m_colonPosition.posInfo.col = binIo.readUInt4();
    m_colonPosition.posInfo.endLine = binIo.readUInt4();
    m_colonPosition.posInfo.endCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasCondition =  binIo.readUInt4();
    if (m_hasCondition != 0)
      setParentEdge(factory->getPointer(m_hasCondition),edkConditional_HasCondition);

    m_hasTrueExpression =  binIo.readUInt4();
    if (m_hasTrueExpression != 0)
      setParentEdge(factory->getPointer(m_hasTrueExpression),edkConditional_HasTrueExpression);

    m_hasFalseExpression =  binIo.readUInt4();
    if (m_hasFalseExpression != 0)
      setParentEdge(factory->getPointer(m_hasFalseExpression),edkConditional_HasFalseExpression);

  }


}


}}}
