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

#ifndef _CAN2LIM_MESSAGES_H_
#define _CAN2LIM_MESSAGES_H_

//main.cpp messages
#define CMSG_CAN2LIM_CONVERSION_START                   WriteMsg::mlNormal, "Conversion start...\n"
#define CMSG_CAN2LIM_CLANGMETRICS                       WriteMsg::mlNormal, "ClangMetrics processing AST file %s...\n"
#define CMSG_CAN2LIM_CONVERTING                         WriteMsg::mlNormal, "Converting file: %s ...\n"
#define CMSG_CAN2LIM_FOUND_COMPONENT                    WriteMsg::mlNormal, "Found component %s ; it's translation units: \n"
#define CMSG_CAN2LIM_FILE_NOT_LOADED                    WriteMsg::mlWarning, "WARNING: File cannot be loaded (%s)\n"
#define CMSG_CAN2LIM_FILE_NOT_LCSI                      WriteMsg::mlWarning, "WARNING: File %s is not .lcsi or LinkerCompilationData is not filled! \n"
#define CMSG_CAN2LIM_CONVERTING_ASG_DONE                WriteMsg::mlNormal, "Converting %s asg... DONE!\n"
#define CMSG_CAN2LIM_CONVERSION_FINISHED                WriteMsg::mlNormal, "Conversion finished!\n"
#define CMSG_CAN2LIM_NO_LCSI_LOADED                     WriteMsg::mlError, "ERROR: No .lcsi files were loaded or only .csi files were added! \n"
#define CMSG_CAN2LIM_FACTORY_SAVE_ERROR                 WriteMsg::mlError, "ERROR: %s\n"
#define CMSG_CAN2LIM_FILTER_SAVE_PROBLEM                WriteMsg::mlWarning, "WARNING: Error happened during writing file: %s"
#define CMSG_CAN2LIM_LIMML_DUMP_PROBLEM                 WriteMsg::mlError, "ERROR: Error happened during opening file: %s"
#define CMSG_CAN2LIM_NO_INPUT_FILE                      WriteMsg::mlError, "ERROR: No input file!"
#define CMSG_CAN2LIM_STATISTICS                         WriteMsg::mlNormal, "\nStatistics:\n"
#define CMSG_CAN2LIM_CONVERSION_PHASE_TIME              WriteMsg::mlNormal, "\tConversion phase time        : %10.2fs\n"
#define CMSG_CAN2LIM_METRICS_CALC_TIME                  WriteMsg::mlNormal, "\tMetrics calcualtion time     : %10.2fs\n"
#define CMSG_CAN2LIM_CONVERSION_TIME                    WriteMsg::mlNormal, "\tConversion time              : %10.2fs\n"
#define CMSG_CAN2LIM_AGGREGATION_TIME                   WriteMsg::mlNormal, "\tAggregation time             : %10.2fs\n"
#define CMSG_CAN2LIM_SAVE_TIME                          WriteMsg::mlNormal, "\tSave asg time                : %10.2fs\n"
#define CMSG_CAN2LIM_DUMP_TIME                          WriteMsg::mlNormal, "\tDump limml time              : %10.2fs\n"
#define CMSG_CAN2LIM_TOTAL_TIME                         WriteMsg::mlNormal, "\tTotal time                   : %10.2fs\n"
#define CMSG_CAN2LIM_PEAK_MEMORY                        WriteMsg::mlNormal, "\tPeak memory usage            : %10.2fMB\n"
#define CMSG_CAN2LIM_NOT_EXISTED_FILES                  WriteMsg::mlNormal, "\tNumber of not existed files  : %10d\n"

#define CMSG_CAN2LIM_CANT_LOAD_COMPONENT_FILE           WriteMsg::mlError,  "Error: Can not load component file: %s\n"
#define CMSG_CAN2LIM_DOUBLE_C_VERSION_NODE              WriteMsg::mlDebug,  "Double member node on the same location with 'C' language type: Node1:%d Node2:%d\n"
#define CMSG_NOT_AST_FILE                               WriteMsg::mlError,  "The component file contains a not AST file!:%s\n"
#define CMSG_FILE_DOES_NOT_EXIST                        WriteMsg::mlError,  "Error: AST file does not exist! (path:%s)\n"


