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

#ifndef ALL_CONDITION_H
#define ALL_CONDITION_H

#include "Condition.h"
#include "NodeTypeCondition.h"
#include "../Helpers.h"

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    /**
    * \brief Class that represent the Condition named 'All' in our pattern
    */
    class AllCondition : public Condition {
    private:
        // \brief Travel from node/type...
        std::vector<std::string> from;
        // \brief Stores the direction where we want to go in the LIM
        Direction edgeDirection;
        // \brief Stores the kind of edge we want to visit
        asg::EdgeKind edgeKind;
        // \brief Stores a Node Condition, must not be null
        std::unique_ptr<NodeTypeCondition> nodeCondition;

    public:
        
        /**
        * \brief Constructor
        * \param _edgeKind      [in], The kind of the edge.
        * \param _edgeDirection [in], The direction in the node we wish to go
        * \param _condition     [in], Ref. to 'NodeTypeCondition' Class
        */
        AllCondition(const asg::EdgeKind _edgeKind, Direction _edgeDirection, const std::vector<std::string> &_from, NodeTypeCondition *_condition);
        
        /**
        * \brief Default destructor
        */
        ~AllCondition();

        /**
        * \brief Refere to Condition::testCondition
        */
        bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode);
    };

}}}}

#endif // !ALL_CONDITION_H
