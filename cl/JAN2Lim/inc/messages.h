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

#ifndef _JAN2LIM_MESSAGE_H
#define _JAN2LIM_MESSAGE_H

//ERROR messages
#define CMSG_MISSING_INPUT_FILES            common::WriteMsg::mlError, "Error: Missing input files!\n"
#define CMSG_CANNOT_OPEN_FILE               common::WriteMsg::mlWarning, "Warining: Cannot open file: \"%s\"\n"
#define CMSG_NEGATIVE_MEMORY_VALUE          common::WriteMsg::mlError, "Error: Wrong (negative) maximum memory value.\n"
#define CMSG_INVALID_MEMORY_VALUE           common::WriteMsg::mlError, "Error: Invalid maxmem value!\n"
#define CMSG_FILTER_FILE_DEPRECATED         common::WriteMsg::mlWarning, "Warning: Filter file (%s) is older than the input file (.lim). Filter file is not used.\n"
#define CMSG_CANNOT_OPEN_FILTER_FILE        common::WriteMsg::mlWarning, "Warning: Filter file cannot be loaded (%s)\n"
#define CMSG_MAXMEM_EXCEEDED                common::WriteMsg::mlError, "Error: Maximum memory exceeded, the remaining files are skipped.\n"

//Warning messages
#define CMSG_ATTRIB_WITHOUT_TYPE_EXPR       common::WriteMsg::mlDebug,   "Debug: Attribute node without type expression\n"
#define CMSG_PARAM_WITHOUT_TYPE_EXPR        common::WriteMsg::mlDebug,   "Debug: Parameter node without type expression\n"
#define CMSG_NEWCLASS_WITHOUT_TYPE_EXPR     common::WriteMsg::mlDebug,   "Debug: NewClass node without type expression\n"
#define CMSG_TYPE_EXPR_WITHOUT_TYPE         common::WriteMsg::mlDebug,   "Debug: TypeExpression node without type\n"
#define CMSG_WARN_CANNOT_READ_FILE          common::WriteMsg::mlWarning, "Warning: File \"%s\" cannot be loaded\n"
#define CMSG_WARN_CANNOT_WRITE_FILE         common::WriteMsg::mlWarning, "Warning: File \"%s\" cannot be saved\n"
#define CMSG_METHOD_WITHOUT_RETURN_TYPE     common::WriteMsg::mlDebug,   "Debug: MethodDeclaration without return type\n"
#define CMSG_METHODE_STACK_IS_EMPTY         common::WriteMsg::mlDebug,   "Debug: The method stack is empty\n"
#define CMSG_METHODE_OR_A_STACK_IS_EMPTY    common::WriteMsg::mlDebug,   "Debug: The method or attribute stack is empty\n"
#define CMSG_HAS_NOT_RAW_TYPE               common::WriteMsg::mlDebug,   "Debug: Has not raw type of type.\n"
#define CMSG_HAS_NOT_REFERS_TO              common::WriteMsg::mlDebug,   "Debug: Has not refers to edge of raw type.\n"
#define CMSG_NO_NODE_TO_DISPATCH            common::WriteMsg::mlDebug,   "Debug: The node to build dispatch is not exist in the lim.\n"
#define CMSG_NEGATIVE_LOC                   common::WriteMsg::mlDebug,   "Debug: LOC would have been negative, changed to 0.\n"
//Debug messages
#define CMSG_VISIT_BEGIN                common::WriteMsg::mlDDDebug, "Visit   ( %-20s), javaID:%d, limID:%d\n"
#define CMSG_VISIT_END                  common::WriteMsg::mlDDDebug, "VisitEnd( %-20s), javaID:%d, limID:%d\n"
#define CMSG_CONVERT_JAVA2LIM           common::WriteMsg::mlDDDebug, "Converting java::Type %d to Lim Type\n"
#define CMSG_NEW_EXT_CLASS              common::WriteMsg::mlDDebug, "New External class: %s\n"
#define CMSG_EXT2COMPLETE_CLASS         common::WriteMsg::mlDDebug, "External --> Complete class: %s\n"
#define CMSG_NEW_COMPLETE_CLASS         common::WriteMsg::mlDDebug, "New Complete class: %s\n"
#define CMSG_IRRELEVANT_CLASS           common::WriteMsg::mlDDebug, "Irrelevant class: %s\n"
#define CMSG_CONVERTING_FILE            common::WriteMsg::mlDebug, "Converting file: %s\n"
#define CMSG_SAVING_FILE                common::WriteMsg::mlDebug, "Saving \"%s\" file.\n"
#define CMSG_UNHANDLED_NODE_KIND        common::WriteMsg::mlDebug, "Unhandled node kind (%d).\n"
#define CMSG_INVOKES_IS_NULL            common::WriteMsg::mlDebug, "Debug: Invokes is null\n"
#define CMSG_UNHANDLED_ACCESSIBILITY    common::WriteMsg::mlDebug, "Debug: Unknown visibility (%s). It is set to private.\n"
#define CMSG_UNEXPECTED_TYPE_NODE       common::WriteMsg::mlDebug, "Debug: Unexpected node (id:%d type:%s) for type conversion.\n"


