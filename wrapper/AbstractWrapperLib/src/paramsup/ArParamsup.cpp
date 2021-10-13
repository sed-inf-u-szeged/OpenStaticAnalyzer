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

#include <AbstractWrapperLib/inc/paramsup/ArParamsup.h>
#include <AbstractWrapperLib/inc/messages.h>
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>

#include <list>
#include <string>
#include <cstring>

using namespace std;

#define AR_PARAMSUP "ArParamsup"

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

bool ColumbusWrappers::ArWrapperSup::archiveArguments(list<string> args, ColumbusWrappers::ArchiveArgs& archiveArgs, ColumbusWrappers::Warnings& arWarnings)
{
  bool operationSpecified = false;
  bool relposNeeded = false;
  bool countNeeded = false;
  bool archiveFound = false;

  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); args_it++)
  {
    const char* arg = args_it->c_str();
    bool processingOption = false;
    if (arg[0] == '-')
    {
      if (strcmp(arg, "-X32_64") == 0)
        continue;

      if (arg[1] == '-')
      {
        if (strcmp(arg, "--plugin") && strcmp(arg, "--target"))
        {
          ++args_it; // skip the next argument;
          continue;
        }
        else if (strcmp(arg, "--help") && strcmp(arg, "--version"))
        {
          continue;
        }
        else
        {
          arWarnings.unrec_args.push_back(arg);
          continue;
        }
      }

      processingOption = true;
      arg += 1;
    } 

    if (processingOption || !operationSpecified)
    {
      while (arg[0] != 0)
      {
        switch (arg[0])
        {
          case 'd':
            archiveArgs.archive_operations.push_back("-delete");
            operationSpecified = true;
            break;

          case 'm':
          case 'p':
            operationSpecified = true;
            archiveArgs.needToWrap = false;
            break;

          case 'q':
          case 'r':
            archiveArgs.archive_operations.push_back("-add");
            operationSpecified = true;
            break;

          case 's':
          case 't':
            operationSpecified = true;
            archiveArgs.needToWrap = false;
            break;

          case 'x':
            archiveArgs.archive_operations.push_back("-extract");
            operationSpecified = true;
            break;

          case 'a':
          case 'b':
          case 'i':
            relposNeeded = true;
            break;

          case 'c':
          case 'D':
          case 'f':
          case 'l':
            break;

          case 'N':
            arWarnings.can_warning.push_back("N modifier is used!");
            countNeeded = true;
            break;

          case 'o':
          case 'P':
          case 'S':
          case 'T':
            break;

          case 'u':
            // At the moment the CANLib unconditionally overwrites the older contnent.
            // The actual zip library does not stores the file creation date hence
            // this behavour can not be implemented.
            arWarnings.can_warning.push_back("u modifier is used!");
            break;

          case 'U':
          case 'v':
          case 'V':
            break;

          default:
            arWarnings.unrec_args.push_back(arg);
            break;
        }
        ++arg;
      }
    }
    else if (relposNeeded)
    {
      relposNeeded = false;
    }
    else if (countNeeded)
    {
      countNeeded = false;
    }
    else if (archiveFound)
    {
      archiveArgs.input_files.push_back(arg);
    }
    else
    {
      archiveArgs.archive_file = arg;
      archiveFound = true;
    }
  }
  return true;
}
