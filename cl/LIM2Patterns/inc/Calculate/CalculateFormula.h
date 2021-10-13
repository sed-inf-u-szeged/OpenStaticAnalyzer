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

#ifndef CALCULATE_FORMULA_H
#define CALCULATE_FORMULA_H

#include "Calculate.h"

namespace columbus { namespace lim { namespace patterns { namespace calculate {
    class FormulaCode : virtual public Code {
    private:
        // \brief Stores the left side of the variable assignment
        std::string left;
         // \brief Stores the right side of the variable assignment
        std::vector<std::pair<std::string, std::string>> right;
         // \brief Stores the type of the assigned valued
        boost::any _currentType;

        /**
         * \brief collect the filters
         * \return the filters name
        */
        std::set<std::string> collectFiltersOnce();
    public:

        /**
        * \brief Constructor
        * \param _left  [in], The left side of the variable assignment
        * \param _right [in], The right side of the variable assignment
        */
        FormulaCode(const std::string &_left, std::vector<std::pair<std::string, std::string>> &_right);
        FormulaCode(const std::string &_left, std::vector<std::pair<std::string, std::string>> &&_right);

        /**
         * \brief Default Destructor
        */
        ~FormulaCode();

        /**
        * \brief Refere to Code::runCode
        */
        bool runCode(graph::Graph &inGraph, const asg::base::Base &base, stringAnyLValue &scopeVariables);
    };
}}}}

#endif // !CALCULATE_FORMULA_H
