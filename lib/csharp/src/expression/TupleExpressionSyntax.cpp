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

namespace expression { 
  TupleExpressionSyntax::TupleExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    ArgumentsContainer()
  {
  }

  TupleExpressionSyntax::~TupleExpressionSyntax() {
  }

  void TupleExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ArgumentsContainer.empty()) {
      const NodeId id = *ArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTupleExpressionSyntax_Arguments);
      ArgumentsContainer.pop_front();
    }
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind TupleExpressionSyntax::getNodeKind() const {
    return ndkTupleExpressionSyntax;
  }

  ListIterator<structure::ArgumentSyntax> TupleExpressionSyntax::getArgumentsListIteratorBegin() const {
    return ListIterator<structure::ArgumentSyntax>(&ArgumentsContainer, factory, true);
  }

  ListIterator<structure::ArgumentSyntax> TupleExpressionSyntax::getArgumentsListIteratorEnd() const {
    return ListIterator<structure::ArgumentSyntax>(&ArgumentsContainer, factory, false);
  }

  bool TupleExpressionSyntax::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int TupleExpressionSyntax::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<structure::ArgumentSyntax> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<structure::ArgumentSyntax> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TupleExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTupleExpressionSyntax_Arguments:
        addArguments(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TupleExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTupleExpressionSyntax_Arguments:
        removeArguments(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TupleExpressionSyntax::addArguments(const structure::ArgumentSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkArgumentSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkTupleExpressionSyntax_Arguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTupleExpressionSyntax_Arguments);
  }

  void TupleExpressionSyntax::addArguments(NodeId _id) {
    const structure::ArgumentSyntax *node = dynamic_cast<structure::ArgumentSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void TupleExpressionSyntax::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::ArgumentSyntax>::Container::iterator it = find(ArgumentsContainer.begin(), ArgumentsContainer.end(), id);

    if (it == ArgumentsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTupleExpressionSyntax_Arguments);
  }

  void TupleExpressionSyntax::removeArguments(structure::ArgumentSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void TupleExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TupleExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TupleExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TupleExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType TupleExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::TupleExpressionSyntax", strlen("expression::TupleExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TupleExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);


    for (ListIterator<structure::ArgumentSyntax>::Container::const_iterator it = ArgumentsContainer.begin(); it != ArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TupleExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTupleExpressionSyntax_Arguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
