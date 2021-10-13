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
  CasePatternSwitchLabelSyntax::CasePatternSwitchLabelSyntax(NodeId _id, Factory *_factory) :
    SwitchLabelSyntax(_id, _factory),
    m_Pattern(0),
    m_WhenClause(0)
  {
  }

  CasePatternSwitchLabelSyntax::~CasePatternSwitchLabelSyntax() {
  }

  void CasePatternSwitchLabelSyntax::prepareDelete(bool tryOnVirtualParent){
    removePattern();
    removeWhenClause();
    structure::SwitchLabelSyntax::prepareDelete(false);
  }

  NodeKind CasePatternSwitchLabelSyntax::getNodeKind() const {
    return ndkCasePatternSwitchLabelSyntax;
  }

  structure::PatternSyntax* CasePatternSwitchLabelSyntax::getPattern() const {
    structure::PatternSyntax *_node = NULL;
    if (m_Pattern != 0)
      _node = dynamic_cast<structure::PatternSyntax*>(factory->getPointer(m_Pattern));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::WhenClauseSyntax* CasePatternSwitchLabelSyntax::getWhenClause() const {
    structure::WhenClauseSyntax *_node = NULL;
    if (m_WhenClause != 0)
      _node = dynamic_cast<structure::WhenClauseSyntax*>(factory->getPointer(m_WhenClause));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool CasePatternSwitchLabelSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCasePatternSwitchLabelSyntax_Pattern:
        setPattern(edgeEnd);
        return true;
      case edkCasePatternSwitchLabelSyntax_WhenClause:
        setWhenClause(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::SwitchLabelSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CasePatternSwitchLabelSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCasePatternSwitchLabelSyntax_Pattern:
        removePattern();
        return true;
      case edkCasePatternSwitchLabelSyntax_WhenClause:
        removeWhenClause();
        return true;
      default:
        break;
    }
    if (structure::SwitchLabelSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CasePatternSwitchLabelSyntax::setPattern(NodeId _id) {
    structure::PatternSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::PatternSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Pattern) {
        removeParentEdge(m_Pattern);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Pattern, m_id, edkCasePatternSwitchLabelSyntax_Pattern);
      }
      m_Pattern = _node->getId();
      if (m_Pattern != 0)
        setParentEdge(factory->getPointer(m_Pattern), edkCasePatternSwitchLabelSyntax_Pattern);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Pattern, this->getId(), edkCasePatternSwitchLabelSyntax_Pattern);
    } else {
      if (m_Pattern) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CasePatternSwitchLabelSyntax::setPattern(structure::PatternSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPattern(_node->getId());
  }

  void CasePatternSwitchLabelSyntax::removePattern() {
      if (m_Pattern) {
        removeParentEdge(m_Pattern);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Pattern, m_id, edkCasePatternSwitchLabelSyntax_Pattern);
      }
      m_Pattern = 0;
  }

  void CasePatternSwitchLabelSyntax::setWhenClause(NodeId _id) {
    structure::WhenClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::WhenClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_WhenClause) {
        removeParentEdge(m_WhenClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_WhenClause, m_id, edkCasePatternSwitchLabelSyntax_WhenClause);
      }
      m_WhenClause = _node->getId();
      if (m_WhenClause != 0)
        setParentEdge(factory->getPointer(m_WhenClause), edkCasePatternSwitchLabelSyntax_WhenClause);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_WhenClause, this->getId(), edkCasePatternSwitchLabelSyntax_WhenClause);
    } else {
      if (m_WhenClause) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CasePatternSwitchLabelSyntax::setWhenClause(structure::WhenClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setWhenClause(_node->getId());
  }

  void CasePatternSwitchLabelSyntax::removeWhenClause() {
      if (m_WhenClause) {
        removeParentEdge(m_WhenClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_WhenClause, m_id, edkCasePatternSwitchLabelSyntax_WhenClause);
      }
      m_WhenClause = 0;
  }

  void CasePatternSwitchLabelSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CasePatternSwitchLabelSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CasePatternSwitchLabelSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void CasePatternSwitchLabelSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType CasePatternSwitchLabelSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::CasePatternSwitchLabelSyntax", strlen("structure::CasePatternSwitchLabelSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CasePatternSwitchLabelSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SwitchLabelSyntax::save(binIo,false);

    binIo.writeUInt4(m_Pattern);
    binIo.writeUInt4(m_WhenClause);

  }

  void CasePatternSwitchLabelSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SwitchLabelSyntax::load(binIo,false);

    m_Pattern =  binIo.readUInt4();
    if (m_Pattern != 0)
      setParentEdge(factory->getPointer(m_Pattern),edkCasePatternSwitchLabelSyntax_Pattern);

    m_WhenClause =  binIo.readUInt4();
    if (m_WhenClause != 0)
      setParentEdge(factory->getPointer(m_WhenClause),edkCasePatternSwitchLabelSyntax_WhenClause);

  }


}


}}}
