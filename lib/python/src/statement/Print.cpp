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

namespace statement { 
  Print::Print(NodeId _id, Factory *_factory) :
    SimpleStatement(_id, _factory),
    m_nl(false),
    m_hasExpressionList(0),
    m_hasDestination(0)
  {
  }

  Print::~Print() {
  }

  void Print::prepareDelete(bool tryOnVirtualParent){
    removeExpressionList();
    removeDestination();
    statement::SimpleStatement::prepareDelete(false);
  }

  NodeKind Print::getNodeKind() const {
    return ndkPrint;
  }

  bool Print::getNl() const {
    return m_nl;
  }

  void Print::setNl(bool _nl) {
    m_nl = _nl;
  }

  expression::ExpressionList* Print::getExpressionList() const {
    expression::ExpressionList *_node = NULL;
    if (m_hasExpressionList != 0)
      _node = dynamic_cast<expression::ExpressionList*>(factory->getPointer(m_hasExpressionList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Print::getDestination() const {
    expression::Expression *_node = NULL;
    if (m_hasDestination != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasDestination));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Print::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPrint_HasExpressionList:
        setExpressionList(edgeEnd);
        return true;
      case edkPrint_HasDestination:
        setDestination(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Print::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPrint_HasExpressionList:
        removeExpressionList();
        return true;
      case edkPrint_HasDestination:
        removeDestination();
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Print::setExpressionList(NodeId _id) {
    expression::ExpressionList *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ExpressionList*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasExpressionList) {
        removeParentEdge(m_hasExpressionList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpressionList, m_id, edkPrint_HasExpressionList);
      }
      m_hasExpressionList = _node->getId();
      if (m_hasExpressionList != 0)
        setParentEdge(factory->getPointer(m_hasExpressionList), edkPrint_HasExpressionList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpressionList, this->getId(), edkPrint_HasExpressionList);
    } else {
      if (m_hasExpressionList) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Print::setExpressionList(expression::ExpressionList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionList(_node->getId());
  }

  void Print::removeExpressionList() {
      if (m_hasExpressionList) {
        removeParentEdge(m_hasExpressionList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpressionList, m_id, edkPrint_HasExpressionList);
      }
      m_hasExpressionList = 0;
  }

  void Print::setDestination(NodeId _id) {
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

      if (m_hasDestination) {
        removeParentEdge(m_hasDestination);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDestination, m_id, edkPrint_HasDestination);
      }
      m_hasDestination = _node->getId();
      if (m_hasDestination != 0)
        setParentEdge(factory->getPointer(m_hasDestination), edkPrint_HasDestination);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasDestination, this->getId(), edkPrint_HasDestination);
    } else {
      if (m_hasDestination) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Print::setDestination(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDestination(_node->getId());
  }

  void Print::removeDestination() {
      if (m_hasDestination) {
        removeParentEdge(m_hasDestination);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDestination, m_id, edkPrint_HasDestination);
      }
      m_hasDestination = 0;
  }

  void Print::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Print::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Print::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Print& node = dynamic_cast<const Print&>(base);
      double matchAttrs = 0;
      if(node.getNl() == getNl()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Print::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Print::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Print", strlen("statement::Print"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Print::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleStatement::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_nl) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasExpressionList);
    binIo.writeUInt4(m_hasDestination);

  }

  void Print::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleStatement::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_nl = boolValues & 1;
    boolValues >>= 1;

    m_hasExpressionList =  binIo.readUInt4();
    if (m_hasExpressionList != 0)
      setParentEdge(factory->getPointer(m_hasExpressionList),edkPrint_HasExpressionList);

    m_hasDestination =  binIo.readUInt4();
    if (m_hasDestination != 0)
      setParentEdge(factory->getPointer(m_hasDestination),edkPrint_HasDestination);

  }


}


}}}
