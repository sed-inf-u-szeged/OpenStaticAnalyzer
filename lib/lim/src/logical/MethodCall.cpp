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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace logical { 
  MethodCall::MethodCall(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_calls(0),
    m_method(0)
  {
  }

  MethodCall::~MethodCall() {
  }

  void MethodCall::clone(const MethodCall& other, bool tryOnVirtualParent) {
    base::Base::clone(other, false);

    m_calls = other.m_calls;
    m_method = other.m_method;
  }

  void MethodCall::prepareDelete(bool tryOnVirtualParent){
    removeMethod();
    base::Base::prepareDelete(false);
  }

  NodeKind MethodCall::getNodeKind() const {
    return ndkMethodCall;
  }

  Key MethodCall::getCallsKey() const {
    return m_calls;
  }

  const std::string& MethodCall::getCalls() const {
    return factory->getStringTable().get(m_calls);
  }

  void MethodCall::setCallsKey(Key _calls) {
    m_calls = _calls;
  }

  void MethodCall::setCalls(const std::string& _calls) {
    m_calls = factory->getStringTable().set(_calls);
  }

  logical::Method* MethodCall::getMethod() const {
    logical::Method *_node = NULL;
    if (m_method != 0)
      _node = dynamic_cast<logical::Method*>(factory->getPointer(m_method));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool MethodCall::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodCall_Method:
        setMethod(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool MethodCall::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodCall_Method:
        removeMethod();
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MethodCall::setMethod(NodeId _id) {
    logical::Method *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<logical::Method*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_method) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_method, m_id, edkMethodCall_Method);
      }
      m_method = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_method, this->getId(), edkMethodCall_Method);
    } else {
      if (m_method) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodCall::setMethod(logical::Method *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setMethod(_node->getId());
  }

  void MethodCall::removeMethod() {
      if (m_method) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_method, m_id, edkMethodCall_Method);
      }
      m_method = 0;
  }

  void MethodCall::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MethodCall::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MethodCall::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const MethodCall& node = dynamic_cast<const MethodCall&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getCalls();
      str2 = node.getCalls();
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

  void MethodCall::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_calls);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_calls = foundKeyId->second;
    } else {
      Key oldkey = m_calls;
      m_calls = newStrTable.set(factory->getStringTable().get(m_calls));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_calls));    }

  }

  NodeHashType MethodCall::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::MethodCall", strlen("logical::MethodCall"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MethodCall::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_calls, StrTable::strToSave);
    binIo.writeUInt4(m_calls);

    binIo.writeUInt4(m_method);

  }

  void MethodCall::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_calls = binIo.readUInt4();

    m_method =  binIo.readUInt4();

  }


}


}}}
