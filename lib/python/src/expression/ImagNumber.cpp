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
  ImagNumber::ImagNumber(NodeId _id, Factory *_factory) :
    Literal(_id, _factory),
    m_im(0.0),
    m_real(0.0)
  {
  }

  ImagNumber::~ImagNumber() {
  }

  void ImagNumber::prepareDelete(bool tryOnVirtualParent){
    expression::Literal::prepareDelete(false);
  }

  NodeKind ImagNumber::getNodeKind() const {
    return ndkImagNumber;
  }

  double ImagNumber::getIm() const {
    return m_im;
  }

  double ImagNumber::getReal() const {
    return m_real;
  }

  void ImagNumber::setIm(double _im) {
    m_im = _im;
  }

  void ImagNumber::setReal(double _real) {
    m_real = _real;
  }

  bool ImagNumber::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Literal::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ImagNumber::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Literal::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ImagNumber::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ImagNumber::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ImagNumber::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ImagNumber& node = dynamic_cast<const ImagNumber&>(base);
      double matchAttrs = 0;
      if(node.getIm() == getIm()) ++matchAttrs;
      if(node.getReal() == getReal()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ImagNumber::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ImagNumber::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ImagNumber", strlen("expression::ImagNumber"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ImagNumber::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Literal::save(binIo,false);

    binIo.writeDouble8(m_im);
    binIo.writeDouble8(m_real);

  }

  void ImagNumber::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Literal::load(binIo,false);

    m_im = binIo.readDouble8();
    m_real = binIo.readDouble8();

  }


}


}}}
