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

#ifndef GLOBALS_AND_CONSTANS_H
#define GLOBALS_AND_CONSTANS_H

// this is usually the same as the version of LIM, if not the needs update mostly at Helpers.cpp#L729
#define LIM2PatternsCompatibleVersion "3.0.31"
#define CREATE_PATTERN_WARNING_NAME(name) name + "_warning"
#define DEPTH_TO_SEARCH_IN 3

#define ARUGMENT_1 const asg::base::Base &
#define ARUGMENT_2 const asg::Factory &
#define ARGUMENTS(name1,name2) ARUGMENT_1 name1 , ARUGMENT_2 name2

#include <map>
#include <set>
#include <ctime>
#include <stack>
#include <string>
#include <vector>
#include <chrono>
#include <istream>
#include <typeinfo>
#include <lim/inc/lim.h>
#include <boost/any.hpp>
#include <pybind11/embed.h>
#include <common/inc/Stat.h>
#include <graph/inc/graph.h>
#include <common/inc/FileSup.h>
#include <pybind11/functional.h>
#include <common/inc/WriteMessage.h>
#include <graphsupport/inc/Metric.h>
#include <boost/algorithm/string.hpp>
#include <limmetrics/inc/LimMetrics.h>
#include <yamlcpp/include/yaml-cpp/yaml.h>

#include "messages.h"
#include "../../../lib/graphsupport/inc/GraphConstants.h"
#include "../lib/lim2graph/inc/Lim2GraphConverter.h"
#include "../lib/lim2graph/inc/VisitorGraphConverter.h"

namespace columbus { namespace lim {namespace patterns {
    // {"variable name", {variable to graph, value of variable}}
    typedef std::map<std::string, std::pair<bool, boost::any>> stringAnyLValue;

    /**
    * \brief Converts the given enum type to string, T must be an asg::EnumType that has the corresponding Common::toString(T) converter
    * \param last [in], the last element of the enum
    * \return the converted enum values
    */
    template<class T>
    std::vector<std::string> enumToStringVector(int last)
    {
        std::vector<std::string> values;
        for (int i = 0; i < last; i++) {
            values.push_back(asg::Common::toString(T(i)));
        }
        return values;
    };

    const  std::vector<std::string> validExtensions{ "yaml", "yml", "json", "xml", "py" };

    const std::string
        //DEFINE      = "define",
        //FOR         = "for",
        //IF          = "if",
        CONDITIONS  = "conditions",
        //ELSE        = "else",
        //ELSE_IF     = "elseIf",
        DIRECTION   = "direction",
        FROM        = "from",
        //LOCAL       = "local",
        EDGE        = "edge",
        //CODE_BLOCK  = "codeBlock",
        //CALCULATE   = "calculate",
        TAGS        = "tags",
        FILTERS     = "filters",
        TYPE        = "kind",
        NAME        = "name",
        ROLE        = "role",
        CATEGORY    = "category",
        DISPLAY_NAME= "displayName",
        PRIORITY    = "priority",
        DESCRIPTION = "description",
        FORWARD     = "forward",
        REVERSE     = "reverse";

    const std::set<std::string> priorityValues {
        "Info", "Minor" , "Major" , "Critical", "Blocker"
    };

    enum Direction {
        forward,
        reverse,
        dirLAST
    };

    const std::string
        AND  = "and",
        OR   = "or",
        NAND = "nand",
        NOR  = "nor",
        NOT = "not",
        XOR  = "xor",
        ALL  = "all",
        ANY  = "any",
        EXISTS = "exists";

    const static std::vector<std::string> relationTypes = {
        "<",">","==","~=","<=",">=","!="
    };
    
    enum ConditionTypes {
        less, greater, equal, similar, lessEqual, greaterEqual, notEqual, LAST
    };

