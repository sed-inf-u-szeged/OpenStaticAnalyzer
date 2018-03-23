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
  InterpolationSyntax::InterpolationSyntax(NodeId _id, Factory *_factory) :
    InterpolatedStringContentSyntax(_id, _factory),
    m_AlignmentClause(0),
    m_Expression(0),
    m_FormatClause(0)
  {
  }

  InterpolationSyntax::~InterpolationSyntax() {
  }

  void InterpolationSyntax::prepareDelete(bool tryOnVirtualParent){
    removeAlignmentClause();
    removeExpression();
    removeFormatClause();
    structure::InterpolatedStringContentSyntax::prepareDelete(false);
  }

  NodeKind InterpolationSyntax::getNodeKind() const {
    return ndkInterpolationSyntax;
  }

  structure::InterpolationAlignmentClauseSyntax* InterpolationSyntax::getAlignmentClause() const {
    structure::InterpolationAlignmentClauseSyntax *_node = NULL;
    if (m_AlignmentClause != 0)
      _node = dynamic_cast<structure::InterpolationAlignmentClauseSyntax*>(factory->getPointer(m_AlignmentClause));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* InterpolationSyntax::getExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Expression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Expression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::InterpolationFormatClauseSyntax* InterpolationSyntax::getFormatClause() const {
    structure::InterpolationFormatClauseSyntax *_node = NULL;
    if (m_FormatClause != 0)
      _node = dynamic_cast<structure::InterpolationFormatClauseSyntax*>(factory->getPointer(m_FormatClause));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool InterpolationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInterpolationSyntax_AlignmentClause:
        setAlignmentClause(edgeEnd);
        return true;
      case edkInterpolationSyntax_Expression:
        setExpression(edgeEnd);
        return true;
      case edkInterpolationSyntax_FormatClause:
        setFormatClause(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::InterpolatedStringContentSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool InterpolationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInterpolationSyntax_AlignmentClause:
        removeAlignmentClause();
        return true;
      case edkInterpolationSyntax_Expression:
        removeExpression();
        return true;
      case edkInterpolationSyntax_FormatClause:
        removeFormatClause();
        return true;
      default:
        break;
    }
    if (structure::InterpolatedStringContentSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void InterpolationSyntax::setAlignmentClause(NodeId _id) {
    structure::InterpolationAlignmentClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::InterpolationAlignmentClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_AlignmentClause) {
        removeParentEdge(m_AlignmentClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_AlignmentClause, m_id, edkInterpolationSyntax_AlignmentClause);
      }
      m_AlignmentClause = _node->getId();
      if (m_AlignmentClause != 0)
        setParentEdge(factory->getPointer(m_AlignmentClause), edkInterpolationSyntax_AlignmentClause);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_AlignmentClause, this->getId(), edkInterpolationSyntax_AlignmentClause);
    } else {
      if (m_AlignmentClause) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void InterpolationSyntax::setAlignmentClause(structure::InterpolationAlignmentClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAlignmentClause(_node->getId());
  }

  void InterpolationSyntax::removeAlignmentClause() {
      if (m_AlignmentClause) {
        removeParentEdge(m_AlignmentClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_AlignmentClause, m_id, edkInterpolationSyntax_AlignmentClause);
      }
      m_AlignmentClause = 0;
  }

  void InterpolationSyntax::setExpression(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkInterpolationSyntax_Expression);
      }
      m_Expression = _node->getId();
      if (m_Expression != 0)
        setParentEdge(factory->getPointer(m_Expression), edkInterpolationSyntax_Expression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Expression, this->getId(), edkInterpolationSyntax_Expression);
    } else {
      if (m_Expression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void InterpolationSyntax::setExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void InterpolationSyntax::removeExpression() {
      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkInterpolationSyntax_Expression);
      }
      m_Expression = 0;
  }

  void InterpolationSyntax::setFormatClause(NodeId _id) {
    structure::InterpolationFormatClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::InterpolationFormatClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_FormatClause) {
        removeParentEdge(m_FormatClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_FormatClause, m_id, edkInterpolationSyntax_FormatClause);
      }
      m_FormatClause = _node->getId();
      if (m_FormatClause != 0)
        setParentEdge(factory->getPointer(m_FormatClause), edkInterpolationSyntax_FormatClause);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_FormatClause, this->getId(), edkInterpolationSyntax_FormatClause);
    } else {
      if (m_FormatClause) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void InterpolationSyntax::setFormatClause(structure::InterpolationFormatClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFormatClause(_node->getId());
  }

  void InterpolationSyntax::removeFormatClause() {
      if (m_FormatClause) {
        removeParentEdge(m_FormatClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_FormatClause, m_id, edkInterpolationSyntax_FormatClause);
      }
      m_FormatClause = 0;
  }

  void InterpolationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void InterpolationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double InterpolationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void InterpolationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType InterpolationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::InterpolationSyntax", strlen("structure::InterpolationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void InterpolationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    InterpolatedStringContentSyntax::save(binIo,false);

    binIo.writeUInt4(m_AlignmentClause);
    binIo.writeUInt4(m_Expression);
    binIo.writeUInt4(m_FormatClause);

  }

  void InterpolationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    InterpolatedStringContentSyntax::load(binIo,false);

    m_AlignmentClause =  binIo.readUInt4();
    if (m_AlignmentClause != 0)
      setParentEdge(factory->getPointer(m_AlignmentClause),edkInterpolationSyntax_AlignmentClause);

    m_Expression =  binIo.readUInt4();
    if (m_Expression != 0)
      setParentEdge(factory->getPointer(m_Expression),edkInterpolationSyntax_Expression);

    m_FormatClause =  binIo.readUInt4();
    if (m_FormatClause != 0)
      setParentEdge(factory->getPointer(m_FormatClause),edkInterpolationSyntax_FormatClause);

  }


}


}}}
