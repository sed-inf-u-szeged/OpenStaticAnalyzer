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

#include "../inc/LIM2Patterns.h"
#include "../inc/Helpers.h"
#include "../inc/PythonBinding.h"
#include <graphsupport/inc/MetricSum.h>
#include <graphsupport/inc/RulBuilder.h>
#include <boost/filesystem.hpp>

using namespace std;
using namespace common;
using namespace columbus::graph;
using namespace columbus::rul;
using namespace columbus::lim::metrics;
using namespace columbus::lim::asg;
using namespace columbus::lim::asg::base;
using namespace columbus::lim::patterns::conditions;
using namespace columbus::graphsupport::graphconstants;

namespace columbus {
    namespace lim {
        namespace patterns {

            using namespace patterns::pythonBinding;

            LIM2PatternsVisitor::LIM2PatternsVisitor(Factory& fact, Graph& inGraph, vector<unique_ptr<Condition>> &_patterns, const set<string> &_whitelist, const set<string> &_blacklist, RulHandler& rl)
                : factory(fact), inGraph(inGraph), patterns(_patterns), whitelist(_whitelist), blacklist(_blacklist), rl(rl), revEdges(factory.getReverseEdges()), _moduleFlag(true){}

            LIM2PatternsVisitor::~LIM2PatternsVisitor()
            {
            }

            void LIM2PatternsVisitor::visit(const Base& _base, bool callVirtualBase) {
                VisitorAbstractNodes::visit(_base);
                currentPatternDocument() = -1;

                for (const auto &pattern : patterns) {
                    result().reset();
                    if (dynamic_cast<NodeTypeCondition*>(pattern.get())) {
                        currentPatternDocument()++;
                        this->visitYaml(_base, dynamic_cast<NodeTypeCondition*>(pattern.get()));
                    }
                    else if (dynamic_cast<PythonCondition*>(pattern.get())){
                        this->visitPython(_base, dynamic_cast<PythonCondition*>(pattern.get()));
                    }
                    else {
                        // HOW DID WE GET HERE ????? this should not be possible...
                    }
                }
            }

            void LIM2PatternsVisitor::visitYaml(const Base& _base, NodeTypeCondition *condition) {
                if (skipPattern(condition->getPatternName())) return;

                if (condition->testCondition(inGraph, _base)) {
                    addWarning(this->inGraph, _base, condition->getPatternName(), condition->getRoleName(), condition->getCategory(), condition->getDescription(), condition->getDisplayName(), condition->getPriority());
                    WriteMsg::write(WriteMsg::mlNormal, "[Found on '" + to_string(_base.getId()) + "']\n");
                    WRITE_DEBUG(" [found on '" + to_string(_base.getId()) + "']");
                }
                // TODO:: Calculate remove
                // reset variables
                /*
                result().addMetricToNode(this->inGraph, _base, roleNames()[currentPatternDocument()][condition->getRoleName()].second);
                for (auto &_role : getRoleNames()[currentPatternDocument()]) {
                    for (auto &_var : _role.second.second) {
                        _var.second.second = boost::any();
                    }
                }*/
            }

            void LIM2PatternsVisitor::visitPython(const Base& _base, PythonCondition *condition) {
                if (skipPattern(condition->getPatternName())) return;

                if (_moduleFlag) {
                    this->pythonBindingModule = make_unique<py::module>(py::module::import("PythonBinding"));
                    _moduleFlag = false;
                }
                condition->testCondition(inGraph, _base);
            }

            bool LIM2PatternsVisitor::skipPattern(const std::string &patternName)
            {
                if (patternName.empty()) return false;
                // whitelist
                if (!whitelist.empty() && whitelist.find(patternName) == whitelist.end()) return true;
                // blacklist
                if (!blacklist.empty() && blacklist.find(patternName) != blacklist.end()) return true;
                return false;
            }

            void LIM2PatternsVisitor::visitEnd(const Base& _base, bool callVirtualBase) {
                VisitorAbstractNodes::visitEnd(_base);
            }

            void loadFilter(Factory& fact, const string& file) {
                string flt = pathRemoveExtension(file) + ".flim";
                if (fileTimeCmp(flt, file) == -1) {
                    WriteMsg::write(WriteMsg::mlWarning, "%s is older than the .lim", flt.c_str());
                }

                try {
                    fact.loadFilter(flt);
                }
                catch (const IOException&) {
                    WriteMsg::write(WriteMsg::mlWarning, "%s cannot be loaded. Continuing without filters...", flt.c_str());
                }
            }

