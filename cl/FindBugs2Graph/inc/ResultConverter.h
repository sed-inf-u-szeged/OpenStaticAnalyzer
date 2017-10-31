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

#ifndef _FB2G_RC_H_
#define _FB2G_RC_H_

#include <string>
#include <vector>
#include <rul/inc/RulHandler.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/GraphRangeIndexer.h>
#include <strtable/inc/RefDistributorStrTable.h>
#include <lim/inc/Factory.h>
#include <java/inc/java.h>

class ResultConverter
{
public:
  ResultConverter(const std::string& limFileName, const std::string& rul, const std::string& rulConfig, const std::string& txtOutputFileName);
  virtual ~ResultConverter();
  void buildtree(const bool exportRul);
  void saveGraph(const std::string& fileName);

  void addWarningToNode(const std::string& path, const std::string& id, const std::string& group, const std::string& warningText, std::list<columbus::graph::AttributeComposite>& sourceLinks, int line, int endline, int col = 0,  int endcol = INT_MAX);
  void collectData(const std::string& fbOutFile);

  bool getFullPath(const std::string& path, std::string& fullPath);
  bool findPath(const columbus::lim::asg::physical::FSEntry& item);
  columbus::graph::Graph* getGraph() { return &graph; }
  void aggregateWarnings(bool createGroups);

  void addLicenseTypeToTheGraphHeader(const std::string& toolName);
protected:
  
  void writeWarningLine(const std::string& id, const std::string& warningText, std::list<columbus::graph::AttributeComposite>& sourceLinks, const std::string& path, int line, int endline, int col, int endcol);
  columbus::RefDistributorStrTable strTable;
  columbus::lim::asg::Factory limFact;
  std::string limFileName;
  columbus::rul::RulHandler* xRulhandler;

  columbus::graph::Graph graph;
  columbus::graphsupport::GraphRangeIndexer& graphIndexer;

  std::vector<std::string> pathFB;
  std::vector<std::string> pathLim;
  std::map<std::string,std::string> pathMap;
  std::string txtOutputFileName;
};

#endif