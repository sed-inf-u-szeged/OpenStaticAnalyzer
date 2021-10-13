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

#include "AbstractWrapperLib/inc/paramsup/ClangParamsup.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <algorithm>

using namespace std;

#define CLANG_PARAMSUP "ClangParamsup"

// Unhandled compiler arguments without any parameter
static const char* unhandled_compiler_arguments[] = {
  "--analyze",
  "-arcmt-migrate-emit-errors",
  "-dD",
  "-dI",
  "-dM",
  "-emit-ast",
  "-emit-llvm",
  "-fapple-kext",
  "-fcoverage-mapping",
  "-fdata-sections",
  "-fdebug-info-for-profiling",
  "-fdebug-macro",
  "-fdebug-types-section",
  "-fdiagnostics-absolute-paths",
  "-fdiagnostics-parseable-fixits",
  "-fdiagnostics-print-source-range-info",
  "-fdiagnostics-show-hotness",
  "-fdiagnostics-show-note-include-stack",
  "-fdiagnostics-show-option",
  "-fdiagnostics-show-template-tree",
  "-fembed-bitcode-marker",
  "-fembed-bitcode",
  "-ffixed-r9",
  "-ffixed-x18",
  "-ffreestanding",
  "-ffunction-sections",
  "-finstrument-functions",
  "-flto",
  "-fno-preserve-as-comments",
  "-fno-sanitize-address-use-after-scope",
  "-fno-sanitize-blacklist",
  "-fno-sanitize-cfi-cross-dso",
  "-fno-sanitize-memory-track-origins",
  "-fno-sanitize-stats",
  "-fno-sanitize-thread-atomics",
  "-fno-sanitize-thread-func-entry-exit",
  "-fno-sanitize-thread-memory-access",
  "-fno-show-column",
  "-fno-show-source-location",
  "-fpcc-struct-return",
  "-fprofile-generate",
  "-fprofile-instr-generate",
  "-freg-struct-return",
  "-frtlib-add-rpath",
  "-fsanitize-address-globals-dead-stripping",
  "-fsanitize-address-use-after-scope",
  "-fsanitize-cfi-cross-dso",
  "-fsanitize-memory-track-origins",
  "-fsanitize-memory-use-after-dtor",
  "-fsanitize-stats",
  "-fsanitize-thread-atomics",
  "-fsanitize-thread-func-entry-exit",
  "-fsanitize-thread-memory-access",
  "-fsave-optimization-record",
  "-fsplit-dwarf-inlining",
  "-fstack-protector-all",
  "-fstack-protector-strong",
  "-fstack-protector",
  "-fstandalone-debug"
  "-funique-section-names",
  "-fuse-init-array",
  "-fwhole-program-vtables",
  "-fxray-instrument",
  "-fvectorize",
  "-gz",
  "-gcodeview",
  "-gdwarf-2",
  "-gdwarf-3",
  "-gdwarf-4",
  "-gdwarf-5",
  "-gline-tables-only",
  "-gmodules",
  "-mabicalls",
  "-malign-double",
  "-mbackchain",
  "-mcrc",
  "-MD",
  "-mexecute-only",
  "-mfentry",
  "-mfix-cortex-a53-835769",
  "-mfp32",
  "-mfp64",
  "-mgeneral-regs-only",
  "-mglobal-merge",
  "-MG",
  "-mhvx-double",
  "-mhvx",
  "-miamcu",
  "--migrate",
  "-mincremental-linker-compatible",
  "-mlong-calls",
  "-mmadd4",
  "-MMD",
  "-mms-bitfields",
  "-mmsa",
  "-mmt",
  "-MM",
  "-mno-abicalls",
  "-mno-execute-only",
  "-mno-fix-cortex-a53-835769",
  "-mno-global-merge",
  "-mno-hvx-double",
  "-mno-hvx",
  "-mno-implicit-float",
  "-mno-incremental-linker-compatible",
  "-mno-long-calls",
  "-mno-madd4",
  "-mno-movt",
  "-mno-ms-bitfields",
  "-mno-msa",
  "-mno-mt",
  "-mno-neg-immediates",
  "-mno-restrict-it",
  "-mno-unaligned-access",
  "-mnocrc",
  "-module-file-info",
  "-momit-leaf-frame-pointer",
  "-mpie-copy-relocations",
  "-MP",
  "-mqdsp6-compat",
  "-mrelax-all",
  "-mrestrict-it",
  "-mrtd",
  "-msoft-float",
  "-mstackrealign",
  "-munaligned-access",
  "-MV",
  "-M",
  "-pg",
  "-print-ivar-layout",
  "-print-libgcc-file-name",
  "-print-resource-dir",
  "-print-search-dirs",
  "-pthread",
  "-P",
  "-Qunused-arguments",
  "-relocatable-pch",
  "-save-stats",
  "-save-temps",
  "-time",
  "--verify-debug-info",
  "-verify-pch",
  "-v",
  "-Wdeprecated",
  "-W"
};

