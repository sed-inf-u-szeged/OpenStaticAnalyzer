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

namespace structure { 
  QualifiedCrefSyntax::QualifiedCrefSyntax(NodeId _id, Factory *_factory) :
    CrefSyntax(_id, _factory),
    m_Container(0),
    m_Member(0)
  {
  }

  QualifiedCrefSyntax::~QualifiedCrefSyntax() {
  }

  void QualifiedCrefSyntax::prepareDelete(bool tryOnVirtualParent){
    removeContainer();
    removeMember();
    structure::CrefSyntax::prepareDelete(false);
  }

  NodeKind QualifiedCrefSyntax::getNodeKind() const {
    return ndkQualifiedCrefSyntax;
  }

  expression::TypeSyntax* QualifiedCrefSyntax::getContainer() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Container != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Container));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::MemberCrefSyntax* QualifiedCrefSyntax::getMember() const {
    structure::MemberCrefSyntax *_node = NULL;
    if (m_Member != 0)
      _node = dynamic_cast<structure::MemberCrefSyntax*>(factory->getPointer(m_Member));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool QualifiedCrefSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQualifiedCrefSyntax_Container:
        setContainer(edgeEnd);
        return true;
      case edkQualifiedCrefSyntax_Member:
        setMember(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::CrefSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool QualifiedCrefSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQualifiedCrefSyntax_Container:
        removeContainer();
        return true;
      case edkQualifiedCrefSyntax_Member:
        removeMember();
        return true;
      default:
        break;
    }
    if (structure::CrefSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void QualifiedCrefSyntax::setContainer(NodeId _id) {
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

      if (m_Container) {
        removeParentEdge(m_Container);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Container, m_id, edkQualifiedCrefSyntax_Container);
      }
      m_Container = _node->getId();
      if (m_Container != 0)
        setParentEdge(factory->getPointer(m_Container), edkQualifiedCrefSyntax_Container);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Container, this->getId(), edkQualifiedCrefSyntax_Container);
    } else {
      if (m_Container) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QualifiedCrefSyntax::setContainer(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setContainer(_node->getId());
  }

  void QualifiedCrefSyntax::removeContainer() {
      if (m_Container) {
        removeParentEdge(m_Container);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Container, m_id, edkQualifiedCrefSyntax_Container);
      }
      m_Container = 0;
  }

  void QualifiedCrefSyntax::setMember(NodeId _id) {
    structure::MemberCrefSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::MemberCrefSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Member) {
        removeParentEdge(m_Member);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Member, m_id, edkQualifiedCrefSyntax_Member);
      }
      m_Member = _node->getId();
      if (m_Member != 0)
        setParentEdge(factory->getPointer(m_Member), edkQualifiedCrefSyntax_Member);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Member, this->getId(), edkQualifiedCrefSyntax_Member);
    } else {
      if (m_Member) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QualifiedCrefSyntax::setMember(structure::MemberCrefSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setMember(_node->getId());
  }

  void QualifiedCrefSyntax::removeMember() {
      if (m_Member) {
        removeParentEdge(m_Member);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Member, m_id, edkQualifiedCrefSyntax_Member);
      }
      m_Member = 0;
  }

  void QualifiedCrefSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void QualifiedCrefSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double QualifiedCrefSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void QualifiedCrefSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType QualifiedCrefSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::QualifiedCrefSyntax", strlen("structure::QualifiedCrefSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void QualifiedCrefSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CrefSyntax::save(binIo,false);

    binIo.writeUInt4(m_Container);
    binIo.writeUInt4(m_Member);

  }

  void QualifiedCrefSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CrefSyntax::load(binIo,false);

    m_Container =  binIo.readUInt4();
    if (m_Container != 0)
      setParentEdge(factory->getPointer(m_Container),edkQualifiedCrefSyntax_Container);

    m_Member =  binIo.readUInt4();
    if (m_Member != 0)
      setParentEdge(factory->getPointer(m_Member),edkQualifiedCrefSyntax_Member);

  }


}


}}}
