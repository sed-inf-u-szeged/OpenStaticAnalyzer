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

#ifndef _JAVA_H_
#define _JAVA_H_

/**
* \file JAVA.h
* \brief Header can be used for precompiled header.
*/
#include <list>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <boost/crc.hpp>

#include "Forwards.h"

// externals
#include "AsgCommon.h"
#include "strtable/inc/RefDistributorStrTable.h"
#include "csi/inc/csi.h"
#include "Exception.h"

#include "Constant.h"
#include "Types.h"
#include "Range.h"
#include "JavaException.h"
#include "ListIterator.h"
#include "Common.h"
#include "ReverseEdges.h"


 /***********************NODES******************/
#include "base/Base.h"
#include "base/Commentable.h"
#include "base/Named.h"
#include "base/PositionedWithoutComment.h"
#include "struc/AnnotatedElement.h"
#include "struc/GenericDeclaration.h"
#include "type/Type.h"
#include "base/Positioned.h"
#include "struc/CompilationUnit.h"
#include "struc/Member.h"
#include "struc/Module.h"
#include "struc/TypeParameter.h"
#include "base/Comment.h"
#include "type/ArrayType.h"
#include "type/ErrorType.h"
#include "type/IntersectionType.h"
#include "type/MethodType.h"
#include "type/ModuleType.h"
#include "type/NoType.h"
#include "type/NullType.h"
#include "type/PackageType.h"
#include "type/PrimitiveType.h"
#include "type/ScopedType.h"
#include "type/TypeVariable.h"
#include "type/UnionType.h"
#include "type/WildcardType.h"
#include "expr/Expression.h"
#include "module/ModuleDirective.h"
#include "statm/Handler.h"
#include "statm/Statement.h"
#include "statm/SwitchLabel.h"
#include "struc/Import.h"
#include "struc/ModuleDeclaration.h"
#include "struc/PackageDeclaration.h"
#include "struc/Declaration.h"
#include "struc/Scope.h"
#include "struc/NamedDeclaration.h"
#include "struc/Package.h"
#include "base/JavadocComment.h"
#include "base/NonJavadocComment.h"
#include "type/BooleanType.h"
#include "type/ByteType.h"
#include "type/CharType.h"
#include "type/DoubleType.h"
#include "type/FloatType.h"
#include "type/IntType.h"
#include "type/LongType.h"
#include "type/ShortType.h"
#include "type/VoidType.h"
#include "type/ClassType.h"
#include "type/ParameterizedType.h"
#include "type/BoundedWildcardType.h"
#include "type/UnboundedWildcardType.h"
#include "expr/Annotation.h"
#include "expr/Binary.h"
#include "expr/Conditional.h"
#include "expr/Erroneous.h"
#include "expr/Identifier.h"
#include "expr/Literal.h"
#include "expr/NewArray.h"
#include "expr/NewClass.h"
#include "expr/PolyExpression.h"
#include "expr/Super.h"
#include "expr/This.h"
#include "expr/TypeExpression.h"
#include "expr/Unary.h"
#include "module/Exports.h"
#include "module/Opens.h"
#include "module/Provides.h"
#include "module/Requires.h"
#include "module/Uses.h"
#include "statm/Assert.h"
#include "statm/Block.h"
#include "statm/Empty.h"
#include "statm/ExpressionStatement.h"
#include "statm/Iteration.h"
#include "statm/Jump.h"
#include "statm/LabeledStatement.h"
#include "statm/Return.h"
#include "statm/Selection.h"
#include "statm/Synchronized.h"
#include "statm/Throw.h"
#include "statm/Try.h"
#include "statm/Case.h"
#include "statm/Default.h"
#include "struc/InitializerBlock.h"
#include "struc/TypeDeclaration.h"
#include "struc/MethodDeclaration.h"
#include "struc/VariableDeclaration.h"
#include "base/BlockComment.h"
#include "base/LineComment.h"
#include "type/LowerBoundedWildcardType.h"
#include "type/UpperBoundedWildcardType.h"
#include "expr/MarkerAnnotation.h"
#include "expr/NormalAnnotation.h"
#include "expr/SingleElementAnnotation.h"
#include "expr/ArrayAccess.h"
#include "expr/Assignment.h"
#include "expr/FieldAccess.h"
#include "expr/InfixExpression.h"
#include "expr/BooleanLiteral.h"
#include "expr/CharacterLiteral.h"
#include "expr/ClassLiteral.h"
#include "expr/NullLiteral.h"
#include "expr/NumberLiteral.h"
#include "expr/StringLiteral.h"
#include "expr/FunctionalExpression.h"
#include "expr/AnnotatedTypeExpression.h"
#include "expr/ArrayTypeExpression.h"
#include "expr/ErroneousTypeExpression.h"
#include "expr/ExternalTypeExpression.h"
#include "expr/PrimitiveTypeExpression.h"
#include "expr/QualifiedTypeExpression.h"
#include "expr/SimpleTypeExpression.h"
#include "expr/TypeApplyExpression.h"
#include "expr/TypeIntersectionExpression.h"
#include "expr/TypeUnionExpression.h"
#include "expr/WildcardExpression.h"
#include "expr/InstanceOf.h"
#include "expr/MethodInvocation.h"
#include "expr/ParenthesizedExpression.h"
#include "expr/PostfixExpression.h"
#include "expr/PrefixExpression.h"
#include "expr/TypeCast.h"
#include "statm/Do.h"
#include "statm/For.h"
#include "statm/While.h"
#include "statm/Break.h"
#include "statm/Continue.h"
#include "statm/If.h"
#include "statm/Switch.h"
#include "struc/InstanceInitializerBlock.h"
#include "struc/StaticInitializerBlock.h"
#include "struc/AnnotationType.h"
#include "struc/ClassDeclaration.h"
#include "struc/Enum.h"
#include "struc/InterfaceDeclaration.h"
#include "struc/AnnotationTypeElement.h"
#include "struc/NormalMethod.h"
#include "struc/EnumConstant.h"
#include "struc/Parameter.h"
#include "struc/Variable.h"
#include "struc/ClassGeneric.h"
#include "struc/InterfaceGeneric.h"
#include "struc/MethodGeneric.h"
#include "expr/DoubleLiteral.h"
#include "expr/FloatLiteral.h"
#include "expr/IntegerLiteral.h"
#include "expr/LongLiteral.h"
#include "expr/Lambda.h"
#include "expr/MemberReference.h"
#include "statm/BasicFor.h"
#include "statm/EnhancedFor.h"
#include "struc/AnonymousClass.h"
#include "struc/Class.h"
#include "struc/Interface.h"
#include "struc/Method.h"


#include "Filter.h"
#include "Factory.h"

#include "visitors/Visitor.h"
#include "visitors/VisitorAbstractNodes.h"
#include "visitors/VisitorAsgStat.h"
#include "visitors/VisitorJAVAML.h"
#include "visitors/VisitorFilter.h"
#include "visitors/VisitorReverseEdges.h"
#include "visitors/VisitorSave.h"
#include "visitors/VisitorSubtreeCollector.h"
#include "visitors/VisitorSimpleEdge.h"
#include "Range.h"

#include "algorithms/Algorithm.h"
#include "algorithms/AlgorithmPreorder.h"
#include "algorithms/AlgorithmCreates.h"
#include "visitors/VisitorJANFilter.h"
#include "visitors/VisitorUniqueNames.h"

#endif

