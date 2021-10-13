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

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <AnalyzerWrapperConfig/AnalyzerWrapperConfig.h>

#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/DirectoryFilter.h>
#include <fstream>
#include <regex>
#include <functional>
#include <sstream>


#include "../../inc/abstractwrapper/AbstractCompiler.h"
#include "../../inc/messages.h"


using namespace std;
using namespace common;
using namespace boost::interprocess;

#define COMPILER_TOOL                   "CAN"
#define ABSTRACT_COMPILER               "AbstractCompiler"
#define COMPILER_CONFIG_TOOL            "CANConfig"
#define PREDEFINED_MACROS_FULL_FILENAME "predefined_macros_full.txt"

namespace ColumbusWrappers {

  struct DialectTable
  {
      int major;
      int minor;
      int patch;
      const char* C;
      const char* CPP;
  };

  vector<DialectTable> ClangDialectTable =
  {
    {   0, 0, 0, "gnu11", "gnu++98" },
    {   6, 0, 0, "gnu11", "gnu++14" },
    { 100, 0, 0, "", "" }
  };

  vector<DialectTable> GCCDialectTable =
  {
    {   0, 0, 0, "gnu89", "gnu++03" },
    {   3, 0, 4, "gnu89", "gnu++03" },
    {   3, 3, 6, "gnu99", "gnu++03" },
    {   5, 5, 0, "gnu11", "gnu++03" },
    {   6, 1, 0, "gnu11", "gnu++14" },
    {   7, 4, 0, "gnu11", "gnu++14" },
    {   8, 1, 0, "gnu17", "gnu++14" },
    { 100, 0, 0, "", "" }
  };

  vector<DialectTable> CLDialectTable =
  {
    {   0, 0, 0, "c89", "c++03" },
    {  15, 0, 0, "c89", "c++03" },
    {  16, 0, 0, "c89", "c++11" },
    {  19, 0, 0, "c11", "c++14" },
    { 100, 0, 0, "", "" }
  };

  AbstractCompiler::AbstractCompiler(string configfile) : AbstractWrapper(configfile),
                                                          comp_needtorun(0),
                                                          comp_needstat(0),
                                                          run_cppcheck(0),
                                                          comp_ml(2),
                                                          comp_paramtoskip(),
                                                          comp_numofparamtoskip(0),
                                                          comp_extraparam(),
                                                          comp_numofextraparam(0),
                                                          comp_tool(),
                                                          cl_version { 0, 0, 0 },
                                                          clang_version { 0, 0, 0 },
                                                          gcc_version { 0, 0, 0 }
  {
    readConfig();
    replaceQuoteForQuoteWithBackslash(wrapper_bin_dir);
    comp_tool = wrapper_bin_dir + DIRDIVSTRING + COMPILER_TOOL;
    comp_config_tool = wrapper_bin_dir + DIRDIVSTRING + COMPILER_CONFIG_TOOL;
  }

  void AbstractCompiler::readConfig() {
    comp_needtorun = getConfigInt(COMPILERSECTION, NEED_TO_RUN, 0);
    instrument_mode = getConfigInt(COMPILERSECTION, INST_MODE, 0);
    comp_needstat = getConfigInt(COMPILERSECTION, NEED_STAT, 0);
    run_cppcheck = getConfigInt(COMPILERSECTION, RUN_CPPCHECK, 0);
    no_delayed_template_parsing = getConfigInt(COMPILERSECTION, NO_DELAYED_TEMPLATE_PARSING, 0);
    comp_ml = getConfigInt(COMPILERSECTION, TOOL_MESSAGE_LEVEL, 2);
    filter_path = getConfigString(LINKERSECTION, LINK_FILTER_FILE, NULL);

    comp_numofparamtoskip = getConfigInt(COMPILERSECTION, NUM_OF_PARAM_TO_SKIP, 0);
    getParamToSkip(COMPILERSECTION, comp_numofparamtoskip, comp_paramtoskip);

    comp_numofextraparam = getConfigInt(COMPILERSECTION, NUM_OF_EXTRA_PARAM, 0);
    getExtraParam(COMPILERSECTION, comp_numofextraparam, comp_extraparam);
  }

