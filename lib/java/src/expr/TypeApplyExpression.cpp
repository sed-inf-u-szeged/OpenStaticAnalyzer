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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expr { 
  TypeApplyExpression::TypeApplyExpression(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    TypeExpression(_id, _factory),
    m_hasRawType(0),
    hasTypeArgumentsContainer()
  {
  }

  TypeApplyExpression::~TypeApplyExpression() {
  }

  void TypeApplyExpression::clone(const TypeApplyExpression& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::TypeExpression::clone(other, false);

    m_hasRawType = other.m_hasRawType;
    hasTypeArgumentsContainer = other.hasTypeArgumentsContainer;
  }

  void TypeApplyExpression::prepareDelete(bool tryOnVirtualParent){
    removeRawType();
    while (!hasTypeArgumentsContainer.empty()) {
      const NodeId id = *hasTypeArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeApplyExpression_HasTypeArguments);
      hasTypeArgumentsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::TypeExpression::prepareDelete(false);
  }

  NodeKind TypeApplyExpression::getNodeKind() const {
    return ndkTypeApplyExpression;
  }

  expr::TypeExpression* TypeApplyExpression::getRawType() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasRawType != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasRawType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::TypeExpression> TypeApplyExpression::getTypeArgumentsListIteratorBegin() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, true);
  }

  ListIterator<expr::TypeExpression> TypeApplyExpression::getTypeArgumentsListIteratorEnd() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, false);
  }

  bool TypeApplyExpression::getTypeArgumentsIsEmpty() const {
    return getTypeArgumentsListIteratorBegin() == getTypeArgumentsListIteratorEnd();
  }

  unsigned int TypeApplyExpression::getTypeArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expr::TypeExpression> endIt = getTypeArgumentsListIteratorEnd();
    for (ListIterator<expr::TypeExpression> it = getTypeArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TypeApplyExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeApplyExpression_HasRawType:
        setRawType(edgeEnd);
        return true;
      case edkTypeApplyExpression_HasTypeArguments:
        addTypeArguments(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expr::TypeExpression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TypeApplyExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeApplyExpression_HasRawType:
        removeRawType();
        return true;
      case edkTypeApplyExpression_HasTypeArguments:
        removeTypeArguments(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expr::TypeExpression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeApplyExpression::setRawType(NodeId _id) {
    expr::TypeExpression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::TypeExpression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasRawType) {
        removeParentEdge(m_hasRawType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRawType, m_id, edkTypeApplyExpression_HasRawType);
      }
      m_hasRawType = _node->getId();
      if (m_hasRawType != 0)
        setParentEdge(factory->getPointer(m_hasRawType), edkTypeApplyExpression_HasRawType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasRawType, this->getId(), edkTypeApplyExpression_HasRawType);
    } else {
      if (m_hasRawType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeApplyExpression::setRawType(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRawType(_node->getId());
  }

  void TypeApplyExpression::removeRawType() {
      if (m_hasRawType) {
        removeParentEdge(m_hasRawType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRawType, m_id, edkTypeApplyExpression_HasRawType);
      }
      m_hasRawType = 0;
  }

  void TypeApplyExpression::addTypeArguments(const expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeApplyExpression_HasTypeArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeApplyExpression_HasTypeArguments);
  }

  void TypeApplyExpression::addTypeArguments(NodeId _id) {
    const expr::TypeExpression *node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypeArguments( node );
  }

  void TypeApplyExpression::removeTypeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::TypeExpression>::Container::iterator it = find(hasTypeArgumentsContainer.begin(), hasTypeArgumentsContainer.end(), id);

    if (it == hasTypeArgumentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeApplyExpression_HasTypeArguments);
  }

  void TypeApplyExpression::removeTypeArguments(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypeArguments(_node->getId());
  }

  void TypeApplyExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeApplyExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeApplyExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const TypeApplyExpression& node = dynamic_cast<const TypeApplyExpression&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void TypeApplyExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TypeApplyExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::TypeApplyExpression", strlen("expr::TypeApplyExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeApplyExpression::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    TypeExpression::sort(false);
  }

  void TypeApplyExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    TypeExpression::save(binIo,false);

    binIo.writeUInt4(m_hasRawType);


    for (ListIterator<expr::TypeExpression>::Container::const_iterator it = hasTypeArgumentsContainer.begin(); it != hasTypeArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeApplyExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    TypeExpression::load(binIo,false);

    m_hasRawType =  binIo.readUInt4();
    if (m_hasRawType != 0)
      setParentEdge(factory->getPointer(m_hasRawType),edkTypeApplyExpression_HasRawType);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeApplyExpression_HasTypeArguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
