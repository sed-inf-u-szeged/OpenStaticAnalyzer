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

#ifndef _JAVASCRIPT_VISITORGRAPHML_H_
#define _JAVASCRIPT_VISITORGRAPHML_H_

#include "javascript/inc/javascript.h"
#include "io/inc/GraphmlIO.h"

/**
* \file VisitorGraphml.h
* \brief Contains declaration of VisitorGraphml class.
*/

namespace columbus { namespace javascript { namespace asg {

  /**
  * \brief Exports the ASG to Graphml format.
  */
  class VisitorGraphml : public Visitor {
    public:
      typedef bool(*NodeCompareFunc)(const base::Base&);

      /**
      * \brief Constructor for VisitorGraphml.
      */
      VisitorGraphml(columbus::io::GraphmlIO& io, std::set< std::string>& edgeFilter, unsigned int maxDrawingDepth = 0);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorGraphml();

      /**
      * \brief Give back to compare function
      */
      NodeCompareFunc getCompareFunctionToNode( std::string& nodeName);

      /**
      * \brief Create compare map
      */
      static std::map< std::string, NodeCompareFunc> create_map(){
        std::map< std::string, NodeCompareFunc> cmpTable;
        cmpTable.insert( std::make_pair( "Comment", &Common::getIsComment));
        cmpTable.insert( std::make_pair( "Named", &Common::getIsNamed));
        cmpTable.insert( std::make_pair( "Positioned", &Common::getIsPositioned));
        cmpTable.insert( std::make_pair( "Program", &Common::getIsProgram));
        cmpTable.insert( std::make_pair( "System", &Common::getIsSystem));
        cmpTable.insert( std::make_pair( "ClassDeclaration", &Common::getIsClassDeclaration));
        cmpTable.insert( std::make_pair( "Declaration", &Common::getIsDeclaration));
        cmpTable.insert( std::make_pair( "ExportAllDeclaration", &Common::getIsExportAllDeclaration));
        cmpTable.insert( std::make_pair( "ExportDefaultDeclaration", &Common::getIsExportDefaultDeclaration));
        cmpTable.insert( std::make_pair( "ExportNamedDeclaration", &Common::getIsExportNamedDeclaration));
        cmpTable.insert( std::make_pair( "FunctionDeclaration", &Common::getIsFunctionDeclaration));
        cmpTable.insert( std::make_pair( "ImportDeclaration", &Common::getIsImportDeclaration));
        cmpTable.insert( std::make_pair( "ModuleDeclaration", &Common::getIsModuleDeclaration));
        cmpTable.insert( std::make_pair( "VariableDeclaration", &Common::getIsVariableDeclaration));
        cmpTable.insert( std::make_pair( "VariableDeclarator", &Common::getIsVariableDeclarator));
        cmpTable.insert( std::make_pair( "ArrayExpression", &Common::getIsArrayExpression));
        cmpTable.insert( std::make_pair( "ArrowFunctionExpression", &Common::getIsArrowFunctionExpression));
        cmpTable.insert( std::make_pair( "AssignmentExpression", &Common::getIsAssignmentExpression));
        cmpTable.insert( std::make_pair( "AssignmentProperty", &Common::getIsAssignmentProperty));
        cmpTable.insert( std::make_pair( "AwaitExpression", &Common::getIsAwaitExpression));
        cmpTable.insert( std::make_pair( "BinaryExpression", &Common::getIsBinaryExpression));
        cmpTable.insert( std::make_pair( "BooleanLiteral", &Common::getIsBooleanLiteral));
        cmpTable.insert( std::make_pair( "CallExpression", &Common::getIsCallExpression));
        cmpTable.insert( std::make_pair( "ClassExpression", &Common::getIsClassExpression));
        cmpTable.insert( std::make_pair( "ConditionalExpression", &Common::getIsConditionalExpression));
        cmpTable.insert( std::make_pair( "Expression", &Common::getIsExpression));
        cmpTable.insert( std::make_pair( "FunctionExpression", &Common::getIsFunctionExpression));
        cmpTable.insert( std::make_pair( "Identifier", &Common::getIsIdentifier));
        cmpTable.insert( std::make_pair( "Literal", &Common::getIsLiteral));
        cmpTable.insert( std::make_pair( "LogicalExpression", &Common::getIsLogicalExpression));
        cmpTable.insert( std::make_pair( "MemberExpression", &Common::getIsMemberExpression));
        cmpTable.insert( std::make_pair( "MetaProperty", &Common::getIsMetaProperty));
        cmpTable.insert( std::make_pair( "NewExpression", &Common::getIsNewExpression));
        cmpTable.insert( std::make_pair( "NullLiteral", &Common::getIsNullLiteral));
        cmpTable.insert( std::make_pair( "NumberLiteral", &Common::getIsNumberLiteral));
        cmpTable.insert( std::make_pair( "ObjectExpression", &Common::getIsObjectExpression));
        cmpTable.insert( std::make_pair( "Property", &Common::getIsProperty));
        cmpTable.insert( std::make_pair( "RegExpLiteral", &Common::getIsRegExpLiteral));
        cmpTable.insert( std::make_pair( "SequenceExpression", &Common::getIsSequenceExpression));
        cmpTable.insert( std::make_pair( "SpreadElement", &Common::getIsSpreadElement));
        cmpTable.insert( std::make_pair( "StringLiteral", &Common::getIsStringLiteral));
        cmpTable.insert( std::make_pair( "Super", &Common::getIsSuper));
        cmpTable.insert( std::make_pair( "TaggedTemplateExpression", &Common::getIsTaggedTemplateExpression));
        cmpTable.insert( std::make_pair( "TemplateElement", &Common::getIsTemplateElement));
        cmpTable.insert( std::make_pair( "TemplateLiteral", &Common::getIsTemplateLiteral));
        cmpTable.insert( std::make_pair( "ThisExpression", &Common::getIsThisExpression));
        cmpTable.insert( std::make_pair( "UnaryExpression", &Common::getIsUnaryExpression));
        cmpTable.insert( std::make_pair( "UpdateExpression", &Common::getIsUpdateExpression));
        cmpTable.insert( std::make_pair( "YieldExpression", &Common::getIsYieldExpression));
        cmpTable.insert( std::make_pair( "ArrayPattern", &Common::getIsArrayPattern));
        cmpTable.insert( std::make_pair( "AssignmentPattern", &Common::getIsAssignmentPattern));
        cmpTable.insert( std::make_pair( "BlockStatement", &Common::getIsBlockStatement));
        cmpTable.insert( std::make_pair( "BreakStatement", &Common::getIsBreakStatement));
        cmpTable.insert( std::make_pair( "CatchClause", &Common::getIsCatchClause));
        cmpTable.insert( std::make_pair( "ContinueStatement", &Common::getIsContinueStatement));
        cmpTable.insert( std::make_pair( "DebuggerStatement", &Common::getIsDebuggerStatement));
        cmpTable.insert( std::make_pair( "DoWhileStatement", &Common::getIsDoWhileStatement));
        cmpTable.insert( std::make_pair( "EmptyStatement", &Common::getIsEmptyStatement));
        cmpTable.insert( std::make_pair( "ExpressionStatement", &Common::getIsExpressionStatement));
        cmpTable.insert( std::make_pair( "ForInStatement", &Common::getIsForInStatement));
        cmpTable.insert( std::make_pair( "ForOfStatement", &Common::getIsForOfStatement));
        cmpTable.insert( std::make_pair( "ForStatement", &Common::getIsForStatement));
        cmpTable.insert( std::make_pair( "Function", &Common::getIsFunction));
        cmpTable.insert( std::make_pair( "IfStatement", &Common::getIsIfStatement));
        cmpTable.insert( std::make_pair( "LabeledStatement", &Common::getIsLabeledStatement));
        cmpTable.insert( std::make_pair( "ObjectPattern", &Common::getIsObjectPattern));
        cmpTable.insert( std::make_pair( "Pattern", &Common::getIsPattern));
        cmpTable.insert( std::make_pair( "RestElement", &Common::getIsRestElement));
        cmpTable.insert( std::make_pair( "ReturnStatement", &Common::getIsReturnStatement));
        cmpTable.insert( std::make_pair( "Statement", &Common::getIsStatement));
        cmpTable.insert( std::make_pair( "SwitchCase", &Common::getIsSwitchCase));
        cmpTable.insert( std::make_pair( "SwitchStatement", &Common::getIsSwitchStatement));
        cmpTable.insert( std::make_pair( "ThrowStatement", &Common::getIsThrowStatement));
        cmpTable.insert( std::make_pair( "TryStatement", &Common::getIsTryStatement));
        cmpTable.insert( std::make_pair( "WhileStatement", &Common::getIsWhileStatement));
        cmpTable.insert( std::make_pair( "WithStatement", &Common::getIsWithStatement));
        cmpTable.insert( std::make_pair( "Class", &Common::getIsClass));
        cmpTable.insert( std::make_pair( "ClassBody", &Common::getIsClassBody));
        cmpTable.insert( std::make_pair( "ExportSpecifier", &Common::getIsExportSpecifier));
        cmpTable.insert( std::make_pair( "ImpSpecifier", &Common::getIsImpSpecifier));
        cmpTable.insert( std::make_pair( "ImportDefaultSpecifier", &Common::getIsImportDefaultSpecifier));
        cmpTable.insert( std::make_pair( "ImportNamespaceSpecifier", &Common::getIsImportNamespaceSpecifier));
        cmpTable.insert( std::make_pair( "ImportSpecifier", &Common::getIsImportSpecifier));
        cmpTable.insert( std::make_pair( "MethodDefinition", &Common::getIsMethodDefinition));
        cmpTable.insert( std::make_pair( "ModuleSpecifier", &Common::getIsModuleSpecifier));
        return cmpTable;
      }

