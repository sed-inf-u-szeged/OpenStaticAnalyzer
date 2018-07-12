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
  ImportSpecifier::ImportSpecifier(NodeId _id, Factory *_factory) :
    ImpSpecifier(_id, _factory),
    m_hasImported(0)
  {
  }

  ImportSpecifier::~ImportSpecifier() {
  }

  void ImportSpecifier::prepareDelete(bool tryOnVirtualParent){
    removeImported();
    structure::ImpSpecifier::prepareDelete(false);
  }

  NodeKind ImportSpecifier::getNodeKind() const {
    return ndkImportSpecifier;
  }

  expression::Identifier* ImportSpecifier::getImported() const {
    expression::Identifier *_node = NULL;
    if (m_hasImported != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasImported));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ImportSpecifier::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportSpecifier_HasImported:
        setImported(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::ImpSpecifier::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ImportSpecifier::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportSpecifier_HasImported:
        removeImported();
        return true;
      default:
        break;
    }
    if (structure::ImpSpecifier::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ImportSpecifier::setImported(NodeId _id) {
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

      if (m_hasImported) {
        removeParentEdge(m_hasImported);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasImported, m_id, edkImportSpecifier_HasImported);
      }
      m_hasImported = _node->getId();
      if (m_hasImported != 0)
        setParentEdge(factory->getPointer(m_hasImported), edkImportSpecifier_HasImported);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasImported, this->getId(), edkImportSpecifier_HasImported);
    } else {
      if (m_hasImported) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ImportSpecifier::setImported(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setImported(_node->getId());
  }

  void ImportSpecifier::removeImported() {
      if (m_hasImported) {
        removeParentEdge(m_hasImported);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasImported, m_id, edkImportSpecifier_HasImported);
      }
      m_hasImported = 0;
  }

  void ImportSpecifier::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ImportSpecifier::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ImportSpecifier::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ImportSpecifier::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ImportSpecifier::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ImportSpecifier", strlen("structure::ImportSpecifier"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ImportSpecifier::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ImpSpecifier::save(binIo,false);

    binIo.writeUInt4(m_hasImported);

  }

  void ImportSpecifier::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ImpSpecifier::load(binIo,false);

    m_hasImported =  binIo.readUInt4();
    if (m_hasImported != 0)
      setParentEdge(factory->getPointer(m_hasImported),edkImportSpecifier_HasImported);

  }


}


}}}
