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

#include "../inc/UdmHelpers.h"

void loadGraphcCalcFor(graph::Graph& graph, map<string, set<string>>& graph_calculatedFors) {
    
    graph::Node::NodeIterator nodeIter = graph.getNodes();

    //
    //  LOOKING FOR "RulMetric" TYPE METRICS AND THEIR "Calculated" ATTRIBUTES IN THE GRAPH
    //

    while (nodeIter.hasNext()) {
        graph::Node nextNode = nodeIter.next();
        if (nextNode.getType().getType() == graphsupport::graphconstants::NTYPE_RUL_METRIC) {
            set<string> calcFors;
            graph::Attribute::AttributeIterator calcAttrIter = nextNode.findAttributeByName(graphsupport::graphconstants::ATTR_RUL_CALCULATED);
            while (calcAttrIter.hasNext()) {
                graph::AttributeComposite& compAttr = dynamic_cast<graph::AttributeComposite&> (calcAttrIter.next());
                graph::Attribute::AttributeIterator compAttrIter = compAttr.getAttributes();
                while (compAttrIter.hasNext())
                    calcFors.insert(compAttrIter.next().getStringValue());
            }
            
            graph_calculatedFors.insert(pair<string, set<string>>(nextNode.getUID(), calcFors));
        }
    }
}

// Loading user's metrics basics setting (id, formula, formulatype, calcFors) -- which have XML tag
void loadUdmNodeRulSettings(map<string, UdmNode>& udm_nodes, rul::RulHandler& rulHand, map<string, set<string>>& graph_calculatedFors) {
    std::vector<std::string> ruleIds;
    rulHand.getRuleIdList(ruleIds);
    for (const auto &ruleId : ruleIds) {
      if (const auto &group = rulHand.getGroupType(ruleId); group != "false" && group != "~~@RUL_EMPTY_STRING@~~") {
        continue;
      }

        if (ruleId == "") {
            throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_NO_FORMULA_NAME);
        }

        if (graph_calculatedFors.find(ruleId) != graph_calculatedFors.end()) {
            throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_OCCUPIED_FORMULA_NAME);
        }

        string formula, formulaType;

        // Loading user's formula's expression
        try {
            formula = rulHand.getSettingValue(ruleId, "Formula");
        }
        catch (rul::RulHandlerException&) {
            // Loading the default (0) expression
            formula = "0";
            WriteMsg::write(CMSG_UDM_NO_FORMULA_EXPRESSION, ruleId.c_str());
            warning = true;
        }

        // Loading user's formula's type
        try {
            if (rulHand.getSettingValue(ruleId, "Type") == "Float" || rulHand.getSettingValue(ruleId, "Type") == "Integer") {
                formulaType = rulHand.getSettingValue(ruleId, "Type");
            }
            else {
                //Loading the default (Float) formula's result type in case of wrong formula type
                formulaType = "Float";
                WriteMsg::write(CMSG_UDM_WRONG_FORMULA_TYPE, ruleId.c_str());
            }
        }
        catch (rul::RulHandlerException&) {
            // Loading the default (Float) formula's result type in case of no formula type
            formulaType = "Float";
        }

        set<string> formulaCalculatedFors = rulHand.getCalculatedForSet(ruleId);
        if (rulHand.getCalculatedForSet(ruleId).empty()) {
            WriteMsg::write(CMSG_UDM_NO_CALCULATED_FOR_SETTINGS, ruleId.c_str());
        }

        udm_nodes.try_emplace(ruleId, ruleId, formula, formulaType, formulaCalculatedFors);

    }
    //}
}

// Just a helperfunction for loadFormulaAttributes, for better transparency, hiding try catch, etc..
inline void safeEvaluateFormula(exprtk::expression<long double>& expression, const string& metric) {

    try {
        // Needs to fill reqMetrics
        expression.value();
    }
    // Catching exception throwed by checkChildTypes()
    catch (InvalidChildTypeEx& ex) {

        string childType = ex.what();
        throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_INVALID_CHILD_TYPE);
    }
}

