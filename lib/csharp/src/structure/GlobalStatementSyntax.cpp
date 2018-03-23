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

namespace structure { 
  GlobalStatementSyntax::GlobalStatementSyntax(NodeId _id, Factory *_factory) :
    MemberDeclarationSyntax(_id, _factory),
    m_Statement(0)
  {
  }

  GlobalStatementSyntax::~GlobalStatementSyntax() {
  }

  void GlobalStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeStatement();
    structure::MemberDeclarationSyntax::prepareDelete(false);
  }

  NodeKind GlobalStatementSyntax::getNodeKind() const {
    return ndkGlobalStatementSyntax;
  }

  statement::StatementSyntax* GlobalStatementSyntax::getStatement() const {
    statement::StatementSyntax *_node = NULL;
    if (m_Statement != 0)
      _node = dynamic_cast<statement::StatementSyntax*>(factory->getPointer(m_Statement));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool GlobalStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGlobalStatementSyntax_Statement:
        setStatement(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool GlobalStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGlobalStatementSyntax_Statement:
        removeStatement();
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void GlobalStatementSyntax::setStatement(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Statement, m_id, edkGlobalStatementSyntax_Statement);
      }
      m_Statement = _node->getId();
      if (m_Statement != 0)
        setParentEdge(factory->getPointer(m_Statement), edkGlobalStatementSyntax_Statement);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Statement, this->getId(), edkGlobalStatementSyntax_Statement);
    } else {
      if (m_Statement) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void GlobalStatementSyntax::setStatement(statement::StatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setStatement(_node->getId());
  }

  void GlobalStatementSyntax::removeStatement() {
      if (m_Statement) {
        removeParentEdge(m_Statement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Statement, m_id, edkGlobalStatementSyntax_Statement);
      }
      m_Statement = 0;
  }

  void GlobalStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void GlobalStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double GlobalStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void GlobalStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType GlobalStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::GlobalStatementSyntax", strlen("structure::GlobalStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void GlobalStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_Statement);

  }

  void GlobalStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberDeclarationSyntax::load(binIo,false);

    m_Statement =  binIo.readUInt4();
    if (m_Statement != 0)
      setParentEdge(factory->getPointer(m_Statement),edkGlobalStatementSyntax_Statement);

  }


}


}}}
