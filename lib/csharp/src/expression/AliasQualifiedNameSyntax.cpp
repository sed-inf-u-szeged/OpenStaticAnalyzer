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
  AliasQualifiedNameSyntax::AliasQualifiedNameSyntax(NodeId _id, Factory *_factory) :
    NameSyntax(_id, _factory),
    m_Alias(0),
    m_Name(0)
  {
  }

  AliasQualifiedNameSyntax::~AliasQualifiedNameSyntax() {
  }

  void AliasQualifiedNameSyntax::prepareDelete(bool tryOnVirtualParent){
    removeAlias();
    removeName();
    expression::NameSyntax::prepareDelete(false);
  }

  NodeKind AliasQualifiedNameSyntax::getNodeKind() const {
    return ndkAliasQualifiedNameSyntax;
  }

  expression::IdentifierNameSyntax* AliasQualifiedNameSyntax::getAlias() const {
    expression::IdentifierNameSyntax *_node = NULL;
    if (m_Alias != 0)
      _node = dynamic_cast<expression::IdentifierNameSyntax*>(factory->getPointer(m_Alias));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::SimpleNameSyntax* AliasQualifiedNameSyntax::getName() const {
    expression::SimpleNameSyntax *_node = NULL;
    if (m_Name != 0)
      _node = dynamic_cast<expression::SimpleNameSyntax*>(factory->getPointer(m_Name));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AliasQualifiedNameSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAliasQualifiedNameSyntax_Alias:
        setAlias(edgeEnd);
        return true;
      case edkAliasQualifiedNameSyntax_Name:
        setName(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::NameSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AliasQualifiedNameSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAliasQualifiedNameSyntax_Alias:
        removeAlias();
        return true;
      case edkAliasQualifiedNameSyntax_Name:
        removeName();
        return true;
      default:
        break;
    }
    if (expression::NameSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AliasQualifiedNameSyntax::setAlias(NodeId _id) {
    expression::IdentifierNameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::IdentifierNameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Alias) {
        removeParentEdge(m_Alias);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Alias, m_id, edkAliasQualifiedNameSyntax_Alias);
      }
      m_Alias = _node->getId();
      if (m_Alias != 0)
        setParentEdge(factory->getPointer(m_Alias), edkAliasQualifiedNameSyntax_Alias);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Alias, this->getId(), edkAliasQualifiedNameSyntax_Alias);
    } else {
      if (m_Alias) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AliasQualifiedNameSyntax::setAlias(expression::IdentifierNameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAlias(_node->getId());
  }

  void AliasQualifiedNameSyntax::removeAlias() {
      if (m_Alias) {
        removeParentEdge(m_Alias);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Alias, m_id, edkAliasQualifiedNameSyntax_Alias);
      }
      m_Alias = 0;
  }

  void AliasQualifiedNameSyntax::setName(NodeId _id) {
    expression::SimpleNameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::SimpleNameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkAliasQualifiedNameSyntax_Name);
      }
      m_Name = _node->getId();
      if (m_Name != 0)
        setParentEdge(factory->getPointer(m_Name), edkAliasQualifiedNameSyntax_Name);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Name, this->getId(), edkAliasQualifiedNameSyntax_Name);
    } else {
      if (m_Name) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AliasQualifiedNameSyntax::setName(expression::SimpleNameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void AliasQualifiedNameSyntax::removeName() {
      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkAliasQualifiedNameSyntax_Name);
      }
      m_Name = 0;
  }

  void AliasQualifiedNameSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AliasQualifiedNameSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AliasQualifiedNameSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AliasQualifiedNameSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType AliasQualifiedNameSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::AliasQualifiedNameSyntax", strlen("expression::AliasQualifiedNameSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AliasQualifiedNameSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    NameSyntax::save(binIo,false);

    binIo.writeUInt4(m_Alias);
    binIo.writeUInt4(m_Name);

  }

  void AliasQualifiedNameSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    NameSyntax::load(binIo,false);

    m_Alias =  binIo.readUInt4();
    if (m_Alias != 0)
      setParentEdge(factory->getPointer(m_Alias),edkAliasQualifiedNameSyntax_Alias);

    m_Name =  binIo.readUInt4();
    if (m_Name != 0)
      setParentEdge(factory->getPointer(m_Name),edkAliasQualifiedNameSyntax_Name);

  }


}


}}}
