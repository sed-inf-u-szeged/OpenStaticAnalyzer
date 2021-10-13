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
  ModuleDeclaration::ModuleDeclaration(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Positioned(_id, _factory),
    m_moduleKind(mkOpen),
    m_hasName(0),
    hasDirectivesContainer(),
    m_moduleType(0),
    m_refersTo(0)
  {
  }

  ModuleDeclaration::~ModuleDeclaration() {
  }

  void ModuleDeclaration::clone(const ModuleDeclaration& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    base::Positioned::clone(other, false);

    m_moduleKind = other.m_moduleKind;
    m_hasName = other.m_hasName;
    hasDirectivesContainer = other.hasDirectivesContainer;
    m_moduleType = other.m_moduleType;
    m_refersTo = other.m_refersTo;
  }

  void ModuleDeclaration::prepareDelete(bool tryOnVirtualParent){
    removeName();
    while (!hasDirectivesContainer.empty()) {
      const NodeId id = *hasDirectivesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkModuleDeclaration_HasDirectives);
      hasDirectivesContainer.pop_front();
    }
    removeModuleType();
    removeRefersTo();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind ModuleDeclaration::getNodeKind() const {
    return ndkModuleDeclaration;
  }

  ModuleKind ModuleDeclaration::getModuleKind() const {
    return m_moduleKind;
  }

  void ModuleDeclaration::setModuleKind(ModuleKind _moduleKind) {
    m_moduleKind = _moduleKind;
  }

  expr::Expression* ModuleDeclaration::getName() const {
    expr::Expression *_node = NULL;
    if (m_hasName != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<module::ModuleDirective> ModuleDeclaration::getDirectivesListIteratorBegin() const {
    return ListIterator<module::ModuleDirective>(&hasDirectivesContainer, factory, true);
  }

  ListIterator<module::ModuleDirective> ModuleDeclaration::getDirectivesListIteratorEnd() const {
    return ListIterator<module::ModuleDirective>(&hasDirectivesContainer, factory, false);
  }

  bool ModuleDeclaration::getDirectivesIsEmpty() const {
    return getDirectivesListIteratorBegin() == getDirectivesListIteratorEnd();
  }

  unsigned int ModuleDeclaration::getDirectivesSize() const {
    unsigned int size = 0;
    ListIterator<module::ModuleDirective> endIt = getDirectivesListIteratorEnd();
    for (ListIterator<module::ModuleDirective> it = getDirectivesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  type::ModuleType* ModuleDeclaration::getModuleType() const {
    type::ModuleType *_node = NULL;
    if (m_moduleType != 0)
      _node = dynamic_cast<type::ModuleType*>(factory->getPointer(m_moduleType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  struc::Module* ModuleDeclaration::getRefersTo() const {
    struc::Module *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<struc::Module*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ModuleDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModuleDeclaration_HasName:
        setName(edgeEnd);
        return true;
      case edkModuleDeclaration_HasDirectives:
        addDirectives(edgeEnd);
        return true;
      case edkModuleDeclaration_ModuleType:
        setModuleType(edgeEnd);
        return true;
      case edkModuleDeclaration_RefersTo:
        setRefersTo(edgeEnd);
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
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ModuleDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModuleDeclaration_HasName:
        removeName();
        return true;
      case edkModuleDeclaration_HasDirectives:
        removeDirectives(edgeEnd);
        return true;
      case edkModuleDeclaration_ModuleType:
        removeModuleType();
        return true;
      case edkModuleDeclaration_RefersTo:
        removeRefersTo();
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
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ModuleDeclaration::setName(NodeId _id) {
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

      if (m_hasName) {
        removeParentEdge(m_hasName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasName, m_id, edkModuleDeclaration_HasName);
      }
      m_hasName = _node->getId();
      if (m_hasName != 0)
        setParentEdge(factory->getPointer(m_hasName), edkModuleDeclaration_HasName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasName, this->getId(), edkModuleDeclaration_HasName);
    } else {
      if (m_hasName) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ModuleDeclaration::setName(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void ModuleDeclaration::removeName() {
      if (m_hasName) {
        removeParentEdge(m_hasName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasName, m_id, edkModuleDeclaration_HasName);
      }
      m_hasName = 0;
  }

  void ModuleDeclaration::addDirectives(const module::ModuleDirective *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsModuleDirective(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasDirectivesContainer.push_back(_node->getId());
    setParentEdge(_node,edkModuleDeclaration_HasDirectives);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkModuleDeclaration_HasDirectives);
  }

  void ModuleDeclaration::addDirectives(NodeId _id) {
    const module::ModuleDirective *node = dynamic_cast<module::ModuleDirective*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addDirectives( node );
  }

  void ModuleDeclaration::removeDirectives(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<module::ModuleDirective>::Container::iterator it = find(hasDirectivesContainer.begin(), hasDirectivesContainer.end(), id);

    if (it == hasDirectivesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasDirectivesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkModuleDeclaration_HasDirectives);
  }

  void ModuleDeclaration::removeDirectives(module::ModuleDirective *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeDirectives(_node->getId());
  }

  void ModuleDeclaration::setModuleType(NodeId _id) {
    type::ModuleType *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<type::ModuleType*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_moduleType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_moduleType, m_id, edkModuleDeclaration_ModuleType);
      }
      m_moduleType = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_moduleType, this->getId(), edkModuleDeclaration_ModuleType);
    } else {
      if (m_moduleType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ModuleDeclaration::setModuleType(type::ModuleType *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setModuleType(_node->getId());
  }

  void ModuleDeclaration::removeModuleType() {
      if (m_moduleType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_moduleType, m_id, edkModuleDeclaration_ModuleType);
      }
      m_moduleType = 0;
  }

  void ModuleDeclaration::setRefersTo(NodeId _id) {
    struc::Module *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::Module*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkModuleDeclaration_RefersTo);
      }
      m_refersTo = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkModuleDeclaration_RefersTo);
    } else {
      if (m_refersTo) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ModuleDeclaration::setRefersTo(struc::Module *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void ModuleDeclaration::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkModuleDeclaration_RefersTo);
      }
      m_refersTo = 0;
  }

  void ModuleDeclaration::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ModuleDeclaration::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ModuleDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ModuleDeclaration& node = dynamic_cast<const ModuleDeclaration&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      if(node.getModuleKind() == getModuleKind()) ++matchAttrs;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ModuleDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ModuleDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::ModuleDeclaration", strlen("struc::ModuleDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ModuleDeclaration::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Positioned::sort(false);
  }

  void ModuleDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Positioned::save(binIo,false);

    binIo.writeUByte1(m_moduleKind);

    binIo.writeUInt4(m_hasName);
    binIo.writeUInt4(m_moduleType);
    binIo.writeUInt4(m_refersTo);


    for (ListIterator<module::ModuleDirective>::Container::const_iterator it = hasDirectivesContainer.begin(); it != hasDirectivesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ModuleDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Positioned::load(binIo,false);

    m_moduleKind = (ModuleKind)binIo.readUByte1();

    m_hasName =  binIo.readUInt4();
    if (m_hasName != 0)
      setParentEdge(factory->getPointer(m_hasName),edkModuleDeclaration_HasName);

    m_moduleType =  binIo.readUInt4();

    m_refersTo =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasDirectivesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkModuleDeclaration_HasDirectives);
      _id = binIo.readUInt4();
    }
  }


}


}}}
