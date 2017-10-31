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

#include "../inc/GraphRangeIndexer.h"
#include "../inc/Metric.h"
#include "../inc/GraphConstants.h"
#include <common/inc/StringSup.h>


using namespace columbus::graph;
using namespace common;
using namespace std;

namespace columbus { namespace graphsupport { 

  static void correctPath(string& path) {
    LowerDriveLetterOnWindows(path);
  }

  GraphRangeIndexer::GraphRangeIndexer() : indexContainer() {
  }

  GraphRangeIndexer& GraphRangeIndexer::getGraphRangeIndexerInstance() {
    if(indexerObj == NULL) 
      indexerObj = new GraphRangeIndexer();
    return *indexerObj;
  }

  GraphRangeIndexer::GraphRangeIndexer(const GraphRangeIndexer& graph) : indexContainer() {
  }


  bool GraphRangeIndexer::getIsOn(const graph::Graph& graph) {
    for(IndexContainer::iterator it = indexContainer.begin(); it != indexContainer.end(); it++) {
      if(it->first == &graph) {
        return true;
      }
    }
    return false;
  }

  void GraphRangeIndexer::getRangeFromNode(const graph::Node& node, RangedNode& range, Key& path) {
    std::string pathString;
    if (getPositionAttribute(node, pathString, range.line, range.col, range.endLine, range.endCol)) {
      correctPath(pathString);
      path = strTable.set(pathString);
    }
  }

  GraphRangeIndexer::PathIndex& GraphRangeIndexer::getGraphPathIndex(const graph::Graph& graph) {
    for(IndexContainer::iterator it = indexContainer.begin(); it != indexContainer.end(); it++) {
      if(it->first == &graph) {
        return it->second;
      }
    }
    indexContainer.push_back(make_pair(&graph, PathIndex()));
    return (indexContainer.back().second);
  }

  void GraphRangeIndexer::turnOn(graph::Graph &graph) {
    if(getIsOn(graph))
      return;

    Node::NodeIterator nodeIt = graph.getNodes();
    PathIndex& index = getGraphPathIndex(graph);
    while(nodeIt.hasNext()) {
      Node node = nodeIt.next();
      RangedNode rangedNode;
      Key path;
      rangedNode.node = node;
      getRangeFromNode(node, rangedNode, path);

      NodePrioritiList& priList = index[path];
      // insert node to list, list stay sorted
      NodePrioritiList::iterator listIt;
      for(listIt = priList.begin(); listIt != priList.end(); listIt++) {
        if(rangedNode < *listIt) 
          break;
      }
      priList.insert(listIt, rangedNode);
    }
  }

  void GraphRangeIndexer::turnOff(graph::Graph& graph) {
    if(!getIsOn(graph))
      return;

    IndexContainer::iterator it;
    for(it = indexContainer.begin(); it != indexContainer.end(); it++) {
      if(it->first == &graph) {
       break;
      }
    }
    indexContainer.erase(it);
  }

  bool GraphRangeIndexer::findNodesByPath(graph::Graph& graph, const string& origPath, std::list<graph::Node>& nodes) {
    if(!getIsOn(graph))
      return false;
    string path = origPath;
    correctPath(path);
    Key pathKey = strTable.get(path);
    if(!pathKey)
      return false;
    PathIndex& index = getGraphPathIndex(graph);
    PathIndex::iterator mapIt = index.find(pathKey);
    if(mapIt == index.end())
      return false;
    NodePrioritiList& list = mapIt->second;
    for(NodePrioritiList::iterator it = list.begin(); it != list.end(); it++)
      nodes.push_back(it->node);
    return true;
  }

  bool GraphRangeIndexer::findNodesByRange(graph::Graph& graph, const string& origPath, int line, int col, int endLine, int endCol, std::list<graph::Node>& nodes) {
    if(!getIsOn(graph))
      return false;
    string path = origPath;
    correctPath(path);
    Key pathKey = strTable.get(path);
    if(!pathKey)
      return false;
    PathIndex& index = getGraphPathIndex(graph);
    PathIndex::iterator mapIt = index.find(pathKey);
    if(mapIt == index.end())
      return false;
    NodePrioritiList& list = mapIt->second;
    for(NodePrioritiList::iterator it = list.begin(); it != list.end(); it++) {
      if( (endLine < it->line) || ((endLine == it->line) && (endCol < it->col)) )
        break;

      if( (line < it->endLine) || ((line == it->endLine) &&  (col <= (it->endCol))) )
        nodes.push_back(it->node);
    }
    return true;
  }

  GraphRangeIndexer* GraphRangeIndexer::indexerObj = NULL;

  StrTable GraphRangeIndexer::strTable = StrTable();

  bool GraphRangeIndexer::RangedNode::operator<(const GraphRangeIndexer::RangedNode &rangedNode) {
    if(this->line < rangedNode.line)
      return true;
    if(this->line == rangedNode.line)
      return this->col < rangedNode.col;
    return false;
  }

  void GraphRangeIndexer::addNode(graph::Graph& graph, graph::Node& node, const string& origPath, int line, int col, int endLine, int endCol) {
    if(!getIsOn(graph))
      return;
    string path = origPath;
    correctPath(path);
    PathIndex& index = getGraphPathIndex(graph);
    RangedNode rangedNode;
    Key pathKey = strTable.set(path);
    rangedNode.node = node;
    rangedNode.col = col;
    rangedNode.line = line;
    rangedNode.endCol = endCol;
    rangedNode.endLine = endLine;

    NodePrioritiList& priList = index[pathKey];
    // insert node to list, list stay sorted
    NodePrioritiList::iterator listIt;
    for(listIt = priList.begin(); listIt != priList.end(); listIt++) {
      if(rangedNode < *listIt) 
        break;
    }
    priList.insert(listIt, rangedNode);
  }



}}