    // Specific attributes for lim nodes
    // [{"string", {{NodeKind1, NodeKind2,} , ["string1", "string2"]}}]
    enum limTypes{
        returnType, 
        isAbstract, 
        isAnonymous, 
        isStatic, 
        isVirtual, 
        parameterSize, 
        accessibility, 
        classKind, 
        methodKind, 
        id, 
        name,
        kind,
        paramKind, 
        type,
        simpleTypeKind,
        pointerKind,
        classType,
        parent
    };
    const std::vector<std::string> limTypesString{
        "returnType",
        "isAbstract",
        "isAnonymous",
        "isStatic",
        "isVirtual",
        "parameterSize",
        "accessibility",
        "classKind",
        "methodKind",
        "id",
        "name",
        "kind",
        "paramKind",
        "type",
        "simpleTypeKind",
        "pointerKind",
        "class",
        "parent"
    };
    const std::vector<std::pair<limTypes, std::pair<std::set<lim::asg::NodeKind>, std::vector<std::string>>>> filterTypesAndValues = {
        {returnType, {
            {lim::asg::ndkMethod},
            {/*number*/}
        }},
        {isAbstract, {
            {lim::asg::ndkMethod, lim::asg::ndkClass},
            {"false", "true"}
        }},
        {isAnonymous,{
            {lim::asg::ndkMethod, lim::asg::ndkPackage, lim::asg::ndkClass, lim::asg::ndkScope},
            {"false", "true"}
        }},
        {isStatic, {
            {lim::asg::ndkMethod, lim::asg::ndkAttribute, lim::asg::ndkClass, lim::asg::ndkPackage, lim::asg::ndkScope},
            {"false", "true"}
        }},
        {isVirtual, {
            {lim::asg::ndkMethod},
            {"false", "true"}
        }},
        {parameterSize, {
            {lim::asg::ndkMethod},
            {/*number*/}
        }},
        {accessibility, {
            {lim::asg::ndkMethod, lim::asg::ndkClass, lim::asg::ndkAttribute, lim::asg::ndkPackage, lim::asg::ndkScope},
            enumToStringVector<asg::AccessibilityKind>(asg::AccessibilityKind::ackLAST)
        }},
        {classKind, {
            {lim::asg::ndkClass, lim::asg::ndkClassGeneric},
            enumToStringVector<asg::ClassKind>(asg::ClassKind::clkLAST)
        }},
        {methodKind, {
            {lim::asg::ndkMethod}, 
            enumToStringVector<asg::MethodKind>(asg::MethodKind::mekLAST)
        }},
        {id, {
            {lim::asg::ndkBase, lim::asg::ndkComment, lim::asg::ndkComponent, lim::asg::ndkControlFlowBlock, lim::asg::ndkNamed, lim::asg::ndkAttribute, lim::asg::ndkAttributeAccess, lim::asg::ndkClass, lim::asg::ndkClassGeneric, lim::asg::ndkClassGenericInstance, lim::asg::ndkClassGenericSpec, lim::asg::ndkFriendship, lim::asg::ndkGenericParameter, lim::asg::ndkMember, lim::asg::ndkMethod, lim::asg::ndkMethodCall, lim::asg::ndkMethodGeneric, lim::asg::ndkMethodGenericInstance, lim::asg::ndkMethodGenericSpec, lim::asg::ndkPackage, lim::asg::ndkParameter, lim::asg::ndkScope, lim::asg::ndkFSEntry, lim::asg::ndkFile, lim::asg::ndkFileSystem, lim::asg::ndkFolder, lim::asg::ndkSimpleType, lim::asg::ndkType, lim::asg::ndkTypeFormer, lim::asg::ndkTypeFormerArray, lim::asg::ndkTypeFormerMethod, lim::asg::ndkTypeFormerNonType, lim::asg::ndkTypeFormerPointer, lim::asg::ndkTypeFormerType},
            {/*number*/}
        }},
        {name, {
            {lim::asg::ndkMethod, lim::asg::ndkClass, lim::asg::ndkAttribute, lim::asg::ndkPackage, lim::asg::ndkParameter, lim::asg::ndkFile, lim::asg::ndkFolder, lim::asg::ndkFileSystem},
            {/*string*/}
        }},
        {kind, {
            {lim::asg::ndkBase, lim::asg::ndkComment, lim::asg::ndkComponent, lim::asg::ndkControlFlowBlock, lim::asg::ndkNamed, lim::asg::ndkAttribute, lim::asg::ndkAttributeAccess, lim::asg::ndkClass, lim::asg::ndkClassGeneric, lim::asg::ndkClassGenericInstance, lim::asg::ndkClassGenericSpec, lim::asg::ndkFriendship, lim::asg::ndkGenericParameter, lim::asg::ndkMember, lim::asg::ndkMethod, lim::asg::ndkMethodCall, lim::asg::ndkMethodGeneric, lim::asg::ndkMethodGenericInstance, lim::asg::ndkMethodGenericSpec, lim::asg::ndkPackage, lim::asg::ndkParameter, lim::asg::ndkScope, lim::asg::ndkFSEntry, lim::asg::ndkFile, lim::asg::ndkFileSystem, lim::asg::ndkFolder, lim::asg::ndkSimpleType, lim::asg::ndkType, lim::asg::ndkTypeFormer, lim::asg::ndkTypeFormerArray, lim::asg::ndkTypeFormerMethod, lim::asg::ndkTypeFormerNonType, lim::asg::ndkTypeFormerPointer, lim::asg::ndkTypeFormerType},
            enumToStringVector<asg::NodeKind>(asg::NodeKind::ndkLAST)
        }},
        {paramKind, {
            {lim::asg::ndkParameter},
            enumToStringVector<asg::ParameterKind>(asg::ParameterKind::pmkLAST)
        }},
        {type, {
            {lim::asg::ndkParameter, lim::asg::ndkAttribute, lim::asg::ndkClass, lim::asg::ndkMethod, lim::asg::ndkType},
            {/*number*/}
        }},
        {simpleTypeKind, {
            {lim::asg::ndkSimpleType},
            enumToStringVector<asg::SimpleTypeKind>(asg::SimpleTypeKind::stkLAST)
        }},
        {pointerKind, {
            {lim::asg::ndkTypeFormerPointer},
            enumToStringVector<asg::PointerKind>(asg::PointerKind::ptkLAST)
        }},
        {classType, {
            {lim::asg::ndkType},
            {/*number*/}
        }},
        {parent, {
            {lim::asg::ndkClass, lim::asg::ndkMethod, lim::asg::ndkAttribute, lim::asg::ndkParameter},
            {/*number*/}
        }}
    };
    // all of the possible edges
    const std::vector<std::string> edgesKind = enumToStringVector<asg::EdgeKind>(asg::EdgeKind::edkLAST);
    // all of the possible nodes
    const std::vector<std::string> nodesKind = enumToStringVector<asg::NodeKind>(asg::NodeKind::ndkLAST);

