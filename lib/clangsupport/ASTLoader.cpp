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

#include "ASTLoader.h"

#include <clang/Frontend/ASTUnit.h>
#include <clang/Frontend/PCHContainerOperations.h>
#include <clang/Frontend/CompilerInstance.h>

using namespace std;

namespace columbus
{

  ASTWithNodeIDMaps loadAST(const string& astFilename, const bool cacheLast)
  {
    static pair<ASTWithNodeIDMaps, string> last = { { nullptr, nullptr }, "" };
    ASTWithNodeIDMaps result = { nullptr, nullptr };

    if (astFilename == last.second)
      return last.first;

    clang::FileSystemOptions FileSystemOpts;
    shared_ptr<clang::PCHContainerOperations> PCHContainerOps = make_shared<clang::PCHContainerOperations>();
    // TODO Check `new clang::DiagnosticOptions()` for memory leak
    clang::IntrusiveRefCntPtr<clang::DiagnosticsEngine> Diags = clang::CompilerInstance::createDiagnostics(new clang::DiagnosticOptions());

    result.astUnit = clang::ASTUnit::LoadFromASTFile(
        astFilename, PCHContainerOps->getRawReader(), clang::ASTUnit::LoadEverything,
        Diags, FileSystemOpts, false, false, clang::CaptureDiagsKind::None, /* AllowPCHWithCompilerErrors = */ true, false);

    result.nodeIdMaps = generateNodeIDMaps(result.astUnit->getASTContext());

    if (cacheLast)
    {
        last.first = result;
        last.second = astFilename;
    }

    return result;
  }

}

