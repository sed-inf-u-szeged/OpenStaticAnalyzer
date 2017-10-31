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

namespace struc { 
  PackageDeclaration::PackageDeclaration(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Positioned(_id, _factory),
    m_hasPackageName(0),
    m_refersTo(0)
  {
  }

  PackageDeclaration::~PackageDeclaration() {
  }

  void PackageDeclaration::clone(const PackageDeclaration& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    base::Positioned::clone(other, false);

    m_hasPackageName = other.m_hasPackageName;
    m_refersTo = other.m_refersTo;
  }

  void PackageDeclaration::prepareDelete(bool tryOnVirtualParent){
    removePackageName();
    removeRefersTo();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind PackageDeclaration::getNodeKind() const {
    return ndkPackageDeclaration;
  }

  expr::Expression* PackageDeclaration::getPackageName() const {
    expr::Expression *_node = NULL;
    if (m_hasPackageName != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasPackageName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  struc::Package* PackageDeclaration::getRefersTo() const {
    struc::Package *_node = NULL;
    if (m_refersTo != 0)
      _node = dynamic_cast<struc::Package*>(factory->getPointer(m_refersTo));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool PackageDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPackageDeclaration_HasPackageName:
        setPackageName(edgeEnd);
        return true;
      case edkPackageDeclaration_RefersTo:
        setRefersTo(edgeEnd);
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
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool PackageDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPackageDeclaration_HasPackageName:
        removePackageName();
        return true;
      case edkPackageDeclaration_RefersTo:
        removeRefersTo();
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
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void PackageDeclaration::setPackageName(NodeId _id) {
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

      if (m_hasPackageName) {
        removeParentEdge(m_hasPackageName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPackageName, m_id, edkPackageDeclaration_HasPackageName);
      }
      m_hasPackageName = _node->getId();
      if (m_hasPackageName != 0)
        setParentEdge(factory->getPointer(m_hasPackageName), edkPackageDeclaration_HasPackageName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasPackageName, this->getId(), edkPackageDeclaration_HasPackageName);
    } else {
      if (m_hasPackageName) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PackageDeclaration::setPackageName(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPackageName(_node->getId());
  }

  void PackageDeclaration::removePackageName() {
      if (m_hasPackageName) {
        removeParentEdge(m_hasPackageName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPackageName, m_id, edkPackageDeclaration_HasPackageName);
      }
      m_hasPackageName = 0;
  }

  void PackageDeclaration::setRefersTo(NodeId _id) {
    struc::Package *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::Package*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkPackageDeclaration_RefersTo);
      }
      m_refersTo = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_refersTo, this->getId(), edkPackageDeclaration_RefersTo);
    } else {
      if (m_refersTo) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PackageDeclaration::setRefersTo(struc::Package *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRefersTo(_node->getId());
  }

  void PackageDeclaration::removeRefersTo() {
      if (m_refersTo) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_refersTo, m_id, edkPackageDeclaration_RefersTo);
      }
      m_refersTo = 0;
  }

  void PackageDeclaration::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void PackageDeclaration::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double PackageDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const PackageDeclaration& node = dynamic_cast<const PackageDeclaration&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void PackageDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType PackageDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::PackageDeclaration", strlen("struc::PackageDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void PackageDeclaration::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Positioned::sort(false);
  }

  void PackageDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasPackageName);
    binIo.writeUInt4(m_refersTo);

  }

  void PackageDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Positioned::load(binIo,false);

    m_hasPackageName =  binIo.readUInt4();
    if (m_hasPackageName != 0)
      setParentEdge(factory->getPointer(m_hasPackageName),edkPackageDeclaration_HasPackageName);

    m_refersTo =  binIo.readUInt4();

  }


}


}}}
