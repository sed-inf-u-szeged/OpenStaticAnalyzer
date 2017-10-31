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

namespace struc { 
  AnnotatedElement::AnnotatedElement(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    hasAnnotationsContainer()
  {
  }

  AnnotatedElement::~AnnotatedElement() {
  }

  void AnnotatedElement::clone(const AnnotatedElement& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }

    hasAnnotationsContainer = other.hasAnnotationsContainer;
  }

  void AnnotatedElement::prepareDelete(bool tryOnVirtualParent){
    while (!hasAnnotationsContainer.empty()) {
      const NodeId id = *hasAnnotationsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAnnotatedElement_HasAnnotations);
      hasAnnotationsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
  }

  ListIterator<expr::Annotation> AnnotatedElement::getAnnotationsListIteratorBegin() const {
    return ListIterator<expr::Annotation>(&hasAnnotationsContainer, factory, true);
  }

  ListIterator<expr::Annotation> AnnotatedElement::getAnnotationsListIteratorEnd() const {
    return ListIterator<expr::Annotation>(&hasAnnotationsContainer, factory, false);
  }

  bool AnnotatedElement::getAnnotationsIsEmpty() const {
    return getAnnotationsListIteratorBegin() == getAnnotationsListIteratorEnd();
  }

  unsigned int AnnotatedElement::getAnnotationsSize() const {
    unsigned int size = 0;
    ListIterator<expr::Annotation> endIt = getAnnotationsListIteratorEnd();
    for (ListIterator<expr::Annotation> it = getAnnotationsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool AnnotatedElement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnotatedElement_HasAnnotations:
        addAnnotations(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool AnnotatedElement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnotatedElement_HasAnnotations:
        removeAnnotations(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  void AnnotatedElement::addAnnotations(const expr::Annotation *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsAnnotation(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasAnnotationsContainer.push_back(_node->getId());
    setParentEdge(_node,edkAnnotatedElement_HasAnnotations);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAnnotatedElement_HasAnnotations);
  }

  void AnnotatedElement::addAnnotations(NodeId _id) {
    const expr::Annotation *node = dynamic_cast<expr::Annotation*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAnnotations( node );
  }

  void AnnotatedElement::removeAnnotations(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Annotation>::Container::iterator it = find(hasAnnotationsContainer.begin(), hasAnnotationsContainer.end(), id);

    if (it == hasAnnotationsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasAnnotationsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAnnotatedElement_HasAnnotations);
  }

  void AnnotatedElement::removeAnnotations(expr::Annotation *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAnnotations(_node->getId());
  }

  double AnnotatedElement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AnnotatedElement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType AnnotatedElement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::AnnotatedElement", strlen("struc::AnnotatedElement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnnotatedElement::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
  }

  void AnnotatedElement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);


    for (ListIterator<expr::Annotation>::Container::const_iterator it = hasAnnotationsContainer.begin(); it != hasAnnotationsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void AnnotatedElement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasAnnotationsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkAnnotatedElement_HasAnnotations);
      _id = binIo.readUInt4();
    }
  }


}


}}}
