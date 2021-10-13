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
  Requires::Requires(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    ModuleDirective(_id, _factory),
    m_isTransitive(false),
    m_isStatic(false),
    m_hasModuleName(0)
  {
  }

  Requires::~Requires() {
  }

  void Requires::clone(const Requires& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    module::ModuleDirective::clone(other, false);

    m_isTransitive = other.m_isTransitive;
    m_isStatic = other.m_isStatic;
    m_hasModuleName = other.m_hasModuleName;
  }

  void Requires::prepareDelete(bool tryOnVirtualParent){
    removeModuleName();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    module::ModuleDirective::prepareDelete(false);
  }

  NodeKind Requires::getNodeKind() const {
    return ndkRequires;
  }

  bool Requires::getIsTransitive() const {
    return m_isTransitive;
  }

  bool Requires::getIsStatic() const {
    return m_isStatic;
  }

  void Requires::setIsTransitive(bool _isTransitive) {
    m_isTransitive = _isTransitive;
  }

  void Requires::setIsStatic(bool _isStatic) {
    m_isStatic = _isStatic;
  }

  expr::Expression* Requires::getModuleName() const {
    expr::Expression *_node = NULL;
    if (m_hasModuleName != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasModuleName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Requires::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRequires_HasModuleName:
        setModuleName(edgeEnd);
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

  bool Requires::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRequires_HasModuleName:
        removeModuleName();
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

  void Requires::setModuleName(NodeId _id) {
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

      if (m_hasModuleName) {
        removeParentEdge(m_hasModuleName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasModuleName, m_id, edkRequires_HasModuleName);
      }
      m_hasModuleName = _node->getId();
      if (m_hasModuleName != 0)
        setParentEdge(factory->getPointer(m_hasModuleName), edkRequires_HasModuleName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasModuleName, this->getId(), edkRequires_HasModuleName);
    } else {
      if (m_hasModuleName) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Requires::setModuleName(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setModuleName(_node->getId());
  }

  void Requires::removeModuleName() {
      if (m_hasModuleName) {
        removeParentEdge(m_hasModuleName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasModuleName, m_id, edkRequires_HasModuleName);
      }
      m_hasModuleName = 0;
  }

  void Requires::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Requires::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Requires::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Requires& node = dynamic_cast<const Requires&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      if(node.getIsTransitive() == getIsTransitive()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      return matchAttrs / (4 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Requires::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Requires::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "module::Requires", strlen("module::Requires"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Requires::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    ModuleDirective::sort(false);
  }

  void Requires::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    ModuleDirective::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isTransitive) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isStatic) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_hasModuleName);

  }

  void Requires::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    ModuleDirective::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isStatic = boolValues & 1;
    boolValues >>= 1;
    m_isTransitive = boolValues & 1;
    boolValues >>= 1;

    m_hasModuleName =  binIo.readUInt4();
    if (m_hasModuleName != 0)
      setParentEdge(factory->getPointer(m_hasModuleName),edkRequires_HasModuleName);

  }


}


}}}
