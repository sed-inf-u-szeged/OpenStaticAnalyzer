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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  JoinedStr::JoinedStr(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    hasValueContainer()
  {
  }

  JoinedStr::~JoinedStr() {
  }

  void JoinedStr::prepareDelete(bool tryOnVirtualParent){
    while (!hasValueContainer.empty()) {
      const NodeId id = *hasValueContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkJoinedStr_HasValue);
      hasValueContainer.pop_front();
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind JoinedStr::getNodeKind() const {
    return ndkJoinedStr;
  }

  ListIterator<expression::Expression> JoinedStr::getValueListIteratorBegin() const {
    return ListIterator<expression::Expression>(&hasValueContainer, factory, true);
  }

  ListIterator<expression::Expression> JoinedStr::getValueListIteratorEnd() const {
    return ListIterator<expression::Expression>(&hasValueContainer, factory, false);
  }

  bool JoinedStr::getValueIsEmpty() const {
    return getValueListIteratorBegin() == getValueListIteratorEnd();
  }

  unsigned int JoinedStr::getValueSize() const {
    unsigned int size = 0;
    ListIterator<expression::Expression> endIt = getValueListIteratorEnd();
    for (ListIterator<expression::Expression> it = getValueListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool JoinedStr::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkJoinedStr_HasValue:
        addValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool JoinedStr::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkJoinedStr_HasValue:
        removeValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void JoinedStr::addValue(const expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasValueContainer.push_back(_node->getId());
    setParentEdge(_node,edkJoinedStr_HasValue);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkJoinedStr_HasValue);
  }

  void JoinedStr::addValue(NodeId _id) {
    const expression::Expression *node = dynamic_cast<expression::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addValue( node );
  }

  void JoinedStr::removeValue(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Expression>::Container::iterator it = find(hasValueContainer.begin(), hasValueContainer.end(), id);

    if (it == hasValueContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasValueContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkJoinedStr_HasValue);
  }

  void JoinedStr::removeValue(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeValue(_node->getId());
  }

  void JoinedStr::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void JoinedStr::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double JoinedStr::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void JoinedStr::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType JoinedStr::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::JoinedStr", strlen("expression::JoinedStr"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void JoinedStr::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);


    for (ListIterator<expression::Expression>::Container::const_iterator it = hasValueContainer.begin(); it != hasValueContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void JoinedStr::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasValueContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkJoinedStr_HasValue);
      _id = binIo.readUInt4();
    }
  }


}


}}}
