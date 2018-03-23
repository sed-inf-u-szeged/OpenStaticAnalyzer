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

namespace statement { 
  SwitchStatementSyntax::SwitchStatementSyntax(NodeId _id, Factory *_factory) :
    StatementSyntax(_id, _factory),
    m_Expression(0),
    SectionsContainer()
  {
  }

  SwitchStatementSyntax::~SwitchStatementSyntax() {
  }

  void SwitchStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeExpression();
    while (!SectionsContainer.empty()) {
      const NodeId id = *SectionsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatementSyntax_Sections);
      SectionsContainer.pop_front();
    }
    statement::StatementSyntax::prepareDelete(false);
  }

  NodeKind SwitchStatementSyntax::getNodeKind() const {
    return ndkSwitchStatementSyntax;
  }

  expression::ExpressionSyntax* SwitchStatementSyntax::getExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Expression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Expression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::SwitchSectionSyntax> SwitchStatementSyntax::getSectionsListIteratorBegin() const {
    return ListIterator<structure::SwitchSectionSyntax>(&SectionsContainer, factory, true);
  }

  ListIterator<structure::SwitchSectionSyntax> SwitchStatementSyntax::getSectionsListIteratorEnd() const {
    return ListIterator<structure::SwitchSectionSyntax>(&SectionsContainer, factory, false);
  }

  bool SwitchStatementSyntax::getSectionsIsEmpty() const {
    return getSectionsListIteratorBegin() == getSectionsListIteratorEnd();
  }

  unsigned int SwitchStatementSyntax::getSectionsSize() const {
    unsigned int size = 0;
    ListIterator<structure::SwitchSectionSyntax> endIt = getSectionsListIteratorEnd();
    for (ListIterator<structure::SwitchSectionSyntax> it = getSectionsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool SwitchStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatementSyntax_Expression:
        setExpression(edgeEnd);
        return true;
      case edkSwitchStatementSyntax_Sections:
        addSections(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SwitchStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatementSyntax_Expression:
        removeExpression();
        return true;
      case edkSwitchStatementSyntax_Sections:
        removeSections(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::StatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SwitchStatementSyntax::setExpression(NodeId _id) {
    expression::ExpressionSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ExpressionSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkSwitchStatementSyntax_Expression);
      }
      m_Expression = _node->getId();
      if (m_Expression != 0)
        setParentEdge(factory->getPointer(m_Expression), edkSwitchStatementSyntax_Expression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Expression, this->getId(), edkSwitchStatementSyntax_Expression);
    } else {
      if (m_Expression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void SwitchStatementSyntax::setExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void SwitchStatementSyntax::removeExpression() {
      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkSwitchStatementSyntax_Expression);
      }
      m_Expression = 0;
  }

  void SwitchStatementSyntax::addSections(const structure::SwitchSectionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkSwitchSectionSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    SectionsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchStatementSyntax_Sections);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchStatementSyntax_Sections);
  }

  void SwitchStatementSyntax::addSections(NodeId _id) {
    const structure::SwitchSectionSyntax *node = dynamic_cast<structure::SwitchSectionSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSections( node );
  }

  void SwitchStatementSyntax::removeSections(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::SwitchSectionSyntax>::Container::iterator it = find(SectionsContainer.begin(), SectionsContainer.end(), id);

    if (it == SectionsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    SectionsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatementSyntax_Sections);
  }

  void SwitchStatementSyntax::removeSections(structure::SwitchSectionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSections(_node->getId());
  }

  void SwitchStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SwitchStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SwitchStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void SwitchStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType SwitchStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::SwitchStatementSyntax", strlen("statement::SwitchStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StatementSyntax::save(binIo,false);

    binIo.writeUInt4(m_Expression);


    for (ListIterator<structure::SwitchSectionSyntax>::Container::const_iterator it = SectionsContainer.begin(); it != SectionsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StatementSyntax::load(binIo,false);

    m_Expression =  binIo.readUInt4();
    if (m_Expression != 0)
      setParentEdge(factory->getPointer(m_Expression),edkSwitchStatementSyntax_Expression);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      SectionsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchStatementSyntax_Sections);
      _id = binIo.readUInt4();
    }
  }


}


}}}
