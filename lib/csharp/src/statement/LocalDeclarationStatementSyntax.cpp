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
  LocalDeclarationStatementSyntax::LocalDeclarationStatementSyntax(NodeId _id, Factory *_factory) :
    StatementSyntax(_id, _factory),
    m_Declaration(0)
  {
  }

  LocalDeclarationStatementSyntax::~LocalDeclarationStatementSyntax() {
  }

  void LocalDeclarationStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeDeclaration();
    statement::StatementSyntax::prepareDelete(false);
  }

  NodeKind LocalDeclarationStatementSyntax::getNodeKind() const {
    return ndkLocalDeclarationStatementSyntax;
  }

  structure::VariableDeclarationSyntax* LocalDeclarationStatementSyntax::getDeclaration() const {
    structure::VariableDeclarationSyntax *_node = NULL;
    if (m_Declaration != 0)
      _node = dynamic_cast<structure::VariableDeclarationSyntax*>(factory->getPointer(m_Declaration));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool LocalDeclarationStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLocalDeclarationStatementSyntax_Declaration:
        setDeclaration(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool LocalDeclarationStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLocalDeclarationStatementSyntax_Declaration:
        removeDeclaration();
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void LocalDeclarationStatementSyntax::setDeclaration(NodeId _id) {
    structure::VariableDeclarationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::VariableDeclarationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Declaration) {
        removeParentEdge(m_Declaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkLocalDeclarationStatementSyntax_Declaration);
      }
      m_Declaration = _node->getId();
      if (m_Declaration != 0)
        setParentEdge(factory->getPointer(m_Declaration), edkLocalDeclarationStatementSyntax_Declaration);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Declaration, this->getId(), edkLocalDeclarationStatementSyntax_Declaration);
    } else {
      if (m_Declaration) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LocalDeclarationStatementSyntax::setDeclaration(structure::VariableDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDeclaration(_node->getId());
  }

  void LocalDeclarationStatementSyntax::removeDeclaration() {
      if (m_Declaration) {
        removeParentEdge(m_Declaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkLocalDeclarationStatementSyntax_Declaration);
      }
      m_Declaration = 0;
  }

  void LocalDeclarationStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void LocalDeclarationStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double LocalDeclarationStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void LocalDeclarationStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType LocalDeclarationStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::LocalDeclarationStatementSyntax", strlen("statement::LocalDeclarationStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void LocalDeclarationStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StatementSyntax::save(binIo,false);

    binIo.writeUInt4(m_Declaration);

  }

  void LocalDeclarationStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StatementSyntax::load(binIo,false);

    m_Declaration =  binIo.readUInt4();
    if (m_Declaration != 0)
      setParentEdge(factory->getPointer(m_Declaration),edkLocalDeclarationStatementSyntax_Declaration);

  }


}


}}}
