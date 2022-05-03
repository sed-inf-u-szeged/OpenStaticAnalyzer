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

#include <columbus_config.h>
#include <BuildInfo.h>
#include "io/inc/IO.h"
#include "io/inc/messages.h"
#include "../inc/GraphConstants.h"
#include "../inc/SarifExporter.h"
#include "../inc/messages.h"
#include "jsoncpp/inc/json.h"
#include <algorithm>
#include <Exception.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <graphsupport/inc/Metric.h>
#include <regex>

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
    const string SARIF_NAME_DOWNLOADURI = "downloadUri";
    const string SARIF_NAME_SEMVER = "semanticVersion";
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
    const string SARIF_NAME_INFORMATION_URI = "informationUri";
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
    const string SARIF_NAME_DESCRIPTION = "description";
    const string SARIF_NAME_DEFCONF = "defaultConfiguration";
    const string SARIF_NAME_RELATIONS = "relationships";
    const string SARIF_NAME_TARGET = "target";
    const string SARIF_NAME_RULEINDEX = "ruleIndex";
    const string SARIF_NAME_RULEID = "ruleId";
    const string SARIF_NAME_BASE_LINE = "baselineState";
    const string SARIF_NAME_ENABLED = "enabled";
    const string SARIF_NAME_PROPERTIES = "properties";
    const string SARIF_NAME_IMPORTANCE = "importance";

    //versions available on https://github.com/oasis-tcs/sarif-spec/tree/master/Schemata
    //Sarif values
    const string SARIF_VALUE_VERSION = "2.1.0";
    const string SARIF_VALUE_SCHEMA = "https://raw.githubusercontent.com/oasis-tcs/sarif-spec/master/Schemata/sarif-schema-2.1.0.json";
    const string SARIF_VALUE_NAME = "OpenStaticAnalyzer";
    const string SARIF_VALUE_LANG = "en-US";
    const string SARIF_VALUE_DOWNURI = "https://github.com/sed-inf-u-szeged/OpenStaticAnalyzer";
    const string SARIF_VALUE_SEMVER = PROJECT_VERSION + std::string("+") + REVISION_NUMBER;
    namespace SARIF_VALUE_PRIORITY {
        const string none = "none";
        const string info = "note";
        const string warning = "warning";
        const string error = "error";
    };
    namespace SARIF_VALUE_BASELINE {
        const string NEW = "new";
        const string UNCHANGED = "unchanged";
        const string UPDATED = "updated";
        const string ABSENT = "absent";
    };
    namespace SARIF_VALUE_IMPORTANCE {
        const string IMPORTANT = "important";
        const string ESSENTIAL = "essential";
        const string UNIMPORTANT = "unimportant";
    };

    const string customCloneClassId = "All_CloneClasses";
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
    private:
        const char *resultLeftMargin = "        ";
        const char *ruleLeftMargin = "            ";
    public:
        void writeData(const Json::Value& root, bool isRule = false) {
            Json::StreamWriterBuilder builder;
            builder["indentation"] = "  ";
            if (!isOpen()) throw columbus::IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_NOT_OPEN);
            else {
                std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                common::updateMemoryStat();
                writer->write(root, stream.get(), isRule ? ruleLeftMargin : resultLeftMargin);
                common::updateMemoryStat();
                flush();
            }
        }
        void writeData(const string &text) {
            *stream << text;
        }
        void writeData(const char *text) {
            *stream << text;
        }
        void writeData(const vector<string> &text) {
            for (auto &t : text) {
                *stream << t;
            }
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
        const string type = aType == Attribute::atInt ? "int" : aType == Attribute::atFloat ? "float" : aType == Attribute::atString ? "string" : aType == Attribute::atComposite ? "composite" : "invalid";
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
    const Attribute &componentHasTheRequiredAttribute(AttributeComposite &attr, const Attribute::aType &aType, const string &name, const string &context) {
        Attribute::AttributeIterator attrItr = attr.findAttribute(aType, name, context);
        if (attrItr.hasNext()) return attrItr.next();
        const string type = aType == Attribute::atInt ? "int" : aType == Attribute::atFloat ? "float" : aType == Attribute::atString ? "string" : aType == Attribute::atComposite ? "composite" : "invalid";
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
    void writeLocation(AttributeComposite &attrComp, Json::Value &location) {
        const AttributeString &path = (AttributeString&)componentHasTheRequiredAttribute(attrComp, Attribute::atString, ATTR_PATH, "");
        const AttributeInt &lineBegin = (AttributeInt&)componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_LINE, "");
        const AttributeInt &lineEnd = (AttributeInt&)componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_ENDLINE, "");
        const AttributeInt &columnBegin = (AttributeInt&)componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_COLUMN, "");
        const AttributeInt &columnEnd = (AttributeInt&)componentHasTheRequiredAttribute(attrComp, Attribute::atInt, ATTR_ENDCOLUMN, "");

        int line = lineBegin.getValue();
        int endLine = lineEnd.getValue();
        int column = columnBegin.getValue();
        int endColumn = columnEnd.getValue();
        std::string _path;
        _path = uriFile + boost::filesystem::path(path.getStringValue()).generic_string();
        boost::replace_all(_path, " ", "%20");

        // negative starting/ending value to 0, because sarif line/column number cannot have negative number
        if (line <= 0) {
            line = 1;
        }
        if (endLine <= 0) {
            endLine = line;
        }
        if (column <= 0) {
            column = 1;
        }
        if (endColumn <= 0) {
            endColumn = column;
        }

        location[SARIF_NAME_PHLOCATION][SARIF_NAME_ARTLOCATION][SARIF_NAME_URI] = _path;

        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_LINE] = line;
        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_COLUMN] = column;
        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_ENDLINE] = endLine;
        location[SARIF_NAME_PHLOCATION][SARIF_NAME_REGION][SARIF_NAME_ENDCOLUMN] = endColumn;
    }

    void writeLocation(const Node &node, Json::Value &location) {
        writeLocation((AttributeComposite&)node.findAttribute(Attribute::atComposite, ATTR_POSITION, CONTEXT_ATTRIBUTE).next(), location);
    }

    void replace(string& str, pair<string, string> opening, pair<string, string> closing) {
        // example : opening={"<pre>","```"}, closing={"</pre>","```"}

        // opFirst = "<pre"
        string opFirst = opening.first.substr(0, opening.first.length() - 1);
        // opLast = ">"
        char opLast = opening.first[opening.first.length() - 1];

        // clFirst = "</pre"
        string clFirst = closing.first.substr(0, closing.first.length() - 1);
        // clLast = ">"
        char clLast = closing.first[closing.first.length() - 1];

        // reg = "<pre(>| .*?>)(.*?)?\<\/pre(>| .+?>)"
    // which is: 
    // group 1 : match any html tag that starts with "<pre>" or "<pre ...>" (html attributes, like id, class,...)
    // group 2 : match everything after the first group
    // group 3 : first occurence of "</pre>" or "</pre ...>" (html attributes like id, class, .... This usually doesn't happen)
        string reg = opFirst + "(" + opLast + "| .*?" + opLast + ")(.*?)?\\" + clFirst[0] + "\\" + clFirst.substr(1, clFirst.length()) + "(" + clLast + "| .+?" + clLast + ")";
        regex r(reg);

        // replaceText = "```Group2```";
        string replaceText = opening.second + "$2" + closing.second;
        str = std::regex_replace(str, r, replaceText, regex_constants::match_not_eol);
    }

    /**
    * \brief convert basic html text to Github Flavored Markdown
    * \param sourceHtml [in-out], reference to source text, also the output for GFM
    */
    string htmlToGFM(string sourceHtml, const string &asg) {
        // newline is replaced by <br> and not as \n, because \n confuses the regex
        const map<pair<string, string>, pair<string, string>> htmlToGFMTags{

            {{"<p>", ""},{"</p>", "<br>"}},
            {{"<b>", "**"},{"</b>", "**"}},
            {{"<strong>", "**"},{"</strong>", "**"}},
            {{"<i>", "*"},{"</i>", "*"}},
            {{"<em>", "*"}, {"</em>", "*"}},
            {{"<ul>", "<br>"}, {"</ul>", ""}},
            {{"<li>", "*   "}, {"</li>", "<br>"}},
            {{"<div>", ""}, {"</div>", ""}},
            {{"<span>", ""}, {"</span>", ""}},
            {{"<code>", "`"}, {"</code>", "`"}},
            {{"<pre>", "```"}, {"</pre>", "```"}},
            {{"<h1>","# "}, {"</h1>",""}},
            {{"<h2>","## "}, {"</h2>",""}},
            {{"<h3>","### "}, {"</h3>",""}},
            {{"<h4>","#### "}, {"</h4>",""}},
            {{"<h5>","##### "}, {"</h5>",""}},
            {{"<h6>","###### "}, {"</h6>",""}},
        };
        const map<string, string> unicodeToGFMTags{
            {"&quot;", "\""},
            {"&lt;", "<"},
            {"&gt;", ">"},
            {"\\n", "\n"},
            {"&#39;", "'"},
            {"&amp;", "&"},
            {"\u2013", "-"}
        };

        // Html links to Markdown links
        while (sourceHtml.find("<a href=\"", 0) != std::string::npos) {
            std::size_t positionStart = sourceHtml.find("<a href=\"", 0);
            std::size_t saveStart = positionStart;
            positionStart += 9;
            std::size_t positionEnd = sourceHtml.find("\"", positionStart);
            string linkHref = "";
            //get the link url from the <a> html tag
            while (positionStart <= positionEnd - 1) {
                linkHref += sourceHtml.at(positionStart);
                positionStart++;
            }

            positionStart = sourceHtml.find(">", positionEnd) + 1;
            positionEnd = sourceHtml.find("</a>", positionStart) - 1;
            string linkText = "";
            //get the text from the <a> html tag
            while (positionStart <= positionEnd) {
                linkText += sourceHtml.at(positionStart);
                positionStart++;
            }
            string link = "[" + linkText + "](" + linkHref + ")";
            sourceHtml.replace(saveStart, positionEnd - saveStart + 5, link);
        }

        for (const auto &tag : unicodeToGFMTags) {
            boost::replace_all(sourceHtml, tag.first, tag.second);
        }
        //have to replace line breaks with a placeholder value, because the regex library cant handle new lines
        boost::replace_all(sourceHtml, "\n", "<br>");
        for (const auto &tag : htmlToGFMTags) {
            replace(sourceHtml, tag.first, tag.second);
        }
        replace(sourceHtml, { "````","\n```cpp\n" }, { "````", "\n```\n" }); // this happens if <pre><code>... exist
        boost::replace_all(sourceHtml, "<br>", "\n");

        boost::replace_tail(sourceHtml, 1, "");
        return sourceHtml;
    }

    std::string getSmellType(const Node &node) {
        AttributeString &ciSmellType = (AttributeString&)componentHasTheRequiredAttribute(node, Attribute::atString, ATTR_DCF_CLONESMELLTYPE, CONTEXT_ATTRIBUTE);
        return ciSmellType.getStringValue();
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

            SarifIO sio;
            sio.open(filename, io::IOBase::eOpenMode::omWrite);

            /*
            * ----------------------------------------- README ------------------------------------------------------
            * Json value as a root has been removed beacause it consumes too much memory
            * For a 5GB graph in memory, the Json::Value consumes an extra 10GB, and memory overflow can occure...
            * Json::Value as shown below works just fine, its performance is acceptable, and its usage is clear,
            *     the only problem is memory consumption
            * The "Json::Value root" has been replaced with sio.writeData(...) as an alternate solution to not store
            *     the data unnecessarily in the memory, since this library (jsoncpp) does not have an option to dump
            *     data constantly into a stream as we assign a value, we must resolve to a solution like this.
            * I will leave this code here as a reference
            * -------------------------------------------------------------------------------------------------------
            */

            /*Json::Value root(Json::objectValue);
            root[SARIF_NAME_VERSION] = SARIF_VALUE_VERSION;
            root[SARIF_NAME_SCHEMA] = SARIF_VALUE_SCHEMA;
            root[SARIF_NAME_RUNS] = Json::arrayValue;
            root[SARIF_NAME_RUNS][0] = Json::objectValue;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_NAME] = SARIF_VALUE_NAME;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_LANG] = SARIF_VALUE_LANG;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_VERSION] = PROJECT_VERSION;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_DOWNLOADURI] = SARIF_VALUE_DOWNURI;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_TOOL][SARIF_NAME_DRIVER][SARIF_NAME_SEMVER] = SARIF_VALUE_SEMVER;
            root[SARIF_NAME_RUNS][0][SARIF_NAME_RESULTS] = Json::arrayValue;*/

            //quote a string
            auto quoted = [](const std::string &str)->std::string {
                return "\"" + str + "\"";
            };
            sio.writeData({
                "{\n",
                "  " + quoted(SARIF_NAME_SCHEMA) + " : " + quoted(SARIF_VALUE_SCHEMA) + ",\n",
                "  " + quoted(SARIF_NAME_VERSION) + " : " + quoted(SARIF_VALUE_VERSION) + ",\n",
                "  " + quoted(SARIF_NAME_RUNS) + " :\n",
                "  [\n",
                "    {\n",
                "      " + quoted(SARIF_NAME_TOOL) + " :\n",
                "      {\n",
                "        " + quoted(SARIF_NAME_DRIVER) + " :\n",
                "          {\n",
                "            " + quoted(SARIF_NAME_NAME) + " : " + quoted(SARIF_VALUE_NAME) + ",\n",
                "            " + quoted(SARIF_NAME_LANG) + " : "+ quoted(SARIF_VALUE_LANG) +",\n",
                "            " + quoted(SARIF_NAME_VERSION) + " : " + quoted(PROJECT_VERSION) + ",\n",
                "            " + quoted(SARIF_NAME_DOWNLOADURI) + " : " + quoted(SARIF_VALUE_DOWNURI) + ",\n",
                "            " + quoted(SARIF_NAME_RULES) + " :\n",
                "            [",
            });


            //Everything related to collect,write and store the rules from the graph
            map<string, int> ruleIndexesInJson;
            {
                Node::NodeIterator ruleNodes = graph.findNodes(NTYPE_RUL_METRIC);
                int ruleCounter = 0;
                boost::filesystem::path full_path(boost::filesystem::current_path().parent_path());
                full_path /= "UsersGuide.html";
                bool userGuideExist = boost::filesystem::exists(full_path);
                string fullPathString = full_path.generic_string();
                fullPathString = uriFile + fullPathString;
                if (userGuideExist) {
                    sio.writeData("        \"" + SARIF_NAME_INFORMATION_URI + "\" : \"" + fullPathString + "\",\n");
                }

                while (ruleNodes.hasNext()) {
                    const Node &ruleNode = ruleNodes.next();
                    const string &description = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_DESCRIPTION, CONTEXT_RUL).getStringValue();
                    const bool ruleParent = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_WARNING, CONTEXT_RUL).getStringValue() == "true";

                    Json::Value rule(Json::objectValue);
                    rule[SARIF_NAME_ID] = ruleNode.getUID();
                    rule[SARIF_NAME_NAME] = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_DISPLAYNAME, CONTEXT_RUL).getStringValue();
                    if (description != "") {
                        rule[SARIF_NAME_SHORTDESC][SARIF_NAME_TEXT] = description;
                    }

                    if (componentHasNonRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_HELPTEXT, CONTEXT_RUL)) {
                        const string &helpText = componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_HELPTEXT, CONTEXT_RUL).getStringValue();
                        string GFMText = htmlToGFM(helpText, asg);
                        rule[SARIF_NAME_FULLDESC][SARIF_NAME_TEXT] = helpText;
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
                            if (!sarifSeverityLevelVal[rank]) continue;

                            priority = (priority == "Info") ? SARIF_VALUE_PRIORITY::info : (priority == "Minor" || priority == "Major") ? SARIF_VALUE_PRIORITY::warning : SARIF_VALUE_PRIORITY::error;
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
                        else {
                            if (userGuideExist) {
                                rule[SARIF_NAME_HELPURI] = fullPathString + "#" + ruleNode.getUID();
                            }
                        }
                    }
                    else {
                        continue;
                    }
                    if (componentHasTheRequiredAttribute(ruleNode, Attribute::atString, ATTR_RUL_GROUPTYPE, CONTEXT_RUL).getStringValue() != "summarized" && !rule[SARIF_NAME_DEFCONF][SARIF_NAME_RANK].empty() && !rule[SARIF_NAME_DEFCONF][SARIF_NAME_LEVEL].empty() && !rule[SARIF_NAME_DEFCONF][SARIF_NAME_ENABLED].empty() && rule[SARIF_NAME_DEFCONF][SARIF_NAME_ENABLED].asString() == "true") {
                        sio.writeData(rule, true);
                        sio.writeData(",");
                        ruleIndexesInJson.emplace(rule[SARIF_NAME_ID].asString(), ruleCounter);
                        common::updateMemoryStat();
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

                    sio.writeData(rule);
                    ruleIndexesInJson.emplace(rule[SARIF_NAME_ID].asString(), ruleCounter);
                    ruleCounter++;
                }
            }

            sio.writeData({
                    "\n",
                    "             ]\n",
                    "         }\n",
                    "      },\n",
                    "      " + quoted(SARIF_NAME_RESULTS) + ":\n",
                    "      ["
                });

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
            bool comma = false;

            // Goes through all the Nodes that has one of the Node type declared above
            while (allNodes.hasNext()) {
                const Node &node = allNodes.next();
                const Node::NodeType &type = node.getType();
                AttributeComposite::AttributeIterator attr = node.findAttributeByContext(CONTEXT_WARNING);
                string smellType = SARIF_VALUE_BASELINE::NEW;

                // CloneClass changes
                // CloneClass handling, add extra rule: All CloneClasses
                if (type == NTYPE_DCF_CLONECLASS && ruleIndexesInJson.find(customCloneClassId) != ruleIndexesInJson.end()) {
                    Json::Value result;
                    const string &name = componentHasTheRequiredAttribute(node, Attribute::atString, ATTR_NAME, CONTEXT_ATTRIBUTE).getStringValue();
                    Edge::EdgeIterator edges = node.findOutEdges(Edge::EdgeType(ETYPE_DCF_CLONETREE, Edge::edtDirectional));
                    string cloneInstanceSmellType;
                    string cloneClassSmellType = getSmellType(node);
                    bool changed = false;
                    int locationsCounter = 0;

                    // has to iterate through the clone instances again
                    while (edges.hasNext()) {
                        // CloneInstance
                        const Node &edgeNode = edges.next().getToNode();
                        cloneInstanceSmellType = getSmellType(edgeNode);

                        if (componentHasNonRequiredAttribute(edgeNode, Attribute::atComposite, ATTR_POSITION, CONTEXT_ATTRIBUTE)) {
                            Json::Value location;
                            writeLocation(edgeNode, location);
                            const string &name = componentHasTheRequiredAttribute(edgeNode, Attribute::atString, ATTR_NAME, CONTEXT_ATTRIBUTE).getStringValue();
                            result[SARIF_NAME_LOCATIONS].append(location);
                            result[SARIF_NAME_LOCATIONS][result[SARIF_NAME_LOCATIONS].size() - 1][SARIF_NAME_PHLOCATION][SARIF_NAME_ARTLOCATION][SARIF_NAME_DESCRIPTION][SARIF_NAME_TEXT] = name + " location";
                        }
                        if (cloneClassSmellType == "cstNone" && cloneInstanceSmellType != "cstNone") {
                            smellType = SARIF_VALUE_BASELINE::UPDATED;
                            changed = true;
                        }

                        locationsCounter++;
                    }
                    if (cloneClassSmellType == "cstAppearing") smellType = SARIF_VALUE_BASELINE::NEW;
                    else if (cloneClassSmellType == "cstDisappearing") smellType = SARIF_VALUE_BASELINE::ABSENT;
                    else if (!changed) smellType = SARIF_VALUE_BASELINE::UNCHANGED;

                    result[SARIF_NAME_RULEINDEX] = ruleIndexesInJson.find(customCloneClassId)->second;
                    result[SARIF_NAME_BASE_LINE] = smellType;
                    result[SARIF_NAME_RULEID] = customCloneClassId;
                    if (locationsCounter > 0) {
                        result[SARIF_NAME_KIND] = "pass";
                        result[SARIF_NAME_OCCURED] = locationsCounter;
                        result[SARIF_NAME_MESSAGE][SARIF_NAME_TEXT] = name;
                        if (comma) sio.writeData(",");
                        sio.writeData(result);
                        comma = true;
                        common::updateMemoryStat();
                    }
                }

                // Warning handling (simple warnings, CloneClass warnings, CloneInstance warning)
                while (attr.hasNext()) {
                    AttributeComposite& attrComp = (AttributeComposite&)attr.next();
                    const string &warningID = attrComp.getName();
                    Json::Value result = Json::objectValue;
                    const string &messageTextTemp = componentHasTheRequiredAttribute(attrComp, Attribute::atString, ATTR_WARNINGTEXT, "").getStringValue();
                    int locationCounter = 0;

                    // if the rule doesn't exist (becuase its not required by severity switch), then the current result will not be examined and will not be saved
                    if (ruleIndexesInJson.find(warningID) == ruleIndexesInJson.end()) continue;

                    // multiple location for the same result
                    if (type == NTYPE_DCF_CLONECLASS) {
                        Edge::EdgeIterator edges = node.findOutEdges(Edge::EdgeType(ETYPE_DCF_CLONETREE, Edge::edtDirectional));

                        while (edges.hasNext()) {
                            // CloneInstance
                            Node edgeNode = edges.next().getToNode();

                            if (componentHasNonRequiredAttribute(edgeNode, Attribute::atComposite, ATTR_POSITION, CONTEXT_ATTRIBUTE)) {
                                Json::Value location;
                                writeLocation(edgeNode, location);
                                const string &name = componentHasTheRequiredAttribute(edgeNode, Attribute::atString, ATTR_NAME, CONTEXT_ATTRIBUTE).getStringValue();
                                result[SARIF_NAME_LOCATIONS][locationCounter] = location;
                                result[SARIF_NAME_LOCATIONS][locationCounter][SARIF_NAME_PHLOCATION][SARIF_NAME_ARTLOCATION][SARIF_NAME_DESCRIPTION][SARIF_NAME_TEXT] = name + " location";
                                locationCounter++;
                            }
                        }
                    }
                    // only one location for the result / not a cloneclass
                    else {
                        Json::Value location;
                        writeLocation(attrComp, location);
                        result[SARIF_NAME_LOCATIONS][locationCounter] = location;
                        locationCounter++;
                    }
                    if (locationCounter == 0) continue; // if there is a cloneclass that has no valid instance (eg. the Instance is cstDisappearing)

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
                            result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_IMPORTANCE] = SARIF_VALUE_IMPORTANCE::ESSENTIAL;

                            const string path = boost::filesystem::path(uriFile + componentHasTheRequiredAttribute(attrTraceComp, Attribute::atString, ATTR_PATH, "").getStringValue()).generic_string();
                            result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_THREADFLOWLOCATION][SARIF_NAME_PHLOCATION][SARIF_NAME_ARTLOCATION][SARIF_NAME_URI] = path;

                            // Add warningText or RoleName as threadflow message
                            if (componentHasNonRequiredAttribute(attrTraceComp, Attribute::atString, ATTR_WARNINGTEXT, "")) {
                                const string &warningText = ((AttributeString&)componentHasTheRequiredAttribute(attrTraceComp, Attribute::atString, ATTR_WARNINGTEXT, "")).getStringValue();
                                result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_THREADFLOWLOCATION][SARIF_NAME_MESSAGE][SARIF_NAME_TEXT] = warningText;
                            }
                            else if (componentHasNonRequiredAttribute(attrTraceComp, Attribute::atString, "RoleName", "")) {
                                const string &warningText = ((AttributeString&)componentHasTheRequiredAttribute(attrTraceComp, Attribute::atString, "RoleName", "")).getStringValue();
                                result[SARIF_NAME_CODEFLOWS][0][SARIF_NAME_THREADFLOWS][0][SARIF_NAME_LOCATIONS][executionOrder][SARIF_NAME_THREADFLOWLOCATION][SARIF_NAME_MESSAGE][SARIF_NAME_TEXT] = warningText;
                            }

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
                    result[SARIF_NAME_RULEINDEX] = ruleIndexesInJson.find(warningID)->second;
                    result[SARIF_NAME_BASE_LINE] = smellType;
                    result[SARIF_NAME_OCCURED] = locationCounter;
                    result[SARIF_NAME_RULEID] = warningID;
                    result[SARIF_NAME_KIND] = "pass";

                    if (comma) sio.writeData(",");
                    sio.writeData(result);
                    comma = true;
                    common::updateMemoryStat();
                }

            }

            sio.writeData({
                "\n",
                "      ]\n",
                "    }\n",
                "  ]\n",
                "}" 
            });

            common::updateMemoryStat();
        }
    }
}
