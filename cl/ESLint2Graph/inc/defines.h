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

#ifndef _ESLINT2GRAPH_DEFINES_H_
#define _ESLINT2GRAPH_DEFINES_H_

#include <sstream>

#define _ESLINT               "ESLint"

// Rule
#define _RULE                 "RuleViolation"
#define _RULE_ID              "ruleId"
#define _RULE_NAME            "ruleName"
#define _RULE_ABBREVIATION    "abbreviation"
#define _RULE_PRIORITY        "severity"
#define _RULE_ENABLED         "enabled"
#define _RULE_HELP            "helpText"

// Group
#define _GROUP                "RuleViolationGroup"
#define _GROUP_ID             "groupId"
#define _GROUP_NAME           "groupName"
#define _GROUP_DESCRIPTION    "description"

//Parameter
#define _PARAMETER            "Parameter" 
#define _PARAMETER_NAME       "parameterName"
#define _PARAMETER_VALUE      "parameterValue"

//xml tags and attributes of eslint result file
#define _FILE                   "file"
#define _FILE_NAME              "name"
#define _WARNING                "error"
#define _WARNING_MSG            "message"
#define _WARNING_LINE           "line"
#define _WARNING_COLUMN         "column"
#define _WARNING_NODETYPE       "nodeType"

#define _RULE_PREFIX            "ESLINT_"

#endif
