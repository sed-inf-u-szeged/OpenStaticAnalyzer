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

#include "../inc/HalsteadVisitor.h"
#include "../inc/messages.h"
#include <numeric>

#define VISIT_BEGIN(node,callVirtualBase,visitName) \
  VisitorAbstractNodes::visit( node, callVirtualBase ); \
  if ( common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDDebug ) \
  { \
    common::WriteMsg::write( CMSG_VISIT_BEGIN, visitName, node.getId(), 0 ); \
  }

#define VISIT_END(node,callVirtualBase,visitName) \
  VisitorAbstractNodes::visitEnd( node, callVirtualBase );

#define VISIT_END_FIRST(node,visitName) \
  if ( common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDDebug ) \
  { \
    common::WriteMsg::write( CMSG_VISIT_END, visitName, node.getId(), 0 ); \
  }



namespace columbus {
    namespace JSAN2Lim {
        HalsteadVisitor::HalsteadVisitor(columbus::javascript::asg::Factory& javascriptFact, bool countSeparators) :
            javascriptFactory(javascriptFact), countSeparators(countSeparators) {}

        std::map<NodeId, HalsteadVisitor::HalsteadInfo> HalsteadVisitor::getHalsteadValues() {
            return halsteadInfos;
        }

        std::string HalsteadVisitor::getEnumText(javascript::asg::AssignmentOperator kind) {
            return javascript::asg::Common::toString(kind);
        }
        std::string HalsteadVisitor::getEnumText(javascript::asg::DeclarationKind kind) {
            return javascript::asg::Common::toString(kind);
        }
        std::string HalsteadVisitor::getEnumText(javascript::asg::LogicalOperator kind) {
            return javascript::asg::Common::toString(kind);
        }
        std::string HalsteadVisitor::getEnumText(javascript::asg::PropertyKind kind) {
            return javascript::asg::Common::toString(kind);
        }
        std::string HalsteadVisitor::getEnumText(javascript::asg::UnaryOperator kind) {
            return javascript::asg::Common::toString(kind);
        }
        std::string HalsteadVisitor::getEnumText(javascript::asg::BinaryOperator kind) {
            return javascript::asg::Common::toString(kind);
        }
        std::string HalsteadVisitor::getEnumText(javascript::asg::UpdateOperator kind) {
            return javascript::asg::Common::toString(kind);
        }
        std::string HalsteadVisitor::getEnumText(javascript::asg::NodeKind kind) {
            return javascript::asg::Common::toString(kind);
        }

        std::string HalsteadVisitor::getEnumText(OperatorTypes kind) {
            const std::string kindStrings[] = {
                "opkArray",
                "opkArrowFunction",
                "opkAssignment",
                "opkAwait",
                "opkBreak",
                "opkBlockStatement",
                "opkClass",
                "opkClassBody",
                "opkConditionalExpression",
                "opkContinue",
                "opkDebugger",
                "opkDoWhile",
                "opkElse",
                "opkEmptyStatement",
                "opkExportSpecifier",
                "opkExportAllDeclaration",
                "opkExportDefaultDeclaration",
                "opkExportNamedDeclaration",
                "opkFor",
                "opkFunctionDeclaration",
                "opkIf",
                "opkImportDefaultSpecifier",
                "opkImportNamespaceSpecifier",
                "opkImportSpecifier",
                "opkImpSpecifier",
                "opkMetaProperty",
                "opkModuleDeclaration",
                "opkNewExpression",
                "opkReturn",
                "opkSeparator",
                "opkSwitch",
                "opkTry",
                "opkThis",
                "opkThrow",
                "opkYieldExpression",
                "opkWhile",
                "opkSuper",
                "opkFinally",
                "opkCatch",
                "opkCase",
                "opkModuleSpecifier",
                "opkImportDeclaration",
                "opkCallExpression",
                "opkObjectExpression",
                "opkTemplateElement",
                "opkMemberExpression",
                "opkForOfStatement",
                "opkForInStatement",
                "opkWithStatement",
                "opkSpreadElement",
                "opkArrayPattern",
                "opkObjectPattern",
                "opkAssignmentPattern",
                "opkVariableInitializer"
            };
            return kindStrings[kind];
        }

