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

#ifndef _LIM2METRICS_MESSAGES_H_
#define _LIM2METRICS_MESSAGES_H_

#define CMSG_LIM2METRICS_FLIM_OLDER_THAN_LIM              common::WriteMsg::mlWarning, "Warning: Filter file (%s) is older than the input file (.lim). Filter file is not used.\n"
#define CMSG_LIM2METRICS_FILTER_NOT_LOADED                common::WriteMsg::mlWarning, "Warning: Filter file cannot be loaded (%s)\n"

#define CMSG_LIM2METRICS_DEBUG_LIM_LOAD                   WriteMsg::mlDebug,   "Debug: Loading LIM\n"
#define CMSG_LIM2METRICS_DEBUG_FILTER_LOAD                WriteMsg::mlDebug,   "Debug: Loading LIM Filter\n"
#define CMSG_LIM2METRICS_DEBUG_GRAPH_CONVERT              WriteMsg::mlDebug,   "Debug: Converting to Graph\n"
#define CMSG_LIM2METRICS_DEBUG_RUL_LOAD                   WriteMsg::mlDebug,   "Debug: Loading RUL\n"
#define CMSG_LIM2METRICS_DEBUG_VISITOR_RUN                WriteMsg::mlDebug,   "Debug: Running Visitor\n"
#define CMSG_LIM2METRICS_DEBUG_EXPORT_RESULTS             WriteMsg::mlDebug,   "Debug: Exporting Results\n"

#endif
