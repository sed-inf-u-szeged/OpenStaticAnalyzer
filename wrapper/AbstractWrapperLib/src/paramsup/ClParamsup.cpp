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

#include "AbstractWrapperLib/inc/paramsup/ClParamsup.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define CL_PARAMSUP "ClParamsup"

// Unhandled preprocessor arguments without any parameter
static const char* unhandled_preproc_arguments[] = {
  "/ZI",                        // /ZI
};

// Unhandled preprocessor arguments with any parameter
static const char* unhandled_preproc_arguments_with_parameter[] = {
  "/AI",                        // /AIdir
  "/FU",                        // /FUfile
};

// Unhandled compiler arguments without parameter.
static const char* unhandled_compiler_arguments[] = {
  "/fd",            // /FD
  "/gs",            // /GS
  "/gf",            // /GF
  "/gt",            // /GT
  "/nologo",        // /nologo
  "/WX-",           // Turn off treat warnings as errors
  "/WX"             // Treat warnings as errors
};

// Unhandled compiler arguments with parameter(s)
static const char* unhandled_compiler_arguments_with_parameter[] = {
  "/zm",            // /Zm[n]
  "/errorreport:",  // /errorReport:[ none | prompt | queue | send ]
};

// Unhandled compiler arguments with/without parameters. These arguments are allowed to use without any parameters and with parameters too.
static const char* unhandled_compiler_arguments_wo_parameter[] = {
  "/fd",            // /Fd[path]
  "/gl",            // /GL[-]
  "/gm",            // /Gm[-]
  "/analyze",       // /analyzer[:WX-]
  "/Yc",
  "/Yu",
  "/Fp"
};

static vector<string> clang_simple_arguments{
  "/Brepro-",
  "/Brepro",
  "/C",
  "/c",
  "/EP",
  "/E",
  "/fallback",
  "/FA",
  "/GA",
  "/Gd",
  "/GF-",
  "/GR-",
  "/GR",
  "/Gr",
  "/GS-",
  "/GS",
  "/Gv",
  "/Gw-",
  "/Gw",
  "/GX-",
  "/GX",
  "/Gy-",
  "/Gy",
  "/Gz",
  "/help",
  "/J",
  "/LDd",
  "/LD",
  "/MDd",
  "/MD",
  "/MTd",
  "/MT",
  "/Od",
  "/Oi-",
  "/Oi",
  "/Os",
  "/Ot",
  "/P",
  "/Qvec-",
  "/Qvec",
  "/showIncludes",
  "/TC",
  "/TP",
  "/utf-8",
  "/vmb",
  "/vmg",
  "/vmm",
  "/vms",
  "/vmv",
  "/W0",
  "/W1",
  "/W2",
  "/W3",
  "/W4",
  "/Wall",
  "/w",
  "/Y-",
  "/Z7",
  "/Zd",
  "/Zi",
  "/Zl",
  "/Zp",
  "/Zs"
};

static vector<string> clang_arguments_with_separate_value = {
  "/D",
  "/EH",
  "/Fa",
  "/Fe",
  "/FI",
  "/Fi",
  "/Fo",
  "/Gs",
  "/imsvc",
  "/I",
  "/O",
  "/o",
  "/Tc",
  "/Tp",
  "/U",
  "/vd",
  "/Zp",
  "/link"
};

static vector<string> clang_arguments_with_prefix = {
  "/arch:",
  "/execution-charset:",
  "/fp:",
  "/source-charset:",
  "/std:",
  "/volatile:",
  "/Zc:",
};

