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

namespace base { 
  Named::Named(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_name(0),
    m_namePosition()
  {
    m_namePosition.posInfo.path = 0;
    m_namePosition.posInfo.line = 0;
    m_namePosition.posInfo.col = 0;
    m_namePosition.posInfo.endLine = 0;
    m_namePosition.posInfo.endCol = 0;
    m_namePosition.posInfo.wideLine = 0;
    m_namePosition.posInfo.wideCol = 0;
    m_namePosition.posInfo.wideEndLine = 0;
    m_namePosition.posInfo.wideEndCol = 0;
  }

  Named::~Named() {
  }

  void Named::clone(const Named& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }

    m_name = other.m_name;
    m_namePosition.posInfo = other.m_namePosition.posInfo;
  }

  void Named::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
  }

  Key Named::getNameKey() const {
    return m_name;
  }

  const std::string& Named::getName() const {
    return factory->getStringTable().get(m_name);
  }

  const Range Named::getNamePosition() const {
    return Range(factory->getStringTable(), m_namePosition.posInfo);
  }

  int Named::compareByNamePosition(const Named& other) const {
    if (m_namePosition.posInfo.path != other.m_namePosition.posInfo.path) {
      return (m_namePosition.posInfo.path < other.m_namePosition.posInfo.path) ? -1 :1 ;
    };
    if (m_namePosition.posInfo.wideLine != other.m_namePosition.posInfo.wideLine) {
      return (m_namePosition.posInfo.wideLine < other.m_namePosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_namePosition.posInfo.wideCol != other.m_namePosition.posInfo.wideCol) {
      return (m_namePosition.posInfo.wideCol < other.m_namePosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_namePosition.posInfo.wideEndLine != other.m_namePosition.posInfo.wideEndLine) {
      return (m_namePosition.posInfo.wideEndLine > other.m_namePosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_namePosition.posInfo.wideEndCol != other.m_namePosition.posInfo.wideEndCol) {
      return (m_namePosition.posInfo.wideEndCol > other.m_namePosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Named::setNameKey(Key _name) {
    m_name = _name;
  }

  void Named::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  void Named::setNamePosition(const Range& _namePosition) {
    m_namePosition.posInfo = _namePosition.positionInfo;
    if (_namePosition.strTable != &factory->getStringTable())
      m_namePosition.posInfo.path = factory->getStringTable().set(_namePosition.getPath());
  }

  bool Named::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool Named::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  double Named::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Named& node = dynamic_cast<const Named&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Named::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Named::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::Named", strlen("base::Named"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Named::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
  }

  void Named::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);
    factory->getStringTable().setType(m_namePosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_namePosition.posInfo.path);
    binIo.writeUInt4(m_namePosition.posInfo.line);
    binIo.writeUInt4(m_namePosition.posInfo.col);
    binIo.writeUInt4(m_namePosition.posInfo.endLine);
    binIo.writeUInt4(m_namePosition.posInfo.endCol);
    binIo.writeUInt4(m_namePosition.posInfo.wideLine);
    binIo.writeUInt4(m_namePosition.posInfo.wideCol);
    binIo.writeUInt4(m_namePosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_namePosition.posInfo.wideEndCol);

  }

  void Named::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo,false);

    m_name = binIo.readUInt4();
    m_namePosition.posInfo.path = binIo.readUInt4();
    m_namePosition.posInfo.line = binIo.readUInt4();
    m_namePosition.posInfo.col = binIo.readUInt4();
    m_namePosition.posInfo.endLine = binIo.readUInt4();
    m_namePosition.posInfo.endCol = binIo.readUInt4();
    m_namePosition.posInfo.wideLine = binIo.readUInt4();
    m_namePosition.posInfo.wideCol = binIo.readUInt4();
    m_namePosition.posInfo.wideEndLine = binIo.readUInt4();
    m_namePosition.posInfo.wideEndCol = binIo.readUInt4();

  }


}


}}}
