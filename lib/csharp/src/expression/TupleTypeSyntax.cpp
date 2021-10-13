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
  TupleTypeSyntax::TupleTypeSyntax(NodeId _id, Factory *_factory) :
    TypeSyntax(_id, _factory),
    ElementsContainer()
  {
  }

  TupleTypeSyntax::~TupleTypeSyntax() {
  }

  void TupleTypeSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ElementsContainer.empty()) {
      const NodeId id = *ElementsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTupleTypeSyntax_Elements);
      ElementsContainer.pop_front();
    }
    expression::TypeSyntax::prepareDelete(false);
  }

  NodeKind TupleTypeSyntax::getNodeKind() const {
    return ndkTupleTypeSyntax;
  }

  ListIterator<structure::TupleElementSyntax> TupleTypeSyntax::getElementsListIteratorBegin() const {
    return ListIterator<structure::TupleElementSyntax>(&ElementsContainer, factory, true);
  }

  ListIterator<structure::TupleElementSyntax> TupleTypeSyntax::getElementsListIteratorEnd() const {
    return ListIterator<structure::TupleElementSyntax>(&ElementsContainer, factory, false);
  }

  bool TupleTypeSyntax::getElementsIsEmpty() const {
    return getElementsListIteratorBegin() == getElementsListIteratorEnd();
  }

  unsigned int TupleTypeSyntax::getElementsSize() const {
    unsigned int size = 0;
    ListIterator<structure::TupleElementSyntax> endIt = getElementsListIteratorEnd();
    for (ListIterator<structure::TupleElementSyntax> it = getElementsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TupleTypeSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTupleTypeSyntax_Elements:
        addElements(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::TypeSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TupleTypeSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTupleTypeSyntax_Elements:
        removeElements(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::TypeSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TupleTypeSyntax::addElements(const structure::TupleElementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTupleElementSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ElementsContainer.push_back(_node->getId());
    setParentEdge(_node,edkTupleTypeSyntax_Elements);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTupleTypeSyntax_Elements);
  }

  void TupleTypeSyntax::addElements(NodeId _id) {
    const structure::TupleElementSyntax *node = dynamic_cast<structure::TupleElementSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addElements( node );
  }

  void TupleTypeSyntax::removeElements(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::TupleElementSyntax>::Container::iterator it = find(ElementsContainer.begin(), ElementsContainer.end(), id);

    if (it == ElementsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ElementsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTupleTypeSyntax_Elements);
  }

  void TupleTypeSyntax::removeElements(structure::TupleElementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeElements(_node->getId());
  }

  void TupleTypeSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TupleTypeSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TupleTypeSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TupleTypeSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType TupleTypeSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::TupleTypeSyntax", strlen("expression::TupleTypeSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TupleTypeSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    TypeSyntax::save(binIo,false);


    for (ListIterator<structure::TupleElementSyntax>::Container::const_iterator it = ElementsContainer.begin(); it != ElementsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TupleTypeSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    TypeSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ElementsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTupleTypeSyntax_Elements);
      _id = binIo.readUInt4();
    }
  }


}


}}}
