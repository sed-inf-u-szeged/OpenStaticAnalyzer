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

namespace module { 
  Module::Module(NodeId _id, Factory *_factory) :
    Named(_id, _factory),
    m_lloc(0),
    hasObjectContainer(),
    hasStatementContainer(),
    m_docstring(0)
  {
  }

  Module::~Module() {
  }

  void Module::prepareDelete(bool tryOnVirtualParent){
    while (!hasObjectContainer.empty()) {
      const NodeId id = *hasObjectContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkModule_HasObject);
      hasObjectContainer.pop_front();
    }
    while (!hasStatementContainer.empty()) {
      const NodeId id = *hasStatementContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkModule_HasStatement);
      hasStatementContainer.pop_front();
    }
    removeDocstring();
    base::Named::prepareDelete(false);
  }

  NodeKind Module::getNodeKind() const {
    return ndkModule;
  }

  int Module::getLloc() const {
    return m_lloc;
  }

  void Module::setLloc(int _lloc) {
    m_lloc = _lloc;
  }

  ListIterator<module::Object> Module::getObjectListIteratorBegin() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, true);
  }

  ListIterator<module::Object> Module::getObjectListIteratorEnd() const {
    return ListIterator<module::Object>(&hasObjectContainer, factory, false);
  }

  bool Module::getObjectIsEmpty() const {
    return getObjectListIteratorBegin() == getObjectListIteratorEnd();
  }

  unsigned int Module::getObjectSize() const {
    unsigned int size = 0;
    ListIterator<module::Object> endIt = getObjectListIteratorEnd();
    for (ListIterator<module::Object> it = getObjectListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<base::Positioned> Module::getStatementListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasStatementContainer, factory, true);
  }

  ListIterator<base::Positioned> Module::getStatementListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasStatementContainer, factory, false);
  }

  bool Module::getStatementIsEmpty() const {
    return getStatementListIteratorBegin() == getStatementListIteratorEnd();
  }

  unsigned int Module::getStatementSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getStatementListIteratorEnd();
    for (ListIterator<base::Positioned> it = getStatementListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  base::Docstring* Module::getDocstring() const {
    base::Docstring *_node = NULL;
    if (m_docstring != 0)
      _node = dynamic_cast<base::Docstring*>(factory->getPointer(m_docstring));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Module::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModule_HasObject:
        addObject(edgeEnd);
        return true;
      case edkModule_HasStatement:
        addStatement(edgeEnd);
        return true;
      case edkModule_Docstring:
        setDocstring(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Module::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModule_HasObject:
        removeObject(edgeEnd);
        return true;
      case edkModule_HasStatement:
        removeStatement(edgeEnd);
        return true;
      case edkModule_Docstring:
        removeDocstring();
        return true;
      default:
        break;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Module::addObject(const module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkObject) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasObjectContainer.push_back(_node->getId());
    setParentEdge(_node,edkModule_HasObject);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkModule_HasObject);
  }

  void Module::addObject(NodeId _id) {
    const module::Object *node = dynamic_cast<module::Object*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addObject( node );
  }

  void Module::removeObject(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<module::Object>::Container::iterator it = find(hasObjectContainer.begin(), hasObjectContainer.end(), id);

    if (it == hasObjectContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasObjectContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkModule_HasObject);
  }

  void Module::removeObject(module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeObject(_node->getId());
  }

  void Module::addStatement(const base::Positioned *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node) || Common::getIsExpression(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasStatementContainer.push_back(_node->getId());
    setParentEdge(_node,edkModule_HasStatement);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkModule_HasStatement);
  }

  void Module::addStatement(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addStatement( node );
  }

  void Module::removeStatement(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasStatementContainer.begin(), hasStatementContainer.end(), id);

    if (it == hasStatementContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasStatementContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkModule_HasStatement);
  }

  void Module::removeStatement(base::Positioned *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeStatement(_node->getId());
  }

  void Module::setDocstring(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_docstring, m_id, edkModule_Docstring);
      }
      m_docstring = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_docstring, this->getId(), edkModule_Docstring);
    } else {
      if (m_docstring) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Module::setDocstring(base::Docstring *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDocstring(_node->getId());
  }

  void Module::removeDocstring() {
      if (m_docstring) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_docstring, m_id, edkModule_Docstring);
      }
      m_docstring = 0;
  }

  void Module::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Module::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Module::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Module& node = dynamic_cast<const Module&>(base);
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

  void Module::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Module::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "module::Module", strlen("module::Module"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Module::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Named::save(binIo,false);

    binIo.writeUInt4(m_lloc);

    binIo.writeUInt4(m_docstring);


    for (ListIterator<module::Object>::Container::const_iterator it = hasObjectContainer.begin(); it != hasObjectContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<base::Positioned>::Container::const_iterator it = hasStatementContainer.begin(); it != hasStatementContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Module::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Named::load(binIo,false);

    m_lloc = binIo.readUInt4();

    m_docstring =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasObjectContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkModule_HasObject);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasStatementContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkModule_HasStatement);
      _id = binIo.readUInt4();
    }
  }


}


}}}
