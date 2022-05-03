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

#include "../inc/Helpers.h"

namespace columbus { namespace lim { namespace patterns {

    columbus::rul::RulHandler& getPatternRulHander() {
        static columbus::rul::RulHandler temp("Default", "eng");
        return temp;
    }

    const RulContainer& getMAIN_GROUP() {
        static RulContainer temp("PatternGroup", "Pattern Name", true );
        return temp;
    };
    const RulContainer& getSUB_GROUP1() {
        static RulContainer temp("AntiPattern", "Anti Pattern", true, "summarized", "", true, "An AntiPattern is a literary form that describes a commonly occurring solution to a problem that generates decidedly negative consequences. The AntiPattern may be the result of a manager or developer not knowing any better, not having sufficient knowledge or experience in solving a particular type of problem, or having applied a perfectly good pattern in the wrong context.");
        return temp;
    }
    const RulContainer& getSUB_GROUP2() {
        static RulContainer temp("DesignPattern", "Design Pattern", true, "summarized", "", true, "In software engineering, a design pattern is a general repeatable solution to a commonly occurring problem in software design. A design pattern isn't a finished design that can be transformed directly into code. It is a description or template for how to solve a problem that can be used in many different situations.");
        return temp;
    }

    std::set<NodeId> getSingleTypes(const lim::asg::type::Type &_type, int depth) {
        if (depth <= 0) return std::set<NodeId>();
        using namespace lim::asg;
        using std::set;

        set<NodeId> _types;
        _types.insert(_type.getId());

        auto typeFormerIt = _type.getTypeFormerListIteratorBegin();

        for (uint32_t i = 0; i < _type.getTypeFormerSize(); i++, ++typeFormerIt) {
            type::TypeFormer &typeFormer = (type::TypeFormer&)(*typeFormerIt);
            if (Common::getIsTypeFormerType(typeFormer)) {
                type::TypeFormerType &tPT = (type::TypeFormerType&)typeFormer;
                auto _base = tPT.getRefersTo();
                int _depth = depth - 1;
                // this happens when there is no 'refersTo' edge
                // error?
                if (_base == nullptr) continue;

                else if (Common::getIsSimpleType(*_base)) {
                    _types.insert(_base->getId());
                }
                else if (_base->getNodeKind() == ndkClass) {
                    // subclasses
                    Class *_class = ((Class*)_base);
                    auto &_childTypes = getNameFromGeneric<asg::ListIterator>(_class->getIsSubclassListIteratorBegin(), _class->getIsSubclassListIteratorEnd(), depth);
                    _types.insert(_base->getId());
                    _types.insert(_childTypes.begin(), _childTypes.end());
                }
                else if (Common::getIsClassGeneric(*_base)) {
                    ClassGeneric* _classGen = (ClassGeneric*)_base;
                    auto &_childTypes = getNameFromGeneric<asg::ListIterator>(_classGen->getIsSubclassListIteratorBegin(), _classGen->getIsSubclassListIteratorEnd(), depth);
                    _types.insert(_base->getId());
                    _types.insert(_childTypes.begin(), _childTypes.end());
                }
                else if (Common::getIsClassGenericInstance(*_base)) {
                    ClassGenericInstance *_classGenInst = (ClassGenericInstance*)_base;
                    auto &_childTypes = getNameFromGeneric<asg::ListIteratorAssocTypeArgumentConstraintKind>(_classGenInst->getArgumentsListIteratorAssocBegin(), _classGenInst->getArgumentsListIteratorAssocEnd(), _depth);
                    _types.insert(_base->getId());
                    _types.insert(_childTypes.begin(), _childTypes.end());
                }
                else if (Common::getIsClassGenericSpec(*_base)) {
                    ClassGenericSpec *_classGenSpec = (ClassGenericSpec*)_base;
                    auto &_childTypes = getNameFromGeneric<asg::ListIteratorAssocTypeArgumentConstraintKind>(_classGenSpec->getArgumentsListIteratorAssocBegin(), _classGenSpec->getArgumentsListIteratorAssocEnd(), _depth);
                    _types.insert(_base->getId());
                    _types.insert(_childTypes.begin(), _childTypes.end());

                    auto *_classGen = _classGenSpec->getSpecialize();
                    auto &_childTypes2 = getNameFromGeneric<asg::ListIterator>(_classGen->getIsSubclassListIteratorBegin(), _classGen->getIsSubclassListIteratorEnd(), depth);
                    _types.insert(_childTypes2.begin(), _childTypes2.end());
                }
                // TODO type::MethodType

            }
            
        }
        return _types;
    }

    namespace {

        /**
         * \brief Cast boost::any into human readable text
         * \param _anyValue [in], The value
         * \return Human readable text of the given value
        */
        /*std::string castBoostAny(const boost::any &_anyValue) {
            using namespace std;
            using lim::asg::base::Base;


            const type_info &info = _anyValue.type();

            if (info == typeid(int)) {
                return to_string(boost::any_cast<int>(_anyValue));
            }
            else if (info == typeid(double)) {
                return to_string(boost::any_cast<double>(_anyValue));
            }
            else if (info == typeid(bool)) {
                return (boost::any_cast<bool>(_anyValue) ? "true" : "false");
            }
            else if (info == typeid(float)) {
                return to_string(boost::any_cast<float>(_anyValue));
            }
            else if (info == typeid(long)) {
                return to_string(boost::any_cast<long>(_anyValue));
            }
            else if (info == typeid(long long)) {
                return to_string(boost::any_cast<long long>(_anyValue));
            }
            else if (info == typeid(unsigned long)) {
                return to_string(boost::any_cast<unsigned long>(_anyValue));
            }
            else if (info == typeid(unsigned long long)) {
                return to_string(boost::any_cast<unsigned long long>(_anyValue));
            }
            else if (info == typeid(const char*)) {
                return boost::any_cast<const char*>(_anyValue);
            }
            else if (info == typeid(char*)) {
                return boost::any_cast<char*>(_anyValue);
            }
            else if (info == typeid(string)) {
                return boost::any_cast<string>(_anyValue);
            }
            else if (info == typeid(uint32_t)) {
                return to_string(boost::any_cast<uint32_t>(_anyValue));
            }
            else if (info == typeid(uint16_t)) {
                return to_string(boost::any_cast<uint16_t>(_anyValue));
            }
            else if (info == typeid(Base*)) {
                return "Base : id" + to_string(boost::any_cast<Base*>(_anyValue)->getId());
            }
            return "0.0";
        }*/

    
        /**
         * \brief Get the string value of an sttribute by the given name
         * \param node [in], The node where the attribute is located
         * \param findValueOf [in], The name of the attribute we are searching for
         * \return string value of the found attribute
        */
        std::string getValueFromGraph(const graph::Node &node, const std::string &findValueOf) {
            try {
                const auto &attr = node.findAttributeByName(findValueOf).next();
                const std::string &val = attr.getStringValue();
                if (attr.getType() == graph::Attribute::atInvalid || val == "__INVALID__") {
                    throw std::exception();
                }
                return val;
            }
            catch (...) {
                std::string msg = "'" + findValueOf + "' does not exists on node '" + node.getUID() + "'\n";
                common::WriteMsg::write(common::WriteMsg::mlWarning, msg.c_str());
                return std::to_string(INT16_MIN);
            }
        }

