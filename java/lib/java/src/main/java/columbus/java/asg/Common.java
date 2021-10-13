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

package columbus.java.asg;

import columbus.java.asg.base.Base;
import columbus.java.asg.enums.NodeKind;
import static columbus.java.asg.enums.NodeKind.*;

/**
 * Common contains general graph algorithms and common methods.
 */
public class Common {

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.BlockComment BlockComment} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.BlockComment BlockComment}.
	 */
	public static boolean getIsBlockComment(Base node) {
		return node instanceof columbus.java.asg.base.BlockComment;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.Comment Comment} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.Comment Comment}.
	 */
	public static boolean getIsComment(Base node) {
		return node instanceof columbus.java.asg.base.Comment;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.Commentable Commentable} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.Commentable Commentable}.
	 */
	public static boolean getIsCommentable(Base node) {
		return node instanceof columbus.java.asg.base.Commentable;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.JavadocComment JavadocComment} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.JavadocComment JavadocComment}.
	 */
	public static boolean getIsJavadocComment(Base node) {
		return node instanceof columbus.java.asg.base.JavadocComment;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.LineComment LineComment} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.LineComment LineComment}.
	 */
	public static boolean getIsLineComment(Base node) {
		return node instanceof columbus.java.asg.base.LineComment;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.Named Named} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.Named Named}.
	 */
	public static boolean getIsNamed(Base node) {
		return node instanceof columbus.java.asg.base.Named;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.NonJavadocComment NonJavadocComment} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.NonJavadocComment NonJavadocComment}.
	 */
	public static boolean getIsNonJavadocComment(Base node) {
		return node instanceof columbus.java.asg.base.NonJavadocComment;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.Positioned Positioned} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.Positioned Positioned}.
	 */
	public static boolean getIsPositioned(Base node) {
		return node instanceof columbus.java.asg.base.Positioned;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.base.PositionedWithoutComment PositionedWithoutComment} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.base.PositionedWithoutComment PositionedWithoutComment}.
	 */
	public static boolean getIsPositionedWithoutComment(Base node) {
		return node instanceof columbus.java.asg.base.PositionedWithoutComment;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.AnnotatedTypeExpression AnnotatedTypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.AnnotatedTypeExpression AnnotatedTypeExpression}.
	 */
	public static boolean getIsAnnotatedTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.AnnotatedTypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Annotation Annotation} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Annotation Annotation}.
	 */
	public static boolean getIsAnnotation(Base node) {
		return node instanceof columbus.java.asg.expr.Annotation;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.ArrayAccess ArrayAccess}.
	 */
	public static boolean getIsArrayAccess(Base node) {
		return node instanceof columbus.java.asg.expr.ArrayAccess;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression}.
	 */
	public static boolean getIsArrayTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.ArrayTypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Assignment Assignment} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Assignment Assignment}.
	 */
	public static boolean getIsAssignment(Base node) {
		return node instanceof columbus.java.asg.expr.Assignment;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Binary Binary} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Binary Binary}.
	 */
	public static boolean getIsBinary(Base node) {
		return node instanceof columbus.java.asg.expr.Binary;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral}.
	 */
	public static boolean getIsBooleanLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.BooleanLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral}.
	 */
	public static boolean getIsCharacterLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.CharacterLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.ClassLiteral ClassLiteral}.
	 */
	public static boolean getIsClassLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.ClassLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Conditional Conditional} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Conditional Conditional}.
	 */
	public static boolean getIsConditional(Base node) {
		return node instanceof columbus.java.asg.expr.Conditional;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral}.
	 */
	public static boolean getIsDoubleLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.DoubleLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Erroneous Erroneous} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Erroneous Erroneous}.
	 */
	public static boolean getIsErroneous(Base node) {
		return node instanceof columbus.java.asg.expr.Erroneous;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression}.
	 */
	public static boolean getIsErroneousTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.ErroneousTypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Expression Expression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Expression Expression}.
	 */
	public static boolean getIsExpression(Base node) {
		return node instanceof columbus.java.asg.expr.Expression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression}.
	 */
	public static boolean getIsExternalTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.ExternalTypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.FieldAccess FieldAccess} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.FieldAccess FieldAccess}.
	 */
	public static boolean getIsFieldAccess(Base node) {
		return node instanceof columbus.java.asg.expr.FieldAccess;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.FloatLiteral FloatLiteral}.
	 */
	public static boolean getIsFloatLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.FloatLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.FunctionalExpression FunctionalExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.FunctionalExpression FunctionalExpression}.
	 */
	public static boolean getIsFunctionalExpression(Base node) {
		return node instanceof columbus.java.asg.expr.FunctionalExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Identifier Identifier} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Identifier Identifier}.
	 */
	public static boolean getIsIdentifier(Base node) {
		return node instanceof columbus.java.asg.expr.Identifier;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.InfixExpression InfixExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.InfixExpression InfixExpression}.
	 */
	public static boolean getIsInfixExpression(Base node) {
		return node instanceof columbus.java.asg.expr.InfixExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.InstanceOf InstanceOf} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.InstanceOf InstanceOf}.
	 */
	public static boolean getIsInstanceOf(Base node) {
		return node instanceof columbus.java.asg.expr.InstanceOf;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral}.
	 */
	public static boolean getIsIntegerLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.IntegerLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Lambda Lambda} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Lambda Lambda}.
	 */
	public static boolean getIsLambda(Base node) {
		return node instanceof columbus.java.asg.expr.Lambda;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Literal Literal} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Literal Literal}.
	 */
	public static boolean getIsLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.Literal;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.LongLiteral LongLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.LongLiteral LongLiteral}.
	 */
	public static boolean getIsLongLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.LongLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation}.
	 */
	public static boolean getIsMarkerAnnotation(Base node) {
		return node instanceof columbus.java.asg.expr.MarkerAnnotation;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.MemberReference MemberReference} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.MemberReference MemberReference}.
	 */
	public static boolean getIsMemberReference(Base node) {
		return node instanceof columbus.java.asg.expr.MemberReference;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.MethodInvocation MethodInvocation}.
	 */
	public static boolean getIsMethodInvocation(Base node) {
		return node instanceof columbus.java.asg.expr.MethodInvocation;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.NewArray NewArray} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.NewArray NewArray}.
	 */
	public static boolean getIsNewArray(Base node) {
		return node instanceof columbus.java.asg.expr.NewArray;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.NewClass NewClass} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.NewClass NewClass}.
	 */
	public static boolean getIsNewClass(Base node) {
		return node instanceof columbus.java.asg.expr.NewClass;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation}.
	 */
	public static boolean getIsNormalAnnotation(Base node) {
		return node instanceof columbus.java.asg.expr.NormalAnnotation;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.NullLiteral NullLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.NullLiteral NullLiteral}.
	 */
	public static boolean getIsNullLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.NullLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.NumberLiteral NumberLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.NumberLiteral NumberLiteral}.
	 */
	public static boolean getIsNumberLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.NumberLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression}.
	 */
	public static boolean getIsParenthesizedExpression(Base node) {
		return node instanceof columbus.java.asg.expr.ParenthesizedExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.PolyExpression PolyExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.PolyExpression PolyExpression}.
	 */
	public static boolean getIsPolyExpression(Base node) {
		return node instanceof columbus.java.asg.expr.PolyExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.PostfixExpression PostfixExpression}.
	 */
	public static boolean getIsPostfixExpression(Base node) {
		return node instanceof columbus.java.asg.expr.PostfixExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.PrefixExpression PrefixExpression}.
	 */
	public static boolean getIsPrefixExpression(Base node) {
		return node instanceof columbus.java.asg.expr.PrefixExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression}.
	 */
	public static boolean getIsPrimitiveTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.PrimitiveTypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression}.
	 */
	public static boolean getIsQualifiedTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.QualifiedTypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression}.
	 */
	public static boolean getIsSimpleTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.SimpleTypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation}.
	 */
	public static boolean getIsSingleElementAnnotation(Base node) {
		return node instanceof columbus.java.asg.expr.SingleElementAnnotation;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.StringLiteral StringLiteral} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.StringLiteral StringLiteral}.
	 */
	public static boolean getIsStringLiteral(Base node) {
		return node instanceof columbus.java.asg.expr.StringLiteral;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Super Super} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Super Super}.
	 */
	public static boolean getIsSuper(Base node) {
		return node instanceof columbus.java.asg.expr.Super;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.This This} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.This This}.
	 */
	public static boolean getIsThis(Base node) {
		return node instanceof columbus.java.asg.expr.This;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression}.
	 */
	public static boolean getIsTypeApplyExpression(Base node) {
		return node instanceof columbus.java.asg.expr.TypeApplyExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.TypeCast TypeCast} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.TypeCast TypeCast}.
	 */
	public static boolean getIsTypeCast(Base node) {
		return node instanceof columbus.java.asg.expr.TypeCast;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.TypeExpression TypeExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.TypeExpression TypeExpression}.
	 */
	public static boolean getIsTypeExpression(Base node) {
		return node instanceof columbus.java.asg.expr.TypeExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.TypeIntersectionExpression TypeIntersectionExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.TypeIntersectionExpression TypeIntersectionExpression}.
	 */
	public static boolean getIsTypeIntersectionExpression(Base node) {
		return node instanceof columbus.java.asg.expr.TypeIntersectionExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression}.
	 */
	public static boolean getIsTypeUnionExpression(Base node) {
		return node instanceof columbus.java.asg.expr.TypeUnionExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.Unary Unary} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.Unary Unary}.
	 */
	public static boolean getIsUnary(Base node) {
		return node instanceof columbus.java.asg.expr.Unary;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.expr.WildcardExpression WildcardExpression}.
	 */
	public static boolean getIsWildcardExpression(Base node) {
		return node instanceof columbus.java.asg.expr.WildcardExpression;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.module.Exports Exports} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.module.Exports Exports}.
	 */
	public static boolean getIsExports(Base node) {
		return node instanceof columbus.java.asg.module.Exports;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.module.ModuleDirective ModuleDirective} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.module.ModuleDirective ModuleDirective}.
	 */
	public static boolean getIsModuleDirective(Base node) {
		return node instanceof columbus.java.asg.module.ModuleDirective;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.module.Opens Opens} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.module.Opens Opens}.
	 */
	public static boolean getIsOpens(Base node) {
		return node instanceof columbus.java.asg.module.Opens;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.module.Provides Provides} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.module.Provides Provides}.
	 */
	public static boolean getIsProvides(Base node) {
		return node instanceof columbus.java.asg.module.Provides;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.module.Requires Requires} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.module.Requires Requires}.
	 */
	public static boolean getIsRequires(Base node) {
		return node instanceof columbus.java.asg.module.Requires;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.module.Uses Uses} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.module.Uses Uses}.
	 */
	public static boolean getIsUses(Base node) {
		return node instanceof columbus.java.asg.module.Uses;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Assert Assert} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Assert Assert}.
	 */
	public static boolean getIsAssert(Base node) {
		return node instanceof columbus.java.asg.statm.Assert;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.BasicFor BasicFor} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.BasicFor BasicFor}.
	 */
	public static boolean getIsBasicFor(Base node) {
		return node instanceof columbus.java.asg.statm.BasicFor;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Block Block} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Block Block}.
	 */
	public static boolean getIsBlock(Base node) {
		return node instanceof columbus.java.asg.statm.Block;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Break Break} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Break Break}.
	 */
	public static boolean getIsBreak(Base node) {
		return node instanceof columbus.java.asg.statm.Break;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Case Case} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Case Case}.
	 */
	public static boolean getIsCase(Base node) {
		return node instanceof columbus.java.asg.statm.Case;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Continue Continue} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Continue Continue}.
	 */
	public static boolean getIsContinue(Base node) {
		return node instanceof columbus.java.asg.statm.Continue;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Default Default} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Default Default}.
	 */
	public static boolean getIsDefault(Base node) {
		return node instanceof columbus.java.asg.statm.Default;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Do Do} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Do Do}.
	 */
	public static boolean getIsDo(Base node) {
		return node instanceof columbus.java.asg.statm.Do;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Empty Empty} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Empty Empty}.
	 */
	public static boolean getIsEmpty(Base node) {
		return node instanceof columbus.java.asg.statm.Empty;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.EnhancedFor EnhancedFor}.
	 */
	public static boolean getIsEnhancedFor(Base node) {
		return node instanceof columbus.java.asg.statm.EnhancedFor;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement}.
	 */
	public static boolean getIsExpressionStatement(Base node) {
		return node instanceof columbus.java.asg.statm.ExpressionStatement;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.For For} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.For For}.
	 */
	public static boolean getIsFor(Base node) {
		return node instanceof columbus.java.asg.statm.For;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Handler Handler} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Handler Handler}.
	 */
	public static boolean getIsHandler(Base node) {
		return node instanceof columbus.java.asg.statm.Handler;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.If If} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.If If}.
	 */
	public static boolean getIsIf(Base node) {
		return node instanceof columbus.java.asg.statm.If;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Iteration Iteration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Iteration Iteration}.
	 */
	public static boolean getIsIteration(Base node) {
		return node instanceof columbus.java.asg.statm.Iteration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Jump Jump} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Jump Jump}.
	 */
	public static boolean getIsJump(Base node) {
		return node instanceof columbus.java.asg.statm.Jump;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.LabeledStatement LabeledStatement}.
	 */
	public static boolean getIsLabeledStatement(Base node) {
		return node instanceof columbus.java.asg.statm.LabeledStatement;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Return Return} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Return Return}.
	 */
	public static boolean getIsReturn(Base node) {
		return node instanceof columbus.java.asg.statm.Return;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Selection Selection} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Selection Selection}.
	 */
	public static boolean getIsSelection(Base node) {
		return node instanceof columbus.java.asg.statm.Selection;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Statement Statement} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Statement Statement}.
	 */
	public static boolean getIsStatement(Base node) {
		return node instanceof columbus.java.asg.statm.Statement;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Switch Switch} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Switch Switch}.
	 */
	public static boolean getIsSwitch(Base node) {
		return node instanceof columbus.java.asg.statm.Switch;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.SwitchLabel SwitchLabel} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.SwitchLabel SwitchLabel}.
	 */
	public static boolean getIsSwitchLabel(Base node) {
		return node instanceof columbus.java.asg.statm.SwitchLabel;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Synchronized Synchronized} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Synchronized Synchronized}.
	 */
	public static boolean getIsSynchronized(Base node) {
		return node instanceof columbus.java.asg.statm.Synchronized;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Throw Throw} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Throw Throw}.
	 */
	public static boolean getIsThrow(Base node) {
		return node instanceof columbus.java.asg.statm.Throw;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.Try Try} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.Try Try}.
	 */
	public static boolean getIsTry(Base node) {
		return node instanceof columbus.java.asg.statm.Try;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.statm.While While} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.statm.While While}.
	 */
	public static boolean getIsWhile(Base node) {
		return node instanceof columbus.java.asg.statm.While;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.AnnotatedElement AnnotatedElement} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.AnnotatedElement AnnotatedElement}.
	 */
	public static boolean getIsAnnotatedElement(Base node) {
		return node instanceof columbus.java.asg.struc.AnnotatedElement;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.AnnotationType AnnotationType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.AnnotationType AnnotationType}.
	 */
	public static boolean getIsAnnotationType(Base node) {
		return node instanceof columbus.java.asg.struc.AnnotationType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement}.
	 */
	public static boolean getIsAnnotationTypeElement(Base node) {
		return node instanceof columbus.java.asg.struc.AnnotationTypeElement;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.AnonymousClass AnonymousClass}.
	 */
	public static boolean getIsAnonymousClass(Base node) {
		return node instanceof columbus.java.asg.struc.AnonymousClass;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Class Class} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Class Class}.
	 */
	public static boolean getIsClass(Base node) {
		return node instanceof columbus.java.asg.struc.Class;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.ClassDeclaration ClassDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.ClassDeclaration ClassDeclaration}.
	 */
	public static boolean getIsClassDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.ClassDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.ClassGeneric ClassGeneric}.
	 */
	public static boolean getIsClassGeneric(Base node) {
		return node instanceof columbus.java.asg.struc.ClassGeneric;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.CompilationUnit CompilationUnit}.
	 */
	public static boolean getIsCompilationUnit(Base node) {
		return node instanceof columbus.java.asg.struc.CompilationUnit;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Declaration Declaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Declaration Declaration}.
	 */
	public static boolean getIsDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.Declaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Enum Enum} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Enum Enum}.
	 */
	public static boolean getIsEnum(Base node) {
		return node instanceof columbus.java.asg.struc.Enum;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.EnumConstant EnumConstant} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.EnumConstant EnumConstant}.
	 */
	public static boolean getIsEnumConstant(Base node) {
		return node instanceof columbus.java.asg.struc.EnumConstant;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.GenericDeclaration GenericDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.GenericDeclaration GenericDeclaration}.
	 */
	public static boolean getIsGenericDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.GenericDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Import Import} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Import Import}.
	 */
	public static boolean getIsImport(Base node) {
		return node instanceof columbus.java.asg.struc.Import;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.InitializerBlock InitializerBlock} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.InitializerBlock InitializerBlock}.
	 */
	public static boolean getIsInitializerBlock(Base node) {
		return node instanceof columbus.java.asg.struc.InitializerBlock;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock}.
	 */
	public static boolean getIsInstanceInitializerBlock(Base node) {
		return node instanceof columbus.java.asg.struc.InstanceInitializerBlock;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Interface Interface} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Interface Interface}.
	 */
	public static boolean getIsInterface(Base node) {
		return node instanceof columbus.java.asg.struc.Interface;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.InterfaceDeclaration InterfaceDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.InterfaceDeclaration InterfaceDeclaration}.
	 */
	public static boolean getIsInterfaceDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.InterfaceDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric}.
	 */
	public static boolean getIsInterfaceGeneric(Base node) {
		return node instanceof columbus.java.asg.struc.InterfaceGeneric;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Member Member} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Member Member}.
	 */
	public static boolean getIsMember(Base node) {
		return node instanceof columbus.java.asg.struc.Member;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Method Method} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Method Method}.
	 */
	public static boolean getIsMethod(Base node) {
		return node instanceof columbus.java.asg.struc.Method;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration}.
	 */
	public static boolean getIsMethodDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.MethodDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.MethodGeneric MethodGeneric}.
	 */
	public static boolean getIsMethodGeneric(Base node) {
		return node instanceof columbus.java.asg.struc.MethodGeneric;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Module Module} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Module Module}.
	 */
	public static boolean getIsModule(Base node) {
		return node instanceof columbus.java.asg.struc.Module;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.ModuleDeclaration ModuleDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.ModuleDeclaration ModuleDeclaration}.
	 */
	public static boolean getIsModuleDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.ModuleDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.NamedDeclaration NamedDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.NamedDeclaration NamedDeclaration}.
	 */
	public static boolean getIsNamedDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.NamedDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.NormalMethod NormalMethod} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.NormalMethod NormalMethod}.
	 */
	public static boolean getIsNormalMethod(Base node) {
		return node instanceof columbus.java.asg.struc.NormalMethod;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Package Package} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Package Package}.
	 */
	public static boolean getIsPackage(Base node) {
		return node instanceof columbus.java.asg.struc.Package;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration}.
	 */
	public static boolean getIsPackageDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.PackageDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Parameter Parameter} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Parameter Parameter}.
	 */
	public static boolean getIsParameter(Base node) {
		return node instanceof columbus.java.asg.struc.Parameter;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Scope Scope} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Scope Scope}.
	 */
	public static boolean getIsScope(Base node) {
		return node instanceof columbus.java.asg.struc.Scope;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock}.
	 */
	public static boolean getIsStaticInitializerBlock(Base node) {
		return node instanceof columbus.java.asg.struc.StaticInitializerBlock;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration}.
	 */
	public static boolean getIsTypeDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.TypeDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.TypeParameter TypeParameter} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.TypeParameter TypeParameter}.
	 */
	public static boolean getIsTypeParameter(Base node) {
		return node instanceof columbus.java.asg.struc.TypeParameter;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.Variable Variable} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.Variable Variable}.
	 */
	public static boolean getIsVariable(Base node) {
		return node instanceof columbus.java.asg.struc.Variable;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.struc.VariableDeclaration VariableDeclaration} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.struc.VariableDeclaration VariableDeclaration}.
	 */
	public static boolean getIsVariableDeclaration(Base node) {
		return node instanceof columbus.java.asg.struc.VariableDeclaration;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ArrayType ArrayType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ArrayType ArrayType}.
	 */
	public static boolean getIsArrayType(Base node) {
		return node instanceof columbus.java.asg.type.ArrayType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.BooleanType BooleanType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.BooleanType BooleanType}.
	 */
	public static boolean getIsBooleanType(Base node) {
		return node instanceof columbus.java.asg.type.BooleanType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.BoundedWildcardType BoundedWildcardType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.BoundedWildcardType BoundedWildcardType}.
	 */
	public static boolean getIsBoundedWildcardType(Base node) {
		return node instanceof columbus.java.asg.type.BoundedWildcardType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ByteType ByteType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ByteType ByteType}.
	 */
	public static boolean getIsByteType(Base node) {
		return node instanceof columbus.java.asg.type.ByteType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.CharType CharType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.CharType CharType}.
	 */
	public static boolean getIsCharType(Base node) {
		return node instanceof columbus.java.asg.type.CharType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ClassType ClassType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ClassType ClassType}.
	 */
	public static boolean getIsClassType(Base node) {
		return node instanceof columbus.java.asg.type.ClassType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.DoubleType DoubleType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.DoubleType DoubleType}.
	 */
	public static boolean getIsDoubleType(Base node) {
		return node instanceof columbus.java.asg.type.DoubleType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ErrorType ErrorType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ErrorType ErrorType}.
	 */
	public static boolean getIsErrorType(Base node) {
		return node instanceof columbus.java.asg.type.ErrorType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.FloatType FloatType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.FloatType FloatType}.
	 */
	public static boolean getIsFloatType(Base node) {
		return node instanceof columbus.java.asg.type.FloatType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.IntType IntType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.IntType IntType}.
	 */
	public static boolean getIsIntType(Base node) {
		return node instanceof columbus.java.asg.type.IntType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.IntersectionType IntersectionType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.IntersectionType IntersectionType}.
	 */
	public static boolean getIsIntersectionType(Base node) {
		return node instanceof columbus.java.asg.type.IntersectionType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.LongType LongType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.LongType LongType}.
	 */
	public static boolean getIsLongType(Base node) {
		return node instanceof columbus.java.asg.type.LongType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType}.
	 */
	public static boolean getIsLowerBoundedWildcardType(Base node) {
		return node instanceof columbus.java.asg.type.LowerBoundedWildcardType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.MethodType MethodType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.MethodType MethodType}.
	 */
	public static boolean getIsMethodType(Base node) {
		return node instanceof columbus.java.asg.type.MethodType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ModuleType ModuleType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ModuleType ModuleType}.
	 */
	public static boolean getIsModuleType(Base node) {
		return node instanceof columbus.java.asg.type.ModuleType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.NoType NoType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.NoType NoType}.
	 */
	public static boolean getIsNoType(Base node) {
		return node instanceof columbus.java.asg.type.NoType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.NullType NullType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.NullType NullType}.
	 */
	public static boolean getIsNullType(Base node) {
		return node instanceof columbus.java.asg.type.NullType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.PackageType PackageType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.PackageType PackageType}.
	 */
	public static boolean getIsPackageType(Base node) {
		return node instanceof columbus.java.asg.type.PackageType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ParameterizedType ParameterizedType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ParameterizedType ParameterizedType}.
	 */
	public static boolean getIsParameterizedType(Base node) {
		return node instanceof columbus.java.asg.type.ParameterizedType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.PrimitiveType PrimitiveType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.PrimitiveType PrimitiveType}.
	 */
	public static boolean getIsPrimitiveType(Base node) {
		return node instanceof columbus.java.asg.type.PrimitiveType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ScopedType ScopedType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ScopedType ScopedType}.
	 */
	public static boolean getIsScopedType(Base node) {
		return node instanceof columbus.java.asg.type.ScopedType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.ShortType ShortType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.ShortType ShortType}.
	 */
	public static boolean getIsShortType(Base node) {
		return node instanceof columbus.java.asg.type.ShortType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.Type Type} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.Type Type}.
	 */
	public static boolean getIsType(Base node) {
		return node instanceof columbus.java.asg.type.Type;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.TypeVariable TypeVariable} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.TypeVariable TypeVariable}.
	 */
	public static boolean getIsTypeVariable(Base node) {
		return node instanceof columbus.java.asg.type.TypeVariable;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType}.
	 */
	public static boolean getIsUnboundedWildcardType(Base node) {
		return node instanceof columbus.java.asg.type.UnboundedWildcardType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.UnionType UnionType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.UnionType UnionType}.
	 */
	public static boolean getIsUnionType(Base node) {
		return node instanceof columbus.java.asg.type.UnionType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType}.
	 */
	public static boolean getIsUpperBoundedWildcardType(Base node) {
		return node instanceof columbus.java.asg.type.UpperBoundedWildcardType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.VoidType VoidType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.VoidType VoidType}.
	 */
	public static boolean getIsVoidType(Base node) {
		return node instanceof columbus.java.asg.type.VoidType;
	}

	/**
	 * Decides whether the node is {@link columbus.java.asg.type.WildcardType WildcardType} or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is {@link columbus.java.asg.type.WildcardType WildcardType}.
	 */
	public static boolean getIsWildcardType(Base node) {
		return node instanceof columbus.java.asg.type.WildcardType;
	}

	/**
	 * Decides whether the node is AP spec node or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is AP spec node.
	 */
	public static boolean getIsAPSpecNode(Base node) {
		NodeKind ndk = node.getNodeKind();
		return
			ndk == ndkBlockComment ||
			ndk == ndkJavadocComment ||
			ndk == ndkLineComment ||
			ndk == ndkArrayType ||
			ndk == ndkBooleanType ||
			ndk == ndkByteType ||
			ndk == ndkCharType ||
			ndk == ndkClassType ||
			ndk == ndkDoubleType ||
			ndk == ndkErrorType ||
			ndk == ndkFloatType ||
			ndk == ndkIntType ||
			ndk == ndkLongType ||
			ndk == ndkLowerBoundedWildcardType ||
			ndk == ndkMethodType ||
			ndk == ndkNoType ||
			ndk == ndkNullType ||
			ndk == ndkPackageType ||
			ndk == ndkParameterizedType ||
			ndk == ndkShortType ||
			ndk == ndkTypeVariable ||
			ndk == ndkUnboundedWildcardType ||
			ndk == ndkUnionType ||
			ndk == ndkUpperBoundedWildcardType ||
			ndk == ndkVoidType;
	}

	/**
	 * Decides whether the node is composite or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is composite.
	 */
	public static boolean getIsComposite(Base node) {
		return !getIsNotComposite(node);
	}

	/**
	 * Decides whether the node is composite or not.
	 * @param node The node whose kind is examined.
	 * @return Returns true if the node is not composite.
	 */
	public static boolean getIsNotComposite(Base node) {
		NodeKind ndk = node.getNodeKind();
		return
			ndk == ndkIdentifier ||
			ndk == ndkBooleanLiteral ||
			ndk == ndkCharacterLiteral ||
			ndk == ndkNullLiteral ||
			ndk == ndkDoubleLiteral ||
			ndk == ndkFloatLiteral ||
			ndk == ndkIntegerLiteral ||
			ndk == ndkLongLiteral ||
			ndk == ndkStringLiteral ||
			ndk == ndkSuper ||
			ndk == ndkThis ||
			ndk == ndkExternalTypeExpression ||
			ndk == ndkPrimitiveTypeExpression ||
			ndk == ndkSimpleTypeExpression ||
			ndk == ndkEmpty ||
			ndk == ndkBreak ||
			ndk == ndkContinue ||
			ndk == ndkModule ||
			ndk == ndkJavadocComment ||
			ndk == ndkBlockComment ||
			ndk == ndkLineComment ||
			ndk == ndkArrayType ||
			ndk == ndkErrorType ||
			ndk == ndkIntersectionType ||
			ndk == ndkMethodType ||
			ndk == ndkModuleType ||
			ndk == ndkNoType ||
			ndk == ndkNullType ||
			ndk == ndkPackageType ||
			ndk == ndkBooleanType ||
			ndk == ndkByteType ||
			ndk == ndkCharType ||
			ndk == ndkDoubleType ||
			ndk == ndkFloatType ||
			ndk == ndkIntType ||
			ndk == ndkLongType ||
			ndk == ndkShortType ||
			ndk == ndkVoidType ||
			ndk == ndkClassType ||
			ndk == ndkParameterizedType ||
			ndk == ndkTypeVariable ||
			ndk == ndkUnionType ||
			ndk == ndkLowerBoundedWildcardType ||
			ndk == ndkUpperBoundedWildcardType ||
			ndk == ndkUnboundedWildcardType;
	}

	/**
	 * Decides whether the 'base' is one of the base kinds (transitive) of 'what'.
	 * @param what The examined node kind.
	 * @param base The base node kind.
	 * @return Returns true if 'base' is a base kind of 'what'.
	 */
	public static boolean getIsBaseClassKind(NodeKind what, NodeKind base) {
		NodeKind type = what;
		while (type != base)
			switch (type) {
				case ndkBase:
					return false;
				case ndkBlockComment:
					type = ndkNonJavadocComment;
					break;
				case ndkComment:
					type = ndkPositionedWithoutComment;
					break;
				case ndkCommentable:
					type = ndkBase;
					break;
				case ndkJavadocComment:
					type = ndkComment;
					break;
				case ndkLineComment:
					type = ndkNonJavadocComment;
					break;
				case ndkNamed:
					type = ndkBase;
					break;
				case ndkNonJavadocComment:
					type = ndkComment;
					break;
				case ndkPositioned:
					return getIsBaseClassKind(ndkCommentable, base) || getIsBaseClassKind(ndkPositionedWithoutComment, base);
				case ndkPositionedWithoutComment:
					type = ndkBase;
					break;
				case ndkAnnotatedTypeExpression:
					type = ndkTypeExpression;
					break;
				case ndkAnnotation:
					type = ndkExpression;
					break;
				case ndkArrayAccess:
					type = ndkBinary;
					break;
				case ndkArrayTypeExpression:
					type = ndkTypeExpression;
					break;
				case ndkAssignment:
					type = ndkBinary;
					break;
				case ndkBinary:
					type = ndkExpression;
					break;
				case ndkBooleanLiteral:
					type = ndkLiteral;
					break;
				case ndkCharacterLiteral:
					type = ndkLiteral;
					break;
				case ndkClassLiteral:
					type = ndkLiteral;
					break;
				case ndkConditional:
					type = ndkExpression;
					break;
				case ndkDoubleLiteral:
					type = ndkNumberLiteral;
					break;
				case ndkErroneous:
					type = ndkExpression;
					break;
				case ndkErroneousTypeExpression:
					type = ndkTypeExpression;
					break;
				case ndkExpression:
					type = ndkPositioned;
					break;
				case ndkExternalTypeExpression:
					type = ndkTypeExpression;
					break;
				case ndkFieldAccess:
					type = ndkBinary;
					break;
				case ndkFloatLiteral:
					type = ndkNumberLiteral;
					break;
				case ndkFunctionalExpression:
					type = ndkPolyExpression;
					break;
				case ndkIdentifier:
					type = ndkExpression;
					break;
				case ndkInfixExpression:
					type = ndkBinary;
					break;
				case ndkInstanceOf:
					type = ndkUnary;
					break;
				case ndkIntegerLiteral:
					type = ndkNumberLiteral;
					break;
				case ndkLambda:
					type = ndkFunctionalExpression;
					break;
				case ndkLiteral:
					type = ndkExpression;
					break;
				case ndkLongLiteral:
					type = ndkNumberLiteral;
					break;
				case ndkMarkerAnnotation:
					type = ndkAnnotation;
					break;
				case ndkMemberReference:
					type = ndkFunctionalExpression;
					break;
				case ndkMethodInvocation:
					type = ndkUnary;
					break;
				case ndkNewArray:
					type = ndkExpression;
					break;
				case ndkNewClass:
					type = ndkExpression;
					break;
				case ndkNormalAnnotation:
					type = ndkAnnotation;
					break;
				case ndkNullLiteral:
					type = ndkLiteral;
					break;
				case ndkNumberLiteral:
					type = ndkLiteral;
					break;
				case ndkParenthesizedExpression:
					type = ndkUnary;
					break;
				case ndkPolyExpression:
					type = ndkExpression;
					break;
				case ndkPostfixExpression:
					type = ndkUnary;
					break;
				case ndkPrefixExpression:
					type = ndkUnary;
					break;
				case ndkPrimitiveTypeExpression:
					type = ndkTypeExpression;
					break;
				case ndkQualifiedTypeExpression:
					type = ndkTypeExpression;
					break;
				case ndkSimpleTypeExpression:
					type = ndkTypeExpression;
					break;
				case ndkSingleElementAnnotation:
					type = ndkAnnotation;
					break;
				case ndkStringLiteral:
					type = ndkLiteral;
					break;
				case ndkSuper:
					type = ndkExpression;
					break;
				case ndkThis:
					type = ndkExpression;
					break;
				case ndkTypeApplyExpression:
					type = ndkTypeExpression;
					break;
				case ndkTypeCast:
					type = ndkUnary;
					break;
				case ndkTypeExpression:
					type = ndkExpression;
					break;
				case ndkTypeIntersectionExpression:
					type = ndkTypeExpression;
					break;
				case ndkTypeUnionExpression:
					type = ndkTypeExpression;
					break;
				case ndkUnary:
					type = ndkExpression;
					break;
				case ndkWildcardExpression:
					type = ndkTypeExpression;
					break;
				case ndkExports:
					type = ndkModuleDirective;
					break;
				case ndkModuleDirective:
					type = ndkPositioned;
					break;
				case ndkOpens:
					type = ndkModuleDirective;
					break;
				case ndkProvides:
					type = ndkModuleDirective;
					break;
				case ndkRequires:
					type = ndkModuleDirective;
					break;
				case ndkUses:
					type = ndkModuleDirective;
					break;
				case ndkAssert:
					type = ndkStatement;
					break;
				case ndkBasicFor:
					type = ndkFor;
					break;
				case ndkBlock:
					type = ndkStatement;
					break;
				case ndkBreak:
					type = ndkJump;
					break;
				case ndkCase:
					type = ndkSwitchLabel;
					break;
				case ndkContinue:
					type = ndkJump;
					break;
				case ndkDefault:
					type = ndkSwitchLabel;
					break;
				case ndkDo:
					type = ndkIteration;
					break;
				case ndkEmpty:
					type = ndkStatement;
					break;
				case ndkEnhancedFor:
					type = ndkFor;
					break;
				case ndkExpressionStatement:
					type = ndkStatement;
					break;
				case ndkFor:
					type = ndkIteration;
					break;
				case ndkHandler:
					type = ndkPositioned;
					break;
				case ndkIf:
					type = ndkSelection;
					break;
				case ndkIteration:
					type = ndkStatement;
					break;
				case ndkJump:
					type = ndkStatement;
					break;
				case ndkLabeledStatement:
					type = ndkStatement;
					break;
				case ndkReturn:
					type = ndkStatement;
					break;
				case ndkSelection:
					type = ndkStatement;
					break;
				case ndkStatement:
					type = ndkPositioned;
					break;
				case ndkSwitch:
					type = ndkSelection;
					break;
				case ndkSwitchLabel:
					type = ndkPositioned;
					break;
				case ndkSynchronized:
					type = ndkStatement;
					break;
				case ndkThrow:
					type = ndkStatement;
					break;
				case ndkTry:
					type = ndkStatement;
					break;
				case ndkWhile:
					type = ndkIteration;
					break;
				case ndkAnnotatedElement:
					type = ndkBase;
					break;
				case ndkAnnotationType:
					type = ndkTypeDeclaration;
					break;
				case ndkAnnotationTypeElement:
					type = ndkMethodDeclaration;
					break;
				case ndkAnonymousClass:
					type = ndkClassDeclaration;
					break;
				case ndkClass:
					type = ndkClassDeclaration;
					break;
				case ndkClassDeclaration:
					type = ndkTypeDeclaration;
					break;
				case ndkClassGeneric:
					return getIsBaseClassKind(ndkClassDeclaration, base) || getIsBaseClassKind(ndkGenericDeclaration, base);
				case ndkCompilationUnit:
					return getIsBaseClassKind(ndkPositionedWithoutComment, base) || getIsBaseClassKind(ndkCommentable, base);
				case ndkDeclaration:
					return getIsBaseClassKind(ndkMember, base) || getIsBaseClassKind(ndkStatement, base);
				case ndkEnum:
					type = ndkTypeDeclaration;
					break;
				case ndkEnumConstant:
					type = ndkVariableDeclaration;
					break;
				case ndkGenericDeclaration:
					type = ndkBase;
					break;
				case ndkImport:
					type = ndkPositioned;
					break;
				case ndkInitializerBlock:
					type = ndkDeclaration;
					break;
				case ndkInstanceInitializerBlock:
					type = ndkInitializerBlock;
					break;
				case ndkInterface:
					type = ndkInterfaceDeclaration;
					break;
				case ndkInterfaceDeclaration:
					type = ndkTypeDeclaration;
					break;
				case ndkInterfaceGeneric:
					return getIsBaseClassKind(ndkInterfaceDeclaration, base) || getIsBaseClassKind(ndkGenericDeclaration, base);
				case ndkMember:
					return getIsBaseClassKind(ndkCommentable, base) || getIsBaseClassKind(ndkAnnotatedElement, base);
				case ndkMethod:
					type = ndkNormalMethod;
					break;
				case ndkMethodDeclaration:
					type = ndkNamedDeclaration;
					break;
				case ndkMethodGeneric:
					return getIsBaseClassKind(ndkNormalMethod, base) || getIsBaseClassKind(ndkGenericDeclaration, base);
				case ndkModule:
					type = ndkNamed;
					break;
				case ndkModuleDeclaration:
					type = ndkPositioned;
					break;
				case ndkNamedDeclaration:
					return getIsBaseClassKind(ndkDeclaration, base) || getIsBaseClassKind(ndkNamed, base);
				case ndkNormalMethod:
					type = ndkMethodDeclaration;
					break;
				case ndkPackage:
					return getIsBaseClassKind(ndkNamed, base) || getIsBaseClassKind(ndkScope, base);
				case ndkPackageDeclaration:
					type = ndkPositioned;
					break;
				case ndkParameter:
					type = ndkVariableDeclaration;
					break;
				case ndkScope:
					type = ndkMember;
					break;
				case ndkStaticInitializerBlock:
					type = ndkInitializerBlock;
					break;
				case ndkTypeDeclaration:
					return getIsBaseClassKind(ndkNamedDeclaration, base) || getIsBaseClassKind(ndkScope, base);
				case ndkTypeParameter:
					return getIsBaseClassKind(ndkPositioned, base) || getIsBaseClassKind(ndkNamed, base);
				case ndkVariable:
					type = ndkVariableDeclaration;
					break;
				case ndkVariableDeclaration:
					type = ndkNamedDeclaration;
					break;
				case ndkArrayType:
					type = ndkType;
					break;
				case ndkBooleanType:
					type = ndkPrimitiveType;
					break;
				case ndkBoundedWildcardType:
					type = ndkWildcardType;
					break;
				case ndkByteType:
					type = ndkPrimitiveType;
					break;
				case ndkCharType:
					type = ndkPrimitiveType;
					break;
				case ndkClassType:
					type = ndkScopedType;
					break;
				case ndkDoubleType:
					type = ndkPrimitiveType;
					break;
				case ndkErrorType:
					type = ndkType;
					break;
				case ndkFloatType:
					type = ndkPrimitiveType;
					break;
				case ndkIntType:
					type = ndkPrimitiveType;
					break;
				case ndkIntersectionType:
					type = ndkType;
					break;
				case ndkLongType:
					type = ndkPrimitiveType;
					break;
				case ndkLowerBoundedWildcardType:
					type = ndkBoundedWildcardType;
					break;
				case ndkMethodType:
					type = ndkType;
					break;
				case ndkModuleType:
					type = ndkType;
					break;
				case ndkNoType:
					type = ndkType;
					break;
				case ndkNullType:
					type = ndkType;
					break;
				case ndkPackageType:
					type = ndkType;
					break;
				case ndkParameterizedType:
					type = ndkScopedType;
					break;
				case ndkPrimitiveType:
					type = ndkType;
					break;
				case ndkScopedType:
					type = ndkType;
					break;
				case ndkShortType:
					type = ndkPrimitiveType;
					break;
				case ndkType:
					type = ndkBase;
					break;
				case ndkTypeVariable:
					type = ndkType;
					break;
				case ndkUnboundedWildcardType:
					type = ndkWildcardType;
					break;
				case ndkUnionType:
					type = ndkType;
					break;
				case ndkUpperBoundedWildcardType:
					type = ndkBoundedWildcardType;
					break;
				case ndkVoidType:
					type = ndkPrimitiveType;
					break;
				case ndkWildcardType:
					type = ndkType;
					break;
			}
		return true;
	}

	/**
	 * Returns true if the node exists and is not filtered out.
	 * @param id The examined node ID.
	 * @return True if the node exists and is not filtered out.
	 */
	public static boolean getIsValid(int id) {
		return id > 1;
	}

}