ColumbusWrappers::ParErrorCode ColumbusWrappers::ClWrapperSup::examinePreprocArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, Warnings& clWarnings, PreprocArgs& preprocArgs, Argument& actArg) {

  string remain = "";
  size_t n;

  // Checking unhandled arguments
  for (n = 0; n < sizeof(unhandled_preproc_arguments)/sizeof(char*); n++) {
    if (*args_it == unhandled_preproc_arguments[n]) {
      return EC_FOUND;
    }
  }

  for (n = 0; n < sizeof(unhandled_preproc_arguments_with_parameter)/sizeof(char*); n++) {
    if (common::isPrefix(*args_it, unhandled_preproc_arguments_with_parameter[n], remain)) {
      if (!remain.empty()) {
        return EC_FOUND;
      } else if (!isLast(args_it, args_end)) {
        ++args_it;
        return EC_FOUND;
      } else {
        return EC_ERROR;
      }
    }
  }

  if (*args_it == "/X") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, *args_it);
    return EC_FOUND;

  } else if (*args_it == "/u") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, *args_it);
    return EC_FOUND;

  } else if (args_it->substr(0,2) == "/I" && args_it->substr(0,7)!="/IMPLIB") {

    if (common::isPrefix(*args_it, "/I", remain)) {
      return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_inc_paths, remain, true);
    }

  } else if (args_it->substr(0,3) == "/FI") {

    if (common::isPrefix(*args_it, "/FI", remain)) {
      return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_inc_files, remain, true);
    }

  } else if (args_it->substr(0,2) == "/D" && args_it->substr(0,5)!="/DEF:" && *args_it != "/DLL") {

    if (common::isPrefix(*args_it, "/D", remain)) {
      return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_defs, remain, true);
    }

  } else if (args_it->substr(0,2) == "/U") {

    if (common::isPrefix(*args_it, "/U", remain)) {
      return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_undefs, remain, true);
    }

  } else {

    return EC_NOT_FOUND;

  }

  return EC_NOT_FOUND;
}


ColumbusWrappers::ParErrorCode ColumbusWrappers::ClWrapperSup::examineLinkerArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, LinkerArgs& linkerArgs, Argument& actArg) {
  string remain = "";
  const string tmparg = *args_it;

  if (common::isPrefix(tmparg, "/libpath:", remain, false, false)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_paths, remain, false);

  } else if (common::isPrefix(tmparg, "/out:", remain, false, false)) {

    linkerArgs.no_output = false;
    return setParameterOfArgumentToArgument(args_it, args_end, actArg, linkerArgs.linker_output_file, remain, false);

  } else if (common::isPrefix(tmparg, "/export:", remain, false, false)) {

    linkerArgs.create_lib = true;

  } else if (common::stringLower(tmparg) == "/dll") {

    linkerArgs.create_dll = true;

  } else if (common::isPrefix(tmparg, "/def:", remain, false, false)) {

    if(!remain.empty()) {
      string fname = remain;
      FILE* f = fopen(fname.c_str(), "r");
      while(!feof(f)) {
        char temp[1000];
        int read = fscanf(f, "%s", temp);
        if (read == EOF || read != 1) {
          fclose(f);
          return EC_ERROR;
        }
        if (strcmp(common::stringLower(temp), "exports") == 0) {
          linkerArgs.create_lib = true;
          break;
        }
      }
      fclose(f);
    }
    return EC_FOUND;

  } else if (common::isPrefix(tmparg, "/implib:", remain, false, false)) {

    actArg.name = remain;
    linkerArgs.import_lib_name = actArg;      //How can the CANLinker use this?
    linkerArgs.create_lib = true;             //...and this?
    return EC_FOUND;

  } else if ((tmparg)[0] != '/') {

    actArg.name = tmparg;
    string ext, file;
    if (common::splitExt(tmparg, file, ext) && common::stringLower(ext) == ".lib") {
      resolveFilePatterToFiles(actArg,linkerArgs.linker_lib_files);

    } else {
      resolveFilePatterToFiles(actArg,linkerArgs.linker_input_files);
    }
    return EC_FOUND;

  } else {

    return EC_NOT_FOUND;

  }

  return EC_NOT_FOUND;
}


