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

namespace expr { 
  Lambda::Lambda(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    FunctionalExpression(_id, _factory),
    m_lloc(0),
    m_paramKind(lpkImplicit),
    m_bodyKind(lbkExpression),
    hasParametersContainer(),
    m_hasBody(0)
  {
  }

  Lambda::~Lambda() {
  }

  void Lambda::clone(const Lambda& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::FunctionalExpression::clone(other, false);

    m_lloc = other.m_lloc;
    m_paramKind = other.m_paramKind;
    m_bodyKind = other.m_bodyKind;
    hasParametersContainer = other.hasParametersContainer;
    m_hasBody = other.m_hasBody;
  }

  void Lambda::prepareDelete(bool tryOnVirtualParent){
    while (!hasParametersContainer.empty()) {
      const NodeId id = *hasParametersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkLambda_HasParameters);
      hasParametersContainer.pop_front();
    }
    removeBody();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::FunctionalExpression::prepareDelete(false);
  }

  NodeKind Lambda::getNodeKind() const {
    return ndkLambda;
  }

  int Lambda::getLloc() const {
    return m_lloc;
  }

  LambdaParameterKind Lambda::getParamKind() const {
    return m_paramKind;
  }

  LambdaBodyKind Lambda::getBodyKind() const {
    return m_bodyKind;
  }

  void Lambda::setLloc(int _lloc) {
    m_lloc = _lloc;
  }

  void Lambda::setParamKind(LambdaParameterKind _paramKind) {
    m_paramKind = _paramKind;
  }

  void Lambda::setBodyKind(LambdaBodyKind _bodyKind) {
    m_bodyKind = _bodyKind;
  }

  ListIterator<struc::Parameter> Lambda::getParametersListIteratorBegin() const {
    return ListIterator<struc::Parameter>(&hasParametersContainer, factory, true);
  }

  ListIterator<struc::Parameter> Lambda::getParametersListIteratorEnd() const {
    return ListIterator<struc::Parameter>(&hasParametersContainer, factory, false);
  }

  bool Lambda::getParametersIsEmpty() const {
    return getParametersListIteratorBegin() == getParametersListIteratorEnd();
  }

  unsigned int Lambda::getParametersSize() const {
    unsigned int size = 0;
    ListIterator<struc::Parameter> endIt = getParametersListIteratorEnd();
    for (ListIterator<struc::Parameter> it = getParametersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  base::Positioned* Lambda::getBody() const {
    base::Positioned *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Lambda::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLambda_HasParameters:
        addParameters(edgeEnd);
        return true;
      case edkLambda_HasBody:
        setBody(edgeEnd);
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
    if (expr::FunctionalExpression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Lambda::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLambda_HasParameters:
        removeParameters(edgeEnd);
        return true;
      case edkLambda_HasBody:
        removeBody();
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
    if (expr::FunctionalExpression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Lambda::addParameters(const struc::Parameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkParameter) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasParametersContainer.push_back(_node->getId());
    setParentEdge(_node,edkLambda_HasParameters);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkLambda_HasParameters);
  }

  void Lambda::addParameters(NodeId _id) {
    const struc::Parameter *node = dynamic_cast<struc::Parameter*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameters( node );
  }

  void Lambda::removeParameters(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::Parameter>::Container::iterator it = find(hasParametersContainer.begin(), hasParametersContainer.end(), id);

    if (it == hasParametersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParametersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkLambda_HasParameters);
  }

  void Lambda::removeParameters(struc::Parameter *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameters(_node->getId());
  }

  void Lambda::setBody(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression) || Common::getIsBaseClassKind(_node->getNodeKind(), ndkStatement)) {
        if (m_hasBody) {
          removeParentEdge(m_hasBody);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasBody, m_id, edkLambda_HasBody);
        }
        m_hasBody = _node->getId();
        if (m_hasBody != 0)
          setParentEdge(factory->getPointer(m_hasBody), edkLambda_HasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkLambda_HasBody);
      } else {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasBody) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Lambda::setBody(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void Lambda::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkLambda_HasBody);
      }
      m_hasBody = 0;
  }

  void Lambda::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Lambda::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Lambda::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Lambda& node = dynamic_cast<const Lambda&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      if(node.getPolyKind() == getPolyKind()) ++matchAttrs;
      if(node.getLloc() == getLloc()) ++matchAttrs;
      if(node.getParamKind() == getParamKind()) ++matchAttrs;
      if(node.getBodyKind() == getBodyKind()) ++matchAttrs;
      return matchAttrs / (6 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Lambda::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Lambda::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::Lambda", strlen("expr::Lambda"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Lambda::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    FunctionalExpression::sort(false);
  }

  void Lambda::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    FunctionalExpression::save(binIo,false);

    binIo.writeUInt4(m_lloc);
    binIo.writeUByte1(m_paramKind);
    binIo.writeUByte1(m_bodyKind);

    binIo.writeUInt4(m_hasBody);


    for (ListIterator<struc::Parameter>::Container::const_iterator it = hasParametersContainer.begin(); it != hasParametersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Lambda::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    FunctionalExpression::load(binIo,false);

    m_lloc = binIo.readUInt4();
    m_paramKind = (LambdaParameterKind)binIo.readUByte1();
    m_bodyKind = (LambdaBodyKind)binIo.readUByte1();

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkLambda_HasBody);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasParametersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkLambda_HasParameters);
      _id = binIo.readUInt4();
    }
  }


}


}}}
