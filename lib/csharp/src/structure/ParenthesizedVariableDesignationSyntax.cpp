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
  ParenthesizedVariableDesignationSyntax::ParenthesizedVariableDesignationSyntax(NodeId _id, Factory *_factory) :
    VariableDesignationSyntax(_id, _factory),
    VariablesContainer()
  {
  }

  ParenthesizedVariableDesignationSyntax::~ParenthesizedVariableDesignationSyntax() {
  }

  void ParenthesizedVariableDesignationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!VariablesContainer.empty()) {
      const NodeId id = *VariablesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkParenthesizedVariableDesignationSyntax_Variables);
      VariablesContainer.pop_front();
    }
    structure::VariableDesignationSyntax::prepareDelete(false);
  }

  NodeKind ParenthesizedVariableDesignationSyntax::getNodeKind() const {
    return ndkParenthesizedVariableDesignationSyntax;
  }

  ListIterator<structure::VariableDesignationSyntax> ParenthesizedVariableDesignationSyntax::getVariablesListIteratorBegin() const {
    return ListIterator<structure::VariableDesignationSyntax>(&VariablesContainer, factory, true);
  }

  ListIterator<structure::VariableDesignationSyntax> ParenthesizedVariableDesignationSyntax::getVariablesListIteratorEnd() const {
    return ListIterator<structure::VariableDesignationSyntax>(&VariablesContainer, factory, false);
  }

  bool ParenthesizedVariableDesignationSyntax::getVariablesIsEmpty() const {
    return getVariablesListIteratorBegin() == getVariablesListIteratorEnd();
  }

  unsigned int ParenthesizedVariableDesignationSyntax::getVariablesSize() const {
    unsigned int size = 0;
    ListIterator<structure::VariableDesignationSyntax> endIt = getVariablesListIteratorEnd();
    for (ListIterator<structure::VariableDesignationSyntax> it = getVariablesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ParenthesizedVariableDesignationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParenthesizedVariableDesignationSyntax_Variables:
        addVariables(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::VariableDesignationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ParenthesizedVariableDesignationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParenthesizedVariableDesignationSyntax_Variables:
        removeVariables(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::VariableDesignationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ParenthesizedVariableDesignationSyntax::addVariables(const structure::VariableDesignationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsVariableDesignationSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    VariablesContainer.push_back(_node->getId());
    setParentEdge(_node,edkParenthesizedVariableDesignationSyntax_Variables);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkParenthesizedVariableDesignationSyntax_Variables);
  }

  void ParenthesizedVariableDesignationSyntax::addVariables(NodeId _id) {
    const structure::VariableDesignationSyntax *node = dynamic_cast<structure::VariableDesignationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addVariables( node );
  }

  void ParenthesizedVariableDesignationSyntax::removeVariables(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::VariableDesignationSyntax>::Container::iterator it = find(VariablesContainer.begin(), VariablesContainer.end(), id);

    if (it == VariablesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    VariablesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkParenthesizedVariableDesignationSyntax_Variables);
  }

  void ParenthesizedVariableDesignationSyntax::removeVariables(structure::VariableDesignationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeVariables(_node->getId());
  }

  void ParenthesizedVariableDesignationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ParenthesizedVariableDesignationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ParenthesizedVariableDesignationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ParenthesizedVariableDesignationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ParenthesizedVariableDesignationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ParenthesizedVariableDesignationSyntax", strlen("structure::ParenthesizedVariableDesignationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ParenthesizedVariableDesignationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    VariableDesignationSyntax::save(binIo,false);


    for (ListIterator<structure::VariableDesignationSyntax>::Container::const_iterator it = VariablesContainer.begin(); it != VariablesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ParenthesizedVariableDesignationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    VariableDesignationSyntax::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      VariablesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkParenthesizedVariableDesignationSyntax_Variables);
      _id = binIo.readUInt4();
    }
  }


}


}}}
