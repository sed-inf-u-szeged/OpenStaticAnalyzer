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

namespace expression { 
  AnonymousObjectCreationExpressionSyntax::AnonymousObjectCreationExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_identifier(0),
    InitializersContainer()
  {
  }

  AnonymousObjectCreationExpressionSyntax::~AnonymousObjectCreationExpressionSyntax() {
  }

  void AnonymousObjectCreationExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!InitializersContainer.empty()) {
      const NodeId id = *InitializersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAnonymousObjectCreationExpressionSyntax_Initializers);
      InitializersContainer.pop_front();
    }
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind AnonymousObjectCreationExpressionSyntax::getNodeKind() const {
    return ndkAnonymousObjectCreationExpressionSyntax;
  }

  Key AnonymousObjectCreationExpressionSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& AnonymousObjectCreationExpressionSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void AnonymousObjectCreationExpressionSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void AnonymousObjectCreationExpressionSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax> AnonymousObjectCreationExpressionSyntax::getInitializersListIteratorBegin() const {
    return ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax>(&InitializersContainer, factory, true);
  }

  ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax> AnonymousObjectCreationExpressionSyntax::getInitializersListIteratorEnd() const {
    return ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax>(&InitializersContainer, factory, false);
  }

  bool AnonymousObjectCreationExpressionSyntax::getInitializersIsEmpty() const {
    return getInitializersListIteratorBegin() == getInitializersListIteratorEnd();
  }

  unsigned int AnonymousObjectCreationExpressionSyntax::getInitializersSize() const {
    unsigned int size = 0;
    ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax> endIt = getInitializersListIteratorEnd();
    for (ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax> it = getInitializersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool AnonymousObjectCreationExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnonymousObjectCreationExpressionSyntax_Initializers:
        addInitializers(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AnonymousObjectCreationExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnonymousObjectCreationExpressionSyntax_Initializers:
        removeInitializers(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AnonymousObjectCreationExpressionSyntax::addInitializers(const structure::AnonymousObjectMemberDeclaratorSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAnonymousObjectMemberDeclaratorSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    InitializersContainer.push_back(_node->getId());
    setParentEdge(_node,edkAnonymousObjectCreationExpressionSyntax_Initializers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAnonymousObjectCreationExpressionSyntax_Initializers);
  }

  void AnonymousObjectCreationExpressionSyntax::addInitializers(NodeId _id) {
    const structure::AnonymousObjectMemberDeclaratorSyntax *node = dynamic_cast<structure::AnonymousObjectMemberDeclaratorSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addInitializers( node );
  }

  void AnonymousObjectCreationExpressionSyntax::removeInitializers(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax>::Container::iterator it = find(InitializersContainer.begin(), InitializersContainer.end(), id);

    if (it == InitializersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    InitializersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAnonymousObjectCreationExpressionSyntax_Initializers);
  }

  void AnonymousObjectCreationExpressionSyntax::removeInitializers(structure::AnonymousObjectMemberDeclaratorSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeInitializers(_node->getId());
  }

  void AnonymousObjectCreationExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AnonymousObjectCreationExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AnonymousObjectCreationExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AnonymousObjectCreationExpressionSyntax& node = dynamic_cast<const AnonymousObjectCreationExpressionSyntax&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getIdentifier();
      str2 = node.getIdentifier();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void AnonymousObjectCreationExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_identifier);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_identifier = foundKeyId->second;
    } else {
      Key oldkey = m_identifier;
      m_identifier = newStrTable.set(factory->getStringTable().get(m_identifier));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_identifier));    }

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType AnonymousObjectCreationExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::AnonymousObjectCreationExpressionSyntax", strlen("expression::AnonymousObjectCreationExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnonymousObjectCreationExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);


    for (ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax>::Container::const_iterator it = InitializersContainer.begin(); it != InitializersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void AnonymousObjectCreationExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      InitializersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkAnonymousObjectCreationExpressionSyntax_Initializers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
