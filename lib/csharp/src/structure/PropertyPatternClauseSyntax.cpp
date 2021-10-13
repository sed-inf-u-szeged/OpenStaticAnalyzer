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
  PropertyPatternClauseSyntax::PropertyPatternClauseSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    SubpatternsContainer()
  {
  }

  PropertyPatternClauseSyntax::~PropertyPatternClauseSyntax() {
  }

  void PropertyPatternClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!SubpatternsContainer.empty()) {
      const NodeId id = *SubpatternsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkPropertyPatternClauseSyntax_Subpatterns);
      SubpatternsContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind PropertyPatternClauseSyntax::getNodeKind() const {
    return ndkPropertyPatternClauseSyntax;
  }

  ListIterator<structure::SubpatternSyntax> PropertyPatternClauseSyntax::getSubpatternsListIteratorBegin() const {
    return ListIterator<structure::SubpatternSyntax>(&SubpatternsContainer, factory, true);
  }

  ListIterator<structure::SubpatternSyntax> PropertyPatternClauseSyntax::getSubpatternsListIteratorEnd() const {
    return ListIterator<structure::SubpatternSyntax>(&SubpatternsContainer, factory, false);
  }

  bool PropertyPatternClauseSyntax::getSubpatternsIsEmpty() const {
    return getSubpatternsListIteratorBegin() == getSubpatternsListIteratorEnd();
  }

  unsigned int PropertyPatternClauseSyntax::getSubpatternsSize() const {
    unsigned int size = 0;
    ListIterator<structure::SubpatternSyntax> endIt = getSubpatternsListIteratorEnd();
    for (ListIterator<structure::SubpatternSyntax> it = getSubpatternsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool PropertyPatternClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPropertyPatternClauseSyntax_Subpatterns:
        addSubpatterns(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool PropertyPatternClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPropertyPatternClauseSyntax_Subpatterns:
        removeSubpatterns(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void PropertyPatternClauseSyntax::addSubpatterns(const structure::SubpatternSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkSubpatternSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    SubpatternsContainer.push_back(_node->getId());
    setParentEdge(_node,edkPropertyPatternClauseSyntax_Subpatterns);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkPropertyPatternClauseSyntax_Subpatterns);
  }

  void PropertyPatternClauseSyntax::addSubpatterns(NodeId _id) {
    const structure::SubpatternSyntax *node = dynamic_cast<structure::SubpatternSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSubpatterns( node );
  }

  void PropertyPatternClauseSyntax::removeSubpatterns(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::SubpatternSyntax>::Container::iterator it = find(SubpatternsContainer.begin(), SubpatternsContainer.end(), id);

    if (it == SubpatternsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    SubpatternsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkPropertyPatternClauseSyntax_Subpatterns);
  }

  void PropertyPatternClauseSyntax::removeSubpatterns(structure::SubpatternSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSubpatterns(_node->getId());
  }

  void PropertyPatternClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void PropertyPatternClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double PropertyPatternClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void PropertyPatternClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType PropertyPatternClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::PropertyPatternClauseSyntax", strlen("structure::PropertyPatternClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void PropertyPatternClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<structure::SubpatternSyntax>::Container::const_iterator it = SubpatternsContainer.begin(); it != SubpatternsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void PropertyPatternClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      SubpatternsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkPropertyPatternClauseSyntax_Subpatterns);
      _id = binIo.readUInt4();
    }
  }


}


}}}
