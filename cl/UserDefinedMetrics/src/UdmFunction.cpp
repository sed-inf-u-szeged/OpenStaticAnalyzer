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

#include "../inc/UdmFunction.h"

long double UdmFunction::operator()(parameter_list_t parameters) {

    // Processing the parameters, defined by the user

    set<string> childTypes = processChildTypes(string_t(parameters[0]));

    string reqMetric = exprtk::to_str(string_t(parameters[1]));

    // Collecting the metric and ChildTypes for checking CalcFors attrs and building dependency
    
    if (aggrCalcFors != NULL) {
        aggrCalcFors->push_back(pair<set<string>, string>(childTypes,reqMetric));
        
    }

    // Checking if the Node is invalid
    
    if (node == graph::Graph::invalidNode) { return 0; }
    
    // Processing recursive parameter

    bool fullrecursive = false;
    int numOfLevels = 1;
    string definedLevel = exprtk::to_str(string_t(parameters[2]));
    boost::algorithm::to_lower(definedLevel);
    
    if (definedLevel == "true") {
        // 3rd param was true
        fullrecursive = true;
    }
    else {

        // if 3rd param was false nothing todo, bc default values
        if (definedLevel != "false") {
            // 3rd param was a number
            try {
            
                numOfLevels = boost::lexical_cast<int>(definedLevel);
            }
            catch (boost::bad_lexical_cast&) {

                warning = true;
                WriteMsg::write(CMSG_UDM_INVALID_REC_DEF, definedLevel.c_str());
            }
        }
    }

    // Collecting the relevant Nodes

    set<graph::Node> relevantChildren;
    getRelevantChildren(relevantChildren, this->node, childTypes, fullrecursive, numOfLevels - 1);

    // Collecting it's metrics

    vector<long double> derivedMetricValues;

    for (const graph::Node& node : relevantChildren) {

        graph::Attribute::AttributeIterator attrIt = node.findAttributeByName(reqMetric);
        if (attrIt.hasNext()) {

            graph::Attribute& attr = attrIt.next();

            if (attr.getType() == graph::Attribute::atInt || attr.getType() == graph::Attribute::atFloat) {

                long double a;
                if (attr.getType() == graph::Attribute::atInt) {

                    graph::AttributeInt& aInt = dynamic_cast<graph::AttributeInt&>(attr);
                    a = aInt.getValue();
                }
                else {

                    graph::AttributeFloat& aFloat = dynamic_cast<graph::AttributeFloat&>(attr);
                    a = aFloat.getValue();
                }

                derivedMetricValues.push_back(a);
            }
        }
    }

    if (derivedMetricValues.empty()) {

        return 0;
    }

    // Calling the derived Class aggregate function

    return aggr(derivedMetricValues);
}

const string& UdmFunction::getName() const{

    return functionName;
}

long double SUM::aggr(const vector<long double>& metricsValues) {

    long double result = 0;
    for (const long double& value : metricsValues) {

        result += value;
    }

    return result;
}


long double AVG::aggr(const vector<long double>& metricsValues) {

    if (metricsValues.empty()) {
        return 0;
    }
    long double result = 0;
    for (const long double& value : metricsValues) {

        result += value;
    }

    return result / metricsValues.size();
}

long double MAX::aggr(const vector<long double>& metricsValues) {

    if (metricsValues.empty()) {
        return 0;
    }
    long double max = metricsValues[0];

    for (const long double& value : metricsValues) {

        if (value > max) {

            max = value;
        }
    }

    return max;
}

long double MIN::aggr(const vector<long double>& metricsValues) {

    if (metricsValues.empty()) {
        return 0;
    }
    long double min = metricsValues[0];
    for (const long double& value : metricsValues) {

        if (value < min) {

            min = value;
        }
    }

    return min;
}

UdmFunction::Inserter::Inserter(exprtk::symbol_table<long double>& symbolTable, const graph::Node& node, vector<pair<set<string>, string>>* aggrCalcFors) {

    sum = new SUM(node, aggrCalcFors);
    avg = new AVG(node, aggrCalcFors);
    min = new MIN(node, aggrCalcFors);
    max = new MAX(node, aggrCalcFors);

    if (!symbolTable.add_function(sum->getName(), *sum)) { WriteMsg::write(CMSG_UDM_CANT_ADD_FUNCTION, sum->getName()); }
    if (!symbolTable.add_function(avg->getName(), *avg)) { WriteMsg::write(CMSG_UDM_CANT_ADD_FUNCTION, avg->getName()); }
    if (!symbolTable.add_function(min->getName(), *min)) { WriteMsg::write(CMSG_UDM_CANT_ADD_FUNCTION, min->getName()); }
    if (!symbolTable.add_function(max->getName(), *max)) { WriteMsg::write(CMSG_UDM_CANT_ADD_FUNCTION, max->getName()); }

}

