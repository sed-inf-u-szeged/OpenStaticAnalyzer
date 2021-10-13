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

#include "CopyMoveWrapper/CopyMoveWrapper.h"

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <AbstractWrapperLib/inc/paramsup/ParamsupCommon.h>
#include <AbstractWrapperLib/inc/messages.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>

#include <fstream>

using namespace std;
using namespace common;
using namespace boost::interprocess;

#define COPY_MOVE_WRAPPER   "CopyMoveWrapper"

namespace ColumbusWrappers {

  static const char* columbusexts[] = {
    ".csi",
    ".acsi",
    ".lcsi"
  };


  CopyMoveWrapper::CopyMoveWrapper(string configfile) :
    AbstractWrapper(configfile),
    acsi_file(wrapper_log_dir + DIRDIVSTRING + "acsi.list"),
    csi_file(wrapper_log_dir + DIRDIVSTRING + "csi.list"),
    lcsi_file(wrapper_log_dir + DIRDIVSTRING + "lcsi.list") {

  }


  bool CopyMoveWrapper::process(int argc, char** argv) {

    list<string> sources;
    list<string> options;
    string target;
    string filterTarget;

    list<string> temp_argv;
    set<pair<string, int> > temp_skip; //empty, but it's needed for setParams function

    setParams(argc, argv, temp_argv, temp_skip);

    getFiles(sources, target, options, temp_argv);
    filterTarget = target;

    string cmd;
    bool isMove = false;
    //egyelore csak linux-ra
    if (wrappedExe == "/bin/cp" || wrappedExe == "cp") {
      cmd = COPY_COMMAND;
    }
    if (wrappedExe == "/bin/mv" || wrappedExe == "mv") {
      isMove = true;
      cmd = MOVE_COMMAND;
    }

    for (list<string>::const_iterator optIt = options.begin(); optIt != options.end(); ++optIt) {
      cmd += " " + *optIt;
    }

    list<string> newSources;
    list<string> newFilterSources;

    if (!pathIsDirectory(target)) {
      if (sources.size() > 1) {
        writeErrorMsg(COPY_MOVE_WRAPPER, CMSG_CMW_MORE_THAN_ONE_SOURCES);
        return false;
      }

      string targetExt, targetName;
      splitExt(target, targetName, targetExt);

      for (list<string>::const_iterator sourceIt = sources.begin(); sourceIt != sources.end(); ++sourceIt) {
        string sourceExt, sourceName;
        splitExt(*sourceIt, sourceName, sourceExt);

        if (sourceExt != targetExt) {
          writeWarningMsg(COPY_MOVE_WRAPPER, CMSG_CMW_DIFFERENT_TYPE_WARNING, targetExt.c_str(), sourceExt.c_str());
        }

        string newSource = *sourceIt;
        insertDir(newSource, false);
        insertDir(target, false);
        checkExtension(newSource, newSources, target);

        insertDir(filterTarget, false);
        checkExtension(newSource, newFilterSources, filterTarget, true);
      }

    } else {

      for (list<string>::const_iterator sourceIt = sources.begin(); sourceIt != sources.end(); ++sourceIt) {

        if (pathIsDirectory(*sourceIt)) {
          string dirSource = *sourceIt;
          if (pathIsDirectory(dirSource)) {
            newSources.push_back(dirSource);
          }
        } else {
          string newSource = *sourceIt;
          insertDir(newSource, false);

          string tmptarget;
          checkExtension(newSource, newSources, tmptarget);
          checkExtension(newSource, newFilterSources, tmptarget, true);
        }
      }

    }

    string targetDir, targetFile;
    common::splitPath(target, targetDir, targetFile);
    if (targetDir[targetDir.length()-1] == DIRDIVCHAR) {
      targetDir = targetDir.substr(0, targetDir.length()-1);
    }

    string tmpdir = common::getCwd();
    if (!isMove) {
      if (!newSources.empty()) {
        writeInfoMsg(COPY_MOVE_WRAPPER, CMSG_CURRENT_WORKDIR, tmpdir.c_str());
        for (list<string>::const_iterator sIt = newSources.begin(); sIt != newSources.end(); ++sIt) {
          string actTarget = target;
          string actCmd = cmd;
          string actSource = *sIt;
          if (pathIsDirectory(actSource)) {
            writeWarningMsg(COPY_MOVE_WRAPPER, CMSG_CMW_SOURCE_IS_DIRECTORY);  //Ilyenkor nem kell masolnunk
            continue;
          }
          actCmd += " " CL_PAR_PLUS + actSource + CL_PAR_PLUS;
          if (pathIsDirectory(actTarget)) {
            actTarget = actTarget + DIRDIVSTRING + outputdir;
            if (!pathIsDirectory(actTarget)) {
              makeDirectory(actTarget);
            }
          } else {
            if (!pathIsDirectory(targetDir)) {
              makeDirectory(targetDir);
            }
          }
          actCmd += " " CL_PAR_PLUS + actTarget + CL_PAR_PLUS;
          writeInfoMsg(COPY_MOVE_WRAPPER, CMSG_ANALYZER_WRAPPER_COMMAND, actCmd.c_str());
          int ret = systemCall(actCmd);
          if (ret != 0) {
            writeErrorMsg(COPY_MOVE_WRAPPER, CMSG_TOOL_RETURNS, wrappedExe.c_str(), ret);
          } else {
            addToListFile(actTarget);
          }
        }
      } else {
        writeWarningMsg(COPY_MOVE_WRAPPER, CMSG_CMW_NO_ASG_FILES, wrappedExe.c_str());
      }
    } else {
      if (!newSources.empty()) {
        writeInfoMsg(COPY_MOVE_WRAPPER, CMSG_CURRENT_WORKDIR, tmpdir.c_str());
        for (list<string>::const_iterator sIt = newSources.begin(); sIt != newSources.end(); ++sIt) {
          string actTarget = target;
          string actCmd = cmd;
          string actSource = *sIt;
          if (pathIsDirectory(actSource)) {
            writeWarningMsg(COPY_MOVE_WRAPPER, CMSG_CMW_SOURCE_IS_DIRECTORY);
            updateListFile(actSource, actTarget);
          } else {
            actCmd += " " CL_PAR_PLUS + actSource + CL_PAR_PLUS;
            if (pathIsDirectory(actTarget)) {
              actTarget = actTarget + DIRDIVSTRING + outputdir;
              if (!pathIsDirectory(actTarget)) {
                makeDirectory(actTarget);
              }
            } else {
              if (!pathIsDirectory(targetDir)) {
                makeDirectory(targetDir);
              }
            }
            actCmd += " " CL_PAR_PLUS + actTarget + CL_PAR_PLUS;
            writeInfoMsg(COPY_MOVE_WRAPPER, CMSG_ANALYZER_WRAPPER_COMMAND, actCmd.c_str());
            int ret = systemCall(actCmd);
            if (ret != 0) {
              writeErrorMsg(COPY_MOVE_WRAPPER, CMSG_TOOL_RETURNS, wrappedExe.c_str(), ret);
            } else {
              updateListFile(actSource, actTarget);
            }
          }
        }
      } else {
        writeWarningMsg(COPY_MOVE_WRAPPER, CMSG_CMW_NO_ASG_FILES, wrappedExe.c_str());
      }
    }

    if (!newFilterSources.empty()) {
      writeInfoMsg(COPY_MOVE_WRAPPER, CMSG_CMW_COPY_FILTER_FILES);
      for (list<string>::const_iterator sfIt = newFilterSources.begin(); sfIt != newFilterSources.end(); ++sfIt) {
        string actTarget = filterTarget;
        string actCmd = cmd;
        string actSource = *sfIt;
        if (pathIsDirectory(actSource)) {
          continue;
        } else {
          actCmd += " " CL_PAR_PLUS + actSource + CL_PAR_PLUS;
          if (pathIsDirectory(actTarget)) {
            actTarget = actTarget + DIRDIVSTRING + outputdir;
            if (!pathIsDirectory(actTarget)) {
              makeDirectory(actTarget);
            }
          } else {
            if (!pathIsDirectory(targetDir)) {
              makeDirectory(targetDir);
            }
          }
          actCmd += " " CL_PAR_PLUS + actTarget + CL_PAR_PLUS;
          writeInfoMsg(COPY_MOVE_WRAPPER, CMSG_ANALYZER_WRAPPER_COMMAND, actCmd.c_str());
          int ret = systemCall(actCmd);
          if (ret != 0) {
            writeErrorMsg(COPY_MOVE_WRAPPER, CMSG_TOOL_RETURNS, wrappedExe.c_str(), ret);
          }
        }
      }
    } else {
      writeWarningMsg(COPY_MOVE_WRAPPER, CMSG_CMW_NO_ASG_FILES, wrappedExe.c_str());
    }

    return true;
  }