        void HalsteadVisitor::incOperands(const javascript::asg::base::Base& operand) {
            if (ignore()) return;
            MethodInfo& mi = methodStack.top();

            if (javascript::asg::Common::getIsIdentifier(operand)) {
                const auto& i = dynamic_cast<const javascript::asg::expression::Identifier&>(operand);
                std::string compactId;

                if (javascript::asg::Common::getIsRestElement(*operand.getParent())) {
                    compactId += "...";
                }

                compactId += i.getName();
                if (i.getRefersTo() != nullptr) {
                    compactId += "<" + javascript::asg::Common::getLongName(*(i.getRefersTo())) + ">";
                } else {
                    compactId += "<" + javascript::asg::Common::getLongName(i) + ">";
                }
                mi.identifiers[compactId]++;
            } else if (javascript::asg::Common::getIsLabeledStatement(operand)) {
                const auto& it = dynamic_cast<const javascript::asg::statement::LabeledStatement&>(operand);
                const auto& i = dynamic_cast<const javascript::asg::expression::Identifier&>(*it.getLabel());
                auto compactId = i.getName();

                if (i.getRefersTo() != nullptr) {
                    compactId += "<" + javascript::asg::Common::getLongName(*(i.getRefersTo())) + ">";
                }

                mi.labels[compactId]++;
            } else if (javascript::asg::Common::getIsMethodDefinition(operand)) {
                const auto& meth = dynamic_cast<const javascript::asg::structure::MethodDefinition&>(operand);
                auto compactId = javascript::asg::Common::getLongName(meth);
                mi.identifiers[compactId]++;
            } else if (javascript::asg::Common::getIsFunction(operand)) {
                const auto& meth = dynamic_cast<const javascript::asg::statement::Function&>(operand);
                auto compactId = javascript::asg::Common::getLongName(meth);
                mi.identifiers[compactId]++;
            } else if (javascript::asg::Common::getIsVariableDeclarator(operand)) {
                const auto& var = dynamic_cast<const javascript::asg::declaration::VariableDeclarator&>(operand);
                if (var.getIdentifier() == nullptr) {
                    auto compactId = javascript::asg::Common::getLongName(var);
                    mi.identifiers[compactId]++;
                }
            } else if (javascript::asg::Common::getIsProperty(operand)) {
                const auto& op = dynamic_cast<const javascript::asg::expression::Property&>(operand);
                if (op.getKey() == op.getValue()) {
                    return;
                }
            } else {
                throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_UNEXPECTED_TYPE(operand.getId(), operand.getNodeKind()));
            }
        }

        void HalsteadVisitor::incOperators(std::string enumKind, unsigned int count = 1) {
            if (ignore()) return;
            if (count <= 0) return;

            if (!countSeparators && enumKind == getEnumText(opkSeparator))
                return;

            MethodInfo& mi = methodStack.top();
            mi.operatorKinds[enumKind] += count;

            return;
        }

