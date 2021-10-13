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
  SwitchExpressionSyntax::SwitchExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    ArmsContainer(),
    m_GoverningExpression(0)
  {
  }

  SwitchExpressionSyntax::~SwitchExpressionSyntax() {
  }

  void SwitchExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ArmsContainer.empty()) {
      const NodeId id = *ArmsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchExpressionSyntax_Arms);
      ArmsContainer.pop_front();
    }
    removeGoverningExpression();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind SwitchExpressionSyntax::getNodeKind() const {
    return ndkSwitchExpressionSyntax;
  }

  ListIterator<structure::SwitchExpressionArmSyntax> SwitchExpressionSyntax::getArmsListIteratorBegin() const {
    return ListIterator<structure::SwitchExpressionArmSyntax>(&ArmsContainer, factory, true);
  }

  ListIterator<structure::SwitchExpressionArmSyntax> SwitchExpressionSyntax::getArmsListIteratorEnd() const {
    return ListIterator<structure::SwitchExpressionArmSyntax>(&ArmsContainer, factory, false);
  }

  bool SwitchExpressionSyntax::getArmsIsEmpty() const {
    return getArmsListIteratorBegin() == getArmsListIteratorEnd();
  }

  unsigned int SwitchExpressionSyntax::getArmsSize() const {
    unsigned int size = 0;
    ListIterator<structure::SwitchExpressionArmSyntax> endIt = getArmsListIteratorEnd();
    for (ListIterator<structure::SwitchExpressionArmSyntax> it = getArmsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::ExpressionSyntax* SwitchExpressionSyntax::getGoverningExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_GoverningExpression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_GoverningExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool SwitchExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchExpressionSyntax_Arms:
        addArms(edgeEnd);
        return true;
      case edkSwitchExpressionSyntax_GoverningExpression:
        setGoverningExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SwitchExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchExpressionSyntax_Arms:
        removeArms(edgeEnd);
        return true;
      case edkSwitchExpressionSyntax_GoverningExpression:
        removeGoverningExpression();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SwitchExpressionSyntax::addArms(const structure::SwitchExpressionArmSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkSwitchExpressionArmSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ArmsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchExpressionSyntax_Arms);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchExpressionSyntax_Arms);
  }

  void SwitchExpressionSyntax::addArms(NodeId _id) {
    const structure::SwitchExpressionArmSyntax *node = dynamic_cast<structure::SwitchExpressionArmSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArms( node );
  }

  void SwitchExpressionSyntax::removeArms(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::SwitchExpressionArmSyntax>::Container::iterator it = find(ArmsContainer.begin(), ArmsContainer.end(), id);

    if (it == ArmsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ArmsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchExpressionSyntax_Arms);
  }

  void SwitchExpressionSyntax::removeArms(structure::SwitchExpressionArmSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArms(_node->getId());
  }

  void SwitchExpressionSyntax::setGoverningExpression(NodeId _id) {
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

      if (m_GoverningExpression) {
        removeParentEdge(m_GoverningExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_GoverningExpression, m_id, edkSwitchExpressionSyntax_GoverningExpression);
      }
      m_GoverningExpression = _node->getId();
      if (m_GoverningExpression != 0)
        setParentEdge(factory->getPointer(m_GoverningExpression), edkSwitchExpressionSyntax_GoverningExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_GoverningExpression, this->getId(), edkSwitchExpressionSyntax_GoverningExpression);
    } else {
      if (m_GoverningExpression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void SwitchExpressionSyntax::setGoverningExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setGoverningExpression(_node->getId());
  }

  void SwitchExpressionSyntax::removeGoverningExpression() {
      if (m_GoverningExpression) {
        removeParentEdge(m_GoverningExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_GoverningExpression, m_id, edkSwitchExpressionSyntax_GoverningExpression);
      }
      m_GoverningExpression = 0;
  }

  void SwitchExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SwitchExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SwitchExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void SwitchExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType SwitchExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::SwitchExpressionSyntax", strlen("expression::SwitchExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_GoverningExpression);


    for (ListIterator<structure::SwitchExpressionArmSyntax>::Container::const_iterator it = ArmsContainer.begin(); it != ArmsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_GoverningExpression =  binIo.readUInt4();
    if (m_GoverningExpression != 0)
      setParentEdge(factory->getPointer(m_GoverningExpression),edkSwitchExpressionSyntax_GoverningExpression);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ArmsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchExpressionSyntax_Arms);
      _id = binIo.readUInt4();
    }
  }


}


}}}
