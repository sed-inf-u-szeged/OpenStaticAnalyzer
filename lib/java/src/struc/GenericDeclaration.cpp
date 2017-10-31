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
  GenericDeclaration::GenericDeclaration(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    hasTypeParametersContainer()
  {
  }

  GenericDeclaration::~GenericDeclaration() {
  }

  void GenericDeclaration::clone(const GenericDeclaration& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }

    hasTypeParametersContainer = other.hasTypeParametersContainer;
  }

  void GenericDeclaration::prepareDelete(bool tryOnVirtualParent){
    while (!hasTypeParametersContainer.empty()) {
      const NodeId id = *hasTypeParametersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkGenericDeclaration_HasTypeParameters);
      hasTypeParametersContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
  }

  ListIterator<struc::TypeParameter> GenericDeclaration::getTypeParametersListIteratorBegin() const {
    return ListIterator<struc::TypeParameter>(&hasTypeParametersContainer, factory, true);
  }

  ListIterator<struc::TypeParameter> GenericDeclaration::getTypeParametersListIteratorEnd() const {
    return ListIterator<struc::TypeParameter>(&hasTypeParametersContainer, factory, false);
  }

  bool GenericDeclaration::getTypeParametersIsEmpty() const {
    return getTypeParametersListIteratorBegin() == getTypeParametersListIteratorEnd();
  }

  unsigned int GenericDeclaration::getTypeParametersSize() const {
    unsigned int size = 0;
    ListIterator<struc::TypeParameter> endIt = getTypeParametersListIteratorEnd();
    for (ListIterator<struc::TypeParameter> it = getTypeParametersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool GenericDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenericDeclaration_HasTypeParameters:
        addTypeParameters(edgeEnd);
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

  bool GenericDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenericDeclaration_HasTypeParameters:
        removeTypeParameters(edgeEnd);
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

  void GenericDeclaration::addTypeParameters(const struc::TypeParameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTypeParameter) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeParametersContainer.push_back(_node->getId());
    setParentEdge(_node,edkGenericDeclaration_HasTypeParameters);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkGenericDeclaration_HasTypeParameters);
  }

  void GenericDeclaration::addTypeParameters(NodeId _id) {
    const struc::TypeParameter *node = dynamic_cast<struc::TypeParameter*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypeParameters( node );
  }

  void GenericDeclaration::removeTypeParameters(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::TypeParameter>::Container::iterator it = find(hasTypeParametersContainer.begin(), hasTypeParametersContainer.end(), id);

    if (it == hasTypeParametersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeParametersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkGenericDeclaration_HasTypeParameters);
  }

  void GenericDeclaration::removeTypeParameters(struc::TypeParameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypeParameters(_node->getId());
  }

  double GenericDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void GenericDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType GenericDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::GenericDeclaration", strlen("struc::GenericDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void GenericDeclaration::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
  }

  void GenericDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);


    for (ListIterator<struc::TypeParameter>::Container::const_iterator it = hasTypeParametersContainer.begin(); it != hasTypeParametersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void GenericDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeParametersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkGenericDeclaration_HasTypeParameters);
      _id = binIo.readUInt4();
    }
  }


}


}}}
