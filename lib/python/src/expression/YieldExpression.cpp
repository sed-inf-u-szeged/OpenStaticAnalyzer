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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  YieldExpression::YieldExpression(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_isFrom(false),
    m_hasExpression(0)
  {
  }

  YieldExpression::~YieldExpression() {
  }

  void YieldExpression::prepareDelete(bool tryOnVirtualParent){
    removeExpression();
    expression::Expression::prepareDelete(false);
  }

  NodeKind YieldExpression::getNodeKind() const {
    return ndkYieldExpression;
  }

  bool YieldExpression::getIsFrom() const {
    return m_isFrom;
  }

  void YieldExpression::setIsFrom(bool _isFrom) {
    m_isFrom = _isFrom;
  }

  expression::Expression* YieldExpression::getExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool YieldExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkYieldExpression_HasExpression:
        setExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool YieldExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkYieldExpression_HasExpression:
        removeExpression();
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void YieldExpression::setExpression(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkYieldExpression_HasExpression);
      }
      m_hasExpression = _node->getId();
      if (m_hasExpression != 0)
        setParentEdge(factory->getPointer(m_hasExpression), edkYieldExpression_HasExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpression, this->getId(), edkYieldExpression_HasExpression);
    } else {
      if (m_hasExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void YieldExpression::setExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void YieldExpression::removeExpression() {
      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkYieldExpression_HasExpression);
      }
      m_hasExpression = 0;
  }

  void YieldExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void YieldExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double YieldExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const YieldExpression& node = dynamic_cast<const YieldExpression&>(base);
      double matchAttrs = 0;
      if(node.getIsFrom() == getIsFrom()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void YieldExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType YieldExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::YieldExpression", strlen("expression::YieldExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void YieldExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isFrom) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasExpression);

  }

  void YieldExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isFrom = boolValues & 1;
    boolValues >>= 1;

    m_hasExpression =  binIo.readUInt4();
    if (m_hasExpression != 0)
      setParentEdge(factory->getPointer(m_hasExpression),edkYieldExpression_HasExpression);

  }


}


}}}
