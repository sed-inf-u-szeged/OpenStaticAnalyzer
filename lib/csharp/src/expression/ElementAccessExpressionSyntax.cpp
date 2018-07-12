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

namespace expression { 
  ElementAccessExpressionSyntax::ElementAccessExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    AccessorCallContainer(),
    m_ArgumentList(0),
    m_Expression(0)
  {
  }

  ElementAccessExpressionSyntax::~ElementAccessExpressionSyntax() {
  }

  void ElementAccessExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AccessorCallContainer.empty()) {
      const NodeId id = *AccessorCallContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkElementAccessExpressionSyntax_AccessorCall);
      AccessorCallContainer.pop_front();
    }
    removeArgumentList();
    removeExpression();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind ElementAccessExpressionSyntax::getNodeKind() const {
    return ndkElementAccessExpressionSyntax;
  }

  ListIterator<structure::AccessorDeclarationSyntax> ElementAccessExpressionSyntax::getAccessorCallListIteratorBegin() const {
    return ListIterator<structure::AccessorDeclarationSyntax>(&AccessorCallContainer, factory, true);
  }

  ListIterator<structure::AccessorDeclarationSyntax> ElementAccessExpressionSyntax::getAccessorCallListIteratorEnd() const {
    return ListIterator<structure::AccessorDeclarationSyntax>(&AccessorCallContainer, factory, false);
  }

  bool ElementAccessExpressionSyntax::getAccessorCallIsEmpty() const {
    return getAccessorCallListIteratorBegin() == getAccessorCallListIteratorEnd();
  }

  unsigned int ElementAccessExpressionSyntax::getAccessorCallSize() const {
    unsigned int size = 0;
    ListIterator<structure::AccessorDeclarationSyntax> endIt = getAccessorCallListIteratorEnd();
    for (ListIterator<structure::AccessorDeclarationSyntax> it = getAccessorCallListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::BracketedArgumentListSyntax* ElementAccessExpressionSyntax::getArgumentList() const {
    structure::BracketedArgumentListSyntax *_node = NULL;
    if (m_ArgumentList != 0)
      _node = dynamic_cast<structure::BracketedArgumentListSyntax*>(factory->getPointer(m_ArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* ElementAccessExpressionSyntax::getExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Expression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Expression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ElementAccessExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkElementAccessExpressionSyntax_AccessorCall:
        addAccessorCall(edgeEnd);
        return true;
      case edkElementAccessExpressionSyntax_ArgumentList:
        setArgumentList(edgeEnd);
        return true;
      case edkElementAccessExpressionSyntax_Expression:
        setExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ElementAccessExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkElementAccessExpressionSyntax_AccessorCall:
        removeAccessorCall(edgeEnd);
        return true;
      case edkElementAccessExpressionSyntax_ArgumentList:
        removeArgumentList();
        return true;
      case edkElementAccessExpressionSyntax_Expression:
        removeExpression();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ElementAccessExpressionSyntax::addAccessorCall(const structure::AccessorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAccessorDeclarationSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AccessorCallContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkElementAccessExpressionSyntax_AccessorCall);
  }

  void ElementAccessExpressionSyntax::addAccessorCall(NodeId _id) {
    const structure::AccessorDeclarationSyntax *node = dynamic_cast<structure::AccessorDeclarationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAccessorCall( node );
  }

  void ElementAccessExpressionSyntax::removeAccessorCall(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AccessorDeclarationSyntax>::Container::iterator it = find(AccessorCallContainer.begin(), AccessorCallContainer.end(), id);

    if (it == AccessorCallContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AccessorCallContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkElementAccessExpressionSyntax_AccessorCall);
  }

  void ElementAccessExpressionSyntax::removeAccessorCall(structure::AccessorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAccessorCall(_node->getId());
  }

  void ElementAccessExpressionSyntax::setArgumentList(NodeId _id) {
    structure::BracketedArgumentListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::BracketedArgumentListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkElementAccessExpressionSyntax_ArgumentList);
      }
      m_ArgumentList = _node->getId();
      if (m_ArgumentList != 0)
        setParentEdge(factory->getPointer(m_ArgumentList), edkElementAccessExpressionSyntax_ArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ArgumentList, this->getId(), edkElementAccessExpressionSyntax_ArgumentList);
    } else {
      if (m_ArgumentList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ElementAccessExpressionSyntax::setArgumentList(structure::BracketedArgumentListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgumentList(_node->getId());
  }

  void ElementAccessExpressionSyntax::removeArgumentList() {
      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkElementAccessExpressionSyntax_ArgumentList);
      }
      m_ArgumentList = 0;
  }

  void ElementAccessExpressionSyntax::setExpression(NodeId _id) {
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

      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkElementAccessExpressionSyntax_Expression);
      }
      m_Expression = _node->getId();
      if (m_Expression != 0)
        setParentEdge(factory->getPointer(m_Expression), edkElementAccessExpressionSyntax_Expression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Expression, this->getId(), edkElementAccessExpressionSyntax_Expression);
    } else {
      if (m_Expression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ElementAccessExpressionSyntax::setExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void ElementAccessExpressionSyntax::removeExpression() {
      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkElementAccessExpressionSyntax_Expression);
      }
      m_Expression = 0;
  }

  void ElementAccessExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ElementAccessExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ElementAccessExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ElementAccessExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ElementAccessExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ElementAccessExpressionSyntax", strlen("expression::ElementAccessExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ElementAccessExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_ArgumentList);
    binIo.writeUInt4(m_Expression);


    for (ListIterator<structure::AccessorDeclarationSyntax>::Container::const_iterator it = AccessorCallContainer.begin(); it != AccessorCallContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ElementAccessExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_ArgumentList =  binIo.readUInt4();
    if (m_ArgumentList != 0)
      setParentEdge(factory->getPointer(m_ArgumentList),edkElementAccessExpressionSyntax_ArgumentList);

    m_Expression =  binIo.readUInt4();
    if (m_Expression != 0)
      setParentEdge(factory->getPointer(m_Expression),edkElementAccessExpressionSyntax_Expression);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AccessorCallContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
