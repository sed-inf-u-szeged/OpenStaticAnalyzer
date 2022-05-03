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

#include "../inc/clangHelpers.h"

#include <clang/AST/RecursiveASTVisitor.h>
#include <iostream>

using namespace clang;

bool isDefinition(const clang::TagDecl * decl)
{
  return decl->isCompleteDefinition();
}

bool isDefinition(const clang::FunctionDecl * decl)
{
  return decl->getDefinition() == decl;
}

bool isDefinition(const clang::ObjCProtocolDecl * decl)
{
  return decl->isThisDeclarationADefinition();
}

bool isDefinition(const clang::ObjCCategoryDecl * decl)
{
  return true;
}

bool isDefinition(const clang::ObjCInterfaceDecl * decl)
{
  return decl->isThisDeclarationADefinition();
}

bool isDefinition(const clang::ValueDecl * decl)
{
  return false;
}

bool isDefinition(const clang::VarDecl * decl)
{
  if (decl->isStaticDataMember())
    return decl->hasInit() || decl->isThisDeclarationADefinition() != clang::VarDecl::DeclarationOnly;
  else
    return decl->isThisDeclarationADefinition() != clang::VarDecl::DeclarationOnly;
}

bool isDefinition(const clang::FieldDecl * decl)
{
  return true;
}

bool isDefinition(const clang::ObjCMethodDecl * decl)
{
  return decl->isThisDeclarationADefinition();
}

bool isDefinition(const clang::NamespaceDecl * decl)
{
  return true;
}

bool isDefinition(const clang::Decl * decl)
{
  if(const TagDecl * td = dyn_cast_or_null<TagDecl>(decl))
    return isDefinition(td);
  else if (const FunctionDecl * fd = dyn_cast_or_null<FunctionDecl>(decl))
    return isDefinition(fd);
  else if (const VarDecl * vd = dyn_cast_or_null<VarDecl>(decl))
    return isDefinition(vd);
  else
  {
    //std::cout << "ERROR, undhandled isDefinition kind" << std::endl;
    return false;
  }
}

const Decl* getLocalDefinition(const clang::Decl * decl)
{
  if(const TagDecl * td = dyn_cast_or_null<TagDecl>(decl))
    return td->getDefinition();
  else if (const FunctionDecl * fd = dyn_cast_or_null<FunctionDecl>(decl))
    return fd->getDefinition();
  else if (const VarDecl * vd = dyn_cast_or_null<VarDecl>(decl))
    return vd->getDefinition();
  else
  {
    //std::cout << "ERROR, undhandled getDefinition kind" << std::endl;
    return nullptr;
  }
}

