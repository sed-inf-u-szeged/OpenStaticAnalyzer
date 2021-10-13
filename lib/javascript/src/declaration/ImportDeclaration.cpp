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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace declaration { 
  ImportDeclaration::ImportDeclaration(NodeId _id, Factory *_factory) :
    ModuleDeclaration(_id, _factory),
    hasSpecifiersContainer(),
    m_hasSource(0)
  {
  }

  ImportDeclaration::~ImportDeclaration() {
  }

  void ImportDeclaration::prepareDelete(bool tryOnVirtualParent){
    while (!hasSpecifiersContainer.empty()) {
      const NodeId id = *hasSpecifiersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkImportDeclaration_HasSpecifiers);
      hasSpecifiersContainer.pop_front();
    }
    removeSource();
    declaration::ModuleDeclaration::prepareDelete(false);
  }

  NodeKind ImportDeclaration::getNodeKind() const {
    return ndkImportDeclaration;
  }

  ListIterator<structure::ImpSpecifier> ImportDeclaration::getSpecifiersListIteratorBegin() const {
    return ListIterator<structure::ImpSpecifier>(&hasSpecifiersContainer, factory, true);
  }

  ListIterator<structure::ImpSpecifier> ImportDeclaration::getSpecifiersListIteratorEnd() const {
    return ListIterator<structure::ImpSpecifier>(&hasSpecifiersContainer, factory, false);
  }

  bool ImportDeclaration::getSpecifiersIsEmpty() const {
    return getSpecifiersListIteratorBegin() == getSpecifiersListIteratorEnd();
  }

  unsigned int ImportDeclaration::getSpecifiersSize() const {
    unsigned int size = 0;
    ListIterator<structure::ImpSpecifier> endIt = getSpecifiersListIteratorEnd();
    for (ListIterator<structure::ImpSpecifier> it = getSpecifiersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::Literal* ImportDeclaration::getSource() const {
    expression::Literal *_node = NULL;
    if (m_hasSource != 0)
      _node = dynamic_cast<expression::Literal*>(factory->getPointer(m_hasSource));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ImportDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportDeclaration_HasSpecifiers:
        addSpecifiers(edgeEnd);
        return true;
      case edkImportDeclaration_HasSource:
        setSource(edgeEnd);
        return true;
      default:
        break;
    }
    if (declaration::ModuleDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ImportDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportDeclaration_HasSpecifiers:
        removeSpecifiers(edgeEnd);
        return true;
      case edkImportDeclaration_HasSource:
        removeSource();
        return true;
      default:
        break;
    }
    if (declaration::ModuleDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ImportDeclaration::addSpecifiers(const structure::ImpSpecifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsImpSpecifier(*_node)))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasSpecifiersContainer.push_back(_node->getId());
    setParentEdge(_node,edkImportDeclaration_HasSpecifiers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkImportDeclaration_HasSpecifiers);
  }

  void ImportDeclaration::addSpecifiers(NodeId _id) {
    const structure::ImpSpecifier *node = dynamic_cast<structure::ImpSpecifier*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSpecifiers( node );
  }

  void ImportDeclaration::removeSpecifiers(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::ImpSpecifier>::Container::iterator it = find(hasSpecifiersContainer.begin(), hasSpecifiersContainer.end(), id);

    if (it == hasSpecifiersContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasSpecifiersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkImportDeclaration_HasSpecifiers);
  }

  void ImportDeclaration::removeSpecifiers(structure::ImpSpecifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSpecifiers(_node->getId());
  }

  void ImportDeclaration::setSource(NodeId _id) {
    expression::Literal *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Literal*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSource) {
        removeParentEdge(m_hasSource);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkImportDeclaration_HasSource);
      }
      m_hasSource = _node->getId();
      if (m_hasSource != 0)
        setParentEdge(factory->getPointer(m_hasSource), edkImportDeclaration_HasSource);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSource, this->getId(), edkImportDeclaration_HasSource);
    } else {
      if (m_hasSource) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ImportDeclaration::setSource(expression::Literal *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSource(_node->getId());
  }

  void ImportDeclaration::removeSource() {
      if (m_hasSource) {
        removeParentEdge(m_hasSource);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkImportDeclaration_HasSource);
      }
      m_hasSource = 0;
  }

  void ImportDeclaration::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ImportDeclaration::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ImportDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ImportDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ImportDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "declaration::ImportDeclaration", strlen("declaration::ImportDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ImportDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ModuleDeclaration::save(binIo,false);

    binIo.writeUInt4(m_hasSource);


    for (ListIterator<structure::ImpSpecifier>::Container::const_iterator it = hasSpecifiersContainer.begin(); it != hasSpecifiersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ImportDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ModuleDeclaration::load(binIo,false);

    m_hasSource =  binIo.readUInt4();
    if (m_hasSource != 0)
      setParentEdge(factory->getPointer(m_hasSource),edkImportDeclaration_HasSource);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasSpecifiersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkImportDeclaration_HasSpecifiers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
