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

#ifndef MULTI_CONDITION_H
#define MULTI_CONDITION_H

#include "../../inc/Conditions/Condition.h"

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    class MultiCondition : public Condition {
    public:
    
        /**
         * \brief Default Constructor
        */
        MultiCondition();

        /**
         * \brief Copy Constructor
        */
        MultiCondition(MultiCondition *multiCond);

        /**
         * \brief Default Constructor
        */
        ~MultiCondition();

        /**
         * \brief Adds a condition
         * \param _condition [in], The condition that's to be added
        */
        void addCondition(Condition *_condition);

        /**
        * \brief Refere to Condition::testCondition
        */
        bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode);

        /**
        * \brief Getter
        * \return the member named "conditions"
        */
        const std::vector<std::unique_ptr<Condition>>& getConditions();
    protected:

        // \brief Storing conditions
        std::vector<std::unique_ptr<Condition>> conditions;
    };
}}}}

#endif // !MULTI_CONDITION_H