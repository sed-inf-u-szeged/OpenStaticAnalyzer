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


#ifndef RulHandler_H_
#define RulHandler_H_

#include <vector>
#include <map>
#include <set>
#include <list>
#include <Exception.h>
#include <iterator>

namespace columbus {

namespace io {
  class SimpleXmlIO;
}

namespace rul {

class RulHandlerException : public columbus::Exception {
public:
  RulHandlerException(const std::string &location, const std::string &message) : Exception(location, message) {}

  virtual const std::string getClassName() const
  {
    return "columbus::rul::RulHandlerException";
  }
};


class RulHandler {

private:

  enum RulBoolean {
    rulUndefined,
    rulTrue,
    rulFalse
  };

  struct RulLang {
    RulBoolean warning;
    std::string displayName;
    std::string description;
    std::string helpText;
    std::string warningText;
    RulLang()
      : warning (rulUndefined)
      , displayName(_empty_string)
      , description(_empty_string)
      , helpText(_empty_string)
      , warningText(_empty_string)
    {}
  };

  struct RulSetting {
    std::string text;
    RulBoolean editable;
    RulSetting()
      : text(_empty_string)
      , editable(rulUndefined)
    {}
    bool operator==(const std::string& text) const
    {
      return this->text == text;
    }
  };


  struct RulConfiguration {
    RulBoolean enabled;
    RulBoolean visiable;
    std::string group;
    std::string originalId;
    std::string aggregatedFormula;
    RulBoolean numeric;
    std::set<std::string> groupMember;
    std::map<std::string, RulLang> langs;
    std::map<std::string, std::string> baselines;
    std::map<std::string, RulSetting> settings;
    std::set<std::string> calculated;
    RulLang* actualLang;
    RulConfiguration* parentConfig;
    RulConfiguration()
      : enabled(rulUndefined)
      , visiable(rulUndefined)
      , group(_empty_string)
      , originalId(_empty_string)
      , aggregatedFormula(_empty_string)
      , numeric(rulUndefined)
      , groupMember()
      , langs()
      , baselines()
      , settings()
      , actualLang(NULL)
      , parentConfig(NULL)
    {}
    
    RulConfiguration(const RulConfiguration& rc)
      : enabled(rc.enabled)
      , visiable(rc.visiable)
      , group(rc.group)
      , originalId(rc.originalId)
      , aggregatedFormula(rc.aggregatedFormula)
      , numeric(rc.numeric)
      , groupMember(rc.groupMember)
      , langs(rc.langs)
      , baselines(rc.baselines)
      , settings(rc.settings)
      , calculated(rc.calculated)
      , actualLang(rc.actualLang)
      , parentConfig(rc.parentConfig)
    {}
    
    RulConfiguration& operator=(const RulConfiguration& rc)
    {
      enabled = rc.enabled;
      visiable = rc.visiable ;
      group = rc.group;
      aggregatedFormula = rc.aggregatedFormula;
      numeric = rc.numeric;
      groupMember = rc.groupMember;
      langs = rc.langs;
      baselines = rc.baselines;
      settings = rc.settings;
      calculated = rc.calculated;
      actualLang = rc.actualLang;
      parentConfig = rc.parentConfig;
      originalId = rc.originalId;
      return *this;
    }
  };

  struct RulMetric {
    std::map<std::string, RulConfiguration> configs;
    RulConfiguration* actualConfig;
    RulMetric() : configs(), actualConfig(NULL) {}
    RulMetric(const RulMetric& rm)
      : configs(rm.configs)
      , actualConfig(rm.actualConfig)
    {}

    RulMetric& operator=(const RulMetric& rm)
    {
      configs = rm.configs;
      actualConfig = rm.actualConfig;
      return *this;
    }
  };

