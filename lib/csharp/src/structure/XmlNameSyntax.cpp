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
  XmlNameSyntax::XmlNameSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_Prefix(0)
  {
  }

  XmlNameSyntax::~XmlNameSyntax() {
  }

  void XmlNameSyntax::prepareDelete(bool tryOnVirtualParent){
    removePrefix();
    base::Positioned::prepareDelete(false);
  }

  NodeKind XmlNameSyntax::getNodeKind() const {
    return ndkXmlNameSyntax;
  }

  structure::XmlPrefixSyntax* XmlNameSyntax::getPrefix() const {
    structure::XmlPrefixSyntax *_node = NULL;
    if (m_Prefix != 0)
      _node = dynamic_cast<structure::XmlPrefixSyntax*>(factory->getPointer(m_Prefix));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool XmlNameSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlNameSyntax_Prefix:
        setPrefix(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool XmlNameSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlNameSyntax_Prefix:
        removePrefix();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void XmlNameSyntax::setPrefix(NodeId _id) {
    structure::XmlPrefixSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::XmlPrefixSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Prefix) {
        removeParentEdge(m_Prefix);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Prefix, m_id, edkXmlNameSyntax_Prefix);
      }
      m_Prefix = _node->getId();
      if (m_Prefix != 0)
        setParentEdge(factory->getPointer(m_Prefix), edkXmlNameSyntax_Prefix);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Prefix, this->getId(), edkXmlNameSyntax_Prefix);
    } else {
      if (m_Prefix) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void XmlNameSyntax::setPrefix(structure::XmlPrefixSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPrefix(_node->getId());
  }

  void XmlNameSyntax::removePrefix() {
      if (m_Prefix) {
        removeParentEdge(m_Prefix);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Prefix, m_id, edkXmlNameSyntax_Prefix);
      }
      m_Prefix = 0;
  }

  void XmlNameSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void XmlNameSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double XmlNameSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void XmlNameSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType XmlNameSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::XmlNameSyntax", strlen("structure::XmlNameSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void XmlNameSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Prefix);

  }

  void XmlNameSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Prefix =  binIo.readUInt4();
    if (m_Prefix != 0)
      setParentEdge(factory->getPointer(m_Prefix),edkXmlNameSyntax_Prefix);

  }


}


}}}
