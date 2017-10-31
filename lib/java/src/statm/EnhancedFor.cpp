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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statm { 
  EnhancedFor::EnhancedFor(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    For(_id, _factory),
    m_colonPosition(),
    m_hasParameter(0),
    m_hasExpression(0)
  {
    m_colonPosition.posInfo.path = 0;
    m_colonPosition.posInfo.line = 0;
    m_colonPosition.posInfo.col = 0;
    m_colonPosition.posInfo.endLine = 0;
    m_colonPosition.posInfo.endCol = 0;
    m_colonPosition.posInfo.wideLine = 0;
    m_colonPosition.posInfo.wideCol = 0;
    m_colonPosition.posInfo.wideEndLine = 0;
    m_colonPosition.posInfo.wideEndCol = 0;
  }

  EnhancedFor::~EnhancedFor() {
  }

  void EnhancedFor::clone(const EnhancedFor& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::For::clone(other, false);

    m_colonPosition.posInfo = other.m_colonPosition.posInfo;
    m_hasParameter = other.m_hasParameter;
    m_hasExpression = other.m_hasExpression;
  }

  void EnhancedFor::prepareDelete(bool tryOnVirtualParent){
    removeParameter();
    removeExpression();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::For::prepareDelete(false);
  }

  NodeKind EnhancedFor::getNodeKind() const {
    return ndkEnhancedFor;
  }

  const Range EnhancedFor::getColonPosition() const {
    return Range(factory->getStringTable(), m_colonPosition.posInfo);
  }

  int EnhancedFor::compareByColonPosition(const EnhancedFor& other) const {
    if (m_colonPosition.posInfo.path != other.m_colonPosition.posInfo.path) {
      return (m_colonPosition.posInfo.path < other.m_colonPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideLine != other.m_colonPosition.posInfo.wideLine) {
      return (m_colonPosition.posInfo.wideLine < other.m_colonPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideCol != other.m_colonPosition.posInfo.wideCol) {
      return (m_colonPosition.posInfo.wideCol < other.m_colonPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideEndLine != other.m_colonPosition.posInfo.wideEndLine) {
      return (m_colonPosition.posInfo.wideEndLine > other.m_colonPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_colonPosition.posInfo.wideEndCol != other.m_colonPosition.posInfo.wideEndCol) {
      return (m_colonPosition.posInfo.wideEndCol > other.m_colonPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void EnhancedFor::setColonPosition(const Range& _colonPosition) {
    m_colonPosition.posInfo = _colonPosition.positionInfo;
    if (_colonPosition.strTable != &factory->getStringTable())
      m_colonPosition.posInfo.path = factory->getStringTable().set(_colonPosition.getPath());
  }

  struc::Parameter* EnhancedFor::getParameter() const {
    struc::Parameter *_node = NULL;
    if (m_hasParameter != 0)
      _node = dynamic_cast<struc::Parameter*>(factory->getPointer(m_hasParameter));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expr::Expression* EnhancedFor::getExpression() const {
    expr::Expression *_node = NULL;
    if (m_hasExpression != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool EnhancedFor::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEnhancedFor_HasParameter:
        setParameter(edgeEnd);
        return true;
      case edkEnhancedFor_HasExpression:
        setExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::For::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool EnhancedFor::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEnhancedFor_HasParameter:
        removeParameter();
        return true;
      case edkEnhancedFor_HasExpression:
        removeExpression();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::For::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void EnhancedFor::setParameter(NodeId _id) {
    struc::Parameter *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::Parameter*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasParameter) {
        removeParentEdge(m_hasParameter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasParameter, m_id, edkEnhancedFor_HasParameter);
      }
      m_hasParameter = _node->getId();
      if (m_hasParameter != 0)
        setParentEdge(factory->getPointer(m_hasParameter), edkEnhancedFor_HasParameter);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasParameter, this->getId(), edkEnhancedFor_HasParameter);
    } else {
      if (m_hasParameter) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void EnhancedFor::setParameter(struc::Parameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameter(_node->getId());
  }

  void EnhancedFor::removeParameter() {
      if (m_hasParameter) {
        removeParentEdge(m_hasParameter);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasParameter, m_id, edkEnhancedFor_HasParameter);
      }
      m_hasParameter = 0;
  }

  void EnhancedFor::setExpression(NodeId _id) {
    expr::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkEnhancedFor_HasExpression);
      }
      m_hasExpression = _node->getId();
      if (m_hasExpression != 0)
        setParentEdge(factory->getPointer(m_hasExpression), edkEnhancedFor_HasExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpression, this->getId(), edkEnhancedFor_HasExpression);
    } else {
      if (m_hasExpression) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void EnhancedFor::setExpression(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void EnhancedFor::removeExpression() {
      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkEnhancedFor_HasExpression);
      }
      m_hasExpression = 0;
  }

  void EnhancedFor::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void EnhancedFor::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double EnhancedFor::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const EnhancedFor& node = dynamic_cast<const EnhancedFor&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void EnhancedFor::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType EnhancedFor::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::EnhancedFor", strlen("statm::EnhancedFor"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void EnhancedFor::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    For::sort(false);
  }

  void EnhancedFor::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    For::save(binIo,false);

    factory->getStringTable().setType(m_colonPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_colonPosition.posInfo.path);
    binIo.writeUInt4(m_colonPosition.posInfo.line);
    binIo.writeUInt4(m_colonPosition.posInfo.col);
    binIo.writeUInt4(m_colonPosition.posInfo.endLine);
    binIo.writeUInt4(m_colonPosition.posInfo.endCol);
    binIo.writeUInt4(m_colonPosition.posInfo.wideLine);
    binIo.writeUInt4(m_colonPosition.posInfo.wideCol);
    binIo.writeUInt4(m_colonPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_colonPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasParameter);
    binIo.writeUInt4(m_hasExpression);

  }

  void EnhancedFor::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    For::load(binIo,false);

    m_colonPosition.posInfo.path = binIo.readUInt4();
    m_colonPosition.posInfo.line = binIo.readUInt4();
    m_colonPosition.posInfo.col = binIo.readUInt4();
    m_colonPosition.posInfo.endLine = binIo.readUInt4();
    m_colonPosition.posInfo.endCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasParameter =  binIo.readUInt4();
    if (m_hasParameter != 0)
      setParentEdge(factory->getPointer(m_hasParameter),edkEnhancedFor_HasParameter);

    m_hasExpression =  binIo.readUInt4();
    if (m_hasExpression != 0)
      setParentEdge(factory->getPointer(m_hasExpression),edkEnhancedFor_HasExpression);

  }


}


}}}
