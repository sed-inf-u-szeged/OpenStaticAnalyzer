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

#include "AbstractWrapperLib/inc/paramsup/ArParamsup.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>

#include <list>
#include <string>

using namespace std;

#define AR_PARAMSUP "ArParamsup"

// These arguments haven't got any equivalent arguments in CANLib so these are not handled yet.
static char not_handled_ar_args[] = {
  'p','t','s','I','N','o','P','D',
  'f','S','T','u','v','V'
};


bool ColumbusWrappers::ArWrapperSup::isObjectFile(string filename) {
  string file, ext;
  if (common::splitExt(filename, file, ext)) {
    if (ext == ".o" || ext == ".ao" || ext == ".lo") {
      return true;
    }
  }
  return false;
}


bool ColumbusWrappers::ArWrapperSup::isArchiveFile(string filename) {
  string file, ext;
  if (common::splitExt(filename, file, ext)) {
    if (ext == ".a") {
      return true;
    }
  }
  return false;
}


void ColumbusWrappers::ArWrapperSup::examineArgument(const list<string>::iterator& it, ArchiveArgs& archiveArgs, Warnings& arWarnings) {

  string tmp;
  if ((*it)[0] == '-') {
    tmp = it->substr(1);
  } else {
    tmp = *it;
  }

  if (tmp.find_first_of("a") != string::npos) {
    archiveArgs.put_after = true;
  }

  if (tmp.find_first_of("bi") != string::npos) {
    archiveArgs.put_before = true;
  }

  for (size_t i = 0; i != tmp.length(); i++) {

    for (size_t j = 0; j < sizeof(not_handled_ar_args)/sizeof(char); j++) {
      if (tmp[i] == not_handled_ar_args[j]) {
        archiveArgs.not_handled_args.push_back(string(1,tmp[i]));
      }
    } 

    if (tmp[i] == 'o') {
       archiveArgs.original_dates = true;
    } else if (tmp[i] == 'c') {

      archiveArgs.need_create = true;

    } else if (tmp[i] == 'd') {

      archiveArgs.archive_operations.push_back("-d");
      archiveArgs.delete_or_extract = true;

    } else if (tmp[i] == 'm') {

      archiveArgs.archive_operations.push_back("-h");

    } else if (tmp[i] == 'q') {

      archiveArgs.archive_modifiers.push_back("-R");
      if (archiveArgs.put_before) {
        archiveArgs.archive_modifiers.push_back("-b");
        archiveArgs.archive_operations.push_back("-p");
      } else if (archiveArgs.put_after) {
        archiveArgs.archive_modifiers.push_back("-B");
        archiveArgs.archive_operations.push_back("-p");
      } else {
        archiveArgs.archive_operations.push_back("-a");
      }

    } else if (tmp[i] == 'r') {

      archiveArgs.archive_modifiers.push_back("-r");
      if (archiveArgs.put_before) {
        archiveArgs.archive_modifiers.push_back("-b");
        archiveArgs.archive_operations.push_back("-p");
      } else if (archiveArgs.put_after) {
        archiveArgs.archive_modifiers.push_back("-B");
        archiveArgs.archive_operations.push_back("-p");
      } else {
        archiveArgs.archive_operations.push_back("-a");
      }

    } else if (tmp[i] == 'x') {

      archiveArgs.archive_operations.push_back("-e");
      archiveArgs.delete_or_extract = true;

    } else if (tmp[i] == 'a' || tmp[i] == 'b' || tmp[i] == 'i') {
      //do nothing it has set previously
    } else {
      arWarnings.unrec_args.push_back(string(1,tmp[i]));
    }
  }

}


bool ColumbusWrappers::ArWrapperSup::archiveArguments(list<string> args, ArchiveArgs& archiveArgs, Warnings& arWarnings) {
  archiveArgs.archive_mode = "-l";

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++) {

    if ((*args_it)[0] != '-') {

      if (isObjectFile(*args_it)) {

        list<string>::iterator tmp_it = args_it;
        tmp_it++;
        if (tmp_it != args.end()) {
          if (isArchiveFile(*tmp_it)) {
            archiveArgs.asg_file = *args_it;
          } else {
            archiveArgs.input_files.push_back(*args_it);
          }
        } else {
          archiveArgs.input_files.push_back(*args_it);
        }

      } else if (isArchiveFile(*args_it)) {

        archiveArgs.no_output = false;
        archiveArgs.archive_file = *args_it;

      } else {

        ColumbusWrappers::ArWrapperSup::examineArgument(args_it, archiveArgs, arWarnings);

      }

    } else {

      if ((args_it->length() >= 2) && (*args_it)[1] == '-') {
        arWarnings.unrec_args.push_back(*args_it);

        // skip the argument of the --???? parameter
        args_it++;
        if (args_it == args.end())
          break;

        arWarnings.unrec_args.push_back(*args_it);
        continue;

      } else  {

        ColumbusWrappers::ArWrapperSup::examineArgument(args_it, archiveArgs, arWarnings);

      }

    }

  }

  if (archiveArgs.archive_file.empty() && !archiveArgs.input_files.empty()) {
    ColumbusWrappers::writeErrorMsg(AR_PARAMSUP, CMSG_AR_PARAMSUP_NO_OUTPUT_ARCHIVE_FILE);
    return false;
  }

  return true;
}
