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
  BasePropertyDeclarationSyntax::BasePropertyDeclarationSyntax(NodeId _id, Factory *_factory) :
    MemberDeclarationSyntax(_id, _factory),
    m_AccessorList(0),
    AttributeListsContainer(),
    m_ExplicitInterfaceSpecifier(0),
    m_Type(0)
  {
  }

  BasePropertyDeclarationSyntax::~BasePropertyDeclarationSyntax() {
  }

  void BasePropertyDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    removeAccessorList();
    while (!AttributeListsContainer.empty()) {
      const NodeId id = *AttributeListsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBasePropertyDeclarationSyntax_AttributeLists);
      AttributeListsContainer.pop_front();
    }
    removeExplicitInterfaceSpecifier();
    removeType();
    structure::MemberDeclarationSyntax::prepareDelete(false);
  }

  structure::AccessorListSyntax* BasePropertyDeclarationSyntax::getAccessorList() const {
    structure::AccessorListSyntax *_node = NULL;
    if (m_AccessorList != 0)
      _node = dynamic_cast<structure::AccessorListSyntax*>(factory->getPointer(m_AccessorList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::AttributeListSyntax> BasePropertyDeclarationSyntax::getAttributeListsListIteratorBegin() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, true);
  }

  ListIterator<structure::AttributeListSyntax> BasePropertyDeclarationSyntax::getAttributeListsListIteratorEnd() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, false);
  }

  bool BasePropertyDeclarationSyntax::getAttributeListsIsEmpty() const {
    return getAttributeListsListIteratorBegin() == getAttributeListsListIteratorEnd();
  }

  unsigned int BasePropertyDeclarationSyntax::getAttributeListsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeListSyntax> endIt = getAttributeListsListIteratorEnd();
    for (ListIterator<structure::AttributeListSyntax> it = getAttributeListsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::ExplicitInterfaceSpecifierSyntax* BasePropertyDeclarationSyntax::getExplicitInterfaceSpecifier() const {
    structure::ExplicitInterfaceSpecifierSyntax *_node = NULL;
    if (m_ExplicitInterfaceSpecifier != 0)
      _node = dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(factory->getPointer(m_ExplicitInterfaceSpecifier));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* BasePropertyDeclarationSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool BasePropertyDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBasePropertyDeclarationSyntax_AccessorList:
        setAccessorList(edgeEnd);
        return true;
      case edkBasePropertyDeclarationSyntax_AttributeLists:
        addAttributeLists(edgeEnd);
        return true;
      case edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier:
        setExplicitInterfaceSpecifier(edgeEnd);
        return true;
      case edkBasePropertyDeclarationSyntax_Type:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BasePropertyDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBasePropertyDeclarationSyntax_AccessorList:
        removeAccessorList();
        return true;
      case edkBasePropertyDeclarationSyntax_AttributeLists:
        removeAttributeLists(edgeEnd);
        return true;
      case edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier:
        removeExplicitInterfaceSpecifier();
        return true;
      case edkBasePropertyDeclarationSyntax_Type:
        removeType();
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BasePropertyDeclarationSyntax::setAccessorList(NodeId _id) {
    structure::AccessorListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::AccessorListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_AccessorList) {
        removeParentEdge(m_AccessorList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_AccessorList, m_id, edkBasePropertyDeclarationSyntax_AccessorList);
      }
      m_AccessorList = _node->getId();
      if (m_AccessorList != 0)
        setParentEdge(factory->getPointer(m_AccessorList), edkBasePropertyDeclarationSyntax_AccessorList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_AccessorList, this->getId(), edkBasePropertyDeclarationSyntax_AccessorList);
    } else {
      if (m_AccessorList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BasePropertyDeclarationSyntax::setAccessorList(structure::AccessorListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAccessorList(_node->getId());
  }

  void BasePropertyDeclarationSyntax::removeAccessorList() {
      if (m_AccessorList) {
        removeParentEdge(m_AccessorList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_AccessorList, m_id, edkBasePropertyDeclarationSyntax_AccessorList);
      }
      m_AccessorList = 0;
  }

  void BasePropertyDeclarationSyntax::addAttributeLists(const structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeListSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributeListsContainer.push_back(_node->getId());
    setParentEdge(_node,edkBasePropertyDeclarationSyntax_AttributeLists);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBasePropertyDeclarationSyntax_AttributeLists);
  }

  void BasePropertyDeclarationSyntax::addAttributeLists(NodeId _id) {
    const structure::AttributeListSyntax *node = dynamic_cast<structure::AttributeListSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributeLists( node );
  }

  void BasePropertyDeclarationSyntax::removeAttributeLists(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeListSyntax>::Container::iterator it = find(AttributeListsContainer.begin(), AttributeListsContainer.end(), id);

    if (it == AttributeListsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributeListsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBasePropertyDeclarationSyntax_AttributeLists);
  }

  void BasePropertyDeclarationSyntax::removeAttributeLists(structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributeLists(_node->getId());
  }

  void BasePropertyDeclarationSyntax::setExplicitInterfaceSpecifier(NodeId _id) {
    structure::ExplicitInterfaceSpecifierSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ExplicitInterfaceSpecifier) {
        removeParentEdge(m_ExplicitInterfaceSpecifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExplicitInterfaceSpecifier, m_id, edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
      }
      m_ExplicitInterfaceSpecifier = _node->getId();
      if (m_ExplicitInterfaceSpecifier != 0)
        setParentEdge(factory->getPointer(m_ExplicitInterfaceSpecifier), edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExplicitInterfaceSpecifier, this->getId(), edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
    } else {
      if (m_ExplicitInterfaceSpecifier) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BasePropertyDeclarationSyntax::setExplicitInterfaceSpecifier(structure::ExplicitInterfaceSpecifierSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExplicitInterfaceSpecifier(_node->getId());
  }

  void BasePropertyDeclarationSyntax::removeExplicitInterfaceSpecifier() {
      if (m_ExplicitInterfaceSpecifier) {
        removeParentEdge(m_ExplicitInterfaceSpecifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExplicitInterfaceSpecifier, m_id, edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
      }
      m_ExplicitInterfaceSpecifier = 0;
  }

  void BasePropertyDeclarationSyntax::setType(NodeId _id) {
    expression::TypeSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::TypeSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkBasePropertyDeclarationSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkBasePropertyDeclarationSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkBasePropertyDeclarationSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BasePropertyDeclarationSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void BasePropertyDeclarationSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkBasePropertyDeclarationSyntax_Type);
      }
      m_Type = 0;
  }

  double BasePropertyDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BasePropertyDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType BasePropertyDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::BasePropertyDeclarationSyntax", strlen("structure::BasePropertyDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BasePropertyDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_AccessorList);
    binIo.writeUInt4(m_ExplicitInterfaceSpecifier);
    binIo.writeUInt4(m_Type);


    for (ListIterator<structure::AttributeListSyntax>::Container::const_iterator it = AttributeListsContainer.begin(); it != AttributeListsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BasePropertyDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberDeclarationSyntax::load(binIo,false);

    m_AccessorList =  binIo.readUInt4();
    if (m_AccessorList != 0)
      setParentEdge(factory->getPointer(m_AccessorList),edkBasePropertyDeclarationSyntax_AccessorList);

    m_ExplicitInterfaceSpecifier =  binIo.readUInt4();
    if (m_ExplicitInterfaceSpecifier != 0)
      setParentEdge(factory->getPointer(m_ExplicitInterfaceSpecifier),edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkBasePropertyDeclarationSyntax_Type);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributeListsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBasePropertyDeclarationSyntax_AttributeLists);
      _id = binIo.readUInt4();
    }
  }


}


}}}
