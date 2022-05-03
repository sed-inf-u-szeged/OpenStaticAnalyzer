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

#ifdef PY3
#define PAN_VER "3"
#else
#define PAN_VER "2"
#endif
#define PROGRAM_NAME "PAN" PAN_VER
#define EXECUTABLE_NAME PROGRAM_NAME

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

#include "../inc/PVisitor.h"
#include "../inc/VisitorType.h"
#include "../inc/messages.h"
#include <MainCommon.h>
#include <common/inc/Stat.h>
#include <common/inc/DirectoryFilter.h>
#include <common/inc/PlatformDependentDefines.h>
#include <io/inc/CsvIO.h>
#include <python/inc/PythonCollector.h>

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::python::asg;


static int parseErrors = 0;

// command line
static std::string listFile;
static std::string out;
static std::string prefix;
static bool dPML = false;
static std::list<std::string> inputFiles;
static std::string outPath;
static bool pkg = false;
static std::string filterFile;
static bool analyzePackages = false;
static std::string pythonBinary;

// Callback methods for argument processing
static bool ppList (const Option *o, char *argv[]) {
  listFile = argv[0];
  return true;
}

static bool ppOut (const Option *o, char *argv[]) {
  out = argv[0];
  return true;
}

static bool ppDPML (const Option *o, char *argv[]) {
  dPML = true;
  return true;
}

static bool ppPref (const Option *o, char *argv[]) {
  prefix = argv[0];
  return true;
}

static void ppFile (char *filename) {
  inputFiles.push_back(filename);
}

static bool ppPkg (const Option *o, char *argv[]) {
  pkg = true;
  return true;
}

static bool ppFilterPath (const Option *o, char *argv[]) {
  filterFile = argv[0];
  return true;
}

static bool ppAnalyzePackages ( const Option *o, char *argv[] ) {
  analyzePackages = true;
  return true; 
}

bool ppPythonBinary(const common::Option *o, char *argv[]) {
  pythonBinary = argv[0];
  return true;
}

const common::Option OPTIONS_OBJ [] = {
  { false,      "-lst",               1,  "filename",   0,     OT_WC,         ppList,             NULL,   CLARG_LST},
  { false,      "-out",               1,  "filename",   0,     OT_WC,         ppOut,              NULL,   CLARG_OUT},
  { false,      "-dPML",              0,  "",           0,     OT_NONE,       ppDPML,             NULL,   CLARG_XML},
  { false,      "-basepath",          1,  "path",       0,     OT_WC,         ppPref,             NULL,   CLARG_PREFIX},
  { false,      "-pkg",               0,  "",           0,     OT_NONE,       ppPkg,              NULL,   CLARG_PKG},
  { false,      "-analyzepackages",   0,  "",           0,     OT_NONE,       ppAnalyzePackages,  NULL,   CLARG_ANALYZE_PKG},
  { false,      "-pythonBinary",      1,  "filename",   0,     OT_WC,         ppPythonBinary,     NULL,   CLARG_PYBIN},
  CL_FLTP
  COMMON_CL_ARGS
};


void checkOutputFile() {
  static std::string psi = ".psi";
  if (!out.empty()) {
    size_t len = out.length();
    size_t psiLen = strlen(psi.c_str());
    if ((psiLen <= len) && (out.substr(len - psiLen) == psi)) {
      outPath = out.substr(0, len - psiLen);
    } else {
      WriteMsg::write(CMSG_NOT_PSI_EXTENSION, out.c_str());
      outPath = std::string(out);
      out += psi;
    }
  } else {
    if (inputFiles.size() == 1) {
      std::string tmp(*inputFiles.begin());
      outPath = tmp.substr(0, tmp.find_last_of('.'));
    } else {
      outPath = "noname";
    }
    out = outPath + psi;
  }
}

static inline void setStartTime(uint64_t *time)
{
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system;
}

