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

namespace struc { 
  Enum::Enum(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    TypeDeclaration(_id, _factory),
    m_semiPosition()
  {
    m_semiPosition.posInfo.path = 0;
    m_semiPosition.posInfo.line = 0;
    m_semiPosition.posInfo.col = 0;
    m_semiPosition.posInfo.endLine = 0;
    m_semiPosition.posInfo.endCol = 0;
    m_semiPosition.posInfo.wideLine = 0;
    m_semiPosition.posInfo.wideCol = 0;
    m_semiPosition.posInfo.wideEndLine = 0;
    m_semiPosition.posInfo.wideEndCol = 0;
  }

  Enum::~Enum() {
  }

  void Enum::clone(const Enum& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::TypeDeclaration::clone(other, false);

    m_semiPosition.posInfo = other.m_semiPosition.posInfo;
  }

  void Enum::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::TypeDeclaration::prepareDelete(false);
  }

  NodeKind Enum::getNodeKind() const {
    return ndkEnum;
  }

  const Range Enum::getSemiPosition() const {
    return Range(factory->getStringTable(), m_semiPosition.posInfo);
  }

  int Enum::compareBySemiPosition(const Enum& other) const {
    if (m_semiPosition.posInfo.path != other.m_semiPosition.posInfo.path) {
      return (m_semiPosition.posInfo.path < other.m_semiPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_semiPosition.posInfo.wideLine != other.m_semiPosition.posInfo.wideLine) {
      return (m_semiPosition.posInfo.wideLine < other.m_semiPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_semiPosition.posInfo.wideCol != other.m_semiPosition.posInfo.wideCol) {
      return (m_semiPosition.posInfo.wideCol < other.m_semiPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_semiPosition.posInfo.wideEndLine != other.m_semiPosition.posInfo.wideEndLine) {
      return (m_semiPosition.posInfo.wideEndLine > other.m_semiPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_semiPosition.posInfo.wideEndCol != other.m_semiPosition.posInfo.wideEndCol) {
      return (m_semiPosition.posInfo.wideEndCol > other.m_semiPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Enum::setSemiPosition(const Range& _semiPosition) {
    m_semiPosition.posInfo = _semiPosition.positionInfo;
    if (_semiPosition.strTable != &factory->getStringTable())
      m_semiPosition.posInfo.path = factory->getStringTable().set(_semiPosition.getPath());
  }

  bool Enum::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (struc::TypeDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Enum::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (struc::TypeDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Enum::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Enum::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Enum::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Enum& node = dynamic_cast<const Enum&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
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
      if(node.getAccessibility() == getAccessibility()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      if(node.getIsFinal() == getIsFinal()) ++matchAttrs;
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getIsStrictfp() == getIsStrictfp()) ++matchAttrs;
      str1 = getBinaryName();
      str2 = node.getBinaryName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (9 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Enum::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_binaryName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_binaryName = foundKeyId->second;
    } else {
      Key oldkey = m_binaryName;
      m_binaryName = newStrTable.set(factory->getStringTable().get(m_binaryName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_binaryName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Enum::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::Enum", strlen("struc::Enum"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Enum::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    TypeDeclaration::sort(false);
  }

  void Enum::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    TypeDeclaration::save(binIo,false);

    factory->getStringTable().setType(m_semiPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_semiPosition.posInfo.path);
    binIo.writeUInt4(m_semiPosition.posInfo.line);
    binIo.writeUInt4(m_semiPosition.posInfo.col);
    binIo.writeUInt4(m_semiPosition.posInfo.endLine);
    binIo.writeUInt4(m_semiPosition.posInfo.endCol);
    binIo.writeUInt4(m_semiPosition.posInfo.wideLine);
    binIo.writeUInt4(m_semiPosition.posInfo.wideCol);
    binIo.writeUInt4(m_semiPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_semiPosition.posInfo.wideEndCol);

  }

  void Enum::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    TypeDeclaration::load(binIo,false);

    m_semiPosition.posInfo.path = binIo.readUInt4();
    m_semiPosition.posInfo.line = binIo.readUInt4();
    m_semiPosition.posInfo.col = binIo.readUInt4();
    m_semiPosition.posInfo.endLine = binIo.readUInt4();
    m_semiPosition.posInfo.endCol = binIo.readUInt4();
    m_semiPosition.posInfo.wideLine = binIo.readUInt4();
    m_semiPosition.posInfo.wideCol = binIo.readUInt4();
    m_semiPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_semiPosition.posInfo.wideEndCol = binIo.readUInt4();

  }


}


}}}
