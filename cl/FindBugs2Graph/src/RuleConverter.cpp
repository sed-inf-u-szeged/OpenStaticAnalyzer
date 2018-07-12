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
#include <common/inc/WriteMessage.h>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace columbus;
using namespace common;

XERCES_CPP_NAMESPACE_USE

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

void RuleConverter::formatMetricId(string& id) {
  id = "FB_" + id;
}

bool bothAreSpaces(char lhs, char rhs) {
  return (lhs == rhs) && (lhs == ' ');
}

void removeWS(string& str){
  
  //delete CR
  str.erase(remove(str.begin(), str.end(), '\r'), str.end());

  //trim the string
  while (!str.empty() && (str[0] == ' ' || str[0] == '\n'))
    str.erase(0, 1);

  while (!str.empty() && (str[str.length()-1] == ' ' || str[str.length()-1] == '\n'))
    str.erase(str.length()-1);
}

class CategoriesHandler : public DefaultHandler {
  private:
    rul::RulHandler* rul;
    string id;
    string content;
    bool bugCategory;
  
  public:
    CategoriesHandler(rul::RulHandler* rul) : DefaultHandler(), rul(rul), bugCategory(false) { }

    virtual void startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
      content.clear();
      
      string name = XMLString::transcode(localname);
      
      if(name == "BugCategory") {
        bugCategory = true;
        getAttr(attrs,"category",id);
        string originalCatName =id ;

        formatCategoryName(id);
        
        rul->defineMetric(id);
       
        rul->createConfiguration(id, rul->getConfig());

        rul->setIsEnabled(id,true);
        rul->setIsVisible(id,true);
        rul->setGroupType(id,"summarized");
        rul->createLanguage(id,"eng");
        rul->setHasWarningText(id,true);
        rul->setSettingValue(id,"Priority","Critical",true);
        rul->setDescription(id, "");
        rul->setDisplayName(id, id);
        rul->setOriginalId(id,originalCatName);
      } 
    }

    virtual void  characters (const XMLCh *const chars, const XMLSize_t length) {
      content += XMLString::transcode(chars);
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
      string name = XMLString::transcode(localname);
      if(name == "BugCategory") {
        bugCategory = false;
      } else if (bugCategory && name == "Details") {
        removeWS(content);
        rul->setHelpText(id,content);
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
      string name = XMLString::transcode(localname);
      
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
        
        string displayName = formatMetricDispName(id);
        RuleConverter::formatMetricId(id);
        rul->defineMetric(id);
        rul->createConfiguration(id, rul->getConfig());
        rul->setIsEnabled(id,true);
        rul->setIsVisible(id,true);
        rul->setGroupType(id,"false");
        rul->createLanguage(id,"eng");
        rul->setHasWarningText(id,true);
        rul->setSettingValue(id,"Priority","Critical",true);
        rul->setDisplayName(id, displayName);
        rul->setOriginalId(id, originalId);
      }
    }

    virtual void  characters (const XMLCh *const chars, const XMLSize_t length) {
      content += XMLString::transcode(chars);
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
      string name = XMLString::transcode(localname);
     
      if (name == "BugPattern") {
        bugPattern = false;
      } else if (bugPattern && name == "ShortDescription") {
        rul->setDescription(id,content);
      } else if (bugPattern && name == "LongDescription") {
        rul->setWarningText(id,content);
      } else if (bugPattern && name == "Details") {
        removeWS(content);
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
      string name = XMLString::transcode(localname);
      if(name == "BugPattern") {
        string id;
        getAttr(attrs,"type",id);
        RuleConverter::formatMetricId(id);

        string deprecated;
        if (getAttr(attrs, "deprecated", deprecated))
          if (deprecated == "true") {
            rul->deleteMetric(id);
            return;
          }

        string category;
        getAttr(attrs,"category",category);
        formatCategoryName(category);
        rul->addMetricGroupMembers(id, category);

        if(category == "Experimental Rules")
          rul->setIsEnabled(id,false);
        
        string experimental;
        if (getAttr(attrs, "experimental", experimental) && experimental == "true")
          rul->setIsEnabled(id,false);
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
      string name = XMLString::transcode(localname);
      if(name == "rule") {
        getAttr(attrs,"key", key);
        RuleConverter::formatMetricId(key);
      }
    }
    
    virtual void  characters (const XMLCh *const chars, const XMLSize_t length) {
      content += XMLString::transcode(chars);
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname) {
      string name = XMLString::transcode(localname);
      try {
        if (name == "priority") {
          if (content == "BLOCKER") 
            rul->setSettingValue(key, "Priority", "Blocker", true);
          else if (content == "CRITICAL") 
            rul->setSettingValue(key, "Priority", "Critical", true);
          else if (content == "MAJOR") 
            rul->setSettingValue(key, "Priority", "Major", true);
          else if (content == "MINOR") 
            rul->setSettingValue(key, "Priority", "Minor", true);
          else if (content == "INFO") 
            rul->setSettingValue(key, "Priority", "Info", true);
        }
      } catch (const rul::RulHandlerException& ex) {
        WriteMsg::write(CMSG_FINDBUGS2GRAPH_RULE_EXCEPTION, ex.getMessage().c_str());
      }
    }
    
};


void RuleConverter::convertRuleFile(const string& messagesXML, const string& findbugsXML, const string& rulesXML, const string& rulName, const string& rulConfig) {

  rul::RulHandler rul(rulConfig,"eng");
  rul.setToolDescription("ID", "FindBugs");
  
  //Processing messages.xml
  CategoriesHandler categoriesHandler(&rul);
  parseXML(messagesXML, &categoriesHandler);

  BugPatternsHandler bugPatternsHandler(&rul);
  parseXML(messagesXML, &bugPatternsHandler);

  //Processing findbugs.xml
  SetGroupsHandler setGroupsHandler(&rul);
  parseXML(findbugsXML, &setGroupsHandler);

  //Processing rules.xml
  SetPriorityHandler setPriorityHandler(&rul);
  parseXML(rulesXML, &setPriorityHandler);

  
  rul.saveRul(rulName);
}
