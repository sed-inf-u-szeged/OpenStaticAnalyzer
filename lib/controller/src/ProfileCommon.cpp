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


#include "../inc/ProfileCommon.h"
#include <algorithm>
#include <io/inc/SimpleXmlIO.h>
#include <common/inc/StringSup.h>

using namespace std;
using namespace columbus;


#define _THRESHOLDS             "thresholds"
#define _THRESHOLD              "threshold"
#define _THRESHOLD_METRIC_ID    "Mid"
#define _THRESHOLD_RELATION     "Relation"
#define _THRESHOLD_VALUE        "Value"
#define _THRESHOLD_ENTITY       "Entity"

struct Threshold {
  std::string metricId;
  std::string relation;
  std::string value;
  std::string entity;
  Threshold() {}
  Threshold(const Threshold& thr) : metricId(thr.metricId), relation(thr.relation), value(thr.value), entity(thr.entity) {}
};

class ThresholdsXmlHandler : public io::SimpleXmlIO::XmlHandler {
  private:
    vector<Threshold>& _thresholds;

  public:

    ThresholdsXmlHandler(vector<Threshold>& thresholds)
      : XmlHandler()
      , _thresholds(thresholds)
    {
    }

    ~ThresholdsXmlHandler() {
    }
  
    ThresholdsXmlHandler(const ThresholdsXmlHandler& sa);
    ThresholdsXmlHandler& operator=(const ThresholdsXmlHandler&);
  
    void processThreshold(const AttributeList &attrs)
    {
      AttributeList::const_iterator attrIt = attrs.begin();

      string metricId;
      string relation;
      string value;
      string entity;

      while(attrIt != attrs.end()){
        if(attrIt->first == _THRESHOLD_METRIC_ID){
          metricId = attrIt->second;
        } else if(attrIt->first == _THRESHOLD_RELATION){
          relation = attrIt->second;
        } else if(attrIt->first == _THRESHOLD_VALUE){
          value = attrIt->second;
        } else if(attrIt->first == _THRESHOLD_ENTITY){
          entity = attrIt->second;
        }
        ++attrIt;
      }

      vector<string> entities;
      common::split(entity, entities, ',');

      for(vector<string>::iterator eIt = entities.begin(); eIt != entities.end(); ++eIt)
      {
        Threshold thr;
        thr.metricId = metricId;
        thr.relation = relation;
        thr.value = value;
        thr.entity = *eIt;
        _thresholds.push_back(thr);
      }
    }

    void beginTag(const string& name, const AttributeList& list)
    {
      if(name == _THRESHOLD) {
        processThreshold(list);
      }
    }

    void endTag(const string& name)
    {
    }

  }; // ThresholdsXmlHandler

namespace columbus
{

namespace controller
{
  
  void profileProcessRulesCSV(const ProfileHandler& profile, map<string, rul::RulHandler*>& rulHandlers, map<string, bool>& runTool, const std::string& rulesCSV)
  {
    vector<string> tableTools; // csv header, tool names
    map<string, vector<int> > tableData; // csv data: (rulID, order)

    // load csv
    vector<string> line;
    columbus::io::CsvIO rulTable(rulesCSV, columbus::io::IOBase::omRead);

    // parse csv header
    rulTable.readLine(line);
    for(size_t i=1; i<line.size(); ++i)
      tableTools.push_back(line[i]);
    line.clear();

    // parse csv data
    while(rulTable.readLine(line) && line.size()==tableTools.size()+1)
    {
      string ruleID = line[0];
      map<string, vector<int> >::iterator row = tableData.insert(make_pair(ruleID, vector<int>())).first;
      
      for(size_t i=1; i<line.size(); ++i)
      {
        if(line[i] == "-")
          row->second.push_back(-1);
        else
          row->second.push_back(atoi(line[i].c_str()));
      }
      line.clear();
    }
    rulTable.close();

    // process data
    map<string, vector<int> >::iterator row = tableData.begin();
    while(row != tableData.end())
    {
      // set 0 if tool not running
      for(map<string, bool>::iterator rtIt = runTool.begin(); rtIt != runTool.end(); ++rtIt)
      {
        size_t pos = find(tableTools.begin(), tableTools.end(), rtIt->first) - tableTools.begin();
        if(pos != tableTools.size() && !rtIt->second)
        {
          row->second[pos] = 0;
        }
      }

      // get enable rule in tool by priority
      size_t mi = row->second.size();
      int mv = 100;
      for(size_t i= 0; i < row->second.size(); ++i)
      {
        if(row->second[i] > 0 && row->second[i] < mv)
        {
          mv = row->second[i]; mi = i;
        }
      }

      string tool("-");
      if (mi != row->second.size())
        tool = tableTools[mi];

      // enable/disable rule
      for(map<string, rul::RulHandler*>::iterator rhIt = rulHandlers.begin(); rhIt != rulHandlers.end(); ++rhIt)
      {
        string ruleID = rhIt->first + "_" + row->first;
        if(rhIt->first == tool)
        {
          if(profile.getIsRuleSettings(row->first))
          {
            rhIt->second->setIsEnabled(ruleID, profile.getIsRuleEnabled(row->first));
            if(profile.getIsRulePriority(row->first))
            {
              rhIt->second->setSettingValue(ruleID, "Priority", profile.getRulePriority(row->first), true);
            }
          }
        }
        else if(rhIt->second->getIsDefined(ruleID))
        {
          rhIt->second->setIsEnabled(ruleID, false);
        }
      }

      ++row;
    }

    // save rul files
    for(map<string, rul::RulHandler*>::iterator rhIt = rulHandlers.begin(); rhIt != rulHandlers.end(); ++rhIt)
    {
      rhIt->second->saveRul(rhIt->second->getFileName());
    }
  }

