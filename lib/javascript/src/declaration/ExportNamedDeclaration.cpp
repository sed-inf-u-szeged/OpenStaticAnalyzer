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
  ExportNamedDeclaration::ExportNamedDeclaration(NodeId _id, Factory *_factory) :
    ModuleDeclaration(_id, _factory),
    m_hasDeclaration(0),
    hasSpecifiersContainer(),
    m_hasSource(0)
  {
  }

  ExportNamedDeclaration::~ExportNamedDeclaration() {
  }

  void ExportNamedDeclaration::prepareDelete(bool tryOnVirtualParent){
    removeDeclaration();
    while (!hasSpecifiersContainer.empty()) {
      const NodeId id = *hasSpecifiersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkExportNamedDeclaration_HasSpecifiers);
      hasSpecifiersContainer.pop_front();
    }
    removeSource();
    declaration::ModuleDeclaration::prepareDelete(false);
  }

  NodeKind ExportNamedDeclaration::getNodeKind() const {
    return ndkExportNamedDeclaration;
  }

  declaration::Declaration* ExportNamedDeclaration::getDeclaration() const {
    declaration::Declaration *_node = NULL;
    if (m_hasDeclaration != 0)
      _node = dynamic_cast<declaration::Declaration*>(factory->getPointer(m_hasDeclaration));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<structure::ExportSpecifier> ExportNamedDeclaration::getSpecifiersListIteratorBegin() const {
    return ListIterator<structure::ExportSpecifier>(&hasSpecifiersContainer, factory, true);
  }

  ListIterator<structure::ExportSpecifier> ExportNamedDeclaration::getSpecifiersListIteratorEnd() const {
    return ListIterator<structure::ExportSpecifier>(&hasSpecifiersContainer, factory, false);
  }

  bool ExportNamedDeclaration::getSpecifiersIsEmpty() const {
    return getSpecifiersListIteratorBegin() == getSpecifiersListIteratorEnd();
  }

  unsigned int ExportNamedDeclaration::getSpecifiersSize() const {
    unsigned int size = 0;
    ListIterator<structure::ExportSpecifier> endIt = getSpecifiersListIteratorEnd();
    for (ListIterator<structure::ExportSpecifier> it = getSpecifiersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::Literal* ExportNamedDeclaration::getSource() const {
    expression::Literal *_node = NULL;
    if (m_hasSource != 0)
      _node = dynamic_cast<expression::Literal*>(factory->getPointer(m_hasSource));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ExportNamedDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExportNamedDeclaration_HasDeclaration:
        setDeclaration(edgeEnd);
        return true;
      case edkExportNamedDeclaration_HasSpecifiers:
        addSpecifiers(edgeEnd);
        return true;
      case edkExportNamedDeclaration_HasSource:
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

  bool ExportNamedDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExportNamedDeclaration_HasDeclaration:
        removeDeclaration();
        return true;
      case edkExportNamedDeclaration_HasSpecifiers:
        removeSpecifiers(edgeEnd);
        return true;
      case edkExportNamedDeclaration_HasSource:
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

  void ExportNamedDeclaration::setDeclaration(NodeId _id) {
    declaration::Declaration *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<declaration::Declaration*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasDeclaration) {
        removeParentEdge(m_hasDeclaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDeclaration, m_id, edkExportNamedDeclaration_HasDeclaration);
      }
      m_hasDeclaration = _node->getId();
      if (m_hasDeclaration != 0)
        setParentEdge(factory->getPointer(m_hasDeclaration), edkExportNamedDeclaration_HasDeclaration);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasDeclaration, this->getId(), edkExportNamedDeclaration_HasDeclaration);
    } else {
      if (m_hasDeclaration) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ExportNamedDeclaration::setDeclaration(declaration::Declaration *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDeclaration(_node->getId());
  }

  void ExportNamedDeclaration::removeDeclaration() {
      if (m_hasDeclaration) {
        removeParentEdge(m_hasDeclaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDeclaration, m_id, edkExportNamedDeclaration_HasDeclaration);
      }
      m_hasDeclaration = 0;
  }

  void ExportNamedDeclaration::addSpecifiers(const structure::ExportSpecifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkExportSpecifier) ))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasSpecifiersContainer.push_back(_node->getId());
    setParentEdge(_node,edkExportNamedDeclaration_HasSpecifiers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkExportNamedDeclaration_HasSpecifiers);
  }

  void ExportNamedDeclaration::addSpecifiers(NodeId _id) {
    const structure::ExportSpecifier *node = dynamic_cast<structure::ExportSpecifier*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSpecifiers( node );
  }

  void ExportNamedDeclaration::removeSpecifiers(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::ExportSpecifier>::Container::iterator it = find(hasSpecifiersContainer.begin(), hasSpecifiersContainer.end(), id);

    if (it == hasSpecifiersContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasSpecifiersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkExportNamedDeclaration_HasSpecifiers);
  }

  void ExportNamedDeclaration::removeSpecifiers(structure::ExportSpecifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSpecifiers(_node->getId());
  }

  void ExportNamedDeclaration::setSource(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkExportNamedDeclaration_HasSource);
      }
      m_hasSource = _node->getId();
      if (m_hasSource != 0)
        setParentEdge(factory->getPointer(m_hasSource), edkExportNamedDeclaration_HasSource);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSource, this->getId(), edkExportNamedDeclaration_HasSource);
    } else {
      if (m_hasSource) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ExportNamedDeclaration::setSource(expression::Literal *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSource(_node->getId());
  }

  void ExportNamedDeclaration::removeSource() {
      if (m_hasSource) {
        removeParentEdge(m_hasSource);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSource, m_id, edkExportNamedDeclaration_HasSource);
      }
      m_hasSource = 0;
  }

  void ExportNamedDeclaration::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ExportNamedDeclaration::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ExportNamedDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ExportNamedDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ExportNamedDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "declaration::ExportNamedDeclaration", strlen("declaration::ExportNamedDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ExportNamedDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ModuleDeclaration::save(binIo,false);

    binIo.writeUInt4(m_hasDeclaration);
    binIo.writeUInt4(m_hasSource);


    for (ListIterator<structure::ExportSpecifier>::Container::const_iterator it = hasSpecifiersContainer.begin(); it != hasSpecifiersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ExportNamedDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ModuleDeclaration::load(binIo,false);

    m_hasDeclaration =  binIo.readUInt4();
    if (m_hasDeclaration != 0)
      setParentEdge(factory->getPointer(m_hasDeclaration),edkExportNamedDeclaration_HasDeclaration);

    m_hasSource =  binIo.readUInt4();
    if (m_hasSource != 0)
      setParentEdge(factory->getPointer(m_hasSource),edkExportNamedDeclaration_HasSource);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasSpecifiersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkExportNamedDeclaration_HasSpecifiers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