            py::module importModule(const std::string& module, const std::string& path, py::object& globals)
            {
                boost::filesystem::path package(path);
                package = package.parent_path();
                string pack = package.string();
#ifndef __linux__
                boost::algorithm::replace_all(pack, "\\", "\\\\");
#endif
                py::dict locals;
                locals["module_name"] = py::cast(module); // have to cast the std::string first
                locals["path"] = py::cast(path);

                py::eval<py::eval_statements>(            // tell eval we're passing multiple statements
                    "import sys\n"
                    "sys.path.append('" + pack + "')\n"
                    "import imp\n"
                    "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
                    globals,
                    locals);

                return locals["new_module"].cast<py::module>();
            }

            void lim2Patterns(const string & limFileName, const vector<string> &patternsFileName, const set<string>& whitelist, const set<string>& blacklist, const string & outputFileName, const string& patternsFolder, const string& metricFileName, const string &graphFileName, bool dumpXML, const string &rulDumpDir)
            {

                vector<unique_ptr<Condition>> conditions;
                {
                    // creating the rules
                    getPatternRulHander().createConfigurationForToolDescription("Default");
                    getPatternRulHander().setToolDescription("ID", getMAIN_GROUP().id);
                    addRulToRulHander(getSUB_GROUP1());
                    addRulToRulHander(getSUB_GROUP2());

                    // processing the pattern file(s)
                    vector<boost::any> patternNodes;
                    for (const auto &_patternFile : patternsFileName) {
                        WriteMsg::write(WriteMsg::mlNormal, "Loading pattern: " + _patternFile + "\n");
                        if (common::pathFindExtension(_patternFile) != "py") {
                            auto _tempPatterns = convertToYaml(_patternFile);
                            for (const auto &_pattern : _tempPatterns ) {
                                patternNodes.push_back(_pattern);
                            }
                        }
                        else {
                            string _scriptName = common::pathRemoveExtension(common::pathFindFileName(_patternFile));
                            py::object _globals = py::module::import("__main__").attr("__dict__");
                            const auto &script = importModule(_scriptName, _patternFile, _globals);
                            patternNodes.push_back(script);
                        }
                    }

                    RefDistributorStrTable strTable;
                    Factory factory(strTable, "", asg::limLangOther);
                    OverrideRelations overrideRelation(factory);
                    list<HeaderData*> header;
                    PropertyData prop;
                    header.push_back(&prop);
                    header.push_back(&overrideRelation);
                    WriteMsg::write(WriteMsg::mlNormal, "Loading: " + limFileName + "\n");
                    factory.load(limFileName, header);
                    //load filter
                    factory.initializeFilter();
                    factory.turnFilterOn();
                    loadFilter(factory, limFileName.c_str());

                    string rulconfig;
                    switch (factory.getLanguage()) {
                    case limLangC:         rulconfig = "c"; break;
                    case limLangCpp:       rulconfig = "cpp"; break;
                    case limLangJava:      rulconfig = "java"; break;
                    case limLangCsharp:    rulconfig = "csharp"; break;
                    case limLangFsql:      rulconfig = "fsql"; break;
                    case limLangJavaScript:rulconfig = "javascript"; break;
                    case limLangPython:    rulconfig = "python"; break;
                    case limLangRpg:       rulconfig = "rpg"; break;
                    default:               rulconfig = "Default"; break;
                    }

                    // create dummy metrl if metricFile wasnt set, because it wont be used anyway...
                    unique_ptr<rul::RulHandler> metrl = metricFileName.empty()?
                        nullptr:
                        make_unique<rul::RulHandler>(metricFileName, rulconfig, "eng");
                    if (!metricFileName.empty()) {
                        WriteMsg::write(WriteMsg::mlNormal, "Loading: " + metricFileName + "\n");

                        vector<string> vec;
                        metrl->collectWarnings(vec, false);

                        // Collecting the metrics
                        //WriteMsg::write(WriteMsg::mlNormal, "Collecting the metrics...\n");
                        for (const auto &_vec : vec) {
                            set<string> vec1 = metrl->getCalculatedForSet(_vec);
                            getMetricIDsAndCalcFor().insert({ _vec, vec1 });
                        }

                        {
                            map<string, set<string>> filterConditions;
                            for (size_t index = 0; index < filterTypesAndValues.size(); index++) {
                                const string &type = limTypesString[filterTypesAndValues[index].first];
                                const auto &_pair = filterTypesAndValues[index].second;
                                set<string> ndkToString;
                                for (const NodeKind &kinds : _pair.first) {
                                    ndkToString.insert(string(Common::toString(kinds)).erase(0, 3));
                                }
                                filterConditions.insert({ type, ndkToString });
                            }
                            getMetricIDsAndCalcFor().insert(filterConditions.begin(), filterConditions.end());
                        }
                    }

                    WriteMsg::write(WriteMsg::mlNormal, "Parsing " + string(metrl != nullptr ? "and checking " : "") + "patterns...\n");
                    // Condition building and patternChecking
                    for (size_t i = 0; i < patternNodes.size(); i++) {
                        auto &patternNode = patternNodes[i];
                        if (patternNode.type() == typeid(YAML::Node)) {
                            getRoleNames().push_back({});
                            conditions.emplace_back(createCondition(boost::any_cast<YAML::Node>(patternNode), patternsFolder));
                            currentPatternDocument()++;
                        }
                        else {
                            const py::module &_module = boost::any_cast<py::module>(patternNode);
                            conditions.emplace_back(make_unique<PythonCondition>(_module));
                        }
                    }

                    Graph graph;
                    // read graph from file or construct graph from the lim and metrics file
                    if (!graphFileName.empty()) {
                        WriteMsg::write(WriteMsg::mlNormal, "Loading: " + graphFileName + "\n");
                        graph.loadBinary(graphFileName);
                    }
                    else {
                        //WriteMsg::write(WriteMsg::mlNormal, "Generating graph from lim\n");
                        lim2graph::convertBaseGraph(factory, graph, true, true, true, true);
                        OverrideRelations overrides(factory);
                        SharedContainers shared;
                        //WriteMsg::write(WriteMsg::mlNormal, "Generating reverse edges...\n");
                        InheritanceHelper inheritance(factory.getReverseEdges());
                        LCOMMapType LCOMMap;
                        shared.overrides = &overrides;
                        shared.factory = &factory;
                        shared.inheritance = &inheritance;
                        shared.LCOMMap = &LCOMMap;

                        LimMetricsVisitor visitor(factory, graph, *metrl, shared);
                        WriteMsg::write(WriteMsg::mlNormal, "Loading : Graph from lim...\n");
                        visitor.run();
                    }
                    
                    LIM2PatternsVisitor lpv(factory, graph, conditions, whitelist, blacklist, *metrl);

                    AlgorithmPreorder aP;
                    aP.setVisitSpecialNodes(true, true);
                    aP.setCrossEdgeToTraversal(edkScope_HasMember);
                    aP.setSafeMode();

                    WriteMsg::write(WriteMsg::mlNormal, "Searching for patterns...\n");

                    aP.run(factory, lpv, factory.getRoot()->getId());

                    const auto &foundPatterns = result().getFoundPatternNames();
                    if (!foundPatterns.empty()) {
                        graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true, foundPatterns, true);
                        graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false, foundPatterns);
                        graphsupport::createGroupMetrics(graph, getPatternRulHander());
                        
                    }

                    WriteMsg::write(WriteMsg::mlNormal, "Creating the output files...\n");
                    graphsupport::buildRulToGraph(graph, getPatternRulHander());
                    graph.saveBinary(outputFileName + ".graph");
                    if (dumpXML)
                        graph.saveXML(outputFileName + ".xml");
                    if (!rulDumpDir.empty())
                        getPatternRulHander().saveRul((boost::filesystem::path(rulDumpDir) / "Patterns.rul").string());


                    //graph.saveCSV(newName + ".csv");
                    //factory.save(newName + ".lim", header);
                    ofstream o;
                    o.open(outputFileName + "-Patterns.txt", std::ofstream::out);
                    o << result().getOutput();
                    o.close();


                    // freeing up globals
                    {
                        getRoleNames().clear();
                        currentlyIn().clear();
                        getMetricIDsAndCalcFor().clear();
                        result().reset();
                    }
                }
            }
        }
    }
}
