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

#ifndef CONDITION_VALIDATOR_H
#define CONDITION_VALIDATOR_H

#include "../Conditions.h"
#include "../../inc/Helpers.h"

namespace columbus { namespace lim { namespace patterns { namespace conditions { 
    namespace validator {
        /**
         * \brief Checks whether the given Yaml Node is correct, throws if not
         * \param node, the yaml node to be checked
        */
        void validateNode(const YAML::Node& node);

        /**
         * \brief Checks whether the given formulas are correct
         * \param formulaLeft, left side of the condition
         * \param formulRight, right side of the condition
         * \param relType, the relation between the 2
         * \return true if everything is correct
        */
        void validateScalar(const std::string &formula, std::vector<std::string> &formulaLeft, std::vector<std::string> &formulRight, const ConditionTypes &relType, const std::string &relation);

        /**
         * \brief Checks whether the given Map(All/Any) is correct, throws if not
         * \param node [in], the yaml node
         * \param edgeKind [inOut], the edge type of the yaml node
         * \param direction [inOut], the edge direction of the yaml node
        */
        void validateMap(const YAML::Node &node, asg::EdgeKind &edgeKind, Direction &direction);

    }
}}}}

#endif // !PATTERN_CHECKER_H
