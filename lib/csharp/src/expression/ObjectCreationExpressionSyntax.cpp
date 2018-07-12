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
  ObjectCreationExpressionSyntax::ObjectCreationExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_ArgumentList(0),
    m_ConstructorCall(0),
    m_Initializer(0),
    m_Type(0)
  {
  }

  ObjectCreationExpressionSyntax::~ObjectCreationExpressionSyntax() {
  }

  void ObjectCreationExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeArgumentList();
    removeConstructorCall();
    removeInitializer();
    removeType();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind ObjectCreationExpressionSyntax::getNodeKind() const {
    return ndkObjectCreationExpressionSyntax;
  }

  structure::ArgumentListSyntax* ObjectCreationExpressionSyntax::getArgumentList() const {
    structure::ArgumentListSyntax *_node = NULL;
    if (m_ArgumentList != 0)
      _node = dynamic_cast<structure::ArgumentListSyntax*>(factory->getPointer(m_ArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::ConstructorDeclarationSyntax* ObjectCreationExpressionSyntax::getConstructorCall() const {
    structure::ConstructorDeclarationSyntax *_node = NULL;
    if (m_ConstructorCall != 0)
      _node = dynamic_cast<structure::ConstructorDeclarationSyntax*>(factory->getPointer(m_ConstructorCall));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::InitializerExpressionSyntax* ObjectCreationExpressionSyntax::getInitializer() const {
    expression::InitializerExpressionSyntax *_node = NULL;
    if (m_Initializer != 0)
      _node = dynamic_cast<expression::InitializerExpressionSyntax*>(factory->getPointer(m_Initializer));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* ObjectCreationExpressionSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ObjectCreationExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObjectCreationExpressionSyntax_ArgumentList:
        setArgumentList(edgeEnd);
        return true;
      case edkObjectCreationExpressionSyntax_ConstructorCall:
        setConstructorCall(edgeEnd);
        return true;
      case edkObjectCreationExpressionSyntax_Initializer:
        setInitializer(edgeEnd);
        return true;
      case edkObjectCreationExpressionSyntax_Type:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ObjectCreationExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkObjectCreationExpressionSyntax_ArgumentList:
        removeArgumentList();
        return true;
      case edkObjectCreationExpressionSyntax_ConstructorCall:
        removeConstructorCall();
        return true;
      case edkObjectCreationExpressionSyntax_Initializer:
        removeInitializer();
        return true;
      case edkObjectCreationExpressionSyntax_Type:
        removeType();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ObjectCreationExpressionSyntax::setArgumentList(NodeId _id) {
    structure::ArgumentListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ArgumentListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkObjectCreationExpressionSyntax_ArgumentList);
      }
      m_ArgumentList = _node->getId();
      if (m_ArgumentList != 0)
        setParentEdge(factory->getPointer(m_ArgumentList), edkObjectCreationExpressionSyntax_ArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ArgumentList, this->getId(), edkObjectCreationExpressionSyntax_ArgumentList);
    } else {
      if (m_ArgumentList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ObjectCreationExpressionSyntax::setArgumentList(structure::ArgumentListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgumentList(_node->getId());
  }

  void ObjectCreationExpressionSyntax::removeArgumentList() {
      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkObjectCreationExpressionSyntax_ArgumentList);
      }
      m_ArgumentList = 0;
  }

  void ObjectCreationExpressionSyntax::setConstructorCall(NodeId _id) {
    structure::ConstructorDeclarationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ConstructorDeclarationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ConstructorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ConstructorCall, m_id, edkObjectCreationExpressionSyntax_ConstructorCall);
      }
      m_ConstructorCall = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ConstructorCall, this->getId(), edkObjectCreationExpressionSyntax_ConstructorCall);
    } else {
      if (m_ConstructorCall) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ObjectCreationExpressionSyntax::setConstructorCall(structure::ConstructorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setConstructorCall(_node->getId());
  }

  void ObjectCreationExpressionSyntax::removeConstructorCall() {
      if (m_ConstructorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ConstructorCall, m_id, edkObjectCreationExpressionSyntax_ConstructorCall);
      }
      m_ConstructorCall = 0;
  }

  void ObjectCreationExpressionSyntax::setInitializer(NodeId _id) {
    expression::InitializerExpressionSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::InitializerExpressionSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Initializer) {
        removeParentEdge(m_Initializer);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Initializer, m_id, edkObjectCreationExpressionSyntax_Initializer);
      }
      m_Initializer = _node->getId();
      if (m_Initializer != 0)
        setParentEdge(factory->getPointer(m_Initializer), edkObjectCreationExpressionSyntax_Initializer);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Initializer, this->getId(), edkObjectCreationExpressionSyntax_Initializer);
    } else {
      if (m_Initializer) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ObjectCreationExpressionSyntax::setInitializer(expression::InitializerExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInitializer(_node->getId());
  }

  void ObjectCreationExpressionSyntax::removeInitializer() {
      if (m_Initializer) {
        removeParentEdge(m_Initializer);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Initializer, m_id, edkObjectCreationExpressionSyntax_Initializer);
      }
      m_Initializer = 0;
  }

  void ObjectCreationExpressionSyntax::setType(NodeId _id) {
    expression::TypeSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::TypeSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkObjectCreationExpressionSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkObjectCreationExpressionSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkObjectCreationExpressionSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ObjectCreationExpressionSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void ObjectCreationExpressionSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkObjectCreationExpressionSyntax_Type);
      }
      m_Type = 0;
  }

  void ObjectCreationExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ObjectCreationExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ObjectCreationExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ObjectCreationExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ObjectCreationExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ObjectCreationExpressionSyntax", strlen("expression::ObjectCreationExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ObjectCreationExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_ArgumentList);
    binIo.writeUInt4(m_ConstructorCall);
    binIo.writeUInt4(m_Initializer);
    binIo.writeUInt4(m_Type);

  }

  void ObjectCreationExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_ArgumentList =  binIo.readUInt4();
    if (m_ArgumentList != 0)
      setParentEdge(factory->getPointer(m_ArgumentList),edkObjectCreationExpressionSyntax_ArgumentList);

    m_ConstructorCall =  binIo.readUInt4();

    m_Initializer =  binIo.readUInt4();
    if (m_Initializer != 0)
      setParentEdge(factory->getPointer(m_Initializer),edkObjectCreationExpressionSyntax_Initializer);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkObjectCreationExpressionSyntax_Type);

  }


}


}}}
