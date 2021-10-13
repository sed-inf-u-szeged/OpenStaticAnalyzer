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

#include <set>
#include <map>
using namespace std;


namespace columbus { namespace lim { namespace asg {
AlgorithmDeepCopy::AlgorithmDeepCopy(NodeId what, Factory& srcFact, Factory& targetFact, std::map<const base::Base*,base::Base*>& mapped_nodes) : 
  srcFact(srcFact), targetFact(targetFact), what(what), lastNode(0), mapped_nodes(mapped_nodes) {
}

AlgorithmDeepCopy::~AlgorithmDeepCopy() {}

base::Base* AlgorithmDeepCopy::clone() {
  base::Base* rv = clone(srcFact.getPointer(what));
  return rv;
}

std::map<const base::Base*, base::Base*>& AlgorithmDeepCopy::getMapping() {
  return mapped_nodes;
}

base::Base* AlgorithmDeepCopy::createNode(const base::Base* oldNode, NodeKind ndk) {
  base::Base* newNode = targetFact.createNode(ndk);
  lastNode = newNode;
  mapped_nodes[oldNode] = newNode;
  return newNode;
}

base::Base* AlgorithmDeepCopy::getMappedNode(const base::Base* oldNode) {
  if(oldNode == NULL) return NULL;
  map<const base::Base*, base::Base*>::iterator iter=mapped_nodes.find(oldNode);
  if(iter == mapped_nodes.end()) {
    base::Base* newNode = clone(oldNode);
    return newNode ;
  } else {
    return iter->second;
  }
}

base::Base* AlgorithmDeepCopy::clone(const base::Base* old) {
  base::Base* newNode;
  switch(old->getNodeKind()) {
    case ndkComment: 
      newNode = createNode(old,ndkComment);
      clone(dynamic_cast<base::Comment*>(newNode), dynamic_cast<const base::Comment*>(old));
      break;
    case ndkComponent: 
      newNode = createNode(old,ndkComponent);
      clone(dynamic_cast<base::Component*>(newNode), dynamic_cast<const base::Component*>(old));
      break;
    case ndkControlFlowBlock: 
      newNode = createNode(old,ndkControlFlowBlock);
      clone(dynamic_cast<base::ControlFlowBlock*>(newNode), dynamic_cast<const base::ControlFlowBlock*>(old));
      break;
    case ndkAttribute: 
      newNode = createNode(old,ndkAttribute);
      clone(dynamic_cast<logical::Attribute*>(newNode), dynamic_cast<const logical::Attribute*>(old));
      break;
    case ndkAttributeAccess: 
      newNode = createNode(old,ndkAttributeAccess);
      clone(dynamic_cast<logical::AttributeAccess*>(newNode), dynamic_cast<const logical::AttributeAccess*>(old));
      break;
    case ndkClass: 
      newNode = createNode(old,ndkClass);
      clone(dynamic_cast<logical::Class*>(newNode), dynamic_cast<const logical::Class*>(old));
      break;
    case ndkClassGeneric: 
      newNode = createNode(old,ndkClassGeneric);
      clone(dynamic_cast<logical::ClassGeneric*>(newNode), dynamic_cast<const logical::ClassGeneric*>(old));
      break;
    case ndkClassGenericInstance: 
      newNode = createNode(old,ndkClassGenericInstance);
      clone(dynamic_cast<logical::ClassGenericInstance*>(newNode), dynamic_cast<const logical::ClassGenericInstance*>(old));
      break;
    case ndkClassGenericSpec: 
      newNode = createNode(old,ndkClassGenericSpec);
      clone(dynamic_cast<logical::ClassGenericSpec*>(newNode), dynamic_cast<const logical::ClassGenericSpec*>(old));
      break;
    case ndkFriendship: 
      newNode = createNode(old,ndkFriendship);
      clone(dynamic_cast<logical::Friendship*>(newNode), dynamic_cast<const logical::Friendship*>(old));
      break;
    case ndkGenericParameter: 
      newNode = createNode(old,ndkGenericParameter);
      clone(dynamic_cast<logical::GenericParameter*>(newNode), dynamic_cast<const logical::GenericParameter*>(old));
      break;
    case ndkMethod: 
      newNode = createNode(old,ndkMethod);
      clone(dynamic_cast<logical::Method*>(newNode), dynamic_cast<const logical::Method*>(old));
      break;
    case ndkMethodCall: 
      newNode = createNode(old,ndkMethodCall);
      clone(dynamic_cast<logical::MethodCall*>(newNode), dynamic_cast<const logical::MethodCall*>(old));
      break;
    case ndkMethodGeneric: 
      newNode = createNode(old,ndkMethodGeneric);
      clone(dynamic_cast<logical::MethodGeneric*>(newNode), dynamic_cast<const logical::MethodGeneric*>(old));
      break;
    case ndkMethodGenericInstance: 
      newNode = createNode(old,ndkMethodGenericInstance);
      clone(dynamic_cast<logical::MethodGenericInstance*>(newNode), dynamic_cast<const logical::MethodGenericInstance*>(old));
      break;
    case ndkMethodGenericSpec: 
      newNode = createNode(old,ndkMethodGenericSpec);
      clone(dynamic_cast<logical::MethodGenericSpec*>(newNode), dynamic_cast<const logical::MethodGenericSpec*>(old));
      break;
    case ndkPackage: 
      newNode = createNode(old,ndkPackage);
      clone(dynamic_cast<logical::Package*>(newNode), dynamic_cast<const logical::Package*>(old));
      break;
    case ndkParameter: 
      newNode = createNode(old,ndkParameter);
      clone(dynamic_cast<logical::Parameter*>(newNode), dynamic_cast<const logical::Parameter*>(old));
      break;
    case ndkFile: 
      newNode = createNode(old,ndkFile);
      clone(dynamic_cast<physical::File*>(newNode), dynamic_cast<const physical::File*>(old));
      break;
    case ndkFileSystem: 
      newNode = createNode(old,ndkFileSystem);
      clone(dynamic_cast<physical::FileSystem*>(newNode), dynamic_cast<const physical::FileSystem*>(old));
      break;
    case ndkFolder: 
      newNode = createNode(old,ndkFolder);
      clone(dynamic_cast<physical::Folder*>(newNode), dynamic_cast<const physical::Folder*>(old));
      break;
    case ndkSimpleType: 
      newNode = createNode(old,ndkSimpleType);
      clone(dynamic_cast<type::SimpleType*>(newNode), dynamic_cast<const type::SimpleType*>(old));
      break;
    case ndkType: 
      newNode = createNode(old,ndkType);
      clone(dynamic_cast<type::Type*>(newNode), dynamic_cast<const type::Type*>(old));
      break;
    case ndkTypeFormerArray: 
      newNode = createNode(old,ndkTypeFormerArray);
      clone(dynamic_cast<type::TypeFormerArray*>(newNode), dynamic_cast<const type::TypeFormerArray*>(old));
      break;
    case ndkTypeFormerMethod: 
      newNode = createNode(old,ndkTypeFormerMethod);
      clone(dynamic_cast<type::TypeFormerMethod*>(newNode), dynamic_cast<const type::TypeFormerMethod*>(old));
      break;
    case ndkTypeFormerNonType: 
      newNode = createNode(old,ndkTypeFormerNonType);
      clone(dynamic_cast<type::TypeFormerNonType*>(newNode), dynamic_cast<const type::TypeFormerNonType*>(old));
      break;
    case ndkTypeFormerPointer: 
      newNode = createNode(old,ndkTypeFormerPointer);
      clone(dynamic_cast<type::TypeFormerPointer*>(newNode), dynamic_cast<const type::TypeFormerPointer*>(old));
      break;
    case ndkTypeFormerType: 
      newNode = createNode(old,ndkTypeFormerType);
      clone(dynamic_cast<type::TypeFormerType*>(newNode), dynamic_cast<const type::TypeFormerType*>(old));
      break;
    default: newNode = NULL; break;
  }
  return newNode;
}
void AlgorithmDeepCopy::clone(base::Base* dest, const base::Base* src) {
}

void AlgorithmDeepCopy::clone(base::Comment* dest, const base::Comment* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setText(src->getText());
  // Copying edges
}

void AlgorithmDeepCopy::clone(base::Component* dest, const base::Component* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setAnalysisTime(src->getAnalysisTime());
  dest->setChangesetID(src->getChangesetID());
  dest->setShortName(src->getShortName());
  // Copying edges
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  for ( ListIterator<base::Component> it = src->getContainsListIteratorBegin(); it != src->getContainsListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addContains(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getFilesListIteratorBegin(); it != src->getFilesListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addFiles(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(base::ControlFlowBlock* dest, const base::ControlFlowBlock* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<logical::Method> it = src->getCallsListIteratorBegin(); it != src->getCallsListIteratorEnd(); ++it ) {
    logical::Method* pNewEdge = dynamic_cast<logical::Method*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCalls(pNewEdge);
  }
  for ( ListIterator<base::ControlFlowBlock> it = src->getPredListIteratorBegin(); it != src->getPredListIteratorEnd(); ++it ) {
    base::ControlFlowBlock* pNewEdge = dynamic_cast<base::ControlFlowBlock*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addPred(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(base::Named* dest, const base::Named* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
}

void AlgorithmDeepCopy::clone(logical::Attribute* dest, const logical::Attribute* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIterator<logical::MethodCall> it = src->getCallsListIteratorBegin(); it != src->getCallsListIteratorEnd(); ++it ) {
    logical::MethodCall* pNewEdge = dynamic_cast<logical::MethodCall*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCalls(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getTypeListIteratorBegin(); it != src->getTypeListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addType(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(logical::AttributeAccess* dest, const logical::AttributeAccess* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setAccesses(src->getAccesses());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAttribute());
  if (pNewSingleEdge)
    dest->setAttribute(dynamic_cast<logical::Attribute*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(logical::Class* dest, const logical::Class* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setClassKind(src->getClassKind());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setObjectSize(src->getObjectSize());
  // Copying edges
  for ( ListIterator<logical::Class> it = src->getExtendsListIteratorBegin(); it != src->getExtendsListIteratorEnd(); ++it ) {
    logical::Class* pNewEdge = dynamic_cast<logical::Class*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addExtends(pNewEdge);
  }
  for ( ListIterator<logical::Friendship> it = src->getGrantsFriendshipListIteratorBegin(); it != src->getGrantsFriendshipListIteratorEnd(); ++it ) {
    logical::Friendship* pNewEdge = dynamic_cast<logical::Friendship*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGrantsFriendship(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getIsSubclassListIteratorBegin(); it != src->getIsSubclassListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsSubclass(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(logical::ClassGeneric* dest, const logical::ClassGeneric* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setClassKind(src->getClassKind());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setObjectSize(src->getObjectSize());
  // Copying edges
  for ( ListIterator<logical::Class> it = src->getExtendsListIteratorBegin(); it != src->getExtendsListIteratorEnd(); ++it ) {
    logical::Class* pNewEdge = dynamic_cast<logical::Class*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addExtends(pNewEdge);
  }
  for ( ListIterator<logical::Friendship> it = src->getGrantsFriendshipListIteratorBegin(); it != src->getGrantsFriendshipListIteratorEnd(); ++it ) {
    logical::Friendship* pNewEdge = dynamic_cast<logical::Friendship*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGrantsFriendship(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getIsSubclassListIteratorBegin(); it != src->getIsSubclassListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsSubclass(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIterator<logical::GenericParameter> it = src->getGenericParameterListIteratorBegin(); it != src->getGenericParameterListIteratorEnd(); ++it ) {
    logical::GenericParameter* pNewEdge = dynamic_cast<logical::GenericParameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGenericParameter(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(logical::ClassGenericInstance* dest, const logical::ClassGenericInstance* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setClassKind(src->getClassKind());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setObjectSize(src->getObjectSize());
  // Copying edges
  for ( ListIterator<logical::Class> it = src->getExtendsListIteratorBegin(); it != src->getExtendsListIteratorEnd(); ++it ) {
    logical::Class* pNewEdge = dynamic_cast<logical::Class*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addExtends(pNewEdge);
  }
  for ( ListIterator<logical::Friendship> it = src->getGrantsFriendshipListIteratorBegin(); it != src->getGrantsFriendshipListIteratorEnd(); ++it ) {
    logical::Friendship* pNewEdge = dynamic_cast<logical::Friendship*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGrantsFriendship(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getIsSubclassListIteratorBegin(); it != src->getIsSubclassListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsSubclass(pNewEdge);
  }
  // Copying attributes
  dest->setIsRealInstance(src->getIsRealInstance());
  // Copying edges
  for ( ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = src->getArgumentsListIteratorAssocBegin(); it != src->getArgumentsListIteratorAssocEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge, it.getAssocClass());
  }
}

void AlgorithmDeepCopy::clone(logical::ClassGenericSpec* dest, const logical::ClassGenericSpec* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setClassKind(src->getClassKind());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setObjectSize(src->getObjectSize());
  // Copying edges
  for ( ListIterator<logical::Class> it = src->getExtendsListIteratorBegin(); it != src->getExtendsListIteratorEnd(); ++it ) {
    logical::Class* pNewEdge = dynamic_cast<logical::Class*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addExtends(pNewEdge);
  }
  for ( ListIterator<logical::Friendship> it = src->getGrantsFriendshipListIteratorBegin(); it != src->getGrantsFriendshipListIteratorEnd(); ++it ) {
    logical::Friendship* pNewEdge = dynamic_cast<logical::Friendship*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGrantsFriendship(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getIsSubclassListIteratorBegin(); it != src->getIsSubclassListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsSubclass(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIterator<logical::GenericParameter> it = src->getGenericParameterListIteratorBegin(); it != src->getGenericParameterListIteratorEnd(); ++it ) {
    logical::GenericParameter* pNewEdge = dynamic_cast<logical::GenericParameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGenericParameter(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = src->getArgumentsListIteratorAssocBegin(); it != src->getArgumentsListIteratorAssocEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getSpecialize());
  if (pNewSingleEdge)
    dest->setSpecialize(dynamic_cast<logical::ClassGeneric*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(logical::Friendship* dest, const logical::Friendship* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setGrants(src->getGrants());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getFriend());
  if (pNewSingleEdge)
    dest->setFriend(dynamic_cast<logical::Scope*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(logical::GenericParameter* dest, const logical::GenericParameter* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setGenericParameterKind(src->getGenericParameterKind());
  // Copying edges
  for ( ListIterator<type::Type> it = src->getParameterConstraintListIteratorBegin(); it != src->getParameterConstraintListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameterConstraint(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(logical::Member* dest, const logical::Member* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(logical::Method* dest, const logical::Method* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setDistinctOperands(src->getDistinctOperands());
  dest->setDistinctOperators(src->getDistinctOperators());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setIsVirtual(src->getIsVirtual());
  dest->setMethodKind(src->getMethodKind());
  dest->setNestingLevel(src->getNestingLevel());
  dest->setNestingLevelElseIf(src->getNestingLevelElseIf());
  dest->setNumberOfBranches(src->getNumberOfBranches());
  dest->setNumberOfStatements(src->getNumberOfStatements());
  dest->setTotalOperands(src->getTotalOperands());
  dest->setTotalOperators(src->getTotalOperators());
  // Copying edges
  for ( ListIterator<logical::AttributeAccess> it = src->getAccessesAttributeListIteratorBegin(); it != src->getAccessesAttributeListIteratorEnd(); ++it ) {
    logical::AttributeAccess* pNewEdge = dynamic_cast<logical::AttributeAccess*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessesAttribute(pNewEdge);
  }
  for ( ListIterator<logical::MethodCall> it = src->getCallsListIteratorBegin(); it != src->getCallsListIteratorEnd(); ++it ) {
    logical::MethodCall* pNewEdge = dynamic_cast<logical::MethodCall*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCalls(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getCanThrowListIteratorBegin(); it != src->getCanThrowListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCanThrow(pNewEdge);
  }
  for ( ListIterator<base::ControlFlowBlock> it = src->getControlFlowBlockListIteratorBegin(); it != src->getControlFlowBlockListIteratorEnd(); ++it ) {
    base::ControlFlowBlock* pNewEdge = dynamic_cast<base::ControlFlowBlock*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addControlFlowBlock(pNewEdge);
  }
  for ( ListIterator<logical::Parameter> it = src->getParameterListIteratorBegin(); it != src->getParameterListIteratorEnd(); ++it ) {
    logical::Parameter* pNewEdge = dynamic_cast<logical::Parameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameter(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getInstantiatesListIteratorBegin(); it != src->getInstantiatesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstantiates(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getReturnsListIteratorBegin(); it != src->getReturnsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addReturns(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getThrowsListIteratorBegin(); it != src->getThrowsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addThrows(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(logical::MethodCall* dest, const logical::MethodCall* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setCalls(src->getCalls());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getMethod());
  if (pNewSingleEdge)
    dest->setMethod(dynamic_cast<logical::Method*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(logical::MethodGeneric* dest, const logical::MethodGeneric* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setDistinctOperands(src->getDistinctOperands());
  dest->setDistinctOperators(src->getDistinctOperators());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setIsVirtual(src->getIsVirtual());
  dest->setMethodKind(src->getMethodKind());
  dest->setNestingLevel(src->getNestingLevel());
  dest->setNestingLevelElseIf(src->getNestingLevelElseIf());
  dest->setNumberOfBranches(src->getNumberOfBranches());
  dest->setNumberOfStatements(src->getNumberOfStatements());
  dest->setTotalOperands(src->getTotalOperands());
  dest->setTotalOperators(src->getTotalOperators());
  // Copying edges
  for ( ListIterator<logical::AttributeAccess> it = src->getAccessesAttributeListIteratorBegin(); it != src->getAccessesAttributeListIteratorEnd(); ++it ) {
    logical::AttributeAccess* pNewEdge = dynamic_cast<logical::AttributeAccess*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessesAttribute(pNewEdge);
  }
  for ( ListIterator<logical::MethodCall> it = src->getCallsListIteratorBegin(); it != src->getCallsListIteratorEnd(); ++it ) {
    logical::MethodCall* pNewEdge = dynamic_cast<logical::MethodCall*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCalls(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getCanThrowListIteratorBegin(); it != src->getCanThrowListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCanThrow(pNewEdge);
  }
  for ( ListIterator<base::ControlFlowBlock> it = src->getControlFlowBlockListIteratorBegin(); it != src->getControlFlowBlockListIteratorEnd(); ++it ) {
    base::ControlFlowBlock* pNewEdge = dynamic_cast<base::ControlFlowBlock*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addControlFlowBlock(pNewEdge);
  }
  for ( ListIterator<logical::Parameter> it = src->getParameterListIteratorBegin(); it != src->getParameterListIteratorEnd(); ++it ) {
    logical::Parameter* pNewEdge = dynamic_cast<logical::Parameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameter(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getInstantiatesListIteratorBegin(); it != src->getInstantiatesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstantiates(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getReturnsListIteratorBegin(); it != src->getReturnsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addReturns(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getThrowsListIteratorBegin(); it != src->getThrowsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addThrows(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIterator<logical::GenericParameter> it = src->getGenericParameterListIteratorBegin(); it != src->getGenericParameterListIteratorEnd(); ++it ) {
    logical::GenericParameter* pNewEdge = dynamic_cast<logical::GenericParameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGenericParameter(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(logical::MethodGenericInstance* dest, const logical::MethodGenericInstance* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setDistinctOperands(src->getDistinctOperands());
  dest->setDistinctOperators(src->getDistinctOperators());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setIsVirtual(src->getIsVirtual());
  dest->setMethodKind(src->getMethodKind());
  dest->setNestingLevel(src->getNestingLevel());
  dest->setNestingLevelElseIf(src->getNestingLevelElseIf());
  dest->setNumberOfBranches(src->getNumberOfBranches());
  dest->setNumberOfStatements(src->getNumberOfStatements());
  dest->setTotalOperands(src->getTotalOperands());
  dest->setTotalOperators(src->getTotalOperators());
  // Copying edges
  for ( ListIterator<logical::AttributeAccess> it = src->getAccessesAttributeListIteratorBegin(); it != src->getAccessesAttributeListIteratorEnd(); ++it ) {
    logical::AttributeAccess* pNewEdge = dynamic_cast<logical::AttributeAccess*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessesAttribute(pNewEdge);
  }
  for ( ListIterator<logical::MethodCall> it = src->getCallsListIteratorBegin(); it != src->getCallsListIteratorEnd(); ++it ) {
    logical::MethodCall* pNewEdge = dynamic_cast<logical::MethodCall*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCalls(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getCanThrowListIteratorBegin(); it != src->getCanThrowListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCanThrow(pNewEdge);
  }
  for ( ListIterator<base::ControlFlowBlock> it = src->getControlFlowBlockListIteratorBegin(); it != src->getControlFlowBlockListIteratorEnd(); ++it ) {
    base::ControlFlowBlock* pNewEdge = dynamic_cast<base::ControlFlowBlock*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addControlFlowBlock(pNewEdge);
  }
  for ( ListIterator<logical::Parameter> it = src->getParameterListIteratorBegin(); it != src->getParameterListIteratorEnd(); ++it ) {
    logical::Parameter* pNewEdge = dynamic_cast<logical::Parameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameter(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getInstantiatesListIteratorBegin(); it != src->getInstantiatesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstantiates(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getReturnsListIteratorBegin(); it != src->getReturnsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addReturns(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getThrowsListIteratorBegin(); it != src->getThrowsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addThrows(pNewEdge);
  }
  // Copying attributes
  dest->setIsRealInstance(src->getIsRealInstance());
  // Copying edges
  for ( ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = src->getArgumentsListIteratorAssocBegin(); it != src->getArgumentsListIteratorAssocEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge, it.getAssocClass());
  }
}

void AlgorithmDeepCopy::clone(logical::MethodGenericSpec* dest, const logical::MethodGenericSpec* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setDistinctOperands(src->getDistinctOperands());
  dest->setDistinctOperators(src->getDistinctOperators());
  dest->setIsAbstract(src->getIsAbstract());
  dest->setIsVirtual(src->getIsVirtual());
  dest->setMethodKind(src->getMethodKind());
  dest->setNestingLevel(src->getNestingLevel());
  dest->setNestingLevelElseIf(src->getNestingLevelElseIf());
  dest->setNumberOfBranches(src->getNumberOfBranches());
  dest->setNumberOfStatements(src->getNumberOfStatements());
  dest->setTotalOperands(src->getTotalOperands());
  dest->setTotalOperators(src->getTotalOperators());
  // Copying edges
  for ( ListIterator<logical::AttributeAccess> it = src->getAccessesAttributeListIteratorBegin(); it != src->getAccessesAttributeListIteratorEnd(); ++it ) {
    logical::AttributeAccess* pNewEdge = dynamic_cast<logical::AttributeAccess*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessesAttribute(pNewEdge);
  }
  for ( ListIterator<logical::MethodCall> it = src->getCallsListIteratorBegin(); it != src->getCallsListIteratorEnd(); ++it ) {
    logical::MethodCall* pNewEdge = dynamic_cast<logical::MethodCall*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCalls(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getCanThrowListIteratorBegin(); it != src->getCanThrowListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCanThrow(pNewEdge);
  }
  for ( ListIterator<base::ControlFlowBlock> it = src->getControlFlowBlockListIteratorBegin(); it != src->getControlFlowBlockListIteratorEnd(); ++it ) {
    base::ControlFlowBlock* pNewEdge = dynamic_cast<base::ControlFlowBlock*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addControlFlowBlock(pNewEdge);
  }
  for ( ListIterator<logical::Parameter> it = src->getParameterListIteratorBegin(); it != src->getParameterListIteratorEnd(); ++it ) {
    logical::Parameter* pNewEdge = dynamic_cast<logical::Parameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameter(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getInstantiatesListIteratorBegin(); it != src->getInstantiatesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstantiates(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getReturnsListIteratorBegin(); it != src->getReturnsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addReturns(pNewEdge);
  }
  for ( ListIterator<type::Type> it = src->getThrowsListIteratorBegin(); it != src->getThrowsListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addThrows(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIterator<logical::GenericParameter> it = src->getGenericParameterListIteratorBegin(); it != src->getGenericParameterListIteratorEnd(); ++it ) {
    logical::GenericParameter* pNewEdge = dynamic_cast<logical::GenericParameter*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addGenericParameter(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = src->getArgumentsListIteratorAssocBegin(); it != src->getArgumentsListIteratorAssocEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getSpecialize());
  if (pNewSingleEdge)
    dest->setSpecialize(dynamic_cast<logical::MethodGeneric*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(logical::Package* dest, const logical::Package* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
  // Copying attributes
  dest->setPackageKind(src->getPackageKind());
  // Copying edges
}

void AlgorithmDeepCopy::clone(logical::Parameter* dest, const logical::Parameter* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setParamKind(src->getParamKind());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<type::Type*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(logical::Scope* dest, const logical::Scope* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  dest->setAccessibility(src->getAccessibility());
  dest->setCommentLines(src->getCommentLines());
  dest->setDemangledName(src->getDemangledName());
  dest->setIsCompilerGenerated(src->getIsCompilerGenerated());
  dest->setIsStatic(src->getIsStatic());
  dest->setLanguage(src->getLanguage());
  dest->setMangledName(src->getMangledName());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAggregated());
  if (pNewSingleEdge)
    dest->setAggregated(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Component> it = src->getBelongsToListIteratorBegin(); it != src->getBelongsToListIteratorEnd(); ++it ) {
    base::Component* pNewEdge = dynamic_cast<base::Component*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addBelongsTo(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getCompilationUnitListIteratorBegin(); it != src->getCompilationUnitListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCompilationUnit(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclares());
  if (pNewSingleEdge)
    dest->setDeclares(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getInstanceListIteratorBegin(); it != src->getInstanceListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInstance(pNewEdge);
  }
  for ( ListIteratorAssocSourcePosition<physical::File> it = src->getIsContainedInListIteratorAssocBegin(); it != src->getIsContainedInListIteratorAssocEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIsContainedIn(pNewEdge, it.getAssocClass());
  }
  pNewSingleEdge = getMappedNode(src->getLanguageVariant());
  if (pNewSingleEdge)
    dest->setLanguageVariant(dynamic_cast<logical::Member*>(pNewSingleEdge));
  for ( ListIterator<type::Type> it = src->getUsesListIteratorBegin(); it != src->getUsesListIteratorEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUses(pNewEdge);
  }
  for ( ListIterator<logical::Member> it = src->getVariantListIteratorBegin(); it != src->getVariantListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariant(pNewEdge);
  }
  // Copying attributes
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setTLLOC(src->getTLLOC());
  dest->setTLOC(src->getTLOC());
  dest->setIsAnonymous(src->getIsAnonymous());
  // Copying edges
  for ( ListIterator<logical::Member> it = src->getMemberListIteratorBegin(); it != src->getMemberListIteratorEnd(); ++it ) {
    logical::Member* pNewEdge = dynamic_cast<logical::Member*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMember(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(physical::FSEntry* dest, const physical::FSEntry* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(physical::File* dest, const physical::File* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setCLOC(src->getCLOC());
  dest->setLLOC(src->getLLOC());
  dest->setLOC(src->getLOC());
  dest->setNumberOfBranches(src->getNumberOfBranches());
  // Copying edges
  for ( ListIterator<base::Comment> it = src->getCommentListIteratorBegin(); it != src->getCommentListIteratorEnd(); ++it ) {
    base::Comment* pNewEdge = dynamic_cast<base::Comment*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addComment(pNewEdge);
  }
  for ( ListIterator<physical::File> it = src->getIncludesListIteratorBegin(); it != src->getIncludesListIteratorEnd(); ++it ) {
    physical::File* pNewEdge = dynamic_cast<physical::File*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIncludes(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(physical::FileSystem* dest, const physical::FileSystem* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  // Copying edges
  for ( ListIterator<physical::FSEntry> it = src->getFSEntryListIteratorBegin(); it != src->getFSEntryListIteratorEnd(); ++it ) {
    physical::FSEntry* pNewEdge = dynamic_cast<physical::FSEntry*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addFSEntry(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(physical::Folder* dest, const physical::Folder* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setName(src->getName());
  // Copying edges
  for ( ListIteratorAssocString<base::Named> it = src->getDependsOnListIteratorAssocBegin(); it != src->getDependsOnListIteratorAssocEnd(); ++it ) {
    base::Named* pNewEdge = dynamic_cast<base::Named*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addDependsOn(pNewEdge, it.getAssocClass());
  }
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<physical::FSEntry> it = src->getContainsListIteratorBegin(); it != src->getContainsListIteratorEnd(); ++it ) {
    physical::FSEntry* pNewEdge = dynamic_cast<physical::FSEntry*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addContains(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(type::SimpleType* dest, const type::SimpleType* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setSimpleTypeKind(src->getSimpleTypeKind());
  // Copying edges
}

void AlgorithmDeepCopy::clone(type::Type* dest, const type::Type* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setRefers(src->getRefers());
  // Copying edges
  for ( ListIterator<type::TypeFormer> it = src->getTypeFormerListIteratorBegin(); it != src->getTypeFormerListIteratorEnd(); ++it ) {
    type::TypeFormer* pNewEdge = dynamic_cast<type::TypeFormer*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addTypeFormer(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(type::TypeFormer* dest, const type::TypeFormer* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(type::TypeFormerArray* dest, const type::TypeFormerArray* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(type::TypeFormerMethod* dest, const type::TypeFormerMethod* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIteratorAssocParameterKind<type::Type> it = src->getParameterTypeListIteratorAssocBegin(); it != src->getParameterTypeListIteratorAssocEnd(); ++it ) {
    type::Type* pNewEdge = dynamic_cast<type::Type*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameterType(pNewEdge, it.getAssocClass());
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getReturnType());
  if (pNewSingleEdge)
    dest->setReturnType(dynamic_cast<type::Type*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(type::TypeFormerNonType* dest, const type::TypeFormerNonType* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(type::TypeFormerPointer* dest, const type::TypeFormerPointer* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPointerKind(src->getPointerKind());
  // Copying edges
}

void AlgorithmDeepCopy::clone(type::TypeFormerType* dest, const type::TypeFormerType* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getRefersTo());
  if (pNewSingleEdge)
    dest->setRefersTo(dynamic_cast<base::Base*>(pNewSingleEdge));
}


}}}