        void HalsteadVisitor::incLiteral(const javascript::asg::NodeKind& lt, const std::string& value) {
            if (ignore()) return;
            auto& mi = methodStack.top();

            switch (lt) {
            case javascript::asg::NodeKind::ndkBooleanLiteral:
                mi.booleanLiterals[value]++;
                break;
            case javascript::asg::NodeKind::ndkNumberLiteral:
                mi.numberLiterals[value]++;
                break;
            case javascript::asg::NodeKind::ndkNullLiteral:
                mi.nullLiterals++;
                break;
            case javascript::asg::NodeKind::ndkStringLiteral:
                mi.stringLiterals[value]++;
                break;
            case javascript::asg::NodeKind::ndkRegExpLiteral:
                mi.regexLiterals[value]++;
                break;
            case javascript::asg::NodeKind::ndkTemplateElement:
                mi.stringLiterals["tE[" + value + "]"]++;
                break;
            default:
                throw columbus::Exception(COLUMBUS_LOCATION, "Unknown literal type");
            }
        }
        void HalsteadVisitor::printMethodInfo(const MethodInfo& mi) {
            using namespace std;
            std::string methodName = "empty";
            if (javascript::asg::Common::getIsMethodDefinition(*mi.method)) {
                auto* methDef = dynamic_cast<const javascript::asg::structure::MethodDefinition*>(mi.method);
                if (javascript::asg::Common::getIsIdentifier(*methDef->getKey())) {
                    auto* id = dynamic_cast<const javascript::asg::expression::Identifier*>(methDef->getKey());
                    methodName = (id == nullptr) ? "emptyMethodDefinitionName" : id->getName();
                }
            } else if (javascript::asg::Common::getIsFunction(*mi.method)) {
                auto* function = dynamic_cast<const javascript::asg::statement::Function*>(mi.method);
                auto* id = function->getIdentifier();
                methodName = (id == nullptr) ? "emptyFunctionName" : id->getName();
            }
            std::cout << "*** " << methodName << "() -> n1=" << mi.halsteadInfo.n1 << ", n2=" << mi.halsteadInfo.n2 << ", N1=" << mi.halsteadInfo.N1 << ", N2=" << mi.halsteadInfo.N2 << std::endl;

            cout << "\tOperators: ";

            for (auto const &entry : mi.operatorKinds) {
                cout << entry.first;
                if (entry.second > 1) {
                    cout << "(x" << entry.second << ")";
                }
                cout << ", ";
            }

            for (auto const &entry : mi.operatorNodes) {
                std::string name;
                javascript::asg::base::Base& node = javascriptFactory.getRef(entry.first);
                if (javascript::asg::Common::getIsClass(node)) {
                    name = javascript::asg::Common::getLongName(node);
                }

                cout << name;
                if (entry.second > 1) {
                    cout << "(x" << entry.second << ")";
                }
                cout << ", ";
            }
            cout << endl;

            cout << "\tOperands: ";
            auto N2List = { mi.identifiers, mi.labels };
            for (auto &map : N2List) {
                for (auto const &entry : map) {
                    cout << entry.first;
                    if (entry.second > 1) {
                        cout << "(x" << entry.second << ")";
                    }
                    cout << ", ";
                }
            }
            cout << endl << "\t\tProperties: ";
            for (auto const &entry : mi.properties) {
                cout << entry.first;
                if (entry.second > 1) {
                    cout << "(x" << entry.second << ")";
                }
                cout << ", ";
            }

            cout << endl << "\t\tDistinct literals: ";
            int distinctLiterals = 0;
            int totalLiterals = 0;
            auto literals = { mi.booleanLiterals, mi.stringLiterals, mi.numberLiterals, mi.regexLiterals };
            for (const auto& litSet : literals) {
                distinctLiterals += litSet.size();
                for (auto const &entry : litSet) {
                    cout << entry.first;
                    totalLiterals += entry.second;
                    if (entry.second > 1) {
                        cout << "(x" << entry.second << ")";
                    }
                    cout << ", ";
                }
            }
            cout << endl << "\t\tTotal number of literals: " << totalLiterals << ", distinct literals: " << distinctLiterals << endl << endl << endl;

            return;
        }

        bool HalsteadVisitor::ignore() {
            if (methodStack.empty()) {
                common::WriteMsg::write(CMSG_EMPTY_METHODSTACK, "ignore()");
                return true;
            }
            auto& mi = methodStack.top();

            // This case covers the methods which are defined inside a class.
            if (dynamic_cast<const javascript::asg::structure::MethodDefinition*>(mi.method) != nullptr) {
                if (classStack.empty()) {
                    return true;
                }
                auto* methodInvocation = dynamic_cast<const javascript::asg::structure::MethodDefinition*>(mi.method);
                auto* parent = methodInvocation->getParent();
                if (parent == nullptr) {
                    return true;
                }
                // If our parent is ClassBody, then get the parent (ClassDeclaration)
                // This is needed as the class stack contains IDs of ClassDeclarations
                if (dynamic_cast<const javascript::asg::structure::ClassBody*>(parent)) {
                    auto* parentClassBody = dynamic_cast<const javascript::asg::structure::ClassBody*>(parent);
                    parent = parentClassBody->getParent();
                }

                if (parent->getId() != classStack.top()) {
                    return true;
                }
            }
            // This case covers the methods which are defined outside a class.
            else if (dynamic_cast<const javascript::asg::statement::Function*>(mi.method) != nullptr) {
                return false;
            } else {
                // This case is impossible.
                throw columbus::Exception(COLUMBUS_LOCATION, "MethodInfo method attribute type is not MethodDefinition or Function.");
            }

            return false;
        }


