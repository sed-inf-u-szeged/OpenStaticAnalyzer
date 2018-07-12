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
  EqualsValueClauseSyntax::EqualsValueClauseSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_Value(0)
  {
  }

  EqualsValueClauseSyntax::~EqualsValueClauseSyntax() {
  }

  void EqualsValueClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    removeValue();
    base::Positioned::prepareDelete(false);
  }

  NodeKind EqualsValueClauseSyntax::getNodeKind() const {
    return ndkEqualsValueClauseSyntax;
  }

  expression::ExpressionSyntax* EqualsValueClauseSyntax::getValue() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Value != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Value));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool EqualsValueClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEqualsValueClauseSyntax_Value:
        setValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool EqualsValueClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEqualsValueClauseSyntax_Value:
        removeValue();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void EqualsValueClauseSyntax::setValue(NodeId _id) {
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

      if (m_Value) {
        removeParentEdge(m_Value);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Value, m_id, edkEqualsValueClauseSyntax_Value);
      }
      m_Value = _node->getId();
      if (m_Value != 0)
        setParentEdge(factory->getPointer(m_Value), edkEqualsValueClauseSyntax_Value);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Value, this->getId(), edkEqualsValueClauseSyntax_Value);
    } else {
      if (m_Value) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void EqualsValueClauseSyntax::setValue(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValue(_node->getId());
  }

  void EqualsValueClauseSyntax::removeValue() {
      if (m_Value) {
        removeParentEdge(m_Value);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Value, m_id, edkEqualsValueClauseSyntax_Value);
      }
      m_Value = 0;
  }

  void EqualsValueClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void EqualsValueClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double EqualsValueClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void EqualsValueClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType EqualsValueClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::EqualsValueClauseSyntax", strlen("structure::EqualsValueClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void EqualsValueClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Value);

  }

  void EqualsValueClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Value =  binIo.readUInt4();
    if (m_Value != 0)
      setParentEdge(factory->getPointer(m_Value),edkEqualsValueClauseSyntax_Value);

  }


}


}}}
