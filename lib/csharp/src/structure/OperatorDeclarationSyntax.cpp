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
  OperatorDeclarationSyntax::OperatorDeclarationSyntax(NodeId _id, Factory *_factory) :
    BaseMethodDeclarationSyntax(_id, _factory),
    m_ReturnType(0)
  {
  }

  OperatorDeclarationSyntax::~OperatorDeclarationSyntax() {
  }

  void OperatorDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    removeReturnType();
    structure::BaseMethodDeclarationSyntax::prepareDelete(false);
  }

  NodeKind OperatorDeclarationSyntax::getNodeKind() const {
    return ndkOperatorDeclarationSyntax;
  }

  expression::TypeSyntax* OperatorDeclarationSyntax::getReturnType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_ReturnType != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_ReturnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool OperatorDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkOperatorDeclarationSyntax_ReturnType:
        setReturnType(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BaseMethodDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool OperatorDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkOperatorDeclarationSyntax_ReturnType:
        removeReturnType();
        return true;
      default:
        break;
    }
    if (structure::BaseMethodDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void OperatorDeclarationSyntax::setReturnType(NodeId _id) {
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

      if (m_ReturnType) {
        removeParentEdge(m_ReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkOperatorDeclarationSyntax_ReturnType);
      }
      m_ReturnType = _node->getId();
      if (m_ReturnType != 0)
        setParentEdge(factory->getPointer(m_ReturnType), edkOperatorDeclarationSyntax_ReturnType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ReturnType, this->getId(), edkOperatorDeclarationSyntax_ReturnType);
    } else {
      if (m_ReturnType) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void OperatorDeclarationSyntax::setReturnType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void OperatorDeclarationSyntax::removeReturnType() {
      if (m_ReturnType) {
        removeParentEdge(m_ReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkOperatorDeclarationSyntax_ReturnType);
      }
      m_ReturnType = 0;
  }

  void OperatorDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void OperatorDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double OperatorDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void OperatorDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType OperatorDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::OperatorDeclarationSyntax", strlen("structure::OperatorDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void OperatorDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BaseMethodDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_ReturnType);

  }

  void OperatorDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BaseMethodDeclarationSyntax::load(binIo,false);

    m_ReturnType =  binIo.readUInt4();
    if (m_ReturnType != 0)
      setParentEdge(factory->getPointer(m_ReturnType),edkOperatorDeclarationSyntax_ReturnType);

  }


}


}}}
