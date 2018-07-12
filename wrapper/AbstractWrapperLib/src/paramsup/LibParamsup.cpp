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

#include "AbstractWrapperLib/inc/paramsup/LibParamsup.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>

#include <list>
#include <string>

using namespace std;

#define LIB_PARAMSUP    "LibParamsup"

// Lib arguments without parameters. These arguments haven't got any parameter.
static const char* lib_args [] = {
  "/nologo",
  "/verbose"
};

// Lib arguments with parameters. These arguments have got parameters after the colon.
static const char* lib_par_args [] = {
  "/errorreport:",
  "/machine:",
  "/libpath:",
  "/name:",
  "/subsystem:",
  "/export:",
  "/include:"
};

// Lib arguments with/without parameters. These arguments are allowed to use without any parameters and with parameters too.
// If they have got any parameter there is a colon before the parameter.
static const char* lib_wo_par_args [] = {
  "/wx",
  "/list",
  "/nodefaultlib",
  "/def",
  "/ltcg"
};


bool ColumbusWrappers::LibWrapperSup::isObjectFile(string filename) {
  string file, ext;
  if (common::splitExt(filename, file, ext)) {
    if ( common::stringLower(ext)  == ".obj") {
      return true;
    }
  }
  return false;
}


bool ColumbusWrappers::LibWrapperSup::isArchiveFile(string filename) {
  string file, ext;
  if (common::splitExt(filename, file, ext)) {
    if ( common::stringLower(ext) == ".lib") {
      return true;
    }
  }
  return false;
}


ColumbusWrappers::ParErrorCode ColumbusWrappers::LibWrapperSup::examineNotHandledArgument(const list<string>::iterator& it, ArchiveArgs& libArgs) {

  string remain = "";
  size_t n;

  for (n = 0; n < sizeof(lib_args)/sizeof(char*); n++) {
    if (common::stringLower(*it) == lib_args[n]) {
      libArgs.not_handled_args.push_back(*it);
      return EC_FOUND;
    }
  }

  for (n = 0; n < sizeof(lib_par_args)/sizeof(char*); n++) {
    if (common::isPrefix(common::stringLower(*it), lib_par_args[n], remain)) {
      if (!remain.empty()) {
        libArgs.not_handled_args.push_back(*it);
        return EC_FOUND;
      } else {
        return EC_ERROR;
      }
    }
  }

  for (n = 0; n < sizeof(lib_wo_par_args)/sizeof(char*); n++) {
    if (common::stringLower(*it) == lib_wo_par_args[n]) {
      libArgs.not_handled_args.push_back(*it);
      return EC_FOUND;
    } else if (common::isPrefix(common::stringLower(*it), string(lib_wo_par_args[n]) + ":", remain)) {
      if (!remain.empty()) {
        libArgs.not_handled_args.push_back(*it);
        return EC_FOUND;
      } else {
        return EC_ERROR;
      }
    } else {
      continue;
    }
  }

  return EC_NOT_FOUND;
}


bool ColumbusWrappers::LibWrapperSup::archiveArguments(std::list<std::string> args, ArchiveArgs& libArgs, Warnings& libWarnings) {
  ColumbusWrappers::ParErrorCode ec = EC_FOUND;

  enum  {
    DoesNotMatter,
    Archive,
    Extract,
    Remove,
  } runPurpose;

  runPurpose = DoesNotMatter;
  libArgs.archive_mode = "-w";
  libArgs.need_create =  true;
  string remain = "";
  string tmp_in = "";
  string outFile = "";
  string extractModulName = "";
  string firstLibFile = "";
  ColumbusWrappers::ParErrorCode ret = EC_FOUND;
  string actualArgument = "";

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++) {

    if ((*args_it)[0] != '/') {

      if (isObjectFile(*args_it)) {
        resolveFilePatterToFiles(common::correctDirDivs(*args_it),libArgs.input_files);//.push_back(common::correctDirDivs(*args_it));
        if (libArgs.first_input.empty()) {
          libArgs.first_input = libArgs.input_files.front();
        }
      } else if (isArchiveFile(*args_it)) {
        libArgs.archive_file = common::correctDirDivs(*args_it);
        if (libArgs.first_input.empty()) {
          libArgs.first_input = common::correctDirDivs(*args_it);
        } else {
          libWarnings.unrec_args.push_back(libArgs.archive_file);
        }
        if (firstLibFile.empty()){
          firstLibFile = common::correctDirDivs(*args_it);
        }
        
      } else {
        libWarnings.unrec_args.push_back(*args_it);
      }

    } else if (common::isPrefix(common::stringLower(*args_it), "/out:", remain)) {

    
      if (!remain.empty()) {
        outFile = common::correctDirDivs(remain);
      } else {
        actualArgument = *args_it;
        ret = EC_ERROR;
        break;
      }

    } else if (common::isPrefix(common::stringLower(*args_it), "/remove:", remain)) {
      libArgs.need_create =  false;
      libArgs.delete_or_extract = true;
      
      runPurpose = Remove;
      if (!remain.empty()) {
        libArgs.archive_operations.push_back("-d");
        resolveFilePatterToFiles(remain,libArgs.input_files);
    
       // libArgs.input_files.push_back(remain);
      } else {
        actualArgument = *args_it;
        ret = EC_ERROR;
        break;
      }

    } else if (common::isPrefix(common::stringLower(*args_it), "/extract:", remain)) {
    
      libArgs.need_create =  false;
      runPurpose = Extract;
      if (!remain.empty()) {
        libArgs.archive_operations.push_back("-x");

        char end;
        if (remain[remain.length()-1] == '"' || remain[remain.length()-1] == '\'') {
          end = remain[remain.length()-2];
        } else {
          end = remain[remain.length()-1];
        }
        if (end == '\\' || end == '/' || end == '.') {    //such as /EXTRACT:/ 
          tmp_in = "";
        } else {
          tmp_in = remain;
        }
        resolveFilePatterToFiles(tmp_in,libArgs.input_files);

        extractModulName = tmp_in;
   
      } else {
        actualArgument = *args_it;
        ret = EC_ERROR;
        break;
      }

    } else if ((ec = ColumbusWrappers::LibWrapperSup::examineNotHandledArgument(args_it, libArgs)) == EC_FOUND) {
    
    } else if (ec == EC_ERROR) {

      actualArgument = *args_it;
      ret = EC_ERROR;
      break;

    } else {

      libWarnings.unrec_args.push_back(*args_it);

    }

  }

  if (ret == EC_ERROR) {
    ColumbusWrappers::writeErrorMsg(LIB_PARAMSUP, CMSG_LIB_PARAMSUP_WRONG_LIB_ARGUMENT, actualArgument.c_str());
    return false;
  }

  if (runPurpose == Extract) {
    
    libArgs.asgMemberName = extractModulName;
    libArgs.asg_file = outFile;
    libArgs.archive_file = libArgs.first_input;
    libArgs.need_create =  false;
    libArgs.delete_or_extract = true;
    
  } else if (runPurpose == Remove) {
    libArgs.asg_file = outFile;
    libArgs.archive_file = libArgs.first_input;
    libArgs.no_output = false;
  } else {

    if ( !outFile.empty()) {
      libArgs.archive_file =outFile;
      libArgs.no_output = false;
    }
  }
  //organize params.


  return true;
}