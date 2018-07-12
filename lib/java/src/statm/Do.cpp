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
  Do::Do(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Iteration(_id, _factory),
    m_whilePosition(),
    m_hasCondition(0)
  {
    m_whilePosition.posInfo.path = 0;
    m_whilePosition.posInfo.line = 0;
    m_whilePosition.posInfo.col = 0;
    m_whilePosition.posInfo.endLine = 0;
    m_whilePosition.posInfo.endCol = 0;
    m_whilePosition.posInfo.wideLine = 0;
    m_whilePosition.posInfo.wideCol = 0;
    m_whilePosition.posInfo.wideEndLine = 0;
    m_whilePosition.posInfo.wideEndCol = 0;
  }

  Do::~Do() {
  }

  void Do::clone(const Do& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Iteration::clone(other, false);

    m_whilePosition.posInfo = other.m_whilePosition.posInfo;
    m_hasCondition = other.m_hasCondition;
  }

  void Do::prepareDelete(bool tryOnVirtualParent){
    removeCondition();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Iteration::prepareDelete(false);
  }

  NodeKind Do::getNodeKind() const {
    return ndkDo;
  }

  const Range Do::getWhilePosition() const {
    return Range(factory->getStringTable(), m_whilePosition.posInfo);
  }

  int Do::compareByWhilePosition(const Do& other) const {
    if (m_whilePosition.posInfo.path != other.m_whilePosition.posInfo.path) {
      return (m_whilePosition.posInfo.path < other.m_whilePosition.posInfo.path) ? -1 :1 ;
    };
    if (m_whilePosition.posInfo.wideLine != other.m_whilePosition.posInfo.wideLine) {
      return (m_whilePosition.posInfo.wideLine < other.m_whilePosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_whilePosition.posInfo.wideCol != other.m_whilePosition.posInfo.wideCol) {
      return (m_whilePosition.posInfo.wideCol < other.m_whilePosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_whilePosition.posInfo.wideEndLine != other.m_whilePosition.posInfo.wideEndLine) {
      return (m_whilePosition.posInfo.wideEndLine > other.m_whilePosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_whilePosition.posInfo.wideEndCol != other.m_whilePosition.posInfo.wideEndCol) {
      return (m_whilePosition.posInfo.wideEndCol > other.m_whilePosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Do::setWhilePosition(const Range& _whilePosition) {
    m_whilePosition.posInfo = _whilePosition.positionInfo;
    if (_whilePosition.strTable != &factory->getStringTable())
      m_whilePosition.posInfo.path = factory->getStringTable().set(_whilePosition.getPath());
  }

  expr::Expression* Do::getCondition() const {
    expr::Expression *_node = NULL;
    if (m_hasCondition != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasCondition));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Do::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDo_HasCondition:
        setCondition(edgeEnd);
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
    if (statm::Iteration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Do::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDo_HasCondition:
        removeCondition();
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
    if (statm::Iteration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Do::setCondition(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkDo_HasCondition);
      }
      m_hasCondition = _node->getId();
      if (m_hasCondition != 0)
        setParentEdge(factory->getPointer(m_hasCondition), edkDo_HasCondition);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasCondition, this->getId(), edkDo_HasCondition);
    } else {
      if (m_hasCondition) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Do::setCondition(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCondition(_node->getId());
  }

  void Do::removeCondition() {
      if (m_hasCondition) {
        removeParentEdge(m_hasCondition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkDo_HasCondition);
      }
      m_hasCondition = 0;
  }

  void Do::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Do::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Do::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Do& node = dynamic_cast<const Do&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Do::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Do::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Do", strlen("statm::Do"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Do::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Iteration::sort(false);
  }

  void Do::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Iteration::save(binIo,false);

    factory->getStringTable().setType(m_whilePosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_whilePosition.posInfo.path);
    binIo.writeUInt4(m_whilePosition.posInfo.line);
    binIo.writeUInt4(m_whilePosition.posInfo.col);
    binIo.writeUInt4(m_whilePosition.posInfo.endLine);
    binIo.writeUInt4(m_whilePosition.posInfo.endCol);
    binIo.writeUInt4(m_whilePosition.posInfo.wideLine);
    binIo.writeUInt4(m_whilePosition.posInfo.wideCol);
    binIo.writeUInt4(m_whilePosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_whilePosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasCondition);

  }

  void Do::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Iteration::load(binIo,false);

    m_whilePosition.posInfo.path = binIo.readUInt4();
    m_whilePosition.posInfo.line = binIo.readUInt4();
    m_whilePosition.posInfo.col = binIo.readUInt4();
    m_whilePosition.posInfo.endLine = binIo.readUInt4();
    m_whilePosition.posInfo.endCol = binIo.readUInt4();
    m_whilePosition.posInfo.wideLine = binIo.readUInt4();
    m_whilePosition.posInfo.wideCol = binIo.readUInt4();
    m_whilePosition.posInfo.wideEndLine = binIo.readUInt4();
    m_whilePosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasCondition =  binIo.readUInt4();
    if (m_hasCondition != 0)
      setParentEdge(factory->getPointer(m_hasCondition),edkDo_HasCondition);

  }


}


}}}
