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
  TryFinal::TryFinal(NodeId _id, Factory *_factory) :
    Try(_id, _factory),
    m_hasFinallyBody(0)
  {
  }

  TryFinal::~TryFinal() {
  }

  void TryFinal::prepareDelete(bool tryOnVirtualParent){
    removeFinallyBody();
    statement::Try::prepareDelete(false);
  }

  NodeKind TryFinal::getNodeKind() const {
    return ndkTryFinal;
  }

  statement::Suite* TryFinal::getFinallyBody() const {
    statement::Suite *_node = NULL;
    if (m_hasFinallyBody != 0)
      _node = dynamic_cast<statement::Suite*>(factory->getPointer(m_hasFinallyBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TryFinal::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryFinal_HasFinallyBody:
        setFinallyBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::Try::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TryFinal::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryFinal_HasFinallyBody:
        removeFinallyBody();
        return true;
      default:
        break;
    }
    if (statement::Try::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TryFinal::setFinallyBody(NodeId _id) {
    statement::Suite *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::Suite*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasFinallyBody) {
        removeParentEdge(m_hasFinallyBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinallyBody, m_id, edkTryFinal_HasFinallyBody);
      }
      m_hasFinallyBody = _node->getId();
      if (m_hasFinallyBody != 0)
        setParentEdge(factory->getPointer(m_hasFinallyBody), edkTryFinal_HasFinallyBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFinallyBody, this->getId(), edkTryFinal_HasFinallyBody);
    } else {
      if (m_hasFinallyBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryFinal::setFinallyBody(statement::Suite *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFinallyBody(_node->getId());
  }

  void TryFinal::removeFinallyBody() {
      if (m_hasFinallyBody) {
        removeParentEdge(m_hasFinallyBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinallyBody, m_id, edkTryFinal_HasFinallyBody);
      }
      m_hasFinallyBody = 0;
  }

  void TryFinal::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TryFinal::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TryFinal::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TryFinal::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TryFinal::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::TryFinal", strlen("statement::TryFinal"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TryFinal::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Try::save(binIo,false);

    binIo.writeUInt4(m_hasFinallyBody);

  }

  void TryFinal::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Try::load(binIo,false);

    m_hasFinallyBody =  binIo.readUInt4();
    if (m_hasFinallyBody != 0)
      setParentEdge(factory->getPointer(m_hasFinallyBody),edkTryFinal_HasFinallyBody);

  }


}


}}}
