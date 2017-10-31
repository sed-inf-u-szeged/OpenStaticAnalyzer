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
  LabeledStatement::LabeledStatement(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Statement(_id, _factory),
    m_label(0),
    m_colonPosition(),
    m_hasStatement(0)
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

  LabeledStatement::~LabeledStatement() {
  }

  void LabeledStatement::clone(const LabeledStatement& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Statement::clone(other, false);

    m_label = other.m_label;
    m_colonPosition.posInfo = other.m_colonPosition.posInfo;
    m_hasStatement = other.m_hasStatement;
  }

  void LabeledStatement::prepareDelete(bool tryOnVirtualParent){
    removeStatement();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Statement::prepareDelete(false);
  }

  NodeKind LabeledStatement::getNodeKind() const {
    return ndkLabeledStatement;
  }

  Key LabeledStatement::getLabelKey() const {
    return m_label;
  }

  const std::string& LabeledStatement::getLabel() const {
    return factory->getStringTable().get(m_label);
  }

  const Range LabeledStatement::getColonPosition() const {
    return Range(factory->getStringTable(), m_colonPosition.posInfo);
  }

  int LabeledStatement::compareByColonPosition(const LabeledStatement& other) const {
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

  void LabeledStatement::setLabelKey(Key _label) {
    m_label = _label;
  }

  void LabeledStatement::setLabel(const std::string& _label) {
    m_label = factory->getStringTable().set(_label);
  }

  void LabeledStatement::setColonPosition(const Range& _colonPosition) {
    m_colonPosition.posInfo = _colonPosition.positionInfo;
    if (_colonPosition.strTable != &factory->getStringTable())
      m_colonPosition.posInfo.path = factory->getStringTable().set(_colonPosition.getPath());
  }

  statm::Statement* LabeledStatement::getStatement() const {
    statm::Statement *_node = NULL;
    if (m_hasStatement != 0)
      _node = dynamic_cast<statm::Statement*>(factory->getPointer(m_hasStatement));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool LabeledStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLabeledStatement_HasStatement:
        setStatement(edgeEnd);
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

  bool LabeledStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLabeledStatement_HasStatement:
        removeStatement();
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

  void LabeledStatement::setStatement(NodeId _id) {
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

      if (m_hasStatement) {
        removeParentEdge(m_hasStatement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasStatement, m_id, edkLabeledStatement_HasStatement);
      }
      m_hasStatement = _node->getId();
      if (m_hasStatement != 0)
        setParentEdge(factory->getPointer(m_hasStatement), edkLabeledStatement_HasStatement);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasStatement, this->getId(), edkLabeledStatement_HasStatement);
    } else {
      if (m_hasStatement) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LabeledStatement::setStatement(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setStatement(_node->getId());
  }

  void LabeledStatement::removeStatement() {
      if (m_hasStatement) {
        removeParentEdge(m_hasStatement);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasStatement, m_id, edkLabeledStatement_HasStatement);
      }
      m_hasStatement = 0;
  }

  void LabeledStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void LabeledStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double LabeledStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const LabeledStatement& node = dynamic_cast<const LabeledStatement&>(base);
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

  void LabeledStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_label);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_label = foundKeyId->second;
    } else {
      Key oldkey = m_label;
      m_label = newStrTable.set(factory->getStringTable().get(m_label));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_label));    }

  }

  NodeHashType LabeledStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::LabeledStatement", strlen("statm::LabeledStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void LabeledStatement::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Statement::sort(false);
  }

  void LabeledStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Statement::save(binIo,false);

    factory->getStringTable().setType(m_label, StrTable::strToSave);
    binIo.writeUInt4(m_label);
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

    binIo.writeUInt4(m_hasStatement);

  }

  void LabeledStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Statement::load(binIo,false);

    m_label = binIo.readUInt4();
    m_colonPosition.posInfo.path = binIo.readUInt4();
    m_colonPosition.posInfo.line = binIo.readUInt4();
    m_colonPosition.posInfo.col = binIo.readUInt4();
    m_colonPosition.posInfo.endLine = binIo.readUInt4();
    m_colonPosition.posInfo.endCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideCol = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_colonPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasStatement =  binIo.readUInt4();
    if (m_hasStatement != 0)
      setParentEdge(factory->getPointer(m_hasStatement),edkLabeledStatement_HasStatement);

  }


}


}}}
