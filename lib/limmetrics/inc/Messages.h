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

#ifndef _LIMMETRICS_MESSAGES_H_
#define _LIMMETRICS_MESSAGES_H_

#define CMSG_LIMMETRICS_VISIT_DEBUG                               WriteMsg::mlDebug,   "Visit %s for node %d (type: %s, phase: %d)\n"
#define CMSG_LIMMETRICS_NOT_CALCULATED                            WriteMsg::mlDDebug,  "  Metric '%s' is not calculated for node %d ( which is a(n) '%s' )\n"
#define CMSG_LIMMETRICS_DISPATCH                                  WriteMsg::mlDebug,   "  Dispatching metric '%s' for node %d in phase %d\n"
#define CMSG_LIMMETRICS_NO_DISPATCH                               WriteMsg::mlDDebug,  "  No handler to dispatch ( metric: '%s', node: %d, phase: %d )\n"
#define CMSG_LIMMETRICS_PHASE                                     WriteMsg::mlDebug,   "---\nPHASE %s\n---\n"
#define CMSG_LIMMETRICS_PHASE_OVER                                WriteMsg::mlDebug,   "Phase %s over\n"
#define CMSG_LIMMETRICS_DISABLED_METRIC                           WriteMsg::mlDebug,   "The metric %s is disabled\n"
#define CMSG_LIMMETRICS_HANDLER_CREATED                           WriteMsg::mlDebug,   "Created MetricHandler with name <%s>\n"

#define CMSG_LIMMETRICS_EX_INVALID_GRAPH_NODE( id )               "Error: Invalid graph node for corresponding lim node (" + id + ")"
#define CMSG_LIMMETRICS_EX_INVALID_METRIC_TYPE( metric )          "Error: Invalid metric type for " + metric

//------- OLD ---------
#define CMSG_LIMMETRICS_CLASSKIND_NOT_FOUND               WriteMsg::mlDebug,   "Debug: Class node kind [%d] not found\n"
#define CMSG_LIMMETRICS_METRIC_OUT_OF_BOUND               WriteMsg::mlError,   "Error: Unknown metric (out of bound)\n"
#define CMSG_LIMMETRICS_MORE_THAN_ONE_TYPEFORMER          WriteMsg::mlDebug,   "Debug: More than one TypeFormer SubClass\n"
#define CMSG_LIMMETRICS_UNDEFINED_CHILD_TNOS              WriteMsg::mlDebug,   "Debug: TNOS of node %d is not set when visiting node %d\n"
#define CMSG_LIMMETRICS_INCORRECT_METRIC_DATA_TYPE        WriteMsg::mlDebug,   "Debug: The data type of %s metric %s is incorrect\n"



#endif
