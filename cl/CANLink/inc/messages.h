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

#ifndef _CANLINK_M_H_
#define _CANLINK_M_H_

//main.cpp
#define CMSG_NO_INPUT_FILE       common::WriteMsg::mlNormal,   "\nNo input file!\n\n"
#define CMSG_NO_OUTPUT_FILE      common::WriteMsg::mlError,    "\nNo output file was set.\n"
#define CMSG_CAN_NOT_OPEN_OUTPUT_FILE common::WriteMsg::mlError,    "Failed to open '%s' file for writting.\n"
#define CMSG_STATISTICS          common::WriteMsg::mlNormal,   "\nStatistics:\n"
#define CMSG_STAT_LINKING_TIME   common::WriteMsg::mlNormal,   "\tLinking time       :%lu sec/100\n"
#define CMSG_STAT_FILTERING_TIME common::WriteMsg::mlNormal,   "\tFiltering time     :%lu sec/100\n"
#define CMSG_STAT_USER_TIME      common::WriteMsg::mlNormal,   "\tTotal user time    :%lu sec/100\n"
#define CMSG_STAT_SYSTEM_TIME    common::WriteMsg::mlNormal,   "\tTotal system time  :%lu sec/100\n"
#define CMSG_STAT_PEAK_MEMORY_USAGE  common::WriteMsg::mlNormal,   "\tPeak memory usage  :%lu MByte\n"
#define CMSG_SAVED              common::WriteMsg::mlDDDebug,  "%s is saved.\n"

#define CMSG_STAT_HEADER_OUTPUT_FILE                        "Output file"
#define CMSG_STAT_HEADER_NUMBER_OF_INPUT_FILES              "Number of input files"
#define CMSG_STAT_HEADER_NUMBER_OF_CSI_FILES                "Number of csi files"
#define CMSG_STAT_HEADER_NUMBER_OF_WARNINGS                 "Number of warnings"
#define CMSG_STAT_HEADER_LINKING_TIME                       "Linking time (s)"
#define CMSG_STAT_HEADER_FILTERING_TIME                     "Filtering time (s)"
#define CMSG_STAT_HEADER_USER_TIME                          "Total user time (s)"
#define CMSG_STAT_HEADER_SYSTEM_TIME                        "Total system time (s)"
#define CMSG_STAT_HEADER_CPU_TIME                           "Total cpu time (s)"
#define CMSG_STAT_HEADER_PEAK_MEMORY_USAGE                  "Peak memory usage (MByte)"
#define CMSG_STAT_HEADER_AVERAGE_NUMBER_OF_NODES            "Average number of nodes"
#define CMSG_STAT_HEADER_NUMBER_OF_NODES_IN_THE_LINKED_ASG  "Number of nodes in the linked ASG"
                                                 
//AutoCheck.cpp
#define CMSG_LINKINDEXORDER_IS_NOT_CORRECT  WriteMsg::mlWarning,  "LinkIndexOrder is not correct in %s : 2 node index is not right, ID-s first %s : %s second %s : %s\n"
#define CMSG_THE_HASH_IS_DIFFERENT          WriteMsg::mlWarning,  "Hash code(0x%x) to node with %u ID is not equal. The old node hash was 0x%x\n"
#define CMSG_THE_HASH_IS_OK                 WriteMsg::mlDDDDebug, "Hash ok %u \n"
#define CMSG_THE_NODE_NOT_CONNECTED_TO_NODE WriteMsg::mlWarning,  "Node with %u ID is not connected to Node with %u ID\n"
#define CMSG_THE_NODE_IS_MISSING_FORM_TREE  WriteMsg::mlWarning,  "Node with %u ID is missing form tree of Node with %u ID\n"
#define CMSG_THE_NODE_HAS_NOT_MANGLEDNAME   WriteMsg::mlDDebug,   "Node with %u ID hasn't mangledname\n"
#define CMSG_EXTRA_SYMBOLS                  WriteMsg::mlNormal,   "Extra symbols :\n"
#define CMSG_MISSING_SYMBOLS                WriteMsg::mlNormal,   "Missing symbols :\n"
#define CMSG_SYMBOL_TYPE_CHECK              WriteMsg::mlNormal,   "Symbol type check :\n"
#define CMSG_SYMBOL_TYPE_IS_NOT_CORRECT     WriteMsg::mlWarning,  "Symbol type is not correct : %s\n"
#define CMSG_ERROR_IN_CHECK                 WriteMsg::mlWarning,  "Error in check\n"
#define CMSG_NODE_CONNECT_MULTI_TIMES_TO    WriteMsg::mlWarning,  "Node with %u ID connect multi times to node with %u ID\n"
#define CMSG_NODE_IS_NOT_EXIST_IN_COMPILATION_UNIT WriteMsg::mlWarning, "Node is not exist in compilation unit %s: %u ID\n"
#define CMSG_EXIST_MORE_THEN_ONE_FROM_INDEXABLE_NODE_WITH_SAME_PROPERTY WriteMsg::mlWarning, "Exist more then one from indexable node with same property: first %s %u ID and %s %u ID\n" 

