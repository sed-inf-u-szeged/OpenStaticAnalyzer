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
  QueryBodySyntax::QueryBodySyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    ClausesContainer(),
    m_Continuation(0),
    m_SelectOrGroup(0)
  {
  }

  QueryBodySyntax::~QueryBodySyntax() {
  }

  void QueryBodySyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ClausesContainer.empty()) {
      const NodeId id = *ClausesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkQueryBodySyntax_Clauses);
      ClausesContainer.pop_front();
    }
    removeContinuation();
    removeSelectOrGroup();
    base::Positioned::prepareDelete(false);
  }

  NodeKind QueryBodySyntax::getNodeKind() const {
    return ndkQueryBodySyntax;
  }

  ListIterator<structure::QueryClauseSyntax> QueryBodySyntax::getClausesListIteratorBegin() const {
    return ListIterator<structure::QueryClauseSyntax>(&ClausesContainer, factory, true);
  }

  ListIterator<structure::QueryClauseSyntax> QueryBodySyntax::getClausesListIteratorEnd() const {
    return ListIterator<structure::QueryClauseSyntax>(&ClausesContainer, factory, false);
  }

  bool QueryBodySyntax::getClausesIsEmpty() const {
    return getClausesListIteratorBegin() == getClausesListIteratorEnd();
  }

  unsigned int QueryBodySyntax::getClausesSize() const {
    unsigned int size = 0;
    ListIterator<structure::QueryClauseSyntax> endIt = getClausesListIteratorEnd();
    for (ListIterator<structure::QueryClauseSyntax> it = getClausesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::QueryContinuationSyntax* QueryBodySyntax::getContinuation() const {
    structure::QueryContinuationSyntax *_node = NULL;
    if (m_Continuation != 0)
      _node = dynamic_cast<structure::QueryContinuationSyntax*>(factory->getPointer(m_Continuation));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::SelectOrGroupClauseSyntax* QueryBodySyntax::getSelectOrGroup() const {
    structure::SelectOrGroupClauseSyntax *_node = NULL;
    if (m_SelectOrGroup != 0)
      _node = dynamic_cast<structure::SelectOrGroupClauseSyntax*>(factory->getPointer(m_SelectOrGroup));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool QueryBodySyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQueryBodySyntax_Clauses:
        addClauses(edgeEnd);
        return true;
      case edkQueryBodySyntax_Continuation:
        setContinuation(edgeEnd);
        return true;
      case edkQueryBodySyntax_SelectOrGroup:
        setSelectOrGroup(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool QueryBodySyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQueryBodySyntax_Clauses:
        removeClauses(edgeEnd);
        return true;
      case edkQueryBodySyntax_Continuation:
        removeContinuation();
        return true;
      case edkQueryBodySyntax_SelectOrGroup:
        removeSelectOrGroup();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void QueryBodySyntax::addClauses(const structure::QueryClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsQueryClauseSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ClausesContainer.push_back(_node->getId());
    setParentEdge(_node,edkQueryBodySyntax_Clauses);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkQueryBodySyntax_Clauses);
  }

  void QueryBodySyntax::addClauses(NodeId _id) {
    const structure::QueryClauseSyntax *node = dynamic_cast<structure::QueryClauseSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addClauses( node );
  }

  void QueryBodySyntax::removeClauses(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::QueryClauseSyntax>::Container::iterator it = find(ClausesContainer.begin(), ClausesContainer.end(), id);

    if (it == ClausesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ClausesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkQueryBodySyntax_Clauses);
  }

  void QueryBodySyntax::removeClauses(structure::QueryClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeClauses(_node->getId());
  }

  void QueryBodySyntax::setContinuation(NodeId _id) {
    structure::QueryContinuationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::QueryContinuationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Continuation) {
        removeParentEdge(m_Continuation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Continuation, m_id, edkQueryBodySyntax_Continuation);
      }
      m_Continuation = _node->getId();
      if (m_Continuation != 0)
        setParentEdge(factory->getPointer(m_Continuation), edkQueryBodySyntax_Continuation);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Continuation, this->getId(), edkQueryBodySyntax_Continuation);
    } else {
      if (m_Continuation) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QueryBodySyntax::setContinuation(structure::QueryContinuationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setContinuation(_node->getId());
  }

  void QueryBodySyntax::removeContinuation() {
      if (m_Continuation) {
        removeParentEdge(m_Continuation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Continuation, m_id, edkQueryBodySyntax_Continuation);
      }
      m_Continuation = 0;
  }

  void QueryBodySyntax::setSelectOrGroup(NodeId _id) {
    structure::SelectOrGroupClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::SelectOrGroupClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_SelectOrGroup) {
        removeParentEdge(m_SelectOrGroup);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_SelectOrGroup, m_id, edkQueryBodySyntax_SelectOrGroup);
      }
      m_SelectOrGroup = _node->getId();
      if (m_SelectOrGroup != 0)
        setParentEdge(factory->getPointer(m_SelectOrGroup), edkQueryBodySyntax_SelectOrGroup);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_SelectOrGroup, this->getId(), edkQueryBodySyntax_SelectOrGroup);
    } else {
      if (m_SelectOrGroup) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QueryBodySyntax::setSelectOrGroup(structure::SelectOrGroupClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSelectOrGroup(_node->getId());
  }

  void QueryBodySyntax::removeSelectOrGroup() {
      if (m_SelectOrGroup) {
        removeParentEdge(m_SelectOrGroup);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_SelectOrGroup, m_id, edkQueryBodySyntax_SelectOrGroup);
      }
      m_SelectOrGroup = 0;
  }

  void QueryBodySyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void QueryBodySyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double QueryBodySyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void QueryBodySyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType QueryBodySyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::QueryBodySyntax", strlen("structure::QueryBodySyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void QueryBodySyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Continuation);
    binIo.writeUInt4(m_SelectOrGroup);


    for (ListIterator<structure::QueryClauseSyntax>::Container::const_iterator it = ClausesContainer.begin(); it != ClausesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void QueryBodySyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Continuation =  binIo.readUInt4();
    if (m_Continuation != 0)
      setParentEdge(factory->getPointer(m_Continuation),edkQueryBodySyntax_Continuation);

    m_SelectOrGroup =  binIo.readUInt4();
    if (m_SelectOrGroup != 0)
      setParentEdge(factory->getPointer(m_SelectOrGroup),edkQueryBodySyntax_SelectOrGroup);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ClausesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkQueryBodySyntax_Clauses);
      _id = binIo.readUInt4();
    }
  }


}


}}}
