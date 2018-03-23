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

namespace expression { 
  IdentifierNameSyntax::IdentifierNameSyntax(NodeId _id, Factory *_factory) :
    SimpleNameSyntax(_id, _factory),
    AccessorCallContainer(),
    m_Declaration(0)
  {
  }

  IdentifierNameSyntax::~IdentifierNameSyntax() {
  }

  void IdentifierNameSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AccessorCallContainer.empty()) {
      const NodeId id = *AccessorCallContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkIdentifierNameSyntax_AccessorCall);
      AccessorCallContainer.pop_front();
    }
    removeDeclaration();
    expression::SimpleNameSyntax::prepareDelete(false);
  }

  NodeKind IdentifierNameSyntax::getNodeKind() const {
    return ndkIdentifierNameSyntax;
  }

  ListIterator<structure::AccessorDeclarationSyntax> IdentifierNameSyntax::getAccessorCallListIteratorBegin() const {
    return ListIterator<structure::AccessorDeclarationSyntax>(&AccessorCallContainer, factory, true);
  }

  ListIterator<structure::AccessorDeclarationSyntax> IdentifierNameSyntax::getAccessorCallListIteratorEnd() const {
    return ListIterator<structure::AccessorDeclarationSyntax>(&AccessorCallContainer, factory, false);
  }

  bool IdentifierNameSyntax::getAccessorCallIsEmpty() const {
    return getAccessorCallListIteratorBegin() == getAccessorCallListIteratorEnd();
  }

  unsigned int IdentifierNameSyntax::getAccessorCallSize() const {
    unsigned int size = 0;
    ListIterator<structure::AccessorDeclarationSyntax> endIt = getAccessorCallListIteratorEnd();
    for (ListIterator<structure::AccessorDeclarationSyntax> it = getAccessorCallListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  base::Positioned* IdentifierNameSyntax::getDeclaration() const {
    base::Positioned *_node = NULL;
    if (m_Declaration != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_Declaration));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool IdentifierNameSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIdentifierNameSyntax_AccessorCall:
        addAccessorCall(edgeEnd);
        return true;
      case edkIdentifierNameSyntax_Declaration:
        setDeclaration(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::SimpleNameSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool IdentifierNameSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIdentifierNameSyntax_AccessorCall:
        removeAccessorCall(edgeEnd);
        return true;
      case edkIdentifierNameSyntax_Declaration:
        removeDeclaration();
        return true;
      default:
        break;
    }
    if (expression::SimpleNameSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void IdentifierNameSyntax::addAccessorCall(const structure::AccessorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAccessorDeclarationSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AccessorCallContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkIdentifierNameSyntax_AccessorCall);
  }

  void IdentifierNameSyntax::addAccessorCall(NodeId _id) {
    const structure::AccessorDeclarationSyntax *node = dynamic_cast<structure::AccessorDeclarationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAccessorCall( node );
  }

  void IdentifierNameSyntax::removeAccessorCall(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AccessorDeclarationSyntax>::Container::iterator it = find(AccessorCallContainer.begin(), AccessorCallContainer.end(), id);

    if (it == AccessorCallContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AccessorCallContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkIdentifierNameSyntax_AccessorCall);
  }

  void IdentifierNameSyntax::removeAccessorCall(structure::AccessorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAccessorCall(_node->getId());
  }

  void IdentifierNameSyntax::setDeclaration(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Declaration) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkIdentifierNameSyntax_Declaration);
      }
      m_Declaration = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Declaration, this->getId(), edkIdentifierNameSyntax_Declaration);
    } else {
      if (m_Declaration) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IdentifierNameSyntax::setDeclaration(base::Positioned *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDeclaration(_node->getId());
  }

  void IdentifierNameSyntax::removeDeclaration() {
      if (m_Declaration) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Declaration, m_id, edkIdentifierNameSyntax_Declaration);
      }
      m_Declaration = 0;
  }

  void IdentifierNameSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void IdentifierNameSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double IdentifierNameSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const IdentifierNameSyntax& node = dynamic_cast<const IdentifierNameSyntax&>(base);
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

  void IdentifierNameSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType IdentifierNameSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::IdentifierNameSyntax", strlen("expression::IdentifierNameSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void IdentifierNameSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleNameSyntax::save(binIo,false);

    binIo.writeUInt4(m_Declaration);


    for (ListIterator<structure::AccessorDeclarationSyntax>::Container::const_iterator it = AccessorCallContainer.begin(); it != AccessorCallContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void IdentifierNameSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleNameSyntax::load(binIo,false);

    m_Declaration =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AccessorCallContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
