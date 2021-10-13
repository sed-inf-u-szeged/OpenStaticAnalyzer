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

#ifndef CALCULATE_FOR_H
#define CALCULATE_FOR_H

#include "Calculate.h"

namespace columbus { namespace lim { namespace patterns { namespace calculate {

    /**
    * \brief Class that represent a for loop code
    */
    class EdgeForCode : public Code {
    private:

        // \brief Stores the direction where we want to go in the LIM
        Direction direction;
        // \brief Stores the local variable defined by the loop
        std::string localVariableName;
        // \brief Stores the local variables defined inside the loop block
        std::set<std::string> defineLocalVariables;
        // \brief Stores the name of a vaiable/role where the edge is attached to
        std::string nodeToFindIn;
        // \brief Stores the kind of edge we want to visit
        asg::EdgeKind edgeKind;
        // \brief Stores the codes inside it's loop
        std::unique_ptr<CodeBlock> codeBlock;
    public:

        /**
        * \brief Constructor
        * \param _direction             [in], The direction in the node we wish to go
        * \param _localVariableName     [in], The local variable defined by the loop
        * \param _defineLocalVariables  [in], The local variables defined inside the loop block
        * \param _nodeToFindIn          [in], The name of a vaiable/role where the edge is attached to
        * \param _edgeKind              [in], The kind of the edge.
        * \param _code                  [in], The codes inside it's loop
        */
        EdgeForCode(Direction &_direction, const std::string &_localVariableName, const std::set<std::string> _defineLocalVariables, const std::string &_nodeToFindIn, asg::EdgeKind _edgeKind, CodeBlock* _code);

        /**
        * \brief Default destructor
        */
        ~EdgeForCode();

        /**
        * \brief Refere to Code::runCode
        */
        bool runCode(graph::Graph &inGraph, const asg::base::Base &base, stringAnyLValue &scopeVariables);
    };
}}}}
#endif // !CALCULATE_FOR_H
