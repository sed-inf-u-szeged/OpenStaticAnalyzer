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

#pragma once
#ifndef CALCULATE_H
#define CALCULATE_H

#include "../../inc/Helpers.h"

namespace columbus { namespace lim { namespace patterns { namespace calculate {

    /**
    * \brief The base pure virtual class, every code type must derived from this
    */
    class Code {
    public:

        /**
        * \brief run the derived code class
        * \param graph [in], graph 
        * \param limNode [in], lim node
        * \param scopeVariables [in], user defined scope variables
        * \return true if everything went well during the code execution
        */
        virtual bool runCode(graph::Graph &inGraph, const asg::base::Base &base, stringAnyLValue &scopeVariables) = 0;
        
        /**
        * \brief Virtual default destructor
        */
        virtual ~Code() {};
    };

    /**
    * \brief Class that represent a block full of codes
    */
    class CodeBlock : public Code {
    protected:
        std::vector<std::unique_ptr<Code>> codes;
    public:

        /**
         * \brief Default Constructor
        */
        CodeBlock();

        /**
        * \brief Constructor
        * \param _codes [in]
        */
        CodeBlock(std::vector<Code*> &_codes);

        /**
        * \brief Default destructor
        */
        virtual ~CodeBlock();

        /**
        * \brief Adds a Code
        * \param _code [in], The code to be added into the block
        */
        void addCodeToBlock(Code* _code);

        /**
        * \brief Refere to Code::runCode
        */
        bool runCode(graph::Graph &inGraph, const asg::base::Base &base, stringAnyLValue &scopeVariables);
    };
}}}}

#endif // !CALCULATE_H