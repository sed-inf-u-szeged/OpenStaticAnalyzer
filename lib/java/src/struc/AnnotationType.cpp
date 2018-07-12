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
  AnnotationType::AnnotationType(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    TypeDeclaration(_id, _factory),
    m_atSignPosition()
  {
    m_atSignPosition.posInfo.path = 0;
    m_atSignPosition.posInfo.line = 0;
    m_atSignPosition.posInfo.col = 0;
    m_atSignPosition.posInfo.endLine = 0;
    m_atSignPosition.posInfo.endCol = 0;
    m_atSignPosition.posInfo.wideLine = 0;
    m_atSignPosition.posInfo.wideCol = 0;
    m_atSignPosition.posInfo.wideEndLine = 0;
    m_atSignPosition.posInfo.wideEndCol = 0;
  }

  AnnotationType::~AnnotationType() {
  }

  void AnnotationType::clone(const AnnotationType& other, bool tryOnVirtualParent) {
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

    m_atSignPosition.posInfo = other.m_atSignPosition.posInfo;
  }

  void AnnotationType::prepareDelete(bool tryOnVirtualParent){
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

  NodeKind AnnotationType::getNodeKind() const {
    return ndkAnnotationType;
  }

  const Range AnnotationType::getAtSignPosition() const {
    return Range(factory->getStringTable(), m_atSignPosition.posInfo);
  }

  int AnnotationType::compareByAtSignPosition(const AnnotationType& other) const {
    if (m_atSignPosition.posInfo.path != other.m_atSignPosition.posInfo.path) {
      return (m_atSignPosition.posInfo.path < other.m_atSignPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_atSignPosition.posInfo.wideLine != other.m_atSignPosition.posInfo.wideLine) {
      return (m_atSignPosition.posInfo.wideLine < other.m_atSignPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_atSignPosition.posInfo.wideCol != other.m_atSignPosition.posInfo.wideCol) {
      return (m_atSignPosition.posInfo.wideCol < other.m_atSignPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_atSignPosition.posInfo.wideEndLine != other.m_atSignPosition.posInfo.wideEndLine) {
      return (m_atSignPosition.posInfo.wideEndLine > other.m_atSignPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_atSignPosition.posInfo.wideEndCol != other.m_atSignPosition.posInfo.wideEndCol) {
      return (m_atSignPosition.posInfo.wideEndCol > other.m_atSignPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void AnnotationType::setAtSignPosition(const Range& _atSignPosition) {
    m_atSignPosition.posInfo = _atSignPosition.positionInfo;
    if (_atSignPosition.strTable != &factory->getStringTable())
      m_atSignPosition.posInfo.path = factory->getStringTable().set(_atSignPosition.getPath());
  }

  bool AnnotationType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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

  bool AnnotationType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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

  void AnnotationType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AnnotationType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AnnotationType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AnnotationType& node = dynamic_cast<const AnnotationType&>(base);
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

  void AnnotationType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType AnnotationType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::AnnotationType", strlen("struc::AnnotationType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnnotationType::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    TypeDeclaration::sort(false);
  }

  void AnnotationType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    TypeDeclaration::save(binIo,false);

    factory->getStringTable().setType(m_atSignPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_atSignPosition.posInfo.path);
    binIo.writeUInt4(m_atSignPosition.posInfo.line);
    binIo.writeUInt4(m_atSignPosition.posInfo.col);
    binIo.writeUInt4(m_atSignPosition.posInfo.endLine);
    binIo.writeUInt4(m_atSignPosition.posInfo.endCol);
    binIo.writeUInt4(m_atSignPosition.posInfo.wideLine);
    binIo.writeUInt4(m_atSignPosition.posInfo.wideCol);
    binIo.writeUInt4(m_atSignPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_atSignPosition.posInfo.wideEndCol);

  }

  void AnnotationType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    TypeDeclaration::load(binIo,false);

    m_atSignPosition.posInfo.path = binIo.readUInt4();
    m_atSignPosition.posInfo.line = binIo.readUInt4();
    m_atSignPosition.posInfo.col = binIo.readUInt4();
    m_atSignPosition.posInfo.endLine = binIo.readUInt4();
    m_atSignPosition.posInfo.endCol = binIo.readUInt4();
    m_atSignPosition.posInfo.wideLine = binIo.readUInt4();
    m_atSignPosition.posInfo.wideCol = binIo.readUInt4();
    m_atSignPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_atSignPosition.posInfo.wideEndCol = binIo.readUInt4();

  }


}


}}}