  struct RulData {
    std::map<std::string, std::map<std::string, std::string> > toolDescription;
    std::map<std::string, RulMetric> metrics;
    std::map<std::string, std::string> redefines;
    std::map<std::string, std::string> originalIdRuleId;
    std::map<std::string, std::string> edges;
    std::map<std::string, std::set<std::string> > viewEdges;
  };

  RulData rulData;

  std::string _configuration;
  std::string _language;
  const std::string _filename;
  bool _strictMode;
  bool _xerces_inited;
  static const std::string _empty_string;
  static int xercesInited;

public:
  RulHandler(const std::string& rulFileName,  const std::string& conf, const std::string& lang, const std::string& encoding = "");
  RulHandler(const std::string& conf,  const std::string& lang);

  void turnOnStrictMode();
  void turnOffStrictMode();
  bool getIsStrictMode() const;
  void createConfiguration(const std::string& ruleId, const std::string& configName);
  void createConfigurationForToolDescription(const std::string& configName);
  void copyMetric(const std::string& fromName, const std::string& toName);
  RulHandler(const RulHandler& handler, bool emptyRulData);
  void copyMetric(const RulHandler& fromRul, const std::string& fromName, const std::string& toName);
  void manuallyCreateIndex();
  void deleteConfiguration(const std::string& config);
  void deleteConfiguration(const std::string& ruleId, const std::string& config);
  void createLanguage(const std::string& ruleId, const std::string& lang);
  void createLanguage(const std::string& ruleId, const std::string& configuration, const std::string& lang);
  void deleteLanguage(const std::string& lang);
  std::string getWarningText(const std::string& ruleId) const;
  void setWarningText(const std::string& ruleId, const std::string& warningText);
  void setWarningText(const std::string& ruleId, const std::string& configuration, const std::string& warningText, const std::string& lang);
  std::string getLineBreakWarningText(const std::string& ruleID, const std::list<std::string>& arg) const;
  std::string getToolDescription(const std::string& field) const;
  void setToolDescription(const std::string& field, const std::string& description) ;
  void setToolDescription(const std::string& field, const std::string& description, const std::string& configuration) ;
  bool getIsDefined(const std::string& ruleId) const;
  void defineMetric(const std::string& ruleId) ;
  void deleteMetric(const std::string& ruleId) ;
  bool getIsEnabled(const std::string& ruleId) const;
  void setIsEnabled(const std::string& ruleId, bool enabled) ;
  void setIsEnabled(const std::string& ruleId, const std::string& configuration, bool enabled) ;
  bool getIsVisible(const std::string& ruleId) const;
  void setIsVisible(const std::string& ruleId, bool visible) ;
  void setIsVisible(const std::string& ruleId, const std::string& configuration, bool visible) ;
  std::string getRuleIdByOriginalId(const std::string& originalId) const;
  std::string getOriginalIdByRuleId(const std::string& ruleId) const;
  void setOriginalId(const std::string& ruleId,const std::string& originalId);
  std::string getHelpText(const std::string& ruleId) const;
  void setHelpText(const std::string& ruleId, const std::string& helpText) ;
  void setHelpText(const std::string& ruleId, const std::string& configuration , const std::string& helpText, const std::string& lang) ;
  bool getHasWarningText(const std::string& ruleId) const;
  void setHasWarningText(const std::string& ruleId,bool hasWarningText) ;
  void setHasWarningText(const std::string& ruleId, const std::string& configuration,bool hasWarningText, const std::string& lang) ;
  std::string getDisplayName(const std::string& ruleId) const;
  void setDisplayName(const std::string& ruleId, const std::string& name) ;
  void setDisplayName(const std::string& ruleId, const std::string& configuration, const std::string& name, const std::string& lang) ;
  std::string getDescription(const std::string& ruleId) const;
  void setDescription(const std::string& ruleId, const std::string& description) ;
  void setDescription(const std::string& ruleId, const std::string& configuration, const std::string& description, const std::string& lang) ;
  std::string getBaselineValue(const std::string& ruleId, const std::string& baselineName) const;
  void setBaselineValue(const std::string& ruleId, const std::string& configuration, const std::string& baselineName, const std::string& value) ;
  void setBaselineValue(const std::string& ruleId, const std::string& baselineName, const std::string& value) ;
  std::string getSettingValue(const std::string& ruleId, const std::string& settingName) const;
  void setSettingValue(const std::string& ruleId, const std::string& configuration, const std::string& settingName, const std::string& value,bool isEditable) ;
  void setSettingValue(const std::string& ruleId, const std::string& settingName, const std::string& value,bool isEditable) ;
  bool getSettingIsEditable(const std::string& ruleId, const std::string& settingName) const;
  std::string getGroupType(const std::string& ruleId) const;
  void setGroupType(const std::string& ruleId, const std::string& groupType);
  void setGroupType(const std::string& ruleId, const std::string& configuration, const std::string& groupType);
  void getMetricGroupMembers(const std::string& ruleId, std::set<std::string>& groupMembers) const;
  void addMetricGroupMembers(const std::string& ruleId, const std::string& groupId) ;
  void addMetricGroupMembers(const std::string& ruleId, const std::string& configuration, const std::string& groupId) ;
  void getGroupMembers(const std::string& groupId, std::set<std::string>& groupMembers) const;
  void getGroupMembers(const std::string& groupId, std::vector<std::string>& groupMembers) const;
  void getMetricConfigurations(const std::string& ruleId, std::vector<std::string>& list) const;
  void getMetricAndConfigurationLanguages(const std::string& ruleId, std::set<std::string>& list) const;
  void getMetricAndConfigurationLanguages(const std::string& ruleId, const std::string& configuration, std::set<std::string>& list) const;
  void getAllConfigurations(std::set<std::string>& list) const;
  std::string getConfigParent(const std::string& config);
  bool hasConfigParent(const std::string& config);
  void setConfigParent(const std::string& config, const std::string& parent) ;
  void deleteConfigParent(const std::string& config);
  void getRuleIdList(std::vector<std::string>& list) const;
  void getRuleIdList(std::set<std::string>& set) const;
  void getGroupIdList(std::vector<std::string>& list);
  void getGroupIdList(std::set<std::string>& list);
  void getMetricSettingsName(const std::string& ruleId, std::set<std::string>& list);
  void saveRul(const std::string& filename) const;
  const std::string& getConfig() const;
  const std::string& getLanguage() const;
  void setConfig(const std::string& configuration);
  void setLanguage(const std::string& language);
  void getExistingAttributes(const std::string& ruleId, std::set<std::string>& attributeSet) const;
  std::string getAttribute(const std::string& ruleId, const std::string& configuration, const std::string& language, const std::string& attributeName) const;
  void setAttribute(const std::string& ruleId, const std::string& configuration, const std::string& language, const std::string& attributeName, const std::string value);
  void getAllLanguages(std::set<std::string>& languages);
  void getMapWarningsToGroups(std::map<std::string, std::string>& mapping);
  void getNamesMapToId(std::map<std::string, std::pair<std::string, std::map<std::string, std::string> > >& mapping);
  void collectWarnings(std::vector<std::string>& warnings, bool groupExporter) ;
  std::string getEdgeType(const std::string& edgeName) const ;
  void setEdgeType(const std::string& edgeName, const std::string& edgeType);
  void getViewNames(std::vector<std::string>& list) const;
  void getViewNames(std::set<std::string>& set) const;
  void getViewEdges(const std::string& viewName, std::vector<std::string>& names) const;
  void getViewEdges(const std::string& viewName, std::set<std::string>& names) const;
  void addView(const std::string& viewName);
  void deleteView(const std::string& viewName);
  void addViewEdge(const std::string& viewName, const std::string& edgeName) ;
  void deleteViewEdge(const std::string& viewName, const std::string& edgeName) ;
  void setAgregatedFormula(const std::string& ruleId, const std::string& formula) ;
  void setAgregatedFormula(const std::string& ruleId, const std::string& configuration, const std::string& formula) ;
  std::string getAgregatedFormula(const std::string& ruleId) const;
  bool getIsNumericType(const std::string& ruleId) const;
  void setIsNumericType(const std::string& ruleId, bool isNumeric) ;
  void setIsNumericType(const std::string& ruleId, const std::string& configuration, bool isNumeric) ;
  void setCalculatedForSet(const std::string& ruleId, const std::string& configuration, const std::set<std::string>& calculatedFor);
  void setCalculatedForSet(const std::string& ruleId, const std::set<std::string>& calculatedFor);
  const std::set<std::string>& getCalculatedForSet(const std::string& ruleId);
  const std::string& getFileName() const;

