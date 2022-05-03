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

namespace expression { 
  ImportExpression::ImportExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    m_hasSource(0)
  {
  }

  ImportExpression::~ImportExpression() {
  }

  void ImportExpression::prepareDelete(bool tryOnVirtualParent){
    removeSource();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind ImportExpression::getNodeKind() const {
    return ndkImportExpression;
  }

  expression::Expression* ImportExpression::getSource() const {
    expression::Expression *_node = NULL;
    if (m_hasSource != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasSource));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ImportExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportExpression_HasSource:
        setSource(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ImportExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportExpression_HasSource:
        removeSource();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ImportExpression::setSource(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSource) {
        removeParentEdge(m_hasSource);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkImportExpression_HasSource);
      }
      m_hasSource = _node->getId();
      if (m_hasSource != 0)
        setParentEdge(factory->getPointer(m_hasSource), edkImportExpression_HasSource);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSource, this->getId(), edkImportExpression_HasSource);
    } else {
      if (m_hasSource) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ImportExpression::setSource(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSource(_node->getId());
  }

  void ImportExpression::removeSource() {
      if (m_hasSource) {
        removeParentEdge(m_hasSource);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkImportExpression_HasSource);
      }
      m_hasSource = 0;
  }

  void ImportExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ImportExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ImportExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ImportExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ImportExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ImportExpression", strlen("expression::ImportExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ImportExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasSource);

  }

  void ImportExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    m_hasSource =  binIo.readUInt4();
    if (m_hasSource != 0)
      setParentEdge(factory->getPointer(m_hasSource),edkImportExpression_HasSource);

  }


}


}}}
