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

#ifndef _COMMON_LIB_MESSAGES_H_
#define _COMMON_LIB_MESSAGES_H_
// Arguments
#define  CMSG_DUINFO_OPTIONFILE          common::WriteMsg::mlDDebug,   "Debug: [common::processOptionFile] Option file: \"%s\"\n"
#define  CMSG_DUINFO_FAILED_TO_OPEN      common::WriteMsg::mlDDebug,   "Debug: [common::processOptionFile] Cannot open file: \"%s\"\n"
#define  CMSG_DUINFO_READ_PARAM          common::WriteMsg::mlDDebug,   "Debug: [common::processOptionFile] read[%s]\n"
#define  CMSG_NO_OPTION_GIVEN            common::WriteMsg::mlError,   "Error: No option was given\n"
#define  CMSG_AMBIGUOUS_PARAM            common::WriteMsg::mlWarning, "Warning: Ambiguous parameter usage\n"
#define  CMSG_FAILED_PROCESSING          common::WriteMsg::mlWarning, "Warning: Cannot process the '%s' option\n"
#define  CMSG_NO_DEFAULT_VALUE           common::WriteMsg::mlWarning, "Warning: The default value of '%s' option is used but it does not have default value\n"
#define  CMSG_UNRECOGNIZED_PARAM         common::WriteMsg::mlWarning, "Warning: Unrecognized parameter: '%s'\n"

// DirectoryFilter
#define  CMSG_CANT_PARSE                 common::WriteMsg::mlError,   "Error: [DirectoryFilter::isFilteredOut] Cannot parse '%s'. Regular expressions error: '%s'\n"

//FileSup
#define  CMSG_BUFFER_TOO_SMALL           common::WriteMsg::mlError,   "Error: [common::getPrivateProfile...] The given buffer is too small\n"
#define  CMSG_APPNAME_REQUIRED           common::WriteMsg::mlError,   "Error: [common::getPrivateProfileSection] 'appname' is not given\n"
#define  CMSG_TEMPFILE_COULDNT_CREATED   common::WriteMsg::mlError,   "Error: [common::writePrivateProfileString] Temproary file could not be created.\n"
#define  CMSG_DUINFO_FLTP_PATH           common::WriteMsg::mlDDebug,   "Debug: [common::loadFltpFile] FLTP path: \"%s\"\n"
#define  CMSG_DUINFO_FLTP_EXCL_PATH      common::WriteMsg::mlDDebug,   "Debug: [common::loadFltpFile] FLTP exclude path: \"%s\"\n"
#define  CMSG_LISTFILE_NOT_ACCESSIBLE    common::WriteMsg::mlDDebug,   "Debug: [common::loadStringListFromFile] Cannot open the input list file: \"%s\"\n"

//WriteMEssage
#define  CMSG_NOT_TAKEN_INTO_ACCOUNT     common::WriteMsg::mlWarning, "Warning: -silent parameter is givel, -ml is not taken into account\n"
#define  CMSG_DUINFO_ML_SILENT           common::WriteMsg::mlDDebug,   "Debug: Message level is set to 0 (silent)\n"
#define  CMSG_DUINFO_ML_ERROR            common::WriteMsg::mlDDebug,   "Debug: Message level is set to 1 (error)\n"
#define  CMSG_DUINFO_ML_WARNING          common::WriteMsg::mlDDebug,   "Debug: Message level is set to 2 (warning)\n"
#define  CMSG_DUINFO_ML_NORMAL           common::WriteMsg::mlDDebug,   "Debug: Message level is set to 3 (normal)\n"
#define  CMSG_DUINFO_ML_DEBUG            common::WriteMsg::mlDDebug,   "Debug: Message level is set to 4 (debug)\n"
#define  CMSG_DUINFO_SET_ML              common::WriteMsg::mlDDebug,   "Debug: Message level is set to %d (debug)\n"

//StringSup
#define CMSG_EX_CANNOT_BE_CONVERTED(STR) "The string \"" + STR + "\" cannot be converted into number."


//Stat
#define CMSG_EX_PROC_READ_ERROR          "Faild to read the stats from the proc file system."
#define CMSG_EX_STAT_WRITE_ERROR         "Faild to open stat file for writing."
#endif