        /**
         * \brief Get the string value of a lim::base class member
         * \param limNode [in], The lim node where value is located
         * \param findValueOf [in], The name of the member we are searching for
         * \return string value of the found value
        */
        std::string getValueFromLim(const asg::base::Base& limNode, const std::string &findValueOf) {
            using namespace std;
            using namespace lim;
            using namespace lim::asg;
            using namespace lim::asg::base;
            using namespace lim::asg::logical;

            const auto ndk = limNode.getNodeKind();

            auto checkCondition = [&findValueOf, &ndk](limTypes _limType) -> bool {
                return filterTypesAndValues[_limType].second.first.find(ndk) != filterTypesAndValues[_limType].second.first.end() && findValueOf == limTypesString[_limType];
            };

            if (Common::getIsMethod(limNode) && (findValueOf == limTypesString[returnType] || findValueOf == limTypesString[type])) {
                auto &_Type = getTraversalEdges(limNode, edkMethod_Returns, false);
                if (!_Type.empty()) {
                    return to_string(_Type[0]->getId());
                }
            }
            else if (checkCondition(isAbstract)) {
                bool isTrue;
                // there is no common base class for getIsAbstract
                if (lim::asg::Common::getIsMethod(limNode)) {
                    isTrue = ((Method&)limNode).getIsAbstract();
                }
                else {
                    isTrue = ((Class&)limNode).getIsAbstract();
                }
                return isTrue ? "true" : "false";
            }
            else if (checkCondition(isAnonymous)) {
                Scope& _method = (Scope&)limNode;
                bool isTrue = _method.getIsAnonymous();
                return isTrue ? "true" : "false";
            }
            else if (checkCondition(isStatic)) {
                Member& _method = (Member&)limNode;
                bool isTrue = _method.getIsStatic();
                return isTrue ? "true" : "false";
            }
            else if (checkCondition(isVirtual)) {
                Method& _method = (Method&)limNode;
                bool isTrue = _method.getIsVirtual();
                return isTrue ? "true" : "false";
            }
            else if (checkCondition(parameterSize)) {
                Method& _method = (Method&)limNode;
                unsigned int numberOfParameter = _method.getParameterSize();
                return to_string(numberOfParameter);
            }
            else if (checkCondition(accessibility)) {
                Member& _member = (Member&)limNode;
                AccessibilityKind _methodAccessibility = _member.getAccessibility();
                return Common::toString(_methodAccessibility);
            }
            else if (checkCondition(classKind)) {
                Class& _class = (Class&)limNode;
                ClassKind _classKind = _class.getClassKind();
                return Common::toString(_classKind);
            }
            else if (checkCondition(methodKind)) {
                Method& _method = (Method&)limNode;
                MethodKind _methodKind = _method.getMethodKind();
                return Common::toString(_methodKind);
            }
            else if (checkCondition(id)) {
                return to_string(limNode.getId());
            }
            else if (checkCondition(name)) {
                Named &_named = (Named&)limNode;
                return _named.getName().empty() ? "-1" : _named.getName();
            }
            else if (checkCondition(kind)) {
                NodeKind _ndk = limNode.getNodeKind();
                return Common::toString(_ndk);
            }
            else if (checkCondition(paramKind)) {
                ParameterKind _pmk = ((Parameter&)limNode).getParamKind();
                return Common::toString(_pmk);
            }
            else if (Common::getIsParameter(limNode) && findValueOf == limTypesString[type]) {
                auto &_Type = getTraversalEdges(limNode, edkParameter_HasType, false);
                if (!_Type.empty()) {
                    return to_string(_Type[0]->getId());
                }
            }
            else if (Common::getIsClass(limNode) && findValueOf == limTypesString[type]) {
                auto &_TypeFormerType = getTraversalEdges(limNode, edkTypeFormerType_RefersTo, true);
                if (!_TypeFormerType.empty()) {
                    auto &_multiType = getTraversalEdges(*_TypeFormerType[0], edkType_HasTypeFormer, true);
                    for (auto &_type : _multiType) {
                        if (getTraversalEdges(*_type, edkType_HasTypeFormer, false).size() >= 2)
                            continue;
                        return to_string(_type->getId());
                    }
                    
                }
            }
            else if (Common::getIsAttribute(limNode) && findValueOf == limTypesString[type]) {
                auto &_Type = getTraversalEdges(limNode, edkAttribute_HasType, false);
                if (!_Type.empty()) {
                    return to_string(_Type[0]->getId());
                }
            }
            else if (Common::getIsType(limNode) && findValueOf == limTypesString[type]) {
                // if its already a type, return itself
                return to_string(limNode.getId());
            }
            else if (checkCondition(simpleTypeKind)) {
                type::SimpleType &_sT = (type::SimpleType&)limNode;
                return Common::toString(_sT.getSimpleTypeKind());
            }
            else if (checkCondition(pointerKind)) {
                type::TypeFormerPointer &_tFP = (type::TypeFormerPointer&)limNode;
                return Common::toString(_tFP.getPointerKind());
            }
            else if (checkCondition(classType)) {
                type::Type &_sT = (type::Type&)limNode;

                const auto &end = _sT.getTypeFormerListIteratorEnd();

                for (auto it = _sT.getTypeFormerListIteratorBegin(); it != end; ++it) {
                    if (Common::getIsTypeFormerType(*it)) {
                        base::Base *_base = ((type::TypeFormerType&)*it).getRefersTo();
                        if (_base && asg::Common::getIsClass(*_base)) {
                            if (asg::Common::getIsClassGenericInstance(*_base)) {
                                auto _classGen = getTraversalEdges(*_base, asg::edkMember_Instance, true);
                                if (_classGen.empty()) {
                                    // THIS SHOULD NEVER BE EMPTY
                                    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("LIM error, reverse edge 'edkMember_Instance' on node '" + std::to_string(_base->getId()) + "' should exist but it doesn't!"));
                                }
                                _base = _classGen[0];
                            }
                            return to_string(_base->getId());
                        }
                    }
                }
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("'class/getClass' didn't found a Class!"));
            }
            else if (checkCondition(parent)) {
                if (Common::getIsClass(limNode) || Common::getIsMethod(limNode) || Common::getIsAttribute(limNode)) {
                    auto &_parent = getTraversalEdges(limNode, edkScope_HasMember, true);
                    // Error if _parent > 1 ??
                    if (!_parent.empty()) return to_string(_parent[0]->getId());
                    // return self is there is no parent
                    return to_string(limNode.getId());
                }
                else {
                    auto &_parent = getTraversalEdges(limNode, edkMethod_HasParameter, true);
                    // Error if _parent > 1 ??
                    if (!_parent.empty()) return to_string(_parent[0]->getId());
                    // return self is there is no parent
                    return to_string(limNode.getId());
                }
            }
            else {
                // if its a string value, e.g. true,false,string,document...
                return findValueOf;
            }

            // if nothing happens, return the original ID of the node
            return to_string(limNode.getId());
        }

    }

    Result::Trace::Trace(const std::string &_role, const std::string &_patternName, uint32_t _nodeId, uint32_t _callStackDepth/*, stringAnyLValue &_variables*/)
        : role(_role), patternName(_patternName), nodeId(_nodeId), callStackDepth(_callStackDepth)/*, variables(_variables)*/ {}
    Result::Trace::~Trace() { /*variables.clear();*/ }
    Result::Result(std::string _text) : outputText(_text) {};

