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

namespace module { 
  Uses::Uses(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    ModuleDirective(_id, _factory),
    m_hasServiceName(0)
  {
  }

  Uses::~Uses() {
  }

  void Uses::clone(const Uses& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    module::ModuleDirective::clone(other, false);

    m_hasServiceName = other.m_hasServiceName;
  }

  void Uses::prepareDelete(bool tryOnVirtualParent){
    removeServiceName();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    module::ModuleDirective::prepareDelete(false);
  }

  NodeKind Uses::getNodeKind() const {
    return ndkUses;
  }

  expr::Expression* Uses::getServiceName() const {
    expr::Expression *_node = NULL;
    if (m_hasServiceName != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasServiceName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Uses::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkUses_HasServiceName:
        setServiceName(edgeEnd);
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
    if (module::ModuleDirective::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Uses::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkUses_HasServiceName:
        removeServiceName();
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
    if (module::ModuleDirective::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Uses::setServiceName(NodeId _id) {
    expr::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasServiceName) {
        removeParentEdge(m_hasServiceName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasServiceName, m_id, edkUses_HasServiceName);
      }
      m_hasServiceName = _node->getId();
      if (m_hasServiceName != 0)
        setParentEdge(factory->getPointer(m_hasServiceName), edkUses_HasServiceName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasServiceName, this->getId(), edkUses_HasServiceName);
    } else {
      if (m_hasServiceName) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Uses::setServiceName(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setServiceName(_node->getId());
  }

  void Uses::removeServiceName() {
      if (m_hasServiceName) {
        removeParentEdge(m_hasServiceName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasServiceName, m_id, edkUses_HasServiceName);
      }
      m_hasServiceName = 0;
  }

  void Uses::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Uses::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Uses::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Uses& node = dynamic_cast<const Uses&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Uses::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Uses::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "module::Uses", strlen("module::Uses"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Uses::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    ModuleDirective::sort(false);
  }

  void Uses::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    ModuleDirective::save(binIo,false);

    binIo.writeUInt4(m_hasServiceName);

  }

  void Uses::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    ModuleDirective::load(binIo,false);

    m_hasServiceName =  binIo.readUInt4();
    if (m_hasServiceName != 0)
      setParentEdge(factory->getPointer(m_hasServiceName),edkUses_HasServiceName);

  }


}


}}}
