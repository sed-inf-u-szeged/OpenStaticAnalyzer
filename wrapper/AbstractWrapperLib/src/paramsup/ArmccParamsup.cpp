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

#include "AbstractWrapperLib/inc/paramsup/ArmccParamsup.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>

using namespace std;

#define ARMCC_PARAMSUP "ArmccParamsup"

// Unhandled preprocessor arguments without any parameter
static const char* unhandled_preproc_arguments[] = {
  "--echo",                        
  "--help",                        
  "--show_cmdline",                
  "--version_number",              
  "--vsn",                         
  "-C",                         
  "--code_gen",
  "--no_code_gen",
  "-E",
  "-M",
  "-Uname"
};

// Unhandled preprocessor argument with any parameter
static const char* unhandled_preproc_arguments_with_parameter[] = {
  "-d",                             // -d??, -dD  -dI  -dM  -dN
  "-MF",                            // -MF file
  "-MT",                            // -MT target
  "-MQ",                            // -MQ target
  "-MD",                            // -MD file (=-M -MF)
  "-MMD",                           // -MMD file
  "-D",                           // -MMD file
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
  "-m",               // -memulatoin
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
  "--c90",                             // -H
  "--c99",                             // -P
  "--compile_all_input",
  "--no_compile_all_input",
  "--cpp",
  "--strict",
  "--no_strict",
  "--strict_warnings",
  "--asm",
  "--interleave",
  "--arm",
  "--thumb",
  "--device"
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
  "-fno-enforce-eh-specs",          // -fno-enforce-eh-specs
  "--multibyte_chars",
  "--gnu",
  "--feedback",
  "--depend"
};

// Unhandled compiler arguments with any parameter
static const char* unhandled_compiler_arguments_with_parameter[] = {
  "-B",                             // -Bprefix
  "-specs",                         // -specs=file
  "-fmessage-length",               // -fmessage-length=n
  "-fvisibility",                   // -fvisibility=visibility
  "-O",
  "--cpu",
  "--apcs",
  "--message_locale",
  "--locale"
};


ColumbusWrappers::ParErrorCode ColumbusWrappers::ArmccWrapperSup::examinePreprocArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, Warnings& armccWarnings, PreprocArgs& preprocArgs, Argument& actArg) {

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
        armccWarnings.can_warning.push_back(string("Parameter of the -include (") + remain + ") is missing!");
        return EC_FOUND;
      }
    } else if (!isLast(args_it, args_end)) {
      ++args_it;
      if (common::pathFileExists(*args_it, false)) {
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_inc_files, *args_it);
        return EC_FOUND;
      } else {
        armccWarnings.can_warning.push_back(string("Parameter of the -include (") + *args_it + ") is missing!");
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

  } else if (*args_it == "-undef") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-u"));
    return EC_FOUND;

  } else if (*args_it == "-fno-exceptions") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-edg:--no_exceptions"));
    return EC_FOUND;

  } else if (*args_it == "-fexceptions") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-edg:--exceptions"));
    return EC_FOUND;

  } else if (common::isPrefix(*args_it, "-ftemplate-depth-", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_args, string("-edg:--pending_instantiations=" + remain), false);

  } else if (*args_it == "-C") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-edg:--comments"));
    return EC_FOUND;

  } else if (*args_it == "-nostdinc" || *args_it == "-nostdinc++") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-nostdinc"));
    return EC_FOUND;

  } else if (*args_it == "-trigraphs") {

    insertArgumentIntoArgumentList(actArg, preprocArgs.prep_args, string("-edg:--trigraphs"));
    return EC_FOUND;

  } else {

    return EC_NOT_FOUND;

  }

  return EC_NOT_FOUND;
}


