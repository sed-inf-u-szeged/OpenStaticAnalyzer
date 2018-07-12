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

#include "../inc/PylintRunner.h"
#include "../inc/messages.h"

#include <common/inc/WriteMessage.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <python/inc/PythonCollector.h>

#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace common;
using namespace columbus;


PylintRunner::PylintRunner() {
}

PylintRunner::~PylintRunner() {
}

void PylintRunner::run(const string& projectBaseDir, const string& pythonBinary, const string& pylintDir, const string& pylintrc, const string& outputFile, const std::list<std::string>& pylintOptions) {
  list<string> packagePaths;

  columbus::python::collectPythonPackages(projectBaseDir, "", packagePaths);

  if (packagePaths.empty()) {
    WriteMsg::write(CMSG_PYLINT_NO_INPUT);
    ofstream ofs(outputFile.c_str(), ofstream::trunc);
    return;
  }

  string pylintScript = (boost::filesystem::path(pylintDir) / "bin" / "pylint").string();

  vector<string> sv;
  sv.push_back("-B"); // don't create .py[co] files
  sv.push_back(pylintScript);
  sv.push_back("--rcfile=" + pylintrc);
  for (const string& s : pylintOptions)
    sv.push_back(s);
  for (list<string>::const_iterator it = packagePaths.begin(); it != packagePaths.end(); ++it) {
    sv.push_back(*it);
  }

  common::pathDeleteFile(outputFile);

  int ret = common::run(pythonBinary, sv, outputFile, outputFile);
  if (ret != 0) {
    WriteMsg::write(CMSG_PYLINT_NON_ZERO_EXIT, ret);
    exit(EXIT_FAILURE);
  }
}
