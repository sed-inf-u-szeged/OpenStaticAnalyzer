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

import columbus.java.asg.base.BlockComment;
import columbus.java.asg.base.JavadocComment;
import columbus.java.asg.base.LineComment;
import columbus.java.asg.expr.AnnotatedTypeExpression;
import columbus.java.asg.expr.ArrayAccess;
import columbus.java.asg.expr.ArrayTypeExpression;
import columbus.java.asg.expr.Assignment;
import columbus.java.asg.expr.BooleanLiteral;
import columbus.java.asg.expr.CharacterLiteral;
import columbus.java.asg.expr.ClassLiteral;
import columbus.java.asg.expr.Conditional;
import columbus.java.asg.expr.DoubleLiteral;
import columbus.java.asg.expr.Erroneous;
import columbus.java.asg.expr.ErroneousTypeExpression;
import columbus.java.asg.expr.ExternalTypeExpression;
import columbus.java.asg.expr.FieldAccess;
import columbus.java.asg.expr.FloatLiteral;
import columbus.java.asg.expr.Identifier;
import columbus.java.asg.expr.InfixExpression;
import columbus.java.asg.expr.InstanceOf;
import columbus.java.asg.expr.IntegerLiteral;
import columbus.java.asg.expr.Lambda;
import columbus.java.asg.expr.LongLiteral;
import columbus.java.asg.expr.MarkerAnnotation;
import columbus.java.asg.expr.MemberReference;
import columbus.java.asg.expr.MethodInvocation;
import columbus.java.asg.expr.NewArray;
import columbus.java.asg.expr.NewClass;
import columbus.java.asg.expr.NormalAnnotation;
import columbus.java.asg.expr.NullLiteral;
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
import columbus.java.asg.expr.TypeIntersectionExpression;
import columbus.java.asg.expr.TypeUnionExpression;
import columbus.java.asg.expr.WildcardExpression;
import columbus.java.asg.module.Exports;
import columbus.java.asg.module.Opens;
import columbus.java.asg.module.Provides;
import columbus.java.asg.module.Requires;
import columbus.java.asg.module.Uses;
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
import columbus.java.asg.statm.Handler;
import columbus.java.asg.statm.If;
import columbus.java.asg.statm.LabeledStatement;
import columbus.java.asg.statm.Return;
import columbus.java.asg.statm.Switch;
import columbus.java.asg.statm.Synchronized;
import columbus.java.asg.statm.Throw;
import columbus.java.asg.statm.Try;
import columbus.java.asg.statm.While;
import columbus.java.asg.struc.AnnotationType;
import columbus.java.asg.struc.AnnotationTypeElement;
import columbus.java.asg.struc.AnonymousClass;
import columbus.java.asg.struc.Class;
import columbus.java.asg.struc.ClassGeneric;
import columbus.java.asg.struc.CompilationUnit;
import columbus.java.asg.struc.Enum;
import columbus.java.asg.struc.EnumConstant;
import columbus.java.asg.struc.Import;
import columbus.java.asg.struc.InstanceInitializerBlock;
import columbus.java.asg.struc.Interface;
import columbus.java.asg.struc.InterfaceGeneric;
import columbus.java.asg.struc.Method;
import columbus.java.asg.struc.MethodGeneric;
import columbus.java.asg.struc.Module;
import columbus.java.asg.struc.ModuleDeclaration;
import columbus.java.asg.struc.Package;
import columbus.java.asg.struc.PackageDeclaration;
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.struc.StaticInitializerBlock;
import columbus.java.asg.struc.TypeParameter;
import columbus.java.asg.struc.Variable;
import columbus.java.asg.type.ArrayType;
import columbus.java.asg.type.BooleanType;
import columbus.java.asg.type.ByteType;
import columbus.java.asg.type.CharType;
import columbus.java.asg.type.ClassType;
import columbus.java.asg.type.DoubleType;
import columbus.java.asg.type.ErrorType;
import columbus.java.asg.type.FloatType;
import columbus.java.asg.type.IntType;
import columbus.java.asg.type.IntersectionType;
import columbus.java.asg.type.LongType;
import columbus.java.asg.type.LowerBoundedWildcardType;
import columbus.java.asg.type.MethodType;
import columbus.java.asg.type.ModuleType;
import columbus.java.asg.type.NoType;
import columbus.java.asg.type.NullType;
import columbus.java.asg.type.PackageType;
import columbus.java.asg.type.ParameterizedType;
import columbus.java.asg.type.ShortType;
import columbus.java.asg.type.TypeVariable;
import columbus.java.asg.type.UnboundedWildcardType;
import columbus.java.asg.type.UnionType;
import columbus.java.asg.type.UpperBoundedWildcardType;
import columbus.java.asg.type.VoidType;

/**
 * VisitorFilter class filters out nodes from the graph.
 */
public class VisitorFilter extends Visitor {

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BlockComment node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(JavadocComment node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LineComment node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnnotatedTypeExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayAccess node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayTypeExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Assignment node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BooleanLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CharacterLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Conditional node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(DoubleLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Erroneous node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ErroneousTypeExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ExternalTypeExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FieldAccess node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FloatLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Identifier node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InfixExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InstanceOf node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(IntegerLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Lambda node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LongLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MarkerAnnotation node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MemberReference node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodInvocation node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NewArray node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NewClass node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NormalAnnotation node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NullLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ParenthesizedExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PostfixExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PrefixExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PrimitiveTypeExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(QualifiedTypeExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(SimpleTypeExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(SingleElementAnnotation node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(StringLiteral node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Super node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(This node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeApplyExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeCast node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeIntersectionExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeUnionExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(WildcardExpression node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Exports node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Opens node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Provides node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Requires node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Uses node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Assert node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BasicFor node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Block node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Break node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Case node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Continue node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Default node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Do node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Empty node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(EnhancedFor node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ExpressionStatement node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Handler node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(If node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LabeledStatement node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Return node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Switch node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Synchronized node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Throw node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Try node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(While node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnnotationType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnnotationTypeElement node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnonymousClass node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Class node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassGeneric node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CompilationUnit node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Enum node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(EnumConstant node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Import node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InstanceInitializerBlock node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Interface node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InterfaceGeneric node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Method node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodGeneric node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Module node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ModuleDeclaration node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Package node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PackageDeclaration node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Parameter node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(StaticInitializerBlock node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeParameter node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Variable node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BooleanType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ByteType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CharType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(DoubleType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ErrorType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FloatType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(IntType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(IntersectionType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LongType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LowerBoundedWildcardType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ModuleType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NoType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NullType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PackageType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ParameterizedType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ShortType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeVariable node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UnboundedWildcardType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UnionType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UpperBoundedWildcardType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

	/**
	 * Deselects the actual node (and only this).
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(VoidType node, boolean callVirtualBase) {
		node.getFactory().setFilteredThisNodeOnly(node.getId());
	}

}
