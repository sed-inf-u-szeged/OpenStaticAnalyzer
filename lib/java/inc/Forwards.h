/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#ifndef _JAVA_Forwards_H_
#define _JAVA_Forwards_H_

/**
* \file Forwards.h
* \brief Contains forward declarations of the classes.
*/

namespace columbus { namespace java { namespace asg {

  class Algorithm;
  class AlgorithmPreorder;
  class ReverseEdges;

  class Visitor;
  class VisitorAbstractNodes;
  class VisitorAsgStat;
  class VisitorJAVAML;
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
    class BlockComment;
    class Comment;
    class Commentable;
    class JavadocComment;
    class LineComment;
    class Named;
    class NonJavadocComment;
    class Positioned;
    class PositionedWithoutComment;
  }

  namespace expr {
    class Annotation;
    class ArrayAccess;
    class ArrayTypeExpression;
    class Assignment;
    class Binary;
    class BooleanLiteral;
    class CharacterLiteral;
    class ClassLiteral;
    class Conditional;
    class DoubleLiteral;
    class Erroneous;
    class ErroneousTypeExpression;
    class Expression;
    class ExternalTypeExpression;
    class FieldAccess;
    class FloatLiteral;
    class Identifier;
    class InfixExpression;
    class InstanceOf;
    class IntegerLiteral;
    class Literal;
    class LongLiteral;
    class MarkerAnnotation;
    class MethodInvocation;
    class NewArray;
    class NewClass;
    class NormalAnnotation;
    class NullLiteral;
    class NumberLiteral;
    class ParenthesizedExpression;
    class PostfixExpression;
    class PrefixExpression;
    class PrimitiveTypeExpression;
    class QualifiedTypeExpression;
    class SimpleTypeExpression;
    class SingleElementAnnotation;
    class StringLiteral;
    class Super;
    class This;
    class TypeApplyExpression;
    class TypeCast;
    class TypeExpression;
    class TypeUnionExpression;
    class Unary;
    class WildcardExpression;
  }

  namespace statm {
    class Assert;
    class BasicFor;
    class Block;
    class Break;
    class Case;
    class Continue;
    class Default;
    class Do;
    class Empty;
    class EnhancedFor;
    class ExpressionStatement;
    class For;
    class Handler;
    class If;
    class Iteration;
    class Jump;
    class LabeledStatement;
    class Return;
    class Selection;
    class Statement;
    class Switch;
    class SwitchLabel;
    class Synchronized;
    class Throw;
    class Try;
    class While;
  }

  namespace struc {
    class AnnotatedElement;
    class AnnotationType;
    class AnnotationTypeElement;
    class AnonymousClass;
    class Class;
    class ClassDeclaration;
    class ClassGeneric;
    class CompilationUnit;
    class Declaration;
    class Enum;
    class EnumConstant;
    class GenericDeclaration;
    class Import;
    class InitializerBlock;
    class InstanceInitializerBlock;
    class Interface;
    class InterfaceDeclaration;
    class InterfaceGeneric;
    class Member;
    class Method;
    class MethodDeclaration;
    class MethodGeneric;
    class NamedDeclaration;
    class NormalMethod;
    class Package;
    class PackageDeclaration;
    class Parameter;
    class Scope;
    class StaticInitializerBlock;
    class TypeDeclaration;
    class TypeParameter;
    class Variable;
    class VariableDeclaration;
  }

  namespace type {
    class ArrayType;
    class BooleanType;
    class BoundedWildcardType;
    class ByteType;
    class CharType;
    class ClassType;
    class DoubleType;
    class ErrorType;
    class FloatType;
    class IntType;
    class LongType;
    class LowerBoundedWildcardType;
    class MethodType;
    class NoType;
    class NullType;
    class PackageType;
    class ParameterizedType;
    class PrimitiveType;
    class ScopedType;
    class ShortType;
    class Type;
    class TypeVariable;
    class UnboundedWildcardType;
    class UnionType;
    class UpperBoundedWildcardType;
    class VoidType;
    class WildcardType;
  }


}}}

namespace columbus { namespace java { namespace linker {
  class LinkerBase;
  class VisitorLinker;
}}}

#endif

