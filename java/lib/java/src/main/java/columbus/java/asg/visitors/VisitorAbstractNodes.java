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

package columbus.java.asg.visitors;

import columbus.java.asg.base.Base;
import columbus.java.asg.base.BlockComment;
import columbus.java.asg.base.Comment;
import columbus.java.asg.base.Commentable;
import columbus.java.asg.base.JavadocComment;
import columbus.java.asg.base.LineComment;
import columbus.java.asg.base.Named;
import columbus.java.asg.base.NonJavadocComment;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.base.PositionedWithoutComment;
import columbus.java.asg.expr.Annotation;
import columbus.java.asg.expr.ArrayAccess;
import columbus.java.asg.expr.ArrayTypeExpression;
import columbus.java.asg.expr.Assignment;
import columbus.java.asg.expr.Binary;
import columbus.java.asg.expr.BooleanLiteral;
import columbus.java.asg.expr.CharacterLiteral;
import columbus.java.asg.expr.ClassLiteral;
import columbus.java.asg.expr.Conditional;
import columbus.java.asg.expr.DoubleLiteral;
import columbus.java.asg.expr.Erroneous;
import columbus.java.asg.expr.ErroneousTypeExpression;
import columbus.java.asg.expr.Expression;
import columbus.java.asg.expr.ExternalTypeExpression;
import columbus.java.asg.expr.FieldAccess;
import columbus.java.asg.expr.FloatLiteral;
import columbus.java.asg.expr.Identifier;
import columbus.java.asg.expr.InfixExpression;
import columbus.java.asg.expr.InstanceOf;
import columbus.java.asg.expr.IntegerLiteral;
import columbus.java.asg.expr.Literal;
import columbus.java.asg.expr.LongLiteral;
import columbus.java.asg.expr.MarkerAnnotation;
import columbus.java.asg.expr.MethodInvocation;
import columbus.java.asg.expr.NewArray;
import columbus.java.asg.expr.NewClass;
import columbus.java.asg.expr.NormalAnnotation;
import columbus.java.asg.expr.NullLiteral;
import columbus.java.asg.expr.NumberLiteral;
import columbus.java.asg.expr.ParenthesizedExpression;
import columbus.java.asg.expr.PostfixExpression;
import columbus.java.asg.expr.PrefixExpression;
import columbus.java.asg.expr.PrimitiveTypeExpression;
import columbus.java.asg.expr.QualifiedTypeExpression;
import columbus.java.asg.expr.SimpleTypeExpression;
import columbus.java.asg.expr.SingleElementAnnotation;
import columbus.java.asg.expr.StringLiteral;
import columbus.java.asg.expr.Super;
import columbus.java.asg.expr.This;
import columbus.java.asg.expr.TypeApplyExpression;
import columbus.java.asg.expr.TypeCast;
import columbus.java.asg.expr.TypeExpression;
import columbus.java.asg.expr.TypeUnionExpression;
import columbus.java.asg.expr.Unary;
import columbus.java.asg.expr.WildcardExpression;
import columbus.java.asg.statm.Assert;
import columbus.java.asg.statm.BasicFor;
import columbus.java.asg.statm.Block;
import columbus.java.asg.statm.Break;
import columbus.java.asg.statm.Case;
import columbus.java.asg.statm.Continue;
import columbus.java.asg.statm.Default;
import columbus.java.asg.statm.Do;
import columbus.java.asg.statm.Empty;
import columbus.java.asg.statm.EnhancedFor;
import columbus.java.asg.statm.ExpressionStatement;
import columbus.java.asg.statm.For;
import columbus.java.asg.statm.Handler;
import columbus.java.asg.statm.If;
import columbus.java.asg.statm.Iteration;
import columbus.java.asg.statm.Jump;
import columbus.java.asg.statm.LabeledStatement;
import columbus.java.asg.statm.Return;
import columbus.java.asg.statm.Selection;
import columbus.java.asg.statm.Statement;
import columbus.java.asg.statm.Switch;
import columbus.java.asg.statm.SwitchLabel;
import columbus.java.asg.statm.Synchronized;
import columbus.java.asg.statm.Throw;
import columbus.java.asg.statm.Try;
import columbus.java.asg.statm.While;
import columbus.java.asg.struc.AnnotatedElement;
import columbus.java.asg.struc.AnnotationType;
import columbus.java.asg.struc.AnnotationTypeElement;
import columbus.java.asg.struc.AnonymousClass;
import columbus.java.asg.struc.Class;
import columbus.java.asg.struc.ClassDeclaration;
import columbus.java.asg.struc.ClassGeneric;
import columbus.java.asg.struc.CompilationUnit;
import columbus.java.asg.struc.Declaration;
import columbus.java.asg.struc.Enum;
import columbus.java.asg.struc.EnumConstant;
import columbus.java.asg.struc.GenericDeclaration;
import columbus.java.asg.struc.Import;
import columbus.java.asg.struc.InitializerBlock;
import columbus.java.asg.struc.InstanceInitializerBlock;
import columbus.java.asg.struc.Interface;
import columbus.java.asg.struc.InterfaceDeclaration;
import columbus.java.asg.struc.InterfaceGeneric;
import columbus.java.asg.struc.Member;
import columbus.java.asg.struc.Method;
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.struc.MethodGeneric;
import columbus.java.asg.struc.NamedDeclaration;
import columbus.java.asg.struc.NormalMethod;
import columbus.java.asg.struc.Package;
import columbus.java.asg.struc.PackageDeclaration;
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.struc.Scope;
import columbus.java.asg.struc.StaticInitializerBlock;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.struc.TypeParameter;
import columbus.java.asg.struc.Variable;
import columbus.java.asg.struc.VariableDeclaration;
import columbus.java.asg.type.ArrayType;
import columbus.java.asg.type.BooleanType;
import columbus.java.asg.type.BoundedWildcardType;
import columbus.java.asg.type.ByteType;
import columbus.java.asg.type.CharType;
import columbus.java.asg.type.ClassType;
import columbus.java.asg.type.DoubleType;
import columbus.java.asg.type.ErrorType;
import columbus.java.asg.type.FloatType;
import columbus.java.asg.type.IntType;
import columbus.java.asg.type.LongType;
import columbus.java.asg.type.LowerBoundedWildcardType;
import columbus.java.asg.type.MethodType;
import columbus.java.asg.type.NoType;
import columbus.java.asg.type.NullType;
import columbus.java.asg.type.PackageType;
import columbus.java.asg.type.ParameterizedType;
import columbus.java.asg.type.PrimitiveType;
import columbus.java.asg.type.ScopedType;
import columbus.java.asg.type.ShortType;
import columbus.java.asg.type.Type;
import columbus.java.asg.type.TypeVariable;
import columbus.java.asg.type.UnboundedWildcardType;
import columbus.java.asg.type.UnionType;
import columbus.java.asg.type.UpperBoundedWildcardType;
import columbus.java.asg.type.VoidType;
import columbus.java.asg.type.WildcardType;

