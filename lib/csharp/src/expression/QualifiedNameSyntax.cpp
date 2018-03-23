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

#include "csharp/inc/csharp.h"
#include "csharp/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "csharp/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace csharp { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  QualifiedNameSyntax::QualifiedNameSyntax(NodeId _id, Factory *_factory) :
    NameSyntax(_id, _factory),
    m_Left(0),
    m_Right(0)
  {
  }

  QualifiedNameSyntax::~QualifiedNameSyntax() {
  }

  void QualifiedNameSyntax::prepareDelete(bool tryOnVirtualParent){
    removeLeft();
    removeRight();
    expression::NameSyntax::prepareDelete(false);
  }

  NodeKind QualifiedNameSyntax::getNodeKind() const {
    return ndkQualifiedNameSyntax;
  }

  expression::NameSyntax* QualifiedNameSyntax::getLeft() const {
    expression::NameSyntax *_node = NULL;
    if (m_Left != 0)
      _node = dynamic_cast<expression::NameSyntax*>(factory->getPointer(m_Left));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::SimpleNameSyntax* QualifiedNameSyntax::getRight() const {
    expression::SimpleNameSyntax *_node = NULL;
    if (m_Right != 0)
      _node = dynamic_cast<expression::SimpleNameSyntax*>(factory->getPointer(m_Right));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool QualifiedNameSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQualifiedNameSyntax_Left:
        setLeft(edgeEnd);
        return true;
      case edkQualifiedNameSyntax_Right:
        setRight(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::NameSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool QualifiedNameSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkQualifiedNameSyntax_Left:
        removeLeft();
        return true;
      case edkQualifiedNameSyntax_Right:
        removeRight();
        return true;
      default:
        break;
    }
    if (expression::NameSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void QualifiedNameSyntax::setLeft(NodeId _id) {
    expression::NameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::NameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Left) {
        removeParentEdge(m_Left);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Left, m_id, edkQualifiedNameSyntax_Left);
      }
      m_Left = _node->getId();
      if (m_Left != 0)
        setParentEdge(factory->getPointer(m_Left), edkQualifiedNameSyntax_Left);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Left, this->getId(), edkQualifiedNameSyntax_Left);
    } else {
      if (m_Left) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QualifiedNameSyntax::setLeft(expression::NameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeft(_node->getId());
  }

  void QualifiedNameSyntax::removeLeft() {
      if (m_Left) {
        removeParentEdge(m_Left);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Left, m_id, edkQualifiedNameSyntax_Left);
      }
      m_Left = 0;
  }

  void QualifiedNameSyntax::setRight(NodeId _id) {
    expression::SimpleNameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::SimpleNameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Right) {
        removeParentEdge(m_Right);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Right, m_id, edkQualifiedNameSyntax_Right);
      }
      m_Right = _node->getId();
      if (m_Right != 0)
        setParentEdge(factory->getPointer(m_Right), edkQualifiedNameSyntax_Right);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Right, this->getId(), edkQualifiedNameSyntax_Right);
    } else {
      if (m_Right) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void QualifiedNameSyntax::setRight(expression::SimpleNameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRight(_node->getId());
  }

  void QualifiedNameSyntax::removeRight() {
      if (m_Right) {
        removeParentEdge(m_Right);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Right, m_id, edkQualifiedNameSyntax_Right);
      }
      m_Right = 0;
  }

  void QualifiedNameSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void QualifiedNameSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double QualifiedNameSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void QualifiedNameSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType QualifiedNameSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::QualifiedNameSyntax", strlen("expression::QualifiedNameSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void QualifiedNameSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    NameSyntax::save(binIo,false);

    binIo.writeUInt4(m_Left);
    binIo.writeUInt4(m_Right);

  }

  void QualifiedNameSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    NameSyntax::load(binIo,false);

    m_Left =  binIo.readUInt4();
    if (m_Left != 0)
      setParentEdge(factory->getPointer(m_Left),edkQualifiedNameSyntax_Left);

    m_Right =  binIo.readUInt4();
    if (m_Right != 0)
      setParentEdge(factory->getPointer(m_Right),edkQualifiedNameSyntax_Right);

  }


}


}}}
