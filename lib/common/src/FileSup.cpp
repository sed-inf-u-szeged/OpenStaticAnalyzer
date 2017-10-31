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

#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>

#include "Exception.h"
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/messages.h>
#include <Environment.h>

#define INIMAXSTRING 2000
#define MAXPATH 4096

namespace fs = boost::filesystem;

#if defined(_WIN32)
  #include <windows.h>
  #include <shlwapi.h>
  #include <io.h>
  #include <fcntl.h>
  #include <direct.h>
  #include "shlobj.h"
#endif

#if defined(__unix__)
  #include <limits.h>
  #include <dirent.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <sys/types.h>
  #include <sys/wait.h>
  #include <sys/file.h>
#endif

#ifdef __unix__
extern char **environ; // For getEnvironmentVariables function.
#endif

size_t common::splitPath(const std::string& path, std::string& dir, std::string& file)
{
  dir = fs::path(path).branch_path().string();
  file = fs::path(path).filename().string();
  return dir.length();
}

std::string common::removeDoubleDirdivs(const std::string& str , bool win /*= true*/)
{
  unsigned p1 = 0, p2 = 0;

  char dirDivChar = win ? '\\' : '/';
  if(win && str.length() > 1)
  {
    // skip windows network name \\.....
    if (str[0]==dirDivChar && str[1]==dirDivChar) {
      p1++; p2++;
    }
  }

  bool previsslash = false;
  for (; p1 < str.length(); ++p1, ++p2) {
    if (previsslash && str[p1] == dirDivChar)
      --p2;
    previsslash = (str[p1] == dirDivChar);
    p2 = p1;
  }
  return str.substr(0, p2);
}

bool common::pathCanonicalize(std::string& dst, const std::string& src)
{
  char buff[MAXPATH];
#ifdef _WIN32
  std::string s = std::string(src);
  // add drive letter when starting with '\'
  if (s[0]=='\\' || s[0]=='/') {
    s = getCwd().substr(0, 2) + s;
  }
  std::string tmp = "";
  if (pathIsRelative(s)) {
    tmp = getCwd() + "\\";
  }
  tmp = tmp + s;
  tmp = removeDoubleDirdivs(tmp, true);
  for (unsigned int i = 0; i < tmp.length(); i++)
    if (tmp[i] == '/') tmp[i] = '\\';
  if (::PathCanonicalize(buff, tmp.c_str()) == FALSE) // call to shlwapi.lib
    return false;
  else dst = buff;
#else
  char* ret = realpath(src.c_str(), buff);
  if(!ret)
    return false;
  dst = buff;
#endif
  return true;
}

std::string common::getExecutableProgramDir() {
#ifdef _WIN32
  char target[MAXPATH];
  strncpy(target, _pgmptr, MAXPATH);
  *PathFindFileName(target) = 0;
  return target;
#elif defined __unix__
  pid_t me = getpid();

  char file[100];
  sprintf(file,"/proc/%d/exe", me);
  char target[MAXPATH];
  
  int size = readlink(file, target, MAXPATH - 1);
  if (size > 0) {
    while (size && target[size - 1] != '/') size--;
    target[size] = 0;
    return target;
  }

  return "";
  
#else
  return "";
#endif
}

bool common::makeDirectory(const std::string& dirName) {
  try {
    return boost::filesystem::create_directories(dirName);
  } catch (fs::filesystem_error e) {
    throw columbus::Exception(COLUMBUS_LOCATION, e.what());
  }
}


