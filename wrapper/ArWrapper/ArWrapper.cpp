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

#include "ArWrapper/ArWrapper.h"
#include <AbstractWrapperLib/inc/messages.h>
#include <AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h>
#include <AbstractWrapperLib/inc/paramsup/ArParamsup.h>
#include <common/inc/WriteMessage.h>

#include <string>
#include <list>

using namespace std;
using namespace common;

#define AR_WRAPPER  "ArWrapper"

namespace ColumbusWrappers {

  ArWrapper::ArWrapper(string configfile) : AbstractArchive(configfile), archiveWarnings(), archiveArgs() {
    mode = wrapper_ar;
  }

  bool ArWrapper::process(int argc, char** argv) {

    list<string> temp_args;
    setParams(argc, argv, temp_args, AbstractArchive::archive_paramtoskip);

    if (ArWrapperSup::archiveArguments(temp_args, archiveArgs, archiveWarnings)) {

      for (list<string>::iterator it_w = archiveWarnings.can_warning.begin(); it_w != archiveWarnings.can_warning.end(); it_w++) {
        writeWarningMsg(AR_WRAPPER, CMSG_WRAPPER_TOOL_WARNINGS, it_w->c_str());
      }

      for (list<string>::iterator it_u = archiveWarnings.unrec_args.begin(); it_u != archiveWarnings.unrec_args.end(); it_u++) {
        writeWarningMsg(AR_WRAPPER, CMSG_WRAPPER_TOOL_UNRECOGNIZE_ARGUMENTS, it_u->c_str());
      }

      if (archiveArgs.needToWrap)
        return executeArchive(archiveArgs);
      else
        return true;

    } else {

      return false;

    }
  }
}
