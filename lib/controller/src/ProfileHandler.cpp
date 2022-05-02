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


#include "../inc/ProfileHandler.h"
#include "../inc/messages.h"
#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <io/inc/SimpleXmlIO.h>

#include <stack>

using namespace std;
using namespace common;
using namespace columbus;

#define _PROFILE_TRUE               "true"
#define _PROFILE_FALSE              "false"

#define _PROFILE                    "analyzer-profile"
#define _TOOL_SETTINGS              "tool-options"
#define _TOOL                       "tool"
#define _TOOL_NAME                  "name"
#define _TOOL_ENABLED               "enabled"
#define _THRESHOLDS                 "metric-thresholds"
#define _THRESHOLD                  "threshold"
#define _THRESHOLD_METRIC_ID        "metric-id"
#define _THRESHOLD_RELATION         "relation"
#define _THRESHOLD_VALUE            "value"
#define _THRESHOLD_ENTITY           "entity"
#define _RULE_SETTINGS              "rule-options"
#define _RULE                       "rule"
#define _RULE_ID                    "id"
#define _RULE_PRIORITY              "priority"
#define _RULE_ENABLED               "enabled"
#define _UDM                        "udm"
#define _UDM_ID                     "id"
#define _UDM_CONFIG                 "configuration"
#define _UDM_CONFIGNAME             "name"
#define _UDM_DESC                   "description"
#define _UDM_DISP                   "display-name"
#define _UDM_GROUP                  "group-member"
#define _UDM_HELPTXT                "help-text"
#define _UDM_FORMULA                "formula"
#define _UDM_TYPE                   "type"
#define _UDM_CALCFOR                "calculated-for"
#define _L2P_WHITELIST              "whitelist"
#define _L2P_BLACKLIST              "blacklist"
#define _L2P_PATTERNS               "pattern_directories"
#define _L2P_ITEM                   "item"


#define _PROFILE_EMPTY_STRING       "~~@PROFILE_EMPTY_STRING@~~"

#define _THRESHOLD_DISABLED_VALUE   "none"

#define THRESHOLD_ID(metricId, entity) (metricId + "~" + entity)

namespace columbus { namespace controller {
  
  const string ProfileHandler::_empty_string = _PROFILE_EMPTY_STRING;
  const set<string> ProfileHandler::standardConfigurations = { "Default", "cpp", "csharp", "java", "javascript", "python", "rpg" };
  const set<string> ProfileHandler::standardGroupNames = { "Cohesion", "Complexity", "Coupling", "Documentation", "Inheritance", "Size", "UserDefinedMetrics", "LIM2Patterns" };

  ProfileHandler::ProfileHandler(): profileData(), _filename("")
  {
  }

  ProfileHandler::ProfileHandler(const string& filename): profileData(), _filename(filename)
  {
    parseXML(filename);
  }

  ProfileHandler::ProfileHandler(const ProfileHandler& handler): profileData(), _filename("")
  {
    profileData = handler.profileData;
  }

  ProfileHandler::~ProfileHandler()
  {
  }
  
  bool ProfileHandler::getIsToolSettings(const string& toolName) const
  {
    map<string, ToolSettings>::const_iterator it =  profileData.toolSettings.find(toolName);
    return it != profileData.toolSettings.end();
  }

  bool ProfileHandler::getIsToolEnabled(const string& toolName) const
  {
    map<string, ToolSettings>::const_iterator it =  profileData.toolSettings.find(toolName);
    if(it != profileData.toolSettings.end())
      return it->second.enabled;
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_SETTINGS_NOT_FOUND + toolName);
  }