  void CopyMoveWrapper::checkExtension(string& file, list<string>& fileList, string& target, bool isFilter /*=false*/) {
    //a target elvileg csak olyankor lesz beallitva, ha egy fajl masolasarol van szo
    if (isObjectFile(file)) {
      if (common::pathFileExists(file + ".csi", false)) {
        fileList.push_back(file+".csi");
        if (!target.empty()) {
          target = target + ".csi";
        }
      }
    } else if (isArchiveFile(file)) {
      if (common::pathFileExists(file + ".acsi", false)) {
        fileList.push_back(file+".acsi");
        if (!target.empty()) {
          target = target + ".acsi";
        }
      }
    } else {
      if (!isFilter) {
        for (size_t n = 0; n < sizeof(columbusexts)/sizeof(char*); n++) {
          if (common::pathFileExists(file + columbusexts[n], false)) {
            fileList.push_back(file + columbusexts[n]);
            if (!target.empty()) {
              target = target + columbusexts[n];
            }
          }
        }
      } else {
        if (common::pathFileExists(file + ".fcsi", false)) {
          fileList.push_back(file + ".fcsi");
          if (!target.empty()) {
            target = target + ".fcsi";
          }
        }
      }
    }
  }



  void CopyMoveWrapper::getFiles(list<string>& sourceFiles, string& target, list<string>& options, list<string> temp_argv) {
    target = "";
    sourceFiles.clear();
    options.clear();
    string lastsource;

    for (list<string>::reverse_iterator revIt = temp_argv.rbegin(); revIt != temp_argv.rend(); ++revIt) {
      if ((*revIt)[0] == '-') {   // parameter
        if ((*revIt == "-r") || (*revIt == "-R")) {
          writeWarningMsg(COPY_MOVE_WRAPPER, CMSG_CMW_RECURSIVE_MODE);
        }
        options.push_front(*revIt);
      } else {    // input
        if (target.empty()) {
          target = indepFullpath(*revIt);
        } else {
          lastsource = indepFullpath(*revIt);
          sourceFiles.push_front(lastsource);
        }
      }
    }
  }


