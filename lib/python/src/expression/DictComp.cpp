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
  DictComp::DictComp(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_hasKeyValue(0),
    hasGeneratorContainer()
  {
  }

  DictComp::~DictComp() {
  }

  void DictComp::prepareDelete(bool tryOnVirtualParent){
    removeKeyValue();
    while (!hasGeneratorContainer.empty()) {
      const NodeId id = *hasGeneratorContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkDictComp_HasGenerator);
      hasGeneratorContainer.pop_front();
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind DictComp::getNodeKind() const {
    return ndkDictComp;
  }

  expression::KeyValue* DictComp::getKeyValue() const {
    expression::KeyValue *_node = NULL;
    if (m_hasKeyValue != 0)
      _node = dynamic_cast<expression::KeyValue*>(factory->getPointer(m_hasKeyValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expression::Generator> DictComp::getGeneratorListIteratorBegin() const {
    return ListIterator<expression::Generator>(&hasGeneratorContainer, factory, true);
  }

  ListIterator<expression::Generator> DictComp::getGeneratorListIteratorEnd() const {
    return ListIterator<expression::Generator>(&hasGeneratorContainer, factory, false);
  }

  bool DictComp::getGeneratorIsEmpty() const {
    return getGeneratorListIteratorBegin() == getGeneratorListIteratorEnd();
  }

  unsigned int DictComp::getGeneratorSize() const {
    unsigned int size = 0;
    ListIterator<expression::Generator> endIt = getGeneratorListIteratorEnd();
    for (ListIterator<expression::Generator> it = getGeneratorListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool DictComp::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDictComp_HasKeyValue:
        setKeyValue(edgeEnd);
        return true;
      case edkDictComp_HasGenerator:
        addGenerator(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool DictComp::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDictComp_HasKeyValue:
        removeKeyValue();
        return true;
      case edkDictComp_HasGenerator:
        removeGenerator(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void DictComp::setKeyValue(NodeId _id) {
    expression::KeyValue *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::KeyValue*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasKeyValue) {
        removeParentEdge(m_hasKeyValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasKeyValue, m_id, edkDictComp_HasKeyValue);
      }
      m_hasKeyValue = _node->getId();
      if (m_hasKeyValue != 0)
        setParentEdge(factory->getPointer(m_hasKeyValue), edkDictComp_HasKeyValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasKeyValue, this->getId(), edkDictComp_HasKeyValue);
    } else {
      if (m_hasKeyValue) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DictComp::setKeyValue(expression::KeyValue *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setKeyValue(_node->getId());
  }

  void DictComp::removeKeyValue() {
      if (m_hasKeyValue) {
        removeParentEdge(m_hasKeyValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasKeyValue, m_id, edkDictComp_HasKeyValue);
      }
      m_hasKeyValue = 0;
  }

  void DictComp::addGenerator(const expression::Generator *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkGenerator) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasGeneratorContainer.push_back(_node->getId());
    setParentEdge(_node,edkDictComp_HasGenerator);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkDictComp_HasGenerator);
  }

  void DictComp::addGenerator(NodeId _id) {
    const expression::Generator *node = dynamic_cast<expression::Generator*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addGenerator( node );
  }

  void DictComp::removeGenerator(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Generator>::Container::iterator it = find(hasGeneratorContainer.begin(), hasGeneratorContainer.end(), id);

    if (it == hasGeneratorContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasGeneratorContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkDictComp_HasGenerator);
  }

  void DictComp::removeGenerator(expression::Generator *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeGenerator(_node->getId());
  }

  void DictComp::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void DictComp::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double DictComp::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void DictComp::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType DictComp::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::DictComp", strlen("expression::DictComp"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void DictComp::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasKeyValue);


    for (ListIterator<expression::Generator>::Container::const_iterator it = hasGeneratorContainer.begin(); it != hasGeneratorContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void DictComp::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    m_hasKeyValue =  binIo.readUInt4();
    if (m_hasKeyValue != 0)
      setParentEdge(factory->getPointer(m_hasKeyValue),edkDictComp_HasKeyValue);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasGeneratorContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkDictComp_HasGenerator);
      _id = binIo.readUInt4();
    }
  }


}


}}}
