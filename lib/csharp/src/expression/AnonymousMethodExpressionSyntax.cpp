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

namespace expression { 
  AnonymousMethodExpressionSyntax::AnonymousMethodExpressionSyntax(NodeId _id, Factory *_factory) :
    AnonymousFunctionExpressionSyntax(_id, _factory),
    m_ParameterList(0)
  {
  }

  AnonymousMethodExpressionSyntax::~AnonymousMethodExpressionSyntax() {
  }

  void AnonymousMethodExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeParameterList();
    expression::AnonymousFunctionExpressionSyntax::prepareDelete(false);
  }

  NodeKind AnonymousMethodExpressionSyntax::getNodeKind() const {
    return ndkAnonymousMethodExpressionSyntax;
  }

  structure::ParameterListSyntax* AnonymousMethodExpressionSyntax::getParameterList() const {
    structure::ParameterListSyntax *_node = NULL;
    if (m_ParameterList != 0)
      _node = dynamic_cast<structure::ParameterListSyntax*>(factory->getPointer(m_ParameterList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AnonymousMethodExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnonymousMethodExpressionSyntax_ParameterList:
        setParameterList(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::AnonymousFunctionExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AnonymousMethodExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnonymousMethodExpressionSyntax_ParameterList:
        removeParameterList();
        return true;
      default:
        break;
    }
    if (expression::AnonymousFunctionExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AnonymousMethodExpressionSyntax::setParameterList(NodeId _id) {
    structure::ParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkAnonymousMethodExpressionSyntax_ParameterList);
      }
      m_ParameterList = _node->getId();
      if (m_ParameterList != 0)
        setParentEdge(factory->getPointer(m_ParameterList), edkAnonymousMethodExpressionSyntax_ParameterList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ParameterList, this->getId(), edkAnonymousMethodExpressionSyntax_ParameterList);
    } else {
      if (m_ParameterList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AnonymousMethodExpressionSyntax::setParameterList(structure::ParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameterList(_node->getId());
  }

  void AnonymousMethodExpressionSyntax::removeParameterList() {
      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkAnonymousMethodExpressionSyntax_ParameterList);
      }
      m_ParameterList = 0;
  }

  void AnonymousMethodExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AnonymousMethodExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AnonymousMethodExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AnonymousMethodExpressionSyntax& node = dynamic_cast<const AnonymousMethodExpressionSyntax&>(base);
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

  void AnonymousMethodExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType AnonymousMethodExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::AnonymousMethodExpressionSyntax", strlen("expression::AnonymousMethodExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnonymousMethodExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    AnonymousFunctionExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_ParameterList);

  }

  void AnonymousMethodExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    AnonymousFunctionExpressionSyntax::load(binIo,false);

    m_ParameterList =  binIo.readUInt4();
    if (m_ParameterList != 0)
      setParentEdge(factory->getPointer(m_ParameterList),edkAnonymousMethodExpressionSyntax_ParameterList);

  }


}


}}}
