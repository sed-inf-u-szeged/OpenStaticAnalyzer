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
using namespace columbus::cppcheck2graph;



class RuleHandler : public DefaultHandler {
private:

  rul::RulHandler& rulHandler;

  // Variables for xml attribute names. 
  XMLCh* ruleIdXMLCh;
  XMLCh* rulePriorityXMLCh;
  XMLCh* ruleWarningXMLCh;
  XMLCh* ruleHelpXMLCh;
  XMLCh* ruleInconclusiveXMLCh;
  XMLCh* resultVersionXMLCh;
  
  map<string, string>& ruleIdMap;
  map<string, string>& ruleNameMap;
  map<string, bool>& ruleEnabled;

public:
  RuleHandler(rul::RulHandler& _rulHandler, map<string, string>& _ruleIdMap, map<string, string>& _ruleNameMap, map<string, bool>& _ruleEnabled):
      DefaultHandler(),
      rulHandler(_rulHandler),
      ruleIdMap(_ruleIdMap),
      ruleNameMap(_ruleNameMap),
      ruleEnabled(_ruleEnabled)
  {
    // Xml attribute names
    ruleIdXMLCh = XMLString::transcode(_RULE_ID);
    rulePriorityXMLCh = XMLString::transcode(_RULE_PRIORITY);
    ruleWarningXMLCh = XMLString::transcode(_RULE_WARNING);
    ruleHelpXMLCh = XMLString::transcode(_RULE_HELP);
    ruleInconclusiveXMLCh = XMLString::transcode(_RULE_INCONCLUSIVE);
    resultVersionXMLCh = XMLString::transcode(_RESULT_VERSION);
  }

  ~RuleHandler(){
    // Xml attribute names
    XMLString::release(&ruleIdXMLCh);
    XMLString::release(&rulePriorityXMLCh);
    XMLString::release(&ruleWarningXMLCh);
    XMLString::release(&ruleHelpXMLCh);
    XMLString::release(&ruleInconclusiveXMLCh);
    XMLString::release(&resultVersionXMLCh);
  }

  virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs){
    char* localnameChar = XMLString::transcode(localname);
    if(strcmp(localnameChar, _RULE) == 0) {
      const XMLCh* ruleId = attrs.getValue(ruleIdXMLCh);
      const XMLCh* rulePriority = attrs.getValue(rulePriorityXMLCh);
      const XMLCh* ruleWarning = attrs.getValue(ruleWarningXMLCh);
      const XMLCh* ruleHelp= attrs.getValue(ruleHelpXMLCh);
      //const XMLCh* ruleInconclusive= attrs.getValue(ruleInconclusiveXMLCh);

      char* ruleIdChar = XMLString::transcode(ruleId);
      char* rulePriorityChar = XMLString::transcode(rulePriority);
      char* ruleWarningChar = XMLString::transcode(ruleWarning);
      char* ruleHelpChar = XMLString::transcode(ruleHelp);
    
      string name = ruleIdChar;
      string priority = rulePriorityChar;
      string warning = ruleWarningChar;
      string help = ruleHelpChar;
    
      if(priority == "error")
        priority = "Blocker";
      else if(priority == "warning")
        priority = "Critical";
      else if(priority == "performance")
        priority = "Major";
      else if(priority == "style")
        priority = "Minor";
      else if(priority == "portability")
        priority = "Minor";
      else if(priority == "information")
        priority = "Info";
      
      string id = _RULE_PREFIX;
      id += ruleIdMap[name];

      if( id != _RULE_PREFIX ) {
        
        /*
        if(ruleInconclusive){
        }
        */

        rulHandler.defineMetric(id);
        rulHandler.createConfiguration(id, rulHandler.getConfig());
        rulHandler.setIsEnabled(id, ruleEnabled[name]);
        rulHandler.createLanguage(id, "eng");
        rulHandler.setHasWarningText(id, true);
        rulHandler.setSettingValue(id, "Priority", priority, true);
        rulHandler.setGroupType(id, "false");
        rulHandler.setOriginalId(id, name);

        string displayName = ruleNameMap[name];//formatDisplayName(name);
        rulHandler.setDisplayName(id, displayName);
        rulHandler.setDescription(id, "");
        rulHandler.setHelpText(id, help);
        //rulHandler.setWarningText(id, warning);
        
      } else {

        WriteMsg::write(CMSG_RULE_NO_NAME, name.c_str());

      }

      XMLString::release(&ruleIdChar);
      XMLString::release(&rulePriorityChar);
      XMLString::release(&ruleWarningChar);
      XMLString::release(&ruleHelpChar);

    }else if(strcmp(localnameChar, _RESULT) == 0) {
      const XMLCh* resultVersion = attrs.getValue(resultVersionXMLCh);
      bool versionOk = false;
      if(resultVersion){
        char* resultVersionChar = XMLString::transcode(resultVersion);

        if(strcmp(resultVersionChar, "2") == 0){
          versionOk = true;
        }

        XMLString::release(&resultVersionChar);
      }
      if(!versionOk){
        WriteMsg::write(CMSG_WRONG_XML_FORMAT_VERSION);
      }
    }
    XMLString::release(&localnameChar);
  }
};




