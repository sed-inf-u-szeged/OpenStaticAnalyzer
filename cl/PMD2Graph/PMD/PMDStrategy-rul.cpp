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

#include <string>
#include <fstream>
#include <set>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif
#include "PMDStrategy.h"
#include <rul/inc/RulHandler.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include "../messages.h"
#include <map>
#include <boost/regex.hpp>
#include <boost/bimap.hpp>

using namespace std;
using namespace columbus;
using namespace common;
XERCES_CPP_NAMESPACE_USE

static const string RULE_PREFIX = "PMD_";

static std::string toUTF8String(const XMLCh* ch) {
  return (char*)TranscodeToStr(ch, "UTF-8").str();
}

struct PMDRule {
  PMDRule()
    : id(), name(), enabled(), priority(), ruleId() {}
  PMDRule(string id, string name, string enabled, string priority)
    : id(id), name(name), enabled(enabled), priority(priority), ruleId(RULE_PREFIX + id) {}
  ~PMDRule() {}

  string id;
  string name;
  string enabled;
  string priority;
  string ruleId; // prefix + id
};

typedef boost::bimap<string, string> RuleId2NameMap;
static RuleId2NameMap ruleIdMap; // rule id (without prefix) <-> original rule name
static map<string, PMDRule> pmdRules; // original rule name -> opts

void PMDStrategy::makeRul(File_Names& file_names, std::string& rul, std::string& rulConfig, std::string& rul_option_filename){
  rul::RulHandler rh(rulConfig, "eng");

  setConstantData(rh);

  ruleIdMap.clear();
  pmdRules.clear();

  // load config file
  if (!rul_option_filename.empty()) {
    ifstream input(rul_option_filename.c_str());
    if (input.is_open()) {
      string line;
      bool first = true;
      while (input.good()) {
        getline(input, line);
        if (first) {
          first = false;
          continue; // skip header
        }
        if (!line.empty()) {
          vector<string> items;
          common::split(line, items, ';');
          if (items.size() == 4) {
            ruleIdMap.insert(RuleId2NameMap::value_type(items[0], items[1]));
            pmdRules[items[1]] = PMDRule(items[0], items[1], items[2], items[3]);
          }
        }
      }
      input.close();
    }
  }

  // create rules
  for (File_Names::iterator it = file_names.begin(); it != file_names.end(); ++it)
    makeRulByFile(it->c_str(), rh);

  // fix references in help texts
  {
    set<string> allIds;
    rh.getRuleIdList(allIds);

    for (string ruleId : allIds) {
      if (rh.getGroupType(ruleId) != "false") {
        // skip groups
        continue;
      }

      const boost::regex re(R"(\{% rule (\w+/)*(\w+)? %\})"); // {% rule LANG/GROUP/RULE %} or {% rule RULE %}

      auto fixRefs = [&](const boost::smatch& what) {
        std::string out = what[0];
        string origName = what[2];
        RuleId2NameMap::right_const_iterator nameIt = ruleIdMap.right.find(origName);
        if (nameIt != ruleIdMap.right.end()) {
          string id = RULE_PREFIX + nameIt->second;
          out = "[" + rh.getDisplayName(id) + "](#" + id + ")";
        }
        return out;
      };

      string helpText = rh.getHelpText(ruleId);
      string newHelpText = boost::regex_replace(helpText, re, fixRefs);

      if (helpText != newHelpText)
        rh.setHelpText(ruleId, newHelpText);
    }
  }

  // rewrite options file
  {
    ofstream output(rul_option_filename.c_str());
    if (output) {
      output << "ID;Name;Enabled;Priority" << "\n";

      // sort by ids
      for (RuleId2NameMap::left_const_iterator it = ruleIdMap.left.begin(); it != ruleIdMap.left.end(); ++it) {
        const PMDRule& rule = pmdRules[it->second];
        if (!rh.getIsDefined(rule.ruleId)) // ignore deleted rules
          continue;
        output << rule.id << ";" << rule.name << ";" << rule.enabled << ";" << rule.priority << "\n";
      }

      output.close();
    }
  }

  // write out the rul file
  rh.saveRul(rul.c_str());
}

static void setShortName(const std::string& origname, const std::string& rulename, std::string& shortname, int small = 0, int ext = 0) {
  RuleId2NameMap::right_const_iterator it = ruleIdMap.right.find(origname);
  if (it != ruleIdMap.right.end()) {
    shortname = it->second;
    return;
  }

  int tsmall = small;
  for (unsigned int i = 0; i < rulename.size(); i++) {
    if (::isupper(rulename[i]) || ::isdigit(rulename[i])) {
      shortname += rulename[i];
    } else if (::islower(rulename[i]) && tsmall > 0) {
      shortname += rulename[i];
      tsmall--;
    }
  }
  if (ext > 0)
    shortname += toString(ext);
  if (shortname.empty())
    setShortName(origname, rulename, shortname, ++small);
  else {
    RuleId2NameMap::left_const_iterator it1 = ruleIdMap.left.find(shortname);
    RuleId2NameMap::left_const_iterator it2 = ruleIdMap.left.end();
    if (it1 != it2) {
      shortname.clear();
      if (tsmall > 0)
        setShortName(origname, rulename, shortname, ++small, ++ext);
      else
        setShortName(origname, rulename, shortname, ++small);
    } else {
      ruleIdMap.insert(RuleId2NameMap::value_type(shortname, origname));
    }
  }
}

