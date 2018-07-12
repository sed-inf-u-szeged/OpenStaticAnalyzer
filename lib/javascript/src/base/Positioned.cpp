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

namespace base { 
  Positioned::Positioned(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_position(),
    commentsContainer()
  {
    m_position.posInfo.path = 0;
    m_position.posInfo.line = 0;
    m_position.posInfo.col = 0;
    m_position.posInfo.endLine = 0;
    m_position.posInfo.endCol = 0;
    m_position.posInfo.wideLine = 0;
    m_position.posInfo.wideCol = 0;
    m_position.posInfo.wideEndLine = 0;
    m_position.posInfo.wideEndCol = 0;
  }

  Positioned::~Positioned() {
  }

  void Positioned::prepareDelete(bool tryOnVirtualParent){
    while (!commentsContainer.empty()) {
      const NodeId id = *commentsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkPositioned_Comments);
      commentsContainer.pop_front();
    }
    base::Base::prepareDelete(false);
  }

  const Range Positioned::getPosition() const {
    return Range(factory->getStringTable(), m_position.posInfo);
  }

  int Positioned::compareByPosition(const Positioned& other) const {
    if (m_position.posInfo.path != other.m_position.posInfo.path) {
      return (m_position.posInfo.path < other.m_position.posInfo.path) ? -1 :1 ;
    };
    if (m_position.posInfo.wideLine != other.m_position.posInfo.wideLine) {
      return (m_position.posInfo.wideLine < other.m_position.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_position.posInfo.wideCol != other.m_position.posInfo.wideCol) {
      return (m_position.posInfo.wideCol < other.m_position.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_position.posInfo.wideEndLine != other.m_position.posInfo.wideEndLine) {
      return (m_position.posInfo.wideEndLine > other.m_position.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_position.posInfo.wideEndCol != other.m_position.posInfo.wideEndCol) {
      return (m_position.posInfo.wideEndCol > other.m_position.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Positioned::setPosition(const Range& _position) {
    m_position.posInfo = _position.positionInfo;
    if (_position.strTable != &factory->getStringTable())
      m_position.posInfo.path = factory->getStringTable().set(_position.getPath());
  }

  ListIterator<base::Comment> Positioned::getCommentsListIteratorBegin() const {
    return ListIterator<base::Comment>(&commentsContainer, factory, true);
  }

  ListIterator<base::Comment> Positioned::getCommentsListIteratorEnd() const {
    return ListIterator<base::Comment>(&commentsContainer, factory, false);
  }

  bool Positioned::getCommentsIsEmpty() const {
    return getCommentsListIteratorBegin() == getCommentsListIteratorEnd();
  }

  unsigned int Positioned::getCommentsSize() const {
    unsigned int size = 0;
    ListIterator<base::Comment> endIt = getCommentsListIteratorEnd();
    for (ListIterator<base::Comment> it = getCommentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Positioned::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPositioned_Comments:
        addComments(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Positioned::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPositioned_Comments:
        removeComments(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Positioned::addComments(const base::Comment *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkComment) ))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    commentsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkPositioned_Comments);
  }

  void Positioned::addComments(NodeId _id) {
    const base::Comment *node = dynamic_cast<base::Comment*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addComments( node );
  }

  void Positioned::removeComments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Comment>::Container::iterator it = find(commentsContainer.begin(), commentsContainer.end(), id);

    if (it == commentsContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    commentsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkPositioned_Comments);
  }

  void Positioned::removeComments(base::Comment *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeComments(_node->getId());
  }

  double Positioned::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Positioned::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Positioned::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::Positioned", strlen("base::Positioned"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Positioned::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_position.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_position.posInfo.path);
    binIo.writeUInt4(m_position.posInfo.line);
    binIo.writeUInt4(m_position.posInfo.col);
    binIo.writeUInt4(m_position.posInfo.endLine);
    binIo.writeUInt4(m_position.posInfo.endCol);
    binIo.writeUInt4(m_position.posInfo.wideLine);
    binIo.writeUInt4(m_position.posInfo.wideCol);
    binIo.writeUInt4(m_position.posInfo.wideEndLine);
    binIo.writeUInt4(m_position.posInfo.wideEndCol);


    for (ListIterator<base::Comment>::Container::const_iterator it = commentsContainer.begin(); it != commentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Positioned::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_position.posInfo.path = binIo.readUInt4();
    m_position.posInfo.line = binIo.readUInt4();
    m_position.posInfo.col = binIo.readUInt4();
    m_position.posInfo.endLine = binIo.readUInt4();
    m_position.posInfo.endCol = binIo.readUInt4();
    m_position.posInfo.wideLine = binIo.readUInt4();
    m_position.posInfo.wideCol = binIo.readUInt4();
    m_position.posInfo.wideEndLine = binIo.readUInt4();
    m_position.posInfo.wideEndCol = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      commentsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
