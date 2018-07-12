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
  VariableDeclaration::VariableDeclaration(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Declaration(_id, _factory),
    m_kind(dkVar),
    hasDeclarationsContainer()
  {
  }

  VariableDeclaration::~VariableDeclaration() {
  }

  void VariableDeclaration::prepareDelete(bool tryOnVirtualParent){
    while (!hasDeclarationsContainer.empty()) {
      const NodeId id = *hasDeclarationsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkVariableDeclaration_HasDeclarations);
      hasDeclarationsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    declaration::Declaration::prepareDelete(false);
  }

  NodeKind VariableDeclaration::getNodeKind() const {
    return ndkVariableDeclaration;
  }

  DeclarationKind VariableDeclaration::getKind() const {
    return m_kind;
  }

  void VariableDeclaration::setKind(DeclarationKind _kind) {
    m_kind = _kind;
  }

  ListIterator<declaration::VariableDeclarator> VariableDeclaration::getDeclarationsListIteratorBegin() const {
    return ListIterator<declaration::VariableDeclarator>(&hasDeclarationsContainer, factory, true);
  }

  ListIterator<declaration::VariableDeclarator> VariableDeclaration::getDeclarationsListIteratorEnd() const {
    return ListIterator<declaration::VariableDeclarator>(&hasDeclarationsContainer, factory, false);
  }

  bool VariableDeclaration::getDeclarationsIsEmpty() const {
    return getDeclarationsListIteratorBegin() == getDeclarationsListIteratorEnd();
  }

  unsigned int VariableDeclaration::getDeclarationsSize() const {
    unsigned int size = 0;
    ListIterator<declaration::VariableDeclarator> endIt = getDeclarationsListIteratorEnd();
    for (ListIterator<declaration::VariableDeclarator> it = getDeclarationsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool VariableDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclaration_HasDeclarations:
        addDeclarations(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (declaration::Declaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool VariableDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclaration_HasDeclarations:
        removeDeclarations(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (declaration::Declaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void VariableDeclaration::addDeclarations(const declaration::VariableDeclarator *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkVariableDeclarator) ))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasDeclarationsContainer.push_back(_node->getId());
    setParentEdge(_node,edkVariableDeclaration_HasDeclarations);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkVariableDeclaration_HasDeclarations);
  }

  void VariableDeclaration::addDeclarations(NodeId _id) {
    const declaration::VariableDeclarator *node = dynamic_cast<declaration::VariableDeclarator*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addDeclarations( node );
  }

  void VariableDeclaration::removeDeclarations(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<declaration::VariableDeclarator>::Container::iterator it = find(hasDeclarationsContainer.begin(), hasDeclarationsContainer.end(), id);

    if (it == hasDeclarationsContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasDeclarationsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkVariableDeclaration_HasDeclarations);
  }

  void VariableDeclaration::removeDeclarations(declaration::VariableDeclarator *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeDeclarations(_node->getId());
  }

  void VariableDeclaration::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void VariableDeclaration::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double VariableDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const VariableDeclaration& node = dynamic_cast<const VariableDeclaration&>(base);
      double matchAttrs = 0;
      if(node.getKind() == getKind()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void VariableDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType VariableDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "declaration::VariableDeclaration", strlen("declaration::VariableDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void VariableDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Declaration::save(binIo,false);

    binIo.writeUByte1(m_kind);


    for (ListIterator<declaration::VariableDeclarator>::Container::const_iterator it = hasDeclarationsContainer.begin(); it != hasDeclarationsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void VariableDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Declaration::load(binIo,false);

    m_kind = (DeclarationKind)binIo.readUByte1();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasDeclarationsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkVariableDeclaration_HasDeclarations);
      _id = binIo.readUInt4();
    }
  }


}


}}}
