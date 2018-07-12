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
  TypeParameterConstraintClauseSyntax::TypeParameterConstraintClauseSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    ConstraintsContainer(),
    m_Name(0)
  {
  }

  TypeParameterConstraintClauseSyntax::~TypeParameterConstraintClauseSyntax() {
  }

  void TypeParameterConstraintClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ConstraintsContainer.empty()) {
      const NodeId id = *ConstraintsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeParameterConstraintClauseSyntax_Constraints);
      ConstraintsContainer.pop_front();
    }
    removeName();
    base::Positioned::prepareDelete(false);
  }

  NodeKind TypeParameterConstraintClauseSyntax::getNodeKind() const {
    return ndkTypeParameterConstraintClauseSyntax;
  }

  ListIterator<structure::TypeParameterConstraintSyntax> TypeParameterConstraintClauseSyntax::getConstraintsListIteratorBegin() const {
    return ListIterator<structure::TypeParameterConstraintSyntax>(&ConstraintsContainer, factory, true);
  }

  ListIterator<structure::TypeParameterConstraintSyntax> TypeParameterConstraintClauseSyntax::getConstraintsListIteratorEnd() const {
    return ListIterator<structure::TypeParameterConstraintSyntax>(&ConstraintsContainer, factory, false);
  }

  bool TypeParameterConstraintClauseSyntax::getConstraintsIsEmpty() const {
    return getConstraintsListIteratorBegin() == getConstraintsListIteratorEnd();
  }

  unsigned int TypeParameterConstraintClauseSyntax::getConstraintsSize() const {
    unsigned int size = 0;
    ListIterator<structure::TypeParameterConstraintSyntax> endIt = getConstraintsListIteratorEnd();
    for (ListIterator<structure::TypeParameterConstraintSyntax> it = getConstraintsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::IdentifierNameSyntax* TypeParameterConstraintClauseSyntax::getName() const {
    expression::IdentifierNameSyntax *_node = NULL;
    if (m_Name != 0)
      _node = dynamic_cast<expression::IdentifierNameSyntax*>(factory->getPointer(m_Name));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TypeParameterConstraintClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeParameterConstraintClauseSyntax_Constraints:
        addConstraints(edgeEnd);
        return true;
      case edkTypeParameterConstraintClauseSyntax_Name:
        setName(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TypeParameterConstraintClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeParameterConstraintClauseSyntax_Constraints:
        removeConstraints(edgeEnd);
        return true;
      case edkTypeParameterConstraintClauseSyntax_Name:
        removeName();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeParameterConstraintClauseSyntax::addConstraints(const structure::TypeParameterConstraintSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeParameterConstraintSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ConstraintsContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeParameterConstraintClauseSyntax_Constraints);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeParameterConstraintClauseSyntax_Constraints);
  }

  void TypeParameterConstraintClauseSyntax::addConstraints(NodeId _id) {
    const structure::TypeParameterConstraintSyntax *node = dynamic_cast<structure::TypeParameterConstraintSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addConstraints( node );
  }

  void TypeParameterConstraintClauseSyntax::removeConstraints(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::TypeParameterConstraintSyntax>::Container::iterator it = find(ConstraintsContainer.begin(), ConstraintsContainer.end(), id);

    if (it == ConstraintsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ConstraintsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeParameterConstraintClauseSyntax_Constraints);
  }

  void TypeParameterConstraintClauseSyntax::removeConstraints(structure::TypeParameterConstraintSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeConstraints(_node->getId());
  }

  void TypeParameterConstraintClauseSyntax::setName(NodeId _id) {
    expression::IdentifierNameSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::IdentifierNameSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkTypeParameterConstraintClauseSyntax_Name);
      }
      m_Name = _node->getId();
      if (m_Name != 0)
        setParentEdge(factory->getPointer(m_Name), edkTypeParameterConstraintClauseSyntax_Name);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Name, this->getId(), edkTypeParameterConstraintClauseSyntax_Name);
    } else {
      if (m_Name) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeParameterConstraintClauseSyntax::setName(expression::IdentifierNameSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void TypeParameterConstraintClauseSyntax::removeName() {
      if (m_Name) {
        removeParentEdge(m_Name);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Name, m_id, edkTypeParameterConstraintClauseSyntax_Name);
      }
      m_Name = 0;
  }

  void TypeParameterConstraintClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeParameterConstraintClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeParameterConstraintClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TypeParameterConstraintClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType TypeParameterConstraintClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::TypeParameterConstraintClauseSyntax", strlen("structure::TypeParameterConstraintClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeParameterConstraintClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Name);


    for (ListIterator<structure::TypeParameterConstraintSyntax>::Container::const_iterator it = ConstraintsContainer.begin(); it != ConstraintsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeParameterConstraintClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Name =  binIo.readUInt4();
    if (m_Name != 0)
      setParentEdge(factory->getPointer(m_Name),edkTypeParameterConstraintClauseSyntax_Name);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ConstraintsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeParameterConstraintClauseSyntax_Constraints);
      _id = binIo.readUInt4();
    }
  }


}


}}}
