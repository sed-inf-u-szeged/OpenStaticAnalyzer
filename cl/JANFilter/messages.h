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

#ifndef _JAN2FILTER_MESSAGE_H
#define _JAN2FILTER_MESSAGE_H

//ERROR messages
#define CMSG_ERROR_MSG              WriteMsg::mlError, "%s\n", message
#define CMSG_CANNOT_OPEN_FILE       WriteMsg::mlError, "Error: Cannot open fltp file (\"%s\")\n"
#define CMSG_CANNOT_READ_FILE       WriteMsg::mlError, "Error: Error happened during reading file: \"%s\"\n"

//Warning messages
#define CMSG_WRONG_FILE_FORMAT          WriteMsg::mlWarning, "Warning: Extension of input file is neither .jsi nor .ljsi.\n"
#define CMSG_FILTER_DOES_NOT_EXIST      WriteMsg::mlWarning, "Warning: Filter file (.fjsi) does not exist.\n"
#define CMSG_FILTER_FILE_DEPRECATED     WriteMsg::mlWarning, "Warning: Filter file (.fjsi) is older than schema file (.jsi or .ljsi). Filter file is not used.\n"
#define CMSG_FILTER_CANNOT_LOAD         WriteMsg::mlWarning, "Warning: Filter cannot be loaded (%s)\n"

//Debug messages
#define CMSG_LOAD_FILTER_FILE           WriteMsg::mlDebug, "Debug: Loading filter file: %s\n"
#define CMSG_SAVE_FILTER_FILE           WriteMsg::mlDebug, "Debug: Saving filter file: %s\n"

#endif
