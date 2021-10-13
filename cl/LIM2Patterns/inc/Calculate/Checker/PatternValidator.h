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

#ifndef CALCULATE_VALIDATOR_H
#define CALCULATE_VALIDATOR_H

#include "../Calculate.h"

namespace columbus { namespace lim { namespace patterns { namespace calculate { namespace validator {
    
    void validateNode(const YAML::Node &node);

    void validateMap(const YAML::Node &node, const std::string &type, const YAML::Node &_second, stringAnyLValue &variables);

    void validateSequence(const YAML::Node &node);

    void validateScalar(std::vector<std::string> splitLeft, std::vector<std::string> splitRight, stringAnyLValue &variables);

}}}}}

#endif