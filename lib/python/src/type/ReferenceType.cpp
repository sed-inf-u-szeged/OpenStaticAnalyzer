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

namespace type { 
  ReferenceType::ReferenceType(NodeId _id, Factory *_factory) :
    Type(_id, _factory),
    m_name(0),
    m_refersTo(0)
  {
  }

  ReferenceType::~ReferenceType() {
  }

  void ReferenceType::prepareDelete(bool tryOnVirtualParent){
    removeRefersTo();
    type::Type::prepareDelete(false);
  }

  NodeKind ReferenceType::getNodeKind() const {
    return ndkReferenceType;
  }

  Key ReferenceType::getNameKey() const {
    return m_name;
  }

  const std::string& ReferenceType::getName() const {
    return factory->getStringTable().get(m_name);
  }

  void ReferenceType::setNameKey(Key _name) {
    m_name = _name;
  }

  void ReferenceType::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  base::Positioned* ReferenceType::getRefersTo() const {
    base::Positioned *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ReferenceType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkReferenceType_RefersTo:
        setRefersTo(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::Type::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ReferenceType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkReferenceType_RefersTo:
        removeRefersTo();
        return true;
      default:
        break;
    }
    if (type::Type::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ReferenceType::setRefersTo(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (_node->getNodeKind() == ndkClassDef || _node->getNodeKind() == ndkModule || _node->getNodeKind() == ndkFunctionDef) {
        if (m_refersTo) {
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_refersTo, m_id, edkReferenceType_RefersTo);
        }
        m_refersTo = _node->getId();
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkReferenceType_RefersTo);
      } else {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_refersTo) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ReferenceType::setRefersTo(base::Positioned *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void ReferenceType::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkReferenceType_RefersTo);
      }
      m_refersTo = 0;
  }

  void ReferenceType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ReferenceType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ReferenceType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ReferenceType& node = dynamic_cast<const ReferenceType&>(base);
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
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ReferenceType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType ReferenceType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::ReferenceType", strlen("type::ReferenceType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ReferenceType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Type::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);

    binIo.writeUInt4(m_refersTo);

  }

  void ReferenceType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Type::load(binIo,false);

    m_name = binIo.readUInt4();

    m_refersTo =  binIo.readUInt4();

  }


}


}}}
