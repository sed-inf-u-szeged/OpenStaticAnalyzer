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
#include <filesystem>
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
#include <rul/inc/RulTags.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/XercesSup.h>
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
  rh.getTagMetadataStore().try_add_kind("tool").try_add_value("PMD");
  general_tag_metadata_container_ = &rh.getTagMetadataStore().try_add_kind("general");

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
    common::Xerces::ScopedTranscode<XMLCh *> rule_node_name_{"rule"};
    common::Xerces::ScopedTranscode<XMLCh *> name_attr_name_{"name"};
    common::Xerces::ScopedTranscode<XMLCh *> message_attr_name_{"message"};
    common::Xerces::ScopedTranscode<XMLCh *> priority_node_name_{"priority"};

    string groupname, groupshortname;
    string pmdgroup(common::Xerces::ScopedTranscode<char *>(root->getAttribute(name_attr_name_)));
    groupname = groupshortname = pmd2InternalGroupName(pmdgroup);

    auto &value_tag_metadata = general_tag_metadata_container_->try_add_value(groupname).value_metadata_ref();
    value_tag_metadata.summarized = true;
    std::string description;
    getDescription(description, root);
    value_tag_metadata.description = std::move(description);

    DOMNodeList* childs = root->getChildNodes();
    XMLSize_t length = childs->getLength();
    for(unsigned int i = 0; i < length; i++){
      DOMNode * node = childs->item(i);
      
      if(XMLString::compareString(node->getNodeName(), rule_node_name_) == 0) {
        if(node->getAttributes()->getNamedItem(name_attr_name_)) {
          DOMNamedNodeMap * mymap = node->getAttributes();
          string shortname, desc;
          // default values
          string enabled = "1";
          auto priority = [&]() -> std::string {
            for (auto *child_node = node->getFirstChild(); child_node != nullptr;
                 child_node = child_node->getNextSibling()) {
              if (XMLString::compareString(child_node->getNodeName(), priority_node_name_) == 0) {
                common::Xerces::ScopedTranscode<char *> priority_value(child_node->getTextContent());
                if (strcmp(priority_value, "2") == 0 || strcmp(priority_value, "3") == 0) { return "Major"; }
                if (strcmp(priority_value, "1") == 0) { return "Critical"; }
                return "Minor";
              }
            }
            return "Minor";
          }();

          string rulename(common::Xerces::ScopedTranscode<char *>(mymap->getNamedItem(name_attr_name_)->getNodeValue()));

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
          if(mymap->getNamedItem(message_attr_name_)){
            desc = common::Xerces::ScopedTranscode<char *>(mymap->getNamedItem(message_attr_name_)->getNodeValue());
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

          rh.addTag(shortname, rul::SplitTagStringView{"tool", "PMD"});
          rh.addTag(shortname, rul::SplitTagStringView{"general", groupname});
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
  common::Xerces::ScopedTranscode<XMLCh *> description_node_name_{"description"};
  common::Xerces::ScopedTranscode<XMLCh *> example_node_name_{"example"};

  DOMNodeList* childs = node->getChildNodes();
  XMLSize_t length = childs->getLength();
  string examples;

  for(unsigned int i = 0; i < length; i++){
    DOMNode * node = childs->item(i);
    if(XMLString::compareString(node->getNodeName(), description_node_name_) == 0){
      XMLCh* descx = (XMLCh*)node->getTextContent();
      desc = toUTF8String(descx);
      common::trim(desc);
    }
    if(XMLString::compareString(node->getNodeName(), example_node_name_)  == 0){
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
