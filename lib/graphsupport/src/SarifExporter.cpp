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

#include "io/inc/IO.h"
#include "io/inc/messages.h"
#include "../inc/GraphConstants.h"
#include "../inc/SarifExporter.h"
#include "../inc/SarifWriter.h"
#include "../inc/messages.h"
#include "jsoncpp/inc/json.h"
#include <algorithm>
#include <Exception.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace columbus::graph;
using namespace columbus::graphsupport::graphconstants;
using namespace std;
using namespace columbus::io;

namespace {
    // SARIF names
    const string SARIF_NAME_VERSION = "version";
    const string SARIF_NAME_SCHEMA = "$schema";
    const string SARIF_NAME_RUNS = "runs";
    const string SARIF_NAME_TOOL = "tool";
    const string SARIF_NAME_DRIVER = "driver";
    const string SARIF_NAME_NAME = "name";
    const string SARIF_NAME_LANG = "language";
    const string SARIF_NAME_RESULTS = "results";
    const string SARIF_NAME_RULES = "rules";
    const string SARIF_NAME_ID = "id";
    const string SARIF_NAME_KIND = "kind";
    const string SARIF_NAME_KINDS = "kinds";
    const string SARIF_NAME_LEVEL = "level";
    const string SARIF_NAME_RANK = "rank";
    const string SARIF_NAME_HELPURI = "helpUri";
    const string SARIF_NAME_LOCATIONS = "locations";
    const string SARIF_NAME_THREADFLOWLOCATION = "location";
    const string SARIF_NAME_OCCURED = "occurrenceCount";
    const string SARIF_NAME_PHLOCATION = "physicalLocation";
    const string SARIF_NAME_ARTLOCATION = "artifactLocation";
    const string SARIF_NAME_URI = "uri";
    const string SARIF_NAME_REGION = "region";
    const string SARIF_NAME_LINE = "startLine";
    const string SARIF_NAME_ENDLINE = "endLine";
    const string SARIF_NAME_COLUMN = "startColumn";
    const string SARIF_NAME_ENDCOLUMN = "endColumn";
    const string SARIF_NAME_CODEFLOWS = "codeFlows";
    const string SARIF_NAME_NESTINGLEVEL = "nestingLevel"; 
    const string SARIF_NAME_EXECUTIONORDER = "executionOrder";
    const string SARIF_NAME_THREADFLOWS = "threadFlows";
    const string SARIF_NAME_TEXT = "text";
    const string SARIF_NAME_MARKDOWN = "markdown";
    const string SARIF_NAME_MESSAGE = "message";
    const string SARIF_NAME_SHORTDESC = "shortDescription";
    const string SARIF_NAME_FULLDESC = "fullDescription";
    const string SARIF_NAME_DEFCONF = "defaultConfiguration";
    const string SARIF_NAME_RELATIONS = "relationships";
    const string SARIF_NAME_TARGET = "target";
    const string SARIF_NAME_RULEINDEX = "ruleIndex";
    const string SARIF_NAME_ENABLED = "enabled";
    const string SARIF_NAME_PROPERTIES = "properties";

    //Sarif values
    //versions available on https://github.com/oasis-tcs/sarif-spec/tree/master/Schemata
    const string SARIF_VALUE_VERSION = "2.1.0";
    const string SARIF_VALUE_SCHEMA  = "http://json.schemastore.org/sarif-2.1.0-rtm.1";
    const string SARIF_VALUE_NAME    = "OpenStaticAnalyzer";
    const string SARIF_VALUE_LANG    = "en-US";
    namespace SARIF_VALUE_PRIORITY {
        const string none    = "none";
        const string note    = "note";
        const string warning = "warning";
        const string error   = "error";
    };

    const string CloneClassIds[] = {
        "CA_warning_CloneClass",
        "CCO_warning_CloneClass",
        "CEE_warning_CloneClass",
        "CEG_warning_CloneClass",
        "CE_warning_CloneClass",
        "CI_warning_CloneClass",
        "CLLOC_warning_CloneClass",
        "CR_warning_CloneClass",
        "CV_warning_CloneClass",
        "NCR_warning_CloneClass"
    };
    
    const string customCloneClassId   = "All_CloneClasses";
    const string customCloneClassName = "All CloneClasses";
    
