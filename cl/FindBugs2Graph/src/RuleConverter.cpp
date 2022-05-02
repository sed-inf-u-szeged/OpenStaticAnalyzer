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

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <rul/inc/RulHandler.h>
#include <rul/inc/RulTags.h>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/XercesSup.h>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <boost/bimap.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

using namespace std;
using namespace columbus;
using namespace common;

XERCES_CPP_NAMESPACE_USE

static const string RULE_PREFIX = "FB_";
static const string DEFAULT_PRIORITY = "UNKNOWN";

typedef boost::bimap<string, string> RuleId2NameMap;
static RuleId2NameMap ruleIdMap; // rule id (without prefix) <-> original rule name

bool getAttr(const Attributes& attrs, const char* attrName, string& val);
bool parseXML(const string& filename, DefaultHandler* handler);


void deleteFirstUnderscorePrefix(string& name) {
  size_t pos = name.find_first_of('_');
  if (pos != string::npos) {
    name = name.substr(pos+1);
  }
}

void removeUnderscoreAndMakeCamelcase(string& name) {
  if (name.empty())
    return;
  
  replace(name.begin(),name.end(), '_', ' ');
  transform(++name.begin(), name.end(), ++name.begin(), ::tolower);
  name[0] = ::toupper(name[0]);  
  
  for (size_t i = 1; i < name.size(); ++i) {
    if (name[i - 1] == ' ')
      name[i] = ::toupper(name[i]);
  }
}

string formatMetricDispName(const string& name){
  string dispName = name;
  
  deleteFirstUnderscorePrefix(dispName);
  removeUnderscoreAndMakeCamelcase(dispName);
  
  return dispName;
}

void formatCategoryName(string& categoryName) {
  if (categoryName == "I18N")
    categoryName = "INTERNATIONALIZATION";
  else if (categoryName == "MT_CORRECTNESS")
    categoryName = "MULTITHREADED_CORRECTNESS";
  else if (categoryName == "SECURITY")
    categoryName = "VULNERABILITY";
  else if (categoryName == "MALICIOUS_CODE")
    categoryName = "SECURITY_CODE_GUIDELINE";
  else if (categoryName == "PERFORMANCE")
    categoryName = "OPTIMIZATION";
  else if (categoryName == "STYLE")
    categoryName = "DODGY_CODE";
    
  removeUnderscoreAndMakeCamelcase(categoryName);
  categoryName += " Rules";
}

