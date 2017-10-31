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

namespace struc { 
  Import::Import(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Positioned(_id, _factory),
    m_isStatic(false),
    m_staticPosition(),
    m_hasTarget(0)
  {
    m_staticPosition.posInfo.path = 0;
    m_staticPosition.posInfo.line = 0;
    m_staticPosition.posInfo.col = 0;
    m_staticPosition.posInfo.endLine = 0;
    m_staticPosition.posInfo.endCol = 0;
    m_staticPosition.posInfo.wideLine = 0;
    m_staticPosition.posInfo.wideCol = 0;
    m_staticPosition.posInfo.wideEndLine = 0;
    m_staticPosition.posInfo.wideEndCol = 0;
  }

  Import::~Import() {
  }

  void Import::clone(const Import& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    base::Positioned::clone(other, false);

    m_isStatic = other.m_isStatic;
    m_staticPosition.posInfo = other.m_staticPosition.posInfo;
    m_hasTarget = other.m_hasTarget;
  }

  void Import::prepareDelete(bool tryOnVirtualParent){
    removeTarget();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind Import::getNodeKind() const {
    return ndkImport;
  }

  bool Import::getIsStatic() const {
    return m_isStatic;
  }

  const Range Import::getStaticPosition() const {
    return Range(factory->getStringTable(), m_staticPosition.posInfo);
  }

  int Import::compareByStaticPosition(const Import& other) const {
    if (m_staticPosition.posInfo.path != other.m_staticPosition.posInfo.path) {
      return (m_staticPosition.posInfo.path < other.m_staticPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideLine != other.m_staticPosition.posInfo.wideLine) {
      return (m_staticPosition.posInfo.wideLine < other.m_staticPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideCol != other.m_staticPosition.posInfo.wideCol) {
      return (m_staticPosition.posInfo.wideCol < other.m_staticPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideEndLine != other.m_staticPosition.posInfo.wideEndLine) {
      return (m_staticPosition.posInfo.wideEndLine > other.m_staticPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_staticPosition.posInfo.wideEndCol != other.m_staticPosition.posInfo.wideEndCol) {
      return (m_staticPosition.posInfo.wideEndCol > other.m_staticPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Import::setIsStatic(bool _isStatic) {
    m_isStatic = _isStatic;
  }

  void Import::setStaticPosition(const Range& _staticPosition) {
    m_staticPosition.posInfo = _staticPosition.positionInfo;
    if (_staticPosition.strTable != &factory->getStringTable())
      m_staticPosition.posInfo.path = factory->getStringTable().set(_staticPosition.getPath());
  }

  expr::Expression* Import::getTarget() const {
    expr::Expression *_node = NULL;
    if (m_hasTarget != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasTarget));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Import::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImport_HasTarget:
        setTarget(edgeEnd);
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
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Import::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImport_HasTarget:
        removeTarget();
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
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Import::setTarget(NodeId _id) {
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

      if (m_hasTarget) {
        removeParentEdge(m_hasTarget);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkImport_HasTarget);
      }
      m_hasTarget = _node->getId();
      if (m_hasTarget != 0)
        setParentEdge(factory->getPointer(m_hasTarget), edkImport_HasTarget);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTarget, this->getId(), edkImport_HasTarget);
    } else {
      if (m_hasTarget) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Import::setTarget(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTarget(_node->getId());
  }

  void Import::removeTarget() {
      if (m_hasTarget) {
        removeParentEdge(m_hasTarget);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkImport_HasTarget);
      }
      m_hasTarget = 0;
  }

  void Import::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Import::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Import::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Import& node = dynamic_cast<const Import&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Import::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Import::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::Import", strlen("struc::Import"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Import::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Positioned::sort(false);
  }

  void Import::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Positioned::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isStatic) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    factory->getStringTable().setType(m_staticPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_staticPosition.posInfo.path);
    binIo.writeUInt4(m_staticPosition.posInfo.line);
    binIo.writeUInt4(m_staticPosition.posInfo.col);
    binIo.writeUInt4(m_staticPosition.posInfo.endLine);
    binIo.writeUInt4(m_staticPosition.posInfo.endCol);
    binIo.writeUInt4(m_staticPosition.posInfo.wideLine);
    binIo.writeUInt4(m_staticPosition.posInfo.wideCol);
    binIo.writeUInt4(m_staticPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_staticPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasTarget);

  }

  void Import::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Positioned::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isStatic = boolValues & 1;
    boolValues >>= 1;
    m_staticPosition.posInfo.path = binIo.readUInt4();
    m_staticPosition.posInfo.line = binIo.readUInt4();
    m_staticPosition.posInfo.col = binIo.readUInt4();
    m_staticPosition.posInfo.endLine = binIo.readUInt4();
    m_staticPosition.posInfo.endCol = binIo.readUInt4();
    m_staticPosition.posInfo.wideLine = binIo.readUInt4();
    m_staticPosition.posInfo.wideCol = binIo.readUInt4();
    m_staticPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_staticPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasTarget =  binIo.readUInt4();
    if (m_hasTarget != 0)
      setParentEdge(factory->getPointer(m_hasTarget),edkImport_HasTarget);

  }


}


}}}
