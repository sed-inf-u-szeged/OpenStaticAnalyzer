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
  SimpleLambdaExpressionSyntax::SimpleLambdaExpressionSyntax(NodeId _id, Factory *_factory) :
    LambdaExpressionSyntax(_id, _factory),
    m_Parameter(0)
  {
  }

  SimpleLambdaExpressionSyntax::~SimpleLambdaExpressionSyntax() {
  }

  void SimpleLambdaExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeParameter();
    expression::LambdaExpressionSyntax::prepareDelete(false);
  }

  NodeKind SimpleLambdaExpressionSyntax::getNodeKind() const {
    return ndkSimpleLambdaExpressionSyntax;
  }

  structure::ParameterSyntax* SimpleLambdaExpressionSyntax::getParameter() const {
    structure::ParameterSyntax *_node = NULL;
    if (m_Parameter != 0)
      _node = dynamic_cast<structure::ParameterSyntax*>(factory->getPointer(m_Parameter));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool SimpleLambdaExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSimpleLambdaExpressionSyntax_Parameter:
        setParameter(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::LambdaExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool SimpleLambdaExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSimpleLambdaExpressionSyntax_Parameter:
        removeParameter();
        return true;
      default:
        break;
    }
    if (expression::LambdaExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SimpleLambdaExpressionSyntax::setParameter(NodeId _id) {
    structure::ParameterSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ParameterSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Parameter) {
        removeParentEdge(m_Parameter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Parameter, m_id, edkSimpleLambdaExpressionSyntax_Parameter);
      }
      m_Parameter = _node->getId();
      if (m_Parameter != 0)
        setParentEdge(factory->getPointer(m_Parameter), edkSimpleLambdaExpressionSyntax_Parameter);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Parameter, this->getId(), edkSimpleLambdaExpressionSyntax_Parameter);
    } else {
      if (m_Parameter) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void SimpleLambdaExpressionSyntax::setParameter(structure::ParameterSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameter(_node->getId());
  }

  void SimpleLambdaExpressionSyntax::removeParameter() {
      if (m_Parameter) {
        removeParentEdge(m_Parameter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Parameter, m_id, edkSimpleLambdaExpressionSyntax_Parameter);
      }
      m_Parameter = 0;
  }

  void SimpleLambdaExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SimpleLambdaExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SimpleLambdaExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const SimpleLambdaExpressionSyntax& node = dynamic_cast<const SimpleLambdaExpressionSyntax&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getIdentifier();
      str2 = node.getIdentifier();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void SimpleLambdaExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_identifier);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_identifier = foundKeyId->second;
    } else {
      Key oldkey = m_identifier;
      m_identifier = newStrTable.set(factory->getStringTable().get(m_identifier));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_identifier));    }

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType SimpleLambdaExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::SimpleLambdaExpressionSyntax", strlen("expression::SimpleLambdaExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SimpleLambdaExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    LambdaExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_Parameter);

  }

  void SimpleLambdaExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    LambdaExpressionSyntax::load(binIo,false);

    m_Parameter =  binIo.readUInt4();
    if (m_Parameter != 0)
      setParentEdge(factory->getPointer(m_Parameter),edkSimpleLambdaExpressionSyntax_Parameter);

  }


}


}}}
