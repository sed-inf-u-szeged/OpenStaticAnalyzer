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

#include "../inc/PylintRulMaker.h"
#include "../inc/messages.h"
#include "rul/inc/RulTags.h"

#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <filesystem>
#include <rul/inc/RulHandler.h>

#include <fstream>
#include <boost/regex.hpp>
#include <boost/bimap.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;
using namespace common;
using namespace columbus;

static const string RULE_PREFIX = "PYLINT_";

typedef boost::bimap<string, string> RuleId2NameMap;
static RuleId2NameMap ruleIdMap; // rule id (without prefix) <-> original pylint rule name

static void makeCamelCase(string& name) {
  if (name.empty())
    return;

  name[0] = ::toupper(name[0]);
  for (size_t i = 1, len = name.size(); i < len; ++i) {
    if (name[i - 1] == ' ')
      name[i] = ::toupper(name[i]);
  }
}

static string convertDisplayName(const string& ruleName) {
  if (ruleName.empty())
    return "";

  string name = ruleName;
  replace(name.begin(), name.end(), '-', ' ');
  makeCamelCase(name);

  return name;
}

static string convertGroupName(const string& groupName) {
  if (groupName.empty())
    return "";

  string name = groupName;
  replace(name.begin(), name.end(), '_', ' ');

  if (name == "classes") {
    name = "class";
  } else if (name == "miscellaneous") {
    name = "miscellaneous";
  } else if (name == "similarities") {
    name = "similarity";
  } else if (name == "master") {
    name = "pylint checker";
  } else if (name[name.size() - 1] == 's') {
    name.erase(name.size() - 1);
  }

  makeCamelCase(name);
  name += " Rules";

  return name;
}

static string convertPriority(const string& id) {
  char c = id[0];
  switch (c) {
    case 'I': return "Minor"; // info
    case 'C': return "Minor"; // convention
    case 'R': return "Minor"; // refactor
    case 'W': return "Major"; // warning
    case 'E': return "Critical"; // error
    case 'F': return "Blocker"; // fatal
    default: return "";
  }
}

// TODO copied from PMD2Graph, and modified slightly
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

static string convertRuleId(const string& origName, const string& dispName) {
  string shortName;
  setShortName(origName, dispName, shortName);
  return shortName;
}

struct PylintRule {
  PylintRule()
    : name(), id(), group(), desc(), warn() {}
  PylintRule(string name, string id, string group, string desc, string warn)
    : name(name), id(id), group(group), desc(desc), warn(warn) {}
  ~PylintRule() {}

  string name;
  string id;
  string group;
  string desc;
  string warn;

  bool operator<(const PylintRule& other) const {
    if (name != other.name)
      return name < other.name;
    // other members are not used for comparison
    return false;
  }
};

PylintRulMaker::PylintRulMaker() {
}

PylintRulMaker::~PylintRulMaker() {
}

