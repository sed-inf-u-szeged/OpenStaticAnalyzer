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

#include "AbstractWrapperLib/inc/paramsup/ParamsupCommon.h"
#include "AbstractWrapperLib/inc/messages.h"

#include <list>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>

#ifdef _WIN32
#include <Windows.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#endif // _WIN32

using namespace std;
using namespace common;

bool ColumbusWrappers::isLast(const list<string>::iterator& it, const list<string>::const_iterator& end_it) {
  list<string>::iterator next_it = it;
  return ((list<string>::const_iterator)(++next_it) == end_it);
}

std::string ColumbusWrappers::indepFullpath(const std::string& path) {
  std::string str_path;
  indepFullpath(path.c_str(), str_path);
  return str_path;
}


std::string ColumbusWrappers::indepFullpath(const char* path) {
  std::string str_path;
  indepFullpath(path, str_path);
  return str_path;
}


void ColumbusWrappers::indepFullpath(const char* path, std::string& str_path) {
  std::string newpath = common::indep_fullpath(path);
  std::string new_can_path;

  if (!common::pathCanonicalize(new_can_path, newpath)) {
    writeDebugMsg("Wrapper",CMSG_PATH_CANONICALIZE_WRONG);
    str_path = newpath;
  } else {
    str_path = new_can_path;
  }
}

bool ColumbusWrappers::compareArguments(Argument first, Argument second) {
  if (first.position < second.position) {
    return true;
  } else {
    return false;
  }
}


string ColumbusWrappers::writeTimeStamp() {
  time_t rawtime;
  struct tm *timeinfo;
  string act_time = "";

  time (&rawtime);
  timeinfo = localtime(&rawtime);
  act_time = asctime(timeinfo);
  act_time.erase(std::remove(act_time.begin(), act_time.end(), '\n'), act_time.end());
  act_time = "[" + act_time + "]";
  return act_time;
}

void ColumbusWrappers::writeInfoMsg(const char* location, const char* msg, ...) {
  char buffer[100000];
  va_list al;
  va_start(al, msg);
  vsprintf(buffer, msg, al);
  va_end(al);
  WriteMsg::write(WriteMsg::mlNormal, "[INFO]%s[%s] %s\n", ColumbusWrappers::writeTimeStamp().c_str(), location, buffer);
}

void ColumbusWrappers::writeErrorMsg(const char* location, const char* msg, ...) {
  char buffer[100000];
  va_list al;
  va_start(al, msg);
  vsprintf(buffer, msg, al);
  va_end(al);
  WriteMsg::write(WriteMsg::mlError, "[ERROR]%s[%s] %s\n", ColumbusWrappers::writeTimeStamp().c_str(), location, buffer);
}

void ColumbusWrappers::writeWarningMsg(const char* location, const char* msg, ...) {
  char buffer[100000];
  va_list al;
  va_start(al, msg);
  vsprintf(buffer, msg, al);
  va_end(al);
  WriteMsg::write(WriteMsg::mlWarning, "[WARNING]%s[%s] %s\n", ColumbusWrappers::writeTimeStamp().c_str(), location, buffer);
}

void ColumbusWrappers::writeDebugMsg(const char* location, WriteMsg::MsgLevel level, const char* msg, ...) {
  char buffer[100000];
  va_list al;
  va_start(al, msg);
  vsprintf(buffer, msg, al);
  va_end(al);
  WriteMsg::write(level, "[DEBUG]%s[%s] %s\n", ColumbusWrappers::writeTimeStamp().c_str(), location, buffer);
}

void ColumbusWrappers::writeMsgToFile(const char* file, const char* location, WriteMsg::MsgLevel level, const char* msg, ...) {
  bool fileIsOpened = false;
  FILE* out = NULL;
  if (file && ((out = fopen(file, "a")) != NULL)) {
    fileIsOpened = true;
  } else {
    out = stdout;
    if (file) {
      writeErrorMsg("Wrapper", CMSG_ERROR_OPEN_FILE, file);
    }
  }

  char buffer[100000];
  va_list al;
  va_start(al, msg);
  vsprintf(buffer, msg, al);
  va_end(al);
  const char* level_string;
  switch (level) {
    case WriteMsg::mlError:
      level_string = "ERROR";
      break;
    case WriteMsg::mlWarning:
      level_string = "WARNING";
      break;
    case WriteMsg::mlNormal:
      level_string = "INFO";
      break;
    default:
      level_string = "DEBUG";
      break;
  }
  WriteMsg::writeToFile(out, level, "[%s]%s[%s] %s\n", level_string, ColumbusWrappers::writeTimeStamp().c_str(), location, buffer);

  if (fileIsOpened)
    fclose(out);
}