static inline void setElapsedTime(uint64_t *time)
{
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system - *time;
}

static inline void updateMemStat(uint64_t *max_mem)
{
  memstat ms = getProcessUsedMemSize();
  if (*max_mem < ms.size) {
    *max_mem = ms.size;
  }
}


static void collectFiles(const std::string& fileOrDir, std::set<std::string>& uniqueFiles, const std::string& ext) {
  try {
    boost::filesystem::path p(fileOrDir);

    if (boost::filesystem::exists(p)) {

      // skip hidden files and directories
      std::string filename = p.filename().string();
      if (filename.empty() || (filename[0] == '.' && filename != ".")) {
        return;
      }

      if (boost::filesystem::is_regular_file(p)) {
        // file
        if (p.extension().string() == ext) {
          uniqueFiles.insert(p.string());
        }

      } else if (boost::filesystem::is_directory(p)) {
        // directory
        std::vector<boost::filesystem::path> paths;
        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(paths));
        std::sort(paths.begin(), paths.end());
        for (std::vector<boost::filesystem::path>::const_iterator it = paths.begin(); it != paths.end(); ++it) {
          collectFiles(it->string(), uniqueFiles, ext);
        }

      }

    } else {
      WriteMsg::write(PATH_DOES_NOT_EXIST, fileOrDir.c_str());
    }
  } catch (const boost::filesystem::filesystem_error& ex) {
    WriteMsg::write(ERROR_WHILE_COLLECTING_FILES, ex.what());
  }
}

static void collectFiles(std::list<std::string>& files, const std::string& ext) {
  std::set<std::string> uniqueFiles;

  for (std::list<std::string>::const_iterator it = files.begin(), itEnd = files.end(); it != itEnd; ++it) {
    collectFiles(*it, uniqueFiles, ext);
  }

  // case insensitive sort
  std::set<std::string, common::case_insensitive_compare> ciFiles(uniqueFiles.begin(), uniqueFiles.end());

  files.clear();
  files.insert(files.begin(), ciFiles.begin(), ciFiles.end());
}


void run(const std::string& name, ASTVisitor& ast_visitor) {
  FILE* file = fopen(name.c_str(), "r");
  if (file == NULL) {
    WriteMsg::write(CMSG_CANNOT_OPEN_FILE, name.c_str());
    return;
  }

  PyArena *arena = PyArena_New();
  if (arena == NULL) {
    fclose(file);
    return;
  }

  WriteMsg::write(CMSG_PARSING, name.c_str());
  PyCompilerFlags flags;
  flags.cf_flags = 0;
  int errorCode = 0;

#ifdef PY3
  mod_ty mod = PyParser_ASTFromFile(file, name.c_str(), 0, Py_file_input, 0, 0, &flags, &errorCode, arena);
#else
  mod_ty mod = PyParser_ASTFromFile(file, name.c_str(), Py_file_input, 0, 0, &flags, &errorCode, arena);
#endif

  if (!mod) {
    ++parseErrors;
    cout.flush();
    cerr.flush();
    PyErr_PrintEx(0);
    cout.flush();
    cerr.flush();
  }

  fclose(file);

  PlLOC plloc;
  vector<int> llines = plloc.processLines(name, ast_visitor.getBuilder());

  if(mod == 0) {
    PyArena_Free(arena);
    WriteMsg::write(CMSG_PARSE_ERROR);
    return;
  }

  std::string module_name = name;
  if(!prefix.empty()){
    size_t pos = module_name.find(prefix);
    if(pos == 0){
      module_name = module_name.substr(prefix.size());
    }else{
      WriteMsg::write(CMSG_PARSE_ERROR);
    }
  }

  ast_visitor.Visit(name, module_name, mod, llines, plloc.getCommentMap());
  PyArena_Free(arena);
}

