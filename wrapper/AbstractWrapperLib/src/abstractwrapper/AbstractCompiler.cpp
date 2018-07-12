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
#include "AbstractWrapperLib/inc/abstractwrapper/AbstractCompiler.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <AnalyzerWrapperConfig/AnalyzerWrapperConfig.h>

#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/WriteMessage.h>
#include <fstream>

using namespace std;
using namespace common;
using namespace boost::interprocess;

#define COMPILER_TOOL            "CAN"
#define ABSTRACT_COMPILER        "AbstractCompiler"
#define PREDEFINED_MACROS_FULL_FILENAME "predefined_macros_full.txt"

namespace ColumbusWrappers {

  AbstractCompiler::AbstractCompiler(string configfile) : AbstractWrapper(configfile),
                                                          comp_needtorun(0),
                                                          comp_needstat(0),
                                                          run_cppcheck(0),
                                                          comp_ml(2),
                                                          comp_paramtoskip(),
                                                          comp_numofparamtoskip(0),
                                                          comp_extraparam(),
                                                          comp_numofextraparam(0),
                                                          comp_tool()
  {
    readConfig();
    replaceQuoteForQuoteWithBackslash(wrapper_bin_dir);
    comp_tool = CL_PAR_PLUS + wrapper_bin_dir + DIRDIVSTRING + "CAN" + CL_PAR_PLUS;
  }


  void AbstractCompiler::readConfig() {
    comp_needtorun = getConfigInt(COMPILERSECTION, NEED_TO_RUN, 0);
    instrument_mode = getConfigInt(COMPILERSECTION, INST_MODE, 0);
    comp_needstat = getConfigInt(COMPILERSECTION, NEED_STAT, 0);
    run_cppcheck = getConfigInt(COMPILERSECTION, RUN_CPPCHECK, 0);
    comp_ml = getConfigInt(COMPILERSECTION, TOOL_MESSAGE_LEVEL, 2);

    comp_numofparamtoskip = getConfigInt(COMPILERSECTION, NUM_OF_PARAM_TO_SKIP, 0);
    getParamToSkip(COMPILERSECTION, comp_numofparamtoskip, comp_paramtoskip);

    comp_numofextraparam = getConfigInt(COMPILERSECTION, NUM_OF_EXTRA_PARAM, 0);
    getExtraParam(COMPILERSECTION, comp_numofextraparam, comp_extraparam);
  }


