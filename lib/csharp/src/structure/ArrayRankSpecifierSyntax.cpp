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
  ArrayRankSpecifierSyntax::ArrayRankSpecifierSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    SizesContainer()
  {
  }

  ArrayRankSpecifierSyntax::~ArrayRankSpecifierSyntax() {
  }

  void ArrayRankSpecifierSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!SizesContainer.empty()) {
      const NodeId id = *SizesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkArrayRankSpecifierSyntax_Sizes);
      SizesContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind ArrayRankSpecifierSyntax::getNodeKind() const {
    return ndkArrayRankSpecifierSyntax;
  }

  ListIterator<expression::ExpressionSyntax> ArrayRankSpecifierSyntax::getSizesListIteratorBegin() const {
    return ListIterator<expression::ExpressionSyntax>(&SizesContainer, factory, true);
  }

  ListIterator<expression::ExpressionSyntax> ArrayRankSpecifierSyntax::getSizesListIteratorEnd() const {
    return ListIterator<expression::ExpressionSyntax>(&SizesContainer, factory, false);
  }

  bool ArrayRankSpecifierSyntax::getSizesIsEmpty() const {
    return getSizesListIteratorBegin() == getSizesListIteratorEnd();
  }

  unsigned int ArrayRankSpecifierSyntax::getSizesSize() const {
    unsigned int size = 0;
    ListIterator<expression::ExpressionSyntax> endIt = getSizesListIteratorEnd();
    for (ListIterator<expression::ExpressionSyntax> it = getSizesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ArrayRankSpecifierSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayRankSpecifierSyntax_Sizes:
        addSizes(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ArrayRankSpecifierSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayRankSpecifierSyntax_Sizes:
        removeSizes(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ArrayRankSpecifierSyntax::addSizes(const expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpressionSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    SizesContainer.push_back(_node->getId());
    setParentEdge(_node,edkArrayRankSpecifierSyntax_Sizes);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkArrayRankSpecifierSyntax_Sizes);
  }

  void ArrayRankSpecifierSyntax::addSizes(NodeId _id) {
    const expression::ExpressionSyntax *node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSizes( node );
  }

  void ArrayRankSpecifierSyntax::removeSizes(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::ExpressionSyntax>::Container::iterator it = find(SizesContainer.begin(), SizesContainer.end(), id);

    if (it == SizesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    SizesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkArrayRankSpecifierSyntax_Sizes);
  }

  void ArrayRankSpecifierSyntax::removeSizes(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSizes(_node->getId());
  }

  void ArrayRankSpecifierSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ArrayRankSpecifierSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ArrayRankSpecifierSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ArrayRankSpecifierSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ArrayRankSpecifierSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ArrayRankSpecifierSyntax", strlen("structure::ArrayRankSpecifierSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ArrayRankSpecifierSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<expression::ExpressionSyntax>::Container::const_iterator it = SizesContainer.begin(); it != SizesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ArrayRankSpecifierSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      SizesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkArrayRankSpecifierSyntax_Sizes);
      _id = binIo.readUInt4();
    }
  }


}


}}}
