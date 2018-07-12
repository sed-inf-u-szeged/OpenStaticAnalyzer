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
  NormalAnnotation::NormalAnnotation(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Annotation(_id, _factory),
    hasArgumentsContainer()
  {
  }

  NormalAnnotation::~NormalAnnotation() {
  }

  void NormalAnnotation::clone(const NormalAnnotation& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Annotation::clone(other, false);

    hasArgumentsContainer = other.hasArgumentsContainer;
  }

  void NormalAnnotation::prepareDelete(bool tryOnVirtualParent){
    while (!hasArgumentsContainer.empty()) {
      const NodeId id = *hasArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNormalAnnotation_HasArguments);
      hasArgumentsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Annotation::prepareDelete(false);
  }

  NodeKind NormalAnnotation::getNodeKind() const {
    return ndkNormalAnnotation;
  }

  ListIterator<expr::Expression> NormalAnnotation::getArgumentsListIteratorBegin() const {
    return ListIterator<expr::Expression>(&hasArgumentsContainer, factory, true);
  }

  ListIterator<expr::Expression> NormalAnnotation::getArgumentsListIteratorEnd() const {
    return ListIterator<expr::Expression>(&hasArgumentsContainer, factory, false);
  }

  bool NormalAnnotation::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int NormalAnnotation::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expr::Expression> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<expr::Expression> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool NormalAnnotation::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNormalAnnotation_HasArguments:
        addArguments(edgeEnd);
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
    if (expr::Annotation::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NormalAnnotation::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNormalAnnotation_HasArguments:
        removeArguments(edgeEnd);
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
    if (expr::Annotation::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NormalAnnotation::addArguments(const expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNormalAnnotation_HasArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNormalAnnotation_HasArguments);
  }

  void NormalAnnotation::addArguments(NodeId _id) {
    const expr::Expression *node = dynamic_cast<expr::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void NormalAnnotation::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Expression>::Container::iterator it = find(hasArgumentsContainer.begin(), hasArgumentsContainer.end(), id);

    if (it == hasArgumentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNormalAnnotation_HasArguments);
  }

  void NormalAnnotation::removeArguments(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void NormalAnnotation::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NormalAnnotation::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NormalAnnotation::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const NormalAnnotation& node = dynamic_cast<const NormalAnnotation&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void NormalAnnotation::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType NormalAnnotation::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::NormalAnnotation", strlen("expr::NormalAnnotation"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NormalAnnotation::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Annotation::sort(false);
  }

  void NormalAnnotation::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Annotation::save(binIo,false);


    for (ListIterator<expr::Expression>::Container::const_iterator it = hasArgumentsContainer.begin(); it != hasArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void NormalAnnotation::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Annotation::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNormalAnnotation_HasArguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
