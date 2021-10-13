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

#include "AbstractWrapperLib/inc/paramsup/GccParamsup.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>

using namespace std;

#define GCC_PARAMSUP "GccParamsup"

// Unhandled preprocessor arguments without any parameter
static const char* unhandled_preproc_arguments[] = {
  "-remap",                         // -remap
  "-M",                             // -M
  "-MM",                            // -MM
  "-MG",                            // -MG
  "-MP",                            // -MP
  "-MD",                            // -MD
  "-MMD"                            // -MMD
};

// Unhandled preprocessor argument with any parameter
static const char* unhandled_preproc_arguments_with_parameter[] = {
  "-d",                             // -d??, -dD  -dI  -dM  -dN
  "-MF",                            // -MF file
  "-MT",                            // -MT target
  "-MQ"                             // -MQ target
};


// Unhandled linker arguments with parameter(s).
static const char* linker_par_args[] = {
  "-a",               // -akeyword
  "-A",               // -Aarchitecture
  "--architecture",   // --architecture=architecture
  "-b",               // -b input-format
  "--format",         // --format=input-format
  "-c",               // -c MRI-commandfile
  "--mri-script",     // --mri-script=MRI-commandfile
  "-e",               // -e entry
  "--entry",          // --entry=entry
  "--auxiliary",      // --auxiliary name
  "-F",               // -F name
  "--filter",         // --filter name
  "-fini",            // -fini name
  "-G",               // -Gvalue
  "--gpsize",         // --gpsize=value
  "-h",               // -hNAME
  "-soname",          // -soname=NAME
  "-init",            // -init name
  "-R",               // -R filename
  "--just-symbols",   // --just-symbols=filename
  "-T",               // -T scriptfile
  "--script",         // --script=scriptfile
  "-u",               // -u symbol
  "--undefined",      // --undefined=symbol
  "--unique",         // --unique[=SECTION]
  "-y",               // -y symbol
  "--trace-symbol",   // --trace-symbol=symbol
  "-Y",               // -Y path (Solaris compatibility)
  "-z",               // -z keyword
  "--version-script", //--version-script=script
  "-h",               // -hname
  "-soname",          // -soname=name 
  "-rpath-link",      // -rpath-link dir
  "-rpath",           // -rpath dir
  "--rpath",          // --rpath dir
  "--hash-style=",    // --hash-style=style
  "-B",               // -Boption
  "--dynamic-list",   // --dynamic-list-data, --dynamic-list-cpp-new, --dynamic-list-cpp-typeinfo, --dynamic-list=dynamic-list-file
  "-P",               // -P auditlib
};

// Unhandled compiler arguments without any parameter
static const char* unhandled_compiler_arguments[] = {
  "-H",                             // -H
  "-P",                             // -P
  "-I-",                            // -I-
  "-Wall",                          // -Wall
  "-W",                             // -W
  "-Wno-sign-compare",              // -Wno-sign-compare
  "-Wno-unused",                    // -Wno-unused
  "-Wno-uninitialized",             // -Wno-uninitialized
  "-Wendif-labels",                 // -Wendif-labels
  "-Wextra",                        // -Wextra
  "-Wshadow",                       // -Wshadow
  "-fno-common",                    // -fno-common
  "-fno-strict-aliasing",           // -fno-strict-aliasing
  "-fuse-cxa-atexit",               // -fuse-cxa-atexit
  "-fvisibility-inlines-hidden",    // -fvisibility-inlines-hidden
  "-pipe",                          // -pipe
  "-fno-enforce-eh-specs"           // -fno-enforce-eh-specs
};

// Unhandled compiler arguments with any parameter
static const char* unhandled_compiler_arguments_with_parameter[] = {
  "-B",                             // -Bprefix
  "-specs",                         // -specs=file
  "-fmessage-length",               // -fmessage-length=n
  "-fvisibility"                    // -fvisibility=visibility
};


