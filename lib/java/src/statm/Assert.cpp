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

namespace statm { 
  Assert::Assert(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Statement(_id, _factory),
    m_colonPosition(),
    m_hasCondition(0),
    m_hasDetail(0)
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

  Assert::~Assert() {
  }

  void Assert::clone(const Assert& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Statement::clone(other, false);

    m_colonPosition.posInfo = other.m_colonPosition.posInfo;
    m_hasCondition = other.m_hasCondition;
    m_hasDetail = other.m_hasDetail;
  }

  void Assert::prepareDelete(bool tryOnVirtualParent){
    removeCondition();
    removeDetail();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Statement::prepareDelete(false);
  }

  NodeKind Assert::getNodeKind() const {
    return ndkAssert;
  }

  const Range Assert::getColonPosition() const {
    return Range(factory->getStringTable(), m_colonPosition.posInfo);
  }

  int Assert::compareByColonPosition(const Assert& other) const {
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

  void Assert::setColonPosition(const Range& _colonPosition) {
    m_colonPosition.posInfo = _colonPosition.positionInfo;
    if (_colonPosition.strTable != &factory->getStringTable())
      m_colonPosition.posInfo.path = factory->getStringTable().set(_colonPosition.getPath());
  }

  expr::Expression* Assert::getCondition() const {
    expr::Expression *_node = NULL;
    if (m_hasCondition != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasCondition));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expr::Expression* Assert::getDetail() const {
    expr::Expression *_node = NULL;
    if (m_hasDetail != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasDetail));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Assert::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAssert_HasCondition:
        setCondition(edgeEnd);
        return true;
      case edkAssert_HasDetail:
        setDetail(edgeEnd);
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
    if (statm::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Assert::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAssert_HasCondition:
        removeCondition();
        return true;
      case edkAssert_HasDetail:
        removeDetail();
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
    if (statm::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Assert::setCondition(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkAssert_HasCondition);
      }
      m_hasCondition = _node->getId();
      if (m_hasCondition != 0)
        setParentEdge(factory->getPointer(m_hasCondition), edkAssert_HasCondition);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasCondition, this->getId(), edkAssert_HasCondition);
    } else {
      if (m_hasCondition) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Assert::setCondition(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCondition(_node->getId());
  }

  void Assert::removeCondition() {
      if (m_hasCondition) {
        removeParentEdge(m_hasCondition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkAssert_HasCondition);
      }
      m_hasCondition = 0;
  }

  void Assert::setDetail(NodeId _id) {
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

      if (m_hasDetail) {
        removeParentEdge(m_hasDetail);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDetail, m_id, edkAssert_HasDetail);
      }
      m_hasDetail = _node->getId();
      if (m_hasDetail != 0)
        setParentEdge(factory->getPointer(m_hasDetail), edkAssert_HasDetail);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasDetail, this->getId(), edkAssert_HasDetail);
    } else {
      if (m_hasDetail) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Assert::setDetail(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDetail(_node->getId());
  }

  void Assert::removeDetail() {
      if (m_hasDetail) {
        removeParentEdge(m_hasDetail);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDetail, m_id, edkAssert_HasDetail);
      }
      m_hasDetail = 0;
  }

  void Assert::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Assert::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Assert::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Assert& node = dynamic_cast<const Assert&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Assert::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Assert::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Assert", strlen("statm::Assert"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Assert::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Statement::sort(false);
  }

  void Assert::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Statement::save(binIo,false);

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
    binIo.writeUInt4(m_hasDetail);

  }

  void Assert::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Statement::load(binIo,false);

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
      setParentEdge(factory->getPointer(m_hasCondition),edkAssert_HasCondition);

    m_hasDetail =  binIo.readUInt4();
    if (m_hasDetail != 0)
      setParentEdge(factory->getPointer(m_hasDetail),edkAssert_HasDetail);

  }


}


}}}
