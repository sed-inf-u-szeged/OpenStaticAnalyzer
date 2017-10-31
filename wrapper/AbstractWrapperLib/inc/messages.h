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

#ifndef WRAPPER_MESSAGES_H_
#define WRAPPER_MESSAGES_H_

//Common messages
#define CMSG_CURRENT_WORKDIR                                       "Current workdir: %s"
#define CMSG_ANALYZER_WRAPPER_COMMAND                              "%s"
#define CMSG_TOOL_RETURNS                                          "%s returned with exit code %d"

//AbstractArchive messages
#define CMSG_ARCHIVE_HAS_NO_INPUT                                  "Archive has no input files!"
#define CMSG_ARCHIVE_NO_NEED_TO_RUN                                "Don't have to run archive by configuration!"
#define CMSG_DEBUG_ARCHIVE_EXECUTION                               common::WriteMsg::mlDDDebug, "Executing archive tool %s in %s archive mode."
#define CMSG_DEBUG_ARCHIVE_MODIFIER                                common::WriteMsg::mlDDDebug, "Archive modifier: %s"
#define CMSG_DEBUG_ARCHIVE_OPERATION                               common::WriteMsg::mlDDDebug, "Archive operation: %s"
#define CMSG_DEBUG_ARCHIVE_OUTPUT                                  common::WriteMsg::mlDDDebug, "Archive output file: %s"
#define CMSG_DEBUG_ARCHIVE_POSITION_ASG                            common::WriteMsg::mlDDDebug, "Archive position asg file: %s"
#define CMSG_DEBUG_ARCHIVE_INPUT                                   common::WriteMsg::mlDDDebug, "Archive input: %s"

//AbstractCompiler messages
#define CMSG_DEBUG_COMPILER_ARGUMENT_WITH_PARAM                    common::WriteMsg::mlDDDebug, "Compiler argument %s with parameter %s"
#define CMSG_INSTRUMENTER_HAS_NO_INPUT                             "%s has no input files!"
#define CMSG_COMPILER_HAS_NO_INPUT                                 "Compiler has no input files!"
#define CMSG_NO_NEED_TO_COMPILE_BY_PARAMS                          "Don't have to compile by parameters!"
#define CMSG_NO_NEED_TO_COMPILE_BY_CONFIG                          "Don't have to compile by configuration!"
#define CMSG_DEBUG_PREPROCESSOR_ARGUMENT                           common::WriteMsg::mlDDDebug, "Preprocessor argument: %s"
#define CMSG_DEBUG_PREPROCESSOR_INPUT_FILE                         common::WriteMsg::mlDDDebug, "Preprocessor input file: %s"
#define CMSG_DEBUG_COMPILER_EXECUTION                              common::WriteMsg::mlDDDebug, "Executing compiler tool %s"
#define CMSG_DEBUG_COMPILER_ARGUMENT                               common::WriteMsg::mlDDDebug, "Compiler argument %s"
#define CMSG_DEBUG_COMPILER_INPUT_FILE                             common::WriteMsg::mlDDDebug, "Compiler input file: %s"
#define CMSG_DEBUG_COMPILER_INPUT_FILE_LANG                        common::WriteMsg::mlDDDebug, "Compiler input file language: %s"
#define CMSG_DEBUG_COMPILER_OUTPUT_FROM_PARAM                      common::WriteMsg::mlDDDebug, "Compiler output file from parameter: %s"
#define CMSG_DEBUG_COMPILER_OUTPUT_FROM_INPUT                      common::WriteMsg::mlDDDebug, "Compiler output file from input file: %s"
#define CMSG_CPPCHECK_FAILED                                       "Cppcheck has failed! (Exit Code:%d) The cppcheck can be disabled with the -runCppcheck=false command line option."

//AbstractLinker messages
#define CMSG_DEBUG_LINKER_FINDING_LIBRARY                          common::WriteMsg::mlDDDebug, "Linker finding library: %s"
#define CMSG_DEBUG_LINKER_FINDING_LIBRARY_IN_PATH                  common::WriteMsg::mlDDDebug, "Linker finding library %s in path %s"
#define CMSG_LIB_FILE_NOT_FOUND                                    "Linker lib file %s cannot be found!"
#define CMSG_DEBUG_LIB_FILE_FOUND                                  common::WriteMsg::mlDDebug, "Linker lib file %s found!"
#define CMSG_DEBUG_LINKER_CREATING_INPUT                           common::WriteMsg::mlDDDebug, "Linker creating input name from input: %s"
#define CMSG_DEBUG_LINKER_CREATING_INPUT_FROM_CAN                  common::WriteMsg::mlDDDebug, "Linker creating input name from CAN output: %s"
#define CMSG_LINKER_HAS_NO_INPUT                                   "Linker has no input files!"
#define CMSG_NO_NEED_TO_LINK_BY_PARAMS                             "Don't have to link by parameters!"
#define CMSG_NO_NEED_TO_LINK_BY_CONFIG                             "Don't have to link by configuration!"
#define CMSG_DEBUG_LINKER_EXECUTION                                common::WriteMsg::mlDDDebug, "Executing linker tool %s"
#define CMSG_DEBUG_LINKER_ARGUMENT                                 common::WriteMsg::mlDDDebug, "Linker argument %s"
#define CMSG_DEBUG_LINKER_OUTPUT                                   common::WriteMsg::mlDDDebug, "Linker output: a.out"
#define CMSG_DEBUG_LINKER_OUTPUT_FROM_PARAM                        common::WriteMsg::mlDDDebug, "Linker output file from parameter: %s"
#define CMSG_LINKER_NO_INPUT_FILES_CREATED                         "No input files were created!"
#define CMSG_LINKER_FILTER_FILE                                    common::WriteMsg::mlDDDebug, "Linker filter file: %s"
#define CMSG_INFO_STATIC_LIB_IS_NOT_LINKED_IN                      "Archive (%s) is not used due to the current linking mode (%d)."

