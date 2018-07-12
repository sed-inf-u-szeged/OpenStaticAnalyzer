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

#ifndef _GRAPHBGRAPH_H
#define _GRAPHBGRAPH_H

#include <list>
#include <set>
#include <map>
#include <queue>
#include <strtable/inc/StrTable.h>
#include <io/inc/IO.h>



/**
* \file BGraph.h
* \brief Contains graph declaration for the graph lib
*/


namespace columbus {  namespace graph {

  /** \internal \brief node visitor */
  typedef void (*nodeVisitorCallback)(const Node& node, void *data);

  /** \internal \brief edge visitor */
  typedef void (*edgeVisitorCallback)(const Edge& edge, void *data);

  class GraphSchemaReader;

  /**
  * \brief class represent graph
  */
  class Graph {

    protected:
      
      /** \internal
       * \param header [in] the section header
       * \return true, if header belongs to edges
       */
      bool isEdgeHeader(const std::list<std::string>& header);
      
      /**
       * \internal
       * process line in node section
       * \param line [in] the processed line
       * \param head [in] the section name
       * \param header [in] the section header
       */
      void processCSVNodeLine(const std::list<std::string>& line, const std::string& head, const std::list<std::string>& header);

      /**
       * \internal
       * process line in edge section
       * \param line [in] the processed line
       * \param head [in] the section name
       * \param header [in] the section header
       */
      void processCSVEdgeLine(const std::list<std::string>& line, const std::string& head, const std::list<std::string>& header);

      /**
       * \internal
       * load attributes and add to T(Edge/Node)
       * \param element [in] attributes added to element
       * \param line [in] the processed line
       * \param header [in] the section header
       * \param offset [in] offset of attributes (first id, ..., skipped)
       */
      template<class T>
      void loadAttributes(T& element, const std::list<std::string>& line, const std::list<std::string>& header, int offset);
      
      /**
       * \internal
       * process an attribute
       * \param element [in] add attribute to element
       * \param sign [in] the attribute sign (path_line)
       * \param value [in] attribute value with context
       */
      template<class T>
      void processAttribute(T& element, const std::string& sign, const std::string& value);

      /**
       * \internal
       * process a part of attribute column, at composite attribute this function is recursive
       * \param element [in] add attribute to element
       * \param slpitSing [inout] the attribute sing at split list
       * \param value [in] the attribute value
       * \param attrType [in] the attribute type
       * \param defCotnext [in] default context for attribute
       */
      template<class T>
      void processAtrtibutePart(T& element, std::list<std::string>& splitSign, const std::string& value, Attribute::aType attrType, const std::string& defCotnext);

      /**
       * \internal
       * find attribute type in attribute sign, and remove the type section from text ([Type:atString]))
       * \param text [inout] attribute sign
       * \return the converted attribute type
       */
      Attribute::aType getTypeFromString(std::string& text);

      /**
       * \internal
       * find context in string ([Context:a])
       * \param text [inout] attribute sing
       * \param vale [out] context
       * \return true if context is founded otherwise false
       */
      bool getContextFromString(std::string& text, std::string& value);

      /**
       * \internal
       * \brief invalidate all attibuteiterator on edge
       * \param edge [in] graph edge
       */
      void deleteIteratorContainerFromEdge(const GraphEdge& edge);

      /**
       * \internal
       * \brief invalidate all attibuteiterator and nodeiterator on vertex
       * \param node [in] graph node
       */
      void deleteIteratorContainerFromNode(const GraphVertex& node);

      /**
       * \internal
       * \brief copy outer graph to this
       * \param graph [in] the outer graph
       */
      void copyGraph(const Graph& graph);

    protected:
      
      /** \internal \brief list of EdgeIterators */
      typedef std::list<Edge::EdgeIterator*> EdgeIteratorList;
      /** \internal \brief list of Nodeiterators*/
      typedef std::list<Node::NodeIterator*> NodeIteratorList;
      
      /** \internal \brief containst witch edge has edge iterator*/
      typedef std::map<GraphVertex,EdgeIteratorList* > EdgeIteratorOnNodeMap;
      /** \internal \brief containst witch AttributeComposite has attribute iterator */
      typedef std::map<std::string, Attribute::AttributeIteratorList*> AttributeIteratorOnAttributeComposite;
      /** \internal \brief  map for header */
      typedef std::map<Key, Key> StringMap;
      

