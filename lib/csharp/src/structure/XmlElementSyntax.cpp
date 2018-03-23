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
  XmlElementSyntax::XmlElementSyntax(NodeId _id, Factory *_factory) :
    XmlNodeSyntax(_id, _factory),
    ContentContainer(),
    m_EndTag(0),
    m_StartTag(0)
  {
  }

  XmlElementSyntax::~XmlElementSyntax() {
  }

  void XmlElementSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ContentContainer.empty()) {
      const NodeId id = *ContentContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkXmlElementSyntax_Content);
      ContentContainer.pop_front();
    }
    removeEndTag();
    removeStartTag();
    structure::XmlNodeSyntax::prepareDelete(false);
  }

  NodeKind XmlElementSyntax::getNodeKind() const {
    return ndkXmlElementSyntax;
  }

  ListIterator<structure::XmlNodeSyntax> XmlElementSyntax::getContentListIteratorBegin() const {
    return ListIterator<structure::XmlNodeSyntax>(&ContentContainer, factory, true);
  }

  ListIterator<structure::XmlNodeSyntax> XmlElementSyntax::getContentListIteratorEnd() const {
    return ListIterator<structure::XmlNodeSyntax>(&ContentContainer, factory, false);
  }

  bool XmlElementSyntax::getContentIsEmpty() const {
    return getContentListIteratorBegin() == getContentListIteratorEnd();
  }

  unsigned int XmlElementSyntax::getContentSize() const {
    unsigned int size = 0;
    ListIterator<structure::XmlNodeSyntax> endIt = getContentListIteratorEnd();
    for (ListIterator<structure::XmlNodeSyntax> it = getContentListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::XmlElementEndTagSyntax* XmlElementSyntax::getEndTag() const {
    structure::XmlElementEndTagSyntax *_node = NULL;
    if (m_EndTag != 0)
      _node = dynamic_cast<structure::XmlElementEndTagSyntax*>(factory->getPointer(m_EndTag));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::XmlElementStartTagSyntax* XmlElementSyntax::getStartTag() const {
    structure::XmlElementStartTagSyntax *_node = NULL;
    if (m_StartTag != 0)
      _node = dynamic_cast<structure::XmlElementStartTagSyntax*>(factory->getPointer(m_StartTag));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool XmlElementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlElementSyntax_Content:
        addContent(edgeEnd);
        return true;
      case edkXmlElementSyntax_EndTag:
        setEndTag(edgeEnd);
        return true;
      case edkXmlElementSyntax_StartTag:
        setStartTag(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::XmlNodeSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool XmlElementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlElementSyntax_Content:
        removeContent(edgeEnd);
        return true;
      case edkXmlElementSyntax_EndTag:
        removeEndTag();
        return true;
      case edkXmlElementSyntax_StartTag:
        removeStartTag();
        return true;
      default:
        break;
    }
    if (structure::XmlNodeSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void XmlElementSyntax::addContent(const structure::XmlNodeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsXmlNodeSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ContentContainer.push_back(_node->getId());
    setParentEdge(_node,edkXmlElementSyntax_Content);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkXmlElementSyntax_Content);
  }

  void XmlElementSyntax::addContent(NodeId _id) {
    const structure::XmlNodeSyntax *node = dynamic_cast<structure::XmlNodeSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addContent( node );
  }

  void XmlElementSyntax::removeContent(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::XmlNodeSyntax>::Container::iterator it = find(ContentContainer.begin(), ContentContainer.end(), id);

    if (it == ContentContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ContentContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkXmlElementSyntax_Content);
  }

  void XmlElementSyntax::removeContent(structure::XmlNodeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeContent(_node->getId());
  }

  void XmlElementSyntax::setEndTag(NodeId _id) {
    structure::XmlElementEndTagSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::XmlElementEndTagSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_EndTag) {
        removeParentEdge(m_EndTag);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_EndTag, m_id, edkXmlElementSyntax_EndTag);
      }
      m_EndTag = _node->getId();
      if (m_EndTag != 0)
        setParentEdge(factory->getPointer(m_EndTag), edkXmlElementSyntax_EndTag);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_EndTag, this->getId(), edkXmlElementSyntax_EndTag);
    } else {
      if (m_EndTag) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void XmlElementSyntax::setEndTag(structure::XmlElementEndTagSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setEndTag(_node->getId());
  }

  void XmlElementSyntax::removeEndTag() {
      if (m_EndTag) {
        removeParentEdge(m_EndTag);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_EndTag, m_id, edkXmlElementSyntax_EndTag);
      }
      m_EndTag = 0;
  }

  void XmlElementSyntax::setStartTag(NodeId _id) {
    structure::XmlElementStartTagSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::XmlElementStartTagSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_StartTag) {
        removeParentEdge(m_StartTag);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_StartTag, m_id, edkXmlElementSyntax_StartTag);
      }
      m_StartTag = _node->getId();
      if (m_StartTag != 0)
        setParentEdge(factory->getPointer(m_StartTag), edkXmlElementSyntax_StartTag);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_StartTag, this->getId(), edkXmlElementSyntax_StartTag);
    } else {
      if (m_StartTag) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void XmlElementSyntax::setStartTag(structure::XmlElementStartTagSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setStartTag(_node->getId());
  }

  void XmlElementSyntax::removeStartTag() {
      if (m_StartTag) {
        removeParentEdge(m_StartTag);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_StartTag, m_id, edkXmlElementSyntax_StartTag);
      }
      m_StartTag = 0;
  }

  void XmlElementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void XmlElementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double XmlElementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void XmlElementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType XmlElementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::XmlElementSyntax", strlen("structure::XmlElementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void XmlElementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    XmlNodeSyntax::save(binIo,false);

    binIo.writeUInt4(m_EndTag);
    binIo.writeUInt4(m_StartTag);


    for (ListIterator<structure::XmlNodeSyntax>::Container::const_iterator it = ContentContainer.begin(); it != ContentContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void XmlElementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    XmlNodeSyntax::load(binIo,false);

    m_EndTag =  binIo.readUInt4();
    if (m_EndTag != 0)
      setParentEdge(factory->getPointer(m_EndTag),edkXmlElementSyntax_EndTag);

    m_StartTag =  binIo.readUInt4();
    if (m_StartTag != 0)
      setParentEdge(factory->getPointer(m_StartTag),edkXmlElementSyntax_StartTag);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ContentContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkXmlElementSyntax_Content);
      _id = binIo.readUInt4();
    }
  }


}


}}}