  list<pair<string, string> > ProfileHandler::getThresholdIds(const string& toolName) const
  {
    map<string, ToolSettings>::const_iterator it =  profileData.toolSettings.find(toolName);
    if (it != profileData.toolSettings.end())
    {
      list<pair<string, string> > ret;
      for(map<string, Threshold>::const_iterator thrIt = it->second.metricTresholds.begin(); thrIt != it->second.metricTresholds.end(); ++thrIt)
        ret.push_back(make_pair(thrIt->second.metricId, thrIt->second.entity));
      return ret;
    }
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_SETTINGS_NOT_FOUND + toolName);
  }
  
  bool ProfileHandler::getIsThreshold(const string& toolName, const string& metricId, const string& entity) const
  {
    map<string, ToolSettings>::const_iterator it =  profileData.toolSettings.find(toolName);
    if(it != profileData.toolSettings.end())
    {
      map<string, Threshold>::const_iterator thrIt = it->second.metricTresholds.find(THRESHOLD_ID(metricId, entity));
      return thrIt != it->second.metricTresholds.end();
    }
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_SETTINGS_NOT_FOUND + toolName);
  }

  bool ProfileHandler::getIsThresholdEnabled(const string& toolName, const string& metricId, const string& entity) const
  {
    map<string, ToolSettings>::const_iterator it =  profileData.toolSettings.find(toolName);
    if (it != profileData.toolSettings.end())
    {
      map<string, Threshold>::const_iterator thrIt = it->second.metricTresholds.find(THRESHOLD_ID(metricId, entity));
      if(thrIt != it->second.metricTresholds.end())
        return thrIt->second.enabled;
      else
        throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_THRESHOLD_NOT_FOUND +THRESHOLD_ID(metricId, entity));
    }
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_SETTINGS_NOT_FOUND + toolName);
  }

  string ProfileHandler::getThresholdRelation(const string& toolName, const string& metricId, const string& entity) const
  {
    map<string, ToolSettings>::const_iterator it =  profileData.toolSettings.find(toolName);
    if(it != profileData.toolSettings.end())
    {
      map<string, Threshold>::const_iterator thrIt = it->second.metricTresholds.find(THRESHOLD_ID(metricId, entity));
      if(thrIt != it->second.metricTresholds.end())
        return thrIt->second.relation;
      else
        throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_THRESHOLD_NOT_FOUND + THRESHOLD_ID(metricId, entity));
    }
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_SETTINGS_NOT_FOUND + toolName);
  }

  string ProfileHandler::getThresholdValue(const string& toolName, const string& metricId, const string& entity) const
  {
    map<string, ToolSettings>::const_iterator it =  profileData.toolSettings.find(toolName);
    if(it != profileData.toolSettings.end())
    {
      map<string, Threshold>::const_iterator thrIt = it->second.metricTresholds.find(THRESHOLD_ID(metricId, entity));
      if(thrIt != it->second.metricTresholds.end())
        return thrIt->second.value;
      else
        throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_THRESHOLD_NOT_FOUND + THRESHOLD_ID(metricId, entity));
    }
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_SETTINGS_NOT_FOUND + toolName);
  }
  
  bool ProfileHandler::getIsRuleSettings(const string& ruleId) const
  {
    map<string, RuleSettings>::const_iterator it =  profileData.ruleSettings.find(ruleId);
    return it != profileData.ruleSettings.end();
  }

  bool ProfileHandler::getIsRuleEnabled(const string& ruleId) const
  {
    map<string, RuleSettings>::const_iterator it =  profileData.ruleSettings.find(ruleId);
    if(it != profileData.ruleSettings.end())
      return it->second.enabled;
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_RULE_SETTINGS_NOT_FOUND + ruleId);
  }
  
  bool ProfileHandler::getIsRulePriority(const string& ruleId) const
  {
    map<string, RuleSettings>::const_iterator it =  profileData.ruleSettings.find(ruleId);
    if(it != profileData.ruleSettings.end())
      return it->second.priority != _empty_string;
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_RULE_SETTINGS_NOT_FOUND + ruleId);
  }

  string ProfileHandler::getRulePriority(const string& ruleId) const
  {
    map<string, RuleSettings>::const_iterator it =  profileData.ruleSettings.find(ruleId);
    if(it != profileData.ruleSettings.end())
      return it->second.priority;
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_RULE_SETTINGS_NOT_FOUND + ruleId);
  }

  list<string> ProfileHandler::getUDMIDs() const
  {
    list<string> temp;
    map<string, ToolSettings>::const_iterator tool = profileData.toolSettings.find("UDM");
    if( tool != profileData.toolSettings.end()){
        map<string, map<string, UDMConfig>>::const_iterator it = tool->second.udmetrics.begin();
        for (; it != tool->second.udmetrics.end(); ++it)
          temp.push_back(it->first);
        return temp;
    }
    else
      throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_UDM_TOOL_MISSING);
  }

  list<string> ProfileHandler::getUDMConfigs(const string& udmID) const 
  {
    list<string> temp;
    map<string, ToolSettings>::const_iterator tool = profileData.toolSettings.find("UDM");
    if (tool != profileData.toolSettings.end()) {
      map<string, map<string, UDMConfig>>::const_iterator udm = tool->second.udmetrics.find(udmID);
      if(udm != tool->second.udmetrics.end()){
        map<string, UDMConfig> configs = udm->second;
        map<string, UDMConfig>::const_iterator it = configs.begin();
        for (; it != configs.end(); ++it)
          temp.push_back(it->first);
        return temp;
      }
      else
        throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_WRONG_ID);
    }
    else
      throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_TOOL_MISSING);
  };

  ProfileHandler::UDMConfig ProfileHandler::getUDMAttributes(const string& udmID, const string& configuration) const {
    UDMConfig attributes;
    map<string, ToolSettings>::const_iterator tool = profileData.toolSettings.find("UDM");
    if (tool != profileData.toolSettings.end()) {
      map<string, map<string, UDMConfig>>::const_iterator udm = tool->second.udmetrics.find(udmID);
      if (udm != tool->second.udmetrics.end()) {
        map<string, UDMConfig>::const_iterator conf = udm->second.find(configuration);
        if (conf != udm->second.end())
          return conf->second;
        else {
          conf = udm->second.find("Default");
          if (conf != udm->second.end())
            return conf->second;
          else
            throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_NO_DEFAULT_CONFIG);
        }
      }
      else
        throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_WRONG_ID);
    }
    else
      throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_TOOL_MISSING);
  }

  std::map<std::string, std::string> ProfileHandler::getLIM2PatternsAttributes(const std::string &toolName) const
  {
      std::map<std::string, std::string> ret;
      map<string, ToolSettings>::const_iterator it = profileData.toolSettings.find(toolName);
      if (it != profileData.toolSettings.end())
      {
          for (auto &entry : it->second.lim2patternsParams) {
              string concat;
              for (size_t i = 0; i < entry.second.size(); i++) {
                  concat += entry.second[i];
                  if (i + 1 < entry.second.size()) concat += ",";
              }
              ret.emplace(entry.first, concat);
          }
          return ret;
      }
      else 
      {
          throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_L2P_SETTINGS_NOT_FOUND + toolName);
      }
  }

  class ProfileXmlHandler : public io::SimpleXmlIO::XmlHandler {

  private:

    enum ReaderState {
      rsNone
    };

  private:
    stack<string> _tagStack;
    ProfileHandler::ToolSettings* _actualTool = nullptr;
    ProfileHandler::ProfileData& _profileData;
    string _actualUDM;
    string _actualL2P;
    string _actualUDMConfig;

  public:

    ProfileXmlHandler(ProfileHandler::ProfileData& profileData)
      : XmlHandler()
      , _tagStack()
      , _profileData(profileData)
      , _actualUDM()
      , _actualUDMConfig()
    {
    }

    ~ProfileXmlHandler()
    {
    }
  
    ProfileXmlHandler(const ProfileXmlHandler& sa) = delete;
    ProfileXmlHandler& operator=(const ProfileXmlHandler&) = delete;
  
    void processToolSettings(const AttributeList &attrs)
    {
      AttributeList::const_iterator attrIt = attrs.begin();
      string name;
      string enabled;

      while(attrIt != attrs.end())
      {
        if (attrIt->first == _TOOL_NAME)
          name = attrIt->second;
        else if(attrIt->first == _TOOL_ENABLED)
          enabled = attrIt->second;
        ++attrIt;
      }

      if(name.empty())
        throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_NAME_MISSING);

      if(enabled.empty())
        throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_TOOL_ENABLED_MISSING);

      map<string, ProfileHandler::ToolSettings>::iterator toolSettings = _profileData.toolSettings.insert(make_pair(name,ProfileHandler::ToolSettings())).first;
      _actualTool = &(toolSettings->second);

      toolSettings->second.enabled = (enabled == _PROFILE_TRUE);
    }

    void processMetricThershold(const AttributeList &attrs)
    {
      if( _actualTool != NULL )
      {
        AttributeList::const_iterator attrIt = attrs.begin();

        string metricId;
        string relation;
        string value;
        string entity;

        while(attrIt != attrs.end())
        {
          if(attrIt->first == _THRESHOLD_METRIC_ID)
            metricId = attrIt->second;
          else if(attrIt->first == _THRESHOLD_RELATION)
            relation = attrIt->second;
          else if(attrIt->first == _THRESHOLD_VALUE)
            value = attrIt->second;
          else if(attrIt->first == _THRESHOLD_ENTITY)
            entity = attrIt->second;

          ++attrIt;
        }

        if(metricId.empty())
          throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_THRESHOLD_METRIC_ID_MISSING);

        if(relation.empty())
          throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_THRESHOLD_RELATION_MISSING);

        if(value.empty())
          throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_THRESHOLD_VALUE_MISSING);

        if(entity.empty())
          throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_THRESHOLD_ENTITY_MISSING);

        vector<string> entities;
        common::split(entity, entities, ',');
        for (const auto& e : entities)
        {
          map<string, ProfileHandler::Threshold>::iterator threshold = _actualTool->metricTresholds.insert(make_pair(THRESHOLD_ID(metricId, e), ProfileHandler::Threshold())).first;
          threshold->second.metricId = metricId;
          threshold->second.relation = relation;
          threshold->second.value = value;
          threshold->second.entity = e;
          threshold->second.enabled = (value != _THRESHOLD_DISABLED_VALUE);
        }
      }
      else
        throw ProfileHandlerException(COLUMBUS_LOCATION, "Threshold doesn't have tool!");
    }

    void processRuleSettings(const AttributeList &attrs)
    {
      AttributeList::const_iterator attrIt = attrs.begin();

      string id;
      string enabled;
      string priority;

      while(attrIt != attrs.end())
      {
        if(attrIt->first == _RULE_ID)
          id = attrIt->second;
        else if(attrIt->first == _RULE_ENABLED)
          enabled = attrIt->second;
        else if(attrIt->first == _RULE_PRIORITY)
          priority = attrIt->second;

        ++attrIt;
      }

      if(id.empty())
        throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_RULE_ID_MISSING);

      if(enabled.empty())
        throw ProfileHandlerException( COLUMBUS_LOCATION, CMSG_EX_RULE_ENABLED_MISSING);

      map<string, ProfileHandler::RuleSettings>::iterator ruleSettings = _profileData.ruleSettings.insert(make_pair(id, ProfileHandler::RuleSettings())).first;
      ruleSettings->second.enabled = (enabled == _PROFILE_TRUE);
      if(!priority.empty())
        ruleSettings->second.priority = priority;
    }

    void processUDM(const AttributeList &attrs) {
      if (_actualTool != NULL)
      {
        AttributeList::const_iterator attrIt = attrs.begin();

        string id;

        while (attrIt != attrs.end())
        {
          if (attrIt->first == _UDM_ID)
            id = attrIt->second;

          ++attrIt;
        }

        if (id.empty())
          throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_ID_MISSING);

        _actualTool->udmetrics.insert(make_pair(id, map<string, ProfileHandler::UDMConfig>()));
        _actualUDM = id;
      }
      else
        throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_TOOL_MISSING);
    }

    void processUDMConfig(const AttributeList &attrs) {
      if (_actualTool != NULL && !_actualUDM.empty())
      {
        AttributeList::const_iterator attrIt = attrs.begin();

        string name;

        while (attrIt != attrs.end())
        {
          if (attrIt->first == _UDM_CONFIGNAME)
            name = attrIt->second;

          ++attrIt;
        }

        if (name.empty())
          throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_CONFIG_NAME_MISSING);
        else if (ProfileHandler::standardConfigurations.find(name) == ProfileHandler::standardConfigurations.end())
          throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_WRONG_CONFIG_NAME);

        map<string, map<string, ProfileHandler::UDMConfig>>::iterator it = _actualTool->udmetrics.find(_actualUDM);
        it->second.insert(make_pair(name, ProfileHandler::UDMConfig()));
        _actualUDMConfig = name;
      }
      else
        throw ProfileHandlerException(COLUMBUS_LOCATION, CMSG_EX_UDM_TOOL_MISSING);
    }

    void actualLIM2PatternsParam(const AttributeList &attrs, const string &name) {
        if (_actualTool != NULL) {
            // ignore attribute list, there are no attributes to be processed
            _actualL2P = name;
        }
    }

    void beginTag(const string& name, const AttributeList& list)
    {
      _tagStack.push(name);

      if (name == _RULE)
        processRuleSettings(list);
      else if (name == _TOOL)
        processToolSettings(list);
      else if (name == _THRESHOLD)
        processMetricThershold(list);
      else if (name == _UDM)
        processUDM(list);
      else if (name == _UDM_CONFIG)
        processUDMConfig(list);
      else if (name == _L2P_WHITELIST)
        actualLIM2PatternsParam(list, _L2P_WHITELIST);
      else if (name == _L2P_BLACKLIST)
        actualLIM2PatternsParam(list, _L2P_BLACKLIST);
      else if (name == _L2P_PATTERNS)
        actualLIM2PatternsParam(list, _L2P_PATTERNS);

    }

    void endTag(const string& name)
    {
      _tagStack.pop();
      if (name == _TOOL)
        _actualTool = NULL;
      else if (name == _UDM_CONFIG)
        _actualUDMConfig = "";
      else if (name == _UDM)
        _actualUDM = "";
      else if (name == _L2P_WHITELIST || name == _L2P_BLACKLIST || name == _L2P_PATTERNS)
        _actualL2P = "";
    }

    void content(const string& content) {
      if (_actualTool != NULL && !_actualUDM.empty() && !_actualUDMConfig.empty()) {
        map<string, map<string, ProfileHandler::UDMConfig>>::iterator it = _actualTool->udmetrics.find(_actualUDM);
        if ( it != _actualTool->udmetrics.end()) {
          map<string, ProfileHandler::UDMConfig>::iterator lastUDM = it->second.find(_actualUDMConfig);
          if ( lastUDM != it->second.end() ) {
            string top = _tagStack.top();
            if (top == _UDM_DESC)
              lastUDM->second.description = content;
            else if (top == _UDM_DISP)
              lastUDM->second.displayName = content;
            else if (top == _UDM_GROUP) {
              WriteMsg::write(WriteMsg::mlWarning, CMSG_WARNING_GROUP_NOT_SUPPORTED);
            }
            else if (top == _UDM_HELPTXT)
              lastUDM->second.helptext = content;
            else if (top == _UDM_FORMULA)
              lastUDM->second.formula = content;
            else if (top == _UDM_TYPE)
              lastUDM->second.type = content;
            else if (top == _UDM_CALCFOR)
              lastUDM->second.calculatedFor.insert(content);

          }
        }
      }
      if (_actualTool != NULL && !_actualL2P.empty()) {
        string top = _tagStack.top();
        // ignore empty content (ascii 10)
        if (content[0] == 10) return;
        if (top == _L2P_WHITELIST || (top == _L2P_ITEM && _actualL2P == _L2P_WHITELIST)) {
            _actualTool->lim2patternsParams[_L2P_WHITELIST].emplace_back(content);
        }
        if (top == _L2P_BLACKLIST || (top == _L2P_ITEM && _actualL2P == _L2P_BLACKLIST)) {
            _actualTool->lim2patternsParams[_L2P_BLACKLIST].emplace_back(content);
        }
        if (top == _L2P_PATTERNS || (top == _L2P_ITEM && _actualL2P == _L2P_PATTERNS)) {
            _actualTool->lim2patternsParams[_L2P_PATTERNS].emplace_back(content);
        }
      }
    }

  }; // ProfileXmlHandler


  void ProfileHandler::parseXML(const string& filename)
  {
    try {
      ProfileXmlHandler profileXmlHandler(profileData);
      io::loadXml(filename, profileXmlHandler);
    }
    catch (const IOException& toCatch)
    {
      throw ProfileHandlerException("ProfileHandle::parseXML", toCatch.getMessage());
    }
  }

} // namespace controller
} // namespace columbus
