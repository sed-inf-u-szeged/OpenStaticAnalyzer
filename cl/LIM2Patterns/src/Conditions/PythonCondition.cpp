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

#include "../../inc/Conditions/PythonCondition.h"
#include "../../inc/messages.h"
#include "../../inc/PythonBinding.h"

using namespace std;
using namespace columbus::graph;
using namespace columbus::lim::asg;
using namespace columbus::lim::asg::base;

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    PythonCondition::PythonCondition(const py::module &_Module) : _module(_Module) {
        //const auto stringType = py::str().get_type();
        //const auto arrayType = py::cast(vector<py::dict>()).get_type();
        //const auto boolType = py::bool_().get_type();

        try {
            py::object _ndk = _module.attr("kind");
            string ndk = pythonBinding::NodeBinding::castPyToString(_ndk);
            if (ndk.empty() || std::find(nodesKind.begin(), nodesKind.end(), ndk) == std::end(nodesKind)) throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("Node type '" + ndk + "' is not valid!"));
            nodeKind = getNodeKind(ndk);
        }
        catch (const columbus::Exception&) {
            throw;
        }
        catch (...) {
            // ignore exception
            nodeKind = getNodeKind("ndkBase");
        }

        try {
            py::object visit = _module.attr("visit");
            if (visit.is_none() || !visit) {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("A visit function with a NodeBinding parameter must be defined!"));
            }
        }
        catch (...) {
            throw;
        }

        try {
            py::object _patternName = _module.attr("name");
            if (_patternName && !_patternName.is_none()) {
                this->patternName = pythonBinding::NodeBinding::castPyToString(_patternName);
            }
            /*else {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_INCORRECT_PATTERN_PY("Python pattern missing 'name' attribute!\n"));
            }*/
        }
        catch (...) {
            // ignore exception
        }
    };
    PythonCondition::~PythonCondition() { }

    bool PythonCondition::testCondition(graph::Graph & inGraph, const asg::base::Base & limNode)
    {
        if (recursiveNodeKindSearching(limNode.getNodeKind(), nodeKind)) {
            pythonBinding::NodeBinding _nB(limNode, inGraph);
            py::object visit = _module.attr("visit")(_nB);
            if (!visit.is_none()) {
                string message = pythonBinding::NodeBinding::castPyToString(visit);
                if (!message.empty()) common::WriteMsg::write(common::WriteMsg::mlNormal, message);
                return true;
            }
        }
        return false;
    }

    const std::string & PythonCondition::getPatternName()
    {
        return this->patternName;
    }

}}}}
