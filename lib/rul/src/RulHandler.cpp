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


#include "rul/inc/RulHandler.h"
#include "rul/inc/messages.h"
#include <common/inc/WriteMessage.h>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLUTF8Transcoder.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>

#include <iostream>
#include <stack>
#include <set>
#include <algorithm>
#include <memory>
#include <io/inc/SimpleXmlIO.h>
#include <common/inc/StringSup.h>

using namespace std;
using namespace common;
XERCES_CPP_NAMESPACE_USE

#define _RUL_FALSE              "false"
#define _RUL_TRUE               "true"
#define _RUL_UNDEFINED          "undefined"
#define _RULE_NAME              "Rul"
#define _DISPLAY_NAME           "DisplayName"
#define _ORIGINAL_ID            "OriginalId"
#define _DESCRIPTION            "Description"
#define _WARNING_TEXT           "WarningText"
#define _WARNING                "Warning"
#define _HELP_TEXT              "HelpText"
#define _TOOL_DESCRIPTION       "ToolDescription"
#define _TOOL_DESCRIPTION_NAME  "name"
#define _TOOL_DESCRIPTION_ITEM  "ToolDescriptionItem"
#define _ENABLED                "Enabled"
#define _METRIC                 "Metric"
#define _METRIC_ID              "id"
#define _DEFAULT_CONFIG         "Default"
#define _DEFAULT_NAME           "name"
#define _SETTINGS               "Settings"
#define _SETTING                "Setting"
#define _SETTING_EDITABLE       "editable"
#define _SETTING_NAME           "name"
#define _CONFIG                 "Configuration"
#define _CONFIG_NAME            "name"
#define _GROUP                  "Group"
#define _GROUP_MEMBER           "GroupMember"
#define _CONFIGURATIONS         "Configurations"
#define _CONFIGURATIONS_CONFIG  "config"
#define _CCNAME                 "name"
#define _CCREDEFINE             "redefine"
#define _LANGUAGE               "Language"
#define _LANGUAGE_LANG          "lang"
#define _EDGE_TYPES             "Edges"
#define _EDGE                   "Edge" //_EDGE_TYPES_ITEM
#define _EDGE_NAME              "name"
#define _EDGE_TYPES_NAME        "name"
#define _VIEWS                  "Views"
#define _VIEW                   "View"
#define _VIEW_NAME              "name"
#define _AGREGATED_FORMULA      "AggregatedFormula"
#define _BASELINES              "Baselines"
#define _BASELINE               "Baseline"
#define _BASELINE_NAME          "name"
#define _NUMERIC_TYPE           "NumericType"
#define _VISIBLE                "Visible"
#define _SUMMARIZED             "summarized"
#define _VISUAL                 "visual"
#define _RUL_EMPTY_STRING       "~~@RUL_EMPTY_STRING@~~"
#define _CALCULATED             "Calculated"
#define _ELEMENT                "CalculatedFor"

namespace columbus {

namespace rul {

const string RulHandler::_empty_string = _RUL_EMPTY_STRING;
  
RulHandler::RulHandler(const string& rulFileName,  const string& conf, const string& lang, const string& encoding)
  : rulData()
  , _configuration(conf)
  , _language(lang)
  , _filename(rulFileName)
  , _strictMode(false)
  , _xerces_inited(true)
{
  xercesInit();
  parseXML(rulFileName, encoding);
  createIndex();
}

RulHandler::RulHandler(const string& conf,  const string& lang)
  : rulData()
  , _configuration(conf)
  , _language(lang)
  , _filename()
  , _strictMode(false)
  , _xerces_inited(false)
{
}

RulHandler::RulHandler(const RulHandler& handler, bool emptyRulData)
  : rulData()
  , _filename("rul_in_memory")
{
  _configuration = handler.getConfig();
  _language = handler.getLanguage();
  _strictMode = handler.getIsStrictMode();
  _xerces_inited = true;
  createIndex();
}

void RulHandler::copyMetric(const RulHandler& fromRul, const string& fromName, const string& toName)
{
  if(fromRul.getIsDefined(fromName) && !getIsDefined(toName)) {
  RulMetric rlm = *fromRul.findMetric(fromName);
  rulData.metrics.insert(make_pair(toName, rlm));
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_NONEXIST_OR_ALREADY_EXIST (fromName, toName) );
  }
}

RulHandler::~RulHandler()
{
  if(_xerces_inited)
    xercesTerminate();
}

int RulHandler::xercesInited = 0;

void RulHandler::xercesInit()
{
  if(xercesInited == 0) {
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        string messageString = message;
        XMLString::release(&message);
        throw RulHandlerException("xercesInit", messageString);
    }
  }
  ++xercesInited;
}

void RulHandler::xercesTerminate()
{
  --xercesInited;
  if(xercesInited == 0) {
    try {
      XMLPlatformUtils::Terminate();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        string messageString = message;
        XMLString::release(&message);
        throw RulHandlerException("xercesTerminate", messageString);
    }
  }
}


void RulHandler::createIndex()
{
  for(map<string, RulMetric>::iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    // set configuration paret and actual lang
    for(map<string, RulConfiguration>::iterator configurationIt = metricIt->second.configs.begin(); configurationIt != metricIt->second.configs.end(); ++configurationIt ) {
      // set parent
      map<string,string>::iterator parentNameIt = rulData.redefines.find(configurationIt->first);
      if(parentNameIt != rulData.redefines.end()) {
        map<string, RulConfiguration>::iterator paretConfigIt = metricIt->second.configs.find(parentNameIt->second);
        if(paretConfigIt != metricIt->second.configs.end()) {
          configurationIt->second.parentConfig = &(paretConfigIt->second);
        }
      }
      // find actual language in actual configuration
      map<string, RulLang>::iterator actualLangIt = configurationIt->second.langs.find(_language);
      if(actualLangIt != configurationIt->second.langs.end()) {
        configurationIt->second.actualLang = &(actualLangIt->second);
      }

    }
    // find actual configuration in metric
    map<string, RulConfiguration>::iterator actualConfigIt = metricIt->second.configs.find(_configuration);
    if(actualConfigIt != metricIt->second.configs.end()) {
      metricIt->second.actualConfig = &(actualConfigIt->second);
    }
  }
}

void RulHandler::clearIndex()
{
  for(map<string, RulMetric>::iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    // set configuration paret and actual lang
    for(map<string, RulConfiguration>::iterator configurationIt = metricIt->second.configs.begin(); configurationIt != metricIt->second.configs.end(); ++configurationIt ) {
      // set parent
      map<string,string>::iterator parentNameIt = rulData.redefines.find(configurationIt->first);
      if(parentNameIt != rulData.redefines.end()) {
        configurationIt->second.parentConfig = NULL;
      }
      // find actual language in actual configuration
      configurationIt->second.actualLang = NULL;
    }
    // find actual configuration in metric
    metricIt->second.actualConfig = NULL;
  }
}

void RulHandler::turnOnStrictMode()
{
  _strictMode = true;
}

void RulHandler::turnOffStrictMode()
{
  _strictMode = false;
}

bool RulHandler::getIsStrictMode() const
{
  return _strictMode;
}

void RulHandler::createConfiguration(const string& ruleId, const string& configName)
{
  RulMetric* metric = findMetric(ruleId);
  map<string, RulConfiguration>::iterator configIt = metric->configs.find(configName);
    
  if(configIt != metric->configs.end()) {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_ALREADY_EXIST_TWO_MESSAGE( ruleId, configName));
  } else {
    configIt = metric->configs.insert(make_pair(configName, RulConfiguration())).first;
    configIt->second.enabled = rulFalse;
    if(configName == _configuration) {
      metric->actualConfig = &configIt->second;
    }
  }

}

void RulHandler::createConfigurationForToolDescription(const string& configName)
{
  bool inserted = rulData.toolDescription.insert(make_pair(configName, map<string,string>()) ).second;
  if(!inserted) {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_ALREADY_EXIST + configName);
  }
}

void RulHandler::copyMetric(const string& fromName, const string& toName)
{
  if(getIsDefined(fromName) && !getIsDefined(toName)) {
  RulMetric* metric = findMetric(fromName);
  RulMetric &tmp = *metric;
  rulData.metrics.insert(make_pair(toName, tmp));
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_NONEXIST_OR_ALREADY_EXIST (fromName, toName) );
  }
}


void RulHandler::deleteConfiguration(const string& config)
{
  for(map<string, RulMetric>::iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    metricIt->second.configs.erase(config);
    if(config == _configuration) {
      metricIt->second.actualConfig = NULL;
    }
  }
  rulData.redefines.erase(config);
  rulData.toolDescription.erase(config);
}

void RulHandler::deleteConfiguration(const string& ruleId, const string& config)
{
  RulMetric* metric = findMetric(ruleId);
  metric->configs.erase(config);
  if(config == _configuration) {
    metric->actualConfig = NULL;
  }
}

