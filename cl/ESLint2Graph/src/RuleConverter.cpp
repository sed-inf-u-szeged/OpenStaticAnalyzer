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

#include "../inc/RuleConverter.h"
#include "../inc/messages.h"
#include "../inc/defines.h"

#include <io/inc/CsvIO.h>

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::eslint2graph;



class RuleHandler : public DefaultHandler {
private:

  rul::RulHandler& rulHandler;

  // Variables for RuleViolation xml attribute names. 
  XMLCh* ruleIdXMLCh;
  XMLCh* ruleNameXMLCh;
  XMLCh* ruleAbbreviationXMLCh;
  XMLCh* rulePriorityXMLCh;
  XMLCh* ruleEnabledXMLCh;
  XMLCh* ruleHelpXMLCh;
  
  // Variables for RuleViolationGroup xml attribute names.
  XMLCh* ruleGroupIdXMLCh;
  XMLCh* ruleGroupNameXMLCh;
  XMLCh* ruleGroupDescriptionXMLCh;
  
  //Variables for Parameter xml attribute names.
  XMLCh* paramaterNameXMLCh;
  XMLCh* paramaterValueXMLCh;
  
  string parentRuleViolationGroupId;
  string parentRuleViolationId;

public:
  RuleHandler(rul::RulHandler& _rulHandler):
    DefaultHandler(),
    rulHandler(_rulHandler)
  {
    // Xml attribute names
    ruleIdXMLCh = XMLString::transcode(_RULE_ID);
    ruleNameXMLCh = XMLString::transcode(_RULE_NAME);
    ruleAbbreviationXMLCh = XMLString::transcode(_RULE_ABBREVIATION);
    rulePriorityXMLCh = XMLString::transcode(_RULE_PRIORITY);
    ruleEnabledXMLCh = XMLString::transcode(_RULE_ENABLED);
    ruleHelpXMLCh = XMLString::transcode(_RULE_HELP);

    ruleGroupIdXMLCh = XMLString::transcode(_GROUP_ID);
    ruleGroupNameXMLCh = XMLString::transcode(_GROUP_NAME);
    ruleGroupDescriptionXMLCh = XMLString::transcode(_GROUP_DESCRIPTION);

    paramaterNameXMLCh = XMLString::transcode(_PARAMETER_NAME);
    paramaterValueXMLCh = XMLString::transcode(_PARAMETER_VALUE);
  }

  //release xml attributes
  ~RuleHandler(){
    XMLString::release(&ruleIdXMLCh);
    XMLString::release(&ruleNameXMLCh);
    XMLString::release(&ruleAbbreviationXMLCh);
    XMLString::release(&rulePriorityXMLCh);
    XMLString::release(&ruleEnabledXMLCh);
    XMLString::release(&ruleHelpXMLCh);
    XMLString::release(&ruleGroupIdXMLCh);
    XMLString::release(&ruleGroupNameXMLCh);
    XMLString::release(&ruleGroupDescriptionXMLCh);
    XMLString::release(&paramaterNameXMLCh);
    XMLString::release(&paramaterValueXMLCh);
  }

  virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs){
    char* localnameChar = XMLString::transcode(localname);
    
    if(strcmp(localnameChar, _GROUP)==0)
    {

      const XMLCh* ruleGroupId = attrs.getValue(ruleGroupIdXMLCh);
      const XMLCh* ruleGroupName = attrs.getValue(ruleGroupNameXMLCh);
      const XMLCh* ruleGroupDescription = attrs.getValue(ruleGroupDescriptionXMLCh);
      
      char* ruleGroupIdChar = XMLString::transcode(ruleGroupId);
      char* ruleGroupNameChar = XMLString::transcode(ruleGroupName);
      char* ruleGroupDescriptionChar = XMLString::transcode(ruleGroupDescription);
      

      string groupId = ruleGroupIdChar;
      string groupName = ruleGroupNameChar;
      string groupDescription = ruleGroupDescriptionChar;
      
      rulHandler.defineMetric(groupId);
      rulHandler.createConfiguration(groupId, rulHandler.getConfig());
      rulHandler.setIsEnabled(groupId, true);
      rulHandler.createLanguage(groupId, "eng");
      rulHandler.setHasWarningText(groupId, true);
      rulHandler.setGroupType(groupId, "summarized");
      
      rulHandler.setDisplayName(groupId, groupName);
      rulHandler.setDescription(groupId, groupDescription);
      rulHandler.setHelpText(groupId, groupDescription);
    
      parentRuleViolationGroupId = groupId;

      XMLString::release(&ruleGroupIdChar);
      XMLString::release(&ruleGroupNameChar);
      XMLString::release(&ruleGroupDescriptionChar);
    }
    else if(strcmp(localnameChar, _RULE) == 0) {
      const XMLCh* ruleId = attrs.getValue(ruleIdXMLCh);
      const XMLCh* ruleName = attrs.getValue(ruleNameXMLCh);
      const XMLCh* ruleAbbreviation = attrs.getValue(ruleAbbreviationXMLCh);
      const XMLCh* rulePriority = attrs.getValue(rulePriorityXMLCh);
      const XMLCh* ruleEnabled = attrs.getValue(ruleEnabledXMLCh);
      const XMLCh* ruleHelp= attrs.getValue(ruleHelpXMLCh);
      
      char* ruleIdChar = XMLString::transcode(ruleId);
      char* ruleNameChar = XMLString::transcode(ruleName);
      char* ruleAbbreviationChar = XMLString::transcode(ruleAbbreviation);
      char* rulePriorityChar = XMLString::transcode(rulePriority);
      char* ruleEnabledChar = XMLString::transcode(ruleEnabled);
      char* ruleHelpChar = XMLString::transcode(ruleHelp);
    
      string id = _RULE_PREFIX;
      id+=ruleAbbreviationChar;
      
      parentRuleViolationId = id;
      string originalId = ruleIdChar;
      string name = ruleNameChar;
      string priority = rulePriorityChar;
      string enabled = ruleEnabledChar;
      string help = ruleHelpChar;

      if( id != _RULE_PREFIX ) {

        rulHandler.defineMetric(id);
        rulHandler.createConfiguration(id, rulHandler.getConfig());
        rulHandler.setIsEnabled(id, enabled=="true");
        rulHandler.createLanguage(id, "eng");
        rulHandler.setHasWarningText(id, true);
        rulHandler.setSettingValue(id, "Priority", priority, true);
        rulHandler.setGroupType(id, parentRuleViolationGroupId);
        rulHandler.setOriginalId(id, originalId);
        
        rulHandler.setDisplayName(id, name);
        rulHandler.setDescription(id, help);
        rulHandler.setHelpText(id, help);
        
      } else {

        WriteMsg::write(CMSG_RULE_NO_NAME, name.c_str());

      }

      XMLString::release(&ruleIdChar);
      XMLString::release(&ruleNameChar);
      XMLString::release(&rulePriorityChar);
      XMLString::release(&ruleEnabledChar);
      XMLString::release(&ruleHelpChar);

    }else if(strcmp(localnameChar, _PARAMETER) == 0) {
      
      const XMLCh* parameterName = attrs.getValue(paramaterNameXMLCh);
      const XMLCh* parameterValue = attrs.getValue(paramaterValueXMLCh);
      
      char* parameterNameChar = XMLString::transcode(parameterName);
      char* parameterValueChar = XMLString::transcode(parameterValue);

      string parName = parameterNameChar;
      string parValue = parameterValueChar;

      rulHandler.setSettingValue(parentRuleViolationId, parName, parValue, true);

      XMLString::release(&parameterNameChar);
      XMLString::release(&parameterValueChar);

    }
    XMLString::release(&localnameChar);
  }
};

RuleConverter::RuleConverter(const std::string& rulConfig):
  parser(),
  rulHandler(rulConfig, "eng")
{
  rulHandler.setToolDescription("ID", "ESLint");
}

RuleConverter::~RuleConverter(){
}

void RuleConverter::process(const std::string& errorListFileName){

  RuleHandler ruleHandler(rulHandler);
  parser.parseXML(errorListFileName, &ruleHandler);
}

void RuleConverter::saveRulFile(const std::string& rulFileName){
  rulHandler.saveRul(rulFileName);
}
