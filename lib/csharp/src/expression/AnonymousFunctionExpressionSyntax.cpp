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
  AnonymousFunctionExpressionSyntax::AnonymousFunctionExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_identifier(0),
    m_Body(0)
  {
  }

  AnonymousFunctionExpressionSyntax::~AnonymousFunctionExpressionSyntax() {
  }

  void AnonymousFunctionExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeBody();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  Key AnonymousFunctionExpressionSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& AnonymousFunctionExpressionSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void AnonymousFunctionExpressionSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void AnonymousFunctionExpressionSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  base::Positioned* AnonymousFunctionExpressionSyntax::getBody() const {
    base::Positioned *_node = NULL;
    if (m_Body != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_Body));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AnonymousFunctionExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnonymousFunctionExpressionSyntax_Body:
        setBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AnonymousFunctionExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnonymousFunctionExpressionSyntax_Body:
        removeBody();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AnonymousFunctionExpressionSyntax::setBody(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkAnonymousFunctionExpressionSyntax_Body);
      }
      m_Body = _node->getId();
      if (m_Body != 0)
        setParentEdge(factory->getPointer(m_Body), edkAnonymousFunctionExpressionSyntax_Body);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Body, this->getId(), edkAnonymousFunctionExpressionSyntax_Body);
    } else {
      if (m_Body) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AnonymousFunctionExpressionSyntax::setBody(base::Positioned *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void AnonymousFunctionExpressionSyntax::removeBody() {
      if (m_Body) {
        removeParentEdge(m_Body);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Body, m_id, edkAnonymousFunctionExpressionSyntax_Body);
      }
      m_Body = 0;
  }

  double AnonymousFunctionExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AnonymousFunctionExpressionSyntax& node = dynamic_cast<const AnonymousFunctionExpressionSyntax&>(base);
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

  void AnonymousFunctionExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType AnonymousFunctionExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::AnonymousFunctionExpressionSyntax", strlen("expression::AnonymousFunctionExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnonymousFunctionExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_Body);

  }

  void AnonymousFunctionExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_Body =  binIo.readUInt4();
    if (m_Body != 0)
      setParentEdge(factory->getPointer(m_Body),edkAnonymousFunctionExpressionSyntax_Body);

  }


}


}}}
