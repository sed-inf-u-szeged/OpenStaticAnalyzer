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

#ifndef _CANLIB_M_H_
#define _CANLIB_M_H_

#define CMSG_MSG_MISSING_ARCHIVE_ERROR                     WriteMsg::mlError, "Unable to open archive file '%s'!\n"
#define CMSG_MSG_MISSING_ARCHIVE_NAME_ERROR                WriteMsg::mlError, "Archive filename is missing!\n"
#define CMSG_MSG_FAILED_TO_ADD_ERROR                       WriteMsg::mlError, "Failed to add file `%s` to the archive! (%s)\n"
#define CMSG_MSG_FAILED_TO_EXTRACT_ERROR                   WriteMsg::mlError, "Failed to extract file `%s` from the archive! (%s)\n"
#define CMSG_MSG_FAILED_TO_DELETE_ERROR                    WriteMsg::mlError, "Failed to delete file `%s` from the archive! (%s)\n"
#define CMSG_MSG_NO_OPERATION_MODE_ERROR                   WriteMsg::mlError, "No operation mode is set!\n"
#define CMSG_MSG_NO_SUCH_FILE_IN_THE_ARCHIVE_ERROR         WriteMsg::mlError, "There is no '%s' file in the archive!\n"
#define CMSG_MSG_FILE_ERROR                                WriteMsg::mlError, "Error! '%s'  (%s)\n"
#define CMSG_MSG_OUTPUT_MUST_BE_A_DIRECTORY_ERROR          WriteMsg::mlError, "If there are more than one files to be extracted, then the output `%s` must be a directory!\n"
#define CMSG_MSG_FILE_ALREADY_EXISTS_WARNING               WriteMsg::mlWarning, "Warning! File '%s' already exists in the archive and replace is disabled!\n"

#endif