ColumbusWrappers::ParErrorCode ColumbusWrappers::GccWrapperSup::examinePreprocArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, Warnings& gccWarnings, PreprocArgs& preprocArgs, Argument& actArg) {

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

  if (common::isPrefix(*args_it, "-I", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_inc_paths, remain, true);

  } else if (common::isPrefix(*args_it, "-include", remain)) {

    if (!remain.empty()) {
      if (common::pathFileExists(remain, false)) {
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_inc_files, remain);
        return EC_FOUND;
      } else {
        gccWarnings.can_warning.push_back(string("Parameter of the -include (") + remain + ") is missing!");
        return EC_FOUND;
      }
    } else if (!isLast(args_it, args_end)) {
      ++args_it;
      if (common::pathFileExists(*args_it, false)) {
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_inc_files, *args_it);
        return EC_FOUND;
      } else {
        gccWarnings.can_warning.push_back(string("Parameter of the -include (") + *args_it + ") is missing!");
        return EC_FOUND;
      }
    } else {
      return EC_ERROR;
    }

  } else if (common::isPrefix(*args_it, "-isystem", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_isystem_dirs, remain, true);

  } else if (common::isPrefix(*args_it, "-D", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_defs, remain, true);

  } else if (common::isPrefix(*args_it, "-U", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_undefs, remain, true);

  } else {

    return EC_NOT_FOUND;

  }

  return EC_NOT_FOUND;
}


ColumbusWrappers::ParErrorCode ColumbusWrappers::GccWrapperSup::examineLinkerArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, LinkerArgs& linkerArgs, Argument& actArg, const bool fullCheck) {

  string remain = "";
  size_t n;
  // Checking unhandled arguments
  for (n = 0; n < sizeof(linker_par_args)/sizeof(char*); n++) {
    if (common::isPrefix(*args_it, linker_par_args[n], remain)) {
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

  if (common::isPrefix(*args_it, "-L", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_paths, remain, true);

  } else if (common::isPrefix(*args_it, "--library-path", remain, true)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_paths, remain, true);

  } else if (common::isPrefix(*args_it, "-l", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_files, remain, true);

  } else if (common::isPrefix(*args_it, "--library", remain, true)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_files, remain, true);

  } else if (*args_it == "--whole-archive") {

    ++args_it;
    while ((list<string>::const_iterator)args_it != args_end && *args_it != "--no-whole-archive") {
      actArg.name = *args_it;
      linkerArgs.linker_input_files.push_back(actArg);
      ++args_it;
      ++actArg.position;
    }
    if ((list<string>::const_iterator)args_it != args_end) {
      return EC_FOUND;
    } else {
      return EC_ERROR;
    }

  } else if (*args_it == "-r" || *args_it == "--relocateable" || *args_it == "--relocatable" || *args_it == "-Ur") {

    linkerArgs.relocatable = true;
    return EC_FOUND;

  } else if (args_it->substr(0,2) == "-O" && args_it->size() <= 3) {

    return EC_FOUND;

  }

  if(!fullCheck) {
    return EC_NOT_FOUND;
  }

  if (common::isPrefix(*args_it, "--output", remain, true)) {

    linkerArgs.no_output = false;
    return setParameterOfArgumentToArgument(args_it, args_end, actArg, linkerArgs.linker_output_file, remain, true);

  } else if (common::isPrefix(*args_it, "-o", remain)) {

    linkerArgs.no_output = false;
    return setParameterOfArgumentToArgument(args_it, args_end, actArg, linkerArgs.linker_output_file, remain, true);

  } else if ((*args_it)[0] != '-') {

    insertArgumentIntoArgumentList(actArg, linkerArgs.linker_input_files, *args_it);
    return EC_FOUND;

  }

  return EC_NOT_FOUND;
}


