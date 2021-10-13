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
  LocalFunctionStatementSyntax::LocalFunctionStatementSyntax(NodeId _id, Factory *_factory) :
    StatementSyntax(_id, _factory),
    m_identifier(0),
    m_Body(0),
    ConstraintClausesContainer(),
    m_ExpressionBody(0),
    m_ParameterList(0),
    m_ReturnType(0),
    m_TypeParameterList(0)
  {
  }

  LocalFunctionStatementSyntax::~LocalFunctionStatementSyntax() {
  }

  void LocalFunctionStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeBody();
    while (!ConstraintClausesContainer.empty()) {
      const NodeId id = *ConstraintClausesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkLocalFunctionStatementSyntax_ConstraintClauses);
      ConstraintClausesContainer.pop_front();
    }
    removeExpressionBody();
    removeParameterList();
    removeReturnType();
    removeTypeParameterList();
    statement::StatementSyntax::prepareDelete(false);
  }

  NodeKind LocalFunctionStatementSyntax::getNodeKind() const {
    return ndkLocalFunctionStatementSyntax;
  }

  Key LocalFunctionStatementSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& LocalFunctionStatementSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void LocalFunctionStatementSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void LocalFunctionStatementSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  statement::BlockSyntax* LocalFunctionStatementSyntax::getBody() const {
    statement::BlockSyntax *_node = NULL;
    if (m_Body != 0)
      _node = dynamic_cast<statement::BlockSyntax*>(factory->getPointer(m_Body));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> LocalFunctionStatementSyntax::getConstraintClausesListIteratorBegin() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, true);
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> LocalFunctionStatementSyntax::getConstraintClausesListIteratorEnd() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, false);
  }

  bool LocalFunctionStatementSyntax::getConstraintClausesIsEmpty() const {
    return getConstraintClausesListIteratorBegin() == getConstraintClausesListIteratorEnd();
  }

  unsigned int LocalFunctionStatementSyntax::getConstraintClausesSize() const {
    unsigned int size = 0;
    ListIterator<structure::TypeParameterConstraintClauseSyntax> endIt = getConstraintClausesListIteratorEnd();
    for (ListIterator<structure::TypeParameterConstraintClauseSyntax> it = getConstraintClausesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::ArrowExpressionClauseSyntax* LocalFunctionStatementSyntax::getExpressionBody() const {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (m_ExpressionBody != 0)
      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*>(factory->getPointer(m_ExpressionBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::ParameterListSyntax* LocalFunctionStatementSyntax::getParameterList() const {
    structure::ParameterListSyntax *_node = NULL;
    if (m_ParameterList != 0)
      _node = dynamic_cast<structure::ParameterListSyntax*>(factory->getPointer(m_ParameterList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* LocalFunctionStatementSyntax::getReturnType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_ReturnType != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_ReturnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::TypeParameterListSyntax* LocalFunctionStatementSyntax::getTypeParameterList() const {
    structure::TypeParameterListSyntax *_node = NULL;
    if (m_TypeParameterList != 0)
      _node = dynamic_cast<structure::TypeParameterListSyntax*>(factory->getPointer(m_TypeParameterList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool LocalFunctionStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLocalFunctionStatementSyntax_Body:
        setBody(edgeEnd);
        return true;
      case edkLocalFunctionStatementSyntax_ConstraintClauses:
        addConstraintClauses(edgeEnd);
        return true;
      case edkLocalFunctionStatementSyntax_ExpressionBody:
        setExpressionBody(edgeEnd);
        return true;
      case edkLocalFunctionStatementSyntax_ParameterList:
        setParameterList(edgeEnd);
        return true;
      case edkLocalFunctionStatementSyntax_ReturnType:
        setReturnType(edgeEnd);
        return true;
      case edkLocalFunctionStatementSyntax_TypeParameterList:
        setTypeParameterList(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool LocalFunctionStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLocalFunctionStatementSyntax_Body:
        removeBody();
        return true;
      case edkLocalFunctionStatementSyntax_ConstraintClauses:
        removeConstraintClauses(edgeEnd);
        return true;
      case edkLocalFunctionStatementSyntax_ExpressionBody:
        removeExpressionBody();
        return true;
      case edkLocalFunctionStatementSyntax_ParameterList:
        removeParameterList();
        return true;
      case edkLocalFunctionStatementSyntax_ReturnType:
        removeReturnType();
        return true;
      case edkLocalFunctionStatementSyntax_TypeParameterList:
        removeTypeParameterList();
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void LocalFunctionStatementSyntax::setBody(NodeId _id) {
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

      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkLocalFunctionStatementSyntax_Body);
      }
      m_Body = _node->getId();
      if (m_Body != 0)
        setParentEdge(factory->getPointer(m_Body), edkLocalFunctionStatementSyntax_Body);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Body, this->getId(), edkLocalFunctionStatementSyntax_Body);
    } else {
      if (m_Body) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LocalFunctionStatementSyntax::setBody(statement::BlockSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void LocalFunctionStatementSyntax::removeBody() {
      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkLocalFunctionStatementSyntax_Body);
      }
      m_Body = 0;
  }

  void LocalFunctionStatementSyntax::addConstraintClauses(const structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTypeParameterConstraintClauseSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ConstraintClausesContainer.push_back(_node->getId());
    setParentEdge(_node,edkLocalFunctionStatementSyntax_ConstraintClauses);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkLocalFunctionStatementSyntax_ConstraintClauses);
  }

  void LocalFunctionStatementSyntax::addConstraintClauses(NodeId _id) {
    const structure::TypeParameterConstraintClauseSyntax *node = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addConstraintClauses( node );
  }

  void LocalFunctionStatementSyntax::removeConstraintClauses(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::iterator it = find(ConstraintClausesContainer.begin(), ConstraintClausesContainer.end(), id);

    if (it == ConstraintClausesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ConstraintClausesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkLocalFunctionStatementSyntax_ConstraintClauses);
  }

  void LocalFunctionStatementSyntax::removeConstraintClauses(structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeConstraintClauses(_node->getId());
  }

  void LocalFunctionStatementSyntax::setExpressionBody(NodeId _id) {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkLocalFunctionStatementSyntax_ExpressionBody);
      }
      m_ExpressionBody = _node->getId();
      if (m_ExpressionBody != 0)
        setParentEdge(factory->getPointer(m_ExpressionBody), edkLocalFunctionStatementSyntax_ExpressionBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExpressionBody, this->getId(), edkLocalFunctionStatementSyntax_ExpressionBody);
    } else {
      if (m_ExpressionBody) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LocalFunctionStatementSyntax::setExpressionBody(structure::ArrowExpressionClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionBody(_node->getId());
  }

  void LocalFunctionStatementSyntax::removeExpressionBody() {
      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkLocalFunctionStatementSyntax_ExpressionBody);
      }
      m_ExpressionBody = 0;
  }

  void LocalFunctionStatementSyntax::setParameterList(NodeId _id) {
    structure::ParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkLocalFunctionStatementSyntax_ParameterList);
      }
      m_ParameterList = _node->getId();
      if (m_ParameterList != 0)
        setParentEdge(factory->getPointer(m_ParameterList), edkLocalFunctionStatementSyntax_ParameterList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ParameterList, this->getId(), edkLocalFunctionStatementSyntax_ParameterList);
    } else {
      if (m_ParameterList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LocalFunctionStatementSyntax::setParameterList(structure::ParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameterList(_node->getId());
  }

  void LocalFunctionStatementSyntax::removeParameterList() {
      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkLocalFunctionStatementSyntax_ParameterList);
      }
      m_ParameterList = 0;
  }

  void LocalFunctionStatementSyntax::setReturnType(NodeId _id) {
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

      if (m_ReturnType) {
        removeParentEdge(m_ReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkLocalFunctionStatementSyntax_ReturnType);
      }
      m_ReturnType = _node->getId();
      if (m_ReturnType != 0)
        setParentEdge(factory->getPointer(m_ReturnType), edkLocalFunctionStatementSyntax_ReturnType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ReturnType, this->getId(), edkLocalFunctionStatementSyntax_ReturnType);
    } else {
      if (m_ReturnType) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LocalFunctionStatementSyntax::setReturnType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void LocalFunctionStatementSyntax::removeReturnType() {
      if (m_ReturnType) {
        removeParentEdge(m_ReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkLocalFunctionStatementSyntax_ReturnType);
      }
      m_ReturnType = 0;
  }

  void LocalFunctionStatementSyntax::setTypeParameterList(NodeId _id) {
    structure::TypeParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::TypeParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_TypeParameterList) {
        removeParentEdge(m_TypeParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_TypeParameterList, m_id, edkLocalFunctionStatementSyntax_TypeParameterList);
      }
      m_TypeParameterList = _node->getId();
      if (m_TypeParameterList != 0)
        setParentEdge(factory->getPointer(m_TypeParameterList), edkLocalFunctionStatementSyntax_TypeParameterList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_TypeParameterList, this->getId(), edkLocalFunctionStatementSyntax_TypeParameterList);
    } else {
      if (m_TypeParameterList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LocalFunctionStatementSyntax::setTypeParameterList(structure::TypeParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTypeParameterList(_node->getId());
  }

  void LocalFunctionStatementSyntax::removeTypeParameterList() {
      if (m_TypeParameterList) {
        removeParentEdge(m_TypeParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_TypeParameterList, m_id, edkLocalFunctionStatementSyntax_TypeParameterList);
      }
      m_TypeParameterList = 0;
  }

  void LocalFunctionStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void LocalFunctionStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double LocalFunctionStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const LocalFunctionStatementSyntax& node = dynamic_cast<const LocalFunctionStatementSyntax&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getIdentifier();
      str2 = node.getIdentifier();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void LocalFunctionStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_identifier);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_identifier = foundKeyId->second;
    } else {
      Key oldkey = m_identifier;
      m_identifier = newStrTable.set(factory->getStringTable().get(m_identifier));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_identifier));    }

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType LocalFunctionStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::LocalFunctionStatementSyntax", strlen("statement::LocalFunctionStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void LocalFunctionStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StatementSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_Body);
    binIo.writeUInt4(m_ExpressionBody);
    binIo.writeUInt4(m_ParameterList);
    binIo.writeUInt4(m_ReturnType);
    binIo.writeUInt4(m_TypeParameterList);


    for (ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::const_iterator it = ConstraintClausesContainer.begin(); it != ConstraintClausesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void LocalFunctionStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StatementSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_Body =  binIo.readUInt4();
    if (m_Body != 0)
      setParentEdge(factory->getPointer(m_Body),edkLocalFunctionStatementSyntax_Body);

    m_ExpressionBody =  binIo.readUInt4();
    if (m_ExpressionBody != 0)
      setParentEdge(factory->getPointer(m_ExpressionBody),edkLocalFunctionStatementSyntax_ExpressionBody);

    m_ParameterList =  binIo.readUInt4();
    if (m_ParameterList != 0)
      setParentEdge(factory->getPointer(m_ParameterList),edkLocalFunctionStatementSyntax_ParameterList);

    m_ReturnType =  binIo.readUInt4();
    if (m_ReturnType != 0)
      setParentEdge(factory->getPointer(m_ReturnType),edkLocalFunctionStatementSyntax_ReturnType);

    m_TypeParameterList =  binIo.readUInt4();
    if (m_TypeParameterList != 0)
      setParentEdge(factory->getPointer(m_TypeParameterList),edkLocalFunctionStatementSyntax_TypeParameterList);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ConstraintClausesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkLocalFunctionStatementSyntax_ConstraintClauses);
      _id = binIo.readUInt4();
    }
  }


}


}}}
