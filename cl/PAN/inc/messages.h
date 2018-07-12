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

#ifndef _PAN_MESSAGE_H
#define _PAN_MESSAGE_H

//main messages
#define CLARG_LST             "List file for additional inputs"
#define CLARG_OUT             "Output file"
#define CLARG_XML             "Generate PML (XML) output"
#define CLARG_PREFIX          "Remove the basepath prefix from all paths"
#define CLARG_PKG             "Build packages according to directory structure."
#define CLARG_ANALYZE_PKG     "Analyze python packages."
#define CLARG_IGNORE          "List of file and directory names separated by colon which will be ignored during the analysis. Default: tests."
#define CLARG_PYBIN           "Sets Python 2.7/3.x binary executable name (full path is required if its directory is not in PATH)."

#define CMSG_NO_INPUT_FILES               WriteMsg::mlWarning, "Warning: No input files\n"
#define CMSG_ONE_INPUT_REQ                WriteMsg::mlError, "Error: Exactly 1 input directory is required, when analyzing packages\n"
#define CMSG_CANNOT_OPEN_LIST             WriteMsg::mlError, "ERROR: Cannot open list file: \"%s\"\n"
#define CMSG_CANNOT_OPEN_FILE             WriteMsg::mlError, "ERROR: Cannot open file: \"%s\"\n"
#define CMSG_PARSE_ERROR                  WriteMsg::mlError, "ERROR: Parser error.\n"
#define CMSG_NOT_PSI_EXTENSION            WriteMsg::mlWarning, "WARNING: Extension of the output file is not '.psi': \"%s\"\n"
#define CMSG_WRONG_PATH_PREFIX            WriteMsg::mlWarning, "WARNING: Wrong path prefix.\n"
#define CMSG_PARSING                      WriteMsg::mlNormal, "Parsing file: %s\n"
#define PATH_DOES_NOT_EXIST               WriteMsg::mlWarning, "Warning: Path does not exist: %s\n"
#define ERROR_WHILE_COLLECTING_FILES      WriteMsg::mlError, "Error: Error while collecting input files: %s\n"
#define CMSG_SAVING_ASG                   WriteMsg::mlNormal, "Saving ASG file: \"%s\"\n"
#define CMSG_CREATING_PML                 WriteMsg::mlNormal, "Creating pml dump: \"%s\"\n"
#define CMSG_FILTERED_FILE                WriteMsg::mlDebug, "Debug: Filtered file: %s\n"
#define CMSG_PYTHON_BIN_UNSPEC            WriteMsg::mlError, "Error: Python binary is not specified.\n"
#define CMSG_PYTHON_BIN_ERROR             WriteMsg::mlError, "Error: Python 2.7/3.x binary is not found on PATH nor specified with '-pythonBinary' option correctly.\n"
#define CMSG_PY_PREFIX_ERROR              WriteMsg::mlError, "Error: Failed to get prefix and exec_prefix values from python.\n"
#define CMSG_PAN_PY_COMPAT_ERROR          WriteMsg::mlError, "Error: PAN python version (%s) is not compatible with the python executable (%s).\n"
#define CMSG_PY_LIB_NOT_FOUND             WriteMsg::mlError, "Error: Couldn't found the python lib directory.\n"
#define CMSG_ERROR_ENVSET_FAILURE         WriteMsg::mlError, "Error: Failed to set '%s' environment variable!\n"

//PBuilder messages
#define CMSG_EX_WRONG_NUM_OP_OR_OP        "Wrong number of operands or operators"
#define CMSG_EX_WRONG_NUM_OP              "Wrong number of operands"

//PVisitor messages
#define CMSG_EXCEPTION_AT                 WriteMsg::mlError, "Exception occurred at %s\n"
#define CMSG_POS                          WriteMsg::mlError, "  %s (line:%d, col:%d)\n"
#define CMSG_ERROR                        WriteMsg::mlError, "ERROR: %s : %s\n"
#define CMSG_UNKNOWN_EXCEPTION            WriteMsg::mlError, "Unknown exception at %s\n"

//VisitorImport messages
#define CMSG_WRONG_PKG_LEVEL              WriteMsg::mlDebug, "Debug: Wrong package level (%d) at ImportFrom node (%u).\n"
#define CMSG_IMPORT_MODULE                WriteMsg::mlDDDebug, "\timport \"%s\" module.\n"

//VisitorType messages
#define CMSG_EX_REDEFINITION(id)          "Redefinition node type (node id:" + id  + ")."

#define CMSG_VISITING                     WriteMsg::mlDDDebug, "Visiting \"%s\" module.\n"

#define CMSG_STATISTICS                     common::WriteMsg::mlNormal, "\nStatistics:\n\
\tParsing time                 : %10.2fs\n\
\tSaving asg time              : %10.2fs\n\
\tDumping pml time             : %10.2fs\n\
\tTotal time                   : %10.2fs\n\
\tPeak memory usage            : %10luMB\n\
\tNumber of parser errors      : %10d\n\n"

#endif
