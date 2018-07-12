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

#include "genealogy/inc/genealogy.h"
#include "genealogy/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "genealogy/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace genealogy { 

typedef boost::crc_32_type  Crc_type;

  SourceCodeElement::SourceCodeElement(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_line(0),
    m_col(0),
    m_endLine(0),
    m_endCol(0),
    m_path(0)
  {
  }

  SourceCodeElement::~SourceCodeElement() {
  }

  void SourceCodeElement::prepareDelete(bool tryOnVirtualParent){
    Base::prepareDelete(false);
  }

  NodeKind SourceCodeElement::getNodeKind() const {
    return ndkSourceCodeElement;
  }

  Key SourceCodeElement::getPathKey() const {
    return m_path;
  }

  const std::string& SourceCodeElement::getPath() const {
    return factory->getStringTable().get(m_path);
  }

  unsigned SourceCodeElement::getLine() const {
    return m_line;
  }

  unsigned SourceCodeElement::getCol() const {
    return m_col;
  }

  unsigned SourceCodeElement::getEndLine() const {
    return m_endLine;
  }

  unsigned SourceCodeElement::getEndCol() const {
    return m_endCol;
  }

  void SourceCodeElement::setPathKey(Key _path) {
    m_path = _path;
  }

  void SourceCodeElement::setPath(const std::string& _path) {
    m_path = factory->getStringTable().set(_path);
  }

  void SourceCodeElement::setLine(unsigned _line) {
    m_line = _line;
  }

  void SourceCodeElement::setCol(unsigned _col) {
    m_col = _col;
  }

  void SourceCodeElement::setEndLine(unsigned _endLine) {
    m_endLine = _endLine;
  }

  void SourceCodeElement::setEndCol(unsigned _endCol) {
    m_endCol = _endCol;
  }

  bool SourceCodeElement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SourceCodeElement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SourceCodeElement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SourceCodeElement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SourceCodeElement::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const SourceCodeElement& node = dynamic_cast<const SourceCodeElement&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getPath();
      str2 = node.getPath();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getLine() == getLine()) ++matchAttrs;
      if(node.getCol() == getCol()) ++matchAttrs;
      if(node.getEndLine() == getEndLine()) ++matchAttrs;
      if(node.getEndCol() == getEndCol()) ++matchAttrs;
      return matchAttrs / (5 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void SourceCodeElement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_path);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_path = foundKeyId->second;
    } else {
      Key oldkey = m_path;
      m_path = newStrTable.set(factory->getStringTable().get(m_path));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_path));    }

  }

  NodeHashType SourceCodeElement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "SourceCodeElement", strlen("SourceCodeElement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SourceCodeElement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_path, StrTable::strToSave);
    binIo.writeUInt4(m_path);
    binIo.writeUInt4(m_line);
    binIo.writeUInt4(m_col);
    binIo.writeUInt4(m_endLine);
    binIo.writeUInt4(m_endCol);

  }

  void SourceCodeElement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_path = binIo.readUInt4();
    m_line = binIo.readUInt4();
    m_col = binIo.readUInt4();
    m_endLine = binIo.readUInt4();
    m_endCol = binIo.readUInt4();

  }



}}