    /**
    * \brief Matchign result storage class
    */
    struct Result {
    private:
        /**
        * \brief Structure to save the values of the node traversal matches
        */
        struct Trace {
            // pattern role name
            std::string role;
            // pattern name
            std::string patternName;
            // node ID of the matched lim node
            uint32_t nodeId;
            // traversal depth
            uint32_t callStackDepth;
            // calculated variables on the node
            //stringAnyLValue variables;
                
            /**
            * \brief Constructor
            */
            Trace(const std::string &_role, const std::string &_patternName, uint32_t _nodeId, uint32_t _callStackDepth/*, stringAnyLValue &_variables*/) ;
            ~Trace();
        };
        std::string outputText;
        // Result trace of the traveled nodes, while searching for the pattern
        std::vector<Trace> traceResult;
        // overall pattern match counter
        uint32_t patternID = 1;
        // match counter for distinct patterns
        std::map<std::string, uint32_t> matchCounter;

        /**
        * \brief Adds an 'intro' text to the output
        * \param _inGraph [in], input Graph
        * \param _base [in]
        * \param _roleName [in], pattern role name of the matching pattern
        * \param depth [in], the depth of the trace
        */
        void addWarningToTxt(graph::Graph &_inGraph, const asg::base::Base &_base, const std::string &_roleName, uint32_t &depth);

        /**
        * \brief Adds an 'intro' text to the output
        * \param inGraph [in], input Graph
        * \param limNode [in]
        * \param patternName [in], the name of the pattern
        * \param depth [in], the depth of the trace
        */
        void addIntroToTxt(graph::Graph &inGraph, const asg::base::Base &limNode, const std::string &patternName, uint32_t &depth);

        /**
        * \brief Add calculated variables on a Node to the output text
        * \param variables [in], calculated variables
        * \param func [in], callback function to convert boost::any to string
        * \param depth [in], the depth of the trace
        */
        //void addCalculatedValuesTxt(const stringAnyLValue &variables, uint32_t depth);


    public:
        Result(std::string _text = "");
            
        /**
        * \brief add Node to result trace
        * \param _base [in], trace Node
        * \param _role [in], pattern node Role name
        * \param _patternName [in], the name of the pattern
        * \param _variables [in], calculated variables on the node
        * \param _depth [in], depth of the trace
        */
        void addNodeToTrace(const int _id, const std::string &_role, const std::string &_patternName, /*stringAnyLValue &_variables,*/ const short &_depth);

