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
  Generator::Generator(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    hasConditionContainer(),
    m_hasIter(0),
    m_hasTarget(0)
  {
  }

  Generator::~Generator() {
  }

  void Generator::prepareDelete(bool tryOnVirtualParent){
    while (!hasConditionContainer.empty()) {
      const NodeId id = *hasConditionContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkGenerator_HasCondition);
      hasConditionContainer.pop_front();
    }
    removeIter();
    removeTarget();
    base::Positioned::prepareDelete(false);
  }

  NodeKind Generator::getNodeKind() const {
    return ndkGenerator;
  }

  ListIterator<expression::Expression> Generator::getConditionListIteratorBegin() const {
    return ListIterator<expression::Expression>(&hasConditionContainer, factory, true);
  }

  ListIterator<expression::Expression> Generator::getConditionListIteratorEnd() const {
    return ListIterator<expression::Expression>(&hasConditionContainer, factory, false);
  }

  bool Generator::getConditionIsEmpty() const {
    return getConditionListIteratorBegin() == getConditionListIteratorEnd();
  }

  unsigned int Generator::getConditionSize() const {
    unsigned int size = 0;
    ListIterator<expression::Expression> endIt = getConditionListIteratorEnd();
    for (ListIterator<expression::Expression> it = getConditionListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::Expression* Generator::getIter() const {
    expression::Expression *_node = NULL;
    if (m_hasIter != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasIter));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Generator::getTarget() const {
    expression::Expression *_node = NULL;
    if (m_hasTarget != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTarget));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Generator::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenerator_HasCondition:
        addCondition(edgeEnd);
        return true;
      case edkGenerator_HasIter:
        setIter(edgeEnd);
        return true;
      case edkGenerator_HasTarget:
        setTarget(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Generator::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenerator_HasCondition:
        removeCondition(edgeEnd);
        return true;
      case edkGenerator_HasIter:
        removeIter();
        return true;
      case edkGenerator_HasTarget:
        removeTarget();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Generator::addCondition(const expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasConditionContainer.push_back(_node->getId());
    setParentEdge(_node,edkGenerator_HasCondition);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkGenerator_HasCondition);
  }

  void Generator::addCondition(NodeId _id) {
    const expression::Expression *node = dynamic_cast<expression::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCondition( node );
  }

  void Generator::removeCondition(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Expression>::Container::iterator it = find(hasConditionContainer.begin(), hasConditionContainer.end(), id);

    if (it == hasConditionContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasConditionContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkGenerator_HasCondition);
  }

  void Generator::removeCondition(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCondition(_node->getId());
  }

  void Generator::setIter(NodeId _id) {
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

      if (m_hasIter) {
        removeParentEdge(m_hasIter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIter, m_id, edkGenerator_HasIter);
      }
      m_hasIter = _node->getId();
      if (m_hasIter != 0)
        setParentEdge(factory->getPointer(m_hasIter), edkGenerator_HasIter);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasIter, this->getId(), edkGenerator_HasIter);
    } else {
      if (m_hasIter) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Generator::setIter(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setIter(_node->getId());
  }

  void Generator::removeIter() {
      if (m_hasIter) {
        removeParentEdge(m_hasIter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIter, m_id, edkGenerator_HasIter);
      }
      m_hasIter = 0;
  }

  void Generator::setTarget(NodeId _id) {
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

      if (m_hasTarget) {
        removeParentEdge(m_hasTarget);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkGenerator_HasTarget);
      }
      m_hasTarget = _node->getId();
      if (m_hasTarget != 0)
        setParentEdge(factory->getPointer(m_hasTarget), edkGenerator_HasTarget);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTarget, this->getId(), edkGenerator_HasTarget);
    } else {
      if (m_hasTarget) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Generator::setTarget(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTarget(_node->getId());
  }

  void Generator::removeTarget() {
      if (m_hasTarget) {
        removeParentEdge(m_hasTarget);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkGenerator_HasTarget);
      }
      m_hasTarget = 0;
  }

  void Generator::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Generator::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Generator::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Generator::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Generator::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Generator", strlen("expression::Generator"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Generator::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasIter);
    binIo.writeUInt4(m_hasTarget);


    for (ListIterator<expression::Expression>::Container::const_iterator it = hasConditionContainer.begin(); it != hasConditionContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Generator::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasIter =  binIo.readUInt4();
    if (m_hasIter != 0)
      setParentEdge(factory->getPointer(m_hasIter),edkGenerator_HasIter);

    m_hasTarget =  binIo.readUInt4();
    if (m_hasTarget != 0)
      setParentEdge(factory->getPointer(m_hasTarget),edkGenerator_HasTarget);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasConditionContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkGenerator_HasCondition);
      _id = binIo.readUInt4();
    }
  }


}


}}}
