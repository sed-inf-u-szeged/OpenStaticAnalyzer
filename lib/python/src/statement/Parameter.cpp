/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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
  Parameter::Parameter(NodeId _id, Factory *_factory) :
    Named(_id, _factory),
    m_kind(pmkNormal),
    m_hasDefaultValue(0),
    m_refersTo(0)
  {
  }

  Parameter::~Parameter() {
  }

  void Parameter::prepareDelete(bool tryOnVirtualParent){
    removeDefaultValue();
    removeRefersTo();
    base::Named::prepareDelete(false);
  }

  NodeKind Parameter::getNodeKind() const {
    return ndkParameter;
  }

  ParameterKind Parameter::getKind() const {
    return m_kind;
  }

  void Parameter::setKind(ParameterKind _kind) {
    m_kind = _kind;
  }

  expression::Expression* Parameter::getDefaultValue() const {
    expression::Expression *_node = NULL;
    if (m_hasDefaultValue != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasDefaultValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  module::Object* Parameter::getRefersTo() const {
    module::Object *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<module::Object*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Parameter::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParameter_HasDefaultValue:
        setDefaultValue(edgeEnd);
        return true;
      case edkParameter_RefersTo:
        setRefersTo(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Parameter::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParameter_HasDefaultValue:
        removeDefaultValue();
        return true;
      case edkParameter_RefersTo:
        removeRefersTo();
        return true;
      default:
        break;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Parameter::setDefaultValue(NodeId _id) {
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

      if (m_hasDefaultValue) {
        removeParentEdge(m_hasDefaultValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDefaultValue, m_id, edkParameter_HasDefaultValue);
      }
      m_hasDefaultValue = _node->getId();
      if (m_hasDefaultValue != 0)
        setParentEdge(factory->getPointer(m_hasDefaultValue), edkParameter_HasDefaultValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasDefaultValue, this->getId(), edkParameter_HasDefaultValue);
    } else {
      if (m_hasDefaultValue) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Parameter::setDefaultValue(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDefaultValue(_node->getId());
  }

  void Parameter::removeDefaultValue() {
      if (m_hasDefaultValue) {
        removeParentEdge(m_hasDefaultValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDefaultValue, m_id, edkParameter_HasDefaultValue);
      }
      m_hasDefaultValue = 0;
  }

  void Parameter::setRefersTo(NodeId _id) {
    module::Object *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<module::Object*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkParameter_RefersTo);
      }
      m_refersTo = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkParameter_RefersTo);
    } else {
      if (m_refersTo) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Parameter::setRefersTo(module::Object *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void Parameter::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkParameter_RefersTo);
      }
      m_refersTo = 0;
  }

  void Parameter::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Parameter::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Parameter::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Parameter& node = dynamic_cast<const Parameter&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getKind() == getKind()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Parameter::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Parameter::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Parameter", strlen("statement::Parameter"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Parameter::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Named::save(binIo,false);

    binIo.writeUByte1(m_kind);

    binIo.writeUInt4(m_hasDefaultValue);
    binIo.writeUInt4(m_refersTo);

  }

  void Parameter::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Named::load(binIo,false);

    m_kind = (ParameterKind)binIo.readUByte1();

    m_hasDefaultValue =  binIo.readUInt4();
    if (m_hasDefaultValue != 0)
      setParentEdge(factory->getPointer(m_hasDefaultValue),edkParameter_HasDefaultValue);

    m_refersTo =  binIo.readUInt4();

  }


}


}}}
