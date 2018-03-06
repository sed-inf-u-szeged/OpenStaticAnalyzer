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

#ifndef _CHECKERSTRATEGY_H
#define _CHECKERSTRATEGY_H

#include <vector>
#include <map>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <common/inc/FileSup.h>
#include "MetricTree.h"
#include <rul/inc/RulHandler.h>
#include <common/inc/WriteMessage.h>
#include <graph/inc/graph.h>

typedef std::list<std::string> File_Names;

#ifndef X
#define X(str) XMLString::transcode(str)
#endif

extern bool print_debug;

#define WRITE_CSV(DEFINED, MEMBER) \
    mt->initialize_warnings(DEFINED); \
    for(vector<WarningElement>::iterator it = wevec.begin(); it != wevec.end(); it++){ \
      if(DEFINED.find(it->MEMBER) == DEFINED.end()){ \
        if(print_debug) \
          WriteMsg::write(WriteMsg::mlError, "WARNING: rul file is different than in making configuration file! Warning that is not set is occured in result xml! Different setting for warningID: %s\n", it->warningID.c_str()); \
      } \
      else{ \
        if(!it->path.empty()) \
          mt->addWarning_ID_Path(*it, it->MEMBER); \
        else if(it->is_component) \
          mt->addWarning_ID_Component(*it, it->MEMBER); \
        else if(!it->uniquename.empty()) \
          mt->addWarning_ID_Scope(*it, it->MEMBER); \
        else if(print_debug) \
          WriteMsg::write(WriteMsg::mlError, "WARNING (macro WRITE_CSV): Warning cannot be forwarded to MetricTree.\n"); \
      } \
    } 


class CheckerStrategy{
public:
  CheckerStrategy() : doc(0), mt(0), shortnames(), graph(), graphIndexer(columbus::graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance())
  {
    this->graphIndexer.turnOn(this->graph);
  }
  virtual ~CheckerStrategy(){}
  virtual void makeRul(File_Names&,std::string& rul, std::string& rulConfig, std::string& rul_option_filename) = 0;
  virtual void makeConfig(File_Names&, std::string&, std::string& rulConfig, std::string& configFile) = 0;
  virtual void makeCsv(std::string& lim, std::string& rul, std::string& rulConfig, File_Names& file_names, std::string& metrics, std::string& groupedmetrics, std::string& monitor, std::string& checkerbasedir);
  virtual void makeCsv(std::string& lim, std::string& rul, std::string& rulConfig , File_Names& file_names, std::string& metrics, std::string& groupedmetrics, std::string& monitor, std::string& checkerbasedir, const std::map<std::string, std::string>& levelMap);

  virtual void saveGraph(const std::string& filename, bool exportRul);

  void setGraph(columbus::graph::Graph& ingraph) { this->graphIndexer.turnOff(this->graph); graph = ingraph; this->graphIndexer.turnOn(this->graph);}

protected:
  XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc;
  MetricTree* mt;
  
  void loaddom(const char* filename);
  void savedom(const char * filename);

  bool getIsNeeded (const std::string& id, const columbus::rul::RulHandler& xRulHandler);

  //makerul common
  virtual void setConstantData(columbus::rul::RulHandler& rh) = 0;
  void setShortName(std::string& rulename,std::string& shortname, int small = 0 , int ext = 0);

  std::set<std::string> shortnames;

  columbus::graph::Graph graph;
  columbus::graphsupport::GraphRangeIndexer& graphIndexer;

};

#endif