void PMDStrategy::makeRulByFile(const char* xmlFile, columbus::rul::RulHandler& rh){
  //initialization
  WriteMsg::write(CMSG_PMD2GRAPH_PROCESSING_FILE, xmlFile);

  loaddom(xmlFile);
  if (doc && doc->getDocumentElement()) {
    DOMElement* root = doc->getDocumentElement();

    string groupname, groupshortname;
    string pmdgroup = XMLString::transcode(root->getAttribute(XMLString::transcode("name")));
    groupname = groupshortname = pmd2InternalGroupName(pmdgroup);

    rh.defineMetric(groupshortname);

    // Default config
    rh.createConfiguration(groupshortname, "Default");
    rh.createLanguage(groupshortname, "Default", "eng");
    string desc = "";
    getDescription(desc, root);
    rh.setDescription(groupshortname, desc);
    rh.setHasWarningText(groupshortname, true);
    rh.setDisplayName(groupshortname, groupname);
    rh.setOriginalId(groupshortname, pmdgroup);
    rh.setGroupType(groupshortname, "summarized");
    rh.setHelpText(groupshortname, desc);
    rh.setIsEnabled(groupshortname, true);
    rh.setIsVisible(groupshortname, true);
    rh.setSettingValue(groupshortname, "Priority", "Minor", true);

    DOMNodeList* childs = root->getChildNodes();
    XMLSize_t length = childs->getLength();
    for(unsigned int i = 0; i < length; i++){
      DOMNode * node = childs->item(i);
      
      if( strcmp(XMLString::transcode(node->getNodeName()),"rule") == 0) {
        if(node->getAttributes()->getNamedItem(XMLString::transcode("name"))) {
          DOMNamedNodeMap * mymap = node->getAttributes();
          string rulename, shortname, desc;
          // default values
          string enabled = "1";
          string priority = "Minor";

          rulename = XMLString::transcode(mymap->getNamedItem(XMLString::transcode("name"))->getNodeValue());

          map<string, PMDRule>::const_iterator nameIt = pmdRules.find(rulename);
          if (nameIt != pmdRules.end()) {
            // the rule already exists in a previous version
            shortname = nameIt->second.id;
            enabled = nameIt->second.enabled;
            priority = nameIt->second.priority;
          } else {
            // new rule, generate an id for it
            setShortName(rulename, rulename, shortname);
            pmdRules[rulename] = PMDRule(shortname, rulename, enabled, priority);
          }

          shortname = RULE_PREFIX + shortname;

          rh.defineMetric(shortname);

          // Default config
          rh.createConfiguration(shortname, "Default");
          rh.createLanguage(shortname, "Default", "eng");
          rh.setHasWarningText(shortname, true);
          rh.setDisplayName(shortname, separateName(rulename));
          rh.setOriginalId(shortname, rulename);
          rh.setGroupType(shortname, "false");
          rh.setSettingValue(shortname, "Priority", priority, true);
          rh.addMetricGroupMembers(shortname, groupshortname);
          rh.setIsEnabled(shortname, enabled == "1");
          if(mymap->getNamedItem(XMLString::transcode("message"))){
            desc = XMLString::transcode(mymap->getNamedItem(XMLString::transcode("message"))->getNodeValue());
            rh.setDescription(shortname, desc);
          }
          string helptext = "";
          getDescription(helptext, node);
          rh.setHelpText(shortname, helptext);

          bool hok = getIsOnlySpaces(helptext);
          bool dok = getIsOnlySpaces(desc);
          if(!hok && dok)
            rh.setHelpText(shortname, desc);
          else if(hok && !dok)
            rh.setDescription(shortname, helptext);
          if(!hok && !dok){
            rh.setHelpText(shortname, rulename);
            rh.setDescription(shortname, rulename);
          }
        }
      }
    }
  }
}

bool PMDStrategy::getIsOnlySpaces(std::string& in){
  bool ok = false;
  for(unsigned int i = 0; i < in.size(); i++)
    if (in[i] != ' ')
      ok = true;
  return ok;
}

void PMDStrategy::getDescription(string& desc, DOMNode* node){
  DOMNodeList* childs = node->getChildNodes();
  XMLSize_t length = childs->getLength();
  string examples;

  for(unsigned int i = 0; i < length; i++){
    DOMNode * node = childs->item(i);
    if(strcmp(XMLString::transcode(node->getNodeName()),"description") == 0){
      XMLCh* descx = (XMLCh*)node->getTextContent();
      desc = toUTF8String(descx);
      common::trim(desc);
    }
    if(strcmp(XMLString::transcode(node->getNodeName()),"example") == 0){
      XMLCh* descx = (XMLCh*)node->getTextContent();
      string ex = toUTF8String(descx);
      common::trim(ex);
      if (!examples.empty())
        examples += "\n";
      examples += "```java\n";
      examples += ex;
      examples += "\n```\n";
    }
  }

  if (!examples.empty()) {
    desc += "\n\nExample(s):\n\n";
    desc += examples;
  }
}

void PMDStrategy::setConstantData(rul::RulHandler& rh){
  rh.setToolDescription("ID", "PMD");
}

bool getIsUpperCase(char c) {
  return (c >= 'A' && c <= 'Z');
}

std::string PMDStrategy::separateName(const std::string &name) {
  string newName;
  for(size_t i = 0; i<name.length(); i++) {
    newName += name[i];
    if(i!= name.length()-1 && !getIsUpperCase(name[i]) && name[i] != ' ' && getIsUpperCase(name[i+1])) {
      newName += ' ';
    }
  }
  return newName;
}

string PMDStrategy::pmd2InternalGroupName(const string& pmdGroupName) {
  string group = pmdGroupName;
  if (group[group.length()-1] == 's') {
    group.erase(group.length()-1);
  }
  group += " Rules";
  return group;
}
