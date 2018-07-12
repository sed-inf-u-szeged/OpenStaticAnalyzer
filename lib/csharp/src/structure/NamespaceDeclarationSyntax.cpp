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
  NamespaceDeclarationSyntax::NamespaceDeclarationSyntax(NodeId _id, Factory *_factory) :
    MemberDeclarationSyntax(_id, _factory),
    ExternsContainer(),
    MembersContainer(),
    m_Name(0),
    UsingsContainer()
  {
  }

  NamespaceDeclarationSyntax::~NamespaceDeclarationSyntax() {
  }

  void NamespaceDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ExternsContainer.empty()) {
      const NodeId id = *ExternsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNamespaceDeclarationSyntax_Externs);
      ExternsContainer.pop_front();
    }
    while (!MembersContainer.empty()) {
      const NodeId id = *MembersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNamespaceDeclarationSyntax_Members);
      MembersContainer.pop_front();
    }
    removeName();
    while (!UsingsContainer.empty()) {
      const NodeId id = *UsingsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNamespaceDeclarationSyntax_Usings);
      UsingsContainer.pop_front();
    }
    structure::MemberDeclarationSyntax::prepareDelete(false);
  }

  NodeKind NamespaceDeclarationSyntax::getNodeKind() const {
    return ndkNamespaceDeclarationSyntax;
  }

  ListIterator<structure::ExternAliasDirectiveSyntax> NamespaceDeclarationSyntax::getExternsListIteratorBegin() const {
    return ListIterator<structure::ExternAliasDirectiveSyntax>(&ExternsContainer, factory, true);
  }

  ListIterator<structure::ExternAliasDirectiveSyntax> NamespaceDeclarationSyntax::getExternsListIteratorEnd() const {
    return ListIterator<structure::ExternAliasDirectiveSyntax>(&ExternsContainer, factory, false);
  }

  bool NamespaceDeclarationSyntax::getExternsIsEmpty() const {
    return getExternsListIteratorBegin() == getExternsListIteratorEnd();
  }

  unsigned int NamespaceDeclarationSyntax::getExternsSize() const {
    unsigned int size = 0;
    ListIterator<structure::ExternAliasDirectiveSyntax> endIt = getExternsListIteratorEnd();
    for (ListIterator<structure::ExternAliasDirectiveSyntax> it = getExternsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<structure::MemberDeclarationSyntax> NamespaceDeclarationSyntax::getMembersListIteratorBegin() const {
    return ListIterator<structure::MemberDeclarationSyntax>(&MembersContainer, factory, true);
  }

  ListIterator<structure::MemberDeclarationSyntax> NamespaceDeclarationSyntax::getMembersListIteratorEnd() const {
    return ListIterator<structure::MemberDeclarationSyntax>(&MembersContainer, factory, false);
  }

  bool NamespaceDeclarationSyntax::getMembersIsEmpty() const {
    return getMembersListIteratorBegin() == getMembersListIteratorEnd();
  }

  unsigned int NamespaceDeclarationSyntax::getMembersSize() const {
    unsigned int size = 0;
    ListIterator<structure::MemberDeclarationSyntax> endIt = getMembersListIteratorEnd();
    for (ListIterator<structure::MemberDeclarationSyntax> it = getMembersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::NameSyntax* NamespaceDeclarationSyntax::getName() const {
    expression::NameSyntax *_node = NULL;
    if (m_Name != 0)
      _node = dynamic_cast<expression::NameSyntax*>(factory->getPointer(m_Name));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::UsingDirectiveSyntax> NamespaceDeclarationSyntax::getUsingsListIteratorBegin() const {
    return ListIterator<structure::UsingDirectiveSyntax>(&UsingsContainer, factory, true);
  }

  ListIterator<structure::UsingDirectiveSyntax> NamespaceDeclarationSyntax::getUsingsListIteratorEnd() const {
    return ListIterator<structure::UsingDirectiveSyntax>(&UsingsContainer, factory, false);
  }

  bool NamespaceDeclarationSyntax::getUsingsIsEmpty() const {
    return getUsingsListIteratorBegin() == getUsingsListIteratorEnd();
  }

  unsigned int NamespaceDeclarationSyntax::getUsingsSize() const {
    unsigned int size = 0;
    ListIterator<structure::UsingDirectiveSyntax> endIt = getUsingsListIteratorEnd();
    for (ListIterator<structure::UsingDirectiveSyntax> it = getUsingsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool NamespaceDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNamespaceDeclarationSyntax_Externs:
        addExterns(edgeEnd);
        return true;
      case edkNamespaceDeclarationSyntax_Members:
        addMembers(edgeEnd);
        return true;
      case edkNamespaceDeclarationSyntax_Name:
        setName(edgeEnd);
        return true;
      case edkNamespaceDeclarationSyntax_Usings:
        addUsings(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NamespaceDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNamespaceDeclarationSyntax_Externs:
        removeExterns(edgeEnd);
        return true;
      case edkNamespaceDeclarationSyntax_Members:
        removeMembers(edgeEnd);
        return true;
      case edkNamespaceDeclarationSyntax_Name:
        removeName();
        return true;
      case edkNamespaceDeclarationSyntax_Usings:
        removeUsings(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NamespaceDeclarationSyntax::addExterns(const structure::ExternAliasDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkExternAliasDirectiveSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ExternsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNamespaceDeclarationSyntax_Externs);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNamespaceDeclarationSyntax_Externs);
  }

  void NamespaceDeclarationSyntax::addExterns(NodeId _id) {
    const structure::ExternAliasDirectiveSyntax *node = dynamic_cast<structure::ExternAliasDirectiveSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addExterns( node );
  }

  void NamespaceDeclarationSyntax::removeExterns(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::ExternAliasDirectiveSyntax>::Container::iterator it = find(ExternsContainer.begin(), ExternsContainer.end(), id);

    if (it == ExternsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ExternsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNamespaceDeclarationSyntax_Externs);
  }

  void NamespaceDeclarationSyntax::removeExterns(structure::ExternAliasDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeExterns(_node->getId());
  }

  void NamespaceDeclarationSyntax::addMembers(const structure::MemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMemberDeclarationSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    MembersContainer.push_back(_node->getId());
    setParentEdge(_node,edkNamespaceDeclarationSyntax_Members);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNamespaceDeclarationSyntax_Members);
  }

  void NamespaceDeclarationSyntax::addMembers(NodeId _id) {
    const structure::MemberDeclarationSyntax *node = dynamic_cast<structure::MemberDeclarationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addMembers( node );
  }

  void NamespaceDeclarationSyntax::removeMembers(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::MemberDeclarationSyntax>::Container::iterator it = find(MembersContainer.begin(), MembersContainer.end(), id);

    if (it == MembersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    MembersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNamespaceDeclarationSyntax_Members);
  }

  void NamespaceDeclarationSyntax::removeMembers(structure::MemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeMembers(_node->getId());
  }

  void NamespaceDeclarationSyntax::setName(NodeId _id) {
    expression::NameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::NameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkNamespaceDeclarationSyntax_Name);
      }
      m_Name = _node->getId();
      if (m_Name != 0)
        setParentEdge(factory->getPointer(m_Name), edkNamespaceDeclarationSyntax_Name);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Name, this->getId(), edkNamespaceDeclarationSyntax_Name);
    } else {
      if (m_Name) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NamespaceDeclarationSyntax::setName(expression::NameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void NamespaceDeclarationSyntax::removeName() {
      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkNamespaceDeclarationSyntax_Name);
      }
      m_Name = 0;
  }

  void NamespaceDeclarationSyntax::addUsings(const structure::UsingDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkUsingDirectiveSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    UsingsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNamespaceDeclarationSyntax_Usings);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNamespaceDeclarationSyntax_Usings);
  }

  void NamespaceDeclarationSyntax::addUsings(NodeId _id) {
    const structure::UsingDirectiveSyntax *node = dynamic_cast<structure::UsingDirectiveSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addUsings( node );
  }

  void NamespaceDeclarationSyntax::removeUsings(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::UsingDirectiveSyntax>::Container::iterator it = find(UsingsContainer.begin(), UsingsContainer.end(), id);

    if (it == UsingsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    UsingsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNamespaceDeclarationSyntax_Usings);
  }

  void NamespaceDeclarationSyntax::removeUsings(structure::UsingDirectiveSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeUsings(_node->getId());
  }

  void NamespaceDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NamespaceDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NamespaceDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void NamespaceDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType NamespaceDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::NamespaceDeclarationSyntax", strlen("structure::NamespaceDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NamespaceDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_Name);


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

  void NamespaceDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberDeclarationSyntax::load(binIo,false);

    m_Name =  binIo.readUInt4();
    if (m_Name != 0)
      setParentEdge(factory->getPointer(m_Name),edkNamespaceDeclarationSyntax_Name);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ExternsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNamespaceDeclarationSyntax_Externs);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      MembersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNamespaceDeclarationSyntax_Members);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      UsingsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNamespaceDeclarationSyntax_Usings);
      _id = binIo.readUInt4();
    }
  }


}


}}}
