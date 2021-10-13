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

#ifndef _DIRECTED_ACYCLIC_GRAPH_
#define _DIRECTED_ACYCLIC_GRAPH_

#include <list>
#include <map>
#include <string>

namespace columbus
{

namespace controller
{

// Representation of a directed acyclic graph
template <class Key>
class DirectedAcyclicGraph
{
public:
  struct Node
  {
    std::list<Key> inEdges;
    std::list<Key> outEdges;
  };

private:
  std::map<Key, Node> nodeMap;

  bool checkForCycle(const Key& dependency, const Key& potentialDependent);

public:
  // Key identifies the node
  void addNode(const Key& key) { nodeMap[key]; }
  void removeNode(const Key& key);

  enum class errorType
  {
    EDGE_ADDED,
    EDGE_ALREADY_EXISTS,
    EDGE_INTRODUCES_CYCLE,
    NODE_CANNOT_HAVE_EDGE_TO_ITSELF
  };

  errorType addEdge(const Key& from, const Key& to); // returns std::pair, first value will be true false if an error occured, second value is the error message
  void removeEdge(const Key& from, const Key& to);
  const std::map<Key, Node>& getNodes() const { return nodeMap; }
  const std::list<Key>* getInEdges(Key key) const;
  const std::list<Key>* getOutEdges(Key key) const; 
};

} // namespace controller

} // namespace columbus

#endif
