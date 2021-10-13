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
  MethodDeclaration::MethodDeclaration(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    NamedDeclaration(_id, _factory),
    m_isAbstract(false),
    m_isStrictfp(false),
    m_lloc(0),
    m_abstractPosition(),
    m_strictfpPosition(),
    m_parametersStartPosition(),
    m_parametersEndPosition(),
    m_hasReturnType(0),
    m_methodType(0),
    overridesContainer()
  {
    m_abstractPosition.posInfo.path = 0;
    m_abstractPosition.posInfo.line = 0;
    m_abstractPosition.posInfo.col = 0;
    m_abstractPosition.posInfo.endLine = 0;
    m_abstractPosition.posInfo.endCol = 0;
    m_abstractPosition.posInfo.wideLine = 0;
    m_abstractPosition.posInfo.wideCol = 0;
    m_abstractPosition.posInfo.wideEndLine = 0;
    m_abstractPosition.posInfo.wideEndCol = 0;
    m_strictfpPosition.posInfo.path = 0;
    m_strictfpPosition.posInfo.line = 0;
    m_strictfpPosition.posInfo.col = 0;
    m_strictfpPosition.posInfo.endLine = 0;
    m_strictfpPosition.posInfo.endCol = 0;
    m_strictfpPosition.posInfo.wideLine = 0;
    m_strictfpPosition.posInfo.wideCol = 0;
    m_strictfpPosition.posInfo.wideEndLine = 0;
    m_strictfpPosition.posInfo.wideEndCol = 0;
    m_parametersStartPosition.posInfo.path = 0;
    m_parametersStartPosition.posInfo.line = 0;
    m_parametersStartPosition.posInfo.col = 0;
    m_parametersStartPosition.posInfo.endLine = 0;
    m_parametersStartPosition.posInfo.endCol = 0;
    m_parametersStartPosition.posInfo.wideLine = 0;
    m_parametersStartPosition.posInfo.wideCol = 0;
    m_parametersStartPosition.posInfo.wideEndLine = 0;
    m_parametersStartPosition.posInfo.wideEndCol = 0;
    m_parametersEndPosition.posInfo.path = 0;
    m_parametersEndPosition.posInfo.line = 0;
    m_parametersEndPosition.posInfo.col = 0;
    m_parametersEndPosition.posInfo.endLine = 0;
    m_parametersEndPosition.posInfo.endCol = 0;
    m_parametersEndPosition.posInfo.wideLine = 0;
    m_parametersEndPosition.posInfo.wideCol = 0;
    m_parametersEndPosition.posInfo.wideEndLine = 0;
    m_parametersEndPosition.posInfo.wideEndCol = 0;
  }

  MethodDeclaration::~MethodDeclaration() {
  }

  void MethodDeclaration::clone(const MethodDeclaration& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::NamedDeclaration::clone(other, false);

    m_lloc = other.m_lloc;
    m_isAbstract = other.m_isAbstract;
    m_abstractPosition.posInfo = other.m_abstractPosition.posInfo;
    m_isStrictfp = other.m_isStrictfp;
    m_strictfpPosition.posInfo = other.m_strictfpPosition.posInfo;
    m_parametersStartPosition.posInfo = other.m_parametersStartPosition.posInfo;
    m_parametersEndPosition.posInfo = other.m_parametersEndPosition.posInfo;
    m_hasReturnType = other.m_hasReturnType;
    m_methodType = other.m_methodType;
    overridesContainer = other.overridesContainer;
  }

  void MethodDeclaration::prepareDelete(bool tryOnVirtualParent){
    removeReturnType();
    removeMethodType();
    while (!overridesContainer.empty()) {
      const NodeId id = *overridesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethodDeclaration_Overrides);
      overridesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::NamedDeclaration::prepareDelete(false);
  }

  int MethodDeclaration::getLloc() const {
    return m_lloc;
  }

  bool MethodDeclaration::getIsAbstract() const {
    return m_isAbstract;
  }

  const Range MethodDeclaration::getAbstractPosition() const {
    return Range(factory->getStringTable(), m_abstractPosition.posInfo);
  }

  int MethodDeclaration::compareByAbstractPosition(const MethodDeclaration& other) const {
    if (m_abstractPosition.posInfo.path != other.m_abstractPosition.posInfo.path) {
      return (m_abstractPosition.posInfo.path < other.m_abstractPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideLine != other.m_abstractPosition.posInfo.wideLine) {
      return (m_abstractPosition.posInfo.wideLine < other.m_abstractPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideCol != other.m_abstractPosition.posInfo.wideCol) {
      return (m_abstractPosition.posInfo.wideCol < other.m_abstractPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideEndLine != other.m_abstractPosition.posInfo.wideEndLine) {
      return (m_abstractPosition.posInfo.wideEndLine > other.m_abstractPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideEndCol != other.m_abstractPosition.posInfo.wideEndCol) {
      return (m_abstractPosition.posInfo.wideEndCol > other.m_abstractPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  bool MethodDeclaration::getIsStrictfp() const {
    return m_isStrictfp;
  }

  const Range MethodDeclaration::getStrictfpPosition() const {
    return Range(factory->getStringTable(), m_strictfpPosition.posInfo);
  }

  int MethodDeclaration::compareByStrictfpPosition(const MethodDeclaration& other) const {
    if (m_strictfpPosition.posInfo.path != other.m_strictfpPosition.posInfo.path) {
      return (m_strictfpPosition.posInfo.path < other.m_strictfpPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideLine != other.m_strictfpPosition.posInfo.wideLine) {
      return (m_strictfpPosition.posInfo.wideLine < other.m_strictfpPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideCol != other.m_strictfpPosition.posInfo.wideCol) {
      return (m_strictfpPosition.posInfo.wideCol < other.m_strictfpPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideEndLine != other.m_strictfpPosition.posInfo.wideEndLine) {
      return (m_strictfpPosition.posInfo.wideEndLine > other.m_strictfpPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideEndCol != other.m_strictfpPosition.posInfo.wideEndCol) {
      return (m_strictfpPosition.posInfo.wideEndCol > other.m_strictfpPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range MethodDeclaration::getParametersStartPosition() const {
    return Range(factory->getStringTable(), m_parametersStartPosition.posInfo);
  }

  int MethodDeclaration::compareByParametersStartPosition(const MethodDeclaration& other) const {
    if (m_parametersStartPosition.posInfo.path != other.m_parametersStartPosition.posInfo.path) {
      return (m_parametersStartPosition.posInfo.path < other.m_parametersStartPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_parametersStartPosition.posInfo.wideLine != other.m_parametersStartPosition.posInfo.wideLine) {
      return (m_parametersStartPosition.posInfo.wideLine < other.m_parametersStartPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_parametersStartPosition.posInfo.wideCol != other.m_parametersStartPosition.posInfo.wideCol) {
      return (m_parametersStartPosition.posInfo.wideCol < other.m_parametersStartPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_parametersStartPosition.posInfo.wideEndLine != other.m_parametersStartPosition.posInfo.wideEndLine) {
      return (m_parametersStartPosition.posInfo.wideEndLine > other.m_parametersStartPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_parametersStartPosition.posInfo.wideEndCol != other.m_parametersStartPosition.posInfo.wideEndCol) {
      return (m_parametersStartPosition.posInfo.wideEndCol > other.m_parametersStartPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range MethodDeclaration::getParametersEndPosition() const {
    return Range(factory->getStringTable(), m_parametersEndPosition.posInfo);
  }

  int MethodDeclaration::compareByParametersEndPosition(const MethodDeclaration& other) const {
    if (m_parametersEndPosition.posInfo.path != other.m_parametersEndPosition.posInfo.path) {
      return (m_parametersEndPosition.posInfo.path < other.m_parametersEndPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_parametersEndPosition.posInfo.wideLine != other.m_parametersEndPosition.posInfo.wideLine) {
      return (m_parametersEndPosition.posInfo.wideLine < other.m_parametersEndPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_parametersEndPosition.posInfo.wideCol != other.m_parametersEndPosition.posInfo.wideCol) {
      return (m_parametersEndPosition.posInfo.wideCol < other.m_parametersEndPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_parametersEndPosition.posInfo.wideEndLine != other.m_parametersEndPosition.posInfo.wideEndLine) {
      return (m_parametersEndPosition.posInfo.wideEndLine > other.m_parametersEndPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_parametersEndPosition.posInfo.wideEndCol != other.m_parametersEndPosition.posInfo.wideEndCol) {
      return (m_parametersEndPosition.posInfo.wideEndCol > other.m_parametersEndPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void MethodDeclaration::setLloc(int _lloc) {
    m_lloc = _lloc;
  }

  void MethodDeclaration::setIsAbstract(bool _isAbstract) {
    m_isAbstract = _isAbstract;
  }

  void MethodDeclaration::setAbstractPosition(const Range& _abstractPosition) {
    m_abstractPosition.posInfo = _abstractPosition.positionInfo;
    if (_abstractPosition.strTable != &factory->getStringTable())
      m_abstractPosition.posInfo.path = factory->getStringTable().set(_abstractPosition.getPath());
  }

  void MethodDeclaration::setIsStrictfp(bool _isStrictfp) {
    m_isStrictfp = _isStrictfp;
  }

  void MethodDeclaration::setStrictfpPosition(const Range& _strictfpPosition) {
    m_strictfpPosition.posInfo = _strictfpPosition.positionInfo;
    if (_strictfpPosition.strTable != &factory->getStringTable())
      m_strictfpPosition.posInfo.path = factory->getStringTable().set(_strictfpPosition.getPath());
  }

  void MethodDeclaration::setParametersStartPosition(const Range& _parametersStartPosition) {
    m_parametersStartPosition.posInfo = _parametersStartPosition.positionInfo;
    if (_parametersStartPosition.strTable != &factory->getStringTable())
      m_parametersStartPosition.posInfo.path = factory->getStringTable().set(_parametersStartPosition.getPath());
  }

  void MethodDeclaration::setParametersEndPosition(const Range& _parametersEndPosition) {
    m_parametersEndPosition.posInfo = _parametersEndPosition.positionInfo;
    if (_parametersEndPosition.strTable != &factory->getStringTable())
      m_parametersEndPosition.posInfo.path = factory->getStringTable().set(_parametersEndPosition.getPath());
  }

  expr::TypeExpression* MethodDeclaration::getReturnType() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasReturnType != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasReturnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  type::MethodType* MethodDeclaration::getMethodType() const {
    type::MethodType *_node = NULL;
    if (m_methodType != 0)
      _node = dynamic_cast<type::MethodType*>(factory->getPointer(m_methodType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<struc::MethodDeclaration> MethodDeclaration::getOverridesListIteratorBegin() const {
    return ListIterator<struc::MethodDeclaration>(&overridesContainer, factory, true);
  }

  ListIterator<struc::MethodDeclaration> MethodDeclaration::getOverridesListIteratorEnd() const {
    return ListIterator<struc::MethodDeclaration>(&overridesContainer, factory, false);
  }

  bool MethodDeclaration::getOverridesIsEmpty() const {
    return getOverridesListIteratorBegin() == getOverridesListIteratorEnd();
  }

  unsigned int MethodDeclaration::getOverridesSize() const {
    unsigned int size = 0;
    ListIterator<struc::MethodDeclaration> endIt = getOverridesListIteratorEnd();
    for (ListIterator<struc::MethodDeclaration> it = getOverridesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool MethodDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodDeclaration_HasReturnType:
        setReturnType(edgeEnd);
        return true;
      case edkMethodDeclaration_MethodType:
        setMethodType(edgeEnd);
        return true;
      case edkMethodDeclaration_Overrides:
        addOverrides(edgeEnd);
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
    if (struc::NamedDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool MethodDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodDeclaration_HasReturnType:
        removeReturnType();
        return true;
      case edkMethodDeclaration_MethodType:
        removeMethodType();
        return true;
      case edkMethodDeclaration_Overrides:
        removeOverrides(edgeEnd);
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
    if (struc::NamedDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MethodDeclaration::setReturnType(NodeId _id) {
    expr::TypeExpression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::TypeExpression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasReturnType) {
        removeParentEdge(m_hasReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasReturnType, m_id, edkMethodDeclaration_HasReturnType);
      }
      m_hasReturnType = _node->getId();
      if (m_hasReturnType != 0)
        setParentEdge(factory->getPointer(m_hasReturnType), edkMethodDeclaration_HasReturnType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasReturnType, this->getId(), edkMethodDeclaration_HasReturnType);
    } else {
      if (m_hasReturnType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodDeclaration::setReturnType(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void MethodDeclaration::removeReturnType() {
      if (m_hasReturnType) {
        removeParentEdge(m_hasReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasReturnType, m_id, edkMethodDeclaration_HasReturnType);
      }
      m_hasReturnType = 0;
  }

  void MethodDeclaration::setMethodType(NodeId _id) {
    type::MethodType *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<type::MethodType*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_methodType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_methodType, m_id, edkMethodDeclaration_MethodType);
      }
      m_methodType = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_methodType, this->getId(), edkMethodDeclaration_MethodType);
    } else {
      if (m_methodType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodDeclaration::setMethodType(type::MethodType *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setMethodType(_node->getId());
  }

  void MethodDeclaration::removeMethodType() {
      if (m_methodType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_methodType, m_id, edkMethodDeclaration_MethodType);
      }
      m_methodType = 0;
  }

  void MethodDeclaration::addOverrides(const struc::MethodDeclaration *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMethodDeclaration(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    overridesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethodDeclaration_Overrides);
  }

  void MethodDeclaration::addOverrides(NodeId _id) {
    const struc::MethodDeclaration *node = dynamic_cast<struc::MethodDeclaration*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addOverrides( node );
  }

  void MethodDeclaration::removeOverrides(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::MethodDeclaration>::Container::iterator it = find(overridesContainer.begin(), overridesContainer.end(), id);

    if (it == overridesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    overridesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethodDeclaration_Overrides);
  }

  void MethodDeclaration::removeOverrides(struc::MethodDeclaration *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeOverrides(_node->getId());
  }

  double MethodDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const MethodDeclaration& node = dynamic_cast<const MethodDeclaration&>(base);
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
      if(node.getLloc() == getLloc()) ++matchAttrs;
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getIsStrictfp() == getIsStrictfp()) ++matchAttrs;
      return matchAttrs / (9 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void MethodDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType MethodDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::MethodDeclaration", strlen("struc::MethodDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MethodDeclaration::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    NamedDeclaration::sort(false);
  }

  void MethodDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    NamedDeclaration::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isAbstract) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isStrictfp) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUInt4(m_lloc);
    factory->getStringTable().setType(m_abstractPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_abstractPosition.posInfo.path);
    binIo.writeUInt4(m_abstractPosition.posInfo.line);
    binIo.writeUInt4(m_abstractPosition.posInfo.col);
    binIo.writeUInt4(m_abstractPosition.posInfo.endLine);
    binIo.writeUInt4(m_abstractPosition.posInfo.endCol);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideLine);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideCol);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_strictfpPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_strictfpPosition.posInfo.path);
    binIo.writeUInt4(m_strictfpPosition.posInfo.line);
    binIo.writeUInt4(m_strictfpPosition.posInfo.col);
    binIo.writeUInt4(m_strictfpPosition.posInfo.endLine);
    binIo.writeUInt4(m_strictfpPosition.posInfo.endCol);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideLine);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideCol);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_parametersStartPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.path);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.line);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.col);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.endLine);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.endCol);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.wideLine);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.wideCol);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_parametersStartPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_parametersEndPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.path);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.line);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.col);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.endLine);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.endCol);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.wideLine);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.wideCol);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_parametersEndPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasReturnType);
    binIo.writeUInt4(m_methodType);


    for (ListIterator<struc::MethodDeclaration>::Container::const_iterator it = overridesContainer.begin(); it != overridesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void MethodDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    NamedDeclaration::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isStrictfp = boolValues & 1;
    boolValues >>= 1;
    m_isAbstract = boolValues & 1;
    boolValues >>= 1;
    m_lloc = binIo.readUInt4();
    m_abstractPosition.posInfo.path = binIo.readUInt4();
    m_abstractPosition.posInfo.line = binIo.readUInt4();
    m_abstractPosition.posInfo.col = binIo.readUInt4();
    m_abstractPosition.posInfo.endLine = binIo.readUInt4();
    m_abstractPosition.posInfo.endCol = binIo.readUInt4();
    m_abstractPosition.posInfo.wideLine = binIo.readUInt4();
    m_abstractPosition.posInfo.wideCol = binIo.readUInt4();
    m_abstractPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_abstractPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_strictfpPosition.posInfo.path = binIo.readUInt4();
    m_strictfpPosition.posInfo.line = binIo.readUInt4();
    m_strictfpPosition.posInfo.col = binIo.readUInt4();
    m_strictfpPosition.posInfo.endLine = binIo.readUInt4();
    m_strictfpPosition.posInfo.endCol = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideLine = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideCol = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_parametersStartPosition.posInfo.path = binIo.readUInt4();
    m_parametersStartPosition.posInfo.line = binIo.readUInt4();
    m_parametersStartPosition.posInfo.col = binIo.readUInt4();
    m_parametersStartPosition.posInfo.endLine = binIo.readUInt4();
    m_parametersStartPosition.posInfo.endCol = binIo.readUInt4();
    m_parametersStartPosition.posInfo.wideLine = binIo.readUInt4();
    m_parametersStartPosition.posInfo.wideCol = binIo.readUInt4();
    m_parametersStartPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_parametersStartPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_parametersEndPosition.posInfo.path = binIo.readUInt4();
    m_parametersEndPosition.posInfo.line = binIo.readUInt4();
    m_parametersEndPosition.posInfo.col = binIo.readUInt4();
    m_parametersEndPosition.posInfo.endLine = binIo.readUInt4();
    m_parametersEndPosition.posInfo.endCol = binIo.readUInt4();
    m_parametersEndPosition.posInfo.wideLine = binIo.readUInt4();
    m_parametersEndPosition.posInfo.wideCol = binIo.readUInt4();
    m_parametersEndPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_parametersEndPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasReturnType =  binIo.readUInt4();
    if (m_hasReturnType != 0)
      setParentEdge(factory->getPointer(m_hasReturnType),edkMethodDeclaration_HasReturnType);

    m_methodType =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      overridesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
