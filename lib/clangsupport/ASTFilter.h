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

#ifndef _ASTFILTER_H_
#define _ASTFILTER_H_

#include <common/inc/DirectoryFilter.h>
#include <common/inc/Stat.h>
#include <clang/Basic/SourceLocation.h>

#include <map>
#include <string>

namespace clang
{
  class ASTContext;
}

namespace columbus
{

enum class FilterState
{
    Filtered,
    NotFiltered
};

class ASTFilter
{
  public:
    ASTFilter(const std::string& filterFile, const clang::ASTContext& astContext, bool visitLambdaClosureClass = false, bool visitTemplateInstantiations = false, bool visitImplicitCode = false);
    ASTFilter(const std::string& filterFile, const clang::ASTContext& astContext, common::Cache<clang::FileID, std::string>* locationCache, bool visitLambdaClosureClass = false, bool visitTemplateInstantiations = false, bool visitImplicitCode = false);
    FilterState getFilterState(void* astNode) const;

    const DirectoryFilter& getDirectoryFilter() const { return directoryFilter; }
  private:
    bool hasFilterFile;

    DirectoryFilter directoryFilter;
    std::map<void*, FilterState> filter;
};

}


#endif
