/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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
#include "../../inc/abstractwrapper/AbstractArchive.h"
#include "../../inc/messages.h"
#include <AnalyzerWrapperConfig/AnalyzerWrapperConfig.h>

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

#define LIB_TOOL            "CANLib"
#define ABSTRACT_ARCHIVE    "AbstractArchive"

namespace ColumbusWrappers {
  AbstractArchive::AbstractArchive(string configfile) : AbstractWrapper(configfile),
                                                        archive_needtorun(0),
                                                        archive_needstat(0),
                                                        archive_ml(2),
                                                        archive_paramtoskip(),
                                                        archive_numofparamtoskip(0),
                                                        archive_extraparam(),
                                                        archive_numofextraparam(0),
                                                        archive_tool()
  {
    readConfig();
    archive_tool = CL_PAR_PLUS + wrapper_bin_dir + DIRDIVSTRING + LIB_TOOL + CL_PAR_PLUS;
  }

  void AbstractArchive::readConfig() {
    archive_needtorun = getConfigInt(ARCHIVESECTION, NEED_TO_RUN, 0);
    archive_needstat = getConfigInt(ARCHIVESECTION, NEED_STAT, 0);
    archive_ml = getConfigInt(ARCHIVESECTION, TOOL_MESSAGE_LEVEL, 2);

    archive_numofparamtoskip = getConfigInt(ARCHIVESECTION, NUM_OF_PARAM_TO_SKIP, 0);
    getParamToSkip(ARCHIVESECTION, archive_numofparamtoskip, archive_paramtoskip);

    archive_numofextraparam = getConfigInt(ARCHIVESECTION, NUM_OF_EXTRA_PARAM, 0);
    getExtraParam(ARCHIVESECTION, archive_numofextraparam, archive_extraparam);
  }


// CANLib archive_mode [modifiers] [operations] archive_file [position_asg] input_files
  bool AbstractArchive::executeArchive(ArchiveArgs& arArgs) const {
    if (arArgs.input_files.empty() && arArgs.asgMemberName.empty() && !arArgs.delete_or_extract) {
      writeWarningMsg(ABSTRACT_ARCHIVE, CMSG_ARCHIVE_HAS_NO_INPUT);
      return true;
    }
    if (!archive_needtorun) {
      writeWarningMsg(ABSTRACT_ARCHIVE, CMSG_ARCHIVE_NO_NEED_TO_RUN);
      return true;
    }

    writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_EXECUTION, archive_tool.c_str(), arArgs.archive_mode.c_str());

    string sys_cmd = archive_tool;

    sys_cmd += " " CL_PAR_PLUS + arArgs.archive_mode + CL_PAR_PLUS;