      /**
      * \brief Filter node types by matching substring in qualified name
      */
      static const std::set< std::string> getNodeTypeSet(){
        std::set< std::string> types;
        types.insert( "base::Base");
        types.insert( "base::Comment");
        types.insert( "base::Named");
        types.insert( "base::Positioned");
        types.insert( "base::Program");
        types.insert( "base::System");
        types.insert( "declaration::ClassDeclaration");
        types.insert( "declaration::Declaration");
        types.insert( "declaration::ExportAllDeclaration");
        types.insert( "declaration::ExportDefaultDeclaration");
        types.insert( "declaration::ExportNamedDeclaration");
        types.insert( "declaration::FunctionDeclaration");
        types.insert( "declaration::ImportDeclaration");
        types.insert( "declaration::ModuleDeclaration");
        types.insert( "declaration::VariableDeclaration");
        types.insert( "declaration::VariableDeclarator");
        types.insert( "expression::ArrayExpression");
        types.insert( "expression::ArrowFunctionExpression");
        types.insert( "expression::AssignmentExpression");
        types.insert( "expression::AssignmentProperty");
        types.insert( "expression::AwaitExpression");
        types.insert( "expression::BinaryExpression");
        types.insert( "expression::BooleanLiteral");
        types.insert( "expression::CallExpression");
        types.insert( "expression::ClassExpression");
        types.insert( "expression::ConditionalExpression");
        types.insert( "expression::Expression");
        types.insert( "expression::FunctionExpression");
        types.insert( "expression::Identifier");
        types.insert( "expression::Literal");
        types.insert( "expression::LogicalExpression");
        types.insert( "expression::MemberExpression");
        types.insert( "expression::MetaProperty");
        types.insert( "expression::NewExpression");
        types.insert( "expression::NullLiteral");
        types.insert( "expression::NumberLiteral");
        types.insert( "expression::ObjectExpression");
        types.insert( "expression::Property");
        types.insert( "expression::RegExpLiteral");
        types.insert( "expression::SequenceExpression");
        types.insert( "expression::SpreadElement");
        types.insert( "expression::StringLiteral");
        types.insert( "expression::Super");
        types.insert( "expression::TaggedTemplateExpression");
        types.insert( "expression::TemplateElement");
        types.insert( "expression::TemplateLiteral");
        types.insert( "expression::ThisExpression");
        types.insert( "expression::UnaryExpression");
        types.insert( "expression::UpdateExpression");
        types.insert( "expression::YieldExpression");
        types.insert( "statement::ArrayPattern");
        types.insert( "statement::AssignmentPattern");
        types.insert( "statement::BlockStatement");
        types.insert( "statement::BreakStatement");
        types.insert( "statement::CatchClause");
        types.insert( "statement::ContinueStatement");
        types.insert( "statement::DebuggerStatement");
        types.insert( "statement::DoWhileStatement");
        types.insert( "statement::EmptyStatement");
        types.insert( "statement::ExpressionStatement");
        types.insert( "statement::ForInStatement");
        types.insert( "statement::ForOfStatement");
        types.insert( "statement::ForStatement");
        types.insert( "statement::Function");
        types.insert( "statement::IfStatement");
        types.insert( "statement::LabeledStatement");
        types.insert( "statement::ObjectPattern");
        types.insert( "statement::Pattern");
        types.insert( "statement::RestElement");
        types.insert( "statement::ReturnStatement");
        types.insert( "statement::Statement");
        types.insert( "statement::SwitchCase");
        types.insert( "statement::SwitchStatement");
        types.insert( "statement::ThrowStatement");
        types.insert( "statement::TryStatement");
        types.insert( "statement::WhileStatement");
        types.insert( "statement::WithStatement");
        types.insert( "structure::Class");
        types.insert( "structure::ClassBody");
        types.insert( "structure::ExportSpecifier");
        types.insert( "structure::ImpSpecifier");
        types.insert( "structure::ImportDefaultSpecifier");
        types.insert( "structure::ImportNamespaceSpecifier");
        types.insert( "structure::ImportSpecifier");
        types.insert( "structure::MethodDefinition");
        types.insert( "structure::ModuleSpecifier");
        return types;
      }

