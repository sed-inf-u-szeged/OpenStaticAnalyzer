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

namespace statm { 
  BasicFor::BasicFor(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    For(_id, _factory),
    m_firstSemiPosition(),
    m_secondSemiPosition(),
    hasInitializersContainer(),
    m_hasCondition(0),
    hasUpdatesContainer()
  {
    m_firstSemiPosition.posInfo.path = 0;
    m_firstSemiPosition.posInfo.line = 0;
    m_firstSemiPosition.posInfo.col = 0;
    m_firstSemiPosition.posInfo.endLine = 0;
    m_firstSemiPosition.posInfo.endCol = 0;
    m_firstSemiPosition.posInfo.wideLine = 0;
    m_firstSemiPosition.posInfo.wideCol = 0;
    m_firstSemiPosition.posInfo.wideEndLine = 0;
    m_firstSemiPosition.posInfo.wideEndCol = 0;
    m_secondSemiPosition.posInfo.path = 0;
    m_secondSemiPosition.posInfo.line = 0;
    m_secondSemiPosition.posInfo.col = 0;
    m_secondSemiPosition.posInfo.endLine = 0;
    m_secondSemiPosition.posInfo.endCol = 0;
    m_secondSemiPosition.posInfo.wideLine = 0;
    m_secondSemiPosition.posInfo.wideCol = 0;
    m_secondSemiPosition.posInfo.wideEndLine = 0;
    m_secondSemiPosition.posInfo.wideEndCol = 0;
  }

  BasicFor::~BasicFor() {
  }

  void BasicFor::clone(const BasicFor& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::For::clone(other, false);

    m_firstSemiPosition.posInfo = other.m_firstSemiPosition.posInfo;
    m_secondSemiPosition.posInfo = other.m_secondSemiPosition.posInfo;
    hasInitializersContainer = other.hasInitializersContainer;
    m_hasCondition = other.m_hasCondition;
    hasUpdatesContainer = other.hasUpdatesContainer;
  }

  void BasicFor::prepareDelete(bool tryOnVirtualParent){
    while (!hasInitializersContainer.empty()) {
      const NodeId id = *hasInitializersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBasicFor_HasInitializers);
      hasInitializersContainer.pop_front();
    }
    removeCondition();
    while (!hasUpdatesContainer.empty()) {
      const NodeId id = *hasUpdatesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBasicFor_HasUpdates);
      hasUpdatesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::For::prepareDelete(false);
  }

  NodeKind BasicFor::getNodeKind() const {
    return ndkBasicFor;
  }

  const Range BasicFor::getFirstSemiPosition() const {
    return Range(factory->getStringTable(), m_firstSemiPosition.posInfo);
  }

