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

#include "ASTIDMapGenerator.h"
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;

namespace {

  class ASTNodeVisitor : public clang::RecursiveASTVisitor<ASTNodeVisitor>
  {
  public:
      ASTNodeVisitor(columbus::NodeIDMaps& nodeIdMaps)
        : nodeIdMaps(nodeIdMaps)
      {}
      
      bool VisitStmt(clang::Stmt *s)
      {
        nodeIdMaps.node2id[s] = idCnt;
        nodeIdMaps.id2node[idCnt] = std::make_pair(s, columbus::AstNodeType::STMT);
        idCnt++;
        return true;
      }
      
      bool VisitDecl(clang::Decl *d)
      {
        nodeIdMaps.node2id[d] = idCnt;
        nodeIdMaps.id2node[idCnt] = std::make_pair(d, columbus::AstNodeType::DECL);
        idCnt++;
        return true;
      }

  private:

      columbus::NodeIDMaps& nodeIdMaps;
      unsigned idCnt = 1;
  };
  
} // anonymous namespace

std::shared_ptr<columbus::NodeIDMaps> columbus::generateNodeIDMaps(const ASTContext& context)
{
  auto nodeIdMaps = std::make_shared<NodeIDMaps>();
  if (context.getTranslationUnitDecl() != nullptr)
  {
    ASTNodeVisitor(*nodeIdMaps).TraverseDecl(context.getTranslationUnitDecl());
  }
  return nodeIdMaps;
}