void checkPython() {
  std::string pyBin;

  if (!pythonBinary.empty()) {
    pyBin = pythonBinary;
  } else {
    // use env vars instead of command line switch
#ifdef PY3
    char* columbusPythonBinary = getenv("COLUMBUS_PYTHON3_BINARY");
#else
    char* columbusPythonBinary = getenv("COLUMBUS_PYTHON2_BINARY");
#endif
    if (columbusPythonBinary != NULL)
      pyBin = columbusPythonBinary;
  }

  if (pyBin.empty()) {
    WriteMsg::write(CMSG_PYTHON_BIN_UNSPEC);
    exit(EXIT_FAILURE);
  }

  std::string pythonPath;
  std::string pythonReleaseVersion; // in the format X.Y

  {
    std::vector<std::string> sv;
    sv.push_back("--version");
    std::stringstream ss;
    int ret = common::run(pyBin, sv, ss);
    std::string outStr = ss.str();

    if (ret != 0) {
      WriteMsg::write(CMSG_PYTHON_BIN_ERROR);
      exit(EXIT_FAILURE);
    }

    static const boost::regex versionRegex("Python (\\d+)\\.(\\d+)");
    boost::smatch match;

    if (boost::regex_search(outStr, match, versionRegex)) {
      pythonReleaseVersion = match[1].str() + "." + match[2].str();

      if (match[1].str() != PAN_VER) {
        WriteMsg::write(CMSG_PAN_PY_COMPAT_ERROR, PAN_VER, pythonReleaseVersion.c_str());
        exit(EXIT_FAILURE);
      }
    }
  }

  {
    std::vector<std::string> sv;
    sv.push_back("-c");
    sv.push_back("import sys; print(sys.prefix); print(sys.exec_prefix);");
    std::stringstream ss;

    int ret = common::run(pyBin, sv, ss);
    if (ret != 0) {
      WriteMsg::write(CMSG_PY_PREFIX_ERROR);
      exit(EXIT_FAILURE);
    }

    std::string line;
    while (getline(ss, line)) {
      common::trim(line);
      if (!line.empty()) {
        boost::filesystem::path p(line);
#ifdef _WIN32
        p /= "Lib";
#else
        p /= "lib";
        p /= ("python" + pythonReleaseVersion);
#endif
        if (boost::filesystem::exists(p)) {
          pythonPath = p.string();
          break;
        }
      }
    }
  }

  if (pythonPath.empty()) {
    WriteMsg::write(CMSG_PY_LIB_NOT_FOUND);
    exit(EXIT_FAILURE);
  }

  char* pythonPathEnv = getenv("PYTHONPATH");
  if (pythonPathEnv != NULL) {
    pythonPath += PATH_SEPARATOR + std::string(pythonPathEnv);
  }

  if (common::setEnvironmentVariable("PYTHONPATH", pythonPath.c_str()) != 0) {
    WriteMsg::write(CMSG_ERROR_ENVSET_FAILURE, "PYTHONPATH");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char** argv)
{
  MAIN_BEGIN

  uint64_t totalTime;
  uint64_t parseTime;
  uint64_t saveTime;
  uint64_t dumpTime;

  uint64_t maxMem = 0;

  setStartTime(&totalTime);

  MainInit(argc, argv, "-");

  checkPython();

  loadStringListFromFile(listFile, inputFiles);

  if (analyzePackages) {
    if (inputFiles.size() != 1) {
      WriteMsg::write(CMSG_ONE_INPUT_REQ);
      clError();
    }

    std::string baseDir = inputFiles.front();
    inputFiles.clear();
    columbus::python::collectPackageFiles(baseDir, "", inputFiles);

  } else {
    collectFiles(inputFiles, ".py");
  }

  if (!filterFile.empty()) {
    DirectoryFilter filter;
    if (common::pathFileExists(filterFile, false)) {
      filter.openFilterFile(filterFile);
    } else {
      WriteMsg::write(CMSG_CANNOT_OPEN_FILE, filterFile.c_str());
      return EXIT_FAILURE;
    }
    if (!filter.isEmpty()) {
      std::list<std::string>::iterator it = inputFiles.begin();
      while (it != inputFiles.end()) {
        if (filter.isFilteredOut(*it)) {
          WriteMsg::write(CMSG_FILTERED_FILE, it->c_str());
          it = inputFiles.erase(it);
        } else {
          ++it;
        }
      }
    }
  }

  if (inputFiles.empty()) {
    WriteMsg::write(CMSG_NO_INPUT_FILES);
  }

  checkOutputFile();

  RefDistributorStrTable strTable;
  Factory* factory = new Factory(strTable);

  setStartTime(&parseTime);

  if (!inputFiles.empty()) {
    if( !Py_IsInitialized() ) {
      Py_NoSiteFlag = 1;
      Py_DontWriteBytecodeFlag = 1; // Suppress writing bytecode files (*.pyc)
      Py_FrozenFlag = 1; // Suppress errors from getpath.c (could not find prefix/exec_prefix... on linux)
      Py_Initialize();
    }

    PBuilder p_builder(factory, pkg);
    ASTVisitor ast_visitor(p_builder);

    for(std::list<std::string>::iterator it = inputFiles.begin(); it != inputFiles.end(); it++) {
      run(*it, ast_visitor);
    }

    updateMemStat(&maxMem);

    VisitorType* edge_visit = new VisitorType(factory, ExpressionsAndInit);
    AlgorithmPreorder ap;
    ap.setVisitSpecialNodes(false, false);
    ap.run(*factory, *edge_visit, *factory->getRoot());
    delete edge_visit;
    edge_visit = new VisitorType(factory, Assignments);
    ap.run(*factory, *edge_visit, *factory->getRoot());
    delete edge_visit;
    edge_visit = new VisitorType(factory, ExprAndAtrRef);
    ap.run(*factory, *edge_visit, *factory->getRoot());
    delete edge_visit;
    edge_visit = new VisitorType(factory, ReturnAndBaseSpec);
    ap.run(*factory, *edge_visit, *factory->getRoot());
    delete edge_visit;
    edge_visit = new VisitorType(factory, ExprAndAtrRef);
    ap.run(*factory, *edge_visit, *factory->getRoot());
    delete edge_visit;
    edge_visit = new VisitorType(factory, ReturnAndBaseSpec);
    ap.run(*factory, *edge_visit, *factory->getRoot());
    delete edge_visit;
  }

  updateMemStat(&maxMem);
  setElapsedTime(&parseTime);
  setStartTime(&saveTime);

  WriteMsg::write(CMSG_SAVING_ASG, out.c_str());
  CsiHeader header;
  header.add(header.csih_OriginalLocation,out);

  factory->save(out, header);
  factory->saveFilter(outPath + ".fpsi");

  updateMemStat(&maxMem);
  setElapsedTime(&saveTime);
  setStartTime(&dumpTime);

  if (dPML) {
    std::string pmlFile = outPath + ".pml";
    WriteMsg::write(CMSG_CREATING_PML, pmlFile.c_str());
    std::ofstream ofs(pmlFile.c_str());
    if (!ofs.is_open()) {
      WriteMsg::write(CMSG_CANNOT_OPEN_FILE, pmlFile.c_str());
    } else {
      VisitorPYTHONML* visitor = new VisitorPYTHONML(ofs, "", false, false);
      AlgorithmPreorder ap;
      ap.run(*factory, *visitor);
      delete visitor;
      ofs.close();
    }
  }

  setElapsedTime(&dumpTime);
  setElapsedTime(&totalTime);

  delete factory;

  WriteMsg::write(
    CMSG_STATISTICS,
    parseTime / 100.0f,
    saveTime / 100.0f,
    dumpTime / 100.0f,
    totalTime / 100.0f,
    maxMem / 1048576,
    parseErrors
    );

  MAIN_END

  return 0;
}
