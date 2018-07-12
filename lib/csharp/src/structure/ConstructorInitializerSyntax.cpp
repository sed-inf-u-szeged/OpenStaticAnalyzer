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
  ConstructorInitializerSyntax::ConstructorInitializerSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_ArgumentList(0),
    m_ConstructorCall(0)
  {
  }

  ConstructorInitializerSyntax::~ConstructorInitializerSyntax() {
  }

  void ConstructorInitializerSyntax::prepareDelete(bool tryOnVirtualParent){
    removeArgumentList();
    removeConstructorCall();
    base::Positioned::prepareDelete(false);
  }

  NodeKind ConstructorInitializerSyntax::getNodeKind() const {
    return ndkConstructorInitializerSyntax;
  }

  structure::ArgumentListSyntax* ConstructorInitializerSyntax::getArgumentList() const {
    structure::ArgumentListSyntax *_node = NULL;
    if (m_ArgumentList != 0)
      _node = dynamic_cast<structure::ArgumentListSyntax*>(factory->getPointer(m_ArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::ConstructorDeclarationSyntax* ConstructorInitializerSyntax::getConstructorCall() const {
    structure::ConstructorDeclarationSyntax *_node = NULL;
    if (m_ConstructorCall != 0)
      _node = dynamic_cast<structure::ConstructorDeclarationSyntax*>(factory->getPointer(m_ConstructorCall));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ConstructorInitializerSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConstructorInitializerSyntax_ArgumentList:
        setArgumentList(edgeEnd);
        return true;
      case edkConstructorInitializerSyntax_ConstructorCall:
        setConstructorCall(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ConstructorInitializerSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConstructorInitializerSyntax_ArgumentList:
        removeArgumentList();
        return true;
      case edkConstructorInitializerSyntax_ConstructorCall:
        removeConstructorCall();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ConstructorInitializerSyntax::setArgumentList(NodeId _id) {
    structure::ArgumentListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ArgumentListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkConstructorInitializerSyntax_ArgumentList);
      }
      m_ArgumentList = _node->getId();
      if (m_ArgumentList != 0)
        setParentEdge(factory->getPointer(m_ArgumentList), edkConstructorInitializerSyntax_ArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ArgumentList, this->getId(), edkConstructorInitializerSyntax_ArgumentList);
    } else {
      if (m_ArgumentList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConstructorInitializerSyntax::setArgumentList(structure::ArgumentListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgumentList(_node->getId());
  }

  void ConstructorInitializerSyntax::removeArgumentList() {
      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkConstructorInitializerSyntax_ArgumentList);
      }
      m_ArgumentList = 0;
  }

  void ConstructorInitializerSyntax::setConstructorCall(NodeId _id) {
    structure::ConstructorDeclarationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ConstructorDeclarationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ConstructorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ConstructorCall, m_id, edkConstructorInitializerSyntax_ConstructorCall);
      }
      m_ConstructorCall = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ConstructorCall, this->getId(), edkConstructorInitializerSyntax_ConstructorCall);
    } else {
      if (m_ConstructorCall) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConstructorInitializerSyntax::setConstructorCall(structure::ConstructorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setConstructorCall(_node->getId());
  }

  void ConstructorInitializerSyntax::removeConstructorCall() {
      if (m_ConstructorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ConstructorCall, m_id, edkConstructorInitializerSyntax_ConstructorCall);
      }
      m_ConstructorCall = 0;
  }

  void ConstructorInitializerSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ConstructorInitializerSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ConstructorInitializerSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ConstructorInitializerSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ConstructorInitializerSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ConstructorInitializerSyntax", strlen("structure::ConstructorInitializerSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ConstructorInitializerSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_ArgumentList);
    binIo.writeUInt4(m_ConstructorCall);

  }

  void ConstructorInitializerSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_ArgumentList =  binIo.readUInt4();
    if (m_ArgumentList != 0)
      setParentEdge(factory->getPointer(m_ArgumentList),edkConstructorInitializerSyntax_ArgumentList);

    m_ConstructorCall =  binIo.readUInt4();

  }


}


}}}