        /**
        * \brief Add text to the txt output
        * \param _inGraph [in], input Graph
        * \param _factory [in], input Factory
        * \param func [in], callback function for boost::any conversion
        */
        void finalizeTXTout(graph::Graph &_inGraph, asg::Factory &_factory);

        // TODO:: Calculate remove
        /**
        * \brief Append calculated metric ti the given node
        * \param _inGraph   [in], input Graph
        * \param _node      [in], input Node
        * \param _variables [in], variables to be added
        */
        /**/
        void addMetricToNode(graph::Graph &_inGraph, const asg::base::Base &_base, stringAnyLValue &_variables);

        /**
        * \brief Add pattern matching result to graph
        * \param _inGraph [in], input Graph
        * \param _factory [in], input Factory
        * \param _patternName [in], the name of the matching pattern
        * \param _warningName [in], the name of the Graph warning
        * \param _currentPatternDoc [in], The current pattern document
        * \param _roleName [in], pattern role name of the matching pattern
        * \param _category [in], category name of the pattern
        */
        void finalizeGRAPHout(graph::Graph &_inGraph, asg::Factory &_factory, const std::string &_patternName, const std::string &_warningName, const short &_currentPatternDoc, const std::string &_roleName, const std::string &_category);

        /**
        * \brief Reset the trace
        */
        void reset();

        /**
        * \brief Get the text output of the pattern matches
        * \return trace result as text
        */
        std::string getOutput();

        /**
        * \brief Remove Node from the result trace
        */
        void removeFromTrace(uint32_t nodeId);

        /**
        * \brief Get the total number of the pattern matches
        * \return 
        */
        uint32_t totalMatches();

        /**
        * \brief Get the number of a specific pattern matches
        * \return
        */
        uint32_t matchCount(std::string &patternName);

        /**
        * \brief Get found pattern names
        * \return
        */
        std::set<std::string> getFoundPatternNames() const;
    };

    typedef std::vector<asg::base::Base*> vecOfBase;
    typedef std::map <asg::NodeKind, std::map<asg::EdgeKind, std::function<vecOfBase(ARUGMENT_1, ARUGMENT_2)>>> functionDef;

    // ReturnVal MUST inherited from Basem, ListIt SHOULD be inherited from ListIteratorBase
    /**
    * \brief Cast a list of Nodes into base::Base
    * \param fact     [in], lim factory
    * \param _itBegin [in], list begin iterator
    * \param _itEnd   [in], list end iterator
    * \return LIM list nodes casted to base list
    */
    template<template<class> class ListIt, 
        class ReturnVal, 
        std::enable_if<std::is_base_of<asg::base::Base, ReturnVal>::value>* = nullptr
    >
    static auto castToBaseVector(const lim::asg::Factory &fact, ListIt<ReturnVal> _itBegin, ListIt<ReturnVal> _itEnd) {
        vecOfBase result;
        while (_itBegin != _itEnd) {
            asg::base::Base *_base = fact.getPointer((*_itBegin).getId());
            result.push_back(_base);
            ++_itBegin;
        }
        return result;
    };

    std::set<columbus::NodeId> getSingleTypes(const lim::asg::type::Type &_type, int depth);

    template<template<typename> class ListIt>
    const std::set<NodeId> getNameFromGeneric(const ListIt<lim::asg::type::Type>& begin, const ListIt<lim::asg::type::Type>& end, int depth) {
        auto it = begin;
        std::set<NodeId> _types;
        while (it != end) {
            lim::asg::type::Type &type = (lim::asg::type::Type&)(*it);
            _types = getSingleTypes(type, depth);
            ++it;
        }
        return _types;
    }

    // TODO:: Change this according to the LIM version
    const std::map<asg::NodeKind, asg::NodeKind>& getHierarchies();

    // TODO:: Change this according to the LIM version
    functionDef& getFunctionsDef();

    /**
    * \brief Searches nodes on a given edge (similar to reverseEdges, but instead of searching backwards, it searches foward)
    * \param base [in], starting node
    * \param _edk [in], edge to travel on
    * \return a list of end nodes (can be empty)
    */
    const vecOfBase getIteratorFunctions(const asg::base::Base &base, const asg::EdgeKind &_edk);

