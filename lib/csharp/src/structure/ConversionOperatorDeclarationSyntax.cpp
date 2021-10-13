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
  ConversionOperatorDeclarationSyntax::ConversionOperatorDeclarationSyntax(NodeId _id, Factory *_factory) :
    BaseMethodDeclarationSyntax(_id, _factory),
    m_Type(0)
  {
  }

  ConversionOperatorDeclarationSyntax::~ConversionOperatorDeclarationSyntax() {
  }

  void ConversionOperatorDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    removeType();
    structure::BaseMethodDeclarationSyntax::prepareDelete(false);
  }

  NodeKind ConversionOperatorDeclarationSyntax::getNodeKind() const {
    return ndkConversionOperatorDeclarationSyntax;
  }

  expression::TypeSyntax* ConversionOperatorDeclarationSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ConversionOperatorDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConversionOperatorDeclarationSyntax_Type:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BaseMethodDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ConversionOperatorDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConversionOperatorDeclarationSyntax_Type:
        removeType();
        return true;
      default:
        break;
    }
    if (structure::BaseMethodDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ConversionOperatorDeclarationSyntax::setType(NodeId _id) {
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

      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkConversionOperatorDeclarationSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkConversionOperatorDeclarationSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkConversionOperatorDeclarationSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConversionOperatorDeclarationSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void ConversionOperatorDeclarationSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkConversionOperatorDeclarationSyntax_Type);
      }
      m_Type = 0;
  }

  void ConversionOperatorDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ConversionOperatorDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ConversionOperatorDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ConversionOperatorDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ConversionOperatorDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ConversionOperatorDeclarationSyntax", strlen("structure::ConversionOperatorDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ConversionOperatorDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BaseMethodDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_Type);

  }

  void ConversionOperatorDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BaseMethodDeclarationSyntax::load(binIo,false);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkConversionOperatorDeclarationSyntax_Type);

  }


}


}}}
