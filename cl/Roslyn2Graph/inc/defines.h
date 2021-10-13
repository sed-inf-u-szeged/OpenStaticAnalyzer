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

#ifndef _ROSLYN2GRAPH_DEFINES_H_
#define _ROSLYN2GRAPH_DEFINES_H_

#include <string>

// Diagnostic
#define _DIAGNOSTIC                   "Diagnostic"
#define _DIAGNOSTIC_ID                "Id"
#define _DIAGNOSTIC_SEVERITY          "Severity"
#define _DIAGNOSTIC_IS_SUPPRESSED     "IsSuppressed"
#define _DIAGNOSTIC_MESSAGE           "Message"

// Location
#define _DIAGNOSTIC_LOCATION          "Location"
#define _DIAGNOSTIC_FILE_PATH         "FilePath"
#define _DIAGNOSTIC_START_LINE        "StartLine"
#define _DIAGNOSTIC_START_CHARACTER   "StartCharacter"
#define _DIAGNOSTIC_END_LINE          "EndLine"
#define _DIAGNOSTIC_END_CHARACTER     "EndCharacter"

// Descriptor
#define _DIAGNOSTIC_DESCRIPTOR        "Descriptor"
#define _DIAGNOSTIC_TITLE             "Title"
#define _DIAGNOSTIC_CATEGORY          "Category"
#define _DIAGNOSTIC_DESCRIPTION       "Description"
#define _DIAGNOSTIC_HELP_LINK_URI     "HelpLinkUri"

#define _RULE_PREFIX            "ROSLYN_"
#define _RULE_GROUP_PREFIX      ""

#endif
