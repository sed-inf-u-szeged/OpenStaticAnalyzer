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

#ifndef _JAVASCRIPT_Forwards_H_
#define _JAVASCRIPT_Forwards_H_

/**
* \file Forwards.h
* \brief Contains forward declarations of the classes.
*/

namespace columbus { namespace javascript { namespace asg {

  class Algorithm;
  class AlgorithmPreorder;
  class ReverseEdges;

  class Visitor;
  class VisitorAbstractNodes;
  class VisitorAsgStat;
  class VisitorGraphml;
  class VisitorJAVASCRIPTML;
  class VisitorFilter;
  class VisitorReverseEdges;
  class VisitorSave;

  template <typename T>
  class ListIterator;
  class Factory;
  class Filter;
  class Range;
  class RangeListIterator;

  namespace base {
    class Base;
    class Comment;
    class Named;
    class Positioned;
    class Program;
    class System;
  }

  namespace declaration {
    class ClassDeclaration;
    class Declaration;
    class ExportAllDeclaration;
    class ExportDefaultDeclaration;
    class ExportNamedDeclaration;
    class FunctionDeclaration;
    class ImportDeclaration;
    class ModuleDeclaration;
    class VariableDeclaration;
    class VariableDeclarator;
  }

  namespace expression {
    class ArrayExpression;
    class ArrowFunctionExpression;
    class AssignmentExpression;
    class AssignmentProperty;
    class AwaitExpression;
    class BinaryExpression;
    class BooleanLiteral;
    class CallExpression;
    class ClassExpression;
    class ConditionalExpression;
    class Expression;
    class FunctionExpression;
    class Identifier;
    class Literal;
    class LogicalExpression;
    class MemberExpression;
    class MetaProperty;
    class NewExpression;
    class NullLiteral;
    class NumberLiteral;
    class ObjectExpression;
    class Property;
    class RegExpLiteral;
    class SequenceExpression;
    class SpreadElement;
    class StringLiteral;
    class Super;
    class TaggedTemplateExpression;
    class TemplateElement;
    class TemplateLiteral;
    class ThisExpression;
    class UnaryExpression;
    class UpdateExpression;
    class YieldExpression;
  }

  namespace statement {
    class ArrayPattern;
    class AssignmentPattern;
    class BlockStatement;
    class BreakStatement;
    class CatchClause;
    class ContinueStatement;
    class DebuggerStatement;
    class DoWhileStatement;
    class EmptyStatement;
    class ExpressionStatement;
    class ForInStatement;
    class ForOfStatement;
    class ForStatement;
    class Function;
    class IfStatement;
    class LabeledStatement;
    class ObjectPattern;
    class Pattern;
    class RestElement;
    class ReturnStatement;
    class Statement;
    class SwitchCase;
    class SwitchStatement;
    class ThrowStatement;
    class TryStatement;
    class WhileStatement;
    class WithStatement;
  }

  namespace structure {
    class Class;
    class ClassBody;
    class ExportSpecifier;
    class ImpSpecifier;
    class ImportDefaultSpecifier;
    class ImportNamespaceSpecifier;
    class ImportSpecifier;
    class MethodDefinition;
    class ModuleSpecifier;
  }


}}}

#endif

