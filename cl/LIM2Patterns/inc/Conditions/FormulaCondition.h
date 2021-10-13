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

#ifndef FORMULA_CONDITION_H
#define FORMULA_CONDITION_H

#include "Condition.h"
#include "../../inc/Helpers.h"

namespace columbus { namespace lim { namespace patterns { namespace conditions {
    
    class FormulaCondition : public Condition {
    public:
        // \brief Helper data class for formula evaluation
        struct FormulaPart {
            enum Type {Operator, Variable, Number} type;
            long double value;
            bool isNegative = false;
            FormulaPart(Type _type) : type(_type) {}
            virtual ~FormulaPart() {};
        };
        struct Operator : virtual public FormulaPart {
            std::string sign;
            Operator() : FormulaPart(FormulaPart::Type::Operator) {}
        };
        struct Variable : virtual public FormulaPart {
            std::string name;
            std::vector<std::string> parentRoles;
            Variable(FormulaPart::Type _type) : FormulaPart(_type) {}
        };

    private:

        // \brief pair<value to find in (e.g. role name), value to find>
        std::vector<std::unique_ptr<FormulaPart>> left;
        // \brief Relation type between the left and right formula
        ConditionTypes relation;
        // \brief pair<value to find in (e.g. role name), value to find>
        std::vector<std::unique_ptr<FormulaPart>> right;

    public:

        /**
         * \brief Determines the default values for every type (e.g. string, int, double)
         * \param _anyValue [in], The type of the value
         * \return The default value for the given parameter
        */
        //static boost::any defaultValueForBoostAny(const boost::any &_anyValue);

        /**
        * \brief Constructor
        * \param leftPostfix  [in], The left side of the formula
        * \param relationType [in], The relation type between the left and the righ formula
        * \param rightPostfix [in], The right side of the formula
        */
        FormulaCondition(std::vector<FormulaPart*> &leftPostfix, ConditionTypes relationType, std::vector<FormulaPart*> &rightPostfix);
        
        /**
         * \brief Default Destructor
        */
        ~FormulaCondition();

        /**
        * \brief Refere to Condition::testCondition
        */
        bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode);
    };

}
}}}

#endif // !FORMULA_CONDITION_H
