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

#include "../inc/graph.h"
#include "../privinc/GraphSchemaReader.h"
#include "../privinc/messages.h"

#define _AttributeGroup     "AttributeGroup"
#define _AttributeGroupName "name"
#define _Attribute          "Attribute"
#define _AttributeName      "name"
#define _AttributeType      "type"
#define _AttributeContext   "context"
#define _Nodes              "Nodes"
#define _Node               "Node"
#define _NodeType           "type"
#define _Attributes         "Attributes"
#define _Int                "int"
#define _Float              "float"
#define _String             "string"
#define _Compoiste          "composite"
#define _NodeGroup          "NodeGroup"
#define _NodeGroupName      "name"
#define _Edges              "Edges"
#define _Edge               "Edge"
#define _EdgeType           "type"
#define _EdgeDirection      "dir"
#define _Between            "Between"
#define _BetweenFrom        "from"
#define _BetweenTo          "to"
#define _Directed           "directed"
#define _Directed_with_reverse "directed_with_reverse"
#define _Bidirected          "bidirected"
#define _Graphschema         "graphschema"

using namespace std;

namespace columbus {  namespace graph {

  // GraphSchemaReader
  GraphSchemaReader::GraphSchemaReader(void) :
    strTable(),
    nodeSchema(),
    edgeSchema(),
    isEnabled(false)
  {
  }

  GraphSchemaReader::~GraphSchemaReader(void)
  {
  }

  void GraphSchemaReader::read(const string& filename) {
    GraphSchemaXmlHandler xmlHandler(this);
    io::loadXml(filename, xmlHandler);
    isEnabled = true;
  }

  void GraphSchemaReader::turnOff() {
    isEnabled = false;
  }

  void GraphSchemaReader::turnOn() {
    isEnabled = true;
  }

  bool GraphSchemaReader::getIsEnabled() const {
    return isEnabled;
  }


  string GraphSchemaReader::createAttributeSign(const string& name, const string& type, const string& context) {
    Key kName = strTable.set(name);
    Key kContext = strTable.set(context);
    string nameKey( reinterpret_cast<char*>(&kName ), 4);
    string contextKey( reinterpret_cast<char*>(&kContext ), 4);
    string typeKey;
    if(type == _Int)
      typeKey = '\0';
    if(type == _Float)
      typeKey = '\1';
    if(type == _String)
      typeKey = '\2';
    if(type == _Compoiste)
      typeKey = '\3';
    return nameKey + typeKey + contextKey;
  }

  string GraphSchemaReader::createAttributeSign(const Attribute& attribute) {
    Attribute::aType type = attribute.getType();
    Key kName = strTable.set(attribute.getName());
    Key kContext = strTable.set(attribute.getContext());
    string nameKey( reinterpret_cast<char*>(&kName ), 4);
    string contextKey( reinterpret_cast<char*>(&kContext ), 4);
    string typeKey;
    switch(type) {
      case Attribute::atInt:
        typeKey = '\0';
        break;
      case Attribute::atFloat:
        typeKey = '\1';
        break;
      case Attribute::atString:
        typeKey = '\2';
        break;
      case Attribute::atComposite:
        typeKey = '\3';
        break;
      default:
        typeKey = '\4';
        break;
    }

    string sign = nameKey + typeKey + contextKey;

    // if attribute is comosite, create sign to child
    if(type == Attribute::atComposite) {
      AttributeComposite& atComposite = (AttributeComposite&)attribute;
      sign += '\1';
      for(AttributeList::iterator it = atComposite.values->begin(); it != atComposite.values->end(); it++) {
        sign += createAttributeSign(**it);
      }      
      sign += '\2';
    }
    return sign;
  }

  bool GraphSchemaReader::canAddNode(const string& nodeType) {
    if(!isEnabled)
      return true;
    Key nodeTypeKey = strTable.get(nodeType);
    if(nodeTypeKey == 0) 
      return false;
    
    NodeSchema::iterator nodeIt = nodeSchema.find(nodeTypeKey);
    if(nodeIt == nodeSchema.end())
      return false;
    return true;
  }

