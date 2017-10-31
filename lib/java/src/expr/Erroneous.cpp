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
  Erroneous::Erroneous(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Expression(_id, _factory),
    hasErrorsContainer()
  {
  }

  Erroneous::~Erroneous() {
  }

  void Erroneous::clone(const Erroneous& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Expression::clone(other, false);

    hasErrorsContainer = other.hasErrorsContainer;
  }

  void Erroneous::prepareDelete(bool tryOnVirtualParent){
    while (!hasErrorsContainer.empty()) {
      const NodeId id = *hasErrorsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkErroneous_HasErrors);
      hasErrorsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Expression::prepareDelete(false);
  }

  NodeKind Erroneous::getNodeKind() const {
    return ndkErroneous;
  }

  ListIterator<base::Positioned> Erroneous::getErrorsListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasErrorsContainer, factory, true);
  }

  ListIterator<base::Positioned> Erroneous::getErrorsListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasErrorsContainer, factory, false);
  }

  bool Erroneous::getErrorsIsEmpty() const {
    return getErrorsListIteratorBegin() == getErrorsListIteratorEnd();
  }

  unsigned int Erroneous::getErrorsSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getErrorsListIteratorEnd();
    for (ListIterator<base::Positioned> it = getErrorsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Erroneous::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkErroneous_HasErrors:
        addErrors(edgeEnd);
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

  bool Erroneous::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkErroneous_HasErrors:
        removeErrors(edgeEnd);
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

  void Erroneous::addErrors(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsPositioned(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasErrorsContainer.push_back(_node->getId());
    setParentEdge(_node,edkErroneous_HasErrors);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkErroneous_HasErrors);
  }

  void Erroneous::addErrors(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addErrors( node );
  }

  void Erroneous::removeErrors(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasErrorsContainer.begin(), hasErrorsContainer.end(), id);

    if (it == hasErrorsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasErrorsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkErroneous_HasErrors);
  }

  void Erroneous::removeErrors(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeErrors(_node->getId());
  }

  void Erroneous::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Erroneous::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Erroneous::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Erroneous& node = dynamic_cast<const Erroneous&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Erroneous::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Erroneous::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::Erroneous", strlen("expr::Erroneous"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Erroneous::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Expression::sort(false);
  }

  void Erroneous::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Expression::save(binIo,false);


    for (ListIterator<base::Positioned>::Container::const_iterator it = hasErrorsContainer.begin(); it != hasErrorsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Erroneous::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Expression::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasErrorsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkErroneous_HasErrors);
      _id = binIo.readUInt4();
    }
  }


}


}}}