UdmFunction::Inserter::~Inserter() {

    delete sum;
    delete avg;
    delete min;
    delete max;
}

set<string> UdmFunction::processChildTypes(const string_t& genString) {

    set<string> result;
    vector<string> tempVect;
    string temp = exprtk::to_str(genString);
    // Split the string 
    boost::split(tempVect, temp, boost::is_any_of(","));
    for (string& str : tempVect) {
        set<string>::iterator a;
        // Removing whitespaceses
        boost::algorithm::trim(str);
        result.insert(str);
    }

    result = resolveKind(result);
    checkChildTypes(result);
    return result;
}

set<string> UdmFunction::resolveKind(set<string>& childTypes) {

    // Predefined Kinds

    using namespace graphsupport::graphconstants;
    map<string, vector<string>> kindMap;
    kindMap["PackageKind"] = { NTYPE_LIM_PACKAGE, NTYPE_LIM_MODULE, NTYPE_LIM_NAMESPACE };
    kindMap["ClassKind"] = { NTYPE_LIM_CLASS, NTYPE_LIM_STRUCTURE, NTYPE_LIM_UNION, NTYPE_LIM_INTERFACE, NTYPE_LIM_ENUM, NTYPE_LIM_CLASSDEF, NTYPE_LIM_ANNOTATION };
    kindMap["MethodKind"] = {NTYPE_LIM_FUNCTION, NTYPE_LIM_FUNCTIONDEF, NTYPE_LIM_FUNCTIONMEMBER, NTYPE_LIM_METHOD, NTYPE_LIM_METHODDEF};

    set<string> result;

    for (const string& childType : childTypes ) {

        // If the map contains the value inserting the vector's elements, else the value
        if (kindMap.find(childType) != kindMap.end()) {
            result.insert(UDM_EXPANDED);
            vector<string>& childVector = kindMap.find(childType)->second;
            for (const string& child : childVector) {

                result.insert(child);
            }
        }
        else {
            result.insert(childType);
        }
    }

    return result;
}

void UdmFunction::getRelevantChildren(set<graph::Node>& relevantChildren, const graph::Node& node, const set<string>& childTypes, const bool& fullrecursive, int numOfLevels) {

    static graph::Edge::EdgeType type(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::eDirectionType::edtDirectional);
    graph::Edge::EdgeIterator eIt = node.findOutEdges(type);

    while (eIt.hasNext()) {

        graph::Edge edge = eIt.next();
        graph::Node derivednode = edge.getToNode();

        if (isRelevant(derivednode, childTypes)) {

            auto it = relevantChildren.insert(derivednode);
            if (it.second && (fullrecursive || numOfLevels > 0)) {

                getRelevantChildren(relevantChildren, derivednode, childTypes, fullrecursive, numOfLevels - 1);
            }
        }
    }
}

inline bool UdmFunction::isRelevant(const graph::Node& node, const set<string>& childTypes) {

    return (find(childTypes.begin(), childTypes.end(), "ALL")) != childTypes.end() ||
        (find(childTypes.begin(), childTypes.end(), node.getType().getType())) != childTypes.end();

}

void UdmFunction::checkChildTypes(set<string>& childTypes) {

    using namespace graphsupport::graphconstants;
    static vector<string> types = { NTYPE_DCF_CLONECLASS, NTYPE_DCF_CLONEINSTANCE, NTYPE_LIM_ANNOTATION, NTYPE_LIM_ATTRIBUTE, NTYPE_LIM_CLASS, NTYPE_LIM_CLASSDEF, NTYPE_LIM_COMPONENT, NTYPE_LIM_ENUM, NTYPE_LIM_FILE,
        NTYPE_LIM_FILESYSTEM, NTYPE_LIM_FOLDER, NTYPE_LIM_FUNCTION, NTYPE_LIM_FUNCTIONDEF, NTYPE_LIM_FUNCTIONMEMBER, NTYPE_LIM_INTERFACE, NTYPE_LIM_METHOD, NTYPE_LIM_METHODDEF, NTYPE_LIM_MODULE, NTYPE_LIM_NAMESPACE,
        NTYPE_LIM_PACKAGE, NTYPE_LIM_PROCEDURE, NTYPE_LIM_ROOT, NTYPE_LIM_SOURCEFILE, NTYPE_LIM_STRUCTURE, NTYPE_LIM_UNION, "ALL" };
    
    for (const string& str : childTypes) {
        if (find(types.begin(), types.end(), str) == types.end() && str != UDM_EXPANDED) {

            throw InvalidChildTypeEx(str);
        }
    }
}