    // because OpenStaticAnalyzer-Linux generates a path starting with /, on the other hand windows generates a path starting with the drive name, e.g. C:
    const string uriFile = 
    #ifdef __linux__
        "file://";
    #else
        "file:///";
    #endif

    /**
    * \brief basic IO class for SARIF
    */
    class SarifIO : public virtual columbus::io::IOBase {
    public:
        SarifIO() {};
        ~SarifIO() {};
        
        void writeData(const string& data) {
            if (!isOpen()) throw columbus::IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_NOT_OPEN);
            else *stream << data;
        }
    };

    /**
    * \brief checks if the given node has the required attribute for a sarif field, similar to graph::Attribute::AttributeIterator
    * \param node [in]
    * \param atype [in], the possible attributes Type
    * \param name [in], the name of the attribute of the given node
    * \param context [in], the context of the attribute of the given node
    * \return an Attribute reference
    */
    const Attribute &componentHasTheRequiredAttribute(const Node &node, const Attribute::aType &aType, const string &name, const string &context) {
        Attribute::AttributeIterator attrItr = node.findAttribute(aType, name, context);
        if (attrItr.hasNext()) return attrItr.next();
        const string type = aType == 0 ? "int" : aType == 1 ? "float" : aType == 2 ? "string" : aType == 3 ? "composite" : "invalid";
        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_SARIF_OUT_OF_DATE(node.getUID(), type, name, context));
    }

    /**
    * \brief checks if the given composite attribute has the required attribute for a sarif field, similar to graph::Attribute::AttributeIterator
    * \param attr [in]
    * \param atype [in], the possible attributes Type
    * \param name [in], the name of the attribute of the given node
    * \param context [in], the context of the attribute of the given node
    * \return an Attribute reference
    */
    const Attribute &componentHasTheRequiredAttribute(AttributeComposite &attr, const Attribute::aType &aType, const string &name, const string &context){
        Attribute::AttributeIterator attrItr = attr.findAttribute(aType, name, context);
        if (attrItr.hasNext()) return attrItr.next();
        const string type =  aType == 0 ? "int" : aType == 1 ? "float" : aType == 2 ? "string" : aType == 3 ? "composite" : "invalid";
        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_SARIF_OUT_OF_DATE("AttributeComposite", type, name, context));
    }

    /**
    * \brief checks if the given composite attribute has the non-required attribute for a sarif field, used to determine the existence of the attribute
    * \param attr [in]
    * \param atype [in], the possible attributes Type
    * \param name [in], the name of the attribute of the given node
    * \param context [in], the context of the attribute of the given node
    * \return true, if the Non-required attribute exists, false otherwise
    */
    bool componentHasNonRequiredAttribute(AttributeComposite &attr, const Attribute::aType &aType, const string &name, const string &context) {
        return attr.findAttribute(aType, name, context).hasNext();
    }

    /**
    * \brief checks if the given node has the non-required attribute for a sarif field, used to determine the existence of the attribute
    * \param attr [in]
    * \param atype [in], the possible attributes Type
    * \param name [in], the name of the attribute of the given node
    * \param context [in], the context of the attribute of the given node
    * \return true, if the Non-required attribute exists, false otherwise
    */
    bool componentHasNonRequiredAttribute(const Node &attr, const Attribute::aType &aType, const string &name, const string &context) {
        return attr.findAttribute(aType, name, context).hasNext();
    }

    /**
    * \brief convert Node/AttributeComposite->Location to Sarif->Location
    * \param attrComp [in], reference to AttributeComposite to which will be converted
    * \param location [in-out], refernce to Json::Value where the converted SARIF location will be stored
    */
    void writeLocation(AttributeComposite& attrComp, Json::Value &location) {
        const Attribute &path = componentHasTheRequiredAttribute(attrComp, Attribute::atString, ATTR_PATH, "");
        const Attribute &lineBegin = componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_LINE, "");
        const Attribute &lineEnd = componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_ENDLINE, "");
        const Attribute &columnBegin = componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_COLUMN, "");
        const Attribute &columnEnd = componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_ENDCOLUMN, "");
        string pathTemp = uriFile + path.getStringValue();
        replace(pathTemp.begin(), pathTemp.end(), '\\', '/');

        string lineBeginValue = lineBegin.getStringValue();
        string columnBeginValue = columnBegin.getStringValue();
        string lineEndValue = lineEnd.getStringValue();
        string columnEndValue = columnEnd.getStringValue();

        // negative starting/ending value to 0, because sarif line/column number cannot have negative number
        if (stoi(lineBeginValue) <= 0) {
            lineBeginValue = "1";
        }
        if (stoi(lineEndValue) <= 0) {
            lineEndValue = lineBeginValue;
        }
        if (stoi(columnBeginValue) <= 0) {
            columnBeginValue = "1";
        }
        if (stoi(columnEndValue) <= 0) {
            columnEndValue = columnBeginValue;
        }

        location[SARIF_NAME_PHLOCATION][SARIF_NAME_ARTLOCATION][SARIF_NAME_URI] = pathTemp;
        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_LINE] = stoi(lineBeginValue);
        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_COLUMN] = stoi(columnBeginValue);
        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_ENDLINE] = stoi(lineEndValue);
        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_ENDCOLUMN] = stoi(columnEndValue);
    }

    bool replace(string& str, const string from, const string end, const string to) {
        size_t startPos = str.find(from);
        if(startPos == std::string::npos)
            return false;
        size_t endPos = str.find(end, startPos + 2) + 1;
        str.replace(startPos, endPos - startPos, to);
        return true;
    }
    
    /**
    * \brief convert basic html text to Github Flavored Markdown
    * \param sourceHtml [in-out], reference to source text, also the output for GFM
    */
    void htmlToGFM(string &sourceHtml, const string &asg){
        const string htmlTags[] = {
            "<p>" , "</p>",
            "<b>", "</b>", "<strong>", "</strong>",
            "<i>" , "</i>", "<em>" , "</em>",
            "<ul>" , "</ul>", "<li>", "</li>",
            "<div>" , "<span>" , "</div>" , "</span>" , "</code>" , "</pre>",
            "&quot;" , "&lt;" , "&gt;", "\n", "\\n", "&#39;", "&amp;"
        }, GFMTags[] = {
            "", "\n",
            "**", "**", "**", "**",
            "*", "*", "*", "*",
            "\n", "", "*   ", "\n",
            "", "", "", "", "`", "```\n",
            "\"", "<" , ">", "\n" , "\n", "'", "&"
        };
        int size = 27;

        // Html links to Markdown links
        while(sourceHtml.find("<a href=\"",0) != std::string::npos){
            std::size_t positionStart = sourceHtml.find("<a href=\"",0);
            std::size_t saveStart = positionStart;
            positionStart += 9;
            std::size_t positionEnd = sourceHtml.find("\"", positionStart);
            string linkHref = "";
            //get the link url from the <a> html tag
            while(positionStart <= positionEnd - 1){
                linkHref += sourceHtml.at(positionStart);
                positionStart++;
            }
            
            positionStart = sourceHtml.find(">", positionEnd) + 1;
            positionEnd = sourceHtml.find("</a>", positionStart) - 1;
            string linkText = "";
            //get the text from the <a> html tag
            while(positionStart <= positionEnd){
                linkText += sourceHtml.at(positionStart);
                positionStart++;
            }
            string link = "[" + linkText + "](" + linkHref + ")";
            sourceHtml.replace(saveStart, positionEnd - saveStart + 5, link);
        }

        //simple tags that doesnt have class, id, data, ... attributes
        for (int i = 0; i < size; i++){
            boost::replace_all(sourceHtml, htmlTags[i], GFMTags[i]);
        }
        //code tags that have class, id, data, ... attributes
        while (replace(sourceHtml, "<pre", ">", "```"));
        while (replace(sourceHtml, "<code", ">", "`"));
        //formatting the markdown code ```
        boost::replace_all(sourceHtml, "````", "```"); // this happens if <pre><code>... exist
        boost::replace_first(sourceHtml, "```", "\n```" + asg + "\n");
        boost::replace_last(sourceHtml, "```", "\n```\n");
        // every remainig <> tag
        while (replace(sourceHtml, "<", ">", ""));

        //Getting rid of excess line breaks
        boost::replace_all(sourceHtml, "\n\n\n", "\n\n"),
        boost::replace_all(sourceHtml, "\n\n\n\n", "\n\n"),
        boost::replace_tail(sourceHtml, 1, "");
    }
}