    std::string positionToString(int line, int col, int endLine, int endCol) {
        return "[Ln:" + std::to_string(line) + ", Col:" + std::to_string(col) + " - Ln:" + std::to_string(endLine) + ", Col:" + std::to_string(endCol) + "]";
    }

    void Result::addWarningToTxt(graph::Graph & _inGraph, const asg::base::Base & _base, const std::string & _roleName, uint32_t & depth) {
        std::string _text = "";
        for (int _depth = depth; _depth > 0; _depth--) _text += "\t";
        _text += "Role '" + _roleName + "' fits on '" + ((asg::base::Named&)_base).getName() + "' (nodeid '" + std::to_string(_base.getId()) + "')";
        if (asg::Common::getIsMember(_base)) {
            auto sourcePosIt = ((asg::Member&)(_base)).getIsContainedInListIteratorAssocBegin();
            std::string foundInPath;
            int line, endLine, column, endColumn;
            graphsupport::getPositionAttribute(_inGraph, "L" + std::to_string(_base.getId()), foundInPath, line, column, endLine, endColumn);
            _text += ", " + foundInPath + " " + positionToString(line, column, endLine, endColumn);
        }
        outputText += _text + "\n";
    }

    void Result::addIntroToTxt(graph::Graph &inGraph, const asg::base::Base &limNode, const std::string &patternName, uint32_t &depth){
        if (!patternName.empty()) {
            std::string foundInPath;
            int line, endLine, column, endColumn;
            std::string TUID = "L" + std::to_string(limNode.getId());
            graphsupport::getPositionAttribute(inGraph, TUID, foundInPath, line, column, endLine, endColumn);
            std::string tabs = "";
            for (int _depth = depth; _depth > 0; _depth--) tabs += "\t";
            if (depth == 0) outputText += "\n";
            outputText += tabs + "Pattern '" + patternName + "' has been found on '" + ((asg::base::Named&)limNode).getName() + "'\n";
            outputText += tabs + "Source : " + foundInPath + " " + positionToString(line, column, endLine, endColumn) + "\n";
        }
    }

    /*
    void Result::addCalculatedValuesTxt(const stringAnyLValue & variables, uint32_t depth) {
        if (!variables.empty()) {
            std::string _text = "", tabs = "";
            for (int _depth = depth; _depth > 0; _depth--) tabs += "\t";
            for (auto &val : variables) {
                if (!val.second.second.empty()) {
                    if (val.second.first) {
                        std::string value = castBoostAny(val.second.second);
                        _text += tabs + "\t- " + val.first + " : " + value + "\n";
                    }
                }

            }

            outputText += _text;
        }
    }*/

    void Result::addNodeToTrace(const int _id, const std::string &_role, const std::string &_patternName/*, stringAnyLValue &_variables*/, const short &_depth) {
        Trace _trace(_role, _patternName, _id, _depth/*, _variables*/);
        traceResult.push_back(_trace);
    }

    void Result::finalizeTXTout(graph::Graph &_inGraph, asg::Factory &_factory) {
        for (size_t index = 0; index < traceResult.size(); index++) {
            addIntroToTxt(_inGraph, _factory.getRef(traceResult[index].nodeId), traceResult[index].patternName, traceResult[index].callStackDepth);
            addWarningToTxt(_inGraph, _factory.getRef(traceResult[index].nodeId), traceResult[index].role, traceResult[index].callStackDepth);
            //addCalculatedValuesTxt(traceResult[index].variables, traceResult[index].callStackDepth);
        }
    }

    void Result::addMetricToNode(graph::Graph &_inGraph, const asg::base::Base &_base, stringAnyLValue &_variables) {
        // add Variables
        if (asg::Common::getIsMember(_base)) {
            graph::Node _node = _inGraph.findNode("L" + std::to_string(_base.getId()));
            for (auto &_variable : _variables) {
                if (_variable.second.first && !_variable.second.second.empty()) {
                    using namespace columbus::graphsupport::graphconstants;
                    std::string name = _variable.first;

                    // Creates attribute on node
                    if (_variable.second.second.type() == typeid(int)) {
                        graph::AttributeInt attrInt = _inGraph.createAttributeInt(name, CONTEXT_METRIC, boost::any_cast<int>(_variable.second.second));
                        graphsupport::addAttributeOnce(_node, attrInt, true);
                    }
                    else if (_variable.second.second.type() == typeid(NodeId)) {
                        graph::AttributeInt attrInt = _inGraph.createAttributeInt(name, CONTEXT_METRIC, boost::any_cast<NodeId>(_variable.second.second));
                        graphsupport::addAttributeOnce(_node, attrInt, true);
                    }
                    else if (_variable.second.second.type() == typeid(double)) {
                        graph::AttributeFloat attrFloat = _inGraph.createAttributeFloat(name, CONTEXT_METRIC, (float)boost::any_cast<double>(_variable.second.second));
                        graphsupport::addAttributeOnce(_node, attrFloat, true);
                    }
                    else if (_variable.second.second.type() == typeid(float)) {
                        graph::AttributeFloat attrFloat = _inGraph.createAttributeFloat(name, CONTEXT_METRIC, boost::any_cast<float>(_variable.second.second));
                        graphsupport::addAttributeOnce(_node, attrFloat, true);
                    }
                    else if (_variable.second.second.type() == typeid(std::string)) {
                        graph::AttributeString attrString = _inGraph.createAttributeString(name, CONTEXT_METRIC, boost::any_cast<std::string>(_variable.second.second));
                        graphsupport::addAttributeOnce(_node, attrString, true);
                    }
                    else if (_variable.second.second.type() == typeid(bool)) {
                        graph::AttributeString attrString = _inGraph.createAttributeString(name, CONTEXT_METRIC, boost::any_cast<bool>(_variable.second.second) ? "true" : "false");
                        graphsupport::addAttributeOnce(_node, attrString, true);
                    }
                }
            }
        }
    }

