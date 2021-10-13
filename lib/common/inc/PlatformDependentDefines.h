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

#ifndef __PlatformDependentDefines_H
#define __PlatformDependentDefines_H

#if defined(__linux__)


#define COPY_COMMAND          "cp -f "           // copy
#define MOVE_COMMAND          "mv -f "           // move
#define DEL_COMMAND           "rm -f "           // delete
#define MKDIR_COMMAND         "mkdir "           // create a directory
#define RENAME_COMMAND        "mv -f "           // rename
#define CL_PAR_PLUS           "'"                // 'one parameter'
#define QUOTE                 '\''               // 'one parameter'
#define PATH_SEPARATOR        ":"

#define DIRDIVSTRING          "/"
#define DIRDIVCHAR            '/'
#define LONGDIRPREFIXSTRING   L""

#define SETENVVAR             "export"
#define ENV_VAL_PLUS          "'"

#define SCRIPTEXT             ".sh"
#define SCRIPTSTART           "#!/bin/sh"
#define BINARYEXT             ""

#elif defined(_WIN32)

#define COPY_COMMAND          "cmd /C copy /Y "    // copy
#define MOVE_COMMAND          "cmd /C move /Y "    // move
#define DEL_COMMAND           "cmd /C del /Q /F "  // delete
#define MKDIR_COMMAND         "cmd /C md "         // create a directory
#define RENAME_COMMAND        "cmd /C ren "        // rename
#define CL_PAR_PLUS           "\""                 // 'one parameter'
#define QUOTE                 '"'                  // 'one parameter'
#define PATH_SEPARATOR        ";"

#define DIRDIVSTRING          "\\"
#define DIRDIVCHAR            '\\'
#define LONGDIRPREFIXSTRING    L"\\\\?\\"
#define LONGDIRPREFIXSTRING_A  "\\\\?\\"

#define SETENVVAR             "set"
#define ENV_VAL_PLUS          ""

#define SCRIPTEXT             ".bat"
#define SCRIPTSTART           "@echo off"
#define BINARYEXT             ".exe"
#endif


#endif
