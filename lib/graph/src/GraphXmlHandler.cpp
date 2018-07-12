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
#include "../privinc/GraphXmlHandler.h"
#include "../privinc/messages.h"

#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h> 

using namespace std;


namespace columbus {  namespace graph {

  GraphXmlHandler::GraphXmlHandler(Graph *g) : 
    graph(g),
    lastContainer(lctNone),
    activeEdge(),
    activeReverseEdge(),
    activeNode(),
    attrCompositeStack()
//    activeAttributeIntSet(NULL)
  {
  }

  GraphXmlHandler::~GraphXmlHandler(void)
  {
  }

  void GraphXmlHandler::beginTag(const string &name, const AttributeList &list) {
    if(name == XML_GRAPH_NODE) {
      lastContainer = lctNode;
      string name;
      string type;
      for(AttributeList::const_iterator it = list.begin(); it != list.end(); it++) {
        if(it->first == XML_GRAPH_NAME)
          name = it->second;
        if(it->first == XML_GRAPH_TYPE)
          type = it->second;
      }
      if(graph->nodeIsExist(name)) {
        activeNode = graph->findNode(name);
        activeNode.setType(Node::NodeType(type));
      } else {
        activeNode = graph->createNode(name,Node::NodeType(type));
      }
    } else if(name == XML_GRAPh_EDGE) {
      string type;
      Edge::eDirectionType direction = Edge::edtBidirectional;
      string to;
      for(AttributeList::const_iterator it = list.begin(); it != list.end(); it++) {
        if(it->first == XML_GRAPH_TYPE)
          type = it->second;
        if(it->first == XML_GRAPH_EDGE_TO)
          to = it->second;
        if(it->first == XML_GRAPH_DIRECTION) {
          if(it->second == "bidirectional")
            direction = Edge::edtBidirectional;
          if(it->second == "directional")
            direction = Edge::edtDirectional;
        }
      }
      Node toNode;
      if(graph->nodeIsExist(to)) {
        toNode = graph->findNode(to);
      } else {
        toNode = graph->createNode(to,Node::NodeType("__INVALID__"));
      }
      switch(direction) {
        case Edge::edtBidirectional:
          activeEdge = graph->createBidirectedEdge(activeNode,toNode,type);
          break;
        case Edge::edtDirectional:
          activeEdge = graph->createDirectedEdge(activeNode,toNode,type,false);
        default:
          break;
      };
      lastContainer = lctEdge;
    } else if(name == XML_GRAPH_EDGE_PAIR) {
      activeReverseEdge = graph->createReservePair(activeEdge);
      lastContainer = lctReverseEdge;
    } else if(name == XML_GRAPH_ATTR) {
      readAttribute(list);
    } else if(name == XML_GRAPH_INFO) {
      string name = "", value = "";
      bool hasName = false, hasValue = false;
      for(AttributeList::const_iterator it = list.begin(); it != list.end(); it++) {
        if(it->first == XML_GRAPH_NAME) {
          name = it->second;
          hasName = true;
        } else if (it->first == XML_GRAPH_VALUE) {
          value = it->second;
          hasValue = true;
        }
      }
      if(hasName && hasValue)
        graph->setHeaderInfo(name, value);      
    }
 
  }

  void GraphXmlHandler::endTag(const string &name) {
    if(name == XML_GRAPH_NODE) {
      lastContainer = lctNone;
    } else {
      if(name == XML_GRAPh_EDGE) {
        lastContainer = lctNode;
      } else {
        if(name == XML_GRAPH_EDGE_PAIR) {
          lastContainer = lctEdge;
        } else {
          if(name == XML_GRAPH_ATTR && ( (lastContainer == lctAttributeCompositeEdge) || (lastContainer == lctAttributeCompositeNode) )  ) {
            if(!attrCompositeStack.empty()) {
              if(attrCompositeStack.top().second == 0) {
                attrCompositeStack.pop();
                if(attrCompositeStack.empty()) {
                  if(lastContainer == lctAttributeCompositeEdge)
                    lastContainer = lctEdge;
                  else
                    lastContainer = lctNode;
                }
              } else {
                attrCompositeStack.top().second--;
              }
            } else {
              throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_XML_FORMAT);
            }                          
          }
        }
      }
    }
  }


