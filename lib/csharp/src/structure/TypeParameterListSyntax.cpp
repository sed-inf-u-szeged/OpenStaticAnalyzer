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
  TypeParameterListSyntax::TypeParameterListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    ParametersContainer()
  {
  }

  TypeParameterListSyntax::~TypeParameterListSyntax() {
  }

  void TypeParameterListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ParametersContainer.empty()) {
      const NodeId id = *ParametersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeParameterListSyntax_Parameters);
      ParametersContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind TypeParameterListSyntax::getNodeKind() const {
    return ndkTypeParameterListSyntax;
  }

  ListIterator<structure::TypeParameterSyntax> TypeParameterListSyntax::getParametersListIteratorBegin() const {
    return ListIterator<structure::TypeParameterSyntax>(&ParametersContainer, factory, true);
  }

  ListIterator<structure::TypeParameterSyntax> TypeParameterListSyntax::getParametersListIteratorEnd() const {
    return ListIterator<structure::TypeParameterSyntax>(&ParametersContainer, factory, false);
  }

  bool TypeParameterListSyntax::getParametersIsEmpty() const {
    return getParametersListIteratorBegin() == getParametersListIteratorEnd();
  }

  unsigned int TypeParameterListSyntax::getParametersSize() const {
    unsigned int size = 0;
    ListIterator<structure::TypeParameterSyntax> endIt = getParametersListIteratorEnd();
    for (ListIterator<structure::TypeParameterSyntax> it = getParametersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TypeParameterListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeParameterListSyntax_Parameters:
        addParameters(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TypeParameterListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeParameterListSyntax_Parameters:
        removeParameters(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeParameterListSyntax::addParameters(const structure::TypeParameterSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTypeParameterSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ParametersContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeParameterListSyntax_Parameters);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeParameterListSyntax_Parameters);
  }

  void TypeParameterListSyntax::addParameters(NodeId _id) {
    const structure::TypeParameterSyntax *node = dynamic_cast<structure::TypeParameterSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameters( node );
  }

  void TypeParameterListSyntax::removeParameters(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::TypeParameterSyntax>::Container::iterator it = find(ParametersContainer.begin(), ParametersContainer.end(), id);

    if (it == ParametersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ParametersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeParameterListSyntax_Parameters);
  }

  void TypeParameterListSyntax::removeParameters(structure::TypeParameterSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameters(_node->getId());
  }

  void TypeParameterListSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeParameterListSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeParameterListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TypeParameterListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType TypeParameterListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::TypeParameterListSyntax", strlen("structure::TypeParameterListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeParameterListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::TypeParameterSyntax>::Container::const_iterator it = ParametersContainer.begin(); it != ParametersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeParameterListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ParametersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeParameterListSyntax_Parameters);
      _id = binIo.readUInt4();
    }
  }


}


}}}
