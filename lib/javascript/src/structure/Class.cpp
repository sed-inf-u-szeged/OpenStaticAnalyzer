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

namespace structure { 
  Class::Class(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasBody(0),
    m_hasSuperClass(0),
    m_hasIdentifier(0)
  {
  }

  Class::~Class() {
  }

  void Class::prepareDelete(bool tryOnVirtualParent){
    removeBody();
    removeSuperClass();
    removeIdentifier();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
  }

  structure::ClassBody* Class::getBody() const {
    structure::ClassBody *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<structure::ClassBody*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Class::getSuperClass() const {
    expression::Expression *_node = NULL;
    if (m_hasSuperClass != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasSuperClass));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Identifier* Class::getIdentifier() const {
    expression::Identifier *_node = NULL;
    if (m_hasIdentifier != 0)
      _node = dynamic_cast<expression::Identifier*>(factory->getPointer(m_hasIdentifier));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Class::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClass_HasBody:
        setBody(edgeEnd);
        return true;
      case edkClass_HasSuperClass:
        setSuperClass(edgeEnd);
        return true;
      case edkClass_HasIdentifier:
        setIdentifier(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool Class::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClass_HasBody:
        removeBody();
        return true;
      case edkClass_HasSuperClass:
        removeSuperClass();
        return true;
      case edkClass_HasIdentifier:
        removeIdentifier();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  void Class::setBody(NodeId _id) {
    structure::ClassBody *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ClassBody*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkClass_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkClass_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkClass_HasBody);
    } else {
      if (m_hasBody) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Class::setBody(structure::ClassBody *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void Class::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkClass_HasBody);
      }
      m_hasBody = 0;
  }

  void Class::setSuperClass(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSuperClass) {
        removeParentEdge(m_hasSuperClass);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSuperClass, m_id, edkClass_HasSuperClass);
      }
      m_hasSuperClass = _node->getId();
      if (m_hasSuperClass != 0)
        setParentEdge(factory->getPointer(m_hasSuperClass), edkClass_HasSuperClass);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSuperClass, this->getId(), edkClass_HasSuperClass);
    } else {
      if (m_hasSuperClass) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Class::setSuperClass(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSuperClass(_node->getId());
  }

  void Class::removeSuperClass() {
      if (m_hasSuperClass) {
        removeParentEdge(m_hasSuperClass);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSuperClass, m_id, edkClass_HasSuperClass);
      }
      m_hasSuperClass = 0;
  }

  void Class::setIdentifier(NodeId _id) {
    expression::Identifier *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Identifier*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasIdentifier) {
        removeParentEdge(m_hasIdentifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIdentifier, m_id, edkClass_HasIdentifier);
      }
      m_hasIdentifier = _node->getId();
      if (m_hasIdentifier != 0)
        setParentEdge(factory->getPointer(m_hasIdentifier), edkClass_HasIdentifier);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasIdentifier, this->getId(), edkClass_HasIdentifier);
    } else {
      if (m_hasIdentifier) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Class::setIdentifier(expression::Identifier *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setIdentifier(_node->getId());
  }

  void Class::removeIdentifier() {
      if (m_hasIdentifier) {
        removeParentEdge(m_hasIdentifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIdentifier, m_id, edkClass_HasIdentifier);
      }
      m_hasIdentifier = 0;
  }

  double Class::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Class::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Class::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::Class", strlen("structure::Class"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Class::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasBody);
    binIo.writeUInt4(m_hasSuperClass);
    binIo.writeUInt4(m_hasIdentifier);

  }

  void Class::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo,false);

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkClass_HasBody);

    m_hasSuperClass =  binIo.readUInt4();
    if (m_hasSuperClass != 0)
      setParentEdge(factory->getPointer(m_hasSuperClass),edkClass_HasSuperClass);

    m_hasIdentifier =  binIo.readUInt4();
    if (m_hasIdentifier != 0)
      setParentEdge(factory->getPointer(m_hasIdentifier),edkClass_HasIdentifier);

  }


}


}}}
