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

#ifndef _GRAPHRANGEINDEXER_H
#define _GRAPHRANGEINDEXER_H

#include <graph/inc/graph.h>
#include <map>
#include <vector>
#include <list>
#include <strtable/inc/StrTable.h>

namespace columbus { namespace graphsupport { 

  /**
   * \brief index nodes by path and line in graph
   */
  class GraphRangeIndexer {

  protected:

    /**
     * \internal
     * \brief node range
     */
    struct RangedNode {
      int line;
      int col;
      int endLine;
      int endCol;
      graph::Node node;

      bool operator<(const RangedNode& rangedNode);
      RangedNode() : line(0), col(0), endLine(0), endCol(0), node() {}
    };

    /**
     * \internal
     * \brief list of node range
     */
    typedef std::list< RangedNode > NodePrioritiList;
    /**
     * \internal
     * \brief index by path
     */
    typedef std::map< columbus::Key, NodePrioritiList > PathIndex;
    /**
     * \internal
     * \brief container for indexers
     */
    typedef std::vector< std::pair<const graph::Graph*, PathIndex > > IndexContainer;

  protected:
    /**
     * \internal \brief actual graph indexer object
     */
    static GraphRangeIndexer* indexerObj;
    /**
     * \internal \brief string tabel for indexers
     */
    static StrTable strTable;
    /**
     * \internal \brief conteainer for indexers
     *
     */
    IndexContainer indexContainer;

  protected:
    /**
    * \internal
    * \brief protected constructor for singleton GraphRangeIndexer class
    */
    GraphRangeIndexer();

    /**
     * \internal
     * \brief copy constructor
     */
    GraphRangeIndexer(const GraphRangeIndexer&);

    /**
    * \internal
    * \brief gives back true, if indexer is on at the graph
    * \param graph [in] the analized graph
    * \return true, if indexer is on, otherwise return false
    */
    bool getIsOn(const graph::Graph& graph) ;

    /**
    * \internal
    * \brief get range from node of graph
    * \param node [in] the node
    * \param range [out] the node range
    */
    void getRangeFromNode(const graph::Node& node, RangedNode& range, columbus::Key& path);

    /**
    * \internal
    * \brief return index to the graph, if it exist, otherwise create an empty index map
    * \param graph [in] the graph
    * \param index [out] the index of the graph
    */
    PathIndex& getGraphPathIndex(const graph::Graph& graph);

    /**
     * \internal
     * \brief add node to index
     * \param graph [in] the graph, witch has indexer and node
     * \param node [in] the added node
     * \param path [in] path of node
     * \param line [in] the line of node
     * \param col [in] the col of node
     * \param endLine [in] the endLine of node
     * \param endCol [in] the endCol of node
     */
    void addNode(graph::Graph& graph, graph::Node& node, const std::string& path, int line, int col, int endLine, int endCol);


  public:

    /**
    * \brief turn on indexer service and build index to graph
    * \param graph [in] the graph
    */
    void turnOn(graph::Graph& graph);

    /**
     * \brief trun off indexer service on graph
     * \param graph [in] the indexed graph
     */
    void turnOff(graph::Graph& graph);

    /**
     * \brief find nodes by path in the index
     * \param graph [in] graph, witch has an index object
     * \param path [in] the searched path
     * \param nodes [out] the founded nodes
     * \return false, if graph doesn't have index, or the index doesn't contains 'path', otherwise return true
     */
    bool findNodesByPath(graph::Graph& graph, const std::string& path, std::list<graph::Node>& nodes);

    /**
     * \brief find nodes by range
     * \param graph [in] graph, witch has an index object
     * \param path [in] the searched path
     * \param line [in] the range start line
     * \param col [in] the range start column
     * \param endLine [in] the range end line
     * \param endCol [in] the range end column
     * \param nodes [out] the founded nodes
     * \return false, if graph doesn't have index, or the index doesn't contains 'path', otherwise return true
     */
    bool findNodesByRange(graph::Graph& graph, const std::string& path, int line, int col, int endLine, int endCol, std::list<graph::Node>& nodes);

    /**
    * \brieg get instance from GraphRangeIndexer singleton class
    * \return a GraphRangeIndexer object
    */
    static GraphRangeIndexer& getGraphRangeIndexerInstance();

    friend void addPositionAttribute(graph::Graph& graph, graph::Node& node, const std::string& path, int line, int col, int endLine, int endCol, bool realizationLevel, bool definition);

  };

}}

#endif
