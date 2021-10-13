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
#include "../../inc/abstractwrapper/AbstractLinker.h"
#include "../../inc/messages.h"
#include "../../../AnalyzerWrapperConfig/AnalyzerWrapperConfig.h"

#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/WriteMessage.h>
#include <fstream>

using namespace std;
using namespace common;
using namespace boost::interprocess;

#define LINKER_TOOL            "CANLink"
#define ABSTRACT_LINKER        "AbstractLinker"

namespace ColumbusWrappers {
  AbstractLinker::AbstractLinker(string configfile) : AbstractWrapper(configfile),
                                                      linker_needtorun(0),
                                                      linker_filterfile(),
                                                      linker_needstat(0),
                                                      linker_ml(2),
                                                      linker_paramtoskip(),
                                                      linker_numofparamtoskip(0),
                                                      linker_extraparam(),
                                                      linker_numofextraparam(0),
                                                      linking_mode(3),
                                                      link_tool()
                                                      
  {
    readConfig();
    link_tool = CL_PAR_PLUS + wrapper_bin_dir + DIRDIVSTRING + LINKER_TOOL + CL_PAR_PLUS;
  }


  void AbstractLinker::readConfig() {
    linker_needtorun = getConfigInt(LINKERSECTION, NEED_TO_RUN, 0);
    linker_filterfile = getConfigString(LINKERSECTION, LINK_FILTER_FILE, NULL);
    linker_needstat = getConfigInt(LINKERSECTION, NEED_STAT, 0);
    linker_ml = getConfigInt(LINKERSECTION, TOOL_MESSAGE_LEVEL, 2);

    linker_numofparamtoskip = getConfigInt(LINKERSECTION, NUM_OF_PARAM_TO_SKIP, 0);
    getParamToSkip(LINKERSECTION, linker_numofparamtoskip, linker_paramtoskip);

    linker_numofextraparam = getConfigInt(LINKERSECTION, NUM_OF_EXTRA_PARAM, 0);
    getExtraParam(LINKERSECTION, linker_numofextraparam, linker_extraparam);
    
    linking_mode = getConfigInt(ALLSECTION, LINKING_MODE, 3);
  }


