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

namespace expression { 
  GenericNameSyntax::GenericNameSyntax(NodeId _id, Factory *_factory) :
    SimpleNameSyntax(_id, _factory),
    m_TypeArgumentList(0)
  {
  }

  GenericNameSyntax::~GenericNameSyntax() {
  }

  void GenericNameSyntax::prepareDelete(bool tryOnVirtualParent){
    removeTypeArgumentList();
    expression::SimpleNameSyntax::prepareDelete(false);
  }

  NodeKind GenericNameSyntax::getNodeKind() const {
    return ndkGenericNameSyntax;
  }

  structure::TypeArgumentListSyntax* GenericNameSyntax::getTypeArgumentList() const {
    structure::TypeArgumentListSyntax *_node = NULL;
    if (m_TypeArgumentList != 0)
      _node = dynamic_cast<structure::TypeArgumentListSyntax*>(factory->getPointer(m_TypeArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool GenericNameSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenericNameSyntax_TypeArgumentList:
        setTypeArgumentList(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::SimpleNameSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool GenericNameSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenericNameSyntax_TypeArgumentList:
        removeTypeArgumentList();
        return true;
      default:
        break;
    }
    if (expression::SimpleNameSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void GenericNameSyntax::setTypeArgumentList(NodeId _id) {
    structure::TypeArgumentListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::TypeArgumentListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_TypeArgumentList) {
        removeParentEdge(m_TypeArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_TypeArgumentList, m_id, edkGenericNameSyntax_TypeArgumentList);
      }
      m_TypeArgumentList = _node->getId();
      if (m_TypeArgumentList != 0)
        setParentEdge(factory->getPointer(m_TypeArgumentList), edkGenericNameSyntax_TypeArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_TypeArgumentList, this->getId(), edkGenericNameSyntax_TypeArgumentList);
    } else {
      if (m_TypeArgumentList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void GenericNameSyntax::setTypeArgumentList(structure::TypeArgumentListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTypeArgumentList(_node->getId());
  }

  void GenericNameSyntax::removeTypeArgumentList() {
      if (m_TypeArgumentList) {
        removeParentEdge(m_TypeArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_TypeArgumentList, m_id, edkGenericNameSyntax_TypeArgumentList);
      }
      m_TypeArgumentList = 0;
  }

  void GenericNameSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void GenericNameSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double GenericNameSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const GenericNameSyntax& node = dynamic_cast<const GenericNameSyntax&>(base);
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

  void GenericNameSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType GenericNameSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::GenericNameSyntax", strlen("expression::GenericNameSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void GenericNameSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleNameSyntax::save(binIo,false);

    binIo.writeUInt4(m_TypeArgumentList);

  }

  void GenericNameSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleNameSyntax::load(binIo,false);

    m_TypeArgumentList =  binIo.readUInt4();
    if (m_TypeArgumentList != 0)
      setParentEdge(factory->getPointer(m_TypeArgumentList),edkGenericNameSyntax_TypeArgumentList);

  }


}


}}}
