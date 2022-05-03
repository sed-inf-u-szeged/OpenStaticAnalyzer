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

#ifndef _ARCHCPP_M_H_
#define _ARCHCPP_M_H_

#define CMSG_EX_ERROR_BUFFER_CREATE "Error : buffer can't be created :"
#define CMSG_EX_ERROR_OPEN_FILE(FILENAME) "Error: opening file :" + FILENAME
#define CMSG_EX_FAILED_DELETE "Error : in delete file :"
#define CMSG_EX_FAILED_RENAME "Error : in rename file :"
#define CMSG_EX_MISSING_FILE_TYPE_INFORMATION "Missing file type information "
#define CMSG_EX_CORRUPT_CONTENT "Error: content is corrupted"
#define CMSG_EX_FILE_NOT_EXIST "File isn't exist"
#define CMSG_ERROR_SET_FILE_STAMP common::WriteMsg::mlError, "Error about set file stamp\n"
#define CMSG_ERROR_GET_FILE_STAMP common::WriteMsg::mlError, "Error about get file stamp\n"
#define CMSG_EX_WRONG_BINARY_VERSION(BINVER_REQ, BINVER_FOUND) "Wrong binary version (" + BINVER_REQ + " required, " + BINVER_FOUND + " found)."
#define CMSG_MSG_ERROR_DURING_ADDING_TO_ARCHIVE_WARNING    common::WriteMsg::mlDebug,   "Error during adding to archive: %s\n"

#endif
