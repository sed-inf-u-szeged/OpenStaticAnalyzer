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
  CompilationUnit::CompilationUnit(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
    PositionedWithoutComment(_id, _factory),
    Commentable(_id, _factory),
    m_fileEncoding(0),
    m_hasPackageDeclaration(0),
    hasImportsContainer(),
    typeDeclarationsContainer(),
    hasOthersContainer()
  {
  }

  CompilationUnit::~CompilationUnit() {
  }

  void CompilationUnit::clone(const CompilationUnit& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    base::PositionedWithoutComment::clone(other, false);
    base::Commentable::clone(other, false);

    m_fileEncoding = other.m_fileEncoding;
    m_hasPackageDeclaration = other.m_hasPackageDeclaration;
    hasImportsContainer = other.hasImportsContainer;
    typeDeclarationsContainer = other.typeDeclarationsContainer;
    hasOthersContainer = other.hasOthersContainer;
  }

  void CompilationUnit::prepareDelete(bool tryOnVirtualParent){
    removePackageDeclaration();
    while (!hasImportsContainer.empty()) {
      const NodeId id = *hasImportsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnit_HasImports);
      hasImportsContainer.pop_front();
    }
    while (!typeDeclarationsContainer.empty()) {
      const NodeId id = *typeDeclarationsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnit_TypeDeclarations);
      typeDeclarationsContainer.pop_front();
    }
    while (!hasOthersContainer.empty()) {
      const NodeId id = *hasOthersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnit_HasOthers);
      hasOthersContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    base::PositionedWithoutComment::prepareDelete(false);
    base::Commentable::prepareDelete(false);
  }

  NodeKind CompilationUnit::getNodeKind() const {
    return ndkCompilationUnit;
  }

  Key CompilationUnit::getFileEncodingKey() const {
    return m_fileEncoding;
  }

  const std::string& CompilationUnit::getFileEncoding() const {
    return factory->getStringTable().get(m_fileEncoding);
  }

  void CompilationUnit::setFileEncodingKey(Key _fileEncoding) {
    m_fileEncoding = _fileEncoding;
  }

  void CompilationUnit::setFileEncoding(const std::string& _fileEncoding) {
    m_fileEncoding = factory->getStringTable().set(_fileEncoding);
  }

  struc::PackageDeclaration* CompilationUnit::getPackageDeclaration() const {
    struc::PackageDeclaration *_node = NULL;
    if (m_hasPackageDeclaration != 0)
      _node = dynamic_cast<struc::PackageDeclaration*>(factory->getPointer(m_hasPackageDeclaration));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<struc::Import> CompilationUnit::getImportsListIteratorBegin() const {
    return ListIterator<struc::Import>(&hasImportsContainer, factory, true);
  }

  ListIterator<struc::Import> CompilationUnit::getImportsListIteratorEnd() const {
    return ListIterator<struc::Import>(&hasImportsContainer, factory, false);
  }

  bool CompilationUnit::getImportsIsEmpty() const {
    return getImportsListIteratorBegin() == getImportsListIteratorEnd();
  }

  unsigned int CompilationUnit::getImportsSize() const {
    unsigned int size = 0;
    ListIterator<struc::Import> endIt = getImportsListIteratorEnd();
    for (ListIterator<struc::Import> it = getImportsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<struc::TypeDeclaration> CompilationUnit::getTypeDeclarationsListIteratorBegin() const {
    return ListIterator<struc::TypeDeclaration>(&typeDeclarationsContainer, factory, true);
  }

  ListIterator<struc::TypeDeclaration> CompilationUnit::getTypeDeclarationsListIteratorEnd() const {
    return ListIterator<struc::TypeDeclaration>(&typeDeclarationsContainer, factory, false);
  }

  bool CompilationUnit::getTypeDeclarationsIsEmpty() const {
    return getTypeDeclarationsListIteratorBegin() == getTypeDeclarationsListIteratorEnd();
  }

  unsigned int CompilationUnit::getTypeDeclarationsSize() const {
    unsigned int size = 0;
    ListIterator<struc::TypeDeclaration> endIt = getTypeDeclarationsListIteratorEnd();
    for (ListIterator<struc::TypeDeclaration> it = getTypeDeclarationsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<base::Positioned> CompilationUnit::getOthersListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasOthersContainer, factory, true);
  }

  ListIterator<base::Positioned> CompilationUnit::getOthersListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasOthersContainer, factory, false);
  }

  bool CompilationUnit::getOthersIsEmpty() const {
    return getOthersListIteratorBegin() == getOthersListIteratorEnd();
  }

  unsigned int CompilationUnit::getOthersSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getOthersListIteratorEnd();
    for (ListIterator<base::Positioned> it = getOthersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool CompilationUnit::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCompilationUnit_HasPackageDeclaration:
        setPackageDeclaration(edgeEnd);
        return true;
      case edkCompilationUnit_HasImports:
        addImports(edgeEnd);
        return true;
      case edkCompilationUnit_TypeDeclarations:
        addTypeDeclarations(edgeEnd);
        return true;
      case edkCompilationUnit_HasOthers:
        addOthers(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::PositionedWithoutComment::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CompilationUnit::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCompilationUnit_HasPackageDeclaration:
        removePackageDeclaration();
        return true;
      case edkCompilationUnit_HasImports:
        removeImports(edgeEnd);
        return true;
      case edkCompilationUnit_TypeDeclarations:
        removeTypeDeclarations(edgeEnd);
        return true;
      case edkCompilationUnit_HasOthers:
        removeOthers(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::PositionedWithoutComment::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CompilationUnit::setPackageDeclaration(NodeId _id) {
    struc::PackageDeclaration *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::PackageDeclaration*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasPackageDeclaration) {
        removeParentEdge(m_hasPackageDeclaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPackageDeclaration, m_id, edkCompilationUnit_HasPackageDeclaration);
      }
      m_hasPackageDeclaration = _node->getId();
      if (m_hasPackageDeclaration != 0)
        setParentEdge(factory->getPointer(m_hasPackageDeclaration), edkCompilationUnit_HasPackageDeclaration);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasPackageDeclaration, this->getId(), edkCompilationUnit_HasPackageDeclaration);
    } else {
      if (m_hasPackageDeclaration) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CompilationUnit::setPackageDeclaration(struc::PackageDeclaration *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPackageDeclaration(_node->getId());
  }

  void CompilationUnit::removePackageDeclaration() {
      if (m_hasPackageDeclaration) {
        removeParentEdge(m_hasPackageDeclaration);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPackageDeclaration, m_id, edkCompilationUnit_HasPackageDeclaration);
      }
      m_hasPackageDeclaration = 0;
  }

  void CompilationUnit::addImports(const struc::Import *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkImport) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasImportsContainer.push_back(_node->getId());
    setParentEdge(_node,edkCompilationUnit_HasImports);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCompilationUnit_HasImports);
  }

  void CompilationUnit::addImports(NodeId _id) {
    const struc::Import *node = dynamic_cast<struc::Import*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addImports( node );
  }

  void CompilationUnit::removeImports(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::Import>::Container::iterator it = find(hasImportsContainer.begin(), hasImportsContainer.end(), id);

    if (it == hasImportsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasImportsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnit_HasImports);
  }

  void CompilationUnit::removeImports(struc::Import *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeImports(_node->getId());
  }

  void CompilationUnit::addTypeDeclarations(const struc::TypeDeclaration *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeDeclaration(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    typeDeclarationsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCompilationUnit_TypeDeclarations);
  }

  void CompilationUnit::addTypeDeclarations(NodeId _id) {
    const struc::TypeDeclaration *node = dynamic_cast<struc::TypeDeclaration*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypeDeclarations( node );
  }

  void CompilationUnit::removeTypeDeclarations(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::TypeDeclaration>::Container::iterator it = find(typeDeclarationsContainer.begin(), typeDeclarationsContainer.end(), id);

    if (it == typeDeclarationsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    typeDeclarationsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnit_TypeDeclarations);
  }

  void CompilationUnit::removeTypeDeclarations(struc::TypeDeclaration *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypeDeclarations(_node->getId());
  }

  void CompilationUnit::addOthers(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsPositioned(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasOthersContainer.push_back(_node->getId());
    setParentEdge(_node,edkCompilationUnit_HasOthers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCompilationUnit_HasOthers);
  }

  void CompilationUnit::addOthers(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addOthers( node );
  }

  void CompilationUnit::removeOthers(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasOthersContainer.begin(), hasOthersContainer.end(), id);

    if (it == hasOthersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasOthersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCompilationUnit_HasOthers);
  }

  void CompilationUnit::removeOthers(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeOthers(_node->getId());
  }

  void CompilationUnit::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CompilationUnit::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CompilationUnit::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const CompilationUnit& node = dynamic_cast<const CompilationUnit&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getFileEncoding();
      str2 = node.getFileEncoding();
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

  void CompilationUnit::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_fileEncoding);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_fileEncoding = foundKeyId->second;
    } else {
      Key oldkey = m_fileEncoding;
      m_fileEncoding = newStrTable.set(factory->getStringTable().get(m_fileEncoding));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_fileEncoding));    }

  }

  NodeHashType CompilationUnit::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::CompilationUnit", strlen("struc::CompilationUnit"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CompilationUnit::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    PositionedWithoutComment::sort(false);
    Commentable::sort(false);
  }

  void CompilationUnit::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    PositionedWithoutComment::save(binIo,false);

    Commentable::save(binIo,false);

    factory->getStringTable().setType(m_fileEncoding, StrTable::strToSave);
    binIo.writeUInt4(m_fileEncoding);

    binIo.writeUInt4(m_hasPackageDeclaration);


    for (ListIterator<struc::Import>::Container::const_iterator it = hasImportsContainer.begin(); it != hasImportsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<struc::TypeDeclaration>::Container::const_iterator it = typeDeclarationsContainer.begin(); it != typeDeclarationsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<base::Positioned>::Container::const_iterator it = hasOthersContainer.begin(); it != hasOthersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void CompilationUnit::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    PositionedWithoutComment::load(binIo,false);

    Commentable::load(binIo,false);

    m_fileEncoding = binIo.readUInt4();

    m_hasPackageDeclaration =  binIo.readUInt4();
    if (m_hasPackageDeclaration != 0)
      setParentEdge(factory->getPointer(m_hasPackageDeclaration),edkCompilationUnit_HasPackageDeclaration);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasImportsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCompilationUnit_HasImports);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      typeDeclarationsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasOthersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCompilationUnit_HasOthers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
