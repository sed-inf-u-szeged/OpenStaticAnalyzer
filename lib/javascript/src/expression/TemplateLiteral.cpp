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

namespace expression { 
  TemplateLiteral::TemplateLiteral(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    hasQuasisContainer(),
    hasExpressionsContainer()
  {
  }

  TemplateLiteral::~TemplateLiteral() {
  }

  void TemplateLiteral::prepareDelete(bool tryOnVirtualParent){
    while (!hasQuasisContainer.empty()) {
      const NodeId id = *hasQuasisContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTemplateLiteral_HasQuasis);
      hasQuasisContainer.pop_front();
    }
    while (!hasExpressionsContainer.empty()) {
      const NodeId id = *hasExpressionsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTemplateLiteral_HasExpressions);
      hasExpressionsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind TemplateLiteral::getNodeKind() const {
    return ndkTemplateLiteral;
  }

  ListIterator<expression::TemplateElement> TemplateLiteral::getQuasisListIteratorBegin() const {
    return ListIterator<expression::TemplateElement>(&hasQuasisContainer, factory, true);
  }

  ListIterator<expression::TemplateElement> TemplateLiteral::getQuasisListIteratorEnd() const {
    return ListIterator<expression::TemplateElement>(&hasQuasisContainer, factory, false);
  }

  bool TemplateLiteral::getQuasisIsEmpty() const {
    return getQuasisListIteratorBegin() == getQuasisListIteratorEnd();
  }

  unsigned int TemplateLiteral::getQuasisSize() const {
    unsigned int size = 0;
    ListIterator<expression::TemplateElement> endIt = getQuasisListIteratorEnd();
    for (ListIterator<expression::TemplateElement> it = getQuasisListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<expression::Expression> TemplateLiteral::getExpressionsListIteratorBegin() const {
    return ListIterator<expression::Expression>(&hasExpressionsContainer, factory, true);
  }

  ListIterator<expression::Expression> TemplateLiteral::getExpressionsListIteratorEnd() const {
    return ListIterator<expression::Expression>(&hasExpressionsContainer, factory, false);
  }

  bool TemplateLiteral::getExpressionsIsEmpty() const {
    return getExpressionsListIteratorBegin() == getExpressionsListIteratorEnd();
  }

  unsigned int TemplateLiteral::getExpressionsSize() const {
    unsigned int size = 0;
    ListIterator<expression::Expression> endIt = getExpressionsListIteratorEnd();
    for (ListIterator<expression::Expression> it = getExpressionsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TemplateLiteral::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTemplateLiteral_HasQuasis:
        addQuasis(edgeEnd);
        return true;
      case edkTemplateLiteral_HasExpressions:
        addExpressions(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TemplateLiteral::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTemplateLiteral_HasQuasis:
        removeQuasis(edgeEnd);
        return true;
      case edkTemplateLiteral_HasExpressions:
        removeExpressions(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TemplateLiteral::addQuasis(const expression::TemplateElement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTemplateElement) ))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasQuasisContainer.push_back(_node->getId());
    setParentEdge(_node,edkTemplateLiteral_HasQuasis);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTemplateLiteral_HasQuasis);
  }

  void TemplateLiteral::addQuasis(NodeId _id) {
    const expression::TemplateElement *node = dynamic_cast<expression::TemplateElement*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addQuasis( node );
  }

  void TemplateLiteral::removeQuasis(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::TemplateElement>::Container::iterator it = find(hasQuasisContainer.begin(), hasQuasisContainer.end(), id);

    if (it == hasQuasisContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasQuasisContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTemplateLiteral_HasQuasis);
  }

  void TemplateLiteral::removeQuasis(expression::TemplateElement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeQuasis(_node->getId());
  }

  void TemplateLiteral::addExpressions(const expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasExpressionsContainer.push_back(_node->getId());
    setParentEdge(_node,edkTemplateLiteral_HasExpressions);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTemplateLiteral_HasExpressions);
  }

  void TemplateLiteral::addExpressions(NodeId _id) {
    const expression::Expression *node = dynamic_cast<expression::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addExpressions( node );
  }

  void TemplateLiteral::removeExpressions(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Expression>::Container::iterator it = find(hasExpressionsContainer.begin(), hasExpressionsContainer.end(), id);

    if (it == hasExpressionsContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasExpressionsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTemplateLiteral_HasExpressions);
  }

  void TemplateLiteral::removeExpressions(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeExpressions(_node->getId());
  }

  void TemplateLiteral::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TemplateLiteral::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TemplateLiteral::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TemplateLiteral::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TemplateLiteral::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::TemplateLiteral", strlen("expression::TemplateLiteral"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TemplateLiteral::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);


    for (ListIterator<expression::TemplateElement>::Container::const_iterator it = hasQuasisContainer.begin(); it != hasQuasisContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<expression::Expression>::Container::const_iterator it = hasExpressionsContainer.begin(); it != hasExpressionsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TemplateLiteral::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasQuasisContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTemplateLiteral_HasQuasis);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasExpressionsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTemplateLiteral_HasExpressions);
      _id = binIo.readUInt4();
    }
  }


}


}}}
