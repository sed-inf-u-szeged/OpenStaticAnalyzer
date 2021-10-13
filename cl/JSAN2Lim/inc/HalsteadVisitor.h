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

#ifndef __HALSTEAD_VISITOR_JS__
#define __HALSTEAD_VISITOR_JS__

#include "lim/inc/lim.h"
#include "javascript/inc/javascript.h"

namespace columbus {
    namespace JSAN2Lim {
        class HalsteadVisitor : public javascript::asg::VisitorAbstractNodes {
        public:
            struct HalsteadInfo {
                unsigned int n1 = 0; // distinct operators
                unsigned int n2 = 0; // distinct operands
                unsigned int N1 = 0; // total operators
                unsigned int N2 = 0; // total operands

                HalsteadInfo() {}
                HalsteadInfo(unsigned int n1, unsigned int n2, unsigned int N1, unsigned int N2) :
                    n1(n1)
                    , n2(n2)
                    , N1(N1)
                    , N2(N2) {}
            };

        private:
            enum OperatorTypes {
                opkArray,
                opkArrowFunction,
                opkAssignment,
                opkAwait,
                opkBreak,
                opkBlockStatement,
                opkClass,
                opkClassBody,
                opkConditionalExpression,
                opkContinue,
                opkDebugger,
                opkDoWhile,
                opkElse,
                opkEmptyStatement,
                opkExportSpecifier,
                opkExportAllDeclaration,
                opkExportDefaultDeclaration,
                opkExportNamedDeclaration,
                opkFor,
                opkFunctionDeclaration,
                opkIf,
                opkImportDefaultSpecifier,
                opkImportNamespaceSpecifier,
                opkImportSpecifier,
                opkImpSpecifier,
                opkMetaProperty,
                opkModuleDeclaration,
                opkNewExpression,
                opkReturn,
                opkSeparator,
                opkSwitch,
                opkTry,
                opkThis,
                opkThrow,
                opkYieldExpression,
                opkWhile,
                opkSuper,
                opkFinally,
                opkCatch,
                opkCase,
                opkModuleSpecifier,
                opkImportDeclaration,
                opkCallExpression,
                opkObjectExpression,
                opkTemplateElement,
                opkMemberExpression,
                opkForOfStatement,
                opkForInStatement,
                opkWithStatement,
                opkSpreadElement,
                opkArrayPattern,
                opkObjectPattern,
                opkAssignmentPattern,
                opkVariableInitializer
            };

            struct MethodInfo {
                MethodInfo() :
                    method(NULL)
                    , halsteadInfo()
                    , operatorKinds()
                    , identifiers()
                    , labels()
                    , properties()
                    , numberLiterals()
                    , regexLiterals()
                    , booleanLiterals()
                    , stringLiterals()
                    , nullLiterals(0) {}

                const javascript::asg::base::Positioned* method;
                HalsteadInfo halsteadInfo;
                std::map<NodeId, unsigned int> operatorNodes;
                std::map<std::string, unsigned int> operatorKinds;
                std::map<std::string, unsigned int> identifiers;
                std::map<std::string, unsigned int> labels;
                std::map<std::string, unsigned int> properties;

                std::map<std::string, unsigned int> numberLiterals;
                std::map<std::string, unsigned int> regexLiterals;
                std::map<std::string, unsigned int> booleanLiterals;
                std::map<std::string, unsigned int> stringLiterals;
                unsigned int nullLiterals;
            };

            javascript::asg::Factory& javascriptFactory;    ///< Reference to the (current) JSAN factory
            std::stack<MethodInfo> methodStack;             ///< Stack for the current Method info
            std::stack<NodeId> classStack;                  ///< Stack for the current class id
            bool countSeparators;                           ///< Set separator counting enabled/disabled
            std::map<NodeId, HalsteadInfo> halsteadInfos;   ///< Stores the halstead data for each method

            void incOperands(const javascript::asg::base::Base&);
            void incOperators(std::string, unsigned int);
            void incLiteral(const javascript::asg::NodeKind&, const std::string&);
            bool ignore();

            // For debug purposes
            void printMethodInfo(const MethodInfo&);

