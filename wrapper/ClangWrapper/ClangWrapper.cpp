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

#include "ClangWrapper.h"
#include <AbstractWrapperLib/inc/messages.h>
#include <AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h>
#include <AbstractWrapperLib/inc/paramsup/ClangParamsup.h>
#include <common/inc/WriteMessage.h>

#include <string>
#include <list>

using namespace std;
using namespace common;

#define CLANG_WRAPPER  "ClangWrapper"

namespace ColumbusWrappers {

  ClangWrapper::ClangWrapper(string configfile) : AbstractWrapper(configfile), AbstractCompiler(configfile), AbstractLinker(configfile), compWarnings(), compArgs(), linkArgs(), prepArgs() {
    mode = wrapper_clang;
  }

  bool ClangWrapper::process(int argc, char** argv) {

    list<ColumbusWrappers::Argument> generated_files;
    list<string> temp_args;
    setParams(argc, argv, temp_args, AbstractCompiler::comp_paramtoskip);
    readCompilerVersion();

    if (ClangWrapperSup::compilerArguments(temp_args, compWarnings, prepArgs, compArgs, linkArgs)) {

      for (list<string>::iterator it_w = compWarnings.can_warning.begin(); it_w != compWarnings.can_warning.end(); it_w++) {
        writeWarningMsg(CLANG_WRAPPER, CMSG_WRAPPER_TOOL_WARNINGS, it_w->c_str());
      }

      for (list<string>::iterator it_u = compWarnings.unrec_args.begin(); it_u != compWarnings.unrec_args.end(); it_u++) {
        writeWarningMsg(CLANG_WRAPPER, CMSG_WRAPPER_TOOL_UNRECOGNIZE_ARGUMENTS, it_u->c_str());
      }


      bool compiler_run = true;
      bool linker_run = true;
      bool prep_run = true;
      compiler_run = executeCompiler(compArgs, prepArgs, generated_files);
      if (linkArgs.linking) {
        linker_run = executeLinker(linkArgs, generated_files);
      }
      return (compiler_run && linker_run && prep_run);

    } else {

      return false;

    }
  }
}