  void AbstractCompiler::concatenatePrefixAndParams(const char* prefix, const list<Argument>& input_list, list<Argument>& output_paramlist, bool separately) const {
    for (list<Argument>::const_iterator it = input_list.begin(); it != input_list.end(); it++) {
      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_ARGUMENT_WITH_PARAM, prefix, it->name.c_str());
      Argument a = *it;
      string param = it->name;
      replaceQuoteForQuoteWithBackslash(param);
      string actParam = "";
      actParam += prefix;
      if (separately) {
        actParam += " ";
      }
      actParam += CL_PAR_PLUS + param + CL_PAR_PLUS;
      a.name = actParam;
      output_paramlist.push_back(a);
    }
  }



  bool AbstractCompiler::executeInstrumenter(list<string> inputArgs, CompilerArgs& compArgs, LinkerArgs& linkArgs) const {
    if (compArgs.comp_input_files.size() + linkArgs.linker_input_files.size() == 0) {
      string msg = prep_instrument ? "PreInstrumenter" : "Instrumenter";
      writeWarningMsg(ABSTRACT_COMPILER, CMSG_INSTRUMENTER_HAS_NO_INPUT, msg.c_str());
      return false;
    }


    if (!compArgs.compiling) {
      writeWarningMsg(ABSTRACT_COMPILER, "Call the original ones");
  
      std::string out;
      std::string err;
      if (common::run(wrappedExe,input_paramvector,out,err)) {
        printf("The orginal program fail %s err:%s",out.c_str(),err.c_str());
      }

      return true;
    }
    if (!comp_needtorun) {
      writeWarningMsg(ABSTRACT_COMPILER, CMSG_NO_NEED_TO_COMPILE_BY_CONFIG);
      return false;
    }
    
    string include_header = "instrumentHeader.h";

    // creating preprocessor and compiler command line
    string comp_cmd = "";
    string prep_cmd = "";
    bool isOut = false; //some output option such as -o or /Fo
    for (list<string>::const_iterator it_i = inputArgs.begin(); it_i != inputArgs.end(); it_i++) {
      string inputCompArg = *it_i;
      string inputPrepArg = *it_i;
      bool isInput = false;   //input file
      bool isOutput = false;  //output file

      for (list<Argument>::const_iterator it_f = compArgs.comp_input_files.begin(); it_f != compArgs.comp_input_files.end(); it_f++) {
        string filename = it_f->name;
        string lang = it_f->lang;
        string prepFile = "";

        if (inputCompArg == filename) {
          isInput = true;
          string tmpfile, tmpext;
          splitExt(inputCompArg, tmpfile, tmpext);
          if (lang == "c") {
            prepFile = tmpfile + ".i";
          } else if (lang == "cpp") {
            if (mode == wrapper_cl) {
              prepFile = "/Tp" + tmpfile + ".i";
            } else {
              prepFile = tmpfile + ".i";
            }
          }
        } else {
          if (mode == wrapper_cl) {
            string tmpfile, tmpext;
            splitExt(inputCompArg, tmpfile, tmpext);
            if (inputCompArg == "/Tp" + filename) {
              isInput = true;
              prepFile = tmpfile + ".i";
            } else if (inputCompArg == "/Tc" + filename) {
              isInput = true;
              prepFile = tmpfile + ".i";
            }
          }
        }

        if (!prepFile.empty()) {
          inputCompArg = prepFile;
        }
      } //for

      if (!inputCompArg.empty()) {
        string remain;
        if (mode == wrapper_cl && (common::isPrefix(inputCompArg, "/Y", remain) || common::isPrefix(inputCompArg, "/Fp", remain))) {
          continue;
        }
        replaceQuoteForQuoteWithBackslash(inputCompArg);
        comp_cmd += " " CL_PAR_PLUS + inputCompArg + CL_PAR_PLUS;
      }

      if (isInput) {
        continue;
      }

      if (mode == wrapper_cl) {
        string tmpInputArg = inputPrepArg;
        common::stringLower(tmpInputArg);
        string compout = compArgs.comp_output_file.name;
        string linkout = linkArgs.linker_output_file.name;
        if (inputPrepArg == "/Fo") {
          isOut = true;
        } else if (tmpInputArg == common::stringLower("/Fo"+compout)) {
          isOutput = true;
          isOut = false;
        } else if (tmpInputArg == common::stringLower("/out:"+linkout)) {
          isOutput = true;
          isOut = false;
        } else if (tmpInputArg == common::stringLower("/Fe"+linkout)) {
          isOutput = true;
          isOut = false;
        }
      } else if ((mode == wrapper_gcc) || (mode == AbstractWrapper::wrapper_armcc)) {
        if (inputPrepArg == "-o") {
          isOut = true;
        } else if (inputPrepArg == "-o"+compArgs.comp_output_file.name) {
          isOutput = true;
          isOut = false;
        } else if (inputPrepArg == "-o"+linkArgs.linker_output_file.name) {
          isOutput = true;
          isOut = false;
        } else if (inputPrepArg == compArgs.comp_output_file.name && isOut) {
          isOutput = true;
          isOut = false;
        } else if (inputPrepArg == linkArgs.linker_output_file.name && isOut) {
          isOutput = true;
          isOut = false;
        }
      }

      if (!isOut && !isOutput) {
        writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_PREPROCESSOR_ARGUMENT, inputPrepArg.c_str());
        replaceQuoteForQuoteWithBackslash(inputPrepArg);
        prep_cmd += " " CL_PAR_PLUS + inputPrepArg + CL_PAR_PLUS;
      }
    } //for

    if (!compArgs.comp_input_files.empty()) {
      // run preprocessing 
      for(list<Argument>::const_iterator it_f = compArgs.comp_input_files.begin(); it_f != compArgs.comp_input_files.end(); it_f++) {
        string input = it_f->name;
        string lang = it_f->lang;
        string prep_file;
        string cmd;

        writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_PREPROCESSOR_INPUT_FILE, input.c_str());

        string filename, ext;
        splitExt(input, filename, ext);
        prep_file = filename + ".i";
        string instr_out = prep_file;
        replaceQuoteForQuoteWithBackslash(prep_file);
        replaceQuoteForQuoteWithBackslash(input);

        if (mode == wrapper_cl) {
          cmd = " -E";
          if (!prep_instrument ) {
            cmd += " -FI " CL_PAR_PLUS + wrapper_work_dir + DIRDIVSTRING + include_header + CL_PAR_PLUS;
          }
        } else if (mode == wrapper_armcc) {
              //--preinclude
          cmd = "-o " CL_PAR_PLUS + prep_file + CL_PAR_PLUS " -E";
          if (!prep_instrument) {
            cmd += " --preinclude " CL_PAR_PLUS + wrapper_work_dir + DIRDIVSTRING + include_header + CL_PAR_PLUS;
          }

        } else  {
          cmd = "-o " CL_PAR_PLUS + prep_file + CL_PAR_PLUS " -E";
          if (!prep_instrument) {
            cmd += " -include " CL_PAR_PLUS + wrapper_work_dir + DIRDIVSTRING + include_header + CL_PAR_PLUS;
          }

        }

        cmd += " " CL_PAR_PLUS + input + CL_PAR_PLUS;

        cmd = wrappedExe + " " + cmd + " " + prep_cmd;

        string tmpdir = common::getCwd();
        writeInfoMsg(ABSTRACT_COMPILER, CMSG_CURRENT_WORKDIR, tmpdir.c_str());
        writeInfoMsg(ABSTRACT_COMPILER, CMSG_ANALYZER_WRAPPER_COMMAND, cmd.c_str());
        int ret_prep = systemCall (cmd, prep_file);
        if (ret_prep != 0) {
          writeErrorMsg(ABSTRACT_COMPILER, ABSTRACT_COMPILER, wrappedExe.c_str(), ret_prep);
          return false;
        }

        if (!prep_instrument) {
          // run instrumenter
          string index_file = "instrument.index";
          systemCall(MOVE_COMMAND + prep_file + " " + prep_file + "_orig");
          string instr_cmd = wrapper_bin_dir + DIRDIVSTRING + "CppInstrumenter " +"-mode "+toString(instrument_mode) + " -indexFile " 
            + CL_PAR_PLUS + wrapper_work_dir + DIRDIVSTRING + index_file 
            + CL_PAR_PLUS " -o " + CL_PAR_PLUS + instr_out + CL_PAR_PLUS + " " 
            + CL_PAR_PLUS + prep_file + "_orig" 
            + CL_PAR_PLUS " " CL_PAR_PLUS "-ml:" + toString(comp_ml) + CL_PAR_PLUS;
          writeInfoMsg(ABSTRACT_COMPILER, CMSG_ANALYZER_WRAPPER_COMMAND, instr_cmd.c_str());
          int ret_instr = systemCall (instr_cmd);
          if (ret_instr != 0) {
            writeErrorMsg(ABSTRACT_COMPILER, ABSTRACT_COMPILER, "CppInstrumenter", ret_instr);
            return false;
          }
        }

      } // for
    } // if

    if (!prep_instrument) {
      // run compiler
      comp_cmd = wrappedExe + " " + comp_cmd;
      if (mode == wrapper_cl) {
        comp_cmd += " /link Ws2_32.lib";
      } else if (mode == wrapper_gcc) {
        //comp_cmd += " -lpthread";
      }
      string tmpdir = common::getCwd();
      writeInfoMsg(ABSTRACT_COMPILER, CMSG_CURRENT_WORKDIR, tmpdir.c_str());
      writeInfoMsg(ABSTRACT_COMPILER, CMSG_ANALYZER_WRAPPER_COMMAND, comp_cmd.c_str());
      int ret_comp = systemCall (comp_cmd);
      if (ret_comp != 0) {
        writeErrorMsg(ABSTRACT_COMPILER, ABSTRACT_COMPILER, wrappedExe.c_str(), ret_comp);
        return false;
      }
    }

    return true;
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

    for (list<Argument>::const_iterator it_p = compArgs.comp_args.begin(); it_p != compArgs.comp_args.end(); it_p++) {
      if (it_p->name.empty())
        continue;
      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_COMPILER_ARGUMENT, it_p->name.c_str());
      Argument a = *it_p;
      replaceQuoteForQuoteWithBackslash(a.name);
      a.name = CL_PAR_PLUS + a.name + CL_PAR_PLUS;
      output_paramlist.push_back(a);
      if(it_p->name == "-std:c89") {
        dialect = "c89";
      } else if(it_p->name == "-std:c99") {
        dialect = "c99";
      } else if(it_p->name == "-std:c++03") {
        dialect = "c++03";
      } else if(it_p->name == "-std:c++11") {
        dialect = "c++11";
      }
    }

    string temp_args = "";
    temp_args += " " CL_PAR_PLUS "-ml:" + toString(comp_ml) + CL_PAR_PLUS;

    if(comp_needstat) {
      string statfile = wrapper_log_dir + DIRDIVSTRING + "statCAN.csv";
      replaceQuoteForQuoteWithBackslash(statfile);
      temp_args += " " CL_PAR_PLUS "-stat:" + statfile + CL_PAR_PLUS;
    }

    if (mode == wrapper_cl) {
      concatenatePrefixAndParams("-FI", preprocArgs.prep_inc_files, output_paramlist);
    } else if (mode == wrapper_gcc) {
      concatenatePrefixAndParams("-include", preprocArgs.prep_inc_files, output_paramlist);
    }
    concatenatePrefixAndParams("-I", preprocArgs.prep_inc_paths, output_paramlist);
    concatenatePrefixAndParams("-D", preprocArgs.prep_defs, output_paramlist);
    concatenatePrefixAndParams("-U", preprocArgs.prep_undefs, output_paramlist);
    concatenatePrefixAndParams("-isystem", preprocArgs.prep_isystem_dirs, output_paramlist);

    for (list<Argument>::const_iterator it_a = preprocArgs.prep_args.begin(); it_a != preprocArgs.prep_args.end(); it_a++) {
      writeDebugMsg(ABSTRACT_COMPILER, CMSG_DEBUG_PREPROCESSOR_ARGUMENT, it_a->name.c_str());
      Argument a = *it_a;
      string param = it_a->name;
      string lang = it_a->lang;
      replaceQuoteForQuoteWithBackslash(a.name);
      a.name = CL_PAR_PLUS + a.name + CL_PAR_PLUS;
      output_paramlist.push_back(a);
    }

    string canconfig = "";
    if (!configdir.empty()) {
      canconfig = "-feconfigdir:" + configdir;
    } else {
      canconfig = "-feconfigdir:" + wrapper_work_dir;
    }

    string extraparams = "";
    if (!comp_extraparam.empty()) {
      vector<string>::const_iterator p_it;
      for (p_it = comp_extraparam.begin(); p_it != comp_extraparam.end(); p_it++) {
        extraparams += " " CL_PAR_PLUS + *p_it + CL_PAR_PLUS;
      }
    }

    bool ok = true;

    for(list<Argument>::const_iterator it_f = compArgs.comp_input_files.begin(); it_f != compArgs.comp_input_files.end(); it_f++) {
      Argument outputFileArg;
      string input = it_f->name;
      string lang = it_f->lang;
      int in_pos = it_f->position;
      string output;

      if (prep_instrument) {
        string filename, ext;
        splitExt(input, filename, ext);
        input = filename + ".i";
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
        output += ".csi";
        outputFileArg.name = output;
        outputFileArg.position = compArgs.comp_output_file.position;
      } else {
        string file, ext;
        common::splitExt(input,file,ext);
        output  = file + getObjectFileExtension()+".csi";
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
      string outputfile = output;
      output = CL_PAR_PLUS "-out:" + output + CL_PAR_PLUS;
      replaceQuoteForQuoteWithBackslash(input);

      output_paramlist.sort(compareArguments);
      string sys_cmd = comp_tool + " " + temp_args;
      for (list<Argument>::iterator it_v = output_paramlist.begin(); it_v != output_paramlist.end(); it_v++) {
        if(!it_v->name.empty()) {
          if (lang == "c" && (it_v->name == CL_PAR_PLUS "-edg:--no_exceptions" CL_PAR_PLUS ||
                              it_v->name == CL_PAR_PLUS "-edg:--exceptions" CL_PAR_PLUS || 
                              it_v->name == CL_PAR_PLUS "-edg:--wchar_t_keyword" CL_PAR_PLUS ||
                              it_v->name == CL_PAR_PLUS "-edg:--old_for_init" CL_PAR_PLUS ||
                              it_v->name == CL_PAR_PLUS "-edg:--auto_type" CL_PAR_PLUS)) {
            continue;
          }
          sys_cmd += " ";
          sys_cmd += it_v->name;
        }
      }
            
      string lang_option = "";
      lang_option = " " CL_PAR_PLUS "-lang:" + lang + CL_PAR_PLUS;

      sys_cmd += lang_option;
      sys_cmd += " " CL_PAR_PLUS + canconfig + CL_PAR_PLUS;
      sys_cmd += " " + extraparams;
      sys_cmd += " " CL_PAR_PLUS + input + CL_PAR_PLUS + " " + output;

      if (mode == wrapper_cl) {
        if (output_dir[output_dir.length()-1] == '\\' || output_dir[output_dir.length()-1] == '/') {
          output_dir = output_dir.substr(0, output_dir.length()-1);
        }
        if (output_dir.empty()) {
          output_dir = ".";
        }
        replaceQuoteForQuoteWithBackslash(output_dir);
        sys_cmd += " " CL_PAR_PLUS "-edg:--import_dir" CL_PAR_PLUS;
        sys_cmd += " " CL_PAR_PLUS "-edg:" + common::indep_fullpath(output_dir) + CL_PAR_PLUS;
      }

      string tmpdir = common::getCwd();
      writeInfoMsg(ABSTRACT_COMPILER, CMSG_CURRENT_WORKDIR, tmpdir.c_str());
      writeInfoMsg(ABSTRACT_COMPILER, CMSG_ANALYZER_WRAPPER_COMMAND, sys_cmd.c_str());
      int ret = systemCall (sys_cmd);

      if(run_cppcheck) {
        vector<string> cppcheck_args;
        string cppcheck_cmd = wrapper_bin_dir + DIRDIVSTRING + "cppcheck" + DIRDIVSTRING + "cppcheck";

        cppcheck_args.push_back("--xml");
        cppcheck_args.push_back("--xml-version=2");

        cppcheck_args.push_back("--inline-suppr");

        string language = ((lang=="c")?"c":"c++");

        cppcheck_args.push_back("--language=" + language);

        if(lang == "c" && dialect == "c++11")
          dialect = "c11";

        if(dialect == "") {
          if(lang == "c")
            dialect = "c89";
          else
            dialect = "c++03";
        }
        cppcheck_args.push_back("--std="+dialect);
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
        for (list<Argument>::iterator it_v = preprocArgs.prep_isystem_dirs.begin(); it_v != preprocArgs.prep_isystem_dirs.end(); ++it_v) {
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
        
        const string predefinedMacrosFileName =  wrapper_work_dir + DIRDIVSTRING PREDEFINED_MACROS_FULL_FILENAME;
        ifstream predefinedMacrosFile(predefinedMacrosFileName.c_str());
        if(predefinedMacrosFile.is_open()) {
          string line;
          while(getline(predefinedMacrosFile, line)) {
            for(std::string::iterator it = line.begin(); it != line.end(); ++it) {
              if(*it == ' ' && (it+1) != line.end()) {
                *it = '=';
              }
            }
            cppcheck_args.push_back("-D" CL_PAR_PLUS + line + CL_PAR_PLUS);
          }
          predefinedMacrosFile.close();
        }
        
        cppcheck_args.push_back(indepFullpath(input));

        string cppcheck_cmd_full = cppcheck_cmd;
        for(vector<string>::iterator it = cppcheck_args.begin(); it != cppcheck_args.end(); ++it)
          cppcheck_cmd_full += " " + *it;

        writeInfoMsg(ABSTRACT_COMPILER, CMSG_ANALYZER_WRAPPER_COMMAND, cppcheck_cmd_full.c_str());
        
        pathDeleteFile(outputfile + ".err");
        int ret_cc = common::run(cppcheck_cmd, cppcheck_args, "", outputfile + ".err");
        if(ret_cc != 0) {
          pathDeleteFile(outputfile + ".err");
          writeErrorMsg(ABSTRACT_COMPILER, CMSG_CPPCHECK_FAILED, ret_cc);
          ok = false;
        }

      }

      if (ret != 0) {
        writeErrorMsg(ABSTRACT_COMPILER, CMSG_TOOL_RETURNS, comp_tool.c_str(), ret);
        ok = false;
      } else {
        string csi_list = wrapper_log_dir + DIRDIVSTRING + "csi.list";
        string lockFile = getLockFileName(csi_list);
        ofstream csilist(csi_list.c_str(), ios::app);
        ofstream lock(lockFile.c_str());

        file_lock f_lock(lockFile.c_str());

        if (csilist.is_open()) {
          //sets an exclusive lock on the file (no other processes can read or write it)
          scoped_lock<file_lock> e_lock(f_lock);

          csilist << indepFullpath(outputfile) << endl;
          csilist.flush();
          csilist.close();
        }
        lock.close();
      }
    }

    return ok;
  }
}
