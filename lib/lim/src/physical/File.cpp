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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace physical { 
  File::File(NodeId _id, Factory *_factory) :
    FSEntry(_id, _factory),
    m_CLOC(0),
    m_LLOC(0),
    m_LOC(0),
    m_numberOfBranches(0),
    hasCommentContainer(),
    includesContainer()
  {
  }

  File::~File() {
  }

  void File::clone(const File& other, bool tryOnVirtualParent) {
    physical::FSEntry::clone(other, false);

    m_CLOC = other.m_CLOC;
    m_LLOC = other.m_LLOC;
    m_LOC = other.m_LOC;
    m_numberOfBranches = other.m_numberOfBranches;
    hasCommentContainer = other.hasCommentContainer;
    includesContainer = other.includesContainer;
  }

  void File::prepareDelete(bool tryOnVirtualParent){
    while (!hasCommentContainer.empty()) {
      const NodeId id = *hasCommentContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFile_HasComment);
      hasCommentContainer.pop_front();
    }
    while (!includesContainer.empty()) {
      const NodeId id = *includesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFile_Includes);
      includesContainer.pop_front();
    }
    physical::FSEntry::prepareDelete(false);
  }

  NodeKind File::getNodeKind() const {
    return ndkFile;
  }

  unsigned File::getCLOC() const {
    return m_CLOC;
  }

  unsigned File::getLLOC() const {
    return m_LLOC;
  }

  unsigned File::getLOC() const {
    return m_LOC;
  }

  unsigned File::getNumberOfBranches() const {
    return m_numberOfBranches;
  }

  void File::setCLOC(unsigned _CLOC) {
    m_CLOC = _CLOC;
  }

  void File::setLLOC(unsigned _LLOC) {
    m_LLOC = _LLOC;
  }

  void File::setLOC(unsigned _LOC) {
    m_LOC = _LOC;
  }

  void File::setNumberOfBranches(unsigned _numberOfBranches) {
    m_numberOfBranches = _numberOfBranches;
  }

  ListIterator<base::Comment> File::getCommentListIteratorBegin() const {
    return ListIterator<base::Comment>(&hasCommentContainer, factory, true);
  }

  ListIterator<base::Comment> File::getCommentListIteratorEnd() const {
    return ListIterator<base::Comment>(&hasCommentContainer, factory, false);
  }

  bool File::getCommentIsEmpty() const {
    return getCommentListIteratorBegin() == getCommentListIteratorEnd();
  }

  unsigned int File::getCommentSize() const {
    unsigned int size = 0;
    ListIterator<base::Comment> endIt = getCommentListIteratorEnd();
    for (ListIterator<base::Comment> it = getCommentListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<physical::File> File::getIncludesListIteratorBegin() const {
    return ListIterator<physical::File>(&includesContainer, factory, true);
  }

  ListIterator<physical::File> File::getIncludesListIteratorEnd() const {
    return ListIterator<physical::File>(&includesContainer, factory, false);
  }

  bool File::getIncludesIsEmpty() const {
    return getIncludesListIteratorBegin() == getIncludesListIteratorEnd();
  }

  unsigned int File::getIncludesSize() const {
    unsigned int size = 0;
    ListIterator<physical::File> endIt = getIncludesListIteratorEnd();
    for (ListIterator<physical::File> it = getIncludesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool File::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFile_HasComment:
        addComment(edgeEnd);
        return true;
      case edkFile_Includes:
        addIncludes(edgeEnd);
        return true;
      default:
        break;
    }
    if (physical::FSEntry::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool File::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFile_HasComment:
        removeComment(edgeEnd);
        return true;
      case edkFile_Includes:
        removeIncludes(edgeEnd);
        return true;
      default:
        break;
    }
    if (physical::FSEntry::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void File::addComment(const base::Comment *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkComment) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasCommentContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFile_HasComment);
  }

  void File::addComment(NodeId _id) {
    const base::Comment *node = dynamic_cast<base::Comment*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addComment( node );
  }

  void File::removeComment(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Comment>::Container::iterator it = find(hasCommentContainer.begin(), hasCommentContainer.end(), id);

    if (it == hasCommentContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasCommentContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFile_HasComment);
  }

  void File::removeComment(base::Comment *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeComment(_node->getId());
  }

  void File::addIncludes(const physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkFile) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    includesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFile_Includes);
  }

  void File::addIncludes(NodeId _id) {
    const physical::File *node = dynamic_cast<physical::File*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addIncludes( node );
  }

  void File::removeIncludes(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<physical::File>::Container::iterator it = find(includesContainer.begin(), includesContainer.end(), id);

    if (it == includesContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    includesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFile_Includes);
  }

  void File::removeIncludes(physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeIncludes(_node->getId());
  }

  void File::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void File::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double File::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const File& node = dynamic_cast<const File&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getCLOC() == getCLOC()) ++matchAttrs;
      if(node.getLLOC() == getLLOC()) ++matchAttrs;
      if(node.getLOC() == getLOC()) ++matchAttrs;
      if(node.getNumberOfBranches() == getNumberOfBranches()) ++matchAttrs;
      return matchAttrs / (5 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void File::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType File::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "physical::File", strlen("physical::File"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void File::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    FSEntry::save(binIo,false);

    binIo.writeUInt4(m_CLOC);
    binIo.writeUInt4(m_LLOC);
    binIo.writeUInt4(m_LOC);
    binIo.writeUInt4(m_numberOfBranches);


    for (ListIterator<base::Comment>::Container::const_iterator it = hasCommentContainer.begin(); it != hasCommentContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<physical::File>::Container::const_iterator it = includesContainer.begin(); it != includesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void File::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    FSEntry::load(binIo,false);

    m_CLOC = binIo.readUInt4();
    m_LLOC = binIo.readUInt4();
    m_LOC = binIo.readUInt4();
    m_numberOfBranches = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasCommentContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      includesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
