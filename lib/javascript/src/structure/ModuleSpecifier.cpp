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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace structure { 
  ModuleSpecifier::ModuleSpecifier(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasLocal(0)
  {
  }

  ModuleSpecifier::~ModuleSpecifier() {
  }

  void ModuleSpecifier::prepareDelete(bool tryOnVirtualParent){
    removeLocal();
    base::Positioned::prepareDelete(false);
  }

  expression::Identifier* ModuleSpecifier::getLocal() const {
    expression::Identifier *_node = NULL;
    if (m_hasLocal != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasLocal));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ModuleSpecifier::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModuleSpecifier_HasLocal:
        setLocal(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ModuleSpecifier::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModuleSpecifier_HasLocal:
        removeLocal();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ModuleSpecifier::setLocal(NodeId _id) {
    expression::Identifier *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Identifier*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasLocal) {
        removeParentEdge(m_hasLocal);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLocal, m_id, edkModuleSpecifier_HasLocal);
      }
      m_hasLocal = _node->getId();
      if (m_hasLocal != 0)
        setParentEdge(factory->getPointer(m_hasLocal), edkModuleSpecifier_HasLocal);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLocal, this->getId(), edkModuleSpecifier_HasLocal);
    } else {
      if (m_hasLocal) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ModuleSpecifier::setLocal(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLocal(_node->getId());
  }

  void ModuleSpecifier::removeLocal() {
      if (m_hasLocal) {
        removeParentEdge(m_hasLocal);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLocal, m_id, edkModuleSpecifier_HasLocal);
      }
      m_hasLocal = 0;
  }

  double ModuleSpecifier::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ModuleSpecifier::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ModuleSpecifier::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ModuleSpecifier", strlen("structure::ModuleSpecifier"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ModuleSpecifier::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasLocal);

  }

  void ModuleSpecifier::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasLocal =  binIo.readUInt4();
    if (m_hasLocal != 0)
      setParentEdge(factory->getPointer(m_hasLocal),edkModuleSpecifier_HasLocal);

  }


}


}}}
