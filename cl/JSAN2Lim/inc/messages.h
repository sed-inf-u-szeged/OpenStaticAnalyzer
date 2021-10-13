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

#ifndef _JSAN2LIM_MESSAGE_H
#define _JSAN2LIM_MESSAGE_H

//ERROR messages
#define CMSG_MISSING_INPUT_FILES            common::WriteMsg::mlError, "Error: Missing input files!\n"
#define CMSG_CANNOT_OPEN_FILE               common::WriteMsg::mlWarning, "Warining: Cannot open file: \"%s\"\n"
#define CMSG_NEGATIVE_MEMORY_VALUE          common::WriteMsg::mlError, "Error: Wrong (negative) maximum memory value.\n"
#define CMSG_INVALID_MEMORY_VALUE           common::WriteMsg::mlError, "Error: Invalid maxmem value!\n"
#define CMSG_FILTER_FILE_DEPRECATED         common::WriteMsg::mlWarning, "Warning: Filter file (%s) is older than the input file (.lim). Filter file is not used.\n"
#define CMSG_CANNOT_OPEN_FILTER_FILE        common::WriteMsg::mlWarning, "Warning: Filter file cannot be loaded (%s)\n"
#define CMSG_MAXMEM_EXCEEDED                common::WriteMsg::mlError, "Error: Maximum memory exceeded, the remaining files are skipped.\n"
#define CMSG_CONVERTING_FILE                common::WriteMsg::mlDebug, "Converting file: %s\n"
#define CMSG_SAVING_FILE                    common::WriteMsg::mlDebug, "Saving \"%s\" file.\n"
#define CMSG_NEGATIVE_LOC                   common::WriteMsg::mlDebug,   "Debug: LOC would have been negative, changed to 0.\n"
#define CMSG_OUTPUT_FILE_CANNOT_OPEN        common::WriteMsg::mlError, "Error: Cannot open output file: \"%s\"\n"

//Warning messages
#define CMSG_WARN_CANNOT_READ_FILE          common::WriteMsg::mlWarning, "Warning: File \"%s\" cannot be loaded\n"
#define CMSG_WARN_CANNOT_WRITE_FILE         common::WriteMsg::mlWarning, "Warning: File \"%s\" cannot be saved\n"
#define CMSG_METHOD_WITHOUT_RETURN_TYPE     common::WriteMsg::mlDebug,   "Debug: MethodDeclaration without return type\n"
#define CMSG_METHODE_STACK_IS_EMPTY         common::WriteMsg::mlDebug,   "Debug: The method stack is empty\n"
#define CMSG_METHODE_OR_A_STACK_IS_EMPTY    common::WriteMsg::mlDebug,   "Debug: The method or attribute stack is empty\n"
#define CMSG_HAS_NOT_RAW_TYPE               common::WriteMsg::mlDebug,   "Debug: Has not raw type of type.\n"
#define CMSG_HAS_NOT_REFERS_TO              common::WriteMsg::mlDebug,   "Debug: Has not refers to edge of raw type.\n"
#define CMSG_NO_NODE_TO_DISPATCH            common::WriteMsg::mlDebug,   "Debug: The node to build dispatch is not exist in the lim.\n"

//Normal messages
#define CMSG_TRACEID_ON                     common::WriteMsg::mlNormal, "Ids of various phase are dumped.\n"
#define CMSG_LOADING_FILE                   common::WriteMsg::mlNormal, "Loading file:    %s\n"
#define CMSG_STATISTICS                     common::WriteMsg::mlNormal, "\nStatistics:\n\
\tConverting time              : %10.2fs\n\
\tSaving asg time              : %10.2fs\n\
\tTotal time                   : %10.2fs\n\
\tPeak memory usage            : %10.2fMB\n\
\tNumber of not existed files  : %10d\n\n"


#define CMSG_STAT_HEADER_NOT_EXISTED_FILE "Number of not existed files"



//DEBUG messages
#define CMSG_VISIT_BEGIN                common::WriteMsg::mlDDDebug, "Visit   ( %-20s), jsID:%d, limID:%d\n"
#define CMSG_VISIT_END                  common::WriteMsg::mlDDDebug, "VisitEnd( %-20s), jsID:%d, limID:%d\n"

//EXCEPTION messages
#define CMSG_EX_UNEXPECTED_TYPE(id, ndk)    "Unexpected Type: " + javascript::asg::Common::toString(ndk) + " (id" + javascript::asg::Common::toString(id) + ")"

#define CMSG_EMPTY_METHODSTACK          common::WriteMsg::mlDDDebug, "Empty method stack while attempting to add %s\n"

#endif