// Unhandled compiler arguments with any parameter
static const char* unhandled_compiler_arguments_with_parameter[] = {
  "--analyzer-output",
  "-arcmt-migrate-report-output",
  "-dependency-dot",
  "-dependency-file",
  "-fbuild-session-file",
  "-fbuild-session-timestamp",
  "-fclang-abi-compat",
  "-fcolor-diagnostics",
  "-fdebug-prefix-map",
  "-fdiagnostics-hotness-threshold",
  "-fembed-bitcode",
  "-ffp-contract",
  "-flto-jobs",
  "-flto",
  "-fno-sanitize-coverage=",
  "-fno-sanitize-recover=",
  "-fno-sanitize-trap=",
  "-foptimization-record-file=",
  "-fplugin=",
  "-fprofile-generate=",
  "-fprofile-instr-generate=",
  "-fprofile-instr-use=",
  "-fprofile-sample-use=",
  "-fprofile-use=",
  "-fsanitize-address-field-padding=",
  "-fsanitize-blacklist=",
  "-fsanitize-coverage=",
  "-fsanitize-memory-track-origins=",
  "-fsanitize-recover=",
  "-fsanitize-trap=",
  "-fsanitize-undefined-strip-path-components=",
  "-fsanitize=",
  "-fshow-overloads=",
  "-fthinlto-index=",
  "-ftrap-function=",
  "-ftrapv-handler=",
  "-fveclib=",
  "-fxray-always-instrument=",
  "-fxray-instruction-threshold=",
  "-fxray-never-instrument=",
  "-G",
  "-gz=",
  "-meabi",
  "-MF",
  "-mios-version-min=",
  "-MJ",
  "-mmacosx-version-min=",
  "-module-dependency-dir",
  "-MQ",
  "-mstack-alignment=",
  "-mstack-probe-size=",
  "-mthread-model",
  "-MT",
  "-print-file-name=",
  "-print-prog-name=",
  "-Rpass-analysis=",
  "-Rpass-missed=",
  "-Rpass=",
  "-save-stats=",
  "-save-temps=",
  "-serialize-diagnostics",
  "--target=",
  "-Tbss",
  "-Tdata",
  "-Ttext",
  "-T",
  "-Wa,",
  "-Wl,",
  "-W",
  "-Xanalyzer",
  "-Xassembler",
  "-Xlinker",
  "-z"
};

