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

#include "python/inc/python.h"
#include "python/inc/messages.h"

#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace common;

namespace columbus { namespace python {

static bool isIgnored(const boost::filesystem::path& p, const list<string>& ignoreList) {
  for (list<string>::const_iterator it = ignoreList.begin(), itEnd = ignoreList.end(); it != itEnd; ++it) {
    if (p.filename().string() == *it) {
      return true;
    }
  }
  return false;
}

static void collectPackages(const string& fileOrDir, const list<string>& ignoreList, bool checkSubDirs, list<string>& packagePaths) {
  try {
    boost::filesystem::path p(fileOrDir);

    if (boost::filesystem::exists(p)) {

      // skip hidden files and directories
      std::string filename = p.filename().string();
      if (filename.empty() || (filename[0] == '.' && filename != ".")) {
        return;
      }

      // skip ignored
      if (isIgnored(p, ignoreList)) {
        return;
      }

      if (boost::filesystem::is_directory(p)) {

        if (boost::filesystem::exists(p / "__init__.py")) {

          packagePaths.push_back(p.string());

        } else if (checkSubDirs) {

          std::vector<boost::filesystem::path> paths;
          std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(paths));
          std::sort(paths.begin(), paths.end());
          for (std::vector<boost::filesystem::path>::const_iterator it = paths.begin(); it != paths.end(); ++it) {
            collectPackages(it->string(), ignoreList, false, packagePaths);
          }

        }
      }

    } else {
      WriteMsg::write(CMSG_PATH_DOES_NOT_EXIST, fileOrDir.c_str());
    }
  } catch (const boost::filesystem::filesystem_error& ex) {
    WriteMsg::write(CMSG_FILESYSTEM_ERROR, ex.what());
  }
}

static void collectFiles(const string& fileOrDir, const list<string>& ignoreList, list<string>& filePaths) {
  try {
    boost::filesystem::path p(fileOrDir);

    if (boost::filesystem::exists(p)) {

      // skip hidden files and directories
      std::string filename = p.filename().string();
      if (filename.empty() || (filename[0] == '.' && filename != ".")) {
        return;
      }

      // skip ignored
      if (isIgnored(p, ignoreList)) {
        return;
      }

      if (boost::filesystem::is_regular_file(p)) {

        if (p.extension().string() == ".py") {
          filePaths.push_back(p.string());
        }

      } else if (boost::filesystem::is_directory(p)) {

        if (boost::filesystem::exists(p / "__init__.py")) {

          std::vector<boost::filesystem::path> paths;
          std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(paths));
          std::sort(paths.begin(), paths.end());
          for (std::vector<boost::filesystem::path>::const_iterator it = paths.begin(); it != paths.end(); ++it) {
            collectFiles(it->string(), ignoreList, filePaths);
          }

        }

      }

    } else {
      WriteMsg::write(CMSG_PATH_DOES_NOT_EXIST, fileOrDir.c_str());
    }
  } catch (const boost::filesystem::filesystem_error& ex) {
    WriteMsg::write(CMSG_FILESYSTEM_ERROR, ex.what());
  }
}


void collectPythonPackages(const string& projectBaseDir, const string& ignore, list<string>& packagePaths) {
  list<string> ignoreList;
  common::split(ignore, ignoreList, ',');

  string baseDir = (boost::filesystem::path(projectBaseDir) / ".").parent_path().string(); // remove trailing slash, if any

  collectPackages(baseDir, ignoreList, true, packagePaths);
}

void collectPackageFiles(const string& projectBaseDir, const string& ignore, list<string>& filePaths) {
  list<string> ignoreList;
  common::split(ignore, ignoreList, ',');

  list<string> packagePaths;
  collectPythonPackages(projectBaseDir, ignore, packagePaths);

  for (list<string>::const_iterator it = packagePaths.begin(); it != packagePaths.end(); ++it) {
    collectFiles(*it, ignoreList, filePaths);
  }
}

}}
