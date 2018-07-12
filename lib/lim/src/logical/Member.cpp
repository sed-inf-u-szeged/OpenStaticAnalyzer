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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace logical { 
  Member::Member(NodeId _id, Factory *_factory) :
    Named(_id, _factory),
    m_isCompilerGenerated(false),
    m_isStatic(false),
    m_accessibility(ackInternal),
    m_commentLines(0),
    m_language(lnkNotSet),
    m_demangledName(0),
    m_mangledName(0),
    m_aggregated(0),
    belongsToContainer(),
    compilationUnitContainer(),
    m_declares(0),
    hasCommentContainer(),
    instanceContainer(),
    isContainedInContainer(),
    m_languageVariant(0),
    usesContainer(),
    variantContainer()
  {
  }

  Member::~Member() {
  }

  void Member::clone(const Member& other, bool tryOnVirtualParent) {
    base::Named::clone(other, false);

    m_accessibility = other.m_accessibility;
    m_commentLines = other.m_commentLines;
    m_demangledName = other.m_demangledName;
    m_isCompilerGenerated = other.m_isCompilerGenerated;
    m_isStatic = other.m_isStatic;
    m_language = other.m_language;
    m_mangledName = other.m_mangledName;
    m_aggregated = other.m_aggregated;
    belongsToContainer = other.belongsToContainer;
    compilationUnitContainer = other.compilationUnitContainer;
    m_declares = other.m_declares;
    hasCommentContainer = other.hasCommentContainer;
    instanceContainer = other.instanceContainer;
    //isAssocEdge
    isContainedInContainer = other.isContainedInContainer;
    m_languageVariant = other.m_languageVariant;
    usesContainer = other.usesContainer;
    variantContainer = other.variantContainer;
  }

  void Member::prepareDelete(bool tryOnVirtualParent){
    removeAggregated();
    while (!belongsToContainer.empty()) {
      const NodeId id = *belongsToContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMember_BelongsTo);
      belongsToContainer.pop_front();
    }
    while (!compilationUnitContainer.empty()) {
      const NodeId id = *compilationUnitContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMember_CompilationUnit);
      compilationUnitContainer.pop_front();
    }
    removeDeclares();
    while (!hasCommentContainer.empty()) {
      const NodeId id = *hasCommentContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMember_HasComment);
      hasCommentContainer.pop_front();
    }
    while (!instanceContainer.empty()) {
      const NodeId id = *instanceContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMember_Instance);
      instanceContainer.pop_front();
    }
    while (!isContainedInContainer.empty()) {
      const NodeId id = *isContainedInContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMember_IsContainedIn);
      isContainedInContainer.pop_front();
    }
    removeLanguageVariant();
    while (!usesContainer.empty()) {
      const NodeId id = *usesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMember_Uses);
      usesContainer.pop_front();
    }
    while (!variantContainer.empty()) {
      const NodeId id = *variantContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMember_Variant);
      variantContainer.pop_front();
    }
    base::Named::prepareDelete(false);
  }

  AccessibilityKind Member::getAccessibility() const {
    return m_accessibility;
  }

  unsigned Member::getCommentLines() const {
    return m_commentLines;
  }

  Key Member::getDemangledNameKey() const {
    return m_demangledName;
  }

  const std::string& Member::getDemangledName() const {
    return factory->getStringTable().get(m_demangledName);
  }

  bool Member::getIsCompilerGenerated() const {
    return m_isCompilerGenerated;
  }

  bool Member::getIsStatic() const {
    return m_isStatic;
  }

  LanguageKind Member::getLanguage() const {
    return m_language;
  }

  Key Member::getMangledNameKey() const {
    return m_mangledName;
  }

  const std::string& Member::getMangledName() const {
    return factory->getStringTable().get(m_mangledName);
  }

  void Member::setAccessibility(AccessibilityKind _accessibility) {
    m_accessibility = _accessibility;
  }

  void Member::setCommentLines(unsigned _commentLines) {
    m_commentLines = _commentLines;
  }

  void Member::setDemangledNameKey(Key _demangledName) {
    m_demangledName = _demangledName;
  }

  void Member::setDemangledName(const std::string& _demangledName) {
    m_demangledName = factory->getStringTable().set(_demangledName);
  }

  void Member::setIsCompilerGenerated(bool _isCompilerGenerated) {
    m_isCompilerGenerated = _isCompilerGenerated;
  }

  void Member::setIsStatic(bool _isStatic) {
    m_isStatic = _isStatic;
  }

  void Member::setLanguage(LanguageKind _language) {
    m_language = _language;
  }

  void Member::setMangledNameKey(Key _mangledName) {
    m_mangledName = _mangledName;
  }

  void Member::setMangledName(const std::string& _mangledName) {
    m_mangledName = factory->getStringTable().set(_mangledName);
  }

  logical::Member* Member::getAggregated() const {
    logical::Member *_node = NULL;
    if (m_aggregated != 0)
      _node = dynamic_cast<logical::Member*>(factory->getPointer(m_aggregated));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<base::Component> Member::getBelongsToListIteratorBegin() const {
    return ListIterator<base::Component>(&belongsToContainer, factory, true);
  }

  ListIterator<base::Component> Member::getBelongsToListIteratorEnd() const {
    return ListIterator<base::Component>(&belongsToContainer, factory, false);
  }

  bool Member::getBelongsToIsEmpty() const {
    return getBelongsToListIteratorBegin() == getBelongsToListIteratorEnd();
  }

  unsigned int Member::getBelongsToSize() const {
    unsigned int size = 0;
    ListIterator<base::Component> endIt = getBelongsToListIteratorEnd();
    for (ListIterator<base::Component> it = getBelongsToListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<physical::File> Member::getCompilationUnitListIteratorBegin() const {
    return ListIterator<physical::File>(&compilationUnitContainer, factory, true);
  }

  ListIterator<physical::File> Member::getCompilationUnitListIteratorEnd() const {
    return ListIterator<physical::File>(&compilationUnitContainer, factory, false);
  }

  bool Member::getCompilationUnitIsEmpty() const {
    return getCompilationUnitListIteratorBegin() == getCompilationUnitListIteratorEnd();
  }

  unsigned int Member::getCompilationUnitSize() const {
    unsigned int size = 0;
    ListIterator<physical::File> endIt = getCompilationUnitListIteratorEnd();
    for (ListIterator<physical::File> it = getCompilationUnitListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  logical::Member* Member::getDeclares() const {
    logical::Member *_node = NULL;
    if (m_declares != 0)
      _node = dynamic_cast<logical::Member*>(factory->getPointer(m_declares));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<base::Comment> Member::getCommentListIteratorBegin() const {
    return ListIterator<base::Comment>(&hasCommentContainer, factory, true);
  }

  ListIterator<base::Comment> Member::getCommentListIteratorEnd() const {
    return ListIterator<base::Comment>(&hasCommentContainer, factory, false);
  }

  bool Member::getCommentIsEmpty() const {
    return getCommentListIteratorBegin() == getCommentListIteratorEnd();
  }

  unsigned int Member::getCommentSize() const {
    unsigned int size = 0;
    ListIterator<base::Comment> endIt = getCommentListIteratorEnd();
    for (ListIterator<base::Comment> it = getCommentListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<logical::Member> Member::getInstanceListIteratorBegin() const {
    return ListIterator<logical::Member>(&instanceContainer, factory, true);
  }

  ListIterator<logical::Member> Member::getInstanceListIteratorEnd() const {
    return ListIterator<logical::Member>(&instanceContainer, factory, false);
  }

  bool Member::getInstanceIsEmpty() const {
    return getInstanceListIteratorBegin() == getInstanceListIteratorEnd();
  }

  unsigned int Member::getInstanceSize() const {
    unsigned int size = 0;
    ListIterator<logical::Member> endIt = getInstanceListIteratorEnd();
    for (ListIterator<logical::Member> it = getInstanceListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIteratorAssocSourcePosition<physical::File> Member::getIsContainedInListIteratorAssocBegin() const {
    return ListIteratorAssocSourcePosition<physical::File>(&isContainedInContainer, factory, true);
  }

  ListIteratorAssocSourcePosition<physical::File> Member::getIsContainedInListIteratorAssocEnd() const {
    return ListIteratorAssocSourcePosition<physical::File>(&isContainedInContainer, factory, false);
  }

  bool Member::getIsContainedInIsEmpty() const {
    return getIsContainedInListIteratorAssocBegin() == getIsContainedInListIteratorAssocEnd();
  }

  unsigned int Member::getIsContainedInSize() const {
    unsigned int size = 0;
    ListIteratorAssocSourcePosition<physical::File> endIt = getIsContainedInListIteratorAssocEnd();
    for (ListIteratorAssocSourcePosition<physical::File> it = getIsContainedInListIteratorAssocBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  logical::Member* Member::getLanguageVariant() const {
    logical::Member *_node = NULL;
    if (m_languageVariant != 0)
      _node = dynamic_cast<logical::Member*>(factory->getPointer(m_languageVariant));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<type::Type> Member::getUsesListIteratorBegin() const {
    return ListIterator<type::Type>(&usesContainer, factory, true);
  }

  ListIterator<type::Type> Member::getUsesListIteratorEnd() const {
    return ListIterator<type::Type>(&usesContainer, factory, false);
  }

  bool Member::getUsesIsEmpty() const {
    return getUsesListIteratorBegin() == getUsesListIteratorEnd();
  }

  unsigned int Member::getUsesSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getUsesListIteratorEnd();
    for (ListIterator<type::Type> it = getUsesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<logical::Member> Member::getVariantListIteratorBegin() const {
    return ListIterator<logical::Member>(&variantContainer, factory, true);
  }

  ListIterator<logical::Member> Member::getVariantListIteratorEnd() const {
    return ListIterator<logical::Member>(&variantContainer, factory, false);
  }

  bool Member::getVariantIsEmpty() const {
    return getVariantListIteratorBegin() == getVariantListIteratorEnd();
  }

  unsigned int Member::getVariantSize() const {
    unsigned int size = 0;
    ListIterator<logical::Member> endIt = getVariantListIteratorEnd();
    for (ListIterator<logical::Member> it = getVariantListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Member::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMember_Aggregated:
        setAggregated(edgeEnd);
        return true;
      case edkMember_BelongsTo:
        addBelongsTo(edgeEnd);
        return true;
      case edkMember_CompilationUnit:
        addCompilationUnit(edgeEnd);
        return true;
      case edkMember_Declares:
        setDeclares(edgeEnd);
        return true;
      case edkMember_HasComment:
        addComment(edgeEnd);
        return true;
      case edkMember_Instance:
        addInstance(edgeEnd);
        return true;
      case edkMember_IsContainedIn:
        addIsContainedIn(edgeEnd, *((const SourcePosition*)acValue));
        return true;
      case edkMember_LanguageVariant:
        setLanguageVariant(edgeEnd);
        return true;
      case edkMember_Uses:
        addUses(edgeEnd);
        return true;
      case edkMember_Variant:
        addVariant(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Member::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMember_Aggregated:
        removeAggregated();
        return true;
      case edkMember_BelongsTo:
        removeBelongsTo(edgeEnd);
        return true;
      case edkMember_CompilationUnit:
        removeCompilationUnit(edgeEnd);
        return true;
      case edkMember_Declares:
        removeDeclares();
        return true;
      case edkMember_HasComment:
        removeComment(edgeEnd);
        return true;
      case edkMember_Instance:
        removeInstance(edgeEnd);
        return true;
      case edkMember_IsContainedIn:
        removeIsContainedIn(edgeEnd);
        return true;
      case edkMember_LanguageVariant:
        removeLanguageVariant();
        return true;
      case edkMember_Uses:
        removeUses(edgeEnd);
        return true;
      case edkMember_Variant:
        removeVariant(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Member::setAggregated(NodeId _id) {
    logical::Member *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<logical::Member*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_aggregated) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_aggregated, m_id, edkMember_Aggregated);
      }
      m_aggregated = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_aggregated, this->getId(), edkMember_Aggregated);
    } else {
      if (m_aggregated) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Member::setAggregated(logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAggregated(_node->getId());
  }

  void Member::removeAggregated() {
      if (m_aggregated) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_aggregated, m_id, edkMember_Aggregated);
      }
      m_aggregated = 0;
  }

  void Member::addBelongsTo(const base::Component *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkComponent) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    belongsToContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMember_BelongsTo);
  }

  void Member::addBelongsTo(NodeId _id) {
    const base::Component *node = dynamic_cast<base::Component*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addBelongsTo( node );
  }

  void Member::removeBelongsTo(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Component>::Container::iterator it = find(belongsToContainer.begin(), belongsToContainer.end(), id);

    if (it == belongsToContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    belongsToContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMember_BelongsTo);
  }

  void Member::removeBelongsTo(base::Component *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeBelongsTo(_node->getId());
  }

  void Member::addCompilationUnit(const physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkFile) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    compilationUnitContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMember_CompilationUnit);
  }

  void Member::addCompilationUnit(NodeId _id) {
    const physical::File *node = dynamic_cast<physical::File*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCompilationUnit( node );
  }

  void Member::removeCompilationUnit(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<physical::File>::Container::iterator it = find(compilationUnitContainer.begin(), compilationUnitContainer.end(), id);

    if (it == compilationUnitContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    compilationUnitContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMember_CompilationUnit);
  }

  void Member::removeCompilationUnit(physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCompilationUnit(_node->getId());
  }

  void Member::setDeclares(NodeId _id) {
    logical::Member *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<logical::Member*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_declares) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_declares, m_id, edkMember_Declares);
      }
      m_declares = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_declares, this->getId(), edkMember_Declares);
    } else {
      if (m_declares) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Member::setDeclares(logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDeclares(_node->getId());
  }

  void Member::removeDeclares() {
      if (m_declares) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_declares, m_id, edkMember_Declares);
      }
      m_declares = 0;
  }

  void Member::addComment(const base::Comment *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkComment) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasCommentContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMember_HasComment);
  }

  void Member::addComment(NodeId _id) {
    const base::Comment *node = dynamic_cast<base::Comment*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addComment( node );
  }

  void Member::removeComment(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Comment>::Container::iterator it = find(hasCommentContainer.begin(), hasCommentContainer.end(), id);

    if (it == hasCommentContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasCommentContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMember_HasComment);
  }

  void Member::removeComment(base::Comment *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeComment(_node->getId());
  }

  void Member::addInstance(const logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMember(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    instanceContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMember_Instance);
  }

  void Member::addInstance(NodeId _id) {
    const logical::Member *node = dynamic_cast<logical::Member*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addInstance( node );
  }

  void Member::removeInstance(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::Member>::Container::iterator it = find(instanceContainer.begin(), instanceContainer.end(), id);

    if (it == instanceContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    instanceContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMember_Instance);
  }

  void Member::removeInstance(logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeInstance(_node->getId());
  }

  void Member::addIsContainedIn(const physical::File *_node, const SourcePosition& acValue) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkFile) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AssocEdge<NodeId,SourcePosition> ac(_node->getId(), acValue);
    isContainedInContainer.push_back(ac);
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMember_IsContainedIn);
  }

  void Member::addIsContainedIn(NodeId _id, const SourcePosition& acValue) {
    const physical::File *node = dynamic_cast<physical::File*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addIsContainedIn( node, acValue );
  }

  void Member::removeIsContainedIn(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIteratorAssocSourcePosition<physical::File>::Container::iterator it = find(isContainedInContainer.begin(), isContainedInContainer.end(), id);

    if (it == isContainedInContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    isContainedInContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMember_IsContainedIn);
  }

  void Member::removeIsContainedIn(physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeIsContainedIn(_node->getId());
  }

  void Member::setLanguageVariant(NodeId _id) {
    logical::Member *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<logical::Member*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_languageVariant) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_languageVariant, m_id, edkMember_LanguageVariant);
      }
      m_languageVariant = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_languageVariant, this->getId(), edkMember_LanguageVariant);
    } else {
      if (m_languageVariant) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Member::setLanguageVariant(logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLanguageVariant(_node->getId());
  }

  void Member::removeLanguageVariant() {
      if (m_languageVariant) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_languageVariant, m_id, edkMember_LanguageVariant);
      }
      m_languageVariant = 0;
  }

  void Member::addUses(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    usesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMember_Uses);
  }

  void Member::addUses(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addUses( node );
  }

  void Member::removeUses(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(usesContainer.begin(), usesContainer.end(), id);

    if (it == usesContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    usesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMember_Uses);
  }

  void Member::removeUses(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeUses(_node->getId());
  }

  void Member::addVariant(const logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMember(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    variantContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMember_Variant);
  }

  void Member::addVariant(NodeId _id) {
    const logical::Member *node = dynamic_cast<logical::Member*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addVariant( node );
  }

  void Member::removeVariant(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::Member>::Container::iterator it = find(variantContainer.begin(), variantContainer.end(), id);

    if (it == variantContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    variantContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMember_Variant);
  }

  void Member::removeVariant(logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeVariant(_node->getId());
  }

  double Member::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Member& node = dynamic_cast<const Member&>(base);
      double matchAttrs = 0;
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
      if(node.getCommentLines() == getCommentLines()) ++matchAttrs;
      str1 = getDemangledName();
      str2 = node.getDemangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      if(node.getLanguage() == getLanguage()) ++matchAttrs;
      str1 = getMangledName();
      str2 = node.getMangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (8 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Member::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_demangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_demangledName = foundKeyId->second;
    } else {
      Key oldkey = m_demangledName;
      m_demangledName = newStrTable.set(factory->getStringTable().get(m_demangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_demangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_mangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_mangledName = foundKeyId->second;
    } else {
      Key oldkey = m_mangledName;
      m_mangledName = newStrTable.set(factory->getStringTable().get(m_mangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_mangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Member::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::Member", strlen("logical::Member"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Member::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Named::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isCompilerGenerated) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isStatic) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUByte1(m_accessibility);
    binIo.writeUInt4(m_commentLines);
    factory->getStringTable().setType(m_demangledName, StrTable::strToSave);
    binIo.writeUInt4(m_demangledName);
    binIo.writeUByte1(m_language);
    factory->getStringTable().setType(m_mangledName, StrTable::strToSave);
    binIo.writeUInt4(m_mangledName);

    binIo.writeUInt4(m_aggregated);
    binIo.writeUInt4(m_declares);
    binIo.writeUInt4(m_languageVariant);


    for (ListIterator<base::Component>::Container::const_iterator it = belongsToContainer.begin(); it != belongsToContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<physical::File>::Container::const_iterator it = compilationUnitContainer.begin(); it != compilationUnitContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<base::Comment>::Container::const_iterator it = hasCommentContainer.begin(); it != hasCommentContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<logical::Member>::Container::const_iterator it = instanceContainer.begin(); it != instanceContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIteratorAssocSourcePosition<physical::File>::Container::const_iterator ait = isContainedInContainer.begin(); ait != isContainedInContainer.end(); ++ait) {
      binIo.writeUInt4(ait->node);
      ait->assocClass.save(binIo);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = usesContainer.begin(); it != usesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<logical::Member>::Container::const_iterator it = variantContainer.begin(); it != variantContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Member::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Named::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isStatic = boolValues & 1;
    boolValues >>= 1;
    m_isCompilerGenerated = boolValues & 1;
    boolValues >>= 1;
    m_accessibility = (AccessibilityKind)binIo.readUByte1();
    m_commentLines = binIo.readUInt4();
    m_demangledName = binIo.readUInt4();
    m_language = (LanguageKind)binIo.readUByte1();
    m_mangledName = binIo.readUInt4();

    m_aggregated =  binIo.readUInt4();

    m_declares =  binIo.readUInt4();

    m_languageVariant =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      belongsToContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      compilationUnitContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasCommentContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      instanceContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      SourcePosition _ac;
      _ac.load(binIo);
      isContainedInContainer.push_back(AssocEdge<NodeId,SourcePosition>(_id, _ac));
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      usesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      variantContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
