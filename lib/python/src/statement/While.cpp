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
  While::While(NodeId _id, Factory *_factory) :
    Iteration(_id, _factory),
    m_hasTestExpression(0)
  {
  }

  While::~While() {
  }

  void While::prepareDelete(bool tryOnVirtualParent){
    removeTestExpression();
    statement::Iteration::prepareDelete(false);
  }

  NodeKind While::getNodeKind() const {
    return ndkWhile;
  }

  expression::Expression* While::getTestExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasTestExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTestExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool While::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWhile_HasTestExpression:
        setTestExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::Iteration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool While::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWhile_HasTestExpression:
        removeTestExpression();
        return true;
      default:
        break;
    }
    if (statement::Iteration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void While::setTestExpression(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasTestExpression) {
        removeParentEdge(m_hasTestExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTestExpression, m_id, edkWhile_HasTestExpression);
      }
      m_hasTestExpression = _node->getId();
      if (m_hasTestExpression != 0)
        setParentEdge(factory->getPointer(m_hasTestExpression), edkWhile_HasTestExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTestExpression, this->getId(), edkWhile_HasTestExpression);
    } else {
      if (m_hasTestExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void While::setTestExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTestExpression(_node->getId());
  }

  void While::removeTestExpression() {
      if (m_hasTestExpression) {
        removeParentEdge(m_hasTestExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTestExpression, m_id, edkWhile_HasTestExpression);
      }
      m_hasTestExpression = 0;
  }

  void While::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void While::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double While::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void While::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType While::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::While", strlen("statement::While"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void While::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Iteration::save(binIo,false);

    binIo.writeUInt4(m_hasTestExpression);

  }

  void While::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Iteration::load(binIo,false);

    m_hasTestExpression =  binIo.readUInt4();
    if (m_hasTestExpression != 0)
      setParentEdge(factory->getPointer(m_hasTestExpression),edkWhile_HasTestExpression);

  }


}


}}}
