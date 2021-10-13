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

#include <vector>
#include <algorithm>

#include "../inc/DirectedAcyclicGraph.h"

using namespace::std;

namespace columbus
{

namespace controller
{

template <class Key>
void DirectedAcyclicGraph<Key>::removeNode(const Key& toRemove)
{
  // Check node exists
  auto it = nodeMap.find(toRemove);
  if (it == nodeMap.end())
    return;
  
  // Fill vector with all edges going out and in from the node
  vector<pair<string, string>> edgesToRemove;
  for (const string& to : it->second.outEdges)
    edgesToRemove.push_back(make_pair(toRemove, to));

  for (const string& in : it->second.inEdges)
    edgesToRemove.push_back(make_pair(in, toRemove));

  // Remove all the edges
  for (const pair<string, string>& edge : edgesToRemove)
    removeEdge(edge.first, edge.second);


  // Remove the node itself
  nodeMap.erase(it);
}

template <class Key>
typename DirectedAcyclicGraph<Key>::errorType DirectedAcyclicGraph<Key>::addEdge(const Key& from, const Key& to)
{
  // A node cannot have an edge to itself
  if (from == to)
    return errorType::NODE_CANNOT_HAVE_EDGE_TO_ITSELF;

  Node* fromNode = nullptr;
  Node* toNode = nullptr;

  // Find nodes for the given keys
  auto it = nodeMap.find(from);
  if (it != nodeMap.end())
    fromNode = &it->second;

  it = nodeMap.find(to);
  if (it != nodeMap.end())
    toNode = &it->second;

  // If both nodes already exist then check the edge doesn't exist and that adding edge doesn't introduce a cycle
  if (fromNode && toNode)
  {
    if (find(fromNode->outEdges.begin(), fromNode->outEdges.end(), to) != fromNode->outEdges.end())
      return errorType::EDGE_ALREADY_EXISTS;
    if (checkForCycle(from, to)) // Returns true if it found a cycle
      return errorType::EDGE_INTRODUCES_CYCLE;
  }

  if(!fromNode)
    fromNode = &nodeMap[from];
  if(!toNode)
    toNode = &nodeMap[to];

  fromNode->outEdges.push_back(to);
  toNode->inEdges.push_back(from);
  return errorType::EDGE_ADDED;
}

template <class Key>
bool DirectedAcyclicGraph<Key>::checkForCycle(const Key& dependency, const Key& potentialDependent)
{
  if (dependency == potentialDependent)
    return true;
  
  Node& dependencyNode = nodeMap[dependency];
  for (const Key& nextDependency : dependencyNode.inEdges)
    if (checkForCycle(nextDependency, potentialDependent)) // Returns true if it found a cycle
      return true;

  // By this point all in-edges have been traversed so the current node cannot depend on the potentialDependent
  return false; 
}

template <class Key>
void DirectedAcyclicGraph<Key>::removeEdge(const Key& from, const Key& to)
{
  // Check nodes exist
  const auto fromIt = nodeMap.find(from);
  const auto toIt = nodeMap.find(to);
  if (fromIt == nodeMap.end() || toIt == nodeMap.end())
    return;

  // Remove edge from -> to
  fromIt->second.outEdges.remove(to);
  toIt->second.inEdges.remove(from);
}

template <class Key>
const list<Key>* DirectedAcyclicGraph<Key>::getInEdges(Key key) const
{
  const auto it = nodeMap.find(key);
  if (it != nodeMap.end())
    return &it->second.inEdges;

  // Return nullptr if node doesn't exist
  return nullptr;
}

template <class Key>
const list<Key>* DirectedAcyclicGraph<Key>::getOutEdges(Key key) const
{
  const auto it = nodeMap.find(key);
  if (it != nodeMap.end())
    return &it->second.outEdges;

  // Return nullptr if node doesn't exist
  return nullptr;
}

template class DirectedAcyclicGraph<string>;

} // namespace controller

} // namespace columbus