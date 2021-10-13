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

#ifndef PYTHON_CONDITION_H
#define PYTHON_CONDITION_H

#include "Condition.h"
#include <pybind11/stl.h>

namespace py = pybind11;

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    #pragma GCC visibility push(hidden)
    class PythonCondition : virtual public Condition {
    private:
        // \brief Stores the name of the pattern
        std::string patternName;
        // \brief Stores the node type of the pattern
        lim::asg::NodeKind nodeKind;
   	// \brief Stores the python module, we need a copy of the actual module, not a reference
        py::module _module;

    public:
        PythonCondition(const py::module &_Module);
        virtual ~PythonCondition();
        bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode);

        /**
       * \brief Getter
       * \return The reference to the "patternName" member
       */
        const std::string &getPatternName();
    };

}}}}

#endif //PYTHON_CONDITION_H
