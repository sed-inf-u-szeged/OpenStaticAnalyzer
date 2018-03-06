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

namespace expression { 
  IntegerLiteral::IntegerLiteral(NodeId _id, Factory *_factory) :
    Literal(_id, _factory),
    m_value(0)
  {
  }

  IntegerLiteral::~IntegerLiteral() {
  }

  void IntegerLiteral::prepareDelete(bool tryOnVirtualParent){
    expression::Literal::prepareDelete(false);
  }

  NodeKind IntegerLiteral::getNodeKind() const {
    return ndkIntegerLiteral;
  }

  int IntegerLiteral::getValue() const {
    return m_value;
  }

  void IntegerLiteral::setValue(int _value) {
    m_value = _value;
  }

  bool IntegerLiteral::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Literal::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool IntegerLiteral::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Literal::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void IntegerLiteral::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void IntegerLiteral::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double IntegerLiteral::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const IntegerLiteral& node = dynamic_cast<const IntegerLiteral&>(base);
      double matchAttrs = 0;
      if(node.getValue() == getValue()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void IntegerLiteral::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType IntegerLiteral::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::IntegerLiteral", strlen("expression::IntegerLiteral"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void IntegerLiteral::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Literal::save(binIo,false);

    binIo.writeUInt4(m_value);

  }

  void IntegerLiteral::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Literal::load(binIo,false);

    m_value = binIo.readUInt4();

  }


}


}}}
