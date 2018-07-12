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
  AttributeListSyntax::AttributeListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    AttributesContainer(),
    m_Target(0)
  {
  }

  AttributeListSyntax::~AttributeListSyntax() {
  }

  void AttributeListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributesContainer.empty()) {
      const NodeId id = *AttributesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAttributeListSyntax_Attributes);
      AttributesContainer.pop_front();
    }
    removeTarget();
    base::Positioned::prepareDelete(false);
  }

  NodeKind AttributeListSyntax::getNodeKind() const {
    return ndkAttributeListSyntax;
  }

  ListIterator<structure::AttributeSyntax> AttributeListSyntax::getAttributesListIteratorBegin() const {
    return ListIterator<structure::AttributeSyntax>(&AttributesContainer, factory, true);
  }

  ListIterator<structure::AttributeSyntax> AttributeListSyntax::getAttributesListIteratorEnd() const {
    return ListIterator<structure::AttributeSyntax>(&AttributesContainer, factory, false);
  }

  bool AttributeListSyntax::getAttributesIsEmpty() const {
    return getAttributesListIteratorBegin() == getAttributesListIteratorEnd();
  }

  unsigned int AttributeListSyntax::getAttributesSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeSyntax> endIt = getAttributesListIteratorEnd();
    for (ListIterator<structure::AttributeSyntax> it = getAttributesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::AttributeTargetSpecifierSyntax* AttributeListSyntax::getTarget() const {
    structure::AttributeTargetSpecifierSyntax *_node = NULL;
    if (m_Target != 0)
      _node = dynamic_cast<structure::AttributeTargetSpecifierSyntax*>(factory->getPointer(m_Target));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AttributeListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeListSyntax_Attributes:
        addAttributes(edgeEnd);
        return true;
      case edkAttributeListSyntax_Target:
        setTarget(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AttributeListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeListSyntax_Attributes:
        removeAttributes(edgeEnd);
        return true;
      case edkAttributeListSyntax_Target:
        removeTarget();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AttributeListSyntax::addAttributes(const structure::AttributeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributesContainer.push_back(_node->getId());
    setParentEdge(_node,edkAttributeListSyntax_Attributes);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAttributeListSyntax_Attributes);
  }

  void AttributeListSyntax::addAttributes(NodeId _id) {
    const structure::AttributeSyntax *node = dynamic_cast<structure::AttributeSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributes( node );
  }

  void AttributeListSyntax::removeAttributes(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeSyntax>::Container::iterator it = find(AttributesContainer.begin(), AttributesContainer.end(), id);

    if (it == AttributesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAttributeListSyntax_Attributes);
  }

  void AttributeListSyntax::removeAttributes(structure::AttributeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributes(_node->getId());
  }

  void AttributeListSyntax::setTarget(NodeId _id) {
    structure::AttributeTargetSpecifierSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::AttributeTargetSpecifierSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Target) {
        removeParentEdge(m_Target);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Target, m_id, edkAttributeListSyntax_Target);
      }
      m_Target = _node->getId();
      if (m_Target != 0)
        setParentEdge(factory->getPointer(m_Target), edkAttributeListSyntax_Target);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Target, this->getId(), edkAttributeListSyntax_Target);
    } else {
      if (m_Target) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AttributeListSyntax::setTarget(structure::AttributeTargetSpecifierSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTarget(_node->getId());
  }

  void AttributeListSyntax::removeTarget() {
      if (m_Target) {
        removeParentEdge(m_Target);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Target, m_id, edkAttributeListSyntax_Target);
      }
      m_Target = 0;
  }

  void AttributeListSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AttributeListSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AttributeListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AttributeListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType AttributeListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::AttributeListSyntax", strlen("structure::AttributeListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AttributeListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Target);


    for (ListIterator<structure::AttributeSyntax>::Container::const_iterator it = AttributesContainer.begin(); it != AttributesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void AttributeListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Target =  binIo.readUInt4();
    if (m_Target != 0)
      setParentEdge(factory->getPointer(m_Target),edkAttributeListSyntax_Target);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkAttributeListSyntax_Attributes);
      _id = binIo.readUInt4();
    }
  }


}


}}}
