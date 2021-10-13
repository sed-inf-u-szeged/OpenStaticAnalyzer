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

namespace statement { 
  ForEachVariableStatementSyntax::ForEachVariableStatementSyntax(NodeId _id, Factory *_factory) :
    CommonForEachStatementSyntax(_id, _factory),
    m_Variable(0)
  {
  }

  ForEachVariableStatementSyntax::~ForEachVariableStatementSyntax() {
  }

  void ForEachVariableStatementSyntax::prepareDelete(bool tryOnVirtualParent){
    removeVariable();
    statement::CommonForEachStatementSyntax::prepareDelete(false);
  }

  NodeKind ForEachVariableStatementSyntax::getNodeKind() const {
    return ndkForEachVariableStatementSyntax;
  }

  expression::ExpressionSyntax* ForEachVariableStatementSyntax::getVariable() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Variable != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Variable));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ForEachVariableStatementSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForEachVariableStatementSyntax_Variable:
        setVariable(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::CommonForEachStatementSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ForEachVariableStatementSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForEachVariableStatementSyntax_Variable:
        removeVariable();
        return true;
      default:
        break;
    }
    if (statement::CommonForEachStatementSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ForEachVariableStatementSyntax::setVariable(NodeId _id) {
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

      if (m_Variable) {
        removeParentEdge(m_Variable);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Variable, m_id, edkForEachVariableStatementSyntax_Variable);
      }
      m_Variable = _node->getId();
      if (m_Variable != 0)
        setParentEdge(factory->getPointer(m_Variable), edkForEachVariableStatementSyntax_Variable);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Variable, this->getId(), edkForEachVariableStatementSyntax_Variable);
    } else {
      if (m_Variable) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForEachVariableStatementSyntax::setVariable(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setVariable(_node->getId());
  }

  void ForEachVariableStatementSyntax::removeVariable() {
      if (m_Variable) {
        removeParentEdge(m_Variable);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Variable, m_id, edkForEachVariableStatementSyntax_Variable);
      }
      m_Variable = 0;
  }

  void ForEachVariableStatementSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ForEachVariableStatementSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ForEachVariableStatementSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ForEachVariableStatementSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ForEachVariableStatementSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ForEachVariableStatementSyntax", strlen("statement::ForEachVariableStatementSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ForEachVariableStatementSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CommonForEachStatementSyntax::save(binIo,false);

    binIo.writeUInt4(m_Variable);

  }

  void ForEachVariableStatementSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CommonForEachStatementSyntax::load(binIo,false);

    m_Variable =  binIo.readUInt4();
    if (m_Variable != 0)
      setParentEdge(factory->getPointer(m_Variable),edkForEachVariableStatementSyntax_Variable);

  }


}


}}}
