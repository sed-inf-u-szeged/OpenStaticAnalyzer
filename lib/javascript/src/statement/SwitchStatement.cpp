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
  SwitchStatement::SwitchStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasDiscriminant(0),
    hasCasesContainer()
  {
  }

  SwitchStatement::~SwitchStatement() {
  }

  void SwitchStatement::prepareDelete(bool tryOnVirtualParent){
    removeDiscriminant();
    while (!hasCasesContainer.empty()) {
      const NodeId id = *hasCasesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatement_HasCases);
      hasCasesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind SwitchStatement::getNodeKind() const {
    return ndkSwitchStatement;
  }

  expression::Expression* SwitchStatement::getDiscriminant() const {
    expression::Expression *_node = NULL;
    if (m_hasDiscriminant != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasDiscriminant));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<statement::SwitchCase> SwitchStatement::getCasesListIteratorBegin() const {
    return ListIterator<statement::SwitchCase>(&hasCasesContainer, factory, true);
  }

  ListIterator<statement::SwitchCase> SwitchStatement::getCasesListIteratorEnd() const {
    return ListIterator<statement::SwitchCase>(&hasCasesContainer, factory, false);
  }

  bool SwitchStatement::getCasesIsEmpty() const {
    return getCasesListIteratorBegin() == getCasesListIteratorEnd();
  }

  unsigned int SwitchStatement::getCasesSize() const {
    unsigned int size = 0;
    ListIterator<statement::SwitchCase> endIt = getCasesListIteratorEnd();
    for (ListIterator<statement::SwitchCase> it = getCasesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool SwitchStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatement_HasDiscriminant:
        setDiscriminant(edgeEnd);
        return true;
      case edkSwitchStatement_HasCases:
        addCases(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SwitchStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatement_HasDiscriminant:
        removeDiscriminant();
        return true;
      case edkSwitchStatement_HasCases:
        removeCases(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SwitchStatement::setDiscriminant(NodeId _id) {
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

      if (m_hasDiscriminant) {
        removeParentEdge(m_hasDiscriminant);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDiscriminant, m_id, edkSwitchStatement_HasDiscriminant);
      }
      m_hasDiscriminant = _node->getId();
      if (m_hasDiscriminant != 0)
        setParentEdge(factory->getPointer(m_hasDiscriminant), edkSwitchStatement_HasDiscriminant);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasDiscriminant, this->getId(), edkSwitchStatement_HasDiscriminant);
    } else {
      if (m_hasDiscriminant) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void SwitchStatement::setDiscriminant(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDiscriminant(_node->getId());
  }

  void SwitchStatement::removeDiscriminant() {
      if (m_hasDiscriminant) {
        removeParentEdge(m_hasDiscriminant);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDiscriminant, m_id, edkSwitchStatement_HasDiscriminant);
      }
      m_hasDiscriminant = 0;
  }

  void SwitchStatement::addCases(const statement::SwitchCase *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkSwitchCase) ))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasCasesContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchStatement_HasCases);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchStatement_HasCases);
  }

  void SwitchStatement::addCases(NodeId _id) {
    const statement::SwitchCase *node = dynamic_cast<statement::SwitchCase*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCases( node );
  }

  void SwitchStatement::removeCases(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::SwitchCase>::Container::iterator it = find(hasCasesContainer.begin(), hasCasesContainer.end(), id);

    if (it == hasCasesContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasCasesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatement_HasCases);
  }

  void SwitchStatement::removeCases(statement::SwitchCase *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCases(_node->getId());
  }

  void SwitchStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SwitchStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SwitchStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void SwitchStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType SwitchStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::SwitchStatement", strlen("statement::SwitchStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasDiscriminant);


    for (ListIterator<statement::SwitchCase>::Container::const_iterator it = hasCasesContainer.begin(); it != hasCasesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasDiscriminant =  binIo.readUInt4();
    if (m_hasDiscriminant != 0)
      setParentEdge(factory->getPointer(m_hasDiscriminant),edkSwitchStatement_HasDiscriminant);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasCasesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchStatement_HasCases);
      _id = binIo.readUInt4();
    }
  }


}


}}}
