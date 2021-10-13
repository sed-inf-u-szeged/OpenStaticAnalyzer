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

#ifndef _LIM2ANTIPATTERNS_MESSAGE_H
#define _LIM2ANTIPATTERNS_MESSAGE_H

#define PROGRAM_NAME "LIM2PatternsTool"
#define EXECUTABLE_NAME "LIM2Patterns"

#define CMSG_EX_UNHANDLED_ASG_TYPE(ASG) "Unhandled ASG type (" + ASG + ")"
#define CMSG_INVALID_LIM_FILE WriteMsg::mlNormal, "Error: No Lim input file were defined\n"
#define CMSG_INVALID_GRAPH_FILE WriteMsg::mlNormal, "Error: No graph input file were defined\n"
#define CMSG_NO_GRAPH_AND_METRICS WriteMsg::mlNormal, "Error: Either -metrics or -graph must be set (both can be set at the same time)\n"
#define CMSG_INVALID_PATTERN_FILE WriteMsg::mlNormal, "Error: No pattern file/directory were defined\n"
#define CMSG_INVALID_OUTPUT_FILE WriteMsg::mlNormal, "Error: Given output file/directory is invalid"
#define CMSG_WRONG_EXTENSION(ext) WriteMsg::mlNormal, "Error: Extension '" + ext + "' not allowed!\n" 
#define CMSG_PATTERN_IS_INVALID(pattern) WriteMsg::mlNormal, "Error: Given '" + string(pattern) + "' directory/file is invalid"
#define CMSG_PATTERN_FOLDER_EMPTY WriteMsg::mlNormal, "Error: Given directory does not contain any pattern file!"
#define CMSG_METRIC_RUL_INVALID WriteMsg::mlNormal, "Error: Given metric file doesn't exist"
#define CMSG_INCORRECT_PATTERN(errorText) "Error, pattern is incorrect:\n   - " + std::string(errorText) + "\n"
#define CMSG_INCORRECT_PATTERN_PY(errorText) "Error, Python pattern is incorrect:\n   - " + std::string(errorText) + "\n"
#define CMSG_INVALID_PATTERNGROUP "Error, PatternGroup wasn't created!\n "
#define CMSG_INVALID_RULDIRECTORY WriteMsg::mlNormal, "Error, invalid rul directory!\n "
#define WRITE_DEBUG(debugText) WriteMsg::write(WriteMsg::mlDebug, std::string(debugText))

#define CMSG_EX_INVALD_GRAPH_NODE(id)  "No corresponding graph node for lim node " + id

#endif
