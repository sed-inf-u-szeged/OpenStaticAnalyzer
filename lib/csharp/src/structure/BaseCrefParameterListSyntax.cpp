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

namespace structure { 
  BaseCrefParameterListSyntax::BaseCrefParameterListSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    ParametersContainer()
  {
  }

  BaseCrefParameterListSyntax::~BaseCrefParameterListSyntax() {
  }

  void BaseCrefParameterListSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ParametersContainer.empty()) {
      const NodeId id = *ParametersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBaseCrefParameterListSyntax_Parameters);
      ParametersContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  ListIterator<structure::CrefParameterSyntax> BaseCrefParameterListSyntax::getParametersListIteratorBegin() const {
    return ListIterator<structure::CrefParameterSyntax>(&ParametersContainer, factory, true);
  }

  ListIterator<structure::CrefParameterSyntax> BaseCrefParameterListSyntax::getParametersListIteratorEnd() const {
    return ListIterator<structure::CrefParameterSyntax>(&ParametersContainer, factory, false);
  }

  bool BaseCrefParameterListSyntax::getParametersIsEmpty() const {
    return getParametersListIteratorBegin() == getParametersListIteratorEnd();
  }

  unsigned int BaseCrefParameterListSyntax::getParametersSize() const {
    unsigned int size = 0;
    ListIterator<structure::CrefParameterSyntax> endIt = getParametersListIteratorEnd();
    for (ListIterator<structure::CrefParameterSyntax> it = getParametersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool BaseCrefParameterListSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseCrefParameterListSyntax_Parameters:
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

  bool BaseCrefParameterListSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseCrefParameterListSyntax_Parameters:
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

  void BaseCrefParameterListSyntax::addParameters(const structure::CrefParameterSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCrefParameterSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ParametersContainer.push_back(_node->getId());
    setParentEdge(_node,edkBaseCrefParameterListSyntax_Parameters);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBaseCrefParameterListSyntax_Parameters);
  }

  void BaseCrefParameterListSyntax::addParameters(NodeId _id) {
    const structure::CrefParameterSyntax *node = dynamic_cast<structure::CrefParameterSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameters( node );
  }

  void BaseCrefParameterListSyntax::removeParameters(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::CrefParameterSyntax>::Container::iterator it = find(ParametersContainer.begin(), ParametersContainer.end(), id);

    if (it == ParametersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ParametersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBaseCrefParameterListSyntax_Parameters);
  }

  void BaseCrefParameterListSyntax::removeParameters(structure::CrefParameterSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameters(_node->getId());
  }

  double BaseCrefParameterListSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BaseCrefParameterListSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType BaseCrefParameterListSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::BaseCrefParameterListSyntax", strlen("structure::BaseCrefParameterListSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BaseCrefParameterListSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::CrefParameterSyntax>::Container::const_iterator it = ParametersContainer.begin(); it != ParametersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BaseCrefParameterListSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ParametersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBaseCrefParameterListSyntax_Parameters);
      _id = binIo.readUInt4();
    }
  }


}


}}}
