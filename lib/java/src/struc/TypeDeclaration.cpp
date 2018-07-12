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

namespace struc { 
  TypeDeclaration::TypeDeclaration(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    NamedDeclaration(_id, _factory),
    Scope(_id, _factory),
    m_isAbstract(false),
    m_isStrictfp(false),
    m_typeNamePosition(),
    m_abstractPosition(),
    m_strictfpPosition(),
    m_binaryName(0),
    m_extendsPosition(),
    m_implementsPosition(),
    m_bodyStartPosition(),
    m_isInCompilationUnit(0),
    m_hasSuperClass(0),
    hasSuperInterfacesContainer(),
    hasOthersContainer()
  {
    m_typeNamePosition.posInfo.path = 0;
    m_typeNamePosition.posInfo.line = 0;
    m_typeNamePosition.posInfo.col = 0;
    m_typeNamePosition.posInfo.endLine = 0;
    m_typeNamePosition.posInfo.endCol = 0;
    m_typeNamePosition.posInfo.wideLine = 0;
    m_typeNamePosition.posInfo.wideCol = 0;
    m_typeNamePosition.posInfo.wideEndLine = 0;
    m_typeNamePosition.posInfo.wideEndCol = 0;
    m_abstractPosition.posInfo.path = 0;
    m_abstractPosition.posInfo.line = 0;
    m_abstractPosition.posInfo.col = 0;
    m_abstractPosition.posInfo.endLine = 0;
    m_abstractPosition.posInfo.endCol = 0;
    m_abstractPosition.posInfo.wideLine = 0;
    m_abstractPosition.posInfo.wideCol = 0;
    m_abstractPosition.posInfo.wideEndLine = 0;
    m_abstractPosition.posInfo.wideEndCol = 0;
    m_strictfpPosition.posInfo.path = 0;
    m_strictfpPosition.posInfo.line = 0;
    m_strictfpPosition.posInfo.col = 0;
    m_strictfpPosition.posInfo.endLine = 0;
    m_strictfpPosition.posInfo.endCol = 0;
    m_strictfpPosition.posInfo.wideLine = 0;
    m_strictfpPosition.posInfo.wideCol = 0;
    m_strictfpPosition.posInfo.wideEndLine = 0;
    m_strictfpPosition.posInfo.wideEndCol = 0;
    m_extendsPosition.posInfo.path = 0;
    m_extendsPosition.posInfo.line = 0;
    m_extendsPosition.posInfo.col = 0;
    m_extendsPosition.posInfo.endLine = 0;
    m_extendsPosition.posInfo.endCol = 0;
    m_extendsPosition.posInfo.wideLine = 0;
    m_extendsPosition.posInfo.wideCol = 0;
    m_extendsPosition.posInfo.wideEndLine = 0;
    m_extendsPosition.posInfo.wideEndCol = 0;
    m_implementsPosition.posInfo.path = 0;
    m_implementsPosition.posInfo.line = 0;
    m_implementsPosition.posInfo.col = 0;
    m_implementsPosition.posInfo.endLine = 0;
    m_implementsPosition.posInfo.endCol = 0;
    m_implementsPosition.posInfo.wideLine = 0;
    m_implementsPosition.posInfo.wideCol = 0;
    m_implementsPosition.posInfo.wideEndLine = 0;
    m_implementsPosition.posInfo.wideEndCol = 0;
    m_bodyStartPosition.posInfo.path = 0;
    m_bodyStartPosition.posInfo.line = 0;
    m_bodyStartPosition.posInfo.col = 0;
    m_bodyStartPosition.posInfo.endLine = 0;
    m_bodyStartPosition.posInfo.endCol = 0;
    m_bodyStartPosition.posInfo.wideLine = 0;
    m_bodyStartPosition.posInfo.wideCol = 0;
    m_bodyStartPosition.posInfo.wideEndLine = 0;
    m_bodyStartPosition.posInfo.wideEndCol = 0;
  }

  TypeDeclaration::~TypeDeclaration() {
  }

  void TypeDeclaration::clone(const TypeDeclaration& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    struc::NamedDeclaration::clone(other, false);
    struc::Scope::clone(other, false);

    m_typeNamePosition.posInfo = other.m_typeNamePosition.posInfo;
    m_isAbstract = other.m_isAbstract;
    m_abstractPosition.posInfo = other.m_abstractPosition.posInfo;
    m_isStrictfp = other.m_isStrictfp;
    m_strictfpPosition.posInfo = other.m_strictfpPosition.posInfo;
    m_binaryName = other.m_binaryName;
    m_extendsPosition.posInfo = other.m_extendsPosition.posInfo;
    m_implementsPosition.posInfo = other.m_implementsPosition.posInfo;
    m_bodyStartPosition.posInfo = other.m_bodyStartPosition.posInfo;
    m_isInCompilationUnit = other.m_isInCompilationUnit;
    m_hasSuperClass = other.m_hasSuperClass;
    hasSuperInterfacesContainer = other.hasSuperInterfacesContainer;
    hasOthersContainer = other.hasOthersContainer;
  }

  void TypeDeclaration::prepareDelete(bool tryOnVirtualParent){
    removeIsInCompilationUnit();
    removeSuperClass();
    while (!hasSuperInterfacesContainer.empty()) {
      const NodeId id = *hasSuperInterfacesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclaration_HasSuperInterfaces);
      hasSuperInterfacesContainer.pop_front();
    }
    while (!hasOthersContainer.empty()) {
      const NodeId id = *hasOthersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclaration_HasOthers);
      hasOthersContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
    struc::NamedDeclaration::prepareDelete(false);
    struc::Scope::prepareDelete(false);
  }

