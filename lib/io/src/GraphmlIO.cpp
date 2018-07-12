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

#include <io/inc/GraphmlIO.h>

using namespace std;

namespace columbus {
namespace io {

GraphmlIO::GraphmlIO(const string& filename, const string& graphName, const string& encoding /*= "UTF-8"*/) : output(filename, columbus::io::IOBase::omWrite), edgeCounter(0), titleFont("Dialog"), contentFont("Dialog"), characterWithMultiplier(8), characterHeightMultiplier(16) {
    output.writeXMLDeclaration("1.0", encoding);
    output.writeBeginElement("graphml");
    output.writeAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns/graphml");
    output.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    output.writeAttribute("xmlns:y", "http://www.yworks.com/xml/graphml");
    output.writeAttribute("xsi:schemaLocation", "http://graphml.graphdrawing.org/xmlns http://www.yworks.com/xml/schema/graphml/1.1/ygraphml.xsd");
    output.writeBeginElement("key");
    output.writeAttribute("for", "graphml");
    output.writeAttribute("id", "d0");
    output.writeAttribute("yfiles.type", "resources");
    output.writeEndElement();
    output.writeBeginElement("key");
    output.writeAttribute("for", "node");
    output.writeAttribute("id", "d1");
    output.writeAttribute("yfiles.type", "nodegraphics");
    output.writeEndElement();
    output.writeBeginElement("key");
    output.writeAttribute("for", "edge");
    output.writeAttribute("id", "d2");
    output.writeAttribute("yfiles.type", "edgegraphics");
    output.writeEndElement();
    output.writeBeginElement("graph");
    output.writeAttribute("edgedefault", "directed");
    output.writeAttribute("id", graphName);
}

GraphmlIO::~GraphmlIO() {
    writeEdgeBufferFlush();
    output.writeEndElement();
    output.writeEndElement();
    output.close();
}

void GraphmlIO::writeEdge(const string& fromNodeId, const string& toNodeId, const string& edgeLabel, const float width, const LineStyle lineStyle, const ArrowType sourceArrowType, const ArrowType targetArrowType) {
    output.writeBeginElement("edge");
    output.writeAttribute("id", edgeCounter++);
    output.writeAttribute("source", fromNodeId);
    output.writeAttribute("target", toNodeId);
    output.writeBeginElement("data");
    output.writeAttribute("key", "d2");
    output.writeBeginElement("y:PolyLineEdge");
    output.writeBeginElement("y:LineStyle");
    output.writeAttribute("type", LineStypeToString(lineStyle));
    output.writeAttribute("width", width);
    output.writeEndElement();
    output.writeBeginElement("y:Arrows");
    output.writeAttribute("source", ArrowTypeToString(sourceArrowType));
    output.writeAttribute("target", ArrowTypeToString(targetArrowType));
    output.writeEndElement();
    output.writeBeginElement("y:EdgeLabel");
    output.writeElementContent(edgeLabel);
    output.writeEndElement();
    output.writeEndElement();
    output.writeEndElement();
    output.writeEndElement();
}

void GraphmlIO::writeEdgeBuffer(const string& fromNodeId, const string& toNodeId, const string& edgeLabel, const float width, const LineStyle lineStyle, const ArrowType sourceArrowType, const ArrowType targetArrowType) {
  edge_meta em;
  em.edgeLabel = edgeLabel;
  em.fromNodeId = fromNodeId;
  em.lineStyle = lineStyle;
  em.sourceArrowType = sourceArrowType;
  em.targetArrowType = targetArrowType;
  em.toNodeId = toNodeId;
  em.width = width;
  edgeBuffer.push_back(em);
}

void GraphmlIO::writeEdgeBufferFlush(){
  for(list<edge_meta>::iterator it = edgeBuffer.begin();it != edgeBuffer.end();++it){
    GraphmlIO::writeEdge(it->fromNodeId,it->toNodeId, it->edgeLabel, it->width, it->lineStyle, it->sourceArrowType, it->targetArrowType);
  }
}

void GraphmlIO::writeNode(const string& nodeId, const string& title, const string& content, const string& titleBGColor, const string& groupId, const string& fillColor) {


    int nodeHeight = 0;
    int nodeWidth = (int) title.size();
    int width = 0;


    for (auto c : content) {
        if (c == '\n') {
            nodeHeight++;
            if (nodeWidth < width)
                nodeWidth = width;
            width = 0;
        }
        else
            width++;
    }
    if (nodeWidth < width)
      nodeWidth = width;

    output.writeBeginElement("node");
    if (groupId.compare("") == 0)
        output.writeAttribute("id", nodeId);
    else
        output.writeAttribute("id", groupId + "::" + nodeId);
    output.writeBeginElement("data");
    output.writeAttribute("key", "d1");
    output.writeBeginElement("y:GenericNode");
    output.writeAttribute("configuration", "EntityRelationship_DetailedEntity");

    output.writeBeginElement("y:Geometry");
    output.writeAttribute("height", 50 + nodeHeight * characterHeightMultiplier);
    output.writeAttribute("width", nodeWidth * characterWithMultiplier);
    output.writeEndElement();

    output.writeBeginElement("y:Fill");
    output.writeAttribute("color", fillColor);
    output.writeAttribute("color2", fillColor);
    output.writeAttribute("transparent", false);
    output.writeEndElement();

    output.writeBeginElement("BorderStyle");
    output.writeAttribute("color", "#000000");
    output.writeAttribute("type", "line");
    output.writeAttribute("width", "1.0");
    output.writeEndElement();

    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "center");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("configuration", "DetailedEntity_NameLabelConfiguation");
    output.writeAttribute("fontFamily", titleFont);
    output.writeAttribute("fontSize", "13");
    output.writeAttribute("fontStyle", "bold");
    output.writeAttribute("backgroundColor", titleBGColor);
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("modelName", "internal");
    output.writeAttribute("modelPosition", "t");
    output.writeAttribute("textColor", "#000000");
    output.writeAttribute("visible", "true");
    output.writeElementContent(title);
    output.writeEndElement();

    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "left");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("configuration", "DetailedEntity_AttributeLabelConfiguation");
    output.writeAttribute("fontFamily", contentFont);
    output.writeAttribute("fontSize", "12");
    output.writeAttribute("fontStyle", "plain");
    output.writeAttribute("hasBackgroundColor", "false");
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("modelName", "custom");
    output.writeAttribute("textColor", "#000000");
    output.writeAttribute("height", "48.103515625");
    output.writeAttribute("visible", "true");
    output.writeElementContent(content);

