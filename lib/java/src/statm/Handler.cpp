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
  Handler::Handler(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Positioned(_id, _factory),
    m_leftParenPosition(),
    m_rightParenPosition(),
    m_hasParameter(0),
    m_hasBlock(0)
  {
    m_leftParenPosition.posInfo.path = 0;
    m_leftParenPosition.posInfo.line = 0;
    m_leftParenPosition.posInfo.col = 0;
    m_leftParenPosition.posInfo.endLine = 0;
    m_leftParenPosition.posInfo.endCol = 0;
    m_leftParenPosition.posInfo.wideLine = 0;
    m_leftParenPosition.posInfo.wideCol = 0;
    m_leftParenPosition.posInfo.wideEndLine = 0;
    m_leftParenPosition.posInfo.wideEndCol = 0;
    m_rightParenPosition.posInfo.path = 0;
    m_rightParenPosition.posInfo.line = 0;
    m_rightParenPosition.posInfo.col = 0;
    m_rightParenPosition.posInfo.endLine = 0;
    m_rightParenPosition.posInfo.endCol = 0;
    m_rightParenPosition.posInfo.wideLine = 0;
    m_rightParenPosition.posInfo.wideCol = 0;
    m_rightParenPosition.posInfo.wideEndLine = 0;
    m_rightParenPosition.posInfo.wideEndCol = 0;
  }

  Handler::~Handler() {
  }

  void Handler::clone(const Handler& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    base::Positioned::clone(other, false);

    m_leftParenPosition.posInfo = other.m_leftParenPosition.posInfo;
    m_rightParenPosition.posInfo = other.m_rightParenPosition.posInfo;
    m_hasParameter = other.m_hasParameter;
    m_hasBlock = other.m_hasBlock;
  }

  void Handler::prepareDelete(bool tryOnVirtualParent){
    removeParameter();
    removeBlock();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind Handler::getNodeKind() const {
    return ndkHandler;
  }

  const Range Handler::getLeftParenPosition() const {
    return Range(factory->getStringTable(), m_leftParenPosition.posInfo);
  }

  int Handler::compareByLeftParenPosition(const Handler& other) const {
    if (m_leftParenPosition.posInfo.path != other.m_leftParenPosition.posInfo.path) {
      return (m_leftParenPosition.posInfo.path < other.m_leftParenPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_leftParenPosition.posInfo.wideLine != other.m_leftParenPosition.posInfo.wideLine) {
      return (m_leftParenPosition.posInfo.wideLine < other.m_leftParenPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_leftParenPosition.posInfo.wideCol != other.m_leftParenPosition.posInfo.wideCol) {
      return (m_leftParenPosition.posInfo.wideCol < other.m_leftParenPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_leftParenPosition.posInfo.wideEndLine != other.m_leftParenPosition.posInfo.wideEndLine) {
      return (m_leftParenPosition.posInfo.wideEndLine > other.m_leftParenPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_leftParenPosition.posInfo.wideEndCol != other.m_leftParenPosition.posInfo.wideEndCol) {
      return (m_leftParenPosition.posInfo.wideEndCol > other.m_leftParenPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range Handler::getRightParenPosition() const {
    return Range(factory->getStringTable(), m_rightParenPosition.posInfo);
  }

  int Handler::compareByRightParenPosition(const Handler& other) const {
    if (m_rightParenPosition.posInfo.path != other.m_rightParenPosition.posInfo.path) {
      return (m_rightParenPosition.posInfo.path < other.m_rightParenPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_rightParenPosition.posInfo.wideLine != other.m_rightParenPosition.posInfo.wideLine) {
      return (m_rightParenPosition.posInfo.wideLine < other.m_rightParenPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_rightParenPosition.posInfo.wideCol != other.m_rightParenPosition.posInfo.wideCol) {
      return (m_rightParenPosition.posInfo.wideCol < other.m_rightParenPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_rightParenPosition.posInfo.wideEndLine != other.m_rightParenPosition.posInfo.wideEndLine) {
      return (m_rightParenPosition.posInfo.wideEndLine > other.m_rightParenPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_rightParenPosition.posInfo.wideEndCol != other.m_rightParenPosition.posInfo.wideEndCol) {
      return (m_rightParenPosition.posInfo.wideEndCol > other.m_rightParenPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Handler::setLeftParenPosition(const Range& _leftParenPosition) {
    m_leftParenPosition.posInfo = _leftParenPosition.positionInfo;
    if (_leftParenPosition.strTable != &factory->getStringTable())
      m_leftParenPosition.posInfo.path = factory->getStringTable().set(_leftParenPosition.getPath());
  }

  void Handler::setRightParenPosition(const Range& _rightParenPosition) {
    m_rightParenPosition.posInfo = _rightParenPosition.positionInfo;
    if (_rightParenPosition.strTable != &factory->getStringTable())
      m_rightParenPosition.posInfo.path = factory->getStringTable().set(_rightParenPosition.getPath());
  }

  struc::Parameter* Handler::getParameter() const {
    struc::Parameter *_node = NULL;
    if (m_hasParameter != 0)
      _node = dynamic_cast<struc::Parameter*>(factory->getPointer(m_hasParameter));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statm::Block* Handler::getBlock() const {
    statm::Block *_node = NULL;
    if (m_hasBlock != 0)
      _node = dynamic_cast<statm::Block*>(factory->getPointer(m_hasBlock));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Handler::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkHandler_HasParameter:
        setParameter(edgeEnd);
        return true;
      case edkHandler_HasBlock:
        setBlock(edgeEnd);
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
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Handler::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkHandler_HasParameter:
        removeParameter();
        return true;
      case edkHandler_HasBlock:
        removeBlock();
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
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Handler::setParameter(NodeId _id) {
    struc::Parameter *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::Parameter*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasParameter) {
        removeParentEdge(m_hasParameter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasParameter, m_id, edkHandler_HasParameter);
      }
      m_hasParameter = _node->getId();
      if (m_hasParameter != 0)
        setParentEdge(factory->getPointer(m_hasParameter), edkHandler_HasParameter);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasParameter, this->getId(), edkHandler_HasParameter);
    } else {
      if (m_hasParameter) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Handler::setParameter(struc::Parameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameter(_node->getId());
  }

  void Handler::removeParameter() {
      if (m_hasParameter) {
        removeParentEdge(m_hasParameter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasParameter, m_id, edkHandler_HasParameter);
      }
      m_hasParameter = 0;
  }

  void Handler::setBlock(NodeId _id) {
    statm::Block *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Block*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkHandler_HasBlock);
      }
      m_hasBlock = _node->getId();
      if (m_hasBlock != 0)
        setParentEdge(factory->getPointer(m_hasBlock), edkHandler_HasBlock);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBlock, this->getId(), edkHandler_HasBlock);
    } else {
      if (m_hasBlock) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Handler::setBlock(statm::Block *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBlock(_node->getId());
  }

  void Handler::removeBlock() {
      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkHandler_HasBlock);
      }
      m_hasBlock = 0;
  }

  void Handler::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Handler::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Handler::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Handler& node = dynamic_cast<const Handler&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Handler::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Handler::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Handler", strlen("statm::Handler"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Handler::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Positioned::sort(false);
  }

  void Handler::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Positioned::save(binIo,false);

    factory->getStringTable().setType(m_leftParenPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_leftParenPosition.posInfo.path);
    binIo.writeUInt4(m_leftParenPosition.posInfo.line);
    binIo.writeUInt4(m_leftParenPosition.posInfo.col);
    binIo.writeUInt4(m_leftParenPosition.posInfo.endLine);
    binIo.writeUInt4(m_leftParenPosition.posInfo.endCol);
    binIo.writeUInt4(m_leftParenPosition.posInfo.wideLine);
    binIo.writeUInt4(m_leftParenPosition.posInfo.wideCol);
    binIo.writeUInt4(m_leftParenPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_leftParenPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_rightParenPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_rightParenPosition.posInfo.path);
    binIo.writeUInt4(m_rightParenPosition.posInfo.line);
    binIo.writeUInt4(m_rightParenPosition.posInfo.col);
    binIo.writeUInt4(m_rightParenPosition.posInfo.endLine);
    binIo.writeUInt4(m_rightParenPosition.posInfo.endCol);
    binIo.writeUInt4(m_rightParenPosition.posInfo.wideLine);
    binIo.writeUInt4(m_rightParenPosition.posInfo.wideCol);
    binIo.writeUInt4(m_rightParenPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_rightParenPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasParameter);
    binIo.writeUInt4(m_hasBlock);

  }

  void Handler::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Positioned::load(binIo,false);

    m_leftParenPosition.posInfo.path = binIo.readUInt4();
    m_leftParenPosition.posInfo.line = binIo.readUInt4();
    m_leftParenPosition.posInfo.col = binIo.readUInt4();
    m_leftParenPosition.posInfo.endLine = binIo.readUInt4();
    m_leftParenPosition.posInfo.endCol = binIo.readUInt4();
    m_leftParenPosition.posInfo.wideLine = binIo.readUInt4();
    m_leftParenPosition.posInfo.wideCol = binIo.readUInt4();
    m_leftParenPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_leftParenPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_rightParenPosition.posInfo.path = binIo.readUInt4();
    m_rightParenPosition.posInfo.line = binIo.readUInt4();
    m_rightParenPosition.posInfo.col = binIo.readUInt4();
    m_rightParenPosition.posInfo.endLine = binIo.readUInt4();
    m_rightParenPosition.posInfo.endCol = binIo.readUInt4();
    m_rightParenPosition.posInfo.wideLine = binIo.readUInt4();
    m_rightParenPosition.posInfo.wideCol = binIo.readUInt4();
    m_rightParenPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_rightParenPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasParameter =  binIo.readUInt4();
    if (m_hasParameter != 0)
      setParentEdge(factory->getPointer(m_hasParameter),edkHandler_HasParameter);

    m_hasBlock =  binIo.readUInt4();
    if (m_hasBlock != 0)
      setParentEdge(factory->getPointer(m_hasBlock),edkHandler_HasBlock);

  }


}


}}}