      /** \internal \brief attribute iterators on vertexes */
      Attribute::AttributeIteratorOnVertexMap attributeIteratorsOnVertex;
      /** \internal \brief attribute iterators on edges */
      Attribute::AttributeIteratorOnEdgeMap attributeIteratorsOnEdge;
      /** \internal \brief edge iterator on nodes*/
      EdgeIteratorOnNodeMap edgeIteratorOnNode;
      /** \internal \brief iterators on nodes*/
      NodeIteratorList nodeIterators;
      /** \internal \brief header information*/
      StringMap headerInformations;

      BGraph* g;
      StrTable* strTable;

      typedef std::map<Key,GraphVertex> KeyMap;
      typedef std::map<GraphEdge, GraphEdge> EdgePairMap; 

      KeyMap nodeUIDs;
      EdgePairMap edgePairMap;

      /** \internal \brief graph Schema reader */
      GraphSchemaReader* gsReader;

    protected:

      /**
      * \internal
      * \brief create Edge reverse pair
      * \param edge [in] create reserve pair for this edge
      * \return the reserve pair
      */
      Edge createReservePair(const Edge& edge);

      /**
      * \internal
      * \brief convert edge to bidirectional, remove edge from graph and add a new directional edge
      * \param edge [inout] the input edge
      */
      void convertEdgeToBidirectional(Edge& edge);

      /**
      * \internal
      * \brief convert edge to directed edge with reverse pair, remove edge from graph and add a new directed edge 
      * \param edge [inout] the input edge
      */
      void convertEdgeToDirectionalWithReverse(Edge& edge);

      /**
      * \internal
      * \brief write a attribute with values to XML
      * \param attribute [in] the attribute
      * \param sio [in] the simple xml out
      */
      void writeAttributeToXml(Attribute& attribute,io::SimpleXmlIO& sio) const;

      /**
      * \internal
      * \brief write a attribute with values to Binary
      * \param attribute [in] the attribute
      * \param out [in] the binary out
      */
      void writeAttributeToBinary(Attribute& attribute,io::BinaryIO& out) const;

      /**
      * \internal
      * \brief read attribute form binary file and add it to an edge or node
      * \param in [in] the binary file
      * \param node_edge [inout] the edge or node wich will have a new attribute
      */
      template<class T>
      void readAttributeToBinary(io::BinaryIO& in, T& node_edge) ;

      Attribute::AttributeIteratorList* getAttributeIteratorOnVertex(GraphVertex vertex);
      void removeAttributeIteratorOnVertexContainer(GraphVertex vertex);
      Attribute::AttributeIteratorList* getAttributeIteratorOnEdge(GraphEdge edge);
      void removeAttributeIteratorOnEdgeContainer(GraphEdge edge);

      /**
      * \internal
      * \brief get edge iterator to node
      * \param vertex [in] vertex(node) in boost
      * \return pointer ot list of edge iterators
      */
      EdgeIteratorList* getEdgeIteratorOnNode(GraphVertex vertex);

      void removeEdgeIteratorContainer(GraphVertex vertex);

      /**
      * \internal
      * \brief get node iterator
      * \return pointer to list node iteratros
      */
      NodeIteratorList* getNodeIterators();

      BGraph* getBGraph() const;
      StrTable* getStrTable() const;
      const std::string& getVertexUID(const GraphVertex& vertex) const;
      void setVertexUID(const GraphVertex& vertex, const std::string& uid);
      const Node::NodeType getVertexType(const GraphVertex& vertex) const;
      AttributeList* getAttributeList(const GraphVertex& vertex) const;
      const Edge::EdgeType getEdgeType(const GraphEdge& edge) const;
      AttributeList* getAttributeList(const GraphEdge& edge) const;

      GraphEdge createEdge(GraphVertex fromVertex, GraphVertex toVertex, const std::string& type, Edge::eDirectionType directionType);
      GraphEdge getEdgePair(GraphEdge edge) const;
      bool hasEdgePair(GraphEdge edge) const;

      void traverseDepthFirstPostorder(const Node& startNode, const Edge::EdgeTypeSet& edges,
        nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc,std::set<GraphVertex>& visitedVertexes, void* data);

      void traverseDepthFirstPreorder(const Node& startNode, const Edge::EdgeTypeSet& edges,
        nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc,std::set<GraphVertex>& visitedVertexes, void* data);

      void traverseDepthFirst(const Node& startNode, const Edge::EdgeTypeSet& edges,
        nodeVisitorCallback nodeVisitorFuncPre, nodeVisitorCallback nodeVisitorFuncPost, edgeVisitorCallback edgeVisitorFunc,std::set<GraphVertex>& visitedVertexes, void* data);

