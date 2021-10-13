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

#ifndef CONDITION_BASE_H
#define CONDITION_BASE_H
#define NO_VALUE (uint32_t)(-1)

#include <graph/inc/graph.h>
#include <lim/inc/lim.h>
#include <vector>
#include <string>

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    
    /**
    * \brief The base pure virtual class, every condition type must derived from this
    */
    class Condition {
    public:
        /**
        * \brief test the derived condition class
        * \param graph [in], graph 
        * \param limNode [in], lim node
        * \return whether the tested condition is true
        */
        virtual bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode) = 0;

        /**
        * \brief Virtual default destructor
        */
        virtual ~Condition() {};
    };
}}}}

#endif // !CONDITION_BASE_H