        void HalsteadVisitor::enterMethod(const javascript::asg::base::Positioned& node) {
            methodStack.push(MethodInfo());
            methodStack.top().method = &node;
        }

        template<typename T> unsigned int sumValues(T map) {
            return std::accumulate(map.begin(), map.end(), 0, [](const unsigned int previous, typename T::value_type p) { return previous + p.second; });
        }

        void HalsteadVisitor::leaveMethod(const javascript::asg::base::Positioned& node) {
            if (ignore()) return;
            MethodInfo& mi = methodStack.top();

            int distinctLiterals = mi.booleanLiterals.size() + mi.numberLiterals.size() + mi.regexLiterals.size() + mi.stringLiterals.size();
            // If we have at least NullLiteral, we add 1 to the distinct literals
            distinctLiterals += (mi.nullLiterals > 0) ? 1 : 0;

            // calculating n - distinct
            // n1
            mi.halsteadInfo.n1 = mi.operatorKinds.size() + mi.operatorNodes.size();

            // n2
            mi.halsteadInfo.n2 = mi.identifiers.size() + mi.properties.size() + mi.labels.size() + distinctLiterals;

            // calculating N - total
            // N1
            mi.halsteadInfo.N1 += sumValues(mi.operatorKinds);
            mi.halsteadInfo.N1 += sumValues(mi.operatorNodes);

            // N2
            mi.halsteadInfo.N2 += sumValues(mi.identifiers);
            mi.halsteadInfo.N2 += sumValues(mi.labels);
            mi.halsteadInfo.N2 += sumValues(mi.properties);

            mi.halsteadInfo.N2 += sumValues(mi.booleanLiterals);
            mi.halsteadInfo.N2 += sumValues(mi.numberLiterals);
            mi.halsteadInfo.N2 += sumValues(mi.regexLiterals);
            mi.halsteadInfo.N2 += sumValues(mi.stringLiterals);
            mi.halsteadInfo.N2 += mi.nullLiterals;

            if (common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDebug) {
                printMethodInfo(mi);
            }

            halsteadInfos[node.getId()] = mi.halsteadInfo;
            //printMethodInfo(mi);
            methodStack.pop();
        }


        /*
         *
         *
         *
         * Class declaration (classStack is used)
         *
         *
         *
         */
        void HalsteadVisitor::visit(const javascript::asg::structure::Class& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Class");

            incOperators(getEnumText(opkClass));
            classStack.push(node.getId());
        }

        void HalsteadVisitor::visitEnd(const javascript::asg::structure::Class& node, bool callVirtualBase) {
            VISIT_END_FIRST(node, "Class");

            // we assume that there will be at least one element in the class stack
            classStack.pop();

            VISIT_END(node, callVirtualBase, "Class");
        }

