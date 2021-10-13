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
  FormattedValue::FormattedValue(NodeId _id, Factory *_factory) :
    Literal(_id, _factory),
    m_conversion(0),
    m_hasValue(0),
    m_hasFormatSpec(0)
  {
  }

  FormattedValue::~FormattedValue() {
  }

  void FormattedValue::prepareDelete(bool tryOnVirtualParent){
    removeValue();
    removeFormatSpec();
    expression::Literal::prepareDelete(false);
  }

  NodeKind FormattedValue::getNodeKind() const {
    return ndkFormattedValue;
  }

  int FormattedValue::getConversion() const {
    return m_conversion;
  }

  void FormattedValue::setConversion(int _conversion) {
    m_conversion = _conversion;
  }

  expression::Expression* FormattedValue::getValue() const {
    expression::Expression *_node = NULL;
    if (m_hasValue != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* FormattedValue::getFormatSpec() const {
    expression::Expression *_node = NULL;
    if (m_hasFormatSpec != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasFormatSpec));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool FormattedValue::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFormattedValue_HasValue:
        setValue(edgeEnd);
        return true;
      case edkFormattedValue_HasFormatSpec:
        setFormatSpec(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Literal::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool FormattedValue::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFormattedValue_HasValue:
        removeValue();
        return true;
      case edkFormattedValue_HasFormatSpec:
        removeFormatSpec();
        return true;
      default:
        break;
    }
    if (expression::Literal::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void FormattedValue::setValue(NodeId _id) {
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

      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkFormattedValue_HasValue);
      }
      m_hasValue = _node->getId();
      if (m_hasValue != 0)
        setParentEdge(factory->getPointer(m_hasValue), edkFormattedValue_HasValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasValue, this->getId(), edkFormattedValue_HasValue);
    } else {
      if (m_hasValue) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void FormattedValue::setValue(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValue(_node->getId());
  }

  void FormattedValue::removeValue() {
      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkFormattedValue_HasValue);
      }
      m_hasValue = 0;
  }

  void FormattedValue::setFormatSpec(NodeId _id) {
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

      if (m_hasFormatSpec) {
        removeParentEdge(m_hasFormatSpec);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFormatSpec, m_id, edkFormattedValue_HasFormatSpec);
      }
      m_hasFormatSpec = _node->getId();
      if (m_hasFormatSpec != 0)
        setParentEdge(factory->getPointer(m_hasFormatSpec), edkFormattedValue_HasFormatSpec);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFormatSpec, this->getId(), edkFormattedValue_HasFormatSpec);
    } else {
      if (m_hasFormatSpec) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void FormattedValue::setFormatSpec(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFormatSpec(_node->getId());
  }

  void FormattedValue::removeFormatSpec() {
      if (m_hasFormatSpec) {
        removeParentEdge(m_hasFormatSpec);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFormatSpec, m_id, edkFormattedValue_HasFormatSpec);
      }
      m_hasFormatSpec = 0;
  }

  void FormattedValue::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void FormattedValue::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double FormattedValue::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const FormattedValue& node = dynamic_cast<const FormattedValue&>(base);
      double matchAttrs = 0;
      if(node.getConversion() == getConversion()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void FormattedValue::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType FormattedValue::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::FormattedValue", strlen("expression::FormattedValue"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void FormattedValue::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Literal::save(binIo,false);

    binIo.writeUInt4(m_conversion);

    binIo.writeUInt4(m_hasValue);
    binIo.writeUInt4(m_hasFormatSpec);

  }

  void FormattedValue::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Literal::load(binIo,false);

    m_conversion = binIo.readUInt4();

    m_hasValue =  binIo.readUInt4();
    if (m_hasValue != 0)
      setParentEdge(factory->getPointer(m_hasValue),edkFormattedValue_HasValue);

    m_hasFormatSpec =  binIo.readUInt4();
    if (m_hasFormatSpec != 0)
      setParentEdge(factory->getPointer(m_hasFormatSpec),edkFormattedValue_HasFormatSpec);

  }


}


}}}
