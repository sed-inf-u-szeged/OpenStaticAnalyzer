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

#ifndef NODE_TYPE_CONDITION_H
#define NODE_TYPE_CONDITION_H

#include "Condition.h"
//#include "../Calculate/Calculate.h"

namespace columbus { namespace lim { namespace patterns { namespace conditions {

    /**
    * \brief Class that represent the Condition named 'Node'
    */
    class NodeTypeCondition : virtual public Condition {
    private:
        // \brief Stores the name of the pattern
        std::string patternName;
        // \brief Stores the displayable name of the pattern
        std::string displayName;
        // \brief Stores the pattern's category (Antipattern/Designpattern)
        std::string category;
        // \brief Stores pattern's description
        std::string description;
        // \brief Stores pattern's role name
        std::string roleName;
        // \brief Stores pattern's priority, used for rule generation
        std::string priority;

        // \brief Stores pattern's filter conditions
        std::unique_ptr<Condition> filterCondition;
        // \brief Stores pattern's conditions
        std::unique_ptr<Condition> condition;
        // \brief Stores the node type of the pattern
        lim::asg::NodeKind nodeKind;
        // \brief Stores pattern's code that's to be calculated
        // TODO:: Calculate remove
        //std::unique_ptr<calculate::Code> calculate;
    public:
        // TODO:: Calculate remove
        /**
        * \brief Constructor
        * \param _nodeKind [in], The node type of the pattern
        * \param _condition [in]
        * \param _filterCondition [in]
        * \param _calculateCode [in], The code that's to be calculated
        * \param _patternName [in], The name of the pattern
        * \param _category [in], Antipattern/Designpattern/Custonpattern
        * \param _description [in]
        * \param _priority [in], Used for rule generation
        */
        NodeTypeCondition(lim::asg::NodeKind _nodeKind, Condition *_condition, Condition *_filterCondition, /*calculate::Code *_calculateCode,*/ const std::string &_roleName, const std::string &_patternName, const std::string &_displayName, const std::string &_category, const std::string &_description, const std::string &_priority);

        /**
         * \brief Default Destructor
        */
        virtual ~NodeTypeCondition();

        /**
        * \brief Refere to Condition::testCondition
        */
        bool testCondition(graph::Graph &inGraph, const asg::base::Base& limNode);

        /**
        * \brief Getter
        * \return The reference to the "nodeKind" member
        */
        const lim::asg::NodeKind &getNodeKind();

        /**
        * \brief Getter
        * \return The reference to the "patternName" member
        */
        const std::string &getPatternName();

        /**
        * \brief Getter
        * \return The reference to the "nodeKind" member
        */
        const std::string &getDisplayName();

        /**
        * \brief Getter
        * \return The reference to the "category" member
        */
        const std::string &getCategory();

        /**
        * \brief Getter
        * \return The reference to the "description" member
        */
        const std::string &getDescription();

        /**
        * \brief Getter
        * \return The reference to the "roleName" member
        */
        const std::string &getRoleName();

        /**
        * \brief Getter
        * \return The reference to the "priority" member
        */
        const std::string &getPriority();

        /**
        * \brief Getter
        * \return The reference to the "filterCondition" member
        */
        const std::unique_ptr<Condition>& getFilterCondition();
    };

}}}}

#endif // !NODE_TYPE_CONDITION_H