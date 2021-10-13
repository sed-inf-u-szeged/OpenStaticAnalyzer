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

#ifndef _PYTHON_Forwards_H_
#define _PYTHON_Forwards_H_

/**
* \file Forwards.h
* \brief Contains forward declarations of the classes.
*/

namespace columbus { namespace python { namespace asg {

  class Algorithm;
  class AlgorithmPreorder;
  class ReverseEdges;

  class Visitor;
  class VisitorAbstractNodes;
  class VisitorPYTHONML;
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
    class Docstring;
    class Named;
    class Positioned;
  }

  namespace expression {
    class ArgumentList;
    class AttributeRef;
    class Await;
    class Binary;
    class BinaryArithmetic;
    class BinaryLogical;
    class BytesLiteral;
    class Call;
    class DictComp;
    class Dictionary;
    class Ellipsis;
    class Expression;
    class ExpressionList;
    class ExtSlice;
    class FloatNumber;
    class FormattedValue;
    class Generator;
    class GeneratorExpression;
    class Identifier;
    class IfExpression;
    class ImagNumber;
    class Index;
    class IntegerLiteral;
    class JoinedStr;
    class KeyValue;
    class Keyword;
    class Lambda;
    class List;
    class ListComp;
    class Literal;
    class LongInteger;
    class NamedExpr;
    class Set;
    class SetComp;
    class Slice;
    class Slicing;
    class Starred;
    class StringConversion;
    class StringLiteral;
    class Subscription;
    class Unary;
    class UnaryOperation;
    class YieldExpression;
  }

  namespace module {
    class Module;
    class Object;
    class Package;
  }

  namespace statement {
    class Alias;
    class AnnAssign;
    class Assert;
    class Assign;
    class AugAssign;
    class BaseSpecifier;
    class Break;
    class ClassDef;
    class CompoundStatement;
    class Continue;
    class Delete;
    class Exec;
    class For;
    class FunctionDef;
    class Global;
    class Handler;
    class If;
    class ImportFrom;
    class ImportStatement;
    class Iteration;
    class Nonlocal;
    class Parameter;
    class Pass;
    class Print;
    class Raise;
    class Return;
    class SimpleStatement;
    class Statement;
    class Suite;
    class TargetList;
    class Try;
    class While;
    class With;
    class WithItem;
  }

  namespace type {
    class DictType;
    class ReferenceType;
    class SequenceType;
    class SimpleType;
    class Type;
  }


}}}

#endif

