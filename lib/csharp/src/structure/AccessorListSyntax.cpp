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
  AccessorListSyntax::AccessorListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    AccessorsContainer()
  {
  }

  AccessorListSyntax::~AccessorListSyntax() {
  }

  void AccessorListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AccessorsContainer.empty()) {
      const NodeId id = *AccessorsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAccessorListSyntax_Accessors);
      AccessorsContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind AccessorListSyntax::getNodeKind() const {
    return ndkAccessorListSyntax;
  }

  ListIterator<structure::AccessorDeclarationSyntax> AccessorListSyntax::getAccessorsListIteratorBegin() const {
    return ListIterator<structure::AccessorDeclarationSyntax>(&AccessorsContainer, factory, true);
  }

  ListIterator<structure::AccessorDeclarationSyntax> AccessorListSyntax::getAccessorsListIteratorEnd() const {
    return ListIterator<structure::AccessorDeclarationSyntax>(&AccessorsContainer, factory, false);
  }

  bool AccessorListSyntax::getAccessorsIsEmpty() const {
    return getAccessorsListIteratorBegin() == getAccessorsListIteratorEnd();
  }

  unsigned int AccessorListSyntax::getAccessorsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AccessorDeclarationSyntax> endIt = getAccessorsListIteratorEnd();
    for (ListIterator<structure::AccessorDeclarationSyntax> it = getAccessorsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool AccessorListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAccessorListSyntax_Accessors:
        addAccessors(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AccessorListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAccessorListSyntax_Accessors:
        removeAccessors(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AccessorListSyntax::addAccessors(const structure::AccessorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAccessorDeclarationSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AccessorsContainer.push_back(_node->getId());
    setParentEdge(_node,edkAccessorListSyntax_Accessors);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAccessorListSyntax_Accessors);
  }

  void AccessorListSyntax::addAccessors(NodeId _id) {
    const structure::AccessorDeclarationSyntax *node = dynamic_cast<structure::AccessorDeclarationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAccessors( node );
  }

  void AccessorListSyntax::removeAccessors(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AccessorDeclarationSyntax>::Container::iterator it = find(AccessorsContainer.begin(), AccessorsContainer.end(), id);

    if (it == AccessorsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AccessorsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAccessorListSyntax_Accessors);
  }

  void AccessorListSyntax::removeAccessors(structure::AccessorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAccessors(_node->getId());
  }

  void AccessorListSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AccessorListSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AccessorListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AccessorListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType AccessorListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::AccessorListSyntax", strlen("structure::AccessorListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AccessorListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::AccessorDeclarationSyntax>::Container::const_iterator it = AccessorsContainer.begin(); it != AccessorsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void AccessorListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AccessorsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkAccessorListSyntax_Accessors);
      _id = binIo.readUInt4();
    }
  }


}


}}}
