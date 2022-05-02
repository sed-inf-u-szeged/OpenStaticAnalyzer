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

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif
#include "PMDStrategy.h"
#include <rul/inc/RulHandler.h>
#include <common/inc/WriteMessage.h>
#include "../messages.h"

using namespace std;
using namespace columbus;
using namespace common;
XERCES_CPP_NAMESPACE_USE

#define X(str) XMLString::transcode(str)

void PMDStrategy::makeConfig(File_Names& file_names, string& rul, string& rulConfig, std::string& configFile)
{
  std::string iniFileName = ((common::pathFindFileName(rul) == rul) ? "." + string(DIRDIVSTRING) : "") + rul;
  rul::RulHandler* xRulHandler = new rul::RulHandler(iniFileName, rulConfig, "eng");

  map<string, string> ruleset2xmlfile;
  map<string, set<string> > rulesets;

  for(File_Names::iterator it = file_names.begin(); it != file_names.end(); it++){
    loaddom(it->c_str());
    if (doc && doc->getDocumentElement()) {
      DOMElement* root = doc->getDocumentElement();
      string groupname = pmd2InternalGroupName(X(root->getAttribute(X("name"))));
      string xmlfile = "category/java/" + common::pathFindFileName(*it);
      ruleset2xmlfile[groupname] = xmlfile;
    }
  }
  
  std::set<std::string> ruleIds;
  xRulHandler->getRuleIdList(ruleIds);

  for (const auto &ruleId : ruleIds) {
    for (const auto &tag : xRulHandler->getTags(ruleId)) {
      if (auto xmlFileIt = ruleset2xmlfile.find(tag->get_last_name()); xmlFileIt != ruleset2xmlfile.end()) {
        auto &excludedRuleSet = rulesets.try_emplace(xmlFileIt->second).first->second;
        if (!xRulHandler->getIsEnabled(ruleId)) {
          auto excludedRuleName = xRulHandler->getDisplayName(ruleId);
          excludedRuleName.erase(std::remove_if(excludedRuleName.begin(), excludedRuleName.end(), ::isspace),
                                 excludedRuleName.end());
          excludedRuleSet.insert(std::move(excludedRuleName));
        }
      }
    }
  }

  delete xRulHandler;

  builddom(rulesets, configFile);

}

void PMDStrategy::builddom(map<string, set<string> >& rulesetMap, std::string& configFile)
{
  map<string, set<string> >::iterator rulesetMap_it;
  set<string>::iterator set_it;
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch)
  {
    WriteMsg::write(CMSG_PMD2GRAPH_ERROR_DURING_INIT, X(toCatch.getMessage()));
    exit(1);
  }

  static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
  DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(gLS);

  try
  {
    doc = impl->createDocument(0, X("ruleset"), 0);

    DOMElement* root = doc->getDocumentElement();
    root->setAttribute(X("name"), X("PMD.rul"));
    root->setAttribute(X("xmlns"), X("http://pmd.sourceforge.net/ruleset/2.0.0"));
    root->setAttribute(X("xmlns:xsi"), X("http://www.w3.org/2001/XMLSchema-instance"));
    root->setAttribute(X("xsi:schemaLocation"), X("http://pmd.sourceforge.net/ruleset/2.0.0 http://pmd.sourceforge.net/ruleset_2_0_0.xsd"));

    DOMElement* descriptionElement = doc->createElement(X("description"));
    root->appendChild(descriptionElement);

    DOMText* descriptionText = doc->createTextNode(X("This ruleset was created from PMD.rul"));
    descriptionElement->appendChild(descriptionText);

    DOMElement* rule;
    DOMElement* exclude;
    for(rulesetMap_it = rulesetMap.begin(); rulesetMap_it != rulesetMap.end(); rulesetMap_it++)
    {
      rule = doc->createElement(X("rule"));
      root->appendChild(rule);
      rule->setAttribute(X("ref"), X(rulesetMap_it->first.c_str()));

      for(set_it = rulesetMap_it->second.begin(); set_it != rulesetMap_it->second.end(); set_it++)
      {
        exclude = doc->createElement(X("exclude"));
        rule->appendChild(exclude);
        exclude->setAttribute(X("name"), X((*set_it).c_str()));
      }
    }
  }
  catch (const OutOfMemoryException&)
  {
    WriteMsg::write(CMSG_PMD2GRAPH_OUT_OF_MEMORY);
    exit(1);
  }
  catch (const DOMException& e)
  {
    WriteMsg::write(CMSG_PMD2GRAPH_DOM_EX, e.code, X(e.getMessage()));
    exit(1);
  }
  catch (...)
  {
    WriteMsg::write(CMSG_PMD2GRAPH_ERROR_READING_DOCUMENT);
    exit(1);
  }

  savedom(configFile.empty() ? "PMD-config.xml" : configFile.c_str());

  doc->release();
}
