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
  AttributeArgumentListSyntax::AttributeArgumentListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    ArgumentsContainer()
  {
  }

  AttributeArgumentListSyntax::~AttributeArgumentListSyntax() {
  }

  void AttributeArgumentListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ArgumentsContainer.empty()) {
      const NodeId id = *ArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAttributeArgumentListSyntax_Arguments);
      ArgumentsContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind AttributeArgumentListSyntax::getNodeKind() const {
    return ndkAttributeArgumentListSyntax;
  }

  ListIterator<structure::AttributeArgumentSyntax> AttributeArgumentListSyntax::getArgumentsListIteratorBegin() const {
    return ListIterator<structure::AttributeArgumentSyntax>(&ArgumentsContainer, factory, true);
  }

  ListIterator<structure::AttributeArgumentSyntax> AttributeArgumentListSyntax::getArgumentsListIteratorEnd() const {
    return ListIterator<structure::AttributeArgumentSyntax>(&ArgumentsContainer, factory, false);
  }

  bool AttributeArgumentListSyntax::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int AttributeArgumentListSyntax::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeArgumentSyntax> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<structure::AttributeArgumentSyntax> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool AttributeArgumentListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeArgumentListSyntax_Arguments:
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

  bool AttributeArgumentListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeArgumentListSyntax_Arguments:
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

  void AttributeArgumentListSyntax::addArguments(const structure::AttributeArgumentSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeArgumentSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkAttributeArgumentListSyntax_Arguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAttributeArgumentListSyntax_Arguments);
  }

  void AttributeArgumentListSyntax::addArguments(NodeId _id) {
    const structure::AttributeArgumentSyntax *node = dynamic_cast<structure::AttributeArgumentSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void AttributeArgumentListSyntax::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeArgumentSyntax>::Container::iterator it = find(ArgumentsContainer.begin(), ArgumentsContainer.end(), id);

    if (it == ArgumentsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAttributeArgumentListSyntax_Arguments);
  }

  void AttributeArgumentListSyntax::removeArguments(structure::AttributeArgumentSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void AttributeArgumentListSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AttributeArgumentListSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AttributeArgumentListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AttributeArgumentListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType AttributeArgumentListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::AttributeArgumentListSyntax", strlen("structure::AttributeArgumentListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AttributeArgumentListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::AttributeArgumentSyntax>::Container::const_iterator it = ArgumentsContainer.begin(); it != ArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void AttributeArgumentListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkAttributeArgumentListSyntax_Arguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
