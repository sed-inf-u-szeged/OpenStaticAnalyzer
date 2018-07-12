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

#include <common/inc/WriteMessage.h>
#include <java/inc/java.h>
#include "../inc/VisitorLinker.h"

using namespace std;
using namespace common;
using namespace columbus::java::asg;


namespace columbus { namespace java { namespace linker {

VisitorLinker::VisitorLinker(UniqueMap& strMap, StrNodeIdMap& pathMap, Factory& fact, Factory& tmpFact)
  : LinkerBase(strMap, pathMap, fact, tmpFact)
{
}

VisitorLinker::~VisitorLinker() {
}


void VisitorLinker::collectEdges(expr::Annotation& newNode, const expr::Annotation& node, vector<NodeId>& v, bool callVirtualBase) {
  checkTypeExpression(newNode.getAnnotationName(), node.getAnnotationName());

  LinkerBase::collectEdges(newNode, node, v, callVirtualBase);
}

void VisitorLinker::collectEdges(struc::MethodDeclaration& newNode, const struc::MethodDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  checkTypeExpression(newNode.getReturnType(), node.getReturnType());

  if (newNode.getReturnType() && node.getReturnType()) {
    tmpFact.setFilteredThisNodeOnly(node.getReturnType()->getId());
  }

  if (callVirtualBase)
    LinkerBase::collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    LinkerBase::collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    LinkerBase::collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  LinkerBase::collectEdges(static_cast<struc::NamedDeclaration&>(newNode), static_cast<const struc::NamedDeclaration&>(node), v, false);

  type::Type* newType = newNode.getMethodType();
  type::Type* otherType = node.getMethodType();
  bool methodTypeFixed = false;
  if (newType && otherType) {
    string s1 = Common::getUniqueNameForType(*newType);
    string s2 = Common::getUniqueNameForType(*otherType);
    if (s2.length() < s1.length()) {
      v.push_back(0);
      methodTypeFixed = true;
    }
  }
  if (!methodTypeFixed) {
    v.push_back(node.getMethodType() ? node.getMethodType()->getId() : 0);
  }

  for (ListIterator<struc::MethodDeclaration> it = node.getOverridesListIteratorBegin(); it != node.getOverridesListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);
}

void VisitorLinker::collectEdges(struc::NormalMethod& newNode, const struc::NormalMethod& node, vector<NodeId>& v, bool callVirtualBase) {
  if (!newNode.getThrownExceptionsIsEmpty() && !node.getThrownExceptionsIsEmpty()) {
    checkTypeExpressionList(newNode.getThrownExceptionsListIteratorBegin(), newNode.getThrownExceptionsListIteratorEnd(), node.getThrownExceptionsListIteratorBegin(), node.getThrownExceptionsListIteratorEnd());
  }

  LinkerBase::collectEdges(newNode, node, v, callVirtualBase);
}

void VisitorLinker::collectEdges(struc::TypeDeclaration& newNode, const struc::TypeDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  checkTypeExpression(newNode.getSuperClass(), node.getSuperClass());

  if (!newNode.getSuperInterfacesIsEmpty() && !node.getSuperInterfacesIsEmpty()) {
    checkTypeExpressionList(newNode.getSuperInterfacesListIteratorBegin(), newNode.getSuperInterfacesListIteratorEnd(), node.getSuperInterfacesListIteratorBegin(), node.getSuperInterfacesListIteratorEnd());
  }

  LinkerBase::collectEdges(newNode, node, v, callVirtualBase);
}

void VisitorLinker::collectEdges(struc::TypeParameter& newNode, const struc::TypeParameter& node, vector<NodeId>& v, bool callVirtualBase) {
  if (!newNode.getBoundsIsEmpty() && !node.getBoundsIsEmpty()) {
    checkTypeExpressionList(newNode.getBoundsListIteratorBegin(), newNode.getBoundsListIteratorEnd(), node.getBoundsListIteratorBegin(), node.getBoundsListIteratorEnd());
  }

  LinkerBase::collectEdges(newNode, node, v, callVirtualBase);
}

void VisitorLinker::collectEdges(struc::VariableDeclaration& newNode, const struc::VariableDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  checkTypeExpression(newNode.getType(), node.getType());

  LinkerBase::collectEdges(newNode, node, v, callVirtualBase);
}

void VisitorLinker::collectEdges(struc::AnnotatedElement& newNode, const struc::AnnotatedElement& node, vector<NodeId>& v, bool callVirtualBase) {
  if (!newNode.getAnnotationsIsEmpty() && !node.getAnnotationsIsEmpty()) {
    ListIterator<expr::Annotation> newIt = newNode.getAnnotationsListIteratorBegin();
    ListIterator<expr::Annotation> otherIt = node.getAnnotationsListIteratorBegin();
    if ((newIt->getPosition().getPathKey() == 0 && otherIt->getPosition().getPathKey() != 0)
      || (newIt->getPosition().getPathKey() == 0 && newNode.getAnnotationsSize() < node.getAnnotationsSize())
    ) {
      std::list<NodeId> toDelete;
      for (ListIterator<expr::Annotation> newItEnd = newNode.getAnnotationsListIteratorEnd(); newIt != newItEnd; ++newIt) {
        toDelete.push_back(newIt->getId());
      }
      for (std::list<NodeId>::const_iterator it = toDelete.begin(); it != toDelete.end(); ++it) {
        fact.destroyNode(*it);
      }
    } else {
      for (ListIterator<expr::Annotation> otherItEnd = node.getAnnotationsListIteratorEnd(); otherIt != otherItEnd; ++otherIt) {
        tmpFact.setFilteredThisNodeOnly(otherIt->getId());
      }
    }
  }

  LinkerBase::collectEdges(newNode, node, v, callVirtualBase);
}

NodeId VisitorLinker::getNewNode(const columbus::java::asg::base::Base& node, bool& update) {
  NodeId ret = LinkerBase::getNewNode(node, update);

  if (ret && !update) {
    if (Common::getIsPositioned(node) && dynamic_cast<const base::Positioned&>(node).getIsCompilerGenerated()) {
      base::Base& b = fact.getRef(ret);
      if (Common::getIsPositioned(b) && !dynamic_cast<base::Positioned&>(b).getIsCompilerGenerated()) {
        update = true; // force update of attributes, e.g. it's a compiler generated constructor
      }
    }
  }

  return ret;
}

void VisitorLinker::checkTypeExpression(expr::TypeExpression* newTypeExpr, expr::TypeExpression* otherTypeExpr) {
  if (newTypeExpr && otherTypeExpr) {
    if (newTypeExpr->getNodeKind() == ndkExternalTypeExpression) {
      if (otherTypeExpr->getNodeKind() != ndkExternalTypeExpression) {
        fact.destroyNode(newTypeExpr->getId());
      } else {
        if (otherTypeExpr->getIsCompilerGenerated()) {
          newTypeExpr->setIsCompilerGenerated(true);
        }
        type::Type* newType = newTypeExpr->getType();
        type::Type* otherType = otherTypeExpr->getType();
        if (newType && newType->getNodeKind() != ndkErrorType && otherType && otherType->getNodeKind() != ndkErrorType) {
          string s1 = Common::getUniqueNameForType(*newType);
          string s2 = Common::getUniqueNameForType(*otherType);
          if (s2.length() > s1.length()) {
            fact.destroyNode(newTypeExpr->getId());
          }
        }
      }
    }
  }
}

void VisitorLinker::checkTypeExpressionList(ListIterator<expr::TypeExpression> it, ListIterator<expr::TypeExpression> itEnd, ListIterator<expr::TypeExpression> otherIt, ListIterator<expr::TypeExpression> otherItEnd) {
  if (it != itEnd && otherIt != otherItEnd) {
    if (it->getNodeKind() == ndkExternalTypeExpression && otherIt->getNodeKind() != ndkExternalTypeExpression) {
      std::list<NodeId> toDelete;
      while (it != itEnd) {
        toDelete.push_back(it->getId());
        ++it;
      }
      for (std::list<NodeId>::const_iterator it = toDelete.begin(); it != toDelete.end(); ++it) {
        fact.destroyNode(*it);
      }
    }
  }
}


}}}

