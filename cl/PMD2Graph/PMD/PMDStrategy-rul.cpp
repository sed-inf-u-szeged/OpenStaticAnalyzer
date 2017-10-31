/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

using namespace std;
using namespace columbus;
using namespace common;
XERCES_CPP_NAMESPACE_USE

void PMDStrategy::makeRul(File_Names& file_names, std::string& rul, std::string& rulConfig, std::string& rul_option_filename, std::string& faulthunterrul){
  rul::RulHandler rh(rulConfig, "eng");

  setConstantData(rh);

  list<pair<string,string> > rul_refs;
  for(File_Names::iterator it = file_names.begin();it != file_names.end();++it)
    makeRulByFile(it->c_str(), rh, rul_refs);

  // FaultHunter -> Default redef
  rh.setConfigParent(CONFIG_FAULTHUNTER, CONFIG_DEFAULT);

  set<string> ref_id_list;
  // setting the groups of referenced ruls
  for(list<pair<string,string> >::iterator it = rul_refs.begin(); it != rul_refs.end(); ++it) {
    string group = group_paths.find(it->first.substr(0, it->first.find_last_of('/')))->second;
    string name = separateName(it->first.substr(it->first.find_last_of('/')+1, it->first.size()-1));
    set<string> members;
    rh.getGroupMembers(group, members);
    set<string>::iterator members_it;
    for(members_it = members.begin(); members_it != members.end(); ++members_it) {
      if(rh.getDisplayName(*members_it) == name) {
        rh.addMetricGroupMembers(*members_it, it->second);
        ref_id_list.insert(it->second + "-"+ *members_it);
        break;
      }
    }
    if(members_it == members.end()) {
      WriteMsg::write(CMSG_PMD2GRAPH_COULDNT_FIND_REF, name.c_str());
    }
  }

  if(rul_option_filename != "") {
    // save a rul option file, setting everything enabled
    ifstream file(rul_option_filename.c_str());
    if(!file.good()) {
      set<string> groups;
      rh.getGroupIdList(groups);

      io::CsvIO out(rul_option_filename, io::IOBase::omWrite);

      // header
      out.writeColumn("Parent");
      out.writeColumn("Name");
      out.writeColumn("ID");
      out.writeColumn("Enabled");
      out.writeColumn("Priority");
      out.writeNewLine();

      // rules
      for(set<string>::iterator group_it = groups.begin(); group_it != groups.end(); ++group_it) {
        set<string> members;
        StringMap shorted_members;
        rh.getGroupMembers(*group_it, members);
        // sort members by display name
        for(set<string>::iterator member_it = members.begin(); member_it != members.end(); ++member_it) {
          shorted_members.insert(pair<string, string>(rh.getDisplayName(*member_it), *member_it));
        }
        for(StringMap::iterator member_it = shorted_members.begin(); member_it != shorted_members.end(); ++member_it) {
          if(ref_id_list.find(*group_it + "-" + member_it->second) != ref_id_list.end()) {
            continue;
          }
          //write ruls
          out.writeColumn(*group_it);
          out.writeColumn(member_it->first);
          out.writeColumn(member_it->second);
          //is enabled
          out.writeColumn(1);
          //priority
          out.writeColumn("Minor");
          out.writeNewLine();
        }
      }

      // groups
      for(set<string>::iterator group_it = groups.begin(); group_it != groups.end(); ++group_it) {
        out.writeColumn(""); // no parent
        out.writeColumn(*group_it);
        out.writeColumn(*group_it);
        //is enabled
        out.writeColumn(1);
        //priority
        out.writeColumn("Minor");
        out.writeNewLine();
      }
      out.close();

    // read an existing rul option file
    } else {
      io::CsvIO in(rul_option_filename, io::IOBase::omRead);
      list<string> cols;
      list<string>::iterator it;

      in.readLine(cols); // skip header
      cols.clear();

      while (in.readLine(cols)) {
        if (cols.empty()) {
          break;
        }

        it = cols.begin();
        ++it; //group name
        ++it; //rul name
        string id = *it;
        bool enabled = common::str2int(*(++it)) != 0;
        rh.setIsEnabled(id, enabled);
        rh.setIsEnabled(id, CONFIG_FAULTHUNTER, enabled);
        rh.setSettingValue(id, "Priority", *(++it), true);

        cols.clear();
      }
      in.close();
    }
    file.close();
  }

  // turn off FH rules in the FaultHunter config
  if (!faulthunterrul.empty()) {
    set<string> pmdRules;
    rh.getRuleIdList(pmdRules);

    rul::RulHandler fhRh(faulthunterrul, "Default", "eng");

    set<string> fhRules;
    fhRh.getRuleIdList(fhRules);

    for (set<string>::const_iterator it = fhRules.begin(), itEnd = fhRules.end(); it != itEnd; ++it) {
      const string& fhRuleId = *it;
      string groupType = fhRh.getGroupType(fhRuleId);
      if (groupType == "false") { // only rules, no groups
        string pmdRuleId = fh2PMDRuleId(fhRuleId);
        if (pmdRules.find(pmdRuleId) != pmdRules.end()) {
          if (fhRh.getIsEnabled(fhRuleId)) {
            rh.setIsEnabled(pmdRuleId, CONFIG_FAULTHUNTER, false); // disable rule
          }
        }
      }
    }
  }

  //Writing out the rul file
  rh.saveRul(rul.c_str());
}

