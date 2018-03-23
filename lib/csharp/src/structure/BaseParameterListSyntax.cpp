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

namespace structure { 
  BaseParameterListSyntax::BaseParameterListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    ParametersContainer()
  {
  }

  BaseParameterListSyntax::~BaseParameterListSyntax() {
  }

  void BaseParameterListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ParametersContainer.empty()) {
      const NodeId id = *ParametersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBaseParameterListSyntax_Parameters);
      ParametersContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  ListIterator<structure::ParameterSyntax> BaseParameterListSyntax::getParametersListIteratorBegin() const {
    return ListIterator<structure::ParameterSyntax>(&ParametersContainer, factory, true);
  }

  ListIterator<structure::ParameterSyntax> BaseParameterListSyntax::getParametersListIteratorEnd() const {
    return ListIterator<structure::ParameterSyntax>(&ParametersContainer, factory, false);
  }

  bool BaseParameterListSyntax::getParametersIsEmpty() const {
    return getParametersListIteratorBegin() == getParametersListIteratorEnd();
  }

  unsigned int BaseParameterListSyntax::getParametersSize() const {
    unsigned int size = 0;
    ListIterator<structure::ParameterSyntax> endIt = getParametersListIteratorEnd();
    for (ListIterator<structure::ParameterSyntax> it = getParametersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool BaseParameterListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseParameterListSyntax_Parameters:
        addParameters(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BaseParameterListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseParameterListSyntax_Parameters:
        removeParameters(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BaseParameterListSyntax::addParameters(const structure::ParameterSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkParameterSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ParametersContainer.push_back(_node->getId());
    setParentEdge(_node,edkBaseParameterListSyntax_Parameters);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBaseParameterListSyntax_Parameters);
  }

  void BaseParameterListSyntax::addParameters(NodeId _id) {
    const structure::ParameterSyntax *node = dynamic_cast<structure::ParameterSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameters( node );
  }

  void BaseParameterListSyntax::removeParameters(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::ParameterSyntax>::Container::iterator it = find(ParametersContainer.begin(), ParametersContainer.end(), id);

    if (it == ParametersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ParametersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBaseParameterListSyntax_Parameters);
  }

  void BaseParameterListSyntax::removeParameters(structure::ParameterSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameters(_node->getId());
  }

  double BaseParameterListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BaseParameterListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType BaseParameterListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::BaseParameterListSyntax", strlen("structure::BaseParameterListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BaseParameterListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::ParameterSyntax>::Container::const_iterator it = ParametersContainer.begin(); it != ParametersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BaseParameterListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ParametersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBaseParameterListSyntax_Parameters);
      _id = binIo.readUInt4();
    }
  }


}


}}}
