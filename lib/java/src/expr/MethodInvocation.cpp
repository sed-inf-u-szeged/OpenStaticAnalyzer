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
  MethodInvocation::MethodInvocation(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Unary(_id, _factory),
    hasTypeArgumentsContainer(),
    hasArgumentsContainer(),
    m_invokes(0)
  {
  }

  MethodInvocation::~MethodInvocation() {
  }

  void MethodInvocation::clone(const MethodInvocation& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Unary::clone(other, false);

    hasTypeArgumentsContainer = other.hasTypeArgumentsContainer;
    hasArgumentsContainer = other.hasArgumentsContainer;
    m_invokes = other.m_invokes;
  }

  void MethodInvocation::prepareDelete(bool tryOnVirtualParent){
    while (!hasTypeArgumentsContainer.empty()) {
      const NodeId id = *hasTypeArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethodInvocation_HasTypeArguments);
      hasTypeArgumentsContainer.pop_front();
    }
    while (!hasArgumentsContainer.empty()) {
      const NodeId id = *hasArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethodInvocation_HasArguments);
      hasArgumentsContainer.pop_front();
    }
    removeInvokes();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Unary::prepareDelete(false);
  }

  NodeKind MethodInvocation::getNodeKind() const {
    return ndkMethodInvocation;
  }

  ListIterator<expr::TypeExpression> MethodInvocation::getTypeArgumentsListIteratorBegin() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, true);
  }

  ListIterator<expr::TypeExpression> MethodInvocation::getTypeArgumentsListIteratorEnd() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, false);
  }

  bool MethodInvocation::getTypeArgumentsIsEmpty() const {
    return getTypeArgumentsListIteratorBegin() == getTypeArgumentsListIteratorEnd();
  }

  unsigned int MethodInvocation::getTypeArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expr::TypeExpression> endIt = getTypeArgumentsListIteratorEnd();
    for (ListIterator<expr::TypeExpression> it = getTypeArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<expr::Expression> MethodInvocation::getArgumentsListIteratorBegin() const {
    return ListIterator<expr::Expression>(&hasArgumentsContainer, factory, true);
  }

  ListIterator<expr::Expression> MethodInvocation::getArgumentsListIteratorEnd() const {
    return ListIterator<expr::Expression>(&hasArgumentsContainer, factory, false);
  }

  bool MethodInvocation::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int MethodInvocation::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expr::Expression> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<expr::Expression> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  struc::MethodDeclaration* MethodInvocation::getInvokes() const {
    struc::MethodDeclaration *_node = NULL;
    if (m_invokes != 0)
      _node = dynamic_cast<struc::MethodDeclaration*>(factory->getPointer(m_invokes));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool MethodInvocation::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodInvocation_HasTypeArguments:
        addTypeArguments(edgeEnd);
        return true;
      case edkMethodInvocation_HasArguments:
        addArguments(edgeEnd);
        return true;
      case edkMethodInvocation_Invokes:
        setInvokes(edgeEnd);
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
    if (expr::Unary::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool MethodInvocation::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodInvocation_HasTypeArguments:
        removeTypeArguments(edgeEnd);
        return true;
      case edkMethodInvocation_HasArguments:
        removeArguments(edgeEnd);
        return true;
      case edkMethodInvocation_Invokes:
        removeInvokes();
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
    if (expr::Unary::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MethodInvocation::addTypeArguments(const expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkMethodInvocation_HasTypeArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethodInvocation_HasTypeArguments);
  }

  void MethodInvocation::addTypeArguments(NodeId _id) {
    const expr::TypeExpression *node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypeArguments( node );
  }

  void MethodInvocation::removeTypeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::TypeExpression>::Container::iterator it = find(hasTypeArgumentsContainer.begin(), hasTypeArgumentsContainer.end(), id);

    if (it == hasTypeArgumentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethodInvocation_HasTypeArguments);
  }

  void MethodInvocation::removeTypeArguments(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypeArguments(_node->getId());
  }

  void MethodInvocation::addArguments(const expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkMethodInvocation_HasArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethodInvocation_HasArguments);
  }

  void MethodInvocation::addArguments(NodeId _id) {
    const expr::Expression *node = dynamic_cast<expr::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void MethodInvocation::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Expression>::Container::iterator it = find(hasArgumentsContainer.begin(), hasArgumentsContainer.end(), id);

    if (it == hasArgumentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethodInvocation_HasArguments);
  }

  void MethodInvocation::removeArguments(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void MethodInvocation::setInvokes(NodeId _id) {
    struc::MethodDeclaration *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::MethodDeclaration*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_invokes) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_invokes, m_id, edkMethodInvocation_Invokes);
      }
      m_invokes = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_invokes, this->getId(), edkMethodInvocation_Invokes);
    } else {
      if (m_invokes) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodInvocation::setInvokes(struc::MethodDeclaration *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInvokes(_node->getId());
  }

  void MethodInvocation::removeInvokes() {
      if (m_invokes) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_invokes, m_id, edkMethodInvocation_Invokes);
      }
      m_invokes = 0;
  }

  void MethodInvocation::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MethodInvocation::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MethodInvocation::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const MethodInvocation& node = dynamic_cast<const MethodInvocation&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void MethodInvocation::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType MethodInvocation::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::MethodInvocation", strlen("expr::MethodInvocation"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MethodInvocation::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Unary::sort(false);
  }

  void MethodInvocation::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Unary::save(binIo,false);

    binIo.writeUInt4(m_invokes);


    for (ListIterator<expr::TypeExpression>::Container::const_iterator it = hasTypeArgumentsContainer.begin(); it != hasTypeArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<expr::Expression>::Container::const_iterator it = hasArgumentsContainer.begin(); it != hasArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void MethodInvocation::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Unary::load(binIo,false);

    m_invokes =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkMethodInvocation_HasTypeArguments);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkMethodInvocation_HasArguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
