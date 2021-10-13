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

#ifndef CREATE_CONDITION_NODE_H
#define CREATE_CONDITION_NODE_H

#include "Checker/PatternValidator.h"

namespace columbus { namespace lim { namespace patterns { 
    namespace RPN {

        /**
         * \brief Converts the given math formula into a postfix processable form
         * \param formula [in],  The formula that's to be converted
         * \param result  [out], The output postfix vector
        */
        void formulaToPostfix(std::vector<std::string> &formula, std::vector<conditions::FormulaCondition::FormulaPart*> &result);

        /**
         * \brief Computes the given postfix math formula
         * \param formula [in], The formula that's to be calculated
         * \return The result of the formula
        */
        double postfixCalculate(std::vector<std::unique_ptr<conditions::FormulaCondition::FormulaPart>> &formula);
    }

    namespace conditions {

        /**
         * \brief Converts the given pathfile into yaml
         * \param patternFileName [in], The path of the pattern file
        */ 
        std::vector<YAML::Node> convertToYaml(const std::string & patternFileName);
        
        /**
         * \brief Splits the given math/formula string into a vector
         * \param formula [in], The string that's to be converted
         * \param out     [out], The output vector
        */
        void splitFormula(const std::string &formula, std::vector<std::string> &out);
        
        /**
         * \brief Creates the condition, by processing the given yaml node
         * \param node           [in], The yaml structure that's to be converted into a Condition
         * \param patternsFolder [in], Predefined pattern folder, it's given by the program parameter
        */
        NodeTypeCondition* createCondition(const YAML::Node &node, const std::string &patternsFolder);
        
        /**
         * \brief Creates a node type condition, by processing the given yaml node
         * \param node           [in], The yaml structure that's to be converted into a Condition
         * \param patternsFolder [in], Predefined pattern folder, it's given by the program parameter
        */
        Condition* createConditionFromNodeType(const YAML::Node &node, const std::string &patternsFolder);
        
        /**
         * \brief Creates a nand/xor/nor/all/any/or/and type condition, by processing the given yaml node
         * \param node           [in], The yaml structure that's to be converted into a Condition
         * \param patternsFolder [in], Predefined pattern folder, it's given by the program parameter
        */
        Condition* createConditionFromMap(const YAML::Node &node, const std::string &patternsFolder);
        
        /**
         * \brief Creates an array type condition, by processing the given yaml node
         * \param node           [in], The yaml structure that's to be converted into a Condition
         * \param patternsFolder [in], Predefined pattern folder, it's given by the program parameter
        */
        Condition* createConditionFromArray(const YAML::Node &node, const std::string &patternsFolder);
        
        /**
         * \brief Creates a formula type condition, by processing the given yaml node
         * \param node           [in], The yaml structure that's to be converted into a Condition
         * \param patternsFolder [in], Predefined pattern folder, it's given by the program parameter
        */
        Condition* createConditionFromScalar(const YAML::Node &node, const std::string &patternsFolder);
    }
}}}
#endif // !CREATE_CONDITION_NODE_H