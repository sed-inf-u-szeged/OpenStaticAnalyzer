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
  ExportSpecifier::ExportSpecifier(NodeId _id, Factory *_factory) :
    ModuleSpecifier(_id, _factory),
    m_hasExported(0)
  {
  }

  ExportSpecifier::~ExportSpecifier() {
  }

  void ExportSpecifier::prepareDelete(bool tryOnVirtualParent){
    removeExported();
    structure::ModuleSpecifier::prepareDelete(false);
  }

  NodeKind ExportSpecifier::getNodeKind() const {
    return ndkExportSpecifier;
  }

  expression::Identifier* ExportSpecifier::getExported() const {
    expression::Identifier *_node = NULL;
    if (m_hasExported != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasExported));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ExportSpecifier::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExportSpecifier_HasExported:
        setExported(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::ModuleSpecifier::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ExportSpecifier::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExportSpecifier_HasExported:
        removeExported();
        return true;
      default:
        break;
    }
    if (structure::ModuleSpecifier::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ExportSpecifier::setExported(NodeId _id) {
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

      if (m_hasExported) {
        removeParentEdge(m_hasExported);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExported, m_id, edkExportSpecifier_HasExported);
      }
      m_hasExported = _node->getId();
      if (m_hasExported != 0)
        setParentEdge(factory->getPointer(m_hasExported), edkExportSpecifier_HasExported);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExported, this->getId(), edkExportSpecifier_HasExported);
    } else {
      if (m_hasExported) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ExportSpecifier::setExported(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExported(_node->getId());
  }

  void ExportSpecifier::removeExported() {
      if (m_hasExported) {
        removeParentEdge(m_hasExported);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExported, m_id, edkExportSpecifier_HasExported);
      }
      m_hasExported = 0;
  }

  void ExportSpecifier::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ExportSpecifier::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ExportSpecifier::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ExportSpecifier::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ExportSpecifier::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ExportSpecifier", strlen("structure::ExportSpecifier"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ExportSpecifier::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ModuleSpecifier::save(binIo,false);

    binIo.writeUInt4(m_hasExported);

  }

  void ExportSpecifier::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ModuleSpecifier::load(binIo,false);

    m_hasExported =  binIo.readUInt4();
    if (m_hasExported != 0)
      setParentEdge(factory->getPointer(m_hasExported),edkExportSpecifier_HasExported);

  }


}


}}}
