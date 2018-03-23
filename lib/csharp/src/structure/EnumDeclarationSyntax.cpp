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

#include "csharp/inc/csharp.h"
#include "csharp/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "csharp/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace csharp { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace structure { 
  EnumDeclarationSyntax::EnumDeclarationSyntax(NodeId _id, Factory *_factory) :
    BaseTypeDeclarationSyntax(_id, _factory),
    MembersContainer()
  {
  }

  EnumDeclarationSyntax::~EnumDeclarationSyntax() {
  }

  void EnumDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!MembersContainer.empty()) {
      const NodeId id = *MembersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkEnumDeclarationSyntax_Members);
      MembersContainer.pop_front();
    }
    structure::BaseTypeDeclarationSyntax::prepareDelete(false);
  }

  NodeKind EnumDeclarationSyntax::getNodeKind() const {
    return ndkEnumDeclarationSyntax;
  }

  ListIterator<structure::EnumMemberDeclarationSyntax> EnumDeclarationSyntax::getMembersListIteratorBegin() const {
    return ListIterator<structure::EnumMemberDeclarationSyntax>(&MembersContainer, factory, true);
  }

  ListIterator<structure::EnumMemberDeclarationSyntax> EnumDeclarationSyntax::getMembersListIteratorEnd() const {
    return ListIterator<structure::EnumMemberDeclarationSyntax>(&MembersContainer, factory, false);
  }

  bool EnumDeclarationSyntax::getMembersIsEmpty() const {
    return getMembersListIteratorBegin() == getMembersListIteratorEnd();
  }

  unsigned int EnumDeclarationSyntax::getMembersSize() const {
    unsigned int size = 0;
    ListIterator<structure::EnumMemberDeclarationSyntax> endIt = getMembersListIteratorEnd();
    for (ListIterator<structure::EnumMemberDeclarationSyntax> it = getMembersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool EnumDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEnumDeclarationSyntax_Members:
        addMembers(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BaseTypeDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool EnumDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEnumDeclarationSyntax_Members:
        removeMembers(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BaseTypeDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void EnumDeclarationSyntax::addMembers(const structure::EnumMemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkEnumMemberDeclarationSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    MembersContainer.push_back(_node->getId());
    setParentEdge(_node,edkEnumDeclarationSyntax_Members);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkEnumDeclarationSyntax_Members);
  }

  void EnumDeclarationSyntax::addMembers(NodeId _id) {
    const structure::EnumMemberDeclarationSyntax *node = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addMembers( node );
  }

  void EnumDeclarationSyntax::removeMembers(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::EnumMemberDeclarationSyntax>::Container::iterator it = find(MembersContainer.begin(), MembersContainer.end(), id);

    if (it == MembersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    MembersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkEnumDeclarationSyntax_Members);
  }

  void EnumDeclarationSyntax::removeMembers(structure::EnumMemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeMembers(_node->getId());
  }

  void EnumDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void EnumDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double EnumDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const EnumDeclarationSyntax& node = dynamic_cast<const EnumDeclarationSyntax&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getIdentifier();
      str2 = node.getIdentifier();
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

  void EnumDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_identifier);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_identifier = foundKeyId->second;
    } else {
      Key oldkey = m_identifier;
      m_identifier = newStrTable.set(factory->getStringTable().get(m_identifier));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_identifier));    }

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType EnumDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::EnumDeclarationSyntax", strlen("structure::EnumDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void EnumDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BaseTypeDeclarationSyntax::save(binIo,false);


    for (ListIterator<structure::EnumMemberDeclarationSyntax>::Container::const_iterator it = MembersContainer.begin(); it != MembersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void EnumDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BaseTypeDeclarationSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      MembersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkEnumDeclarationSyntax_Members);
      _id = binIo.readUInt4();
    }
  }


}


}}}
