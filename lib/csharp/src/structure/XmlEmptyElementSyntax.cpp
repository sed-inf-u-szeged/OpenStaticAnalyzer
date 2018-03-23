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
  XmlEmptyElementSyntax::XmlEmptyElementSyntax(NodeId _id, Factory *_factory) :
    XmlNodeSyntax(_id, _factory),
    AttributesContainer(),
    m_Name(0)
  {
  }

  XmlEmptyElementSyntax::~XmlEmptyElementSyntax() {
  }

  void XmlEmptyElementSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributesContainer.empty()) {
      const NodeId id = *AttributesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkXmlEmptyElementSyntax_Attributes);
      AttributesContainer.pop_front();
    }
    removeName();
    structure::XmlNodeSyntax::prepareDelete(false);
  }

  NodeKind XmlEmptyElementSyntax::getNodeKind() const {
    return ndkXmlEmptyElementSyntax;
  }

  ListIterator<structure::XmlAttributeSyntax> XmlEmptyElementSyntax::getAttributesListIteratorBegin() const {
    return ListIterator<structure::XmlAttributeSyntax>(&AttributesContainer, factory, true);
  }

  ListIterator<structure::XmlAttributeSyntax> XmlEmptyElementSyntax::getAttributesListIteratorEnd() const {
    return ListIterator<structure::XmlAttributeSyntax>(&AttributesContainer, factory, false);
  }

  bool XmlEmptyElementSyntax::getAttributesIsEmpty() const {
    return getAttributesListIteratorBegin() == getAttributesListIteratorEnd();
  }

  unsigned int XmlEmptyElementSyntax::getAttributesSize() const {
    unsigned int size = 0;
    ListIterator<structure::XmlAttributeSyntax> endIt = getAttributesListIteratorEnd();
    for (ListIterator<structure::XmlAttributeSyntax> it = getAttributesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::XmlNameSyntax* XmlEmptyElementSyntax::getName() const {
    structure::XmlNameSyntax *_node = NULL;
    if (m_Name != 0)
      _node = dynamic_cast<structure::XmlNameSyntax*>(factory->getPointer(m_Name));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool XmlEmptyElementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlEmptyElementSyntax_Attributes:
        addAttributes(edgeEnd);
        return true;
      case edkXmlEmptyElementSyntax_Name:
        setName(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::XmlNodeSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool XmlEmptyElementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlEmptyElementSyntax_Attributes:
        removeAttributes(edgeEnd);
        return true;
      case edkXmlEmptyElementSyntax_Name:
        removeName();
        return true;
      default:
        break;
    }
    if (structure::XmlNodeSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void XmlEmptyElementSyntax::addAttributes(const structure::XmlAttributeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsXmlAttributeSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributesContainer.push_back(_node->getId());
    setParentEdge(_node,edkXmlEmptyElementSyntax_Attributes);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkXmlEmptyElementSyntax_Attributes);
  }

  void XmlEmptyElementSyntax::addAttributes(NodeId _id) {
    const structure::XmlAttributeSyntax *node = dynamic_cast<structure::XmlAttributeSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributes( node );
  }

  void XmlEmptyElementSyntax::removeAttributes(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::XmlAttributeSyntax>::Container::iterator it = find(AttributesContainer.begin(), AttributesContainer.end(), id);

    if (it == AttributesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkXmlEmptyElementSyntax_Attributes);
  }

  void XmlEmptyElementSyntax::removeAttributes(structure::XmlAttributeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributes(_node->getId());
  }

  void XmlEmptyElementSyntax::setName(NodeId _id) {
    structure::XmlNameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::XmlNameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkXmlEmptyElementSyntax_Name);
      }
      m_Name = _node->getId();
      if (m_Name != 0)
        setParentEdge(factory->getPointer(m_Name), edkXmlEmptyElementSyntax_Name);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Name, this->getId(), edkXmlEmptyElementSyntax_Name);
    } else {
      if (m_Name) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void XmlEmptyElementSyntax::setName(structure::XmlNameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void XmlEmptyElementSyntax::removeName() {
      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkXmlEmptyElementSyntax_Name);
      }
      m_Name = 0;
  }

  void XmlEmptyElementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void XmlEmptyElementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double XmlEmptyElementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void XmlEmptyElementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType XmlEmptyElementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::XmlEmptyElementSyntax", strlen("structure::XmlEmptyElementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void XmlEmptyElementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    XmlNodeSyntax::save(binIo,false);

    binIo.writeUInt4(m_Name);


    for (ListIterator<structure::XmlAttributeSyntax>::Container::const_iterator it = AttributesContainer.begin(); it != AttributesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void XmlEmptyElementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    XmlNodeSyntax::load(binIo,false);

    m_Name =  binIo.readUInt4();
    if (m_Name != 0)
      setParentEdge(factory->getPointer(m_Name),edkXmlEmptyElementSyntax_Name);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkXmlEmptyElementSyntax_Attributes);
      _id = binIo.readUInt4();
    }
  }


}


}}}