  void profileProcessToolThresholds(const ProfileHandler& profile, const string& toolName, const string& thresholdsFileIn, const string& thresholdsFileOut)
  {
    vector<Threshold> thresholds;
    vector<Threshold> thresholdsOut;

    //load default thresholds
    try
    {
      ThresholdsXmlHandler thresholdsXmlHandler(thresholds);
      io::loadXml(thresholdsFileIn, thresholdsXmlHandler);
    }
    catch (const IOException& toCatch)
    {
      throw ProfileHandlerException("profileProcessThresholds", toCatch.getMessage());
    }

    if(profile.getIsToolSettings(toolName))
    {
      list<pair<string, string> > profileThresholds = profile.getThresholdIds(toolName);
      //process thresholds
      for(vector<Threshold>::iterator it = thresholds.begin(); it != thresholds.end(); ++it)
      {
        if(profile.getIsThreshold(toolName, it->metricId, it->entity))
        {
          profileThresholds.remove(make_pair(it->metricId, it->entity));
          if(profile.getIsThresholdEnabled(toolName, it->metricId, it->entity))
          {
            Threshold thr(*it);
            thr.relation = profile.getThresholdRelation(toolName, it->metricId, it->entity);
            thr.value = profile.getThresholdValue(toolName, it->metricId, it->entity);
            thresholdsOut.push_back(thr);
          }
        }
        else
        {
          thresholdsOut.push_back(*it);
        }
      }
      //add new thresholds
      for(list<pair<string, string> >::iterator it = profileThresholds.begin(); it != profileThresholds.end(); ++it)
      {
        if(profile.getIsThresholdEnabled(toolName, it->first, it->second))
        {
          Threshold thr;
          thr.metricId = it->first;
          thr.entity = it->second;
          thr.relation = profile.getThresholdRelation(toolName, it->first, it->second);
          thr.value = profile.getThresholdValue(toolName, it->first, it->second);
          thresholdsOut.push_back(thr);
        }
      }   
    }
    else
    {
      thresholdsOut.insert(thresholdsOut.end(), thresholds.begin(), thresholds.end());
    }

    //save thresholds
    io::SimpleXmlIO outFile(thresholdsFileOut, io::IOBase::omWrite);
    outFile.writeXMLDeclaration("1.0", "UTF-8");
    
    outFile.writeBeginElement(_THRESHOLDS);

    for(vector<Threshold>::iterator it = thresholdsOut.begin(); it != thresholdsOut.end(); ++it)
    {
      outFile.writeBeginElement(_THRESHOLD);
      outFile.writeAttribute(_THRESHOLD_METRIC_ID, it->metricId);
      outFile.writeAttribute(_THRESHOLD_RELATION, it->relation);
      outFile.writeAttribute(_THRESHOLD_VALUE, it->value);
      outFile.writeAttribute(_THRESHOLD_ENTITY, it->entity);
      outFile.writeEndElement();
    }
    outFile.writeEndElement();
    outFile.close();
  }

} // namespace controller
} // namespace columbus
