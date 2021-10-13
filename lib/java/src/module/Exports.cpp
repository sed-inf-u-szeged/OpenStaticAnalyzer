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

namespace module { 
  Exports::Exports(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    ModuleDirective(_id, _factory),
    m_hasPackageName(0),
    hasModuleNamesContainer()
  {
  }

  Exports::~Exports() {
  }

  void Exports::clone(const Exports& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    module::ModuleDirective::clone(other, false);

    m_hasPackageName = other.m_hasPackageName;
    hasModuleNamesContainer = other.hasModuleNamesContainer;
  }

  void Exports::prepareDelete(bool tryOnVirtualParent){
    removePackageName();
    while (!hasModuleNamesContainer.empty()) {
      const NodeId id = *hasModuleNamesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkExports_HasModuleNames);
      hasModuleNamesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    module::ModuleDirective::prepareDelete(false);
  }

  NodeKind Exports::getNodeKind() const {
    return ndkExports;
  }

  expr::Expression* Exports::getPackageName() const {
    expr::Expression *_node = NULL;
    if (m_hasPackageName != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasPackageName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::Expression> Exports::getModuleNamesListIteratorBegin() const {
    return ListIterator<expr::Expression>(&hasModuleNamesContainer, factory, true);
  }

  ListIterator<expr::Expression> Exports::getModuleNamesListIteratorEnd() const {
    return ListIterator<expr::Expression>(&hasModuleNamesContainer, factory, false);
  }

  bool Exports::getModuleNamesIsEmpty() const {
    return getModuleNamesListIteratorBegin() == getModuleNamesListIteratorEnd();
  }

  unsigned int Exports::getModuleNamesSize() const {
    unsigned int size = 0;
    ListIterator<expr::Expression> endIt = getModuleNamesListIteratorEnd();
    for (ListIterator<expr::Expression> it = getModuleNamesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Exports::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExports_HasPackageName:
        setPackageName(edgeEnd);
        return true;
      case edkExports_HasModuleNames:
        addModuleNames(edgeEnd);
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
    if (module::ModuleDirective::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Exports::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExports_HasPackageName:
        removePackageName();
        return true;
      case edkExports_HasModuleNames:
        removeModuleNames(edgeEnd);
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
    if (module::ModuleDirective::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Exports::setPackageName(NodeId _id) {
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

      if (m_hasPackageName) {
        removeParentEdge(m_hasPackageName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPackageName, m_id, edkExports_HasPackageName);
      }
      m_hasPackageName = _node->getId();
      if (m_hasPackageName != 0)
        setParentEdge(factory->getPointer(m_hasPackageName), edkExports_HasPackageName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasPackageName, this->getId(), edkExports_HasPackageName);
    } else {
      if (m_hasPackageName) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Exports::setPackageName(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPackageName(_node->getId());
  }

  void Exports::removePackageName() {
      if (m_hasPackageName) {
        removeParentEdge(m_hasPackageName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPackageName, m_id, edkExports_HasPackageName);
      }
      m_hasPackageName = 0;
  }

  void Exports::addModuleNames(const expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasModuleNamesContainer.push_back(_node->getId());
    setParentEdge(_node,edkExports_HasModuleNames);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkExports_HasModuleNames);
  }

  void Exports::addModuleNames(NodeId _id) {
    const expr::Expression *node = dynamic_cast<expr::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addModuleNames( node );
  }

  void Exports::removeModuleNames(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::Expression>::Container::iterator it = find(hasModuleNamesContainer.begin(), hasModuleNamesContainer.end(), id);

    if (it == hasModuleNamesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasModuleNamesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkExports_HasModuleNames);
  }

  void Exports::removeModuleNames(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeModuleNames(_node->getId());
  }

  void Exports::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Exports::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Exports::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Exports& node = dynamic_cast<const Exports&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Exports::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Exports::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "module::Exports", strlen("module::Exports"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Exports::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    ModuleDirective::sort(false);
  }

  void Exports::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    ModuleDirective::save(binIo,false);

    binIo.writeUInt4(m_hasPackageName);


    for (ListIterator<expr::Expression>::Container::const_iterator it = hasModuleNamesContainer.begin(); it != hasModuleNamesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Exports::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    ModuleDirective::load(binIo,false);

    m_hasPackageName =  binIo.readUInt4();
    if (m_hasPackageName != 0)
      setParentEdge(factory->getPointer(m_hasPackageName),edkExports_HasPackageName);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasModuleNamesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkExports_HasModuleNames);
      _id = binIo.readUInt4();
    }
  }


}


}}}