void RulHandler::createLanguage(const string& ruleId, const string& lang)
{
  RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig != NULL) {
    
    map<string, RulLang>::iterator actLang = metric->actualConfig->langs.find(lang);
      
    if(actLang != metric->actualConfig->langs.end()) {
      throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_LANGUAGE_ALREADY_EXIST( ruleId, _configuration, lang));
    } else {
      actLang =  metric->actualConfig->langs.insert(make_pair(lang, RulLang())).first;
      actLang->second.warning = rulFalse;
      if(_language == lang) {
        metric->actualConfig->actualLang = &(actLang->second);
      }
    }
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_ACTUAL_CONFIG_NOT_EXIST + _configuration);
  }
}

void RulHandler::createLanguage(const string& ruleId, const string& configuration, const string& lang)
{
  RulConfiguration* config = findConfiguration(ruleId, configuration);
  pair<map<string, RulLang>::iterator, bool> langCreated = config->langs.insert(make_pair(lang, RulLang()));
  if(langCreated.second) {
    if(_language == lang) {
      config->actualLang = &(langCreated.first->second);
    }
    langCreated.first->second.warning = rulFalse;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_LANGUAGE_ALREADY_EXIST( ruleId, _configuration, lang));
  }
}

void RulHandler::deleteLanguage(const string& lang)
{
  for(map<string, RulMetric>::iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    for(map<string, RulConfiguration>::iterator configIt = metricIt->second.configs.begin(); configIt != metricIt->second.configs.end(); ++configIt) {
      configIt->second.langs.erase(lang);
    }
  }
  createIndex();
}

string RulHandler::getWarningText(const string& ruleId) const
{
  return getLangSpecData(ruleId, &RulLang::warningText, _empty_string);
}

void RulHandler::setWarningText(const string& ruleId, const string& warningText)
{
  setLangSpecData(ruleId, &RulLang::warningText , warningText);
}

void RulHandler::setWarningText(const string& ruleId, const string& configuration, const string& warningText, const string& lang)
{
  setLangSpecData(ruleId, configuration, lang, &RulLang::warningText, warningText);
}

string RulHandler::getLineBreakWarningText(const string& ruleID, const list<string>& arg) const
{
  string ret = getWarningText(ruleID);

  list<string>::const_iterator argIt = arg.begin();

  string::size_type idx = 0;
  string endOfLine = "\n";
  string tabSign = "\t";
  while (true)
  {
    idx = ret.find("%", idx);
    if (idx == string::npos)
      break;

    const size_t &retLen = ret.length();
    if(idx+1 < retLen && ret[idx+1] == 'n'){
      ret.replace(idx,2,endOfLine);
      idx += endOfLine.length();
    }
    else if(idx+1 < retLen && ret[idx+1] == 't'){
      ret.replace(idx,2,tabSign);
      idx += tabSign.length();
    }
    else{
      if(argIt == arg.end() ){
        WriteMsg::write( CMSG_SOME_ARGS_NOT_FILLED, ruleID.c_str());
        return ret;
      }

      ret.replace(idx, 1, *argIt);
      idx += argIt->length();
      argIt++;
    }
  }
  return ret;
}

string RulHandler::getToolDescription(const string& field) const
{
  string config = _configuration;
  map<string, map<string, string> >::const_iterator configIt = rulData.toolDescription.find(config);
  while(true) {
    if(configIt != rulData.toolDescription.end()) {
      map<string, string>::const_iterator valueIt = configIt->second.find(field);
      if(valueIt != configIt->second.end()) {
        if(valueIt->first != _empty_string) {
          return valueIt->second;
        }
      }
    }
    
    // find parent of configuration
    map<string, string>::const_iterator redefIt = rulData.redefines.find(config);
    if(redefIt != rulData.redefines.end()) {
      config = redefIt->second;
      configIt = rulData.toolDescription.find(redefIt->second);
    } else {
      break;
    }
  }
  throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_DESCRIPTION_NOT_FOUND + field);
}

void RulHandler::setToolDescription(const string& field, const string& description)
{
  setToolDescription(field, description, _configuration);
}

void RulHandler::setToolDescription(const string& field, const string& description, const string& configuration)
{
  rulData.toolDescription[configuration][field] = description;
}

bool RulHandler::getIsDefined(const string& ruleId) const
{
  map<string, RulMetric>::const_iterator metricIt =  rulData.metrics.find(ruleId);
  if(metricIt != rulData.metrics.end()) {
    return true;
  } else {
    return false;
  }
}

void RulHandler::defineMetric(const string& ruleId)
{
  rulData.metrics.insert(make_pair(ruleId, RulMetric()));
}

void RulHandler::deleteMetric(const string& ruleId)
{
  rulData.metrics.erase(ruleId);
}

bool RulHandler::getIsEnabled(const string& ruleId) const
{
  return getConfSpecData(ruleId, &RulConfiguration::enabled, rulUndefined) == rulTrue;
}

void RulHandler::setIsEnabled(const string& ruleId, bool enabled)
{
  setConfSpecData(ruleId, &RulConfiguration::enabled, enabled ? rulTrue : rulFalse);
}

void RulHandler::setIsEnabled(const string& ruleId, const string& configuration, bool enabled)
{
  setConfSpecData(ruleId, configuration, &RulConfiguration::enabled, enabled ? rulTrue : rulFalse);
}

bool RulHandler::getIsVisible(const string& ruleId) const
{
  return getConfSpecData(ruleId, &RulConfiguration::visiable, rulUndefined) == rulTrue;
}

void RulHandler::setIsVisible(const string& ruleId, bool visible)
{
  setConfSpecData(ruleId, &RulConfiguration::visiable, visible ? rulTrue : rulFalse);
}

void RulHandler::setIsVisible(const string& ruleId, const string& configuration, bool visible)
{
  setConfSpecData(ruleId, configuration, &RulConfiguration::visiable, visible ? rulTrue : rulFalse);
}

string RulHandler::getHelpText(const string& ruleId) const
{
  return getLangSpecData(ruleId, &RulLang::helpText, _empty_string);
}

void RulHandler::setHelpText(const string& ruleId, const string& helpText)
{
  setLangSpecData(ruleId, &RulLang::helpText, helpText);
}

void RulHandler::setHelpText(const string& ruleId, const string& configuration , const string& helpText, const string& lang)
{
  setLangSpecData(ruleId, configuration, lang, &RulLang::helpText, helpText);
}

bool RulHandler::getHasWarningText(const string& ruleId) const
{
  return getLangSpecData(ruleId, &RulLang::warning, rulUndefined) == rulTrue;
}

void RulHandler::setHasWarningText(const string& ruleId,bool hasWarningText)
{
  setLangSpecData(ruleId, &RulLang::warning, hasWarningText ? rulTrue : rulFalse);
}

void RulHandler::setHasWarningText(const string& ruleId, const string& configuration,bool hasWarningText, const string& lang)
{
  setLangSpecData(ruleId, configuration, lang, &RulLang::warning, hasWarningText ? rulTrue : rulFalse);
}

string RulHandler::getDisplayName(const string& ruleId) const
{
  return getLangSpecData(ruleId, &RulLang::displayName, _empty_string);
}

void RulHandler::setDisplayName(const string& ruleId, const string& name)
{
  setLangSpecData(ruleId, &RulLang::displayName, name);
}

void RulHandler::setDisplayName(const string& ruleId, const string& configuration, const string& name, const string& lang)
{
  setLangSpecData(ruleId, configuration, lang, &RulLang::displayName, name);
}

string RulHandler::getDescription(const string& ruleId) const
{
  return getLangSpecData(ruleId, &RulLang::description, _empty_string);
}

void RulHandler::setDescription(const string& ruleId, const string& description)
{
  setLangSpecData(ruleId, &RulLang::description, description);
}

void RulHandler::setDescription(const string& ruleId, const string& configuration, const string& description, const string& lang)
{
  setLangSpecData(ruleId, configuration, lang, &RulLang::description, description);
}

string RulHandler::getBaselineValue(const string& ruleId, const string& baselineName) const
{
  map<string, string>::const_iterator baselineIt;
  bool found = false;
  getConfSpecDataFromMap(ruleId, baselineName, &RulConfiguration::baselines, baselineIt, _empty_string, found);
  if(found) {
    return baselineIt->second;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_BASE_LINE_NOT_FOUND + baselineName);
  }
}

void RulHandler::setBaselineValue(const string& ruleId, const string& configuration, const string& baselineName, const string& value)
{
  RulConfiguration* config = findConfiguration(ruleId, configuration);
  config->baselines[baselineName] = value;
}

void RulHandler::setBaselineValue(const string& ruleId, const string& baselineName, const string& value)
{
  RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig != NULL) {
    metric->actualConfig->baselines[baselineName] = value;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_DOESNOT_EXIT_TWO_MESSAGE( ruleId, _configuration));
  }
}

string RulHandler::getSettingValue(const string& ruleId, const string& settingName) const
{
  map<string, RulSetting>::const_iterator settingIt;
  bool found = false;
  getConfSpecDataFromMap(ruleId, settingName, &RulConfiguration::settings, settingIt, _empty_string, found);
  if(found) {
    return settingIt->second.text;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_SETTING_NOT_FOUND + settingName);
  }
}

