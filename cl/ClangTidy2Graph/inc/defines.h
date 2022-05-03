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

#ifndef _CLANGTIDY2GRAPH_DEFINES_H_
#define _CLANGTIDY2GRAPH_DEFINES_H_

#include <sstream>

// xml version
#define _RESULT                     "results"
#define _RESULT_VERSION             "version"
      
// Rule     
#define _RULE                       "error"
#define _RULE_ID                    "id"
#define _RULE_PRIORITY              "severity"
#define _RULE_WARNING               "msg"
#define _RULE_HELP                  "verbose"
#define _RULE_INCONCLUSIVE          "inconclusive"

// RuleName
#define _RULENAME                   "rule"

// Group
#define _GROUPS                     "groups"
#define _GROUP                      "group"
#define _GROUP_ID                   "id"
#define _GROUP_NAME                 "name"
#define _GROUP_DESCRIPTION          "description"
#define _GROUP_HELP                 "help"
#define _GROUP_RULE                 "error"
#define _GROUP_RULE_ID              "id"

// Warning
#define _DIAGNOSTIC                 "Diagnostic"
#define _DIAGNOSTIC_NAME            "DiagnosticName"
#define _DIAGNOSTIC_MSG             "Message"
#define _DIAGNOSTIC_LOCATION_FILE   "FilePath"
#define _DIAGNOSTIC_LOCATION_LINE   "Line"
#define _DIAGNOSTIC_LOCATION_COLUMN "Column"
#define _DIAGNOSTIC_NOTE            "Notes"

#define _RULE_PREFIX            "CLANGTIDY_"


inline std::string formatDisplayName(const std::string& name){
  
  std::ostringstream displaynameS;

  for(std::string::size_type i=0; i < name.length(); ++i){
    if(isupper(name[i]) && i > 0){
      displaynameS << " ";
    }
    displaynameS << name[i];
  }

  std::string ret = displaynameS.str();

  ret[0] = toupper(ret[0]);
  /*
  if(ret.find("Obsolete Functions") != std::string::npos){
    ret = ret.substr(0, 18) + " " + ret.substr(18);
  }else if(ret.find("Nonreentrant Functions") != std::string::npos){
    ret = ret.substr(0, 22) + " " + ret.substr(22);
  }else if(ret == "Wrongmathcall"){
    ret = "Wrong Math Call";
  }*/

  return ret;
}

#endif
