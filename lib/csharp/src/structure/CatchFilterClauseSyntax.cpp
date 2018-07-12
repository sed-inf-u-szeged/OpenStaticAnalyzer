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
  CatchFilterClauseSyntax::CatchFilterClauseSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_FilterExpression(0)
  {
  }

  CatchFilterClauseSyntax::~CatchFilterClauseSyntax() {
  }

  void CatchFilterClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    removeFilterExpression();
    base::Positioned::prepareDelete(false);
  }

  NodeKind CatchFilterClauseSyntax::getNodeKind() const {
    return ndkCatchFilterClauseSyntax;
  }

  expression::ExpressionSyntax* CatchFilterClauseSyntax::getFilterExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_FilterExpression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_FilterExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool CatchFilterClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCatchFilterClauseSyntax_FilterExpression:
        setFilterExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CatchFilterClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCatchFilterClauseSyntax_FilterExpression:
        removeFilterExpression();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CatchFilterClauseSyntax::setFilterExpression(NodeId _id) {
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

      if (m_FilterExpression) {
        removeParentEdge(m_FilterExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_FilterExpression, m_id, edkCatchFilterClauseSyntax_FilterExpression);
      }
      m_FilterExpression = _node->getId();
      if (m_FilterExpression != 0)
        setParentEdge(factory->getPointer(m_FilterExpression), edkCatchFilterClauseSyntax_FilterExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_FilterExpression, this->getId(), edkCatchFilterClauseSyntax_FilterExpression);
    } else {
      if (m_FilterExpression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CatchFilterClauseSyntax::setFilterExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFilterExpression(_node->getId());
  }

  void CatchFilterClauseSyntax::removeFilterExpression() {
      if (m_FilterExpression) {
        removeParentEdge(m_FilterExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_FilterExpression, m_id, edkCatchFilterClauseSyntax_FilterExpression);
      }
      m_FilterExpression = 0;
  }

  void CatchFilterClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CatchFilterClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CatchFilterClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void CatchFilterClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType CatchFilterClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::CatchFilterClauseSyntax", strlen("structure::CatchFilterClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CatchFilterClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_FilterExpression);

  }

  void CatchFilterClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_FilterExpression =  binIo.readUInt4();
    if (m_FilterExpression != 0)
      setParentEdge(factory->getPointer(m_FilterExpression),edkCatchFilterClauseSyntax_FilterExpression);

  }


}


}}}
