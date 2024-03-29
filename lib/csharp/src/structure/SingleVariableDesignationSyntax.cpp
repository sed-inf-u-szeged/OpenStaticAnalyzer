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

#include "csharp/inc/csharp.h"
#include "csharp/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "csharp/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace csharp { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace structure { 
  SingleVariableDesignationSyntax::SingleVariableDesignationSyntax(NodeId _id, Factory *_factory) :
    VariableDesignationSyntax(_id, _factory),
    m_identifier(0)
  {
  }

  SingleVariableDesignationSyntax::~SingleVariableDesignationSyntax() {
  }

  void SingleVariableDesignationSyntax::prepareDelete(bool tryOnVirtualParent){
    structure::VariableDesignationSyntax::prepareDelete(false);
  }

  NodeKind SingleVariableDesignationSyntax::getNodeKind() const {
    return ndkSingleVariableDesignationSyntax;
  }

  Key SingleVariableDesignationSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& SingleVariableDesignationSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void SingleVariableDesignationSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void SingleVariableDesignationSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  bool SingleVariableDesignationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (structure::VariableDesignationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SingleVariableDesignationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (structure::VariableDesignationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SingleVariableDesignationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SingleVariableDesignationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SingleVariableDesignationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const SingleVariableDesignationSyntax& node = dynamic_cast<const SingleVariableDesignationSyntax&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getIdentifier();
      str2 = node.getIdentifier();
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

  void SingleVariableDesignationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_identifier);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_identifier = foundKeyId->second;
    } else {
      Key oldkey = m_identifier;
      m_identifier = newStrTable.set(factory->getStringTable().get(m_identifier));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_identifier));    }

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType SingleVariableDesignationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::SingleVariableDesignationSyntax", strlen("structure::SingleVariableDesignationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SingleVariableDesignationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    VariableDesignationSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

  }

  void SingleVariableDesignationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    VariableDesignationSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

  }


}


}}}