ColumbusWrappers::ParErrorCode ColumbusWrappers::ArmccWrapperSup::examineLinkerArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, LinkerArgs& linkerArgs, Argument& actArg, const bool fullCheck) {

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


bool ColumbusWrappers::ArmccWrapperSup::compilerArguments(list<string> args, Warnings& armccWarnings, PreprocArgs& preprocArgs, CompilerArgs& compilerArgs, LinkerArgs& linkerArgs) {

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

    } else if ((ec = ColumbusWrappers::ArmccWrapperSup::examinePreprocArg(args_it, args.end(), armccWarnings, preprocArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

    } else if ((ec = ColumbusWrappers::ArmccWrapperSup::examineLinkerArg(args_it, args.end(), linkerArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

    } else if (*args_it == "-march") {
      // skipped argument
      if (args_it->substr(0,7) == "-march=" && 7 < args_it->length()) {
        // nothing to do
      } else if (6 < args_it->length()) {
        // nothing to do
      } else if (!isLast(args_it, args.end())) {
        ++args_it;
      } else {
        actualArgument = *args_it;
        ret = EC_ERROR;
        break;
      }

    } else if (*args_it == "-ansi") {

      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--c89"));

    } else if (common::isPrefix(*args_it, "-std=", remain)) {

      if (remain == "c90" || remain == "c89" || remain == "iso9899:1990" || remain == "gnu90" || remain == "gnu89") {
        insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-std:c89"));
      }
      if (remain == "c99" || remain == "c9x" || remain == "iso9899:1999" || remain == "iso9899:199x" || remain == "gnu99" || remain == "gnu9x") {
        insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-std:c99"));
      }
      if (remain == "c++99" || remain == "gnu++98") {
        insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-std:c++03"));
      }
      if (remain == "c11" || remain == "c1x" || remain == "iso9899:2011" || remain == "gnu11" || remain == "gnu1x" || remain == "gnu++11" || remain == "gnu++0x" || remain == "c++11" || remain == "c++0x") {
        insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-std:c++11"));
      }

    } else if (*args_it == "-pthreads" || *args_it == "-pthread") {

      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, string("-edg:--thread_local_storage"));

    } else if ((*args_it)[0] != '-') {

      actArg.name = *args_it;
      string ext, file;
      if(common::splitExt(*args_it, file, ext)) {
        if (ext[0] == '.') {
          ext = ext.substr(1);
        }
        if (common::isclang(ext) || common::iscpplang(ext)) {
          if (common::isclang(ext)) {
            actArg.lang = "c";
          } else {
            actArg.lang = "cpp";
          }
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
      ec = ColumbusWrappers::ArmccWrapperSup::examineLinkerArg(args_it, args.end(), linkerArgs, actArg);
        if (ec == EC_NOT_FOUND) {
          armccWarnings.unrec_args.push_back(*args_it);
        } else if (ec == EC_ERROR) {
          actualArgument = *args_it;
          ret = EC_ERROR;
          break;
        }

    } else {

      armccWarnings.unrec_args.push_back(*args_it);

    }

  } //for

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(ARMCC_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  ret = EC_FOUND;

  int actWlpos = 0;
  for (list<string>::iterator Wl_it = Wl_args.begin(); Wl_it != Wl_args.end(); Wl_it++) {
    actArg.position = Wl_pos[actWlpos];
    ec = ColumbusWrappers::ArmccWrapperSup::examineLinkerArg(Wl_it, Wl_args.end(), linkerArgs, actArg);
    if (ec == EC_NOT_FOUND) {
      armccWarnings.unrec_args.push_back(*Wl_it);
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
    ec = ColumbusWrappers::ArmccWrapperSup::examinePreprocArg(Wp_it, Wp_args.end(), armccWarnings, preprocArgs, actArg);
    if (ec == EC_NOT_FOUND) {
      armccWarnings.unrec_args.push_back(*Wp_it);
    } else if (ec == EC_ERROR) {
      actualArgument = *Wp_it;
      ret = EC_ERROR;
      break;
    }
    ++actWppos;
  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(ARMCC_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  if (compilerArgs.compiling && linkerArgs.linking) {
    linkerArgs.linker_output_file = temp_output;
    compilerArgs.comp_output_file = temp_output;
  } else if (compilerArgs.compiling) {
    compilerArgs.comp_output_file = temp_output;
  } else {
    armccWarnings.can_warning.push_back("Only preprocessing is needed");
  }

  

  compilerArgs.max_arg = actArg.position;

  return true;
}


bool ColumbusWrappers::ArmccWrapperSup::linkerArguments(list<string> args, Warnings& armccWarnings, LinkerArgs& linkerArgs) {
  Argument actArg;
  ColumbusWrappers::ParErrorCode ret = EC_FOUND;
  string actualArgument = "";

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++) {
    ++actArg.position;
    ColumbusWrappers::ParErrorCode ec = ColumbusWrappers::ArmccWrapperSup::examineLinkerArg(args_it, args.end(),  linkerArgs, actArg, true);
    if (ec == EC_NOT_FOUND) {
      armccWarnings.unrec_args.push_back(*args_it);
    } else if (ec == EC_ERROR) {
      actualArgument = *args_it;
      ret = EC_ERROR;
      break;
    }
  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(ARMCC_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_LINKER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  linkerArgs.max_arg = actArg.position;
  return true;
}