    /**
    * Storing rul metadata
    */
    struct RulContainer {
        std::string id;
        std::string name;
        bool enabled;
        std::string group;
        std::string groupMember;
        bool warning;
        std::string helpText;
        std::string &description = helpText;
        RulContainer(const std::string &_id, const std::string &_name, bool _enabled, const std::string &_group = "", const std::string &_groupMember = "", bool _warning = false, const std::string &_helpText = "") :
            id(_id), name(_name), enabled(_enabled), group(_group), groupMember(_groupMember), warning(_warning), helpText(_helpText) {}
    };

    columbus::rul::RulHandler& getPatternRulHander();

    // PatternGroup
    const RulContainer& getMAIN_GROUP(); 
    // AntiPattern
    const RulContainer& getSUB_GROUP1(); 
    // DesignPattern
    const RulContainer& getSUB_GROUP2(); 

    graph::Node limToGraph(graph::Graph &inGraph, const columbus::lim::asg::base::Base& limNode);

    /**
    * \Brief Creates an official columbus Rul
    * \param _rul[in], custom rul metadata
    * \param _metricID[in]
    * \param prioriy[in]
    * \param nodeKind[in]
    */
    void addRulToRulHander(const RulContainer &_rul, const std::string &_metricID = "", const std::string &prioriy = "", const std::set<std::string> nodeKind = {});
        
    //Condition.h
    // save calculateable variables to the role names // would work if it was saved in a Node Condition
    // TODO:: Calculate remove
    std::vector<std::map<std::string, std::pair<uint32_t, bool/*stringAnyLValue*/>>>& getRoleNames();

    /**
    * \brief Helper for pattern checking
    */
    std::vector<std::pair<lim::asg::NodeKind, std::string>>& currentlyIn();

    /**
    * \brief Helper for pattern checking
    */
    std::map<std::string, std::set<std::string>>& getMetricIDsAndCalcFor();
        
    /**
    * \brief Creates and returns a single copy of "Result"
    */
    Result &result();

    /**
    * \brief Helper for Result
    */
    short &calculatedVariablesInNodesDepth();

    /**
    * \brief Helper
    */
    short &currentPatternDocument();

    /**
    * \brief Validates the given edge on the given node (only works for forward/normal edges, doesnt work for reverse edges)
    * \param _edk[in]
    * \param _ndk[in]
    * \return true if edge is valid
    */
    bool validateEdge(asg::EdgeKind &_edk, asg::NodeKind _ndk);

    /**
    * \brief Gives back a list of nodes based on the given edge and direction
    * \param base[in]
    * \param _edk[in]
    * \param reverse[in], travel direction in lim graph
    * \return the found nodes, wrapped in a list
    */
    const vecOfBase getTraversalEdges(const asg::base::Base &base, const asg::EdgeKind &_edk, bool reverse = false);

    /**
    * \brief Adds warnings to graph nodes based on the result of pattern matching
    * \param inGraph[in]
    * \param _base[in]
    * \param patternName[in]
    * \param roleName[in], pattern role name
    * \param description[in], pattern warning description
    * \param displayName[in], pattern name to be displayed on the warning
    * \param priority[in], priority of the pattern warning
    */
    void addWarning(graph::Graph& inGraph, const asg::base::Base &_base, const std::string &patternName, const std::string &roleName, const std::string &category, const std::string &description, const std::string &displayName, const std::string &priority);

    /**
        * \brief Cast the given string into a boost::any type
        * \param value [in], string that's to be converted
        * \return The converted value
    */
    boost::any castStringToBoostAny(const std::string &value);

    /**
        * \brief Special case for returnType and getType
        * \param limNode [in], The lim node where value is located
        * \param compareValueOf [in], the return/type value to compare too
        * \return string value of the found value
    */
    bool findTypeValue(const asg::base::Base& limNodeThis, const asg::base::Base& limNodeCompareTo, int depth = DEPTH_TO_SEARCH_IN);

    bool recursiveNodeKindSearching(const asg::NodeKind ndk1, const asg::NodeKind ndk2);

    /**/
    std::string getValue(graph::Graph &inGraph, const std::string &valueToFind, const asg::base::Base& nodeToFindIn);

    lim::asg::EdgeKind getEdgeKind(const std::string &_edge);
    lim::asg::NodeKind getNodeKind(const std::string &_ndk);

}}}
#endif // !GLOBALS_AND_CONSTANS_H
