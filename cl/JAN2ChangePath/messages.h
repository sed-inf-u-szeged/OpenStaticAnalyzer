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

#ifndef _JAN2JML_MESSAGE_H
#define _JAN2JML_MESSAGE_H

//ERROR messages
#define CMSG_MISSING_INPUT_FILES            WriteMsg::mlError, "Error: Missing input files\n"
#define CMSG_MISSING_FROM_PARAMETER         WriteMsg::mlError, "Error: The -from parameter is empty\n"
#define CMSG_CANNOT_LOAD_FILE               WriteMsg::mlError, "Error: Cannot load file: \"%s\"\n"
#define CMSG_CANNOT_SAVE_FILE               WriteMsg::mlError, "Error: Cannot save file: \"%s\"\n"
#define CMSG_ERROR_WHILE_TOUCHING_FILTER    WriteMsg::mlError, "Error: Error while touching the filter file (\"%s\"): \"%s\"\n"

//Normal messages
#define CMSG_START_JAN2CHANGEPATH           WriteMsg::mlNormal, "Changing path from '%s' to '%s'\n"
#define CMSG_LOADING                        WriteMsg::mlNormal, "Loading file: \"%s\"\n"
#define CMSG_REPLACING_PATH                 WriteMsg::mlNormal, "Replacing the paths\n"
#define CMSG_WRITING_PATH                   WriteMsg::mlNormal, "Saving file: \"%s\"\n"
#define CMSG_TOUCHING_FILTER                WriteMsg::mlNormal, "Touching the filter file: \"%s\"\n"

//Debug messages
#define CMSG_DONE                           WriteMsg::mlDebug,  "Debug: Paths are changed\n"

#endif