    output.writeBeginElement("y:LabelModel");
    output.writeBeginElement("y:ErdAttributesNodeLabelModel");
    output.writeEndElement();
    output.writeEndElement();
    output.writeBeginElement("y:ModelParameter");
    output.writeBeginElement("y:ErdAttributesNodeLabelModelParameter");
    output.writeEndElement();
    output.writeEndElement();

    output.writeEndElement();

    output.writeBeginElement("y:StyleProperties");
    output.writeBeginElement("y:Property");
    output.writeAttribute("class", "java.lang.Boolean");
    output.writeAttribute("name", "shadow");
    output.writeAttribute("value", "true");
    output.writeEndElement();
    output.writeEndElement();
    output.writeEndElement();
    output.writeEndElement();
    output.writeEndElement();
}

void GraphmlIO::writeCGNode(const string& nodeId, const string& title, const string& titleBGColor, const string& textColor, const string& shape) {

    int nodeHeight = 0;
    int nodeWidth = 0;
    int width = 0;

    for (auto c : title) {
        if (c == '\n') {
            nodeHeight++;
            if (nodeWidth < width)
                nodeWidth = width;
            width = 0;
        }
        else
            width++;
    }

    if (nodeHeight == 0)
        nodeWidth = width;

    output.writeBeginElement("node");
    output.writeAttribute("id", nodeId);
    output.writeBeginElement("data");
    output.writeAttribute("key", "d1");
    output.writeBeginElement("y:ShapeNode");

    output.writeBeginElement("y:Geometry");
    output.writeAttribute("height", 40 + nodeHeight * characterHeightMultiplier);
    output.writeAttribute("width", nodeWidth * characterWithMultiplier + 20);
    output.writeEndElement();

    output.writeBeginElement("y:Fill");
    output.writeAttribute("color", titleBGColor);
    output.writeAttribute("transparent", "false");
    output.writeEndElement();

    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "center");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("fontFamily", titleFont);
    output.writeAttribute("fontSize", "13");
    output.writeAttribute("fontStyle", "bold");
    output.writeAttribute("backgroundColor", titleBGColor);
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("modelName", "internal");
    output.writeAttribute("modelPosition", "c");
    output.writeAttribute("textColor", textColor);
    output.writeAttribute("visible", "true");
    output.writeElementContent(title);
    output.writeEndElement();

    output.writeBeginElement("y:Shape");
    output.writeAttribute("type", shape);
    output.writeEndElement();

    output.writeEndElement();
    output.writeEndElement();
    output.writeEndElement();
}