void RulHandler::manuallyCreateIndex()
{
  createIndex();
}

void RulHandler::setSettingValue(const string& ruleId, const string& configName, RulConfiguration* config, const string& settingName, const string& value,bool isEditable)
{
  map<string, RulSetting>::iterator settingIt = config->settings.find(settingName);
  if(settingIt == config->settings.end() || settingIt->second.editable == rulTrue) {
    RulSetting rulSetting;
    rulSetting.editable = isEditable ? rulTrue : rulFalse;
    rulSetting.text = value;
    config->settings[settingName] = rulSetting;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_SETTING_NOT_EDITABLE( ruleId, configName, settingName ));
  }
}

void RulHandler::setSettingValue(const string& ruleId, const string& configuration, const string& settingName, const string& value,bool isEditable)
{
  RulConfiguration* config = findConfiguration(ruleId, configuration);
  setSettingValue(ruleId, configuration, config, settingName, value, isEditable);
}

void RulHandler::setSettingValue(const string& ruleId, const string& settingName, const string& value,bool isEditable)
{
  RulConfiguration* config = findMetric(ruleId)->actualConfig;
  if(config != NULL) {
    setSettingValue(ruleId, _configuration, config, settingName, value, isEditable);
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_DOESNOT_EXIT_TWO_MESSAGE( ruleId, _configuration));
  }
}

bool RulHandler::getSettingIsEditable(const string& ruleId, const string& settingName) const
{
  map<string, RulSetting>::const_iterator settingIt;
  bool found = false;
  getConfSpecDataFromMap(ruleId, settingName, &RulConfiguration::settings, settingIt, _empty_string, found);
  if(found) {
    return settingIt->second.editable == rulTrue;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_SETTING_NOT_FOUND + settingName);
  }
}

string RulHandler::getGroupType(const string& ruleId) const
{
  return getConfSpecData(ruleId, &RulConfiguration::group, _empty_string);
}

void RulHandler::setGroupType(const string& ruleId, const string& groupType)
{
  setConfSpecData(ruleId, &RulConfiguration::group, groupType);
}

void RulHandler::setGroupType(const string& ruleId, const string& configuration, const string& groupType)
{
  setConfSpecData(ruleId, configuration,&RulConfiguration::group, groupType);
}

void RulHandler::getMetricGroupMembers(const string& ruleId, set<string>& groupMembers) const
{
  insert_iterator<set<string>> insertIt(groupMembers, groupMembers.end());
  getMetricGroupMembers(ruleId, insertIt);
}

void RulHandler::addMetricGroupMembers(const string& ruleId, const string& groupId)
{
  RulConfiguration* config = findMetric(ruleId)->actualConfig;
  if(config != NULL) {
    config->groupMember.insert(groupId);
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_DOESNOT_EXIT_TWO_MESSAGE( ruleId, _configuration));
  }
}

void RulHandler::addMetricGroupMembers(const string& ruleId, const string& configuration, const string& groupId)
{
  RulConfiguration* config = findConfiguration(ruleId, configuration);
  config->groupMember.insert(groupId);
}

void RulHandler::getGroupMembers(const string& groupId, set<string>& groupMembers) const
{
  insert_iterator<set<string>> insertIt(groupMembers, groupMembers.end());
  getGroupMembers(groupId, insertIt);
}

void RulHandler::getGroupMembers(const string& groupId, vector<string>& groupMembers) const
{
  set<string> sset;
  getGroupMembers(groupId, sset);
  for(set<string>::const_iterator it = sset.begin(); it != sset.end(); ++it) {
    groupMembers.push_back(*it);
  }
}

void RulHandler::getMetricConfigurations(const string& ruleId, vector<string>& list) const
{
  set<string> stringSet;
  const RulMetric* metric = findMetric(ruleId);
  for(map<string, RulConfiguration>::const_iterator configIt = metric->configs.begin(); configIt != metric->configs.end(); ++configIt) {
    stringSet.insert(configIt->first);
  }

  for(set<string>::const_iterator it = stringSet.begin(); it != stringSet.end(); ++it) {
    list.push_back(*it);
  }
}

void RulHandler::getMetricAndConfigurationLanguages(const string& ruleId, set<string>& list) const
{
  const RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig != NULL) {
    for(map<string, RulLang>::const_iterator it = metric->actualConfig->langs.begin(); it != metric->actualConfig->langs.end(); ++it ) {
      list.insert(it->first);
    }
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_NO_CONFIGURATION_FOUND_TWO_MESSAGE( ruleId, _configuration) );
  }
}

void RulHandler::getMetricAndConfigurationLanguages(const string& ruleId, const string& configuration, set<string>& list) const
{
  const RulMetric* metric = findMetric(ruleId);

  map<string, RulConfiguration>::const_iterator configIt = metric->configs.find(configuration);
  if(configIt != metric->configs.end()) {
    for(map<string, RulLang>::const_iterator it = configIt->second.langs.begin(); it != configIt->second.langs.end(); ++it ) {
      list.insert(it->first);
    }
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_NO_CONFIGURATION_FOUND + configuration  );
  }
}

void RulHandler::getAllConfigurations(set<string>& list) const
{
  for(map<string, RulMetric>::const_iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {

    for(map<string, RulConfiguration>::const_iterator configIt = metricIt->second.configs.begin(); configIt != metricIt->second.configs.end(); ++configIt ) {
      list.insert(configIt->first);
    }
  }
}

string RulHandler::getConfigParent(const string& config)
{
  map<string,string>::const_iterator redefineIt = rulData.redefines.find(config);
  if(redefineIt != rulData.redefines.end()) {
    return redefineIt->second;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_NO_PARENT + config);
  }
}

bool RulHandler::hasConfigParent(const string& config)
{
  map<string,string>::const_iterator redefineIt = rulData.redefines.find(config);
  if(redefineIt != rulData.redefines.end()) {
    return true;
  } else {
    return false;
  }
}

void RulHandler::setConfigParent(const string& config, const string& parent)
{
  rulData.redefines[config] = parent;
}

void RulHandler::deleteConfigParent(const string& config)
{
  rulData.redefines.erase(config);
}

void RulHandler::getRuleIdList(vector<string>& list) const
{
  insert_iterator<vector<string>> insertIt(list, list.end());
  getRuleIdList(insertIt);
  sort(list.begin(), list.end());
}

void RulHandler::getRuleIdList(set<string>& s) const
{
  insert_iterator<set<string>> insertIt(s, s.end());
  getRuleIdList(insertIt);
}

void RulHandler::getGroupIdList(vector<string>& list)
{
  insert_iterator<vector<string>> insertIt(list, list.end());
  getGroupIdList(insertIt);
}

void RulHandler::getGroupIdList(set<string>& list)
{
  insert_iterator<set<string>> insertIt(list, list.end());
  getGroupIdList(insertIt);
}

void RulHandler::getMetricSettingsName(const string& ruleId, set<string>& list)
{
  const RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig != NULL) {
    const RulConfiguration* config = metric->actualConfig;
    do {
      for(map<string, RulSetting>::const_iterator settingIt = config->settings.begin(); settingIt != config->settings.end(); ++settingIt) {
        list.insert(settingIt->first);
      }
      config = getParentConfig(config);
    } while(!_strictMode && config != NULL);
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_NO_CONFIGURATION_FOUND_TWO_MESSAGE( ruleId, _configuration) );
  }
}

void RulHandler::writeRulToolDescription(io::SimpleXmlIO& xml) const
{
  for(map<string, map<string, string> >::const_iterator configIt = rulData.toolDescription.begin(); configIt != rulData.toolDescription.end(); ++configIt) {
    xml.writeBeginElement(_CONFIG);
    xml.writeAttribute(_CONFIG_NAME, configIt->first);
    for(map<string, string>::const_iterator tooldId = configIt->second.begin(); tooldId != configIt->second.end(); ++tooldId) {
      xml.writeBeginElement(_TOOL_DESCRIPTION_ITEM);
      xml.writeAttribute(_TOOL_DESCRIPTION_NAME, tooldId->first);
      xml.writeElementContent(tooldId->second);
      xml.writeEndElement();
    }
    xml.writeEndElement();
  }
}

void RulHandler::writeRulRedefines(io::SimpleXmlIO& xml ) const
{
  for(map<string, string>::const_iterator redefineIt = rulData.redefines.begin(); redefineIt != rulData.redefines.end(); ++redefineIt) {
    xml.writeBeginElement(_CONFIGURATIONS_CONFIG);
    xml.writeAttribute(_CCNAME, redefineIt->first);
    xml.writeAttribute(_CCREDEFINE, redefineIt->second);
    xml.writeEndElement();
  }
}

