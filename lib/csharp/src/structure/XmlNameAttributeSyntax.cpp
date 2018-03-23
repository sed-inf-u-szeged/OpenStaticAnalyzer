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
  XmlNameAttributeSyntax::XmlNameAttributeSyntax(NodeId _id, Factory *_factory) :
    XmlAttributeSyntax(_id, _factory),
    m_Identifier(0)
  {
  }

  XmlNameAttributeSyntax::~XmlNameAttributeSyntax() {
  }

  void XmlNameAttributeSyntax::prepareDelete(bool tryOnVirtualParent){
    removeIdentifier();
    structure::XmlAttributeSyntax::prepareDelete(false);
  }

  NodeKind XmlNameAttributeSyntax::getNodeKind() const {
    return ndkXmlNameAttributeSyntax;
  }

  expression::IdentifierNameSyntax* XmlNameAttributeSyntax::getIdentifier() const {
    expression::IdentifierNameSyntax *_node = NULL;
    if (m_Identifier != 0)
      _node = dynamic_cast<expression::IdentifierNameSyntax*>(factory->getPointer(m_Identifier));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool XmlNameAttributeSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlNameAttributeSyntax_Identifier:
        setIdentifier(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::XmlAttributeSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool XmlNameAttributeSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlNameAttributeSyntax_Identifier:
        removeIdentifier();
        return true;
      default:
        break;
    }
    if (structure::XmlAttributeSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void XmlNameAttributeSyntax::setIdentifier(NodeId _id) {
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

      if (m_Identifier) {
        removeParentEdge(m_Identifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Identifier, m_id, edkXmlNameAttributeSyntax_Identifier);
      }
      m_Identifier = _node->getId();
      if (m_Identifier != 0)
        setParentEdge(factory->getPointer(m_Identifier), edkXmlNameAttributeSyntax_Identifier);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Identifier, this->getId(), edkXmlNameAttributeSyntax_Identifier);
    } else {
      if (m_Identifier) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void XmlNameAttributeSyntax::setIdentifier(expression::IdentifierNameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setIdentifier(_node->getId());
  }

  void XmlNameAttributeSyntax::removeIdentifier() {
      if (m_Identifier) {
        removeParentEdge(m_Identifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Identifier, m_id, edkXmlNameAttributeSyntax_Identifier);
      }
      m_Identifier = 0;
  }

  void XmlNameAttributeSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void XmlNameAttributeSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double XmlNameAttributeSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void XmlNameAttributeSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType XmlNameAttributeSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::XmlNameAttributeSyntax", strlen("structure::XmlNameAttributeSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void XmlNameAttributeSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    XmlAttributeSyntax::save(binIo,false);

    binIo.writeUInt4(m_Identifier);

  }

  void XmlNameAttributeSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    XmlAttributeSyntax::load(binIo,false);

    m_Identifier =  binIo.readUInt4();
    if (m_Identifier != 0)
      setParentEdge(factory->getPointer(m_Identifier),edkXmlNameAttributeSyntax_Identifier);

  }


}


}}}
