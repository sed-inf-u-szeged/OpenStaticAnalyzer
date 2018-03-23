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
  SwitchSectionSyntax::SwitchSectionSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    LabelsContainer(),
    StatementsContainer()
  {
  }

  SwitchSectionSyntax::~SwitchSectionSyntax() {
  }

  void SwitchSectionSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!LabelsContainer.empty()) {
      const NodeId id = *LabelsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchSectionSyntax_Labels);
      LabelsContainer.pop_front();
    }
    while (!StatementsContainer.empty()) {
      const NodeId id = *StatementsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchSectionSyntax_Statements);
      StatementsContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind SwitchSectionSyntax::getNodeKind() const {
    return ndkSwitchSectionSyntax;
  }

  ListIterator<structure::SwitchLabelSyntax> SwitchSectionSyntax::getLabelsListIteratorBegin() const {
    return ListIterator<structure::SwitchLabelSyntax>(&LabelsContainer, factory, true);
  }

  ListIterator<structure::SwitchLabelSyntax> SwitchSectionSyntax::getLabelsListIteratorEnd() const {
    return ListIterator<structure::SwitchLabelSyntax>(&LabelsContainer, factory, false);
  }

  bool SwitchSectionSyntax::getLabelsIsEmpty() const {
    return getLabelsListIteratorBegin() == getLabelsListIteratorEnd();
  }

  unsigned int SwitchSectionSyntax::getLabelsSize() const {
    unsigned int size = 0;
    ListIterator<structure::SwitchLabelSyntax> endIt = getLabelsListIteratorEnd();
    for (ListIterator<structure::SwitchLabelSyntax> it = getLabelsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<statement::StatementSyntax> SwitchSectionSyntax::getStatementsListIteratorBegin() const {
    return ListIterator<statement::StatementSyntax>(&StatementsContainer, factory, true);
  }

  ListIterator<statement::StatementSyntax> SwitchSectionSyntax::getStatementsListIteratorEnd() const {
    return ListIterator<statement::StatementSyntax>(&StatementsContainer, factory, false);
  }

  bool SwitchSectionSyntax::getStatementsIsEmpty() const {
    return getStatementsListIteratorBegin() == getStatementsListIteratorEnd();
  }

  unsigned int SwitchSectionSyntax::getStatementsSize() const {
    unsigned int size = 0;
    ListIterator<statement::StatementSyntax> endIt = getStatementsListIteratorEnd();
    for (ListIterator<statement::StatementSyntax> it = getStatementsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool SwitchSectionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchSectionSyntax_Labels:
        addLabels(edgeEnd);
        return true;
      case edkSwitchSectionSyntax_Statements:
        addStatements(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SwitchSectionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchSectionSyntax_Labels:
        removeLabels(edgeEnd);
        return true;
      case edkSwitchSectionSyntax_Statements:
        removeStatements(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SwitchSectionSyntax::addLabels(const structure::SwitchLabelSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsSwitchLabelSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    LabelsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchSectionSyntax_Labels);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchSectionSyntax_Labels);
  }

  void SwitchSectionSyntax::addLabels(NodeId _id) {
    const structure::SwitchLabelSyntax *node = dynamic_cast<structure::SwitchLabelSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addLabels( node );
  }

  void SwitchSectionSyntax::removeLabels(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::SwitchLabelSyntax>::Container::iterator it = find(LabelsContainer.begin(), LabelsContainer.end(), id);

    if (it == LabelsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    LabelsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchSectionSyntax_Labels);
  }

  void SwitchSectionSyntax::removeLabels(structure::SwitchLabelSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeLabels(_node->getId());
  }

  void SwitchSectionSyntax::addStatements(const statement::StatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatementSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    StatementsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchSectionSyntax_Statements);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchSectionSyntax_Statements);
  }

  void SwitchSectionSyntax::addStatements(NodeId _id) {
    const statement::StatementSyntax *node = dynamic_cast<statement::StatementSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addStatements( node );
  }

  void SwitchSectionSyntax::removeStatements(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::StatementSyntax>::Container::iterator it = find(StatementsContainer.begin(), StatementsContainer.end(), id);

    if (it == StatementsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    StatementsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchSectionSyntax_Statements);
  }

  void SwitchSectionSyntax::removeStatements(statement::StatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeStatements(_node->getId());
  }

  void SwitchSectionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SwitchSectionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SwitchSectionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void SwitchSectionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType SwitchSectionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::SwitchSectionSyntax", strlen("structure::SwitchSectionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchSectionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::SwitchLabelSyntax>::Container::const_iterator it = LabelsContainer.begin(); it != LabelsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<statement::StatementSyntax>::Container::const_iterator it = StatementsContainer.begin(); it != StatementsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchSectionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      LabelsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchSectionSyntax_Labels);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      StatementsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchSectionSyntax_Statements);
      _id = binIo.readUInt4();
    }
  }


}


}}}
