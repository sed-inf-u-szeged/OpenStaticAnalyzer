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
  AnonymousFunctionExpressionSyntax::AnonymousFunctionExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_identifier(0),
    m_Block(0),
    m_ExpressionBody(0)
  {
  }

  AnonymousFunctionExpressionSyntax::~AnonymousFunctionExpressionSyntax() {
  }

  void AnonymousFunctionExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeBlock();
    removeExpressionBody();
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

  statement::BlockSyntax* AnonymousFunctionExpressionSyntax::getBlock() const {
    statement::BlockSyntax *_node = NULL;
    if (m_Block != 0)
      _node = dynamic_cast<statement::BlockSyntax*>(factory->getPointer(m_Block));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* AnonymousFunctionExpressionSyntax::getExpressionBody() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_ExpressionBody != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_ExpressionBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AnonymousFunctionExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnonymousFunctionExpressionSyntax_Block:
        setBlock(edgeEnd);
        return true;
      case edkAnonymousFunctionExpressionSyntax_ExpressionBody:
        setExpressionBody(edgeEnd);
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
      case edkAnonymousFunctionExpressionSyntax_Block:
        removeBlock();
        return true;
      case edkAnonymousFunctionExpressionSyntax_ExpressionBody:
        removeExpressionBody();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AnonymousFunctionExpressionSyntax::setBlock(NodeId _id) {
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

      if (m_Block) {
        removeParentEdge(m_Block);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Block, m_id, edkAnonymousFunctionExpressionSyntax_Block);
      }
      m_Block = _node->getId();
      if (m_Block != 0)
        setParentEdge(factory->getPointer(m_Block), edkAnonymousFunctionExpressionSyntax_Block);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Block, this->getId(), edkAnonymousFunctionExpressionSyntax_Block);
    } else {
      if (m_Block) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AnonymousFunctionExpressionSyntax::setBlock(statement::BlockSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBlock(_node->getId());
  }

  void AnonymousFunctionExpressionSyntax::removeBlock() {
      if (m_Block) {
        removeParentEdge(m_Block);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Block, m_id, edkAnonymousFunctionExpressionSyntax_Block);
      }
      m_Block = 0;
  }

  void AnonymousFunctionExpressionSyntax::setExpressionBody(NodeId _id) {
    expression::ExpressionSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ExpressionSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkAnonymousFunctionExpressionSyntax_ExpressionBody);
      }
      m_ExpressionBody = _node->getId();
      if (m_ExpressionBody != 0)
        setParentEdge(factory->getPointer(m_ExpressionBody), edkAnonymousFunctionExpressionSyntax_ExpressionBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExpressionBody, this->getId(), edkAnonymousFunctionExpressionSyntax_ExpressionBody);
    } else {
      if (m_ExpressionBody) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AnonymousFunctionExpressionSyntax::setExpressionBody(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionBody(_node->getId());
  }

  void AnonymousFunctionExpressionSyntax::removeExpressionBody() {
      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkAnonymousFunctionExpressionSyntax_ExpressionBody);
      }
      m_ExpressionBody = 0;
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

    binIo.writeUInt4(m_Block);
    binIo.writeUInt4(m_ExpressionBody);

  }

  void AnonymousFunctionExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_Block =  binIo.readUInt4();
    if (m_Block != 0)
      setParentEdge(factory->getPointer(m_Block),edkAnonymousFunctionExpressionSyntax_Block);

    m_ExpressionBody =  binIo.readUInt4();
    if (m_ExpressionBody != 0)
      setParentEdge(factory->getPointer(m_ExpressionBody),edkAnonymousFunctionExpressionSyntax_ExpressionBody);

  }


}


}}}
