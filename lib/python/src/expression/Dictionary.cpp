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
  Dictionary::Dictionary(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    hasKeyValueContainer()
  {
  }

  Dictionary::~Dictionary() {
  }

  void Dictionary::prepareDelete(bool tryOnVirtualParent){
    while (!hasKeyValueContainer.empty()) {
      const NodeId id = *hasKeyValueContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkDictionary_HasKeyValue);
      hasKeyValueContainer.pop_front();
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind Dictionary::getNodeKind() const {
    return ndkDictionary;
  }

  ListIterator<expression::KeyValue> Dictionary::getKeyValueListIteratorBegin() const {
    return ListIterator<expression::KeyValue>(&hasKeyValueContainer, factory, true);
  }

  ListIterator<expression::KeyValue> Dictionary::getKeyValueListIteratorEnd() const {
    return ListIterator<expression::KeyValue>(&hasKeyValueContainer, factory, false);
  }

  bool Dictionary::getKeyValueIsEmpty() const {
    return getKeyValueListIteratorBegin() == getKeyValueListIteratorEnd();
  }

  unsigned int Dictionary::getKeyValueSize() const {
    unsigned int size = 0;
    ListIterator<expression::KeyValue> endIt = getKeyValueListIteratorEnd();
    for (ListIterator<expression::KeyValue> it = getKeyValueListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Dictionary::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDictionary_HasKeyValue:
        addKeyValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Dictionary::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDictionary_HasKeyValue:
        removeKeyValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Dictionary::addKeyValue(const expression::KeyValue *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkKeyValue) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasKeyValueContainer.push_back(_node->getId());
    setParentEdge(_node,edkDictionary_HasKeyValue);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkDictionary_HasKeyValue);
  }

  void Dictionary::addKeyValue(NodeId _id) {
    const expression::KeyValue *node = dynamic_cast<expression::KeyValue*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addKeyValue( node );
  }

  void Dictionary::removeKeyValue(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::KeyValue>::Container::iterator it = find(hasKeyValueContainer.begin(), hasKeyValueContainer.end(), id);

    if (it == hasKeyValueContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasKeyValueContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkDictionary_HasKeyValue);
  }

  void Dictionary::removeKeyValue(expression::KeyValue *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeKeyValue(_node->getId());
  }

  void Dictionary::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Dictionary::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Dictionary::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Dictionary::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Dictionary::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Dictionary", strlen("expression::Dictionary"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Dictionary::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);


    for (ListIterator<expression::KeyValue>::Container::const_iterator it = hasKeyValueContainer.begin(); it != hasKeyValueContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Dictionary::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasKeyValueContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkDictionary_HasKeyValue);
      _id = binIo.readUInt4();
    }
  }


}


}}}