void RulHandler::writeRulViews(io::SimpleXmlIO& xml ) const
{
  for(map<string, set<string> >::const_iterator viewIt = rulData.viewEdges.begin(); viewIt != rulData.viewEdges.end(); ++viewIt ) {
    xml.writeBeginElement(_VIEW) ;
    xml.writeAttribute(_VIEW_NAME, viewIt->first);
    for(set<string>::const_iterator edgeIt = viewIt->second.begin(); edgeIt != viewIt->second.end(); ++edgeIt) {
      xml.writeBeginElement(_EDGE);
      xml.writeAttribute(_EDGE_NAME, *edgeIt);
      xml.writeEndElement();
    }
    xml.writeEndElement();
  }
}

void RulHandler::writeRulEdgeTypes(io::SimpleXmlIO& xml ) const
{
  for(map<string, string>::const_iterator edgeIt = rulData.edges.begin(); edgeIt != rulData.edges.end(); ++edgeIt) {
    xml.writeBeginElement(_EDGE);
    xml.writeAttribute(_EDGE_TYPES_NAME, edgeIt->first);
    xml.writeElementContent(edgeIt->second);
    xml.writeEndElement();
  }
}

inline void RulHandler::writeRulAttribute(io::SimpleXmlIO& xml, const char* tagName, const string& value) const
{
  if(value != _empty_string) {
    xml.writeBeginElement(tagName);
    xml.writeElementContent(value);
    xml.writeEndElement();
  }
}


inline void RulHandler::writeRulAttribute(io::SimpleXmlIO& xml, const char* tagName, const RulHandler::RulBoolean& value) const
{
  if(value != rulUndefined) {
    xml.writeBeginElement(tagName);
    xml.writeElementContent(rulBooleanToString(value));
    xml.writeEndElement();
  }
}


void RulHandler::writeRulMetric(io::SimpleXmlIO& xml ) const
{
  vector< pair<string, const RulMetric*> > sortedMetricList;
  sortedMetricList.reserve(rulData.metrics.size() + 1);

  for(map<string, RulMetric>::const_iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    sortedMetricList.push_back(make_pair(metricIt->first, &(metricIt->second)));
  }

  sort(sortedMetricList.begin(), sortedMetricList.end());

  for(vector< pair<string, const RulMetric*> >::const_iterator metricIt = sortedMetricList.begin(); metricIt != sortedMetricList.end(); ++metricIt) {
    xml.writeBeginElement(_METRIC);
    xml.writeAttribute(_METRIC_ID, metricIt->first);
    for(map<string, RulConfiguration>::const_iterator configIt = metricIt->second->configs.begin(); configIt != metricIt->second->configs.end(); ++configIt) {
      xml.writeBeginElement(_CONFIG);
      xml.writeAttribute(_CONFIG_NAME, configIt->first);

      writeRulAttribute(xml, _ENABLED, configIt->second.enabled);
      writeRulAttribute(xml, _VISIBLE, configIt->second.visiable);
      writeRulAttribute(xml, _GROUP, configIt->second.group);
      writeRulAttribute(xml, _ORIGINAL_ID, configIt->second.originalId);
      writeRulAttribute(xml, _AGREGATED_FORMULA, configIt->second.aggregatedFormula);
      writeRulAttribute(xml, _NUMERIC_TYPE, configIt->second.numeric);

      for(set<string>::const_iterator groupmemberIt = configIt->second.groupMember.begin(); groupmemberIt != configIt->second.groupMember.end(); ++groupmemberIt) {
        writeRulAttribute(xml, _GROUP_MEMBER, *groupmemberIt);
      }
      writeRulLang(xml, configIt->second);

      xml.writeBeginElement(_BASELINES);
      for(map<string, string>::const_iterator baselineIt = configIt->second.baselines.begin(); baselineIt != configIt->second.baselines.end(); ++baselineIt ) {
        xml.writeBeginElement(_BASELINE);
        xml.writeAttribute(_BASELINE_NAME, baselineIt->first);
        xml.writeElementContent(baselineIt->second);
        xml.writeEndElement();
      }
      xml.writeEndElement();

      xml.writeBeginElement(_SETTINGS);
      for(map<string, RulSetting>::const_iterator settingIt = configIt->second.settings.begin(); settingIt != configIt->second.settings.end(); ++settingIt) {
        xml.writeBeginElement(_SETTING);
        xml.writeAttribute(_SETTING_NAME, settingIt->first);
        xml.writeAttribute(_SETTING_EDITABLE, rulBooleanToString(settingIt->second.editable));
        xml.writeElementContent(settingIt->second.text);
        xml.writeEndElement();
      }
      xml.writeEndElement();

      xml.writeBeginElement(_CALCULATED);
      for(set<string>::const_iterator calcElementsIt = configIt->second.calculated.begin(); calcElementsIt != configIt->second.calculated.end(); ++calcElementsIt) {
        xml.writeBeginElement(_ELEMENT);
        xml.writeElementContent(*calcElementsIt);
        xml.writeEndElement();
      }
      xml.writeEndElement();

      xml.writeEndElement();
    }
    xml.writeEndElement();
  }
}

void RulHandler::writeRulLang(io::SimpleXmlIO& xml, const RulConfiguration& rulConfig ) const
{
  for(map<string, RulLang>::const_iterator langIt = rulConfig.langs.begin(); langIt != rulConfig.langs.end(); ++langIt) {
    xml.writeBeginElement(_LANGUAGE);
    xml.writeAttribute(_LANGUAGE_LANG, langIt->first);
    writeRulAttribute(xml,_WARNING, langIt->second.warning);
    writeRulAttribute(xml, _DISPLAY_NAME, langIt->second.displayName);
    writeRulAttribute(xml, _DESCRIPTION, langIt->second.description);
    writeRulAttribute(xml, _HELP_TEXT, langIt->second.helpText);
    writeRulAttribute(xml, _WARNING_TEXT, langIt->second.warningText);
    xml.writeEndElement();
  }
}

void RulHandler::saveRul(const string& filename) const
{
  io::SimpleXmlIO xml(filename, io::IOBase::omWrite);
  xml.writeXMLDeclaration("1.0", "UTF-8");
  xml.writeBeginElement(_RULE_NAME);
  xml.writeAttribute("xmlns","OpenStaticAnalyzer");
  xml.writeAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
  xml.writeBeginElement(_TOOL_DESCRIPTION);
  writeRulToolDescription(xml);
  xml.writeEndElement();

  xml.writeBeginElement(_CONFIGURATIONS);
  writeRulRedefines(xml);
  xml.writeEndElement();

  xml.writeBeginElement(_VIEWS);
  writeRulViews(xml);
  xml.writeEndElement();

  xml.writeBeginElement(_EDGE_TYPES);
  writeRulEdgeTypes(xml);
  xml.writeEndElement();

  writeRulMetric(xml);

  xml.writeEndElement();
  xml.close();
}

const string& RulHandler::getConfig() const
{
  return _configuration;
}

const string& RulHandler::getLanguage() const
{
  return _language;
}

void RulHandler::setConfig(const string& configuration)
{
  _configuration = configuration;
  clearIndex();
  createIndex();
}

void RulHandler::setLanguage(const string& language)
{
  _language = language;
  clearIndex();
  createIndex();
}

void RulHandler::getExistingAttributes(const string& ruleId, set<string>& attributeSet) const
{
  const RulMetric* metric = findMetric(ruleId) ;
  if(metric->actualConfig != NULL && metric->actualConfig->actualLang != NULL) {
    if(metric->actualConfig->enabled != rulUndefined) {
      attributeSet.insert(_ENABLED);
    }
    if(metric->actualConfig->group != _empty_string) {
      attributeSet.insert(_GROUP);
    }
    if(!metric->actualConfig->groupMember.empty()) {
      attributeSet.insert(_GROUP_MEMBER);
    }
    if(metric->actualConfig->numeric != rulUndefined) {
      attributeSet.insert(_NUMERIC_TYPE);
    }
    if(metric->actualConfig->visiable != rulUndefined) {
      attributeSet.insert(_VISIBLE);
    }
    if(metric->actualConfig->actualLang->description != _empty_string) {
      attributeSet.insert(_DESCRIPTION);
    }
    if(metric->actualConfig->actualLang->displayName != _empty_string) {
      attributeSet.insert(_DISPLAY_NAME);
    }
    if(metric->actualConfig->actualLang->helpText != _empty_string) {
      attributeSet.insert(_HELP_TEXT);
    }
    if(metric->actualConfig->actualLang->warning != rulUndefined) {
      attributeSet.insert(_WARNING);
    }
    if(metric->actualConfig->actualLang->warningText != _empty_string) {
      attributeSet.insert(_WARNING_TEXT);
    }
    if(!metric->actualConfig->settings.empty()) {
      attributeSet.insert(_SETTINGS);
    }
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_NO_CONFIGURATION_OR_LANGUAGE_FOUND_TWO_MESSAGE( ruleId, _configuration));
  }
}

