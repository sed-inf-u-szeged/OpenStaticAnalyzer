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

#ifndef _CONTR_MSG_H_
#define _CONTR_MSG_H_

#define CMSG_EX_RULE_ID_MISSING                               "Rule does not have id"
#define CMSG_EX_RULE_ENABLED_MISSING                          "Rule does not have enabled attribute"
#define CMSG_EX_RULE_SETTINGS_NOT_FOUND                       "Rule settings is not found: "
#define CMSG_EX_TOOL_SETTINGS_NOT_FOUND                       "Tool settings is not found: "
#define CMSG_EX_THRESHOLD_NOT_FOUND                           "Threshold is not found: "
#define CMSG_EX_THRESHOLD_METRIC_ID_MISSING                   "Threshold does not have metric id attribute"
#define CMSG_EX_THRESHOLD_RELATION_MISSING                    "Threshold does not have relation attribute"
#define CMSG_EX_THRESHOLD_VALUE_MISSING                       "Threshold does not have value attribute"
#define CMSG_EX_THRESHOLD_ENTITY_MISSING                      "Threshold does not have entity attribute"
#define CMSG_EX_TOOL_NAME_MISSING                             "Tool does not have name attribute"
#define CMSG_EX_TOOL_ENABLED_MISSING                          "Tool does not have enabled attribute"

#define CMSG_ERROR_CREATE_DIR                                 "ERROR: Can't create %s dir.\n"
#define CMSG_ERROR_EXECUTION_FAILURE                          "ERROR: Execution failure! Exit:%d\n"
#define CMSG_ERROR_ENVSET_FAILURE                             "ERROR: Failed to set '%s' environment variable!\n"
#define CMSG_WARNING_ENVSET_OVERWRITE                         "WARNING: Overwriting '%s' environment variable!\n"

#endif