//AbstractWrapper messages
#define CMSG_ABSTRACT_WRAPPER_ORIGINAL_WRAPPED_TOOL                common::WriteMsg::mlDebug, "Original wrapped tool: %s"
#define CMSG_ABSTRACT_WRAPPER_ORIGINAL_ARGUMENT_CL                 common::WriteMsg::mlDebug, "Original argument %d from commandline: %s"
#define CMSG_ABSTRACT_WRAPPER_ARGUMENT_QUOTES_REMOVED              common::WriteMsg::mlDDDDebug, "Argument %d from commandline after removing quotes: %s"
#define CMSG_ABSTRACT_WRAPPER_SKIP_ARGUMENT                        common::WriteMsg::mlDDDDebug, "Skip argument %s with its %d parameters."
#define CMSG_ABSTRACT_WRAPPER_INPUT_COMMAND_FILE                   common::WriteMsg::mlDebug, "Input line from command file %s : \n %s"
#define CMSG_ABSTRACT_WRAPPER_SPLIT_COMMAND_FILE_ARGS              common::WriteMsg::mlDDDebug, "Argument from commandfile after splitting arguments: %s"
#define CMSG_ABSTRACT_WRAPPER_COMMAND_FILE_ARGS_QOUTES_REMOVED     common::WriteMsg::mlDDDebug, "Argument from commandfile after removing quotes: %s"

//ArParamsup messages
#define CMSG_AR_PARAMSUP_NO_OUTPUT_ARCHIVE_FILE                    "No output archive file was given!"

//ClParamsup and GccParamsup messages
#define CMSG_COMPILER_PARAMSUP_BOTH_C_CPP_FILE                      "Both /TC and /TP is set!"
#define CMSG_COMPILER_PARAMSUP_WRONG_COMPILER_ARGUMENT              "Compiler argument %s is wrong!"
#define CMSG_COMPILER_PARAMSUP_WRONG_LINKER_ARGUMENT                "Linker argument %s is wrong!"

//LibParamsup messages
#define CMSG_LIB_PARAMSUP_WRONG_LIB_ARGUMENT                        "Lib argument %s is wrong!"

//ParamsupCommon messages
#define CMSG_PATH_CANONICALIZE_WRONG                                common::WriteMsg::mlDDDebug, "There is a problem with common::pathCanonicalize!"
#define CMSG_ERROR_OPEN_FILE                                        "Cannot open file for appending: %s"

//Wrapper tools messages
#define CMSG_WRAPPER_TOOL_WARNINGS                                  "%s"
#define CMSG_WRAPPER_TOOL_UNRECOGNIZE_ARGUMENTS                     "Unrecognized argument: %s"

//CopyMoveWrapper messages
#define CMSG_CMW_MORE_THAN_ONE_SOURCES                              "ERROR: more than one sources are used but the target is not a directory!"
#define CMSG_CMW_DIFFERENT_TYPE_WARNING                             "Warning: the target (%s) is different type than the source (%s)."
#define CMSG_CMW_SOURCE_IS_DIRECTORY                                "The source is a directory!"
#define CMSG_CMW_NO_ASG_FILES                                       "Don't need to use %s. There is no columbus asg files."
#define CMSG_CMW_COPY_FILTER_FILES                                  "Copying filter file(s)..."
#define CMSG_CMW_RECURSIVE_MODE                                     "Recursive mode was used!"
#define CMSG_CMW_LIST_FILE_UPDATE                                   common::WriteMsg::mlDDDebug, "List file updated with source %s and target %s"
#define CMSG_CMW_LIST_FILE_ADD                                      common::WriteMsg::mlDDDebug, "Added source to list file: %s"

//Java wrappers common messages
#define CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT              "You have to start the wrapper environment before use this tool!"
#define CMSG_JAVA_EXEWRAPPER_DIRECTORY_SEARCH_FAIL                  "Error occured while trying to find out the directory of the exewrapper!"
#define CMSG_JAVA_ORIGINAL_PROGRAM_CANNOT_FIND                      "Not found the original program: %s"
#define CMSG_JAVA_IO_OPEN_ERROR                                     "IO error while opening %s."
#define CMSG_JAVA_UNKNOWN_EXCEPTION                                 "Unknown exception occured!"

//AntWrapper messages
#define CMSG_ANT_WRAPPER_MISSING_ANT_PARAMETER                      "Ant build file name is missing!"

//JavacWrapper messages
#define CMSG_JAVAC_WRAPPER_PMD_EXEC_ERROR                           "Error while executing PMD."
#define CMSG_JAVAC_WRAPPER_JAVAC_EXEC_ERROR                         "Error while executing javac."

//JarWrapper messages
#define CMSG_JAR_WRAPPER_XML_PARSING_ERROR                          "Parsing the 'project' tag of %s is failed!"

#endif