  namespace
  {
    string mapCompilerDialectToCppcheckDialect(const string& dialect)
    {
      if (dialect == "c90" || dialect == "c89" || dialect == "iso9899:1990" || dialect == "gnu90" || dialect == "gnu89")
        return "c89";
      else if (dialect == "c99" || dialect == "c9x" || dialect == "iso9899:1999" || dialect == "iso9899:199x" || dialect == "gnu99" || dialect == "gnu9x")
        return "c99";
      else if (dialect == "c11" || dialect == "c1x" || dialect == "iso9899:2011" || dialect == "gnu11" || dialect == "gnu1x")
        return "c11";
      else if (dialect == "c17" || dialect == "c18" || dialect == "iso9899:2017" || dialect == "iso9899:2018" || dialect == "gnu17" || dialect == "gnu18")
        //return "c17";
        return "c11"; // the cppcheck does not know the c17
      else if (dialect == "c++98" || dialect == "gnu++98" || dialect == "c++03" || dialect == "gnu++03")
        return "c++03";
      else if (dialect == "gnu++11" || dialect == "gnu++0x" || dialect == "c++11" || dialect == "c++0x")
        return "c++11";
      else if (dialect == "c++14" || dialect == "c++1y" || dialect == "gnu++14" || dialect == "gnu++1y")
        return "c++14";
      else if (dialect == "c++17" || dialect == "c++1z" || dialect == "gnu++17" || dialect == "gnu++1z")
        //return "c++17";
        return "c++14"; // the cppcheck does not know the c++17

      return "c++11";
    }

    string getCANIniNameForCompiler(const string& compilerPath)
    {
      stringstream stream;
      stream << hex << std::hash<string>()(compilerPath) << ".ini";
      return stream.str();
    }

    void parseVersionString(int version[3], const string& versionString)
    {
        regex versionRegexp("(\\d+)\\.(\\d+)\\.(\\d+)");
        smatch versionMatch;
        if (regex_search(versionString, versionMatch, versionRegexp))
        {
            version[0] = stoi(versionMatch[1].str());
            version[1] = stoi(versionMatch[2].str());
            version[2] = stoi(versionMatch[3].str());
            writeInfoMsg(ABSTRACT_COMPILER, "Compiler version from config: %d.%d.%d\n", version[0], version[1], version[2]);
        }
    }
  }
    

  void AbstractCompiler::setCompilerVersion(file_lock& f_lock, int version[3], const vector<string>& commandlineArguments, const std::string& versionRegexString)
  {
    scoped_lock<file_lock> lock(f_lock);
    string version_from_config = getConfigString(COMPILERSECTION, wrappedExe.c_str(), NULL);

    if (version_from_config.empty())
    {
      stringstream output;
      int ret = common::run(wrappedExe, commandlineArguments, output);
      if (ret == 0)
      {
        regex versionRegex(versionRegexString);
        smatch versionMatch;
        string outputText = output.str();

        if (regex_search(outputText, versionMatch, versionRegex) && versionMatch.size() == 6)
        {
          version[0] = stoi(versionMatch[1].str());
          version[1] = stoi(versionMatch[3].str());
          version[2] = stoi(versionMatch[5].str());
          writePrivateProfileString(COMPILERSECTION, wrappedExe.c_str(), (to_string(version[0]) + "." + to_string(version[1]) + "." + to_string(version[2])).c_str(), configfile.c_str());
          writeInfoMsg(ABSTRACT_COMPILER, "Compiler version: %d.%d.%d\n", version[0], version[1], version[2]);
        }
      }
      else
      {
        writeInfoMsg(ABSTRACT_COMPILER, "Failed to check the compiler version! (exit code:%d)\n", ret);
      }

      if (mode == wrapper_gcc)
      {
        string ini_name = getCANIniNameForCompiler(wrappedExe);
        vector<string> args = { "-out", wrapper_work_dir, "-filename", ini_name, "-gcc", wrappedExe };

        ret = common::run(comp_config_tool, args);
        if (ret != 0)
        {
          writeInfoMsg(ABSTRACT_COMPILER, "Failed to run the " COMPILER_CONFIG_TOOL "! (exit code:%d)\n", ret);
        }
      }
    }
    else
    {
      parseVersionString(version, version_from_config);
    }
  }

