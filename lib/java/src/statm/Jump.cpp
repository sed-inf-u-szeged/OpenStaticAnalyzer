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
  Jump::Jump(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Statement(_id, _factory),
    m_label(0),
    m_labelPosition(),
    m_target(0)
  {
    m_labelPosition.posInfo.path = 0;
    m_labelPosition.posInfo.line = 0;
    m_labelPosition.posInfo.col = 0;
    m_labelPosition.posInfo.endLine = 0;
    m_labelPosition.posInfo.endCol = 0;
    m_labelPosition.posInfo.wideLine = 0;
    m_labelPosition.posInfo.wideCol = 0;
    m_labelPosition.posInfo.wideEndLine = 0;
    m_labelPosition.posInfo.wideEndCol = 0;
  }

  Jump::~Jump() {
  }

  void Jump::clone(const Jump& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Statement::clone(other, false);

    m_label = other.m_label;
    m_labelPosition.posInfo = other.m_labelPosition.posInfo;
    m_target = other.m_target;
  }

  void Jump::prepareDelete(bool tryOnVirtualParent){
    removeTarget();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Statement::prepareDelete(false);
  }

  Key Jump::getLabelKey() const {
    return m_label;
  }

  const std::string& Jump::getLabel() const {
    return factory->getStringTable().get(m_label);
  }

  const Range Jump::getLabelPosition() const {
    return Range(factory->getStringTable(), m_labelPosition.posInfo);
  }

  int Jump::compareByLabelPosition(const Jump& other) const {
    if (m_labelPosition.posInfo.path != other.m_labelPosition.posInfo.path) {
      return (m_labelPosition.posInfo.path < other.m_labelPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_labelPosition.posInfo.wideLine != other.m_labelPosition.posInfo.wideLine) {
      return (m_labelPosition.posInfo.wideLine < other.m_labelPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_labelPosition.posInfo.wideCol != other.m_labelPosition.posInfo.wideCol) {
      return (m_labelPosition.posInfo.wideCol < other.m_labelPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_labelPosition.posInfo.wideEndLine != other.m_labelPosition.posInfo.wideEndLine) {
      return (m_labelPosition.posInfo.wideEndLine > other.m_labelPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_labelPosition.posInfo.wideEndCol != other.m_labelPosition.posInfo.wideEndCol) {
      return (m_labelPosition.posInfo.wideEndCol > other.m_labelPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Jump::setLabelKey(Key _label) {
    m_label = _label;
  }

  void Jump::setLabel(const std::string& _label) {
    m_label = factory->getStringTable().set(_label);
  }

  void Jump::setLabelPosition(const Range& _labelPosition) {
    m_labelPosition.posInfo = _labelPosition.positionInfo;
    if (_labelPosition.strTable != &factory->getStringTable())
      m_labelPosition.posInfo.path = factory->getStringTable().set(_labelPosition.getPath());
  }

  statm::Statement* Jump::getTarget() const {
    statm::Statement *_node = NULL;
    if (m_target != 0)
      _node = dynamic_cast<statm::Statement*>(factory->getPointer(m_target));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Jump::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkJump_Target:
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
    if (statm::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Jump::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkJump_Target:
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
    if (statm::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Jump::setTarget(NodeId _id) {
    statm::Statement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Statement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_target) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_target, m_id, edkJump_Target);
      }
      m_target = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_target, this->getId(), edkJump_Target);
    } else {
      if (m_target) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Jump::setTarget(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTarget(_node->getId());
  }

  void Jump::removeTarget() {
      if (m_target) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_target, m_id, edkJump_Target);
      }
      m_target = 0;
  }

  double Jump::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Jump& node = dynamic_cast<const Jump&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getLabel();
      str2 = node.getLabel();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Jump::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_label);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_label = foundKeyId->second;
    } else {
      Key oldkey = m_label;
      m_label = newStrTable.set(factory->getStringTable().get(m_label));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_label));    }

  }

  NodeHashType Jump::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Jump", strlen("statm::Jump"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Jump::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Statement::sort(false);
  }

  void Jump::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Statement::save(binIo,false);

    factory->getStringTable().setType(m_label, StrTable::strToSave);
    binIo.writeUInt4(m_label);
    factory->getStringTable().setType(m_labelPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_labelPosition.posInfo.path);
    binIo.writeUInt4(m_labelPosition.posInfo.line);
    binIo.writeUInt4(m_labelPosition.posInfo.col);
    binIo.writeUInt4(m_labelPosition.posInfo.endLine);
    binIo.writeUInt4(m_labelPosition.posInfo.endCol);
    binIo.writeUInt4(m_labelPosition.posInfo.wideLine);
    binIo.writeUInt4(m_labelPosition.posInfo.wideCol);
    binIo.writeUInt4(m_labelPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_labelPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_target);

  }

  void Jump::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Statement::load(binIo,false);

    m_label = binIo.readUInt4();
    m_labelPosition.posInfo.path = binIo.readUInt4();
    m_labelPosition.posInfo.line = binIo.readUInt4();
    m_labelPosition.posInfo.col = binIo.readUInt4();
    m_labelPosition.posInfo.endLine = binIo.readUInt4();
    m_labelPosition.posInfo.endCol = binIo.readUInt4();
    m_labelPosition.posInfo.wideLine = binIo.readUInt4();
    m_labelPosition.posInfo.wideCol = binIo.readUInt4();
    m_labelPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_labelPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_target =  binIo.readUInt4();

  }


}


}}}
