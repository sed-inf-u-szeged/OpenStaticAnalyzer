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
  NewClass::NewClass(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Expression(_id, _factory),
    m_hasEnclosingExpression(0),
    hasTypeArgumentsContainer(),
    m_hasTypeName(0),
    hasArgumentsContainer(),
    m_hasAnonymousClass(0),
    m_constructor(0)
  {
  }

  NewClass::~NewClass() {
  }

  void NewClass::clone(const NewClass& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Expression::clone(other, false);

    m_hasEnclosingExpression = other.m_hasEnclosingExpression;
    hasTypeArgumentsContainer = other.hasTypeArgumentsContainer;
    m_hasTypeName = other.m_hasTypeName;
    hasArgumentsContainer = other.hasArgumentsContainer;
    m_hasAnonymousClass = other.m_hasAnonymousClass;
    m_constructor = other.m_constructor;
  }

  void NewClass::prepareDelete(bool tryOnVirtualParent){
    removeEnclosingExpression();
    while (!hasTypeArgumentsContainer.empty()) {
      const NodeId id = *hasTypeArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNewClass_HasTypeArguments);
      hasTypeArgumentsContainer.pop_front();
    }
    removeTypeName();
    while (!hasArgumentsContainer.empty()) {
      const NodeId id = *hasArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNewClass_HasArguments);
      hasArgumentsContainer.pop_front();
    }
    removeAnonymousClass();
    removeConstructor();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Expression::prepareDelete(false);
  }

  NodeKind NewClass::getNodeKind() const {
    return ndkNewClass;
  }

  expr::Expression* NewClass::getEnclosingExpression() const {
    expr::Expression *_node = NULL;
    if (m_hasEnclosingExpression != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasEnclosingExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::TypeExpression> NewClass::getTypeArgumentsListIteratorBegin() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, true);
  }

  ListIterator<expr::TypeExpression> NewClass::getTypeArgumentsListIteratorEnd() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, false);
  }

  bool NewClass::getTypeArgumentsIsEmpty() const {
    return getTypeArgumentsListIteratorBegin() == getTypeArgumentsListIteratorEnd();
  }

  unsigned int NewClass::getTypeArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expr::TypeExpression> endIt = getTypeArgumentsListIteratorEnd();
    for (ListIterator<expr::TypeExpression> it = getTypeArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expr::TypeExpression* NewClass::getTypeName() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasTypeName != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasTypeName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::Expression> NewClass::getArgumentsListIteratorBegin() const {
    return ListIterator<expr::Expression>(&hasArgumentsContainer, factory, true);
  }

  ListIterator<expr::Expression> NewClass::getArgumentsListIteratorEnd() const {
    return ListIterator<expr::Expression>(&hasArgumentsContainer, factory, false);
  }

  bool NewClass::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int NewClass::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expr::Expression> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<expr::Expression> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  struc::AnonymousClass* NewClass::getAnonymousClass() const {
    struc::AnonymousClass *_node = NULL;
    if (m_hasAnonymousClass != 0)
      _node = dynamic_cast<struc::AnonymousClass*>(factory->getPointer(m_hasAnonymousClass));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  struc::NormalMethod* NewClass::getConstructor() const {
    struc::NormalMethod *_node = NULL;
    if (m_constructor != 0)
      _node = dynamic_cast<struc::NormalMethod*>(factory->getPointer(m_constructor));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool NewClass::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNewClass_HasEnclosingExpression:
        setEnclosingExpression(edgeEnd);
        return true;
      case edkNewClass_HasTypeArguments:
        addTypeArguments(edgeEnd);
        return true;
      case edkNewClass_HasTypeName:
        setTypeName(edgeEnd);
        return true;
      case edkNewClass_HasArguments:
        addArguments(edgeEnd);
        return true;
      case edkNewClass_HasAnonymousClass:
        setAnonymousClass(edgeEnd);
        return true;
      case edkNewClass_Constructor:
        setConstructor(edgeEnd);
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
    if (expr::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NewClass::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNewClass_HasEnclosingExpression:
        removeEnclosingExpression();
        return true;
      case edkNewClass_HasTypeArguments:
        removeTypeArguments(edgeEnd);
        return true;
      case edkNewClass_HasTypeName:
        removeTypeName();
        return true;
      case edkNewClass_HasArguments:
        removeArguments(edgeEnd);
        return true;
      case edkNewClass_HasAnonymousClass:
        removeAnonymousClass();
        return true;
      case edkNewClass_Constructor:
        removeConstructor();
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
    if (expr::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NewClass::setEnclosingExpression(NodeId _id) {
    expr::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasEnclosingExpression) {
        removeParentEdge(m_hasEnclosingExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasEnclosingExpression, m_id, edkNewClass_HasEnclosingExpression);
      }
      m_hasEnclosingExpression = _node->getId();
      if (m_hasEnclosingExpression != 0)
        setParentEdge(factory->getPointer(m_hasEnclosingExpression), edkNewClass_HasEnclosingExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasEnclosingExpression, this->getId(), edkNewClass_HasEnclosingExpression);
    } else {
      if (m_hasEnclosingExpression) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NewClass::setEnclosingExpression(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setEnclosingExpression(_node->getId());
  }

  void NewClass::removeEnclosingExpression() {
      if (m_hasEnclosingExpression) {
        removeParentEdge(m_hasEnclosingExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasEnclosingExpression, m_id, edkNewClass_HasEnclosingExpression);
      }
      m_hasEnclosingExpression = 0;
  }

  void NewClass::addTypeArguments(const expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNewClass_HasTypeArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNewClass_HasTypeArguments);
  }

  void NewClass::addTypeArguments(NodeId _id) {
    const expr::TypeExpression *node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypeArguments( node );
  }

  void NewClass::removeTypeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::TypeExpression>::Container::iterator it = find(hasTypeArgumentsContainer.begin(), hasTypeArgumentsContainer.end(), id);

    if (it == hasTypeArgumentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNewClass_HasTypeArguments);
  }

  void NewClass::removeTypeArguments(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypeArguments(_node->getId());
  }

  void NewClass::setTypeName(NodeId _id) {
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

      if (m_hasTypeName) {
        removeParentEdge(m_hasTypeName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTypeName, m_id, edkNewClass_HasTypeName);
      }
      m_hasTypeName = _node->getId();
      if (m_hasTypeName != 0)
        setParentEdge(factory->getPointer(m_hasTypeName), edkNewClass_HasTypeName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTypeName, this->getId(), edkNewClass_HasTypeName);
    } else {
      if (m_hasTypeName) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NewClass::setTypeName(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTypeName(_node->getId());
  }

  void NewClass::removeTypeName() {
      if (m_hasTypeName) {
        removeParentEdge(m_hasTypeName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTypeName, m_id, edkNewClass_HasTypeName);
      }
      m_hasTypeName = 0;
  }

  void NewClass::addArguments(const expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNewClass_HasArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNewClass_HasArguments);
  }

  void NewClass::addArguments(NodeId _id) {
    const expr::Expression *node = dynamic_cast<expr::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void NewClass::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Expression>::Container::iterator it = find(hasArgumentsContainer.begin(), hasArgumentsContainer.end(), id);

    if (it == hasArgumentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNewClass_HasArguments);
  }

  void NewClass::removeArguments(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void NewClass::setAnonymousClass(NodeId _id) {
    struc::AnonymousClass *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::AnonymousClass*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasAnonymousClass) {
        removeParentEdge(m_hasAnonymousClass);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAnonymousClass, m_id, edkNewClass_HasAnonymousClass);
      }
      m_hasAnonymousClass = _node->getId();
      if (m_hasAnonymousClass != 0)
        setParentEdge(factory->getPointer(m_hasAnonymousClass), edkNewClass_HasAnonymousClass);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasAnonymousClass, this->getId(), edkNewClass_HasAnonymousClass);
    } else {
      if (m_hasAnonymousClass) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NewClass::setAnonymousClass(struc::AnonymousClass *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAnonymousClass(_node->getId());
  }

  void NewClass::removeAnonymousClass() {
      if (m_hasAnonymousClass) {
        removeParentEdge(m_hasAnonymousClass);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAnonymousClass, m_id, edkNewClass_HasAnonymousClass);
      }
      m_hasAnonymousClass = 0;
  }

  void NewClass::setConstructor(NodeId _id) {
    struc::NormalMethod *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::NormalMethod*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_constructor) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_constructor, m_id, edkNewClass_Constructor);
      }
      m_constructor = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_constructor, this->getId(), edkNewClass_Constructor);
    } else {
      if (m_constructor) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NewClass::setConstructor(struc::NormalMethod *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setConstructor(_node->getId());
  }

  void NewClass::removeConstructor() {
      if (m_constructor) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_constructor, m_id, edkNewClass_Constructor);
      }
      m_constructor = 0;
  }

  void NewClass::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NewClass::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NewClass::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const NewClass& node = dynamic_cast<const NewClass&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void NewClass::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType NewClass::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::NewClass", strlen("expr::NewClass"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NewClass::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Expression::sort(false);
  }

  void NewClass::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasEnclosingExpression);
    binIo.writeUInt4(m_hasTypeName);
    binIo.writeUInt4(m_hasAnonymousClass);
    binIo.writeUInt4(m_constructor);


    for (ListIterator<expr::TypeExpression>::Container::const_iterator it = hasTypeArgumentsContainer.begin(); it != hasTypeArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<expr::Expression>::Container::const_iterator it = hasArgumentsContainer.begin(); it != hasArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void NewClass::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Expression::load(binIo,false);

    m_hasEnclosingExpression =  binIo.readUInt4();
    if (m_hasEnclosingExpression != 0)
      setParentEdge(factory->getPointer(m_hasEnclosingExpression),edkNewClass_HasEnclosingExpression);

    m_hasTypeName =  binIo.readUInt4();
    if (m_hasTypeName != 0)
      setParentEdge(factory->getPointer(m_hasTypeName),edkNewClass_HasTypeName);

    m_hasAnonymousClass =  binIo.readUInt4();
    if (m_hasAnonymousClass != 0)
      setParentEdge(factory->getPointer(m_hasAnonymousClass),edkNewClass_HasAnonymousClass);

    m_constructor =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNewClass_HasTypeArguments);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNewClass_HasArguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
