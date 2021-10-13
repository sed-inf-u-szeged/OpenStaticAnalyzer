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
  Identifier::Identifier(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    Pattern(_id, _factory),
    Named(_id, _factory),
    m_refersTo(0)
  {
  }

  Identifier::~Identifier() {
  }

  void Identifier::prepareDelete(bool tryOnVirtualParent){
    removeRefersTo();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
    statement::Pattern::prepareDelete(false);
    base::Named::prepareDelete(false);
  }

  NodeKind Identifier::getNodeKind() const {
    return ndkIdentifier;
  }

  base::Positioned* Identifier::getRefersTo() const {
    base::Positioned *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Identifier::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIdentifier_RefersTo:
        setRefersTo(edgeEnd);
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
    if (statement::Pattern::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Identifier::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIdentifier_RefersTo:
        removeRefersTo();
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
    if (statement::Pattern::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Identifier::setRefersTo(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkIdentifier_RefersTo);
      }
      m_refersTo = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkIdentifier_RefersTo);
    } else {
      if (m_refersTo) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Identifier::setRefersTo(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void Identifier::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkIdentifier_RefersTo);
      }
      m_refersTo = 0;
  }

  void Identifier::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Identifier::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Identifier::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Identifier& node = dynamic_cast<const Identifier&>(base);
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

  void Identifier::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Identifier::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Identifier", strlen("expression::Identifier"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Identifier::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    Pattern::save(binIo,false);

    Named::save(binIo,false);

    binIo.writeUInt4(m_refersTo);

  }

  void Identifier::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    Pattern::load(binIo,false);

    Named::load(binIo,false);

    m_refersTo =  binIo.readUInt4();

  }


}


}}}