      void createGMLNode(io::SimpleXmlIO& sio, void* id, const std::string& name) const;
      void createGMLEdge(io::SimpleXmlIO& sio, unsigned id, void* from, void* to, Edge::eDirectionType et, const std::string& name) const;
      void clearHelperContaioners();
      void clearAttributes();
      void clear_node(const GraphVertex& node);
      void delete_edge(const GraphEdge& edge) ;

    public:

      /**
      * mmDropOldAttributes: drop all old attributes, 
      * mmDropNewAttributes: if element is exist drop all new attributes, if element is new, we copy all attributes
      * mmUnionAttribute: union exist elements attributes, set union mode with CompsiteAndStringMergeMode and NumericMergeMode
      * \brief graph merge mode
      */
      enum MergeMode {
        mmDropOldAttributes,
        mmDropNewAttributes,
        mmUnionAttribute
      };

      /**
      * csmmDropOldAttributes: drop all old attributes, if it exist in new graph(string, composite)
      * csmmDropNewAttributes: drop all new attributes, if it exist in old graph(string, composite)
      * csmmAddNewAttributes: add new attributes to element (if attribute is exist we add it too)
      * csmmUnionNewAttributes: add new attributes to element (if attribute is exist we don't add it)
      * \brief set how to merge composite and string attribute
      */
      enum CompsiteAndStringMergeMode {
        csmmDropOldAttributes,
        csmmDropNewAttributes,
        csmmAddNewAttributes,
        csmmUnionNewAttributes
      };

      /**
      * nmmDropOldAttributes: drop all old attributes, if it exist in new graph(int, float)
      * nmmDropNewAttributes: drop all new attributes, if it exist in old graph(int, float)
      * nmmAddNewAttributes: add new attributes to element (if attribute is exist we add it too)
      * nmmSummariteAttributes: summarize numerical attribute
      * \brief set how to merge int and float attribute
      */
      enum NumericMergeMode {
        nmmDropOldAttributes,
        nmmDropNewAttributes,
        nmmAddNewAttributes,
        nmmSummarizeAttributes
      };

    public:

      /**
      * \brief graph constructor
      */
      Graph() ;

      /**
      * \brief copy constructor
      */
      Graph(const Graph& graph);

      /**
       * \brief copy graph
       * \param graph [in] other graph
       */
      Graph& operator=(const Graph& graph);

      /**
      * \brief destructor
      */
      ~Graph() ;

      void clear();

      bool nodeIsExist(const std::string& UID);
      Node createNode(const std::string& UID, const Node::NodeType& NTYPE);  // O(log(N))
      Node createNode(const char* UID, const char* NTYPE);
      Node addNode(const Node& node);  // O(log(N))
      
      bool deleteNode(const std::string& UID); // O(log(N) + E))
      bool deleteNode(const Node& node); // O(log(N) + E)
      bool deleteNode(const Node::NodeType& NTYPE); // O(N + E)
        
      Edge createDirectedEdge(const Node& from, const Node& to, const std::string& type, bool createReverse); // O(1)
      Edge createDirectedEdge(const std::string& fromUID, const std::string& toUID, const std::string& type, bool createReverse); // O(log(N))
      Edge createBidirectedEdge(const Node& from, const Node& to, const std::string& type); //O(1)
      Edge createBidirectedEdge(const std::string& fromUID, const std::string& toUID, const std::string& type); // O(log(N))
      
      void traverseBreadthFirst(const Node& startNode, const Edge::EdgeTypeSet& edges, 
                                nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc, void* data);
      
      void traverseDepthFirstPostorder(const Node& startNode, const Edge::EdgeTypeSet& edges, 
                                nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc, void* data);

      void traverseDepthFirstPreorder(const Node& startNode, const Edge::EdgeTypeSet& edges, 
                                nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc, void* data);

      void traverseDepthFirst(const Node& startNode, const Edge::EdgeTypeSet& edges,
                                nodeVisitorCallback nodeVisitorFuncPre, nodeVisitorCallback nodeVisitorFuncPost, edgeVisitorCallback edgeVisitorFunc, void* data);

      Node findNode(const std::string& UID);  // O(log(N))
      Node::NodeIterator findNodes(const Node::NodeType& NTYPE); // O(N)
      Node::NodeIterator findNodes(const Node::NodeTypeSet& NTS); // O(N)

