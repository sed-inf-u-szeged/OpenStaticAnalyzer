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
  AnnotationTypeElement::AnnotationTypeElement(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    MethodDeclaration(_id, _factory),
    m_defaultPosition(),
    m_hasDefaultValue(0)
  {
    m_defaultPosition.posInfo.path = 0;
    m_defaultPosition.posInfo.line = 0;
    m_defaultPosition.posInfo.col = 0;
    m_defaultPosition.posInfo.endLine = 0;
    m_defaultPosition.posInfo.endCol = 0;
    m_defaultPosition.posInfo.wideLine = 0;
    m_defaultPosition.posInfo.wideCol = 0;
    m_defaultPosition.posInfo.wideEndLine = 0;
    m_defaultPosition.posInfo.wideEndCol = 0;
  }

  AnnotationTypeElement::~AnnotationTypeElement() {
  }

  void AnnotationTypeElement::clone(const AnnotationTypeElement& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::MethodDeclaration::clone(other, false);

    m_defaultPosition.posInfo = other.m_defaultPosition.posInfo;
    m_hasDefaultValue = other.m_hasDefaultValue;
  }

  void AnnotationTypeElement::prepareDelete(bool tryOnVirtualParent){
    removeDefaultValue();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::MethodDeclaration::prepareDelete(false);
  }

  NodeKind AnnotationTypeElement::getNodeKind() const {
    return ndkAnnotationTypeElement;
  }

  const Range AnnotationTypeElement::getDefaultPosition() const {
    return Range(factory->getStringTable(), m_defaultPosition.posInfo);
  }

  int AnnotationTypeElement::compareByDefaultPosition(const AnnotationTypeElement& other) const {
    if (m_defaultPosition.posInfo.path != other.m_defaultPosition.posInfo.path) {
      return (m_defaultPosition.posInfo.path < other.m_defaultPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_defaultPosition.posInfo.wideLine != other.m_defaultPosition.posInfo.wideLine) {
      return (m_defaultPosition.posInfo.wideLine < other.m_defaultPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_defaultPosition.posInfo.wideCol != other.m_defaultPosition.posInfo.wideCol) {
      return (m_defaultPosition.posInfo.wideCol < other.m_defaultPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_defaultPosition.posInfo.wideEndLine != other.m_defaultPosition.posInfo.wideEndLine) {
      return (m_defaultPosition.posInfo.wideEndLine > other.m_defaultPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_defaultPosition.posInfo.wideEndCol != other.m_defaultPosition.posInfo.wideEndCol) {
      return (m_defaultPosition.posInfo.wideEndCol > other.m_defaultPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void AnnotationTypeElement::setDefaultPosition(const Range& _defaultPosition) {
    m_defaultPosition.posInfo = _defaultPosition.positionInfo;
    if (_defaultPosition.strTable != &factory->getStringTable())
      m_defaultPosition.posInfo.path = factory->getStringTable().set(_defaultPosition.getPath());
  }

  expr::Expression* AnnotationTypeElement::getDefaultValue() const {
    expr::Expression *_node = NULL;
    if (m_hasDefaultValue != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasDefaultValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AnnotationTypeElement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnotationTypeElement_HasDefaultValue:
        setDefaultValue(edgeEnd);
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
    if (tryOnVirtualParent) {
      if (struc::Member::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (struc::MethodDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AnnotationTypeElement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAnnotationTypeElement_HasDefaultValue:
        removeDefaultValue();
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
    if (tryOnVirtualParent) {
      if (struc::Member::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (struc::MethodDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AnnotationTypeElement::setDefaultValue(NodeId _id) {
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

      if (m_hasDefaultValue) {
        removeParentEdge(m_hasDefaultValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDefaultValue, m_id, edkAnnotationTypeElement_HasDefaultValue);
      }
      m_hasDefaultValue = _node->getId();
      if (m_hasDefaultValue != 0)
        setParentEdge(factory->getPointer(m_hasDefaultValue), edkAnnotationTypeElement_HasDefaultValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasDefaultValue, this->getId(), edkAnnotationTypeElement_HasDefaultValue);
    } else {
      if (m_hasDefaultValue) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AnnotationTypeElement::setDefaultValue(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDefaultValue(_node->getId());
  }

  void AnnotationTypeElement::removeDefaultValue() {
      if (m_hasDefaultValue) {
        removeParentEdge(m_hasDefaultValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDefaultValue, m_id, edkAnnotationTypeElement_HasDefaultValue);
      }
      m_hasDefaultValue = 0;
  }

  void AnnotationTypeElement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AnnotationTypeElement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AnnotationTypeElement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AnnotationTypeElement& node = dynamic_cast<const AnnotationTypeElement&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getAccessibility() == getAccessibility()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      if(node.getIsFinal() == getIsFinal()) ++matchAttrs;
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getIsStrictfp() == getIsStrictfp()) ++matchAttrs;
      return matchAttrs / (8 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void AnnotationTypeElement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType AnnotationTypeElement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::AnnotationTypeElement", strlen("struc::AnnotationTypeElement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AnnotationTypeElement::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    MethodDeclaration::sort(false);
  }

  void AnnotationTypeElement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    MethodDeclaration::save(binIo,false);

    factory->getStringTable().setType(m_defaultPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_defaultPosition.posInfo.path);
    binIo.writeUInt4(m_defaultPosition.posInfo.line);
    binIo.writeUInt4(m_defaultPosition.posInfo.col);
    binIo.writeUInt4(m_defaultPosition.posInfo.endLine);
    binIo.writeUInt4(m_defaultPosition.posInfo.endCol);
    binIo.writeUInt4(m_defaultPosition.posInfo.wideLine);
    binIo.writeUInt4(m_defaultPosition.posInfo.wideCol);
    binIo.writeUInt4(m_defaultPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_defaultPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_hasDefaultValue);

  }

  void AnnotationTypeElement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    MethodDeclaration::load(binIo,false);

    m_defaultPosition.posInfo.path = binIo.readUInt4();
    m_defaultPosition.posInfo.line = binIo.readUInt4();
    m_defaultPosition.posInfo.col = binIo.readUInt4();
    m_defaultPosition.posInfo.endLine = binIo.readUInt4();
    m_defaultPosition.posInfo.endCol = binIo.readUInt4();
    m_defaultPosition.posInfo.wideLine = binIo.readUInt4();
    m_defaultPosition.posInfo.wideCol = binIo.readUInt4();
    m_defaultPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_defaultPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_hasDefaultValue =  binIo.readUInt4();
    if (m_hasDefaultValue != 0)
      setParentEdge(factory->getPointer(m_hasDefaultValue),edkAnnotationTypeElement_HasDefaultValue);

  }


}


}}}
