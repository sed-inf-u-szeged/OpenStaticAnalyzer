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
  NormalMethod::NormalMethod(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    MethodDeclaration(_id, _factory),
    m_isSynchronized(false),
    m_isNative(false),
    m_methodKind(mekNormal),
    m_synchronizedPosition(),
    m_nativePosition(),
    m_throwsPosition(),
    hasParametersContainer(),
    m_hasBody(0),
    hasThrownExceptionsContainer()
  {
    m_synchronizedPosition.posInfo.path = 0;
    m_synchronizedPosition.posInfo.line = 0;
    m_synchronizedPosition.posInfo.col = 0;
    m_synchronizedPosition.posInfo.endLine = 0;
    m_synchronizedPosition.posInfo.endCol = 0;
    m_synchronizedPosition.posInfo.wideLine = 0;
    m_synchronizedPosition.posInfo.wideCol = 0;
    m_synchronizedPosition.posInfo.wideEndLine = 0;
    m_synchronizedPosition.posInfo.wideEndCol = 0;
    m_nativePosition.posInfo.path = 0;
    m_nativePosition.posInfo.line = 0;
    m_nativePosition.posInfo.col = 0;
    m_nativePosition.posInfo.endLine = 0;
    m_nativePosition.posInfo.endCol = 0;
    m_nativePosition.posInfo.wideLine = 0;
    m_nativePosition.posInfo.wideCol = 0;
    m_nativePosition.posInfo.wideEndLine = 0;
    m_nativePosition.posInfo.wideEndCol = 0;
    m_throwsPosition.posInfo.path = 0;
    m_throwsPosition.posInfo.line = 0;
    m_throwsPosition.posInfo.col = 0;
    m_throwsPosition.posInfo.endLine = 0;
    m_throwsPosition.posInfo.endCol = 0;
    m_throwsPosition.posInfo.wideLine = 0;
    m_throwsPosition.posInfo.wideCol = 0;
    m_throwsPosition.posInfo.wideEndLine = 0;
    m_throwsPosition.posInfo.wideEndCol = 0;
  }

  NormalMethod::~NormalMethod() {
  }

  void NormalMethod::clone(const NormalMethod& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::MethodDeclaration::clone(other, false);

    m_methodKind = other.m_methodKind;
    m_isSynchronized = other.m_isSynchronized;
    m_synchronizedPosition.posInfo = other.m_synchronizedPosition.posInfo;
    m_isNative = other.m_isNative;
    m_nativePosition.posInfo = other.m_nativePosition.posInfo;
    m_throwsPosition.posInfo = other.m_throwsPosition.posInfo;
    hasParametersContainer = other.hasParametersContainer;
    m_hasBody = other.m_hasBody;
    hasThrownExceptionsContainer = other.hasThrownExceptionsContainer;
  }

  void NormalMethod::prepareDelete(bool tryOnVirtualParent){
    while (!hasParametersContainer.empty()) {
      const NodeId id = *hasParametersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNormalMethod_HasParameters);
      hasParametersContainer.pop_front();
    }
    removeBody();
    while (!hasThrownExceptionsContainer.empty()) {
      const NodeId id = *hasThrownExceptionsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNormalMethod_HasThrownExceptions);
      hasThrownExceptionsContainer.pop_front();
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
    struc::MethodDeclaration::prepareDelete(false);
  }

  MethodKind NormalMethod::getMethodKind() const {
    return m_methodKind;
  }

  bool NormalMethod::getIsSynchronized() const {
    return m_isSynchronized;
  }

  const Range NormalMethod::getSynchronizedPosition() const {
    return Range(factory->getStringTable(), m_synchronizedPosition.posInfo);
  }

  int NormalMethod::compareBySynchronizedPosition(const NormalMethod& other) const {
    if (m_synchronizedPosition.posInfo.path != other.m_synchronizedPosition.posInfo.path) {
      return (m_synchronizedPosition.posInfo.path < other.m_synchronizedPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_synchronizedPosition.posInfo.wideLine != other.m_synchronizedPosition.posInfo.wideLine) {
      return (m_synchronizedPosition.posInfo.wideLine < other.m_synchronizedPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_synchronizedPosition.posInfo.wideCol != other.m_synchronizedPosition.posInfo.wideCol) {
      return (m_synchronizedPosition.posInfo.wideCol < other.m_synchronizedPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_synchronizedPosition.posInfo.wideEndLine != other.m_synchronizedPosition.posInfo.wideEndLine) {
      return (m_synchronizedPosition.posInfo.wideEndLine > other.m_synchronizedPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_synchronizedPosition.posInfo.wideEndCol != other.m_synchronizedPosition.posInfo.wideEndCol) {
      return (m_synchronizedPosition.posInfo.wideEndCol > other.m_synchronizedPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  bool NormalMethod::getIsNative() const {
    return m_isNative;
  }

  const Range NormalMethod::getNativePosition() const {
    return Range(factory->getStringTable(), m_nativePosition.posInfo);
  }

  int NormalMethod::compareByNativePosition(const NormalMethod& other) const {
    if (m_nativePosition.posInfo.path != other.m_nativePosition.posInfo.path) {
      return (m_nativePosition.posInfo.path < other.m_nativePosition.posInfo.path) ? -1 :1 ;
    };
    if (m_nativePosition.posInfo.wideLine != other.m_nativePosition.posInfo.wideLine) {
      return (m_nativePosition.posInfo.wideLine < other.m_nativePosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_nativePosition.posInfo.wideCol != other.m_nativePosition.posInfo.wideCol) {
      return (m_nativePosition.posInfo.wideCol < other.m_nativePosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_nativePosition.posInfo.wideEndLine != other.m_nativePosition.posInfo.wideEndLine) {
      return (m_nativePosition.posInfo.wideEndLine > other.m_nativePosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_nativePosition.posInfo.wideEndCol != other.m_nativePosition.posInfo.wideEndCol) {
      return (m_nativePosition.posInfo.wideEndCol > other.m_nativePosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range NormalMethod::getThrowsPosition() const {
    return Range(factory->getStringTable(), m_throwsPosition.posInfo);
  }

  int NormalMethod::compareByThrowsPosition(const NormalMethod& other) const {
    if (m_throwsPosition.posInfo.path != other.m_throwsPosition.posInfo.path) {
      return (m_throwsPosition.posInfo.path < other.m_throwsPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_throwsPosition.posInfo.wideLine != other.m_throwsPosition.posInfo.wideLine) {
      return (m_throwsPosition.posInfo.wideLine < other.m_throwsPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_throwsPosition.posInfo.wideCol != other.m_throwsPosition.posInfo.wideCol) {
      return (m_throwsPosition.posInfo.wideCol < other.m_throwsPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_throwsPosition.posInfo.wideEndLine != other.m_throwsPosition.posInfo.wideEndLine) {
      return (m_throwsPosition.posInfo.wideEndLine > other.m_throwsPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_throwsPosition.posInfo.wideEndCol != other.m_throwsPosition.posInfo.wideEndCol) {
      return (m_throwsPosition.posInfo.wideEndCol > other.m_throwsPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void NormalMethod::setMethodKind(MethodKind _methodKind) {
    m_methodKind = _methodKind;
  }

  void NormalMethod::setIsSynchronized(bool _isSynchronized) {
    m_isSynchronized = _isSynchronized;
  }

  void NormalMethod::setSynchronizedPosition(const Range& _synchronizedPosition) {
    m_synchronizedPosition.posInfo = _synchronizedPosition.positionInfo;
    if (_synchronizedPosition.strTable != &factory->getStringTable())
      m_synchronizedPosition.posInfo.path = factory->getStringTable().set(_synchronizedPosition.getPath());
  }

  void NormalMethod::setIsNative(bool _isNative) {
    m_isNative = _isNative;
  }

  void NormalMethod::setNativePosition(const Range& _nativePosition) {
    m_nativePosition.posInfo = _nativePosition.positionInfo;
    if (_nativePosition.strTable != &factory->getStringTable())
      m_nativePosition.posInfo.path = factory->getStringTable().set(_nativePosition.getPath());
  }

  void NormalMethod::setThrowsPosition(const Range& _throwsPosition) {
    m_throwsPosition.posInfo = _throwsPosition.positionInfo;
    if (_throwsPosition.strTable != &factory->getStringTable())
      m_throwsPosition.posInfo.path = factory->getStringTable().set(_throwsPosition.getPath());
  }

  ListIterator<struc::Parameter> NormalMethod::getParametersListIteratorBegin() const {
    return ListIterator<struc::Parameter>(&hasParametersContainer, factory, true);
  }

  ListIterator<struc::Parameter> NormalMethod::getParametersListIteratorEnd() const {
    return ListIterator<struc::Parameter>(&hasParametersContainer, factory, false);
  }

  bool NormalMethod::getParametersIsEmpty() const {
    return getParametersListIteratorBegin() == getParametersListIteratorEnd();
  }

  unsigned int NormalMethod::getParametersSize() const {
    unsigned int size = 0;
    ListIterator<struc::Parameter> endIt = getParametersListIteratorEnd();
    for (ListIterator<struc::Parameter> it = getParametersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  statm::Block* NormalMethod::getBody() const {
    statm::Block *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<statm::Block*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::TypeExpression> NormalMethod::getThrownExceptionsListIteratorBegin() const {
    return ListIterator<expr::TypeExpression>(&hasThrownExceptionsContainer, factory, true);
  }

  ListIterator<expr::TypeExpression> NormalMethod::getThrownExceptionsListIteratorEnd() const {
    return ListIterator<expr::TypeExpression>(&hasThrownExceptionsContainer, factory, false);
  }

  bool NormalMethod::getThrownExceptionsIsEmpty() const {
    return getThrownExceptionsListIteratorBegin() == getThrownExceptionsListIteratorEnd();
  }

  unsigned int NormalMethod::getThrownExceptionsSize() const {
    unsigned int size = 0;
    ListIterator<expr::TypeExpression> endIt = getThrownExceptionsListIteratorEnd();
    for (ListIterator<expr::TypeExpression> it = getThrownExceptionsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool NormalMethod::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNormalMethod_HasParameters:
        addParameters(edgeEnd);
        return true;
      case edkNormalMethod_HasBody:
        setBody(edgeEnd);
        return true;
      case edkNormalMethod_HasThrownExceptions:
        addThrownExceptions(edgeEnd);
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
    if (struc::MethodDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NormalMethod::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNormalMethod_HasParameters:
        removeParameters(edgeEnd);
        return true;
      case edkNormalMethod_HasBody:
        removeBody();
        return true;
      case edkNormalMethod_HasThrownExceptions:
        removeThrownExceptions(edgeEnd);
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
    if (struc::MethodDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NormalMethod::addParameters(const struc::Parameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkParameter) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasParametersContainer.push_back(_node->getId());
    setParentEdge(_node,edkNormalMethod_HasParameters);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNormalMethod_HasParameters);
  }

  void NormalMethod::addParameters(NodeId _id) {
    const struc::Parameter *node = dynamic_cast<struc::Parameter*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameters( node );
  }

  void NormalMethod::removeParameters(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::Parameter>::Container::iterator it = find(hasParametersContainer.begin(), hasParametersContainer.end(), id);

    if (it == hasParametersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParametersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNormalMethod_HasParameters);
  }

  void NormalMethod::removeParameters(struc::Parameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameters(_node->getId());
  }

  void NormalMethod::setBody(NodeId _id) {
    statm::Block *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Block*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkNormalMethod_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkNormalMethod_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkNormalMethod_HasBody);
    } else {
      if (m_hasBody) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NormalMethod::setBody(statm::Block *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void NormalMethod::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkNormalMethod_HasBody);
      }
      m_hasBody = 0;
  }

  void NormalMethod::addThrownExceptions(const expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasThrownExceptionsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNormalMethod_HasThrownExceptions);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNormalMethod_HasThrownExceptions);
  }

  void NormalMethod::addThrownExceptions(NodeId _id) {
    const expr::TypeExpression *node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addThrownExceptions( node );
  }

  void NormalMethod::removeThrownExceptions(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::TypeExpression>::Container::iterator it = find(hasThrownExceptionsContainer.begin(), hasThrownExceptionsContainer.end(), id);

    if (it == hasThrownExceptionsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasThrownExceptionsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNormalMethod_HasThrownExceptions);
  }

  void NormalMethod::removeThrownExceptions(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeThrownExceptions(_node->getId());
  }

  double NormalMethod::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const NormalMethod& node = dynamic_cast<const NormalMethod&>(base);
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
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getIsStrictfp() == getIsStrictfp()) ++matchAttrs;
      if(node.getMethodKind() == getMethodKind()) ++matchAttrs;
      if(node.getIsSynchronized() == getIsSynchronized()) ++matchAttrs;
      if(node.getIsNative() == getIsNative()) ++matchAttrs;
      return matchAttrs / (11 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void NormalMethod::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType NormalMethod::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::NormalMethod", strlen("struc::NormalMethod"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NormalMethod::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    MethodDeclaration::sort(false);
  }

  void NormalMethod::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    MethodDeclaration::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isSynchronized) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isNative) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUByte1(m_methodKind);
    factory->getStringTable().setType(m_synchronizedPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.path);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.line);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.col);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.endLine);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.endCol);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.wideLine);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.wideCol);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_synchronizedPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_nativePosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_nativePosition.posInfo.path);
    binIo.writeUInt4(m_nativePosition.posInfo.line);
    binIo.writeUInt4(m_nativePosition.posInfo.col);
    binIo.writeUInt4(m_nativePosition.posInfo.endLine);
    binIo.writeUInt4(m_nativePosition.posInfo.endCol);
    binIo.writeUInt4(m_nativePosition.posInfo.wideLine);
    binIo.writeUInt4(m_nativePosition.posInfo.wideCol);
    binIo.writeUInt4(m_nativePosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_nativePosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_throwsPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_throwsPosition.posInfo.path);
    binIo.writeUInt4(m_throwsPosition.posInfo.line);
    binIo.writeUInt4(m_throwsPosition.posInfo.col);
    binIo.writeUInt4(m_throwsPosition.posInfo.endLine);
    binIo.writeUInt4(m_throwsPosition.posInfo.endCol);
    binIo.writeUInt4(m_throwsPosition.posInfo.wideLine);
    binIo.writeUInt4(m_throwsPosition.posInfo.wideCol);
    binIo.writeUInt4(m_throwsPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_throwsPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasBody);


    for (ListIterator<struc::Parameter>::Container::const_iterator it = hasParametersContainer.begin(); it != hasParametersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<expr::TypeExpression>::Container::const_iterator it = hasThrownExceptionsContainer.begin(); it != hasThrownExceptionsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void NormalMethod::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    MethodDeclaration::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isNative = boolValues & 1;
    boolValues >>= 1;
    m_isSynchronized = boolValues & 1;
    boolValues >>= 1;
    m_methodKind = (MethodKind)binIo.readUByte1();
    m_synchronizedPosition.posInfo.path = binIo.readUInt4();
    m_synchronizedPosition.posInfo.line = binIo.readUInt4();
    m_synchronizedPosition.posInfo.col = binIo.readUInt4();
    m_synchronizedPosition.posInfo.endLine = binIo.readUInt4();
    m_synchronizedPosition.posInfo.endCol = binIo.readUInt4();
    m_synchronizedPosition.posInfo.wideLine = binIo.readUInt4();
    m_synchronizedPosition.posInfo.wideCol = binIo.readUInt4();
    m_synchronizedPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_synchronizedPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_nativePosition.posInfo.path = binIo.readUInt4();
    m_nativePosition.posInfo.line = binIo.readUInt4();
    m_nativePosition.posInfo.col = binIo.readUInt4();
    m_nativePosition.posInfo.endLine = binIo.readUInt4();
    m_nativePosition.posInfo.endCol = binIo.readUInt4();
    m_nativePosition.posInfo.wideLine = binIo.readUInt4();
    m_nativePosition.posInfo.wideCol = binIo.readUInt4();
    m_nativePosition.posInfo.wideEndLine = binIo.readUInt4();
    m_nativePosition.posInfo.wideEndCol = binIo.readUInt4();
    m_throwsPosition.posInfo.path = binIo.readUInt4();
    m_throwsPosition.posInfo.line = binIo.readUInt4();
    m_throwsPosition.posInfo.col = binIo.readUInt4();
    m_throwsPosition.posInfo.endLine = binIo.readUInt4();
    m_throwsPosition.posInfo.endCol = binIo.readUInt4();
    m_throwsPosition.posInfo.wideLine = binIo.readUInt4();
    m_throwsPosition.posInfo.wideCol = binIo.readUInt4();
    m_throwsPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_throwsPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkNormalMethod_HasBody);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasParametersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNormalMethod_HasParameters);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasThrownExceptionsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNormalMethod_HasThrownExceptions);
      _id = binIo.readUInt4();
    }
  }


}


}}}
