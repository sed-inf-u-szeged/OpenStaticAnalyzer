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

namespace declaration { 
  ExportAllDeclaration::ExportAllDeclaration(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Declaration(_id, _factory),
    m_hasSource(0),
    m_hasExported(0)
  {
  }

  ExportAllDeclaration::~ExportAllDeclaration() {
  }

  void ExportAllDeclaration::prepareDelete(bool tryOnVirtualParent){
    removeSource();
    removeExported();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    declaration::Declaration::prepareDelete(false);
  }

  NodeKind ExportAllDeclaration::getNodeKind() const {
    return ndkExportAllDeclaration;
  }

  expression::Literal* ExportAllDeclaration::getSource() const {
    expression::Literal *_node = NULL;
    if (m_hasSource != 0)
      _node = dynamic_cast<expression::Literal*>(factory->getPointer(m_hasSource));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Identifier* ExportAllDeclaration::getExported() const {
    expression::Identifier *_node = NULL;
    if (m_hasExported != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasExported));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ExportAllDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExportAllDeclaration_HasSource:
        setSource(edgeEnd);
        return true;
      case edkExportAllDeclaration_HasExported:
        setExported(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (declaration::Declaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ExportAllDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExportAllDeclaration_HasSource:
        removeSource();
        return true;
      case edkExportAllDeclaration_HasExported:
        removeExported();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (declaration::Declaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ExportAllDeclaration::setSource(NodeId _id) {
    expression::Literal *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Literal*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSource) {
        removeParentEdge(m_hasSource);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkExportAllDeclaration_HasSource);
      }
      m_hasSource = _node->getId();
      if (m_hasSource != 0)
        setParentEdge(factory->getPointer(m_hasSource), edkExportAllDeclaration_HasSource);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSource, this->getId(), edkExportAllDeclaration_HasSource);
    } else {
      if (m_hasSource) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ExportAllDeclaration::setSource(expression::Literal *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSource(_node->getId());
  }

  void ExportAllDeclaration::removeSource() {
      if (m_hasSource) {
        removeParentEdge(m_hasSource);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkExportAllDeclaration_HasSource);
      }
      m_hasSource = 0;
  }

  void ExportAllDeclaration::setExported(NodeId _id) {
    expression::Identifier *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Identifier*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasExported) {
        removeParentEdge(m_hasExported);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExported, m_id, edkExportAllDeclaration_HasExported);
      }
      m_hasExported = _node->getId();
      if (m_hasExported != 0)
        setParentEdge(factory->getPointer(m_hasExported), edkExportAllDeclaration_HasExported);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExported, this->getId(), edkExportAllDeclaration_HasExported);
    } else {
      if (m_hasExported) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ExportAllDeclaration::setExported(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExported(_node->getId());
  }

  void ExportAllDeclaration::removeExported() {
      if (m_hasExported) {
        removeParentEdge(m_hasExported);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExported, m_id, edkExportAllDeclaration_HasExported);
      }
      m_hasExported = 0;
  }

  void ExportAllDeclaration::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ExportAllDeclaration::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ExportAllDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ExportAllDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ExportAllDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "declaration::ExportAllDeclaration", strlen("declaration::ExportAllDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ExportAllDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Declaration::save(binIo,false);

    binIo.writeUInt4(m_hasSource);
    binIo.writeUInt4(m_hasExported);

  }

  void ExportAllDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Declaration::load(binIo,false);

    m_hasSource =  binIo.readUInt4();
    if (m_hasSource != 0)
      setParentEdge(factory->getPointer(m_hasSource),edkExportAllDeclaration_HasSource);

    m_hasExported =  binIo.readUInt4();
    if (m_hasExported != 0)
      setParentEdge(factory->getPointer(m_hasExported),edkExportAllDeclaration_HasExported);

  }


}


}}}