  void AbstractCompiler::readCompilerVersion()
  {
    try
    {
      string lockFileName = common::getLockFileName(configfile);
      ofstream lock(lockFileName.c_str());
      file_lock f_lock(lockFileName.c_str());

      if (mode == wrapper_cl)
        setCompilerVersion(f_lock, cl_version, {}, "Compiler Version\\s*(\\d+)(\\.)?(\\d+)?(\\.)?(\\d+)?");
      else if (mode == wrapper_clang)
        setCompilerVersion(f_lock, clang_version, {"--version"}, "clang version\\s*(\\d+)(\\.)?(\\d+)?(\\.)?(\\d+)?");
      else if (mode == wrapper_gcc)
        setCompilerVersion(f_lock, gcc_version, {"--version"}, "^[^ ]+\\s*\\([^)]*\\)\\s*(\\d+)(\\.)?(\\d+)?(\\.)?(\\d+)?");
    }
    catch (const boost::interprocess::interprocess_exception& ex)
    {
      writeInfoMsg(ABSTRACT_COMPILER, "Failed to check the CL compiler version! (%s)\n", ex.what());
    }
  }

  void AbstractCompiler::concatenatePrefixAndParams(const char* prefix, const list<Argument>& input_list, list<Argument>& output_paramlist, bool separately) const {
    for (const auto& argument : input_list)
    {
      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_ARGUMENT_WITH_PARAM, prefix, argument.name.c_str());
      Argument a = argument;
      a.name = prefix + a.name;
      output_paramlist.push_back(std::move(a));
    }
  }


  bool AbstractCompiler::executeCompiler(CompilerArgs& compArgs, PreprocArgs& preprocArgs, list<Argument>& generated_files) const {
    if (compArgs.comp_input_files.empty()) {
      writeWarningMsg(ABSTRACT_COMPILER, CMSG_COMPILER_HAS_NO_INPUT);
      return true;
    }
    if (!compArgs.compiling) {
      writeWarningMsg(ABSTRACT_COMPILER, CMSG_NO_NEED_TO_COMPILE_BY_PARAMS);
      return true;
    }
    if (!comp_needtorun) {
      writeWarningMsg(ABSTRACT_COMPILER, CMSG_NO_NEED_TO_COMPILE_BY_CONFIG);
      return true;
    }
    
    list<Argument> output_paramlist;        // list for ordered CAN commandline

    writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_EXECUTION, comp_tool.c_str());
    
    string dialect;
    string defaultDialect;
    bool shouldUseDefaultDialect = true;

    for (const auto& argument : compArgs.comp_args)
    {
      if (argument.name.empty())
        continue;

      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_ARGUMENT, argument.name.c_str());

      if (argument.name.find("-std") == 0 || argument.name.find("/std") == 0)
      {
        dialect = argument.name.substr(5);

        // As it turns out, clang and msvc are not always compatible in the same way with the experimental, latest c++2a features,
        // so for now, just limit msvc support to the latest stable one for the cl version (this is always c++17 now (current date is 2020.02.05.))
        if (mode == wrapper_cl && dialect == "c++latest")
        {
          defaultDialect = "c++17";
          continue;
        }
        else
          shouldUseDefaultDialect = false; // If the dialect was given explictly to the compiler as argument, and it's not latest, we should use this
      }
      else if (argument.name.find("-ansi") == 0)
        shouldUseDefaultDialect = false;

      output_paramlist.push_back(argument);
    }

    //clang and clang-cl sometimes have different argument format
    concatenatePrefixAndParams((mode == wrapper_cl?"/FI":"-include"), preprocArgs.prep_inc_files, output_paramlist);
    concatenatePrefixAndParams("-I", preprocArgs.prep_inc_paths, output_paramlist);
    concatenatePrefixAndParams("-D", preprocArgs.prep_defs, output_paramlist);
    concatenatePrefixAndParams("-U", preprocArgs.prep_undefs, output_paramlist);
    concatenatePrefixAndParams("-isystem", preprocArgs.prep_isystem_dirs, output_paramlist);

    for (const auto& prepocArg : preprocArgs.prep_args) {
      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_PREPROCESSOR_ARGUMENT, prepocArg.name.c_str());
      output_paramlist.push_back(prepocArg);
    }

    bool ok = true;

    for(list<Argument>::const_iterator it_f = compArgs.comp_input_files.begin(); it_f != compArgs.comp_input_files.end(); it_f++) {
      Argument outputFileArg;
      string input = it_f->name;
      string lang = it_f->lang;
      int in_pos = it_f->position;
      string output;

      if (shouldUseDefaultDialect && defaultDialect.empty())
      {
        // if no dialect is set then set it to the default dialect based on the version of the compiler

        vector<DialectTable>* dialectTable = nullptr;
        const int* version = nullptr;

        if (mode == wrapper_clang)
        {
          dialectTable = &ClangDialectTable;
          version = clang_version;
        }
        else if (mode == wrapper_cl)
        {
          dialectTable = &CLDialectTable;
          version = cl_version;
        }
        else if (mode == wrapper_gcc)
        {
          dialectTable = &GCCDialectTable;
          version = gcc_version;
        }

        for (size_t i = 1; i < dialectTable->size(); ++i)
        {
          const auto& dialectVersion = (*dialectTable)[i];
          if ( (version[0] < dialectVersion.major) ||
               ((version[0] == dialectVersion.major) && (version[1] < dialectVersion.minor)) ||
               ((version[0] == dialectVersion.major) && (version[1] == dialectVersion.minor) && (version[2] < dialectVersion.patch)))
          {
            if (lang == "c")
              defaultDialect = (*dialectTable)[i - 1].C;
            else
              defaultDialect = (*dialectTable)[i - 1].CPP;
            break;
          }
        }
      }

      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_INPUT_FILE, input.c_str());
      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_INPUT_FILE_LANG, lang.c_str());

      string output_dir;
      if(!compArgs.comp_output_file.name.empty()) {
        writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_OUTPUT_FROM_PARAM, compArgs.comp_output_file.name.c_str());
        output = compArgs.comp_output_file.name;
        if (output[output.length()-1] == '\\' || output[output.length()-1] == '/') {
          string inputfile, inputdir;
          common::splitPath(input, inputdir, inputfile);
          string file, ext;
          common::splitExt(inputfile,file,ext);
          output  = output + file + getObjectFileExtension();
        }
        string tmp_file;
        common::splitPath(output, output_dir, tmp_file);
        replaceQuoteForQuoteWithBackslash(output);
        insertDir(output, true);
        output += ".ast";
        outputFileArg.name = output;
        outputFileArg.position = compArgs.comp_output_file.position;
      } else {
        string file, ext;
        common::splitExt(input,file,ext);
        output  = file + getObjectFileExtension()+".ast";
        if (compArgs.no_output) {
          string tmpdir, tmpfile;
          common::splitPath(output, tmpdir, tmpfile);
          output = tmpfile;
        }
        writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_OUTPUT_FROM_INPUT, output.c_str());
        replaceQuoteForQuoteWithBackslash(output);
        insertDir(output, true);
        outputFileArg.name = output;
        outputFileArg.position = in_pos;
      }

      generated_files.push_back(outputFileArg);
      replaceQuoteForQuoteWithBackslash(input);

      output_paramlist.sort(compareArguments);

      vector<string> analyzer_command_arguments;

      if (mode == wrapper_cl)
      {
        analyzer_command_arguments.push_back("--driver-mode=cl");
        analyzer_command_arguments.push_back("-Wno-c++11-narrowing");
        analyzer_command_arguments.push_back("-march=native");
        analyzer_command_arguments.push_back("-Wno-error=non-pod-varargs");
        analyzer_command_arguments.push_back("-Wno-error=invalid-token-paste");
        analyzer_command_arguments.push_back("-Wno-error=address-of-temporary");

        if (lang == "c")
          analyzer_command_arguments.push_back("-TC");

        if (cl_version[0] != 0)
        {
          analyzer_command_arguments.push_back("-fms-compatibility-version=" + to_string(cl_version[0]) + "." + to_string(cl_version[1]) + "." + to_string(cl_version[2]));
        }
        if (no_delayed_template_parsing)
        {
          analyzer_command_arguments.push_back("-fno-delayed-template-parsing");
        }
      }

      for (list<Argument>::iterator it_v = output_paramlist.begin(); it_v != output_paramlist.end(); it_v++) {
        if(!it_v->name.empty()) {
          analyzer_command_arguments.push_back(it_v->name);
        }
      }
            
      // This is all a bad hack, but if we add intrin.h , we should add it here, as there might be other forced includes for the compilation,
      // and the macro definitions if intrin.h shouldn't interfere with those.
      if (mode == wrapper_cl)
      {
        if (getenv("IN_COLUMBUS_REGTEST") == NULL) // We cannot allow this force include in the regtests as it will make it uncomparable among different PCs
        {
          analyzer_command_arguments.push_back("-D_CRT_RAND_S=");
          analyzer_command_arguments.push_back("/FIintrin.h");
          analyzer_command_arguments.push_back("-D__PRFCHWINTRIN_H");
        }
      }

      if (shouldUseDefaultDialect)
      {
        if(mode == wrapper_cl)
          analyzer_command_arguments.push_back("-std:" + defaultDialect);
        else
          analyzer_command_arguments.push_back("-std=" + defaultDialect);
        dialect = defaultDialect;
      }

      analyzer_command_arguments.insert(analyzer_command_arguments.end(), comp_extraparam.begin(), comp_extraparam.end());

      for (auto& argument : analyzer_command_arguments)
        argument = "-extra-arg=" + argument;

      analyzer_command_arguments.push_back("-extra-arg=-fsyntax-only");
      analyzer_command_arguments.push_back("-o=" + output);
      analyzer_command_arguments.push_back("-fltp=" + filter_path);

      if(comp_needstat)
        analyzer_command_arguments.push_back("-stat=" + wrapper_log_dir + DIRDIVSTRING + "statCAN.csv");

      analyzer_command_arguments.push_back("-extra-arg=-ferror-limit=500000");

      if (mode == wrapper_gcc)
      {
        analyzer_command_arguments.push_back("-config=" + wrapper_work_dir + DIRDIVSTRING + getCANIniNameForCompiler(wrappedExe));
        analyzer_command_arguments.push_back("-extra-arg=-nostdinc");
        analyzer_command_arguments.push_back("-extra-arg=-nostdinc++");
        analyzer_command_arguments.push_back("-extra-arg=-v");
      }

      analyzer_command_arguments.push_back(input);
      analyzer_command_arguments.push_back("--");

      string tmpdir = common::getCwd();
      writeInfoMsg(ABSTRACT_COMPILER, CMSG_CURRENT_WORKDIR, tmpdir.c_str());
      writeInfoMsg(ABSTRACT_COMPILER, CMSG_ANALYZER_WRAPPER_COMMAND, comp_tool.c_str());
      for (const auto& arg : analyzer_command_arguments)
      {
        writeInfoMsg(ABSTRACT_COMPILER, "%s", arg.c_str());
      }

      int ret = systemCall (comp_tool, analyzer_command_arguments);

      if(run_cppcheck && (lang == "c" || lang == "c++")) {
        vector<string> cppcheck_args;
        string cppcheck_cmd = wrapper_bin_dir + DIRDIVSTRING + "cppcheck" + DIRDIVSTRING + "cppcheck";

        cppcheck_args.push_back("--xml");
        cppcheck_args.push_back("--xml-version=2");

        cppcheck_args.push_back("--inline-suppr");
        cppcheck_args.push_back("--language=" + lang);

        cppcheck_args.push_back("--std=" + mapCompilerDialectToCppcheckDialect(dialect));

        cppcheck_args.push_back("--platform=" CPPCHECK_PLATFORM);
        cppcheck_args.push_back("--enable=warning,style");
      
        for (list<Argument>::iterator it_v = preprocArgs.prep_inc_files.begin(); it_v != preprocArgs.prep_inc_files.end(); ++it_v) {
          if(!it_v->name.empty()) {
            cppcheck_args.push_back("--include="+it_v->name);
          }
        }

        for (list<Argument>::iterator it_v = preprocArgs.prep_inc_paths.begin(); it_v != preprocArgs.prep_inc_paths.end(); ++it_v) {
          if(!it_v->name.empty()) {
            cppcheck_args.push_back("-I"+it_v->name);
          }
        }

        for (list<Argument>::iterator it_v = preprocArgs.prep_defs.begin(); it_v != preprocArgs.prep_defs.end(); ++it_v) {
          if(!it_v->name.empty()) {
            cppcheck_args.push_back("-D"+it_v->name);
          }
        }
        for (list<Argument>::iterator it_v = preprocArgs.prep_undefs.begin(); it_v != preprocArgs.prep_undefs.end(); ++it_v) {
          if(!it_v->name.empty()) {
            cppcheck_args.push_back("-U"+it_v->name);
          }
        }
        
        cppcheck_args.push_back(indepFullpath(input));

        string cppcheck_cmd_full = cppcheck_cmd;
        for(vector<string>::iterator it = cppcheck_args.begin(); it != cppcheck_args.end(); ++it)
          cppcheck_cmd_full += " " + *it;

        writeInfoMsg(ABSTRACT_COMPILER, CMSG_ANALYZER_WRAPPER_COMMAND, cppcheck_cmd_full.c_str());
        
        pathDeleteFile(output + ".err");
        int ret_cc = common::run(cppcheck_cmd, cppcheck_args, "", output + ".err");
        if(ret_cc != 0) {
          pathDeleteFile(output + ".err");
          writeErrorMsg(ABSTRACT_COMPILER, CMSG_CPPCHECK_FAILED, ret_cc);
          ok = false;
        }

      }

      if (ret != 0) {
        DirectoryFilter directoryFilter;
        directoryFilter.openFilterFile(filter_path);
        string canonicalFileName = common::pathCanonicalize(input.c_str());
        if (!directoryFilter.isFilteredOut(canonicalFileName))
        {
          writeErrorMsg(ABSTRACT_COMPILER, CMSG_TOOL_RETURNS, comp_tool.c_str(), ret);
          ok = false;
        } 
      } else {
        string ast_list = wrapper_log_dir + DIRDIVSTRING + "ast.list";
        string lockFile = getLockFileName(ast_list);
        ofstream astlist(ast_list.c_str(), ios::app);
        ofstream lock(lockFile.c_str());

        file_lock f_lock(lockFile.c_str());

        if (astlist.is_open()) {
          //sets an exclusive lock on the file (no other processes can read or write it)
          scoped_lock<file_lock> e_lock(f_lock);

          astlist << indepFullpath(output) << endl;
          astlist.flush();
          astlist.close();
        }
        lock.close();
      }
    }

    return ok;
  }
}
