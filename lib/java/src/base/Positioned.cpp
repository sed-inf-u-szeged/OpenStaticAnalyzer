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
  Positioned::Positioned(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
    Commentable(_id, _factory),
    PositionedWithoutComment(_id, _factory),
    m_isCompilerGenerated(false),
    m_isToolGenerated(false)
  {
  }

  Positioned::~Positioned() {
  }

  void Positioned::clone(const Positioned& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    base::PositionedWithoutComment::clone(other, false);

    m_isCompilerGenerated = other.m_isCompilerGenerated;
    m_isToolGenerated = other.m_isToolGenerated;
  }

  void Positioned::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    base::PositionedWithoutComment::prepareDelete(false);
  }

  bool Positioned::getIsCompilerGenerated() const {
    return m_isCompilerGenerated;
  }

  bool Positioned::getIsToolGenerated() const {
    return m_isToolGenerated;
  }

  void Positioned::setIsCompilerGenerated(bool _isCompilerGenerated) {
    m_isCompilerGenerated = _isCompilerGenerated;
  }

  void Positioned::setIsToolGenerated(bool _isToolGenerated) {
    m_isToolGenerated = _isToolGenerated;
  }

  bool Positioned::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (base::PositionedWithoutComment::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Positioned::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (base::PositionedWithoutComment::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  double Positioned::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Positioned& node = dynamic_cast<const Positioned&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Positioned::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Positioned::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::Positioned", strlen("base::Positioned"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Positioned::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    PositionedWithoutComment::sort(false);
  }

  void Positioned::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    PositionedWithoutComment::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isCompilerGenerated) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isToolGenerated) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

  }

  void Positioned::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo,false);

    PositionedWithoutComment::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isToolGenerated = boolValues & 1;
    boolValues >>= 1;
    m_isCompilerGenerated = boolValues & 1;
    boolValues >>= 1;

  }


}


}}}