string RulHandler::getAttribute(const string& ruleId, const string& configuration, const string& language, const string& attributeName) const
{
  const RulMetric* metric = findMetric(ruleId);

  map<string, RulConfiguration>::const_iterator configIt = metric->configs.find(configuration);
  if(configIt != metric->configs.end()) {
    const RulConfiguration* config = &configIt->second;
    while(config != NULL) {
      if(attributeName == _ENABLED) {
        if(config->enabled != rulUndefined) {
          return rulBooleanToString(config->enabled);
        }
      } else if (attributeName == _GROUP) {
        if(config->group != _empty_string) {
          return config->group;
        }
      } else if (attributeName == _NUMERIC_TYPE) {
        if(config->numeric != rulUndefined) {
          return rulBooleanToString(config->numeric);
        }
      } else if (attributeName == _VISIBLE) {
        if(config->visiable != rulUndefined) {
          return rulBooleanToString(config->visiable);
        }
      } else {
        if(config->actualLang != NULL) {
          if(attributeName == _DESCRIPTION) {
            if(config->actualLang->description != _empty_string) {
              return config->actualLang->description;
            }
          } else if (attributeName == _DISPLAY_NAME) {
            if(config->actualLang->displayName != _empty_string) {
              return config->actualLang->displayName;
            }
          } else if (attributeName == _HELP_TEXT) {
            if(config->actualLang->helpText != _empty_string) {
              return config->actualLang->helpText;
            }
          } else if (attributeName == _WARNING) {
            if(config->actualLang->warning != rulUndefined) {
              return rulBooleanToString(config->actualLang->warning);
            }
          } else if (attributeName == _WARNING_TEXT) {
            if(config->actualLang->warningText != _empty_string) {
              return config->actualLang->warningText;
            }
          } else {
            throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NAME + attributeName);
          }
        } else {
          throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_LANGUAGE_NOT_FOUND + _language);
        }
      }
      if(!_strictMode) {
        config = getParentConfig(config);
      } else {
        throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_ATTRIBUTE_NOT_FOUND + attributeName);
      }
    }
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_ATTRIBUTE_NOT_FOUND + attributeName);
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_NO_PARENT + configuration);
  }

  return "";
}

void RulHandler::setAttribute(const string& ruleId, const string& configuration, const string& language, const string& attributeName, const string value)
{
  if(attributeName == _ENABLED) {
    setIsEnabled(ruleId, configuration, common::stringLower(value) == _RUL_TRUE);
  } else if (attributeName == _GROUP) {
    setGroupType(ruleId, configuration, value);
  } else if (attributeName == _NUMERIC_TYPE) {
    setIsNumericType(ruleId, configuration, common::stringLower(value) == _RUL_TRUE);
  } else if (attributeName == _VISIBLE) {
    setIsVisible(ruleId, configuration, common::stringLower(value) == _RUL_TRUE);
  } else if(attributeName == _DESCRIPTION) {
    setDescription(ruleId, configuration, value, language);
  } else if (attributeName == _DISPLAY_NAME) {
    setDisplayName(ruleId, configuration, value, language);
  } else if (attributeName == _HELP_TEXT) {
    setHelpText(ruleId, configuration, value, language);
  } else if (attributeName == _WARNING) {
    setHasWarningText(ruleId, configuration, common::stringLower(value) == _RUL_TRUE, language);
  } else if (attributeName == _WARNING_TEXT) {
    setWarningText(ruleId, configuration, value, language);
  }
}

void RulHandler::getAllLanguages(set<string>& languages)
{
  for(map<string, RulMetric>::const_iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    for(map<string, RulConfiguration>::const_iterator configIt = metricIt->second.configs.begin(); configIt != metricIt->second.configs.end(); ++configIt ) {
      for(map<string, RulLang>::const_iterator langIt = configIt->second.langs.begin(); langIt != configIt->second.langs.begin(); ++langIt) {
        languages.insert(langIt->first);
      }
    }
  }
}

void RulHandler::getMapWarningsToGroups(map<string, string>& mapping)
{
  set<string> groups;
  getGroupIdList(groups);
  set<string>::iterator it, it2;

  for(it = groups.begin(); it != groups.end(); it++){
    set<string> groupMembers;
    getGroupMembers(*it, groupMembers);
    for(it2 = groupMembers.begin(); it2 != groupMembers.end(); it2++)
      mapping[*it2] = *it;
  }
}

void RulHandler::getNamesMapToId(map<string, pair<string, map<string, string> > >& mapping)
{
  vector<string> groupIdList;
  getGroupIdList(groupIdList);
  for(vector<string>::iterator groupIdIt = groupIdList.begin(); groupIdIt != groupIdList.end(); groupIdIt++) {
    mapping.insert(make_pair(getDisplayName(*groupIdIt), make_pair( *groupIdIt, map<string, string>() ) ) );
    vector<string> groupMemberIdList;
    getGroupMembers(*groupIdIt, groupMemberIdList);
    for(vector<string>::iterator groupMemberIdIt = groupMemberIdList.begin(); groupMemberIdIt != groupMemberIdList.end(); groupMemberIdIt++) {
      mapping[*groupIdIt].second.insert(make_pair(getDisplayName(*groupMemberIdIt), *groupMemberIdIt));
    }
  }
}

void RulHandler::collectWarnings(vector<string>& warnings, bool groupExporter)
{
  vector<string> ruleIdList;
  getRuleIdList(ruleIdList);
  for(vector<string>::iterator it = ruleIdList.begin(); it != ruleIdList.end(); it++) {
    if(getIsEnabled(*it) && (((!groupExporter) && (getGroupType(*it) == _RUL_FALSE)) || ( groupExporter && (getGroupType(*it) == _SUMMARIZED) ) ) ) {
      if( find(warnings.begin(), warnings.end(), *it) == warnings.end()) {
        warnings.push_back(*it);
      }
    }
  }
}

string RulHandler::getEdgeType(const string& edgeName) const
{
  map<string, string>::const_iterator edgeIt = rulData.edges.find(edgeName);
  if(edgeIt != rulData.edges.end()) {
    return edgeIt->second;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_EDGE_NOT_FOUND + edgeName);
  }
}

void RulHandler::setEdgeType(const string& edgeName, const string& edgeType)
{
  rulData.edges[edgeName] = edgeType;
}

void RulHandler::getViewNames(vector<string>& list) const
{
  for(map<string, set<string> >::const_iterator it = rulData.viewEdges.begin(); it != rulData.viewEdges.end(); ++it ) {
    list.push_back(it->first);
  }
}

void RulHandler::getViewNames(set<string>& strset) const
{
  for(map<string, set<string> >::const_iterator it = rulData.viewEdges.begin(); it != rulData.viewEdges.end(); ++it ) {
    strset.insert(it->first);
  }
}

void RulHandler::getViewEdges(const string& viewName, vector<string>& names) const
{
  insert_iterator<vector<string>> insertIt(names, names.end());
  getViewEdges(viewName, insertIt);
}

void RulHandler::getViewEdges(const string& viewName, set<string>& names) const
{
  insert_iterator<set<string>> insertIt(names, names.end());
  getViewEdges(viewName, insertIt);
}

void RulHandler::addView(const string& viewName)
{
  map<string, set<string> >::iterator viewEdgesIt = rulData.viewEdges.find(viewName);
  if(viewEdgesIt == rulData.viewEdges.end()) {
    rulData.viewEdges.insert(make_pair(viewName, set<string>()));
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_VIEW_ALREADY_EXIST + viewName);
  }
}

void RulHandler::deleteView(const string& viewName)
{
  rulData.viewEdges.erase(viewName);
}

void RulHandler::addViewEdge(const string& viewName, const string& edgeName)
{
  map<string, set<string> >::iterator viewEdgesIt = rulData.viewEdges.find(viewName);
  if(viewEdgesIt != rulData.viewEdges.end()) {
    viewEdgesIt->second.insert(edgeName);
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_VIEW_ALREADY_EXIST + viewName);
  }
}

void RulHandler::deleteViewEdge(const string& viewName, const string& edgeName)
{
  map<string, set<string> >::iterator viewEdgesIt = rulData.viewEdges.find(viewName);
  if(viewEdgesIt != rulData.viewEdges.end()) {
    viewEdgesIt->second.erase(edgeName);
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_VIEW_ALREADY_EXIST + viewName);
  }
}

void RulHandler::setAgregatedFormula(const string& ruleId, const string& formula)
{
  setConfSpecData(ruleId, &RulConfiguration::aggregatedFormula, formula);
}

void RulHandler::setAgregatedFormula(const string& ruleId, const string& configuration, const string& formula)
{
  setConfSpecData(ruleId, configuration, &RulConfiguration::aggregatedFormula, formula);
}

string RulHandler::getAgregatedFormula(const string& ruleId) const
{
  return getConfSpecData(ruleId, &RulConfiguration::aggregatedFormula, _empty_string);
}

bool RulHandler::getIsNumericType(const string& ruleId) const
{
  return getConfSpecData(ruleId, &RulConfiguration::numeric, rulUndefined) == rulTrue;
}

void RulHandler::setIsNumericType(const string& ruleId, bool isNumeric)
{
  setConfSpecData(ruleId, &RulConfiguration::numeric, isNumeric ? rulTrue : rulFalse);
}

void RulHandler::setIsNumericType(const string& ruleId, const string& configuration, bool isNumeric)
{
  setConfSpecData(ruleId, configuration, &RulConfiguration::numeric, isNumeric ? rulTrue : rulFalse);
}


