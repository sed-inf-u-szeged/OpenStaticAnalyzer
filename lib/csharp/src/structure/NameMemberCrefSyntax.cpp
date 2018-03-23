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
  NameMemberCrefSyntax::NameMemberCrefSyntax(NodeId _id, Factory *_factory) :
    MemberCrefSyntax(_id, _factory),
    m_Name(0),
    m_Parameters(0)
  {
  }

  NameMemberCrefSyntax::~NameMemberCrefSyntax() {
  }

  void NameMemberCrefSyntax::prepareDelete(bool tryOnVirtualParent){
    removeName();
    removeParameters();
    structure::MemberCrefSyntax::prepareDelete(false);
  }

  NodeKind NameMemberCrefSyntax::getNodeKind() const {
    return ndkNameMemberCrefSyntax;
  }

  expression::TypeSyntax* NameMemberCrefSyntax::getName() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Name != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Name));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::CrefParameterListSyntax* NameMemberCrefSyntax::getParameters() const {
    structure::CrefParameterListSyntax *_node = NULL;
    if (m_Parameters != 0)
      _node = dynamic_cast<structure::CrefParameterListSyntax*>(factory->getPointer(m_Parameters));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool NameMemberCrefSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNameMemberCrefSyntax_Name:
        setName(edgeEnd);
        return true;
      case edkNameMemberCrefSyntax_Parameters:
        setParameters(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberCrefSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NameMemberCrefSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNameMemberCrefSyntax_Name:
        removeName();
        return true;
      case edkNameMemberCrefSyntax_Parameters:
        removeParameters();
        return true;
      default:
        break;
    }
    if (structure::MemberCrefSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NameMemberCrefSyntax::setName(NodeId _id) {
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

      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkNameMemberCrefSyntax_Name);
      }
      m_Name = _node->getId();
      if (m_Name != 0)
        setParentEdge(factory->getPointer(m_Name), edkNameMemberCrefSyntax_Name);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Name, this->getId(), edkNameMemberCrefSyntax_Name);
    } else {
      if (m_Name) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NameMemberCrefSyntax::setName(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void NameMemberCrefSyntax::removeName() {
      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkNameMemberCrefSyntax_Name);
      }
      m_Name = 0;
  }

  void NameMemberCrefSyntax::setParameters(NodeId _id) {
    structure::CrefParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::CrefParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Parameters) {
        removeParentEdge(m_Parameters);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Parameters, m_id, edkNameMemberCrefSyntax_Parameters);
      }
      m_Parameters = _node->getId();
      if (m_Parameters != 0)
        setParentEdge(factory->getPointer(m_Parameters), edkNameMemberCrefSyntax_Parameters);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Parameters, this->getId(), edkNameMemberCrefSyntax_Parameters);
    } else {
      if (m_Parameters) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NameMemberCrefSyntax::setParameters(structure::CrefParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameters(_node->getId());
  }

  void NameMemberCrefSyntax::removeParameters() {
      if (m_Parameters) {
        removeParentEdge(m_Parameters);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Parameters, m_id, edkNameMemberCrefSyntax_Parameters);
      }
      m_Parameters = 0;
  }

  void NameMemberCrefSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NameMemberCrefSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NameMemberCrefSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void NameMemberCrefSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType NameMemberCrefSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::NameMemberCrefSyntax", strlen("structure::NameMemberCrefSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NameMemberCrefSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberCrefSyntax::save(binIo,false);

    binIo.writeUInt4(m_Name);
    binIo.writeUInt4(m_Parameters);

  }

  void NameMemberCrefSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberCrefSyntax::load(binIo,false);

    m_Name =  binIo.readUInt4();
    if (m_Name != 0)
      setParentEdge(factory->getPointer(m_Name),edkNameMemberCrefSyntax_Name);

    m_Parameters =  binIo.readUInt4();
    if (m_Parameters != 0)
      setParentEdge(factory->getPointer(m_Parameters),edkNameMemberCrefSyntax_Parameters);

  }


}


}}}
