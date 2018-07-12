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
  VariableDeclarationSyntax::VariableDeclarationSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_Type(0),
    VariablesContainer()
  {
  }

  VariableDeclarationSyntax::~VariableDeclarationSyntax() {
  }

  void VariableDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    removeType();
    while (!VariablesContainer.empty()) {
      const NodeId id = *VariablesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkVariableDeclarationSyntax_Variables);
      VariablesContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind VariableDeclarationSyntax::getNodeKind() const {
    return ndkVariableDeclarationSyntax;
  }

  expression::TypeSyntax* VariableDeclarationSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::VariableDeclaratorSyntax> VariableDeclarationSyntax::getVariablesListIteratorBegin() const {
    return ListIterator<structure::VariableDeclaratorSyntax>(&VariablesContainer, factory, true);
  }

  ListIterator<structure::VariableDeclaratorSyntax> VariableDeclarationSyntax::getVariablesListIteratorEnd() const {
    return ListIterator<structure::VariableDeclaratorSyntax>(&VariablesContainer, factory, false);
  }

  bool VariableDeclarationSyntax::getVariablesIsEmpty() const {
    return getVariablesListIteratorBegin() == getVariablesListIteratorEnd();
  }

  unsigned int VariableDeclarationSyntax::getVariablesSize() const {
    unsigned int size = 0;
    ListIterator<structure::VariableDeclaratorSyntax> endIt = getVariablesListIteratorEnd();
    for (ListIterator<structure::VariableDeclaratorSyntax> it = getVariablesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool VariableDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclarationSyntax_Type:
        setType(edgeEnd);
        return true;
      case edkVariableDeclarationSyntax_Variables:
        addVariables(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool VariableDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclarationSyntax_Type:
        removeType();
        return true;
      case edkVariableDeclarationSyntax_Variables:
        removeVariables(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void VariableDeclarationSyntax::setType(NodeId _id) {
    expression::TypeSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::TypeSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkVariableDeclarationSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkVariableDeclarationSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkVariableDeclarationSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void VariableDeclarationSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void VariableDeclarationSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkVariableDeclarationSyntax_Type);
      }
      m_Type = 0;
  }

  void VariableDeclarationSyntax::addVariables(const structure::VariableDeclaratorSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkVariableDeclaratorSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    VariablesContainer.push_back(_node->getId());
    setParentEdge(_node,edkVariableDeclarationSyntax_Variables);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkVariableDeclarationSyntax_Variables);
  }

  void VariableDeclarationSyntax::addVariables(NodeId _id) {
    const structure::VariableDeclaratorSyntax *node = dynamic_cast<structure::VariableDeclaratorSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addVariables( node );
  }

  void VariableDeclarationSyntax::removeVariables(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::VariableDeclaratorSyntax>::Container::iterator it = find(VariablesContainer.begin(), VariablesContainer.end(), id);

    if (it == VariablesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    VariablesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkVariableDeclarationSyntax_Variables);
  }

  void VariableDeclarationSyntax::removeVariables(structure::VariableDeclaratorSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeVariables(_node->getId());
  }

  void VariableDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void VariableDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double VariableDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void VariableDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType VariableDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::VariableDeclarationSyntax", strlen("structure::VariableDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void VariableDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Type);


    for (ListIterator<structure::VariableDeclaratorSyntax>::Container::const_iterator it = VariablesContainer.begin(); it != VariablesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void VariableDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkVariableDeclarationSyntax_Type);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      VariablesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkVariableDeclarationSyntax_Variables);
      _id = binIo.readUInt4();
    }
  }


}


}}}
