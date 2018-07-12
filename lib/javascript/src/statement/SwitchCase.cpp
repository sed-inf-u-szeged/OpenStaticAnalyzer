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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statement { 
  SwitchCase::SwitchCase(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasTest(0),
    hasConsequentContainer()
  {
  }

  SwitchCase::~SwitchCase() {
  }

  void SwitchCase::prepareDelete(bool tryOnVirtualParent){
    removeTest();
    while (!hasConsequentContainer.empty()) {
      const NodeId id = *hasConsequentContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchCase_HasConsequent);
      hasConsequentContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind SwitchCase::getNodeKind() const {
    return ndkSwitchCase;
  }

  expression::Expression* SwitchCase::getTest() const {
    expression::Expression *_node = NULL;
    if (m_hasTest != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTest));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<statement::Statement> SwitchCase::getConsequentListIteratorBegin() const {
    return ListIterator<statement::Statement>(&hasConsequentContainer, factory, true);
  }

  ListIterator<statement::Statement> SwitchCase::getConsequentListIteratorEnd() const {
    return ListIterator<statement::Statement>(&hasConsequentContainer, factory, false);
  }

  bool SwitchCase::getConsequentIsEmpty() const {
    return getConsequentListIteratorBegin() == getConsequentListIteratorEnd();
  }

  unsigned int SwitchCase::getConsequentSize() const {
    unsigned int size = 0;
    ListIterator<statement::Statement> endIt = getConsequentListIteratorEnd();
    for (ListIterator<statement::Statement> it = getConsequentListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool SwitchCase::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchCase_HasTest:
        setTest(edgeEnd);
        return true;
      case edkSwitchCase_HasConsequent:
        addConsequent(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SwitchCase::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchCase_HasTest:
        removeTest();
        return true;
      case edkSwitchCase_HasConsequent:
        removeConsequent(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SwitchCase::setTest(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkSwitchCase_HasTest);
      }
      m_hasTest = _node->getId();
      if (m_hasTest != 0)
        setParentEdge(factory->getPointer(m_hasTest), edkSwitchCase_HasTest);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTest, this->getId(), edkSwitchCase_HasTest);
    } else {
      if (m_hasTest) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void SwitchCase::setTest(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTest(_node->getId());
  }

  void SwitchCase::removeTest() {
      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkSwitchCase_HasTest);
      }
      m_hasTest = 0;
  }

  void SwitchCase::addConsequent(const statement::Statement *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node)))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasConsequentContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchCase_HasConsequent);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchCase_HasConsequent);
  }

  void SwitchCase::addConsequent(NodeId _id) {
    const statement::Statement *node = dynamic_cast<statement::Statement*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addConsequent( node );
  }

  void SwitchCase::removeConsequent(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Statement>::Container::iterator it = find(hasConsequentContainer.begin(), hasConsequentContainer.end(), id);

    if (it == hasConsequentContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasConsequentContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchCase_HasConsequent);
  }

  void SwitchCase::removeConsequent(statement::Statement *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeConsequent(_node->getId());
  }

  void SwitchCase::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SwitchCase::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SwitchCase::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void SwitchCase::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType SwitchCase::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::SwitchCase", strlen("statement::SwitchCase"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchCase::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasTest);


    for (ListIterator<statement::Statement>::Container::const_iterator it = hasConsequentContainer.begin(); it != hasConsequentContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchCase::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasTest =  binIo.readUInt4();
    if (m_hasTest != 0)
      setParentEdge(factory->getPointer(m_hasTest),edkSwitchCase_HasTest);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasConsequentContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchCase_HasConsequent);
      _id = binIo.readUInt4();
    }
  }


}


}}}
