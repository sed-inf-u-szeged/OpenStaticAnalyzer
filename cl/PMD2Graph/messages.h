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

#ifndef _PMD2GRAPH_MESSAGES_H_
#define _PMD2GRAPH_MESSAGES_H_

//main.cpp messages
#define CMSG_PMD2GRAPH_ARGS_OUT_PARAM_ERROR                  WriteMsg::mlError, "Error: If the parameter -makecsv is used either parameter -printstdout or parameter -out must be given\n"
#define CMSG_PMD2GRAPH_ARGS_MORE_THAN_ONE_PHASE              WriteMsg::mlError, "Error: The parameters -makerul, -makeconfig, and -makecsv cannot be used together\n"
#define CMSG_PMD2GRAPH_ARGS_NO_PHASE_GIVEN                   WriteMsg::mlError, "Error: One of the parameters -makerul, -makeconfig, and -makecsv must be set\n"
#define CMSG_PMD2GRAPH_ARGS_MAKERUL_ERROR                    WriteMsg::mlError, "Error: Parameter -makerul requires a list file (-lst) and a rule file name (-rul)\n"
#define CMSG_PMD2GRAPH_ARGS_MAKECONFIG_ERROR                 WriteMsg::mlError, "Error: Parameter -makeconfig requires a rul file (-rul) and a list file (-lst)\n"
#define CMSG_PMD2GRAPH_ARGS_MAKECSV_ERROR                    WriteMsg::mlError, "Error: Parameter -makecsv requires a LIM ASG file (-lim), a list file (-lst), a rule file with -rul, and at least one of following output parameters: -metrics, -groupedmetrics, -warnings, -graph\n"
#define CMSG_PMD2GRAPH_ERROR_ANALYZE_FILE                    WriteMsg::mlNormal, "Error during PMD analyze at file: %s\n"

#define CMSG_PMD2GRAPH_CANT_LOAD_LIST_FILE                   WriteMsg::mlError, "Error: Cannot load list file: \"%s\"\n"
#define CMSG_PMD2GRAPH_EXCEPTION_INFO                        WriteMsg::mlError, "Error: %s : %s\n"
#define CMSG_PMD2GRAPH_DUMPING_OUTPUT_TO_FILE                WriteMsg::mlDebug, "Debug: Dumping output to file: \"%s\"\n"
#define CMSG_PMD2GRAPH_ERROR_OPENING_DUMP_FILE               WriteMsg::mlError, "Error: Cannot open output file \"%s\" (dumping to standard output)\n"
#define CMSG_PMD2GRAPH_DUMPING_OUTPUT_TO_STANDARD_OUTPUT     WriteMsg::mlDebug, "Debug: Dumping output to standard output\n"

//CheckerStrategy.cpp messages
#define CMSG_PMD2GRAPH_ERROR_DURING_PARSING                  WriteMsg::mlError, "\nError: Parsing error: '%s'\nError: Exception message: '%s'\n"
#define CMSG_PMD2GRAPH_LINE                                  WriteMsg::mlError, "Error: Line: %d, col:%d\n"
#define CMSG_PMD2GRAPH_ERROR_DURING_PARSING_DOMEX            WriteMsg::mlError, "\nError: DOM Parsing error: '%s'\nError: DOMException code: '%s'"
#define CMSG_PMD2GRAPH_EX_MESSAGE                            WriteMsg::mlError, "Error: Message: '%s'\n"
#define CMSG_PMD2GRAPH_UNEXPECTED_PARSING_EX                 WriteMsg::mlError, "\nError: Unexpected exception during parsing: '%s'\n"
#define CMSG_PMD2GRAPH_ERROR_CREATING_TRANSCODER             WriteMsg::mlError, "Error: An error occurred during creation of output transcoder: '%s'\n"
#define CMSG_PMD2GRAPH_ERROR_WRITING_XML_FILE                WriteMsg::mlError, "Error: An error occurred while writing XML file\n"

//MetricTree.cpp messages
#define CMSG_PMD2GRAPH_USING_CONFIG                          WriteMsg::mlNormal, "Using configuration: \"%s\"\n"
#define CMSG_PMD2GRAPH_LOADING_LIM                           WriteMsg::mlNormal, "Loading LIM ASG file \"%s\"\n"
#define CMSG_PMD2GRAPH_LOADING_LIM_FILTER                    WriteMsg::mlNormal, "Loading filter file \"%s\"\n"
#define CMSG_PMD2GRAPH_FILTER_FILE_IS_DEPRECATED             WriteMsg::mlWarning, "Warning: Filter file (%s) is older than the input file. Filter file is not used.\n"
#define CMSG_PMD2GRAPH_LOAD_LIM_EXCEPTION                    WriteMsg::mlError, "Error: LIM ASG file (%s) cannot be loaded: %s : %s\n"
#define CMSG_PMD2GRAPH_LOAD_FILTER_EXCEPTION                 WriteMsg::mlError, "Error: Filter file (%s) cannot be loaded: %s : %s\n"
#define CMSG_PMD2GRAPH_NO_NODE_FOUND_AT_PATH                 WriteMsg::mlWarning, "Warning: Warning '%s' cannot be added as no node found at [path:%s line:%d col:%d endline:%d endcol:%d]\n"
#define CMSG_PMD2GRAPH_ADDED_WARNING                         "%s(%d): %s: %s\n"
#define CMSG_PMD2GRAPH_WARNING_ALREADY_ADDED                 WriteMsg::mlWarning, "Warning: Warning '%s' has already been added. (node:%s path:%s line:%d col:%d endline:%d endcol:%d text:'%s')\n"

//PMDStrategy-rul.cpp messages
#define CMSG_PMD2GRAPH_COULDNT_FIND_REF                      WriteMsg::mlError, "Error: Could not find the referenced element for rul ref: %s\n"
#define CMSG_PMD2GRAPH_PROCESSING_FILE                       WriteMsg::mlDebug, "Debug: Processing file \"%s\""

//PMDStrategy-config.cpp messages
#define CMSG_PMD2GRAPH_ERROR_DURING_INIT                     WriteMsg::mlError, "Error: Initialization error: '%s'\n"
#define CMSG_PMD2GRAPH_OUT_OF_MEMORY                         WriteMsg::mlError, "Error: OutOfMemoryException\n"
#define CMSG_PMD2GRAPH_DOM_EX                                WriteMsg::mlError, "Error: DOMException: '%d', message: '%s'"
#define CMSG_PMD2GRAPH_ERROR_READING_DOCUMENT                WriteMsg::mlError, "Error: An error occurred while creating the document"

//PMDStrategy-csv.cpp messages
#define CMSG_PMD2GRAPH_LOADING_XML                           WriteMsg::mlNormal, "Loading xml file \"%s\"\n"

#endif