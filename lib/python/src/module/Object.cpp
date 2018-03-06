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

namespace module { 
  Object::Object(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_name(0),
    refersToContainer(),
    hasTypeContainer()
  {
  }

  Object::~Object() {
  }

  void Object::prepareDelete(bool tryOnVirtualParent){
    while (!refersToContainer.empty()) {
      const NodeId id = *refersToContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkObject_RefersTo);
      refersToContainer.pop_front();
    }
    while (!hasTypeContainer.empty()) {
      const NodeId id = *hasTypeContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkObject_HasType);
      hasTypeContainer.pop_front();
    }
    base::Base::prepareDelete(false);
  }

  NodeKind Object::getNodeKind() const {
    return ndkObject;
  }

  Key Object::getNameKey() const {
    return m_name;
  }

  const std::string& Object::getName() const {
    return factory->getStringTable().get(m_name);
  }

  void Object::setNameKey(Key _name) {
    m_name = _name;
  }

  void Object::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  ListIterator<base::Positioned> Object::getRefersToListIteratorBegin() const {
    return ListIterator<base::Positioned>(&refersToContainer, factory, true);
  }

  ListIterator<base::Positioned> Object::getRefersToListIteratorEnd() const {
    return ListIterator<base::Positioned>(&refersToContainer, factory, false);
  }

  bool Object::getRefersToIsEmpty() const {
    return getRefersToListIteratorBegin() == getRefersToListIteratorEnd();
  }

  unsigned int Object::getRefersToSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getRefersToListIteratorEnd();
    for (ListIterator<base::Positioned> it = getRefersToListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> Object::getTypeListIteratorBegin() const {
    return ListIterator<type::Type>(&hasTypeContainer, factory, true);
  }

  ListIterator<type::Type> Object::getTypeListIteratorEnd() const {
    return ListIterator<type::Type>(&hasTypeContainer, factory, false);
  }

  bool Object::getTypeIsEmpty() const {
    return getTypeListIteratorBegin() == getTypeListIteratorEnd();
  }

  unsigned int Object::getTypeSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getTypeListIteratorEnd();
    for (ListIterator<type::Type> it = getTypeListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Object::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObject_RefersTo:
        addRefersTo(edgeEnd);
        return true;
      case edkObject_HasType:
        addType(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Object::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObject_RefersTo:
        removeRefersTo(edgeEnd);
        return true;
      case edkObject_HasType:
        removeType(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Object::addRefersTo(const base::Positioned *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkClassDef)  || (_node->getNodeKind() == ndkFunctionDef)  || (_node->getNodeKind() == ndkModule)  || (_node->getNodeKind() == ndkIdentifier)  || (_node->getNodeKind() == ndkParameter) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    refersToContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkObject_RefersTo);
  }

  void Object::addRefersTo(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addRefersTo( node );
  }

  void Object::removeRefersTo(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(refersToContainer.begin(), refersToContainer.end(), id);

    if (it == refersToContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    refersToContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkObject_RefersTo);
  }

  void Object::removeRefersTo(base::Positioned *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeRefersTo(_node->getId());
  }

  void Object::addType(const type::Type *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsType(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkObject_HasType);
  }

  void Object::addType(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addType( node );
  }

  void Object::removeType(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(hasTypeContainer.begin(), hasTypeContainer.end(), id);

    if (it == hasTypeContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkObject_HasType);
  }

  void Object::removeType(type::Type *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeType(_node->getId());
  }

  void Object::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Object::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Object::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Object& node = dynamic_cast<const Object&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
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

  void Object::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Object::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "module::Object", strlen("module::Object"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Object::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);


    for (ListIterator<base::Positioned>::Container::const_iterator it = refersToContainer.begin(); it != refersToContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = hasTypeContainer.begin(); it != hasTypeContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Object::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_name = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      refersToContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
