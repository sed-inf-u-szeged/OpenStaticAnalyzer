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

#include "csharp/inc/csharp.h"
#include "csharp/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "csharp/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace csharp { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace structure { 
  BaseListSyntax::BaseListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    TypesContainer()
  {
  }

  BaseListSyntax::~BaseListSyntax() {
  }

  void BaseListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!TypesContainer.empty()) {
      const NodeId id = *TypesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBaseListSyntax_Types);
      TypesContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind BaseListSyntax::getNodeKind() const {
    return ndkBaseListSyntax;
  }

  ListIterator<structure::BaseTypeSyntax> BaseListSyntax::getTypesListIteratorBegin() const {
    return ListIterator<structure::BaseTypeSyntax>(&TypesContainer, factory, true);
  }

  ListIterator<structure::BaseTypeSyntax> BaseListSyntax::getTypesListIteratorEnd() const {
    return ListIterator<structure::BaseTypeSyntax>(&TypesContainer, factory, false);
  }

  bool BaseListSyntax::getTypesIsEmpty() const {
    return getTypesListIteratorBegin() == getTypesListIteratorEnd();
  }

  unsigned int BaseListSyntax::getTypesSize() const {
    unsigned int size = 0;
    ListIterator<structure::BaseTypeSyntax> endIt = getTypesListIteratorEnd();
    for (ListIterator<structure::BaseTypeSyntax> it = getTypesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool BaseListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseListSyntax_Types:
        addTypes(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BaseListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseListSyntax_Types:
        removeTypes(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BaseListSyntax::addTypes(const structure::BaseTypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsBaseTypeSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    TypesContainer.push_back(_node->getId());
    setParentEdge(_node,edkBaseListSyntax_Types);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBaseListSyntax_Types);
  }

  void BaseListSyntax::addTypes(NodeId _id) {
    const structure::BaseTypeSyntax *node = dynamic_cast<structure::BaseTypeSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypes( node );
  }

  void BaseListSyntax::removeTypes(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::BaseTypeSyntax>::Container::iterator it = find(TypesContainer.begin(), TypesContainer.end(), id);

    if (it == TypesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    TypesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBaseListSyntax_Types);
  }

  void BaseListSyntax::removeTypes(structure::BaseTypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypes(_node->getId());
  }

  void BaseListSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BaseListSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BaseListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BaseListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType BaseListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::BaseListSyntax", strlen("structure::BaseListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BaseListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::BaseTypeSyntax>::Container::const_iterator it = TypesContainer.begin(); it != TypesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BaseListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      TypesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBaseListSyntax_Types);
      _id = binIo.readUInt4();
    }
  }


}


}}}