  int BasicFor::compareByFirstSemiPosition(const BasicFor& other) const {
    if (m_firstSemiPosition.posInfo.path != other.m_firstSemiPosition.posInfo.path) {
      return (m_firstSemiPosition.posInfo.path < other.m_firstSemiPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_firstSemiPosition.posInfo.wideLine != other.m_firstSemiPosition.posInfo.wideLine) {
      return (m_firstSemiPosition.posInfo.wideLine < other.m_firstSemiPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_firstSemiPosition.posInfo.wideCol != other.m_firstSemiPosition.posInfo.wideCol) {
      return (m_firstSemiPosition.posInfo.wideCol < other.m_firstSemiPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_firstSemiPosition.posInfo.wideEndLine != other.m_firstSemiPosition.posInfo.wideEndLine) {
      return (m_firstSemiPosition.posInfo.wideEndLine > other.m_firstSemiPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_firstSemiPosition.posInfo.wideEndCol != other.m_firstSemiPosition.posInfo.wideEndCol) {
      return (m_firstSemiPosition.posInfo.wideEndCol > other.m_firstSemiPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range BasicFor::getSecondSemiPosition() const {
    return Range(factory->getStringTable(), m_secondSemiPosition.posInfo);
  }

  int BasicFor::compareBySecondSemiPosition(const BasicFor& other) const {
    if (m_secondSemiPosition.posInfo.path != other.m_secondSemiPosition.posInfo.path) {
      return (m_secondSemiPosition.posInfo.path < other.m_secondSemiPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_secondSemiPosition.posInfo.wideLine != other.m_secondSemiPosition.posInfo.wideLine) {
      return (m_secondSemiPosition.posInfo.wideLine < other.m_secondSemiPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_secondSemiPosition.posInfo.wideCol != other.m_secondSemiPosition.posInfo.wideCol) {
      return (m_secondSemiPosition.posInfo.wideCol < other.m_secondSemiPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_secondSemiPosition.posInfo.wideEndLine != other.m_secondSemiPosition.posInfo.wideEndLine) {
      return (m_secondSemiPosition.posInfo.wideEndLine > other.m_secondSemiPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_secondSemiPosition.posInfo.wideEndCol != other.m_secondSemiPosition.posInfo.wideEndCol) {
      return (m_secondSemiPosition.posInfo.wideEndCol > other.m_secondSemiPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void BasicFor::setFirstSemiPosition(const Range& _firstSemiPosition) {
    m_firstSemiPosition.posInfo = _firstSemiPosition.positionInfo;
    if (_firstSemiPosition.strTable != &factory->getStringTable())
      m_firstSemiPosition.posInfo.path = factory->getStringTable().set(_firstSemiPosition.getPath());
  }

  void BasicFor::setSecondSemiPosition(const Range& _secondSemiPosition) {
    m_secondSemiPosition.posInfo = _secondSemiPosition.positionInfo;
    if (_secondSemiPosition.strTable != &factory->getStringTable())
      m_secondSemiPosition.posInfo.path = factory->getStringTable().set(_secondSemiPosition.getPath());
  }

  ListIterator<statm::Statement> BasicFor::getInitializersListIteratorBegin() const {
    return ListIterator<statm::Statement>(&hasInitializersContainer, factory, true);
  }

  ListIterator<statm::Statement> BasicFor::getInitializersListIteratorEnd() const {
    return ListIterator<statm::Statement>(&hasInitializersContainer, factory, false);
  }

  bool BasicFor::getInitializersIsEmpty() const {
    return getInitializersListIteratorBegin() == getInitializersListIteratorEnd();
  }

  unsigned int BasicFor::getInitializersSize() const {
    unsigned int size = 0;
    ListIterator<statm::Statement> endIt = getInitializersListIteratorEnd();
    for (ListIterator<statm::Statement> it = getInitializersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expr::Expression* BasicFor::getCondition() const {
    expr::Expression *_node = NULL;
    if (m_hasCondition != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasCondition));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<statm::Statement> BasicFor::getUpdatesListIteratorBegin() const {
    return ListIterator<statm::Statement>(&hasUpdatesContainer, factory, true);
  }

  ListIterator<statm::Statement> BasicFor::getUpdatesListIteratorEnd() const {
    return ListIterator<statm::Statement>(&hasUpdatesContainer, factory, false);
  }

  bool BasicFor::getUpdatesIsEmpty() const {
    return getUpdatesListIteratorBegin() == getUpdatesListIteratorEnd();
  }

  unsigned int BasicFor::getUpdatesSize() const {
    unsigned int size = 0;
    ListIterator<statm::Statement> endIt = getUpdatesListIteratorEnd();
    for (ListIterator<statm::Statement> it = getUpdatesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool BasicFor::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBasicFor_HasInitializers:
        addInitializers(edgeEnd);
        return true;
      case edkBasicFor_HasCondition:
        setCondition(edgeEnd);
        return true;
      case edkBasicFor_HasUpdates:
        addUpdates(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::For::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BasicFor::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBasicFor_HasInitializers:
        removeInitializers(edgeEnd);
        return true;
      case edkBasicFor_HasCondition:
        removeCondition();
        return true;
      case edkBasicFor_HasUpdates:
        removeUpdates(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::For::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BasicFor::addInitializers(const statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasInitializersContainer.push_back(_node->getId());
    setParentEdge(_node,edkBasicFor_HasInitializers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBasicFor_HasInitializers);
  }

  void BasicFor::addInitializers(NodeId _id) {
    const statm::Statement *node = dynamic_cast<statm::Statement*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addInitializers( node );
  }

  void BasicFor::removeInitializers(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statm::Statement>::Container::iterator it = find(hasInitializersContainer.begin(), hasInitializersContainer.end(), id);

    if (it == hasInitializersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasInitializersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBasicFor_HasInitializers);
  }

  void BasicFor::removeInitializers(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeInitializers(_node->getId());
  }

  void BasicFor::setCondition(NodeId _id) {
    expr::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasCondition) {
        removeParentEdge(m_hasCondition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkBasicFor_HasCondition);
      }
      m_hasCondition = _node->getId();
      if (m_hasCondition != 0)
        setParentEdge(factory->getPointer(m_hasCondition), edkBasicFor_HasCondition);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasCondition, this->getId(), edkBasicFor_HasCondition);
    } else {
      if (m_hasCondition) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BasicFor::setCondition(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCondition(_node->getId());
  }

  void BasicFor::removeCondition() {
      if (m_hasCondition) {
        removeParentEdge(m_hasCondition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCondition, m_id, edkBasicFor_HasCondition);
      }
      m_hasCondition = 0;
  }

  void BasicFor::addUpdates(const statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasUpdatesContainer.push_back(_node->getId());
    setParentEdge(_node,edkBasicFor_HasUpdates);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBasicFor_HasUpdates);
  }

  void BasicFor::addUpdates(NodeId _id) {
    const statm::Statement *node = dynamic_cast<statm::Statement*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addUpdates( node );
  }

  void BasicFor::removeUpdates(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statm::Statement>::Container::iterator it = find(hasUpdatesContainer.begin(), hasUpdatesContainer.end(), id);

    if (it == hasUpdatesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasUpdatesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBasicFor_HasUpdates);
  }

  void BasicFor::removeUpdates(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeUpdates(_node->getId());
  }

  void BasicFor::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BasicFor::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BasicFor::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const BasicFor& node = dynamic_cast<const BasicFor&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void BasicFor::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType BasicFor::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::BasicFor", strlen("statm::BasicFor"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BasicFor::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    For::sort(false);
  }

  void BasicFor::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    For::save(binIo,false);

    factory->getStringTable().setType(m_firstSemiPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.path);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.line);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.col);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.endLine);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.endCol);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.wideLine);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.wideCol);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_firstSemiPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_secondSemiPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.path);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.line);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.col);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.endLine);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.endCol);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.wideLine);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.wideCol);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_secondSemiPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasCondition);


    for (ListIterator<statm::Statement>::Container::const_iterator it = hasInitializersContainer.begin(); it != hasInitializersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<statm::Statement>::Container::const_iterator it = hasUpdatesContainer.begin(); it != hasUpdatesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BasicFor::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    For::load(binIo,false);

    m_firstSemiPosition.posInfo.path = binIo.readUInt4();
    m_firstSemiPosition.posInfo.line = binIo.readUInt4();
    m_firstSemiPosition.posInfo.col = binIo.readUInt4();
    m_firstSemiPosition.posInfo.endLine = binIo.readUInt4();
    m_firstSemiPosition.posInfo.endCol = binIo.readUInt4();
    m_firstSemiPosition.posInfo.wideLine = binIo.readUInt4();
    m_firstSemiPosition.posInfo.wideCol = binIo.readUInt4();
    m_firstSemiPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_firstSemiPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_secondSemiPosition.posInfo.path = binIo.readUInt4();
    m_secondSemiPosition.posInfo.line = binIo.readUInt4();
    m_secondSemiPosition.posInfo.col = binIo.readUInt4();
    m_secondSemiPosition.posInfo.endLine = binIo.readUInt4();
    m_secondSemiPosition.posInfo.endCol = binIo.readUInt4();
    m_secondSemiPosition.posInfo.wideLine = binIo.readUInt4();
    m_secondSemiPosition.posInfo.wideCol = binIo.readUInt4();
    m_secondSemiPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_secondSemiPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasCondition =  binIo.readUInt4();
    if (m_hasCondition != 0)
      setParentEdge(factory->getPointer(m_hasCondition),edkBasicFor_HasCondition);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasInitializersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBasicFor_HasInitializers);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasUpdatesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBasicFor_HasUpdates);
      _id = binIo.readUInt4();
    }
  }


}


}}}