static vector<string> clang_simple_arguments {
  "-###",
  "-ansi",
  "-CC",
  "-cl-denorms-are-zero",
  "-cl-fast-relaxed-math",
  "-cl-finite-math-only",
  "-cl-fp32-correctly-rounded-divide-sqrt",
  "-cl-kernel-arg-info",
  "-cl-mad-enable",
  "-cl-no-signed-zeros",
  "-cl-opt-disable",
  "-cl-single-precision-constant",
  "-cl-strict-aliasing",
  "-cl-unsafe-math-optimizations",
  "--cuda-compile-host-device",
  "--cuda-device-only",
  "--cuda-host-only",
  "--cuda-noopt-device-debug",
  "-C",
  "-c",
  "-faligned-allocation",
  "-fallow-editor-placeholders",
  "-fansi-escape-codes",
  "-fapple-pragma-pack",
  "-fapplication-extension",
  "-fblocks",
  "-fborland-extensions",
  "-fbuiltin-module-map",
  "-fcoroutines-ts",
  "-fcuda-approx-transcendentals",
  "-fcuda-flush-denormals-to-zero",
  "-fcxx-exceptions",
  "-fdeclspec",
  "-fdelayed-template-parsing",
  "-fdollars-in-identifiers",
  "-femit-all-decls",
  "-femulated-tls",
  "-fexceptions",
  "-fexperimental-new-pass-manager",
  "-ffast-math",
  "-fgnu-keywords",
  "-fimplicit-module-maps",
  "-finline-functions",
  "-finline-hint-functions",
  "-fintegrated-as",
  "-fmath-errno",
  "-fmodules-decluse",
  "-fmodules-disable-diagnostic-validation",
  "-fmodules-search-all",
  "-fmodules-strict-decluse",
  "-fmodules-ts",
  "-fmodules-validate-once-per-build-session",
  "-fmodules-validate-system-headers",
  "-fmodules",
  "-fms-compatibility",
  "-fms-extensions",
  "-fno-access-control",
  "-fno-aligned-new",
  "-fno-assume-sane-operator-new",
  "-fno-autolink",
  "-fno-builtin",
  "-fno-common",
  "-fno-constant-cfstrings",
  "-fno-coverage-mapping",
  "-fno-crash-diagnostics",
  "-fno-debug-info-for-profiling",
  "-fno-debug-macro",
  "-fno-declspec",
  "-fno-delayed-template-parsing",
  "-fno-diagnostics-fixit-info",
  "-fno-dollars-in-identifiers",
  "-fno-elide-constructors",
  "-fno-elide-type",
  "-fno-experimental-new-pass-manager",
  "-fno-exceptions",
  "-fno-gnu-inline-asm",
  "-fno-integrated-as",
  "-fno-jump-tables",
  "-fno-lax-vector-conversions",
  "-fno-lto",
  "-fno-math-errno",
  "-fno-merge-all-constants",
  "-fno-objc-infer-related-result-type",
  "-fno-operator-names",
  "-fno-omit-frame-pointer",
  "-fno-profile-generate",
  "-fno-profile-instr-generate",
  "-fno-profile-instr-use",
  "-fno-reroll-loops",
  "-fno-rtlib-add-rpath",
  "-fno-rtti",
  "-fno-short-wchar",
  "-fno-signed-char",
  "-fno-signed-zeros",
  "-fno-sized-deallocation",
  "-fno-spell-checking",
  "-fno-stack-protector",
  "-fno-standalone-debug",
  "-fno-strict-aliasing",
  "-fno-threadsafe-statics",
  "-fno-trigraphs",
  "-fno-unroll-loops",
  "-fno-use-cxa-atexit",
  "-fno-use-init-array",
  "-fobjc-arc-exceptions",
  "-fobjc-arc",
  "-fobjc-exceptions",
  "-fobjc-weak",
  "-fpascal-strings",
  "-fPIC",
  "-freciprocal-math",
  "-frelaxed-template-template-args",
  "-freroll-loops",
  "-frtti",
  "-fshort-enums",
  "-fshort-wchar",
  "-fsized-deallocation",
  "-fsjlj-exceptions",
  "-fslp-vectorize",
  "-fstrict-enums",
  "-fstrict-return",
  "-fstrict-vtable-pointers"
  "-ftrapv",
  "-ftrigraphs",
  "-funroll-loops",
  "-funsigned-char",
  "-funwind-tables",
  "-fvisibility-inlines-hidden",
  "-fvisibility-ms-compat",
  "-fwrapv",
  "-fwritable-strings",
  "-fzvector",
  "-help",
  "-H",
  "-I-",
  "-index-header-map",
  "--no-cuda-version-check",
  "-mcx16",
  "-nobuiltininc",
  "-nostdinc++",
  "-ObjC++",
  "-objcmt-atomic-property",
  "-objcmt-migrate-all",
  "-objcmt-migrate-annotation",
  "-objcmt-migrate-designated-init",
  "-objcmt-migrate-instancetype",
  "-objcmt-migrate-literals",
  "-objcmt-migrate-ns-macros",
  "-objcmt-migrate-property-dot-syntax",
  "-objcmt-migrate-property",
  "-objcmt-migrate-protocol-conformance",
  "-objcmt-migrate-readonly-property",
  "-objcmt-migrate-readwrite-property",
  "-objcmt-migrate-subscripting",
  "-objcmt-ns-nonatomic-iosonly",
  "-objcmt-returns-innerpointer-property",
  "-ObjC",
  "-pipe",
  "--precompile",
  "-rewrite-legacy-objc",
  "-rewrite-objc",
  "-S",
  "-traditional-cpp",
  "-trigraphs",
  "-undef",
  "-W",
  "-w"

};