void GraphmlIO::writeGroupBegin(const string& groupId, const string& groupName, const string& fillColor) {
    const int nodeWidth = (int) groupName.size();

    output.writeBeginElement("node");
    output.writeAttribute("id", groupId);
    output.writeAttribute("yfiles.foldertype", "group");

    output.writeBeginElement("data");
    output.writeAttribute("key", "d1");


    output.writeBeginElement("y:ProxyAutoBoundsNode");
    output.writeBeginElement("y:Realizers");
    output.writeAttribute("active", "0");
    output.writeBeginElement("y:GroupNode");
    output.writeBeginElement("y:Geometry");
    output.writeAttribute("height", "200");
    output.writeAttribute("width", nodeWidth);
    output.writeEndElement();

    output.writeBeginElement("y:Fill");
    output.writeAttribute("color", fillColor);
    output.writeAttribute("transparent", "false");
    output.writeEndElement();

    output.writeBeginElement("y:BorderStyle");
    output.writeAttribute("color", "#000000");
    output.writeAttribute("type", "line");
    output.writeAttribute("width", "1.0");
    output.writeEndElement();

    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "center");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("backgroundColor", "#B7B69E");
    output.writeAttribute("borderDistance", "0.0");
    output.writeAttribute("fontFamily", "Dialog");
    output.writeAttribute("fontSize", "13");
    output.writeAttribute("fontStyle", "plain");
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("height", "22");
    output.writeAttribute("modelName", "internal");
    output.writeAttribute("modelPosition", "t");
    output.writeAttribute("textColor", "#000000");
    output.writeAttribute("visible", "true");
    output.writeElementContent(groupName);
    output.writeEndElement();

    output.writeBeginElement("y:Shape");
    output.writeAttribute("type", "rectangle");
    output.writeEndElement();

    output.writeBeginElement("y:State");
    output.writeAttribute("closed", "false");
    output.writeAttribute("closedHeight", "50.0");
    output.writeAttribute("closedWidth", "50.0");
    output.writeAttribute("innerGraphDisplayEnabled", "false");
    output.writeEndElement();

    output.writeEndElement();
    output.writeEndElement();
    output.writeEndElement();


    output.writeEndElement(); //data

    output.writeBeginElement("graph");
    output.writeAttribute("edgedefault", "directed");
    output.writeAttribute("id", groupId + ":");
}

void GraphmlIO::writeGroupEnd() {
    output.writeEndElement();

    output.writeEndElement();
}

