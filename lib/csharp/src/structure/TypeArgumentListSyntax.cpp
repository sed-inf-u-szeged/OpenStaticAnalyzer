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
  TypeArgumentListSyntax::TypeArgumentListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    ArgumentsContainer()
  {
  }

  TypeArgumentListSyntax::~TypeArgumentListSyntax() {
  }

  void TypeArgumentListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ArgumentsContainer.empty()) {
      const NodeId id = *ArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeArgumentListSyntax_Arguments);
      ArgumentsContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind TypeArgumentListSyntax::getNodeKind() const {
    return ndkTypeArgumentListSyntax;
  }

  ListIterator<expression::TypeSyntax> TypeArgumentListSyntax::getArgumentsListIteratorBegin() const {
    return ListIterator<expression::TypeSyntax>(&ArgumentsContainer, factory, true);
  }

  ListIterator<expression::TypeSyntax> TypeArgumentListSyntax::getArgumentsListIteratorEnd() const {
    return ListIterator<expression::TypeSyntax>(&ArgumentsContainer, factory, false);
  }

  bool TypeArgumentListSyntax::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int TypeArgumentListSyntax::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expression::TypeSyntax> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<expression::TypeSyntax> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TypeArgumentListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeArgumentListSyntax_Arguments:
        addArguments(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TypeArgumentListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeArgumentListSyntax_Arguments:
        removeArguments(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeArgumentListSyntax::addArguments(const expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeArgumentListSyntax_Arguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeArgumentListSyntax_Arguments);
  }

  void TypeArgumentListSyntax::addArguments(NodeId _id) {
    const expression::TypeSyntax *node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void TypeArgumentListSyntax::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::TypeSyntax>::Container::iterator it = find(ArgumentsContainer.begin(), ArgumentsContainer.end(), id);

    if (it == ArgumentsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeArgumentListSyntax_Arguments);
  }

  void TypeArgumentListSyntax::removeArguments(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void TypeArgumentListSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeArgumentListSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeArgumentListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TypeArgumentListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType TypeArgumentListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::TypeArgumentListSyntax", strlen("structure::TypeArgumentListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeArgumentListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<expression::TypeSyntax>::Container::const_iterator it = ArgumentsContainer.begin(); it != ArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeArgumentListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeArgumentListSyntax_Arguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
