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

namespace expression { 
  ObjectExpression::ObjectExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    hasPropertiesContainer()
  {
  }

  ObjectExpression::~ObjectExpression() {
  }

  void ObjectExpression::prepareDelete(bool tryOnVirtualParent){
    while (!hasPropertiesContainer.empty()) {
      const NodeId id = *hasPropertiesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkObjectExpression_HasProperties);
      hasPropertiesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind ObjectExpression::getNodeKind() const {
    return ndkObjectExpression;
  }

  ListIterator<expression::Property> ObjectExpression::getPropertiesListIteratorBegin() const {
    return ListIterator<expression::Property>(&hasPropertiesContainer, factory, true);
  }

  ListIterator<expression::Property> ObjectExpression::getPropertiesListIteratorEnd() const {
    return ListIterator<expression::Property>(&hasPropertiesContainer, factory, false);
  }

  bool ObjectExpression::getPropertiesIsEmpty() const {
    return getPropertiesListIteratorBegin() == getPropertiesListIteratorEnd();
  }

  unsigned int ObjectExpression::getPropertiesSize() const {
    unsigned int size = 0;
    ListIterator<expression::Property> endIt = getPropertiesListIteratorEnd();
    for (ListIterator<expression::Property> it = getPropertiesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ObjectExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObjectExpression_HasProperties:
        addProperties(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ObjectExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObjectExpression_HasProperties:
        removeProperties(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ObjectExpression::addProperties(const expression::Property *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsProperty(*_node)))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasPropertiesContainer.push_back(_node->getId());
    setParentEdge(_node,edkObjectExpression_HasProperties);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkObjectExpression_HasProperties);
  }

  void ObjectExpression::addProperties(NodeId _id) {
    const expression::Property *node = dynamic_cast<expression::Property*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addProperties( node );
  }

  void ObjectExpression::removeProperties(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Property>::Container::iterator it = find(hasPropertiesContainer.begin(), hasPropertiesContainer.end(), id);

    if (it == hasPropertiesContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasPropertiesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkObjectExpression_HasProperties);
  }

  void ObjectExpression::removeProperties(expression::Property *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeProperties(_node->getId());
  }

  void ObjectExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ObjectExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ObjectExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ObjectExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ObjectExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ObjectExpression", strlen("expression::ObjectExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ObjectExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);


    for (ListIterator<expression::Property>::Container::const_iterator it = hasPropertiesContainer.begin(); it != hasPropertiesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ObjectExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasPropertiesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkObjectExpression_HasProperties);
      _id = binIo.readUInt4();
    }
  }


}


}}}