// Processing the formula and collecting graph, normal and pass dependencies, child types and metric name of the aggr. function
void loadFormulaAttributes(UdmNode& udm_node, map<string, UdmNode>& udm_nodes, const map<string, set<string>>& graph_calculatedFors) {

    exprtk::symbol_table<long double> symbolTable;
    exprtk::expression<long double> expression;
    expression.register_symbol_table(symbolTable);
    exprtk::parser<long double> parser;
    string expressionString = udm_node.getFormula();

    string metricName = udm_node.getMetricName();
    set<string>& udm_dependencies = udm_node.getNormalDependency();
    set<string>& udm_passDependencies = udm_node.getPassDependency();
    set<string>& graph_dependencies = udm_node.getGraphDependency();
    vector<pair<set<string>, string>>& udm_aggrCalcFors = udm_node.getAggregateCalcFors();

    // Creating invalid Node
    graph::Node node;
    UdmFunction::Inserter inserter(symbolTable, node, &udm_aggrCalcFors);

    // Checking whether the formula is already calculable (is constant)
    if (!parser.compile(expressionString, expression)) {

        // If not constant, checking for errors
        parser.enable_unknown_symbol_resolver();
        if (!parser.compile(expressionString, expression)) {
            throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_WRONG_FORMULA_EXPRESSION);
        }

        //
        //  LOADING FORMULA'S VARIABLES (NORMAL AND GRAPH DEPS)
        //

        deque<string> variables;
        symbolTable.get_variable_list(variables);

        //
        //  SEARCHING FOR METRICS OR OTHER FORMULAS BY THE FOUND VARIABLES
        //

        deque<string>::iterator varIter = variables.begin();
        for (; varIter != variables.end(); ++varIter) {
            // Checking whether the variable is a formula given by the user
            if (udm_nodes.find(*varIter) != udm_nodes.end()) {
                udm_dependencies.insert(*varIter);
            }
            // ...or a metric from the graph...
            else if (graph_calculatedFors.find(*varIter) != graph_calculatedFors.end()) {
                graph_dependencies.insert(*varIter);
            }
            // ...or a built-in constant
            else if (*varIter == "pi" || *varIter == "epsilon" || *varIter == "inf") {
                continue;
            }
            // ...or none if the above
            else {
                throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_VARIABLE_COULDNT_BE_FOUND);
            }
        }
    }

    //
    // LOADING FORMULA'S PASS DEPENDENCIES AND AGGRCALCFORS
    //

    safeEvaluateFormula(expression, metricName);

    if (udm_aggrCalcFors.size()) {

        for (const auto& dep : udm_aggrCalcFors) {

            const string& reqMetric = dep.second;
            // Checking if the metric is userdefined
            if (udm_nodes.find(reqMetric) != udm_nodes.end()) {

                udm_passDependencies.insert(reqMetric);
                // Checking if the metric are in the normal dependencies too
                auto it = udm_dependencies.find(reqMetric);
                if (it != udm_dependencies.end()) {
                    udm_dependencies.erase(it);
                }
            }
            else {
                if (graph_calculatedFors.find(reqMetric) == graph_calculatedFors.end()) {
                    // If the graph and the userdefined metrics does not contains the reqMetric
                    throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_AGGR_VARIABLE_COULDNT_BE_FOUND);
                }
            }
        }
    }
}

void loadUdmMetrics(map<string, UdmNode>& udm_nodes, rul::RulHandler& rulHand, map<string, set<string>>& graph_calculatedFors) {

    // Loading the settings from the rul
    loadUdmNodeRulSettings(udm_nodes, rulHand, graph_calculatedFors);

    // Processing the udm_node's formula
    for (auto& udm_node : udm_nodes) {

        loadFormulaAttributes(udm_node.second, udm_nodes, graph_calculatedFors);

    }
}

void checkCalcFors(const map<string, UdmNode>& udm_nodes, map<string, set<string>>& graph_calculatedFors) {

    for (const auto& udm_node : udm_nodes) {

        const set<string>& udm_dependencies = udm_node.second.getNormalDependency();
        const set<string>& udm_calcFors = udm_node.second.getCalcFors();
        const set<string>& udm_graphDependencies = udm_node.second.getGraphDependency();
        const vector<pair<set<string>, string>>& udm_aggrCalcFors = udm_node.second.getAggregateCalcFors();
        const string& metricName = udm_node.first;

        // Checking the CalculatedFor attributes between the formula and it's graph dependencies
        for (const string& udm_graphDependency : udm_graphDependencies) {

            const set<string>& udm_graphDependencyCalcFors = graph_calculatedFors.find(udm_graphDependency)->second;
            if (!includes(udm_graphDependencyCalcFors.begin(), udm_graphDependencyCalcFors.end(), udm_calcFors.begin(), udm_calcFors.end())) {
                string variable = udm_graphDependency;
                throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_WRONG_FORMULA_CALCFOR_ATTR);
            }

        }
        // Checking the CalculatedFor attributes between the formula and it's udm dependencies
        for (const string& udm_dependency : udm_dependencies) {

            const set<string>& udm_dependencyCalcFors = udm_nodes.find(udm_dependency)->second.getCalcFors();
            if (!includes(udm_dependencyCalcFors.begin(), udm_dependencyCalcFors.end(), udm_calcFors.begin(), udm_calcFors.end())) {
                string metricName = udm_node.first; //variable for the error message
                string variable = udm_dependency;    //variable for the error message

                throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_WRONG_FORMULA_CALCFOR_ATTR);
            }
        }

        // Checking the CalculatedFor attributes between the metric from the aggr function and childTypes
        for (const auto& udm_aggrCalcFor : udm_aggrCalcFors) {

            const set<string>& childTypes = udm_aggrCalcFor.first;
            const string& reqMetric = udm_aggrCalcFor.second;

            if (childTypes.find(UDM_EXPANDED) != childTypes.end()) { continue; }

            if (udm_nodes.find(reqMetric) != udm_nodes.end() || graph_calculatedFors.find(reqMetric) != graph_calculatedFors.end()){
                const set<string>* reqMetricCalcFors;
                if (udm_nodes.find(reqMetric) != udm_nodes.end()) {

                    reqMetricCalcFors = &(udm_nodes.find(reqMetric)->second.getCalcFors());
                }
                else {

                    reqMetricCalcFors = &(graph_calculatedFors.find(reqMetric)->second);
                }
                if (!includes(reqMetricCalcFors->begin(), reqMetricCalcFors->end(), childTypes.begin(), childTypes.end()) && childTypes.find("ALL") == childTypes.end()) {
                    string formula = udm_node.first; //variable for the error message
                    string variable = reqMetric;  //variable for the error message
                    throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_WRONG_AGGR_CALCFOR);
                }
            }
            else {
                throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_AGGR_VARIABLE_COULDNT_BE_FOUND);
            }
        }
    }
}