/**
 * Visitor class for all edges and nodes (including abstract nodes as well).
 */
public class VisitorAbstractNodes extends Visitor {

	/**
	 * Empty abstract visitor for {@link columbus.java.asg.base.Base Base} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Base node, boolean callVirtualBase) {
	}

	/**
	 * Empty abstract end visitor for {@link columbus.java.asg.base.Base Base} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Base node, boolean callVirtualBase) {
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.BlockComment BlockComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BlockComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		visit((NonJavadocComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.BlockComment BlockComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BlockComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		visitEnd((NonJavadocComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.Comment Comment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Comment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		visit((PositionedWithoutComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.Comment Comment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Comment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		visitEnd((PositionedWithoutComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.Commentable Commentable} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Commentable node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.Commentable Commentable} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Commentable node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(JavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		visit((Comment)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(JavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		visitEnd((Comment)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.LineComment LineComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LineComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		visit((NonJavadocComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.LineComment LineComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LineComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		visitEnd((NonJavadocComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.Named Named} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Named node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.Named Named} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Named node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.NonJavadocComment NonJavadocComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(NonJavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		visit((Comment)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.NonJavadocComment NonJavadocComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(NonJavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		visitEnd((Comment)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.Positioned Positioned} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Positioned node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((PositionedWithoutComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.Positioned Positioned} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Positioned node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((PositionedWithoutComment)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.base.PositionedWithoutComment PositionedWithoutComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(PositionedWithoutComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.base.PositionedWithoutComment PositionedWithoutComment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(PositionedWithoutComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Annotation Annotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Annotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Annotation Annotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Annotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ArrayAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ArrayTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Assignment Assignment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Assignment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Assignment Assignment} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Assignment node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Binary Binary} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Binary node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Binary Binary} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Binary node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BooleanLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BooleanLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(CharacterLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CharacterLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ClassLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Conditional Conditional} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Conditional node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Conditional Conditional} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Conditional node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(DoubleLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(DoubleLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Erroneous Erroneous} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Erroneous node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Erroneous Erroneous} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Erroneous node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ErroneousTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ErroneousTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Expression Expression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Expression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Expression Expression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Expression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ExternalTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ExternalTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(FieldAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FieldAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(FloatLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FloatLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Identifier Identifier} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Identifier node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Identifier Identifier} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Identifier node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Binary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InstanceOf node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InstanceOf node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(IntegerLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(IntegerLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Literal Literal} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Literal node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Literal Literal} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Literal node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LongLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LongLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((NumberLiteral)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MarkerAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Annotation)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MarkerAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Annotation)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MethodInvocation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodInvocation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.NewArray NewArray} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NewArray node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.NewArray NewArray} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NewArray node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.NewClass NewClass} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NewClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.NewClass NewClass} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NewClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NormalAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Annotation)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NormalAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Annotation)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NullLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NullLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.NumberLiteral NumberLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(NumberLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.NumberLiteral NumberLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(NumberLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ParenthesizedExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ParenthesizedExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PostfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PostfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PrefixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PrefixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PrimitiveTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PrimitiveTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(QualifiedTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(QualifiedTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(SimpleTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(SimpleTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(SingleElementAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Annotation)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(SingleElementAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Annotation)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(StringLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(StringLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Literal)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Super Super} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Super node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Super Super} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Super node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.This This} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(This node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.This This} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(This node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeApplyExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeApplyExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeCast TypeCast} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeCast node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeCast TypeCast} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeCast node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Unary)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeExpression TypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(TypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeExpression TypeExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(TypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeUnionExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeUnionExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.Unary Unary} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Unary node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.Unary Unary} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Unary node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Expression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(WildcardExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(WildcardExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((TypeExpression)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Assert Assert} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Assert node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Assert Assert} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Assert node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.BasicFor BasicFor} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BasicFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((For)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.BasicFor BasicFor} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BasicFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((For)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Block Block} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Block node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Block Block} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Block node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Break Break} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Break node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Jump)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Break Break} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Break node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Jump)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Case Case} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Case node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((SwitchLabel)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Case Case} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Case node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((SwitchLabel)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Continue Continue} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Continue node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Jump)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Continue Continue} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Continue node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Jump)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Default Default} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Default node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((SwitchLabel)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Default Default} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Default node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((SwitchLabel)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Do Do} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Do node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Iteration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Do Do} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Do node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Iteration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Empty Empty} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Empty node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Empty Empty} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Empty node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(EnhancedFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((For)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(EnhancedFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((For)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ExpressionStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ExpressionStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.For For} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(For node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Iteration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.For For} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(For node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Iteration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Handler Handler} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Handler node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Handler Handler} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Handler node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.If If} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(If node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Selection)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.If If} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(If node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Selection)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Iteration Iteration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Iteration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Iteration Iteration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Iteration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Jump Jump} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Jump node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Jump Jump} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Jump node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LabeledStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LabeledStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Return Return} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Return node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Return Return} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Return node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Selection Selection} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Selection node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Selection Selection} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Selection node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Statement Statement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Statement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Statement Statement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Statement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Switch Switch} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Switch node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Selection)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Switch Switch} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Switch node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Selection)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.SwitchLabel SwitchLabel} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(SwitchLabel node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.SwitchLabel SwitchLabel} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(SwitchLabel node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Synchronized Synchronized} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Synchronized node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Synchronized Synchronized} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Synchronized node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Throw Throw} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Throw node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Throw Throw} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Throw node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.Try Try} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Try node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.Try Try} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Try node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.statm.While While} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(While node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Iteration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.statm.While While} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(While node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Iteration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.AnnotatedElement AnnotatedElement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(AnnotatedElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.AnnotatedElement AnnotatedElement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(AnnotatedElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(AnnotationType node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnnotationType node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(AnnotationTypeElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((MethodDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnnotationTypeElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((MethodDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(AnonymousClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((ClassDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnonymousClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((ClassDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Class Class} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Class node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((ClassDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Class Class} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Class node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((ClassDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.ClassDeclaration ClassDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(ClassDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.ClassDeclaration ClassDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(ClassDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ClassGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((ClassDeclaration)node, false);
		visit((GenericDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((ClassDeclaration)node, false);
		visitEnd((GenericDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(CompilationUnit node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		visit((PositionedWithoutComment)node, false);
		visit((Commentable)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CompilationUnit node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		visitEnd((PositionedWithoutComment)node, false);
		visitEnd((Commentable)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Declaration Declaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Declaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Declaration Declaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Declaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((Statement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Enum Enum} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Enum node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Enum Enum} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Enum node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(EnumConstant node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((VariableDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(EnumConstant node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((VariableDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.GenericDeclaration GenericDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(GenericDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.GenericDeclaration GenericDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(GenericDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Import Import} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Import node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Import Import} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Import node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.InitializerBlock InitializerBlock} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(InitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((Declaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.InitializerBlock InitializerBlock} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(InitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((Declaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InstanceInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((InitializerBlock)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InstanceInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((InitializerBlock)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Interface Interface} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Interface node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((InterfaceDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Interface Interface} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Interface node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((InterfaceDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.InterfaceDeclaration InterfaceDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(InterfaceDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.InterfaceDeclaration InterfaceDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(InterfaceDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((TypeDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InterfaceGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((InterfaceDeclaration)node, false);
		visit((GenericDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InterfaceGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((InterfaceDeclaration)node, false);
		visitEnd((GenericDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Member Member} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Member node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((AnnotatedElement)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Member Member} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Member node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((AnnotatedElement)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Method Method} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Method node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((NormalMethod)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Method Method} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Method node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((NormalMethod)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(MethodDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((NamedDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(MethodDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((NamedDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MethodGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((NormalMethod)node, false);
		visit((GenericDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((NormalMethod)node, false);
		visitEnd((GenericDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.NamedDeclaration NamedDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(NamedDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((Declaration)node, false);
		visit((Named)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.NamedDeclaration NamedDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(NamedDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((Declaration)node, false);
		visitEnd((Named)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.NormalMethod NormalMethod} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(NormalMethod node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((MethodDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.NormalMethod NormalMethod} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(NormalMethod node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((MethodDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Package Package} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Package node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((Named)node, false);
		visit((Scope)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Package Package} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Package node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((Named)node, false);
		visitEnd((Scope)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PackageDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PackageDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Positioned)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Parameter Parameter} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Parameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((VariableDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Parameter Parameter} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Parameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((VariableDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Scope Scope} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Scope node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Scope Scope} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Scope node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(StaticInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((InitializerBlock)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(StaticInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((InitializerBlock)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(TypeDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((NamedDeclaration)node, false);
		visit((Scope)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(TypeDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((NamedDeclaration)node, false);
		visitEnd((Scope)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeParameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		visit((Positioned)node, false);
		visit((Named)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeParameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		visitEnd((Positioned)node, false);
		visitEnd((Named)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.Variable Variable} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Variable node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((VariableDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.Variable Variable} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Variable node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((VariableDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.struc.VariableDeclaration VariableDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(VariableDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visit((Base)node, false);
		if (callVirtualBase)
			visit((Commentable)node, false);
		if (callVirtualBase)
			visit((Member)node, false);
		visit((NamedDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.struc.VariableDeclaration VariableDeclaration} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(VariableDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			visitEnd((Base)node, false);
		if (callVirtualBase)
			visitEnd((Commentable)node, false);
		if (callVirtualBase)
			visitEnd((Member)node, false);
		visitEnd((NamedDeclaration)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.ArrayType ArrayType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ArrayType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.ArrayType ArrayType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.BooleanType BooleanType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BooleanType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.BooleanType BooleanType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BooleanType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.BoundedWildcardType BoundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(BoundedWildcardType node, boolean callVirtualBase) {
		visit((WildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.BoundedWildcardType BoundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(BoundedWildcardType node, boolean callVirtualBase) {
		visitEnd((WildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.ByteType ByteType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ByteType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.ByteType ByteType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ByteType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.CharType CharType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(CharType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.CharType CharType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CharType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.ClassType ClassType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ClassType node, boolean callVirtualBase) {
		visit((ScopedType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.ClassType ClassType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassType node, boolean callVirtualBase) {
		visitEnd((ScopedType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.DoubleType DoubleType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(DoubleType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.DoubleType DoubleType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(DoubleType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.ErrorType ErrorType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ErrorType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.ErrorType ErrorType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ErrorType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.FloatType FloatType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(FloatType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.FloatType FloatType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FloatType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.IntType IntType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(IntType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.IntType IntType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(IntType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.LongType LongType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LongType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.LongType LongType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LongType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LowerBoundedWildcardType node, boolean callVirtualBase) {
		visit((BoundedWildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LowerBoundedWildcardType node, boolean callVirtualBase) {
		visitEnd((BoundedWildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.MethodType MethodType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MethodType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.MethodType MethodType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.NoType NoType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NoType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.NoType NoType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NoType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.NullType NullType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NullType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.NullType NullType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NullType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.PackageType PackageType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PackageType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.PackageType PackageType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PackageType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ParameterizedType node, boolean callVirtualBase) {
		visit((ScopedType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ParameterizedType node, boolean callVirtualBase) {
		visitEnd((ScopedType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.PrimitiveType PrimitiveType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(PrimitiveType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.PrimitiveType PrimitiveType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(PrimitiveType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.ScopedType ScopedType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(ScopedType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.ScopedType ScopedType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(ScopedType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.ShortType ShortType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ShortType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.ShortType ShortType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ShortType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.Type Type} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(Type node, boolean callVirtualBase) {
		visit((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.Type Type} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(Type node, boolean callVirtualBase) {
		visitEnd((Base)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeVariable node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeVariable node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(UnboundedWildcardType node, boolean callVirtualBase) {
		visit((WildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UnboundedWildcardType node, boolean callVirtualBase) {
		visitEnd((WildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.UnionType UnionType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(UnionType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.UnionType UnionType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UnionType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(UpperBoundedWildcardType node, boolean callVirtualBase) {
		visit((BoundedWildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UpperBoundedWildcardType node, boolean callVirtualBase) {
		visitEnd((BoundedWildcardType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.VoidType VoidType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(VoidType node, boolean callVirtualBase) {
		visit((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.VoidType VoidType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(VoidType node, boolean callVirtualBase) {
		visitEnd((PrimitiveType)node, false);
	}

	/**
	 * Abstract visitor, which calls the visitor of the base class(es) of the {@link columbus.java.asg.type.WildcardType WildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit(WildcardType node, boolean callVirtualBase) {
		visit((Type)node, false);
	}

	/**
	 * Abstract visitor, which calls the end visitor of the base class(es) of the {@link columbus.java.asg.type.WildcardType WildcardType} node.
	 * @param node            The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(WildcardType node, boolean callVirtualBase) {
		visitEnd((Type)node, false);
	}

}
