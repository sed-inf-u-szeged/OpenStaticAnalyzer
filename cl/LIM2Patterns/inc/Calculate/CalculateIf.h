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

#ifndef CALCULATE_IF_H
#define CALCULATE_IF_H

#include "Calculate.h"
#include "../Conditions/Condition.h"

namespace columbus { namespace lim { namespace patterns { namespace calculate {
    class IfCode : public Code {
    private:
        // \brief Stores the condition to be tested in the if statement
        std::unique_ptr<conditions::Condition> condition;
        // \brief Stores the local variables defined inside the loop block
        std::set<std::string> defineLocalVariables;
        // \brief Stores the codes inside it's loop
        std::unique_ptr<CodeBlock> codeBlock;
        // \brief Stores the else if statements
        std::vector<std::unique_ptr<IfCode>> elseIfStatements;
        // \brief Stores the else statements
        std::unique_ptr<IfCode> elseStatement;

    public:

        /**
        * \brief Constructor
        * \param _condition [in], The condition of the if code
        * \param _defineLocalVariables [in], The local variables defined inside the loop block
        */
        IfCode(conditions::Condition *_condition, CodeBlock* _code, const std::set<std::string> &_defineLocalVariables = {});

        /**
         * \brief Default Destructor
        */
        ~IfCode();

        /**
         * \brief Adds an else if branch to the if statement
         * \param _ifCode [in], The Else if branch to be added
        */
        void addElseIfStatemnt(IfCode* _ifCode);

        /**
         * \brief Sets the else branch to the if statement
         * \param _ifCode [in], The Else branch to be set
        */
        void setElseStatement(IfCode* _ifCode);

        /**
        * \brief Refere to Code::runCode
        */
        bool runCode(graph::Graph &inGraph, const asg::base::Base &base, stringAnyLValue &scopeVariables);
    };
}}}}

#endif // !CALCULATE_IF_H