// TODO copied from PMD2Graph, and modified slightly
static void setShortName(const string& origname, const string& rulename, string& shortname, int small = 0, int ext = 0) {
  RuleId2NameMap::right_const_iterator it = ruleIdMap.right.find(origname);
  if (it != ruleIdMap.right.end()) {
    shortname = it->second;
    return;
  }

  int tsmall = small;
  for (unsigned int i = 0; i < rulename.size(); i++) {
    if (::isupper(rulename[i])) {
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

static bool isRuleSkipped(const string& name) {
  // these rules are skipped by default
  if (name == "DP_DO_INSIDE_DO_PRIVILEDGED" ||
      name == "UNKNOWN" ||
      name.compare(0, 5, "NOISE") == 0 || // NOISE_FIELD_REFERENCE, NOISE_METHOD_CALL, ...
      name.compare(0, 7, "TESTING") == 0) // TESTING, TESTING1, TESTING2, ...
    return true;
  else
    return false;
}

static bool isGroupSkipped(const string& name) {
  return name == "NOISE";
}

void RuleConverter::formatMetricId(string& id) {
  if (isRuleSkipped(id)) {
    id.clear();
    return;
  }

  string shortname;
  string dispNameForGen = id;
  removeUnderscoreAndMakeCamelcase(dispNameForGen);
  setShortName(id, dispNameForGen, shortname);
  id = RULE_PREFIX + shortname;
}

bool bothAreSpaces(char lhs, char rhs) {
  return (lhs == rhs) && (lhs == ' ');
}

void collapseWS(string& str) {
  str.erase(remove(str.begin(), str.end(), '\r'), str.end());
  replace(str.begin(), str.end(), '\n', ' ');
  boost::trim_all(str);
}

// use pandoc to convert html descriptions to markdown format
void convertDesc(string& str) {
  // temporary files
  static const string src = std::tmpnam(nullptr);
  static const string dst = std::tmpnam(nullptr);

  // for syntax highlighting
  boost::replace_all(str, "<pre><code>", "<pre class = \"java\"><code>");

  // write out the original description
  ofstream out(src.c_str());
  if (out) {
    out << str;
    out.close();
  }

  vector<string> sv;
  sv.push_back("-f");
  sv.push_back("html");
  sv.push_back("-t");
  sv.push_back("markdown_github");
  sv.push_back("-o");
  sv.push_back(dst);
  sv.push_back(src);

  // convert
  int ret = common::run("pandoc", sv);
  if (ret != 0) {
    WriteMsg::write(CMSG_FINDBUGS2GRAPH_PANDOC_ERROR, ret);
    exit(EXIT_FAILURE);
  }

  // read back the result
  ifstream in(dst.c_str());
  str = string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

class CategoriesHandler : public DefaultHandler {
  private:
    string id;
    string content;
    rul::TagKindMetadataContainer *general_tag_metadata_;
    bool bugCategory = false;
  
  public:
    explicit CategoriesHandler(rul::TagMetadataStore &tag_metadata_store) {
      tag_metadata_store.try_add_kind("tool").try_add_value("FindBugs");
      general_tag_metadata_ =
          &tag_metadata_store.try_add_kind("general");
    }

    virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
      content.clear();
      
      string name(common::Xerces::ScopedTranscode<char *>{localname});
      
      if(name == "BugCategory") {
        bugCategory = true;
        getAttr(attrs,"category",id);
        string originalCatName =id ;

        if (isGroupSkipped(id)) {
          bugCategory = false;
          return;
        }

        formatCategoryName(id);
      } 
    }

    virtual void  characters (const XMLCh *const chars, const XMLSize_t length) {
      content += common::Xerces::ScopedTranscode<char *>(chars);
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname) {
      string name(common::Xerces::ScopedTranscode<char *>{localname});
      if (name == "BugCategory") {
        bugCategory = false;
      } else if (bugCategory && name == "Details") {
        collapseWS(content);
        auto &value_tag_metadata = general_tag_metadata_->try_add_value(std::move(id)).value_metadata_ref();
        value_tag_metadata.summarized = true;
        value_tag_metadata.description = std::move(content);
      }
    }
};

class BugPatternsHandler : public DefaultHandler {
  private:
    rul::RulHandler* rul;
    string id;
    string content;

    bool bugPattern;

  public:
    BugPatternsHandler(rul::RulHandler* rul) : DefaultHandler(), rul(rul), bugPattern(false) { }

    virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
      content.clear();
      string name(common::Xerces::ScopedTranscode<char *>{localname});
      
      if(name == "BugPattern") {
        bugPattern = true;

        getAttr(attrs,"type", id);
        string originalId = id;
        string deprecated;
        if (getAttr(attrs, "deprecated", deprecated))
          if (deprecated == "true") {
            bugPattern = false;
            return;
          }

        if (isRuleSkipped(originalId)) {
          bugPattern = false;
          return;
        }

        string displayName = formatMetricDispName(id);
        RuleConverter::formatMetricId(id);
        rul->defineMetric(id);
        rul->createConfiguration(id, rul->getConfig());
        rul->setIsEnabled(id,true);
        rul->setIsVisible(id,true);
        rul->setGroupType(id,"false");
        rul->createLanguage(id,"eng");
        rul->setHasWarningText(id,true);
        rul->setSettingValue(id, "Priority", DEFAULT_PRIORITY, true);
        rul->setDisplayName(id, displayName);
        rul->setOriginalId(id, originalId);
      }
    }

    virtual void  characters (const XMLCh *const chars, const XMLSize_t length) {
      content += common::Xerces::ScopedTranscode<char *>(chars);
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
      string name(common::Xerces::ScopedTranscode<char *>{localname});
     
      if (name == "BugPattern") {
        bugPattern = false;
      } else if (bugPattern && name == "ShortDescription") {
        rul->setDescription(id,content);
      } else if (bugPattern && name == "LongDescription") {
        rul->setWarningText(id,content);
      } else if (bugPattern && name == "Details") {
        convertDesc(content);
        rul->setHelpText(id, content);
      }
    }
};

class SetGroupsHandler : public DefaultHandler {
  private:
    rul::RulHandler* rul;

  public:
    SetGroupsHandler(rul::RulHandler* rul) : DefaultHandler(), rul(rul) { }

    virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
      string name(common::Xerces::ScopedTranscode<char *>{localname});
      if(name == "BugPattern") {
        string id;
        getAttr(attrs,"type",id);
        RuleConverter::formatMetricId(id);

        if (!rul->getIsDefined(id))
          return;

        string deprecated;
        if (getAttr(attrs, "deprecated", deprecated))
          if (deprecated == "true") {
            if (rul->getIsDefined(id)) {
              rul->deleteMetric(id);
            }
            return;
          }

        string category;
        getAttr(attrs,"category",category);
        formatCategoryName(category);

        if(category == "Experimental Rules")
          rul->setIsEnabled(id,false);
        
        string experimental;
        if (getAttr(attrs, "experimental", experimental) && experimental == "true")
          rul->setIsEnabled(id,false);

        rul->addTag(id, rul::SplitTagStringView{"tool", "FindBugs"});
        rul->addTag(id, rul::SplitTagStringView{"general", category});
      }
    }
};

class SetPriorityHandler : public DefaultHandler {
  private:
    rul::RulHandler* rul;
    string key;
    string content;
    
  public:
    SetPriorityHandler(rul::RulHandler* rul) : DefaultHandler(), rul(rul) { }

    virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
      content.clear();
      string name(common::Xerces::ScopedTranscode<char *>{localname});
      if(name == "rule") {
        getAttr(attrs,"key", key);
        RuleConverter::formatMetricId(key);
        if (getAttr(attrs, "priority", content)) { // for newer xml files
          setPriority();
        }
      }
    }

    virtual void  characters (const XMLCh *const chars, const XMLSize_t length) {
      content += common::Xerces::ScopedTranscode<char *>(chars);
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname) {
      string name(common::Xerces::ScopedTranscode<char *>{localname});
      if (name == "priority")
        setPriority();
    }

    void setPriority() {
      if (rul->getIsDefined(key)) {
        string prio = content;
        // FB/SB priorities: BLOCKER, CRITICAL, MAJOR, MINOR, INFO
        transform(++prio.begin(), prio.end(), ++prio.begin(), ::tolower);
        rul->setSettingValue(key, "Priority", prio, true);
      }
    }
};

