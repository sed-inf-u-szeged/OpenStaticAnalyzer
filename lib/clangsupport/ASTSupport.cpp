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

#include "ASTSupport.h"
#include <clang/AST/ParentMapContext.h>

namespace columbus{
  using namespace std;
  
  //node can be one of Decl, Stmt, Type, TypeLoc, NestedNameSpecifier or NestedNameSpecifierLoc. TODO: others
  clang::DynTypedNodeList getParents(clang::ASTContext* context, clang::DynTypedNode node){
      if(const clang::Decl* d = node.get<clang::Decl>())
      {
        return context->getParents(*d);
        
      }else if(const clang::Stmt* s = node.get<clang::Stmt>())
      {
        return context->getParents(*s);
        
      }else if(const clang::Type* t = node.get<clang::Type>())
      {
        return context->getParents(*t);
        
      }
      
      return clang::DynTypedNodeList(clang::DynTypedNode::create(*(context->getTranslationUnitDecl())));
  }
  
  
}