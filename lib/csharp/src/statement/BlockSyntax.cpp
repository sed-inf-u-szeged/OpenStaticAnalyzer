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
  BlockSyntax::BlockSyntax(NodeId _id, Factory *_factory) :
    StatementSyntax(_id, _factory),
    StatementsContainer()
  {
  }

  BlockSyntax::~BlockSyntax() {
  }

  void BlockSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!StatementsContainer.empty()) {
      const NodeId id = *StatementsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBlockSyntax_Statements);
      StatementsContainer.pop_front();
    }
    statement::StatementSyntax::prepareDelete(false);
  }

  NodeKind BlockSyntax::getNodeKind() const {
    return ndkBlockSyntax;
  }

  ListIterator<statement::StatementSyntax> BlockSyntax::getStatementsListIteratorBegin() const {
    return ListIterator<statement::StatementSyntax>(&StatementsContainer, factory, true);
  }

  ListIterator<statement::StatementSyntax> BlockSyntax::getStatementsListIteratorEnd() const {
    return ListIterator<statement::StatementSyntax>(&StatementsContainer, factory, false);
  }

  bool BlockSyntax::getStatementsIsEmpty() const {
    return getStatementsListIteratorBegin() == getStatementsListIteratorEnd();
  }

  unsigned int BlockSyntax::getStatementsSize() const {
    unsigned int size = 0;
    ListIterator<statement::StatementSyntax> endIt = getStatementsListIteratorEnd();
    for (ListIterator<statement::StatementSyntax> it = getStatementsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool BlockSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBlockSyntax_Statements:
        addStatements(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BlockSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBlockSyntax_Statements:
        removeStatements(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BlockSyntax::addStatements(const statement::StatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatementSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    StatementsContainer.push_back(_node->getId());
    setParentEdge(_node,edkBlockSyntax_Statements);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBlockSyntax_Statements);
  }

  void BlockSyntax::addStatements(NodeId _id) {
    const statement::StatementSyntax *node = dynamic_cast<statement::StatementSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addStatements( node );
  }

  void BlockSyntax::removeStatements(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::StatementSyntax>::Container::iterator it = find(StatementsContainer.begin(), StatementsContainer.end(), id);

    if (it == StatementsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    StatementsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBlockSyntax_Statements);
  }

  void BlockSyntax::removeStatements(statement::StatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeStatements(_node->getId());
  }

  void BlockSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BlockSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BlockSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BlockSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType BlockSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::BlockSyntax", strlen("statement::BlockSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BlockSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StatementSyntax::save(binIo,false);


    for (ListIterator<statement::StatementSyntax>::Container::const_iterator it = StatementsContainer.begin(); it != StatementsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BlockSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StatementSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      StatementsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBlockSyntax_Statements);
      _id = binIo.readUInt4();
    }
  }


}


}}}
