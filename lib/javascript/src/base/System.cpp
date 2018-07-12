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

namespace base { 
  System::System(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    hasProgramsContainer()
  {
  }

  System::~System() {
  }

  void System::prepareDelete(bool tryOnVirtualParent){
    while (!hasProgramsContainer.empty()) {
      const NodeId id = *hasProgramsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_HasPrograms);
      hasProgramsContainer.pop_front();
    }
    base::Base::prepareDelete(false);
  }

  NodeKind System::getNodeKind() const {
    return ndkSystem;
  }

  ListIterator<base::Program> System::getProgramsListIteratorBegin() const {
    return ListIterator<base::Program>(&hasProgramsContainer, factory, true);
  }

  ListIterator<base::Program> System::getProgramsListIteratorEnd() const {
    return ListIterator<base::Program>(&hasProgramsContainer, factory, false);
  }

  bool System::getProgramsIsEmpty() const {
    return getProgramsListIteratorBegin() == getProgramsListIteratorEnd();
  }

  unsigned int System::getProgramsSize() const {
    unsigned int size = 0;
    ListIterator<base::Program> endIt = getProgramsListIteratorEnd();
    for (ListIterator<base::Program> it = getProgramsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool System::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSystem_HasPrograms:
        addPrograms(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool System::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSystem_HasPrograms:
        removePrograms(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void System::addPrograms(const base::Program *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkProgram) ))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasProgramsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSystem_HasPrograms);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSystem_HasPrograms);
  }

  void System::addPrograms(NodeId _id) {
    const base::Program *node = dynamic_cast<base::Program*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addPrograms( node );
  }

  void System::removePrograms(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Program>::Container::iterator it = find(hasProgramsContainer.begin(), hasProgramsContainer.end(), id);

    if (it == hasProgramsContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasProgramsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_HasPrograms);
  }

  void System::removePrograms(base::Program *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removePrograms(_node->getId());
  }

  void System::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void System::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double System::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void System::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType System::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::System", strlen("base::System"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void System::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);


    for (ListIterator<base::Program>::Container::const_iterator it = hasProgramsContainer.begin(); it != hasProgramsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void System::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasProgramsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSystem_HasPrograms);
      _id = binIo.readUInt4();
    }
  }


}


}}}
