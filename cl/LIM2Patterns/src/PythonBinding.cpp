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

#include "../inc/PythonBinding.h"
#include "../inc/Conditions/Conditions.h"
#include <type_traits>
#define strdup _strdup


#define OVERLOAD(...) py::overload_cast<__VA_ARGS__>
#define METHOD(...) (&NodeBinding::__VA_ARGS__)
#define CONST_METHOD(name) METHOD(name, py::const_)

namespace columbus { namespace lim { namespace patterns { namespace pythonBinding {
    using namespace std;
    using namespace asg;
    using namespace patterns::conditions;
    using namespace columbus::graphsupport::graphconstants;

    string NodeBinding::castPyToString(py::object &_ojbect) {
        const auto stringType = py::str().get_type();
        const auto intType = py::int_().get_type();
        const auto floatType = py::float_().get_type();
        const auto boolType = py::bool_().get_type();
        auto _valType = _ojbect.get_type();
        string message;

        if (_valType.is(intType)) {
            message = to_string(_ojbect.cast<int>());
        }
        else if (_valType.is(floatType)) {
            message = to_string(_ojbect.cast<float>());
        }
        else if (_valType.is(boolType)) {
            message = _ojbect.cast<bool>() ? "true" : "false";
        }
        else if (_valType.is(stringType)) {
            message = _ojbect.cast<string>();
        }
        else {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("Invalid return type!"));
        }

        return message;
    }

    NodeBinding::NodeBinding(const base::Base *_base, graph::Graph &_graph) : factory(_base->getFactory()), graph(_graph), base(*_base) { }
    NodeBinding::NodeBinding(const base::Base &_base, graph::Graph &_graph) : factory(_base.getFactory()),  graph(_graph), base(_base) { }

    NodeBinding::NodeBinding(const NodeBinding &_nodeBinding) : factory(_nodeBinding.factory), graph(_nodeBinding.graph), base(_nodeBinding.base) {}
    NodeBinding::NodeBinding(const NodeBinding *_nodeBinding) : factory(_nodeBinding->factory), graph(_nodeBinding->graph), base(_nodeBinding->base) {}
    
    NodeBinding NodeBinding::operator=(NodeBinding &_nodeBinding) {return NodeBinding(_nodeBinding);}
    NodeBinding NodeBinding::operator=(NodeBinding *_nodeBinding) {return NodeBinding(_nodeBinding);}

    bool NodeBinding::is(const py::str &nodeKind) const {
        string ndk = nodeKind;
        NodeKind typeName = getNodeKind(ndk);

        return recursiveNodeKindSearching(this->base.getNodeKind(), typeName);
    }
    
    NodeBinding NodeBinding::getType() const {
        int typeID = getValuePy("type").cast<int>();
        if (typeID == -1) throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("No 'Type' were found for [" + to_string(this->base.getId()) + "] node"));
        return NodeBinding(this->factory.getRef(typeID), this->graph);
    }

    NodeBinding NodeBinding::getClass() const {
        int typeID = getValuePy("class").cast<int>();
        return NodeBinding(this->factory.getRef(typeID), this->graph);
    }

    NodeBinding NodeBinding::getParent() const {
        int typeID = getValuePy("parent").cast<int>();
        return NodeBinding(this->factory.getRef(typeID), this->graph);
    }

    py::object NodeBinding::getValuePy(const py::str &_value) const {
        string _val = getValue(this->graph, _value, this->base);

        if (_val == columbus::graphsupport::graphconstants::ATTRVALUE_INVALID){
            string msg = "Metric '" + _value.cast<string>() + "'  is not applicable on node 'L" + std::to_string(this->base.getId()) + "'\n";
            common::WriteMsg::write(common::WriteMsg::mlWarning, msg.c_str());
            return py::cast(INT16_MIN);
        }

        auto value = castStringToBoostAny(_val);
        
        if (value.type() == typeid(int)) {
            return py::cast(boost::any_cast<int>(value));
        }
        else if (value.type() == typeid(float)) {
            return py::cast(boost::any_cast<float>(value));
        }
        else if (value.type() == typeid(double)) {
            return py::cast(boost::any_cast<double>(value));
        }
        else if (value.type() == typeid(bool)) {
            return py::cast(boost::any_cast<bool>(value));
        }
        else {
            string val = boost::any_cast<string>(value);
            return val == "true" ? py::cast(true) : (val == "false" ? py::cast(false) : py::cast(val));
        }
    }

