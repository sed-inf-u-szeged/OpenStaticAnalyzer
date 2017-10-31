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

#ifndef _METRIC_HUNTER_MESSAGES_H_
#define _METRIC_HUNTER_MESSAGES_H_

#define CMSG_UNKNOWN_RELATION     "Unknown relation"

#define CMSG_RULE_SKIPPED          WriteMsg::mlWarning, "Warning: Rule for the following threshold configuration has not been built into the graph!\n%s\n" 
#define CMSG_NO_RULE_FOUND         WriteMsg::mlWarning, "Warning: No '%s' metric rule found in the graph!\n"
#define CMSG_RULE_IS_NOT_ENABLED   WriteMsg::mlWarning, "Warning: Metric '%s' was not enabled!\n"
#define CMSG_INVALID_ENTITY        WriteMsg::mlWarning, "Warning: Metric '%s' is not calculated for the '%s' entities!\n"
#define CMSG_NO_INPUT_FILE         WriteMsg::mlError,   "Error: There is no input file!\n"
#define CMSG_NO_OUTPUT_FILE        WriteMsg::mlError,   "Error: There is no output file!\n"
#define CMSG_NO_THRESHOLD_FILE     WriteMsg::mlError,   "Error: There is no thresholds file to use!\n"
#define CMSG_ADDED_WARNINGS        WriteMsg::mlNormal,  "Succesfully added %i warnings! \n"
#define CMSG_DEBUG_INPUT           WriteMsg::mlDebug,   "Input file: %s \n Threshold file: %s\n"
#define CMSG_GRAPH_SAVED           WriteMsg::mlNormal,  "Graph saved successfully to %s! \n"
#define CMSG_XML_SAVED             WriteMsg::mlNormal,  "XML saved successfully! \n"
#define CMSG_WARNING_ADDED         WriteMsg::mlDebug,   "Added warning to the node %s (%s).\n"
#define CMSG_WARNING_NOT_ADDED     WriteMsg::mlError,   "Can't add warning to the node %s.\n"
#define CMSG_UNKNOWN_REL_ERROR     WriteMsg::mlError,   CMSG_UNKNOWN_RELATION

#endif