namespace columbus {
    namespace graphsupport {

        void exportToSarif(Graph & graph, const std::string & filename, const string & sarifSeverityLevel)
        {
            const string &asg = graph.getHeaderInfo("asg");
            bool sarifSeverityLevelVal[] = {
                sarifSeverityLevel.find('1') != std::string::npos,
                sarifSeverityLevel.find('2') != std::string::npos,
                sarifSeverityLevel.find('3') != std::string::npos,
                sarifSeverityLevel.find('4') != std::string::npos,
                sarifSeverityLevel.find('5') != std::string::npos,
                sarifSeverityLevel.find('c') != std::string::npos || sarifSeverityLevel.find('C') != std::string::npos
            };

            Json::Value root(Json::objectValue);
            root[SARIF_NAME_VERSION] = SARIF_VALUE_VERSION;
            root[SARIF_NAME_SCHEMA] = SARIF_VALUE_SCHEMA;
            root[SARIF_NAME_RUNS] = Json::arrayValue;
            root[SARIF_NAME_RUNS][0] = Json::objectValue;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_NAME] = SARIF_VALUE_NAME;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_LANG] = SARIF_VALUE_LANG;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_RESULTS] = Json::arrayValue;

            //Everything related to collect,write and store the rules from the graph
            map<string, int> ruleIndexesInJson;
            {
                Node::NodeIterator ruleNodes = graph.findNodes(NTYPE_RUL_METRIC);
                root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_RULES] = Json::arrayValue;
                int ruleCounter = 0;
                boost::filesystem::path full_path(boost::filesystem::current_path().parent_path());
                full_path /= "UsersGuide.html";
                bool userGuideExist = boost::filesystem::exists(full_path);
                string fullPathString = full_path.string();
                fullPathString = uriFile + fullPathString;

                replace(fullPathString.begin(), fullPathString.end(), '\\', '/');

                while (ruleNodes.hasNext()) {
                    const Node &ruleNode = ruleNodes.next();
                    const string &description = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_DESCRIPTION, CONTEXT_RUL).getStringValue();
                    const bool ruleParent = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_WARNING, CONTEXT_RUL).getStringValue() == "true";
                    
                    Json::Value rule(Json::objectValue);
                    rule[SARIF_NAME_ID] = ruleNode.getUID();
                    rule[SARIF_NAME_NAME] = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_DISPLAYNAME, CONTEXT_RUL).getStringValue();
                    if(description != ""){
                        rule[SARIF_NAME_SHORTDESC][SARIF_NAME_TEXT] = description;
                    }

                    if(componentHasNonRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_HELPTEXT, CONTEXT_RUL)){
                        const string &helpText = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_HELPTEXT, CONTEXT_RUL).getStringValue();
                        string GFMText = helpText;
                        rule[SARIF_NAME_FULLDESC][SARIF_NAME_TEXT] = helpText;
                        htmlToGFM(GFMText, asg);
                        rule[SARIF_NAME_FULLDESC][SARIF_NAME_MARKDOWN] = GFMText;
                    }

                    rule[SARIF_NAME_DEFCONF][SARIF_NAME_ENABLED] = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_ENABLED, CONTEXT_RUL).getStringValue() == "true";

                    if (ruleParent) {
                        AttributeComposite &ruleAttribute = (AttributeComposite&)componentHasTheRequiredAttribute(ruleNode, Attribute::atComposite, ATTR_RUL_SETTINGS, CONTEXT_RUL);
                        
                        if (componentHasNonRequiredAttribute(ruleAttribute, Attribute::atString, ATTR_RUL_PRIORITY, CONTEXT_RUL)) {
                            string priority = componentHasTheRequiredAttribute(ruleAttribute, Attribute::atString, ATTR_RUL_PRIORITY, CONTEXT_RUL).getStringValue();
                            int rank = (priority == "Info" ? 0 : (priority == "Minor" ? 1 : (priority == "Major" ? 2 : (priority == "Critical" ? 3 : 4))));
                                
                            // if the severity of the result is not required to be converted, then the rule will not be saved
                            AttributeComposite& attrCalc = (AttributeComposite&)componentHasTheRequiredAttribute(ruleNode, Attribute::atComposite, ATTR_RUL_CALCULATED, CONTEXT_RUL);
                            if (componentHasNonRequiredAttribute(attrCalc, Attribute::atString, ATTR_RUL_CALCULATEDFOR, CONTEXT_RUL)) {
                                string calcVal = componentHasTheRequiredAttribute(attrCalc, Attribute::atString, ATTR_RUL_CALCULATEDFOR, CONTEXT_RUL).getStringValue();

                                if (calcVal == NTYPE_DCF_CLONEINSTANCE || calcVal == NTYPE_DCF_CLONECLASS) {
                                    rank = 5;
                                }
                            }
                            if(!sarifSeverityLevelVal[rank]) continue;

                            priority = (priority == "Info") ? SARIF_VALUE_PRIORITY::note : (priority == "Minor" || priority == "Major") ? SARIF_VALUE_PRIORITY::warning : SARIF_VALUE_PRIORITY::error;
                            rule[SARIF_NAME_DEFCONF][SARIF_NAME_LEVEL] = priority;
                            rule[SARIF_NAME_DEFCONF][SARIF_NAME_RANK] = rank;
                        }

                        if (componentHasNonRequiredAttribute(ruleAttribute, Attribute::atString, "metricName", CONTEXT_RUL)) {
                            const string &parentName = componentHasTheRequiredAttribute(ruleAttribute, Attribute::atString, "metricName", CONTEXT_RUL).getStringValue();
                            rule[SARIF_NAME_RELATIONS] = Json::arrayValue;
                            rule[SARIF_NAME_RELATIONS][0][SARIF_NAME_TARGET][SARIF_NAME_ID] = parentName;
                            rule[SARIF_NAME_RELATIONS][0][SARIF_NAME_KINDS][0] = "subset";

                            if (userGuideExist) {
                                rule[SARIF_NAME_HELPURI] = fullPathString + "#" + parentName;
                            }
                        }
                        else{
                            if (userGuideExist) {
                                rule[SARIF_NAME_HELPURI] = fullPathString + "#" + ruleNode.getUID();
                            }
                        }

                    }
                    else {
                        continue;
                    }
                    if (componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_GROUPTYPE, CONTEXT_RUL).getStringValue() != "summarized" && !rule[SARIF_NAME_DEFCONF][SARIF_NAME_RANK].empty() && !rule[SARIF_NAME_DEFCONF][SARIF_NAME_LEVEL].empty() && !rule[SARIF_NAME_DEFCONF][SARIF_NAME_ENABLED].empty() && rule[SARIF_NAME_DEFCONF][SARIF_NAME_ENABLED].asString() == "true") {
                        root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_RULES][ruleCounter] = Json::Value(rule);
                        ruleCounter++;
                    }
                }
                //If clone class is to be converted we add a custom (new) Rule, called customCloneClassId
                if (sarifSeverityLevelVal[5]) {
                    Json::Value rule(Json::objectValue);
                    rule[SARIF_NAME_ID] = customCloneClassId;
                    rule[SARIF_NAME_NAME] = customCloneClassName;
                    rule[SARIF_NAME_FULLDESC][SARIF_NAME_TEXT] = "Clone Class";
                    rule[SARIF_NAME_DEFCONF][SARIF_NAME_ENABLED] = true;
                    rule[SARIF_NAME_DEFCONF][SARIF_NAME_LEVEL] = "note";
                    rule[SARIF_NAME_DEFCONF][SARIF_NAME_RANK] = 5;

                    root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_RULES][ruleCounter] = Json::Value(rule);
                    ruleCounter++;
                }

                //soft references to the rules, required to do this way, because this type of json formatter organize the elements by its name, and not by the order it was insterted
                for (unsigned int index = 0; index < root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_RULES].size(); index++) {
                    ruleIndexesInJson.insert(pair<string, int>(root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_RULES][index][SARIF_NAME_ID].asString(), index));
                }
            }


            Node::NodeTypeSet types;

            // adding every type of node, that possibly can have warning in it
            {
                types.insert(NTYPE_LIM_COMPONENT);
                types.insert(NTYPE_LIM_MODULE);
                types.insert(NTYPE_LIM_NAMESPACE);
                types.insert(NTYPE_LIM_PACKAGE);
                types.insert(NTYPE_LIM_ROOT);
                types.insert(NTYPE_LIM_CLASS);
                types.insert(NTYPE_LIM_STRUCTURE);
                types.insert(NTYPE_LIM_UNION);
                types.insert(NTYPE_LIM_INTERFACE);
                types.insert(NTYPE_LIM_ENUM);
                types.insert(NTYPE_LIM_ANNOTATION);
                types.insert(NTYPE_LIM_SOURCEFILE);
                types.insert(NTYPE_LIM_CLASSDEF);
                types.insert(NTYPE_LIM_FUNCTION);
                types.insert(NTYPE_LIM_METHOD);
                types.insert(NTYPE_LIM_FUNCTIONMEMBER);
                types.insert(NTYPE_LIM_PROCEDURE);
                types.insert(NTYPE_LIM_FUNCTIONDEF);
                types.insert(NTYPE_LIM_METHODDEF);
                types.insert(NTYPE_LIM_ATTRIBUTE);
                types.insert(NTYPE_LIM_FILE);
                types.insert(NTYPE_DCF_CLONECLASS);
                types.insert(NTYPE_RPG_SYSTEM);
                types.insert(NTYPE_RPG_PROGRAM);
                types.insert(NTYPE_RPG_MODULE);
                types.insert(NTYPE_RPG_PROCEDURE);
                types.insert(NTYPE_RPG_SUBROUTINE); 
                types.insert(NTYPE_DCF_CLONEINSTANCE);
            }

            Node::NodeIterator allNodes = graph.findNodes(types);
            int resultCounter = 0;

            // Goes through all the Nodes that has one of the Node type declared above
            while (allNodes.hasNext()) {
                Node node = allNodes.next();
                string  name = node.getUID();
                Node::NodeType type = node.getType();
                AttributeComposite::AttributeIterator attr = node.findAttributeByContext(CONTEXT_WARNING);

                // Warning handling (simple warnings, CloneClass warnings, CloneInstance warning)
                while (attr.hasNext()) {
                    AttributeComposite& attrComp = (AttributeComposite&)attr.next();
                    const string &warningID = attrComp.getName();
                    Json::Value result = Json::objectValue;

                    // if the rule doesn't exist (becuase its not required by severity switch), then the current result will not be examined and will not be saved
                    if (ruleIndexesInJson.find(warningID) == ruleIndexesInJson.end()) continue;
                      
                    //linking the rule object index
                    result[SARIF_NAME_RULEINDEX] = ruleIndexesInJson.find(warningID)->second;
                    result[SARIF_NAME_KIND] = "pass";
                    result[SARIF_NAME_LOCATIONS] = Json::arrayValue;

                    // MultiLocation Start
                    {
                        Json::Value location(Json::objectValue);
                        int locationCounter = 0;
                        // multiple location for the same result
                        if (type == NTYPE_DCF_CLONECLASS) {
                            Edge::EdgeIterator edges = node.findOutEdges(Edge::EdgeType(ETYPE_DCF_CLONETREE, Edge::edtDirectional));

                            while (edges.hasNext()) {
                                Node edgeNode = edges.next().getToNode();
                                if (componentHasNonRequiredAttribute(edgeNode, Attribute::atComposite, ATTR_POSITION, CONTEXT_ATTRIBUTE)) {
                                    AttributeComposite& attrComp = (AttributeComposite&)(edgeNode.findAttribute(Attribute::atComposite, ATTR_POSITION, CONTEXT_ATTRIBUTE).next());
                                    writeLocation(attrComp, location);

                                    result[SARIF_NAME_LOCATIONS][locationCounter] = Json::Value(location);
                                    locationCounter++;
                                }
                            }
                        }
                        // only one location for the result / not a cloneclass
                        else {
                            writeLocation(attrComp, location);
                            result[SARIF_NAME_LOCATIONS][locationCounter] = Json::Value(location);
                            locationCounter++;
                        }
                        if (locationCounter == 0) continue; // if there is a cloneclass that has no valid instance (eg. the Instance is cstDisappearing)
                        result[SARIF_NAME_OCCURED] = locationCounter;
                    }
                    const string &messageTextTemp = componentHasTheRequiredAttribute(attrComp, Attribute::atString, ATTR_WARNINGTEXT, "").getStringValue();
                    
                    // if the node has traceCallBack attribute
                    if (componentHasNonRequiredAttribute(attrComp, Attribute::atComposite, ATTR_EXTRAINFO, CONTEXT_TRACE)) {
                        AttributeComposite& attrExtraInfo = (AttributeComposite&)componentHasTheRequiredAttribute(attrComp, Attribute::atComposite, ATTR_EXTRAINFO, CONTEXT_TRACE);
                        AttributeComposite::AttributeIterator attrItr = attrExtraInfo.findAttribute(Attribute::atComposite, ATTR_SOURCELINK, "");
                        int executionOrder = 0;

                        while (attrItr.hasNext()) {
                            AttributeComposite& attrTraceComp = (AttributeComposite&)attrItr.next();
                            Json::Value location(Json::objectValue);

                            writeLocation(attrTraceComp, location);
                            
                            result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_EXECUTIONORDER] = executionOrder;
                            result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_THREADFLOWLOCATION] = location;

                            // sourcelink relative path to absolute path
                            boost::filesystem::path absolutePath(result[SARIF_NAME_LOCATIONS][0][SARIF_NAME_PHLOCATION][SARIF_NAME_ARTLOCATION][SARIF_NAME_URI].asString());
                            string relativePath = componentHasTheRequiredAttribute(attrTraceComp, Attribute::atString, ATTR_PATH, "").getStringValue();
                            replace(relativePath.begin(), relativePath.end(), '\\', '/');
                            absolutePath.remove_filename();
                            absolutePath += "/" + relativePath;
                            result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_THREADFLOWLOCATION][SARIF_NAME_PHLOCATION][SARIF_NAME_ARTLOCATION][SARIF_NAME_URI] = absolutePath.string();

                            if (componentHasNonRequiredAttribute(attrTraceComp, Attribute::atInt, ATTR_CALLSTACKDEPTH, "")) {
                                const int callStackDepth = ((AttributeInt&)componentHasTheRequiredAttribute(attrTraceComp, Attribute::atInt, ATTR_CALLSTACKDEPTH, "")).getValue();
                                result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_NESTINGLEVEL] = callStackDepth;
                            }
                            else {
                                result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_NESTINGLEVEL] = 0;
                            }

                            executionOrder++;
                        }
                    }

                    result[SARIF_NAME_MESSAGE][SARIF_NAME_TEXT] = messageTextTemp;
                    root[SARIF_NAME_RUNS][0][SARIF_NAME_RESULTS][resultCounter] = Json::Value(result);
                    resultCounter++;
                }
                
                // CloneClass handling
                if (type == NTYPE_DCF_CLONECLASS && ruleIndexesInJson.find(customCloneClassId) != ruleIndexesInJson.end()) {
                    Json::Value result = Json::objectValue;
                    Json::Value location(Json::objectValue);
                    int locationCounter = 0;
                    Edge::EdgeIterator edges = node.findOutEdges(Edge::EdgeType(ETYPE_DCF_CLONETREE, Edge::edtDirectional));
                    const string &name = componentHasTheRequiredAttribute(node, Attribute::atString, ATTR_NAME, CONTEXT_ATTRIBUTE).getStringValue();

                    //linking the rule object index
                    result[SARIF_NAME_RULEINDEX] = ruleIndexesInJson.find(customCloneClassId)->second;
                    result[SARIF_NAME_LOCATIONS] = Json::arrayValue;

                    while (edges.hasNext()) {
                        Node edgeNode = edges.next().getToNode();
                        if (componentHasNonRequiredAttribute(edgeNode, Attribute::atComposite, ATTR_POSITION, CONTEXT_ATTRIBUTE)) {
                            AttributeComposite& attrComp = (AttributeComposite&)(edgeNode.findAttribute(Attribute::atComposite, ATTR_POSITION, CONTEXT_ATTRIBUTE).next());
                            writeLocation(attrComp, location);

                            result[SARIF_NAME_LOCATIONS][locationCounter] = Json::Value(location);
                            locationCounter++;
                        }
                    }
                    if (locationCounter > 0) {  // if there is a cloneclass that has no valid instance (eg. the Instance is cstDisappearing)
                        result[SARIF_NAME_KIND] = "pass";
                        result[SARIF_NAME_OCCURED] = locationCounter;
                        result[SARIF_NAME_MESSAGE][SARIF_NAME_TEXT] = name;
                        root[SARIF_NAME_RUNS][0][SARIF_NAME_RESULTS][resultCounter] = Json::Value(result);
                        resultCounter++;
                    }
                }
            }

            SarifIO sio;
            sio.open(filename, io::IOBase::eOpenMode::omWrite);
            Json::SarifWriter writer;
            sio.writeData(writer.write(root));
            sio.close();
        }
    }
}