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

namespace expr { 
  MemberReference::MemberReference(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    FunctionalExpression(_id, _factory),
    m_mode(mrmkInvoke),
    m_referenceKind(mrkSuper),
    m_overloadKind(mrokOverloaded),
    m_name(0),
    m_hasQualifierExpression(0),
    hasTypeArgumentsContainer(),
    m_referredMethod(0)
  {
  }

  MemberReference::~MemberReference() {
  }

  void MemberReference::clone(const MemberReference& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::FunctionalExpression::clone(other, false);

    m_name = other.m_name;
    m_mode = other.m_mode;
    m_referenceKind = other.m_referenceKind;
    m_overloadKind = other.m_overloadKind;
    m_hasQualifierExpression = other.m_hasQualifierExpression;
    hasTypeArgumentsContainer = other.hasTypeArgumentsContainer;
    m_referredMethod = other.m_referredMethod;
  }

  void MemberReference::prepareDelete(bool tryOnVirtualParent){
    removeQualifierExpression();
    while (!hasTypeArgumentsContainer.empty()) {
      const NodeId id = *hasTypeArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMemberReference_HasTypeArguments);
      hasTypeArgumentsContainer.pop_front();
    }
    removeReferredMethod();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::FunctionalExpression::prepareDelete(false);
  }

  NodeKind MemberReference::getNodeKind() const {
    return ndkMemberReference;
  }

  Key MemberReference::getNameKey() const {
    return m_name;
  }

  const std::string& MemberReference::getName() const {
    return factory->getStringTable().get(m_name);
  }

  MemberReferenceModeKind MemberReference::getMode() const {
    return m_mode;
  }

  MemberReferenceKind MemberReference::getReferenceKind() const {
    return m_referenceKind;
  }

  MemberReferenceOverloadKind MemberReference::getOverloadKind() const {
    return m_overloadKind;
  }

  void MemberReference::setNameKey(Key _name) {
    m_name = _name;
  }

  void MemberReference::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  void MemberReference::setMode(MemberReferenceModeKind _mode) {
    m_mode = _mode;
  }

  void MemberReference::setReferenceKind(MemberReferenceKind _referenceKind) {
    m_referenceKind = _referenceKind;
  }

  void MemberReference::setOverloadKind(MemberReferenceOverloadKind _overloadKind) {
    m_overloadKind = _overloadKind;
  }

  expr::Expression* MemberReference::getQualifierExpression() const {
    expr::Expression *_node = NULL;
    if (m_hasQualifierExpression != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasQualifierExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::TypeExpression> MemberReference::getTypeArgumentsListIteratorBegin() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, true);
  }

  ListIterator<expr::TypeExpression> MemberReference::getTypeArgumentsListIteratorEnd() const {
    return ListIterator<expr::TypeExpression>(&hasTypeArgumentsContainer, factory, false);
  }

  bool MemberReference::getTypeArgumentsIsEmpty() const {
    return getTypeArgumentsListIteratorBegin() == getTypeArgumentsListIteratorEnd();
  }

