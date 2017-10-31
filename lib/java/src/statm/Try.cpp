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
  Try::Try(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Statement(_id, _factory),
    m_resourceLeftParenPosition(),
    m_resourceRightParenPosition(),
    m_finallyPosition(),
    hasResourcesContainer(),
    m_hasBlock(0),
    hasHandlersContainer(),
    m_hasFinallyBlock(0)
  {
    m_resourceLeftParenPosition.posInfo.path = 0;
    m_resourceLeftParenPosition.posInfo.line = 0;
    m_resourceLeftParenPosition.posInfo.col = 0;
    m_resourceLeftParenPosition.posInfo.endLine = 0;
    m_resourceLeftParenPosition.posInfo.endCol = 0;
    m_resourceLeftParenPosition.posInfo.wideLine = 0;
    m_resourceLeftParenPosition.posInfo.wideCol = 0;
    m_resourceLeftParenPosition.posInfo.wideEndLine = 0;
    m_resourceLeftParenPosition.posInfo.wideEndCol = 0;
    m_resourceRightParenPosition.posInfo.path = 0;
    m_resourceRightParenPosition.posInfo.line = 0;
    m_resourceRightParenPosition.posInfo.col = 0;
    m_resourceRightParenPosition.posInfo.endLine = 0;
    m_resourceRightParenPosition.posInfo.endCol = 0;
    m_resourceRightParenPosition.posInfo.wideLine = 0;
    m_resourceRightParenPosition.posInfo.wideCol = 0;
    m_resourceRightParenPosition.posInfo.wideEndLine = 0;
    m_resourceRightParenPosition.posInfo.wideEndCol = 0;
    m_finallyPosition.posInfo.path = 0;
    m_finallyPosition.posInfo.line = 0;
    m_finallyPosition.posInfo.col = 0;
    m_finallyPosition.posInfo.endLine = 0;
    m_finallyPosition.posInfo.endCol = 0;
    m_finallyPosition.posInfo.wideLine = 0;
    m_finallyPosition.posInfo.wideCol = 0;
    m_finallyPosition.posInfo.wideEndLine = 0;
    m_finallyPosition.posInfo.wideEndCol = 0;
  }

  Try::~Try() {
  }

  void Try::clone(const Try& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Statement::clone(other, false);

    m_resourceLeftParenPosition.posInfo = other.m_resourceLeftParenPosition.posInfo;
    m_resourceRightParenPosition.posInfo = other.m_resourceRightParenPosition.posInfo;
    m_finallyPosition.posInfo = other.m_finallyPosition.posInfo;
    hasResourcesContainer = other.hasResourcesContainer;
    m_hasBlock = other.m_hasBlock;
    hasHandlersContainer = other.hasHandlersContainer;
    m_hasFinallyBlock = other.m_hasFinallyBlock;
  }

  void Try::prepareDelete(bool tryOnVirtualParent){
    while (!hasResourcesContainer.empty()) {
      const NodeId id = *hasResourcesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTry_HasResources);
      hasResourcesContainer.pop_front();
    }
    removeBlock();
    while (!hasHandlersContainer.empty()) {
      const NodeId id = *hasHandlersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTry_HasHandlers);
      hasHandlersContainer.pop_front();
    }
    removeFinallyBlock();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Statement::prepareDelete(false);
  }

  NodeKind Try::getNodeKind() const {
    return ndkTry;
  }

  const Range Try::getResourceLeftParenPosition() const {
    return Range(factory->getStringTable(), m_resourceLeftParenPosition.posInfo);
  }

  int Try::compareByResourceLeftParenPosition(const Try& other) const {
    if (m_resourceLeftParenPosition.posInfo.path != other.m_resourceLeftParenPosition.posInfo.path) {
      return (m_resourceLeftParenPosition.posInfo.path < other.m_resourceLeftParenPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_resourceLeftParenPosition.posInfo.wideLine != other.m_resourceLeftParenPosition.posInfo.wideLine) {
      return (m_resourceLeftParenPosition.posInfo.wideLine < other.m_resourceLeftParenPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_resourceLeftParenPosition.posInfo.wideCol != other.m_resourceLeftParenPosition.posInfo.wideCol) {
      return (m_resourceLeftParenPosition.posInfo.wideCol < other.m_resourceLeftParenPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_resourceLeftParenPosition.posInfo.wideEndLine != other.m_resourceLeftParenPosition.posInfo.wideEndLine) {
      return (m_resourceLeftParenPosition.posInfo.wideEndLine > other.m_resourceLeftParenPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_resourceLeftParenPosition.posInfo.wideEndCol != other.m_resourceLeftParenPosition.posInfo.wideEndCol) {
      return (m_resourceLeftParenPosition.posInfo.wideEndCol > other.m_resourceLeftParenPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range Try::getResourceRightParenPosition() const {
    return Range(factory->getStringTable(), m_resourceRightParenPosition.posInfo);
  }

  int Try::compareByResourceRightParenPosition(const Try& other) const {
    if (m_resourceRightParenPosition.posInfo.path != other.m_resourceRightParenPosition.posInfo.path) {
      return (m_resourceRightParenPosition.posInfo.path < other.m_resourceRightParenPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_resourceRightParenPosition.posInfo.wideLine != other.m_resourceRightParenPosition.posInfo.wideLine) {
      return (m_resourceRightParenPosition.posInfo.wideLine < other.m_resourceRightParenPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_resourceRightParenPosition.posInfo.wideCol != other.m_resourceRightParenPosition.posInfo.wideCol) {
      return (m_resourceRightParenPosition.posInfo.wideCol < other.m_resourceRightParenPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_resourceRightParenPosition.posInfo.wideEndLine != other.m_resourceRightParenPosition.posInfo.wideEndLine) {
      return (m_resourceRightParenPosition.posInfo.wideEndLine > other.m_resourceRightParenPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_resourceRightParenPosition.posInfo.wideEndCol != other.m_resourceRightParenPosition.posInfo.wideEndCol) {
      return (m_resourceRightParenPosition.posInfo.wideEndCol > other.m_resourceRightParenPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range Try::getFinallyPosition() const {
    return Range(factory->getStringTable(), m_finallyPosition.posInfo);
  }

  int Try::compareByFinallyPosition(const Try& other) const {
    if (m_finallyPosition.posInfo.path != other.m_finallyPosition.posInfo.path) {
      return (m_finallyPosition.posInfo.path < other.m_finallyPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_finallyPosition.posInfo.wideLine != other.m_finallyPosition.posInfo.wideLine) {
      return (m_finallyPosition.posInfo.wideLine < other.m_finallyPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_finallyPosition.posInfo.wideCol != other.m_finallyPosition.posInfo.wideCol) {
      return (m_finallyPosition.posInfo.wideCol < other.m_finallyPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_finallyPosition.posInfo.wideEndLine != other.m_finallyPosition.posInfo.wideEndLine) {
      return (m_finallyPosition.posInfo.wideEndLine > other.m_finallyPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_finallyPosition.posInfo.wideEndCol != other.m_finallyPosition.posInfo.wideEndCol) {
      return (m_finallyPosition.posInfo.wideEndCol > other.m_finallyPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Try::setResourceLeftParenPosition(const Range& _resourceLeftParenPosition) {
    m_resourceLeftParenPosition.posInfo = _resourceLeftParenPosition.positionInfo;
    if (_resourceLeftParenPosition.strTable != &factory->getStringTable())
      m_resourceLeftParenPosition.posInfo.path = factory->getStringTable().set(_resourceLeftParenPosition.getPath());
  }

  void Try::setResourceRightParenPosition(const Range& _resourceRightParenPosition) {
    m_resourceRightParenPosition.posInfo = _resourceRightParenPosition.positionInfo;
    if (_resourceRightParenPosition.strTable != &factory->getStringTable())
      m_resourceRightParenPosition.posInfo.path = factory->getStringTable().set(_resourceRightParenPosition.getPath());
  }

  void Try::setFinallyPosition(const Range& _finallyPosition) {
    m_finallyPosition.posInfo = _finallyPosition.positionInfo;
    if (_finallyPosition.strTable != &factory->getStringTable())
      m_finallyPosition.posInfo.path = factory->getStringTable().set(_finallyPosition.getPath());
  }

  ListIterator<struc::Variable> Try::getResourcesListIteratorBegin() const {
    return ListIterator<struc::Variable>(&hasResourcesContainer, factory, true);
  }

  ListIterator<struc::Variable> Try::getResourcesListIteratorEnd() const {
    return ListIterator<struc::Variable>(&hasResourcesContainer, factory, false);
  }

  bool Try::getResourcesIsEmpty() const {
    return getResourcesListIteratorBegin() == getResourcesListIteratorEnd();
  }

  unsigned int Try::getResourcesSize() const {
    unsigned int size = 0;
    ListIterator<struc::Variable> endIt = getResourcesListIteratorEnd();
    for (ListIterator<struc::Variable> it = getResourcesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  statm::Block* Try::getBlock() const {
    statm::Block *_node = NULL;
    if (m_hasBlock != 0)
      _node = dynamic_cast<statm::Block*>(factory->getPointer(m_hasBlock));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<statm::Handler> Try::getHandlersListIteratorBegin() const {
    return ListIterator<statm::Handler>(&hasHandlersContainer, factory, true);
  }

  ListIterator<statm::Handler> Try::getHandlersListIteratorEnd() const {
    return ListIterator<statm::Handler>(&hasHandlersContainer, factory, false);
  }

  bool Try::getHandlersIsEmpty() const {
    return getHandlersListIteratorBegin() == getHandlersListIteratorEnd();
  }

  unsigned int Try::getHandlersSize() const {
    unsigned int size = 0;
    ListIterator<statm::Handler> endIt = getHandlersListIteratorEnd();
    for (ListIterator<statm::Handler> it = getHandlersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  statm::Block* Try::getFinallyBlock() const {
    statm::Block *_node = NULL;
    if (m_hasFinallyBlock != 0)
      _node = dynamic_cast<statm::Block*>(factory->getPointer(m_hasFinallyBlock));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Try::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTry_HasResources:
        addResources(edgeEnd);
        return true;
      case edkTry_HasBlock:
        setBlock(edgeEnd);
        return true;
      case edkTry_HasHandlers:
        addHandlers(edgeEnd);
        return true;
      case edkTry_HasFinallyBlock:
        setFinallyBlock(edgeEnd);
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
    if (statm::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Try::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTry_HasResources:
        removeResources(edgeEnd);
        return true;
      case edkTry_HasBlock:
        removeBlock();
        return true;
      case edkTry_HasHandlers:
        removeHandlers(edgeEnd);
        return true;
      case edkTry_HasFinallyBlock:
        removeFinallyBlock();
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
    if (statm::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Try::addResources(const struc::Variable *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkVariable) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasResourcesContainer.push_back(_node->getId());
    setParentEdge(_node,edkTry_HasResources);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTry_HasResources);
  }

  void Try::addResources(NodeId _id) {
    const struc::Variable *node = dynamic_cast<struc::Variable*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addResources( node );
  }

  void Try::removeResources(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::Variable>::Container::iterator it = find(hasResourcesContainer.begin(), hasResourcesContainer.end(), id);

    if (it == hasResourcesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasResourcesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTry_HasResources);
  }

  void Try::removeResources(struc::Variable *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeResources(_node->getId());
  }

  void Try::setBlock(NodeId _id) {
    statm::Block *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Block*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkTry_HasBlock);
      }
      m_hasBlock = _node->getId();
      if (m_hasBlock != 0)
        setParentEdge(factory->getPointer(m_hasBlock), edkTry_HasBlock);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBlock, this->getId(), edkTry_HasBlock);
    } else {
      if (m_hasBlock) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Try::setBlock(statm::Block *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBlock(_node->getId());
  }

  void Try::removeBlock() {
      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkTry_HasBlock);
      }
      m_hasBlock = 0;
  }

  void Try::addHandlers(const statm::Handler *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkHandler) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasHandlersContainer.push_back(_node->getId());
    setParentEdge(_node,edkTry_HasHandlers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTry_HasHandlers);
  }

  void Try::addHandlers(NodeId _id) {
    const statm::Handler *node = dynamic_cast<statm::Handler*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addHandlers( node );
  }

  void Try::removeHandlers(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statm::Handler>::Container::iterator it = find(hasHandlersContainer.begin(), hasHandlersContainer.end(), id);

    if (it == hasHandlersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasHandlersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTry_HasHandlers);
  }

  void Try::removeHandlers(statm::Handler *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeHandlers(_node->getId());
  }

  void Try::setFinallyBlock(NodeId _id) {
    statm::Block *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Block*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasFinallyBlock) {
        removeParentEdge(m_hasFinallyBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinallyBlock, m_id, edkTry_HasFinallyBlock);
      }
      m_hasFinallyBlock = _node->getId();
      if (m_hasFinallyBlock != 0)
        setParentEdge(factory->getPointer(m_hasFinallyBlock), edkTry_HasFinallyBlock);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFinallyBlock, this->getId(), edkTry_HasFinallyBlock);
    } else {
      if (m_hasFinallyBlock) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Try::setFinallyBlock(statm::Block *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFinallyBlock(_node->getId());
  }

  void Try::removeFinallyBlock() {
      if (m_hasFinallyBlock) {
        removeParentEdge(m_hasFinallyBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinallyBlock, m_id, edkTry_HasFinallyBlock);
      }
      m_hasFinallyBlock = 0;
  }

  void Try::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Try::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Try::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Try& node = dynamic_cast<const Try&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Try::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Try::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Try", strlen("statm::Try"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Try::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Statement::sort(false);
  }

  void Try::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Statement::save(binIo,false);

    factory->getStringTable().setType(m_resourceLeftParenPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.path);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.line);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.col);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.endLine);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.endCol);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.wideLine);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.wideCol);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_resourceLeftParenPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_resourceRightParenPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.path);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.line);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.col);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.endLine);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.endCol);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.wideLine);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.wideCol);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_resourceRightParenPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_finallyPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_finallyPosition.posInfo.path);
    binIo.writeUInt4(m_finallyPosition.posInfo.line);
    binIo.writeUInt4(m_finallyPosition.posInfo.col);
    binIo.writeUInt4(m_finallyPosition.posInfo.endLine);
    binIo.writeUInt4(m_finallyPosition.posInfo.endCol);
    binIo.writeUInt4(m_finallyPosition.posInfo.wideLine);
    binIo.writeUInt4(m_finallyPosition.posInfo.wideCol);
    binIo.writeUInt4(m_finallyPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_finallyPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasBlock);
    binIo.writeUInt4(m_hasFinallyBlock);


    for (ListIterator<struc::Variable>::Container::const_iterator it = hasResourcesContainer.begin(); it != hasResourcesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<statm::Handler>::Container::const_iterator it = hasHandlersContainer.begin(); it != hasHandlersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Try::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Statement::load(binIo,false);

    m_resourceLeftParenPosition.posInfo.path = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.line = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.col = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.endLine = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.endCol = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.wideLine = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.wideCol = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_resourceLeftParenPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.path = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.line = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.col = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.endLine = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.endCol = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.wideLine = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.wideCol = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_resourceRightParenPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_finallyPosition.posInfo.path = binIo.readUInt4();
    m_finallyPosition.posInfo.line = binIo.readUInt4();
    m_finallyPosition.posInfo.col = binIo.readUInt4();
    m_finallyPosition.posInfo.endLine = binIo.readUInt4();
    m_finallyPosition.posInfo.endCol = binIo.readUInt4();
    m_finallyPosition.posInfo.wideLine = binIo.readUInt4();
    m_finallyPosition.posInfo.wideCol = binIo.readUInt4();
    m_finallyPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_finallyPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasBlock =  binIo.readUInt4();
    if (m_hasBlock != 0)
      setParentEdge(factory->getPointer(m_hasBlock),edkTry_HasBlock);

    m_hasFinallyBlock =  binIo.readUInt4();
    if (m_hasFinallyBlock != 0)
      setParentEdge(factory->getPointer(m_hasFinallyBlock),edkTry_HasFinallyBlock);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasResourcesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTry_HasResources);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasHandlersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTry_HasHandlers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
