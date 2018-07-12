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
  AttributeSyntax::AttributeSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_ArgumentList(0),
    m_Name(0)
  {
  }

  AttributeSyntax::~AttributeSyntax() {
  }

  void AttributeSyntax::prepareDelete(bool tryOnVirtualParent){
    removeArgumentList();
    removeName();
    base::Positioned::prepareDelete(false);
  }

  NodeKind AttributeSyntax::getNodeKind() const {
    return ndkAttributeSyntax;
  }

  structure::AttributeArgumentListSyntax* AttributeSyntax::getArgumentList() const {
    structure::AttributeArgumentListSyntax *_node = NULL;
    if (m_ArgumentList != 0)
      _node = dynamic_cast<structure::AttributeArgumentListSyntax*>(factory->getPointer(m_ArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::NameSyntax* AttributeSyntax::getName() const {
    expression::NameSyntax *_node = NULL;
    if (m_Name != 0)
      _node = dynamic_cast<expression::NameSyntax*>(factory->getPointer(m_Name));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AttributeSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeSyntax_ArgumentList:
        setArgumentList(edgeEnd);
        return true;
      case edkAttributeSyntax_Name:
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

  bool AttributeSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeSyntax_ArgumentList:
        removeArgumentList();
        return true;
      case edkAttributeSyntax_Name:
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

  void AttributeSyntax::setArgumentList(NodeId _id) {
    structure::AttributeArgumentListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::AttributeArgumentListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkAttributeSyntax_ArgumentList);
      }
      m_ArgumentList = _node->getId();
      if (m_ArgumentList != 0)
        setParentEdge(factory->getPointer(m_ArgumentList), edkAttributeSyntax_ArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ArgumentList, this->getId(), edkAttributeSyntax_ArgumentList);
    } else {
      if (m_ArgumentList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AttributeSyntax::setArgumentList(structure::AttributeArgumentListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgumentList(_node->getId());
  }

  void AttributeSyntax::removeArgumentList() {
      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkAttributeSyntax_ArgumentList);
      }
      m_ArgumentList = 0;
  }

  void AttributeSyntax::setName(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Name, m_id, edkAttributeSyntax_Name);
      }
      m_Name = _node->getId();
      if (m_Name != 0)
        setParentEdge(factory->getPointer(m_Name), edkAttributeSyntax_Name);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Name, this->getId(), edkAttributeSyntax_Name);
    } else {
      if (m_Name) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AttributeSyntax::setName(expression::NameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void AttributeSyntax::removeName() {
      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkAttributeSyntax_Name);
      }
      m_Name = 0;
  }

  void AttributeSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AttributeSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AttributeSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AttributeSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType AttributeSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::AttributeSyntax", strlen("structure::AttributeSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AttributeSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_ArgumentList);
    binIo.writeUInt4(m_Name);

  }

  void AttributeSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_ArgumentList =  binIo.readUInt4();
    if (m_ArgumentList != 0)
      setParentEdge(factory->getPointer(m_ArgumentList),edkAttributeSyntax_ArgumentList);

    m_Name =  binIo.readUInt4();
    if (m_Name != 0)
      setParentEdge(factory->getPointer(m_Name),edkAttributeSyntax_Name);

  }


}


}}}
