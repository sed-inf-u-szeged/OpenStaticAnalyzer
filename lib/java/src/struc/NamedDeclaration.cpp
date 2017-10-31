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
  NamedDeclaration::NamedDeclaration(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    Declaration(_id, _factory),
    Named(_id, _factory),
    m_isStatic(false),
    m_isFinal(false),
    m_accessibility(ackNone),
    m_accessibilityPosition(),
    m_staticPosition(),
    m_finalPosition()
  {
    m_accessibilityPosition.posInfo.path = 0;
    m_accessibilityPosition.posInfo.line = 0;
    m_accessibilityPosition.posInfo.col = 0;
    m_accessibilityPosition.posInfo.endLine = 0;
    m_accessibilityPosition.posInfo.endCol = 0;
    m_accessibilityPosition.posInfo.wideLine = 0;
    m_accessibilityPosition.posInfo.wideCol = 0;
    m_accessibilityPosition.posInfo.wideEndLine = 0;
    m_accessibilityPosition.posInfo.wideEndCol = 0;
    m_staticPosition.posInfo.path = 0;
    m_staticPosition.posInfo.line = 0;
    m_staticPosition.posInfo.col = 0;
    m_staticPosition.posInfo.endLine = 0;
    m_staticPosition.posInfo.endCol = 0;
    m_staticPosition.posInfo.wideLine = 0;
    m_staticPosition.posInfo.wideCol = 0;
    m_staticPosition.posInfo.wideEndLine = 0;
    m_staticPosition.posInfo.wideEndCol = 0;
    m_finalPosition.posInfo.path = 0;
    m_finalPosition.posInfo.line = 0;
    m_finalPosition.posInfo.col = 0;
    m_finalPosition.posInfo.endLine = 0;
    m_finalPosition.posInfo.endCol = 0;
    m_finalPosition.posInfo.wideLine = 0;
    m_finalPosition.posInfo.wideCol = 0;
    m_finalPosition.posInfo.wideEndLine = 0;
    m_finalPosition.posInfo.wideEndCol = 0;
  }

  NamedDeclaration::~NamedDeclaration() {
  }

  void NamedDeclaration::clone(const NamedDeclaration& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::Declaration::clone(other, false);
    base::Named::clone(other, false);

    m_accessibility = other.m_accessibility;
    m_accessibilityPosition.posInfo = other.m_accessibilityPosition.posInfo;
    m_isStatic = other.m_isStatic;
    m_staticPosition.posInfo = other.m_staticPosition.posInfo;
    m_isFinal = other.m_isFinal;
    m_finalPosition.posInfo = other.m_finalPosition.posInfo;
  }

  void NamedDeclaration::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::Declaration::prepareDelete(false);
    base::Named::prepareDelete(false);
  }

  AccessibilityKind NamedDeclaration::getAccessibility() const {
    return m_accessibility;
  }

  const Range NamedDeclaration::getAccessibilityPosition() const {
    return Range(factory->getStringTable(), m_accessibilityPosition.posInfo);
  }

  int NamedDeclaration::compareByAccessibilityPosition(const NamedDeclaration& other) const {
    if (m_accessibilityPosition.posInfo.path != other.m_accessibilityPosition.posInfo.path) {
      return (m_accessibilityPosition.posInfo.path < other.m_accessibilityPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_accessibilityPosition.posInfo.wideLine != other.m_accessibilityPosition.posInfo.wideLine) {
      return (m_accessibilityPosition.posInfo.wideLine < other.m_accessibilityPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_accessibilityPosition.posInfo.wideCol != other.m_accessibilityPosition.posInfo.wideCol) {
      return (m_accessibilityPosition.posInfo.wideCol < other.m_accessibilityPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_accessibilityPosition.posInfo.wideEndLine != other.m_accessibilityPosition.posInfo.wideEndLine) {
      return (m_accessibilityPosition.posInfo.wideEndLine > other.m_accessibilityPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_accessibilityPosition.posInfo.wideEndCol != other.m_accessibilityPosition.posInfo.wideEndCol) {
      return (m_accessibilityPosition.posInfo.wideEndCol > other.m_accessibilityPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  bool NamedDeclaration::getIsStatic() const {
    return m_isStatic;
  }

  const Range NamedDeclaration::getStaticPosition() const {
    return Range(factory->getStringTable(), m_staticPosition.posInfo);
  }

  int NamedDeclaration::compareByStaticPosition(const NamedDeclaration& other) const {
    if (m_staticPosition.posInfo.path != other.m_staticPosition.posInfo.path) {
      return (m_staticPosition.posInfo.path < other.m_staticPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideLine != other.m_staticPosition.posInfo.wideLine) {
      return (m_staticPosition.posInfo.wideLine < other.m_staticPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideCol != other.m_staticPosition.posInfo.wideCol) {
      return (m_staticPosition.posInfo.wideCol < other.m_staticPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideEndLine != other.m_staticPosition.posInfo.wideEndLine) {
      return (m_staticPosition.posInfo.wideEndLine > other.m_staticPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideEndCol != other.m_staticPosition.posInfo.wideEndCol) {
      return (m_staticPosition.posInfo.wideEndCol > other.m_staticPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  bool NamedDeclaration::getIsFinal() const {
    return m_isFinal;
  }

  const Range NamedDeclaration::getFinalPosition() const {
    return Range(factory->getStringTable(), m_finalPosition.posInfo);
  }

  int NamedDeclaration::compareByFinalPosition(const NamedDeclaration& other) const {
    if (m_finalPosition.posInfo.path != other.m_finalPosition.posInfo.path) {
      return (m_finalPosition.posInfo.path < other.m_finalPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_finalPosition.posInfo.wideLine != other.m_finalPosition.posInfo.wideLine) {
      return (m_finalPosition.posInfo.wideLine < other.m_finalPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_finalPosition.posInfo.wideCol != other.m_finalPosition.posInfo.wideCol) {
      return (m_finalPosition.posInfo.wideCol < other.m_finalPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_finalPosition.posInfo.wideEndLine != other.m_finalPosition.posInfo.wideEndLine) {
      return (m_finalPosition.posInfo.wideEndLine > other.m_finalPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_finalPosition.posInfo.wideEndCol != other.m_finalPosition.posInfo.wideEndCol) {
      return (m_finalPosition.posInfo.wideEndCol > other.m_finalPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void NamedDeclaration::setAccessibility(AccessibilityKind _accessibility) {
    m_accessibility = _accessibility;
  }

  void NamedDeclaration::setAccessibilityPosition(const Range& _accessibilityPosition) {
    m_accessibilityPosition.posInfo = _accessibilityPosition.positionInfo;
    if (_accessibilityPosition.strTable != &factory->getStringTable())
      m_accessibilityPosition.posInfo.path = factory->getStringTable().set(_accessibilityPosition.getPath());
  }

  void NamedDeclaration::setIsStatic(bool _isStatic) {
    m_isStatic = _isStatic;
  }

  void NamedDeclaration::setStaticPosition(const Range& _staticPosition) {
    m_staticPosition.posInfo = _staticPosition.positionInfo;
    if (_staticPosition.strTable != &factory->getStringTable())
      m_staticPosition.posInfo.path = factory->getStringTable().set(_staticPosition.getPath());
  }

  void NamedDeclaration::setIsFinal(bool _isFinal) {
    m_isFinal = _isFinal;
  }

  void NamedDeclaration::setFinalPosition(const Range& _finalPosition) {
    m_finalPosition.posInfo = _finalPosition.positionInfo;
    if (_finalPosition.strTable != &factory->getStringTable())
      m_finalPosition.posInfo.path = factory->getStringTable().set(_finalPosition.getPath());
  }

  bool NamedDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (struc::Declaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NamedDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (struc::Declaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  double NamedDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const NamedDeclaration& node = dynamic_cast<const NamedDeclaration&>(base);
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
      return matchAttrs / (6 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void NamedDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType NamedDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::NamedDeclaration", strlen("struc::NamedDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NamedDeclaration::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    Declaration::sort(false);
    Named::sort(false);
  }

  void NamedDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    Declaration::save(binIo,false);

    Named::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isStatic) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isFinal) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUByte1(m_accessibility);
    factory->getStringTable().setType(m_accessibilityPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.path);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.line);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.col);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.endLine);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.endCol);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.wideLine);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.wideCol);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_accessibilityPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_staticPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_staticPosition.posInfo.path);
    binIo.writeUInt4(m_staticPosition.posInfo.line);
    binIo.writeUInt4(m_staticPosition.posInfo.col);
    binIo.writeUInt4(m_staticPosition.posInfo.endLine);
    binIo.writeUInt4(m_staticPosition.posInfo.endCol);
    binIo.writeUInt4(m_staticPosition.posInfo.wideLine);
    binIo.writeUInt4(m_staticPosition.posInfo.wideCol);
    binIo.writeUInt4(m_staticPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_staticPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_finalPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_finalPosition.posInfo.path);
    binIo.writeUInt4(m_finalPosition.posInfo.line);
    binIo.writeUInt4(m_finalPosition.posInfo.col);
    binIo.writeUInt4(m_finalPosition.posInfo.endLine);
    binIo.writeUInt4(m_finalPosition.posInfo.endCol);
    binIo.writeUInt4(m_finalPosition.posInfo.wideLine);
    binIo.writeUInt4(m_finalPosition.posInfo.wideCol);
    binIo.writeUInt4(m_finalPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_finalPosition.posInfo.wideEndCol);

  }

  void NamedDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    Declaration::load(binIo,false);

    Named::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isFinal = boolValues & 1;
    boolValues >>= 1;
    m_isStatic = boolValues & 1;
    boolValues >>= 1;
    m_accessibility = (AccessibilityKind)binIo.readUByte1();
    m_accessibilityPosition.posInfo.path = binIo.readUInt4();
    m_accessibilityPosition.posInfo.line = binIo.readUInt4();
    m_accessibilityPosition.posInfo.col = binIo.readUInt4();
    m_accessibilityPosition.posInfo.endLine = binIo.readUInt4();
    m_accessibilityPosition.posInfo.endCol = binIo.readUInt4();
    m_accessibilityPosition.posInfo.wideLine = binIo.readUInt4();
    m_accessibilityPosition.posInfo.wideCol = binIo.readUInt4();
    m_accessibilityPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_accessibilityPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_staticPosition.posInfo.path = binIo.readUInt4();
    m_staticPosition.posInfo.line = binIo.readUInt4();
    m_staticPosition.posInfo.col = binIo.readUInt4();
    m_staticPosition.posInfo.endLine = binIo.readUInt4();
    m_staticPosition.posInfo.endCol = binIo.readUInt4();
    m_staticPosition.posInfo.wideLine = binIo.readUInt4();
    m_staticPosition.posInfo.wideCol = binIo.readUInt4();
    m_staticPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_staticPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_finalPosition.posInfo.path = binIo.readUInt4();
    m_finalPosition.posInfo.line = binIo.readUInt4();
    m_finalPosition.posInfo.col = binIo.readUInt4();
    m_finalPosition.posInfo.endLine = binIo.readUInt4();
    m_finalPosition.posInfo.endCol = binIo.readUInt4();
    m_finalPosition.posInfo.wideLine = binIo.readUInt4();
    m_finalPosition.posInfo.wideCol = binIo.readUInt4();
    m_finalPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_finalPosition.posInfo.wideEndCol = binIo.readUInt4();

  }


}


}}}
