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
  FunctionDef::FunctionDef(NodeId _id, Factory *_factory) :
    CompoundStatement(_id, _factory),
    m_lloc(0),
    m_name(0),
    hasDecoratorContainer(),
    hasObjectContainer(),
    hasParameterContainer(),
    m_refersTo(0),
    m_returnType(0),
    m_docstring(0)
  {
  }

  FunctionDef::~FunctionDef() {
  }

  void FunctionDef::prepareDelete(bool tryOnVirtualParent){
    while (!hasDecoratorContainer.empty()) {
      const NodeId id = *hasDecoratorContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFunctionDef_HasDecorator);
      hasDecoratorContainer.pop_front();
    }
    while (!hasObjectContainer.empty()) {
      const NodeId id = *hasObjectContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFunctionDef_HasObject);
      hasObjectContainer.pop_front();
    }
    while (!hasParameterContainer.empty()) {
      const NodeId id = *hasParameterContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFunctionDef_HasParameter);
      hasParameterContainer.pop_front();
    }
    removeRefersTo();
    removeReturnType();
    removeDocstring();
    statement::CompoundStatement::prepareDelete(false);
  }

  NodeKind FunctionDef::getNodeKind() const {
    return ndkFunctionDef;
  }

  Key FunctionDef::getNameKey() const {
    return m_name;
  }

  const std::string& FunctionDef::getName() const {
    return factory->getStringTable().get(m_name);
  }

  int FunctionDef::getLloc() const {
    return m_lloc;
  }

  void FunctionDef::setNameKey(Key _name) {
    m_name = _name;
  }

  void FunctionDef::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  void FunctionDef::setLloc(int _lloc) {
    m_lloc = _lloc;
  }

  ListIterator<expression::Expression> FunctionDef::getDecoratorListIteratorBegin() const {
    return ListIterator<expression::Expression>(&hasDecoratorContainer, factory, true);
  }

  ListIterator<expression::Expression> FunctionDef::getDecoratorListIteratorEnd() const {
    return ListIterator<expression::Expression>(&hasDecoratorContainer, factory, false);
  }

  bool FunctionDef::getDecoratorIsEmpty() const {
    return getDecoratorListIteratorBegin() == getDecoratorListIteratorEnd();
  }

  unsigned int FunctionDef::getDecoratorSize() const {
    unsigned int size = 0;
    ListIterator<expression::Expression> endIt = getDecoratorListIteratorEnd();
    for (ListIterator<expression::Expression> it = getDecoratorListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<module::Object> FunctionDef::getObjectListIteratorBegin() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, true);
  }

  ListIterator<module::Object> FunctionDef::getObjectListIteratorEnd() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, false);
  }

  bool FunctionDef::getObjectIsEmpty() const {
    return getObjectListIteratorBegin() == getObjectListIteratorEnd();
  }

  unsigned int FunctionDef::getObjectSize() const {
    unsigned int size = 0;
    ListIterator<module::Object> endIt = getObjectListIteratorEnd();
    for (ListIterator<module::Object> it = getObjectListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<statement::Parameter> FunctionDef::getParameterListIteratorBegin() const {
    return ListIterator<statement::Parameter>(&hasParameterContainer, factory, true);
  }

  ListIterator<statement::Parameter> FunctionDef::getParameterListIteratorEnd() const {
    return ListIterator<statement::Parameter>(&hasParameterContainer, factory, false);
  }

  bool FunctionDef::getParameterIsEmpty() const {
    return getParameterListIteratorBegin() == getParameterListIteratorEnd();
  }

  unsigned int FunctionDef::getParameterSize() const {
    unsigned int size = 0;
    ListIterator<statement::Parameter> endIt = getParameterListIteratorEnd();
    for (ListIterator<statement::Parameter> it = getParameterListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  module::Object* FunctionDef::getRefersTo() const {
    module::Object *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<module::Object*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  type::Type* FunctionDef::getReturnType() const {
    type::Type *_node = NULL;
    if (m_returnType != 0)
      _node = dynamic_cast<type::Type*>(factory->getPointer(m_returnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  base::Docstring* FunctionDef::getDocstring() const {
    base::Docstring *_node = NULL;
    if (m_docstring != 0)
      _node = dynamic_cast<base::Docstring*>(factory->getPointer(m_docstring));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool FunctionDef::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFunctionDef_HasDecorator:
        addDecorator(edgeEnd);
        return true;
      case edkFunctionDef_HasObject:
        addObject(edgeEnd);
        return true;
      case edkFunctionDef_HasParameter:
        addParameter(edgeEnd);
        return true;
      case edkFunctionDef_RefersTo:
        setRefersTo(edgeEnd);
        return true;
      case edkFunctionDef_ReturnType:
        setReturnType(edgeEnd);
        return true;
      case edkFunctionDef_Docstring:
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

  bool FunctionDef::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFunctionDef_HasDecorator:
        removeDecorator(edgeEnd);
        return true;
      case edkFunctionDef_HasObject:
        removeObject(edgeEnd);
        return true;
      case edkFunctionDef_HasParameter:
        removeParameter(edgeEnd);
        return true;
      case edkFunctionDef_RefersTo:
        removeRefersTo();
        return true;
      case edkFunctionDef_ReturnType:
        removeReturnType();
        return true;
      case edkFunctionDef_Docstring:
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

  void FunctionDef::addDecorator(const expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasDecoratorContainer.push_back(_node->getId());
    setParentEdge(_node,edkFunctionDef_HasDecorator);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFunctionDef_HasDecorator);
  }

  void FunctionDef::addDecorator(NodeId _id) {
    const expression::Expression *node = dynamic_cast<expression::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addDecorator( node );
  }

  void FunctionDef::removeDecorator(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Expression>::Container::iterator it = find(hasDecoratorContainer.begin(), hasDecoratorContainer.end(), id);

    if (it == hasDecoratorContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasDecoratorContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFunctionDef_HasDecorator);
  }

  void FunctionDef::removeDecorator(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeDecorator(_node->getId());
  }

  void FunctionDef::addObject(const module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkObject) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasObjectContainer.push_back(_node->getId());
    setParentEdge(_node,edkFunctionDef_HasObject);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFunctionDef_HasObject);
  }

  void FunctionDef::addObject(NodeId _id) {
    const module::Object *node = dynamic_cast<module::Object*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addObject( node );
  }

  void FunctionDef::removeObject(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<module::Object>::Container::iterator it = find(hasObjectContainer.begin(), hasObjectContainer.end(), id);

    if (it == hasObjectContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasObjectContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFunctionDef_HasObject);
  }

  void FunctionDef::removeObject(module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeObject(_node->getId());
  }

  void FunctionDef::addParameter(const statement::Parameter *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkParameter) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasParameterContainer.push_back(_node->getId());
    setParentEdge(_node,edkFunctionDef_HasParameter);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFunctionDef_HasParameter);
  }

  void FunctionDef::addParameter(NodeId _id) {
    const statement::Parameter *node = dynamic_cast<statement::Parameter*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameter( node );
  }

  void FunctionDef::removeParameter(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Parameter>::Container::iterator it = find(hasParameterContainer.begin(), hasParameterContainer.end(), id);

    if (it == hasParameterContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParameterContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFunctionDef_HasParameter);
  }

  void FunctionDef::removeParameter(statement::Parameter *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameter(_node->getId());
  }

  void FunctionDef::setRefersTo(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkFunctionDef_RefersTo);
      }
      m_refersTo = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkFunctionDef_RefersTo);
    } else {
      if (m_refersTo) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void FunctionDef::setRefersTo(module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void FunctionDef::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkFunctionDef_RefersTo);
      }
      m_refersTo = 0;
  }

  void FunctionDef::setReturnType(NodeId _id) {
    type::Type *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<type::Type*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_returnType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_returnType, m_id, edkFunctionDef_ReturnType);
      }
      m_returnType = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_returnType, this->getId(), edkFunctionDef_ReturnType);
    } else {
      if (m_returnType) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void FunctionDef::setReturnType(type::Type *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void FunctionDef::removeReturnType() {
      if (m_returnType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_returnType, m_id, edkFunctionDef_ReturnType);
      }
      m_returnType = 0;
  }

  void FunctionDef::setDocstring(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_docstring, m_id, edkFunctionDef_Docstring);
      }
      m_docstring = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_docstring, this->getId(), edkFunctionDef_Docstring);
    } else {
      if (m_docstring) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void FunctionDef::setDocstring(base::Docstring *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDocstring(_node->getId());
  }

  void FunctionDef::removeDocstring() {
      if (m_docstring) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_docstring, m_id, edkFunctionDef_Docstring);
      }
      m_docstring = 0;
  }

  void FunctionDef::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void FunctionDef::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double FunctionDef::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const FunctionDef& node = dynamic_cast<const FunctionDef&>(base);
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

  void FunctionDef::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType FunctionDef::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::FunctionDef", strlen("statement::FunctionDef"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void FunctionDef::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CompoundStatement::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);
    binIo.writeUInt4(m_lloc);

    binIo.writeUInt4(m_refersTo);
    binIo.writeUInt4(m_returnType);
    binIo.writeUInt4(m_docstring);


    for (ListIterator<expression::Expression>::Container::const_iterator it = hasDecoratorContainer.begin(); it != hasDecoratorContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<module::Object>::Container::const_iterator it = hasObjectContainer.begin(); it != hasObjectContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<statement::Parameter>::Container::const_iterator it = hasParameterContainer.begin(); it != hasParameterContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void FunctionDef::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CompoundStatement::load(binIo,false);

    m_name = binIo.readUInt4();
    m_lloc = binIo.readUInt4();

    m_refersTo =  binIo.readUInt4();

    m_returnType =  binIo.readUInt4();

    m_docstring =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasDecoratorContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkFunctionDef_HasDecorator);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasObjectContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkFunctionDef_HasObject);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasParameterContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkFunctionDef_HasParameter);
      _id = binIo.readUInt4();
    }
  }


}


}}}