  virtual ~RulHandler();

protected:

  static void xercesInit();
  static void xercesTerminate();
  void parseXML(const std::string& filename, const std::string& encoding);
  void createIndex();
  void clearIndex();
  const RulMetric* findMetric(const std::string& metricID) const;
  RulMetric* findMetric(const std::string& metricID) ;
  RulConfiguration* findConfiguration(const std::string& metricID, const std::string& configuration);
  RulLang* findLanguage(const std::string& metricID, const std::string& configuration, const std::string& language);
  const RulConfiguration* getParentConfig(const RulConfiguration* rulConfig) const;

  template<typename T, typename R>
  const R& getLangSpecData (const std::string& ruleId, T key, const R& wrongValue) const;

  template<typename T, typename V>
  void setLangSpecData (const std::string& ruleId, T key, const V& value);

  template<typename T, typename V>
  void setLangSpecData (const std::string& ruleId, const std::string& configuration, const std::string& language, T key, const V& value);

  template<typename T, typename V>
  void setConfSpecData (const std::string& ruleId, T key, const V& value);

  template<typename T, typename V>
  void setConfSpecData (const std::string& ruleId, const std::string& configuration, T key, const V& value);

  template<typename T, typename R>
  const R& getConfSpecData (const std::string& ruleId, T key, const R& wrongValue) const;