    void NodeBinding::traverse(const py::str & _edge, Callback callback, const py::str &ndk, bool reverse) const {
        auto edgeKind = getEdgeKind(_edge);
        auto nodeKind = getNodeKind(ndk);
        traverse(edgeKind, callback, nodeKind, reverse);
    }
    void NodeBinding::traverse(const EdgeKind &_edge, Callback callback, const lim::asg::NodeKind &ndk, bool reverse) const {
        if (callback != nullptr) {
            const auto &nodes = getTraversalEdges(this->base, _edge, reverse);
            for (size_t index = 0; index < nodes.size(); index++) {
                if (recursiveNodeKindSearching(nodes[index]->getNodeKind(), ndk)) {
                    callback(NodeBinding(nodes[index], this->graph));
                }
            }
        }
        else {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("Callback function must be defined!"));
        }
    }

    vector<CALLBACK_ARGS> NodeBinding::traverse(const py::str &edge, const py::str &ndk, bool reverse) const {
        auto edgeKind = getEdgeKind(edge);
        auto nodeKind = getNodeKind(ndk);
        return traverse(edgeKind, nodeKind, reverse);
    }
    vector<CALLBACK_ARGS> NodeBinding::traverse(const EdgeKind &_edge, const lim::asg::NodeKind &ndk, bool reverse) const {
        vector<CALLBACK_ARGS> ret;
        auto nodes = getTraversalEdges(this->base, _edge, reverse);
        auto it = nodes.begin();
        while (it != nodes.end()) {
            if (recursiveNodeKindSearching((*it)->getNodeKind(), ndk)) {
                ret.push_back(NodeBinding(*it, this->graph));
            }
            it++;
        }
        return ret;
    }

    bool NodeBinding::type_equal(const float compareToValue) const {
        return this->type_equal((int)ceil(compareToValue));
    }
    bool NodeBinding::type_equal(const int compareToValue) const {
        string thisType = getValue(this->graph,"type", this->base);
        string otherType = to_string(compareToValue);
        return !thisType.empty() && !otherType.empty() && thisType != "-1" && otherType != "-1" && thisType == otherType;
    }
    bool NodeBinding::type_equal(const NodeBinding &compareToValue) const {
        int _compareToValue = Common::getIsType(compareToValue.base) ? compareToValue.base.getId() : compareToValue.getValuePy("type").cast<int>();
        return this->type_equal(_compareToValue);
    }