ColumbusWrappers::ParErrorCode ColumbusWrappers::insertParameterOfArgumentIntoArgumentList(std::list<std::string>::iterator& it, const list<string>::const_iterator& args_end, Argument& actArg, std::list<Argument>& argList, string argName, bool maybeSpaceSeparatedArgument) {
  if (!argName.empty()) {
    actArg.name = argName;
    argList.push_back(actArg);
    return ColumbusWrappers::EC_FOUND;
  } else if (maybeSpaceSeparatedArgument && !ColumbusWrappers::isLast(it, args_end)) {
    ++it;
    actArg.name = *it;
    argList.push_back(actArg);
    return ColumbusWrappers::EC_FOUND;
  } else {
    return ColumbusWrappers::EC_ERROR;
  }
}

ColumbusWrappers::ParErrorCode ColumbusWrappers::setParameterOfArgumentToArgument(std::list<std::string>::iterator& it, const list<string>::const_iterator& args_end, Argument& actArg, Argument& actualArgument, string argName, bool maybeSpaceSeparatedArgument) {
  if (!argName.empty()) {
    actArg.name = argName;
    actualArgument = actArg;
    return ColumbusWrappers::EC_FOUND;
  } else if (maybeSpaceSeparatedArgument && !ColumbusWrappers::isLast(it, args_end)) {
    ++it;
    actArg.name = *it;
    actualArgument = actArg;
    return ColumbusWrappers::EC_FOUND;
  } else {
    return ColumbusWrappers::EC_ERROR;
  }
}

void ColumbusWrappers::insertArgumentIntoArgumentList(Argument& actArg, list<Argument>& argList, string argName) {
  actArg.name = argName;
  argList.push_back(actArg);
}

void  ColumbusWrappers::resolveFilePatterToFiles(Argument& actArg , std::list<Argument>& argList ) {
#ifdef _WIN32


  WIN32_FIND_DATA findFileData;
  HANDLE hFind =FindFirstFile(actArg.name.c_str(),  &findFileData);

  if (hFind == INVALID_HANDLE_VALUE) {
    /*I haven't better idea. */
    argList.push_back(actArg);
    return;
  }


  std::string dirPart;
  std::string filePart;
  common::splitPath(actArg.name,dirPart,filePart);

  Argument newArgument;
  newArgument.lang = actArg.lang;
  newArgument.position = actArg.position;
  newArgument.name = (boost::filesystem::path(dirPart) /findFileData.cFileName).string();
  argList.push_back(newArgument);
 

  while (FindNextFile(hFind,&findFileData)) {
    newArgument.lang = actArg.lang;
    newArgument.position = actArg.position;
    newArgument.name = (boost::filesystem::path(dirPart) / findFileData.cFileName).string();
    common::WriteMsg::write(common::WriteMsg::mlNormal,"The %s name resolved to %s\n",actArg.name,newArgument.name.c_str());
    argList.push_back(newArgument);
  }
  FindClose(hFind);
#else 
  argList.push_back(actArg);
#endif // _WIN32
}

void ColumbusWrappers::resolveFilePatterToFiles( const std::string& actArg , std::list<std::string>& argList ) {
#ifdef _WIN32
  WIN32_FIND_DATA findFileData;
  HANDLE hFind =FindFirstFile(actArg.c_str(),  &findFileData);
  std::string dir, file;
  common::splitPath(actArg, dir, file);

  if (hFind == INVALID_HANDLE_VALUE) {
    /*I haven't better idea. */
    argList.push_back(actArg);
    return;
  }
  std::string newArgument = findFileData.cFileName;
  if (dir.empty()) {
    argList.push_back(newArgument);
  } else {
    argList.push_back(dir + DIRDIVCHAR + newArgument);
  }
  while (FindNextFile(hFind,&findFileData)) {
    newArgument = findFileData.cFileName;
    if (dir.empty()) {
      argList.push_back(newArgument);
    } else {
      argList.push_back(dir + DIRDIVCHAR + newArgument);
    }
  }

#else 
  argList.push_back(actArg);
#endif // _WIN32
}
