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
  UsingDirectiveSyntax::UsingDirectiveSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_Alias(0),
    m_Name(0)
  {
  }

  UsingDirectiveSyntax::~UsingDirectiveSyntax() {
  }

  void UsingDirectiveSyntax::prepareDelete(bool tryOnVirtualParent){
    removeAlias();
    removeName();
    base::Positioned::prepareDelete(false);
  }

  NodeKind UsingDirectiveSyntax::getNodeKind() const {
    return ndkUsingDirectiveSyntax;
  }

  structure::NameEqualsSyntax* UsingDirectiveSyntax::getAlias() const {
    structure::NameEqualsSyntax *_node = NULL;
    if (m_Alias != 0)
      _node = dynamic_cast<structure::NameEqualsSyntax*>(factory->getPointer(m_Alias));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::NameSyntax* UsingDirectiveSyntax::getName() const {
    expression::NameSyntax *_node = NULL;
    if (m_Name != 0)
      _node = dynamic_cast<expression::NameSyntax*>(factory->getPointer(m_Name));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool UsingDirectiveSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkUsingDirectiveSyntax_Alias:
        setAlias(edgeEnd);
        return true;
      case edkUsingDirectiveSyntax_Name:
        setName(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool UsingDirectiveSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkUsingDirectiveSyntax_Alias:
        removeAlias();
        return true;
      case edkUsingDirectiveSyntax_Name:
        removeName();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void UsingDirectiveSyntax::setAlias(NodeId _id) {
    structure::NameEqualsSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::NameEqualsSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Alias) {
        removeParentEdge(m_Alias);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Alias, m_id, edkUsingDirectiveSyntax_Alias);
      }
      m_Alias = _node->getId();
      if (m_Alias != 0)
        setParentEdge(factory->getPointer(m_Alias), edkUsingDirectiveSyntax_Alias);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Alias, this->getId(), edkUsingDirectiveSyntax_Alias);
    } else {
      if (m_Alias) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void UsingDirectiveSyntax::setAlias(structure::NameEqualsSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAlias(_node->getId());
  }

  void UsingDirectiveSyntax::removeAlias() {
      if (m_Alias) {
        removeParentEdge(m_Alias);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Alias, m_id, edkUsingDirectiveSyntax_Alias);
      }
      m_Alias = 0;
  }

  void UsingDirectiveSyntax::setName(NodeId _id) {
    expression::NameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::NameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkUsingDirectiveSyntax_Name);
      }
      m_Name = _node->getId();
      if (m_Name != 0)
        setParentEdge(factory->getPointer(m_Name), edkUsingDirectiveSyntax_Name);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Name, this->getId(), edkUsingDirectiveSyntax_Name);
    } else {
      if (m_Name) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void UsingDirectiveSyntax::setName(expression::NameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void UsingDirectiveSyntax::removeName() {
      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkUsingDirectiveSyntax_Name);
      }
      m_Name = 0;
  }

  void UsingDirectiveSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void UsingDirectiveSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double UsingDirectiveSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void UsingDirectiveSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType UsingDirectiveSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::UsingDirectiveSyntax", strlen("structure::UsingDirectiveSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void UsingDirectiveSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Alias);
    binIo.writeUInt4(m_Name);

  }

  void UsingDirectiveSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Alias =  binIo.readUInt4();
    if (m_Alias != 0)
      setParentEdge(factory->getPointer(m_Alias),edkUsingDirectiveSyntax_Alias);

    m_Name =  binIo.readUInt4();
    if (m_Name != 0)
      setParentEdge(factory->getPointer(m_Name),edkUsingDirectiveSyntax_Name);

  }


}


}}}
