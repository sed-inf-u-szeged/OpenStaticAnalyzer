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

namespace expression { 
  QueryExpressionSyntax::QueryExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_Body(0),
    m_FromClause(0)
  {
  }

  QueryExpressionSyntax::~QueryExpressionSyntax() {
  }

  void QueryExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeBody();
    removeFromClause();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind QueryExpressionSyntax::getNodeKind() const {
    return ndkQueryExpressionSyntax;
  }

  structure::QueryBodySyntax* QueryExpressionSyntax::getBody() const {
    structure::QueryBodySyntax *_node = NULL;
    if (m_Body != 0)
      _node = dynamic_cast<structure::QueryBodySyntax*>(factory->getPointer(m_Body));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::FromClauseSyntax* QueryExpressionSyntax::getFromClause() const {
    structure::FromClauseSyntax *_node = NULL;
    if (m_FromClause != 0)
      _node = dynamic_cast<structure::FromClauseSyntax*>(factory->getPointer(m_FromClause));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool QueryExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQueryExpressionSyntax_Body:
        setBody(edgeEnd);
        return true;
      case edkQueryExpressionSyntax_FromClause:
        setFromClause(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool QueryExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQueryExpressionSyntax_Body:
        removeBody();
        return true;
      case edkQueryExpressionSyntax_FromClause:
        removeFromClause();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void QueryExpressionSyntax::setBody(NodeId _id) {
    structure::QueryBodySyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::QueryBodySyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkQueryExpressionSyntax_Body);
      }
      m_Body = _node->getId();
      if (m_Body != 0)
        setParentEdge(factory->getPointer(m_Body), edkQueryExpressionSyntax_Body);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Body, this->getId(), edkQueryExpressionSyntax_Body);
    } else {
      if (m_Body) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QueryExpressionSyntax::setBody(structure::QueryBodySyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void QueryExpressionSyntax::removeBody() {
      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkQueryExpressionSyntax_Body);
      }
      m_Body = 0;
  }

  void QueryExpressionSyntax::setFromClause(NodeId _id) {
    structure::FromClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::FromClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_FromClause) {
        removeParentEdge(m_FromClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_FromClause, m_id, edkQueryExpressionSyntax_FromClause);
      }
      m_FromClause = _node->getId();
      if (m_FromClause != 0)
        setParentEdge(factory->getPointer(m_FromClause), edkQueryExpressionSyntax_FromClause);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_FromClause, this->getId(), edkQueryExpressionSyntax_FromClause);
    } else {
      if (m_FromClause) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QueryExpressionSyntax::setFromClause(structure::FromClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFromClause(_node->getId());
  }

  void QueryExpressionSyntax::removeFromClause() {
      if (m_FromClause) {
        removeParentEdge(m_FromClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_FromClause, m_id, edkQueryExpressionSyntax_FromClause);
      }
      m_FromClause = 0;
  }

  void QueryExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void QueryExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double QueryExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void QueryExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType QueryExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::QueryExpressionSyntax", strlen("expression::QueryExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void QueryExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_Body);
    binIo.writeUInt4(m_FromClause);

  }

  void QueryExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_Body =  binIo.readUInt4();
    if (m_Body != 0)
      setParentEdge(factory->getPointer(m_Body),edkQueryExpressionSyntax_Body);

    m_FromClause =  binIo.readUInt4();
    if (m_FromClause != 0)
      setParentEdge(factory->getPointer(m_FromClause),edkQueryExpressionSyntax_FromClause);

  }


}


}}}
