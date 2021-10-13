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
  AccessorDeclarationSyntax::AccessorDeclarationSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_identifier(0),
    AttributeListsContainer(),
    m_Body(0),
    m_ExpressionBody(0)
  {
  }

  AccessorDeclarationSyntax::~AccessorDeclarationSyntax() {
  }

  void AccessorDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributeListsContainer.empty()) {
      const NodeId id = *AttributeListsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAccessorDeclarationSyntax_AttributeLists);
      AttributeListsContainer.pop_front();
    }
    removeBody();
    removeExpressionBody();
    base::Positioned::prepareDelete(false);
  }

  NodeKind AccessorDeclarationSyntax::getNodeKind() const {
    return ndkAccessorDeclarationSyntax;
  }

  Key AccessorDeclarationSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& AccessorDeclarationSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void AccessorDeclarationSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void AccessorDeclarationSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  ListIterator<structure::AttributeListSyntax> AccessorDeclarationSyntax::getAttributeListsListIteratorBegin() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, true);
  }

  ListIterator<structure::AttributeListSyntax> AccessorDeclarationSyntax::getAttributeListsListIteratorEnd() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, false);
  }

  bool AccessorDeclarationSyntax::getAttributeListsIsEmpty() const {
    return getAttributeListsListIteratorBegin() == getAttributeListsListIteratorEnd();
  }

  unsigned int AccessorDeclarationSyntax::getAttributeListsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeListSyntax> endIt = getAttributeListsListIteratorEnd();
    for (ListIterator<structure::AttributeListSyntax> it = getAttributeListsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  statement::BlockSyntax* AccessorDeclarationSyntax::getBody() const {
    statement::BlockSyntax *_node = NULL;
    if (m_Body != 0)
      _node = dynamic_cast<statement::BlockSyntax*>(factory->getPointer(m_Body));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::ArrowExpressionClauseSyntax* AccessorDeclarationSyntax::getExpressionBody() const {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (m_ExpressionBody != 0)
      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*>(factory->getPointer(m_ExpressionBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AccessorDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAccessorDeclarationSyntax_AttributeLists:
        addAttributeLists(edgeEnd);
        return true;
      case edkAccessorDeclarationSyntax_Body:
        setBody(edgeEnd);
        return true;
      case edkAccessorDeclarationSyntax_ExpressionBody:
        setExpressionBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AccessorDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAccessorDeclarationSyntax_AttributeLists:
        removeAttributeLists(edgeEnd);
        return true;
      case edkAccessorDeclarationSyntax_Body:
        removeBody();
        return true;
      case edkAccessorDeclarationSyntax_ExpressionBody:
        removeExpressionBody();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AccessorDeclarationSyntax::addAttributeLists(const structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeListSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributeListsContainer.push_back(_node->getId());
    setParentEdge(_node,edkAccessorDeclarationSyntax_AttributeLists);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAccessorDeclarationSyntax_AttributeLists);
  }

  void AccessorDeclarationSyntax::addAttributeLists(NodeId _id) {
    const structure::AttributeListSyntax *node = dynamic_cast<structure::AttributeListSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributeLists( node );
  }

  void AccessorDeclarationSyntax::removeAttributeLists(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeListSyntax>::Container::iterator it = find(AttributeListsContainer.begin(), AttributeListsContainer.end(), id);

    if (it == AttributeListsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributeListsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAccessorDeclarationSyntax_AttributeLists);
  }

  void AccessorDeclarationSyntax::removeAttributeLists(structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributeLists(_node->getId());
  }

  void AccessorDeclarationSyntax::setBody(NodeId _id) {
    statement::BlockSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::BlockSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkAccessorDeclarationSyntax_Body);
      }
      m_Body = _node->getId();
      if (m_Body != 0)
        setParentEdge(factory->getPointer(m_Body), edkAccessorDeclarationSyntax_Body);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Body, this->getId(), edkAccessorDeclarationSyntax_Body);
    } else {
      if (m_Body) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AccessorDeclarationSyntax::setBody(statement::BlockSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void AccessorDeclarationSyntax::removeBody() {
      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkAccessorDeclarationSyntax_Body);
      }
      m_Body = 0;
  }

  void AccessorDeclarationSyntax::setExpressionBody(NodeId _id) {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkAccessorDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = _node->getId();
      if (m_ExpressionBody != 0)
        setParentEdge(factory->getPointer(m_ExpressionBody), edkAccessorDeclarationSyntax_ExpressionBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExpressionBody, this->getId(), edkAccessorDeclarationSyntax_ExpressionBody);
    } else {
      if (m_ExpressionBody) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AccessorDeclarationSyntax::setExpressionBody(structure::ArrowExpressionClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionBody(_node->getId());
  }

  void AccessorDeclarationSyntax::removeExpressionBody() {
      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkAccessorDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = 0;
  }

  void AccessorDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AccessorDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AccessorDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AccessorDeclarationSyntax& node = dynamic_cast<const AccessorDeclarationSyntax&>(base);
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

  void AccessorDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType AccessorDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::AccessorDeclarationSyntax", strlen("structure::AccessorDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AccessorDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_Body);
    binIo.writeUInt4(m_ExpressionBody);


    for (ListIterator<structure::AttributeListSyntax>::Container::const_iterator it = AttributeListsContainer.begin(); it != AttributeListsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void AccessorDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_Body =  binIo.readUInt4();
    if (m_Body != 0)
      setParentEdge(factory->getPointer(m_Body),edkAccessorDeclarationSyntax_Body);

    m_ExpressionBody =  binIo.readUInt4();
    if (m_ExpressionBody != 0)
      setParentEdge(factory->getPointer(m_ExpressionBody),edkAccessorDeclarationSyntax_ExpressionBody);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributeListsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkAccessorDeclarationSyntax_AttributeLists);
      _id = binIo.readUInt4();
    }
  }


}


}}}
