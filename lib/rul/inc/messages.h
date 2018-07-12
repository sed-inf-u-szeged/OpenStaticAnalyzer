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

#ifndef _RUL_MSG_H_
#define _RUL_MSG_H_

#define CMSG_EX_OPEN_INPUT_FILE_MESSAGE(EXMESSAGE, EXLOCATION)                  ":Error while opening input file: " + EXMESSAGE + " (" + EXLOCATION + ")"
#define CMSG_EX_OPEN_INPUT_FILE                                                 ":Error while opening input file"
#define CMSG_EX_RULHANDLER_NOT_EXIST                                            ": RulHandler does not exist"
#define CMSG_EX_CONFIGURATION_ALREADY_EXIST_TWO_MESSAGE( RULEID, CONFIGNAME)    "Configuration already exist: " + RULEID + ":" + CONFIGNAME
#define CMSG_EX_CONFIGURATION_ALREADY_EXIST                                     "Configuration already exist: "
#define CMSG_EX_NONEXIST_OR_ALREADY_EXIST( ORIGINAL, COPIEDNAME)                "The original rule (" + ORIGINAL + ") does not exist, or there is a rule named " + COPIEDNAME + ". You can't overwrite an existing rule."
#define CMSG_EX_LANGUAGE_ALREADY_EXIST( RULEID, CONFIGURATION, RULLANG)         "Language is already exist " + RULEID + ":" + CONFIGURATION + ":" + RULLANG
#define CMSG_EX_ACTUAL_CONFIG_NOT_EXIST                                         "Actual configuration does not exist: "
#define CMSG_SOME_ARGS_NOT_FILLED                           WriteMsg::mlNormal, "Warning(Rulhandler): Some arguments are not filled for %s\n"
#define CMSG_EX_TOOL_DESCRIPTION_NOT_FOUND                                      "Tool description is not found: "
#define CMSG_EX_BASE_LINE_NOT_FOUND                                             "Baseline not found:"
#define CMSG_EX_CONFIGURATION_DOESNOT_EXIT_TWO_MESSAGE( RULEID, CONFIGNAME)     "Configuration does not exist: " + RULEID + ":" + CONFIGNAME
#define CMSG_EX_SETTING_NOT_FOUND                                               "Setting is not found:"
#define CMSG_EX_SETTING_NOT_EDITABLE( RULEID, CONFIGURATION, SETTINGNAME)       "Setting is not editable: " + RULEID + ":" + CONFIGURATION + ":" + SETTINGNAME 
#define CMSG_EX_NO_CONFIGURATION_FOUND_TWO_MESSAGE( RULEID, CONFIG)             "No configuration found: " + RULEID + ":" + CONFIG
#define CMSG_EX_NO_CONFIGURATION_FOUND                                          "No configuration found: "
#define CMSG_EX_CONFIGURATION_NO_PARENT                                         "Configuration does not have parent: "
#define CMSG_EX_NO_CONFIGURATION_OR_LANGUAGE_FOUND_TWO_MESSAGE( RULEID, CONFIG) "Configuration or language is not found: " + RULEID + ":" + CONFIG
#define CMSG_EX_INVALID_ATTRIBUTE_NAME                                          "Attribute name is invalid: "
#define CMSG_EX_LANGUAGE_NOT_FOUND                                              "Language is not found: "
#define CMSG_EX_ATTRIBUTE_NOT_FOUND                                             "Attribute is not found: "
#define CMSG_EX_CONFIGURATION_NOT_FOUND                                         "Configuration is not found: "
#define CMSG_EX_EDGE_NOT_FOUND                                                  "Edge is not found: "
#define CMSG_EX_VIEW_ALREADY_EXIST                                              "View already exists: "
#define CMSG_EX_VIEW_NOT_FOUND                                                  "View is not found: "
#define CMSG_EX_METRIC_NOT_FOUND                                                "Metric is not found: "
#define CMSG_EX_LANGUAGE_NOT_FOUND_THREE_MESSAGE( MSGID, CONFIG, MSGLANGUAGE)   "Language is not found: " + MSGID + ":" + CONFIG + ":" + MSGLANGUAGE
#define CMSG_EX_CONFIGURATION_OR_LANGUAGE_NOT_FOUND_THREE_MESSAGE( MSGID, CONFIG, MSGLANGUAGE) "Configuration or language does not exist: " + MSGID + ":" + CONFIG + ":" + MSGLANGUAGE
#define CMSG_EX_METRIC_NOT_FOUND_FOR                                            "Metric is not found for: "
#define CMSG_EX_CONFIG_METRIC_OR_TOOLDESCRIPTOR                                 "Configuration is outside of metric or tooldescription"
#define CMSG_EX_CONFIGNAME_MISSING                                              "Configuration name is missing"
#define CMSG_EX_TOOLDESCRITIONITEM_MISSING                                      "ToolDescriptionItem name is missing"
#define CMSG_EX_CONFIGURATION_EMPTY                                             "Actual configuration is empty: "
#define CMSG_EX_METRIC_NO_ID                                                    "Metric does not have ID"
#define CMSG_EX_LANGUAGE_NOT_IN_CONFIGURATION_TAG                               "Language is not in configuration tag"
#define CMSG_EX_LANGUAGE_HAS_NOT_LANG_ATTRIBUTE                                 "Language does not have lang attribute"
#define CMSG_EX_ITEM_HAS_NOT_NAME_ATTRIBUTE                                     "Item does not have name attribute"
#define CMSG_EX_UNEXPECTED_EXCEPTION                                            "Unexpected Exception"

#endif