void RulHandler::setCalculatedForSet(const string& ruleId, const set<string>& calculatedFor)
{
  setConfSpecData(ruleId, &RulConfiguration::calculated, calculatedFor);
}

void RulHandler::setCalculatedForSet(const string& ruleId, const string& configuration, const set<string>& calculatedFor)
{
  setConfSpecData(ruleId, configuration, &RulConfiguration::calculated, calculatedFor);
}

const set<string>& RulHandler::getCalculatedForSet(const string& ruleId) {
  return getConfSpecData(ruleId, &RulConfiguration::calculated, set<string>());
}

const string& RulHandler::getFileName() const {
  return _filename;
}

template<class T>
void RulHandler::getViewEdges(const string& viewName, insert_iterator<T> insertIt) const
{
  map<string, set<string> >::const_iterator viewIt = rulData.viewEdges.find(viewName);
  if(viewIt != rulData.viewEdges.end()) {
    for(set<string>::const_iterator edgeIt = viewIt->second.begin(); edgeIt != viewIt->second.end(); ++edgeIt) {
      insertIt = *edgeIt;
    }
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_VIEW_NOT_FOUND + viewName);
  }
}

string RulHandler::rulBooleanToString(const RulBoolean& rulBool) const
{
  switch(rulBool) {
  case rulFalse:
    return _RUL_FALSE;
  case rulTrue:
    return _RUL_TRUE;
  case rulUndefined:
    return _RUL_UNDEFINED;
  default:
    return "";
  }
}


template<class T>
void RulHandler::getGroupIdList(insert_iterator<T> insertIt) const
{
  for(map<string, RulMetric>::const_iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    string group = getGroupType(metricIt->first);
    if(group  == _SUMMARIZED || group == _VISUAL) {
      insertIt = metricIt->first;
    }
  }
}


template<class T>
void RulHandler::getRuleIdList(insert_iterator<T> insertIt) const
{
  for(map<string, RulMetric>::const_iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    insertIt = metricIt->first;
  }
}

template<class T>
void RulHandler::getGroupMembers(const string& groupId, insert_iterator<T> insertIt) const
{
  for(map<string, RulMetric>::const_iterator metricIt = rulData.metrics.begin(); metricIt != rulData.metrics.end(); ++metricIt) {
    const RulConfiguration* config = metricIt->second.actualConfig;
    if(config == NULL) {
      throw RulHandlerException("","");
    }
    do {
      for(set<string>::const_iterator groupMemberIt = config->groupMember.begin(); groupMemberIt != config->groupMember.end(); ++groupMemberIt) {
        if(groupId == *groupMemberIt) {
          insertIt = metricIt->first;
        }
      }
      config = getParentConfig(config);
    } while(!_strictMode && config != NULL);
  }
}

template<class T>
void RulHandler::getMetricGroupMembers(const string& ruleId, insert_iterator<T> insertIt ) const
{
  const RulMetric* metric = findMetric(ruleId);
  const RulConfiguration* config = metric->actualConfig;
  if(config == NULL) {
    throw RulHandlerException("","");
  }
  do {
    for(set<string>::const_iterator groupMemberIt = config->groupMember.begin(); groupMemberIt != config->groupMember.end(); ++groupMemberIt) {
      insertIt = string(*groupMemberIt);
    }
    config = getParentConfig(config);
  } while(!_strictMode && config != NULL);
}

const RulHandler::RulMetric* RulHandler::findMetric(const string& metricID) const
{
  map<string, RulMetric>::const_iterator metricIt =  rulData.metrics.find(metricID);
  if(metricIt != rulData.metrics.end()) {
    return &metricIt->second;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_METRIC_NOT_FOUND + metricID);
  }
}

RulHandler::RulMetric* RulHandler::findMetric(const string& metricID)
{
  map<string, RulMetric>::iterator metricIt =  rulData.metrics.find(metricID);
  if(metricIt != rulData.metrics.end()) {
    return &metricIt->second;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_METRIC_NOT_FOUND + metricID);
  }
}

RulHandler::RulConfiguration* RulHandler::findConfiguration(const string& metricID, const string& configuration)
{
  RulMetric* metric = findMetric(metricID);
  map<string, RulConfiguration>::iterator configIt = metric->configs.find(configuration);
  if(configIt != metric->configs.end()) {
    return &configIt->second;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_DOESNOT_EXIT_TWO_MESSAGE( metricID, configuration));
  }
}

RulHandler::RulLang* RulHandler::findLanguage(const string& metricID, const string& configuration, const string& language)
{
  RulConfiguration* config = findConfiguration(metricID, configuration);
  map<string, RulLang>::iterator langIt = config->langs.find(language);
  if(langIt != config->langs.end()) {
    return &langIt->second;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION,CMSG_EX_LANGUAGE_NOT_FOUND_THREE_MESSAGE( metricID, configuration, language));
  }
}


const RulHandler::RulConfiguration* RulHandler::getParentConfig(const RulConfiguration* rulConfig) const
{
  return rulConfig->parentConfig;
}

template<typename T, typename R>
const R& RulHandler::getLangSpecData (const string& ruleId, T key, const R& wrongValue) const
{
  const RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig != NULL && metric->actualConfig->actualLang != NULL) {
    const RulConfiguration* rulConfig = metric->actualConfig;
    const RulConfiguration* lastConfig = metric->actualConfig;
    
    while(rulConfig != NULL) {
      lastConfig = rulConfig;
      if(!_strictMode && rulConfig->actualLang->*key == wrongValue ) {
          rulConfig = getParentConfig(rulConfig);
      } else {
        return rulConfig->actualLang->*key;
      }
    }
    return lastConfig->actualLang->*key;
  } else {
    throw RulHandlerException(COLUMBUS_LOCATION,CMSG_EX_LANGUAGE_NOT_FOUND_THREE_MESSAGE( ruleId, _configuration, _language));
  }
}

template<typename T, typename V>
void RulHandler::setLangSpecData (const string& ruleId, T key, const V& value)
{
  RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig != NULL && metric->actualConfig->actualLang != NULL) {
    metric->actualConfig->actualLang->*key = value;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_OR_LANGUAGE_NOT_FOUND_THREE_MESSAGE(ruleId, _configuration, _language));
  }
}

template<typename T, typename V>
void RulHandler::setLangSpecData (const string& ruleId, const string& configuration, const string& language, T key, const V& value)
{
  RulLang* lang = findLanguage(ruleId, configuration, language);
  lang->*key = value;
}


template<typename T, typename R>
const R& RulHandler::getConfSpecData (const string& ruleId, T key, const R& wrongValue) const
{
  const RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig) {
    const RulConfiguration* rulConfig = metric->actualConfig;
    const RulConfiguration* lastConfig = metric->actualConfig;
    while(rulConfig != NULL) {
      lastConfig = rulConfig;
      if(!_strictMode && rulConfig->*key == wrongValue) {
          rulConfig = getParentConfig(rulConfig);
      } else {
        return rulConfig->*key;
      }
    }
    return lastConfig->*key;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_METRIC_NOT_FOUND_FOR + ruleId);
  }
}

template<typename T, typename V>
void RulHandler::setConfSpecData (const string& ruleId, T key, const V& value)
{
  RulMetric* metric = findMetric(ruleId);
  if(metric->actualConfig) {
    metric->actualConfig->*key = value;
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_DOESNOT_EXIT_TWO_MESSAGE( ruleId, _configuration));
  }
}

template<typename T, typename V>
void RulHandler::setConfSpecData (const string& ruleId, const string& configuration, T key, const V& value)
{
  RulConfiguration* config = findConfiguration(ruleId, configuration);
  config->*key = value;
}

template<typename T, typename R, typename N>
void RulHandler::getConfSpecDataFromMap (const string& ruleId, const N& name, T key, R& retvalue, const string& wrongValue, bool& found ) const
{
  const RulMetric* metric = findMetric(ruleId);
  found = false;
  if(metric->actualConfig != NULL) {
    const RulConfiguration* rulConfig = metric->actualConfig;
    while(rulConfig != NULL) {
      retvalue  = (rulConfig->*key).find(name);
      if(!_strictMode && ((retvalue == (rulConfig->*key).end()) || retvalue->second == wrongValue)) {
          rulConfig = getParentConfig(rulConfig);
      } else {
        found = true;
        break;
      }
    }
  } else {
    throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_METRIC_NOT_FOUND_FOR + ruleId);
  }
}

class RulXmlHandler : public DefaultHandler
{
private:

