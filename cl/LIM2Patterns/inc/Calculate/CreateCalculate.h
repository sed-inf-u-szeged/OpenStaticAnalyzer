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

#ifndef CREATE_CALCULATE_H
#define CREATE_CALCULATE_H

#include "Calculate.h"
#include "CalculateFor.h"
#include "CalculateFormula.h"
#include "CalculateIf.h"

namespace columbus { namespace lim { namespace patterns { namespace calculate {

    /**
     * \brief Creates the code that's to be run after filtering, by processing the given yaml node
     * \param node [in], The yaml structure that's to be converted into a Condition
    */
    Code* createCalculate(const YAML::Node &node);

    /**
     * \brief Creates a for/if/formula code that's to be run after filtering, by processing the given yaml node
     * \param node [in], The yaml structure that's to be converted into a Condition
    */
    Code* createCalculateFromMap(const YAML::Node &node);

    /**
     * \brief Creates a code block that's to be run after filtering, by processing the given yaml node
     * \param node [in], The yaml structure that's to be converted into a Condition
    */
    Code* createCalculateFromArray(const YAML::Node &node);

    /**
     * \brief Creates a formula that's to be run after filtering, by processing the given yaml node
     * \param node [in], The yaml structure that's to be converted into a Condition
    */
    Code* createCalculateFromScalar(const YAML::Node &node);
}}}}

#endif // !CREATE_CALCULATE_H

