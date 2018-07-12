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

namespace struc { 
  Variable::Variable(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    VariableDeclaration(_id, _factory),
    m_isTransient(false),
    m_isVolatile(false),
    m_transientPosition(),
    m_volatilePosition(),
    m_equalSignPosition(),
    m_hasInitialValue(0)
  {
    m_transientPosition.posInfo.path = 0;
    m_transientPosition.posInfo.line = 0;
    m_transientPosition.posInfo.col = 0;
    m_transientPosition.posInfo.endLine = 0;
    m_transientPosition.posInfo.endCol = 0;
    m_transientPosition.posInfo.wideLine = 0;
    m_transientPosition.posInfo.wideCol = 0;
    m_transientPosition.posInfo.wideEndLine = 0;
    m_transientPosition.posInfo.wideEndCol = 0;
    m_volatilePosition.posInfo.path = 0;
    m_volatilePosition.posInfo.line = 0;
    m_volatilePosition.posInfo.col = 0;
    m_volatilePosition.posInfo.endLine = 0;
    m_volatilePosition.posInfo.endCol = 0;
    m_volatilePosition.posInfo.wideLine = 0;
    m_volatilePosition.posInfo.wideCol = 0;
    m_volatilePosition.posInfo.wideEndLine = 0;
    m_volatilePosition.posInfo.wideEndCol = 0;
    m_equalSignPosition.posInfo.path = 0;
    m_equalSignPosition.posInfo.line = 0;
    m_equalSignPosition.posInfo.col = 0;
    m_equalSignPosition.posInfo.endLine = 0;
    m_equalSignPosition.posInfo.endCol = 0;
    m_equalSignPosition.posInfo.wideLine = 0;
    m_equalSignPosition.posInfo.wideCol = 0;
    m_equalSignPosition.posInfo.wideEndLine = 0;
    m_equalSignPosition.posInfo.wideEndCol = 0;
  }

  Variable::~Variable() {
  }

  void Variable::clone(const Variable& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::VariableDeclaration::clone(other, false);

    m_isTransient = other.m_isTransient;
    m_transientPosition.posInfo = other.m_transientPosition.posInfo;
    m_isVolatile = other.m_isVolatile;
    m_volatilePosition.posInfo = other.m_volatilePosition.posInfo;
    m_equalSignPosition.posInfo = other.m_equalSignPosition.posInfo;
    m_hasInitialValue = other.m_hasInitialValue;
  }

  void Variable::prepareDelete(bool tryOnVirtualParent){
    removeInitialValue();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::VariableDeclaration::prepareDelete(false);
  }

  NodeKind Variable::getNodeKind() const {
    return ndkVariable;
  }

  bool Variable::getIsTransient() const {
    return m_isTransient;
  }

  const Range Variable::getTransientPosition() const {
    return Range(factory->getStringTable(), m_transientPosition.posInfo);
  }

  int Variable::compareByTransientPosition(const Variable& other) const {
    if (m_transientPosition.posInfo.path != other.m_transientPosition.posInfo.path) {
      return (m_transientPosition.posInfo.path < other.m_transientPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_transientPosition.posInfo.wideLine != other.m_transientPosition.posInfo.wideLine) {
      return (m_transientPosition.posInfo.wideLine < other.m_transientPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_transientPosition.posInfo.wideCol != other.m_transientPosition.posInfo.wideCol) {
      return (m_transientPosition.posInfo.wideCol < other.m_transientPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_transientPosition.posInfo.wideEndLine != other.m_transientPosition.posInfo.wideEndLine) {
      return (m_transientPosition.posInfo.wideEndLine > other.m_transientPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_transientPosition.posInfo.wideEndCol != other.m_transientPosition.posInfo.wideEndCol) {
      return (m_transientPosition.posInfo.wideEndCol > other.m_transientPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  bool Variable::getIsVolatile() const {
    return m_isVolatile;
  }

  const Range Variable::getVolatilePosition() const {
    return Range(factory->getStringTable(), m_volatilePosition.posInfo);
  }

  int Variable::compareByVolatilePosition(const Variable& other) const {
    if (m_volatilePosition.posInfo.path != other.m_volatilePosition.posInfo.path) {
      return (m_volatilePosition.posInfo.path < other.m_volatilePosition.posInfo.path) ? -1 :1 ;
    };
    if (m_volatilePosition.posInfo.wideLine != other.m_volatilePosition.posInfo.wideLine) {
      return (m_volatilePosition.posInfo.wideLine < other.m_volatilePosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_volatilePosition.posInfo.wideCol != other.m_volatilePosition.posInfo.wideCol) {
      return (m_volatilePosition.posInfo.wideCol < other.m_volatilePosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_volatilePosition.posInfo.wideEndLine != other.m_volatilePosition.posInfo.wideEndLine) {
      return (m_volatilePosition.posInfo.wideEndLine > other.m_volatilePosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_volatilePosition.posInfo.wideEndCol != other.m_volatilePosition.posInfo.wideEndCol) {
      return (m_volatilePosition.posInfo.wideEndCol > other.m_volatilePosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range Variable::getEqualSignPosition() const {
    return Range(factory->getStringTable(), m_equalSignPosition.posInfo);
  }

  int Variable::compareByEqualSignPosition(const Variable& other) const {
    if (m_equalSignPosition.posInfo.path != other.m_equalSignPosition.posInfo.path) {
      return (m_equalSignPosition.posInfo.path < other.m_equalSignPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_equalSignPosition.posInfo.wideLine != other.m_equalSignPosition.posInfo.wideLine) {
      return (m_equalSignPosition.posInfo.wideLine < other.m_equalSignPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_equalSignPosition.posInfo.wideCol != other.m_equalSignPosition.posInfo.wideCol) {
      return (m_equalSignPosition.posInfo.wideCol < other.m_equalSignPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_equalSignPosition.posInfo.wideEndLine != other.m_equalSignPosition.posInfo.wideEndLine) {
      return (m_equalSignPosition.posInfo.wideEndLine > other.m_equalSignPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_equalSignPosition.posInfo.wideEndCol != other.m_equalSignPosition.posInfo.wideEndCol) {
      return (m_equalSignPosition.posInfo.wideEndCol > other.m_equalSignPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void Variable::setIsTransient(bool _isTransient) {
    m_isTransient = _isTransient;
  }

  void Variable::setTransientPosition(const Range& _transientPosition) {
    m_transientPosition.posInfo = _transientPosition.positionInfo;
    if (_transientPosition.strTable != &factory->getStringTable())
      m_transientPosition.posInfo.path = factory->getStringTable().set(_transientPosition.getPath());
  }

  void Variable::setIsVolatile(bool _isVolatile) {
    m_isVolatile = _isVolatile;
  }

  void Variable::setVolatilePosition(const Range& _volatilePosition) {
    m_volatilePosition.posInfo = _volatilePosition.positionInfo;
    if (_volatilePosition.strTable != &factory->getStringTable())
      m_volatilePosition.posInfo.path = factory->getStringTable().set(_volatilePosition.getPath());
  }

  void Variable::setEqualSignPosition(const Range& _equalSignPosition) {
    m_equalSignPosition.posInfo = _equalSignPosition.positionInfo;
    if (_equalSignPosition.strTable != &factory->getStringTable())
      m_equalSignPosition.posInfo.path = factory->getStringTable().set(_equalSignPosition.getPath());
  }

  expr::Expression* Variable::getInitialValue() const {
    expr::Expression *_node = NULL;
    if (m_hasInitialValue != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasInitialValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Variable::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariable_HasInitialValue:
        setInitialValue(edgeEnd);
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
    if (tryOnVirtualParent) {
      if (struc::Member::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (struc::VariableDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Variable::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariable_HasInitialValue:
        removeInitialValue();
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
    if (tryOnVirtualParent) {
      if (struc::Member::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (struc::VariableDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Variable::setInitialValue(NodeId _id) {
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

      if (m_hasInitialValue) {
        removeParentEdge(m_hasInitialValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasInitialValue, m_id, edkVariable_HasInitialValue);
      }
      m_hasInitialValue = _node->getId();
      if (m_hasInitialValue != 0)
        setParentEdge(factory->getPointer(m_hasInitialValue), edkVariable_HasInitialValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasInitialValue, this->getId(), edkVariable_HasInitialValue);
    } else {
      if (m_hasInitialValue) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Variable::setInitialValue(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInitialValue(_node->getId());
  }

  void Variable::removeInitialValue() {
      if (m_hasInitialValue) {
        removeParentEdge(m_hasInitialValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasInitialValue, m_id, edkVariable_HasInitialValue);
      }
      m_hasInitialValue = 0;
  }

  void Variable::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Variable::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Variable::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Variable& node = dynamic_cast<const Variable&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getAccessibility() == getAccessibility()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      if(node.getIsFinal() == getIsFinal()) ++matchAttrs;
      if(node.getIsTransient() == getIsTransient()) ++matchAttrs;
      if(node.getIsVolatile() == getIsVolatile()) ++matchAttrs;
      return matchAttrs / (8 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Variable::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Variable::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::Variable", strlen("struc::Variable"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Variable::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    VariableDeclaration::sort(false);
  }

  void Variable::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    VariableDeclaration::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isTransient) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isVolatile) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    factory->getStringTable().setType(m_transientPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_transientPosition.posInfo.path);
    binIo.writeUInt4(m_transientPosition.posInfo.line);
    binIo.writeUInt4(m_transientPosition.posInfo.col);
    binIo.writeUInt4(m_transientPosition.posInfo.endLine);
    binIo.writeUInt4(m_transientPosition.posInfo.endCol);
    binIo.writeUInt4(m_transientPosition.posInfo.wideLine);
    binIo.writeUInt4(m_transientPosition.posInfo.wideCol);
    binIo.writeUInt4(m_transientPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_transientPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_volatilePosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_volatilePosition.posInfo.path);
    binIo.writeUInt4(m_volatilePosition.posInfo.line);
    binIo.writeUInt4(m_volatilePosition.posInfo.col);
    binIo.writeUInt4(m_volatilePosition.posInfo.endLine);
    binIo.writeUInt4(m_volatilePosition.posInfo.endCol);
    binIo.writeUInt4(m_volatilePosition.posInfo.wideLine);
    binIo.writeUInt4(m_volatilePosition.posInfo.wideCol);
    binIo.writeUInt4(m_volatilePosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_volatilePosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_equalSignPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_equalSignPosition.posInfo.path);
    binIo.writeUInt4(m_equalSignPosition.posInfo.line);
    binIo.writeUInt4(m_equalSignPosition.posInfo.col);
    binIo.writeUInt4(m_equalSignPosition.posInfo.endLine);
    binIo.writeUInt4(m_equalSignPosition.posInfo.endCol);
    binIo.writeUInt4(m_equalSignPosition.posInfo.wideLine);
    binIo.writeUInt4(m_equalSignPosition.posInfo.wideCol);
    binIo.writeUInt4(m_equalSignPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_equalSignPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasInitialValue);

  }

  void Variable::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    VariableDeclaration::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isVolatile = boolValues & 1;
    boolValues >>= 1;
    m_isTransient = boolValues & 1;
    boolValues >>= 1;
    m_transientPosition.posInfo.path = binIo.readUInt4();
    m_transientPosition.posInfo.line = binIo.readUInt4();
    m_transientPosition.posInfo.col = binIo.readUInt4();
    m_transientPosition.posInfo.endLine = binIo.readUInt4();
    m_transientPosition.posInfo.endCol = binIo.readUInt4();
    m_transientPosition.posInfo.wideLine = binIo.readUInt4();
    m_transientPosition.posInfo.wideCol = binIo.readUInt4();
    m_transientPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_transientPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_volatilePosition.posInfo.path = binIo.readUInt4();
    m_volatilePosition.posInfo.line = binIo.readUInt4();
    m_volatilePosition.posInfo.col = binIo.readUInt4();
    m_volatilePosition.posInfo.endLine = binIo.readUInt4();
    m_volatilePosition.posInfo.endCol = binIo.readUInt4();
    m_volatilePosition.posInfo.wideLine = binIo.readUInt4();
    m_volatilePosition.posInfo.wideCol = binIo.readUInt4();
    m_volatilePosition.posInfo.wideEndLine = binIo.readUInt4();
    m_volatilePosition.posInfo.wideEndCol = binIo.readUInt4();
    m_equalSignPosition.posInfo.path = binIo.readUInt4();
    m_equalSignPosition.posInfo.line = binIo.readUInt4();
    m_equalSignPosition.posInfo.col = binIo.readUInt4();
    m_equalSignPosition.posInfo.endLine = binIo.readUInt4();
    m_equalSignPosition.posInfo.endCol = binIo.readUInt4();
    m_equalSignPosition.posInfo.wideLine = binIo.readUInt4();
    m_equalSignPosition.posInfo.wideCol = binIo.readUInt4();
    m_equalSignPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_equalSignPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasInitialValue =  binIo.readUInt4();
    if (m_hasInitialValue != 0)
      setParentEdge(factory->getPointer(m_hasInitialValue),edkVariable_HasInitialValue);

  }


}


}}}
