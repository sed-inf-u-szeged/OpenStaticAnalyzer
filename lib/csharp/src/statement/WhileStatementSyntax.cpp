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

#include "csharp/inc/csharp.h"
#include "csharp/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "csharp/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace csharp { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statement { 
  WhileStatementSyntax::WhileStatementSyntax(NodeId _id, Factory *_factory) :
    StatementSyntax(_id, _factory),
    m_Condition(0),
    m_Statement(0)
  {
  }

  WhileStatementSyntax::~WhileStatementSyntax() {
  }

  void WhileStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeCondition();
    removeStatement();
    statement::StatementSyntax::prepareDelete(false);
  }

  NodeKind WhileStatementSyntax::getNodeKind() const {
    return ndkWhileStatementSyntax;
  }

  expression::ExpressionSyntax* WhileStatementSyntax::getCondition() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Condition != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Condition));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::StatementSyntax* WhileStatementSyntax::getStatement() const {
    statement::StatementSyntax *_node = NULL;
    if (m_Statement != 0)
      _node = dynamic_cast<statement::StatementSyntax*>(factory->getPointer(m_Statement));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool WhileStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWhileStatementSyntax_Condition:
        setCondition(edgeEnd);
        return true;
      case edkWhileStatementSyntax_Statement:
        setStatement(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool WhileStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWhileStatementSyntax_Condition:
        removeCondition();
        return true;
      case edkWhileStatementSyntax_Statement:
        removeStatement();
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void WhileStatementSyntax::setCondition(NodeId _id) {
    expression::ExpressionSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ExpressionSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Condition) {
        removeParentEdge(m_Condition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Condition, m_id, edkWhileStatementSyntax_Condition);
      }
      m_Condition = _node->getId();
      if (m_Condition != 0)
        setParentEdge(factory->getPointer(m_Condition), edkWhileStatementSyntax_Condition);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Condition, this->getId(), edkWhileStatementSyntax_Condition);
    } else {
      if (m_Condition) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WhileStatementSyntax::setCondition(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCondition(_node->getId());
  }

  void WhileStatementSyntax::removeCondition() {
      if (m_Condition) {
        removeParentEdge(m_Condition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Condition, m_id, edkWhileStatementSyntax_Condition);
      }
      m_Condition = 0;
  }

  void WhileStatementSyntax::setStatement(NodeId _id) {
    statement::StatementSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::StatementSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Statement) {
        removeParentEdge(m_Statement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Statement, m_id, edkWhileStatementSyntax_Statement);
      }
      m_Statement = _node->getId();
      if (m_Statement != 0)
        setParentEdge(factory->getPointer(m_Statement), edkWhileStatementSyntax_Statement);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Statement, this->getId(), edkWhileStatementSyntax_Statement);
    } else {
      if (m_Statement) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WhileStatementSyntax::setStatement(statement::StatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setStatement(_node->getId());
  }

  void WhileStatementSyntax::removeStatement() {
      if (m_Statement) {
        removeParentEdge(m_Statement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Statement, m_id, edkWhileStatementSyntax_Statement);
      }
      m_Statement = 0;
  }

  void WhileStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void WhileStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double WhileStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void WhileStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType WhileStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::WhileStatementSyntax", strlen("statement::WhileStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void WhileStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StatementSyntax::save(binIo,false);

    binIo.writeUInt4(m_Condition);
    binIo.writeUInt4(m_Statement);

  }

  void WhileStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StatementSyntax::load(binIo,false);

    m_Condition =  binIo.readUInt4();
    if (m_Condition != 0)
      setParentEdge(factory->getPointer(m_Condition),edkWhileStatementSyntax_Condition);

    m_Statement =  binIo.readUInt4();
    if (m_Statement != 0)
      setParentEdge(factory->getPointer(m_Statement),edkWhileStatementSyntax_Statement);

  }


}


}}}
