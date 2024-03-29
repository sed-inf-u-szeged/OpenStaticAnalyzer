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
  TypeIntersectionExpression::TypeIntersectionExpression(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    TypeExpression(_id, _factory),
    hasBoundsContainer()
  {
  }

  TypeIntersectionExpression::~TypeIntersectionExpression() {
  }

  void TypeIntersectionExpression::clone(const TypeIntersectionExpression& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::TypeExpression::clone(other, false);

    hasBoundsContainer = other.hasBoundsContainer;
  }

  void TypeIntersectionExpression::prepareDelete(bool tryOnVirtualParent){
    while (!hasBoundsContainer.empty()) {
      const NodeId id = *hasBoundsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeIntersectionExpression_HasBounds);
      hasBoundsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::TypeExpression::prepareDelete(false);
  }

  NodeKind TypeIntersectionExpression::getNodeKind() const {
    return ndkTypeIntersectionExpression;
  }

  ListIterator<expr::TypeExpression> TypeIntersectionExpression::getBoundsListIteratorBegin() const {
    return ListIterator<expr::TypeExpression>(&hasBoundsContainer, factory, true);
  }

  ListIterator<expr::TypeExpression> TypeIntersectionExpression::getBoundsListIteratorEnd() const {
    return ListIterator<expr::TypeExpression>(&hasBoundsContainer, factory, false);
  }

  bool TypeIntersectionExpression::getBoundsIsEmpty() const {
    return getBoundsListIteratorBegin() == getBoundsListIteratorEnd();
  }

  unsigned int TypeIntersectionExpression::getBoundsSize() const {
    unsigned int size = 0;
    ListIterator<expr::TypeExpression> endIt = getBoundsListIteratorEnd();
    for (ListIterator<expr::TypeExpression> it = getBoundsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TypeIntersectionExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeIntersectionExpression_HasBounds:
        addBounds(edgeEnd);
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

  bool TypeIntersectionExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeIntersectionExpression_HasBounds:
        removeBounds(edgeEnd);
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

  void TypeIntersectionExpression::addBounds(const expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasBoundsContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeIntersectionExpression_HasBounds);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeIntersectionExpression_HasBounds);
  }

  void TypeIntersectionExpression::addBounds(NodeId _id) {
    const expr::TypeExpression *node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addBounds( node );
  }

  void TypeIntersectionExpression::removeBounds(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::TypeExpression>::Container::iterator it = find(hasBoundsContainer.begin(), hasBoundsContainer.end(), id);

    if (it == hasBoundsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasBoundsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeIntersectionExpression_HasBounds);
  }

  void TypeIntersectionExpression::removeBounds(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeBounds(_node->getId());
  }

  void TypeIntersectionExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeIntersectionExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeIntersectionExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const TypeIntersectionExpression& node = dynamic_cast<const TypeIntersectionExpression&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void TypeIntersectionExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TypeIntersectionExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::TypeIntersectionExpression", strlen("expr::TypeIntersectionExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeIntersectionExpression::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    TypeExpression::sort(false);
  }

  void TypeIntersectionExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    TypeExpression::save(binIo,false);


    for (ListIterator<expr::TypeExpression>::Container::const_iterator it = hasBoundsContainer.begin(); it != hasBoundsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeIntersectionExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    TypeExpression::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasBoundsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeIntersectionExpression_HasBounds);
      _id = binIo.readUInt4();
    }
  }


}


}}}