    void Result::finalizeGRAPHout(graph::Graph &_inGraph, asg::Factory &_factory, const std::string &_patternName, const std::string &_warningName, const short &_currentPatternDoc, const std::string &_roleName, const std::string &_category) {
        matchCounter[_patternName]++;

        graph::Node _node = _inGraph.findNode("L" + std::to_string(traceResult.front().nodeId));
        const std::string warningText = "Found '" + _patternName + "' pattern!";
        using namespace columbus::graphsupport::graphconstants;

        //addMetricToNode(traceResult.front().front());

        asg::base::Base &_base = _factory.getRef(traceResult.front().nodeId);
        std::string foundInPath;
        int line, endLine, column, endColumn;
        std::string TUID = "L" + std::to_string(_base.getId());
        graphsupport::getPositionAttribute(_inGraph, TUID, foundInPath, line, column, endLine, endColumn);
        auto firstNode = traceResult.front().nodeId;

        // createExtraInfo for tracing the results
        graph::AttributeComposite extraInfo = _inGraph.createAttributeComposite(ATTR_EXTRAINFO, CONTEXT_TRACE);
        bool traceIsOn = false;
        for (size_t index = 1; index < traceResult.size(); index++) {
            if (firstNode == traceResult[index].nodeId) continue;
            traceIsOn = true;
            std::string childTUID = "L" + std::to_string(traceResult[index].nodeId);
            std::string _foundInPath; int _line, _column, _endLine, _endColumn;
            graphsupport::getPositionAttribute(_inGraph, childTUID, _foundInPath, _line, _column, _endLine, _endColumn);

            const graph::Node &childNode = _inGraph.findNode(childTUID);

            graph::AttributeComposite attr = _inGraph.createAttributeComposite(_warningName + "_reference", "");
            attr.addAttribute(_inGraph.createAttributeString("NodeID", "", TUID));
            attr.addAttribute(_inGraph.createAttributeInt("PatternID", "", patternID));
            attr.addAttribute(_inGraph.createAttributeString("Path", "", _foundInPath));
            attr.addAttribute(_inGraph.createAttributeInt("Line", "", _line));
            attr.addAttribute(_inGraph.createAttributeInt("Column", "", _column));
            attr.addAttribute(_inGraph.createAttributeInt("EndLine", "", _endLine));
            attr.addAttribute(_inGraph.createAttributeInt("EndColumn", "", _endColumn));
            graphsupport::addAttributeOnce(childNode, attr, true);

            graph::AttributeComposite sorceLink = _inGraph.createAttributeComposite(ATTR_SOURCELINK, "");

            sorceLink.addAttribute(_inGraph.createAttributeString("RoleName", "", traceResult[index].role));
            sorceLink.addAttribute(_inGraph.createAttributeString("NodeID", "", childTUID));
            sorceLink.addAttribute(_inGraph.createAttributeString("Path", "", _foundInPath));
            sorceLink.addAttribute(_inGraph.createAttributeInt("Line", "", _line));
            sorceLink.addAttribute(_inGraph.createAttributeInt("Column", "", _column));
            sorceLink.addAttribute(_inGraph.createAttributeInt("EndLine", "", _endLine));
            sorceLink.addAttribute(_inGraph.createAttributeInt("EndColumn", "", _endColumn));

            if (!traceResult[index].patternName.empty())
                sorceLink.addAttribute(_inGraph.createAttributeString("PatternName", "", traceResult[index].patternName));
            extraInfo.addAttribute(sorceLink);
        }

        // create warning depending on tracing (if there is tracing, we create a warning with extrainfo)
        if (traceIsOn) {
            graphsupport::addWarningOnce(_inGraph, _node, _warningName, foundInPath, line, column, endLine, endColumn, warningText, extraInfo);
        }
        else {
            graphsupport::addWarningOnce(_inGraph, _node, _warningName, foundInPath, line, column, endLine, endColumn, warningText);
        }
        // Creates and sets a specific warning only once (used if the Graph already contains pattern warnings)
        auto createAttrOnce = [&](graph::AttributeComposite &attrComp, std::string name, const std::string &val, const int &patternID = -1) {
            auto it1 = patternID == -1 ? attrComp.findAttribute(graph::Attribute::atString, name, "") : attrComp.findAttribute(graph::Attribute::atInt, name, "");
            if (it1.hasNext()) {
                if (patternID == -1) {
                    graph::AttributeString &attr = (graph::AttributeString&)it1.next();
                    attr.setValue(val);
                }
                else {
                    graph::AttributeInt &attr = (graph::AttributeInt&)it1.next();
                    attr.setValue(patternID);
                }
            }
            else {
                if (patternID == -1) {
                    attrComp.addAttribute(_inGraph.createAttributeString(name, "", val));
                }
                else {
                    attrComp.addAttribute(_inGraph.createAttributeInt(name, "", patternID));
                }
            }
        };

        graph::AttributeComposite &attrComp = (graph::AttributeComposite&)(_node.findAttribute(graph::Attribute::atComposite, _warningName, CONTEXT_WARNING).next());
        createAttrOnce(attrComp, "RoleName", _roleName);
        createAttrOnce(attrComp, "PatternName", _patternName);
        createAttrOnce(attrComp, "PatternID", "", patternID);

        patternID++;
        //}
    }

    void Result::reset() {
        traceResult.clear();
    }

    std::string Result::getOutput() {
        std::string individualMatches = "";
        for (auto &pair : matchCounter) {
            individualMatches += pair.first + " matches: " + std::to_string(pair.second) + "\n";
        }
        outputText.insert(0,
            "Total matches: " + std::to_string(patternID - 1) + "\n" +
            individualMatches);
        return outputText;
    }

    void Result::removeFromTrace(uint32_t nodeId) {
        for (size_t i = 0; i < traceResult.size(); i++) {
            if (traceResult[i].nodeId == nodeId) {
                traceResult.erase(traceResult.begin() + i);
            }
        }
    }

    uint32_t Result::totalMatches() {
        return this->patternID;
    }

    uint32_t Result::matchCount(std::string &patternName) {
        return this->matchCounter[patternName];
    }

    std::set<std::string> Result::getFoundPatternNames() const{
        std::set<std::string> names;
        for (const auto &entry : this->matchCounter) {
            names.insert(CREATE_PATTERN_WARNING_NAME(entry.first));
        }
        return names;
    }

    const std::map<asg::NodeKind, asg::NodeKind>& getHierarchies() {
        using namespace lim::asg;

        const static std::map<NodeKind, NodeKind> hierarchies{
           {
               ndkBase , ndkLAST
           },
           {
               ndkComment, ndkBase
           },
           {
               ndkComponent, ndkNamed
           },
           {
               ndkNamed, ndkBase
           },
           {
               ndkControlFlowBlock, ndkBase
           },
           {
               ndkAttribute, ndkMember
           },
           {
               ndkAttributeAccess, ndkBase
           },
           {
               ndkClass, ndkScope
           },
           {
               ndkClassGeneric, ndkClass
           },
           {
               ndkClassGenericInstance, ndkClass
           },
           {
               ndkClassGenericSpec, ndkClassGenericInstance
           },
           {
               ndkFriendship, ndkBase
           },
           {
               ndkGenericParameter, ndkNamed
           },
           {
               ndkMember, ndkNamed
           },
           {
               ndkMethod, ndkScope
           },
           {
               ndkMethodCall, ndkBase
           },
           {
               ndkMethodGeneric, ndkMethod
           },
           {
               ndkMethodGenericInstance, ndkMethod
           },
           {
               ndkMethodGenericSpec, ndkMethodGeneric
           },
           {
               ndkPackage, ndkScope
           },
           {
               ndkParameter, ndkNamed
           },
           {
               ndkScope, ndkMember
           },
           {
               ndkFSEntry, ndkNamed
           },
           {
               ndkFile, ndkFSEntry
           },
           {
               ndkFileSystem, ndkNamed
           },
           {
               ndkFolder, ndkFSEntry
           },
           {
               ndkSimpleType, ndkBase
           },
           {
               ndkType, ndkBase
           },
           {
               ndkTypeFormer, ndkBase
           },
           {
               ndkTypeFormerArray, ndkTypeFormer
           },
           {
               ndkTypeFormerMethod, ndkTypeFormer
           },
           {
               ndkTypeFormerNonType, ndkTypeFormer
           },
           {
               ndkTypeFormerPointer, ndkTypeFormer
           },
           {
               ndkTypeFormerType, ndkTypeFormer
           }
        };
        return hierarchies;
    }

