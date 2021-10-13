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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statement { 
  ReturnStatement::ReturnStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasArgument(0)
  {
  }

  ReturnStatement::~ReturnStatement() {
  }

  void ReturnStatement::prepareDelete(bool tryOnVirtualParent){
    removeArgument();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind ReturnStatement::getNodeKind() const {
    return ndkReturnStatement;
  }

  expression::Expression* ReturnStatement::getArgument() const {
    expression::Expression *_node = NULL;
    if (m_hasArgument != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasArgument));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ReturnStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkReturnStatement_HasArgument:
        setArgument(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ReturnStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkReturnStatement_HasArgument:
        removeArgument();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ReturnStatement::setArgument(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasArgument) {
        removeParentEdge(m_hasArgument);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasArgument, m_id, edkReturnStatement_HasArgument);
      }
      m_hasArgument = _node->getId();
      if (m_hasArgument != 0)
        setParentEdge(factory->getPointer(m_hasArgument), edkReturnStatement_HasArgument);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasArgument, this->getId(), edkReturnStatement_HasArgument);
    } else {
      if (m_hasArgument) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ReturnStatement::setArgument(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgument(_node->getId());
  }

  void ReturnStatement::removeArgument() {
      if (m_hasArgument) {
        removeParentEdge(m_hasArgument);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasArgument, m_id, edkReturnStatement_HasArgument);
      }
      m_hasArgument = 0;
  }

  void ReturnStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ReturnStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ReturnStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ReturnStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ReturnStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ReturnStatement", strlen("statement::ReturnStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ReturnStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasArgument);

  }

  void ReturnStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasArgument =  binIo.readUInt4();
    if (m_hasArgument != 0)
      setParentEdge(factory->getPointer(m_hasArgument),edkReturnStatement_HasArgument);

  }


}


}}}
