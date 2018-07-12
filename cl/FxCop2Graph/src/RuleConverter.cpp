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

#include "../inc/RuleConverter.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace fxcop2graph;

XERCES_CPP_NAMESPACE_USE


bool getAttr(const Attributes& attrs, const char* attrName, string& val);
bool parseXML(const string& filename, DefaultHandler* handler);

class FxCopHandler : public DefaultHandler{
private:
    rul::RulHandler* rul;
    string MetricId;
    string CheckId;
    string Category;
    string Name;
    string Description;
    string MessageLevel;
    string content;
    string CategoryFriendlyName;
    string TypeName;

    std::vector<std::string> metricIds;

public:
    FxCopHandler(rul::RulHandler* rul) : rul(rul), metricIds() {
    }


    virtual void startElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs) {
        string name = XMLString::transcode(localname);
        content.clear();
        if (name == "Rules"){
            getAttr(attrs, "FriendlyName", CategoryFriendlyName);
        }
        if (name == "Rule") {
            getAttr(attrs, "CheckId", CheckId);
            getAttr(attrs, "Category", Category);
            getAttr(attrs, "TypeName", TypeName);
            Category += " Rules";
        }

    }

    virtual void  characters(const XMLCh *const chars, const XMLSize_t length) {
        content += XMLString::transcode(chars);
    }

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }


    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    virtual void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname) {
        string name = XMLString::transcode(localname);
        try {
            if (name == "MessageLevel") {
                if (std::strstr(content.c_str(), "CriticalError"))
                    rul->setSettingValue(MetricId, "Priority", "Blocker", true);
                else if (std::strstr(content.c_str(), "Error"))
                    rul->setSettingValue(MetricId, "Priority", "Critical", true);
                else if (std::strstr(content.c_str(), "CriticalWarning"))
                    rul->setSettingValue(MetricId, "Priority", "Major", true);
                else if (std::strstr(content.c_str(), "Warning"))
                    rul->setSettingValue(MetricId, "Priority", "Minor", true);
                else if (std::strstr(content.c_str(), "Information"))
                    rul->setSettingValue(MetricId, "Priority", "Info", true);

            } else if (name == "Name") {
                using namespace std;
                string displayNameBeginLetters = "";
                if (TypeName.find("FxCopRule") != std::string::npos) {
                    TypeName = TypeName.substr(0, TypeName.length() - string("FxCopRule").length() - 1);
                }
                for (size_t i = 1; i < TypeName.length() - 1; i++)
                {
                    if (TypeName[i - 1] >= 97 && TypeName[i] <= 90 && TypeName[i] >= 65 && TypeName[i + 1] >= 97) {
                        TypeName.insert(i, " ");
                    }
                }
                std::vector<std::string> splittedTypeName = split(TypeName, ' ');
                for (std::vector<std::string>::iterator it = splittedTypeName.begin(); it != splittedTypeName.end(); ++it) {
                    displayNameBeginLetters += toupper((*it)[0]);
                }

                int i = 0;
                while (true) {
                    if (std::find(metricIds.begin(), metricIds.end(), displayNameBeginLetters) != metricIds.end()) { // if contains id
                        i++;
                        displayNameBeginLetters = "";
                        for (std::vector<std::string>::iterator it = splittedTypeName.begin(); it != splittedTypeName.end(); ++it) {
                            for (int j = 0; j <= i && i < (*it).length(); j++)
                                displayNameBeginLetters += toupper((*it)[j]);

                            if (i >= (*it).length()) i -= (*it).length();
                        }
                    } else {
                        break;
                    }
                }

                metricIds.push_back(displayNameBeginLetters);
                MetricId = "FXCOP_" + displayNameBeginLetters;
                rul->defineMetric(MetricId);
                rul->createConfiguration(MetricId, "Default");
                rul->setIsEnabled(MetricId, true);
                rul->setIsVisible(MetricId, true);
                rul->setOriginalId(MetricId, CheckId);
                rul->setGroupType(MetricId, "false");
                rul->createLanguage(MetricId, "eng");
                rul->setDisplayName(MetricId, content);
                rul->setHasWarningText(MetricId, true);
                rul->addMetricGroupMembers(MetricId, Category);

            } else if (name == "Description") {
                rul->setHelpText(MetricId, content);

            } else if (name == "Rules"){
                rul->defineMetric(Category);
                rul->createConfiguration(Category, "Default");
                rul->setIsEnabled(Category, true);
                rul->setIsVisible(Category, true);
                rul->setGroupType(Category, "summarized");
                rul->createLanguage(Category, "eng");
                rul->setHasWarningText(Category, true);
                rul->setDisplayName(Category, CategoryFriendlyName);
                rul->setDescription(Category, "");
            }
        } catch (const rul::RulHandlerException& ex) {
            WriteMsg::write(CMSG_FXCOP2GRAPH_RULE_EXCEPTION, ex.getMessage().c_str());
        }
        content.clear();
    }
};

void RuleConverter::convertRuleFile(const vector<string>& file_names, const Config& config) {
    this->config = config;

    rul::RulHandler rul("Default", "eng");
    rul.setToolDescription("ID", "FxCop");

    FxCopHandler* fxCopHandler = new FxCopHandler(&rul);

    for (const auto& filename : file_names)
    {
      parseXML(filename, fxCopHandler);
    }

    rul.saveRul(config.rulFile);
}
