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
  Delete::Delete(NodeId _id, Factory *_factory) :
    SimpleStatement(_id, _factory),
    m_hasTargetList(0)
  {
  }

  Delete::~Delete() {
  }

  void Delete::prepareDelete(bool tryOnVirtualParent){
    removeTargetList();
    statement::SimpleStatement::prepareDelete(false);
  }

  NodeKind Delete::getNodeKind() const {
    return ndkDelete;
  }

  statement::TargetList* Delete::getTargetList() const {
    statement::TargetList *_node = NULL;
    if (m_hasTargetList != 0)
      _node = dynamic_cast<statement::TargetList*>(factory->getPointer(m_hasTargetList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Delete::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDelete_HasTargetList:
        setTargetList(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Delete::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDelete_HasTargetList:
        removeTargetList();
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Delete::setTargetList(NodeId _id) {
    statement::TargetList *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::TargetList*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasTargetList) {
        removeParentEdge(m_hasTargetList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTargetList, m_id, edkDelete_HasTargetList);
      }
      m_hasTargetList = _node->getId();
      if (m_hasTargetList != 0)
        setParentEdge(factory->getPointer(m_hasTargetList), edkDelete_HasTargetList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTargetList, this->getId(), edkDelete_HasTargetList);
    } else {
      if (m_hasTargetList) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Delete::setTargetList(statement::TargetList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTargetList(_node->getId());
  }

  void Delete::removeTargetList() {
      if (m_hasTargetList) {
        removeParentEdge(m_hasTargetList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTargetList, m_id, edkDelete_HasTargetList);
      }
      m_hasTargetList = 0;
  }

  void Delete::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Delete::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Delete::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Delete::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Delete::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Delete", strlen("statement::Delete"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Delete::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleStatement::save(binIo,false);

    binIo.writeUInt4(m_hasTargetList);

  }

  void Delete::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleStatement::load(binIo,false);

    m_hasTargetList =  binIo.readUInt4();
    if (m_hasTargetList != 0)
      setParentEdge(factory->getPointer(m_hasTargetList),edkDelete_HasTargetList);

  }


}


}}}
