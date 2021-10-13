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

#ifndef PYTHON_ADAPTER_H
#define PYTHON_ADAPTER_H

#include "Conditions/Checker/PatternValidator.h"
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/operators.h>

#define CALLBACK_ARGS NodeBinding

namespace py = pybind11;

namespace columbus { namespace lim { namespace patterns { namespace pythonBinding {

    class NodeBinding;
    
    typedef std::function<py::object(CALLBACK_ARGS)> Callback;

    class NodeBinding {
    private:
        /** \brief Factory container*/
        lim::asg::Factory &factory;
        /** \brief Graph container*/
        graph::Graph &graph;
        /** \brief Base container*/
        const lim::asg::base::Base &base;
        /**
         * \brief Processes the python dictionary while searching for children node recursively
         * \param children        [in], dictionary of childtren nodes
         * \param roleName        [in], role name for the output generation
         * \param patternName    [in], pattern name for the output generation
         * \param depth            [in], child depth, def. value is 0
         */
        void addChildrenToTrace(const py::dict &children, const std::string &roleName, int depth = 0) const;
    
    public:


        static std::string castPyToString(py::object &_object);
        NodeBinding(const asg::base::Base* _base, graph::Graph &_graph);
        NodeBinding(const asg::base::Base& _base, graph::Graph &_graph);
        NodeBinding(const NodeBinding &_nodeBinding);
        NodeBinding(const NodeBinding *_nodeBinding);

        NodeBinding operator=(NodeBinding &_nodeBinding);
        NodeBinding operator=(NodeBinding *_nodeBinding);

        /**
         * \brief Recursively searches for nodekind
         * \return 
         */
        bool is(const py::str &nodeKind) const;

        /**
         * \brief Gives back the type of a the lim base node
         * \return Returns a wrapped base node in NodeBinding
         */
        NodeBinding getType() const;

        /**
         * \brief Gives back the class of a the lim type node
         * \return Returns a wrapped base node in NodeBinding
         */
        NodeBinding getClass() const;

        /**
         * \brief Gives back the parent of a the lim node (only works for Class, Method, Parameter, Attribute)
         * \return Returns a wrapped base node in NodeBinding
         */
        NodeBinding getParent() const;

        /**
         * \brief Searches by the given value in graph, lim
         * \param _value [in], the searchable value
         * \return returns the found value, or throws
         */
        py::object getValuePy(const py::str &_value) const;

        /**
         * \brief Travels throught the given edge, and calls the callback for every visited edge node
         * \param _edge    [in], The name of the edge
         * \param callback [in], The python callback function (the callback must have a NodeBinding parameter)
         * \param reverse  [in], The direction of the visiting
         */
        void traverse(const py::str &_edge, Callback callback, const py::str &ndk = "ndkBase", bool reverse = false) const;

        /**
         * \brief Travels throught the given edge, and calls the callback for every visited edge node
         * \param _edge    [in], The name of the edge
         * \param callback [in], The python callback function (the callback must have a NodeBinding parameter)
         * \param reverse  [in], The direction of the visiting
         */
        void traverse(const lim::asg::EdgeKind &_edge, Callback callback, const lim::asg::NodeKind &ndk, bool reverse = false) const;

        /**
         * \brief Collects every node by the given edge name
         * \param _edge    [in], The name of the edge
         * \param reverse  [in], The direction of the visiting
         * \return returns an array of nodes, wrapped in NodeBinding
         */
        std::vector<CALLBACK_ARGS> traverse(const py::str &edge, const py::str &ndk = "ndkBase", bool reverse = false) const;

        /**
         * \brief Collects every node by the given edge name
         * \param _edge    [in], The name of the edge
         * \param reverse  [in], The direction of the visiting
         * \return returns an array of nodes, wrapped in NodeBinding
         */
        std::vector<CALLBACK_ARGS> traverse(const lim::asg::EdgeKind &_edge, const lim::asg::NodeKind &ndk, bool reverse = false) const;

        /**
         * \brief Compares 'this' to the given type (similar to operator==), exact match eg. vector<set<int>> == vector<set<float>> will returns false
         * \param compareToValue [in]
         * \return true if equals
         */
        bool type_equal(const float compareToValue) const;