void PMDStrategy::makeRulByFile(const char* xmlFile, columbus::rul::RulHandler& rh, list<pair<string,string> > &rul_refs){
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
    rh.setGroupType(groupshortname, "summarized");
    rh.setHelpText(groupshortname, desc);
    rh.setIsEnabled(groupshortname, true);
    rh.setIsVisible(groupshortname, true);
    rh.setSettingValue(groupshortname, "Priority", "Minor", true);

    // FaultHunter config
    rh.createConfiguration(groupshortname, CONFIG_FAULTHUNTER);
    rh.createLanguage(groupshortname, CONFIG_FAULTHUNTER, "eng");
    rh.setConfig(CONFIG_FAULTHUNTER);
    rh.setHasWarningText(groupshortname, true);
    rh.setIsEnabled(groupshortname, true);
    rh.setConfig(CONFIG_DEFAULT);

    string path = xmlFile;
    std::replace(path.begin(), path.end(), DIRDIVCHAR, '/');
    path.erase(0, path.rfind("rulesets/"));
    group_paths[path] = groupshortname;

    DOMNodeList* childs = root->getChildNodes();
    XMLSize_t length = childs->getLength();
    for(unsigned int i = 0; i < length; i++){
      DOMNode * node = childs->item(i);
      
      if( strcmp(XMLString::transcode(node->getNodeName()),"rule") == 0) {
        if(node->getAttributes()->getNamedItem(XMLString::transcode("name"))) {
          DOMNamedNodeMap * mymap = node->getAttributes();
          string rulename, shortname, desc;
          rulename = XMLString::transcode(mymap->getNamedItem(XMLString::transcode("name"))->getNodeValue());
          setShortName(rulename, shortname);
          shortname = "PMD_" + shortname;

          rh.defineMetric(shortname);

          // Default config
          rh.createConfiguration(shortname, "Default");
          rh.createLanguage(shortname, "Default", "eng");
          rh.setHasWarningText(shortname, true);
          rh.setDisplayName(shortname, separateName(rulename));
          rh.setGroupType(shortname, "false");
          rh.setSettingValue(shortname, "Priority", "Minor", true);
          rh.addMetricGroupMembers(shortname, groupshortname);
          rh.setIsEnabled(shortname, true);
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

          // FaultHunter config
          rh.createConfiguration(shortname, CONFIG_FAULTHUNTER);
          rh.createLanguage(shortname, CONFIG_FAULTHUNTER, "eng");
          rh.setConfig(CONFIG_FAULTHUNTER);
          rh.setHasWarningText(shortname, true);
          rh.setIsEnabled(shortname, true);
          rh.setConfig(CONFIG_DEFAULT);

        } else if(node->getAttributes()->getNamedItem(XMLString::transcode("ref"))) {
          string name = XMLString::transcode(node->getAttributes()->getNamedItem(XMLString::transcode("ref"))->getNodeValue());
          rul_refs.push_back(pair<string, string>(name, groupshortname));
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
  for(unsigned int i = 0; i < length; i++){
    DOMNode * node = childs->item(i);
    if(strcmp(XMLString::transcode(node->getNodeName()),"description") == 0){
      XMLCh* descx = (XMLCh*)node->getTextContent();
      XMLString::collapseWS(descx);
      desc = XMLString::transcode(descx);
    }
    if(strcmp(XMLString::transcode(node->getNodeName()),"example") == 0){
      XMLCh* descx = (XMLCh*)node->getTextContent();
      // pre tag is needed to keep whitespaces
      desc += "<br>Example(s):<br><pre>";
      desc += XMLString::transcode(descx);
      desc += "</pre>";
    }
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

string PMDStrategy::fh2PMDRuleId(const std::string& fhRuleId) {
  string pmdRuleId = fhRuleId;
  if (pmdRuleId.find("FH_") == 0) {
    pmdRuleId.erase(0, 3);
  }
  pmdRuleId = "PMD_" + pmdRuleId;
  return pmdRuleId;
}

