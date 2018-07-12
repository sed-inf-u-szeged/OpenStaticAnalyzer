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
  If::If(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Selection(_id, _factory),
    m_elsePosition(),
    m_hasSubstatement(0),
    m_hasFalseSubstatement(0)
  {
    m_elsePosition.posInfo.path = 0;
    m_elsePosition.posInfo.line = 0;
    m_elsePosition.posInfo.col = 0;
    m_elsePosition.posInfo.endLine = 0;
    m_elsePosition.posInfo.endCol = 0;
    m_elsePosition.posInfo.wideLine = 0;
    m_elsePosition.posInfo.wideCol = 0;
    m_elsePosition.posInfo.wideEndLine = 0;
    m_elsePosition.posInfo.wideEndCol = 0;
  }

  If::~If() {
  }

  void If::clone(const If& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Selection::clone(other, false);

    m_elsePosition.posInfo = other.m_elsePosition.posInfo;
    m_hasSubstatement = other.m_hasSubstatement;
    m_hasFalseSubstatement = other.m_hasFalseSubstatement;
  }

  void If::prepareDelete(bool tryOnVirtualParent){
    removeSubstatement();
    removeFalseSubstatement();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Selection::prepareDelete(false);
  }

  NodeKind If::getNodeKind() const {
    return ndkIf;
  }

  const Range If::getElsePosition() const {
    return Range(factory->getStringTable(), m_elsePosition.posInfo);
  }

  int If::compareByElsePosition(const If& other) const {
    if (m_elsePosition.posInfo.path != other.m_elsePosition.posInfo.path) {
      return (m_elsePosition.posInfo.path < other.m_elsePosition.posInfo.path) ? -1 :1 ;
    };
    if (m_elsePosition.posInfo.wideLine != other.m_elsePosition.posInfo.wideLine) {
      return (m_elsePosition.posInfo.wideLine < other.m_elsePosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_elsePosition.posInfo.wideCol != other.m_elsePosition.posInfo.wideCol) {
      return (m_elsePosition.posInfo.wideCol < other.m_elsePosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_elsePosition.posInfo.wideEndLine != other.m_elsePosition.posInfo.wideEndLine) {
      return (m_elsePosition.posInfo.wideEndLine > other.m_elsePosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_elsePosition.posInfo.wideEndCol != other.m_elsePosition.posInfo.wideEndCol) {
      return (m_elsePosition.posInfo.wideEndCol > other.m_elsePosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void If::setElsePosition(const Range& _elsePosition) {
    m_elsePosition.posInfo = _elsePosition.positionInfo;
    if (_elsePosition.strTable != &factory->getStringTable())
      m_elsePosition.posInfo.path = factory->getStringTable().set(_elsePosition.getPath());
  }

  statm::Statement* If::getSubstatement() const {
    statm::Statement *_node = NULL;
    if (m_hasSubstatement != 0)
      _node = dynamic_cast<statm::Statement*>(factory->getPointer(m_hasSubstatement));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statm::Statement* If::getFalseSubstatement() const {
    statm::Statement *_node = NULL;
    if (m_hasFalseSubstatement != 0)
      _node = dynamic_cast<statm::Statement*>(factory->getPointer(m_hasFalseSubstatement));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool If::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIf_HasSubstatement:
        setSubstatement(edgeEnd);
        return true;
      case edkIf_HasFalseSubstatement:
        setFalseSubstatement(edgeEnd);
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
    if (statm::Selection::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool If::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIf_HasSubstatement:
        removeSubstatement();
        return true;
      case edkIf_HasFalseSubstatement:
        removeFalseSubstatement();
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
    if (statm::Selection::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void If::setSubstatement(NodeId _id) {
    statm::Statement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Statement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSubstatement) {
        removeParentEdge(m_hasSubstatement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSubstatement, m_id, edkIf_HasSubstatement);
      }
      m_hasSubstatement = _node->getId();
      if (m_hasSubstatement != 0)
        setParentEdge(factory->getPointer(m_hasSubstatement), edkIf_HasSubstatement);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSubstatement, this->getId(), edkIf_HasSubstatement);
    } else {
      if (m_hasSubstatement) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void If::setSubstatement(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSubstatement(_node->getId());
  }

  void If::removeSubstatement() {
      if (m_hasSubstatement) {
        removeParentEdge(m_hasSubstatement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSubstatement, m_id, edkIf_HasSubstatement);
      }
      m_hasSubstatement = 0;
  }

  void If::setFalseSubstatement(NodeId _id) {
    statm::Statement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Statement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasFalseSubstatement) {
        removeParentEdge(m_hasFalseSubstatement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFalseSubstatement, m_id, edkIf_HasFalseSubstatement);
      }
      m_hasFalseSubstatement = _node->getId();
      if (m_hasFalseSubstatement != 0)
        setParentEdge(factory->getPointer(m_hasFalseSubstatement), edkIf_HasFalseSubstatement);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFalseSubstatement, this->getId(), edkIf_HasFalseSubstatement);
    } else {
      if (m_hasFalseSubstatement) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void If::setFalseSubstatement(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFalseSubstatement(_node->getId());
  }

  void If::removeFalseSubstatement() {
      if (m_hasFalseSubstatement) {
        removeParentEdge(m_hasFalseSubstatement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFalseSubstatement, m_id, edkIf_HasFalseSubstatement);
      }
      m_hasFalseSubstatement = 0;
  }

  void If::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void If::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double If::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const If& node = dynamic_cast<const If&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void If::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType If::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::If", strlen("statm::If"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void If::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Selection::sort(false);
  }

  void If::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Selection::save(binIo,false);

    factory->getStringTable().setType(m_elsePosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_elsePosition.posInfo.path);
    binIo.writeUInt4(m_elsePosition.posInfo.line);
    binIo.writeUInt4(m_elsePosition.posInfo.col);
    binIo.writeUInt4(m_elsePosition.posInfo.endLine);
    binIo.writeUInt4(m_elsePosition.posInfo.endCol);
    binIo.writeUInt4(m_elsePosition.posInfo.wideLine);
    binIo.writeUInt4(m_elsePosition.posInfo.wideCol);
    binIo.writeUInt4(m_elsePosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_elsePosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasSubstatement);
    binIo.writeUInt4(m_hasFalseSubstatement);

  }

  void If::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Selection::load(binIo,false);

    m_elsePosition.posInfo.path = binIo.readUInt4();
    m_elsePosition.posInfo.line = binIo.readUInt4();
    m_elsePosition.posInfo.col = binIo.readUInt4();
    m_elsePosition.posInfo.endLine = binIo.readUInt4();
    m_elsePosition.posInfo.endCol = binIo.readUInt4();
    m_elsePosition.posInfo.wideLine = binIo.readUInt4();
    m_elsePosition.posInfo.wideCol = binIo.readUInt4();
    m_elsePosition.posInfo.wideEndLine = binIo.readUInt4();
    m_elsePosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasSubstatement =  binIo.readUInt4();
    if (m_hasSubstatement != 0)
      setParentEdge(factory->getPointer(m_hasSubstatement),edkIf_HasSubstatement);

    m_hasFalseSubstatement =  binIo.readUInt4();
    if (m_hasFalseSubstatement != 0)
      setParentEdge(factory->getPointer(m_hasFalseSubstatement),edkIf_HasFalseSubstatement);

  }


}


}}}
