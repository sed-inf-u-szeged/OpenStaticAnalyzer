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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  Lambda::Lambda(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    hasObjectContainer(),
    hasParameterContainer(),
    m_hasExpression(0)
  {
  }

  Lambda::~Lambda() {
  }

  void Lambda::prepareDelete(bool tryOnVirtualParent){
    while (!hasObjectContainer.empty()) {
      const NodeId id = *hasObjectContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkLambda_HasObject);
      hasObjectContainer.pop_front();
    }
    while (!hasParameterContainer.empty()) {
      const NodeId id = *hasParameterContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkLambda_HasParameter);
      hasParameterContainer.pop_front();
    }
    removeExpression();
    expression::Expression::prepareDelete(false);
  }

  NodeKind Lambda::getNodeKind() const {
    return ndkLambda;
  }

  ListIterator<module::Object> Lambda::getObjectListIteratorBegin() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, true);
  }

  ListIterator<module::Object> Lambda::getObjectListIteratorEnd() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, false);
  }

  bool Lambda::getObjectIsEmpty() const {
    return getObjectListIteratorBegin() == getObjectListIteratorEnd();
  }

  unsigned int Lambda::getObjectSize() const {
    unsigned int size = 0;
    ListIterator<module::Object> endIt = getObjectListIteratorEnd();
    for (ListIterator<module::Object> it = getObjectListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<statement::Parameter> Lambda::getParameterListIteratorBegin() const {
    return ListIterator<statement::Parameter>(&hasParameterContainer, factory, true);
  }

  ListIterator<statement::Parameter> Lambda::getParameterListIteratorEnd() const {
    return ListIterator<statement::Parameter>(&hasParameterContainer, factory, false);
  }

  bool Lambda::getParameterIsEmpty() const {
    return getParameterListIteratorBegin() == getParameterListIteratorEnd();
  }

  unsigned int Lambda::getParameterSize() const {
    unsigned int size = 0;
    ListIterator<statement::Parameter> endIt = getParameterListIteratorEnd();
    for (ListIterator<statement::Parameter> it = getParameterListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::Expression* Lambda::getExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Lambda::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLambda_HasObject:
        addObject(edgeEnd);
        return true;
      case edkLambda_HasParameter:
        addParameter(edgeEnd);
        return true;
      case edkLambda_HasExpression:
        setExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Lambda::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLambda_HasObject:
        removeObject(edgeEnd);
        return true;
      case edkLambda_HasParameter:
        removeParameter(edgeEnd);
        return true;
      case edkLambda_HasExpression:
        removeExpression();
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Lambda::addObject(const module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkObject) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasObjectContainer.push_back(_node->getId());
    setParentEdge(_node,edkLambda_HasObject);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkLambda_HasObject);
  }

  void Lambda::addObject(NodeId _id) {
    const module::Object *node = dynamic_cast<module::Object*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addObject( node );
  }

  void Lambda::removeObject(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<module::Object>::Container::iterator it = find(hasObjectContainer.begin(), hasObjectContainer.end(), id);

    if (it == hasObjectContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasObjectContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkLambda_HasObject);
  }

  void Lambda::removeObject(module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeObject(_node->getId());
  }

  void Lambda::addParameter(const statement::Parameter *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkParameter) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasParameterContainer.push_back(_node->getId());
    setParentEdge(_node,edkLambda_HasParameter);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkLambda_HasParameter);
  }

  void Lambda::addParameter(NodeId _id) {
    const statement::Parameter *node = dynamic_cast<statement::Parameter*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameter( node );
  }

  void Lambda::removeParameter(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Parameter>::Container::iterator it = find(hasParameterContainer.begin(), hasParameterContainer.end(), id);

    if (it == hasParameterContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParameterContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkLambda_HasParameter);
  }

  void Lambda::removeParameter(statement::Parameter *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameter(_node->getId());
  }

  void Lambda::setExpression(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkLambda_HasExpression);
      }
      m_hasExpression = _node->getId();
      if (m_hasExpression != 0)
        setParentEdge(factory->getPointer(m_hasExpression), edkLambda_HasExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpression, this->getId(), edkLambda_HasExpression);
    } else {
      if (m_hasExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Lambda::setExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void Lambda::removeExpression() {
      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkLambda_HasExpression);
      }
      m_hasExpression = 0;
  }

  void Lambda::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Lambda::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Lambda::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Lambda::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Lambda::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Lambda", strlen("expression::Lambda"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Lambda::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasExpression);


    for (ListIterator<module::Object>::Container::const_iterator it = hasObjectContainer.begin(); it != hasObjectContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<statement::Parameter>::Container::const_iterator it = hasParameterContainer.begin(); it != hasParameterContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Lambda::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    m_hasExpression =  binIo.readUInt4();
    if (m_hasExpression != 0)
      setParentEdge(factory->getPointer(m_hasExpression),edkLambda_HasExpression);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasObjectContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkLambda_HasObject);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasParameterContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkLambda_HasParameter);
      _id = binIo.readUInt4();
    }
  }


}


}}}