  unsigned int MemberReference::getTypeArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<expr::TypeExpression> endIt = getTypeArgumentsListIteratorEnd();
    for (ListIterator<expr::TypeExpression> it = getTypeArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  struc::MethodDeclaration* MemberReference::getReferredMethod() const {
    struc::MethodDeclaration *_node = NULL;
    if (m_referredMethod != 0)
      _node = dynamic_cast<struc::MethodDeclaration*>(factory->getPointer(m_referredMethod));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool MemberReference::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMemberReference_HasQualifierExpression:
        setQualifierExpression(edgeEnd);
        return true;
      case edkMemberReference_HasTypeArguments:
        addTypeArguments(edgeEnd);
        return true;
      case edkMemberReference_ReferredMethod:
        setReferredMethod(edgeEnd);
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
    if (expr::FunctionalExpression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool MemberReference::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMemberReference_HasQualifierExpression:
        removeQualifierExpression();
        return true;
      case edkMemberReference_HasTypeArguments:
        removeTypeArguments(edgeEnd);
        return true;
      case edkMemberReference_ReferredMethod:
        removeReferredMethod();
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
    if (expr::FunctionalExpression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MemberReference::setQualifierExpression(NodeId _id) {
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

      if (m_hasQualifierExpression) {
        removeParentEdge(m_hasQualifierExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasQualifierExpression, m_id, edkMemberReference_HasQualifierExpression);
      }
      m_hasQualifierExpression = _node->getId();
      if (m_hasQualifierExpression != 0)
        setParentEdge(factory->getPointer(m_hasQualifierExpression), edkMemberReference_HasQualifierExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasQualifierExpression, this->getId(), edkMemberReference_HasQualifierExpression);
    } else {
      if (m_hasQualifierExpression) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MemberReference::setQualifierExpression(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setQualifierExpression(_node->getId());
  }

  void MemberReference::removeQualifierExpression() {
      if (m_hasQualifierExpression) {
        removeParentEdge(m_hasQualifierExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasQualifierExpression, m_id, edkMemberReference_HasQualifierExpression);
      }
      m_hasQualifierExpression = 0;
  }

  void MemberReference::addTypeArguments(const expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkMemberReference_HasTypeArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMemberReference_HasTypeArguments);
  }

  void MemberReference::addTypeArguments(NodeId _id) {
    const expr::TypeExpression *node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypeArguments( node );
  }

  void MemberReference::removeTypeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::TypeExpression>::Container::iterator it = find(hasTypeArgumentsContainer.begin(), hasTypeArgumentsContainer.end(), id);

    if (it == hasTypeArgumentsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMemberReference_HasTypeArguments);
  }

  void MemberReference::removeTypeArguments(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypeArguments(_node->getId());
  }

  void MemberReference::setReferredMethod(NodeId _id) {
    struc::MethodDeclaration *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::MethodDeclaration*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_referredMethod) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_referredMethod, m_id, edkMemberReference_ReferredMethod);
      }
      m_referredMethod = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_referredMethod, this->getId(), edkMemberReference_ReferredMethod);
    } else {
      if (m_referredMethod) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MemberReference::setReferredMethod(struc::MethodDeclaration *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReferredMethod(_node->getId());
  }

  void MemberReference::removeReferredMethod() {
      if (m_referredMethod) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_referredMethod, m_id, edkMemberReference_ReferredMethod);
      }
      m_referredMethod = 0;
  }

  void MemberReference::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MemberReference::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MemberReference::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const MemberReference& node = dynamic_cast<const MemberReference&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      if(node.getPolyKind() == getPolyKind()) ++matchAttrs;
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
      if(node.getMode() == getMode()) ++matchAttrs;
      if(node.getReferenceKind() == getReferenceKind()) ++matchAttrs;
      if(node.getOverloadKind() == getOverloadKind()) ++matchAttrs;
      return matchAttrs / (7 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void MemberReference::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType MemberReference::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::MemberReference", strlen("expr::MemberReference"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MemberReference::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    FunctionalExpression::sort(false);
  }

  void MemberReference::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    FunctionalExpression::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);
    binIo.writeUByte1(m_mode);
    binIo.writeUByte1(m_referenceKind);
    binIo.writeUByte1(m_overloadKind);

    binIo.writeUInt4(m_hasQualifierExpression);
    binIo.writeUInt4(m_referredMethod);


    for (ListIterator<expr::TypeExpression>::Container::const_iterator it = hasTypeArgumentsContainer.begin(); it != hasTypeArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void MemberReference::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    FunctionalExpression::load(binIo,false);

    m_name = binIo.readUInt4();
    m_mode = (MemberReferenceModeKind)binIo.readUByte1();
    m_referenceKind = (MemberReferenceKind)binIo.readUByte1();
    m_overloadKind = (MemberReferenceOverloadKind)binIo.readUByte1();

    m_hasQualifierExpression =  binIo.readUInt4();
    if (m_hasQualifierExpression != 0)
      setParentEdge(factory->getPointer(m_hasQualifierExpression),edkMemberReference_HasQualifierExpression);

    m_referredMethod =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkMemberReference_HasTypeArguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
