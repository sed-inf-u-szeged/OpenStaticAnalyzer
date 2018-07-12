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

#ifndef _JSAN2CHANGEPATH_MESSAGES_H_
#define _JSAN2CHANGEPATH_MESSAGES_H_

#define CMSG_MISSING_INPUT_FILES            WriteMsg::mlError,  "Error: Missing input files\n"
#define CMSG_MISSING_FROM_PARAMETER         WriteMsg::mlError,  "Error: The -changepathfrom parameter is empty\n"
#define CMSG_LOADING_FILE                   WriteMsg::mlNormal, "Loading file: %s\n"
#define CMSG_SAVING_FILE                    WriteMsg::mlNormal, "Saving file: %s\n"
#define CMSG_REPLACING_PATH                 WriteMsg::mlNormal, "Replacing the paths\n"

#endif