bool ColumbusWrappers::GccWrapperSup::compilerArguments(list<string> args, Warnings& gccWarnings, PreprocArgs& preprocArgs, CompilerArgs& compilerArgs, LinkerArgs& linkerArgs) {

  ColumbusWrappers::ParErrorCode ec = EC_FOUND;
  Argument actArg;

  Argument temp_output;
  string remain = "";

  list<string> Wp_args;
  vector<int> Wp_pos;
  list<string> Wl_args;
  vector<int> Wl_pos;

  ColumbusWrappers::ParErrorCode ret = EC_FOUND;
  string actualArgument = "";

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++) {
    // Checking unhandled arguments.
    size_t n;
    bool recognized = false;
    for (n = 0; n < sizeof(unhandled_compiler_arguments)/sizeof(char*); n++) {
      if (*args_it == unhandled_compiler_arguments[n]) {
        recognized = true;
        break;
      }
    }

    if (recognized) {
      continue;
    }

    for (n = 0; n < sizeof(unhandled_compiler_arguments_with_parameter)/sizeof(char*); n++) {
      if (common::isPrefix(*args_it, unhandled_compiler_arguments_with_parameter[n], remain)) {
        if (!remain.empty()) {
          recognized = true;
          break;
        } else if (!isLast(args_it, args.end())) {
          ++args_it;
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

    ++actArg.position;

    if (*args_it == "-E") {

      compilerArgs.compiling = false;
      linkerArgs.linking = false;

    } else if (*args_it == "-S") {

      compilerArgs.compiling = false;
      linkerArgs.linking = false;

    } else if (*args_it == "-c") {

      compilerArgs.compiling &= true;
      linkerArgs.linking = false;

    } else if (common::isPrefix(*args_it, "-x", remain)) {

      if (remain.empty()) {
        ++args_it;
        if (args_it != args.end()) {
          actArg.lang = *args_it;
        } else {
          actualArgument = *args_it;
          ret = EC_ERROR;
          break;
        }
      } else {
        actArg.lang = remain;
      }
      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, "");
    } else if ((ec = ColumbusWrappers::GccWrapperSup::examinePreprocArg(args_it, args.end(), gccWarnings, preprocArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

    } else if ((ec = ColumbusWrappers::GccWrapperSup::examineLinkerArg(args_it, args.end(), linkerArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

    } else if (common::isPrefix(*args_it, "-march=", remain)) {

      if (remain == "core2") {
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__core2=1"));
        ++actArg.position;
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__core2__=1"));
        ++actArg.position;
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__tune_core2__=1"));
        ++actArg.position;
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__SSE3__=1"));
        ++actArg.position;
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__SSSE3__=1"));
      }
    } else if (common::isPrefix(*args_it, "-std=", remain)) {
      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, *args_it);
    } else if ((*args_it)[0] != '-') {

      actArg.name = *args_it;
      string ext, file;
      if(common::splitExt(*args_it, file, ext)) {
        if (ext[0] == '.') {
          ext = ext.substr(1);
        }
        for (list<Argument>::const_reverse_iterator argIt = compilerArgs.comp_args.rbegin(); argIt !=  compilerArgs.comp_args.rend(); ++argIt) {
          if (!argIt->lang.empty()) {
            actArg.lang = argIt->lang;
            break;
          }
        }
        if (common::isclang(ext)) {
          if (actArg.lang.empty())
            actArg.lang = "c";
          compilerArgs.comp_input_files.push_back(actArg);
        } else if (common::iscpplang(ext)) {
          if (actArg.lang.empty())
            actArg.lang = "c++";
          compilerArgs.comp_input_files.push_back(actArg);
        } else {
          linkerArgs.linker_input_files.push_back(actArg);
        }
      } else {
        linkerArgs.linker_input_files.push_back(actArg);
      }

    } else if (common::isPrefix(*args_it, "-o", remain)) {

      compilerArgs.no_output = false;
      if (!remain.empty()) {
        temp_output.position = actArg.position;
        temp_output.name = remain;
      } else if (!isLast(args_it, args.end())) {
        ++args_it;
        temp_output.position = actArg.position;
        temp_output.name = *args_it;
      } else {
        actualArgument = *args_it;
        ret = EC_ERROR;
        break;
      }

    } else if (*args_it == "-fpic") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__pic__=1"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__PIC__=1"));

    } else if (*args_it == "-fPIC") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__pic__=2"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__PIC__=2"));

    } else if (*args_it == "-fpie") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__pie__=1"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__PIE__=1"));

    } else if (*args_it == "-fPIE") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__pie__=2"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__PIE__=2"));

    } else if (*args_it == "-msse3") {

      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__SSE3__=1"));

    } else if (*args_it == "-mssse3") {
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__SSSE3__=1"));
      ++actArg.position;
      insertArgumentIntoArgumentList(actArg, preprocArgs.prep_defs, string("__SSE3__=1"));

    } else if (common::isPrefix(*args_it, "-Wp,", remain)) {

      string act_arg = args_it->substr(4);
      size_t next_comma = act_arg.find_first_of(",");
      int actpos = actArg.position;

      while (next_comma != std::string::npos) {
        Wp_args.push_back(act_arg.substr(0,next_comma));
        Wp_pos.push_back(actpos);
        act_arg = act_arg.substr(next_comma + 1);
        next_comma = act_arg.find_first_of(",");
        ++actArg.position;
        ++actpos;
      }
      Wp_args.push_back(act_arg);
      Wp_pos.push_back(actpos);

    } else if (common::isPrefix(*args_it, "-Wl,", remain)) {

      string act_arg = args_it->substr(4);
      size_t next_comma = act_arg.find_first_of(",");
      int actpos = actArg.position;

      while (next_comma != std::string::npos) {
        Wl_args.push_back(act_arg.substr(0,next_comma));
        Wl_pos.push_back(actpos);
        act_arg = act_arg.substr(next_comma + 1);
        next_comma = act_arg.find_first_of(",");
        ++actArg.position;
        ++actpos;
      }
      Wl_args.push_back(act_arg);
      Wl_pos.push_back(actpos);

    } else if (*args_it == "-Xlinker") {

      ++args_it;
      ec = ColumbusWrappers::GccWrapperSup::examineLinkerArg(args_it, args.end(), linkerArgs, actArg);
        if (ec == EC_NOT_FOUND) {
          gccWarnings.unrec_args.push_back(*args_it);
        } else if (ec == EC_ERROR) {
          actualArgument = *args_it;
          ret = EC_ERROR;
          break;
        }

    } else {

      gccWarnings.unrec_args.push_back(*args_it);

    }

  } //for

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(GCC_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  ret = EC_FOUND;

  int actWlpos = 0;
  for (list<string>::iterator Wl_it = Wl_args.begin(); Wl_it != Wl_args.end(); Wl_it++) {
    actArg.position = Wl_pos[actWlpos];
    ec = ColumbusWrappers::GccWrapperSup::examineLinkerArg(Wl_it, Wl_args.end(), linkerArgs, actArg);
    if (ec == EC_NOT_FOUND) {
      gccWarnings.unrec_args.push_back(*Wl_it);
    } else if (ec == EC_ERROR) {
      actualArgument = *Wl_it;
      ret = EC_ERROR;
      break;
    }
    ++actWlpos;
  }

  int actWppos = 0;
  for (list<string>::iterator Wp_it = Wp_args.begin(); Wp_it != Wp_args.end(); Wp_it++) {
    actArg.position = Wp_pos[actWppos];
    ec = ColumbusWrappers::GccWrapperSup::examinePreprocArg(Wp_it, Wp_args.end(), gccWarnings, preprocArgs, actArg);
    if (ec == EC_NOT_FOUND) {
      gccWarnings.unrec_args.push_back(*Wp_it);
    } else if (ec == EC_ERROR) {
      actualArgument = *Wp_it;
      ret = EC_ERROR;
      break;
    }
    ++actWppos;
  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(GCC_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  if (compilerArgs.compiling && linkerArgs.linking) {
    linkerArgs.linker_output_file = temp_output;
  } else if (compilerArgs.compiling) {
    compilerArgs.comp_output_file = temp_output;
  } else {
    gccWarnings.can_warning.push_back("Only preprocessing is needed");
  }

  compilerArgs.max_arg = actArg.position;

  return true;
}


bool ColumbusWrappers::GccWrapperSup::linkerArguments(list<string> args, Warnings& gccWarnings, LinkerArgs& linkerArgs) {
  Argument actArg;
  ColumbusWrappers::ParErrorCode ret = EC_FOUND;
  string actualArgument = "";

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++) {
    ++actArg.position;
    ColumbusWrappers::ParErrorCode ec = ColumbusWrappers::GccWrapperSup::examineLinkerArg(args_it, args.end(),  linkerArgs, actArg, true);
    if (ec == EC_NOT_FOUND) {
      gccWarnings.unrec_args.push_back(*args_it);
    } else if (ec == EC_ERROR) {
      actualArgument = *args_it;
      ret = EC_ERROR;
      break;
    }
  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(GCC_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_LINKER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  linkerArgs.max_arg = actArg.position;
  return true;
}

