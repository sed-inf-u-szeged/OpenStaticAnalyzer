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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace type { 
  ModuleType::ModuleType(NodeId _id, Factory *_factory) :
    Type(_id, _factory),
    m_refersTo(0)
  {
  }

  ModuleType::~ModuleType() {
  }

  void ModuleType::clone(const ModuleType& other, bool tryOnVirtualParent) {
    type::Type::clone(other, false);

    m_refersTo = other.m_refersTo;
  }

  void ModuleType::prepareDelete(bool tryOnVirtualParent){
    removeRefersTo();
    type::Type::prepareDelete(false);
  }

  NodeKind ModuleType::getNodeKind() const {
    return ndkModuleType;
  }

  struc::Module* ModuleType::getRefersTo() const {
    struc::Module *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<struc::Module*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ModuleType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModuleType_RefersTo:
        setRefersTo(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::Type::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ModuleType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModuleType_RefersTo:
        removeRefersTo();
        return true;
      default:
        break;
    }
    if (type::Type::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ModuleType::setRefersTo(NodeId _id) {
    struc::Module *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::Module*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkModuleType_RefersTo);
      }
      m_refersTo = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkModuleType_RefersTo);
    } else {
      if (m_refersTo) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ModuleType::setRefersTo(struc::Module *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void ModuleType::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkModuleType_RefersTo);
      }
      m_refersTo = 0;
  }

  void ModuleType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ModuleType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ModuleType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ModuleType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ModuleType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::ModuleType", strlen("type::ModuleType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ModuleType::sort(bool withVirtualBase /* = true */) {
    Type::sort(false);
  }

  void ModuleType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Type::save(binIo,false);

    binIo.writeUInt4(m_refersTo);

  }

  void ModuleType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Type::load(binIo,false);

    m_refersTo =  binIo.readUInt4();

  }


}


}}}
