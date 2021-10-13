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

bool ColumbusWrappers::LibWrapperSup::isObjectFile(string filename) {
  string file, ext;
  if (common::splitExt(filename, file, ext)) 
  {
    if (common::stringLower(ext)  == ".obj")
      return true;
  }
  return false;
}

bool ColumbusWrappers::LibWrapperSup::isArchiveFile(string filename) {
  string file, ext;
  if (common::splitExt(filename, file, ext)) 
  {
    if (common::stringLower(ext) == ".lib")
      return true;
  }
  return false;
}


bool ColumbusWrappers::LibWrapperSup::archiveArguments(std::list<std::string> args, ArchiveArgs& libArgs, Warnings& libWarnings)
{
  string remaining;
  bool firstObjectFound = false;
  for (list<string>::iterator args_it = args.begin(); args_it != args.end(); ++args_it)
  {
    const string& arg = *args_it;

    if (arg[0] != '/') 
    {
      if (isObjectFile(arg)) 
      {
        list<string> filelist;
        resolveFilePatterToFiles(arg, filelist);

        for (const auto& filename : filelist)
        {
          if (isObjectFile(filename))
          {
            libArgs.input_files.push_back(filename);
            if (!firstObjectFound && libArgs.archive_file.empty())
            {
              libArgs.archive_file = common::replaceExtension(filename, "lib");
              firstObjectFound = true;
            }
          }
        }
      } 
      else if (isArchiveFile(arg)) 
      {
        if (libArgs.archive_file.empty())
          libArgs.archive_file = arg;
        else
        {
          libWarnings.can_warning.push_back("Multiple lib input is not handled yet!");
        }
      } else {
        libWarnings.unrec_args.push_back(arg);
      }
    }
    else if (common::isPrefix(arg, "/out:", remaining, false, false)) 
    {
      if (!remaining.empty())
        libArgs.archive_file = remaining;
      else 
        return false;

    } 
    else if (common::isPrefix(arg, "/remove:", remaining, false, false))
    {
      if (!remaining.empty())
      {
        libArgs.archive_operations.push_back("-delete");
        libArgs.input_files.push_back(remaining);
      }
      else
        return false;
    }
    else if (common::isPrefix(arg, "/extract:", remaining, false, false)) 
    {
      if (!remaining.empty())
      {
        libArgs.archive_operations.push_back("-extract");
        libArgs.input_files.push_back(remaining);
      }
      else
        return false;
    }
    else if (common::isPrefix(arg, "/def", remaining, false, false) ||
      common::isPrefix(arg, "/errorreport:", remaining, false, false) ||
      common::isPrefix(arg, "/export:", remaining, false, false) ||
      common::isPrefix(arg, "/include:", remaining, false, false) ||
      common::isPrefix(arg, "/list", remaining, false, false) ||
      common::isPrefix(arg, "/ltcg", remaining, false, false) ||
      common::isPrefix(arg, "/machine:", remaining, false, false) ||
      common::isPrefix(arg, "/name:", remaining, false, false) ||
      common::isPrefix(arg, "/nodefaultlib:", remaining, false, false) ||
      common::isPrefix(arg, "/nologo", remaining, false, false) ||
      common::isPrefix(arg, "/subsystem:", remaining, false, false) ||
      common::isPrefix(arg, "/verbose", remaining, false, false) ||
      common::isPrefix(arg, "/wx:", remaining, false, false))
    {
      // Nothing to do.
    }
    else 
    {
      libWarnings.unrec_args.push_back(arg);
    }
  }

  if (libArgs.archive_operations.empty())
    libArgs.archive_operations.push_back("-add");
  
  if (libArgs.archive_file.empty())
    return false;

  return true;
}