      void deleteEdge(const Edge& edge); 
      void deleteEdge(const Edge::EdgeType& type);
      void deleteEdge(const Node& from, const Node& to);

      /**
      * \brief create int attribute
      * \param name [in] the attribute name
      * \param value [in] the attribute value
      * \return copy of created attribute
      */
      AttributeInt createAttributeInt(const std::string& name, const std::string& context, int value);

      /**
      * \brief create float attribute
      * \param name [in] the attribute name
      * \param value [in] the attribute value
      * \return copy of created attribute
      */
      AttributeFloat createAttributeFloat(const std::string& name, const std::string& context, float value);

      /**
      * \brief create string attribute
      * \param name [in] the attribute name
      * \param value [in] the attribute value
      * \return copy of created attribute
      */
      AttributeString createAttributeString(const std::string& name, const std::string& context, const std::string& value);


      /**
      * \brief create composite attribute
      * \param name [in] the attribute name
      * \param tool [in] the context
      * \return copy of created attribute
      */
      AttributeComposite createAttributeComposite(const std::string& name, const std::string& context);

      void initAttribute(const Node::NodeTypeSet& nodeTypeSet,const Attribute& attr);

      /**
      * \brief collect the Leaf by edgeType
      * \param edgeType [in] the tree edges
      * \return the set of leafs
      */
      Node::NodeSet getLeafByEdgeType(const Edge::EdgeType& edgeType);

      /**
      * \brief find root nodes from graph by edgeType
      * \param edgeType [in] the tree edges
      * \return tho set of roots
      */
      Node::NodeSet getRootByEdgeType(const Edge::EdgeType& edgeType);

      /**
      * \brief set new infromation
      * \param key [in] the information name
      * \patam value [in] the information value
      */
      void setHeaderInfo(const std::string& key, const std::string& value);

      /**
      * \brief get information
      * \param key [in] the info name
      * \return the information value
      * \throw GraphException if key doesn't exist
      */
      std::string getHeaderInfo(const std::string& key);

      /**
      * \brief delete information form header
      * \param key [in] the info name
      * 
      */
      bool deleteHeaderInfo(const std::string& key);

      /**
      * \brief delete all information from header
      */
      void clearHeaderInfo();

      /**
      * \brief load graph validator xml schema, or append loaded schemas
      *       if we load a schema, the graph check add nodes, edges and attributes 
      * \param filename [in] the validator xml schema
      */
      void loadSchema(const std::string& filename) ;

      void saveXML(const std::string& filename) const;
      void saveGML(const std::string& filename) const;
      void loadXML(const std::string& filename) ;
      
      void saveBinary(const std::string& filename) const;
      void loadBinary(const std::string& filename) ;

      void saveCSV(const std::string& filename, const std::string& edge) const;
      void saveCSV(const std::string& filename) ;
      void loadCSV(const std::string& filename);

      /**
      * \brief get iterator to all nodes
      * \return iterator to nodes
      */
      Node::NodeIterator getNodes() ;


      /**
      * Merge this graph with 'graph'
      * Merge modes(nodes,edges):
      *       mmDropOldAttributes: drop all old attributes, 
      *       mmDropNewAttributes: if element is exist drop all new attributes, if element is new, we copy all attributes
      *       mmUnionAttribute: union exist elements attributes, set union mode with CompsiteAndStringMergeMode and NumericMergeMode
      * mmUnionAttribute options:
      *       String and composite attribute merge modes:
      *         csmmDropOldAttributes: drop all old attributes, if it exist in new graph(string, composite)
      *         csmmDropNewAttributes: drop all new attributes, if it exist in old graph(string, composite)
      *         csmmAddNewAttributes: add new attributes to element (if attribute is exist we add it too)
      *         csmmUnionNewAttributes: add new attributes to element (if attribute is exist we don't add it)
      *       Integer and float attribute merge modes:
      *         nmmDropOldAttributes: drop all old attributes, if it exist in new graph(int, float)
      *         nmmDropNewAttributes: drop all new attributes, if it exist in old graph(int, float)
      *         nmmSummariteAttributes: summarize numerical attribute
      *
      * \brief merge 'graph' to this graph
      * \param graph [in] this graph merged with 'graph'
      * \param nodeMode [in] merge mode to nodes
      * \param nodeAttributeStringAndCompositeMode [in] node string and composite attribute merge mode
      * \param nodeAttributeNumericMode [in] node string and composite aattribute merge mode
      * \param edgeMode [in] merge mode to edges
      * \param edgeAttributeStringAndCompositeMode [in] edge string and composite aattribute merge mode
      * \param edgeAttributeNumericMode [in] edge string and composite attribute merge mode
      */
      void merge(Graph& graph, Graph::MergeMode nodeMode, Graph::CompsiteAndStringMergeMode nodeAttributeStringAndCompositeMode, Graph::NumericMergeMode nodeAttributeNumericMode,
        Graph::MergeMode edgeMode, Graph::CompsiteAndStringMergeMode edgeAttributeStringAndCompositeMode, Graph::NumericMergeMode edgeAttributeNumericMode);

