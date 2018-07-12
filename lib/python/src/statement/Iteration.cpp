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

namespace statement { 
  Iteration::Iteration(NodeId _id, Factory *_factory) :
    CompoundStatement(_id, _factory),
    m_hasElseBody(0)
  {
  }

  Iteration::~Iteration() {
  }

  void Iteration::prepareDelete(bool tryOnVirtualParent){
    removeElseBody();
    statement::CompoundStatement::prepareDelete(false);
  }

  statement::Suite* Iteration::getElseBody() const {
    statement::Suite *_node = NULL;
    if (m_hasElseBody != 0)
      _node = dynamic_cast<statement::Suite*>(factory->getPointer(m_hasElseBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Iteration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIteration_HasElseBody:
        setElseBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Iteration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIteration_HasElseBody:
        removeElseBody();
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Iteration::setElseBody(NodeId _id) {
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

      if (m_hasElseBody) {
        removeParentEdge(m_hasElseBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkIteration_HasElseBody);
      }
      m_hasElseBody = _node->getId();
      if (m_hasElseBody != 0)
        setParentEdge(factory->getPointer(m_hasElseBody), edkIteration_HasElseBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasElseBody, this->getId(), edkIteration_HasElseBody);
    } else {
      if (m_hasElseBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Iteration::setElseBody(statement::Suite *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setElseBody(_node->getId());
  }

  void Iteration::removeElseBody() {
      if (m_hasElseBody) {
        removeParentEdge(m_hasElseBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkIteration_HasElseBody);
      }
      m_hasElseBody = 0;
  }

  double Iteration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Iteration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Iteration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Iteration", strlen("statement::Iteration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Iteration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CompoundStatement::save(binIo,false);

    binIo.writeUInt4(m_hasElseBody);

  }

  void Iteration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CompoundStatement::load(binIo,false);

    m_hasElseBody =  binIo.readUInt4();
    if (m_hasElseBody != 0)
      setParentEdge(factory->getPointer(m_hasElseBody),edkIteration_HasElseBody);

  }


}


}}}
