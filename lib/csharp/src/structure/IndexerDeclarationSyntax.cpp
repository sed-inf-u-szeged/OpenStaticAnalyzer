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
  IndexerDeclarationSyntax::IndexerDeclarationSyntax(NodeId _id, Factory *_factory) :
    BasePropertyDeclarationSyntax(_id, _factory),
    m_ExpressionBody(0),
    m_ParameterList(0)
  {
  }

  IndexerDeclarationSyntax::~IndexerDeclarationSyntax() {
  }

  void IndexerDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    removeExpressionBody();
    removeParameterList();
    structure::BasePropertyDeclarationSyntax::prepareDelete(false);
  }

  NodeKind IndexerDeclarationSyntax::getNodeKind() const {
    return ndkIndexerDeclarationSyntax;
  }

  structure::ArrowExpressionClauseSyntax* IndexerDeclarationSyntax::getExpressionBody() const {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (m_ExpressionBody != 0)
      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*>(factory->getPointer(m_ExpressionBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::BracketedParameterListSyntax* IndexerDeclarationSyntax::getParameterList() const {
    structure::BracketedParameterListSyntax *_node = NULL;
    if (m_ParameterList != 0)
      _node = dynamic_cast<structure::BracketedParameterListSyntax*>(factory->getPointer(m_ParameterList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool IndexerDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIndexerDeclarationSyntax_ExpressionBody:
        setExpressionBody(edgeEnd);
        return true;
      case edkIndexerDeclarationSyntax_ParameterList:
        setParameterList(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BasePropertyDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool IndexerDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIndexerDeclarationSyntax_ExpressionBody:
        removeExpressionBody();
        return true;
      case edkIndexerDeclarationSyntax_ParameterList:
        removeParameterList();
        return true;
      default:
        break;
    }
    if (structure::BasePropertyDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void IndexerDeclarationSyntax::setExpressionBody(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkIndexerDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = _node->getId();
      if (m_ExpressionBody != 0)
        setParentEdge(factory->getPointer(m_ExpressionBody), edkIndexerDeclarationSyntax_ExpressionBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExpressionBody, this->getId(), edkIndexerDeclarationSyntax_ExpressionBody);
    } else {
      if (m_ExpressionBody) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IndexerDeclarationSyntax::setExpressionBody(structure::ArrowExpressionClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionBody(_node->getId());
  }

  void IndexerDeclarationSyntax::removeExpressionBody() {
      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkIndexerDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = 0;
  }

  void IndexerDeclarationSyntax::setParameterList(NodeId _id) {
    structure::BracketedParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::BracketedParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkIndexerDeclarationSyntax_ParameterList);
      }
      m_ParameterList = _node->getId();
      if (m_ParameterList != 0)
        setParentEdge(factory->getPointer(m_ParameterList), edkIndexerDeclarationSyntax_ParameterList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ParameterList, this->getId(), edkIndexerDeclarationSyntax_ParameterList);
    } else {
      if (m_ParameterList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IndexerDeclarationSyntax::setParameterList(structure::BracketedParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameterList(_node->getId());
  }

  void IndexerDeclarationSyntax::removeParameterList() {
      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkIndexerDeclarationSyntax_ParameterList);
      }
      m_ParameterList = 0;
  }

  void IndexerDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void IndexerDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double IndexerDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void IndexerDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType IndexerDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::IndexerDeclarationSyntax", strlen("structure::IndexerDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void IndexerDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BasePropertyDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_ExpressionBody);
    binIo.writeUInt4(m_ParameterList);

  }

  void IndexerDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BasePropertyDeclarationSyntax::load(binIo,false);

    m_ExpressionBody =  binIo.readUInt4();
    if (m_ExpressionBody != 0)
      setParentEdge(factory->getPointer(m_ExpressionBody),edkIndexerDeclarationSyntax_ExpressionBody);

    m_ParameterList =  binIo.readUInt4();
    if (m_ParameterList != 0)
      setParentEdge(factory->getPointer(m_ParameterList),edkIndexerDeclarationSyntax_ParameterList);

  }


}


}}}
