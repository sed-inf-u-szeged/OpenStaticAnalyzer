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
  BaseFieldDeclarationSyntax::BaseFieldDeclarationSyntax(NodeId _id, Factory *_factory) :
    MemberDeclarationSyntax(_id, _factory),
    AttributeListsContainer(),
    m_Declaration(0)
  {
  }

  BaseFieldDeclarationSyntax::~BaseFieldDeclarationSyntax() {
  }

  void BaseFieldDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributeListsContainer.empty()) {
      const NodeId id = *AttributeListsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBaseFieldDeclarationSyntax_AttributeLists);
      AttributeListsContainer.pop_front();
    }
    removeDeclaration();
    structure::MemberDeclarationSyntax::prepareDelete(false);
  }

  ListIterator<structure::AttributeListSyntax> BaseFieldDeclarationSyntax::getAttributeListsListIteratorBegin() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, true);
  }

  ListIterator<structure::AttributeListSyntax> BaseFieldDeclarationSyntax::getAttributeListsListIteratorEnd() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, false);
  }

  bool BaseFieldDeclarationSyntax::getAttributeListsIsEmpty() const {
    return getAttributeListsListIteratorBegin() == getAttributeListsListIteratorEnd();
  }

  unsigned int BaseFieldDeclarationSyntax::getAttributeListsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeListSyntax> endIt = getAttributeListsListIteratorEnd();
    for (ListIterator<structure::AttributeListSyntax> it = getAttributeListsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::VariableDeclarationSyntax* BaseFieldDeclarationSyntax::getDeclaration() const {
    structure::VariableDeclarationSyntax *_node = NULL;
    if (m_Declaration != 0)
      _node = dynamic_cast<structure::VariableDeclarationSyntax*>(factory->getPointer(m_Declaration));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool BaseFieldDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseFieldDeclarationSyntax_AttributeLists:
        addAttributeLists(edgeEnd);
        return true;
      case edkBaseFieldDeclarationSyntax_Declaration:
        setDeclaration(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BaseFieldDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseFieldDeclarationSyntax_AttributeLists:
        removeAttributeLists(edgeEnd);
        return true;
      case edkBaseFieldDeclarationSyntax_Declaration:
        removeDeclaration();
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BaseFieldDeclarationSyntax::addAttributeLists(const structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeListSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributeListsContainer.push_back(_node->getId());
    setParentEdge(_node,edkBaseFieldDeclarationSyntax_AttributeLists);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBaseFieldDeclarationSyntax_AttributeLists);
  }

  void BaseFieldDeclarationSyntax::addAttributeLists(NodeId _id) {
    const structure::AttributeListSyntax *node = dynamic_cast<structure::AttributeListSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributeLists( node );
  }

  void BaseFieldDeclarationSyntax::removeAttributeLists(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeListSyntax>::Container::iterator it = find(AttributeListsContainer.begin(), AttributeListsContainer.end(), id);

    if (it == AttributeListsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributeListsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBaseFieldDeclarationSyntax_AttributeLists);
  }

  void BaseFieldDeclarationSyntax::removeAttributeLists(structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributeLists(_node->getId());
  }

  void BaseFieldDeclarationSyntax::setDeclaration(NodeId _id) {
    structure::VariableDeclarationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::VariableDeclarationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Declaration) {
        removeParentEdge(m_Declaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkBaseFieldDeclarationSyntax_Declaration);
      }
      m_Declaration = _node->getId();
      if (m_Declaration != 0)
        setParentEdge(factory->getPointer(m_Declaration), edkBaseFieldDeclarationSyntax_Declaration);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Declaration, this->getId(), edkBaseFieldDeclarationSyntax_Declaration);
    } else {
      if (m_Declaration) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BaseFieldDeclarationSyntax::setDeclaration(structure::VariableDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDeclaration(_node->getId());
  }

  void BaseFieldDeclarationSyntax::removeDeclaration() {
      if (m_Declaration) {
        removeParentEdge(m_Declaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkBaseFieldDeclarationSyntax_Declaration);
      }
      m_Declaration = 0;
  }

  double BaseFieldDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BaseFieldDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType BaseFieldDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::BaseFieldDeclarationSyntax", strlen("structure::BaseFieldDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BaseFieldDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_Declaration);


    for (ListIterator<structure::AttributeListSyntax>::Container::const_iterator it = AttributeListsContainer.begin(); it != AttributeListsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BaseFieldDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberDeclarationSyntax::load(binIo,false);

    m_Declaration =  binIo.readUInt4();
    if (m_Declaration != 0)
      setParentEdge(factory->getPointer(m_Declaration),edkBaseFieldDeclarationSyntax_Declaration);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributeListsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBaseFieldDeclarationSyntax_AttributeLists);
      _id = binIo.readUInt4();
    }
  }


}


}}}