//Linker.cpp

#define CMSG_IS_NOT_SAME_KIND_SIMBOL         WriteMsg::mlWarning,"Not a same kind of symbol! %s %s != %s\n"
#define CMSG_THERE_IS_NO_INPUT               WriteMsg::mlError,  "ERROR: There is no input for the linker!\n"
#define CMSG_FILE_BEGIN                      WriteMsg::mlNormal,   "FILE BEGIN %s\n"
#define CMSG_FILE_END                        WriteMsg::mlNormal,   "FILE END %s\n"
#define CMSG_FILE_BEGIN_ACSI                 WriteMsg::mlNormal,   "ACSI %s: FILE BEGIN %s\n"
#define CMSG_FILE_END_ACSI                   WriteMsg::mlNormal,   "ACSI %s: FILE END %s\n"
#define CMSG_IN_FILE                         WriteMsg::mlError,    "%s :in %s file\n", e.getMessage().c_str() , inputFileNames.front().c_str()
#define CMSG_FILE_PEAK_MEMORY_USAGE          WriteMsg::mlDebug,    "\tFile %s : Peak memory usage :%lu Mb\n"
#define CMSG_THE_FILE_IS_NOT_EXIST           WriteMsg::mlWarning,  "WARNING: The %s file does not exist!\n"
#define CMSG_THE_FILE_IS_NOT_EXIST_ERROR     WriteMsg::mlError,    "ERROR: The %s file does not exist!\n"
#define CMSG_SAME_NODE_EXSIST                WriteMsg::mlDDDebug,  "Two equivalent nodes (%s) in the first ASG:  (%d == %d)\n"
#define CMSG_DOUBLE_SYMBOL_DEFINITION_ABOUT  WriteMsg::mlWarning,  "Error: Double Symbol definition about dst %s in %s and src %s in %s\n"
#define CMSG_WEAK_SYMBOL_IS_DROPPED_FROM     WriteMsg::mlDDebug, "Weak symbol %s is dropped from %s\n"
#define CMSG_ERROR_AT_LINKER_EXCEPTION       WriteMsg::mlError, "Error at Linker::copyAllPositionNode exception (%s)."
#define CMSG_THE_NODE_PARENT_NOT_FOUND       WriteMsg::mlDDDDebug, "The %d node parent not found in the linked but the original has \n"
#define CMSG_THE_ID_IN_THE_LINKED_ASG_IS     WriteMsg::mlDDDDebug, "The %d id in the linked asg is %d\n"
#define CMSG_DOUBLE_MAIN_SYMBOL_DEFINITION   WriteMsg::mlError,    "Error: Double main Symbol definition\n"
#define CMSG_THE_NODE_IN_THE_SRC_CORRESPOND  WriteMsg::mlDDDDebug, "The node %d (in the src) correspond to %d node in the (dest asg )\n"
#define CMSG_DUPLICATED_NODE_IN_THE_SPANNING_TREE WriteMsg::mlError, "Duplicated node in the spanning-tree:%u (%s)\n"
#define CMSG_VISITED_NODES                   WriteMsg::mlDebug, "Visited nodes:%d\n"
#define CMSG_NUMBER_OF_TYPE_NODES            WriteMsg::mlDebug, "Number of Type nodes:%u\n"
#define CMSG_GLOBAL_NODES                    WriteMsg::mlDebug, "Global nodes:\n"
#define CMSG_PS_PU_DEBUG                     WriteMsg::mlDebug, "  %s:%u\n"
#define CMSG_TOTAL_GLOBAL_NODES              WriteMsg::mlDebug, "Total global nodes:%u\n"
#define CMSG_DOUBLE_OVERWRITE_WARNING        WriteMsg::mlWarning,  "Warning!: Double overwrite! The %d is already overwritten with %d and can not overwrite with the %d again!\n"
#define CMSG_OVERWRITING_NON_SYMBOL          WriteMsg::mlDebug, "Overwritting (non-symbol) %d node with %d node."
#define CMSG_MAPPING_NODES                   WriteMsg::mlDebug, "Mapping (%d) to the %d node.\n"
#define CMSG_DOUBLE_MAPPING_WARNING          WriteMsg::mlDebug, "Node (%d) is not maped to the %d node because some other node is already mapped to this node and it can be overwritten!\n"
//node comp
#define CMSG_OPERATOR_USE_ITSEFT        common::WriteMsg::mlDebug, " < operator of node is not good !!! use itseft for decide node kind %s (%d)\n"
#define CMSG_NOT_RULE_FOR_NODE          common::WriteMsg::mlDDDDebug, "Not rule to compare the %s node kind. (%d, %d)\n"

#endif
