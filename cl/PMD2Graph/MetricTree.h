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

#ifndef _METRICTREE_H
#define _METRICTREE_H

#include <vector>
#include <map>
#include <set>
#include <functional>
#include <xercesc/dom/DOMDocument.hpp>
#include <rul/inc/RulHandler.h>
#include <common/inc/FileSup.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/GraphRangeIndexer.h>
#include <common/inc/PlatformDependentDefines.h>

#include <iostream>
using namespace std;

class MetricTree
{
public:
  MetricTree(std::string& fileName, std::string& rul, std::string& rulConfig, const std::map<std::string, std::string>& levelMap, columbus::graph::Graph& graph, columbus::graphsupport::GraphRangeIndexer& graphIndexer);
  virtual ~MetricTree();
  void buildtree();

  void addWarningToNode(const std::string& path, int line, int col, int endline, int endcol, const std::string& groupID, const std::string& warningID, const std::string& warningText, bool we_is_component, FILE *f);

protected:
  std::string& fileName;
  columbus::rul::RulHandler* xRulhandler;

  std::map<std::string, std::string> levelMap;

  columbus::graph::Graph& graph;
  columbus::graphsupport::GraphRangeIndexer& graphIndexer;

  friend class CheckerStrategy;

};

#endif
