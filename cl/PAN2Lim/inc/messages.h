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

#ifndef _PAN2LIM_MESSAGE_H
#define _PAN2LIM_MESSAGE_H

//cl arg descriptions
#define CLARG_LIM                          "Name of the output LIM file"
#define CLARG_NOFILTER                     "Filter files are not used"
#define CLARG_MAXMEM                       "Maximum usable memory (not converted files are written out)"

//ERROR messages
#define CMSG_MISSING_INPUT_FILES            common::WriteMsg::mlError, "Error: Missing input files!\n"
#define CMSG_CANNOT_OPEN_FILE               common::WriteMsg::mlWarning, "Warining: Cannot open file: \"%s\"\n"
#define CMSG_NEGATIVE_MEMORY_VALUE          common::WriteMsg::mlError, "Error: Wrong (negative) maximum memory value.\n"
#define CMSG_INVALID_MEMORY_VALUE           common::WriteMsg::mlError, "Error: Invalid maxmem value!\n"
#define CMSG_FILTER_FILE_DEPRECATED         common::WriteMsg::mlWarning, "Warning: Filter file (%s) is older than the input file (.lim). Filter file is not used.\n"
#define CMSG_CANNOT_OPEN_FILTER_FILE        common::WriteMsg::mlWarning, "Warning: Filter file cannot be loaded (%s)\n"
#define CMSG_MAXMEM_EXCEEDED                common::WriteMsg::mlError, "Error: Maximum memory exceeded, the remaining files are skipped.\n"

#define CMSG_WARN_CANNOT_READ_FILE          common::WriteMsg::mlWarning, "Warning: File \"%s\" cannot be loaded\n"
#define CMSG_WARN_CANNOT_WRITE_FILE         common::WriteMsg::mlWarning, "Warning: File \"%s\" cannot be saved\n"
#define CMSG_CONVERTING_FILE                common::WriteMsg::mlDebug, "Converting file: %s\n"
#define CMSG_SAVING_FILE                    common::WriteMsg::mlDebug, "Saving \"%s\" file.\n"

//Normal messages
#define CMSG_LOADING_FILE                   common::WriteMsg::mlNormal, "Loading file:    %s\n"
#define CMSG_STATISTICS                     common::WriteMsg::mlNormal, "\nStatistics:\n\
\tConverting time              : %10.2fs\n\
\tSaving asg time              : %10.2fs\n\
\tTotal time                   : %10.2fs\n\
\tPeak memory usage            : %10luMB\n\
\tNumber of not existed files  : %10d\n\n"

//Exception messages
#define CMSG_INVALID_NODEKIND "invalid nodeKind"
#define CMSG_WRONG_ASG "Wrong ASG"

#endif