    functionDef& getFunctionsDef() {
        using namespace lim::asg;
        using namespace lim::asg::base;
        using namespace lim::asg::logical;
        using namespace lim::asg::type;

        static functionDef functions{
        {ndkComponent, {
            {edkComponent_CompilationUnit, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Component &_component = (Component&)(base);
                return castToBaseVector(fact, _component.getCompilationUnitListIteratorBegin(), _component.getCompilationUnitListIteratorEnd());
            }},
            {edkComponent_Contains, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Component &_component = (Component&)(base);
                return castToBaseVector(fact, _component.getContainsListIteratorBegin(), _component.getContainsListIteratorEnd());
            }},
            {edkComponent_HasFiles, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Component &_component = (Component&)(base);
                return castToBaseVector(fact, _component.getFilesListIteratorBegin(), _component.getFilesListIteratorEnd());
            }}
        }},
        {ndkControlFlowBlock, {
            {edkControlFlowBlock_Calls, [](ARGUMENTS(base,fact)) -> vecOfBase {
                ControlFlowBlock &_contFlow = (ControlFlowBlock&)(base);
                return castToBaseVector(fact, _contFlow.getCallsListIteratorBegin(), _contFlow.getCallsListIteratorEnd());
            }},
            {edkControlFlowBlock_Pred, [](ARGUMENTS(base,fact)) -> vecOfBase {
                ControlFlowBlock &_contFlow = (ControlFlowBlock&)(base);
                return castToBaseVector(fact, _contFlow.getPredListIteratorBegin(), _contFlow.getPredListIteratorEnd());
            }}
        }},
        {ndkNamed,{
            {edkNamed_DependsOn,[](ARGUMENTS(base,fact))->vecOfBase {
                Named &_named = (Named&)(base);
                return castToBaseVector(fact, _named.getDependsOnListIteratorAssocBegin(), _named.getDependsOnListIteratorAssocEnd());
            }}
        }},
        {ndkAttribute, {
            {edkAttribute_Calls, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Attribute &_attr = (Attribute&)(base);
                return castToBaseVector(fact, _attr.getCallsListIteratorBegin(), _attr.getCallsListIteratorEnd());
            }},
            {edkAttribute_HasType, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Attribute &_attr = (Attribute&)(base);
                return castToBaseVector(fact, _attr.getTypeListIteratorBegin(), _attr.getTypeListIteratorEnd());
            }}
        }},
        {ndkAttributeAccess, {
            {edkAttributeAccess_Attribute, [](ARGUMENTS(base,fact)) -> vecOfBase {
                AttributeAccess &_attr = (AttributeAccess&)(base);
                if (_attr.getAttribute() == nullptr)
                    return vecOfBase{};
                return vecOfBase{ _attr.getAttribute() };
            }}
        }},
        {ndkClass, {
            {edkClass_IsSubclass, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Class &_class = (Class&)(base);
                return castToBaseVector(fact, _class.getIsSubclassListIteratorBegin(), _class.getIsSubclassListIteratorEnd());
            }},
            {edkClass_Extends, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Class &_class = (Class&)(base);
                return castToBaseVector(fact, _class.getExtendsListIteratorBegin(), _class.getExtendsListIteratorEnd());
            }},
            {edkClass_GrantsFriendship, [](ARGUMENTS(base,fact)) -> vecOfBase {
                Class &_class = (Class&)(base);
                return castToBaseVector(fact, _class.getGrantsFriendshipListIteratorBegin(), _class.getGrantsFriendshipListIteratorEnd());
            }}
            }},
            {ndkClassGeneric,{
                {edkClassGeneric_HasGenericParameter,[](ARGUMENTS(base,fact))->vecOfBase {
                    ClassGeneric &_classGen = (ClassGeneric&)(base);
                    return castToBaseVector(fact, _classGen.getGenericParameterListIteratorBegin(), _classGen.getGenericParameterListIteratorEnd());
                }}
            }},
            {ndkClassGenericInstance,{
                {edkClassGenericInstance_HasArguments,[](ARGUMENTS(base,fact))->vecOfBase {
                    ClassGenericInstance &_classGenInst = (ClassGenericInstance&)(base);
                    return castToBaseVector(fact, _classGenInst.getArgumentsListIteratorAssocBegin(), _classGenInst.getArgumentsListIteratorAssocEnd());
                }}
            }},
            {ndkClassGenericSpec,{
                {edkClassGenericSpec_HasArguments,[](ARGUMENTS(base,fact))->vecOfBase {
                    ClassGenericSpec &_classGenSpec = (ClassGenericSpec&)(base);
                    return castToBaseVector(fact, _classGenSpec.getArgumentsListIteratorAssocBegin(), _classGenSpec.getArgumentsListIteratorAssocEnd());
                }},
                {edkClassGenericSpec_Specialize,[](ARGUMENTS(base,fact))->vecOfBase {
                    ClassGenericSpec &_classGenSpec = (ClassGenericSpec&)(base);
                    if (_classGenSpec.getSpecialize() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{ _classGenSpec.getSpecialize()};
                }}
            }},
            {ndkFriendship,{
                {edkFriendship_Friend,[](ARGUMENTS(base,fact))->vecOfBase {
                    Friendship &_friendship = (Friendship&)(base);
                    if (_friendship.getFriend() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{ _friendship.getFriend() };
                }}
            }},
            {ndkGenericParameter,{
                {edkGenericParameter_HasParameterConstraint,[](ARGUMENTS(base,fact))->vecOfBase {
                    GenericParameter &_genPar = (GenericParameter&)(base);
                    return castToBaseVector(fact, _genPar.getParameterConstraintListIteratorBegin(), _genPar.getParameterConstraintListIteratorEnd());
                }}
            }},
            {ndkScope,{
                {edkScope_HasMember,[](ARGUMENTS(base,fact))->vecOfBase {
                    Scope &_scope = (Scope&)(base);
                    return castToBaseVector(fact, _scope.getMemberListIteratorBegin(), _scope.getMemberListIteratorEnd());
                }}
            }},
            {ndkMember,{
                {edkMember_Aggregated,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    if (_member.getAggregated() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{ _member.getAggregated() };
                }},
                {edkMember_BelongsTo,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    return castToBaseVector(fact, _member.getBelongsToListIteratorBegin(), _member.getBelongsToListIteratorEnd());
                }},
                {edkMember_CompilationUnit,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    return castToBaseVector(fact, _member.getCompilationUnitListIteratorBegin(), _member.getCompilationUnitListIteratorEnd());
                }},
                {edkMember_Declares,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    if (_member.getDeclares() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{ _member.getDeclares() };
                }},
                {edkMember_HasComment,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    return castToBaseVector(fact, _member.getCommentListIteratorBegin(), _member.getCommentListIteratorEnd());
                }},
                {edkMember_Instance,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    return castToBaseVector(fact, _member.getInstanceListIteratorBegin(), _member.getInstanceListIteratorEnd());
                }},
                {edkMember_IsContainedIn,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    return castToBaseVector(fact, _member.getIsContainedInListIteratorAssocBegin(), _member.getIsContainedInListIteratorAssocEnd());
                }},
                {edkMember_Declares,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    if (_member.getLanguageVariant() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{ _member.getLanguageVariant() };
                }},
                {edkMember_Uses,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    return castToBaseVector(fact, _member.getUsesListIteratorBegin(), _member.getUsesListIteratorEnd());
                }},
                {edkMember_Variant,[](ARGUMENTS(base,fact))->vecOfBase {
                    Member &_member = (Member&)(base);
                    return castToBaseVector(fact, _member.getVariantListIteratorBegin(), _member.getVariantListIteratorEnd());
                }}
            }},
            {ndkType,{
                {edkType_HasTypeFormer,[](ARGUMENTS(base,fact))->vecOfBase {
                    Type &_type = (Type&)(base);
                    return castToBaseVector(fact, _type.getTypeFormerListIteratorBegin(), _type.getTypeFormerListIteratorEnd());
                }}
            }},
            {ndkTypeFormerType,{
                {edkTypeFormerType_RefersTo,[](ARGUMENTS(base,fact))->vecOfBase {
                    TypeFormerType &_type = (TypeFormerType&)(base);
                    if (_type.getRefersTo() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{_type.getRefersTo()};
                }}
            }},
            {ndkTypeFormerMethod,{
                {edkTypeFormerMethod_HasReturnType,[](ARGUMENTS(base,fact))->vecOfBase {
                    TypeFormerMethod &_typeFormerMethod = (TypeFormerMethod&)(base);
                    if (_typeFormerMethod.getReturnType() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{ _typeFormerMethod.getReturnType()};
                }},
                {edkTypeFormerMethod_HasParameterType,[](ARGUMENTS(base,fact))->vecOfBase {
                    TypeFormerMethod &_typeFormerMethod = (TypeFormerMethod&)(base);
                    return castToBaseVector(fact, _typeFormerMethod.getParameterTypeListIteratorAssocBegin(), _typeFormerMethod.getParameterTypeListIteratorAssocEnd());
                }}
            }},
            {ndkMethod,{
                {edkMethod_AccessesAttribute,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getAccessesAttributeListIteratorBegin(), _method.getAccessesAttributeListIteratorEnd());
                }},
                {edkMethod_Calls,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getCallsListIteratorBegin(), _method.getCallsListIteratorEnd());
                }},
                {edkMethod_CanThrow,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getCanThrowListIteratorBegin(), _method.getCanThrowListIteratorEnd());
                }},
                {edkMethod_HasControlFlowBlock,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getControlFlowBlockListIteratorBegin(), _method.getControlFlowBlockListIteratorEnd());
                }},
                {edkMethod_HasParameter,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getParameterListIteratorBegin(), _method.getParameterListIteratorEnd());
                }},
                {edkMethod_Instantiates,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getInstantiatesListIteratorBegin(), _method.getInstantiatesListIteratorEnd());
                }},
                {edkMethod_Returns,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getReturnsListIteratorBegin(), _method.getReturnsListIteratorEnd());
                }},
                {edkMethod_Throws,[](ARGUMENTS(base,fact))->vecOfBase {
                    Method &_method = (Method&)(base);
                    return castToBaseVector(fact, _method.getThrowsListIteratorBegin(), _method.getThrowsListIteratorEnd());
                }}
            }},
            {ndkMethodCall,{
                {edkMethodCall_Method,[](ARGUMENTS(base,fact))->vecOfBase {
                    MethodCall &_methodCall = (MethodCall&)(base);
                    if (_methodCall.getMethod() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{_methodCall.getMethod()};
                }}
            }},
            {ndkMethodGeneric,{
                {edkMethodGeneric_HasGenericParameter,[](ARGUMENTS(base,fact))->vecOfBase {
                    MethodGeneric &_methodGeneric = (MethodGeneric&)(base);
                    return castToBaseVector(fact, _methodGeneric.getGenericParameterListIteratorBegin(), _methodGeneric.getGenericParameterListIteratorEnd());
                }}
            }},
            {ndkMethodGenericInstance, {
                {edkMethodGenericInstance_HasArguments,[](ARGUMENTS(base,fact))->vecOfBase {
                    MethodGenericInstance &_methodGenericInstance = (MethodGenericInstance&)(base);
                    return castToBaseVector(fact, _methodGenericInstance.getArgumentsListIteratorAssocBegin(), _methodGenericInstance.getArgumentsListIteratorAssocEnd());
                }}
            }},
            {ndkMethodGenericSpec, {
                {edkMethodGenericSpec_HasArguments,[](ARGUMENTS(base,fact))->vecOfBase {
                    MethodGenericSpec &_methodGenericSpec = (MethodGenericSpec&)(base);
                    return castToBaseVector(fact, _methodGenericSpec.getArgumentsListIteratorAssocBegin(), _methodGenericSpec.getArgumentsListIteratorAssocEnd());
                }},
                {edkMethodGenericSpec_Specialize,[](ARGUMENTS(base,fact))->vecOfBase {
                    MethodGenericSpec &_methodGenericSpec = (MethodGenericSpec&)(base);
                    if (_methodGenericSpec.getSpecialize() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{ _methodGenericSpec.getSpecialize() };
                }}
            }},
            {ndkFile, {
                {edkFile_HasComment,[](ARGUMENTS(base,fact))->vecOfBase {
                    physical::File &_file = (physical::File&)(base);
                    return castToBaseVector(fact, _file.getCommentListIteratorBegin(), _file.getCommentListIteratorEnd());
                }},
                {edkFile_Includes,[](ARGUMENTS(base,fact))->vecOfBase {
                    physical::File &_file = (physical::File&)(base);
                    return castToBaseVector(fact, _file.getIncludesListIteratorBegin(), _file.getIncludesListIteratorEnd());
                }}
            }},
            {ndkFileSystem,{
                {edkFileSystem_HasFSEntry,[](ARGUMENTS(base,fact))->vecOfBase {
                    physical::FileSystem &_fileSys = (physical::FileSystem&)(base);
                    return castToBaseVector(fact, _fileSys.getFSEntryListIteratorBegin(), _fileSys.getFSEntryListIteratorEnd());
                }}
            }},
            {ndkFolder,{
                {edkFolder_Contains,[](ARGUMENTS(base,fact))->vecOfBase {
                    physical::Folder &_folder = (physical::Folder&)(base);
                    return castToBaseVector(fact, _folder.getContainsListIteratorBegin(), _folder.getContainsListIteratorEnd());
                }}
            }},
            {ndkParameter,{
                {edkParameter_HasType,[](ARGUMENTS(base,fact))->vecOfBase {
                    Parameter &_param = (Parameter&)(base);
                    if (_param.getType() == nullptr)
                        return vecOfBase{};
                    return vecOfBase{_param.getType()};
                }}
            }}
        };

        return functions;
    }

    const vecOfBase getIteratorFunctions(const asg::base::Base &base, const asg::EdgeKind &_edk) {
        using namespace lim::asg;
        using namespace lim::asg::base;
        using namespace lim::asg::logical;
        using namespace lim::asg::type;

        static const asg::Factory &fact = base.getFactory();

        vecOfBase ret;
        NodeKind _ndk = base.getNodeKind();
        auto &functions = getFunctionsDef();
        auto &hierarchies = getHierarchies();

        // recursively searches specific edge (jumps to parent class (Method -> Named -> Base, ...) if there is no edge to be found)
        while (_ndk != ndkLAST) {
            if (functions.find(_ndk) != functions.end()) {
                // if edge is found
                if (functions[_ndk].find(_edk) != functions[_ndk].end()) {
                    ret = functions[_ndk][_edk](base, fact);
                    break;
                }
            }
            _ndk = hierarchies.at(_ndk);
        }

        return ret;
    }

    graph::Node limToGraph(graph::Graph &inGraph, const columbus::lim::asg::base::Base& limNode) {
        graph::Node gNode = inGraph.findNode(lim2graph::VisitorGraphConverter::determineNodeName(limNode));
        if (gNode == graph::Graph::invalidNode) throw columbus::Exception("LIM2AntiPatternsVisitor::limToGraph", CMSG_EX_INVALD_GRAPH_NODE(std::to_string(limNode.getId())));
        return gNode;
    }

    void addCalcForToRul(const std::string &_metricID, const std::set<std::string> nodeKind) {
        auto &patternRulHander = getPatternRulHander();
        auto temp = patternRulHander.getCalculatedForSet(_metricID);
        for (auto kind : nodeKind) {
            temp.insert(kind);
        }
        patternRulHander.setCalculatedForSet(_metricID, temp);
    }

    void addRulToRulHander(const RulContainer &_rul, const std::string &_metricID, const std::string &prioriy, const std::set<std::string> nodeKind) {
        using std::string;
        auto &patternRulHander = getPatternRulHander();

        string configName = "Default";
        string metricID = _metricID.empty() ? _rul.id : _metricID;
        if (!patternRulHander.getIsDefined(metricID)) {
            patternRulHander.defineMetric(metricID);
            patternRulHander.createConfiguration(metricID, configName);
            patternRulHander.createLanguage(metricID, "eng");
            patternRulHander.setIsEnabled(metricID, true);
            patternRulHander.setIsVisible(metricID, true);
            patternRulHander.setGroupType(metricID, configName, _rul.group);
            if (!_rul.groupMember.empty())
                patternRulHander.addMetricGroupMembers(metricID, _rul.groupMember);
            patternRulHander.setHasWarningText(metricID, true);
            patternRulHander.setDisplayName(metricID, _rul.name);
            patternRulHander.setWarningText(metricID, _rul.helpText);
            //TODO setDescription
            patternRulHander.setDescription(metricID, _rul.description);
            patternRulHander.setHelpText(metricID, _rul.helpText);
            if (!prioriy.empty()) {
                patternRulHander.setSettingValue(metricID, columbus::graphsupport::graphconstants::ATTR_RUL_PRIORITY, prioriy, true);
            }
            if (!nodeKind.empty()) {
                patternRulHander.setCalculatedForSet(metricID, nodeKind);
            }
        }
        else {
            auto calcsFor = patternRulHander.getCalculatedForSet(metricID);
            
        }
    }

    void addCalForToRulHandler(const std::string &metricID, const std::string &calcFor) {
        auto &patternRulHander = getPatternRulHander();
        if (patternRulHander.getIsDefined(metricID)) {
            auto calcsFor = patternRulHander.getCalculatedForSet(metricID);
            calcsFor.emplace(calcFor);
            patternRulHander.setCalculatedForSet(metricID, calcsFor);
        }
        else {
            throw columbus::Exception(COLUMBUS_LOCATION, "Metric '" + metricID + "' does not exists!");
        }
    }

    std::vector<std::map<std::string, std::pair<uint32_t, bool/*stringAnyLValue*/>>>& getRoleNames() {
        // var[pattern document number][role name][{node id , calculated variables}]
        static std::vector<std::map<std::string, std::pair<uint32_t, bool/*stringAnyLValue*/>>> var;
        return var;
    }

    std::vector<std::pair<lim::asg::NodeKind, std::string>>& currentlyIn() {
        // [{ndkAttribute, "_attr1"}]
        static std::vector<std::pair<lim::asg::NodeKind, std::string>> var;
        return var;
    }

    std::map<std::string, std::set<std::string>>& getMetricIDsAndCalcFor() {
        //getting this in run-time from MET.rul
        static std::map<std::string, std::set<std::string>> var;
        return var;
    }

    Result &result() {
        static Result var;
        return var;
    }

    short &calculatedVariablesInNodesDepth() {
        static short var = 0;
        return var;
    }

    short &currentPatternDocument() {
        static short var = 0;
        return var;
    }

    bool validateEdge(asg::EdgeKind &_edk, asg::NodeKind _ndk) {
        using namespace lim::asg;
        using namespace lim::asg::base;
        using namespace lim::asg::logical;
        using namespace lim::asg::type;

        auto &functions = getFunctionsDef();
        auto &hierarchies = getHierarchies();

        // does the same as the 'while' in 'getIteratorFunctions', but instead of collecting nodes, it gives back a boolean if its a valid edge
        while (_ndk != ndkLAST) {
            if (functions.find(_ndk) != functions.end()) {
                // if edge is found
                if (functions[_ndk].find(_edk) != functions[_ndk].end()) {
                    return true;
                }
            }
            _ndk = hierarchies.at(_ndk);
        }

        return false;
    }

    const vecOfBase getTraversalEdges(const asg::base::Base &base, const asg::EdgeKind &_edk, bool reverse) {
        static auto &_fact = base.getFactory();
        if (reverse) {
            const auto &rev = _fact.getReverseEdges();
            vecOfBase ret;
            try {
                auto it = rev.constIteratorBegin(base.getId(), _edk);
                const auto &itEnd = rev.constIteratorEnd(base.getId(), _edk);
                return castToBaseVector(_fact, it, itEnd);
            }
            catch (...) {
                // no reverse were found
            }
            return ret;
        }
        else {
            return getIteratorFunctions(base, _edk);
        }
    }

    void addWarning(graph::Graph& inGraph, const asg::base::Base &_base, const std::string &patternName, const std::string &roleName, const std::string &category, const std::string &description, const std::string &displayName, const std::string &priority) {
        using std::string;
        using namespace lim;
        using namespace lim::asg;
        using namespace lim::asg::base;
        using namespace lim::asg::logical;
        //using conditions::FormulaCondition;
        using namespace columbus::graphsupport::graphconstants;

        if (!Common::getIsMember(_base)) return;

        result().finalizeTXTout(inGraph, _base.getFactory());
        string warningName = CREATE_PATTERN_WARNING_NAME(patternName);
        const string &metricID = warningName;

        // creating the rule node for the first time
        if (!getPatternRulHander().getIsDefined(metricID)) {

            // this comes from CsvExporter.cpp#L262
            static const std::string asg = inGraph.getHeaderInfo(graphsupport::graphconstants::HEADER_ASG_KEY);

            static const std::map<std::string, std::set<std::string>> calculatedFors{
                {graphsupport::graphconstants::HEADER_ASG_VALUE_JAVA, {
                    graphsupport::graphconstants::NTYPE_LIM_CLASS,
                    graphsupport::graphconstants::NTYPE_LIM_ENUM,
                    graphsupport::graphconstants::NTYPE_LIM_INTERFACE,
                    graphsupport::graphconstants::NTYPE_LIM_ANNOTATION,
                    graphsupport::graphconstants::NTYPE_LIM_METHOD,
                    graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE,
                    graphsupport::graphconstants::NTYPE_LIM_COMPONENT,
                    graphsupport::graphconstants::NTYPE_LIM_PACKAGE
                }},
                {graphsupport::graphconstants::HEADER_ASG_VALUE_CPP, {
                    graphsupport::graphconstants::NTYPE_LIM_CLASS,
                    graphsupport::graphconstants::NTYPE_LIM_ENUM,
                    graphsupport::graphconstants::NTYPE_LIM_INTERFACE,
                    graphsupport::graphconstants::NTYPE_LIM_STRUCTURE,
                    graphsupport::graphconstants::NTYPE_LIM_METHOD,
                    graphsupport::graphconstants::NTYPE_LIM_FUNCTION,
                    graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE,
                    graphsupport::graphconstants::NTYPE_LIM_COMPONENT,
                    graphsupport::graphconstants::NTYPE_LIM_NAMESPACE
                }},
                {graphsupport::graphconstants::HEADER_ASG_VALUE_C, {
                    graphsupport::graphconstants::NTYPE_LIM_ENUM,
                    graphsupport::graphconstants::NTYPE_LIM_STRUCTURE,
                    graphsupport::graphconstants::NTYPE_LIM_FUNCTION,
                    graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE,
                    graphsupport::graphconstants::NTYPE_LIM_COMPONENT,
                    graphsupport::graphconstants::NTYPE_LIM_NAMESPACE
                }},
                {graphsupport::graphconstants::HEADER_ASG_VALUE_RPG, {
                    graphsupport::graphconstants::NTYPE_RPG_SYSTEM,
                    graphsupport::graphconstants::NTYPE_RPG_PROGRAM,
                    graphsupport::graphconstants::NTYPE_RPG_PROCEDURE,
                    graphsupport::graphconstants::NTYPE_RPG_SUBROUTINE,
                    graphsupport::graphconstants::NTYPE_LIM_COMPONENT
                }},
                {graphsupport::graphconstants::HEADER_ASG_VALUE_PYTHON, {
                    graphsupport::graphconstants::NTYPE_LIM_CLASS,
                    graphsupport::graphconstants::NTYPE_LIM_METHOD,
                    graphsupport::graphconstants::NTYPE_LIM_FUNCTION,
                    graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE,
                    graphsupport::graphconstants::NTYPE_LIM_COMPONENT,
                    graphsupport::graphconstants::NTYPE_LIM_PACKAGE,
                    graphsupport::graphconstants::NTYPE_LIM_MODULE
                }},
                {graphsupport::graphconstants::HEADER_ASG_VALUE_CSHARP, {
                    graphsupport::graphconstants::NTYPE_LIM_CLASS,
                    graphsupport::graphconstants::NTYPE_LIM_ENUM,
                    graphsupport::graphconstants::NTYPE_LIM_INTERFACE,
                    graphsupport::graphconstants::NTYPE_LIM_STRUCTURE,
                    graphsupport::graphconstants::NTYPE_LIM_DELEGATE,
                    graphsupport::graphconstants::NTYPE_LIM_METHOD,
                    graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE,
                    graphsupport::graphconstants::NTYPE_LIM_COMPONENT,
                    graphsupport::graphconstants::NTYPE_LIM_NAMESPACE
                }},
                {graphsupport::graphconstants::HEADER_ASG_VALUE_JAVASCRIPT, {
                    graphsupport::graphconstants::NTYPE_LIM_CLASS,
                    graphsupport::graphconstants::NTYPE_LIM_METHOD,
                    graphsupport::graphconstants::NTYPE_LIM_FUNCTION,
                    graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE,
                    graphsupport::graphconstants::NTYPE_LIM_COMPONENT,
                    graphsupport::graphconstants::NTYPE_LIM_PACKAGE
                }}
            };

            RulContainer _rul(metricID, displayName.empty() ? patternName : displayName, true, "false", category, true, description);
           
            auto calculatedFor = calculatedFors.find(asg);

            if (inGraph.findNode(category) == graph::Graph::invalidNode) {
                if (category != getSUB_GROUP1().id && category != getSUB_GROUP2().id) {
                    const RulContainer SUB_GROUP(category, category, true, "summarized", "", true, "Custom Patterns");
                    addRulToRulHander(SUB_GROUP);
                }
            }

            addRulToRulHander(_rul, metricID, priority, calculatedFor->second);
        }
        // append CALCULATEDFOR to an existing pattern_warning
        else {
            auto node = inGraph.findNode("L" + std::to_string(_base.getId()));
            string nodeKind = node.getType().getType();
            addCalForToRulHandler(metricID, nodeKind);
        }

        result().finalizeGRAPHout(inGraph, _base.getFactory(), patternName, warningName, currentPatternDocument(), roleName, category);
    }

    boost::any castStringToBoostAny(const std::string &value) {
        // primitive type determining
        bool isNegative = value[0] == '-';
        bool isNumber = isNegative ? isdigit(value[1]) : isdigit(value[0]);
        bool isDecimal = isNumber ? (value.find('.') == value.find(',') ? false : true) : false;
        if (isDecimal) {
            return std::stod(value.c_str());
        }
        else if (isNumber) {
            return std::stoi(value.c_str());
        }
        else {
            return value;
        }
    }

    bool findTypeValue(const asg::base::Base& limNodeThis, const asg::base::Base& limNodeCompareTo, int depth) {
        auto getNodeTypeFromKind = [](const asg::base::Base& _limNodeThis) {
            int ID = std::stoi(getValueFromLim(_limNodeThis, "type"));
            return ID == -1 ? nullptr : (asg::type::Type*)(_limNodeThis.getFactory().getPointer(ID));
        };

        using namespace lim::asg;
        int DEPTH = depth;

        type::Type *type1 = getNodeTypeFromKind(limNodeThis);
        type::Type *type2 = getNodeTypeFromKind(limNodeCompareTo);

        if (type1 == nullptr || type2 == nullptr) return false;
        const auto &_types1 = getSingleTypes(*type1, DEPTH);
        const auto &_types2 = getSingleTypes(*type2, DEPTH);

        std::set<NodeId> _intersectTypes;
        std::set_intersection(_types1.begin(), _types1.end(), _types2.begin(), _types2.end(), std::inserter(_intersectTypes, _intersectTypes.begin()));

        return !_intersectTypes.empty();
    }

    // TODO::this
    bool recursiveNodeKindSearching(const asg::NodeKind ndk1, const asg::NodeKind ndk2)
    {
        return lim::asg::Common::getIsBaseClassKind(ndk1, ndk2);
    }

    std::string getValue(graph::Graph &inGraph, const std::string &valueToFind, const asg::base::Base& nodeToFindIn) {
        const static auto filters = [] {
            std::set<std::string> filters;
            for (const auto &var : filterTypesAndValues)
            {
                filters.insert(limTypesString[var.first]);
                for (const auto &str : var.second.second) {
                    filters.insert(str);
                }
            }
            return filters;
        }();

        if (filters.find(valueToFind) != filters.end()) {
            return getValueFromLim(nodeToFindIn, valueToFind);
        }
        else {
            // throws when 'valueToFind' is invalid
            return getValueFromGraph(limToGraph(inGraph, nodeToFindIn), valueToFind);
        }
    };

    asg::EdgeKind getEdgeKind(const std::string &_edge) {
        for (size_t index = 0; index < edgesKind.size(); index++) {
            if (edgesKind[index] == _edge) {
                return (asg::EdgeKind)index;
            }
        }
        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Edge: '" + _edge + "' is invalid in!"));
    }
    asg::NodeKind getNodeKind(const std::string &_ndk) {
        for (size_t index = 0; index < nodesKind.size(); index++) {
            if (nodesKind[index] == _ndk) {
                return (asg::NodeKind)index;
            }
        }
        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN("Node type: '" + _ndk + "' is invalid in!"));
    }
}}}