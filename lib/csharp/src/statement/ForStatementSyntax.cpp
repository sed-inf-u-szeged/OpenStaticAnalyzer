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
  ForStatementSyntax::ForStatementSyntax(NodeId _id, Factory *_factory) :
    StatementSyntax(_id, _factory),
    m_Condition(0),
    m_Declaration(0),
    IncrementorsContainer(),
    InitializersContainer(),
    m_Statement(0)
  {
  }

  ForStatementSyntax::~ForStatementSyntax() {
  }

  void ForStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeCondition();
    removeDeclaration();
    while (!IncrementorsContainer.empty()) {
      const NodeId id = *IncrementorsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkForStatementSyntax_Incrementors);
      IncrementorsContainer.pop_front();
    }
    while (!InitializersContainer.empty()) {
      const NodeId id = *InitializersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkForStatementSyntax_Initializers);
      InitializersContainer.pop_front();
    }
    removeStatement();
    statement::StatementSyntax::prepareDelete(false);
  }

  NodeKind ForStatementSyntax::getNodeKind() const {
    return ndkForStatementSyntax;
  }

  expression::ExpressionSyntax* ForStatementSyntax::getCondition() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Condition != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Condition));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::VariableDeclarationSyntax* ForStatementSyntax::getDeclaration() const {
    structure::VariableDeclarationSyntax *_node = NULL;
    if (m_Declaration != 0)
      _node = dynamic_cast<structure::VariableDeclarationSyntax*>(factory->getPointer(m_Declaration));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expression::ExpressionSyntax> ForStatementSyntax::getIncrementorsListIteratorBegin() const {
    return ListIterator<expression::ExpressionSyntax>(&IncrementorsContainer, factory, true);
  }

  ListIterator<expression::ExpressionSyntax> ForStatementSyntax::getIncrementorsListIteratorEnd() const {
    return ListIterator<expression::ExpressionSyntax>(&IncrementorsContainer, factory, false);
  }

  bool ForStatementSyntax::getIncrementorsIsEmpty() const {
    return getIncrementorsListIteratorBegin() == getIncrementorsListIteratorEnd();
  }

  unsigned int ForStatementSyntax::getIncrementorsSize() const {
    unsigned int size = 0;
    ListIterator<expression::ExpressionSyntax> endIt = getIncrementorsListIteratorEnd();
    for (ListIterator<expression::ExpressionSyntax> it = getIncrementorsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<expression::ExpressionSyntax> ForStatementSyntax::getInitializersListIteratorBegin() const {
    return ListIterator<expression::ExpressionSyntax>(&InitializersContainer, factory, true);
  }

  ListIterator<expression::ExpressionSyntax> ForStatementSyntax::getInitializersListIteratorEnd() const {
    return ListIterator<expression::ExpressionSyntax>(&InitializersContainer, factory, false);
  }

  bool ForStatementSyntax::getInitializersIsEmpty() const {
    return getInitializersListIteratorBegin() == getInitializersListIteratorEnd();
  }

  unsigned int ForStatementSyntax::getInitializersSize() const {
    unsigned int size = 0;
    ListIterator<expression::ExpressionSyntax> endIt = getInitializersListIteratorEnd();
    for (ListIterator<expression::ExpressionSyntax> it = getInitializersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  statement::StatementSyntax* ForStatementSyntax::getStatement() const {
    statement::StatementSyntax *_node = NULL;
    if (m_Statement != 0)
      _node = dynamic_cast<statement::StatementSyntax*>(factory->getPointer(m_Statement));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ForStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForStatementSyntax_Condition:
        setCondition(edgeEnd);
        return true;
      case edkForStatementSyntax_Declaration:
        setDeclaration(edgeEnd);
        return true;
      case edkForStatementSyntax_Incrementors:
        addIncrementors(edgeEnd);
        return true;
      case edkForStatementSyntax_Initializers:
        addInitializers(edgeEnd);
        return true;
      case edkForStatementSyntax_Statement:
        setStatement(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ForStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForStatementSyntax_Condition:
        removeCondition();
        return true;
      case edkForStatementSyntax_Declaration:
        removeDeclaration();
        return true;
      case edkForStatementSyntax_Incrementors:
        removeIncrementors(edgeEnd);
        return true;
      case edkForStatementSyntax_Initializers:
        removeInitializers(edgeEnd);
        return true;
      case edkForStatementSyntax_Statement:
        removeStatement();
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ForStatementSyntax::setCondition(NodeId _id) {
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

      if (m_Condition) {
        removeParentEdge(m_Condition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Condition, m_id, edkForStatementSyntax_Condition);
      }
      m_Condition = _node->getId();
      if (m_Condition != 0)
        setParentEdge(factory->getPointer(m_Condition), edkForStatementSyntax_Condition);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Condition, this->getId(), edkForStatementSyntax_Condition);
    } else {
      if (m_Condition) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForStatementSyntax::setCondition(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCondition(_node->getId());
  }

  void ForStatementSyntax::removeCondition() {
      if (m_Condition) {
        removeParentEdge(m_Condition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Condition, m_id, edkForStatementSyntax_Condition);
      }
      m_Condition = 0;
  }

  void ForStatementSyntax::setDeclaration(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkForStatementSyntax_Declaration);
      }
      m_Declaration = _node->getId();
      if (m_Declaration != 0)
        setParentEdge(factory->getPointer(m_Declaration), edkForStatementSyntax_Declaration);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Declaration, this->getId(), edkForStatementSyntax_Declaration);
    } else {
      if (m_Declaration) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForStatementSyntax::setDeclaration(structure::VariableDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDeclaration(_node->getId());
  }

  void ForStatementSyntax::removeDeclaration() {
      if (m_Declaration) {
        removeParentEdge(m_Declaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkForStatementSyntax_Declaration);
      }
      m_Declaration = 0;
  }

  void ForStatementSyntax::addIncrementors(const expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpressionSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    IncrementorsContainer.push_back(_node->getId());
    setParentEdge(_node,edkForStatementSyntax_Incrementors);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkForStatementSyntax_Incrementors);
  }

  void ForStatementSyntax::addIncrementors(NodeId _id) {
    const expression::ExpressionSyntax *node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addIncrementors( node );
  }

  void ForStatementSyntax::removeIncrementors(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::ExpressionSyntax>::Container::iterator it = find(IncrementorsContainer.begin(), IncrementorsContainer.end(), id);

    if (it == IncrementorsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    IncrementorsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkForStatementSyntax_Incrementors);
  }

  void ForStatementSyntax::removeIncrementors(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeIncrementors(_node->getId());
  }

  void ForStatementSyntax::addInitializers(const expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpressionSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    InitializersContainer.push_back(_node->getId());
    setParentEdge(_node,edkForStatementSyntax_Initializers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkForStatementSyntax_Initializers);
  }

  void ForStatementSyntax::addInitializers(NodeId _id) {
    const expression::ExpressionSyntax *node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addInitializers( node );
  }

  void ForStatementSyntax::removeInitializers(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::ExpressionSyntax>::Container::iterator it = find(InitializersContainer.begin(), InitializersContainer.end(), id);

    if (it == InitializersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    InitializersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkForStatementSyntax_Initializers);
  }

  void ForStatementSyntax::removeInitializers(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeInitializers(_node->getId());
  }

  void ForStatementSyntax::setStatement(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Statement, m_id, edkForStatementSyntax_Statement);
      }
      m_Statement = _node->getId();
      if (m_Statement != 0)
        setParentEdge(factory->getPointer(m_Statement), edkForStatementSyntax_Statement);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Statement, this->getId(), edkForStatementSyntax_Statement);
    } else {
      if (m_Statement) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForStatementSyntax::setStatement(statement::StatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setStatement(_node->getId());
  }

  void ForStatementSyntax::removeStatement() {
      if (m_Statement) {
        removeParentEdge(m_Statement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Statement, m_id, edkForStatementSyntax_Statement);
      }
      m_Statement = 0;
  }

  void ForStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ForStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ForStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ForStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ForStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ForStatementSyntax", strlen("statement::ForStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ForStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StatementSyntax::save(binIo,false);

    binIo.writeUInt4(m_Condition);
    binIo.writeUInt4(m_Declaration);
    binIo.writeUInt4(m_Statement);


    for (ListIterator<expression::ExpressionSyntax>::Container::const_iterator it = IncrementorsContainer.begin(); it != IncrementorsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<expression::ExpressionSyntax>::Container::const_iterator it = InitializersContainer.begin(); it != InitializersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ForStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StatementSyntax::load(binIo,false);

    m_Condition =  binIo.readUInt4();
    if (m_Condition != 0)
      setParentEdge(factory->getPointer(m_Condition),edkForStatementSyntax_Condition);

    m_Declaration =  binIo.readUInt4();
    if (m_Declaration != 0)
      setParentEdge(factory->getPointer(m_Declaration),edkForStatementSyntax_Declaration);

    m_Statement =  binIo.readUInt4();
    if (m_Statement != 0)
      setParentEdge(factory->getPointer(m_Statement),edkForStatementSyntax_Statement);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      IncrementorsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkForStatementSyntax_Incrementors);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      InitializersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkForStatementSyntax_Initializers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
