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

#include "LdWrapper/LdWrapper.h"
#include <AbstractWrapperLib/inc/messages.h>
#include <AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h>
#include <AbstractWrapperLib/inc/paramsup/GccParamsup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>

#include <string>
#include <list>

using namespace std;
using namespace common;

#define LD_WRAPPER    "LdWrapper"

namespace ColumbusWrappers {

  LdWrapper::LdWrapper(string configfile) : AbstractWrapper(configfile), AbstractLinker(configfile), linkWarnings(), linkArgs() {
    mode = wrapper_gcc;
  }

  bool LdWrapper::process(int argc, char** argv) {

    list<ColumbusWrappers::Argument> generated_files;
    list<string> temp_args;
    setParams(argc, argv, temp_args, AbstractLinker::linker_paramtoskip);

    if (instrument_enable) {

      string cmd;
      list<string>::const_iterator arg_it;
      for (arg_it = temp_args.begin(); arg_it != temp_args.end(); arg_it++) {
        string actArg = *arg_it;
        replaceQuoteForQuoteWithBackslash(actArg);
        cmd += " " CL_PAR_PLUS + actArg + CL_PAR_PLUS;
      }
      cmd += " -lpthread";
      cmd = wrappedExe + cmd;
      writeInfoMsg(LD_WRAPPER, CMSG_ANALYZER_WRAPPER_COMMAND, cmd.c_str());
      bool linker_run = systemCall(cmd);
      return linker_run;

    } else {

      if (GccWrapperSup::linkerArguments(temp_args, linkWarnings, linkArgs)) {

        for (list<string>::iterator it_w = linkWarnings.can_warning.begin(); it_w != linkWarnings.can_warning.end(); it_w++) {
          writeWarningMsg(LD_WRAPPER, CMSG_WRAPPER_TOOL_WARNINGS, it_w->c_str());
        }

        for (list<string>::iterator it_u = linkWarnings.unrec_args.begin(); it_u != linkWarnings.unrec_args.end(); it_u++) {
          writeWarningMsg(LD_WRAPPER, CMSG_WRAPPER_TOOL_UNRECOGNIZE_ARGUMENTS, it_u->c_str());
        }

        bool linker_run = executeLinker(linkArgs, generated_files);

        return (linker_run);
      } else {

        return false;

      }
    }
  }
}