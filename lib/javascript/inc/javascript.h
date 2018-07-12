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

#ifndef _JAVASCRIPT_H_
#define _JAVASCRIPT_H_

/**
* \file JAVASCRIPT.h
* \brief Header can be used for precompiled header.
*/

#include <list>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <boost/crc.hpp>

#include "csi/inc/HeaderData.h" 
#include "csi/inc/PropertyData.h" 
#include "Forwards.h"

// externals
#include "AsgCommon.h"
#include "strtable/inc/RefDistributorStrTable.h"
#include "csi/inc/csi.h"
#include "Exception.h"

#include "Constant.h"
#include "Types.h"
#include "Range.h"
#include "JavaScriptException.h"
#include "ListIterator.h"
#include "Common.h"
#include "ReverseEdges.h"


 /***********************NODES******************/
#include "base/Base.h"
#include "base/Positioned.h"
#include "base/System.h"
#include "base/Comment.h"
#include "base/Named.h"
#include "declaration/ModuleDeclaration.h"
#include "declaration/VariableDeclarator.h"
#include "expression/Expression.h"
#include "expression/Literal.h"
#include "expression/Property.h"
#include "expression/SpreadElement.h"
#include "expression/Super.h"
#include "expression/TemplateElement.h"
#include "statement/CatchClause.h"
#include "statement/Function.h"
#include "statement/Pattern.h"
#include "statement/Statement.h"
#include "statement/SwitchCase.h"
#include "structure/Class.h"
#include "structure/ClassBody.h"
#include "structure/MethodDefinition.h"
#include "structure/ModuleSpecifier.h"
#include "base/Program.h"
#include "expression/Identifier.h"
#include "declaration/ExportNamedDeclaration.h"
#include "declaration/ImportDeclaration.h"
#include "expression/ArrayExpression.h"
#include "expression/ArrowFunctionExpression.h"
#include "expression/AssignmentExpression.h"
#include "expression/AwaitExpression.h"
#include "expression/BinaryExpression.h"
#include "expression/CallExpression.h"
#include "expression/ClassExpression.h"
#include "expression/ConditionalExpression.h"
#include "expression/FunctionExpression.h"
#include "expression/LogicalExpression.h"
#include "expression/MemberExpression.h"
#include "expression/MetaProperty.h"
#include "expression/NewExpression.h"
#include "expression/ObjectExpression.h"
#include "expression/SequenceExpression.h"
#include "expression/TaggedTemplateExpression.h"
#include "expression/TemplateLiteral.h"
#include "expression/ThisExpression.h"
#include "expression/UnaryExpression.h"
#include "expression/UpdateExpression.h"
#include "expression/YieldExpression.h"
#include "expression/BooleanLiteral.h"
#include "expression/NullLiteral.h"
#include "expression/NumberLiteral.h"
#include "expression/RegExpLiteral.h"
#include "expression/StringLiteral.h"
#include "expression/AssignmentProperty.h"
#include "statement/ArrayPattern.h"
#include "statement/AssignmentPattern.h"
#include "statement/ObjectPattern.h"
#include "statement/RestElement.h"
#include "declaration/Declaration.h"
#include "statement/BlockStatement.h"
#include "statement/BreakStatement.h"
#include "statement/ContinueStatement.h"
#include "statement/DebuggerStatement.h"
#include "statement/EmptyStatement.h"
#include "statement/ExpressionStatement.h"
#include "statement/ForInStatement.h"
#include "statement/ForStatement.h"
#include "statement/IfStatement.h"
#include "statement/LabeledStatement.h"
#include "statement/ReturnStatement.h"
#include "statement/SwitchStatement.h"
#include "statement/ThrowStatement.h"
#include "statement/TryStatement.h"
#include "statement/WhileStatement.h"
#include "statement/WithStatement.h"
#include "declaration/ClassDeclaration.h"
#include "structure/ExportSpecifier.h"
#include "structure/ImpSpecifier.h"
#include "declaration/FunctionDeclaration.h"
#include "declaration/ExportAllDeclaration.h"
#include "declaration/ExportDefaultDeclaration.h"
#include "declaration/VariableDeclaration.h"
#include "statement/ForOfStatement.h"
#include "statement/DoWhileStatement.h"
#include "structure/ImportDefaultSpecifier.h"
#include "structure/ImportNamespaceSpecifier.h"
#include "structure/ImportSpecifier.h"


#include "Filter.h"
#include "Factory.h"

#include "visitors/Visitor.h"
#include "visitors/VisitorAbstractNodes.h"
#include "visitors/VisitorAsgStat.h"
#include "visitors/VisitorGraphml.h"
#include "visitors/VisitorJAVASCRIPTML.h"
#include "visitors/VisitorFilter.h"
#include "visitors/VisitorReverseEdges.h"
#include "visitors/VisitorSave.h"
#include "visitors/VisitorSubtreeCollector.h"
#include "visitors/VisitorSimpleEdge.h"
#include "Range.h"

#include "algorithms/Algorithm.h"
#include "algorithms/AlgorithmPreorder.h"

#endif

