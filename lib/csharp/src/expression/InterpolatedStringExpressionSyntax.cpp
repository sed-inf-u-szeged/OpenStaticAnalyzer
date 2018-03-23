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

namespace expression { 
  InterpolatedStringExpressionSyntax::InterpolatedStringExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    ContentsContainer()
  {
  }

  InterpolatedStringExpressionSyntax::~InterpolatedStringExpressionSyntax() {
  }

  void InterpolatedStringExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ContentsContainer.empty()) {
      const NodeId id = *ContentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkInterpolatedStringExpressionSyntax_Contents);
      ContentsContainer.pop_front();
    }
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind InterpolatedStringExpressionSyntax::getNodeKind() const {
    return ndkInterpolatedStringExpressionSyntax;
  }

  ListIterator<structure::InterpolatedStringContentSyntax> InterpolatedStringExpressionSyntax::getContentsListIteratorBegin() const {
    return ListIterator<structure::InterpolatedStringContentSyntax>(&ContentsContainer, factory, true);
  }

  ListIterator<structure::InterpolatedStringContentSyntax> InterpolatedStringExpressionSyntax::getContentsListIteratorEnd() const {
    return ListIterator<structure::InterpolatedStringContentSyntax>(&ContentsContainer, factory, false);
  }

  bool InterpolatedStringExpressionSyntax::getContentsIsEmpty() const {
    return getContentsListIteratorBegin() == getContentsListIteratorEnd();
  }

  unsigned int InterpolatedStringExpressionSyntax::getContentsSize() const {
    unsigned int size = 0;
    ListIterator<structure::InterpolatedStringContentSyntax> endIt = getContentsListIteratorEnd();
    for (ListIterator<structure::InterpolatedStringContentSyntax> it = getContentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool InterpolatedStringExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInterpolatedStringExpressionSyntax_Contents:
        addContents(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool InterpolatedStringExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInterpolatedStringExpressionSyntax_Contents:
        removeContents(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void InterpolatedStringExpressionSyntax::addContents(const structure::InterpolatedStringContentSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsInterpolatedStringContentSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ContentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkInterpolatedStringExpressionSyntax_Contents);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkInterpolatedStringExpressionSyntax_Contents);
  }

  void InterpolatedStringExpressionSyntax::addContents(NodeId _id) {
    const structure::InterpolatedStringContentSyntax *node = dynamic_cast<structure::InterpolatedStringContentSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addContents( node );
  }

  void InterpolatedStringExpressionSyntax::removeContents(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::InterpolatedStringContentSyntax>::Container::iterator it = find(ContentsContainer.begin(), ContentsContainer.end(), id);

    if (it == ContentsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ContentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkInterpolatedStringExpressionSyntax_Contents);
  }

  void InterpolatedStringExpressionSyntax::removeContents(structure::InterpolatedStringContentSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeContents(_node->getId());
  }

  void InterpolatedStringExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void InterpolatedStringExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double InterpolatedStringExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void InterpolatedStringExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType InterpolatedStringExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::InterpolatedStringExpressionSyntax", strlen("expression::InterpolatedStringExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void InterpolatedStringExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);


    for (ListIterator<structure::InterpolatedStringContentSyntax>::Container::const_iterator it = ContentsContainer.begin(); it != ContentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void InterpolatedStringExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ContentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkInterpolatedStringExpressionSyntax_Contents);
      _id = binIo.readUInt4();
    }
  }


}


}}}
