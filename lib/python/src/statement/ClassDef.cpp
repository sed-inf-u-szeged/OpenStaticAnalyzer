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

namespace statement { 
  ClassDef::ClassDef(NodeId _id, Factory *_factory) :
    CompoundStatement(_id, _factory),
    m_lloc(0),
    m_name(0),
    hasObjectContainer(),
    hasBaseSpecifierContainer(),
    hasDecoratorContainer(),
    m_refersTo(0),
    m_docstring(0)
  {
  }

  ClassDef::~ClassDef() {
  }

  void ClassDef::prepareDelete(bool tryOnVirtualParent){
    while (!hasObjectContainer.empty()) {
      const NodeId id = *hasObjectContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClassDef_HasObject);
      hasObjectContainer.pop_front();
    }
    while (!hasBaseSpecifierContainer.empty()) {
      const NodeId id = *hasBaseSpecifierContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClassDef_HasBaseSpecifier);
      hasBaseSpecifierContainer.pop_front();
    }
    while (!hasDecoratorContainer.empty()) {
      const NodeId id = *hasDecoratorContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClassDef_HasDecorator);
      hasDecoratorContainer.pop_front();
    }
    removeRefersTo();
    removeDocstring();
    statement::CompoundStatement::prepareDelete(false);
  }

  NodeKind ClassDef::getNodeKind() const {
    return ndkClassDef;
  }

  Key ClassDef::getNameKey() const {
    return m_name;
  }

  const std::string& ClassDef::getName() const {
    return factory->getStringTable().get(m_name);
  }

  int ClassDef::getLloc() const {
    return m_lloc;
  }

  void ClassDef::setNameKey(Key _name) {
    m_name = _name;
  }

  void ClassDef::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  void ClassDef::setLloc(int _lloc) {
    m_lloc = _lloc;
  }

  ListIterator<module::Object> ClassDef::getObjectListIteratorBegin() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, true);
  }

  ListIterator<module::Object> ClassDef::getObjectListIteratorEnd() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, false);
  }

  bool ClassDef::getObjectIsEmpty() const {
    return getObjectListIteratorBegin() == getObjectListIteratorEnd();
  }

  unsigned int ClassDef::getObjectSize() const {
    unsigned int size = 0;
    ListIterator<module::Object> endIt = getObjectListIteratorEnd();
    for (ListIterator<module::Object> it = getObjectListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<statement::BaseSpecifier> ClassDef::getBaseSpecifierListIteratorBegin() const {
    return ListIterator<statement::BaseSpecifier>(&hasBaseSpecifierContainer, factory, true);
  }

  ListIterator<statement::BaseSpecifier> ClassDef::getBaseSpecifierListIteratorEnd() const {
    return ListIterator<statement::BaseSpecifier>(&hasBaseSpecifierContainer, factory, false);
  }

  bool ClassDef::getBaseSpecifierIsEmpty() const {
    return getBaseSpecifierListIteratorBegin() == getBaseSpecifierListIteratorEnd();
  }

  unsigned int ClassDef::getBaseSpecifierSize() const {
    unsigned int size = 0;
    ListIterator<statement::BaseSpecifier> endIt = getBaseSpecifierListIteratorEnd();
    for (ListIterator<statement::BaseSpecifier> it = getBaseSpecifierListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<expression::Expression> ClassDef::getDecoratorListIteratorBegin() const {
    return ListIterator<expression::Expression>(&hasDecoratorContainer, factory, true);
  }

  ListIterator<expression::Expression> ClassDef::getDecoratorListIteratorEnd() const {
    return ListIterator<expression::Expression>(&hasDecoratorContainer, factory, false);
  }

  bool ClassDef::getDecoratorIsEmpty() const {
    return getDecoratorListIteratorBegin() == getDecoratorListIteratorEnd();
  }

  unsigned int ClassDef::getDecoratorSize() const {
    unsigned int size = 0;
    ListIterator<expression::Expression> endIt = getDecoratorListIteratorEnd();
    for (ListIterator<expression::Expression> it = getDecoratorListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  module::Object* ClassDef::getRefersTo() const {
    module::Object *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<module::Object*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  base::Docstring* ClassDef::getDocstring() const {
    base::Docstring *_node = NULL;
    if (m_docstring != 0)
      _node = dynamic_cast<base::Docstring*>(factory->getPointer(m_docstring));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ClassDef::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClassDef_HasObject:
        addObject(edgeEnd);
        return true;
      case edkClassDef_HasBaseSpecifier:
        addBaseSpecifier(edgeEnd);
        return true;
      case edkClassDef_HasDecorator:
        addDecorator(edgeEnd);
        return true;
      case edkClassDef_RefersTo:
        setRefersTo(edgeEnd);
        return true;
      case edkClassDef_Docstring:
        setDocstring(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ClassDef::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClassDef_HasObject:
        removeObject(edgeEnd);
        return true;
      case edkClassDef_HasBaseSpecifier:
        removeBaseSpecifier(edgeEnd);
        return true;
      case edkClassDef_HasDecorator:
        removeDecorator(edgeEnd);
        return true;
      case edkClassDef_RefersTo:
        removeRefersTo();
        return true;
      case edkClassDef_Docstring:
        removeDocstring();
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ClassDef::addObject(const module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkObject) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasObjectContainer.push_back(_node->getId());
    setParentEdge(_node,edkClassDef_HasObject);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClassDef_HasObject);
  }

  void ClassDef::addObject(NodeId _id) {
    const module::Object *node = dynamic_cast<module::Object*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addObject( node );
  }

  void ClassDef::removeObject(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<module::Object>::Container::iterator it = find(hasObjectContainer.begin(), hasObjectContainer.end(), id);

    if (it == hasObjectContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasObjectContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClassDef_HasObject);
  }

  void ClassDef::removeObject(module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeObject(_node->getId());
  }

  void ClassDef::addBaseSpecifier(const statement::BaseSpecifier *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkBaseSpecifier) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasBaseSpecifierContainer.push_back(_node->getId());
    setParentEdge(_node,edkClassDef_HasBaseSpecifier);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClassDef_HasBaseSpecifier);
  }

  void ClassDef::addBaseSpecifier(NodeId _id) {
    const statement::BaseSpecifier *node = dynamic_cast<statement::BaseSpecifier*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addBaseSpecifier( node );
  }

  void ClassDef::removeBaseSpecifier(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::BaseSpecifier>::Container::iterator it = find(hasBaseSpecifierContainer.begin(), hasBaseSpecifierContainer.end(), id);

    if (it == hasBaseSpecifierContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasBaseSpecifierContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClassDef_HasBaseSpecifier);
  }

  void ClassDef::removeBaseSpecifier(statement::BaseSpecifier *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeBaseSpecifier(_node->getId());
  }

  void ClassDef::addDecorator(const expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasDecoratorContainer.push_back(_node->getId());
    setParentEdge(_node,edkClassDef_HasDecorator);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClassDef_HasDecorator);
  }

  void ClassDef::addDecorator(NodeId _id) {
    const expression::Expression *node = dynamic_cast<expression::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addDecorator( node );
  }

  void ClassDef::removeDecorator(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Expression>::Container::iterator it = find(hasDecoratorContainer.begin(), hasDecoratorContainer.end(), id);

    if (it == hasDecoratorContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasDecoratorContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClassDef_HasDecorator);
  }

  void ClassDef::removeDecorator(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeDecorator(_node->getId());
  }

  void ClassDef::setRefersTo(NodeId _id) {
    module::Object *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<module::Object*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkClassDef_RefersTo);
      }
      m_refersTo = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkClassDef_RefersTo);
    } else {
      if (m_refersTo) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ClassDef::setRefersTo(module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void ClassDef::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkClassDef_RefersTo);
      }
      m_refersTo = 0;
  }

  void ClassDef::setDocstring(NodeId _id) {
    base::Docstring *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Docstring*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_docstring) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_docstring, m_id, edkClassDef_Docstring);
      }
      m_docstring = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_docstring, this->getId(), edkClassDef_Docstring);
    } else {
      if (m_docstring) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ClassDef::setDocstring(base::Docstring *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDocstring(_node->getId());
  }

  void ClassDef::removeDocstring() {
      if (m_docstring) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_docstring, m_id, edkClassDef_Docstring);
      }
      m_docstring = 0;
  }

  void ClassDef::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ClassDef::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ClassDef::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ClassDef& node = dynamic_cast<const ClassDef&>(base);
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
      if(node.getLloc() == getLloc()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ClassDef::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType ClassDef::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ClassDef", strlen("statement::ClassDef"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ClassDef::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CompoundStatement::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);
    binIo.writeUInt4(m_lloc);

    binIo.writeUInt4(m_refersTo);
    binIo.writeUInt4(m_docstring);


    for (ListIterator<module::Object>::Container::const_iterator it = hasObjectContainer.begin(); it != hasObjectContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<statement::BaseSpecifier>::Container::const_iterator it = hasBaseSpecifierContainer.begin(); it != hasBaseSpecifierContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<expression::Expression>::Container::const_iterator it = hasDecoratorContainer.begin(); it != hasDecoratorContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ClassDef::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CompoundStatement::load(binIo,false);

    m_name = binIo.readUInt4();
    m_lloc = binIo.readUInt4();

    m_refersTo =  binIo.readUInt4();

    m_docstring =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasObjectContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkClassDef_HasObject);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasBaseSpecifierContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkClassDef_HasBaseSpecifier);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasDecoratorContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkClassDef_HasDecorator);
      _id = binIo.readUInt4();
    }
  }


}


}}}
