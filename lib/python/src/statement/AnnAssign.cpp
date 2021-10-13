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
  AnnAssign::AnnAssign(NodeId _id, Factory *_factory) :
    Assign(_id, _factory),
    m_isSimple(false),
    m_hasAnnotation(0)
  {
  }

  AnnAssign::~AnnAssign() {
  }

  void AnnAssign::prepareDelete(bool tryOnVirtualParent){
    removeAnnotation();
    statement::Assign::prepareDelete(false);
  }

  NodeKind AnnAssign::getNodeKind() const {
    return ndkAnnAssign;
  }

  bool AnnAssign::getIsSimple() const {
    return m_isSimple;
  }

  void AnnAssign::setIsSimple(bool _isSimple) {
    m_isSimple = _isSimple;
  }

  expression::Expression* AnnAssign::getAnnotation() const {
    expression::Expression *_node = NULL;
    if (m_hasAnnotation != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasAnnotation));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AnnAssign::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnAssign_HasAnnotation:
        setAnnotation(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::Assign::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AnnAssign::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnAssign_HasAnnotation:
        removeAnnotation();
        return true;
      default:
        break;
    }
    if (statement::Assign::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AnnAssign::setAnnotation(NodeId _id) {
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

      if (m_hasAnnotation) {
        removeParentEdge(m_hasAnnotation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAnnotation, m_id, edkAnnAssign_HasAnnotation);
      }
      m_hasAnnotation = _node->getId();
      if (m_hasAnnotation != 0)
        setParentEdge(factory->getPointer(m_hasAnnotation), edkAnnAssign_HasAnnotation);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasAnnotation, this->getId(), edkAnnAssign_HasAnnotation);
    } else {
      if (m_hasAnnotation) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AnnAssign::setAnnotation(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAnnotation(_node->getId());
  }

  void AnnAssign::removeAnnotation() {
      if (m_hasAnnotation) {
        removeParentEdge(m_hasAnnotation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAnnotation, m_id, edkAnnAssign_HasAnnotation);
      }
      m_hasAnnotation = 0;
  }

  void AnnAssign::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AnnAssign::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AnnAssign::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AnnAssign& node = dynamic_cast<const AnnAssign&>(base);
      double matchAttrs = 0;
      if(node.getIsSimple() == getIsSimple()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void AnnAssign::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType AnnAssign::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::AnnAssign", strlen("statement::AnnAssign"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnnAssign::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Assign::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isSimple) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasAnnotation);

  }

  void AnnAssign::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Assign::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isSimple = boolValues & 1;
    boolValues >>= 1;

    m_hasAnnotation =  binIo.readUInt4();
    if (m_hasAnnotation != 0)
      setParentEdge(factory->getPointer(m_hasAnnotation),edkAnnAssign_HasAnnotation);

  }


}


}}}
