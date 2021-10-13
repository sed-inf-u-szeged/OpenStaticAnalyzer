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

#ifndef NOT_CONDITION_H
#define NOT_CONDITION_H

#include "MultiCondition.h"

namespace columbus {
    namespace lim {
        namespace patterns {
            namespace conditions {

                /**
                * \brief Class that represent the Condition named 'And'
                */
                class NotCondition : public Condition {
                public:
                    /**
                    * \brief default Constructor
                    */
                    NotCondition(Condition *_condition);

                    virtual ~NotCondition();

                    /**
                    * \brief Refer to Condition::testCondition
                    */
                    virtual bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode);

                private:
                    std::unique_ptr<Condition> condition;
                };

            }
        }
    }
}

#endif // !NOT_CONDITION_H
