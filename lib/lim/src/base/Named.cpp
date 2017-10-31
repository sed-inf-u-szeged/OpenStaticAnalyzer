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

namespace base { 
  Named::Named(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_name(0),
    dependsOnContainer()
  {
  }

  Named::~Named() {
  }

  void Named::clone(const Named& other, bool tryOnVirtualParent) {
    base::Base::clone(other, false);

    m_name = other.m_name;
    //isAssocEdge
    dependsOnContainer = other.dependsOnContainer;
  }

  void Named::prepareDelete(bool tryOnVirtualParent){
    while (!dependsOnContainer.empty()) {
      const NodeId id = *dependsOnContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNamed_DependsOn);
      dependsOnContainer.pop_front();
    }
    base::Base::prepareDelete(false);
  }

  Key Named::getNameKey() const {
    return m_name;
  }

  const std::string& Named::getName() const {
    return factory->getStringTable().get(m_name);
  }

  void Named::setNameKey(Key _name) {
    m_name = _name;
  }

  void Named::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  ListIteratorAssocString<base::Named> Named::getDependsOnListIteratorAssocBegin() const {
    return ListIteratorAssocString<base::Named>(&dependsOnContainer, factory, true);
  }

  ListIteratorAssocString<base::Named> Named::getDependsOnListIteratorAssocEnd() const {
    return ListIteratorAssocString<base::Named>(&dependsOnContainer, factory, false);
  }

  bool Named::getDependsOnIsEmpty() const {
    return getDependsOnListIteratorAssocBegin() == getDependsOnListIteratorAssocEnd();
  }

  unsigned int Named::getDependsOnSize() const {
    unsigned int size = 0;
    ListIteratorAssocString<base::Named> endIt = getDependsOnListIteratorAssocEnd();
    for (ListIteratorAssocString<base::Named> it = getDependsOnListIteratorAssocBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Named::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNamed_DependsOn:
        addDependsOn(edgeEnd, *((const std::string*)acValue));
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Named::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNamed_DependsOn:
        removeDependsOn(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Named::addDependsOn(const base::Named *_node, const std::string& acValue) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsNamed(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AssocEdge<NodeId,Key> ac(_node->getId(), factory->getStringTable().set(acValue));
    dependsOnContainer.push_back(ac);
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNamed_DependsOn);
  }

  void Named::addDependsOn(NodeId _id, const std::string& acValue) {
    const base::Named *node = dynamic_cast<base::Named*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addDependsOn( node, acValue );
  }

  void Named::removeDependsOn(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIteratorAssocString<base::Named>::Container::iterator it = find(dependsOnContainer.begin(), dependsOnContainer.end(), id);

    if (it == dependsOnContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    dependsOnContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNamed_DependsOn);
  }

  void Named::removeDependsOn(base::Named *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeDependsOn(_node->getId());
  }

  double Named::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Named& node = dynamic_cast<const Named&>(base);
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
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Named::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Named::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::Named", strlen("base::Named"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Named::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);


    for (ListIteratorAssocString<base::Named>::Container::const_iterator ait = dependsOnContainer.begin(); ait != dependsOnContainer.end(); ++ait) {
      binIo.writeUInt4(ait->node);
      factory->getStringTable().setType(ait->assocClass, StrTable::strToSave);
      binIo.writeUInt4(ait->assocClass);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Named::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_name = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      Key _ac = binIo.readUInt4();
      dependsOnContainer.push_back(AssocEdge<NodeId,Key>(_id, _ac));
      _id = binIo.readUInt4();
    }
  }


}


}}}
