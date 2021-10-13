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
#include <iostream>

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
    archive_tool = wrapper_bin_dir + DIRDIVSTRING + LIB_TOOL;
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
  bool AbstractArchive::executeArchive(ColumbusWrappers::ArchiveArgs& arArgs) const {
    if (arArgs.input_files.empty())
      writeWarningMsg(ABSTRACT_ARCHIVE, CMSG_ARCHIVE_HAS_NO_INPUT); // in case of extraction it is a valid usage

    if (!archive_needtorun) {
      writeWarningMsg(ABSTRACT_ARCHIVE, CMSG_ARCHIVE_NO_NEED_TO_RUN);
      return true;
    }

    string aastFileName = objectNameToAstName(arArgs.archive_file);
    writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_EXECUTION, archive_tool.c_str());

    vector<string> args;

    args.push_back("-ml:" + toString(archive_ml));

    for (const string& operation : arArgs.archive_operations)
    {
      writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_OPERATION, operation.c_str());
      args.push_back(operation);
      if (operation == "-add")
        args.push_back("-onelevelonly");
    }

    for (const string& modifier : arArgs.archive_modifiers)
    {
      writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_MODIFIER, modifier.c_str());
      args.push_back(modifier);
    }

    args.push_back(aastFileName);
 
    list<string> inputFileList;
    for (const string& inputFilename : arArgs.input_files)
    {
      writeDebugMsg(ABSTRACT_ARCHIVE, CMSG_DEBUG_ARCHIVE_INPUT, inputFilename.c_str());
      string astName = objectNameToAstName(inputFilename);
      inputFileList.push_back(astName);
      
      // handling of .comment files
      string commentFile = astName + ".comment";
      if (common::pathFileExists(commentFile))
      {
        inputFileList.push_back(commentFile);
      }
    }

    string inputfile_list = wrapper_temp_dir + DIRDIVSTRING + common::toString(getCurrentProcessId()) + "input.list";
    ofstream inputlist(inputfile_list.c_str(), ios::trunc);
    if (inputlist.is_open())
    {
      for (const string& inputFilename : inputFileList)
        inputlist << inputFilename << "\n";
      inputlist.close();
    }

    if (archive_needstat)
    {
      string statfile = wrapper_log_dir + DIRDIVSTRING + "statCANLib.csv";
      args.push_back("-stat:" + statfile);
    }

    args.push_back("-inputlist:" + inputfile_list);

    string currentWorkDir = common::getCwd();
    writeInfoMsg(ABSTRACT_ARCHIVE, CMSG_CURRENT_WORKDIR, currentWorkDir.c_str());

    for (const string& arg : args)
      writeInfoMsg(ABSTRACT_ARCHIVE, "[%s]", arg.c_str());

    int ret = systemCall(archive_tool, args);
    if (ret != 0)
    {
      writeErrorMsg(ABSTRACT_ARCHIVE, CMSG_TOOL_RETURNS, archive_tool.c_str(), ret);
      return false;
    }
    else
    {
      string aast_list = wrapper_log_dir + DIRDIVSTRING + "aast.list";
      string lockFile = getLockFileName(aast_list);
      ofstream aastlist(aast_list.c_str(), ios::app);
      ofstream lock(lockFile.c_str());

      file_lock f_lock(lockFile.c_str());

      if (aastlist.is_open()) {
        //sets an exclusive lock on the file (no other processes can read or write it)
        scoped_lock<file_lock> e_lock(f_lock);

        aastlist << indepFullpath(aastFileName) << endl;
        aastlist.flush();
        aastlist.close();
      }
      lock.close();

      pathDeleteFile(inputfile_list);
    }

    return true;
  }

  std::string AbstractArchive::objectNameToAstName( const std::string& objectName ) const
  {
    string tmp_input = objectName;
    replaceQuoteForQuoteWithBackslash(tmp_input);
    insertDir(tmp_input, false);
    if (isArchiveFile(tmp_input)) {
      return  tmp_input + ".aast" ;
    }
    return  tmp_input + ".ast" ;
  }

}