  bool CopyMoveWrapper::loadListFile(string& file, list<string>& fileList) {
    if (!file.empty()) {
      ifstream ifs(file.c_str());
      if (ifs.is_open()) {
        string tmp;
        while (getline(ifs, tmp)) {
          if (!tmp.length())
            continue;
          if (tmp[tmp.length()-1]==0xD) { // handle DOS line-ends in unix
            fileList.push_back(tmp.substr(0,tmp.length()-1));
          } else {
            fileList.push_back(tmp);
          }
        }
        ifs.close();
        return true;
      }
    }
    return false;
  }

  void CopyMoveWrapper::saveListFile(string& file, list<string>& fileList) {
    ofstream outputfile(file.c_str());
    if (outputfile.is_open()) {
      for (list<string>::iterator it = fileList.begin(); it != fileList.end(); ++it) {
        outputfile << *it << std::endl;
        outputfile.flush();
      }
      outputfile.close();
    }
  }


  void CopyMoveWrapper::updateListFile(string& source, string& target) {
    writeDebugMsg(COPY_MOVE_WRAPPER, CMSG_CMW_LIST_FILE_UPDATE, source.c_str(), target.c_str());

    list<string> acsi_list;
    list<string> csi_list;
    list<string> lcsi_list;

    if (pathIsDirectory(source)) {
      updateListFile(source, target, acsi_file, true);
      updateListFile(source, target, csi_file, true);
      updateListFile(source, target, lcsi_file, true);
    } else {
      string sourceExt, sourceName;
      splitExt(source, sourceName, sourceExt);

      if (sourceExt == ".csi") {
        updateListFile(source, target, csi_file);
      } else if (sourceExt == ".acsi") {
        updateListFile(source, target, acsi_file);
      } else if (sourceExt == ".lcsi") {
        updateListFile(source, target, lcsi_file);
      }
    }

  }