void GraphmlIO::writeGroupNodeBegin(const string& nodeId, const string& title, const string& content, const string& titleBGColor, const string& groupId, const string& fillColor) {
    
    int nodeHeight = 0;
    int nodeWidth = (int) title.size();
    int width = 0;


    for (auto c : content) {
        if (c == '\n') {
            nodeHeight++;
            if (nodeWidth < width)
                nodeWidth = width;
            width = 0;
        }
        else
            width++;
    }
    if (nodeWidth < width)
        nodeWidth = width;

    output.writeBeginElement("node");
    if (groupId.compare("") == 0)
        output.writeAttribute("id", nodeId);
    else
        output.writeAttribute("id", groupId + "::" + nodeId);
    output.writeAttribute("yfiles.foldertype", "group");

    output.writeBeginElement("data");
    output.writeAttribute("key", "d1");
    
    output.writeBeginElement("y:ProxyAutoBoundsNode");
    output.writeBeginElement("y:Realizers");
    output.writeAttribute("active", "0");
    
    output.writeBeginElement("y:GroupNode");
    output.writeAttribute("configuration", "EntityRelationship_DetailedEntity");

    output.writeBeginElement("y:Geometry");
    output.writeAttribute("height", 50 + nodeHeight * characterHeightMultiplier);
    output.writeAttribute("width", nodeWidth * characterWithMultiplier);
    output.writeEndElement();

    output.writeBeginElement("y:Fill");
    output.writeAttribute("color", titleBGColor);
    output.writeAttribute("transparent", "false");
    output.writeEndElement();

    output.writeBeginElement("y:BorderStyle");
    output.writeAttribute("color", "#000000");
    output.writeAttribute("type", "line");
    output.writeAttribute("width", "1.0");
    output.writeEndElement();

    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "center");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("configuration", "DetailedEntity_NameLabelConfiguation");
    output.writeAttribute("fontFamily", titleFont);
    output.writeAttribute("fontSize", "13");
    output.writeAttribute("fontStyle", "bold");
    output.writeAttribute("hasBackgroundColor", "false");
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("modelName", "internal");
    output.writeAttribute("modelPosition", "t");
    output.writeAttribute("textColor", "#000000");
    output.writeAttribute("visible", "true");
    output.writeElementContent(title);
    output.writeEndElement();


    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "left");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("configuration", "DetailedEntity_AttributeLabelConfiguation");
    output.writeAttribute("fontFamily", contentFont);
    output.writeAttribute("fontSize", "12");
    output.writeAttribute("fontStyle", "plain");
    output.writeAttribute("backgroundColor", fillColor);
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("modelName", "custom");
    output.writeAttribute("textColor", "#000000");
    output.writeAttribute("height", "48.103515625");
    output.writeAttribute("visible", "true");
    output.writeElementContent(content);

    output.writeBeginElement("y:LabelModel");
    output.writeBeginElement("y:ErdAttributesNodeLabelModel");
    output.writeEndElement();
    output.writeEndElement();
    output.writeBeginElement("y:ModelParameter");
    output.writeBeginElement("y:ErdAttributesNodeLabelModelParameter");
    output.writeEndElement();
    output.writeEndElement();

    output.writeEndElement();

    output.writeBeginElement("y:Shape");
    output.writeAttribute("type", "rectangle");
    output.writeEndElement();

    output.writeBeginElement("y:State");
    output.writeAttribute("closed", "false");
    output.writeAttribute("innerGraphDisplayEnabled", "false");
    output.writeEndElement();

    output.writeEndElement();//groupnode
    
    output.writeBeginElement("y:GroupNode");
    

    output.writeBeginElement("y:Geometry");
    output.writeAttribute("height", 50 + nodeHeight * characterHeightMultiplier);
    output.writeAttribute("width", nodeWidth * characterWithMultiplier);
    output.writeEndElement();

    output.writeBeginElement("y:Fill");
    output.writeAttribute("color", titleBGColor);
    output.writeAttribute("transparent", "false");
    output.writeEndElement();

    output.writeBeginElement("y:BorderStyle");
    output.writeAttribute("color", "#000000");
    output.writeAttribute("type", "line");
    output.writeAttribute("width", "1.0");
    output.writeEndElement();

    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "center");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("configuration", "DetailedEntity_NameLabelConfiguation");
    output.writeAttribute("fontFamily", titleFont);
    output.writeAttribute("fontSize", "13");
    output.writeAttribute("fontStyle", "bold");
    output.writeAttribute("hasBackgroundColor", "false");
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("modelName", "internal");
    output.writeAttribute("modelPosition", "t");
    output.writeAttribute("textColor", "#000000");
    output.writeAttribute("visible", "true");
    output.writeElementContent(title);
    output.writeEndElement();


    output.writeBeginElement("y:NodeLabel");
    output.writeAttribute("alignment", "left");
    output.writeAttribute("autoSizePolicy", "content");
    output.writeAttribute("configuration", "DetailedEntity_AttributeLabelConfiguation");
    output.writeAttribute("fontFamily", contentFont);
    output.writeAttribute("fontSize", "12");
    output.writeAttribute("fontStyle", "plain");
    output.writeAttribute("backgroundColor", fillColor);
    output.writeAttribute("hasLineColor", "false");
    output.writeAttribute("modelName", "custom");
    output.writeAttribute("textColor", "#000000");
    output.writeAttribute("height", "48.103515625");
    output.writeAttribute("visible", "true");
    output.writeElementContent(content);

    output.writeBeginElement("y:LabelModel");
    output.writeBeginElement("y:ErdAttributesNodeLabelModel");
    output.writeEndElement();
    output.writeEndElement();
    output.writeBeginElement("y:ModelParameter");
    output.writeBeginElement("y:ErdAttributesNodeLabelModelParameter");
    output.writeEndElement();
    output.writeEndElement();

    output.writeEndElement();

    output.writeBeginElement("y:Shape");
    output.writeAttribute("type", "rectangle");
    output.writeEndElement();

    output.writeBeginElement("y:State");
    output.writeAttribute("closed", "true");
    output.writeAttribute("innerGraphDisplayEnabled", "false");
    output.writeEndElement();

    output.writeEndElement();// groupnode

    output.writeEndElement();
    output.writeEndElement();


    output.writeEndElement(); //data

    output.writeBeginElement("graph");
    output.writeAttribute("edgedefault", "directed");
    output.writeAttribute("id", nodeId + ":");
}

