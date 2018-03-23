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
  ArrayTypeSyntax::ArrayTypeSyntax(NodeId _id, Factory *_factory) :
    TypeSyntax(_id, _factory),
    m_ElementType(0),
    RankSpecifiersContainer()
  {
  }

  ArrayTypeSyntax::~ArrayTypeSyntax() {
  }

  void ArrayTypeSyntax::prepareDelete(bool tryOnVirtualParent){
    removeElementType();
    while (!RankSpecifiersContainer.empty()) {
      const NodeId id = *RankSpecifiersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkArrayTypeSyntax_RankSpecifiers);
      RankSpecifiersContainer.pop_front();
    }
    expression::TypeSyntax::prepareDelete(false);
  }

  NodeKind ArrayTypeSyntax::getNodeKind() const {
    return ndkArrayTypeSyntax;
  }

  expression::TypeSyntax* ArrayTypeSyntax::getElementType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_ElementType != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_ElementType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::ArrayRankSpecifierSyntax> ArrayTypeSyntax::getRankSpecifiersListIteratorBegin() const {
    return ListIterator<structure::ArrayRankSpecifierSyntax>(&RankSpecifiersContainer, factory, true);
  }

  ListIterator<structure::ArrayRankSpecifierSyntax> ArrayTypeSyntax::getRankSpecifiersListIteratorEnd() const {
    return ListIterator<structure::ArrayRankSpecifierSyntax>(&RankSpecifiersContainer, factory, false);
  }

  bool ArrayTypeSyntax::getRankSpecifiersIsEmpty() const {
    return getRankSpecifiersListIteratorBegin() == getRankSpecifiersListIteratorEnd();
  }

  unsigned int ArrayTypeSyntax::getRankSpecifiersSize() const {
    unsigned int size = 0;
    ListIterator<structure::ArrayRankSpecifierSyntax> endIt = getRankSpecifiersListIteratorEnd();
    for (ListIterator<structure::ArrayRankSpecifierSyntax> it = getRankSpecifiersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ArrayTypeSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayTypeSyntax_ElementType:
        setElementType(edgeEnd);
        return true;
      case edkArrayTypeSyntax_RankSpecifiers:
        addRankSpecifiers(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::TypeSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ArrayTypeSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayTypeSyntax_ElementType:
        removeElementType();
        return true;
      case edkArrayTypeSyntax_RankSpecifiers:
        removeRankSpecifiers(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::TypeSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ArrayTypeSyntax::setElementType(NodeId _id) {
    expression::TypeSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::TypeSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ElementType) {
        removeParentEdge(m_ElementType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ElementType, m_id, edkArrayTypeSyntax_ElementType);
      }
      m_ElementType = _node->getId();
      if (m_ElementType != 0)
        setParentEdge(factory->getPointer(m_ElementType), edkArrayTypeSyntax_ElementType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ElementType, this->getId(), edkArrayTypeSyntax_ElementType);
    } else {
      if (m_ElementType) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ArrayTypeSyntax::setElementType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setElementType(_node->getId());
  }

  void ArrayTypeSyntax::removeElementType() {
      if (m_ElementType) {
        removeParentEdge(m_ElementType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ElementType, m_id, edkArrayTypeSyntax_ElementType);
      }
      m_ElementType = 0;
  }

  void ArrayTypeSyntax::addRankSpecifiers(const structure::ArrayRankSpecifierSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkArrayRankSpecifierSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    RankSpecifiersContainer.push_back(_node->getId());
    setParentEdge(_node,edkArrayTypeSyntax_RankSpecifiers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkArrayTypeSyntax_RankSpecifiers);
  }

  void ArrayTypeSyntax::addRankSpecifiers(NodeId _id) {
    const structure::ArrayRankSpecifierSyntax *node = dynamic_cast<structure::ArrayRankSpecifierSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addRankSpecifiers( node );
  }

  void ArrayTypeSyntax::removeRankSpecifiers(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::ArrayRankSpecifierSyntax>::Container::iterator it = find(RankSpecifiersContainer.begin(), RankSpecifiersContainer.end(), id);

    if (it == RankSpecifiersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    RankSpecifiersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkArrayTypeSyntax_RankSpecifiers);
  }

  void ArrayTypeSyntax::removeRankSpecifiers(structure::ArrayRankSpecifierSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeRankSpecifiers(_node->getId());
  }

  void ArrayTypeSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ArrayTypeSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ArrayTypeSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ArrayTypeSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ArrayTypeSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ArrayTypeSyntax", strlen("expression::ArrayTypeSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ArrayTypeSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    TypeSyntax::save(binIo,false);

    binIo.writeUInt4(m_ElementType);


    for (ListIterator<structure::ArrayRankSpecifierSyntax>::Container::const_iterator it = RankSpecifiersContainer.begin(); it != RankSpecifiersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ArrayTypeSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    TypeSyntax::load(binIo,false);

    m_ElementType =  binIo.readUInt4();
    if (m_ElementType != 0)
      setParentEdge(factory->getPointer(m_ElementType),edkArrayTypeSyntax_ElementType);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      RankSpecifiersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkArrayTypeSyntax_RankSpecifiers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
