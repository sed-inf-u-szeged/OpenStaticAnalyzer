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

namespace statement { 
  BreakStatement::BreakStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasLabel(0)
  {
  }

  BreakStatement::~BreakStatement() {
  }

  void BreakStatement::prepareDelete(bool tryOnVirtualParent){
    removeLabel();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind BreakStatement::getNodeKind() const {
    return ndkBreakStatement;
  }

  expression::Identifier* BreakStatement::getLabel() const {
    expression::Identifier *_node = NULL;
    if (m_hasLabel != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasLabel));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool BreakStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBreakStatement_HasLabel:
        setLabel(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BreakStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBreakStatement_HasLabel:
        removeLabel();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BreakStatement::setLabel(NodeId _id) {
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

      if (m_hasLabel) {
        removeParentEdge(m_hasLabel);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLabel, m_id, edkBreakStatement_HasLabel);
      }
      m_hasLabel = _node->getId();
      if (m_hasLabel != 0)
        setParentEdge(factory->getPointer(m_hasLabel), edkBreakStatement_HasLabel);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLabel, this->getId(), edkBreakStatement_HasLabel);
    } else {
      if (m_hasLabel) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BreakStatement::setLabel(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLabel(_node->getId());
  }

  void BreakStatement::removeLabel() {
      if (m_hasLabel) {
        removeParentEdge(m_hasLabel);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLabel, m_id, edkBreakStatement_HasLabel);
      }
      m_hasLabel = 0;
  }

  void BreakStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BreakStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BreakStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BreakStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType BreakStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::BreakStatement", strlen("statement::BreakStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BreakStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasLabel);

  }

  void BreakStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasLabel =  binIo.readUInt4();
    if (m_hasLabel != 0)
      setParentEdge(factory->getPointer(m_hasLabel),edkBreakStatement_HasLabel);

  }


}


}}}
