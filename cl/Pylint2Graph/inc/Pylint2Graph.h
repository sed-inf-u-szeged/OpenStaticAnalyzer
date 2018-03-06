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

#ifndef _PYLINT2GRAPH_H_
#define _PYLINT2GRAPH_H_

#include <string>

#include <strtable/inc/RefDistributorStrTable.h>
#include <lim/inc/Factory.h>
#include <rul/inc/RulHandler.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/GraphRangeIndexer.h>

class Pylint2Graph {
  public:
    Pylint2Graph(const std::string& rulFile, const std::string& rulConfig, std::ostream& out, const std::string& changePathFrom = "", const std::string& changePathTo = "");
    virtual ~Pylint2Graph();

    void buildGraph(const std::string& limFileName);
    void convertResults(const std::string& pylintResultsFile);
    void saveResultGraph(const std::string& outGraphFile, bool exportRul);

  protected:
    void addWarningToNode(const std::string& path, int line, int col, int endline, int endcol, const std::string& warningID, const std::string& warningText);

  protected:
    std::ostream& out;
    std::string changePathFrom;
    std::string changePathTo;
    columbus::RefDistributorStrTable strTable;
    columbus::lim::asg::Factory limFact;
    columbus::rul::RulHandler* rulHandler;
    columbus::graph::Graph graph;
    columbus::graphsupport::GraphRangeIndexer& graphIndexer;
};

#endif
