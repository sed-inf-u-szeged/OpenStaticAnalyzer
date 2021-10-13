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

namespace structure { 
  ClassBody::ClassBody(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    hasBodyContainer()
  {
  }

  ClassBody::~ClassBody() {
  }

  void ClassBody::prepareDelete(bool tryOnVirtualParent){
    while (!hasBodyContainer.empty()) {
      const NodeId id = *hasBodyContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClassBody_HasBody);
      hasBodyContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind ClassBody::getNodeKind() const {
    return ndkClassBody;
  }

  ListIterator<structure::MethodDefinition> ClassBody::getBodyListIteratorBegin() const {
    return ListIterator<structure::MethodDefinition>(&hasBodyContainer, factory, true);
  }

  ListIterator<structure::MethodDefinition> ClassBody::getBodyListIteratorEnd() const {
    return ListIterator<structure::MethodDefinition>(&hasBodyContainer, factory, false);
  }

  bool ClassBody::getBodyIsEmpty() const {
    return getBodyListIteratorBegin() == getBodyListIteratorEnd();
  }

  unsigned int ClassBody::getBodySize() const {
    unsigned int size = 0;
    ListIterator<structure::MethodDefinition> endIt = getBodyListIteratorEnd();
    for (ListIterator<structure::MethodDefinition> it = getBodyListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ClassBody::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClassBody_HasBody:
        addBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ClassBody::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClassBody_HasBody:
        removeBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ClassBody::addBody(const structure::MethodDefinition *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkMethodDefinition) ))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasBodyContainer.push_back(_node->getId());
    setParentEdge(_node,edkClassBody_HasBody);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClassBody_HasBody);
  }

  void ClassBody::addBody(NodeId _id) {
    const structure::MethodDefinition *node = dynamic_cast<structure::MethodDefinition*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addBody( node );
  }

  void ClassBody::removeBody(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::MethodDefinition>::Container::iterator it = find(hasBodyContainer.begin(), hasBodyContainer.end(), id);

    if (it == hasBodyContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasBodyContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClassBody_HasBody);
  }

  void ClassBody::removeBody(structure::MethodDefinition *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeBody(_node->getId());
  }

  void ClassBody::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ClassBody::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ClassBody::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ClassBody::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ClassBody::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ClassBody", strlen("structure::ClassBody"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ClassBody::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::MethodDefinition>::Container::const_iterator it = hasBodyContainer.begin(); it != hasBodyContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ClassBody::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasBodyContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkClassBody_HasBody);
      _id = binIo.readUInt4();
    }
  }


}


}}}
