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
  NullableTypeSyntax::NullableTypeSyntax(NodeId _id, Factory *_factory) :
    TypeSyntax(_id, _factory),
    m_ElementType(0)
  {
  }

  NullableTypeSyntax::~NullableTypeSyntax() {
  }

  void NullableTypeSyntax::prepareDelete(bool tryOnVirtualParent){
    removeElementType();
    expression::TypeSyntax::prepareDelete(false);
  }

  NodeKind NullableTypeSyntax::getNodeKind() const {
    return ndkNullableTypeSyntax;
  }

  expression::TypeSyntax* NullableTypeSyntax::getElementType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_ElementType != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_ElementType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool NullableTypeSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNullableTypeSyntax_ElementType:
        setElementType(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::TypeSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NullableTypeSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNullableTypeSyntax_ElementType:
        removeElementType();
        return true;
      default:
        break;
    }
    if (expression::TypeSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NullableTypeSyntax::setElementType(NodeId _id) {
    expression::TypeSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::TypeSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ElementType) {
        removeParentEdge(m_ElementType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ElementType, m_id, edkNullableTypeSyntax_ElementType);
      }
      m_ElementType = _node->getId();
      if (m_ElementType != 0)
        setParentEdge(factory->getPointer(m_ElementType), edkNullableTypeSyntax_ElementType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ElementType, this->getId(), edkNullableTypeSyntax_ElementType);
    } else {
      if (m_ElementType) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NullableTypeSyntax::setElementType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setElementType(_node->getId());
  }

  void NullableTypeSyntax::removeElementType() {
      if (m_ElementType) {
        removeParentEdge(m_ElementType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ElementType, m_id, edkNullableTypeSyntax_ElementType);
      }
      m_ElementType = 0;
  }

  void NullableTypeSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NullableTypeSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NullableTypeSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void NullableTypeSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType NullableTypeSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::NullableTypeSyntax", strlen("expression::NullableTypeSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NullableTypeSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    TypeSyntax::save(binIo,false);

    binIo.writeUInt4(m_ElementType);

  }

  void NullableTypeSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    TypeSyntax::load(binIo,false);

    m_ElementType =  binIo.readUInt4();
    if (m_ElementType != 0)
      setParentEdge(factory->getPointer(m_ElementType),edkNullableTypeSyntax_ElementType);

  }


}


}}}