  enum ReaderState {
    rsNone,
    rsToolDescriptionItem,
    rsEnabled,
    rsNumericType,
    rsVisiable,
    rsGroup,
    rsGroupMember,
    rsOriginalId,
    rsWarning,
    rsWarningText,
    rsDisplayName,
    rsDescription,
    rsHelpText,
    rsSetting,
    rsBaseline,
    rsEdge,
    rsAggregatedFormula,
    rsCalculatedElement
  };

private:
  stack<string> _tagStack;
  RulHandler::RulData& _rulData;
  bool _inToolDescription;
  bool _inViews;
  string _actualConfig;
  RulHandler::RulConfiguration* _actualConfigInMetric;
  string* _actualToolDescription;
  RulHandler::RulMetric* _actualMetric;
  RulHandler::RulLang* _actualLang;
  RulHandler::RulSetting* _actualSetting;
  string _actualBaselineName;
  string _actualEdgeName;
  string _actualViewName;
  string _actualMetricId;
  string _actualContent;
  ReaderState _readerState;
  XMLCh* configNameXMLCh; // _CONFIG_NAME
  XMLCh* toolDescriptionNameCh; //_TOOL_DESCRIPTION_NAME
  XMLTranscoder* transcoder;

protected:

  char* xmlTranscode(const XMLCh* xmlCh)
  {
    XMLSize_t inputSize = XMLString::stringLen(xmlCh);
    XMLByte* buffer = new XMLByte[inputSize * 2 + 1];
    XMLSize_t charsEaten = 0;
    XMLSize_t transformedChars = transcoder->transcodeTo(xmlCh, inputSize, buffer, inputSize *2 , charsEaten, XMLTranscoder::UnRep_Throw);
    buffer[transformedChars] = '\0';
    return reinterpret_cast<char*>(buffer);
  }

  void xmlRelease(char** data)
  {
    delete [] *data;
    *data = NULL;
  }

public:

  RulXmlHandler(RulHandler::RulData& rulData)
    : _tagStack()
    , _rulData(rulData)
    , _inToolDescription(false)
    , _inViews(false)
    , _actualConfigInMetric(NULL)
    , _actualToolDescription(NULL)
    , _actualMetric(NULL)
    , _actualLang(NULL)
    , _actualSetting(NULL)
    , _readerState(rsNone)
    , configNameXMLCh(NULL)
    , toolDescriptionNameCh(NULL)
    , transcoder(NULL)
  {
    configNameXMLCh = XMLString::transcode(_CONFIG_NAME);
    toolDescriptionNameCh = XMLString::transcode(_TOOL_DESCRIPTION_NAME);

    XMLTransService::Codes codes;
    transcoder = XMLPlatformUtils::fgTransService->makeNewTranscoderFor("utf-8", codes, 4096);
  }

  ~RulXmlHandler()
  {
    XMLString::release(&configNameXMLCh);
    XMLString::release(&toolDescriptionNameCh);
    delete transcoder;
  }
  
  RulXmlHandler(const RulXmlHandler& sa);
  RulXmlHandler& operator=(const RulXmlHandler&);
  
