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

namespace structure { 
  OrderByClauseSyntax::OrderByClauseSyntax(NodeId _id, Factory *_factory) :
    QueryClauseSyntax(_id, _factory),
    OrderingsContainer()
  {
  }

  OrderByClauseSyntax::~OrderByClauseSyntax() {
  }

  void OrderByClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!OrderingsContainer.empty()) {
      const NodeId id = *OrderingsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkOrderByClauseSyntax_Orderings);
      OrderingsContainer.pop_front();
    }
    structure::QueryClauseSyntax::prepareDelete(false);
  }

  NodeKind OrderByClauseSyntax::getNodeKind() const {
    return ndkOrderByClauseSyntax;
  }

  ListIterator<structure::OrderingSyntax> OrderByClauseSyntax::getOrderingsListIteratorBegin() const {
    return ListIterator<structure::OrderingSyntax>(&OrderingsContainer, factory, true);
  }

  ListIterator<structure::OrderingSyntax> OrderByClauseSyntax::getOrderingsListIteratorEnd() const {
    return ListIterator<structure::OrderingSyntax>(&OrderingsContainer, factory, false);
  }

  bool OrderByClauseSyntax::getOrderingsIsEmpty() const {
    return getOrderingsListIteratorBegin() == getOrderingsListIteratorEnd();
  }

  unsigned int OrderByClauseSyntax::getOrderingsSize() const {
    unsigned int size = 0;
    ListIterator<structure::OrderingSyntax> endIt = getOrderingsListIteratorEnd();
    for (ListIterator<structure::OrderingSyntax> it = getOrderingsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool OrderByClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkOrderByClauseSyntax_Orderings:
        addOrderings(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::QueryClauseSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool OrderByClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkOrderByClauseSyntax_Orderings:
        removeOrderings(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::QueryClauseSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void OrderByClauseSyntax::addOrderings(const structure::OrderingSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkOrderingSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    OrderingsContainer.push_back(_node->getId());
    setParentEdge(_node,edkOrderByClauseSyntax_Orderings);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkOrderByClauseSyntax_Orderings);
  }

  void OrderByClauseSyntax::addOrderings(NodeId _id) {
    const structure::OrderingSyntax *node = dynamic_cast<structure::OrderingSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addOrderings( node );
  }

  void OrderByClauseSyntax::removeOrderings(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::OrderingSyntax>::Container::iterator it = find(OrderingsContainer.begin(), OrderingsContainer.end(), id);

    if (it == OrderingsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    OrderingsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkOrderByClauseSyntax_Orderings);
  }

  void OrderByClauseSyntax::removeOrderings(structure::OrderingSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeOrderings(_node->getId());
  }

  void OrderByClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void OrderByClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double OrderByClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void OrderByClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType OrderByClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::OrderByClauseSyntax", strlen("structure::OrderByClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void OrderByClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    QueryClauseSyntax::save(binIo,false);


    for (ListIterator<structure::OrderingSyntax>::Container::const_iterator it = OrderingsContainer.begin(); it != OrderingsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void OrderByClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    QueryClauseSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      OrderingsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkOrderByClauseSyntax_Orderings);
      _id = binIo.readUInt4();
    }
  }


}


}}}