      /** \internal \brief It contains a table to node names and compare functions */
      static const std::map< std::string, NodeCompareFunc> compareTable;

      /**
      * \brief Set startpoint
      */
      void setStartPoint( NodeId startPoint);

      /**
      * \brief Set it is white color node or not
      */
      void setIsWhiteColor( bool isWhite);

      /**
      * \brief Set it is need to grouping tree nodes or not
      */
      void setIsGroupingTreeNodes( bool groupingTreeNodes);

      /**
      * \brief Set it is enabled to draw cross edges or not
      */
      void setIsEnableCrossEdge( bool isVisitCrossEdge);

      /**
      * \brief Set node type names to show attributes only of these types 
      */
      void addToFilterNodeTypeAttributes( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void addToFilterNodeType( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void filterNodeTypeMatch( std::string pattern);

      /**
      * \brief Writes the Graphml representation of the base::Comment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Converts the base::Comment node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the base::Program node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Program& node, bool callVirtualBase = true);

      /**
      * \brief Converts the base::Program node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Program& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the base::System node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::System& node, bool callVirtualBase = true);

      /**
      * \brief Converts the base::System node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::System& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::ClassDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ClassDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::ClassDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ClassDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::ExportAllDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportAllDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::ExportAllDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportAllDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::ExportDefaultDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportDefaultDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::ExportDefaultDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportDefaultDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::ExportNamedDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ExportNamedDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::ExportNamedDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ExportNamedDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::FunctionDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::FunctionDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::FunctionDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::FunctionDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::ImportDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ImportDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::ImportDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ImportDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::ModuleDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::ModuleDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::ModuleDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::ModuleDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::VariableDeclaration node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::VariableDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::VariableDeclaration node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::VariableDeclaration& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the declaration::VariableDeclarator node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const declaration::VariableDeclarator& node, bool callVirtualBase = true);

      /**
      * \brief Converts the declaration::VariableDeclarator node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const declaration::VariableDeclarator& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ArrayExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ArrayExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ArrowFunctionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrowFunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ArrowFunctionExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrowFunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::AssignmentExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AssignmentExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AssignmentExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AssignmentExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::AssignmentProperty node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AssignmentProperty& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AssignmentProperty node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AssignmentProperty& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::AwaitExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AwaitExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AwaitExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AwaitExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::BinaryExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::BinaryExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::BooleanLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BooleanLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::BooleanLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BooleanLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::CallExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CallExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::CallExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CallExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ClassExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ClassExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ClassExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ClassExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ConditionalExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ConditionalExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::FunctionExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::FunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::FunctionExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::FunctionExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::Identifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Identifier& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::Identifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Identifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::LogicalExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::LogicalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::LogicalExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LogicalExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::MemberExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::MemberExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::MetaProperty node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MetaProperty& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::MetaProperty node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MetaProperty& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::NewExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NewExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::NewExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NewExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::NullLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NullLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::NullLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NullLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::NumberLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NumberLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::NumberLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NumberLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ObjectExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ObjectExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ObjectExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ObjectExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::Property node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Property& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::Property node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Property& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::RegExpLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RegExpLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::RegExpLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RegExpLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::SequenceExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SequenceExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::SequenceExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SequenceExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::SpreadElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SpreadElement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::SpreadElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SpreadElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::StringLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StringLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::StringLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StringLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::Super node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::Super& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::Super node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::Super& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::TaggedTemplateExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TaggedTemplateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::TaggedTemplateExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TaggedTemplateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::TemplateElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TemplateElement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::TemplateElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TemplateElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::TemplateLiteral node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TemplateLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::TemplateLiteral node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TemplateLiteral& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ThisExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ThisExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ThisExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ThisExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::UnaryExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::UnaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::UnaryExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UnaryExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::UpdateExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::UpdateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::UpdateExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::UpdateExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::YieldExpression node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::YieldExpression& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::YieldExpression node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::YieldExpression& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ArrayPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ArrayPattern& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ArrayPattern node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ArrayPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::AssignmentPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::AssignmentPattern& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::AssignmentPattern node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::AssignmentPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::BlockStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BlockStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::BlockStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BlockStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::BreakStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BreakStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::BreakStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BreakStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::CatchClause node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::CatchClause& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::CatchClause node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::CatchClause& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ContinueStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ContinueStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ContinueStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ContinueStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::DebuggerStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DebuggerStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::DebuggerStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DebuggerStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::DoWhileStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DoWhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::DoWhileStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DoWhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::EmptyStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::EmptyStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::EmptyStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::EmptyStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ExpressionStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ExpressionStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ExpressionStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ExpressionStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ForInStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForInStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ForInStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForInStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ForOfStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForOfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ForOfStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForOfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ForStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ForStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::Function node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::Function& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::Function node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::Function& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::IfStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::IfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::IfStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::IfStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::LabeledStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LabeledStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::LabeledStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LabeledStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ObjectPattern node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ObjectPattern& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ObjectPattern node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ObjectPattern& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::RestElement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::RestElement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::RestElement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::RestElement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ReturnStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ReturnStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ReturnStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ReturnStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::SwitchCase node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchCase& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::SwitchCase node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchCase& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::SwitchStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::SwitchStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ThrowStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ThrowStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ThrowStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ThrowStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::TryStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::TryStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::WhileStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::WhileStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WhileStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::WithStatement node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WithStatement& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::WithStatement node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WithStatement& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ClassBody node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassBody& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ClassBody node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassBody& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ExportSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ExportSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ImportDefaultSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportDefaultSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ImportDefaultSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportDefaultSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ImportNamespaceSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportNamespaceSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ImportNamespaceSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportNamespaceSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ImportSpecifier node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ImportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ImportSpecifier node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ImportSpecifier& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::MethodDefinition node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::MethodDefinition& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::MethodDefinition node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::MethodDefinition& node, bool callVirtualBase = true);

      /**
      * \brief Edge visitor for comments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPositioned_Comments(const base::Positioned& begin, const base::Comment& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProgram_HasBody(const base::Program& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasPrograms edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSystem_HasPrograms(const base::System& begin, const base::Program& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportAllDeclaration_HasSource(const declaration::ExportAllDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportDefaultDeclaration_HasDeclaration(const declaration::ExportDefaultDeclaration& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasDeclaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasDeclaration(const declaration::ExportNamedDeclaration& begin, const declaration::Declaration& end);

      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasSpecifiers(const declaration::ExportNamedDeclaration& begin, const structure::ExportSpecifier& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportNamedDeclaration_HasSource(const declaration::ExportNamedDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportDeclaration_HasSpecifiers(const declaration::ImportDeclaration& begin, const structure::ImpSpecifier& end);

      /**
      * \brief Edge  visitor for hasSource edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportDeclaration_HasSource(const declaration::ImportDeclaration& begin, const expression::Literal& end);

      /**
      * \brief Edge  visitor for hasDeclarations edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaration_HasDeclarations(const declaration::VariableDeclaration& begin, const declaration::VariableDeclarator& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarator_HasIdentifier(const declaration::VariableDeclarator& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarator_HasInit(const declaration::VariableDeclarator& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayExpression_HasElements(const expression::ArrayExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpression_HasLeft(const expression::AssignmentExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpression_HasRight(const expression::AssignmentExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAwaitExpression_HasArgument(const expression::AwaitExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpression_HasLeft(const expression::BinaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpression_HasRight(const expression::BinaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_HasCallee(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCallExpression_HasArguments(const expression::CallExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasAlternate(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasConsequent(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpression_HasTest(const expression::ConditionalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifier_RefersTo(const expression::Identifier& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLogicalExpression_HasLeft(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLogicalExpression_HasRight(const expression::LogicalExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberExpression_HasProperty(const expression::MemberExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberExpression_HasObject(const expression::MemberExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasMeta edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMetaProperty_HasMeta(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasProperty edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMetaProperty_HasProperty(const expression::MetaProperty& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasCallee edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_HasCallee(const expression::NewExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNewExpression_HasArguments(const expression::NewExpression& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectExpression_HasProperties(const expression::ObjectExpression& begin, const expression::Property& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProperty_HasValue(const expression::Property& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitProperty_HasKey(const expression::Property& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSequenceExpression_HasExpressions(const expression::SequenceExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSpreadElement_HasArgument(const expression::SpreadElement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTaggedTemplateExpression_HasTag(const expression::TaggedTemplateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasQuasi edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTaggedTemplateExpression_HasQuasi(const expression::TaggedTemplateExpression& begin, const expression::TemplateLiteral& end);

      /**
      * \brief Edge  visitor for hasQuasis edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTemplateLiteral_HasQuasis(const expression::TemplateLiteral& begin, const expression::TemplateElement& end);

      /**
      * \brief Edge  visitor for hasExpressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTemplateLiteral_HasExpressions(const expression::TemplateLiteral& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnaryExpression_HasArgument(const expression::UnaryExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUpdateExpression_HasArgument(const expression::UpdateExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldExpression_HasArgument(const expression::YieldExpression& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasElements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayPattern_HasElements(const statement::ArrayPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentPattern_HasLeft(const statement::AssignmentPattern& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentPattern_HasRight(const statement::AssignmentPattern& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlockStatement_HasBody(const statement::BlockStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBreakStatement_HasLabel(const statement::BreakStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasParam edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClause_HasParam(const statement::CatchClause& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClause_HasBody(const statement::CatchClause& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitContinueStatement_HasLabel(const statement::ContinueStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatement_HasExpression(const statement::ExpressionStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasRight edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasRight(const statement::ForInStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasBody(const statement::ForInStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLeft edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForInStatement_HasLeft(const statement::ForInStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasBody(const statement::ForStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasTest(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasUpdate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasUpdate(const statement::ForStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasInit edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatement_HasInit(const statement::ForStatement& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasParams edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasParams(const statement::Function& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasBody(const statement::Function& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFunction_HasIdentifier(const statement::Function& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasTest(const statement::IfStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasConsequent(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasAlternate edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatement_HasAlternate(const statement::IfStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasLabel edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasLabel(const statement::LabeledStatement& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatement_HasBody(const statement::LabeledStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasProperties edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectPattern_HasProperties(const statement::ObjectPattern& begin, const expression::Property& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRestElement_HasArgument(const statement::RestElement& begin, const statement::Pattern& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturnStatement_HasArgument(const statement::ReturnStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchCase_HasTest(const statement::SwitchCase& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasConsequent edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchCase_HasConsequent(const statement::SwitchCase& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasDiscriminant edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_HasDiscriminant(const statement::SwitchStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasCases edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatement_HasCases(const statement::SwitchStatement& begin, const statement::SwitchCase& end);

      /**
      * \brief Edge  visitor for hasArgument edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrowStatement_HasArgument(const statement::ThrowStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasBlock(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasFinalizer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasFinalizer(const statement::TryStatement& begin, const statement::BlockStatement& end);

      /**
      * \brief Edge  visitor for hasHandler edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatement_HasHandler(const statement::TryStatement& begin, const statement::CatchClause& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatement_HasBody(const statement::WhileStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasTest edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatement_HasTest(const statement::WhileStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasObject edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWithStatement_HasObject(const statement::WithStatement& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWithStatement_HasBody(const statement::WithStatement& begin, const statement::Statement& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasBody(const structure::Class& begin, const structure::ClassBody& end);

      /**
      * \brief Edge  visitor for hasSuperClass edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasSuperClass(const structure::Class& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasIdentifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_HasIdentifier(const structure::Class& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassBody_HasBody(const structure::ClassBody& begin, const structure::MethodDefinition& end);

      /**
      * \brief Edge  visitor for hasExported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExportSpecifier_HasExported(const structure::ExportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasImported edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImportSpecifier_HasImported(const structure::ImportSpecifier& begin, const expression::Identifier& end);

      /**
      * \brief Edge  visitor for hasKey edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDefinition_HasKey(const structure::MethodDefinition& begin, const expression::Expression& end);

      /**
      * \brief Edge  visitor for hasValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDefinition_HasValue(const structure::MethodDefinition& begin, const expression::FunctionExpression& end);

      /**
      * \brief Edge  visitor for hasLocal edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitModuleSpecifier_HasLocal(const structure::ModuleSpecifier& begin, const expression::Identifier& end);

    protected:

      /**
      * \internal
      * \brief Converts the attributes of the base::Base node.
      */
      void addAttributeToContent(const base::Base& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Comment node.
      */
      void addAttributeToContent(const base::Comment& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Named node.
      */
      void addAttributeToContent(const base::Named& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Positioned node.
      */
      void addAttributeToContent(const base::Positioned& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Program node.
      */
      void addAttributeToContent(const base::Program& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::System node.
      */
      void addAttributeToContent(const base::System& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::ClassDeclaration node.
      */
      void addAttributeToContent(const declaration::ClassDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::Declaration node.
      */
      void addAttributeToContent(const declaration::Declaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::ExportAllDeclaration node.
      */
      void addAttributeToContent(const declaration::ExportAllDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::ExportDefaultDeclaration node.
      */
      void addAttributeToContent(const declaration::ExportDefaultDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::ExportNamedDeclaration node.
      */
      void addAttributeToContent(const declaration::ExportNamedDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::FunctionDeclaration node.
      */
      void addAttributeToContent(const declaration::FunctionDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::ImportDeclaration node.
      */
      void addAttributeToContent(const declaration::ImportDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::ModuleDeclaration node.
      */
      void addAttributeToContent(const declaration::ModuleDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::VariableDeclaration node.
      */
      void addAttributeToContent(const declaration::VariableDeclaration& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the declaration::VariableDeclarator node.
      */
      void addAttributeToContent(const declaration::VariableDeclarator& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ArrayExpression node.
      */
      void addAttributeToContent(const expression::ArrayExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ArrowFunctionExpression node.
      */
      void addAttributeToContent(const expression::ArrowFunctionExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AssignmentExpression node.
      */
      void addAttributeToContent(const expression::AssignmentExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AssignmentProperty node.
      */
      void addAttributeToContent(const expression::AssignmentProperty& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AwaitExpression node.
      */
      void addAttributeToContent(const expression::AwaitExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::BinaryExpression node.
      */
      void addAttributeToContent(const expression::BinaryExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::BooleanLiteral node.
      */
      void addAttributeToContent(const expression::BooleanLiteral& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::CallExpression node.
      */
      void addAttributeToContent(const expression::CallExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ClassExpression node.
      */
      void addAttributeToContent(const expression::ClassExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ConditionalExpression node.
      */
      void addAttributeToContent(const expression::ConditionalExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::Expression node.
      */
      void addAttributeToContent(const expression::Expression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::FunctionExpression node.
      */
      void addAttributeToContent(const expression::FunctionExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::Identifier node.
      */
      void addAttributeToContent(const expression::Identifier& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::Literal node.
      */
      void addAttributeToContent(const expression::Literal& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::LogicalExpression node.
      */
      void addAttributeToContent(const expression::LogicalExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::MemberExpression node.
      */
      void addAttributeToContent(const expression::MemberExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::MetaProperty node.
      */
      void addAttributeToContent(const expression::MetaProperty& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::NewExpression node.
      */
      void addAttributeToContent(const expression::NewExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::NullLiteral node.
      */
      void addAttributeToContent(const expression::NullLiteral& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::NumberLiteral node.
      */
      void addAttributeToContent(const expression::NumberLiteral& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ObjectExpression node.
      */
      void addAttributeToContent(const expression::ObjectExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::Property node.
      */
      void addAttributeToContent(const expression::Property& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::RegExpLiteral node.
      */
      void addAttributeToContent(const expression::RegExpLiteral& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::SequenceExpression node.
      */
      void addAttributeToContent(const expression::SequenceExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::SpreadElement node.
      */
      void addAttributeToContent(const expression::SpreadElement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::StringLiteral node.
      */
      void addAttributeToContent(const expression::StringLiteral& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::Super node.
      */
      void addAttributeToContent(const expression::Super& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::TaggedTemplateExpression node.
      */
      void addAttributeToContent(const expression::TaggedTemplateExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::TemplateElement node.
      */
      void addAttributeToContent(const expression::TemplateElement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::TemplateLiteral node.
      */
      void addAttributeToContent(const expression::TemplateLiteral& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ThisExpression node.
      */
      void addAttributeToContent(const expression::ThisExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::UnaryExpression node.
      */
      void addAttributeToContent(const expression::UnaryExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::UpdateExpression node.
      */
      void addAttributeToContent(const expression::UpdateExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::YieldExpression node.
      */
      void addAttributeToContent(const expression::YieldExpression& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ArrayPattern node.
      */
      void addAttributeToContent(const statement::ArrayPattern& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::AssignmentPattern node.
      */
      void addAttributeToContent(const statement::AssignmentPattern& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::BlockStatement node.
      */
      void addAttributeToContent(const statement::BlockStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::BreakStatement node.
      */
      void addAttributeToContent(const statement::BreakStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::CatchClause node.
      */
      void addAttributeToContent(const statement::CatchClause& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ContinueStatement node.
      */
      void addAttributeToContent(const statement::ContinueStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::DebuggerStatement node.
      */
      void addAttributeToContent(const statement::DebuggerStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::DoWhileStatement node.
      */
      void addAttributeToContent(const statement::DoWhileStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::EmptyStatement node.
      */
      void addAttributeToContent(const statement::EmptyStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ExpressionStatement node.
      */
      void addAttributeToContent(const statement::ExpressionStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ForInStatement node.
      */
      void addAttributeToContent(const statement::ForInStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ForOfStatement node.
      */
      void addAttributeToContent(const statement::ForOfStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ForStatement node.
      */
      void addAttributeToContent(const statement::ForStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::Function node.
      */
      void addAttributeToContent(const statement::Function& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::IfStatement node.
      */
      void addAttributeToContent(const statement::IfStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::LabeledStatement node.
      */
      void addAttributeToContent(const statement::LabeledStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ObjectPattern node.
      */
      void addAttributeToContent(const statement::ObjectPattern& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::Pattern node.
      */
      void addAttributeToContent(const statement::Pattern& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::RestElement node.
      */
      void addAttributeToContent(const statement::RestElement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ReturnStatement node.
      */
      void addAttributeToContent(const statement::ReturnStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::Statement node.
      */
      void addAttributeToContent(const statement::Statement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::SwitchCase node.
      */
      void addAttributeToContent(const statement::SwitchCase& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::SwitchStatement node.
      */
      void addAttributeToContent(const statement::SwitchStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ThrowStatement node.
      */
      void addAttributeToContent(const statement::ThrowStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::TryStatement node.
      */
      void addAttributeToContent(const statement::TryStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::WhileStatement node.
      */
      void addAttributeToContent(const statement::WhileStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::WithStatement node.
      */
      void addAttributeToContent(const statement::WithStatement& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::Class node.
      */
      void addAttributeToContent(const structure::Class& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ClassBody node.
      */
      void addAttributeToContent(const structure::ClassBody& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ExportSpecifier node.
      */
      void addAttributeToContent(const structure::ExportSpecifier& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ImpSpecifier node.
      */
      void addAttributeToContent(const structure::ImpSpecifier& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ImportDefaultSpecifier node.
      */
      void addAttributeToContent(const structure::ImportDefaultSpecifier& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ImportNamespaceSpecifier node.
      */
      void addAttributeToContent(const structure::ImportNamespaceSpecifier& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ImportSpecifier node.
      */
      void addAttributeToContent(const structure::ImportSpecifier& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::MethodDefinition node.
      */
      void addAttributeToContent(const structure::MethodDefinition& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ModuleSpecifier node.
      */
      void addAttributeToContent(const structure::ModuleSpecifier& node, std::string& content, bool callVirtualBase);

      /** \internal \brief The ofstream into the DOT graph will be written. */
      columbus::io::GraphmlIO &io;

      /** \internal \brief Internal counter for generating edges. */
      long long edgeCounter;

    private:

      /** \internal \brief It contains ids of the drawed nodes */
      std::map< NodeId, bool> idsToDrawedNodes;

      /** \internal \brief How many edges are should be draw */
      unsigned int maxDrawingDepth;

      /** \internal \brief Edges names to filtering */
      std::set< std::string> edgeFilter;

      /** \internal \brief The contains is not enable to draw */
      std::set< NodeId> nodeFilter;

      /** \internal \brief The contains is not enable to draw */
      bool visitCrossEdge;

      /** \internal \brief It is need to draw into white */
      bool isColorWhite;

      /** \internal \brief Show attributes only of these node types. If it is empty then show all attributes. */
      std::set< std::string> nodeTypeAttributeFilter;

      /** \internal \brief Helper variable for determine is the actual node groupNode it visitEnd */
      NodeId lastVisitedNodeId;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<EdgeKind> edgeKindStack;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<NodeId> parentNodeStack;

      /** \internal \brief It is need to grouping tree nodes */
      bool isGroupingTreeNodes;

      /** \internal \brief Node type names to filtering out */
      std::set< std::string> nodeTypeFilter;

  }; // VisitorGraphml


}}}
#endif

