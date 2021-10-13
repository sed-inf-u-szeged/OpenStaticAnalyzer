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

#ifndef OR_CONDITION_H
#define OR_CONDITION_H

#include "MultiCondition.h"

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    /**
    * \brief Class that represent the Condition named 'Or' in our pattern
    */
    class OrCondition : public MultiCondition {
    public:

        /**
         * \brief Default Constructor
        */
        OrCondition();

        /**
        * \brief Copy Constructor
        * \param multiCond [in]
        */
        OrCondition(MultiCondition *multiCond);

        /**
        * \brief Refere to Condition::testCondition
        */
        virtual bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode);
    };

}}}}

#endif // !OR_CONDITION_H