  void AbstractLinker::examineLibs(LinkerArgs& linkerArgs, list<Argument>& libFiles) const {
    Argument libArg;

    for (list<Argument>::const_iterator it_files = linkerArgs.linker_lib_files.begin(); it_files != linkerArgs.linker_lib_files.end(); it_files++) {

      if (it_files->name != "") {

        libArg.position = it_files->position;
        writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_FINDING_LIBRARY, it_files->name.c_str());

        string file = it_files->name;
        string obj_file = file + ".obj";
        string lib_file = file + ".lib";
        string libfile = "lib" + it_files->name;
        string libfile_a = libfile + ".a";
        string libfile_so = libfile + ".so";
        bool found = false;

        if (common::pathFileExists(libfile_so, false)) {           //lib with .so
          found = true;
          libArg.name = libfile_so;
          libFiles.push_back(libArg);
        } else if (common::pathFileExists(libfile_a, false)) {     //lib with .a
          found = true;
          libArg.name = libfile_a;
          libFiles.push_back(libArg);
        } else if (common::pathFileExists(libfile, false)) {    //lib without .a or .so
          found = true;
          libArg.name = libfile;
          libFiles.push_back(libArg);
        } else if (common::pathFileExists(file, false)) {       //if .dll or .lib (originally with .dll or .lib extension)
          found = true;
          libArg.name = file;
          libFiles.push_back(libArg);
        } else if (common::pathFileExists(obj_file, false)) {   //if libname with .obj (originally without extension)
          found = true;
          libArg.name = obj_file;
          libFiles.push_back(libArg);
        } else if (common::pathFileExists(lib_file, false)) {   //if libname with .lib (originally without extension)
          found = true;
          libArg.name = lib_file;
          libFiles.push_back(libArg);
        } else {

          for (list<Argument>::const_iterator it_paths = linkerArgs.linker_lib_paths.begin(); it_paths != linkerArgs.linker_lib_paths.end(); it_paths++) {

            writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_FINDING_LIBRARY_IN_PATH, it_files->name.c_str(), it_paths->name.c_str());

            string out = indepFullpath(it_paths->name + DIRDIVSTRING + it_files->name);
            string obj_out = out + ".obj";
            string lib_out = out + ".lib";
            string libout = it_paths->name + DIRDIVSTRING + "lib" + it_files->name;
            string libout_so = libout + ".so";
            string libout_a = libout + ".a";

            if (common::pathFileExists(libout_so, false)) {
              found = true;
              libArg.name = libout_so;
              libFiles.push_back(libArg);
            } else if (common::pathFileExists(libout_a, false)) {
              found = true;
              libArg.name = libout_a;
              libFiles.push_back(libArg);
            } else if (common::pathFileExists(libout, false)) {
              found = true;
              libArg.name = libout;
              libFiles.push_back(libArg);
            } else if (common::pathFileExists(out, false)) {
              found = true;
              libArg.name = out;
              libFiles.push_back(libArg);
            } else if (common::pathFileExists(obj_out, false)) {
              found = true;
              libArg.name = obj_out;
              libFiles.push_back(libArg);
            } else if (common::pathFileExists(lib_out, false)) {
              found = true;
              libArg.name = lib_out;
              libFiles.push_back(libArg);
            }

          }

        }

        if (!found) {
          writeWarningMsg(ABSTRACT_LINKER, CMSG_LIB_FILE_NOT_FOUND, it_files->name.c_str());
        } else {
          writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LIB_FILE_FOUND, libArg.name.c_str());
        }

      }

    }
  }



  bool AbstractLinker::createInputNames(const list<Argument>& i_files, list<Argument>& output_paramlist) const {
    bool ret = false;

    Argument fileArg;
    for (list<Argument>::const_iterator it = i_files.begin(); it != i_files.end(); it++) {
      writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_CREATING_INPUT, it->name.c_str());
      string input = it->name;
      fileArg.position = it->position;
      replaceQuoteForQuoteWithBackslash(input);

      insertDir(input, false);

      if (isObjectFile(input)) {
        input += ".ast";
        fileArg.name = input;
        output_paramlist.push_back(fileArg);
        ret = true;
      } else if (isArchiveFile(input)) {
        if (linking_mode == 3) {
          input += ".aast";
          fileArg.name = input;
          output_paramlist.push_back(fileArg);
          ret = true;
        } else {
          writeInfoMsg(ABSTRACT_LINKER, CMSG_INFO_STATIC_LIB_IS_NOT_LINKED_IN, input.c_str(), linking_mode);
        }
      } else {
        writeInfoMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_UNKNOWN_INPUT, input.c_str());
      }
    }

    return ret;
  }


  bool AbstractLinker::createInputNamesFromCANOutput(const list<Argument>& i_files, list<Argument>& output_paramlist) const {
    bool ret = false;

    Argument fileArg;
    for (list<Argument>::const_iterator it = i_files.begin(); it != i_files.end(); it++) {
      writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_CREATING_INPUT_FROM_CAN, it->name.c_str());
      string input = it->name;
      fileArg.position = it->position;
      replaceQuoteForQuoteWithBackslash(input);

      fileArg.name = input;
      output_paramlist.push_back(fileArg);
      ret = true;
    }

    return ret;
  }



  bool AbstractLinker::executeLinker(LinkerArgs& linkerArgs, list<Argument>& cmp_generated_files) const {
    if (linkerArgs.linker_input_files.empty() && cmp_generated_files.empty()) {
      writeWarningMsg(ABSTRACT_LINKER, CMSG_LINKER_HAS_NO_INPUT);
      return true;
    }
    if (!linkerArgs.linking) {
      writeWarningMsg(ABSTRACT_LINKER, CMSG_NO_NEED_TO_LINK_BY_PARAMS);
      return true;
    }
    if (!linker_needtorun) {
      writeWarningMsg(ABSTRACT_LINKER, CMSG_NO_NEED_TO_LINK_BY_CONFIG);
      return true;
    }

    list<Argument> output_paramlist;        // list for ordered CANLink commandline

    writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_EXECUTION, link_tool.c_str());

    for (list<Argument>::const_iterator it_p = linkerArgs.linker_args.begin(); it_p != linkerArgs.linker_args.end(); it_p++) {
      writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_ARGUMENT, it_p->name.c_str());
      Argument a = *it_p;
      a.name = CL_PAR_PLUS + it_p->name + CL_PAR_PLUS;
      output_paramlist.push_back(a);
    }

    string output;
    Argument outputFileArg;
    if (linkerArgs.linker_output_file.name == "") {
      writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_OUTPUT);
      output = indepFullpath("a.out") + ".component";
      outputFileArg.position = linkerArgs.max_arg + 1;
    } else {
      writeDebugMsg(ABSTRACT_LINKER, CMSG_DEBUG_LINKER_OUTPUT_FROM_PARAM, linkerArgs.linker_output_file.name.c_str());
      output = indepFullpath(linkerArgs.linker_output_file.name) + ".component";
      outputFileArg.position = linkerArgs.linker_output_file.position;
    }
    replaceQuoteForQuoteWithBackslash(output);
    insertDir(output, true);
    outputFileArg.name = "-out:" CL_PAR_PLUS + output + CL_PAR_PLUS;
    output_paramlist.push_back(outputFileArg);



    list<Argument> templist;
    examineLibs(linkerArgs, templist);
    list<Argument> inputFileList;

    bool existInput = createInputNames(templist, inputFileList);
    existInput |= createInputNames(linkerArgs.linker_input_files, inputFileList);
    existInput |= createInputNamesFromCANOutput(cmp_generated_files, inputFileList);

    if (!existInput) {
      writeWarningMsg(ABSTRACT_LINKER, CMSG_LINKER_NO_INPUT_FILES_CREATED);
      return true;
    }

    inputFileList.sort(compareArguments);
    string currentWorkDir = common::getCwd();
    string inputfile_list = wrapper_temp_dir + DIRDIVSTRING + common::toString(getCurrentProcessId()) + "input.list";
    for (list<Argument>::iterator it_inputfiles = inputFileList.begin(); it_inputfiles != inputFileList.end(); ++it_inputfiles) {
      ofstream inputlist(inputfile_list.c_str(), ios::app);
      if (inputlist.is_open()) {
        inputlist << indepFullpath(it_inputfiles->name) << endl;
        inputlist.flush();
        inputlist.close();
      }
    }

    string sys_cmd = link_tool;
    output_paramlist.sort(compareArguments);
    for (list<Argument>::iterator it_v = output_paramlist.begin(); it_v != output_paramlist.end(); it_v++) {
      if(!it_v->name.empty()) {
        sys_cmd += " ";
        sys_cmd += it_v->name;
      }
    }

    sys_cmd += " " CL_PAR_PLUS "-ml:" + toString(linker_ml) + CL_PAR_PLUS;
    if (linker_needstat) {
      string statfile = wrapper_log_dir + DIRDIVSTRING + "statCANLink.csv";
      replaceQuoteForQuoteWithBackslash(statfile);
      sys_cmd += " " CL_PAR_PLUS "-stat:" +statfile + CL_PAR_PLUS;
    }
    if (!linker_filterfile.empty()) {
      writeDebugMsg(ABSTRACT_LINKER, CMSG_LINKER_FILTER_FILE, linker_filterfile.c_str());
      sys_cmd += " " CL_PAR_PLUS "-filter:" + linker_filterfile + CL_PAR_PLUS;
    }

    string extraparams = "";
    if (!linker_extraparam.empty()) {
      vector<string>::const_iterator p_it;
      for (p_it = linker_extraparam.begin(); p_it != linker_extraparam.end(); p_it++) {
        extraparams += " " CL_PAR_PLUS + *p_it + CL_PAR_PLUS;
      }
    }

    sys_cmd += " " + extraparams;

    sys_cmd += " " CL_PAR_PLUS "-ilist:" + inputfile_list + CL_PAR_PLUS;

    writeInfoMsg(ABSTRACT_LINKER, CMSG_CURRENT_WORKDIR, currentWorkDir.c_str());
    writeInfoMsg(ABSTRACT_LINKER, CMSG_ANALYZER_WRAPPER_COMMAND, sys_cmd.c_str());
    int ret = systemCall(sys_cmd);
    if (ret != 0) {
      writeErrorMsg(ABSTRACT_LINKER, CMSG_TOOL_RETURNS, link_tool.c_str(), ret);
      return false;
    } else {
      string f, e;
      if (common::splitExt(output, f, e)) {
        string component_list = wrapper_log_dir + DIRDIVSTRING + "component.list";
        string lockFile = getLockFileName(component_list);
        ofstream componentlist(component_list.c_str(), ios::app);
        ofstream lock(lockFile.c_str());

        file_lock f_lock(lockFile.c_str());

        if (componentlist.is_open()) {
          //sets an exclusive lock on the file (no other processes can read or write it)
          scoped_lock<file_lock> e_lock(f_lock);

          componentlist << indepFullpath(output) << endl;
          componentlist.flush();
          componentlist.close();
        }
        lock.close();
      }
      systemCall(DEL_COMMAND " " CL_PAR_PLUS + inputfile_list + CL_PAR_PLUS);
    }

    return true;
  }

}