  bool GraphSchemaReader::canAddAttributeToNode(const string& nodeType, const Attribute& attribute) {
    if(!isEnabled)
      return true;
    Key nodeTypeKey = strTable.get(nodeType);
    if(nodeTypeKey == 0) 
      return false;
    
    NodeSchema::iterator nodeIt = nodeSchema.find(nodeTypeKey);
    if(nodeIt == nodeSchema.end())
      return false;
    string attributeSign = createAttributeSign(attribute);
    Key kAttributeSign = strTable.get(attributeSign.c_str(), static_cast<unsigned long>(attributeSign.size()));
    if(kAttributeSign == 0 )
      return false;
    KeySet::iterator attributeIt = nodeIt->second.find(kAttributeSign);
    if(attributeIt == nodeIt->second.end())
      return false;
    return true;
  }

  bool GraphSchemaReader::canAddEdge(const string& edgeType, Edge::eDirectionType direction, const string& fromType, const string toType) {
    if(!isEnabled)
      return true;
   Key edgeTypeKey = strTable.get(edgeType);
    if(edgeTypeKey == 0)
      return false;

    Key fromKey = strTable.get(fromType);
    Key toKey = strTable.get(toType);

    switch (direction) {
      case Edge::edtBidirectional: 
        {
          EdgeSchema::iterator edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtBidirected));
          if(edgeIt == edgeSchema.end()) 
            return false;

          if( (edgeIt->second.second.find(make_pair(fromKey, toKey)) == edgeIt->second.second.end()  )
            && (edgeIt->second.second.find(make_pair(toKey, fromKey)) == edgeIt->second.second.end() )) 
            return false;
          break;
        }

