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

namespace base { 
  PositionedWithoutComment::PositionedWithoutComment(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_position()
  {
    m_position.posInfo.path = 0;
    m_position.posInfo.line = 0;
    m_position.posInfo.col = 0;
    m_position.posInfo.endLine = 0;
    m_position.posInfo.endCol = 0;
    m_position.posInfo.wideLine = 0;
    m_position.posInfo.wideCol = 0;
    m_position.posInfo.wideEndLine = 0;
    m_position.posInfo.wideEndCol = 0;
  }

  PositionedWithoutComment::~PositionedWithoutComment() {
  }

  void PositionedWithoutComment::clone(const PositionedWithoutComment& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }

    m_position.posInfo = other.m_position.posInfo;
  }

  void PositionedWithoutComment::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
  }

  const Range PositionedWithoutComment::getPosition() const {
    return Range(factory->getStringTable(), m_position.posInfo);
  }

  int PositionedWithoutComment::compareByPosition(const PositionedWithoutComment& other) const {
    if (m_position.posInfo.path != other.m_position.posInfo.path) {
      return (m_position.posInfo.path < other.m_position.posInfo.path) ? -1 :1 ;
    };
    if (m_position.posInfo.wideLine != other.m_position.posInfo.wideLine) {
      return (m_position.posInfo.wideLine < other.m_position.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_position.posInfo.wideCol != other.m_position.posInfo.wideCol) {
      return (m_position.posInfo.wideCol < other.m_position.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_position.posInfo.wideEndLine != other.m_position.posInfo.wideEndLine) {
      return (m_position.posInfo.wideEndLine > other.m_position.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_position.posInfo.wideEndCol != other.m_position.posInfo.wideEndCol) {
      return (m_position.posInfo.wideEndCol > other.m_position.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void PositionedWithoutComment::setPosition(const Range& _position) {
    m_position.posInfo = _position.positionInfo;
    if (_position.strTable != &factory->getStringTable())
      m_position.posInfo.path = factory->getStringTable().set(_position.getPath());
  }

  bool PositionedWithoutComment::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool PositionedWithoutComment::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  double PositionedWithoutComment::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void PositionedWithoutComment::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType PositionedWithoutComment::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::PositionedWithoutComment", strlen("base::PositionedWithoutComment"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void PositionedWithoutComment::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
  }

  void PositionedWithoutComment::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    factory->getStringTable().setType(m_position.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_position.posInfo.path);
    binIo.writeUInt4(m_position.posInfo.line);
    binIo.writeUInt4(m_position.posInfo.col);
    binIo.writeUInt4(m_position.posInfo.endLine);
    binIo.writeUInt4(m_position.posInfo.endCol);
    binIo.writeUInt4(m_position.posInfo.wideLine);
    binIo.writeUInt4(m_position.posInfo.wideCol);
    binIo.writeUInt4(m_position.posInfo.wideEndLine);
    binIo.writeUInt4(m_position.posInfo.wideEndCol);

  }

  void PositionedWithoutComment::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo,false);

    m_position.posInfo.path = binIo.readUInt4();
    m_position.posInfo.line = binIo.readUInt4();
    m_position.posInfo.col = binIo.readUInt4();
    m_position.posInfo.endLine = binIo.readUInt4();
    m_position.posInfo.endCol = binIo.readUInt4();
    m_position.posInfo.wideLine = binIo.readUInt4();
    m_position.posInfo.wideCol = binIo.readUInt4();
    m_position.posInfo.wideEndLine = binIo.readUInt4();
    m_position.posInfo.wideEndCol = binIo.readUInt4();

  }


}


}}}