static vector<string> clang_arguments_with_separate_value = {
  "-B",
  "-cxx-isystem",
  "-fmodules-user-build-path",
  "-F",
  "-idirafter",
  "-iframeworkwithsysroot",
  "-iframework",
  "-imacros",
  "-include-pch",
  "-iprefix",
  "-iquote",
  "-isysroot",
  "-isystem-after",
  "-isystem",
  "-ivfsoverlay",
  "-iwithprefixbefore",
  "-iwithprefix",
  "-iwithsysroot",
  "-I",
  "-L",
  "-mllvm",
  "-o",
  "-U",
  "-working-directory",
  "-Xcuda-fatbinary",
  "-Xcuda-ptxas",
  "-Xpreprocessor",
  "-x"
};

static vector<string> clang_arguments_with_prefix = {
  "-cl-std=",
  "--cuda-gpu-arch=",
  "--cuda-path="
  "-fcomment-block-commands=",
  "-fmax-type-align=",
  "-fmodule-file=",
  "-fmodule-map-file=",
  "-fmodule-name=",
  "-fmodules-cache-path=",
  "-fmodules-ignore-macro=",
  "-fmodules-prune-after=",
  "-fmodules-prune-interval=",
  "-fms-compatibility-version=",
  "-fmsc-version=",
  "-fnew-alignment=",
  "-fno-builtin-",
  "-fprebuilt-module-path=",
  "-fobjc-runtime=",
  "-fopenmp-targets=",
  "-fpack-struct=",
  "-fvisibility=",
  "--no-cuda-gpu-arch=",
  "--no-system-header-prefix=",
  "-objcmt-whitelist-dir-path=",
  "--ptxas-path=",
  "-rtlib=",
  "-R",
  "-std=",
  "-stdlib=",
  "--system-header-prefix=",
  "-Wp,",
  "--gcc-toolchain="
};



ColumbusWrappers::ParErrorCode ColumbusWrappers::ClangWrapperSup::examinePreprocArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, Warnings& clangWarnings, PreprocArgs& preprocArgs, Argument& actArg)
{
  string remain = "";

  if (common::isPrefix(*args_it, "-I", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_inc_paths, remain, true);

  } else if (common::isPrefix(*args_it, "-include", remain)) {

    if (!remain.empty()) {
      if (common::pathFileExists(remain, false)) {
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_inc_files, remain);
        return EC_FOUND;
      } else {
        clangWarnings.can_warning.push_back(string("Parameter of the -include (") + remain + ") is missing!");
        return EC_FOUND;
      }
    } else if (!isLast(args_it, args_end)) {
      ++args_it;
      if (common::pathFileExists(*args_it, false)) {
        insertArgumentIntoArgumentList(actArg, preprocArgs.prep_inc_files, *args_it);
        return EC_FOUND;
      } else {
        clangWarnings.can_warning.push_back(string("Parameter of the -include (") + *args_it + ") is missing!");
        return EC_FOUND;
      }
    } else {
      return EC_ERROR;
    }

  } else if (common::isPrefix(*args_it, "-isystem", remain)) {

    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, preprocArgs.prep_isystem_dirs, remain, true);

  } else if (common::isPrefix(*args_it, "--cxx-isystem", remain)) {

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


ColumbusWrappers::ParErrorCode ColumbusWrappers::ClangWrapperSup::examineLinkerArg(list<string>::iterator& args_it, const list<string>::const_iterator& args_end, LinkerArgs& linkerArgs, Argument& actArg, const bool fullCheck)
{
  string remain = "";
  
  if (common::isPrefix(*args_it, "-L", remain)) 
    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_paths, remain, true);

  else if (common::isPrefix(*args_it, "--library-path", remain, true))
    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_paths, remain, true);

  else if (common::isPrefix(*args_it, "-l", remain))
    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_files, remain, true);

  else if (common::isPrefix(*args_it, "--library", remain, true))
    return insertParameterOfArgumentIntoArgumentList(args_it, args_end, actArg, linkerArgs.linker_lib_files, remain, true);

  if(!fullCheck) {
    return EC_NOT_FOUND;
  }

  if (common::isPrefix(*args_it, "--output", remain, true))
  {
    linkerArgs.no_output = false;
    return setParameterOfArgumentToArgument(args_it, args_end, actArg, linkerArgs.linker_output_file, remain, true);
  }
  else if (common::isPrefix(*args_it, "-o", remain))
  {
    linkerArgs.no_output = false;
    return setParameterOfArgumentToArgument(args_it, args_end, actArg, linkerArgs.linker_output_file, remain, true);
  }
  else if ((*args_it)[0] != '-')
  {
    insertArgumentIntoArgumentList(actArg, linkerArgs.linker_input_files, *args_it);
    return EC_FOUND;
  }

  return EC_NOT_FOUND;
}