  void CopyMoveWrapper::updateListFile(string& source, string& target, string& listFile, bool sourceIsDirectory /*=false*/) {
    list<string> fileList;
    string lockFile = getLockFileName(listFile);
    ofstream lock(lockFile.c_str());

    file_lock f_lock(lockFile.c_str());
    {
      //sets an exclusive lock on the file (no other processes can read or write it)
      scoped_lock<file_lock> e_lock(f_lock);

      if (!loadListFile(listFile, fileList))
        return;

      list<string> newFileList;
      string actSource = indepFullpath(source);
      string actTarget = indepFullpath(target);
      for (list<string>::iterator it = fileList.begin(); it != fileList.end(); ++it) {
        string dir, file;
        common::splitPath(*it, dir, file);
        string sDir, sFile;
        common::splitPath(actSource, sDir, sFile);
        string tmpSource = actSource + DIRDIVSTRING + outputdir;
        if (sourceIsDirectory) {
          if (dir == tmpSource || (dir + DIRDIVSTRING) == tmpSource || dir == (tmpSource + DIRDIVSTRING)) {
            *it = actTarget + DIRDIVSTRING + sFile + DIRDIVSTRING + file;
            insertDir(*it, false);
          } else {
            size_t found = it->find(actSource);
            if (found != std::string::npos && found == 0 && ((*it)[actSource.length()+1] == DIRDIVCHAR || (*it)[actSource.length()] == DIRDIVCHAR)) {
              *it = actTarget + DIRDIVSTRING + sFile + DIRDIVSTRING + it->substr(actSource.length()+1, it->length()-actSource.length());
            }
          }
        } else {
          if (sFile == file) {
            if (pathIsDirectory(actTarget)) {
              *it = actTarget + DIRDIVSTRING + file;
            } else {
              *it = actTarget;
            }
          }
        }
      }

      systemCall(DEL_COMMAND " " CL_PAR_PLUS + listFile + CL_PAR_PLUS);

      saveListFile(listFile, fileList);
    }
    lock.close();
  }

  void CopyMoveWrapper::addToListFile(string& target) {
    writeDebugMsg(COPY_MOVE_WRAPPER, CMSG_CMW_LIST_FILE_ADD, target.c_str());

    string targetExt, targetName;
    splitExt(target, targetName, targetExt);

    if (targetExt == ".csi") {
      addToListFile(target, csi_file);
    } else if (targetExt == ".acsi") {
      addToListFile(target, acsi_file);
    } else if (targetExt == ".lcsi") {
      addToListFile(target, lcsi_file);
    }
  }

  void CopyMoveWrapper::addToListFile(string& target, string& listFile) {
    list<string> fileList;
    string lockFile = getLockFileName(listFile);
    ofstream lock(lockFile.c_str());
    
    file_lock f_lock(lockFile.c_str());
    {
      //sets an exclusive lock on the file (no other processes can read or write it)
      scoped_lock<file_lock> e_lock(f_lock);

      if(!loadListFile(listFile, fileList))
        return;

      list<string> newFileList;
      string actTarget = indepFullpath(target);
      fileList.push_back(actTarget);

      systemCall(DEL_COMMAND " " CL_PAR_PLUS + listFile + CL_PAR_PLUS);

      saveListFile(listFile, fileList);
    }
    lock.close();
  }


}
