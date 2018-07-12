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
  InitializerExpressionSyntax::InitializerExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    ExpressionsContainer()
  {
  }

  InitializerExpressionSyntax::~InitializerExpressionSyntax() {
  }

  void InitializerExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ExpressionsContainer.empty()) {
      const NodeId id = *ExpressionsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkInitializerExpressionSyntax_Expressions);
      ExpressionsContainer.pop_front();
    }
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind InitializerExpressionSyntax::getNodeKind() const {
    return ndkInitializerExpressionSyntax;
  }

  ListIterator<expression::ExpressionSyntax> InitializerExpressionSyntax::getExpressionsListIteratorBegin() const {
    return ListIterator<expression::ExpressionSyntax>(&ExpressionsContainer, factory, true);
  }

  ListIterator<expression::ExpressionSyntax> InitializerExpressionSyntax::getExpressionsListIteratorEnd() const {
    return ListIterator<expression::ExpressionSyntax>(&ExpressionsContainer, factory, false);
  }

  bool InitializerExpressionSyntax::getExpressionsIsEmpty() const {
    return getExpressionsListIteratorBegin() == getExpressionsListIteratorEnd();
  }

  unsigned int InitializerExpressionSyntax::getExpressionsSize() const {
    unsigned int size = 0;
    ListIterator<expression::ExpressionSyntax> endIt = getExpressionsListIteratorEnd();
    for (ListIterator<expression::ExpressionSyntax> it = getExpressionsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool InitializerExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInitializerExpressionSyntax_Expressions:
        addExpressions(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool InitializerExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInitializerExpressionSyntax_Expressions:
        removeExpressions(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void InitializerExpressionSyntax::addExpressions(const expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpressionSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ExpressionsContainer.push_back(_node->getId());
    setParentEdge(_node,edkInitializerExpressionSyntax_Expressions);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkInitializerExpressionSyntax_Expressions);
  }

  void InitializerExpressionSyntax::addExpressions(NodeId _id) {
    const expression::ExpressionSyntax *node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addExpressions( node );
  }

  void InitializerExpressionSyntax::removeExpressions(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::ExpressionSyntax>::Container::iterator it = find(ExpressionsContainer.begin(), ExpressionsContainer.end(), id);

    if (it == ExpressionsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ExpressionsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkInitializerExpressionSyntax_Expressions);
  }

  void InitializerExpressionSyntax::removeExpressions(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeExpressions(_node->getId());
  }

  void InitializerExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void InitializerExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double InitializerExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void InitializerExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType InitializerExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::InitializerExpressionSyntax", strlen("expression::InitializerExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void InitializerExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);


    for (ListIterator<expression::ExpressionSyntax>::Container::const_iterator it = ExpressionsContainer.begin(); it != ExpressionsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void InitializerExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ExpressionsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkInitializerExpressionSyntax_Expressions);
      _id = binIo.readUInt4();
    }
  }


}


}}}
