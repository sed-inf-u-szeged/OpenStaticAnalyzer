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

#include "ASTFilter.h"
#include <clang/Metrics/ASTPrePostVisitor.h>
#include "messages.h"
#include <clang/Basic/FileEntry.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <common/inc/DirectoryFilter.h>
#include <common/inc/WriteMessage.h>
#include <set>
#include <stack>
#include <iostream>
#include <common/inc/FileSup.h>
#include <common/inc/Stat.h>

using namespace std;
using namespace clang;


namespace {

using columbus::FilterState;
using clang::ASTPrePostVisitor;

class FilterVisitor : public ASTPrePostVisitor
{
  public:

    FilterVisitor(const ASTContext& context, const DirectoryFilter& directoryFilter, map<void*, FilterState>& nodeFilter, common::Cache<FileID, string> *locationCache, const bool visitLambdaClosureClass, const bool visitTemplateInstantiations, const bool visitImplicitCode, const FilterState initialFilterState = FilterState::NotFiltered)
      : context (context)
      , directoryFilter (directoryFilter)
      , nodeFilter (nodeFilter)
      , locationCache (locationCache)
      , visitLambdaClosureClass (visitLambdaClosureClass)
      , visitTemplateInstantiations (visitTemplateInstantiations)
      , visitImplicitCode (visitImplicitCode)
    {
      filterStateStack.push(initialFilterState);
    }

    bool visitStmt(clang::Stmt *s) override
    {
      doFiltering<Stmt>(s, nullptr);
      if (visitLambdaClosureClass)
      {
        LambdaExpr* lambdaExpr = dyn_cast<LambdaExpr>(s);
        if (lambdaExpr != nullptr && lambdaExpr->getLambdaClass())
        {
          FilterVisitor closureClassVisitor(context, directoryFilter, nodeFilter, locationCache, visitLambdaClosureClass, visitTemplateInstantiations, visitImplicitCode, filterStateStack.top());
          clang::ASTPrePostTraverser(context, lambdaExpr->getLambdaClass(), closureClassVisitor, visitTemplateInstantiations, visitImplicitCode).run();
        }
      }
      return true;
    }

    void visitEndStmt(Stmt *s) override
    {
      filterStateStack.pop();
      return;
    }

    bool visitDecl(Decl *d) override
    {
      if (TranslationUnitDecl::classof(d))
      {
        nodeFilter[d] = FilterState::NotFiltered;
        filterStateStack.push(FilterState::NotFiltered);
      }
      else
        doFiltering<Decl>(d, d->getDeclContext() != nullptr ? cast<Decl>(d->getDeclContext()) : nullptr);
      return true;
    }

    void visitEndDecl(Decl *d) override
    {
      filterStateStack.pop();
      return;
    }

  private:

    template<typename T>
    string getLineInfo(T* node)
    {
      FullSourceLoc fullLocation = context.getFullLoc(node->getBeginLoc());

      if (fullLocation.isValid())
      {
        fullLocation = fullLocation.getFileLoc();
        if (fullLocation.getFileEntry())
        {
          if (locationCache != nullptr)
          {
              const auto result = locationCache->getValue(fullLocation.getFileID());
              if (result.found)
                return result.value;
              else
              {
                string canonicalizedName = common::pathCanonicalize(fullLocation.getFileEntry()->getName().str());
                locationCache->setValue(fullLocation.getFileID(), canonicalizedName);
                return canonicalizedName;
              }
          }
          return common::pathCanonicalize(fullLocation.getFileEntry()->getName().str());
        }
        else
        {
          return string();
        }
      }

      return string();
    }

    template<typename T>
    void doFiltering(T* node, T* parent)
    {
      // check the semantic parent
      if (parent != nullptr)
      {
        auto& semanticParentFilterState = nodeFilter[parent];
        if (semanticParentFilterState == FilterState::Filtered)
        {
          filterStateStack.push(FilterState::Filtered);
          return;
        }

      }

      // semantic parent does not exists or it is not filtered
      // we should check te ast parent
      auto astFilterState = filterStateStack.top();
      if (astFilterState == FilterState::Filtered)
      {
        filterStateStack.push(FilterState::Filtered);
        return;
      }

      // neither the semantic parent nor the ast parent is filtered
      auto& filterState = nodeFilter[node];
      if (!directoryFilter.isFilteredOut(getLineInfo(node)))
          filterState = FilterState::NotFiltered;

      filterStateStack.push(filterState);
    }

  private:

    const ASTContext& context;
    const DirectoryFilter& directoryFilter;
    map<void*, FilterState>& nodeFilter;
    stack<FilterState> filterStateStack;
    common::Cache<FileID, string> *locationCache;

    const bool visitLambdaClosureClass;
    const bool visitTemplateInstantiations;
    const bool visitImplicitCode;

};

} // anonymous

namespace columbus
{

ASTFilter::ASTFilter(const string& filterFile, const ASTContext& astContext, const bool visitLambdaClosureClass, const bool visitTemplateInstantiations, const bool visitImplicitCode)
  : ASTFilter(filterFile, astContext, nullptr, visitLambdaClosureClass, visitTemplateInstantiations, visitImplicitCode)
{

}


ASTFilter::ASTFilter(const string& filterFile, const ASTContext& astContext, common::Cache<FileID, string> *locationCache, const bool visitLambdaClosureClass, const bool visitTemplateInstantiations, const bool visitImplicitCode)
{
  if (directoryFilter.openFilterFile(filterFile))
  {
    hasFilterFile = true;
    FilterVisitor visitor(astContext, directoryFilter, filter, locationCache, visitLambdaClosureClass, visitTemplateInstantiations, visitImplicitCode);
    ASTPrePostTraverser(astContext, visitor, nullptr, visitTemplateInstantiations, visitImplicitCode).run();
  }
  else
  {
    hasFilterFile = false;
    common::WriteMsg::write(CMSG_FAILED_TO_LOAD_FILTER_FILE, filterFile.c_str());
  }
}

FilterState ASTFilter::getFilterState(void* astNode) const
{
  if (!hasFilterFile)
    return FilterState::NotFiltered;

  auto filterIterator = filter.find(astNode);
  if (filterIterator != filter.end())
    return filterIterator->second;

  return FilterState::Filtered;
}

} // columbus