      case Edge::edtDirectional:
        {
          EdgeSchema::iterator edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtDirected));
          if(edgeIt == edgeSchema.end()) {
            edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtDirected_with_reverse));
            if(edgeIt == edgeSchema.end()) 
              return false;
          }

          if( (edgeIt->second.second.find(make_pair(fromKey, toKey)) == edgeIt->second.second.end()  ) ) 
            return false;
          break;
        }
      case Edge::edtReverse:
        {
          EdgeSchema::iterator edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtDirected_with_reverse));
          if(edgeIt == edgeSchema.end()) 
            return false;
        
          if( (edgeIt->second.second.find(make_pair(toKey, fromKey)) == edgeIt->second.second.end()  ) )
            return false;
          break;
        }
    }
    return true;
  }

  bool GraphSchemaReader::canAddAttributeToEdge(const string& edgeType, Edge::eDirectionType direction, const string& fromType, const string toType, const Attribute& attribute) {
    if(!isEnabled)
      return true;
    Key edgeTypeKey = strTable.get(edgeType);
    if(edgeTypeKey == 0)
      return false;
    string attributeSign = createAttributeSign(attribute);
    Key kAttributeSign = strTable.get(attributeSign.c_str(), static_cast<unsigned long>(attributeSign.size()));

    if(kAttributeSign == 0)
      return false;

    EdgeSchema::iterator edgeIt = edgeSchema.end();
    switch (direction) {
      case Edge::edtBidirectional: 
        {
          edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtBidirected));
          if(edgeIt == edgeSchema.end()) 
            return false;
          break;
        }
      case Edge::edtDirectional:
        {
          edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtDirected));
          if(edgeIt == edgeSchema.end()) {
            edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtDirected_with_reverse));
            if(edgeIt == edgeSchema.end()) 
              return false;
          }
          break;
        }
      case Edge::edtReverse:
        {
          EdgeSchema::iterator edgeIt = edgeSchema.find(make_pair(edgeTypeKey, sdtDirected_with_reverse));
          if(edgeIt == edgeSchema.end()) 
            return false;
          break;
        }
    }
    if( edgeIt->second.first.find(kAttributeSign) == edgeIt->second.first.end())
      return false;

    return true;
  }

  // GraphSchemaReader end

  // GraphSchemaXmlHandler

  GraphSchemaXmlHandler::GraphSchemaXmlHandler(GraphSchemaReader *gsr) :
    lastAttributeSign(""),
    attributeDeepCounter(0),
    prevAttributeDeepCounter(0),
    lastAttributeGroup(0),
    lastNode(0),
    lastNodeGroup(0),
    lastEdge(),
    attributeGroups(),
    nodeGroups(),
    graphSr(gsr),
    lastRead()
  {
    lastRead.push(rsNone);
  }

  GraphSchemaXmlHandler::~GraphSchemaXmlHandler() {
  }


  void GraphSchemaXmlHandler::readAttribute(const AttributeList& list) {

    string attrName;
    string attrType;
    string attrContext;

    for(AttributeList::const_iterator alIt = list.begin(); alIt != list.end(); alIt++) {
      if(alIt->first == _AttributeName) {
        attrName = alIt->second;
      }
      if(alIt->first == _AttributeType) {
        attrType = alIt->second;
      }
      if(alIt->first == _AttributeContext) {
        attrContext = alIt->second;
      }

    }
    if( prevAttributeDeepCounter < attributeDeepCounter )
      lastAttributeSign += '\1';
    lastAttributeSign += graphSr->createAttributeSign(attrName, attrType, attrContext);

    if( prevAttributeDeepCounter > attributeDeepCounter )
      for(int i = 0; i< prevAttributeDeepCounter-attributeDeepCounter; i++)
        lastAttributeSign += '\2';
    prevAttributeDeepCounter = attributeDeepCounter;
    attributeDeepCounter++;
    

    lastRead.push(rsAttribute);
  }

  void GraphSchemaXmlHandler::readAttributeGroup(const AttributeList& list) {
   // read attributegroup tag inside root tag
    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    if( lastRead.top() == rsNone ) {
      for(AttributeList::const_iterator it = list.begin(); it != list.end(); it++) {
        if( it->first == _AttributeGroupName ) {
          lastAttributeGroup = graphSr->strTable.set(it->second);
          attributeGroups.insert(make_pair(lastAttributeGroup, set<Key>()));
          break;
        }
      }
    }


    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    // read attributegroup tag inside attributeGroup
    if(lastRead.top() == rsAttributeGroup) {
      AttributeGroups::iterator it = attributeGroups.find(lastAttributeGroup);
      if(it == attributeGroups.end())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_GROUP_FOUNDED + graphSr->strTable.get(lastAttributeGroup) );
      string attrName;
      for(AttributeList::const_iterator alIt = list.begin(); alIt != list.end(); alIt++) {
        if(alIt->first == _AttributeGroupName) {
          attrName = alIt->second;
        }
      }
      // find readed attribute group and add all membert to parent group
      AttributeGroups::iterator readedGroupIt = attributeGroups.find(graphSr->strTable.get(attrName));
      if(readedGroupIt == attributeGroups.end())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_GROUP_FOUNDED + attrName);
      it->second.insert(readedGroupIt->second.begin(), readedGroupIt->second.end());

    }
    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    // read attributegroup tag inside attributes
    if(lastRead.top() == rsAttributes) {

        // find group
      string attrName;
      for(AttributeList::const_iterator alIt = list.begin(); alIt != list.end(); alIt++) {
        if(alIt->first == _AttributeGroupName) {
          attrName = alIt->second;
        }
      }
      AttributeGroups::iterator readedGroupIt = attributeGroups.find(graphSr->strTable.get(attrName));
      if(readedGroupIt == attributeGroups.end())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_GROUP_FOUNDED + attrName);

      lastRead.pop();

      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      // attributes in node
      if(lastRead.top() == rsNode) {


        GraphSchemaReader::NodeSchema::iterator lastNodeIt = graphSr->nodeSchema.find(lastNode);
        if(lastNodeIt == graphSr->nodeSchema.end())
          GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_GROUP_FOUNDED + graphSr->strTable.get(lastNode));
        lastNodeIt->second.insert(readedGroupIt->second.begin(), readedGroupIt->second.end());

      }

      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      // attributes in edge
      if(lastRead.top() == rsEdge) {
        GraphSchemaReader::EdgeSchema::iterator lastEdgeIt = graphSr->edgeSchema.find(lastEdge);
        if(lastEdgeIt == graphSr->edgeSchema.end())
          GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_EDGE_FOUNDED + graphSr->strTable.get(lastEdge.first));
        lastEdgeIt->second.first.insert(readedGroupIt->second.begin(), readedGroupIt->second.end());

      }

      // attributes in nodeGroup
      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      if(lastRead.top() == rsNodeGroup) {
        NodeGroups::iterator nodeGroupIt = nodeGroups.find(lastNodeGroup);
        if(nodeGroupIt == nodeGroups.end()) 
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_NODEGROUP_FOUNDED + graphSr->strTable.get(lastNodeGroup));
        // add all attributes to all nodes
        // find all contained nodes
        for(set<Key>::iterator it = nodeGroupIt->second.begin(); it != nodeGroupIt->second.end(); it++) {
          // add all attributes
          for(set<Key>::iterator atIt = readedGroupIt->second.begin(); atIt != readedGroupIt->second.end(); atIt++) {
            // add attribute to founded node
            GraphSchemaReader::NodeSchema::iterator nodeSchemaIt = graphSr->nodeSchema.find(*it);
            if(nodeSchemaIt == graphSr->nodeSchema.end())
              throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_NODE_FOUNDED + graphSr->strTable.get(*it) );
            nodeSchemaIt->second.insert(*atIt) ;
          }
        }
      }
      lastRead.push(rsAttributes);
    }

    lastRead.push(rsAttributeGroup);
  }

  void GraphSchemaXmlHandler::readNodes(const AttributeList& list) {
    lastRead.push(rsNodes);
  }

  void GraphSchemaXmlHandler::readNode(const AttributeList& list) {
    // inside nodes tag
    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    if(lastRead.top() == rsNodes) {
      lastRead.pop();

      string nodeType;
      for(AttributeList::const_iterator alIt = list.begin(); alIt != list.end(); alIt++) {
        if(alIt->first == _NodeType) {
          nodeType = alIt->second;
        }
      }
      // if nodes tag in root tag
      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      if(lastRead.top() == rsNone) {
        lastNode = graphSr->strTable.set(nodeType);
        graphSr->nodeSchema.insert(make_pair(lastNode, set<Key>()));
      }

      // if nodes tag in nodegroup

      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      if(lastRead.top() == rsNodeGroup) {
        // find last node group
        NodeGroups::iterator nodeGroupIt = nodeGroups.find(lastNodeGroup);
        if(nodeGroupIt == nodeGroups.end())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODEGROUP_DOESNOT_FOUND + graphSr->strTable.get(lastNodeGroup) );
        nodeGroupIt->second.insert(graphSr->strTable.set(nodeType));
      }
      lastRead.push(rsNodes);
    }
    lastRead.push(rsNode);
  }


  void GraphSchemaXmlHandler::readAttributes(const AttributeList& list) {
    // inside node tag
    lastRead.push(rsAttributes);
  }

  void GraphSchemaXmlHandler::readNodeGroup(const AttributeList& list) {
    // inisde root tag
    string groupName;
    for(AttributeList::const_iterator alIt = list.begin(); alIt != list.end(); alIt++) {
      if(alIt->first == _NodeGroupName) {
        groupName = alIt->second;
      }
    }

    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    if(lastRead.top() == rsNone) {
      lastNodeGroup = graphSr->strTable.set(groupName);
      nodeGroups.insert(make_pair(lastNodeGroup, set<Key>()));
    }

    // inside nodes tag
    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    if(lastRead.top() == rsNodes) {
      lastRead.pop();
      // find readed nodeGroup
      NodeGroups::iterator readedNodeGroupIt = nodeGroups.find(graphSr->strTable.get(groupName));
      if(readedNodeGroupIt == nodeGroups.end()) 
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODEGROUP_DOESNOT_FOUND + groupName);
      
      // nodes in NodeGroup tag
      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      if(lastRead.top() == rsNodeGroup) {
        // find container node
        NodeGroups::iterator lastNodeGroupIt = nodeGroups.find(lastNodeGroup);
        if(lastNodeGroupIt == nodeGroups.end()) 
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODEGROUP_DOESNOT_FOUND + graphSr->strTable.get(lastNodeGroup));
        // add nodes from 'readedNodeGroupIt' to 'lastNodeGroupIt'
        lastNodeGroupIt->second.insert(readedNodeGroupIt->second.begin(),readedNodeGroupIt->second.end());
      }
      lastRead.push(rsNodes);
    }

    lastRead.push(rsNodeGroup);
  }


  void GraphSchemaXmlHandler::readEdges(const AttributeList& list) {
    lastRead.push(rsEdges);
  }

  void GraphSchemaXmlHandler::readEdge(const AttributeList& list) {

    //edge side Edges tag

    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    if(lastRead.top() == rsEdges) {
      string type;
      GraphSchemaReader::sDirectionType eDirection = GraphSchemaReader::sdtDirected;
      for(AttributeList::const_iterator alIt = list.begin(); alIt != list.end(); alIt++) {
        if(alIt->first == _EdgeType) {
          type = alIt->second;
        }
        if(alIt->first == _EdgeDirection) {
          string dir = alIt->second;
          if(dir == _Directed) {
            eDirection = GraphSchemaReader::sdtDirected;
          }
          if(dir == _Directed_with_reverse) {
            eDirection = GraphSchemaReader::sdtDirected_with_reverse;
          }
          if(dir == _Bidirected) {
            eDirection = GraphSchemaReader::sdtBidirected;
          }
        }
      }

      // insert a new edge
      lastEdge = (make_pair(graphSr->strTable.set(type), eDirection) );
      graphSr->edgeSchema.insert(make_pair (lastEdge, 
        make_pair( GraphSchemaReader::KeySet(), GraphSchemaReader::KeyPairSet() ) ) );

    }

    lastRead.push(rsEdge);
  }

  void GraphSchemaXmlHandler::readBetween(const AttributeList& list) {
    // inside edge tag
    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    if(lastRead.top() == rsEdge) {
      // find last edge
      GraphSchemaReader::EdgeSchema::iterator lastEdgeIt = graphSr->edgeSchema.find(lastEdge);
      if(lastEdgeIt == graphSr->edgeSchema.end())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_EDGE_DOESNOT_FOUND + graphSr->strTable.get(lastEdge.first) );
      string from;
      string to;
      for(AttributeList::const_iterator alIt = list.begin(); alIt != list.end(); alIt++) {
        if(alIt->first == _BetweenFrom) {
          from = alIt->second;
        }
        if(alIt->first == _BetweenTo) {
          to = alIt->second;
        }
      }

      // find from edge
      GraphSchemaReader::NodeSchema::iterator fromNodeIt = graphSr->nodeSchema.find(graphSr->strTable.get(from));
      NodeGroups::iterator fromNodeGroup = nodeGroups.end();
      if(fromNodeIt == graphSr->nodeSchema.end()) {
        fromNodeGroup = nodeGroups.find(graphSr->strTable.get(from));
        if(fromNodeGroup == nodeGroups.end())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODE_DOESNOT_FOUND + from );
      }
      // find to edge
      GraphSchemaReader::NodeSchema::iterator toNodeIt = graphSr->nodeSchema.find(graphSr->strTable.get(to));
      NodeGroups::iterator toNodeGroup = nodeGroups.end() ;
      if(toNodeIt == graphSr->nodeSchema.end()) {
        toNodeGroup = nodeGroups.find(graphSr->strTable.get(to));
        if(toNodeGroup == nodeGroups.end())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODE_DOESNOT_FOUND + to );
      }

      // add edge to nodes
      // node to node
      if( (fromNodeIt != graphSr->nodeSchema.end()) && (toNodeIt != graphSr->nodeSchema.end()) ) {
        lastEdgeIt->second.second.insert(make_pair( fromNodeIt->first, toNodeIt->first));
      }

      // node to nodeGroup
      if( (fromNodeIt != graphSr->nodeSchema.end()) && (toNodeGroup != nodeGroups.end() ) ) {
        for(GraphSchemaReader::KeySet::iterator it = toNodeGroup->second.begin(); it != toNodeGroup->second.end(); it++ ) {
          lastEdgeIt->second.second.insert(make_pair( fromNodeIt->first, *it));
        }
      }

      // nodeGroup to node
      if( (fromNodeGroup != nodeGroups.end()) && (toNodeIt != graphSr->nodeSchema.end()) ) {
        for(GraphSchemaReader::KeySet::iterator it = fromNodeGroup->second.begin(); it != fromNodeGroup->second.end(); it++ ) {
          lastEdgeIt->second.second.insert(make_pair( *it, toNodeIt->first));
        }
      }

      //nodeGtoup to nodeGroup
      if( (fromNodeGroup != nodeGroups.end()) && (toNodeGroup != nodeGroups.end() )  ) {
        for(GraphSchemaReader::KeySet::iterator it = fromNodeGroup->second.begin(); it != fromNodeGroup->second.end(); it++ ) {
          for(GraphSchemaReader::KeySet::iterator it2 = toNodeGroup->second.begin(); it2 != toNodeGroup->second.end(); it2++ ) {
            lastEdgeIt->second.second.insert(make_pair( *it, *it2));
          }
        }
      }

    }
    lastRead.push(rsBetween);
  }

  void GraphSchemaXmlHandler::beginTag(const string& name, const AttributeList& list) {

    // read attributeGroup tag
    if(name == _AttributeGroup) {
      readAttributeGroup(list);
    } else
    //read attribute tag
    if(name == _Attribute) {
      readAttribute(list);
    } else
    // read Nodes tag
    if(name == _Nodes) {
      readNodes(list);     
    } else
    // read node tag
    if(name == _Node) {
      readNode(list);
    } else
    // read attributes tag
    if(name == _Attributes) {
      readAttributes(list);
    } else
    // read NodeGroup tag
    if(name == _NodeGroup) {
      readNodeGroup(list);
    } else
    // read Edges tag
    if(name == _Edges) {
      readEdges(list);
    } else
    if(name == _Edge) {
      readEdge(list);
    } else
    if(name == _Between) {
      readBetween(list);
    } else if(name != _Graphschema)
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_NO_CAN_RECOGNIZE + name);

  }

  void GraphSchemaXmlHandler::endTag(const string& name) {
    bool attrIsTop = false;
    if(lastRead.empty())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
    if(lastRead.top() == rsAttribute ) {
      attributeDeepCounter--;
      attrIsTop = true;
    }
    
    lastRead.pop();
    if(lastRead.empty())
      return;
    if(attrIsTop && (lastRead.top() != rsAttribute) ) {
      if( prevAttributeDeepCounter > attributeDeepCounter )
        for(int i = 0; i< prevAttributeDeepCounter-attributeDeepCounter; i++)
          lastAttributeSign += '\2';
      attributeDeepCounter = prevAttributeDeepCounter = 0;
      Key attrSignKey = graphSr->strTable.set(lastAttributeSign.c_str(), static_cast<long>(lastAttributeSign.size()));
      lastAttributeSign = "";
      // add attribute sign to attributeGroups
      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      if(lastRead.top() == rsAttributeGroup) {
        AttributeGroups::iterator attrIt = attributeGroups.find(lastAttributeGroup);
        if(attrIt == attributeGroups.end())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_ATTRIBUTEGROUP_DOESNOT_FOUND + graphSr->strTable.get(lastAttributeGroup) );
        attrIt->second.insert(attrSignKey);
      }

      // add attribute sign
      if(lastRead.empty())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
      if(lastRead.top() == rsAttributes) {
        lastRead.pop();

        // if attributes in node
        if(lastRead.empty())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
        if(lastRead.top() == rsNode) {
          GraphSchemaReader::NodeSchema::iterator it = graphSr->nodeSchema.find(lastNode);
          if(it == graphSr->nodeSchema.end())
            throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODE_DOESNOT_FOUND + graphSr->strTable.get(lastNode) );
          it->second.insert(attrSignKey);
        }

        // if attributes in nodeGroup
        if(lastRead.empty())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
        if(lastRead.top() == rsNodeGroup) {
          NodeGroups::iterator nodeGropuIt = nodeGroups.find(lastNodeGroup);
          if(nodeGropuIt == nodeGroups.end())
            throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODEGROUP_DOESNOT_FOUND + graphSr->strTable.get(lastNodeGroup) );
          // add attributes for all contained nodes
          for(set<Key>::iterator it = nodeGropuIt->second.begin(); it != nodeGropuIt->second.end(); it++) {
            // find node
            GraphSchemaReader::NodeSchema::iterator nodeIt = graphSr->nodeSchema.find(*it);
            if(nodeIt == graphSr->nodeSchema.end()) 
              throw GraphException( COLUMBUS_LOCATION, CMSG_EX_NODE_DOESNOT_FOUND + graphSr->strTable.get(*it) );
            nodeIt->second.insert(attrSignKey);
          }
        }

        // if attributes in edge
        if(lastRead.empty())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_TAG_FOUND_OUTSIDE_OF_THE_ROOT_NODE );
        if(lastRead.top() == rsEdge) {
          // find last edge 
          GraphSchemaReader::EdgeSchema::iterator lastEdgeIt = graphSr->edgeSchema.find(lastEdge);
          if(lastEdgeIt == graphSr->edgeSchema.end())
            throw GraphException( COLUMBUS_LOCATION, CMSG_EX_EDGE_DOESNOT_FOUND + graphSr->strTable.get(lastEdge.first) );
          lastEdgeIt->second.first.insert(attrSignKey);
        }

        lastRead.push(rsAttributes);
      }

    }
  }

  // GraphSchemaXmlHandler end
  // TurnOffFilterSafety

  GraphSchemaReader::TurnOffFilterSafety::TurnOffFilterSafety(GraphSchemaReader& gsReader) : 
    _gsReader(gsReader),
    _state(gsReader.getIsEnabled()) {
   
    _gsReader.turnOff();
  }

  GraphSchemaReader::TurnOffFilterSafety::~TurnOffFilterSafety() {
    if(_state) {
      _gsReader.turnOn();
    }
  }

  // TurnOffFilterSafety end
}}
