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
  XmlCrefAttributeSyntax::XmlCrefAttributeSyntax(NodeId _id, Factory *_factory) :
    XmlAttributeSyntax(_id, _factory),
    m_Cref(0)
  {
  }

  XmlCrefAttributeSyntax::~XmlCrefAttributeSyntax() {
  }

  void XmlCrefAttributeSyntax::prepareDelete(bool tryOnVirtualParent){
    removeCref();
    structure::XmlAttributeSyntax::prepareDelete(false);
  }

  NodeKind XmlCrefAttributeSyntax::getNodeKind() const {
    return ndkXmlCrefAttributeSyntax;
  }

  structure::CrefSyntax* XmlCrefAttributeSyntax::getCref() const {
    structure::CrefSyntax *_node = NULL;
    if (m_Cref != 0)
      _node = dynamic_cast<structure::CrefSyntax*>(factory->getPointer(m_Cref));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool XmlCrefAttributeSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlCrefAttributeSyntax_Cref:
        setCref(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::XmlAttributeSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool XmlCrefAttributeSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkXmlCrefAttributeSyntax_Cref:
        removeCref();
        return true;
      default:
        break;
    }
    if (structure::XmlAttributeSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void XmlCrefAttributeSyntax::setCref(NodeId _id) {
    structure::CrefSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::CrefSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Cref) {
        removeParentEdge(m_Cref);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Cref, m_id, edkXmlCrefAttributeSyntax_Cref);
      }
      m_Cref = _node->getId();
      if (m_Cref != 0)
        setParentEdge(factory->getPointer(m_Cref), edkXmlCrefAttributeSyntax_Cref);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Cref, this->getId(), edkXmlCrefAttributeSyntax_Cref);
    } else {
      if (m_Cref) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void XmlCrefAttributeSyntax::setCref(structure::CrefSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCref(_node->getId());
  }

  void XmlCrefAttributeSyntax::removeCref() {
      if (m_Cref) {
        removeParentEdge(m_Cref);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Cref, m_id, edkXmlCrefAttributeSyntax_Cref);
      }
      m_Cref = 0;
  }

  void XmlCrefAttributeSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void XmlCrefAttributeSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double XmlCrefAttributeSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void XmlCrefAttributeSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType XmlCrefAttributeSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::XmlCrefAttributeSyntax", strlen("structure::XmlCrefAttributeSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void XmlCrefAttributeSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    XmlAttributeSyntax::save(binIo,false);

    binIo.writeUInt4(m_Cref);

  }

  void XmlCrefAttributeSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    XmlAttributeSyntax::load(binIo,false);

    m_Cref =  binIo.readUInt4();
    if (m_Cref != 0)
      setParentEdge(factory->getPointer(m_Cref),edkXmlCrefAttributeSyntax_Cref);

  }


}


}}}