    for (list<string>::const_iterator it_m = arArgs.archive_modifiers.begin(); it_m != arArgs.archive_modifiers.end(); it_m++) {
      writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_MODIFIER, it_m->c_str());
      sys_cmd += " " CL_PAR_PLUS + *it_m + CL_PAR_PLUS;
    }

    for (list<string>::const_iterator it_o = arArgs.archive_operations.begin(); it_o != arArgs.archive_operations.end(); it_o++) {
      writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_OPERATION, it_o->c_str());
      sys_cmd += " " CL_PAR_PLUS + *it_o + CL_PAR_PLUS;
    }

    string output;
    if (!arArgs.no_output) {
      output = arArgs.archive_file;
    } else {
      output = arArgs.first_input;
      string tmpdir, tmpfile;
      common::splitPath(output, tmpdir, tmpfile);
      output = tmpfile;
    }
    writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_OUTPUT, output.c_str());
    replaceQuoteForQuoteWithBackslash(output);
    insertDir(output, true);
    if (arArgs.need_create) {
      if (!arArgs.archive_mode.compare("-w")) {
        sys_cmd += " " CL_PAR_PLUS "-a" CL_PAR_PLUS;
      }
      sys_cmd += " " CL_PAR_PLUS "-c" CL_PAR_PLUS;
    }
 
    if (arArgs.original_dates) {
      
      sys_cmd += " " CL_PAR_PLUS "-t" CL_PAR_PLUS;
    }


    if (!arArgs.archive_mode.compare("-w") && arArgs.delete_or_extract ) {

      if (!arArgs.asgMemberName.empty()) {
        sys_cmd += " " CL_PAR_PLUS;
        sys_cmd += arArgs.asgMemberName + ".csi";
        sys_cmd += CL_PAR_PLUS;
      }
    }

    sys_cmd += " " CL_PAR_PLUS + output + ".acsi" CL_PAR_PLUS;

    if (!arArgs.archive_mode.compare("-w") && arArgs.delete_or_extract && !arArgs.asg_file.empty()) {
      sys_cmd += " " CL_PAR_PLUS;
      sys_cmd += "-out";
      sys_cmd += CL_PAR_PLUS;
    }

    if (!arArgs.asg_file.empty()) {
      writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_POSITION_ASG, arArgs.asg_file.c_str());
      sys_cmd += " " CL_PAR_PLUS + objectNameToCsiName(arArgs.asg_file ) + CL_PAR_PLUS;
    }

    list<string> inputFileList;
    for (list<string>::const_iterator it_i = arArgs.input_files.begin(); it_i != arArgs.input_files.end(); it_i++) {
      writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_INPUT, it_i->c_str());
      
      inputFileList.push_back( arArgs.delete_or_extract ? *it_i + ".csi": objectNameToCsiName( *it_i ) );

    }

    string currentWorkDir = common::getCwd();
    string inputfile_list = wrapper_temp_dir + DIRDIVSTRING + common::toString(getCurrentProcessId()) + "input.list";
    for (list<string>::iterator it_inputfiles = inputFileList.begin(); it_inputfiles != inputFileList.end(); ++it_inputfiles) {
      ofstream inputlist(inputfile_list.c_str(), ios::app);
      if (inputlist.is_open()) {
        if (!arArgs.delete_or_extract){
          inputlist << indepFullpath(*it_inputfiles) << endl;
        } else {
          inputlist << *it_inputfiles << endl;
        }
        inputlist.flush();
        inputlist.close();
      }
    }

    if(archive_needstat) {
      string statfile = wrapper_log_dir + DIRDIVSTRING + "statCANLib.csv";
      replaceQuoteForQuoteWithBackslash(statfile);
      sys_cmd += " " CL_PAR_PLUS "-stat:" + statfile + CL_PAR_PLUS;
    }

    sys_cmd += " -ml:" + toString(archive_ml);

    sys_cmd += " " CL_PAR_PLUS "-ilist:" + inputfile_list + CL_PAR_PLUS;


     

    if ((mode == wrapper_gcc || mode == wrapper_ar) && arArgs.delete_or_extract &&  arArgs.archive_operations.front() == "-e") {
      sys_cmd += " " CL_PAR_PLUS;
      sys_cmd += "-out";
      sys_cmd += CL_PAR_PLUS;

      sys_cmd += " " CL_PAR_PLUS;
      sys_cmd += outputdir;
      sys_cmd += CL_PAR_PLUS;
      makeDirectory(outputdir);
    }


    writeInfoMsg(ABSTRACT_ARCHIVE, CMSG_CURRENT_WORKDIR, currentWorkDir.c_str());
    writeInfoMsg(ABSTRACT_ARCHIVE, CMSG_ANALYZER_WRAPPER_COMMAND, sys_cmd.c_str());
    int ret = systemCall(sys_cmd);
    if (ret != 0) {
      writeErrorMsg(ABSTRACT_ARCHIVE, CMSG_TOOL_RETURNS, archive_tool.c_str(), ret);
      return false;
    } else {
      string acsi_list = wrapper_log_dir + DIRDIVSTRING + "acsi.list";
      string lockFile = getLockFileName(acsi_list);
      ofstream acsilist(acsi_list.c_str(), ios::app);
      ofstream lock(lockFile.c_str());

      file_lock f_lock(lockFile.c_str());

      if (acsilist.is_open()) {
        //sets an exclusive lock on the file (no other processes can read or write it)
        scoped_lock<file_lock> e_lock(f_lock);

        acsilist << indepFullpath(output+".acsi") << endl;
        acsilist.flush();
        acsilist.close();
      }
      lock.close();

      systemCall(DEL_COMMAND " " CL_PAR_PLUS + inputfile_list + CL_PAR_PLUS);
    }

    return true;
  }

  std::string AbstractArchive::objectNameToCsiName( const std::string& objectName ) const
  {
    string tmp_input = objectName;
    replaceQuoteForQuoteWithBackslash(tmp_input);
    insertDir(tmp_input, false);
    if (isArchiveFile(tmp_input)) {
      return  tmp_input+".acsi" ;
    }
    return  tmp_input+".csi" ;
  }

}
