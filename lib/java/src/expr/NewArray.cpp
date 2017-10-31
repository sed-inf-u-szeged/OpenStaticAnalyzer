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
  NewArray::NewArray(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Expression(_id, _factory),
    m_leftBracePosition(),
    m_hasComponentType(0),
    hasDimensionsContainer(),
    hasInitializersContainer()
  {
    m_leftBracePosition.posInfo.path = 0;
    m_leftBracePosition.posInfo.line = 0;
    m_leftBracePosition.posInfo.col = 0;
    m_leftBracePosition.posInfo.endLine = 0;
    m_leftBracePosition.posInfo.endCol = 0;
    m_leftBracePosition.posInfo.wideLine = 0;
    m_leftBracePosition.posInfo.wideCol = 0;
    m_leftBracePosition.posInfo.wideEndLine = 0;
    m_leftBracePosition.posInfo.wideEndCol = 0;
  }

  NewArray::~NewArray() {
  }

  void NewArray::clone(const NewArray& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Expression::clone(other, false);

    m_leftBracePosition.posInfo = other.m_leftBracePosition.posInfo;
    m_hasComponentType = other.m_hasComponentType;
    hasDimensionsContainer = other.hasDimensionsContainer;
    hasInitializersContainer = other.hasInitializersContainer;
  }

  void NewArray::prepareDelete(bool tryOnVirtualParent){
    removeComponentType();
    while (!hasDimensionsContainer.empty()) {
      const NodeId id = *hasDimensionsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNewArray_HasDimensions);
      hasDimensionsContainer.pop_front();
    }
    while (!hasInitializersContainer.empty()) {
      const NodeId id = *hasInitializersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNewArray_HasInitializers);
      hasInitializersContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Expression::prepareDelete(false);
  }

  NodeKind NewArray::getNodeKind() const {
    return ndkNewArray;
  }

  const Range NewArray::getLeftBracePosition() const {
    return Range(factory->getStringTable(), m_leftBracePosition.posInfo);
  }

  int NewArray::compareByLeftBracePosition(const NewArray& other) const {
    if (m_leftBracePosition.posInfo.path != other.m_leftBracePosition.posInfo.path) {
      return (m_leftBracePosition.posInfo.path < other.m_leftBracePosition.posInfo.path) ? -1 :1 ;
    };
    if (m_leftBracePosition.posInfo.wideLine != other.m_leftBracePosition.posInfo.wideLine) {
      return (m_leftBracePosition.posInfo.wideLine < other.m_leftBracePosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_leftBracePosition.posInfo.wideCol != other.m_leftBracePosition.posInfo.wideCol) {
      return (m_leftBracePosition.posInfo.wideCol < other.m_leftBracePosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_leftBracePosition.posInfo.wideEndLine != other.m_leftBracePosition.posInfo.wideEndLine) {
      return (m_leftBracePosition.posInfo.wideEndLine > other.m_leftBracePosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_leftBracePosition.posInfo.wideEndCol != other.m_leftBracePosition.posInfo.wideEndCol) {
      return (m_leftBracePosition.posInfo.wideEndCol > other.m_leftBracePosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void NewArray::setLeftBracePosition(const Range& _leftBracePosition) {
    m_leftBracePosition.posInfo = _leftBracePosition.positionInfo;
    if (_leftBracePosition.strTable != &factory->getStringTable())
      m_leftBracePosition.posInfo.path = factory->getStringTable().set(_leftBracePosition.getPath());
  }

  expr::TypeExpression* NewArray::getComponentType() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasComponentType != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasComponentType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::Expression> NewArray::getDimensionsListIteratorBegin() const {
    return ListIterator<expr::Expression>(&hasDimensionsContainer, factory, true);
  }

  ListIterator<expr::Expression> NewArray::getDimensionsListIteratorEnd() const {
    return ListIterator<expr::Expression>(&hasDimensionsContainer, factory, false);
  }

  bool NewArray::getDimensionsIsEmpty() const {
    return getDimensionsListIteratorBegin() == getDimensionsListIteratorEnd();
  }

  unsigned int NewArray::getDimensionsSize() const {
    unsigned int size = 0;
    ListIterator<expr::Expression> endIt = getDimensionsListIteratorEnd();
    for (ListIterator<expr::Expression> it = getDimensionsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<expr::Expression> NewArray::getInitializersListIteratorBegin() const {
    return ListIterator<expr::Expression>(&hasInitializersContainer, factory, true);
  }

  ListIterator<expr::Expression> NewArray::getInitializersListIteratorEnd() const {
    return ListIterator<expr::Expression>(&hasInitializersContainer, factory, false);
  }

  bool NewArray::getInitializersIsEmpty() const {
    return getInitializersListIteratorBegin() == getInitializersListIteratorEnd();
  }

  unsigned int NewArray::getInitializersSize() const {
    unsigned int size = 0;
    ListIterator<expr::Expression> endIt = getInitializersListIteratorEnd();
    for (ListIterator<expr::Expression> it = getInitializersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool NewArray::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNewArray_HasComponentType:
        setComponentType(edgeEnd);
        return true;
      case edkNewArray_HasDimensions:
        addDimensions(edgeEnd);
        return true;
      case edkNewArray_HasInitializers:
        addInitializers(edgeEnd);
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

  bool NewArray::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNewArray_HasComponentType:
        removeComponentType();
        return true;
      case edkNewArray_HasDimensions:
        removeDimensions(edgeEnd);
        return true;
      case edkNewArray_HasInitializers:
        removeInitializers(edgeEnd);
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

  void NewArray::setComponentType(NodeId _id) {
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

      if (m_hasComponentType) {
        removeParentEdge(m_hasComponentType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasComponentType, m_id, edkNewArray_HasComponentType);
      }
      m_hasComponentType = _node->getId();
      if (m_hasComponentType != 0)
        setParentEdge(factory->getPointer(m_hasComponentType), edkNewArray_HasComponentType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasComponentType, this->getId(), edkNewArray_HasComponentType);
    } else {
      if (m_hasComponentType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NewArray::setComponentType(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setComponentType(_node->getId());
  }

  void NewArray::removeComponentType() {
      if (m_hasComponentType) {
        removeParentEdge(m_hasComponentType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasComponentType, m_id, edkNewArray_HasComponentType);
      }
      m_hasComponentType = 0;
  }

  void NewArray::addDimensions(const expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasDimensionsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNewArray_HasDimensions);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNewArray_HasDimensions);
  }

  void NewArray::addDimensions(NodeId _id) {
    const expr::Expression *node = dynamic_cast<expr::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addDimensions( node );
  }

  void NewArray::removeDimensions(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Expression>::Container::iterator it = find(hasDimensionsContainer.begin(), hasDimensionsContainer.end(), id);

    if (it == hasDimensionsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasDimensionsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNewArray_HasDimensions);
  }

  void NewArray::removeDimensions(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeDimensions(_node->getId());
  }

  void NewArray::addInitializers(const expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasInitializersContainer.push_back(_node->getId());
    setParentEdge(_node,edkNewArray_HasInitializers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNewArray_HasInitializers);
  }

  void NewArray::addInitializers(NodeId _id) {
    const expr::Expression *node = dynamic_cast<expr::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addInitializers( node );
  }

  void NewArray::removeInitializers(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Expression>::Container::iterator it = find(hasInitializersContainer.begin(), hasInitializersContainer.end(), id);

    if (it == hasInitializersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasInitializersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNewArray_HasInitializers);
  }

  void NewArray::removeInitializers(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeInitializers(_node->getId());
  }

  void NewArray::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NewArray::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NewArray::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const NewArray& node = dynamic_cast<const NewArray&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void NewArray::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType NewArray::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::NewArray", strlen("expr::NewArray"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NewArray::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Expression::sort(false);
  }

  void NewArray::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Expression::save(binIo,false);

    factory->getStringTable().setType(m_leftBracePosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_leftBracePosition.posInfo.path);
    binIo.writeUInt4(m_leftBracePosition.posInfo.line);
    binIo.writeUInt4(m_leftBracePosition.posInfo.col);
    binIo.writeUInt4(m_leftBracePosition.posInfo.endLine);
    binIo.writeUInt4(m_leftBracePosition.posInfo.endCol);
    binIo.writeUInt4(m_leftBracePosition.posInfo.wideLine);
    binIo.writeUInt4(m_leftBracePosition.posInfo.wideCol);
    binIo.writeUInt4(m_leftBracePosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_leftBracePosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasComponentType);


    for (ListIterator<expr::Expression>::Container::const_iterator it = hasDimensionsContainer.begin(); it != hasDimensionsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<expr::Expression>::Container::const_iterator it = hasInitializersContainer.begin(); it != hasInitializersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void NewArray::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Expression::load(binIo,false);

    m_leftBracePosition.posInfo.path = binIo.readUInt4();
    m_leftBracePosition.posInfo.line = binIo.readUInt4();
    m_leftBracePosition.posInfo.col = binIo.readUInt4();
    m_leftBracePosition.posInfo.endLine = binIo.readUInt4();
    m_leftBracePosition.posInfo.endCol = binIo.readUInt4();
    m_leftBracePosition.posInfo.wideLine = binIo.readUInt4();
    m_leftBracePosition.posInfo.wideCol = binIo.readUInt4();
    m_leftBracePosition.posInfo.wideEndLine = binIo.readUInt4();
    m_leftBracePosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasComponentType =  binIo.readUInt4();
    if (m_hasComponentType != 0)
      setParentEdge(factory->getPointer(m_hasComponentType),edkNewArray_HasComponentType);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasDimensionsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNewArray_HasDimensions);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasInitializersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNewArray_HasInitializers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
