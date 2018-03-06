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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statement { 
  ImportFrom::ImportFrom(NodeId _id, Factory *_factory) :
    ImportStatement(_id, _factory),
    m_level(0),
    m_modulname(0)
  {
  }

  ImportFrom::~ImportFrom() {
  }

  void ImportFrom::prepareDelete(bool tryOnVirtualParent){
    statement::ImportStatement::prepareDelete(false);
  }

  NodeKind ImportFrom::getNodeKind() const {
    return ndkImportFrom;
  }

  Key ImportFrom::getModulnameKey() const {
    return m_modulname;
  }

  const std::string& ImportFrom::getModulname() const {
    return factory->getStringTable().get(m_modulname);
  }

  int ImportFrom::getLevel() const {
    return m_level;
  }

  void ImportFrom::setModulnameKey(Key _modulname) {
    m_modulname = _modulname;
  }

  void ImportFrom::setModulname(const std::string& _modulname) {
    m_modulname = factory->getStringTable().set(_modulname);
  }

  void ImportFrom::setLevel(int _level) {
    m_level = _level;
  }

  bool ImportFrom::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (statement::ImportStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ImportFrom::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (statement::ImportStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ImportFrom::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ImportFrom::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ImportFrom::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ImportFrom& node = dynamic_cast<const ImportFrom&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getModulname();
      str2 = node.getModulname();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getLevel() == getLevel()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ImportFrom::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_modulname);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_modulname = foundKeyId->second;
    } else {
      Key oldkey = m_modulname;
      m_modulname = newStrTable.set(factory->getStringTable().get(m_modulname));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_modulname));    }

  }

  NodeHashType ImportFrom::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ImportFrom", strlen("statement::ImportFrom"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ImportFrom::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ImportStatement::save(binIo,false);

    factory->getStringTable().setType(m_modulname, StrTable::strToSave);
    binIo.writeUInt4(m_modulname);
    binIo.writeUInt4(m_level);

  }

  void ImportFrom::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ImportStatement::load(binIo,false);

    m_modulname = binIo.readUInt4();
    m_level = binIo.readUInt4();

  }


}


}}}
