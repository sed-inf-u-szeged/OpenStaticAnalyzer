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
  Parameter::Parameter(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    VariableDeclaration(_id, _factory),
    m_isVarargs(false),
    m_varargsPosition()
  {
    m_varargsPosition.posInfo.path = 0;
    m_varargsPosition.posInfo.line = 0;
    m_varargsPosition.posInfo.col = 0;
    m_varargsPosition.posInfo.endLine = 0;
    m_varargsPosition.posInfo.endCol = 0;
    m_varargsPosition.posInfo.wideLine = 0;
    m_varargsPosition.posInfo.wideCol = 0;
    m_varargsPosition.posInfo.wideEndLine = 0;
    m_varargsPosition.posInfo.wideEndCol = 0;
  }

  Parameter::~Parameter() {
  }

  void Parameter::clone(const Parameter& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::VariableDeclaration::clone(other, false);

    m_isVarargs = other.m_isVarargs;
    m_varargsPosition.posInfo = other.m_varargsPosition.posInfo;
  }

  void Parameter::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::VariableDeclaration::prepareDelete(false);
  }

  NodeKind Parameter::getNodeKind() const {
    return ndkParameter;
  }

  bool Parameter::getIsVarargs() const {
    return m_isVarargs;
  }

  const Range Parameter::getVarargsPosition() const {
    return Range(factory->getStringTable(), m_varargsPosition.posInfo);
  }

  int Parameter::compareByVarargsPosition(const Parameter& other) const {
    if (m_varargsPosition.posInfo.path != other.m_varargsPosition.posInfo.path) {
      return (m_varargsPosition.posInfo.path < other.m_varargsPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_varargsPosition.posInfo.wideLine != other.m_varargsPosition.posInfo.wideLine) {
      return (m_varargsPosition.posInfo.wideLine < other.m_varargsPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_varargsPosition.posInfo.wideCol != other.m_varargsPosition.posInfo.wideCol) {
      return (m_varargsPosition.posInfo.wideCol < other.m_varargsPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_varargsPosition.posInfo.wideEndLine != other.m_varargsPosition.posInfo.wideEndLine) {
      return (m_varargsPosition.posInfo.wideEndLine > other.m_varargsPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_varargsPosition.posInfo.wideEndCol != other.m_varargsPosition.posInfo.wideEndCol) {
      return (m_varargsPosition.posInfo.wideEndCol > other.m_varargsPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Parameter::setIsVarargs(bool _isVarargs) {
    m_isVarargs = _isVarargs;
  }

  void Parameter::setVarargsPosition(const Range& _varargsPosition) {
    m_varargsPosition.posInfo = _varargsPosition.positionInfo;
    if (_varargsPosition.strTable != &factory->getStringTable())
      m_varargsPosition.posInfo.path = factory->getStringTable().set(_varargsPosition.getPath());
  }

  bool Parameter::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (struc::VariableDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Parameter::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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
    if (struc::VariableDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Parameter::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Parameter::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Parameter::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Parameter& node = dynamic_cast<const Parameter&>(base);
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
      if(node.getIsVarargs() == getIsVarargs()) ++matchAttrs;
      return matchAttrs / (7 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Parameter::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Parameter::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::Parameter", strlen("struc::Parameter"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Parameter::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    VariableDeclaration::sort(false);
  }

  void Parameter::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    VariableDeclaration::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isVarargs) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    factory->getStringTable().setType(m_varargsPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_varargsPosition.posInfo.path);
    binIo.writeUInt4(m_varargsPosition.posInfo.line);
    binIo.writeUInt4(m_varargsPosition.posInfo.col);
    binIo.writeUInt4(m_varargsPosition.posInfo.endLine);
    binIo.writeUInt4(m_varargsPosition.posInfo.endCol);
    binIo.writeUInt4(m_varargsPosition.posInfo.wideLine);
    binIo.writeUInt4(m_varargsPosition.posInfo.wideCol);
    binIo.writeUInt4(m_varargsPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_varargsPosition.posInfo.wideEndCol);

  }

  void Parameter::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    VariableDeclaration::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isVarargs = boolValues & 1;
    boolValues >>= 1;
    m_varargsPosition.posInfo.path = binIo.readUInt4();
    m_varargsPosition.posInfo.line = binIo.readUInt4();
    m_varargsPosition.posInfo.col = binIo.readUInt4();
    m_varargsPosition.posInfo.endLine = binIo.readUInt4();
    m_varargsPosition.posInfo.endCol = binIo.readUInt4();
    m_varargsPosition.posInfo.wideLine = binIo.readUInt4();
    m_varargsPosition.posInfo.wideCol = binIo.readUInt4();
    m_varargsPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_varargsPosition.posInfo.wideEndCol = binIo.readUInt4();

  }


}


}}}
