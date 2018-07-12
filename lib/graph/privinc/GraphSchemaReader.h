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

#ifndef GraphSchemaReaderGRAPH_H
#define GraphSchemaReaderGRAPH_H

#include <io/inc/IO.h>
#include <strtable/inc/StrTable.h>
#include "graph/inc/graph.h"

namespace columbus {  namespace graph {

  class GraphSchemaReader {

    public:

      /**
       * \brief Turn off graph schema validation. Destructor turn it back
       */
      class TurnOffFilterSafety {

        private:
          GraphSchemaReader& _gsReader;
          bool _state;
        public:
          TurnOffFilterSafety(GraphSchemaReader& gsReader);
          ~TurnOffFilterSafety();
      };


    private:

      // the edges direction types
      enum sDirectionType {
        sdtDirected,
        sdtDirected_with_reverse,
        sdtBidirected
      };

      StrTable strTable;      //strTable for attribute signatures
      
      typedef std::set<Key> KeySet;                           // set of keys
      typedef std::pair<Key, sDirectionType> SchemaEdgeType ; // shchema for edgeTypes (Key:The edge type, sDirectionType: the edge direction)
      typedef std::pair<Key,Key> KeyPair;                     // pair of keys
      typedef std::set<KeyPair> KeyPairSet;                   // set of keypairs

      // map<NodeType(key), set<attributum lenyomat(key)>>
      typedef std::map<Key, KeySet > NodeSchema;
      // map<pair<EdgeType (Key), edgeDirection>, pair<set<attributum lenyomat (key)>, set<pair<NodeType from(key), NodeType to(key)>>> 
      // if the edgeDirection is edtReverse then edge is directed_with_reverse
      typedef std::map<SchemaEdgeType , std::pair< KeySet, KeyPairSet > > EdgeSchema;

      NodeSchema nodeSchema;    // nodes from schema
      EdgeSchema edgeSchema;    // edges from schema

      bool isEnabled;           // if we read a schema, it will be true, otherwise false

      
    public:

      /**
      * \brief create attribute signature
      * \param name [in] name of attribtute
      * \param type [in] type of attribute
      * \param context [in] context of attribute
      * \return the attribute sugnature
      */
      std::string createAttributeSign(const std::string& name, const std::string& type, const std::string& context);
      
      /**
      * \brief create attribute signature
      * \param attribute [in] the attribute
      * \return the attribute sugnature
      */
      std::string createAttributeSign(const Attribute& attribute);

      /**
      * \brief return true, if we can add node to graph (based on schema)
      * \param nodeType [in] the type of node
      * \return true, if node can be added to graph, otherwise false
      */
      bool canAddNode(const std::string& nodeType) ;

      /**
      * \brief return true, if we can add attribute to node (based on schema)
      * \param nodeType [in] type of node
      * \param attribute [in] the attribute
      * \return true, if attribute can addet to node, otherwise false
      */
      bool canAddAttributeToNode(const std::string& nodeType, const Attribute& attribute);

      /**
      * \brief return true, if we can add edge to graph (based on schema)
      * \param edgeType [in] the type of node
      * \param direction [in] direction of edge
      * \param fromType [in] type of source node 
      * \param toType [in] type of target node
      * \return true, if node can be added to graph, otherwise false
      */
      bool canAddEdge(const std::string& edgeType, Edge::eDirectionType direction, const std::string& fromType, const std::string toType);

      /**
      * \brief return true, if we can add attribute to edge (based on schema)
      * \param edgeType [in] the type of node
      * \param direction [in] direction of edge
      * \param fromType [in] type of source node 
      * \param toType [in] type of target node
      * \param attribute [in] the attribute
      * \return true, if attribute can be added to edge, otherwise false
      */
      bool canAddAttributeToEdge(const std::string& edgeType, Edge::eDirectionType direction, const std::string& fromType, const std::string toType, const Attribute& attribute);

      /**
      * constructor
      */
      GraphSchemaReader(void);

      

      /**
      * destructor
      */
      ~GraphSchemaReader(void);

      /**
      * \brief read a file and parse it
      * \param filename [in] name of the file
      */
      void read(const std::string& filename) ;

      /**
       * \brief turn off graph schema validation
       */
      void turnOff();

      /**
       * \brief turn on graph schema validation
       */
      void turnOn();

      /**
       * \brief return graph schema validation state
       * \return true, if graph schema validation is active, otherwise return false
       */
      bool getIsEnabled() const;

    friend class GraphSchemaXmlHandler;
  };

  class GraphSchemaXmlHandler : public io::SimpleXmlIO::XmlHandler {


    private:

      // state of the reader
      enum ReadState {
        rsNone,
        rsAttributeGroup,
        rsAttribute,
        rsAttributes,
        rsNodes,
        rsNode,
        rsNodeGroup,
        rsEdges,
        rsEdge,
        rsBetween
      };

      std::string lastAttributeSign;     // last attribute signature
      int attributeDeepCounter;     // the attribute depth
      int prevAttributeDeepCounter; // the previous attribute depth

      Key lastAttributeGroup;       // the last attributegroup key
      Key lastNode;                 // the last node key
      Key lastNodeGroup;            // the last node group key
      GraphSchemaReader::SchemaEdgeType lastEdge;   //the last edge schema (edgetype and direction)

      typedef std::map<Key,std::set<Key> > AttributeGroups; // attribute groups type
      typedef std::map<Key,std::set<Key> > NodeGroups;      // node groups type

      AttributeGroups attributeGroups;                      // attribute groups
      NodeGroups nodeGroups;                                // node groups

      GraphSchemaReader* graphSr;                           // pointer to graph schema reader

      std::stack<ReadState> lastRead;                       // the reader state stack

      /**
      * \brief constructor
      * \param g [in] the loader graph
      */
      GraphSchemaXmlHandler(GraphSchemaReader *gsr);
      
      /**
      * \brief read an attribute tag
      * \param list [in] the tag attributes
      */
      void readAttribute(const AttributeList& list);

      /**
      * \brief read an attribute group tag
      * \param list [in] the tag attributes
      */
      void readAttributeGroup(const AttributeList& list); 

      /**
      * \brief read a nodes tag
      * \param list [in] the tag attributes
      */
      void readNodes(const AttributeList& list);
      
      /**
      * \brief read a nodes tag
      * \param list [in] the tag attributes
      */
      void readNode(const AttributeList& list);

      /**
      * \brief read an attributes tag
      * \param list [in] the tag attributes
      */
      void readAttributes(const AttributeList& list);

      /**
      * \brief read a nodegroup tag
      * \param list [in] the tag attributes
      */
      void readNodeGroup(const AttributeList& list);
      
      /**
      * \brief read an edges tag
      * \param list [in] the tag attributes
      */
      void readEdges(const AttributeList& list);

      /**
      * \brief read an edge tag
      * \param list [in] the tag attributes
      */
      void readEdge(const AttributeList& list);

      /**
      * \brief read a between tag
      * \param list [in] the tag attributes
      */
      void readBetween(const AttributeList& list);

      //disable copy
      GraphSchemaXmlHandler(const GraphSchemaXmlHandler& );
      GraphSchemaXmlHandler& operator=(const columbus::graph::GraphSchemaXmlHandler&);
    public:
      virtual ~GraphSchemaXmlHandler();
      /**
      * \breif read begin of a tag
      * \param name [in] the tag name
      * \param list [in] the attributes list
      */
      void beginTag(const std::string& name, const AttributeList& list);

      /**
      * \breif read end of a tag
      * \param name [in] the tag name
      */
      void endTag(const std::string& name);

    friend class GraphSchemaReader;

  };

}}
#endif
