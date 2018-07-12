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
  Function::Function(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_generator(false),
    m_async(false),
    hasParamsContainer(),
    m_hasBody(0),
    m_hasIdentifier(0)
  {
  }

  Function::~Function() {
  }

  void Function::prepareDelete(bool tryOnVirtualParent){
    while (!hasParamsContainer.empty()) {
      const NodeId id = *hasParamsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFunction_HasParams);
      hasParamsContainer.pop_front();
    }
    removeBody();
    removeIdentifier();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
  }

  NodeKind Function::getNodeKind() const {
    return ndkFunction;
  }

  bool Function::getGenerator() const {
    return m_generator;
  }

  bool Function::getAsync() const {
    return m_async;
  }

  void Function::setGenerator(bool _generator) {
    m_generator = _generator;
  }

  void Function::setAsync(bool _async) {
    m_async = _async;
  }

  ListIterator<statement::Pattern> Function::getParamsListIteratorBegin() const {
    return ListIterator<statement::Pattern>(&hasParamsContainer, factory, true);
  }

  ListIterator<statement::Pattern> Function::getParamsListIteratorEnd() const {
    return ListIterator<statement::Pattern>(&hasParamsContainer, factory, false);
  }

  bool Function::getParamsIsEmpty() const {
    return getParamsListIteratorBegin() == getParamsListIteratorEnd();
  }

  unsigned int Function::getParamsSize() const {
    unsigned int size = 0;
    ListIterator<statement::Pattern> endIt = getParamsListIteratorEnd();
    for (ListIterator<statement::Pattern> it = getParamsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  base::Positioned* Function::getBody() const {
    base::Positioned *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Identifier* Function::getIdentifier() const {
    expression::Identifier *_node = NULL;
    if (m_hasIdentifier != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasIdentifier));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Function::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFunction_HasParams:
        addParams(edgeEnd);
        return true;
      case edkFunction_HasBody:
        setBody(edgeEnd);
        return true;
      case edkFunction_HasIdentifier:
        setIdentifier(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool Function::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFunction_HasParams:
        removeParams(edgeEnd);
        return true;
      case edkFunction_HasBody:
        removeBody();
        return true;
      case edkFunction_HasIdentifier:
        removeIdentifier();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  void Function::addParams(const statement::Pattern *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsPattern(*_node)))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasParamsContainer.push_back(_node->getId());
    setParentEdge(_node,edkFunction_HasParams);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFunction_HasParams);
  }

  void Function::addParams(NodeId _id) {
    const statement::Pattern *node = dynamic_cast<statement::Pattern*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParams( node );
  }

  void Function::removeParams(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Pattern>::Container::iterator it = find(hasParamsContainer.begin(), hasParamsContainer.end(), id);

    if (it == hasParamsContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParamsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFunction_HasParams);
  }

  void Function::removeParams(statement::Pattern *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParams(_node->getId());
  }

  void Function::setBody(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (_node->getNodeKind() == ndkBlockStatement || Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression)) {
        if (m_hasBody) {
          removeParentEdge(m_hasBody);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasBody, m_id, edkFunction_HasBody);
        }
        m_hasBody = _node->getId();
        if (m_hasBody != 0)
          setParentEdge(factory->getPointer(m_hasBody), edkFunction_HasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkFunction_HasBody);
      } else {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasBody) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Function::setBody(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void Function::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkFunction_HasBody);
      }
      m_hasBody = 0;
  }

  void Function::setIdentifier(NodeId _id) {
    expression::Identifier *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Identifier*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasIdentifier) {
        removeParentEdge(m_hasIdentifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIdentifier, m_id, edkFunction_HasIdentifier);
      }
      m_hasIdentifier = _node->getId();
      if (m_hasIdentifier != 0)
        setParentEdge(factory->getPointer(m_hasIdentifier), edkFunction_HasIdentifier);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasIdentifier, this->getId(), edkFunction_HasIdentifier);
    } else {
      if (m_hasIdentifier) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Function::setIdentifier(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setIdentifier(_node->getId());
  }

  void Function::removeIdentifier() {
      if (m_hasIdentifier) {
        removeParentEdge(m_hasIdentifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIdentifier, m_id, edkFunction_HasIdentifier);
      }
      m_hasIdentifier = 0;
  }

  void Function::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Function::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Function::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Function& node = dynamic_cast<const Function&>(base);
      double matchAttrs = 0;
      if(node.getGenerator() == getGenerator()) ++matchAttrs;
      if(node.getAsync() == getAsync()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Function::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Function::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Function", strlen("statement::Function"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Function::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_generator) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_async) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasBody);
    binIo.writeUInt4(m_hasIdentifier);


    for (ListIterator<statement::Pattern>::Container::const_iterator it = hasParamsContainer.begin(); it != hasParamsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Function::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_async = boolValues & 1;
    boolValues >>= 1;
    m_generator = boolValues & 1;
    boolValues >>= 1;

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkFunction_HasBody);

    m_hasIdentifier =  binIo.readUInt4();
    if (m_hasIdentifier != 0)
      setParentEdge(factory->getPointer(m_hasIdentifier),edkFunction_HasIdentifier);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasParamsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkFunction_HasParams);
      _id = binIo.readUInt4();
    }
  }


}


}}}