  const Range TypeDeclaration::getTypeNamePosition() const {
    return Range(factory->getStringTable(), m_typeNamePosition.posInfo);
  }

  int TypeDeclaration::compareByTypeNamePosition(const TypeDeclaration& other) const {
    if (m_typeNamePosition.posInfo.path != other.m_typeNamePosition.posInfo.path) {
      return (m_typeNamePosition.posInfo.path < other.m_typeNamePosition.posInfo.path) ? -1 :1 ;
    };
    if (m_typeNamePosition.posInfo.wideLine != other.m_typeNamePosition.posInfo.wideLine) {
      return (m_typeNamePosition.posInfo.wideLine < other.m_typeNamePosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_typeNamePosition.posInfo.wideCol != other.m_typeNamePosition.posInfo.wideCol) {
      return (m_typeNamePosition.posInfo.wideCol < other.m_typeNamePosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_typeNamePosition.posInfo.wideEndLine != other.m_typeNamePosition.posInfo.wideEndLine) {
      return (m_typeNamePosition.posInfo.wideEndLine > other.m_typeNamePosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_typeNamePosition.posInfo.wideEndCol != other.m_typeNamePosition.posInfo.wideEndCol) {
      return (m_typeNamePosition.posInfo.wideEndCol > other.m_typeNamePosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  bool TypeDeclaration::getIsAbstract() const {
    return m_isAbstract;
  }

  const Range TypeDeclaration::getAbstractPosition() const {
    return Range(factory->getStringTable(), m_abstractPosition.posInfo);
  }

  int TypeDeclaration::compareByAbstractPosition(const TypeDeclaration& other) const {
    if (m_abstractPosition.posInfo.path != other.m_abstractPosition.posInfo.path) {
      return (m_abstractPosition.posInfo.path < other.m_abstractPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideLine != other.m_abstractPosition.posInfo.wideLine) {
      return (m_abstractPosition.posInfo.wideLine < other.m_abstractPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideCol != other.m_abstractPosition.posInfo.wideCol) {
      return (m_abstractPosition.posInfo.wideCol < other.m_abstractPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideEndLine != other.m_abstractPosition.posInfo.wideEndLine) {
      return (m_abstractPosition.posInfo.wideEndLine > other.m_abstractPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_abstractPosition.posInfo.wideEndCol != other.m_abstractPosition.posInfo.wideEndCol) {
      return (m_abstractPosition.posInfo.wideEndCol > other.m_abstractPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  bool TypeDeclaration::getIsStrictfp() const {
    return m_isStrictfp;
  }

  const Range TypeDeclaration::getStrictfpPosition() const {
    return Range(factory->getStringTable(), m_strictfpPosition.posInfo);
  }

  int TypeDeclaration::compareByStrictfpPosition(const TypeDeclaration& other) const {
    if (m_strictfpPosition.posInfo.path != other.m_strictfpPosition.posInfo.path) {
      return (m_strictfpPosition.posInfo.path < other.m_strictfpPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideLine != other.m_strictfpPosition.posInfo.wideLine) {
      return (m_strictfpPosition.posInfo.wideLine < other.m_strictfpPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideCol != other.m_strictfpPosition.posInfo.wideCol) {
      return (m_strictfpPosition.posInfo.wideCol < other.m_strictfpPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideEndLine != other.m_strictfpPosition.posInfo.wideEndLine) {
      return (m_strictfpPosition.posInfo.wideEndLine > other.m_strictfpPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_strictfpPosition.posInfo.wideEndCol != other.m_strictfpPosition.posInfo.wideEndCol) {
      return (m_strictfpPosition.posInfo.wideEndCol > other.m_strictfpPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  Key TypeDeclaration::getBinaryNameKey() const {
    return m_binaryName;
  }

  const std::string& TypeDeclaration::getBinaryName() const {
    return factory->getStringTable().get(m_binaryName);
  }

  const Range TypeDeclaration::getExtendsPosition() const {
    return Range(factory->getStringTable(), m_extendsPosition.posInfo);
  }

  int TypeDeclaration::compareByExtendsPosition(const TypeDeclaration& other) const {
    if (m_extendsPosition.posInfo.path != other.m_extendsPosition.posInfo.path) {
      return (m_extendsPosition.posInfo.path < other.m_extendsPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_extendsPosition.posInfo.wideLine != other.m_extendsPosition.posInfo.wideLine) {
      return (m_extendsPosition.posInfo.wideLine < other.m_extendsPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_extendsPosition.posInfo.wideCol != other.m_extendsPosition.posInfo.wideCol) {
      return (m_extendsPosition.posInfo.wideCol < other.m_extendsPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_extendsPosition.posInfo.wideEndLine != other.m_extendsPosition.posInfo.wideEndLine) {
      return (m_extendsPosition.posInfo.wideEndLine > other.m_extendsPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_extendsPosition.posInfo.wideEndCol != other.m_extendsPosition.posInfo.wideEndCol) {
      return (m_extendsPosition.posInfo.wideEndCol > other.m_extendsPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range TypeDeclaration::getImplementsPosition() const {
    return Range(factory->getStringTable(), m_implementsPosition.posInfo);
  }

  int TypeDeclaration::compareByImplementsPosition(const TypeDeclaration& other) const {
    if (m_implementsPosition.posInfo.path != other.m_implementsPosition.posInfo.path) {
      return (m_implementsPosition.posInfo.path < other.m_implementsPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_implementsPosition.posInfo.wideLine != other.m_implementsPosition.posInfo.wideLine) {
      return (m_implementsPosition.posInfo.wideLine < other.m_implementsPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_implementsPosition.posInfo.wideCol != other.m_implementsPosition.posInfo.wideCol) {
      return (m_implementsPosition.posInfo.wideCol < other.m_implementsPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_implementsPosition.posInfo.wideEndLine != other.m_implementsPosition.posInfo.wideEndLine) {
      return (m_implementsPosition.posInfo.wideEndLine > other.m_implementsPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_implementsPosition.posInfo.wideEndCol != other.m_implementsPosition.posInfo.wideEndCol) {
      return (m_implementsPosition.posInfo.wideEndCol > other.m_implementsPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  const Range TypeDeclaration::getBodyStartPosition() const {
    return Range(factory->getStringTable(), m_bodyStartPosition.posInfo);
  }

  int TypeDeclaration::compareByBodyStartPosition(const TypeDeclaration& other) const {
    if (m_bodyStartPosition.posInfo.path != other.m_bodyStartPosition.posInfo.path) {
      return (m_bodyStartPosition.posInfo.path < other.m_bodyStartPosition.posInfo.path) ? -1 :1 ;
    };
    if (m_bodyStartPosition.posInfo.wideLine != other.m_bodyStartPosition.posInfo.wideLine) {
      return (m_bodyStartPosition.posInfo.wideLine < other.m_bodyStartPosition.posInfo.wideLine) ? -1 :1 ;
    };
    if (m_bodyStartPosition.posInfo.wideCol != other.m_bodyStartPosition.posInfo.wideCol) {
      return (m_bodyStartPosition.posInfo.wideCol < other.m_bodyStartPosition.posInfo.wideCol) ? -1 :1 ;
    };
    if (m_bodyStartPosition.posInfo.wideEndLine != other.m_bodyStartPosition.posInfo.wideEndLine) {
      return (m_bodyStartPosition.posInfo.wideEndLine > other.m_bodyStartPosition.posInfo.wideEndLine) ? -1 :1 ;
    };
    if (m_bodyStartPosition.posInfo.wideEndCol != other.m_bodyStartPosition.posInfo.wideEndCol) {
      return (m_bodyStartPosition.posInfo.wideEndCol > other.m_bodyStartPosition.posInfo.wideEndCol) ? -1 :1 ;
    };
    if (getNodeKind() != other.getNodeKind()) {
      return (getNodeKind() < other.getNodeKind()) ? -1 :1 ;
    };
    return 0;
  }

  void TypeDeclaration::setTypeNamePosition(const Range& _typeNamePosition) {
    m_typeNamePosition.posInfo = _typeNamePosition.positionInfo;
    if (_typeNamePosition.strTable != &factory->getStringTable())
      m_typeNamePosition.posInfo.path = factory->getStringTable().set(_typeNamePosition.getPath());
  }

  void TypeDeclaration::setIsAbstract(bool _isAbstract) {
    m_isAbstract = _isAbstract;
  }

  void TypeDeclaration::setAbstractPosition(const Range& _abstractPosition) {
    m_abstractPosition.posInfo = _abstractPosition.positionInfo;
    if (_abstractPosition.strTable != &factory->getStringTable())
      m_abstractPosition.posInfo.path = factory->getStringTable().set(_abstractPosition.getPath());
  }

  void TypeDeclaration::setIsStrictfp(bool _isStrictfp) {
    m_isStrictfp = _isStrictfp;
  }

  void TypeDeclaration::setStrictfpPosition(const Range& _strictfpPosition) {
    m_strictfpPosition.posInfo = _strictfpPosition.positionInfo;
    if (_strictfpPosition.strTable != &factory->getStringTable())
      m_strictfpPosition.posInfo.path = factory->getStringTable().set(_strictfpPosition.getPath());
  }

  void TypeDeclaration::setBinaryNameKey(Key _binaryName) {
    m_binaryName = _binaryName;
  }

  void TypeDeclaration::setBinaryName(const std::string& _binaryName) {
    m_binaryName = factory->getStringTable().set(_binaryName);
  }

  void TypeDeclaration::setExtendsPosition(const Range& _extendsPosition) {
    m_extendsPosition.posInfo = _extendsPosition.positionInfo;
    if (_extendsPosition.strTable != &factory->getStringTable())
      m_extendsPosition.posInfo.path = factory->getStringTable().set(_extendsPosition.getPath());
  }

  void TypeDeclaration::setImplementsPosition(const Range& _implementsPosition) {
    m_implementsPosition.posInfo = _implementsPosition.positionInfo;
    if (_implementsPosition.strTable != &factory->getStringTable())
      m_implementsPosition.posInfo.path = factory->getStringTable().set(_implementsPosition.getPath());
  }

  void TypeDeclaration::setBodyStartPosition(const Range& _bodyStartPosition) {
    m_bodyStartPosition.posInfo = _bodyStartPosition.positionInfo;
    if (_bodyStartPosition.strTable != &factory->getStringTable())
      m_bodyStartPosition.posInfo.path = factory->getStringTable().set(_bodyStartPosition.getPath());
  }

  struc::CompilationUnit* TypeDeclaration::getIsInCompilationUnit() const {
    struc::CompilationUnit *_node = NULL;
    if (m_isInCompilationUnit != 0)
      _node = dynamic_cast<struc::CompilationUnit*>(factory->getPointer(m_isInCompilationUnit));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expr::TypeExpression* TypeDeclaration::getSuperClass() const {
    expr::TypeExpression *_node = NULL;
    if (m_hasSuperClass != 0)
      _node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(m_hasSuperClass));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expr::TypeExpression> TypeDeclaration::getSuperInterfacesListIteratorBegin() const {
    return ListIterator<expr::TypeExpression>(&hasSuperInterfacesContainer, factory, true);
  }

  ListIterator<expr::TypeExpression> TypeDeclaration::getSuperInterfacesListIteratorEnd() const {
    return ListIterator<expr::TypeExpression>(&hasSuperInterfacesContainer, factory, false);
  }

  bool TypeDeclaration::getSuperInterfacesIsEmpty() const {
    return getSuperInterfacesListIteratorBegin() == getSuperInterfacesListIteratorEnd();
  }

  unsigned int TypeDeclaration::getSuperInterfacesSize() const {
    unsigned int size = 0;
    ListIterator<expr::TypeExpression> endIt = getSuperInterfacesListIteratorEnd();
    for (ListIterator<expr::TypeExpression> it = getSuperInterfacesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<base::Positioned> TypeDeclaration::getOthersListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasOthersContainer, factory, true);
  }

  ListIterator<base::Positioned> TypeDeclaration::getOthersListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasOthersContainer, factory, false);
  }

  bool TypeDeclaration::getOthersIsEmpty() const {
    return getOthersListIteratorBegin() == getOthersListIteratorEnd();
  }

  unsigned int TypeDeclaration::getOthersSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getOthersListIteratorEnd();
    for (ListIterator<base::Positioned> it = getOthersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TypeDeclaration::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeDeclaration_IsInCompilationUnit:
        setIsInCompilationUnit(edgeEnd);
        return true;
      case edkTypeDeclaration_HasSuperClass:
        setSuperClass(edgeEnd);
        return true;
      case edkTypeDeclaration_HasSuperInterfaces:
        addSuperInterfaces(edgeEnd);
        return true;
      case edkTypeDeclaration_HasOthers:
        addOthers(edgeEnd);
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
    if (struc::NamedDeclaration::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (struc::Scope::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TypeDeclaration::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeDeclaration_IsInCompilationUnit:
        removeIsInCompilationUnit();
        return true;
      case edkTypeDeclaration_HasSuperClass:
        removeSuperClass();
        return true;
      case edkTypeDeclaration_HasSuperInterfaces:
        removeSuperInterfaces(edgeEnd);
        return true;
      case edkTypeDeclaration_HasOthers:
        removeOthers(edgeEnd);
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
    if (struc::NamedDeclaration::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (struc::Scope::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeDeclaration::setIsInCompilationUnit(NodeId _id) {
    struc::CompilationUnit *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<struc::CompilationUnit*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_isInCompilationUnit) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_isInCompilationUnit, m_id, edkTypeDeclaration_IsInCompilationUnit);
      }
      m_isInCompilationUnit = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_isInCompilationUnit, this->getId(), edkTypeDeclaration_IsInCompilationUnit);
    } else {
      if (m_isInCompilationUnit) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeDeclaration::setIsInCompilationUnit(struc::CompilationUnit *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setIsInCompilationUnit(_node->getId());
  }

  void TypeDeclaration::removeIsInCompilationUnit() {
      if (m_isInCompilationUnit) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_isInCompilationUnit, m_id, edkTypeDeclaration_IsInCompilationUnit);
      }
      m_isInCompilationUnit = 0;
  }

  void TypeDeclaration::setSuperClass(NodeId _id) {
    expr::TypeExpression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::TypeExpression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasSuperClass) {
        removeParentEdge(m_hasSuperClass);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSuperClass, m_id, edkTypeDeclaration_HasSuperClass);
      }
      m_hasSuperClass = _node->getId();
      if (m_hasSuperClass != 0)
        setParentEdge(factory->getPointer(m_hasSuperClass), edkTypeDeclaration_HasSuperClass);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasSuperClass, this->getId(), edkTypeDeclaration_HasSuperClass);
    } else {
      if (m_hasSuperClass) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeDeclaration::setSuperClass(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSuperClass(_node->getId());
  }

  void TypeDeclaration::removeSuperClass() {
      if (m_hasSuperClass) {
        removeParentEdge(m_hasSuperClass);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasSuperClass, m_id, edkTypeDeclaration_HasSuperClass);
      }
      m_hasSuperClass = 0;
  }

  void TypeDeclaration::addSuperInterfaces(const expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeExpression(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasSuperInterfacesContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeDeclaration_HasSuperInterfaces);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeDeclaration_HasSuperInterfaces);
  }

  void TypeDeclaration::addSuperInterfaces(NodeId _id) {
    const expr::TypeExpression *node = dynamic_cast<expr::TypeExpression*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSuperInterfaces( node );
  }

  void TypeDeclaration::removeSuperInterfaces(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expr::TypeExpression>::Container::iterator it = find(hasSuperInterfacesContainer.begin(), hasSuperInterfacesContainer.end(), id);

    if (it == hasSuperInterfacesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasSuperInterfacesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclaration_HasSuperInterfaces);
  }

  void TypeDeclaration::removeSuperInterfaces(expr::TypeExpression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSuperInterfaces(_node->getId());
  }

  void TypeDeclaration::addOthers(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsPositioned(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasOthersContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeDeclaration_HasOthers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeDeclaration_HasOthers);
  }

  void TypeDeclaration::addOthers(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addOthers( node );
  }

  void TypeDeclaration::removeOthers(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasOthersContainer.begin(), hasOthersContainer.end(), id);

    if (it == hasOthersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasOthersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclaration_HasOthers);
  }

  void TypeDeclaration::removeOthers(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeOthers(_node->getId());
  }

  double TypeDeclaration::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const TypeDeclaration& node = dynamic_cast<const TypeDeclaration&>(base);
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
      str1 = getBinaryName();
      str2 = node.getBinaryName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (9 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void TypeDeclaration::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_binaryName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_binaryName = foundKeyId->second;
    } else {
      Key oldkey = m_binaryName;
      m_binaryName = newStrTable.set(factory->getStringTable().get(m_binaryName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_binaryName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType TypeDeclaration::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::TypeDeclaration", strlen("struc::TypeDeclaration"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeDeclaration::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    NamedDeclaration::sort(false);
    Scope::sort(false);
  }

  void TypeDeclaration::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    NamedDeclaration::save(binIo,false);

    Scope::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isAbstract) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isStrictfp) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    factory->getStringTable().setType(m_typeNamePosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_typeNamePosition.posInfo.path);
    binIo.writeUInt4(m_typeNamePosition.posInfo.line);
    binIo.writeUInt4(m_typeNamePosition.posInfo.col);
    binIo.writeUInt4(m_typeNamePosition.posInfo.endLine);
    binIo.writeUInt4(m_typeNamePosition.posInfo.endCol);
    binIo.writeUInt4(m_typeNamePosition.posInfo.wideLine);
    binIo.writeUInt4(m_typeNamePosition.posInfo.wideCol);
    binIo.writeUInt4(m_typeNamePosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_typeNamePosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_abstractPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_abstractPosition.posInfo.path);
    binIo.writeUInt4(m_abstractPosition.posInfo.line);
    binIo.writeUInt4(m_abstractPosition.posInfo.col);
    binIo.writeUInt4(m_abstractPosition.posInfo.endLine);
    binIo.writeUInt4(m_abstractPosition.posInfo.endCol);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideLine);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideCol);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_abstractPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_strictfpPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_strictfpPosition.posInfo.path);
    binIo.writeUInt4(m_strictfpPosition.posInfo.line);
    binIo.writeUInt4(m_strictfpPosition.posInfo.col);
    binIo.writeUInt4(m_strictfpPosition.posInfo.endLine);
    binIo.writeUInt4(m_strictfpPosition.posInfo.endCol);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideLine);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideCol);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_strictfpPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_binaryName, StrTable::strToSave);
    binIo.writeUInt4(m_binaryName);
    factory->getStringTable().setType(m_extendsPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_extendsPosition.posInfo.path);
    binIo.writeUInt4(m_extendsPosition.posInfo.line);
    binIo.writeUInt4(m_extendsPosition.posInfo.col);
    binIo.writeUInt4(m_extendsPosition.posInfo.endLine);
    binIo.writeUInt4(m_extendsPosition.posInfo.endCol);
    binIo.writeUInt4(m_extendsPosition.posInfo.wideLine);
    binIo.writeUInt4(m_extendsPosition.posInfo.wideCol);
    binIo.writeUInt4(m_extendsPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_extendsPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_implementsPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_implementsPosition.posInfo.path);
    binIo.writeUInt4(m_implementsPosition.posInfo.line);
    binIo.writeUInt4(m_implementsPosition.posInfo.col);
    binIo.writeUInt4(m_implementsPosition.posInfo.endLine);
    binIo.writeUInt4(m_implementsPosition.posInfo.endCol);
    binIo.writeUInt4(m_implementsPosition.posInfo.wideLine);
    binIo.writeUInt4(m_implementsPosition.posInfo.wideCol);
    binIo.writeUInt4(m_implementsPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_implementsPosition.posInfo.wideEndCol);
    factory->getStringTable().setType(m_bodyStartPosition.posInfo.path, StrTable::strToSave);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.path);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.line);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.col);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.endLine);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.endCol);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.wideLine);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.wideCol);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.wideEndLine);
    binIo.writeUInt4(m_bodyStartPosition.posInfo.wideEndCol);

    binIo.writeUInt4(m_isInCompilationUnit);
    binIo.writeUInt4(m_hasSuperClass);


    for (ListIterator<expr::TypeExpression>::Container::const_iterator it = hasSuperInterfacesContainer.begin(); it != hasSuperInterfacesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<base::Positioned>::Container::const_iterator it = hasOthersContainer.begin(); it != hasOthersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeDeclaration::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    NamedDeclaration::load(binIo,false);

    Scope::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isStrictfp = boolValues & 1;
    boolValues >>= 1;
    m_isAbstract = boolValues & 1;
    boolValues >>= 1;
    m_typeNamePosition.posInfo.path = binIo.readUInt4();
    m_typeNamePosition.posInfo.line = binIo.readUInt4();
    m_typeNamePosition.posInfo.col = binIo.readUInt4();
    m_typeNamePosition.posInfo.endLine = binIo.readUInt4();
    m_typeNamePosition.posInfo.endCol = binIo.readUInt4();
    m_typeNamePosition.posInfo.wideLine = binIo.readUInt4();
    m_typeNamePosition.posInfo.wideCol = binIo.readUInt4();
    m_typeNamePosition.posInfo.wideEndLine = binIo.readUInt4();
    m_typeNamePosition.posInfo.wideEndCol = binIo.readUInt4();
    m_abstractPosition.posInfo.path = binIo.readUInt4();
    m_abstractPosition.posInfo.line = binIo.readUInt4();
    m_abstractPosition.posInfo.col = binIo.readUInt4();
    m_abstractPosition.posInfo.endLine = binIo.readUInt4();
    m_abstractPosition.posInfo.endCol = binIo.readUInt4();
    m_abstractPosition.posInfo.wideLine = binIo.readUInt4();
    m_abstractPosition.posInfo.wideCol = binIo.readUInt4();
    m_abstractPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_abstractPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_strictfpPosition.posInfo.path = binIo.readUInt4();
    m_strictfpPosition.posInfo.line = binIo.readUInt4();
    m_strictfpPosition.posInfo.col = binIo.readUInt4();
    m_strictfpPosition.posInfo.endLine = binIo.readUInt4();
    m_strictfpPosition.posInfo.endCol = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideLine = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideCol = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_strictfpPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_binaryName = binIo.readUInt4();
    m_extendsPosition.posInfo.path = binIo.readUInt4();
    m_extendsPosition.posInfo.line = binIo.readUInt4();
    m_extendsPosition.posInfo.col = binIo.readUInt4();
    m_extendsPosition.posInfo.endLine = binIo.readUInt4();
    m_extendsPosition.posInfo.endCol = binIo.readUInt4();
    m_extendsPosition.posInfo.wideLine = binIo.readUInt4();
    m_extendsPosition.posInfo.wideCol = binIo.readUInt4();
    m_extendsPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_extendsPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_implementsPosition.posInfo.path = binIo.readUInt4();
    m_implementsPosition.posInfo.line = binIo.readUInt4();
    m_implementsPosition.posInfo.col = binIo.readUInt4();
    m_implementsPosition.posInfo.endLine = binIo.readUInt4();
    m_implementsPosition.posInfo.endCol = binIo.readUInt4();
    m_implementsPosition.posInfo.wideLine = binIo.readUInt4();
    m_implementsPosition.posInfo.wideCol = binIo.readUInt4();
    m_implementsPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_implementsPosition.posInfo.wideEndCol = binIo.readUInt4();
    m_bodyStartPosition.posInfo.path = binIo.readUInt4();
    m_bodyStartPosition.posInfo.line = binIo.readUInt4();
    m_bodyStartPosition.posInfo.col = binIo.readUInt4();
    m_bodyStartPosition.posInfo.endLine = binIo.readUInt4();
    m_bodyStartPosition.posInfo.endCol = binIo.readUInt4();
    m_bodyStartPosition.posInfo.wideLine = binIo.readUInt4();
    m_bodyStartPosition.posInfo.wideCol = binIo.readUInt4();
    m_bodyStartPosition.posInfo.wideEndLine = binIo.readUInt4();
    m_bodyStartPosition.posInfo.wideEndCol = binIo.readUInt4();

    m_isInCompilationUnit =  binIo.readUInt4();

    m_hasSuperClass =  binIo.readUInt4();
    if (m_hasSuperClass != 0)
      setParentEdge(factory->getPointer(m_hasSuperClass),edkTypeDeclaration_HasSuperClass);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasSuperInterfacesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeDeclaration_HasSuperInterfaces);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasOthersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeDeclaration_HasOthers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
