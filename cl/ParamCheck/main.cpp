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

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <common/inc/StringSup.h>
#include "messages.h"
using namespace std;


void dumpParameters(const char *params) {
  vector<string> args;
  common::splitArgs(params, args);
  bool include = false;
  for (vector<string>::const_iterator it = args.begin(); it != args.end(); ++it) {
    if (it->find("-D") == 0) {
      size_t eqpos = it->find_first_of('=');
      string macro = it->substr(2, eqpos - 2);
      string value;
      if (eqpos != string::npos)
        value = it->substr(eqpos + 1);
        
      printf( CMSG_DEFINE, macro.c_str(), value.c_str());
    } else if (*it == "-I") {
      include = true;

    } else if (include) {
      include = false;
      printf( CMSG_STRING, it->c_str());
    }
      
  }
}

int main(int argc, char* argv[]) {
  
  char *params;

  if ((params = getenv("MSC_CMD_FLAGS")) != NULL) {
    dumpParameters(params);
  }

  if ((params = getenv("MSC_IDE_FLAGS")) != NULL) {
    dumpParameters(params);
  }

  return 0;
}
