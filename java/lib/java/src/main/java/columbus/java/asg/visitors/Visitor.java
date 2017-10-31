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

package columbus.java.asg.visitors;

/**
 * Visitor for each non-abstract nodes and all edges of the graph.
 */
public class Visitor {

	/** Stores the depth position. */
	protected int depth;

	/**
	 * Constructor for Visitor.
	 */
	public Visitor() {
	}

	/**
	 * Gives back the the actual position's depth.
	 * @return The depth of the actual position.
	 */
	public int getDepth() {
		return depth;
	}

	/**
	 * Increasing the depth by one.
	 */
	public void incDepth() {
		++depth;
	}

	/**
	 * Decreasing the depth by one.
	 */
	public void decDepth() {
		--depth;
	}

	/**
	 * This method is called before the beginning of visiting process.
	 */
	public void beginVisit() {
	}

	/**
	 * This method is called when the visiting process has finished.
	 */
	public void finishVisit() {
	}

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.base.BlockComment BlockComment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.base.BlockComment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.base.BlockComment BlockComment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.base.BlockComment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.base.JavadocComment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.base.JavadocComment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.base.LineComment LineComment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.base.LineComment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.base.LineComment LineComment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.base.LineComment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.ArrayAccess node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.ArrayAccess node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.ArrayTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.ArrayTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.Assignment Assignment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.Assignment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.Assignment Assignment} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.Assignment node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.BooleanLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.BooleanLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.CharacterLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.CharacterLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.ClassLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.ClassLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.Conditional Conditional} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.Conditional node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.Conditional Conditional} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.Conditional node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.DoubleLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.DoubleLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.Erroneous Erroneous} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.Erroneous node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.Erroneous Erroneous} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.Erroneous node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.ErroneousTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.ErroneousTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.ExternalTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.ExternalTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.FieldAccess node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.FieldAccess node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.FloatLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.FloatLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.Identifier Identifier} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.Identifier node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.Identifier Identifier} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.Identifier node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.InfixExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.InfixExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.InstanceOf node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.InstanceOf node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.IntegerLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.IntegerLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.LongLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.LongLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.MarkerAnnotation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.MarkerAnnotation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.MethodInvocation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.MethodInvocation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.NewArray NewArray} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.NewArray node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.NewArray NewArray} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.NewArray node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.NewClass NewClass} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.NewClass node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.NewClass NewClass} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.NewClass node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.NormalAnnotation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.NormalAnnotation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.NullLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.NullLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.ParenthesizedExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.ParenthesizedExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.PostfixExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.PostfixExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.PrefixExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.PrefixExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.PrimitiveTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.PrimitiveTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.QualifiedTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.QualifiedTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.SimpleTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.SimpleTypeExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.SingleElementAnnotation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.SingleElementAnnotation node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.StringLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.StringLiteral node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.Super Super} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.Super node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.Super Super} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.Super node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.This This} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.This node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.This This} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.This node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.TypeApplyExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.TypeApplyExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.TypeCast TypeCast} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.TypeCast node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.TypeCast TypeCast} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.TypeCast node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.TypeUnionExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.TypeUnionExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.expr.WildcardExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.expr.WildcardExpression node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Assert Assert} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Assert node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Assert Assert} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Assert node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.BasicFor BasicFor} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.BasicFor node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.BasicFor BasicFor} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.BasicFor node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Block Block} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Block node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Block Block} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Block node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Break Break} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Break node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Break Break} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Break node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Case Case} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Case node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Case Case} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Case node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Continue Continue} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Continue node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Continue Continue} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Continue node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Default Default} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Default node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Default Default} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Default node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Do Do} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Do node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Do Do} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Do node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Empty Empty} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Empty node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Empty Empty} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Empty node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.EnhancedFor node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.EnhancedFor node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.ExpressionStatement node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.ExpressionStatement node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Handler Handler} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Handler node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Handler Handler} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Handler node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.If If} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.If node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.If If} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.If node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.LabeledStatement node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.LabeledStatement node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Return Return} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Return node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Return Return} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Return node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Switch Switch} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Switch node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Switch Switch} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Switch node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Synchronized Synchronized} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Synchronized node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Synchronized Synchronized} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Synchronized node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Throw Throw} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Throw node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Throw Throw} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Throw node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.Try Try} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.Try node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.Try Try} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.Try node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.statm.While While} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.statm.While node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.statm.While While} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.statm.While node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.AnnotationType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.AnnotationType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.AnnotationTypeElement node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.AnnotationTypeElement node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.AnonymousClass node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.AnonymousClass node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Class Class} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Class node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Class Class} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Class node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.ClassGeneric node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.ClassGeneric node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.CompilationUnit node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.CompilationUnit node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Enum Enum} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Enum node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Enum Enum} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Enum node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.EnumConstant node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.EnumConstant node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Import Import} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Import node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Import Import} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Import node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.InstanceInitializerBlock node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.InstanceInitializerBlock node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Interface Interface} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Interface node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Interface Interface} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Interface node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.InterfaceGeneric node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.InterfaceGeneric node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Method Method} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Method node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Method Method} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Method node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.MethodGeneric node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.MethodGeneric node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Package Package} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Package node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Package Package} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Package node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.PackageDeclaration node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.PackageDeclaration node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Parameter Parameter} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Parameter node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Parameter Parameter} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Parameter node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.StaticInitializerBlock node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.StaticInitializerBlock node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.TypeParameter node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.TypeParameter node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.struc.Variable Variable} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.struc.Variable node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.struc.Variable Variable} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.struc.Variable node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.ArrayType ArrayType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.ArrayType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.ArrayType ArrayType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.ArrayType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.BooleanType BooleanType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.BooleanType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.BooleanType BooleanType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.BooleanType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.ByteType ByteType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.ByteType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.ByteType ByteType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.ByteType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.CharType CharType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.CharType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.CharType CharType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.CharType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.ClassType ClassType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.ClassType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.ClassType ClassType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.ClassType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.DoubleType DoubleType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.DoubleType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.DoubleType DoubleType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.DoubleType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.ErrorType ErrorType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.ErrorType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.ErrorType ErrorType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.ErrorType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.FloatType FloatType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.FloatType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.FloatType FloatType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.FloatType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.IntType IntType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.IntType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.IntType IntType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.IntType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.LongType LongType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.LongType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.LongType LongType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.LongType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.LowerBoundedWildcardType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.LowerBoundedWildcardType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.MethodType MethodType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.MethodType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.MethodType MethodType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.MethodType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.NoType NoType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.NoType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.NoType NoType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.NoType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.NullType NullType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.NullType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.NullType NullType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.NullType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.PackageType PackageType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.PackageType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.PackageType PackageType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.PackageType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.ParameterizedType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.ParameterizedType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.ShortType ShortType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.ShortType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.ShortType ShortType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.ShortType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.TypeVariable node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.TypeVariable node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.UnboundedWildcardType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.UnboundedWildcardType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.UnionType UnionType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.UnionType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.UnionType UnionType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.UnionType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.UpperBoundedWildcardType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.UpperBoundedWildcardType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the beginning of the {@link columbus.java.asg.type.VoidType VoidType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visit   (columbus.java.asg.type.VoidType node, boolean callVirtualBase) { }

	/**
	 * Visitor which is called at the end of the {@link columbus.java.asg.type.VoidType VoidType} node visiting.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	public void visitEnd(columbus.java.asg.type.VoidType node, boolean callVirtualBase) { }

	/**
	 * Edge visitor for 'comments' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitCommentable_Comments   (columbus.java.asg.base.Commentable begin, columbus.java.asg.base.Comment end) { }

	/**
	 * Edge end visitor for 'comments' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndCommentable_Comments(columbus.java.asg.base.Commentable begin, columbus.java.asg.base.Comment end) { }

	/**
	 * Edge visitor for 'hasAnnotationName' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitAnnotation_HasAnnotationName   (columbus.java.asg.expr.Annotation begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasAnnotationName' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndAnnotation_HasAnnotationName(columbus.java.asg.expr.Annotation begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasComponentType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitArrayTypeExpression_HasComponentType   (columbus.java.asg.expr.ArrayTypeExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasComponentType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndArrayTypeExpression_HasComponentType(columbus.java.asg.expr.ArrayTypeExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasLeftOperand' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitBinary_HasLeftOperand   (columbus.java.asg.expr.Binary begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasLeftOperand' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndBinary_HasLeftOperand(columbus.java.asg.expr.Binary begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasRightOperand' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitBinary_HasRightOperand   (columbus.java.asg.expr.Binary begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasRightOperand' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndBinary_HasRightOperand(columbus.java.asg.expr.Binary begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasComponentType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitClassLiteral_HasComponentType   (columbus.java.asg.expr.ClassLiteral begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasComponentType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndClassLiteral_HasComponentType(columbus.java.asg.expr.ClassLiteral begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasCondition' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitConditional_HasCondition   (columbus.java.asg.expr.Conditional begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasCondition' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndConditional_HasCondition(columbus.java.asg.expr.Conditional begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasTrueExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitConditional_HasTrueExpression   (columbus.java.asg.expr.Conditional begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasTrueExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndConditional_HasTrueExpression(columbus.java.asg.expr.Conditional begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasFalseExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitConditional_HasFalseExpression   (columbus.java.asg.expr.Conditional begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasFalseExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndConditional_HasFalseExpression(columbus.java.asg.expr.Conditional begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasErrors' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitErroneous_HasErrors   (columbus.java.asg.expr.Erroneous begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge end visitor for 'hasErrors' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndErroneous_HasErrors(columbus.java.asg.expr.Erroneous begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge visitor for 'hasErrors' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitErroneousTypeExpression_HasErrors   (columbus.java.asg.expr.ErroneousTypeExpression begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge end visitor for 'hasErrors' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndErroneousTypeExpression_HasErrors(columbus.java.asg.expr.ErroneousTypeExpression begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge visitor for 'type' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitExpression_Type   (columbus.java.asg.expr.Expression begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'type' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndExpression_Type(columbus.java.asg.expr.Expression begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'refersTo' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitIdentifier_RefersTo   (columbus.java.asg.expr.Identifier begin, columbus.java.asg.base.Named end) { }

	/**
	 * Edge end visitor for 'refersTo' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndIdentifier_RefersTo(columbus.java.asg.expr.Identifier begin, columbus.java.asg.base.Named end) { }

	/**
	 * Edge visitor for 'hasTypeOperand' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitInstanceOf_HasTypeOperand   (columbus.java.asg.expr.InstanceOf begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasTypeOperand' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndInstanceOf_HasTypeOperand(columbus.java.asg.expr.InstanceOf begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasTypeArguments' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodInvocation_HasTypeArguments   (columbus.java.asg.expr.MethodInvocation begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasTypeArguments' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodInvocation_HasTypeArguments(columbus.java.asg.expr.MethodInvocation begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasArguments' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodInvocation_HasArguments   (columbus.java.asg.expr.MethodInvocation begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasArguments' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodInvocation_HasArguments(columbus.java.asg.expr.MethodInvocation begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'invokes' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodInvocation_Invokes   (columbus.java.asg.expr.MethodInvocation begin, columbus.java.asg.struc.MethodDeclaration end) { }

	/**
	 * Edge end visitor for 'invokes' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodInvocation_Invokes(columbus.java.asg.expr.MethodInvocation begin, columbus.java.asg.struc.MethodDeclaration end) { }

	/**
	 * Edge visitor for 'hasComponentType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewArray_HasComponentType   (columbus.java.asg.expr.NewArray begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasComponentType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewArray_HasComponentType(columbus.java.asg.expr.NewArray begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasDimensions' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewArray_HasDimensions   (columbus.java.asg.expr.NewArray begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasDimensions' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewArray_HasDimensions(columbus.java.asg.expr.NewArray begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasInitializers' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewArray_HasInitializers   (columbus.java.asg.expr.NewArray begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasInitializers' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewArray_HasInitializers(columbus.java.asg.expr.NewArray begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasEnclosingExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewClass_HasEnclosingExpression   (columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasEnclosingExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewClass_HasEnclosingExpression(columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasTypeArguments' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewClass_HasTypeArguments   (columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasTypeArguments' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewClass_HasTypeArguments(columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasTypeName' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewClass_HasTypeName   (columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasTypeName' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewClass_HasTypeName(columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasArguments' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewClass_HasArguments   (columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasArguments' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewClass_HasArguments(columbus.java.asg.expr.NewClass begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasAnonymousClass' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewClass_HasAnonymousClass   (columbus.java.asg.expr.NewClass begin, columbus.java.asg.struc.AnonymousClass end) { }

	/**
	 * Edge end visitor for 'hasAnonymousClass' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewClass_HasAnonymousClass(columbus.java.asg.expr.NewClass begin, columbus.java.asg.struc.AnonymousClass end) { }

	/**
	 * Edge visitor for 'constructor' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNewClass_Constructor   (columbus.java.asg.expr.NewClass begin, columbus.java.asg.struc.NormalMethod end) { }

	/**
	 * Edge end visitor for 'constructor' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNewClass_Constructor(columbus.java.asg.expr.NewClass begin, columbus.java.asg.struc.NormalMethod end) { }

	/**
	 * Edge visitor for 'hasArguments' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNormalAnnotation_HasArguments   (columbus.java.asg.expr.NormalAnnotation begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasArguments' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNormalAnnotation_HasArguments(columbus.java.asg.expr.NormalAnnotation begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasQualifierType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitQualifiedTypeExpression_HasQualifierType   (columbus.java.asg.expr.QualifiedTypeExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasQualifierType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndQualifiedTypeExpression_HasQualifierType(columbus.java.asg.expr.QualifiedTypeExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasSimpleType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitQualifiedTypeExpression_HasSimpleType   (columbus.java.asg.expr.QualifiedTypeExpression begin, columbus.java.asg.expr.SimpleTypeExpression end) { }

	/**
	 * Edge end visitor for 'hasSimpleType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndQualifiedTypeExpression_HasSimpleType(columbus.java.asg.expr.QualifiedTypeExpression begin, columbus.java.asg.expr.SimpleTypeExpression end) { }

	/**
	 * Edge visitor for 'hasArgument' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitSingleElementAnnotation_HasArgument   (columbus.java.asg.expr.SingleElementAnnotation begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasArgument' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndSingleElementAnnotation_HasArgument(columbus.java.asg.expr.SingleElementAnnotation begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasRawType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeApplyExpression_HasRawType   (columbus.java.asg.expr.TypeApplyExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasRawType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeApplyExpression_HasRawType(columbus.java.asg.expr.TypeApplyExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasTypeArguments' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeApplyExpression_HasTypeArguments   (columbus.java.asg.expr.TypeApplyExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasTypeArguments' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeApplyExpression_HasTypeArguments(columbus.java.asg.expr.TypeApplyExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasTypeOperand' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeCast_HasTypeOperand   (columbus.java.asg.expr.TypeCast begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasTypeOperand' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeCast_HasTypeOperand(columbus.java.asg.expr.TypeCast begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasAlternatives' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeUnionExpression_HasAlternatives   (columbus.java.asg.expr.TypeUnionExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasAlternatives' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeUnionExpression_HasAlternatives(columbus.java.asg.expr.TypeUnionExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasOperand' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitUnary_HasOperand   (columbus.java.asg.expr.Unary begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasOperand' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndUnary_HasOperand(columbus.java.asg.expr.Unary begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasBound' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitWildcardExpression_HasBound   (columbus.java.asg.expr.WildcardExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasBound' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndWildcardExpression_HasBound(columbus.java.asg.expr.WildcardExpression begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasCondition' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitAssert_HasCondition   (columbus.java.asg.statm.Assert begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasCondition' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndAssert_HasCondition(columbus.java.asg.statm.Assert begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasDetail' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitAssert_HasDetail   (columbus.java.asg.statm.Assert begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasDetail' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndAssert_HasDetail(columbus.java.asg.statm.Assert begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasInitializers' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitBasicFor_HasInitializers   (columbus.java.asg.statm.BasicFor begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasInitializers' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndBasicFor_HasInitializers(columbus.java.asg.statm.BasicFor begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasCondition' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitBasicFor_HasCondition   (columbus.java.asg.statm.BasicFor begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasCondition' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndBasicFor_HasCondition(columbus.java.asg.statm.BasicFor begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasUpdates' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitBasicFor_HasUpdates   (columbus.java.asg.statm.BasicFor begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasUpdates' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndBasicFor_HasUpdates(columbus.java.asg.statm.BasicFor begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasStatements' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitBlock_HasStatements   (columbus.java.asg.statm.Block begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasStatements' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndBlock_HasStatements(columbus.java.asg.statm.Block begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitCase_HasExpression   (columbus.java.asg.statm.Case begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndCase_HasExpression(columbus.java.asg.statm.Case begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasCondition' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitDo_HasCondition   (columbus.java.asg.statm.Do begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasCondition' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndDo_HasCondition(columbus.java.asg.statm.Do begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasParameter' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEnhancedFor_HasParameter   (columbus.java.asg.statm.EnhancedFor begin, columbus.java.asg.struc.Parameter end) { }

	/**
	 * Edge end visitor for 'hasParameter' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndEnhancedFor_HasParameter(columbus.java.asg.statm.EnhancedFor begin, columbus.java.asg.struc.Parameter end) { }

	/**
	 * Edge visitor for 'hasExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEnhancedFor_HasExpression   (columbus.java.asg.statm.EnhancedFor begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndEnhancedFor_HasExpression(columbus.java.asg.statm.EnhancedFor begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitExpressionStatement_HasExpression   (columbus.java.asg.statm.ExpressionStatement begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndExpressionStatement_HasExpression(columbus.java.asg.statm.ExpressionStatement begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasParameter' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitHandler_HasParameter   (columbus.java.asg.statm.Handler begin, columbus.java.asg.struc.Parameter end) { }

	/**
	 * Edge end visitor for 'hasParameter' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndHandler_HasParameter(columbus.java.asg.statm.Handler begin, columbus.java.asg.struc.Parameter end) { }

	/**
	 * Edge visitor for 'hasBlock' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitHandler_HasBlock   (columbus.java.asg.statm.Handler begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge end visitor for 'hasBlock' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndHandler_HasBlock(columbus.java.asg.statm.Handler begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge visitor for 'hasSubstatement' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitIf_HasSubstatement   (columbus.java.asg.statm.If begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasSubstatement' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndIf_HasSubstatement(columbus.java.asg.statm.If begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasFalseSubstatement' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitIf_HasFalseSubstatement   (columbus.java.asg.statm.If begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasFalseSubstatement' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndIf_HasFalseSubstatement(columbus.java.asg.statm.If begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasSubstatement' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitIteration_HasSubstatement   (columbus.java.asg.statm.Iteration begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasSubstatement' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndIteration_HasSubstatement(columbus.java.asg.statm.Iteration begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'target' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitJump_Target   (columbus.java.asg.statm.Jump begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'target' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndJump_Target(columbus.java.asg.statm.Jump begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasStatement' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitLabeledStatement_HasStatement   (columbus.java.asg.statm.LabeledStatement begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasStatement' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndLabeledStatement_HasStatement(columbus.java.asg.statm.LabeledStatement begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitReturn_HasExpression   (columbus.java.asg.statm.Return begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndReturn_HasExpression(columbus.java.asg.statm.Return begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasCondition' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitSelection_HasCondition   (columbus.java.asg.statm.Selection begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasCondition' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndSelection_HasCondition(columbus.java.asg.statm.Selection begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasCases' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitSwitch_HasCases   (columbus.java.asg.statm.Switch begin, columbus.java.asg.statm.SwitchLabel end) { }

	/**
	 * Edge end visitor for 'hasCases' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndSwitch_HasCases(columbus.java.asg.statm.Switch begin, columbus.java.asg.statm.SwitchLabel end) { }

	/**
	 * Edge visitor for 'hasStatements' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitSwitchLabel_HasStatements   (columbus.java.asg.statm.SwitchLabel begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge end visitor for 'hasStatements' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndSwitchLabel_HasStatements(columbus.java.asg.statm.SwitchLabel begin, columbus.java.asg.statm.Statement end) { }

	/**
	 * Edge visitor for 'hasLock' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitSynchronized_HasLock   (columbus.java.asg.statm.Synchronized begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasLock' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndSynchronized_HasLock(columbus.java.asg.statm.Synchronized begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasBlock' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitSynchronized_HasBlock   (columbus.java.asg.statm.Synchronized begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge end visitor for 'hasBlock' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndSynchronized_HasBlock(columbus.java.asg.statm.Synchronized begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge visitor for 'hasExpression' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitThrow_HasExpression   (columbus.java.asg.statm.Throw begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasExpression' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndThrow_HasExpression(columbus.java.asg.statm.Throw begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasResources' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTry_HasResources   (columbus.java.asg.statm.Try begin, columbus.java.asg.struc.Variable end) { }

	/**
	 * Edge end visitor for 'hasResources' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTry_HasResources(columbus.java.asg.statm.Try begin, columbus.java.asg.struc.Variable end) { }

	/**
	 * Edge visitor for 'hasBlock' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTry_HasBlock   (columbus.java.asg.statm.Try begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge end visitor for 'hasBlock' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTry_HasBlock(columbus.java.asg.statm.Try begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge visitor for 'hasHandlers' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTry_HasHandlers   (columbus.java.asg.statm.Try begin, columbus.java.asg.statm.Handler end) { }

	/**
	 * Edge end visitor for 'hasHandlers' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTry_HasHandlers(columbus.java.asg.statm.Try begin, columbus.java.asg.statm.Handler end) { }

	/**
	 * Edge visitor for 'hasFinallyBlock' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTry_HasFinallyBlock   (columbus.java.asg.statm.Try begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge end visitor for 'hasFinallyBlock' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTry_HasFinallyBlock(columbus.java.asg.statm.Try begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge visitor for 'hasCondition' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitWhile_HasCondition   (columbus.java.asg.statm.While begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasCondition' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndWhile_HasCondition(columbus.java.asg.statm.While begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasAnnotations' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitAnnotatedElement_HasAnnotations   (columbus.java.asg.struc.AnnotatedElement begin, columbus.java.asg.expr.Annotation end) { }

	/**
	 * Edge end visitor for 'hasAnnotations' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndAnnotatedElement_HasAnnotations(columbus.java.asg.struc.AnnotatedElement begin, columbus.java.asg.expr.Annotation end) { }

	/**
	 * Edge visitor for 'hasDefaultValue' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitAnnotationTypeElement_HasDefaultValue   (columbus.java.asg.struc.AnnotationTypeElement begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasDefaultValue' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndAnnotationTypeElement_HasDefaultValue(columbus.java.asg.struc.AnnotationTypeElement begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasPackageDeclaration' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitCompilationUnit_HasPackageDeclaration   (columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.struc.PackageDeclaration end) { }

	/**
	 * Edge end visitor for 'hasPackageDeclaration' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndCompilationUnit_HasPackageDeclaration(columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.struc.PackageDeclaration end) { }

	/**
	 * Edge visitor for 'hasImports' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitCompilationUnit_HasImports   (columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.struc.Import end) { }

	/**
	 * Edge end visitor for 'hasImports' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndCompilationUnit_HasImports(columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.struc.Import end) { }

	/**
	 * Edge visitor for 'typeDeclarations' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitCompilationUnit_TypeDeclarations   (columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.struc.TypeDeclaration end) { }

	/**
	 * Edge end visitor for 'typeDeclarations' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndCompilationUnit_TypeDeclarations(columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.struc.TypeDeclaration end) { }

	/**
	 * Edge visitor for 'hasOthers' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitCompilationUnit_HasOthers   (columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge end visitor for 'hasOthers' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndCompilationUnit_HasOthers(columbus.java.asg.struc.CompilationUnit begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge visitor for 'hasNewClass' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEnumConstant_HasNewClass   (columbus.java.asg.struc.EnumConstant begin, columbus.java.asg.expr.NewClass end) { }

	/**
	 * Edge end visitor for 'hasNewClass' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndEnumConstant_HasNewClass(columbus.java.asg.struc.EnumConstant begin, columbus.java.asg.expr.NewClass end) { }

	/**
	 * Edge visitor for 'hasTypeParameters' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitGenericDeclaration_HasTypeParameters   (columbus.java.asg.struc.GenericDeclaration begin, columbus.java.asg.struc.TypeParameter end) { }

	/**
	 * Edge end visitor for 'hasTypeParameters' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndGenericDeclaration_HasTypeParameters(columbus.java.asg.struc.GenericDeclaration begin, columbus.java.asg.struc.TypeParameter end) { }

	/**
	 * Edge visitor for 'hasTarget' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitImport_HasTarget   (columbus.java.asg.struc.Import begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasTarget' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndImport_HasTarget(columbus.java.asg.struc.Import begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasBody' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitInitializerBlock_HasBody   (columbus.java.asg.struc.InitializerBlock begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge end visitor for 'hasBody' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndInitializerBlock_HasBody(columbus.java.asg.struc.InitializerBlock begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge visitor for 'hasReturnType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodDeclaration_HasReturnType   (columbus.java.asg.struc.MethodDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasReturnType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodDeclaration_HasReturnType(columbus.java.asg.struc.MethodDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'methodType' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodDeclaration_MethodType   (columbus.java.asg.struc.MethodDeclaration begin, columbus.java.asg.type.MethodType end) { }

	/**
	 * Edge end visitor for 'methodType' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodDeclaration_MethodType(columbus.java.asg.struc.MethodDeclaration begin, columbus.java.asg.type.MethodType end) { }

	/**
	 * Edge visitor for 'overrides' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodDeclaration_Overrides   (columbus.java.asg.struc.MethodDeclaration begin, columbus.java.asg.struc.MethodDeclaration end) { }

	/**
	 * Edge end visitor for 'overrides' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodDeclaration_Overrides(columbus.java.asg.struc.MethodDeclaration begin, columbus.java.asg.struc.MethodDeclaration end) { }

	/**
	 * Edge visitor for 'hasParameters' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNormalMethod_HasParameters   (columbus.java.asg.struc.NormalMethod begin, columbus.java.asg.struc.Parameter end) { }

	/**
	 * Edge end visitor for 'hasParameters' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNormalMethod_HasParameters(columbus.java.asg.struc.NormalMethod begin, columbus.java.asg.struc.Parameter end) { }

	/**
	 * Edge visitor for 'hasBody' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNormalMethod_HasBody   (columbus.java.asg.struc.NormalMethod begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge end visitor for 'hasBody' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNormalMethod_HasBody(columbus.java.asg.struc.NormalMethod begin, columbus.java.asg.statm.Block end) { }

	/**
	 * Edge visitor for 'hasThrownExceptions' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitNormalMethod_HasThrownExceptions   (columbus.java.asg.struc.NormalMethod begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasThrownExceptions' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndNormalMethod_HasThrownExceptions(columbus.java.asg.struc.NormalMethod begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasCompilationUnits' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitPackage_HasCompilationUnits   (columbus.java.asg.struc.Package begin, columbus.java.asg.struc.CompilationUnit end) { }

	/**
	 * Edge end visitor for 'hasCompilationUnits' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndPackage_HasCompilationUnits(columbus.java.asg.struc.Package begin, columbus.java.asg.struc.CompilationUnit end) { }

	/**
	 * Edge visitor for 'hasPackageName' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitPackageDeclaration_HasPackageName   (columbus.java.asg.struc.PackageDeclaration begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasPackageName' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndPackageDeclaration_HasPackageName(columbus.java.asg.struc.PackageDeclaration begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'refersTo' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitPackageDeclaration_RefersTo   (columbus.java.asg.struc.PackageDeclaration begin, columbus.java.asg.struc.Package end) { }

	/**
	 * Edge end visitor for 'refersTo' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndPackageDeclaration_RefersTo(columbus.java.asg.struc.PackageDeclaration begin, columbus.java.asg.struc.Package end) { }

	/**
	 * Edge visitor for 'hasMembers' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitScope_HasMembers   (columbus.java.asg.struc.Scope begin, columbus.java.asg.struc.Member end) { }

	/**
	 * Edge end visitor for 'hasMembers' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndScope_HasMembers(columbus.java.asg.struc.Scope begin, columbus.java.asg.struc.Member end) { }

	/**
	 * Edge visitor for 'isInCompilationUnit' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeDeclaration_IsInCompilationUnit   (columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.struc.CompilationUnit end) { }

	/**
	 * Edge end visitor for 'isInCompilationUnit' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeDeclaration_IsInCompilationUnit(columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.struc.CompilationUnit end) { }

	/**
	 * Edge visitor for 'hasSuperClass' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeDeclaration_HasSuperClass   (columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasSuperClass' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeDeclaration_HasSuperClass(columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasSuperInterfaces' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeDeclaration_HasSuperInterfaces   (columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasSuperInterfaces' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeDeclaration_HasSuperInterfaces(columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasOthers' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeDeclaration_HasOthers   (columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge end visitor for 'hasOthers' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeDeclaration_HasOthers(columbus.java.asg.struc.TypeDeclaration begin, columbus.java.asg.base.Positioned end) { }

	/**
	 * Edge visitor for 'hasBounds' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeParameter_HasBounds   (columbus.java.asg.struc.TypeParameter begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasBounds' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeParameter_HasBounds(columbus.java.asg.struc.TypeParameter begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'hasInitialValue' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitVariable_HasInitialValue   (columbus.java.asg.struc.Variable begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge end visitor for 'hasInitialValue' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndVariable_HasInitialValue(columbus.java.asg.struc.Variable begin, columbus.java.asg.expr.Expression end) { }

	/**
	 * Edge visitor for 'hasType' edge which is called when the subtree of this edge is started.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitVariableDeclaration_HasType   (columbus.java.asg.struc.VariableDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge end visitor for 'hasType' edge which is called after the subtree of this edge is finished.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndVariableDeclaration_HasType(columbus.java.asg.struc.VariableDeclaration begin, columbus.java.asg.expr.TypeExpression end) { }

	/**
	 * Edge visitor for 'componentType' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitArrayType_ComponentType   (columbus.java.asg.type.ArrayType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'componentType' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndArrayType_ComponentType(columbus.java.asg.type.ArrayType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'refersTo' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitClassType_RefersTo   (columbus.java.asg.type.ClassType begin, columbus.java.asg.struc.TypeDeclaration end) { }

	/**
	 * Edge end visitor for 'refersTo' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndClassType_RefersTo(columbus.java.asg.type.ClassType begin, columbus.java.asg.struc.TypeDeclaration end) { }

	/**
	 * Edge visitor for 'returnType' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodType_ReturnType   (columbus.java.asg.type.MethodType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'returnType' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodType_ReturnType(columbus.java.asg.type.MethodType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'parameterTypes' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodType_ParameterTypes   (columbus.java.asg.type.MethodType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'parameterTypes' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodType_ParameterTypes(columbus.java.asg.type.MethodType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'thrownTypes' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitMethodType_ThrownTypes   (columbus.java.asg.type.MethodType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'thrownTypes' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndMethodType_ThrownTypes(columbus.java.asg.type.MethodType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'refersTo' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitPackageType_RefersTo   (columbus.java.asg.type.PackageType begin, columbus.java.asg.struc.Package end) { }

	/**
	 * Edge end visitor for 'refersTo' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndPackageType_RefersTo(columbus.java.asg.type.PackageType begin, columbus.java.asg.struc.Package end) { }

	/**
	 * Edge visitor for 'rawType' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitParameterizedType_RawType   (columbus.java.asg.type.ParameterizedType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'rawType' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndParameterizedType_RawType(columbus.java.asg.type.ParameterizedType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'argumentTypes' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitParameterizedType_ArgumentTypes   (columbus.java.asg.type.ParameterizedType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'argumentTypes' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndParameterizedType_ArgumentTypes(columbus.java.asg.type.ParameterizedType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'owner' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitScopedType_Owner   (columbus.java.asg.type.ScopedType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'owner' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndScopedType_Owner(columbus.java.asg.type.ScopedType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'refersTo' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitTypeVariable_RefersTo   (columbus.java.asg.type.TypeVariable begin, columbus.java.asg.struc.TypeParameter end) { }

	/**
	 * Edge end visitor for 'refersTo' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndTypeVariable_RefersTo(columbus.java.asg.type.TypeVariable begin, columbus.java.asg.struc.TypeParameter end) { }

	/**
	 * Edge visitor for 'alternatives' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitUnionType_Alternatives   (columbus.java.asg.type.UnionType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'alternatives' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndUnionType_Alternatives(columbus.java.asg.type.UnionType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge visitor for 'bound' edge which is called when this edge is visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitWildcardType_Bound   (columbus.java.asg.type.WildcardType begin, columbus.java.asg.type.Type end) { }

	/**
	 * Edge end visitor for 'bound' edge which is called after this edge has been visited.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	public void visitEndWildcardType_Bound(columbus.java.asg.type.WildcardType begin, columbus.java.asg.type.Type end) { }

}