class GroupHandler : public DefaultHandler {
private:
  rul::RulHandler& rulHandler;

  // Variables for xml attribute names. 
  XMLCh* groupIdXMLCh;
  XMLCh* groupNameXMLCh;
  XMLCh* groupDescriptionXMLCh;
  XMLCh* groupHelpXMLCh;
  XMLCh* groupRuleIdXMLCh;
  
  // Data for the current group.
  std::string id;
  
  map<string, string>& nameMap;

public:
  GroupHandler(rul::RulHandler& _rulHandler, map<string, string>& _nameMap):
      DefaultHandler(),
      rulHandler(_rulHandler),
      nameMap(_nameMap)
  {
    // Xml attribute names
    groupIdXMLCh = XMLString::transcode(_GROUP_ID);
    groupNameXMLCh = XMLString::transcode(_GROUP_NAME);
    groupDescriptionXMLCh = XMLString::transcode(_GROUP_DESCRIPTION);
    groupHelpXMLCh = XMLString::transcode(_GROUP_HELP);
    groupRuleIdXMLCh = XMLString::transcode(_GROUP_RULE_ID);
  }

  ~GroupHandler(){
    // Xml attribute names
    XMLString::release(&groupIdXMLCh);
    XMLString::release(&groupNameXMLCh);
    XMLString::release(&groupDescriptionXMLCh);
    XMLString::release(&groupHelpXMLCh);
    XMLString::release(&groupRuleIdXMLCh);
  }

  virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs){
    char* localnameChar = XMLString::transcode(localname);
    if(strcmp(localnameChar, _GROUP) == 0) {
      const XMLCh* groupId = attrs.getValue(groupIdXMLCh);
      const XMLCh* groupName= attrs.getValue(groupNameXMLCh);
      const XMLCh* groupDescription = attrs.getValue(groupDescriptionXMLCh);
      const XMLCh* groupHelp= attrs.getValue(groupHelpXMLCh);

      char* groupIdChar = XMLString::transcode(groupId);
      char* groupNameChar = XMLString::transcode(groupName);
      char* groupDescriptionChar = XMLString::transcode(groupDescription);
      char* groupHelpChar = XMLString::transcode(groupHelp);

      id = groupIdChar;
      string name = groupNameChar;
      string description = groupDescriptionChar;
      string help = groupHelpChar;


      rulHandler.defineMetric(id);
      rulHandler.createConfiguration(id, rulHandler.getConfig());
      rulHandler.setIsEnabled(id, true);
      rulHandler.createLanguage(id, "eng");
      rulHandler.setHasWarningText(id, true);
      rulHandler.setIsVisible(id, true);
      rulHandler.setGroupType(id, "summarized");
      
      
      rulHandler.setDisplayName(id, name);
      rulHandler.setDescription(id, description);
      rulHandler.setHelpText(id, help);
      

      XMLString::release(&groupIdChar);
      XMLString::release(&groupNameChar);
      XMLString::release(&groupDescriptionChar);
      XMLString::release(&groupHelpChar);

    }else if(strcmp(localnameChar, _GROUP_RULE) == 0) {
      const XMLCh* ruleId = attrs.getValue(groupRuleIdXMLCh);

      char* ruleIdChar = XMLString::transcode(ruleId);
      
      string ruleIdStr = ruleIdChar;
      ruleIdStr = _RULE_PREFIX + nameMap[ruleIdStr]; 

      try{
        rulHandler.addMetricGroupMembers(ruleIdStr, id);
      }catch(rul::RulHandlerException &e){
        WriteMsg::write(WriteMsg::mlWarning, "%s\n", e.getMessage().c_str());
      }

      XMLString::release(&ruleIdChar);

    }
  }
};


RuleConverter::RuleConverter(const std::string& rulConfig):
    parser(),
    rulHandler(rulConfig, "eng")
{
  rulHandler.setToolDescription("ID", "Cppcheck");
}

RuleConverter::~RuleConverter(){
}

void RuleConverter::process(const std::string& configFileName, const std::string& errorListFileName, const std::string& errorGroupsFileName){

  io::CsvIO options(configFileName, io::IOBase::omRead);

  vector<string> line;
  options.readLine(line);
  line.clear();

  while(options.readLine(line)){
    string oid = line[0];
    string id = line[1];
    string newname = line[2];
    bool enabled = line[3]=="1";
    
    ruleIdMap.insert(make_pair(oid, id));
    ruleNameMap.insert(make_pair(oid, newname));
    ruleEnabled.insert(make_pair(oid, enabled));

    line.clear();
  }

  RuleHandler ruleHandler(rulHandler, ruleIdMap, ruleNameMap, ruleEnabled);
  parser.parseXML(errorListFileName, &ruleHandler);

  GroupHandler groupHandler(rulHandler, ruleIdMap);
  parser.parseXML(errorGroupsFileName, &groupHandler);
}

void RuleConverter::saveRulFile(const std::string& rulFileName){
  rulHandler.saveRul(rulFileName);
}
