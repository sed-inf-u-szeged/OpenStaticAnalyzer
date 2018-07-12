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
  Program::Program(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Named(_id, _factory),
    m_sourceType(pstScript),
    hasBodyContainer()
  {
  }

  Program::~Program() {
  }

  void Program::prepareDelete(bool tryOnVirtualParent){
    while (!hasBodyContainer.empty()) {
      const NodeId id = *hasBodyContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkProgram_HasBody);
      hasBodyContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    base::Named::prepareDelete(false);
  }

  NodeKind Program::getNodeKind() const {
    return ndkProgram;
  }

  ProgramSourceType Program::getSourceType() const {
    return m_sourceType;
  }

  void Program::setSourceType(ProgramSourceType _sourceType) {
    m_sourceType = _sourceType;
  }

  ListIterator<base::Positioned> Program::getBodyListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasBodyContainer, factory, true);
  }

  ListIterator<base::Positioned> Program::getBodyListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasBodyContainer, factory, false);
  }

  bool Program::getBodyIsEmpty() const {
    return getBodyListIteratorBegin() == getBodyListIteratorEnd();
  }

  unsigned int Program::getBodySize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getBodyListIteratorEnd();
    for (ListIterator<base::Positioned> it = getBodyListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Program::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkProgram_HasBody:
        addBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Program::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkProgram_HasBody:
        removeBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Program::addBody(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsModuleDeclaration(*_node) || Common::getIsStatement(*_node)))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasBodyContainer.push_back(_node->getId());
    setParentEdge(_node,edkProgram_HasBody);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkProgram_HasBody);
  }

  void Program::addBody(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addBody( node );
  }

  void Program::removeBody(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasBodyContainer.begin(), hasBodyContainer.end(), id);

    if (it == hasBodyContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasBodyContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkProgram_HasBody);
  }

  void Program::removeBody(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeBody(_node->getId());
  }

  void Program::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Program::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Program::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Program& node = dynamic_cast<const Program&>(base);
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
      if(node.getSourceType() == getSourceType()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Program::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Program::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::Program", strlen("base::Program"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Program::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Named::save(binIo,false);

    binIo.writeUByte1(m_sourceType);


    for (ListIterator<base::Positioned>::Container::const_iterator it = hasBodyContainer.begin(); it != hasBodyContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Program::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Named::load(binIo,false);

    m_sourceType = (ProgramSourceType)binIo.readUByte1();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasBodyContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkProgram_HasBody);
      _id = binIo.readUInt4();
    }
  }


}


}}}
