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

#ifndef _CAN2LIM_HELPERS_H
#define _CAN2LIM_HELPERS_H

#include <clang/Tooling/Tooling.h>

bool isDefinition(const clang::TagDecl *decl);
bool isDefinition(const clang::FunctionDecl *decl);
bool isDefinition(const clang::ObjCProtocolDecl *decl);
bool isDefinition(const clang::ObjCCategoryDecl *decl);
bool isDefinition(const clang::ObjCInterfaceDecl *decl);
bool isDefinition(const clang::ValueDecl *decl);
bool isDefinition(const clang::VarDecl *decl);
bool isDefinition(const clang::FieldDecl *decl);
bool isDefinition(const clang::ObjCMethodDecl *decl);
bool isDefinition(const clang::NamespaceDecl *decl);

// Deduce the type of decl with dynamic casts and return the answer (only works for LIM types that have declaration-definition pairs)
bool isDefinition(const clang::Decl *decl);

// Gets the definition for the declaration if it's present in the TU
const clang::Decl * getLocalDefinition(const clang::Decl * decl);

/// Sometimes we would like to add an id to a container in the LIM but we don't want to add duplicates.
/// This functionality is not implemented in the LIM API so here is a helper to check for it.
/// Note : It's O(n)
template<class NODEPTR, class IT>
bool contains(IT begin, IT end, NODEPTR node)
{
  for (auto it = begin; it != end; ++it)
  {
    if (it->getId() == node->getId())
      return true;
  }
  return false;
}
#endif