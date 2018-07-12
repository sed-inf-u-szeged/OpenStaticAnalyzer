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
  PropertyDeclarationSyntax::PropertyDeclarationSyntax(NodeId _id, Factory *_factory) :
    BasePropertyDeclarationSyntax(_id, _factory),
    m_identifier(0),
    m_ExpressionBody(0),
    m_Initializer(0)
  {
  }

  PropertyDeclarationSyntax::~PropertyDeclarationSyntax() {
  }

  void PropertyDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    removeExpressionBody();
    removeInitializer();
    structure::BasePropertyDeclarationSyntax::prepareDelete(false);
  }

  NodeKind PropertyDeclarationSyntax::getNodeKind() const {
    return ndkPropertyDeclarationSyntax;
  }

  Key PropertyDeclarationSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& PropertyDeclarationSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void PropertyDeclarationSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void PropertyDeclarationSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  structure::ArrowExpressionClauseSyntax* PropertyDeclarationSyntax::getExpressionBody() const {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (m_ExpressionBody != 0)
      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*>(factory->getPointer(m_ExpressionBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::EqualsValueClauseSyntax* PropertyDeclarationSyntax::getInitializer() const {
    structure::EqualsValueClauseSyntax *_node = NULL;
    if (m_Initializer != 0)
      _node = dynamic_cast<structure::EqualsValueClauseSyntax*>(factory->getPointer(m_Initializer));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool PropertyDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPropertyDeclarationSyntax_ExpressionBody:
        setExpressionBody(edgeEnd);
        return true;
      case edkPropertyDeclarationSyntax_Initializer:
        setInitializer(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BasePropertyDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool PropertyDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPropertyDeclarationSyntax_ExpressionBody:
        removeExpressionBody();
        return true;
      case edkPropertyDeclarationSyntax_Initializer:
        removeInitializer();
        return true;
      default:
        break;
    }
    if (structure::BasePropertyDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void PropertyDeclarationSyntax::setExpressionBody(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkPropertyDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = _node->getId();
      if (m_ExpressionBody != 0)
        setParentEdge(factory->getPointer(m_ExpressionBody), edkPropertyDeclarationSyntax_ExpressionBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExpressionBody, this->getId(), edkPropertyDeclarationSyntax_ExpressionBody);
    } else {
      if (m_ExpressionBody) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PropertyDeclarationSyntax::setExpressionBody(structure::ArrowExpressionClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionBody(_node->getId());
  }

  void PropertyDeclarationSyntax::removeExpressionBody() {
      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkPropertyDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = 0;
  }

  void PropertyDeclarationSyntax::setInitializer(NodeId _id) {
    structure::EqualsValueClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::EqualsValueClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Initializer) {
        removeParentEdge(m_Initializer);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Initializer, m_id, edkPropertyDeclarationSyntax_Initializer);
      }
      m_Initializer = _node->getId();
      if (m_Initializer != 0)
        setParentEdge(factory->getPointer(m_Initializer), edkPropertyDeclarationSyntax_Initializer);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Initializer, this->getId(), edkPropertyDeclarationSyntax_Initializer);
    } else {
      if (m_Initializer) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PropertyDeclarationSyntax::setInitializer(structure::EqualsValueClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInitializer(_node->getId());
  }

  void PropertyDeclarationSyntax::removeInitializer() {
      if (m_Initializer) {
        removeParentEdge(m_Initializer);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Initializer, m_id, edkPropertyDeclarationSyntax_Initializer);
      }
      m_Initializer = 0;
  }

  void PropertyDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void PropertyDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double PropertyDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const PropertyDeclarationSyntax& node = dynamic_cast<const PropertyDeclarationSyntax&>(base);
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

  void PropertyDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType PropertyDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::PropertyDeclarationSyntax", strlen("structure::PropertyDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void PropertyDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BasePropertyDeclarationSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_ExpressionBody);
    binIo.writeUInt4(m_Initializer);

  }

  void PropertyDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BasePropertyDeclarationSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_ExpressionBody =  binIo.readUInt4();
    if (m_ExpressionBody != 0)
      setParentEdge(factory->getPointer(m_ExpressionBody),edkPropertyDeclarationSyntax_ExpressionBody);

    m_Initializer =  binIo.readUInt4();
    if (m_Initializer != 0)
      setParentEdge(factory->getPointer(m_Initializer),edkPropertyDeclarationSyntax_Initializer);

  }


}


}}}