      /**
      * \brief merge 'graph' to this graph
      * \param filename [in] this graph merged with thath graph witch in 'filename' file
      * \param nodeMode [in] merge mode to nodes
      * \param nodeAttributeStringAndCompositeMode [in] node string and composite attribute merge mode
      * \param nodeAttributeNumericMode [in] node string and composite aattribute merge mode
      * \param edgeMode [in] merge mode to edges
      * \param edgeAttributeStringAndCompositeMode [in] edge string and composite aattribute merge mode
      * \param edgeAttributeNumericMode [in] edge string and composite attribute merge mode
      */
      void mergeWithBinary(const std::string& filename, Graph::MergeMode nodeMode, Graph::CompsiteAndStringMergeMode nodeAttributeStringAndCompositeMode, Graph::NumericMergeMode nodeAttributeNumericMode,
        Graph::MergeMode edgeMode, Graph::CompsiteAndStringMergeMode edgeAttributeStringAndCompositeMode, Graph::NumericMergeMode edgeAttributeNumericMode);

      /**
      * \brief merge 'graph' to this graph
      * \param filename [in] this graph merged with thath graph witch in 'filename' file
      * \param nodeMode [in] merge mode to nodes
      * \param nodeAttributeStringAndCompositeMode [in] node string and composite attribute merge mode
      * \param nodeAttributeNumericMode [in] node string and composite aattribute merge mode
      * \param edgeMode [in] merge mode to edges
      * \param edgeAttributeStringAndCompositeMode [in] edge string and composite aattribute merge mode
      * \param edgeAttributeNumericMode [in] edge string and composite attribute merge mode
      */
      void mergeWithXML(const std::string& filename, Graph::MergeMode nodeMode, Graph::CompsiteAndStringMergeMode nodeAttributeStringAndCompositeMode, Graph::NumericMergeMode nodeAttributeNumericMode,
        Graph::MergeMode edgeMode, Graph::CompsiteAndStringMergeMode edgeAttributeStringAndCompositeMode, Graph::NumericMergeMode edgeAttributeNumericMode);

    public:
    
      static const Node invalidNode;
      static const Edge invalidEdge;
      static const Attribute invalidAttribute;


    private:
      void convertEdgeMerge(std::multimap<std::string, Edge>& oldNodeTargets, Edge& newEdge, Graph& oldGraph, MergeMode mode,
          Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode);

      void convertEdgeAttribute(Edge& oldEdge, Edge& newEdge, Graph& oldGraph, Graph::MergeMode mode,
          Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode);

      void convertNodeMerge(Node& newNode, Graph& oldGraph, Graph::MergeMode mode,
          Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode);

      template<class NodeEdge>
      void convertSummarizeAttribute(NodeEdge& oldNode, NodeEdge& newNode,
          Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode);

      template<class NodeEdge>
      void convertOnlyNewAttribute(NodeEdge& oldNode, NodeEdge& newNode) ;


      Node createNode(Key UIDKey, Key NTYPEKey);  
      GraphEdge createEdge(GraphVertex fromVertex, GraphVertex toVertex, Key type, Edge::eDirectionType directionType);
      Edge createBidirectedEdge(const Node& from, const Node& to, Key typeKey);
      Edge createDirectedEdge(const Node& from, const Node& to, Key typeKey, bool createReverse);


    friend class Node;
    friend class Edge;  
    friend class Edge::EdgeIterator;
    friend class Node::NodeIterator;
    friend class Attribute;
    friend class Attribute::AttributeIterator;
    friend class AttributeString;
    friend class AttributeComposite;
    friend class GraphXmlHandler;
    friend void convertEdgeMerge(std::multimap<std::string, Edge>& , Edge& , Graph& , Graph::MergeMode , Graph::CompsiteAndStringMergeMode , Graph::NumericMergeMode );
  };

}}

#endif