static void loadRuleOptions(const string& fileName) {
  if (fileName.empty())
    return;

  // load config file
  ifstream input(fileName.c_str());
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
        if (items.size() == 2) {
          ruleIdMap.insert(RuleId2NameMap::value_type(items[0], items[1]));
        }
      }
    }
    input.close();
  }
}

static void saveRuleOptions(const string& fileName, rul::RulHandler* rul) {
  if (fileName.empty())
    return;

  ofstream output((fileName + "_out").c_str());
  if (output) {
    output << "ID;Name" << "\n";
    // sort by ids
    for (RuleId2NameMap::left_const_iterator it = ruleIdMap.left.begin(); it != ruleIdMap.left.end(); ++it) {
      const string& ruleId = it->first;
      const string& origName = it->second;
      if (!rul->getIsDefined(RULE_PREFIX + ruleId)) {
        // ignore deleted/skipped rules
        continue;
      }
      output << ruleId << ";" << origName << "\n";
    }
    output.close();
  }
}

static void checkPriorities(rul::RulHandler* rul) {
  set<string> allIds;
  rul->getRuleIdList(allIds);

  for (const string& ruleId : allIds) {
    if (rul->getGroupType(ruleId) != "false") {
      continue;
    }
    string prio = rul->getSettingValue(ruleId, "Priority");
    if (prio == DEFAULT_PRIORITY) {
      WriteMsg::write(CMSG_FINDBUGS2GRAPH_MISSING_PRIORITY, ruleId.c_str(), rul->getOriginalIdByRuleId(ruleId).c_str());
    }
  }
}

void RuleConverter::convertRuleFile(const string& messagesXML, const string& findbugsXML, const vector<string>& rulesXMLs, const string& rulName, const string& rulConfig, const string& idsFileName) {
  rul::RulHandler rul(rulConfig,"eng");
  rul.setToolDescription("ID", "FindBugs");

  //Load previous rule ids
  loadRuleOptions(idsFileName);

  //Processing messages.xml
  CategoriesHandler categoriesHandler(rul.getTagMetadataStore());
  parseXML(messagesXML, &categoriesHandler);

  BugPatternsHandler bugPatternsHandler(&rul);
  parseXML(messagesXML, &bugPatternsHandler);

  //Processing findbugs.xml
  SetGroupsHandler setGroupsHandler(&rul);
  parseXML(findbugsXML, &setGroupsHandler);

  //Processing rules.xml
  for (const auto &rulesXML : rulesXMLs){
    SetPriorityHandler setPriorityHandler(&rul);
    parseXML(rulesXML, &setPriorityHandler);
  }

  //Save rule ids
  saveRuleOptions(idsFileName, &rul);

  //Check rule priorities
  checkPriorities(&rul);

  rul.saveRul(rulName);
}
