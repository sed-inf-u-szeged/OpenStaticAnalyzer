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

#ifndef _UDM_FUNC_
#define _UDM_FUNC_

#include "UdmCommon.h"
#include "graph/inc/graph.h"
#include "graphsupport/inc/GraphConstants.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace columbus;
using namespace common;

typedef typename exprtk::igeneric_function<long double>::parameter_list_t parameter_list_t;
typedef typename exprtk::igeneric_function<long double>::generic_type generic_type;
typedef typename generic_type::string_view string_t;

class SUM;
class AVG;
class MIN;
class MAX;

class UdmFunction : public exprtk::igeneric_function<long double> {

private:

    const string functionName;

    // First store the childTypes, second the reqMetric of an aggr function in the formula
    vector<pair<set<string>, string>>* aggrCalcFors;

    // Split the genString and fill childType, call resolveKind and checkChildType
    set<string> processChildTypes(const string_t& genString);
    
    // Collecting relevant Nodes (specified in childType) to the relevantChildren
    void getRelevantChildren(set<graph::Node>& relevantChildren, const graph::Node& node, const set<string>& childTypes, const bool& fullrecursive, int numOfLevels);
    
    // Resolving predefined Kinds
    set<string> resolveKind(set<string>& childTypes);
    
    // Checking if childType contains the type of the Node
    inline bool isRelevant(const graph::Node& node, const set<string>& childTypes);

    // Throws an exception, if any of the childTypes is different from the predefined ones
    void checkChildTypes(set<string>& childTypes);

protected:

    const graph::Node node;
    
    // Get the collected values and do some calculation
    virtual long double aggr(const vector<long double>& metricsValues) = 0;

public:

    // "SSS" means the exprtk::igeneric_function has 3 string parameters, the parser compile only if it's true
    UdmFunction(const graph::Node& node, const string functionName, vector<pair<set<string>, string>>* aggrCalcFors) : exprtk::igeneric_function<long double>("SSS"), functionName(functionName), aggrCalcFors(aggrCalcFors), node(node) {}

    // Main logic, called to calculate the function's value
    long double operator ()(parameter_list_t parameters);
    
    // Inserting the defined functions into the symbolTable 
    class Inserter {

    private:

        SUM *sum;
        AVG *avg;
        MIN *min;
        MAX *max;

    public:

        Inserter(exprtk::symbol_table<long double>& symbolTable, const graph::Node& node, vector<pair<set<string>, string>>* aggrCalcFors = NULL);
        ~Inserter();
    };
    
    const string& getName() const;
    
};

class SUM : public UdmFunction {

protected:

    long double aggr(const vector<long double>& metricsValues);

public:

    SUM(const graph::Node& node, vector<pair<set<string>, string>>* aggrCalcFors) : UdmFunction(node, "SM_SUM", aggrCalcFors) {}
};


class AVG : public UdmFunction {

protected:

    long double aggr(const vector<long double>& metricsValues);

public:

    AVG(const graph::Node& node, vector<pair<set<string>, string>>* aggrCalcFors) : UdmFunction(node, "SM_AVG", aggrCalcFors) {}
};


class MIN : public UdmFunction {

protected:

    long double aggr(const vector<long double>& metricsValues);

public:

    MIN(const graph::Node& node, vector<pair<set<string>, string>>* aggrCalcFors) : UdmFunction(node, "SM_MIN", aggrCalcFors) {}
};


class MAX : public UdmFunction {

protected:

    long double aggr(const vector<long double>& metricsValues);

public:

    MAX(const graph::Node& node, vector<pair<set<string>, string>>* aggrCalcFors) : UdmFunction(node, "SM_MAX", aggrCalcFors) {}
};


#endif