  void processConfig(const Attributes &attrs)
  {
    const XMLCh* config = attrs.getValue(configNameXMLCh);
    if(config != NULL) {
      char* actualConfigChar = xmlTranscode(config);
      if(_inToolDescription) {
        _actualConfig = actualConfigChar;
      } else {
        if(_actualMetric != NULL) {
          _actualConfigInMetric = &(_actualMetric->configs[actualConfigChar]);
          
        } else {
          throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIG_METRIC_OR_TOOLDESCRIPTOR);
        }
      }
      xmlRelease(&actualConfigChar);
    } else {
      throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGNAME_MISSING);
    }
  }

  void processToolDescription(const Attributes &attrs)
  {
    if(!_actualConfig.empty()) {
      const XMLCh* descName = attrs.getValue(toolDescriptionNameCh);
      if(descName != NULL) {
        char* descNameChar = xmlTranscode(descName);
        _actualToolDescription =  &( (_rulData.toolDescription[_actualConfig])[descNameChar]);
        _readerState = rsToolDescriptionItem;
        xmlRelease(&descNameChar);
      } else {
        throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOLDESCRITIONITEM_MISSING + _tagStack.top());
      }
    } else {
      throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_CONFIGURATION_EMPTY + _tagStack.top());
    }
  }

  void processConfigurationRedefine(const Attributes &attrs)
  {
    XMLCh* configNameCh = XMLString::transcode(_CCNAME);
    XMLCh* configRedefineCh = XMLString::transcode(_CCREDEFINE);
    const XMLCh* configNameValCh = attrs.getValue(configNameCh);
    const XMLCh* configRedefineValCh = attrs.getValue(configRedefineCh);

    if( (configNameValCh != NULL) && (configRedefineValCh != NULL) ) {
      char* configNameValChar = xmlTranscode(configNameValCh);
      char* configRedefineValChar = xmlTranscode(configRedefineValCh);
      _rulData.redefines[configNameValChar] = configRedefineValChar;
      xmlRelease(&configNameValChar);
      xmlRelease(&configRedefineValChar);
    }

    XMLString::release(&configNameCh);
    XMLString::release(&configRedefineCh);
  }

  void processMetric(const Attributes &attrs)
  {
    XMLCh* metricIdConstCh = XMLString::transcode(_METRIC_ID);
    const XMLCh* metricId = attrs.getValue(metricIdConstCh);
    if(metricId != NULL) {
      char* metricIdChar = xmlTranscode(metricId);
      _actualMetric = &(_rulData.metrics[metricIdChar]);
      _actualMetricId = string (metricIdChar);
      xmlRelease(&metricIdChar);
    } else {
      throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_METRIC_NO_ID);
    }
    XMLString::release(&metricIdConstCh);
  }

  void processLanguage(const Attributes &attrs)
  {
    XMLCh* languageLangCh = XMLString::transcode(_LANGUAGE_LANG);
    const XMLCh* languageCh = attrs.getValue(languageLangCh);
    if(languageCh != NULL) {
      char* languageChar = xmlTranscode(languageCh);
      if(_actualConfigInMetric != NULL) {
        _actualLang = &(_actualConfigInMetric->langs[languageChar]);
      } else {
        throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_LANGUAGE_NOT_IN_CONFIGURATION_TAG);
      }
      xmlRelease(&languageChar);
    } else {
      throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_LANGUAGE_HAS_NOT_LANG_ATTRIBUTE);
    }
    XMLString::release(&languageLangCh);
  }

  void processSetting(const Attributes &attrs)
  {
    XMLCh* settingNameCh = XMLString::transcode(_SETTING_NAME);
    XMLCh* settingEditableCh = XMLString::transcode(_SETTING_EDITABLE);

    const XMLCh* settingName = attrs.getValue(settingNameCh);
    const XMLCh* settingEditable = attrs.getValue(settingEditableCh);

    if(_actualConfigInMetric != NULL) {

      if(settingName != NULL) {
        char* settingNameChar = xmlTranscode(settingName);
        map<string, RulHandler::RulSetting>::iterator settingIt = _actualConfigInMetric->settings.insert(make_pair(settingNameChar, RulHandler::RulSetting())).first;
        _actualSetting = &settingIt->second;
        _readerState = rsSetting;
        xmlRelease(&settingNameChar);

        if( settingEditable != NULL ) {
          char* settingEditableChar = xmlTranscode(settingEditable);
          _actualSetting->editable = (strcmp(settingEditableChar, _RUL_TRUE) == 0)? RulHandler::rulTrue : RulHandler::rulFalse;
          xmlRelease(&settingEditableChar);
        }
      } else {
        throw RulHandlerException("processSetting(const Attributes &attrs)","Setting doesn't have name!");
      }
    } else {
      throw RulHandlerException("processSetting(const Attributes &attrs)","Setting doesn't have configuration!");
    }

    XMLString::release(&settingNameCh);
    XMLString::release(&settingEditableCh);
  }

  void processNamedItem(const Attributes &attrs, const char* nameName, string& actualName, ReaderState rs)
  {
    XMLCh* nameCh = XMLString::transcode(nameName);
    const XMLCh* name = attrs.getValue(nameCh);
    if(name != NULL) {
      char* nameChar = xmlTranscode(name);
      actualName = nameChar;
      xmlRelease(&nameChar);
      _readerState = rs;
    } else {
      throw RulHandlerException( COLUMBUS_LOCATION, CMSG_EX_ITEM_HAS_NOT_NAME_ATTRIBUTE);
    }
    XMLString::release(&nameCh);
  }

  void processBaseline(const Attributes &attrs)
  {
    processNamedItem(attrs, _BASELINE_NAME, _actualBaselineName, rsBaseline);
  }

  void processEdgeItem(const Attributes &attrs)
  {
    if(!_inViews) {
      processNamedItem(attrs, _EDGE_TYPES_NAME, _actualEdgeName, rsEdge);
    } else {
      string edgename = "";
      processNamedItem(attrs, _EDGE_NAME, edgename, rsNone);
      if(!_actualViewName.empty()) {
        (_rulData.viewEdges[_actualViewName]).insert(edgename) ;
      }
    }
  }

  void processView(const Attributes &attrs)
  {
    processNamedItem(attrs, _VIEW_NAME, _actualViewName, rsNone);
  }

  virtual void  startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs)
  {
    char* localnameChar = xmlTranscode(localname);
    _tagStack.push(localnameChar);

    if(strcmp(localnameChar, _TOOL_DESCRIPTION) == 0) {
      _inToolDescription = true;
    } else if (strcmp(localnameChar, _CONFIG) == 0) {
      processConfig(attrs);
    } else if (strcmp(localnameChar, _TOOL_DESCRIPTION_ITEM) == 0) {
      processToolDescription(attrs);
    } else if (strcmp(localnameChar, _CONFIGURATIONS_CONFIG) == 0) {
      processConfigurationRedefine(attrs);
    } else if (strcmp(localnameChar, _METRIC) == 0) {
      processMetric(attrs);
    } else if (strcmp(localnameChar, _ENABLED) == 0) {
      _readerState = rsEnabled;
    } else if (strcmp(localnameChar, _NUMERIC_TYPE) == 0) {
      _readerState = rsNumericType;
    } else if (strcmp(localnameChar, _VISIBLE) == 0 ) {
      _readerState = rsVisiable;
    } else if (strcmp(localnameChar, _GROUP) == 0 ) {
      _readerState = rsGroup;
    } else if (strcmp(localnameChar, _GROUP_MEMBER) == 0 ) {
      _readerState = rsGroupMember;
    } else if (strcmp(localnameChar, _ORIGINAL_ID ) == 0 ) {
      _readerState = rsOriginalId;
    } else if (strcmp(localnameChar, _LANGUAGE) == 0 ) {
      processLanguage(attrs);
    } else if (strcmp(localnameChar, _WARNING) == 0 ) {
      _readerState = rsWarning;
    } else if (strcmp(localnameChar, _WARNING_TEXT) == 0 ) {
      _readerState = rsWarningText;
    } else if (strcmp(localnameChar, _DISPLAY_NAME) == 0 ) {
      _readerState = rsDisplayName;
    } else if (strcmp(localnameChar, _DESCRIPTION) == 0 ) {
      _readerState = rsDescription;
    } else if (strcmp(localnameChar, _HELP_TEXT) == 0 ) {
      _readerState = rsHelpText;
    } else if (strcmp(localnameChar, _SETTING) == 0 ) {
      processSetting(attrs);
    } else if (strcmp(localnameChar, _BASELINE) == 0 ) {
      processBaseline(attrs);
    } else if (strcmp(localnameChar, _EDGE) == 0) {
      processEdgeItem(attrs);
    } else if (strcmp(localnameChar, _VIEWS) == 0) {
      _inViews = true;
    } else if (strcmp(localnameChar, _VIEW) == 0) {
      processView(attrs);
    } else if (strcmp(localnameChar, _AGREGATED_FORMULA) == 0) {
      _readerState = rsAggregatedFormula;
    } else if (strcmp(localnameChar,_ELEMENT) == 0) {
      _readerState = rsCalculatedElement;
    }
    xmlRelease(&localnameChar);
  }

  virtual void  endElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname)
  {
    switch(_readerState) {
      case rsToolDescriptionItem:
        if(_actualToolDescription != NULL) {
          *_actualToolDescription = _actualContent;
        }
        break;
      case rsEnabled:
        if(_actualConfigInMetric != NULL) {
          _actualConfigInMetric->enabled = (_actualContent == _RUL_TRUE) ? RulHandler::rulTrue : RulHandler::rulFalse;
        }
        break;
      case rsNumericType:
        if(_actualConfigInMetric != NULL) {
          _actualConfigInMetric->numeric = (_actualContent == _RUL_TRUE) ? RulHandler::rulTrue : RulHandler::rulFalse;
        }
        break;
      case rsVisiable:
        if(_actualConfigInMetric != NULL) {
          _actualConfigInMetric->visiable = (_actualContent == _RUL_TRUE) ? RulHandler::rulTrue : RulHandler::rulFalse;
        }
        break;
      case rsGroup:
        if(_actualConfigInMetric != NULL) {
          _actualConfigInMetric->group = _actualContent;
        }
        break;
      case rsOriginalId:
        if(_actualConfigInMetric != NULL) {
          _actualConfigInMetric->originalId = _actualContent;
          _rulData.originalIdRuleId[_actualContent] = _actualMetricId;
        }
        break;
      case rsGroupMember:
        if(_actualConfigInMetric != NULL) {
          _actualConfigInMetric->groupMember.insert(_actualContent);
        }
        break;
      case rsWarning:
        if(_actualLang != NULL) {
          _actualLang->warning = (_actualContent == _RUL_TRUE) ? RulHandler::rulTrue : RulHandler::rulFalse;
        }
        break;
      case rsWarningText:
        if(_actualLang != NULL) {
          _actualLang->warningText = _actualContent;
        }
        break;
      case rsDisplayName:
        if(_actualLang != NULL) {
          _actualLang->displayName = _actualContent;
        }
        break;
      case rsDescription:
        if(_actualLang != NULL) {
          _actualLang->description = _actualContent;
        }
        break;
      case rsHelpText:
        if(_actualLang != NULL) {
          _actualLang->helpText = _actualContent;
        }
        break;
      case rsSetting:
        if(_actualSetting != NULL) {
          _actualSetting->text = _actualContent;
        }
        break;
      case rsBaseline:
        if(!_actualBaselineName.empty() && _actualConfigInMetric != NULL) {
          _actualConfigInMetric->baselines.insert(make_pair(_actualBaselineName, _actualContent) );
        }
        break;
      case rsEdge:
        if(!_actualEdgeName.empty()) {
          _rulData.edges.insert(make_pair(_actualEdgeName, _actualContent) );
        }
        break;
      case rsAggregatedFormula:
        if(_actualConfigInMetric != NULL) {
          _actualConfigInMetric->aggregatedFormula = _actualContent;
        }
        break;
      case rsCalculatedElement:
        if (_actualConfigInMetric != NULL) {
          _actualConfigInMetric->calculated.insert(_actualContent);
        }
        break;
      default:
        break;
    };

    char* localnameChar = xmlTranscode(localname);
    _tagStack.pop();

    if(strcmp(localnameChar, _TOOL_DESCRIPTION) == 0) {
      _inToolDescription = false;
    } else if (strcmp(localnameChar, _CONFIG) == 0) {
      _actualConfig.clear();
      _actualConfigInMetric = NULL;
    } else if (strcmp(localnameChar, _TOOL_DESCRIPTION_ITEM) == 0) {
      _actualToolDescription = NULL;
    } else if (strcmp(localnameChar, _METRIC) == 0) {
      _actualMetric = NULL;
    } else if (strcmp(localnameChar, _LANGUAGE) == 0 ) {
      _actualLang = NULL;
    } else if (strcmp(localnameChar, _SETTING) == 0 ) {
      _actualSetting = NULL;
    } else if (strcmp(localnameChar, _BASELINE) == 0 ) {
      _actualBaselineName.clear();
    } else if (strcmp(localnameChar, _EDGE) == 0) {
      _actualEdgeName.clear();
    } else if (strcmp(localnameChar, _VIEWS) == 0) {
      _inViews = false;
    } else if (strcmp(localnameChar, _VIEW) == 0) {
      _actualViewName.clear();
    }

    _actualContent.clear();
    _readerState = rsNone;
    xmlRelease(&localnameChar);
  }

  virtual void  characters (const XMLCh *const chars, const XMLSize_t length)
  {
    if(_readerState == rsNone)
      return;
    char* charsChar = xmlTranscode(chars);
    _actualContent.append(charsChar);
    xmlRelease(&charsChar);
  }
};

void RulHandler::parseXML(const string& filename, const string& encoding)
{
  unique_ptr<SAX2XMLReader> parser(XMLReaderFactory::createXMLReader());
  parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional
  parser->setFeature(XMLUni::fgXercesDynamic, true);
  unique_ptr<DefaultHandler> rulXmlHandler(new RulXmlHandler(rulData));
  parser->setContentHandler(rulXmlHandler.get());
  parser->setErrorHandler(rulXmlHandler.get());

  try {
    LocalFileInputSource source(XMLString::transcode(filename.c_str()));
    if(encoding != "") {
      source.setEncoding(XMLString::transcode(encoding.c_str()));
    }
    parser->parse(source);
  } catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    string stringMessage = message;
    XMLString::release(&message);
    throw RulHandlerException("RulHandler::parseXML",stringMessage);
  } catch (const SAXParseException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    string stringMessage = message;
    XMLString::release(&message);
    throw RulHandlerException("RulHandler::parseXML",stringMessage);
  }
}

string RulHandler::getRuleIdByOriginalId( const string& originalId ) const
{
  map <string,string >::const_iterator it =  rulData.originalIdRuleId.find(originalId);
  if (it == rulData.originalIdRuleId.end()){
     throw RulHandlerException("RulHandler::getRuleIdByOriginalId",CMSG_EX_NONEXIST_OR_ALREADY_EXIST(originalId,originalId));
  }
  return it->second;
}

void RulHandler::setOriginalId( const string& ruleId,const string& originalId )
{
    setConfSpecData(ruleId, &RulConfiguration::originalId,originalId );
    rulData.originalIdRuleId[originalId] = ruleId;
}

} // namespace rul
} // namespace columbus
