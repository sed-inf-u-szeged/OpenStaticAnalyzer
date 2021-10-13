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


#ifndef _CONTR_PROFILE_HANDLER_H_
#define _CONTR_PROFILE_HANDLER_H_

#include <vector>
#include <map>
#include <set>
#include <list>
#include <Exception.h>

namespace columbus {

namespace controller {
  
class ProfileHandlerException : public columbus::Exception {
  public:
  ProfileHandlerException(const std::string &location, const std::string &message)
    : Exception(location, message)
  {
  }

  virtual const std::string getClassName() const {
    return "columbus::controller::ProfileHandlerException";
  }
};


class ProfileHandler {
public:

  struct UDMConfig {
    std::string description;
    std::string displayName;
    std::string groupMember;
    std::string helptext;
    std::string formula;
    std::string type;
    std::set<std::string> calculatedFor;
    UDMConfig() : description(), displayName(), groupMember(), helptext(), formula(), type(), calculatedFor() {}
    UDMConfig(const UDMConfig& u) : description(u.description), displayName(u.displayName), groupMember(u.groupMember), helptext(u.helptext), formula(u.formula), type(u.type), calculatedFor(u.calculatedFor) {}
  };
  
private:
  
  struct Threshold {
    std::string metricId;
    std::string relation;
    std::string value;
    std::string entity;
    bool enabled;
    Threshold() : metricId(_empty_string), relation(_empty_string), value(_empty_string), entity(_empty_string) {}
  };

  struct ToolSettings {
    bool enabled;
    std::map<std::string, Threshold> metricTresholds;
    std::map<std::string, std::map<std::string, UDMConfig>> udmetrics;
    std::map<std::string, std::vector<std::string>> lim2patternsParams;
    ToolSettings() : metricTresholds(), udmetrics(), lim2patternsParams(){}
  };

  struct RuleSettings {
    bool enabled;
    std::string priority;
    RuleSettings() : priority(_empty_string) {}
  };

  struct ProfileData {
    std::map<std::string, RuleSettings> ruleSettings;
    std::map<std::string, ToolSettings> toolSettings;
    ProfileData() : ruleSettings(), toolSettings() {}
  };

  ProfileData profileData;
  const std::string _filename;
  static const std::string _empty_string;
  static const std::set<std::string> standardGroupNames;
  static const std::set<std::string> standardConfigurations;

public:
  
  ProfileHandler();

  ProfileHandler(const std::string& profileFileName);
  ProfileHandler(const ProfileHandler& profile);
  
  virtual ~ProfileHandler();
  
  /**
  * \brief Get is tool settings specified
  * \param toolName [in] the name of the tool
  * \return true if tool settings specified
  */
  bool getIsToolSettings(const std::string& toolName) const;

  /**
  * \brief Get is tool enabled
  * \param toolName [in] the name of the tool
  * \return true if tool enabled
  * \throw ProfileHandlerException if tool settings not specified
  */
  bool getIsToolEnabled(const std::string& toolName) const;
  
  /**
  * \brief Get the list of the threshold identifiers 
  * \param toolName [in] the name of the tool
  * \return the list of the identifiers
  * \throw ProfileHandlerException if tool settings not specified
  */
  std::list<std::pair<std::string, std::string> > getThresholdIds(const std::string& toolName) const;
  
  /**
  * \brief Get is threshold exists 
  * \param toolName [in] the name of the tool
  * \param metricId [in] metric id
  * \param entity [in] entity
  * \return true if threshold exists
  * \throw ProfileHandlerException if tool settings not specified
  */
  bool getIsThreshold(const std::string& toolName, const std::string& metricId, const std::string& entity) const;

  /**
  * \brief Get is threshold enabled 
  * \param toolName [in] the name of the tool
  * \param metricId [in] metric id
  * \param entity [in] entity
  * \return true if threshold enabled
  * \throw ProfileHandlerException if tool settings not specified
  * \throw ProfileHandlerException if threshold not exists
  */
  bool getIsThresholdEnabled(const std::string& toolName, const std::string& metricId, const std::string& entity) const;

  /**
  * \brief Get threshold relation 
  * \param toolName [in] the name of the tool
  * \param metricId [in] metric id
  * \param entity [in] entity
  * \return threshold relation
  * \throw ProfileHandlerException if tool settings not specified
  * \throw ProfileHandlerException if threshold not exists
  */
  std::string getThresholdRelation(const std::string& toolName, const std::string& metricId, const std::string& entity) const;

  /**
  * \brief Get threshold value 
  * \param toolName [in] the name of the tool
  * \param metricId [in] metric id
  * \param entity [in] entity
  * \return threshold value
  * \throw ProfileHandlerException if tool settings not specified
  * \throw ProfileHandlerException if threshold not exists
  */
  std::string getThresholdValue(const std::string& toolName, const std::string& metricId, const std::string& entity) const;

  /**
  * \brief Get is rule settings specified
  * \param ruleId [in] the id of the rule
  * \return true if rule settings specified
  */
  bool getIsRuleSettings(const std::string& ruleId) const;

  /**
  * \brief Get is rule enabled
  * \param ruleId [in] the id of the rule
  * \return true if rule enabled
  * \throw ProfileHandlerException if rule settings not specified
  */
  bool getIsRuleEnabled(const std::string& ruleId) const;
  
  /**
  * \brief Get is rule has priority specified
  * \param ruleId [in] the id of the rule
  * \return true if rule has priority specified
  * \throw ProfileHandlerException if rule settings not specified
  */
  bool getIsRulePriority(const std::string& ruleId) const;

  /**
  * \brief Get rule priority specified
  * \param ruleId [in] the id of the rule
  * \return rule priority
  * \throw ProfileHandlerException if rule settings not specified
  */
  std::string getRulePriority(const std::string& ruleId) const;

  /**
  * \brief Get all the user defined metrics' id
  * \return All the udms, empty list if there is no udm defined
  * \throw ProfileHandlerException if UDM tool is not found
  */
  std::list<std::string> getUDMIDs() const;

  /**
  * \brief Get a user defined metric's configuration
  * \param udmID [in] the udm's id
  * \return All the udm's configuration, empty list, if udm is not found
  * \throw ProfileHandlerException if UDM tool is not found, or if udm is not found
  */
  std::list<std::string> getUDMConfigs(const std::string& udmID) const;

  /**
  * \brief Get all of the user defined metric's attributes
  * \param udmID [in] the udm's id
  * \param configuration [in] the attributes's configuration
  * \return UDMConfig with all the attributes in it, if configuration does not found the "Default" configuration's attributes
  * \throw ProfileHandlerException if UDM tool is not found, or if udm is not found, or if neither 'configuration' nor 'Default' configuration are not found
  */
  UDMConfig getUDMAttributes(const std::string& udmID, const std::string& configuration) const;


  /**
  * \brief Get LIM2Patterns tool parameters
  * \param toolName [in] name of the tool
  * \return mapped parameters
  * \throw ProfileHandlerException when not a single parameter was set
  */
  std::map<std::string, std::string> getLIM2PatternsAttributes(const std::string &toolName) const;

  /**
  * \brief Get all of the user defined metric's GroupMember attribute
  * \return A list with all the attributes in it
  * \throw ProfileHandlerException if UDM tool is not found
  */
  std::set<std::string> getUDMGroupMembers(const std::string& configuration) const;

  void parseXML(const std::string& filename);
  
  friend class ProfileXmlHandler;
};


}

}

#endif /* _CONTR_PROFILE_HANDLER_H_ */
