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
  IndexerMemberCrefSyntax::IndexerMemberCrefSyntax(NodeId _id, Factory *_factory) :
    MemberCrefSyntax(_id, _factory),
    m_Parameters(0)
  {
  }

  IndexerMemberCrefSyntax::~IndexerMemberCrefSyntax() {
  }

  void IndexerMemberCrefSyntax::prepareDelete(bool tryOnVirtualParent){
    removeParameters();
    structure::MemberCrefSyntax::prepareDelete(false);
  }

  NodeKind IndexerMemberCrefSyntax::getNodeKind() const {
    return ndkIndexerMemberCrefSyntax;
  }

  structure::CrefBracketedParameterListSyntax* IndexerMemberCrefSyntax::getParameters() const {
    structure::CrefBracketedParameterListSyntax *_node = NULL;
    if (m_Parameters != 0)
      _node = dynamic_cast<structure::CrefBracketedParameterListSyntax*>(factory->getPointer(m_Parameters));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool IndexerMemberCrefSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIndexerMemberCrefSyntax_Parameters:
        setParameters(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberCrefSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool IndexerMemberCrefSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIndexerMemberCrefSyntax_Parameters:
        removeParameters();
        return true;
      default:
        break;
    }
    if (structure::MemberCrefSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void IndexerMemberCrefSyntax::setParameters(NodeId _id) {
    structure::CrefBracketedParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::CrefBracketedParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Parameters) {
        removeParentEdge(m_Parameters);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Parameters, m_id, edkIndexerMemberCrefSyntax_Parameters);
      }
      m_Parameters = _node->getId();
      if (m_Parameters != 0)
        setParentEdge(factory->getPointer(m_Parameters), edkIndexerMemberCrefSyntax_Parameters);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Parameters, this->getId(), edkIndexerMemberCrefSyntax_Parameters);
    } else {
      if (m_Parameters) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IndexerMemberCrefSyntax::setParameters(structure::CrefBracketedParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameters(_node->getId());
  }

  void IndexerMemberCrefSyntax::removeParameters() {
      if (m_Parameters) {
        removeParentEdge(m_Parameters);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Parameters, m_id, edkIndexerMemberCrefSyntax_Parameters);
      }
      m_Parameters = 0;
  }

  void IndexerMemberCrefSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void IndexerMemberCrefSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double IndexerMemberCrefSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void IndexerMemberCrefSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType IndexerMemberCrefSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::IndexerMemberCrefSyntax", strlen("structure::IndexerMemberCrefSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void IndexerMemberCrefSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberCrefSyntax::save(binIo,false);

    binIo.writeUInt4(m_Parameters);

  }

  void IndexerMemberCrefSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberCrefSyntax::load(binIo,false);

    m_Parameters =  binIo.readUInt4();
    if (m_Parameters != 0)
      setParentEdge(factory->getPointer(m_Parameters),edkIndexerMemberCrefSyntax_Parameters);

  }


}


}}}