  void GraphXmlHandler::addAttributeToActiveElement(const Attribute& activeAttribute) {
    if(activeAttribute.getType() != Attribute::atComposite ) {
      if(!attrCompositeStack.empty())
        attrCompositeStack.top().second++;
      switch(lastContainer) {
        case lctNode:
          activeNode.addAttribute(activeAttribute);
          break;
        case lctEdge:
          activeEdge.addAttribute(activeAttribute);
          break;
        case lctReverseEdge:
          activeReverseEdge.addAttribute(activeAttribute);
          break;
        case lctAttributeCompositeEdge:
        case lctAttributeCompositeNode:
          attrCompositeStack.top().first->addAttribute(activeAttribute);
        default:
          break;
      }
    } else {
      switch(lastContainer) {
        case lctNode:
          attrCompositeStack.push(make_pair((AttributeComposite*)&activeNode.addAttribute(activeAttribute), 0));
          break;
        case lctEdge:
          attrCompositeStack.push(make_pair((AttributeComposite*)&activeEdge.addAttribute(activeAttribute), 0));
          break;
        case lctReverseEdge:
          attrCompositeStack.push(make_pair((AttributeComposite*)&activeReverseEdge.addAttribute(activeAttribute), 0));
          break;
        case lctAttributeCompositeEdge:
        case lctAttributeCompositeNode:
          attrCompositeStack.push(make_pair((AttributeComposite*)&(attrCompositeStack.top().first->addAttribute(activeAttribute)), 0));
          break;
        default:
          break;
      }
    }
  }


  void GraphXmlHandler::readAttribute(const AttributeList &list) {

    Attribute::aType type = Attribute::atInt;
    string name;
    string value;
    string context;

    for(AttributeList::const_iterator it = list.begin(); it != list.end(); it++) {
      if(it->first == XML_GRAPH_TYPE) {
        if(it->second == "int")
          type = Attribute::atInt;
        if(it->second == "float")
          type = Attribute::atFloat;
        if(it->second == "string")
          type = Attribute::atString;
        if(it->second == "composite")
          type = Attribute::atComposite;
      }
      if(it->first == XML_GRAPH_NAME) {
        name = it->second;
      }
      if(it->first == XML_GRAPH_VALUE) {
        value = it->second;
      }
      if(it->first == XML_GRAPH_CONTEXT) {
        context = it->second;
      }
    }

    switch(type) {
      case Attribute::atInt:
        {
          AttributeInt activeAttribute = graph->createAttributeInt(name, context, atoi(value.c_str() ) );
          addAttributeToActiveElement(activeAttribute);
          break;
        }
      case Attribute::atFloat:
        {
          AttributeFloat activeAttribute = graph->createAttributeFloat(name, context, (float)atof(value.c_str() ) ) ;
          addAttributeToActiveElement(activeAttribute);
          break;
        }
      case Attribute::atString:
        {
          AttributeString activeAttribute = graph->createAttributeString(name, context, value);
          addAttributeToActiveElement(activeAttribute);
          break;
        }
      case Attribute::atComposite:
        {
          AttributeComposite activeAttribute = graph->createAttributeComposite(name, context);
          addAttributeToActiveElement(activeAttribute);
          if(lastContainer == lctEdge) {
            lastContainer = lctAttributeCompositeEdge;
          } else {
            if(lastContainer == lctNode)
              lastContainer = lctAttributeCompositeNode;
          }
          break;
        }
      case Attribute::atInvalid:
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_FOUND);
        
      default:
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_UNHANDLED_ATTRIBUTE_TYPE_FOUND);
        
    }
  }

}}

