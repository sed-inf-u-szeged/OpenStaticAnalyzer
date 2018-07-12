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
  CompilationUnitSyntax::CompilationUnitSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    AttributeListsContainer(),
    ExternsContainer(),
    MembersContainer(),
    UsingsContainer()
  {
  }

  CompilationUnitSyntax::~CompilationUnitSyntax() {
  }

  void CompilationUnitSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributeListsContainer.empty()) {
      const NodeId id = *AttributeListsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_AttributeLists);
      AttributeListsContainer.pop_front();
    }
    while (!ExternsContainer.empty()) {
      const NodeId id = *ExternsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_Externs);
      ExternsContainer.pop_front();
    }
    while (!MembersContainer.empty()) {
      const NodeId id = *MembersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_Members);
      MembersContainer.pop_front();
    }
    while (!UsingsContainer.empty()) {
      const NodeId id = *UsingsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_Usings);
      UsingsContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind CompilationUnitSyntax::getNodeKind() const {
    return ndkCompilationUnitSyntax;
  }

  ListIterator<structure::AttributeListSyntax> CompilationUnitSyntax::getAttributeListsListIteratorBegin() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, true);
  }

  ListIterator<structure::AttributeListSyntax> CompilationUnitSyntax::getAttributeListsListIteratorEnd() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, false);
  }

  bool CompilationUnitSyntax::getAttributeListsIsEmpty() const {
    return getAttributeListsListIteratorBegin() == getAttributeListsListIteratorEnd();
  }

  unsigned int CompilationUnitSyntax::getAttributeListsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeListSyntax> endIt = getAttributeListsListIteratorEnd();
    for (ListIterator<structure::AttributeListSyntax> it = getAttributeListsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<structure::ExternAliasDirectiveSyntax> CompilationUnitSyntax::getExternsListIteratorBegin() const {
    return ListIterator<structure::ExternAliasDirectiveSyntax>(&ExternsContainer, factory, true);
  }

  ListIterator<structure::ExternAliasDirectiveSyntax> CompilationUnitSyntax::getExternsListIteratorEnd() const {
    return ListIterator<structure::ExternAliasDirectiveSyntax>(&ExternsContainer, factory, false);
  }

  bool CompilationUnitSyntax::getExternsIsEmpty() const {
    return getExternsListIteratorBegin() == getExternsListIteratorEnd();
  }

  unsigned int CompilationUnitSyntax::getExternsSize() const {
    unsigned int size = 0;
    ListIterator<structure::ExternAliasDirectiveSyntax> endIt = getExternsListIteratorEnd();
    for (ListIterator<structure::ExternAliasDirectiveSyntax> it = getExternsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<structure::MemberDeclarationSyntax> CompilationUnitSyntax::getMembersListIteratorBegin() const {
    return ListIterator<structure::MemberDeclarationSyntax>(&MembersContainer, factory, true);
  }

  ListIterator<structure::MemberDeclarationSyntax> CompilationUnitSyntax::getMembersListIteratorEnd() const {
    return ListIterator<structure::MemberDeclarationSyntax>(&MembersContainer, factory, false);
  }

  bool CompilationUnitSyntax::getMembersIsEmpty() const {
    return getMembersListIteratorBegin() == getMembersListIteratorEnd();
  }

  unsigned int CompilationUnitSyntax::getMembersSize() const {
    unsigned int size = 0;
    ListIterator<structure::MemberDeclarationSyntax> endIt = getMembersListIteratorEnd();
    for (ListIterator<structure::MemberDeclarationSyntax> it = getMembersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<structure::UsingDirectiveSyntax> CompilationUnitSyntax::getUsingsListIteratorBegin() const {
    return ListIterator<structure::UsingDirectiveSyntax>(&UsingsContainer, factory, true);
  }

  ListIterator<structure::UsingDirectiveSyntax> CompilationUnitSyntax::getUsingsListIteratorEnd() const {
    return ListIterator<structure::UsingDirectiveSyntax>(&UsingsContainer, factory, false);
  }

  bool CompilationUnitSyntax::getUsingsIsEmpty() const {
    return getUsingsListIteratorBegin() == getUsingsListIteratorEnd();
  }

  unsigned int CompilationUnitSyntax::getUsingsSize() const {
    unsigned int size = 0;
    ListIterator<structure::UsingDirectiveSyntax> endIt = getUsingsListIteratorEnd();
    for (ListIterator<structure::UsingDirectiveSyntax> it = getUsingsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool CompilationUnitSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCompilationUnitSyntax_AttributeLists:
        addAttributeLists(edgeEnd);
        return true;
      case edkCompilationUnitSyntax_Externs:
        addExterns(edgeEnd);
        return true;
      case edkCompilationUnitSyntax_Members:
        addMembers(edgeEnd);
        return true;
      case edkCompilationUnitSyntax_Usings:
        addUsings(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CompilationUnitSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCompilationUnitSyntax_AttributeLists:
        removeAttributeLists(edgeEnd);
        return true;
      case edkCompilationUnitSyntax_Externs:
        removeExterns(edgeEnd);
        return true;
      case edkCompilationUnitSyntax_Members:
        removeMembers(edgeEnd);
        return true;
      case edkCompilationUnitSyntax_Usings:
        removeUsings(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CompilationUnitSyntax::addAttributeLists(const structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeListSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributeListsContainer.push_back(_node->getId());
    setParentEdge(_node,edkCompilationUnitSyntax_AttributeLists);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCompilationUnitSyntax_AttributeLists);
  }

  void CompilationUnitSyntax::addAttributeLists(NodeId _id) {
    const structure::AttributeListSyntax *node = dynamic_cast<structure::AttributeListSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributeLists( node );
  }

  void CompilationUnitSyntax::removeAttributeLists(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeListSyntax>::Container::iterator it = find(AttributeListsContainer.begin(), AttributeListsContainer.end(), id);

    if (it == AttributeListsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributeListsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_AttributeLists);
  }

  void CompilationUnitSyntax::removeAttributeLists(structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributeLists(_node->getId());
  }

  void CompilationUnitSyntax::addExterns(const structure::ExternAliasDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkExternAliasDirectiveSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ExternsContainer.push_back(_node->getId());
    setParentEdge(_node,edkCompilationUnitSyntax_Externs);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCompilationUnitSyntax_Externs);
  }

  void CompilationUnitSyntax::addExterns(NodeId _id) {
    const structure::ExternAliasDirectiveSyntax *node = dynamic_cast<structure::ExternAliasDirectiveSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addExterns( node );
  }

  void CompilationUnitSyntax::removeExterns(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::ExternAliasDirectiveSyntax>::Container::iterator it = find(ExternsContainer.begin(), ExternsContainer.end(), id);

    if (it == ExternsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ExternsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_Externs);
  }

  void CompilationUnitSyntax::removeExterns(structure::ExternAliasDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeExterns(_node->getId());
  }

  void CompilationUnitSyntax::addMembers(const structure::MemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMemberDeclarationSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    MembersContainer.push_back(_node->getId());
    setParentEdge(_node,edkCompilationUnitSyntax_Members);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCompilationUnitSyntax_Members);
  }

  void CompilationUnitSyntax::addMembers(NodeId _id) {
    const structure::MemberDeclarationSyntax *node = dynamic_cast<structure::MemberDeclarationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addMembers( node );
  }

  void CompilationUnitSyntax::removeMembers(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::MemberDeclarationSyntax>::Container::iterator it = find(MembersContainer.begin(), MembersContainer.end(), id);

    if (it == MembersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    MembersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_Members);
  }

  void CompilationUnitSyntax::removeMembers(structure::MemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeMembers(_node->getId());
  }

  void CompilationUnitSyntax::addUsings(const structure::UsingDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkUsingDirectiveSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    UsingsContainer.push_back(_node->getId());
    setParentEdge(_node,edkCompilationUnitSyntax_Usings);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCompilationUnitSyntax_Usings);
  }

  void CompilationUnitSyntax::addUsings(NodeId _id) {
    const structure::UsingDirectiveSyntax *node = dynamic_cast<structure::UsingDirectiveSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addUsings( node );
  }

  void CompilationUnitSyntax::removeUsings(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::UsingDirectiveSyntax>::Container::iterator it = find(UsingsContainer.begin(), UsingsContainer.end(), id);

    if (it == UsingsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    UsingsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnitSyntax_Usings);
  }

  void CompilationUnitSyntax::removeUsings(structure::UsingDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeUsings(_node->getId());
  }

  void CompilationUnitSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CompilationUnitSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CompilationUnitSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void CompilationUnitSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType CompilationUnitSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::CompilationUnitSyntax", strlen("structure::CompilationUnitSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CompilationUnitSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::AttributeListSyntax>::Container::const_iterator it = AttributeListsContainer.begin(); it != AttributeListsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<structure::ExternAliasDirectiveSyntax>::Container::const_iterator it = ExternsContainer.begin(); it != ExternsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<structure::MemberDeclarationSyntax>::Container::const_iterator it = MembersContainer.begin(); it != MembersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<structure::UsingDirectiveSyntax>::Container::const_iterator it = UsingsContainer.begin(); it != UsingsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void CompilationUnitSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributeListsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCompilationUnitSyntax_AttributeLists);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      ExternsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCompilationUnitSyntax_Externs);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      MembersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCompilationUnitSyntax_Members);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      UsingsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCompilationUnitSyntax_Usings);
      _id = binIo.readUInt4();
    }
  }


}


}}}
