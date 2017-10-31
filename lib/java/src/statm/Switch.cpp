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
  Switch::Switch(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Selection(_id, _factory),
    m_blockStartPosition(),
    hasCasesContainer()
  {
    m_blockStartPosition.posInfo.path = 0;
    m_blockStartPosition.posInfo.line = 0;
    m_blockStartPosition.posInfo.col = 0;
    m_blockStartPosition.posInfo.endLine = 0;
    m_blockStartPosition.posInfo.endCol = 0;
    m_blockStartPosition.posInfo.wideLine = 0;
    m_blockStartPosition.posInfo.wideCol = 0;
    m_blockStartPosition.posInfo.wideEndLine = 0;
    m_blockStartPosition.posInfo.wideEndCol = 0;
  }

  Switch::~Switch() {
  }

  void Switch::clone(const Switch& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Selection::clone(other, false);

    m_blockStartPosition.posInfo = other.m_blockStartPosition.posInfo;
    hasCasesContainer = other.hasCasesContainer;
  }

  void Switch::prepareDelete(bool tryOnVirtualParent){
    while (!hasCasesContainer.empty()) {
      const NodeId id = *hasCasesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitch_HasCases);
      hasCasesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Selection::prepareDelete(false);
  }

  NodeKind Switch::getNodeKind() const {
    return ndkSwitch;
  }

  const Range Switch::getBlockStartPosition() const {
    return Range(factory->getStringTable(), m_blockStartPosition.posInfo);
  }

  int Switch::compareByBlockStartPosition(const Switch& other) const {
    if (m_blockStartPosition.posInfo.path != other.m_blockStartPosition.posInfo.path) {
      return (m_blockStartPosition.posInfo.path < other.m_blockStartPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideLine != other.m_blockStartPosition.posInfo.wideLine) {
      return (m_blockStartPosition.posInfo.wideLine < other.m_blockStartPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideCol != other.m_blockStartPosition.posInfo.wideCol) {
      return (m_blockStartPosition.posInfo.wideCol < other.m_blockStartPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideEndLine != other.m_blockStartPosition.posInfo.wideEndLine) {
      return (m_blockStartPosition.posInfo.wideEndLine > other.m_blockStartPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_blockStartPosition.posInfo.wideEndCol != other.m_blockStartPosition.posInfo.wideEndCol) {
      return (m_blockStartPosition.posInfo.wideEndCol > other.m_blockStartPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Switch::setBlockStartPosition(const Range& _blockStartPosition) {
    m_blockStartPosition.posInfo = _blockStartPosition.positionInfo;
    if (_blockStartPosition.strTable != &factory->getStringTable())
      m_blockStartPosition.posInfo.path = factory->getStringTable().set(_blockStartPosition.getPath());
  }

  ListIterator<statm::SwitchLabel> Switch::getCasesListIteratorBegin() const {
    return ListIterator<statm::SwitchLabel>(&hasCasesContainer, factory, true);
  }

  ListIterator<statm::SwitchLabel> Switch::getCasesListIteratorEnd() const {
    return ListIterator<statm::SwitchLabel>(&hasCasesContainer, factory, false);
  }

  bool Switch::getCasesIsEmpty() const {
    return getCasesListIteratorBegin() == getCasesListIteratorEnd();
  }

  unsigned int Switch::getCasesSize() const {
    unsigned int size = 0;
    ListIterator<statm::SwitchLabel> endIt = getCasesListIteratorEnd();
    for (ListIterator<statm::SwitchLabel> it = getCasesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Switch::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitch_HasCases:
        addCases(edgeEnd);
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
    if (statm::Selection::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Switch::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitch_HasCases:
        removeCases(edgeEnd);
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
    if (statm::Selection::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Switch::addCases(const statm::SwitchLabel *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsSwitchLabel(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasCasesContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitch_HasCases);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitch_HasCases);
  }

  void Switch::addCases(NodeId _id) {
    const statm::SwitchLabel *node = dynamic_cast<statm::SwitchLabel*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCases( node );
  }

  void Switch::removeCases(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statm::SwitchLabel>::Container::iterator it = find(hasCasesContainer.begin(), hasCasesContainer.end(), id);

    if (it == hasCasesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasCasesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitch_HasCases);
  }

  void Switch::removeCases(statm::SwitchLabel *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCases(_node->getId());
  }

  void Switch::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Switch::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Switch::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Switch& node = dynamic_cast<const Switch&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Switch::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Switch::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Switch", strlen("statm::Switch"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Switch::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Selection::sort(false);
  }

  void Switch::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Selection::save(binIo,false);

    factory->getStringTable().setType(m_blockStartPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_blockStartPosition.posInfo.path);
    binIo.writeUInt4(m_blockStartPosition.posInfo.line);
    binIo.writeUInt4(m_blockStartPosition.posInfo.col);
    binIo.writeUInt4(m_blockStartPosition.posInfo.endLine);
    binIo.writeUInt4(m_blockStartPosition.posInfo.endCol);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideLine);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideCol);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_blockStartPosition.posInfo.wideEndCol);


    for (ListIterator<statm::SwitchLabel>::Container::const_iterator it = hasCasesContainer.begin(); it != hasCasesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Switch::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Selection::load(binIo,false);

    m_blockStartPosition.posInfo.path = binIo.readUInt4();
    m_blockStartPosition.posInfo.line = binIo.readUInt4();
    m_blockStartPosition.posInfo.col = binIo.readUInt4();
    m_blockStartPosition.posInfo.endLine = binIo.readUInt4();
    m_blockStartPosition.posInfo.endCol = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideLine = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideCol = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_blockStartPosition.posInfo.wideEndCol = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasCasesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitch_HasCases);
      _id = binIo.readUInt4();
    }
  }


}


}}}