        /*
        *
        *
        *
        * Method definitions (methodStack is used)
        *
        *
        *
        */
        void HalsteadVisitor::visit(const javascript::asg::structure::MethodDefinition& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "MethodDefinition");
            enterMethod(node);
            incOperators(getEnumText(opkFunctionDeclaration));
        }

        void HalsteadVisitor::visitEnd(const javascript::asg::structure::MethodDefinition& node, bool callVirtualBase) {
            VISIT_END_FIRST(node, "MethodDefinition");
            leaveMethod(node);
            VISIT_END(node, callVirtualBase, "MethodDefinition");
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::Function& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Function");
            if (javascript::asg::Common::getIsFunctionExpression(node) && node.getParent() && javascript::asg::Common::getIsMethodDefinition(*node.getParent())) {
                return;
            }
            enterMethod(node);

            if (node.getParamsSize() > 1) {
                incOperators(getEnumText(opkSeparator), safeDecrement(node.getParamsSize(), 1));
            }
        }

        void HalsteadVisitor::visitEnd(const javascript::asg::statement::Function& node, bool callVirtualBase) {
            VISIT_END_FIRST(node, "Function");
            if (javascript::asg::Common::getIsFunctionExpression(node) && node.getParent() && javascript::asg::Common::getIsMethodDefinition(*node.getParent())) {
                return;
            }
            leaveMethod(node);
            VISIT_END(node, callVirtualBase, "Function");
        }

        void HalsteadVisitor::visit(const javascript::asg::declaration::FunctionDeclaration& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "FunctionDeclaration");
            incOperators(getEnumText(opkFunctionDeclaration));
        }

        void HalsteadVisitor::visitEnd(const javascript::asg::declaration::FunctionDeclaration& node, bool callVirtualBase) {
            VISIT_END(node, callVirtualBase, "FunctionDeclaration");
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::ArrowFunctionExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ArrowFunctionExpression");

            incOperators(getEnumText(opkArrowFunction));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::FunctionExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "FunctionExpression");

            if (node.getParent() && javascript::asg::Common::getIsMethodDefinition(*node.getParent())) {
                return;
            }
            incOperators(getEnumText(opkFunctionDeclaration));
        }


        /*
        *
        *
        *
        * Statements
        *
        *
        *
        */
        void HalsteadVisitor::visit(const javascript::asg::statement::ContinueStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Continue");
            incOperators(getEnumText(opkContinue));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::DebuggerStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Debugger");
            incOperators(getEnumText(opkDebugger));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::ForStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "For");
            incOperators(getEnumText(opkFor));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::WhileStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "While");
            if (javascript::asg::Common::getIsDoWhileStatement(node)) {
                incOperators(getEnumText(opkDoWhile));
                return;
            }
            incOperators(getEnumText(opkWhile));

        }

        void HalsteadVisitor::visit(const javascript::asg::statement::IfStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "If");
            incOperators(getEnumText(opkIf));

            // if the statement has else case
            if (node.getAlternate() != nullptr) {
                incOperators(getEnumText(opkElse));
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::BreakStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Break");
            incOperators(getEnumText(opkBreak));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::ThrowStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Throw");
            incOperators(getEnumText(opkThrow));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::LabeledStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "LabeledStatement");
            incOperands(node);
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::EmptyStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "EmptyStatement");
            incOperators(getEnumText(opkEmptyStatement));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::TryStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "TryStatement");
            incOperators(getEnumText(opkTry));

            // if the statement has finally block
            if (node.getFinalizer() != nullptr) {
                incOperators(getEnumText(opkFinally));
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::ReturnStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ReturnStatement");
            incOperators(getEnumText(opkReturn));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::BlockStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "BlockStatement");
            auto* parent = node.getParent();

            // According to MDN: function, try need opening and closing brackets (they are part of the syntax)
            // So, we should not count them there.
            if (parent != nullptr && !(javascript::asg::Common::getIsFunction(*parent)
                || javascript::asg::Common::getIsMethodDefinition(*parent)
                || javascript::asg::Common::getIsTryStatement(*parent)
                || javascript::asg::Common::getIsCatchClause(*parent)
                )) {
                incOperators(getEnumText(opkBlockStatement));
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::SwitchStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "SwitchStatement");
            incOperators(getEnumText(opkSwitch));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::CatchClause& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "CatchClause");
            incOperators(getEnumText(opkCatch));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::SwitchCase& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "SwitchCase");
            incOperators(getEnumText(opkCase));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::ForInStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ForInStatement");

            if (javascript::asg::Common::getIsForOfStatement(node)) {
                incOperators(getEnumText(opkForOfStatement));
                return;
            }
            incOperators(getEnumText(opkForInStatement));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::WithStatement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "WithStatement");

            incOperators(getEnumText(opkWithStatement));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::ArrayPattern& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ArrayPattern");

            incOperators(getEnumText(opkArrayPattern));

            if (node.getElementsSize() > 1) {
                incOperators(getEnumText(opkSeparator), safeDecrement(node.getElementsSize(), 1));
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::RestElement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "RestElement");
            // Do nothing here, operand is handled at its identifier
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::ObjectPattern& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ObjectPattern");
            incOperators(getEnumText(opkObjectPattern));
        }

        void HalsteadVisitor::visit(const javascript::asg::statement::AssignmentPattern& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "AssignmentPattern");
            incOperators(getEnumText(opkAssignmentPattern));
        }

        /*
        *
        *
        *
        * Structure
        *
        *
        *
        */
        void HalsteadVisitor::visit(const javascript::asg::structure::ClassBody& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ClassBody");
            incOperators(getEnumText(opkClassBody));
        }

        void HalsteadVisitor::visit(const javascript::asg::structure::ExportSpecifier& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ExportSpecifier");
            incOperators(getEnumText(opkExportSpecifier));
        }

        void HalsteadVisitor::visit(const javascript::asg::structure::ImpSpecifier& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ImpSpecifier");
            if (javascript::asg::Common::getIsImportDefaultSpecifier(node)) {
                incOperators(getEnumText(opkImportDefaultSpecifier));
            } else if (javascript::asg::Common::getIsImportNamespaceSpecifier(node)) {
                incOperators(getEnumText(opkImportNamespaceSpecifier));
            } else if (javascript::asg::Common::getIsImportSpecifier(node)) {
                incOperators(getEnumText(opkImportSpecifier));
            } else {
                incOperators(getEnumText(opkImpSpecifier));
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::structure::ModuleSpecifier& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ModuleSpecifier");
            incOperators(getEnumText(opkModuleSpecifier));
        }

        /*
        *
        *
        *
        * Expression
        *
        *
        *
        */
        void HalsteadVisitor::visit(const javascript::asg::expression::ThisExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "This");
            incOperators(getEnumText(opkThis));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::Identifier& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Identifier");

            auto* parent = node.getParent();

            // Properties are handled in Property visitor
            // in tagged templates, the tag name (identifier) should be considered as operator, not operand
            if (parent != nullptr && (javascript::asg::Common::getIsProperty(*parent) || javascript::asg::Common::getIsTaggedTemplateExpression(*parent))) {
                return;
            }
            incOperands(node);
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::NullLiteral& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "NullLiteral");
            incLiteral(node.getNodeKind(), "");
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::StringLiteral& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "StringLiteral");
            incLiteral(node.getNodeKind(), node.getValue());
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::BooleanLiteral& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "BooleanLiteral");
            // for readability purposes, we use strings
            incLiteral(node.getNodeKind(), (node.getValue() ? "true" : "false"));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::NumberLiteral& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "NumberLiteral");
            incLiteral(node.getNodeKind(), std::to_string(node.getValue()));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::RegExpLiteral& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "NumberLiteral");
            incLiteral(node.getNodeKind(), node.getRaw());
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::ArrayExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ArrayExpression");
            incOperators(getEnumText(opkArray));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::AwaitExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "AwaitExpression");
            incOperators(getEnumText(opkAwait));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::BinaryExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "BinaryExpression");
            incOperators(getEnumText(node.getOperator()));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::NewExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "NewExpression");
            incOperators(getEnumText(opkNewExpression));
            // Count separators
            incOperators(getEnumText(opkSeparator), safeDecrement(node.getArgumentsSize(), 1));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::SequenceExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "SequenceExpression");
            // Count separators
            incOperators(getEnumText(opkSeparator), safeDecrement(node.getExpressionsSize(), 1));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::YieldExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "YieldExpression");
            incOperators(getEnumText(opkYieldExpression));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::ConditionalExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ConditionalExpression");
            incOperators(getEnumText(opkConditionalExpression));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::AssignmentExpression& node, bool callVirtualBase) {
            // This is not a binary expression
            VISIT_BEGIN(node, callVirtualBase, "AssignmentExpression");
            incOperators(getEnumText(node.getOperator()));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::MetaProperty& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "MetaProperty");
            incOperators(getEnumText(opkMetaProperty));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::LogicalExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "LogicalExpression");
            incOperators(getEnumText(node.getOperator()));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::MemberExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "MemberExpression");
            incOperators(getEnumText(opkMemberExpression));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::UnaryExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "UnaryExpression");
            incOperators(getEnumText(node.getOperator()));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::CallExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "CallExpression");
            incOperators(getEnumText(opkCallExpression));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::TaggedTemplateExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "TaggedTemplateExpression");
            // should be always true
            if (node.getTag() != nullptr && javascript::asg::Common::getIsIdentifier(*node.getTag())) {
                const auto* identifier = dynamic_cast<const javascript::asg::expression::Identifier*>(node.getTag());
                incOperators(identifier->getName());
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::Property& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Property");
            incOperands(node);

            // Properties can be used in object patterns the following way:
            // var {op, lhs, rhs} = getASTNode();
            // In this particular case, the property's key and value are the same.
            // We should count them once.
            // This case is handled here.
            if (node.getKey() != nullptr && node.getKey() == node.getValue()) {
                incOperands(*node.getKey());
                return;
            }

            // If the property's key and value are different
            if (node.getKey() != nullptr && javascript::asg::Common::getIsIdentifier(*node.getKey())) {
                incOperands(*node.getKey());
            }
            if (node.getValue() != nullptr && javascript::asg::Common::getIsIdentifier(*node.getValue())) {
                incOperands(*node.getValue());
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::Super& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "Super");
            incOperators(getEnumText(opkSuper));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::ObjectExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ObjectExpression");
            incOperators(getEnumText(opkObjectExpression));
            // Count separators
            if (node.getPropertiesSize() > 1) {
                incOperators(getEnumText(opkSeparator), safeDecrement(node.getPropertiesSize(), 1));
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::UpdateExpression& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "UpdateExpression");
            incOperators(getEnumText(node.getOperator()));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::TemplateElement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "TemplateElement");

            // If the expression is at the end of the literal, there will be an empty element.
            if (node.getValue() == "") {
                return;
            }
            incLiteral(node.getNodeKind(), node.getValue());
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::SpreadElement& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "SpreadElement");
            incOperators(getEnumText(opkSpreadElement));
        }

        void HalsteadVisitor::visit(const javascript::asg::expression::TemplateLiteral& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "TemplateLiteral");
            if (node.getExpressionsSize() > 0) {
                incOperators(getEnumText(opkTemplateElement), node.getExpressionsSize());
            }
        }

        /*
        *
        *
        *
        * Declaration
        *
        *
        *
        */
        void HalsteadVisitor::visit(const javascript::asg::declaration::ExportAllDeclaration& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ExportAllDeclaration");
            incOperators(getEnumText(opkExportAllDeclaration));
        }

        void HalsteadVisitor::visit(const javascript::asg::declaration::ExportDefaultDeclaration& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ExportDefaultDeclaration");
            incOperators(getEnumText(opkExportDefaultDeclaration));
        }

        void HalsteadVisitor::visit(const javascript::asg::declaration::ExportNamedDeclaration& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ExportNamedDeclaration");
            incOperators(getEnumText(opkExportNamedDeclaration));
        }

        void HalsteadVisitor::visit(const javascript::asg::declaration::VariableDeclaration& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "VariableDeclaration");
            incOperators(getEnumText(node.getKind()));
            // Count separators
            if (node.getDeclarationsSize() > 1) {
                incOperators(getEnumText(opkSeparator), safeDecrement(node.getDeclarationsSize(), 1));
            }
        }

        void HalsteadVisitor::visit(const javascript::asg::declaration::ImportDeclaration& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ImportDeclaration");
            incOperators(getEnumText(opkImportDeclaration));
        }

        void HalsteadVisitor::visit(const javascript::asg::declaration::ModuleDeclaration& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "ModuleDeclaration");
            incOperators(getEnumText(opkModuleDeclaration));
        }

        void HalsteadVisitor::visit(const javascript::asg::declaration::VariableDeclarator& node, bool callVirtualBase) {
            VISIT_BEGIN(node, callVirtualBase, "VariableDeclarator");
            incOperands(node);

            if (node.getInit() != nullptr) {
                incOperators(getEnumText(opkVariableInitializer));
            }
        }
    }
}