void PylintRulMaker::makeRul(const string& messagesFileName, const string& idsFileName, const string& rulFile) {
  ruleIdMap.clear();

  // load existing ids
  if (!idsFileName.empty()) {
    ifstream input(idsFileName.c_str());
    if (input.is_open()) {
      string line;
      while (input.good()) {
        getline(input, line);
        if (!line.empty()) {
          vector<string> items;
          common::split(line, items, ';');
          if (items.size() == 2) {
            ruleIdMap.insert(RuleId2NameMap::value_type(items[0], items[1]));
          }
        }
      }
      input.close();
    }
  }

  rul::RulHandler rulHandler("Default", "eng");
  rulHandler.setToolDescription("ID", "Pylint");

  set<PylintRule> rules;
  map<string, set<string> > groupMembers;

  const boost::regex regexpRule(":(\\w+[-\\w]*):(\\w+[-\\w]*) \\((\\w+)\\):(?: \\*(.*)\\*)?");

  // read file and convert rules
  ifstream input(messagesFileName.c_str());
  if (input.is_open()) {
    string line;
    string def, desc;

    while (input.good()) {
      getline(input, line);

      if (line.empty() || line[0] == ':') {

        if (!def.empty()) {
          boost::smatch match;

          if (boost::regex_search(def, match, regexpRule)) {
            string group = match[1];
            string name = match[2];
            string id = match[3];
            string warn = match[4];

            rules.insert(PylintRule(name, id, group, desc, warn));

          } else {
            WriteMsg::write(CMSG_PYLINTRULMAKER_REGEXP_ERROR, def.c_str());
          }

          def = "";
          desc = "";
        }
      }

      if (line.empty()) {
        continue;
      } else if (line[0] == ':') {
        def = line;
      } else {
        common::trim(line, " ");
        if (!desc.empty() && *desc.rbegin() != '-') {
          desc += " ";
        }
        desc += line;
      }

    }

    input.close();

  } else {
    WriteMsg::write(CMSG_CANNOT_OPEN_FILE, messagesFileName.c_str());
    exit(EXIT_FAILURE);
  }

  // create rules
  for (set<PylintRule>::const_iterator it = rules.begin(), itEnd = rules.end(); it != itEnd; ++it) {
    const PylintRule& rule = *it;

    string prio = convertPriority(rule.id);
    string dispName = convertDisplayName(rule.name);
    string ruleId;
    bool isEnabled = true;
    string helpText = rule.desc;

    RuleId2NameMap::right_const_iterator nameIt = ruleIdMap.right.find(rule.name);
    if (nameIt != ruleIdMap.right.end()) {
      // the rule already exists in a previous version
      ruleId = nameIt->second;
    } else {
      // new rule, generate an id for it
      ruleId = convertRuleId(rule.name, dispName);
      ruleIdMap.insert(RuleId2NameMap::value_type(ruleId, rule.name));
    }

    ruleId = RULE_PREFIX + ruleId;

    groupMembers[rule.group].insert(ruleId);

    // these rules are disabled by default
    if (rule.name == "import-error" || rule.name == "method-check-failed" || rule.name == "unresolved-interface") {
      isEnabled = false;
    }

    // fix helptext
    {
      // helper func for escaping markdown / html spec chars : < { } [] \ _
      auto escapeSpecChars = [&](const boost::smatch& what) {
        std::string out = what[0];
        if (!out.empty() && out[0] != '`') {
          const boost::regex re("([_<\\{\\}\\[\\]\\\\])");
          out = boost::regex_replace(out, re, "\\\\\\1");
          boost::replace_all(out, "--", "\\-\\-");
        }
        return out;
      };

      // escape spec chars which are not inside a code block (between 2 ` or ``)
      const boost::regex reCode("`[^`]+`|[^`]+");
      helpText = boost::regex_replace(helpText, reCode, escapeSpecChars);

      // add < and > around links
      const boost::regex reUrl("(http[s]?://[^ ]+)([^\\.! ])");
      helpText = boost::regex_replace(helpText, reUrl, "<\\1\\2>");
    }

    rulHandler.defineMetric(ruleId);
    rulHandler.createConfiguration(ruleId, "Default");
    rulHandler.setIsEnabled(ruleId, isEnabled);
    rulHandler.setIsVisible(ruleId, true);
    rulHandler.setGroupType(ruleId, "false");
    rulHandler.createLanguage(ruleId, "eng");
    rulHandler.setHasWarningText(ruleId, true);
    rulHandler.setSettingValue(ruleId, "Priority", prio, true);
    rulHandler.setDisplayName(ruleId, dispName);
    rulHandler.setDescription(ruleId, rule.desc);
    rulHandler.setHelpText(ruleId, helpText);
    rulHandler.setWarningText(ruleId, rule.warn);
    rulHandler.setOriginalId(ruleId, rule.name);
  }

  // rewrite ids file
  {
    ofstream output((idsFileName + "_out").c_str());
    if (output.is_open()) {
      // sort by ids
      for (RuleId2NameMap::left_const_iterator it = ruleIdMap.left.begin(); it != ruleIdMap.left.end(); ++it) {
        output << it->first << ";" << it->second << "\n";
      }
      output.close();
    }
  }

  auto pylint_tag = rulHandler.getTagStore().create_or_get(rul::SplitTagStringView{"tool", "Pylint"});
  rulHandler.getTagMetadataStore().try_add_kind("tool").try_add_value("Pylint");
  auto &general_tag_metadata_container = rulHandler.getTagMetadataStore().try_add_kind("general");

  // create groups
  for (map<string, set<string> >::const_iterator git = groupMembers.begin(), gitEnd = groupMembers.end(); git != gitEnd; ++git) {
    string pylintGroupName = git->first;
    string groupName = convertGroupName(pylintGroupName);

    auto &value_tag_metadata = general_tag_metadata_container.try_add_value(groupName).value_metadata_ref();
    value_tag_metadata.description = groupName;
    value_tag_metadata.summarized = true;

    // disable these groups and their rules by default
    //   similarities - copy-paste detector, similar to DCF
    //   master - pylint's main checker component (analyzer errors, info messages, etc.)
    bool isDisabledByDefault = false;
    if (pylintGroupName == "similarities" || pylintGroupName == "master") {
      isDisabledByDefault = true;
    }

    for (set<string>::const_iterator rit = git->second.begin(), ritEnd = git->second.end(); rit != ritEnd; ++rit) {
      rulHandler.addTag(*rit, rul::SplitTagStringView{"general", groupName});
      rulHandler.addTag(*rit, pylint_tag);
      if (isDisabledByDefault) {
        rulHandler.setIsEnabled(*rit, false);
      }
    }
  }

  // save rul
  rulHandler.saveRul(rulFile);
}
