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
  TryStatementSyntax::TryStatementSyntax(NodeId _id, Factory *_factory) :
    StatementSyntax(_id, _factory),
    m_Block(0),
    CatchesContainer(),
    m_Finally(0)
  {
  }

  TryStatementSyntax::~TryStatementSyntax() {
  }

  void TryStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeBlock();
    while (!CatchesContainer.empty()) {
      const NodeId id = *CatchesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTryStatementSyntax_Catches);
      CatchesContainer.pop_front();
    }
    removeFinally();
    statement::StatementSyntax::prepareDelete(false);
  }

  NodeKind TryStatementSyntax::getNodeKind() const {
    return ndkTryStatementSyntax;
  }

  statement::BlockSyntax* TryStatementSyntax::getBlock() const {
    statement::BlockSyntax *_node = NULL;
    if (m_Block != 0)
      _node = dynamic_cast<statement::BlockSyntax*>(factory->getPointer(m_Block));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::CatchClauseSyntax> TryStatementSyntax::getCatchesListIteratorBegin() const {
    return ListIterator<structure::CatchClauseSyntax>(&CatchesContainer, factory, true);
  }

  ListIterator<structure::CatchClauseSyntax> TryStatementSyntax::getCatchesListIteratorEnd() const {
    return ListIterator<structure::CatchClauseSyntax>(&CatchesContainer, factory, false);
  }

  bool TryStatementSyntax::getCatchesIsEmpty() const {
    return getCatchesListIteratorBegin() == getCatchesListIteratorEnd();
  }

  unsigned int TryStatementSyntax::getCatchesSize() const {
    unsigned int size = 0;
    ListIterator<structure::CatchClauseSyntax> endIt = getCatchesListIteratorEnd();
    for (ListIterator<structure::CatchClauseSyntax> it = getCatchesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::FinallyClauseSyntax* TryStatementSyntax::getFinally() const {
    structure::FinallyClauseSyntax *_node = NULL;
    if (m_Finally != 0)
      _node = dynamic_cast<structure::FinallyClauseSyntax*>(factory->getPointer(m_Finally));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TryStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryStatementSyntax_Block:
        setBlock(edgeEnd);
        return true;
      case edkTryStatementSyntax_Catches:
        addCatches(edgeEnd);
        return true;
      case edkTryStatementSyntax_Finally:
        setFinally(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TryStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryStatementSyntax_Block:
        removeBlock();
        return true;
      case edkTryStatementSyntax_Catches:
        removeCatches(edgeEnd);
        return true;
      case edkTryStatementSyntax_Finally:
        removeFinally();
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TryStatementSyntax::setBlock(NodeId _id) {
    statement::BlockSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::BlockSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Block) {
        removeParentEdge(m_Block);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Block, m_id, edkTryStatementSyntax_Block);
      }
      m_Block = _node->getId();
      if (m_Block != 0)
        setParentEdge(factory->getPointer(m_Block), edkTryStatementSyntax_Block);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Block, this->getId(), edkTryStatementSyntax_Block);
    } else {
      if (m_Block) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryStatementSyntax::setBlock(statement::BlockSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBlock(_node->getId());
  }

  void TryStatementSyntax::removeBlock() {
      if (m_Block) {
        removeParentEdge(m_Block);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Block, m_id, edkTryStatementSyntax_Block);
      }
      m_Block = 0;
  }

  void TryStatementSyntax::addCatches(const structure::CatchClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCatchClauseSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    CatchesContainer.push_back(_node->getId());
    setParentEdge(_node,edkTryStatementSyntax_Catches);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTryStatementSyntax_Catches);
  }

  void TryStatementSyntax::addCatches(NodeId _id) {
    const structure::CatchClauseSyntax *node = dynamic_cast<structure::CatchClauseSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCatches( node );
  }

  void TryStatementSyntax::removeCatches(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::CatchClauseSyntax>::Container::iterator it = find(CatchesContainer.begin(), CatchesContainer.end(), id);

    if (it == CatchesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    CatchesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTryStatementSyntax_Catches);
  }

  void TryStatementSyntax::removeCatches(structure::CatchClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCatches(_node->getId());
  }

  void TryStatementSyntax::setFinally(NodeId _id) {
    structure::FinallyClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::FinallyClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Finally) {
        removeParentEdge(m_Finally);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Finally, m_id, edkTryStatementSyntax_Finally);
      }
      m_Finally = _node->getId();
      if (m_Finally != 0)
        setParentEdge(factory->getPointer(m_Finally), edkTryStatementSyntax_Finally);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Finally, this->getId(), edkTryStatementSyntax_Finally);
    } else {
      if (m_Finally) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryStatementSyntax::setFinally(structure::FinallyClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFinally(_node->getId());
  }

  void TryStatementSyntax::removeFinally() {
      if (m_Finally) {
        removeParentEdge(m_Finally);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Finally, m_id, edkTryStatementSyntax_Finally);
      }
      m_Finally = 0;
  }

  void TryStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TryStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TryStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TryStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType TryStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::TryStatementSyntax", strlen("statement::TryStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TryStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StatementSyntax::save(binIo,false);

    binIo.writeUInt4(m_Block);
    binIo.writeUInt4(m_Finally);


    for (ListIterator<structure::CatchClauseSyntax>::Container::const_iterator it = CatchesContainer.begin(); it != CatchesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TryStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StatementSyntax::load(binIo,false);

    m_Block =  binIo.readUInt4();
    if (m_Block != 0)
      setParentEdge(factory->getPointer(m_Block),edkTryStatementSyntax_Block);

    m_Finally =  binIo.readUInt4();
    if (m_Finally != 0)
      setParentEdge(factory->getPointer(m_Finally),edkTryStatementSyntax_Finally);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      CatchesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTryStatementSyntax_Catches);
      _id = binIo.readUInt4();
    }
  }


}


}}}