bool ColumbusWrappers::ClangWrapperSup::compilerArguments(list<string> args, Warnings& clangWarnings, PreprocArgs& preprocArgs, CompilerArgs& compilerArgs, LinkerArgs& linkerArgs) {

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
  bool skipNextXclang = false;

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
      // generating PCH so we skipp it
      if (actArg.lang == "c-header" || actArg.lang == "cxx-header")
        compilerArgs.compiling = false;

      insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, "");
    } else if ((ec = ColumbusWrappers::ClangWrapperSup::examinePreprocArg(args_it, args.end(), clangWarnings, preprocArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;
    } else if ((ec = ColumbusWrappers::ClangWrapperSup::examineLinkerArg(args_it, args.end(), linkerArgs, actArg)) == EC_FOUND) {

    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

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
        } else if (common::isobjclang(ext)) {
          if (actArg.lang.empty())
            actArg.lang = "objective-c";
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
    }
    else if (*args_it == "-Xclang")
    {
      ++args_it;
      if (args_it != args.end())
      {
        if (skipNextXclang)
        {
          skipNextXclang = false;
          ++actArg.position;
        }

        else if (*args_it == "-emit-pch")
        {
          compilerArgs.compiling = false;
          ++actArg.position;
        }
        else if (*args_it == "-include-pch")
        {
          skipNextXclang = true;
          ++actArg.position;
        }
        else
        {
          insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, "-Xclang");
          ++actArg.position;
          insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, *args_it);
        }
      }
    } else {
      // Assuming that the clang has the same parameter as the clang we put all the available clang parameters to comp_args
      actArg.name = *args_it;
      vector<string>::const_iterator found_it;
      string remain;

      if (find(clang_simple_arguments.begin(), clang_simple_arguments.end(), *args_it) != clang_simple_arguments.end())
      {
        compilerArgs.comp_args.push_back(actArg);
      }
      else if ((found_it = find_if(clang_arguments_with_prefix.begin(),
                                   clang_arguments_with_prefix.end(),
                                   [&] (const string& s) { return common::isPrefix(*args_it, s, remain); })) != clang_arguments_with_prefix.end())
      {
        compilerArgs.comp_args.push_back(actArg);
      }
      else if ((found_it = find_if(clang_arguments_with_separate_value.begin(),
                                   clang_arguments_with_separate_value.end(),
                                   [&] (const string& s) { return common::isPrefix(*args_it, s, remain); })) != clang_arguments_with_separate_value.end())
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
        insertArgumentIntoArgumentList(actArg, compilerArgs.comp_args, "");
        clangWarnings.unrec_args.push_back(*args_it);
      }
    }

  } //for

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(CLANG_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  ret = EC_FOUND;

  int actWppos = 0;
  for (list<string>::iterator Wp_it = Wp_args.begin(); Wp_it != Wp_args.end(); Wp_it++) {
    actArg.position = Wp_pos[actWppos];
    ec = ColumbusWrappers::ClangWrapperSup::examinePreprocArg(Wp_it, Wp_args.end(), clangWarnings, preprocArgs, actArg);
    if (ec == EC_NOT_FOUND) {
      clangWarnings.unrec_args.push_back(*Wp_it);
    } else if (ec == EC_ERROR) {
      actualArgument = *Wp_it;
      ret = EC_ERROR;
      break;
    }
    ++actWppos;
  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(CLANG_PARAMSUP, CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT, actualArgument.c_str());
    return false;
  }

  if (compilerArgs.compiling && linkerArgs.linking) {
    linkerArgs.linker_output_file = temp_output;
  } else if (compilerArgs.compiling) {
    compilerArgs.comp_output_file = temp_output;
  } else {
    clangWarnings.can_warning.push_back("Only preprocessing is needed");
  }

  compilerArgs.max_arg = actArg.position;

  return true;
}