void GraphmlIO::writeGroupNodeEnd() {
    output.writeEndElement();

    output.writeEndElement();
}

void GraphmlIO::setNodeTitleFamily(const string& font) {
    titleFont = font;
}

void GraphmlIO::setNodeContentFamily(const string& font) {
    contentFont = font;
}

void GraphmlIO::setCharacterWithMultiplier(const int multiplier) {
    characterWithMultiplier = multiplier;
}

void GraphmlIO::setCharacterHeightMultiplier(const int multiplier) {
    characterHeightMultiplier = multiplier;
}

const char* GraphmlIO::ArrowTypeToString(const ArrowType arrowType) {
    switch (arrowType) {
        case at_standard:
            return "standard";
        case at_delta:
            return "delta";
        case at_diamond:
            return "diamond";
        case at_white_diamond:
            return "white_diamond";
        case at_white_delta:
            return "white_delta";
        case at_none:
            return "none";
        case at_plain:
            return "plain";
        case at_concave:
            return "concave";
        case at_convex:
            return "convex";
        case at_circle:
            return "circle";
        case at_dash:
            return "dash";
        case at_transparent_circle:
            return "transparent_circle";
        case at_skewed_dash:
            return "skewed_dash";
        case at_t_shape:
            return "t_shape";
        default:
            return "UNKOWN ARROW TYPE";
    }
}

const char* GraphmlIO::LineStypeToString(const LineStyle lineStyle) {
    switch (lineStyle) {
        case ls_line:
            return "line";
        case ls_dashed:
            return "dashed";
        case ls_dotted:
            return "dotted";
        case ls_dashed_dotted:
            return "dashed_dotted";
        default:
            return "UNKNOWN LINE STYLE";
    }
}

}
}
