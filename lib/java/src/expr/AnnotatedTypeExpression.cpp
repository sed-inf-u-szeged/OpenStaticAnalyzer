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
  AnnotatedTypeExpression::AnnotatedTypeExpression(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    TypeExpression(_id, _factory),
    hasAnnotationsContainer(),
    m_hasUnderlyingType(0)
  {
  }

  AnnotatedTypeExpression::~AnnotatedTypeExpression() {
  }

  void AnnotatedTypeExpression::clone(const AnnotatedTypeExpression& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::TypeExpression::clone(other, false);

    hasAnnotationsContainer = other.hasAnnotationsContainer;
    m_hasUnderlyingType = other.m_hasUnderlyingType;
  }

  void AnnotatedTypeExpression::prepareDelete(bool tryOnVirtualParent){
    while (!hasAnnotationsContainer.empty()) {
      const NodeId id = *hasAnnotationsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAnnotatedTypeExpression_HasAnnotations);
      hasAnnotationsContainer.pop_front();
    }
    removeUnderlyingType();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::TypeExpression::prepareDelete(false);
  }

  NodeKind AnnotatedTypeExpression::getNodeKind() const {
    return ndkAnnotatedTypeExpression;
  }

  ListIterator<expr::Annotation> AnnotatedTypeExpression::getAnnotationsListIteratorBegin() const {
    return ListIterator<expr::Annotation>(&hasAnnotationsContainer, factory, true);
  }

  ListIterator<expr::Annotation> AnnotatedTypeExpression::getAnnotationsListIteratorEnd() const {
    return ListIterator<expr::Annotation>(&hasAnnotationsContainer, factory, false);
  }

  bool AnnotatedTypeExpression::getAnnotationsIsEmpty() const {
    return getAnnotationsListIteratorBegin() == getAnnotationsListIteratorEnd();
  }

  unsigned int AnnotatedTypeExpression::getAnnotationsSize() const {
    unsigned int size = 0;
    ListIterator<expr::Annotation> endIt = getAnnotationsListIteratorEnd();
    for (ListIterator<expr::Annotation> it = getAnnotationsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expr::TypeExpression* AnnotatedTypeExpression::getUnderlyingType() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasUnderlyingType != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasUnderlyingType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AnnotatedTypeExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnotatedTypeExpression_HasAnnotations:
        addAnnotations(edgeEnd);
        return true;
      case edkAnnotatedTypeExpression_HasUnderlyingType:
        setUnderlyingType(edgeEnd);
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

  bool AnnotatedTypeExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnotatedTypeExpression_HasAnnotations:
        removeAnnotations(edgeEnd);
        return true;
      case edkAnnotatedTypeExpression_HasUnderlyingType:
        removeUnderlyingType();
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

  void AnnotatedTypeExpression::addAnnotations(const expr::Annotation *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsAnnotation(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasAnnotationsContainer.push_back(_node->getId());
    setParentEdge(_node,edkAnnotatedTypeExpression_HasAnnotations);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAnnotatedTypeExpression_HasAnnotations);
  }

  void AnnotatedTypeExpression::addAnnotations(NodeId _id) {
    const expr::Annotation *node = dynamic_cast<expr::Annotation*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAnnotations( node );
  }

  void AnnotatedTypeExpression::removeAnnotations(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Annotation>::Container::iterator it = find(hasAnnotationsContainer.begin(), hasAnnotationsContainer.end(), id);

    if (it == hasAnnotationsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasAnnotationsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAnnotatedTypeExpression_HasAnnotations);
  }

  void AnnotatedTypeExpression::removeAnnotations(expr::Annotation *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAnnotations(_node->getId());
  }

  void AnnotatedTypeExpression::setUnderlyingType(NodeId _id) {
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

      if (m_hasUnderlyingType) {
        removeParentEdge(m_hasUnderlyingType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasUnderlyingType, m_id, edkAnnotatedTypeExpression_HasUnderlyingType);
      }
      m_hasUnderlyingType = _node->getId();
      if (m_hasUnderlyingType != 0)
        setParentEdge(factory->getPointer(m_hasUnderlyingType), edkAnnotatedTypeExpression_HasUnderlyingType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasUnderlyingType, this->getId(), edkAnnotatedTypeExpression_HasUnderlyingType);
    } else {
      if (m_hasUnderlyingType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AnnotatedTypeExpression::setUnderlyingType(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setUnderlyingType(_node->getId());
  }

  void AnnotatedTypeExpression::removeUnderlyingType() {
      if (m_hasUnderlyingType) {
        removeParentEdge(m_hasUnderlyingType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasUnderlyingType, m_id, edkAnnotatedTypeExpression_HasUnderlyingType);
      }
      m_hasUnderlyingType = 0;
  }

  void AnnotatedTypeExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AnnotatedTypeExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AnnotatedTypeExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AnnotatedTypeExpression& node = dynamic_cast<const AnnotatedTypeExpression&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void AnnotatedTypeExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType AnnotatedTypeExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::AnnotatedTypeExpression", strlen("expr::AnnotatedTypeExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnnotatedTypeExpression::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    TypeExpression::sort(false);
  }

  void AnnotatedTypeExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    TypeExpression::save(binIo,false);

    binIo.writeUInt4(m_hasUnderlyingType);


    for (ListIterator<expr::Annotation>::Container::const_iterator it = hasAnnotationsContainer.begin(); it != hasAnnotationsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void AnnotatedTypeExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    TypeExpression::load(binIo,false);

    m_hasUnderlyingType =  binIo.readUInt4();
    if (m_hasUnderlyingType != 0)
      setParentEdge(factory->getPointer(m_hasUnderlyingType),edkAnnotatedTypeExpression_HasUnderlyingType);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasAnnotationsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkAnnotatedTypeExpression_HasAnnotations);
      _id = binIo.readUInt4();
    }
  }


}


}}}