std::string common::indep_fullpath(const std::string& path)
{
  std::string str = removeQuotes(path);

  if (!str.length())
    return str;

  if (str[0] == DIRDIVCHAR)    // FullPath
    return str;
    
#if defined(__unix__)
  if (str[0] == '~')          // Home realtive
  {
    char* home = getenv("HOME");
    if (!home) {
      return std::string();
    }
    
    std::string full = home + str.substr(1);
    return full;
  }
#elif defined(_WIN32)

  if (str[0] == '/')    // Special FullPath starting with '/'
    return str;
  
  // FullPath with drive letter
  if (str.length() >= 2 && ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')) && str[1] == ':')   
    return str;

#endif

  // It is relative path 
  std::string cwd = getCwd();
  if (!cwd.length()) {
    return std::string();
  }
  if (cwd[cwd.length()-1] != DIRDIVCHAR) {
    cwd += DIRDIVSTRING;
  }
  cwd += str;
  return cwd;
}

static inline void skipWhiteSpaces(char*& line) {
  while (*line && (*line == '\t' || *line == ' '))
    line++;
}


static char* getSectionName(char *line) {
  if(!line) return NULL;
  char* section = line;

  skipWhiteSpaces(line);

  if (*line != '[')
    return NULL;

  line++;
  section = line;

  while (*line && *line != ']')
    line++;

  if (*line == ']')
    *line = 0;
  else
    section = NULL;

  return section;
}


static bool getKeyAndValue(char* line, char*& key, char*& value) {
  if(!line) return false;

  skipWhiteSpaces(line);

  key = line;

  while (*line && *line != '\t' && *line != ' ' && *line != '=')
    line++;

  if (*line != '=') {
    char *endmarker = line;
    skipWhiteSpaces(line);
    *endmarker = 0;
  }

  if (*line == '=') {
    *line = 0;
    line++;
  } else {
    key = value = NULL;
    return false;
  }

  skipWhiteSpaces(line);
  value = line;

  char *lastchar = NULL;

  while (*line &&  *line != '\r' && *line != '\n') {
    if (*line != ' ' && *line != '\t')
      lastchar = line;
    line++;
  }

  if (lastchar)
    lastchar[1] = 0;

  *line = 0;
  return true;
}

size_t common::getPrivateProfileSection(const char* appname, char* ret_string, size_t size, const char* filename) {
  ret_string[0] = '\0';
  if (size < 2) {
    WriteMsg::write(CMSG_BUFFER_TOO_SMALL);
    return 0;
  }
  if(!appname){
    WriteMsg::write(CMSG_APPNAME_REQUIRED);
    return 0;
  }

  size_t pos = 0;
  FILE* inifile = fopen(filename, "r");

  if (inifile)  {
    char line[INIMAXSTRING];
    bool in_good_section = false;
    while (fgets(line, INIMAXSTRING, inifile)) {
      char *s = getSectionName(line);

      if (s) {   // It is a section header line
        if (caseInsensitiveComp(s, appname))
          in_good_section = true;
        else
          in_good_section = false;
      }
      else if (in_good_section){
        char *lastchar = NULL;
        char *actchar = line;
        while (*actchar &&  *actchar != '\r' && *actchar != '\n') {
          if (*actchar != ' ' && *actchar != '\t')
            lastchar = actchar;
          actchar++;
        }
        if(lastchar)
          lastchar[1] = 0;
        if(strlen(line) != 0 && line[0] != '\r' && line[0] != '\n' ){
          size_t ksize = strlen(line);
          if (pos + ksize + 2 <= size) {
            strncpy(ret_string + pos, line, ksize +1);
            pos += ksize + 1;
          } else
            WriteMsg::write(CMSG_BUFFER_TOO_SMALL);
        }
      }
    }
    fclose(inifile);
  }
  if(strlen(ret_string) == 0)
    return 0;
  ret_string[pos] = 0;   // this is a closing zero.
  return pos;
}

unsigned int common::getPrivateProfileInt(const char * appname, const char * keyname, unsigned int def, const char * filename, bool casesensitive /*=false*/)
{
  if (!appname || !keyname)
    return def;

  FILE* inifile = fopen(filename, "r");

  if (inifile)  {
    char line[INIMAXSTRING];
    bool in_good_section = false;
    while (fgets(line, INIMAXSTRING, inifile)) {
      char *s = getSectionName(line);
      char *key = NULL;
      char *value = NULL;

      if (s) {   // It is a section header line
        if ((casesensitive && strcmp(s,appname)==0) || (!casesensitive && caseInsensitiveComp(s, appname)))
          in_good_section = true;
        else
          in_good_section = false;
      } else if (getKeyAndValue(line, key, value))  // It is a key=value line
        if (in_good_section && caseInsensitiveComp(key, keyname)) {
          fclose(inifile);
          return atol(value);
        }
    }
    fclose(inifile);
  }
  return def;
}


size_t common::getPrivateProfileString(const char * appname, const char * keyname, const char *def, char * ret_string, size_t size, const char *filename, bool casesensitive /*=false*/)
{
  if ((!appname || !keyname) && size < 2) {
    WriteMsg::write(CMSG_BUFFER_TOO_SMALL);
    return 0;
  }

  size_t pos = 0;
  FILE* inifile = fopen(filename, "r");

  if (inifile)  {
    char line[INIMAXSTRING];
    bool in_good_section = false;
    while (fgets(line, INIMAXSTRING, inifile)) {
      char *s = getSectionName(line);
      char *key = NULL;
      char *value = NULL;

      if (s) {   // It is a section header line
        if (appname) {
          if ((casesensitive && strcmp(s,appname)==0) || (!casesensitive && caseInsensitiveComp(s, appname)))
            in_good_section = true;
          else
            in_good_section = false;
        } else {  // All section names have to be collected
          size_t ssize = strlen(s);
          if (pos + ssize + 2 <= size) {
            strncpy(ret_string + pos, s, ssize +1);
            pos += ssize + 1;
          } else
            WriteMsg::write(CMSG_BUFFER_TOO_SMALL);
        }
      } else if (getKeyAndValue(line, key, value) && appname) {// It is a key=value line and the appname is specified
        if (in_good_section) {
          if (keyname) {
          if (caseInsensitiveComp(key, keyname)) {
            strncpy(ret_string, value, size-1);
            ret_string[size-1] = 0;
            fclose(inifile);
            return size - 1;
          }
          } else {  // All key names have to be collected
          size_t ksize = strlen(key);
          if (pos + ksize + 2 <= size) {
            strncpy(ret_string + pos, key, ksize +1);
            pos += ksize + 1;
          } else
            WriteMsg::write(CMSG_BUFFER_TOO_SMALL);
          }
        }
      }
    }
    fclose(inifile);
  }

  if (!appname || !keyname) {
    ret_string[pos] = 0;   // this is a closing zero.
    return pos;
  }
  
  if (def) { // neither the appname nor the keyname is set but there is a default
    strcpy(ret_string, def);
    return strlen(def);
  }
    
  ret_string[0] = 0;  // none of the appname, keyname and def is set.
  return 0;
}

unsigned int common::writePrivateProfileString(const char* appname, const char* keyname, const char* str, const char* filename, bool casesensitive /*=false*/) {
  std::string tempfilename = (boost::filesystem::temp_directory_path()/boost::filesystem::unique_path()).string();
  FILE* tempfile = fopen(tempfilename.c_str(), "wb+");

  if (!tempfile) {
    WriteMsg::write(CMSG_TEMPFILE_COULDNT_CREATED);
    return 0;
  }

  char line[INIMAXSTRING];
  bool found_key = false;
  bool found_section = false;

  FILE* inifile = fopen(filename, "r");

  if (inifile)  {
    bool in_good_section = false;
    bool newvalue = false;

    while (fgets(line, INIMAXSTRING, inifile)) {
      char *s = NULL;
      char *key = NULL;
      char *value = NULL;
      char saveline[INIMAXSTRING];

      strcpy(saveline, line);
      newvalue = false;

      if ((s = getSectionName(line))) {
        if ((casesensitive && strcmp(s,appname)==0) || (!casesensitive && caseInsensitiveComp(s, appname))) {
          in_good_section = true;
          found_section = true;
        } else {
          if (in_good_section && !found_key) {
            fprintf(tempfile, "%s=%s\n", keyname, str);
            found_key = true;
          }
          in_good_section = false;
        }
      } else if (getKeyAndValue(line, key, value))  // It is a key=value line
        if (in_good_section && caseInsensitiveComp(key, keyname)) {
          found_key = true;
          if ((casesensitive && strcmp(str,value)!=0) || (!casesensitive && !caseInsensitiveComp(str, value))) {
            fprintf(tempfile, "%s=%s\n", keyname, str);
            newvalue = true;
          }
        }

      if (!newvalue)
        fprintf(tempfile, "%s", saveline);
    }
    fclose(inifile);
  }

  if (!found_section)
    fprintf(tempfile, "[%s]\n", appname);

  if (!found_key)
    fprintf(tempfile, "%s=%s\n", keyname, str);

  // Overwrite the old ini with the tempfile
  inifile = fopen(filename, "wt");

  if (inifile) {
    fseek(tempfile, 0, SEEK_SET);

    size_t count = 0;
    while ((count = fread(line, 1, INIMAXSTRING, tempfile)))
      fwrite(line, 1, count, inifile);

    fclose(inifile);
  }

  fclose(tempfile);
  remove(tempfilename.c_str());
  return 1;
}

unsigned int common::convertZeroTerminatedStringList(const char *input_list, std::list<std::string>& output_list) {
  unsigned int counter = 0;
  while (*input_list) {
    output_list.push_back(input_list);
    input_list += output_list.back().size() + 1;
    ++counter;
  }
  return counter;
}


std::string common::pathRemoveFileSpec(const std::string& path)
{
  std::string p = pathFindFileName(path);
  if (!p.length() || p == path) return path;
  else return path.substr(0, path.length() - p.length() - 1);
}

std::string common::pathFindFileName(const std::string& path)
{
  std::string str = std::string(path);
  if(str.length())
  {
    for (size_t i = str.length() -1; i!=0; --i)
      if (str[i] == '/'
#ifdef _WIN32
                    || str[i] == '\\' || str[i] == ':'
#endif
         )
        return str.substr(i+1);
  }
  return str;
}

std::string common::pathFindExtension(const std::string& path)
{
  std::string ret = std::string(path);
  if(!ret.length()) return ret;
  size_t p = ret.length() - 1;
  while(p != 0 && ret[p] != '.')
  {
    p--;
  }
  if(p != 0)
    return ret.substr(p+1);
  else return ret;
}

std::string common::pathRemoveExtension(const std::string& path)
{
  std::string ext = pathFindExtension(path);
  if (ext == path) return path;
  else return std::string(path).substr(0, path.length() - ext.length()-1);
}

std::string common::pathRemoveAllExtensions(const std::string& path)
{
  std::string ret = std::string(path);
  size_t p = ret.length(); --p;
  while(p != 0 && ret[p] != '\\' && ret[p] != '/')
  {
    --p;
  }
  while(p < ret.length() && ret[p] != '.')
  {
    ++p;
  }
  return ret.substr(0, p);
}

bool common::pathAddExtension(std::string& path, const std::string& extension)
{
  path += extension;
  return true;
}

bool common::pathFileExists(const std::string& path, bool dirAllowed)
{
  if(fs::exists(path))
  {
    if(fs::is_directory(path))
      return dirAllowed;
    else
      return true;
  } else {
    return false;
  }
}


bool common::splitExt(const std::string& file, std::string& filename, std::string& ext) {
  size_t div_pos = file.find_last_of(DIRDIVCHAR);
  size_t dot_pos = file.find_last_of('.');

  if (dot_pos == std::string::npos) {
    filename = file;
    ext = "";
    return false;
  }

  if (div_pos != std::string::npos && div_pos > dot_pos) {
    filename = file;
    ext = "";
    return false;
  } else {
    filename = file.substr(0, dot_pos);
    ext = file.substr(dot_pos);
    return true;
  }
}

bool common::pathIsAbsolute(const std::string& path)
{
  return fs::path(path).is_complete();
}

bool common::pathIsRelative(const std::string& path)
{
  return !fs::path(path).is_complete();
}

std::string common::getCwd()
{
#if defined(_WIN32)
  return correctDirDivs(fs::current_path().string());
#else
  return fs::current_path().string();
#endif
}

int common::chDir(const std::string& dirname)
{
#if defined(_WIN32)
  return ::_chdir(dirname.c_str());
#endif
#if defined(__unix__)
  return ::chdir(dirname.c_str());
#endif
}

std::string common::correctDirDivs(std::string path)
{
  std::string::size_type pos = 0;
#if defined(_WIN32)
  std::string toSearch = "/";
#endif
#if defined(__unix__)
  std::string toSearch = "\\";
#endif
  while ((pos = path.find(toSearch,pos)) != std::string::npos)
    path.replace(pos,1,DIRDIVSTRING);
  return path;
}

int common::fileTimeCmp(const std::string& first, const std::string& second) {  // -1: first < second; 0: first==second; 1: first > second
  if(!pathFileExists(first))
    return -2;
  if(!pathFileExists(second))
    return -3;
  try {
    time_t tFirst  = fs::last_write_time(first);
    time_t tSecond = fs::last_write_time(second);
    if     (tFirst < tSecond) return -1;
    else if(tFirst > tSecond) return  1;
    else                      return  0;
  } catch (fs::filesystem_error e) {
    throw columbus::Exception(COLUMBUS_LOCATION, e.what());
  }
}

bool common::pathDeleteFile(const std::string& path) {
  return fs::remove(path);
}

bool common::pathIsDirectory (const std::string& path) {
  return fs::is_directory(path);
}

#ifdef __unix__

static int handle_system_exit_status(int status) {
  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    return WTERMSIG(status);
  } else if (WIFSTOPPED(status)) {
    return WSTOPSIG(status);
  } 
  
  return status;
}