  template<typename T, typename R, typename N>
  void getConfSpecDataFromMap (const std::string& ruleId, const N& name, T key, R& retvalue, const std::string& wrongValue, bool& found) const;

  template<class T>
  void getMetricGroupMembers(const std::string& ruleId, std::insert_iterator<T> insertIt ) const;

  template<class T>
  void getGroupMembers(const std::string& groupId, std::insert_iterator<T> insertIt) const;

  template<class T>
  void getRuleIdList(std::insert_iterator<T> insertIt) const ;

  template<class T>
  void getGroupIdList(std::insert_iterator<T> insertIt) const ;

  template<class T>
  void getViewEdges(const std::string& viewName, std::insert_iterator<T> insertIt) const;

  void setSettingValue(const std::string& ruleId, const std::string& configName, RulConfiguration* config, const std::string& settingName, const std::string& value,bool isEditable) ;
  std::string rulBooleanToString(const RulBoolean& rulBool) const;
  void writeRulToolDescription(io::SimpleXmlIO& xml ) const;
  void writeRulRedefines(io::SimpleXmlIO& xml ) const;
  void writeRulViews(io::SimpleXmlIO& xml ) const;
  void writeRulEdgeTypes(io::SimpleXmlIO& xml )const ;
  void writeRulMetric(io::SimpleXmlIO& xml )const ;
  void writeRulAttribute(io::SimpleXmlIO& xml, const char* tagName, const RulHandler::RulBoolean& value) const;
  void writeRulAttribute(io::SimpleXmlIO& xml, const char* tagName, const std::string& value) const;
  void writeRulLang(io::SimpleXmlIO& xml, const RulConfiguration& rulConfig )const ;

  friend class RulXmlHandler;
};

} // namespace rul

} // namespace columbus

#endif /* RulHandler_H_ */
