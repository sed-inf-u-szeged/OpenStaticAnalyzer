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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace base { 
  Commentable::Commentable(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    commentsContainer()
  {
  }

  Commentable::~Commentable() {
  }

  void Commentable::clone(const Commentable& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }

    commentsContainer = other.commentsContainer;
  }

  void Commentable::prepareDelete(bool tryOnVirtualParent){
    while (!commentsContainer.empty()) {
      const NodeId id = *commentsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCommentable_Comments);
      commentsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
  }

  ListIterator<base::Comment> Commentable::getCommentsListIteratorBegin() const {
    return ListIterator<base::Comment>(&commentsContainer, factory, true);
  }

  ListIterator<base::Comment> Commentable::getCommentsListIteratorEnd() const {
    return ListIterator<base::Comment>(&commentsContainer, factory, false);
  }

  bool Commentable::getCommentsIsEmpty() const {
    return getCommentsListIteratorBegin() == getCommentsListIteratorEnd();
  }

  unsigned int Commentable::getCommentsSize() const {
    unsigned int size = 0;
    ListIterator<base::Comment> endIt = getCommentsListIteratorEnd();
    for (ListIterator<base::Comment> it = getCommentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Commentable::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCommentable_Comments:
        addComments(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool Commentable::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCommentable_Comments:
        removeComments(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  void Commentable::addComments(const base::Comment *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsComment(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    commentsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCommentable_Comments);
  }

  void Commentable::addComments(NodeId _id) {
    const base::Comment *node = dynamic_cast<base::Comment*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addComments( node );
  }

  void Commentable::removeComments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Comment>::Container::iterator it = find(commentsContainer.begin(), commentsContainer.end(), id);

    if (it == commentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    commentsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCommentable_Comments);
  }

  void Commentable::removeComments(base::Comment *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeComments(_node->getId());
  }

  double Commentable::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Commentable::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Commentable::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::Commentable", strlen("base::Commentable"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Commentable::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
  }

  void Commentable::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);


    for (ListIterator<base::Comment>::Container::const_iterator it = commentsContainer.begin(); it != commentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Commentable::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      commentsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
