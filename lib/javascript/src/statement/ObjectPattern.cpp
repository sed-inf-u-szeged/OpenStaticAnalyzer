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
  ObjectPattern::ObjectPattern(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Pattern(_id, _factory),
    hasPropertiesContainer()
  {
  }

  ObjectPattern::~ObjectPattern() {
  }

  void ObjectPattern::prepareDelete(bool tryOnVirtualParent){
    while (!hasPropertiesContainer.empty()) {
      const NodeId id = *hasPropertiesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkObjectPattern_HasProperties);
      hasPropertiesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Pattern::prepareDelete(false);
  }

  NodeKind ObjectPattern::getNodeKind() const {
    return ndkObjectPattern;
  }

  ListIterator<base::Positioned> ObjectPattern::getPropertiesListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasPropertiesContainer, factory, true);
  }

  ListIterator<base::Positioned> ObjectPattern::getPropertiesListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasPropertiesContainer, factory, false);
  }

  bool ObjectPattern::getPropertiesIsEmpty() const {
    return getPropertiesListIteratorBegin() == getPropertiesListIteratorEnd();
  }

  unsigned int ObjectPattern::getPropertiesSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getPropertiesListIteratorEnd();
    for (ListIterator<base::Positioned> it = getPropertiesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ObjectPattern::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObjectPattern_HasProperties:
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
    if (statement::Pattern::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ObjectPattern::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObjectPattern_HasProperties:
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
    if (statement::Pattern::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ObjectPattern::addProperties(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkProperty)  || (_node->getNodeKind() == ndkRestElement) ))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasPropertiesContainer.push_back(_node->getId());
    setParentEdge(_node,edkObjectPattern_HasProperties);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkObjectPattern_HasProperties);
  }

  void ObjectPattern::addProperties(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addProperties( node );
  }

  void ObjectPattern::removeProperties(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasPropertiesContainer.begin(), hasPropertiesContainer.end(), id);

    if (it == hasPropertiesContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasPropertiesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkObjectPattern_HasProperties);
  }

  void ObjectPattern::removeProperties(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeProperties(_node->getId());
  }

  void ObjectPattern::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ObjectPattern::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ObjectPattern::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ObjectPattern::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ObjectPattern::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ObjectPattern", strlen("statement::ObjectPattern"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ObjectPattern::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Pattern::save(binIo,false);


    for (ListIterator<base::Positioned>::Container::const_iterator it = hasPropertiesContainer.begin(); it != hasPropertiesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ObjectPattern::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Pattern::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasPropertiesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkObjectPattern_HasProperties);
      _id = binIo.readUInt4();
    }
  }


}


}}}
