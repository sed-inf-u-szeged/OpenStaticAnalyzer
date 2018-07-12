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
  "/zi",            // /Zi
  "/zd",            // /Zd
  "/z7",            // /Z7
  "/fd",            // /FD
  "/gs",            // /GS
  "/gf",            // /GF
  "/gt",            // /GT
  "/nologo",        // /nologo
};

// Unhandled compiler arguments with parameter(s)
static const char* unhandled_compiler_arguments_with_parameter[] = {
  "/zm",            // /Zm[n]
  "/w",             // /W[n], /Wall, /WX, /Wd[n], /We[n], /Wo[n], /WL, /WS
  "/fp:",           // /Fp:[precise | except[-] | fast | strict ]
  "/errorreport:",  // /errorReport:[ none | prompt | queue | send ]
};

// Unhandled compiler arguments with/without parameters. These arguments are allowed to use without any parameters and with parameters too.
static const char* unhandled_compiler_arguments_wo_parameter[] = {
  "/fd",            // /Fd[path]
  "/gs",            // /Gs[size]
  "/gl",            // /GL[-]
  "/gm",            // /Gm[-]
  "/gy",            // /Gy[-]
  "/analyze",       // /analyzer[:WX-]
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

  } else if (*args_it == "/C") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-edg:--comments"));
    return EC_FOUND;

  } else {

    return EC_NOT_FOUND;

  }

  return EC_NOT_FOUND;
}


ColumbusWrappers::ParErrorCode ColumbusWrappers::ClWrapperSup::examineLinkerArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, LinkerArgs& linkerArgs, Argument& actArg) {
  string remain = "";
  string tmparg = *args_it;

  if (common::isPrefix(common::stringLower(tmparg), "/libpath:", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_paths, remain, false);

  } else if (common::isPrefix(common::stringLower(tmparg), "/out:", remain)) {

    linkerArgs.no_output = false;
    return setParameterOfArgumentToArgument(args_it, args_end, actArg, linkerArgs.linker_output_file, remain, false);

  } else if (common::isPrefix(common::stringLower(tmparg), "/export:", remain)) {

    linkerArgs.create_lib = true;

  } else if (common::stringLower(tmparg) == "/dll") {

    linkerArgs.create_dll = true;

  } else if (common::isPrefix(common::stringLower(tmparg), "/def:", remain)) {

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

  } else if (common::isPrefix(common::stringLower(tmparg), "/implib:", remain)) {

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
      if (common::isPrefix(common::stringLower(tmpArg), unhandled_compiler_arguments_with_parameter[n], remain)) {
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
      } else if (common::isPrefix(common::stringLower(tmpArg), unhandled_compiler_arguments_wo_parameter[n], remain)) {
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
            actArg.lang = "cpp";
          } else if (common::isclang(ext)) {
            actArg.lang = "c";
            wasClangInput = true;
          } else {
            actArg.lang = "cpp";
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
        ret = EC_ERROR;
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

    } else if (*args_it == "/Ze") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_MSC_EXTENSIONS=1"));

    } else if (*args_it == "/J") {

      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--unsigned_chars"));

    } else if (*args_it == "/GR") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_CPPRTTI"));

    } else if (*args_it == "/GX") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-edg:--exceptions"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_CPPUNWIND"));

    } else if (args_it->substr(0,3) == "/EH" && (args_it->length() == 4 || args_it->length() == 5 || args_it->length() == 6)) {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-edg:--exceptions"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_CPPUNWIND"));

    } else if (*args_it == "/LDd") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_DEBUG"));

    } else if (*args_it == "/MDd") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_DEBUG"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_DLL"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_MT"));

    } else if (*args_it == "/MD") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_DLL"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_MT"));

    } else if (*args_it == "/MLd") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_DEBUG"));

    } else if (*args_it == "/MTd") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_DEBUG"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_MT"));

    } else if (*args_it == "/MT") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_MT"));

    } else if (common::isPrefix(*args_it, "/clr", remain)) {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_MANAGED=1"));

    } else if (common::isPrefix(*args_it, "/RTC", remain)) {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__MSVC_RUNTIME_CHECKS"));

    } else if (common::isPrefix(*args_it, "/Zc:", remain)) {

      list<string> ZcList;
      common::split(remain, ZcList, ',');
      for (list<string>::const_iterator ZcIt = ZcList.begin(); ZcIt != ZcList.end(); ZcIt++) {
        if (*ZcIt == "wchar_t" || *ZcIt == "wchar_t-") {
          insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--wchar_t_keyword"));
        } else if (*ZcIt == "forScope" || *ZcIt == "forScope-") {
          insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--old_for_init"));
        } else if (*ZcIt == "auto" || *ZcIt == "auto-") {
          insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--auto_type"));
        } else {
          clWarnings.unrec_args.push_back(*args_it);
        }
      }

    } else if (*args_it == "/Gd") {

      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--default_calling_convention"));
      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:__cdecl"));

    } else if (*args_it == "/Gr") {

      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--default_calling_convention"));
      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:__fastcall"));

    } else if (*args_it == "/Gz") {

      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--default_calling_convention"));
      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:__stdcall"));

    } else if (*args_it == "/Wp64") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("_Wp64"));

    } else if (*args_it == "/TP") {

      isCpplang = true;

    } else if (common::isPrefix(*args_it, "/Tp", remain)) {

      actArg.lang = "cpp";
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

    } else if (args_it->substr(0,3) == "/Fp" || args_it->substr(0,3) == "/Yc" || args_it->substr(0,3) == "/Yu" || args_it->substr(0,3) == "/Yx") {
      //do nothing just recognize them
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

      clWarnings.unrec_args.push_back(*args_it);

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