//cpp2lim.cpp messages
#define CMSG_CAN2LIM_ALGORITHMCALLS_START               WriteMsg::mlNormal, "Run AlgorithmCalls start...\n"
#define CMSG_CAN2LIM_ALGORITHMCALLS_FINISHED            WriteMsg::mlNormal, "Run AlgorithmCalls finished!\n"
#define CMSG_CAN2LIM_CONVERTING_NODES_START             WriteMsg::mlNormal, "Converting nodes start...\n"
#define CMSG_CAN2LIM_CONVERTING_NODES_FINISHED          WriteMsg::mlNormal, "Converting nodes finished!\n"
#define CMSG_CAN2LIM_COMPILATION_UNIT_WARNING           WriteMsg::mlWarning, "WARNING! Compilation unit info is empty at node %d in component %s.\n"

#define CMSG_CAN2LIM_EX_WRONG_TEMPLATE_PARAMETER        "Wrong template parameter type"
#define CMSG_CAN2LIM_EX_INVALID_DECLARATION             "Invalid declaration [ " + cpp::asg::Common::toString(decl->getNodeKind()) + " ]"
#define CMSG_CAN2LIM_EX_INVALID_NODEKIND                "Invalid NodeKind [ " + cpp::asg::Common::toString(node.getNodeKind()) + " ]"
#define CMSG_CAN2LIM_EX_NL_NOT_NEGATIVE                 "Nesting level can not be negative!"
#define CMSG_CAN2LIM_EX_NLE_NOT_NEGATIVE                "Nesting level ElseIf can not be negative!"

#define CMSG_CAN2LIM_SOURCERANGE_FILE_MISMATCH          WriteMsg::mlWarning, "WARNING! File of the start position (%s) differs from the file of the end position (%s).\n"

#define CMSG_CAN2LIM_NOLIMNODE_EX(id)                   "Can not find LIM node for not documentation comment:" + id
#define CMSG_CAN2LIM_NOLIMNODE_WARNING                  WriteMsg::mlDebug, "WARNING! Can not find LIM node for not documentation comment (%d)!"

//VisitorAggregated.cpp messages
#define CMSG_CAN2LIM_VISITOR_AGGREGATED                 WriteMsg::mlNormal, "VisitorAggregated"
#define CMSG_CAN2LIM_VARIANTS_INSIDE_COMPONENT          WriteMsg::mlNormal, " for variants inside components"
#define CMSG_CAN2LIM_VARIANTS_BETWEEN_COMPONENT         WriteMsg::mlNormal, " for variants between components"
#define CMSG_CAN2LIM_AGGREGATED_START                   WriteMsg::mlNormal, " start...\n"
#define CMSG_CAN2LIM_AGGREGATED_FINISHED                WriteMsg::mlNormal, "VisitorAggregated finished!\n"


//VisitorHasMemberCorrector.cpp messages
#define CMSG_CAN2LIM_HAS_MEMBER_START                   WriteMsg::mlNormal, "VisitorHasMemberCorrector start...\n"
#define CMSG_CAN2LIM_HAS_MEMBER_FINISHED                WriteMsg::mlNormal, "VisitorHasMemberCorrector finished!\n"


//VisitorNewAggregatedNodeCreator.cpp messages
#define CMSG_CAN2LIM_NEW_AGGREGATE_START                WriteMsg::mlNormal, "VisitorNewAggregateNodeCreator start...\n"
#define CMSG_CAN2LIM_NEW_AGGREGATE_FINISHED             WriteMsg::mlNormal, "VisitorNewAggregateNodeCreator finished!\n"

#define CMSG_CAN2LIM_LOCVISITOR_START                   WriteMsg::mlNormal, "VisitorLOC start...\n"
#define CMSG_CAN2LIM_LOCVISITOR_END                     WriteMsg::mlNormal, "VisitorLOC finished!\n"

//Halstead messages
#define CMSG_CAN2LIM_HALSTEAD_VISIT_START               WriteMsg::mlNormal, "Halstead visitor start...\n"
#define CMSG_CAN2LIM_HALSTEAD_VISIT_END                 WriteMsg::mlNormal, "Halstead visitor finished!\n"

#endif
