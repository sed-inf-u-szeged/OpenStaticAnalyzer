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

namespace struc { 
  StaticInitializerBlock::StaticInitializerBlock(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    InitializerBlock(_id, _factory),
    m_blockStartPosition()
  {
    m_blockStartPosition.posInfo.path = 0;
    m_blockStartPosition.posInfo.line = 0;
    m_blockStartPosition.posInfo.col = 0;
    m_blockStartPosition.posInfo.endLine = 0;
    m_blockStartPosition.posInfo.endCol = 0;
    m_blockStartPosition.posInfo.wideLine = 0;
    m_blockStartPosition.posInfo.wideCol = 0;
    m_blockStartPosition.posInfo.wideEndLine = 0;
    m_blockStartPosition.posInfo.wideEndCol = 0;
  }

  StaticInitializerBlock::~StaticInitializerBlock() {
  }

  void StaticInitializerBlock::clone(const StaticInitializerBlock& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::InitializerBlock::clone(other, false);

    m_blockStartPosition.posInfo = other.m_blockStartPosition.posInfo;
  }

  void StaticInitializerBlock::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::InitializerBlock::prepareDelete(false);
  }

  NodeKind StaticInitializerBlock::getNodeKind() const {
    return ndkStaticInitializerBlock;
  }

  const Range StaticInitializerBlock::getBlockStartPosition() const {
    return Range(factory->getStringTable(), m_blockStartPosition.posInfo);
  }

  int StaticInitializerBlock::compareByBlockStartPosition(const StaticInitializerBlock& other) const {
    if (m_blockStartPosition.posInfo.path != other.m_blockStartPosition.posInfo.path) {
      return (m_blockStartPosition.posInfo.path < other.m_blockStartPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideLine != other.m_blockStartPosition.posInfo.wideLine) {
      return (m_blockStartPosition.posInfo.wideLine < other.m_blockStartPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideCol != other.m_blockStartPosition.posInfo.wideCol) {
      return (m_blockStartPosition.posInfo.wideCol < other.m_blockStartPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideEndLine != other.m_blockStartPosition.posInfo.wideEndLine) {
      return (m_blockStartPosition.posInfo.wideEndLine > other.m_blockStartPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideEndCol != other.m_blockStartPosition.posInfo.wideEndCol) {
      return (m_blockStartPosition.posInfo.wideEndCol > other.m_blockStartPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void StaticInitializerBlock::setBlockStartPosition(const Range& _blockStartPosition) {
    m_blockStartPosition.posInfo = _blockStartPosition.positionInfo;
    if (_blockStartPosition.strTable != &factory->getStringTable())
      m_blockStartPosition.posInfo.path = factory->getStringTable().set(_blockStartPosition.getPath());
  }

  bool StaticInitializerBlock::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (tryOnVirtualParent) {
      if (struc::Member::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (struc::InitializerBlock::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool StaticInitializerBlock::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (tryOnVirtualParent) {
      if (struc::Member::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (struc::InitializerBlock::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void StaticInitializerBlock::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void StaticInitializerBlock::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double StaticInitializerBlock::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const StaticInitializerBlock& node = dynamic_cast<const StaticInitializerBlock&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void StaticInitializerBlock::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType StaticInitializerBlock::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::StaticInitializerBlock", strlen("struc::StaticInitializerBlock"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void StaticInitializerBlock::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    InitializerBlock::sort(false);
  }

  void StaticInitializerBlock::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    InitializerBlock::save(binIo,false);

    factory->getStringTable().setType(m_blockStartPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_blockStartPosition.posInfo.path);
    binIo.writeUInt4(m_blockStartPosition.posInfo.line);
    binIo.writeUInt4(m_blockStartPosition.posInfo.col);
    binIo.writeUInt4(m_blockStartPosition.posInfo.endLine);
    binIo.writeUInt4(m_blockStartPosition.posInfo.endCol);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideLine);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideCol);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideEndCol);

  }

  void StaticInitializerBlock::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    InitializerBlock::load(binIo,false);

    m_blockStartPosition.posInfo.path = binIo.readUInt4();
    m_blockStartPosition.posInfo.line = binIo.readUInt4();
    m_blockStartPosition.posInfo.col = binIo.readUInt4();
    m_blockStartPosition.posInfo.endLine = binIo.readUInt4();
    m_blockStartPosition.posInfo.endCol = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideLine = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideCol = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideEndCol = binIo.readUInt4();

  }


}


}}}
