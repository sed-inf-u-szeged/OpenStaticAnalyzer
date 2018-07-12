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
  SwitchLabel::SwitchLabel(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Positioned(_id, _factory),
    m_colonPosition(),
    hasStatementsContainer()
  {
    m_colonPosition.posInfo.path = 0;
    m_colonPosition.posInfo.line = 0;
    m_colonPosition.posInfo.col = 0;
    m_colonPosition.posInfo.endLine = 0;
    m_colonPosition.posInfo.endCol = 0;
    m_colonPosition.posInfo.wideLine = 0;
    m_colonPosition.posInfo.wideCol = 0;
    m_colonPosition.posInfo.wideEndLine = 0;
    m_colonPosition.posInfo.wideEndCol = 0;
  }

  SwitchLabel::~SwitchLabel() {
  }

  void SwitchLabel::clone(const SwitchLabel& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    base::Positioned::clone(other, false);

    m_colonPosition.posInfo = other.m_colonPosition.posInfo;
    hasStatementsContainer = other.hasStatementsContainer;
  }

  void SwitchLabel::prepareDelete(bool tryOnVirtualParent){
    while (!hasStatementsContainer.empty()) {
      const NodeId id = *hasStatementsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchLabel_HasStatements);
      hasStatementsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    base::Positioned::prepareDelete(false);
  }

  const Range SwitchLabel::getColonPosition() const {
    return Range(factory->getStringTable(), m_colonPosition.posInfo);
  }

  int SwitchLabel::compareByColonPosition(const SwitchLabel& other) const {
    if (m_colonPosition.posInfo.path != other.m_colonPosition.posInfo.path) {
      return (m_colonPosition.posInfo.path < other.m_colonPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideLine != other.m_colonPosition.posInfo.wideLine) {
      return (m_colonPosition.posInfo.wideLine < other.m_colonPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideCol != other.m_colonPosition.posInfo.wideCol) {
      return (m_colonPosition.posInfo.wideCol < other.m_colonPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideEndLine != other.m_colonPosition.posInfo.wideEndLine) {
      return (m_colonPosition.posInfo.wideEndLine > other.m_colonPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideEndCol != other.m_colonPosition.posInfo.wideEndCol) {
      return (m_colonPosition.posInfo.wideEndCol > other.m_colonPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void SwitchLabel::setColonPosition(const Range& _colonPosition) {
    m_colonPosition.posInfo = _colonPosition.positionInfo;
    if (_colonPosition.strTable != &factory->getStringTable())
      m_colonPosition.posInfo.path = factory->getStringTable().set(_colonPosition.getPath());
  }

  ListIterator<statm::Statement> SwitchLabel::getStatementsListIteratorBegin() const {
    return ListIterator<statm::Statement>(&hasStatementsContainer, factory, true);
  }

  ListIterator<statm::Statement> SwitchLabel::getStatementsListIteratorEnd() const {
    return ListIterator<statm::Statement>(&hasStatementsContainer, factory, false);
  }

  bool SwitchLabel::getStatementsIsEmpty() const {
    return getStatementsListIteratorBegin() == getStatementsListIteratorEnd();
  }

  unsigned int SwitchLabel::getStatementsSize() const {
    unsigned int size = 0;
    ListIterator<statm::Statement> endIt = getStatementsListIteratorEnd();
    for (ListIterator<statm::Statement> it = getStatementsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool SwitchLabel::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchLabel_HasStatements:
        addStatements(edgeEnd);
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
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SwitchLabel::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchLabel_HasStatements:
        removeStatements(edgeEnd);
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
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SwitchLabel::addStatements(const statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasStatementsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchLabel_HasStatements);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchLabel_HasStatements);
  }

  void SwitchLabel::addStatements(NodeId _id) {
    const statm::Statement *node = dynamic_cast<statm::Statement*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addStatements( node );
  }

  void SwitchLabel::removeStatements(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statm::Statement>::Container::iterator it = find(hasStatementsContainer.begin(), hasStatementsContainer.end(), id);

    if (it == hasStatementsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasStatementsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchLabel_HasStatements);
  }

  void SwitchLabel::removeStatements(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeStatements(_node->getId());
  }

  double SwitchLabel::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const SwitchLabel& node = dynamic_cast<const SwitchLabel&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void SwitchLabel::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType SwitchLabel::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::SwitchLabel", strlen("statm::SwitchLabel"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchLabel::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Positioned::sort(false);
  }

  void SwitchLabel::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Positioned::save(binIo,false);

    factory->getStringTable().setType(m_colonPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_colonPosition.posInfo.path);
    binIo.writeUInt4(m_colonPosition.posInfo.line);
    binIo.writeUInt4(m_colonPosition.posInfo.col);
    binIo.writeUInt4(m_colonPosition.posInfo.endLine);
    binIo.writeUInt4(m_colonPosition.posInfo.endCol);
    binIo.writeUInt4(m_colonPosition.posInfo.wideLine);
    binIo.writeUInt4(m_colonPosition.posInfo.wideCol);
    binIo.writeUInt4(m_colonPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_colonPosition.posInfo.wideEndCol);


    for (ListIterator<statm::Statement>::Container::const_iterator it = hasStatementsContainer.begin(); it != hasStatementsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchLabel::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Positioned::load(binIo,false);

    m_colonPosition.posInfo.path = binIo.readUInt4();
    m_colonPosition.posInfo.line = binIo.readUInt4();
    m_colonPosition.posInfo.col = binIo.readUInt4();
    m_colonPosition.posInfo.endLine = binIo.readUInt4();
    m_colonPosition.posInfo.endCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndCol = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasStatementsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchLabel_HasStatements);
      _id = binIo.readUInt4();
    }
  }


}


}}}