//Normal messages
#define CMSG_TRACEID_ON                 common::WriteMsg::mlNormal, "Ids of various phase are dumped.\n"
#define CMSG_LOADING_FILE               common::WriteMsg::mlNormal, "Loading file:    %s\n"
#define CMSG_COMPSTRUCT_NOT_BUILD       common::WriteMsg::mlNormal, "The component structure  hasn't built.\n"
#define CMSG_STATISTICS                 common::WriteMsg::mlNormal, "\nStatistics:\n\
\tConverting time              : %10.2fs\n\
\tSaving asg time              : %10.2fs\n\
\tDumping limml time           : %10.2fs\n\
\tTotal time                   : %10.2fs\n\
\tPeak memory usage            : %10.2fMB\n\
\tNumber of not existed files  : %10d\n\n"

#define CMSG_STAT_HEADER_CONVERTING_TIME "Converting time"
#define CMSG_STAT_HEADER_SAVE_TIME "Saving asg time"
#define CMSG_STAT_HEADER_DUMP_TIME "Dumping limml time"
#define CMSG_STAT_HEADER_TOTAL_TIME "Total time"
#define CMSG_STAT_HEADER_PEAK_MEMORY "Peak memory usage"
#define CMSG_STAT_HEADER_NOT_EXISTED_FILE "Number of not existed files"


//STAT messages
#define CMSG_STAT_NOSC                  "\n\tNumber of Source classes     : %10d\n"
#define CMSG_STAT_NOEC                  "\tNumber of External classes   : %10d\n"
#define CMSG_STAT_NOIC                  "\tNumber of Irrelevant classes : %10d\n"
#define CMSG_STAT_NOCC                  "\tNumber of Converted classes  : %10d\n"
#define CMSG_STAT_NOSKC                 "\tNumber of Skipped classes    : %10d\n"
#define CMSG_STAT_NOC                   "\tTotal Number of classes      : %10d\n\n"
#define CMSG_STAT_NODC                  "\tNumber of Dumped classes     : %10d\n"

//Exceptions
#define CMSG_EX_INVOKES_IS_NULL             "Invokes is null"
#define CMSG_EX_RAW_TYPE_NULL               "Raw type of Parametrized type is null"
#define CMSG_EX_RAW_TYPE_NOT_CLASS          "Raw type of Parametrized type is not a ClassType"
#define CMSG_EX_TYPEDECLERATION_NULL        "Referred TypeDeclaration of raw type of Parametrized type is null"
#define CMSG_EX_CANNOT_CONVERT_TO_CLASS     "RefersTo of the rawType does not convert to lim::Class"
#define CMSG_EX_WRONG_ASG                   "Wrong ASG"
#define CMSG_EX_NULL_PARENT                 "Java parent of TypeParameter is 0"

#define CMSG_EX_COPMATIBILITY_ERROR(id)     "Java node " + id + " has no Lim-compatible parent"
#define CMSG_EX_WRONG_PARAM_NODE(id)        "Wrong Parameter node (" + id + ")"
#define CMSG_EX_INVALID_NODEKIND(id, ndk)   "Invalid NodeKind (" + java::asg::Common::toString(ndk) + ", node id " + java::asg::Common::toString(id) + " )."
#define CMSG_EX_UNEXPECTED_TYPE(id, ndk)    "Unexpected Type: " + java::asg::Common::toString(ndk) + " (id" + java::asg::Common::toString(id) + ")"
#define CMSG_EX_EMPTY_CLASS_STACK(id, ndk)  "Class stack is empty at node id" + id + " (" + ndk + ")"

#endif