        /**
         * \brief Compares 'this' to the given type (similar to operator==), exact match eg. vector<set<int>> == vector<set<float>> will returns false
         * \param compareToValue [in]
         * \return true if equals
         */
        bool type_equal(const int compareToValue) const;

        /**
         * \brief Compares 'this' to the given type (similar to operator==), exact match eg. vector<set<int>> == vector<set<float>> will returns false
         * \param compareToValue [in]
         * \return true if equals
         */
        bool type_equal(const NodeBinding &compareToValue) const;


        /**
         * \brief Compares 'this' to the given type (similar to operator==), exact match eg. vector<set<int>> == vector<set<float>> will returns true
         * \param compareToValue  [in]
         * \param depthToSearchIn [in] , the number of abstraction we consider to search in, default value is 3
         * \return true if similar
         */
        bool type_similar(const float compareToValue, int depthToSearchIn = DEPTH_TO_SEARCH_IN) const;

        /**
         * \brief Compares 'this' to the given type (similar to operator==), exact match eg. vector<set<int>> == vector<set<float>> will returns true
         * \param compareToValue  [in]
         * \param depthToSearchIn [in] , the number of abstraction we consider to search in, default value is 3
         * \return true if similar
         */
        bool type_similar(const int compareToValue, int depthToSearchIn = DEPTH_TO_SEARCH_IN) const;

        /**
         * \brief Compares 'this' to the given type (similar to operator==), exact match eg. vector<set<int>> == vector<set<float>> will returns true
         * \param compareToValue  [in]
         * \param depthToSearchIn [in] , the number of abstraction we consider to search in, default value is 3
         * \return true if similar
         */
        bool type_similar(const NodeBinding &compareToValue, int depthToSearchIn = DEPTH_TO_SEARCH_IN) const;


        /**
         * \brief sets a warning on a Graph node
         * \param patternName  [in]
         * \param roleName     [in]
         * \param children     [in], python dictionaries containing the children nodes
         * \param displayName  [in]
         * \param category     [in]
         * \param description  [in]
         */
        void setWarning(const py::str &patternName, const py::str &roleName, const py::dict &children, const py::str &displayName = "", const py::str &category = "DesignPattern", const py::str &priority = "Info", const py::str &description = "") const;
        
        /**
         * \brief sets a warning on a Graph node
         * \param patternName  [in]
         * \param roleName     [in]
         * \param displayName  [in]
         * \param category     [in]
         * \param description  [in]
         */
        void setWarning(const py::str &patternName, const py::str &roleName, const py::str &displayName = "", const py::str &category = "DesignPattern", const py::str &priority = "Info", const py::str &description = "") const;
        
        /**
         * \brief Sets an attribute in a node
         * \param key   [in], the name of the attribute
         * \param value [in], the value of the attribute
         */
        void setMetric(const py::str &key, py::object value);

        /**
         * \brief Sets an attribute in a node as AttributeString
         * \param key   [in], the name of the attribute
         * \param value [in], the value of the attribute
         */
        void setMetric(const std::string &key, const std::string &value);

        /**
         * \brief Sets an attribute in a node as AttributeFloat
         * \param key   [in], the name of the attribute
         * \param value [in], the value of the attribute
         */
        void setMetric(const std::string &key, const float value);

        /**
         * \brief Sets an attribute in a node as AttributeInt
         * \param key   [in], the name of the attribute
         * \param value [in], the value of the attribute
         */
        void setMetric(const std::string &key, const int value);

        /**
         * \brief Sets an attribute in a node as AttributeString
         * \param key   [in], the name of the attribute
         * \param value [in], the value of the attribute
         */
        void setMetric(const std::string &key, const bool value);

        /**
         * \brief Converts the class into readable std::string
         * \return
         */
        std::string toString() const;

        /**
         * \brief Not equal operator overloading, compares lim node id's to each other
         * \param other [in], The NodeBinding to be compared to
         * \return true if not equals
         */
        bool operator!=(const NodeBinding &other) const;

        /**
         * \brief Not equal operator overloading, compares lim node id's to each other
         * \param other [in], The NodeBinding to be compared to
         * \return true if equals
         */
        bool operator==(const NodeBinding &other) const;
    };

}}}}

#endif