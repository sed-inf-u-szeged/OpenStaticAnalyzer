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
  CatchClause::CatchClause(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasParam(0),
    m_hasBody(0)
  {
  }

  CatchClause::~CatchClause() {
  }

  void CatchClause::prepareDelete(bool tryOnVirtualParent){
    removeParam();
    removeBody();
    base::Positioned::prepareDelete(false);
  }

  NodeKind CatchClause::getNodeKind() const {
    return ndkCatchClause;
  }

  statement::Pattern* CatchClause::getParam() const {
    statement::Pattern *_node = NULL;
    if (m_hasParam != 0)
      _node = dynamic_cast<statement::Pattern*>(factory->getPointer(m_hasParam));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::BlockStatement* CatchClause::getBody() const {
    statement::BlockStatement *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<statement::BlockStatement*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool CatchClause::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCatchClause_HasParam:
        setParam(edgeEnd);
        return true;
      case edkCatchClause_HasBody:
        setBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CatchClause::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCatchClause_HasParam:
        removeParam();
        return true;
      case edkCatchClause_HasBody:
        removeBody();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CatchClause::setParam(NodeId _id) {
    statement::Pattern *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::Pattern*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasParam) {
        removeParentEdge(m_hasParam);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasParam, m_id, edkCatchClause_HasParam);
      }
      m_hasParam = _node->getId();
      if (m_hasParam != 0)
        setParentEdge(factory->getPointer(m_hasParam), edkCatchClause_HasParam);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasParam, this->getId(), edkCatchClause_HasParam);
    } else {
      if (m_hasParam) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CatchClause::setParam(statement::Pattern *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParam(_node->getId());
  }

  void CatchClause::removeParam() {
      if (m_hasParam) {
        removeParentEdge(m_hasParam);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasParam, m_id, edkCatchClause_HasParam);
      }
      m_hasParam = 0;
  }

  void CatchClause::setBody(NodeId _id) {
    statement::BlockStatement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::BlockStatement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkCatchClause_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkCatchClause_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkCatchClause_HasBody);
    } else {
      if (m_hasBody) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CatchClause::setBody(statement::BlockStatement *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void CatchClause::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkCatchClause_HasBody);
      }
      m_hasBody = 0;
  }

  void CatchClause::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CatchClause::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CatchClause::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void CatchClause::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType CatchClause::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::CatchClause", strlen("statement::CatchClause"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CatchClause::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasParam);
    binIo.writeUInt4(m_hasBody);

  }

  void CatchClause::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasParam =  binIo.readUInt4();
    if (m_hasParam != 0)
      setParentEdge(factory->getPointer(m_hasParam),edkCatchClause_HasParam);

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkCatchClause_HasBody);

  }


}


}}}