bool ColumbusWrappers::ClWrapperSup::compilerArguments(list<string> args, Warnings& clWarnings, PreprocArgs& preprocArgs, CompilerArgs& compilerArgs, LinkerArgs& linkerArgs) {
  ColumbusWrappers::ParErrorCode ec = EC_FOUND;
  string remain = "";
  bool zaSet=false;
  list<string> Wl_args;
  Argument actArg;
  ColumbusWrappers::ParErrorCode ret = EC_FOUND;
  string actualArgument = "";
  bool isClang = false;
  bool isCpplang = false;
  bool wasClangInput = false;

  Argument outputDirArg;

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++) {
    string tmpArg = *args_it;

    //Options are specified by either a forward slash (/) or a dash (-)

    if ( (*args_it)[0] == '-') {
       (*args_it)[0] = '/';
    }
    

    // Checking unhandled arguments.
    size_t n;
    bool recognized = false;
    for (n = 0; n < sizeof(unhandled_compiler_arguments)/sizeof(char*); n++) {
      if (common::stringLower(tmpArg) == unhandled_compiler_arguments[n]) {
        recognized = true;
        break;
      }
    }

    if (recognized) {
      continue;
    }

    for (n = 0; n < sizeof(unhandled_compiler_arguments_with_parameter)/sizeof(char*); n++) {
      if (*args_it == "/Wp64") {
        continue;
      }
      if (common::isPrefix(tmpArg, unhandled_compiler_arguments_with_parameter[n], remain, false, false)) {
        if (!remain.empty()) {
          recognized = true;
          break;
        } else {
          actualArgument = *args_it;
          ret = EC_ERROR;
          break;
        }
      }
    }

    if (ret == EC_ERROR) {
      break;
    }

    if (recognized) {
      continue;
    }

    for (n = 0; n < sizeof(unhandled_compiler_arguments_wo_parameter)/sizeof(char*); n++) {
      if (common::stringLower(tmpArg) == unhandled_compiler_arguments_wo_parameter[n]) {
        recognized = true;
        break;
      } else if (common::isPrefix(tmpArg, unhandled_compiler_arguments_wo_parameter[n], remain, false, false)) {
        if (!remain.empty()) {
          recognized = true;
          break;
        } else {
          actualArgument = *args_it;
          ret = EC_ERROR;
          break;
        }
      } else {
        continue;
      }
    }

    if (ret == EC_ERROR) {
      break;
    }

    if (recognized) {
      continue;
    }

    ++actArg.position;

    if (*args_it == "/E" || *args_it == "/EP" || *args_it == "/P") {

      compilerArgs.compiling = false;
      linkerArgs.linking = false;
      clWarnings.can_warning.push_back("Only preprocessing is needed");

    } else if (*args_it == "/c") {

      compilerArgs.compiling = true;
      linkerArgs.linking = false;

    } else if ((*args_it)[0] != '/') {

      actArg.name = *args_it;
      string ext, file;
      if (common::splitExt(*args_it, file, ext)) {
        if (ext[0] == '.') {
          ext = ext.substr(1);
        }
        if (common::isclang(ext) || common::iscpplang(ext)) {
          if (isClang) {
            actArg.lang = "c";
          } else if (isCpplang) {
            actArg.lang = "c++";
          } else if (common::isclang(ext)) {
            actArg.lang = "c";
            wasClangInput = true;
          } else {
            actArg.lang = "c++";
          }

          //TODO resolve special chars.

          resolveFilePatterToFiles(actArg,compilerArgs.comp_input_files);
        }
      }

    } else if (common::isPrefix(*args_it, "/Fo", remain)) {

      compilerArgs.no_output = false;
      if (!remain.empty()) {
        int idx = remain.length()-1;
        if (remain[idx] == '"') {
          idx--;
        }
        actArg.name = remain;       // file or directory
        compilerArgs.comp_output_file = actArg; // otherwise the output file is given
      } else {
        actualArgument = *args_it;
        // No problem if /Fo doesnt have a value, it doesn't need to in cl.exe...
        //ret = EC_ERROR;
        break;
      }

    } else if (common::isPrefix(*args_it, "/Fe", remain)) {

      linkerArgs.no_output = false;
      if ((ret = setParameterOfArgumentToArgument(args_it, args.end(), actArg, linkerArgs.linker_output_file, remain, false)) == EC_ERROR) {
        actualArgument = *args_it;
        break;
      }

    } else if (common::isPrefix(common::stringLower(tmpArg), "/o", remain) && common::stringLower(tmpArg) != "/opt" && common::stringLower(tmpArg) != "/out" && common::stringLower(tmpArg) != "/order") {

      if (remain.empty()) {
        clWarnings.unrec_args.push_back(*args_it);
      }

    } else if ((ec = ColumbusWrappers::ClWrapperSup::examinePreprocArg(args_it, args.end(), clWarnings, preprocArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

    } else if ((ec = ColumbusWrappers::ClWrapperSup::examineLinkerArg(args_it, args.end(), linkerArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

    } else if (*args_it == "/Za") {

      zaSet = true;

    } else if (*args_it == "/Wp64") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_Wp64"));

    } else if (*args_it == "/TP") {

      isCpplang = true;

    } else if (common::isPrefix(*args_it, "/Tp", remain)) {

      actArg.lang = "c++";
      if (!remain.empty()) {
        insertArgumentIntoArgumentList(actArg, compilerArgs.comp_input_files, remain);
      }

    } else if (*args_it == "/TC") {

      isClang = true;

    } else if (common::isPrefix(*args_it, "/Tc", remain)) {

      actArg.lang = "c";
      wasClangInput = true;
      if (!remain.empty()) {
        insertArgumentIntoArgumentList(actArg, compilerArgs.comp_input_files, remain);
      }

    } else if (*args_it == "/link") {

      list<string>::iterator prev;
      while (args_it != args.end()) {
        prev = args_it;
        ++args_it;
        if (args_it == args.end()) {
          break;
        }
        Wl_args.push_back(*args_it);
      }
      args_it = prev;

      for (list<string>::iterator Wl_it = Wl_args.begin(); Wl_it != Wl_args.end(); Wl_it++) {
        ec = ColumbusWrappers::ClWrapperSup::examineLinkerArg(Wl_it, Wl_args.end(), linkerArgs, actArg);
        if (ec == EC_NOT_FOUND) {
          clWarnings.unrec_args.push_back(*Wl_it);
        } else if (ec == EC_ERROR) {
          actualArgument = *Wl_it;
          ret = EC_ERROR;
          break;
        }
        ++actArg.position;
      }
      if (ret == EC_ERROR) {
        break;
      }

    } else {

      // Assuming that the clang has the same parameters as the cl we put all the available clang parameters to comp_args
      actArg.name = *args_it;
      vector<string>::const_iterator found_it;
      string remain;

      if (find(clang_simple_arguments.begin(), clang_simple_arguments.end(), *args_it) != clang_simple_arguments.end())
      {
        compilerArgs.comp_args.push_back(actArg);
      }
      else if ((found_it = find_if(clang_arguments_with_prefix.begin(),
        clang_arguments_with_prefix.end(),
        [&](const string& s) { return common::isPrefix(*args_it, s, remain); })) != clang_arguments_with_prefix.end())
      {
        compilerArgs.comp_args.push_back(actArg);
      }
      else if ((found_it = find_if(clang_arguments_with_separate_value.begin(),
        clang_arguments_with_separate_value.end(),
        [&](const string& s) { return common::isPrefix(*args_it, s, remain); })) != clang_arguments_with_separate_value.end())
      {
        compilerArgs.comp_args.push_back(actArg);
        if (remain.empty())
        {
          ++args_it;
          if (args_it != args.end())
          {
            actArg.name = *args_it;
            ++actArg.position;
            compilerArgs.comp_args.push_back(actArg);
          }
        }
      }
      else
      {
        clWarnings.unrec_args.push_back(*args_it);
      }

    }

  }

  if (zaSet && (isClang || wasClangInput)) {
    ++actArg.position;
    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__STDC__=1"));
  }

  if (isClang && isCpplang) {
    ColumbusWrappers::writeWarningMsg(CL_PARAMSUP, CMSG_COMPILER_PARAMSUP_BOTH_C_CPP_FILE);
  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(CL_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  compilerArgs.max_arg = actArg.position;

  return true;
}


bool ColumbusWrappers::ClWrapperSup::linkerArguments(list<string> args, Warnings& clWarnings, LinkerArgs& linkerArgs) {
  Argument actArg;
  ColumbusWrappers::ParErrorCode ret = EC_FOUND;
  string actualArgument = "";

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++) {


    if ( (*args_it)[0] == '-') {
      (*args_it)[0] = '/';
    }

    ++actArg.position;
    ColumbusWrappers::ParErrorCode ec = ColumbusWrappers::ClWrapperSup::examineLinkerArg(args_it, args.end(), linkerArgs, actArg);
    if (ec == EC_NOT_FOUND) {
      clWarnings.unrec_args.push_back(*args_it);
    } else if (ec == EC_ERROR) {
      actualArgument = *args_it;
      ret = EC_ERROR;
      break;
    }
  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(CL_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_LINKER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  linkerArgs.max_arg = actArg.position;
  return true;
}