void buildDependency(vector<vector<string>>& passVector, map<string, UdmNode>& udm_nodes) {

    // Need, bc in traverse using []operator
    passVector.resize(udm_nodes.size());
    vector<string> loopCheck;
    for (auto& udm_node : udm_nodes) {
        udm_node.second.traverse(passVector, udm_nodes, loopCheck);
    }

}

// Calculate the Node's metrics, which are in the dependency vector and write it to the graph
void evaluateNode(graph::Node& node, const map<string, UdmNode>& udm_nodes, const vector<string>& dependency, graph::Graph& graph) {

    exprtk::symbol_table<long double> symbolTable;
    exprtk::expression<long double> expression;
    exprtk::parser<long double> parser;
    expression.register_symbol_table(symbolTable);

    // Inserting the aggregations functions
    UdmFunction::Inserter inserter(symbolTable, node);

    //
    // GETTING NODE'S "metric" TYPE ATTRIBUTES AND ADDING THEM TO THE SYMBOL TABLE
    //

    graph::Attribute::AttributeIterator aI = node.findAttributeByContext(graphsupport::graphconstants::CONTEXT_METRIC);
    while (aI.hasNext()) {
        long double a;
        graph::Attribute& attr = aI.next();

        if (attr.getType() == graph::Attribute::atInt) {

            graph::AttributeInt& aInt = dynamic_cast<graph::AttributeInt&>(attr);
            a = aInt.getValue();
        }
        else {
            if (attr.getType() == graph::Attribute::atFloat) {

                graph::AttributeFloat& aFloat = dynamic_cast<graph::AttributeFloat&>(attr);
                a = aFloat.getValue();
            }
            else {
                a = 0;
            }
        }
        if (!symbolTable.add_constant(attr.getName(), a)) {
            WriteMsg::write(CMSG_UDM_CANT_ADD_VARIABLE, attr.getName().c_str());
        }
    }
    symbolTable.add_constants();  // Defining the constants: Pi, Epsilon, Infinity

    //
    // CALCULATING THE FORMULA AND INSERTING ITS VALUE IN THE GRAPH
    //

    for (const string& metricName : dependency) {
        // Checking whether the current node's type is in the current formulas calculated attributes
        const UdmNode& depUdmNode = udm_nodes.find(metricName)->second;
        const set<string>& depCalcFors = depUdmNode.getCalcFors();
        if (depCalcFors.find(node.getType().getType()) != depCalcFors.end()) {
            if (!parser.compile(udm_nodes.find(metricName)->second.getFormula(), expression)) {
                throw Exception(COLUMBUS_LOCATION, CMSG_UDM_EX_WRONG_FORMULA_EXPRESSION);
            }
            else {

                //
                // CREATING A METRIC TYPE ATTRIBUTE WITH THE VALUE OF THE EXPRESSION(formula)
                //

                long double a = expression.value();

                if (depUdmNode.getFormulaType() == "Float") {
                    graphsupport::setMetricFloat(graph, node, metricName, static_cast<float>(a));
                    if (node.findAttributeByName(metricName).hasNext()) {
                        // Checking whether the Metric is invalid is done separately, afterwards
                        // because setMetricFloat() can create invalid metrics, silently
                        if (graphsupport::isINVALID(node.findAttributeByName(metricName).next())) {
                            WriteMsg::write(CMSG_UDM_INVALID_ATTRIBUTE, metricName.c_str(), node.getUID().c_str());
                            warning = true;
                        }
                    }
                }
                else {
                    graphsupport::setMetricInt(graph, node, metricName, static_cast<int>(a));
                }

                if (!symbolTable.add_constant(metricName, a)) {
                    WriteMsg::write(CMSG_UDM_CANT_ADD_VARIABLE, metricName.c_str());
                }
            }
        }
    }
}

void evaluateGraph(const map<string, UdmNode>& udm_nodes, const vector<vector<string>>& passVector, graph::Graph& graph) {

    for (const vector<string>& pass : passVector) {

        graph::Node::NodeIterator nodeIter = graph.getNodes();
        while (nodeIter.hasNext()) {
            graph::Node currentNode = nodeIter.next();
            evaluateNode(currentNode, udm_nodes, pass, graph);
        }
    }
}