    bool NodeBinding::type_similar(const float compareToValue, int depthToSearchIn) const {
        return this->type_similar((int)compareToValue, depthToSearchIn);
    }
    bool NodeBinding::type_similar(const int compareToValue, int depthToSearchIn) const {
        return findTypeValue(this->base, this->factory.getRef(compareToValue), depthToSearchIn);
    }
    bool NodeBinding::type_similar(const NodeBinding &compareToValue, int depthToSearchIn) const {
        NodeId _compareToValue = Common::getIsType(compareToValue.base) ? compareToValue.base.getId() : compareToValue.getValuePy("type").cast<int>();
        return this->type_similar((int)this->factory.getRef(_compareToValue).getId(), depthToSearchIn);
    }

        
    void NodeBinding::addChildrenToTrace(const py::dict &children, const string &roleName, int depth) const{
        
        const auto stringType = py::str().get_type();
        const auto arrayType = py::cast(vector<py::dict>()).get_type();
        const auto nodeType = py::cast(*this).get_type();

        for (auto &_pair : children) {
            const auto &key = _pair.first;
            const auto &value = _pair.second;
            const string _key = key.cast<string>();
            auto _keyType = key.get_type();
            auto _valType = value.get_type();

            if (!_keyType.is(stringType)) {
                // error, key must be string
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("Key must be a string/text!"));
            }

            if (_key == "node" || _key != "children") {
                string _roleName = _key == "node" ? roleName : _key;
                if (_valType.is(nodeType)) {
                    int _baseID = (value.cast<NodeBinding>()).base.getId();
                    result().addNodeToTrace(_baseID, _roleName, "", depth);
                }
                else if (_valType.is(arrayType)) {
                    auto _array = value.cast<vector<py::object>>();

                    for (auto &element : _array) {
                        if (element.get_type().is(nodeType)) {
                            int _baseID = (element.cast<NodeBinding>()).base.getId();
                            result().addNodeToTrace(_baseID, _roleName, "", depth);

                            if (children.contains("children"))
                                this->addChildrenToTrace(children["children"], _roleName, depth + 1);

                        }
                        else {
                            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("Value in array must be 'NodeBinding'!"));
                        }
                    }
                }
            }
        }
    }

    void NodeBinding::setWarning(const py::str & patternName, const py::str & roleName, const py::dict &children, const py::str &displayName, const py::str & category, const py::str & priority, const py::str &description) const {
        
        result().addNodeToTrace(this->base.getId(), roleName, patternName, 0);

        addChildrenToTrace(children, roleName, 1);

        addWarning(this->graph, this->base, patternName, roleName, category, description, displayName, priority);

        result().reset();
    }

    void NodeBinding::setWarning(const py::str & patternName, const py::str & roleName, const py::str &displayName, const py::str & category, const py::str & priority, const py::str &description) const {
        this->setWarning(patternName, roleName, {}, displayName, category, priority, description);
    }

    void NodeBinding::setMetric(const py::str &key, py::object value) {
        auto _type = value.get_type();
        if (_type.is(py::int_().get_type())) {
            this->setMetric(key, value.cast<int>());
        }
        else if (_type.is(py::float_().get_type())) {
            this->setMetric(key, value.cast<float>());
        }
        else if (_type.is(py::bool_().get_type())) {
            this->setMetric(key, value.cast<bool>());
        }
        else if (_type.is(py::str().get_type())) {
            this->setMetric(key, value.cast<string>());
        }
        else {
            throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("Metric value must be number/decimal/test/bool!"));
        }
    }

    void NodeBinding::setMetric(const string &key, const string &value) {
        if (Common::getIsMember(this->base)) {
            const graph::Node &_node = limToGraph(this->graph, this->base);
            auto attrFloat = graph.createAttributeString(key, CONTEXT_METRIC, value);
            graphsupport::addAttributeOnce(_node, attrFloat, true);
        }
    }

    void NodeBinding::setMetric(const string &key, const float value) {
        if (Common::getIsMember(this->base)) {
            const graph::Node &_node = limToGraph(this->graph, this->base);
            auto attrFloat = graph.createAttributeFloat(key, CONTEXT_METRIC, value);
            graphsupport::addAttributeOnce(_node, attrFloat, true);
        }
    }

    void NodeBinding::setMetric(const string &key, const int value) {
        if (Common::getIsMember(this->base)) {
            const graph::Node &_node = limToGraph(this->graph, this->base);
            auto attrFloat = graph.createAttributeInt(key, CONTEXT_METRIC, value);
            graphsupport::addAttributeOnce(_node, attrFloat, true);
        }
    }

    void NodeBinding::setMetric(const string &key, const bool value) {
        string val = value ? "true" : "false";
        this->setMetric(key, val);
    }

    string NodeBinding::toString() const {
        return "<PythonBinding.NodeBinding object, node '" + this->getValuePy("kind").cast<string>() + "' id '" + to_string(this->getValuePy("id").cast<int>()) + "'>";
    }


    bool NodeBinding::operator!=(const NodeBinding &other) const {
        return !(*this == other);
    }
    bool NodeBinding::operator==(const NodeBinding &other) const {
        return this->base.getId() == other.base.getId();
    }


    PYBIND11_EMBEDDED_MODULE(PythonBinding, m) {
        py::class_<NodeBinding>(m, "NodeBinding")
            .def(py::init<const NodeBinding&>())
            .def(py::init<const NodeBinding*>())

            .def("getValue",     OVERLOAD(const py::str&) CONST_METHOD(getValuePy), py::arg("value"))
            .def("getType",      OVERLOAD()               CONST_METHOD(getType))
            .def("getClass",     OVERLOAD()               CONST_METHOD(getClass))
            .def("getParent",    OVERLOAD()               CONST_METHOD(getParent))

            .def("traverse",    OVERLOAD(const py::str&, Callback, const py::str&, bool)    CONST_METHOD(traverse), py::return_value_policy::reference, py::arg("edge"), py::arg("callback"), py::arg("kind") = std::string("ndkBase"), py::arg("reverse") = false)
            .def("traverse",    OVERLOAD(const py::str&,           const py::str&, bool)    CONST_METHOD(traverse), py::return_value_policy::reference, py::arg("edge"),                      py::arg("kind") = std::string("ndkBase"), py::arg("reverse") = false)

            .def("typeEquals",   OVERLOAD(const float)           CONST_METHOD(type_equal), py::arg("nodeId"))
            .def("typeEquals",   OVERLOAD(const int)             CONST_METHOD(type_equal), py::arg("nodeId"))
            .def("typeEquals",   OVERLOAD(const NodeBinding&)    CONST_METHOD(type_equal), py::arg("node"))

            .def("typeSimilar", OVERLOAD(const float, const int)        CONST_METHOD(type_similar), py::arg("nodeId"), py::arg("depthToSearchIn") = DEPTH_TO_SEARCH_IN)
            .def("typeSimilar", OVERLOAD(const int,   const int)        CONST_METHOD(type_similar), py::arg("nodeId"), py::arg("depthToSearchIn") = DEPTH_TO_SEARCH_IN)
            .def("typeSimilar", OVERLOAD(const NodeBinding&, const int) CONST_METHOD(type_similar), py::arg("node"),   py::arg("depthToSearchIn") = DEPTH_TO_SEARCH_IN)

            .def("setMetric",    OVERLOAD(const py::str&, py::object)  METHOD(setMetric), py::arg("name"), py::arg("value"))

            .def("setWarning",   OVERLOAD(const py::str &, const py::str &, const py::dict &, const py::str &, const py::str &, const py::str &, const py::str &)    CONST_METHOD(setWarning), py::arg("patternName"), py::arg("roleName"), py::arg("children"), py::arg("displayName") = std::string(""), py::arg("category") = std::string("DesignPattern"), py::arg("priority") = std::string("Info"), py::arg("description") = std::string(""))
            .def("setWarning",   OVERLOAD(const py::str &, const py::str &,                   const py::str &, const py::str &, const py::str &, const py::str &)    CONST_METHOD(setWarning), py::arg("patternName"), py::arg("roleName"),                      py::arg("displayName") = std::string(""), py::arg("category") = std::string("DesignPattern"), py::arg("priority") = std::string("Info"), py::arg("description") = std::string(""))

            .def("toString",     OVERLOAD()  CONST_METHOD(toString))

            .def("instanceOf",   OVERLOAD(const py::str &)  CONST_METHOD(is), py::arg("nodeKind"))
            .def(py::self == py::self)
            .def(py::self != py::self)
            .def("__repr__",     OVERLOAD()  CONST_METHOD(toString)); // for python print(NodeBindingClass)

        static py::exception<columbus::Exception> exc(m, "Python Exception");
        py::register_exception_translator([](std::exception_ptr ex) {
            try {
                if (ex) std::rethrow_exception(ex);
            }
            catch (const columbus::Exception &ex) {
                exc(ex.getMessage().c_str());
            }
            catch (...) {
                throw;
            }
        });

    }
}}}}