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
  VariableDeclaratorSyntax::VariableDeclaratorSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_identifier(0),
    m_ArgumentList(0),
    m_Initializer(0)
  {
  }

  VariableDeclaratorSyntax::~VariableDeclaratorSyntax() {
  }

  void VariableDeclaratorSyntax::prepareDelete(bool tryOnVirtualParent){
    removeArgumentList();
    removeInitializer();
    base::Positioned::prepareDelete(false);
  }

  NodeKind VariableDeclaratorSyntax::getNodeKind() const {
    return ndkVariableDeclaratorSyntax;
  }

  Key VariableDeclaratorSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& VariableDeclaratorSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void VariableDeclaratorSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void VariableDeclaratorSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  structure::BracketedArgumentListSyntax* VariableDeclaratorSyntax::getArgumentList() const {
    structure::BracketedArgumentListSyntax *_node = NULL;
    if (m_ArgumentList != 0)
      _node = dynamic_cast<structure::BracketedArgumentListSyntax*>(factory->getPointer(m_ArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::EqualsValueClauseSyntax* VariableDeclaratorSyntax::getInitializer() const {
    structure::EqualsValueClauseSyntax *_node = NULL;
    if (m_Initializer != 0)
      _node = dynamic_cast<structure::EqualsValueClauseSyntax*>(factory->getPointer(m_Initializer));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool VariableDeclaratorSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclaratorSyntax_ArgumentList:
        setArgumentList(edgeEnd);
        return true;
      case edkVariableDeclaratorSyntax_Initializer:
        setInitializer(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool VariableDeclaratorSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclaratorSyntax_ArgumentList:
        removeArgumentList();
        return true;
      case edkVariableDeclaratorSyntax_Initializer:
        removeInitializer();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void VariableDeclaratorSyntax::setArgumentList(NodeId _id) {
    structure::BracketedArgumentListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::BracketedArgumentListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkVariableDeclaratorSyntax_ArgumentList);
      }
      m_ArgumentList = _node->getId();
      if (m_ArgumentList != 0)
        setParentEdge(factory->getPointer(m_ArgumentList), edkVariableDeclaratorSyntax_ArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ArgumentList, this->getId(), edkVariableDeclaratorSyntax_ArgumentList);
    } else {
      if (m_ArgumentList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void VariableDeclaratorSyntax::setArgumentList(structure::BracketedArgumentListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgumentList(_node->getId());
  }

  void VariableDeclaratorSyntax::removeArgumentList() {
      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkVariableDeclaratorSyntax_ArgumentList);
      }
      m_ArgumentList = 0;
  }

  void VariableDeclaratorSyntax::setInitializer(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Initializer, m_id, edkVariableDeclaratorSyntax_Initializer);
      }
      m_Initializer = _node->getId();
      if (m_Initializer != 0)
        setParentEdge(factory->getPointer(m_Initializer), edkVariableDeclaratorSyntax_Initializer);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Initializer, this->getId(), edkVariableDeclaratorSyntax_Initializer);
    } else {
      if (m_Initializer) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void VariableDeclaratorSyntax::setInitializer(structure::EqualsValueClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInitializer(_node->getId());
  }

  void VariableDeclaratorSyntax::removeInitializer() {
      if (m_Initializer) {
        removeParentEdge(m_Initializer);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Initializer, m_id, edkVariableDeclaratorSyntax_Initializer);
      }
      m_Initializer = 0;
  }

  void VariableDeclaratorSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void VariableDeclaratorSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double VariableDeclaratorSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const VariableDeclaratorSyntax& node = dynamic_cast<const VariableDeclaratorSyntax&>(base);
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

  void VariableDeclaratorSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType VariableDeclaratorSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::VariableDeclaratorSyntax", strlen("structure::VariableDeclaratorSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void VariableDeclaratorSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_ArgumentList);
    binIo.writeUInt4(m_Initializer);

  }

  void VariableDeclaratorSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_ArgumentList =  binIo.readUInt4();
    if (m_ArgumentList != 0)
      setParentEdge(factory->getPointer(m_ArgumentList),edkVariableDeclaratorSyntax_ArgumentList);

    m_Initializer =  binIo.readUInt4();
    if (m_Initializer != 0)
      setParentEdge(factory->getPointer(m_Initializer),edkVariableDeclaratorSyntax_Initializer);

  }


}


}}}