            void enterMethod(const javascript::asg::base::Positioned& node);
            void leaveMethod(const javascript::asg::base::Positioned& node);

            inline unsigned int safeDecrement(unsigned int number, unsigned int subtrahend) {
                return (number - subtrahend) > 0 ? number - subtrahend : 0;
            }

            std::string getEnumText(javascript::asg::AssignmentOperator);
            std::string getEnumText(javascript::asg::BinaryOperator);
            std::string getEnumText(javascript::asg::DeclarationKind);
            std::string getEnumText(javascript::asg::LogicalOperator);
            std::string getEnumText(javascript::asg::PropertyKind);
            std::string getEnumText(javascript::asg::UnaryOperator);
            std::string getEnumText(javascript::asg::UpdateOperator);
            std::string getEnumText(javascript::asg::NodeKind);
            std::string getEnumText(OperatorTypes);
        public:
            HalsteadVisitor(javascript::asg::Factory&, bool = false);
            // Declarations
            virtual void visit(const javascript::asg::structure::Class&, bool);
            virtual void visitEnd(const javascript::asg::structure::Class&, bool);
            virtual void visit(const javascript::asg::declaration::ExportAllDeclaration&, bool);
            virtual void visit(const javascript::asg::declaration::ExportDefaultDeclaration&, bool);
            virtual void visit(const javascript::asg::declaration::ExportNamedDeclaration&, bool);
            // Function declaration
            virtual void visit(const javascript::asg::declaration::FunctionDeclaration&, bool);
            virtual void visitEnd(const javascript::asg::declaration::FunctionDeclaration&, bool);
            virtual void visit(const javascript::asg::declaration::ImportDeclaration&, bool);
            virtual void visit(const javascript::asg::declaration::ModuleDeclaration&, bool);
            virtual void visit(const javascript::asg::declaration::VariableDeclaration&, bool);
            virtual void visit(const javascript::asg::declaration::VariableDeclarator&, bool);
            // Expressions
            virtual void visit(const javascript::asg::expression::ArrayExpression&, bool);
            virtual void visit(const javascript::asg::expression::ArrowFunctionExpression&, bool);
            virtual void visit(const javascript::asg::expression::AssignmentExpression&, bool);
            virtual void visit(const javascript::asg::expression::AwaitExpression&, bool);
            virtual void visit(const javascript::asg::expression::BinaryExpression&, bool);
            virtual void visit(const javascript::asg::expression::BooleanLiteral&, bool);
            virtual void visit(const javascript::asg::expression::CallExpression&, bool);
            virtual void visit(const javascript::asg::expression::ConditionalExpression&, bool);
            virtual void visit(const javascript::asg::expression::FunctionExpression&, bool);
            virtual void visit(const javascript::asg::expression::Identifier&, bool);
            virtual void visit(const javascript::asg::expression::LogicalExpression&, bool);
            virtual void visit(const javascript::asg::expression::MemberExpression&, bool);
            virtual void visit(const javascript::asg::expression::MetaProperty&, bool);
            virtual void visit(const javascript::asg::expression::NewExpression&, bool);
            virtual void visit(const javascript::asg::expression::NullLiteral&, bool);
            virtual void visit(const javascript::asg::expression::NumberLiteral&, bool);
            virtual void visit(const javascript::asg::expression::ObjectExpression&, bool);
            virtual void visit(const javascript::asg::expression::Property&, bool);
            virtual void visit(const javascript::asg::expression::RegExpLiteral&, bool);
            virtual void visit(const javascript::asg::expression::SequenceExpression&, bool);
            virtual void visit(const javascript::asg::expression::SpreadElement&, bool);
            virtual void visit(const javascript::asg::expression::StringLiteral&, bool);
            virtual void visit(const javascript::asg::expression::Super&, bool);
            virtual void visit(const javascript::asg::expression::TaggedTemplateExpression&, bool);
            virtual void visit(const javascript::asg::expression::TemplateLiteral&, bool);
            virtual void visit(const javascript::asg::expression::TemplateElement&, bool);
            virtual void visit(const javascript::asg::expression::ThisExpression&, bool);
            virtual void visit(const javascript::asg::expression::UnaryExpression&, bool);
            virtual void visit(const javascript::asg::expression::UpdateExpression&, bool);
            virtual void visit(const javascript::asg::expression::YieldExpression&, bool);
            //Statements
            virtual void visit(const javascript::asg::statement::ArrayPattern&, bool);
            virtual void visit(const javascript::asg::statement::AssignmentPattern&, bool);
            virtual void visit(const javascript::asg::statement::BlockStatement&, bool);
            virtual void visit(const javascript::asg::statement::BreakStatement&, bool);
            virtual void visit(const javascript::asg::statement::CatchClause&, bool);
            virtual void visit(const javascript::asg::statement::ContinueStatement&, bool);
            virtual void visit(const javascript::asg::statement::DebuggerStatement&, bool);
            virtual void visit(const javascript::asg::statement::WhileStatement&, bool);
            virtual void visit(const javascript::asg::statement::EmptyStatement&, bool);
            virtual void visit(const javascript::asg::statement::ForInStatement&, bool);
            virtual void visit(const javascript::asg::statement::ForStatement&, bool);
            virtual void visit(const javascript::asg::statement::Function&, bool);
            virtual void visitEnd(const javascript::asg::statement::Function&, bool);
            virtual void visit(const javascript::asg::statement::IfStatement&, bool);
            virtual void visit(const javascript::asg::statement::LabeledStatement&, bool);
            virtual void visit(const javascript::asg::statement::ObjectPattern&, bool);
            virtual void visit(const javascript::asg::statement::RestElement&, bool);
            virtual void visit(const javascript::asg::statement::ReturnStatement&, bool);
            virtual void visit(const javascript::asg::statement::SwitchCase&, bool);
            virtual void visit(const javascript::asg::statement::SwitchStatement&, bool);
            virtual void visit(const javascript::asg::statement::ThrowStatement&, bool);
            virtual void visit(const javascript::asg::statement::TryStatement&, bool);
            virtual void visit(const javascript::asg::statement::WithStatement&, bool);
            //Structures
            virtual void visit(const javascript::asg::structure::ClassBody&, bool);
            virtual void visit(const javascript::asg::structure::ExportSpecifier&, bool);
            virtual void visit(const javascript::asg::structure::ImpSpecifier&, bool);
            virtual void visit(const javascript::asg::structure::MethodDefinition&, bool);
            virtual void visitEnd(const javascript::asg::structure::MethodDefinition&, bool);
            virtual void visit(const javascript::asg::structure::ModuleSpecifier&, bool);
            // Too general
            // virtual void visit(const javascript::asg::statement::Statement&, bool);
            // virtual void visit(const javascript::asg::statement::Pattern&, bool);
            // virtual void visit(const javascript::asg::statement::ExpressionStatement&, bool);
            // virtual void visit(const javascript::asg::declaration::Declaration&, bool);
            // virtual void visit(const javascript::asg::expression::Literal&, bool);
            //
            // Handled in Class
            // virtual void visit(const javascript::asg::declaration::ClassDeclaration&, bool);
            // virtual void visitEnd(const javascript::asg::declaration::ClassDeclaration&, bool);
            // virtual void visit(const javascript::asg::expression::ClassExpression&, bool);
            //
            // Handled in ImpSpecifier
            // virtual void visit(const javascript::asg::structure::ImportDefaultSpecifier&, bool);
            // virtual void visit(const javascript::asg::structure::ImportNamespaceSpecifier&, bool);
            // virtual void visit(const javascript::asg::structure::ImportSpecifier&, bool);
            //
            // Handled in ForInStatement
            // virtual void visit(const javascript::asg::statement::ForOfStatement&, bool);
            //
            // Handled in WhileStatement
            // void visit(const javascript::asg::statement::DoWhileStatement&, bool);
            //
            // Handled in Property
            // virtual void visit(const javascript::asg::expression::AssignmentProperty&, bool);

            std::map<NodeId, HalsteadVisitor::HalsteadInfo> getHalsteadValues();
        };
    }
}
#endif
