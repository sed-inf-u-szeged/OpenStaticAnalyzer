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

#ifndef _ADJMATRIXGRAPH_H_
#define _ADJMATRIXGRAPH_H_

#include <map>
#include <set>
#include <vector>
#include <algorithm>

namespace columbus {

  template<class PropertyType>
  class AdjMatrixGraph {
  public:
      typedef std::map<PropertyType, std::size_t> NodeIdVertexMap;
      typedef std::vector<std::pair<std::size_t, std::size_t> > EdgeList;
      typedef std::map<std::size_t, std::set<std::size_t> > OutEdgesMap;

  //private:
  public:
    std::size_t _size;
    bool* _graph;
    PropertyType* _vertexProps;
    NodeIdVertexMap _nodeIdToVertexMap;
    EdgeList _edgeList;
    OutEdgesMap _outEdges;
    std::size_t* _parents;
    std::size_t* _outEdgeNums;

    AdjMatrixGraph(AdjMatrixGraph& ajdMGraph) {}
    AdjMatrixGraph& operator=(AdjMatrixGraph& ajdMGraph) {}

  public:
    AdjMatrixGraph() : _size(0), _graph(NULL), _vertexProps(NULL), _nodeIdToVertexMap(NodeIdVertexMap()), _edgeList(EdgeList()), _outEdges(OutEdgesMap()), _parents(NULL), _outEdgeNums(NULL) {}

    ~AdjMatrixGraph() {
      delete[] _graph;
      delete[] _vertexProps;
      delete[] _parents;
      delete[] _outEdgeNums;
    }

    bool setSize(std::size_t size) {
      if(size > 0 && !_graph) {
        _size = size;
        _graph = new bool[size*size];
        _vertexProps = new PropertyType[size];
        _parents = new std::size_t[size];
        _outEdgeNums = new std::size_t[size];
        for(std::size_t i = 0; i < size*size; ++i) {
          _graph[i] = false;
        }
        for(std::size_t i = 0; i < size; ++i) {
          _vertexProps[i] = 0;
          _parents[i] = -1;
          _outEdgeNums[i] = 0;
        }
        _outEdges.clear();
        return true;
      }
      return false;
    }

    std::size_t getSize() {
      return _size;
    }

    std::size_t getSizeWithEdges() {
      return _size + _edgeList.size();
    }

    bool addEdge(std::size_t n, std::size_t m, bool isTreeEdge = false) {
      if(_graph && n < _size && m < _size) {
        if(!_graph[n*_size+m]) {
          _edgeList.push_back(std::make_pair(n, m));
          _graph[n*_size+m] = true;
          _outEdges[n].insert(m);
          if (isTreeEdge) {
            _parents[m] = n;
          }
          _outEdgeNums[n]++;
        }
        return true;
      }
      return false;
    }

    bool removeEdge(std::size_t n, std::size_t m) {
      if(_graph && n < _size && m < _size) {
        if(_graph[n*_size+m]) {
          std::remove(_edgeList.begin(), _edgeList.end(), std::make_pair(n, m));
          _graph[n*_size+m] = false;
          _outEdges[n].erase(m);
          _parents[m] = -1;
          _outEdgeNums[n]--;
        }
        return true;
      }
      return false;
    }

    inline bool existEdge(std::size_t n, std::size_t m) {
      if(_graph && n < _size && m < _size) {
        return _graph[n*_size+m];
      }
      return false;
    }

    const EdgeList& getEdges() {
      return _edgeList;
    }

    bool setParent(std::size_t child, std::size_t parent) {
      //if (_parents && child < _size && parent < _size && _graph[parent * _size + child]) {
      if (_parents && child < _size && parent < _size) {
        _parents[child] = parent;
        return true;
      }
      return false;
    }

    std::size_t getParent(std::size_t node) {
      //if (_parents && node < _size && _graph[_parents[node] * _size + node]) {
      if (_parents && node < _size ) {
        return _parents[node];
      }
      return -1;
    }

    const OutEdgesMap& getOutEdges() {
      return _outEdges;
    }

    std::size_t getOutEdgeNum(std::size_t n) {
      if (_graph && n < _size) {
        return _outEdgeNums[n];
      }
      return 0;
    }

    std::size_t getVertexByProperty(PropertyType node) {
      typename NodeIdVertexMap::const_iterator it = _nodeIdToVertexMap.find(node);
      if(it != _nodeIdToVertexMap.end()) {
        return it->second;
      }
      return -1;
    }

    PropertyType getProperty(std::size_t node) {
      if(_vertexProps && node < _size) {
        return _vertexProps[node];
      }
      return -1;
    }

    bool setVertexProperty(std::size_t node, PropertyType prop) {
      if(_vertexProps && node < _size) {
        _vertexProps[node] = prop;
        _nodeIdToVertexMap.insert(std::make_pair(prop, node));
        return true;
      }
      return false;
    }

    AdjMatrixGraph<PropertyType>* copyGraph(std::size_t from, std::size_t from_end) {
      if (from >= _size || from_end >= _size)
        return NULL;

      AdjMatrixGraph<PropertyType>* newGraph = new AdjMatrixGraph<PropertyType>();
      newGraph->setSize(_size - (from + from_end));

      // properties
      for (std::size_t i = from, counter = 0; i < _size - from_end; ++i, ++counter) {
        newGraph->setVertexProperty(counter, this->getProperty(i));
      }

      // edges
      for (EdgeList::const_iterator edgesIt = this->_edgeList.begin(); edgesIt != this->_edgeList.end(); ++edgesIt) {
        if (edgesIt->first >= from && edgesIt->first < (_size - from_end) &&
            edgesIt->second >= from && edgesIt->second < (_size - from_end))
        {
          newGraph->addEdge(edgesIt->first - from, edgesIt->second - from);
        }
      }

      // parent edges
      for (std::size_t i = from; i < _size - from_end; ++i) {
        if (_parents[i] >= from && _parents[i] < (_size - from_end) && _graph[_parents[i] * _size + i])
          newGraph->setParent(i - from, _parents[i] - from);
      }

      return newGraph;
    }

  };

}

#endif
