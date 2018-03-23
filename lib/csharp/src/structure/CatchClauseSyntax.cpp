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
  CatchClauseSyntax::CatchClauseSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_Block(0),
    m_Declaration(0),
    m_Filter(0)
  {
  }

  CatchClauseSyntax::~CatchClauseSyntax() {
  }

  void CatchClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    removeBlock();
    removeDeclaration();
    removeFilter();
    base::Positioned::prepareDelete(false);
  }

  NodeKind CatchClauseSyntax::getNodeKind() const {
    return ndkCatchClauseSyntax;
  }

  statement::BlockSyntax* CatchClauseSyntax::getBlock() const {
    statement::BlockSyntax *_node = NULL;
    if (m_Block != 0)
      _node = dynamic_cast<statement::BlockSyntax*>(factory->getPointer(m_Block));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::CatchDeclarationSyntax* CatchClauseSyntax::getDeclaration() const {
    structure::CatchDeclarationSyntax *_node = NULL;
    if (m_Declaration != 0)
      _node = dynamic_cast<structure::CatchDeclarationSyntax*>(factory->getPointer(m_Declaration));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::CatchFilterClauseSyntax* CatchClauseSyntax::getFilter() const {
    structure::CatchFilterClauseSyntax *_node = NULL;
    if (m_Filter != 0)
      _node = dynamic_cast<structure::CatchFilterClauseSyntax*>(factory->getPointer(m_Filter));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool CatchClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCatchClauseSyntax_Block:
        setBlock(edgeEnd);
        return true;
      case edkCatchClauseSyntax_Declaration:
        setDeclaration(edgeEnd);
        return true;
      case edkCatchClauseSyntax_Filter:
        setFilter(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CatchClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCatchClauseSyntax_Block:
        removeBlock();
        return true;
      case edkCatchClauseSyntax_Declaration:
        removeDeclaration();
        return true;
      case edkCatchClauseSyntax_Filter:
        removeFilter();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CatchClauseSyntax::setBlock(NodeId _id) {
    statement::BlockSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::BlockSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Block) {
        removeParentEdge(m_Block);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Block, m_id, edkCatchClauseSyntax_Block);
      }
      m_Block = _node->getId();
      if (m_Block != 0)
        setParentEdge(factory->getPointer(m_Block), edkCatchClauseSyntax_Block);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Block, this->getId(), edkCatchClauseSyntax_Block);
    } else {
      if (m_Block) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CatchClauseSyntax::setBlock(statement::BlockSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBlock(_node->getId());
  }

  void CatchClauseSyntax::removeBlock() {
      if (m_Block) {
        removeParentEdge(m_Block);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Block, m_id, edkCatchClauseSyntax_Block);
      }
      m_Block = 0;
  }

  void CatchClauseSyntax::setDeclaration(NodeId _id) {
    structure::CatchDeclarationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::CatchDeclarationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Declaration) {
        removeParentEdge(m_Declaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkCatchClauseSyntax_Declaration);
      }
      m_Declaration = _node->getId();
      if (m_Declaration != 0)
        setParentEdge(factory->getPointer(m_Declaration), edkCatchClauseSyntax_Declaration);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Declaration, this->getId(), edkCatchClauseSyntax_Declaration);
    } else {
      if (m_Declaration) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CatchClauseSyntax::setDeclaration(structure::CatchDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDeclaration(_node->getId());
  }

  void CatchClauseSyntax::removeDeclaration() {
      if (m_Declaration) {
        removeParentEdge(m_Declaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkCatchClauseSyntax_Declaration);
      }
      m_Declaration = 0;
  }

  void CatchClauseSyntax::setFilter(NodeId _id) {
    structure::CatchFilterClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::CatchFilterClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Filter) {
        removeParentEdge(m_Filter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Filter, m_id, edkCatchClauseSyntax_Filter);
      }
      m_Filter = _node->getId();
      if (m_Filter != 0)
        setParentEdge(factory->getPointer(m_Filter), edkCatchClauseSyntax_Filter);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Filter, this->getId(), edkCatchClauseSyntax_Filter);
    } else {
      if (m_Filter) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CatchClauseSyntax::setFilter(structure::CatchFilterClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFilter(_node->getId());
  }

  void CatchClauseSyntax::removeFilter() {
      if (m_Filter) {
        removeParentEdge(m_Filter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Filter, m_id, edkCatchClauseSyntax_Filter);
      }
      m_Filter = 0;
  }

  void CatchClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CatchClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CatchClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void CatchClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType CatchClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::CatchClauseSyntax", strlen("structure::CatchClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CatchClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Block);
    binIo.writeUInt4(m_Declaration);
    binIo.writeUInt4(m_Filter);

  }

  void CatchClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Block =  binIo.readUInt4();
    if (m_Block != 0)
      setParentEdge(factory->getPointer(m_Block),edkCatchClauseSyntax_Block);

    m_Declaration =  binIo.readUInt4();
    if (m_Declaration != 0)
      setParentEdge(factory->getPointer(m_Declaration),edkCatchClauseSyntax_Declaration);

    m_Filter =  binIo.readUInt4();
    if (m_Filter != 0)
      setParentEdge(factory->getPointer(m_Filter),edkCatchClauseSyntax_Filter);

  }


}


}}}
