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

#ifndef _IO_LIB_MESSAGES_H_
#define _IO_LIB_MESSAGES_H_

// open exceptions
#define CMSG_EX_OPEN_FILE            "Cannot open the file: "
#define CMSG_EX_OPEN_TWO_FILES       "Cannot open two files at the same time"
#define CMSG_EX_OPEN_STREAMBUF       "Cannot open streambuffer"
#define CMSG_EX_OPEN_ZIPPED_MODE     "Cannot open ZippedIO with not zipped mode"
#define CMSG_EX_OPEN_XML_ONLY_WRITE  "You can open SimpleXmlIO only for writing"

// file exceptions
#define CMSG_EX_FILE_NOT_OPEN        "File is not open"
#define CMSG_EX_FILE_READ_ONLY       "File is opened only for reading"
#define CMSG_EX_FILE_WRITE_ONLY      "File is opened only for writing"
#define CMSG_EX_FILE_ZIPPED          "The opened file is zipped"

// xml exceptions
#define CMSG_EX_XML_DECLARATION_TOP  "XML declaration can be writen only to the top of the file"
#define CMSG_EX_XML_DTD_TOP          "XML DTD can be writen only to top of the file"
#define CMSG_EX_XML_LAST_OPERATION   "Last operation is not Tag Open or Attribute Write"
#define CMSG_EX_XML_TAG_NOT_FOUND    "Opened tag is not found"
#define CMSG_EX_XML_WRONG_TAG        "Wrong tag format"
#define CMSG_EX_XML_WRONG_TAG_FORMAT "Wrong tag format : "

// misc exceptions
#define CMSG_EX_WRONG_SIZE           "Wrong type size"
#define CMSG_EX_TOO_LONG_STRING      "The string length is greater than 65535"
#define CMSG_EX_MEMORY_ALLOCATION    "Memory allocation error"

#endif // _IO_LIB_MESSAGES_H_
