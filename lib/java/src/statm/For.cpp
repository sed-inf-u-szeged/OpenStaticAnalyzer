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
  For::For(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Iteration(_id, _factory),
    m_leftParenPosition(),
    m_rightParenPosition()
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

  For::~For() {
  }

  void For::clone(const For& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Iteration::clone(other, false);

    m_leftParenPosition.posInfo = other.m_leftParenPosition.posInfo;
    m_rightParenPosition.posInfo = other.m_rightParenPosition.posInfo;
  }

  void For::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Iteration::prepareDelete(false);
  }

  const Range For::getLeftParenPosition() const {
    return Range(factory->getStringTable(), m_leftParenPosition.posInfo);
  }

  int For::compareByLeftParenPosition(const For& other) const {
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

  const Range For::getRightParenPosition() const {
    return Range(factory->getStringTable(), m_rightParenPosition.posInfo);
  }

  int For::compareByRightParenPosition(const For& other) const {
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

  void For::setLeftParenPosition(const Range& _leftParenPosition) {
    m_leftParenPosition.posInfo = _leftParenPosition.positionInfo;
    if (_leftParenPosition.strTable != &factory->getStringTable())
      m_leftParenPosition.posInfo.path = factory->getStringTable().set(_leftParenPosition.getPath());
  }

  void For::setRightParenPosition(const Range& _rightParenPosition) {
    m_rightParenPosition.posInfo = _rightParenPosition.positionInfo;
    if (_rightParenPosition.strTable != &factory->getStringTable())
      m_rightParenPosition.posInfo.path = factory->getStringTable().set(_rightParenPosition.getPath());
  }

  bool For::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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

  bool For::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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

  double For::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const For& node = dynamic_cast<const For&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void For::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType For::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::For", strlen("statm::For"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void For::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Iteration::sort(false);
  }

  void For::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Iteration::save(binIo,false);

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

  }

  void For::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Iteration::load(binIo,false);

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

  }


}


}}}