#endif


#ifdef _WIN32 

static int run(const std::string& cmd, std::ostream& out) {
  char *debugfile = getenv(COLUMBUS_RUN_DEBUG_ENV_VAR);
  if (debugfile != NULL) {
   FILE* f = fopen(debugfile, "at");
   if (f != NULL) {
     fprintf(f, "RUN:[%s]\n", cmd.c_str());
     fclose(f);
   }
  }

  BOOL                bRet = FALSE;
  STARTUPINFO         si   = {0};
  PROCESS_INFORMATION pi   = {0};

  si.cb = sizeof(si);
  si.dwFlags    = STARTF_USESTDHANDLES;
  si.hStdInput  = GetStdHandle (STD_INPUT_HANDLE);

  HANDLE pipe[2];
  SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
  
  if (!CreatePipe(&pipe[0], &pipe[1], &sa, 0) ) {
    return GetLastError();
  }

  if (!SetHandleInformation(pipe[0], HANDLE_FLAG_INHERIT, 0)) {
    int ret = GetLastError();
    CloseHandle(pipe[0]);
    CloseHandle(pipe[1]);
    return ret;
  }

  si.hStdOutput = pipe[1];
  si.hStdError = pipe[1];

  char buff[32768];
  strncpy(buff, cmd.c_str(), 32767);
  buff[32767] = 0;
  bRet = CreateProcess (NULL, buff, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
  DWORD dw = 0;

  CloseHandle(pipe[1]);

  if (bRet) {
    const int BUFFERSIZE = 32768;
    DWORD readSize;
    char readBuffer[BUFFERSIZE];
    while (ReadFile( pipe[0], readBuffer, BUFFERSIZE, &readSize, NULL) && (readSize != 0)) {
      out.write(readBuffer, readSize);
    }
    WaitForSingleObject (pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &dw);
    CloseHandle (pi.hProcess);
    CloseHandle (pi.hThread);
  } else {
    dw = GetLastError();
  }

  CloseHandle(pipe[0]);

  return dw;
}

#endif

int common::run(const std::string& cmd, bool silent, const std::string& out /*= ""*/, const std::string& err /*= ""*/)
{
  char *debugfile = getenv(COLUMBUS_RUN_DEBUG_ENV_VAR);
  if (debugfile != NULL) {
    FILE* f = fopen(debugfile, "at");
    if (f != NULL) {
     fprintf(f, "RUN:[%s]\n", cmd.c_str());
     fclose(f);
    }
  }
  
  bool same_file = false;
  
  if (out.length() && err.length()) 
    same_file = (out == err);

#ifdef _WIN32
  BOOL                bRet = FALSE;
  STARTUPINFO         si   = {0};
  PROCESS_INFORMATION pi   = {0};

  // Make child process use this app's standard files.
  si.cb = sizeof(si);
  si.dwFlags    = STARTF_USESTDHANDLES;
  si.hStdInput  = GetStdHandle (STD_INPUT_HANDLE);

  bool outopened = false;
  bool erropened = false;
  SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

  if (!silent) {
    if (out.empty())
      si.hStdOutput = GetStdHandle (STD_OUTPUT_HANDLE);
    else {
      si.hStdOutput = CreateFile(out.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
      if (si.hStdOutput == INVALID_HANDLE_VALUE)
        si.hStdOutput = GetStdHandle (STD_OUTPUT_HANDLE);
      else
        outopened = true;
    }
    if (err.empty())
      si.hStdError = GetStdHandle (STD_ERROR_HANDLE);
    else {
      if (same_file) {
        if (outopened) 
          si.hStdError = si.hStdOutput;
        else
          si.hStdError = GetStdHandle (STD_ERROR_HANDLE);
      } else {
        si.hStdError = CreateFile(err.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (si.hStdError == INVALID_HANDLE_VALUE)
          si.hStdError = GetStdHandle (STD_ERROR_HANDLE);
        else
          erropened = true;
      }
    }
  } else {
    si.hStdOutput = NULL;
    si.hStdError  = NULL;
  }

  SetFilePointer(si.hStdOutput, 0, 0, FILE_END);
  SetFilePointer(si.hStdError, 0, 0, FILE_END);
  char buff[32768];
  strncpy(buff, cmd.c_str(), 32767);
  buff[32767] = 0;
  bRet = CreateProcess (NULL, buff, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
  DWORD dw = 0;

  if (bRet) {
    WaitForSingleObject (pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &dw);
    CloseHandle (pi.hProcess);
    CloseHandle (pi.hThread);
  } else {
    dw = GetLastError();
  }

  FlushFileBuffers(si.hStdOutput);
  FlushFileBuffers(si.hStdError);

  if (outopened)
    CloseHandle (si.hStdOutput);

  if (erropened)
    CloseHandle (si.hStdError);

  return dw;
#else
  bool tcsh = false;
  char *shell = getenv("shell");

  if (shell && strstr(shell, "tcsh"))
    tcsh = true;

  if (silent) {
    int ret;
    
    if (tcsh)
      ret = system ((std::string("(") + cmd + ">/dev/null ) >&/dev/null").c_str());
    else
      ret = system ((std::string(cmd) + " 1>/dev/null 2>/dev/null").c_str());
    
    return handle_system_exit_status(ret);
  } else {

    std::string outredirect;
    std::string errorredirect;
    if (tcsh) {
      int ret = 0;
      if (same_file) {
        ret = system((std::string(cmd) + ">&" + std::string(out)).c_str());
      } else {
        if (!out.empty())
          outredirect = " >>" + out;
        if (!err.empty())
          errorredirect = " >>&" + err;
        ret = system((std::string("(") + cmd + outredirect + ")" + errorredirect).c_str());
      }
      return handle_system_exit_status(ret);
    } else {
      if (!out.empty())
        outredirect = " 1>>" + out;
      if (!err.empty()) {
        if (same_file) 
          errorredirect = " 2>&1";
        else 
          errorredirect = " 2>>" + err;
      }
      int ret = system((cmd  + outredirect + errorredirect).c_str());
      return handle_system_exit_status(ret);
    }
  }
#endif
}


#ifdef __unix__

static int run_with_args(const char *command, char* argv[], const char* out, const char* err)
{
  char *debugfile = getenv(COLUMBUS_RUN_DEBUG_ENV_VAR);
  if (debugfile != NULL) {
    FILE* f = fopen(debugfile, "at");
    if (f != NULL) {
      fprintf(f, "RUN_WITH_ARGS: [%s] ", command);
      char** arg = argv;
      while (*arg != NULL) {
        fprintf(f, "[%s]", *arg);
        arg++;
     }
     fprintf(f, "\n");
     fclose(f);
   }
  }

  int status;
  pid_t pid;

  fflush(stdout);
  fflush(stderr);

  pid = fork ();
  if (pid == 0) {
    
    /* Set the standard input/output channels of the new process.  */
    
    if (out != NULL && out[0] != 0) {
      int outfile = open(out, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
      if (outfile != -1 && outfile != STDOUT_FILENO) {
        dup2 (outfile, STDOUT_FILENO);
        close (outfile);
      }
    }

    if (err != NULL && err[0] != 0) {
      if (out != NULL && (strcmp(out, err) == 0)) {
        dup2 (STDOUT_FILENO, STDERR_FILENO);
      }else {
        int errfile = open(err, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
        
        if (errfile != -1 && errfile != STDERR_FILENO) {
          dup2 (errfile, STDERR_FILENO);
          close (errfile);
        }
      }
    }
    
    execvp(command, argv);
    _exit (EXIT_FAILURE);
  } else if (pid < 0) {
   /* The fork failed.  Report failure.  */
   return EXIT_FAILURE;
  } else {
   /* This is the parent process.  Wait for the child to complete.  */
   if (waitpid (pid, &status, 0) != pid)
     return EXIT_FAILURE;
  }
 return handle_system_exit_status(status);
}

static int run_with_args(const char *command, char* argv[], std::ostream& out)
{
  char *debugfile = getenv(COLUMBUS_RUN_DEBUG_ENV_VAR);
  if (debugfile != NULL) {
    FILE* f = fopen(debugfile, "at");
    if (f != NULL) {
      fprintf(f, "RUN_WITH_ARGS: [%s] ", command);
      char** arg = argv;
      while (*arg != NULL) {
        fprintf(f, "[%s]", *arg);
        arg++;
     }
     fprintf(f, "\n");
     fclose(f);
   }
  }

  fflush(stdout);
  fflush(stderr);

  int status;
  pid_t pid;
  int pipefd[2];

  if (pipe(pipefd) == -1) {
    return EXIT_FAILURE;
  }

  pid = fork ();
  if (pid == 0) {
    /* Set the standard input/output channels of the new process.  */
    close(pipefd[0]);
    fflush(stdout);
    dup2(pipefd[1], STDOUT_FILENO);
    dup2(STDOUT_FILENO, STDERR_FILENO);
    close(pipefd[1]);
    setvbuf(stdout, NULL, _IONBF, 0);
    execvp(command, argv);
    _exit (EXIT_FAILURE);
  } else if (pid < 0) {
   /* The fork failed.  Report failure.  */
   return EXIT_FAILURE;
  } else {
   /* This is the parent process.  Wait for the child to complete.  */
   close(pipefd[1]);  // no write
   char c;
   while(read(pipefd[0], &c, 1) > 0) 
     out.put(c); 

   close(pipefd[0]);

   if (waitpid (pid, &status, 0) != pid)
     return EXIT_FAILURE;
  }
 return handle_system_exit_status(status);
}

#endif

/*
  Argument parsing rules of the windows command line:

  * Arguments are delimited by white space, which is either a space or a tab.
  * The caret character (^) is not recognized as an escape character or delimiter. 
    The character is handled completely by the command-line parser in the operating 
    system before being passed to the argv array in the program.
  * A string surrounded by double quotation marks ("string") is interpreted as a 
    single argument, regardless of white space contained within. A quoted string 
    can be embedded in an argument.
  * A double quotation mark preceded by a backslash (\") is interpreted as a literal 
    double quotation mark character (").
  * Backslashes are interpreted literally, unless they immediately precede a double 
    quotation mark.
  * If an even number of backslashes is followed by a double quotation mark, one 
    backslash is placed in the argv array for every pair of backslashes, and the 
    double quotation mark is interpreted as a string delimiter.
  * If an odd number of backslashes is followed by a double quotation mark, one 
    backslash is placed in the argv array for every pair of backslashes, and the 
    double quotation mark is "escaped" by the remaining backslash, causing a literal 
    double quotation mark (") to be placed in argv.

*/

#ifdef _WIN32

static void doubleBackslashCharacters(const std::string& orig, size_t pos, std::string& result) {
  do {
    --pos;
    if (orig[pos] == '\\')
      result.push_back('\\');   // only one is added since the original backshalses are already added
    else 
      break;
  } while (pos != 0);
}

static std::string convertToWindowsCmdlineArgument(const std::string& arg) {
  
  std::string result;
  enum last_char {
    lc_other,
    lc_space,
    lc_quotation,
    lc_bslash
  } lastchar = lc_other;

  for (size_t cpos = 0; cpos < arg.size(); ++cpos) {
    // The white space sequence have to be closed with a quotation mark
    if (lastchar == lc_space && arg[cpos] != ' ') 
      result.push_back('\"');
    
    if (arg[cpos] == ' ') {
      if (lastchar == lc_other) {
        result.push_back('\"');
      } else if (lastchar == lc_bslash) {
        doubleBackslashCharacters(arg, cpos, result);
        result.push_back('\"');
      }
      result.push_back(arg[cpos]);
      lastchar = lc_space;
    
    } else if (arg[cpos] == '\"') {
      if (lastchar == lc_bslash) {
        doubleBackslashCharacters(arg, cpos, result);
      }
      result.push_back('\\');
      result.push_back(arg[cpos]);
      lastchar = lc_quotation;
    
    } else if (arg[cpos] == '\\') {
      result.push_back(arg[cpos]);
      lastchar = lc_bslash;
    
    } else {
      result.push_back(arg[cpos]);
      lastchar = lc_other;
    }
  }

  // If the last character was a space then the closing quotation mark have to be added
  if (lastchar == lc_space) 
    result.push_back('\"');

  return result;
}

#endif


int common::run(const std::string& program, const std::vector<std::string>& args, const std::string& out /* = std::string() */, const std::string& err /* = std::string() */)
{
  int ret = EXIT_FAILURE;

#ifdef __unix__
  size_t argc = args.size() + 2;    // +1 for the command name and +1 for the closing NULL;
  char** argv = (char**)malloc(sizeof(char*) * argc);
  
  argv[0] = strdup(program.c_str());
  argv[argc - 1] = NULL;
  
  for (size_t i = 0; i < args.size(); ++i) {
    argv[i + 1] = strdup(args[i].c_str());
  }
  ret = run_with_args(argv[0], argv, out.c_str(), err.c_str());
  for (size_t i = 0; i < argc; ++i) {
    free(argv[i]);
  }
  free(argv);

#else
  std::string command;
  if (program[0] != '\"')
    command = '\"' + program  + '\"';
  else
    command = program;
  
  for (size_t i = 0; i < args.size(); ++i) {
    command.push_back(' ');
    command.append(convertToWindowsCmdlineArgument(args[i]));
  }
  
  ret = run(command, false, out, err);
#endif
  
  return ret;
}

int common::run(const std::string& program, const std::vector<std::string>& args, std::ostream& out)
{
  int ret = EXIT_FAILURE;

#ifdef __unix__
  size_t argc = args.size() + 2;    // +1 for the command name and +1 for the closing NULL;
  char** argv = (char**)malloc(sizeof(char*) * argc);
  
  argv[0] = strdup(program.c_str());
  argv[argc - 1] = NULL;
  
  for (size_t i = 0; i < args.size(); ++i) {
    argv[i + 1] = strdup(args[i].c_str());
  }
  ret = run_with_args(argv[0], argv, out);
  for (size_t i = 0; i < argc; ++i) {
    free(argv[i]);
  }
  free(argv);

#else
  std::string command;
  if (program[0] != '\"')
    command = '\"' + program  + '\"';
  else
    command = program;
  
  for (size_t i = 0; i < args.size(); ++i) {
    command.push_back(' ');
    command.append(convertToWindowsCmdlineArgument(args[i]));
  }
  
  ret = ::run(command, out);
#endif
  
  return ret;
}

std::string common::findFile(const char *filename, const char *skip) {
  if(!filename || !skip) return std::string();

  char* path = getenv("PATH");
  if (!path)
    return std::string();

  char* copypath = strdup(path);
  if (!copypath)
    return std::string();

  char* dir = strtok(copypath, PATH_SEPARATOR);
  while (dir) {

#ifdef _WIN32
      size_t length = strlen(dir);
      if (length && dir[0]=='"'){
        size_t i=1;
        for(; i<length-1;i++){
          dir[i-1]=dir[i];
        }
        dir[i-1]='\0';
      }
#endif
    if ( !fs::exists(skip) || ( fs::exists(dir) && fs::exists(skip) && !fs::equivalent(dir, skip) ) ) {
      char buffer[MAXPATH];
      sprintf(buffer, "%s%s%s", dir, DIRDIVSTRING, filename);
      if (pathFileExists(buffer, false)) {
        free(copypath);
        return std::string(buffer);
      }

#ifdef _WIN32
      sprintf(buffer, "%s%s%s.com", dir, DIRDIVSTRING, filename);
      if (pathFileExists(buffer, false)) {
        free(copypath);
        return std::string(buffer);
      }

      sprintf(buffer, "%s%s%s.exe", dir, DIRDIVSTRING, filename);
      if (pathFileExists(buffer, false)) {
        free(copypath);
        return std::string(buffer);
      }

      sprintf(buffer, "%s%s%s.bat", dir, DIRDIVSTRING, filename);
      if (pathFileExists(buffer, false)) {
        free(copypath);
        return std::string(buffer);
      }
#endif
    }
    dir = strtok(NULL, PATH_SEPARATOR);
  }

  free(copypath);
  return std::string();
}

int common::setEnvironmentVariable(const char* envname, const char* envval) {
  int ret = 0;

#ifdef _WIN32
  ret = _putenv_s(envname, envval);
#elif __unix__
  ret = setenv(envname, envval, 1);
#endif

  return ret;
}


int common::unsetEnvironmentVariable(const char* envname) {
  int ret = 0;

#ifdef _WIN32
  ret = _putenv_s(envname, "");
#elif __unix__
  ret = unsetenv(envname);
#endif

  return ret;
}

void common::getEnvironmentVariables(std::vector<std::string>& variables)
{
#ifdef _WIN32
  LPTSTR lpszVariable;
  LPTCH lpvEnv;

  lpvEnv = GetEnvironmentStrings();
  lpszVariable = (LPTSTR) lpvEnv;

  while (*lpszVariable)
  {
    variables.push_back(std::string(lpszVariable));
    lpszVariable += lstrlen(lpszVariable) + 1;
  }
  FreeEnvironmentStrings(lpvEnv);

#elif __unix__
  for (char **env = environ; *env; ++env){
    variables.push_back(std::string(*env));
  }
#endif
}


const char * common::cextensions[] = {
  "c",
#ifdef _WIN32
  "C"
#endif
};

const char * common::cppextensions[] = {
  "cpp",
  "CPP",
  "cxx",
  "CXX",
  "cc",
  "CC",
  "cp",
  "CP",
  "c++",
  "C++",
#ifndef _WIN32
  "C"
#endif
  };

bool common::isclang(const std::string& ext)
{
  int bound = sizeof(cextensions)/sizeof(char*);
  for(int i=0;i<bound;i++){
    if(!strcmp(cextensions[i],ext.c_str()))
      return true;
  }
  return false;
}

bool common::iscpplang(const std::string& ext)
{
  int bound = sizeof(cppextensions)/sizeof(char*);
  for(int i=0;i<bound;i++){
    if(!strcmp(cppextensions[i],ext.c_str()))
      return true;
  }
  return false;
}

bool common::isPrefix(const std::string& str, const std::string& test, std::string& remain, bool skipeq)
{
  bool prefix = true;
  remain = "";

  unsigned i = 0;
  while (i < str.length() && i < test.length() && (str[i] == test[i])) { 
    i++;
  }

  if (i < test.length()) 
    prefix = false;

  remain = str.substr(i);
  if (skipeq && remain.length() && remain[0] == '=')
    remain = remain.substr(1);

  return prefix;
}

static bool fileIsGreater(std::pair<std::string, unsigned long long> p1, std::pair<std::string, unsigned long long> p2)
{
  return p1.second > p2.second;
}

void common::sortBySizeDescending(std::list<std::string>& fileList, bool skipFirst) {

  std::vector<std::pair<std::string, unsigned long long> >  fileSizes;
  std::list<std::string>::iterator it = fileList.begin();

  if(skipFirst) 
    it++;

  for(; it != fileList.end(); ++it)
  {
    unsigned long long length = fs::file_size(it->c_str());
    fileSizes.push_back(std::make_pair(*it, length));
  }
  
  std::sort(fileSizes.begin(), fileSizes.end(), fileIsGreater);

  if(skipFirst)
    fileList.erase(++(fileList.begin()), fileList.end());
  else
    fileList.clear();
  
  
  for(std::vector<std::pair<std::string, unsigned long long> >::iterator it1 = fileSizes.begin(); it1 != fileSizes.end(); it1++)
    fileList.push_back(it1->first);    
}

bool common::loadFltpFile(const std::string& filename, std::vector<std::string>& fltpPaths, std::vector<std::string>& fltpExcludePaths, bool pathLower /* = false*/)
{
  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open())
    return false;

  fltpPaths.clear();
  fltpExcludePaths.clear();

  std::string line;
  while (getline(ifs, line)) {
    size_t len = line.length();
    if (!len)
      continue;
    if (line.at(len-1) == 0xD) { // handle DOS line-ends in unix
      if (len == 1) // if this line contains only this line-end character it is also skipped
        continue;
      line = line.substr(0, len-1);
    }

    if (pathLower)
      stringLower(line);

    if (line[0] != '-') {
      fltpPaths.push_back(line);
      WriteMsg::write(CMSG_DUINFO_FLTP_PATH, line.c_str());
    } else {
      fltpExcludePaths.push_back(line.substr(1));
      WriteMsg::write(CMSG_DUINFO_FLTP_EXCL_PATH, line.c_str() + 1);
    }
  }

  ifs.close();
  return true;
}

std::string common::replaceExtension(const std::string& filename, const std::string& new_extension)
{
  std::string new_filename = filename;
  replaceExtensionInPlace(new_filename, new_extension);
  return new_filename;
}

void common::replaceExtensionInPlace(std::string& filename, const std::string& new_extension)
{
  size_t dot_pos = filename.find_last_of(".");
  if (dot_pos != std::string::npos)
    filename = filename.substr(0, dot_pos) + new_extension;
  else
    filename += new_extension;
}

bool common::loadStringListFromFile(const std::string& listFileName, std::list<std::string>& fileNameList)
{
  if (!listFileName.empty()) {
    std::ifstream ifs(listFileName.c_str());
    if (ifs.is_open()) {
      std::string tmp;
      while (std::getline(ifs, tmp)) {
        if (!tmp.length())
          continue;
        trim(tmp);
        if (!tmp.empty())
          fileNameList.push_back(tmp);
      }
      ifs.close();
      return true;
    } else {
      common::WriteMsg::write(CMSG_LISTFILE_NOT_ACCESSIBLE, listFileName.c_str());
    }
  }
  return false;
}

std::string common::getLockFileName(const std::string& fileName)
{
  return fileName + ".lock";
}
