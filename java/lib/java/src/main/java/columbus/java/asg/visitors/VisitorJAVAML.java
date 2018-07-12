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

import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import columbus.logger.LoggerHandler;

import columbus.java.asg.*;
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
 * Creates XML dump.
 */
public class VisitorJAVAML extends Visitor {

	private static final LoggerHandler logger = new LoggerHandler(VisitorJAVAML.class, columbus.java.asg.Constant.LoggerPropertyFile);
	/** The xml will be written into this. */
	protected PrintWriter ofs;

	/** The name of the output file. */
	protected String fileName;

	/** The name of the project. */
	protected String projectName;

	/** Flag to know if the ID of the nodes have to be written or not. */
	protected boolean noId;

	/**
	 * Constructor of XML generator visitor.
	 * @param fileName    Name of the output file.
	 * @param projectName Name of the project.
	 * @param noId        Do not write the ID of the nodes.
	 */
	public VisitorJAVAML(String fileName, String projectName, boolean noId) {
		this.fileName = fileName;
		this.projectName = projectName;
		this.noId = noId;
	}

	/**
	 * This method is called before the beginning of visiting process. It flushes the header of xml.
	 */
	@Override
	public void beginVisit() {
		if (ofs != null)
			throw new JavaException(logger.formatMessage("ex.java.JVM.File_is_already_opened"));

		try {
			ofs = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(fileName), "UTF-8")));
		} catch (IOException e) {
			throw new JavaException(e);
		}
		ofs.println("<?xml version='1.0' encoding=\"utf-8\"?>");
		ofs.print("<Project name='" + projectName + "'");
		ofs.print(" xmlns:base='columbus_java_schema/base'");
		ofs.print(" xmlns:expr='columbus_java_schema/expr'");
		ofs.print(" xmlns:statm='columbus_java_schema/statm'");
		ofs.print(" xmlns:struc='columbus_java_schema/struc'");
		ofs.print(" xmlns:type='columbus_java_schema/type'");
		ofs.println(">");
	}

	/**
	 * This method is called when the visiting process has finished. It flushes the tail of xml.
	 */
	@Override
	public void finishVisit() {
		ofs.println("<Filtered id='id1'/>");
		ofs.println("</Project>");

		ofs.close();
		ofs = null;
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.base.BlockComment BlockComment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BlockComment node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<base:BlockComment");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.base.BlockComment BlockComment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BlockComment node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</base:BlockComment>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(JavadocComment node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<base:JavadocComment");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(JavadocComment node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</base:JavadocComment>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.base.LineComment LineComment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LineComment node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<base:LineComment");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.base.LineComment LineComment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LineComment node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</base:LineComment>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ArrayAccess node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:ArrayAccess");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayAccess node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:ArrayAccess>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ArrayTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:ArrayTypeExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:ArrayTypeExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.Assignment Assignment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Assignment node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:Assignment");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.Assignment Assignment} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Assignment node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:Assignment>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BooleanLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:BooleanLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BooleanLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:BooleanLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(CharacterLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:CharacterLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CharacterLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:CharacterLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ClassLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:ClassLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:ClassLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.Conditional Conditional} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Conditional node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:Conditional");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.Conditional Conditional} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Conditional node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:Conditional>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(DoubleLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:DoubleLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(DoubleLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:DoubleLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.Erroneous Erroneous} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Erroneous node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:Erroneous");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.Erroneous Erroneous} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Erroneous node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:Erroneous>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ErroneousTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:ErroneousTypeExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ErroneousTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:ErroneousTypeExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ExternalTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:ExternalTypeExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ExternalTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:ExternalTypeExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(FieldAccess node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:FieldAccess");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FieldAccess node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:FieldAccess>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(FloatLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:FloatLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FloatLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:FloatLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.Identifier Identifier} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Identifier node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:Identifier");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.Identifier Identifier} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Identifier node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:Identifier>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InfixExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:InfixExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InfixExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:InfixExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InstanceOf node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:InstanceOf");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InstanceOf node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:InstanceOf>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(IntegerLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:IntegerLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(IntegerLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:IntegerLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LongLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:LongLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LongLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:LongLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MarkerAnnotation node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:MarkerAnnotation");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MarkerAnnotation node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:MarkerAnnotation>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MethodInvocation node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:MethodInvocation");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodInvocation node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:MethodInvocation>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.NewArray NewArray} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NewArray node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:NewArray");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.NewArray NewArray} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NewArray node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:NewArray>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.NewClass NewClass} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NewClass node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:NewClass");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.NewClass NewClass} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NewClass node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:NewClass>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NormalAnnotation node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:NormalAnnotation");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NormalAnnotation node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:NormalAnnotation>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NullLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:NullLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NullLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:NullLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ParenthesizedExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:ParenthesizedExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ParenthesizedExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:ParenthesizedExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PostfixExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:PostfixExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PostfixExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:PostfixExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PrefixExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:PrefixExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PrefixExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:PrefixExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PrimitiveTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:PrimitiveTypeExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PrimitiveTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:PrimitiveTypeExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(QualifiedTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:QualifiedTypeExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(QualifiedTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:QualifiedTypeExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(SimpleTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:SimpleTypeExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(SimpleTypeExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:SimpleTypeExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(SingleElementAnnotation node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:SingleElementAnnotation");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(SingleElementAnnotation node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:SingleElementAnnotation>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(StringLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:StringLiteral");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(StringLiteral node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:StringLiteral>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.Super Super} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Super node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:Super");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.Super Super} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Super node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:Super>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.This This} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(This node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:This");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.This This} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(This node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:This>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeApplyExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:TypeApplyExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeApplyExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:TypeApplyExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.TypeCast TypeCast} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeCast node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:TypeCast");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.TypeCast TypeCast} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeCast node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:TypeCast>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeUnionExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:TypeUnionExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeUnionExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:TypeUnionExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(WildcardExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<expr:WildcardExpression");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(WildcardExpression node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</expr:WildcardExpression>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Assert Assert} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Assert node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Assert");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Assert Assert} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Assert node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Assert>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.BasicFor BasicFor} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BasicFor node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:BasicFor");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.BasicFor BasicFor} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BasicFor node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:BasicFor>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Block Block} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Block node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Block");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Block Block} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Block node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Block>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Break Break} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Break node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Break");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Break Break} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Break node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Break>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Case Case} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Case node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Case");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Case Case} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Case node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Case>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Continue Continue} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Continue node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Continue");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Continue Continue} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Continue node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Continue>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Default Default} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Default node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Default");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Default Default} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Default node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Default>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Do Do} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Do node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Do");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Do Do} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Do node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Do>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Empty Empty} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Empty node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Empty");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Empty Empty} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Empty node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Empty>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(EnhancedFor node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:EnhancedFor");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(EnhancedFor node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:EnhancedFor>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ExpressionStatement node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:ExpressionStatement");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ExpressionStatement node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:ExpressionStatement>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Handler Handler} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Handler node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Handler");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Handler Handler} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Handler node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Handler>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.If If} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(If node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:If");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.If If} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(If node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:If>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LabeledStatement node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:LabeledStatement");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LabeledStatement node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:LabeledStatement>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Return Return} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Return node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Return");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Return Return} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Return node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Return>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Switch Switch} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Switch node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Switch");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Switch Switch} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Switch node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Switch>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Synchronized Synchronized} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Synchronized node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Synchronized");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Synchronized Synchronized} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Synchronized node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Synchronized>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Throw Throw} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Throw node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Throw");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Throw Throw} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Throw node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Throw>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.Try Try} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Try node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:Try");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.Try Try} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Try node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:Try>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.statm.While While} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(While node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<statm:While");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.statm.While While} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(While node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</statm:While>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(AnnotationType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:AnnotationType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnnotationType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:AnnotationType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(AnnotationTypeElement node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:AnnotationTypeElement");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnnotationTypeElement node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:AnnotationTypeElement>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(AnonymousClass node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:AnonymousClass");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(AnonymousClass node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:AnonymousClass>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Class Class} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Class node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Class");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Class Class} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Class node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Class>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ClassGeneric node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:ClassGeneric");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassGeneric node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:ClassGeneric>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(CompilationUnit node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:CompilationUnit");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CompilationUnit node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:CompilationUnit>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Enum Enum} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Enum node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Enum");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Enum Enum} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Enum node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Enum>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(EnumConstant node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:EnumConstant");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(EnumConstant node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:EnumConstant>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Import Import} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Import node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Import");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Import Import} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Import node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Import>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InstanceInitializerBlock node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:InstanceInitializerBlock");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InstanceInitializerBlock node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:InstanceInitializerBlock>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Interface Interface} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Interface node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Interface");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Interface Interface} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Interface node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Interface>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(InterfaceGeneric node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:InterfaceGeneric");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(InterfaceGeneric node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:InterfaceGeneric>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Method Method} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Method node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Method");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Method Method} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Method node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Method>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MethodGeneric node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:MethodGeneric");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodGeneric node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:MethodGeneric>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Package Package} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Package node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Package");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Package Package} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Package node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Package>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PackageDeclaration node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:PackageDeclaration");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PackageDeclaration node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:PackageDeclaration>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Parameter Parameter} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Parameter node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Parameter");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Parameter Parameter} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Parameter node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Parameter>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(StaticInitializerBlock node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:StaticInitializerBlock");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(StaticInitializerBlock node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:StaticInitializerBlock>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeParameter node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:TypeParameter");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeParameter node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:TypeParameter>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.struc.Variable Variable} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(Variable node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<struc:Variable");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.struc.Variable Variable} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Variable node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</struc:Variable>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.ArrayType ArrayType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ArrayType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:ArrayType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.ArrayType ArrayType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ArrayType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:ArrayType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.BooleanType BooleanType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(BooleanType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:BooleanType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.BooleanType BooleanType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(BooleanType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.ByteType ByteType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ByteType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:ByteType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.ByteType ByteType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ByteType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.CharType CharType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(CharType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:CharType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.CharType CharType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(CharType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.ClassType ClassType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ClassType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:ClassType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.ClassType ClassType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ClassType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:ClassType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.DoubleType DoubleType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(DoubleType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:DoubleType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.DoubleType DoubleType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(DoubleType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.ErrorType ErrorType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ErrorType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:ErrorType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.ErrorType ErrorType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ErrorType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.FloatType FloatType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(FloatType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:FloatType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.FloatType FloatType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(FloatType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.IntType IntType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(IntType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:IntType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.IntType IntType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(IntType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.LongType LongType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LongType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:LongType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.LongType LongType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LongType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(LowerBoundedWildcardType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:LowerBoundedWildcardType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(LowerBoundedWildcardType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:LowerBoundedWildcardType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.MethodType MethodType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(MethodType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:MethodType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.MethodType MethodType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(MethodType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:MethodType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.NoType NoType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NoType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:NoType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.NoType NoType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NoType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.NullType NullType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(NullType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:NullType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.NullType NullType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(NullType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.PackageType PackageType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(PackageType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:PackageType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.PackageType PackageType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(PackageType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:PackageType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ParameterizedType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:ParameterizedType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ParameterizedType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:ParameterizedType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.ShortType ShortType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(ShortType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:ShortType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.ShortType ShortType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(ShortType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(TypeVariable node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:TypeVariable");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(TypeVariable node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:TypeVariable>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(UnboundedWildcardType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:UnboundedWildcardType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UnboundedWildcardType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:UnboundedWildcardType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.UnionType UnionType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(UnionType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:UnionType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.UnionType UnionType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UnionType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:UnionType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(UpperBoundedWildcardType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:UpperBoundedWildcardType");
		writeAttributes(node, true);
		ofs.println(">");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(UpperBoundedWildcardType node, boolean callVirtualBase) {
		createIndentation();
		ofs.println("</type:UpperBoundedWildcardType>");
	}

	/**
	 * Writes the XML representation of the {@link columbus.java.asg.type.VoidType VoidType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visit(VoidType node, boolean callVirtualBase) {
		createIndentation();
		ofs.print("<type:VoidType");
		writeAttributes(node, true);
		ofs.println("/>");

		writeCompositeAttributes(node, true);
	}

	/**
	 * Writes the end part of XML representation of the {@link columbus.java.asg.type.VoidType VoidType} node into the output file.
	 * @param node The node which is visited.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(VoidType node, boolean callVirtualBase) {
	}

	/**
	 * Writes the XML representation of the 'comments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitCommentable_Comments(Commentable begin, Comment end) {
		createIndentation();
		ofs.print("<Commentable_Comments ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'comments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndCommentable_Comments(Commentable begin, Comment end) {
	}

	/**
	 * Writes the XML representation of the 'hasAnnotationName' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitAnnotation_HasAnnotationName(Annotation begin, TypeExpression end) {
		createIndentation();
		ofs.println("<Annotation_HasAnnotationName>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasAnnotationName' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndAnnotation_HasAnnotationName(Annotation begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</Annotation_HasAnnotationName>");
	}

	/**
	 * Writes the XML representation of the 'hasComponentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitArrayTypeExpression_HasComponentType(ArrayTypeExpression begin, TypeExpression end) {
		createIndentation();
		ofs.println("<ArrayTypeExpression_HasComponentType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasComponentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndArrayTypeExpression_HasComponentType(ArrayTypeExpression begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</ArrayTypeExpression_HasComponentType>");
	}

	/**
	 * Writes the XML representation of the 'hasLeftOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitBinary_HasLeftOperand(Binary begin, Expression end) {
		createIndentation();
		ofs.println("<Binary_HasLeftOperand>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasLeftOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndBinary_HasLeftOperand(Binary begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Binary_HasLeftOperand>");
	}

	/**
	 * Writes the XML representation of the 'hasRightOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitBinary_HasRightOperand(Binary begin, Expression end) {
		createIndentation();
		ofs.println("<Binary_HasRightOperand>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasRightOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndBinary_HasRightOperand(Binary begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Binary_HasRightOperand>");
	}

	/**
	 * Writes the XML representation of the 'hasComponentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitClassLiteral_HasComponentType(ClassLiteral begin, TypeExpression end) {
		createIndentation();
		ofs.println("<ClassLiteral_HasComponentType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasComponentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndClassLiteral_HasComponentType(ClassLiteral begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</ClassLiteral_HasComponentType>");
	}

	/**
	 * Writes the XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitConditional_HasCondition(Conditional begin, Expression end) {
		createIndentation();
		ofs.println("<Conditional_HasCondition>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndConditional_HasCondition(Conditional begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Conditional_HasCondition>");
	}

	/**
	 * Writes the XML representation of the 'hasTrueExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitConditional_HasTrueExpression(Conditional begin, Expression end) {
		createIndentation();
		ofs.println("<Conditional_HasTrueExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTrueExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndConditional_HasTrueExpression(Conditional begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Conditional_HasTrueExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasFalseExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitConditional_HasFalseExpression(Conditional begin, Expression end) {
		createIndentation();
		ofs.println("<Conditional_HasFalseExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasFalseExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndConditional_HasFalseExpression(Conditional begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Conditional_HasFalseExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasErrors' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitErroneous_HasErrors(Erroneous begin, Positioned end) {
		createIndentation();
		ofs.println("<Erroneous_HasErrors>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasErrors' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndErroneous_HasErrors(Erroneous begin, Positioned end) {
		decDepth();
		createIndentation();
		ofs.println("</Erroneous_HasErrors>");
	}

	/**
	 * Writes the XML representation of the 'hasErrors' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitErroneousTypeExpression_HasErrors(ErroneousTypeExpression begin, Positioned end) {
		createIndentation();
		ofs.println("<ErroneousTypeExpression_HasErrors>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasErrors' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndErroneousTypeExpression_HasErrors(ErroneousTypeExpression begin, Positioned end) {
		decDepth();
		createIndentation();
		ofs.println("</ErroneousTypeExpression_HasErrors>");
	}

	/**
	 * Writes the XML representation of the 'type' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitExpression_Type(Expression begin, Type end) {
		createIndentation();
		ofs.print("<Expression_Type ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'type' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndExpression_Type(Expression begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitIdentifier_RefersTo(Identifier begin, Named end) {
		createIndentation();
		ofs.print("<Identifier_RefersTo ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndIdentifier_RefersTo(Identifier begin, Named end) {
	}

	/**
	 * Writes the XML representation of the 'hasTypeOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitInstanceOf_HasTypeOperand(InstanceOf begin, TypeExpression end) {
		createIndentation();
		ofs.println("<InstanceOf_HasTypeOperand>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTypeOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndInstanceOf_HasTypeOperand(InstanceOf begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</InstanceOf_HasTypeOperand>");
	}

	/**
	 * Writes the XML representation of the 'hasTypeArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodInvocation_HasTypeArguments(MethodInvocation begin, TypeExpression end) {
		createIndentation();
		ofs.println("<MethodInvocation_HasTypeArguments>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTypeArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodInvocation_HasTypeArguments(MethodInvocation begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</MethodInvocation_HasTypeArguments>");
	}

	/**
	 * Writes the XML representation of the 'hasArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodInvocation_HasArguments(MethodInvocation begin, Expression end) {
		createIndentation();
		ofs.println("<MethodInvocation_HasArguments>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodInvocation_HasArguments(MethodInvocation begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</MethodInvocation_HasArguments>");
	}

	/**
	 * Writes the XML representation of the 'invokes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodInvocation_Invokes(MethodInvocation begin, MethodDeclaration end) {
		createIndentation();
		ofs.print("<MethodInvocation_Invokes ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'invokes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodInvocation_Invokes(MethodInvocation begin, MethodDeclaration end) {
	}

	/**
	 * Writes the XML representation of the 'hasComponentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewArray_HasComponentType(NewArray begin, TypeExpression end) {
		createIndentation();
		ofs.println("<NewArray_HasComponentType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasComponentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewArray_HasComponentType(NewArray begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</NewArray_HasComponentType>");
	}

	/**
	 * Writes the XML representation of the 'hasDimensions' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewArray_HasDimensions(NewArray begin, Expression end) {
		createIndentation();
		ofs.println("<NewArray_HasDimensions>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasDimensions' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewArray_HasDimensions(NewArray begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</NewArray_HasDimensions>");
	}

	/**
	 * Writes the XML representation of the 'hasInitializers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewArray_HasInitializers(NewArray begin, Expression end) {
		createIndentation();
		ofs.println("<NewArray_HasInitializers>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasInitializers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewArray_HasInitializers(NewArray begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</NewArray_HasInitializers>");
	}

	/**
	 * Writes the XML representation of the 'hasEnclosingExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewClass_HasEnclosingExpression(NewClass begin, Expression end) {
		createIndentation();
		ofs.println("<NewClass_HasEnclosingExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasEnclosingExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewClass_HasEnclosingExpression(NewClass begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</NewClass_HasEnclosingExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasTypeArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewClass_HasTypeArguments(NewClass begin, TypeExpression end) {
		createIndentation();
		ofs.println("<NewClass_HasTypeArguments>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTypeArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewClass_HasTypeArguments(NewClass begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</NewClass_HasTypeArguments>");
	}

	/**
	 * Writes the XML representation of the 'hasTypeName' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewClass_HasTypeName(NewClass begin, TypeExpression end) {
		createIndentation();
		ofs.println("<NewClass_HasTypeName>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTypeName' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewClass_HasTypeName(NewClass begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</NewClass_HasTypeName>");
	}

	/**
	 * Writes the XML representation of the 'hasArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewClass_HasArguments(NewClass begin, Expression end) {
		createIndentation();
		ofs.println("<NewClass_HasArguments>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewClass_HasArguments(NewClass begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</NewClass_HasArguments>");
	}

	/**
	 * Writes the XML representation of the 'hasAnonymousClass' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewClass_HasAnonymousClass(NewClass begin, AnonymousClass end) {
		createIndentation();
		ofs.println("<NewClass_HasAnonymousClass>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasAnonymousClass' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewClass_HasAnonymousClass(NewClass begin, AnonymousClass end) {
		decDepth();
		createIndentation();
		ofs.println("</NewClass_HasAnonymousClass>");
	}

	/**
	 * Writes the XML representation of the 'constructor' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNewClass_Constructor(NewClass begin, NormalMethod end) {
		createIndentation();
		ofs.print("<NewClass_Constructor ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'constructor' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNewClass_Constructor(NewClass begin, NormalMethod end) {
	}

	/**
	 * Writes the XML representation of the 'hasArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNormalAnnotation_HasArguments(NormalAnnotation begin, Expression end) {
		createIndentation();
		ofs.println("<NormalAnnotation_HasArguments>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNormalAnnotation_HasArguments(NormalAnnotation begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</NormalAnnotation_HasArguments>");
	}

	/**
	 * Writes the XML representation of the 'hasQualifierType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitQualifiedTypeExpression_HasQualifierType(QualifiedTypeExpression begin, TypeExpression end) {
		createIndentation();
		ofs.println("<QualifiedTypeExpression_HasQualifierType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasQualifierType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndQualifiedTypeExpression_HasQualifierType(QualifiedTypeExpression begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</QualifiedTypeExpression_HasQualifierType>");
	}

	/**
	 * Writes the XML representation of the 'hasSimpleType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitQualifiedTypeExpression_HasSimpleType(QualifiedTypeExpression begin, SimpleTypeExpression end) {
		createIndentation();
		ofs.println("<QualifiedTypeExpression_HasSimpleType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasSimpleType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndQualifiedTypeExpression_HasSimpleType(QualifiedTypeExpression begin, SimpleTypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</QualifiedTypeExpression_HasSimpleType>");
	}

	/**
	 * Writes the XML representation of the 'hasArgument' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitSingleElementAnnotation_HasArgument(SingleElementAnnotation begin, Expression end) {
		createIndentation();
		ofs.println("<SingleElementAnnotation_HasArgument>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasArgument' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndSingleElementAnnotation_HasArgument(SingleElementAnnotation begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</SingleElementAnnotation_HasArgument>");
	}

	/**
	 * Writes the XML representation of the 'hasRawType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeApplyExpression_HasRawType(TypeApplyExpression begin, TypeExpression end) {
		createIndentation();
		ofs.println("<TypeApplyExpression_HasRawType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasRawType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeApplyExpression_HasRawType(TypeApplyExpression begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeApplyExpression_HasRawType>");
	}

	/**
	 * Writes the XML representation of the 'hasTypeArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeApplyExpression_HasTypeArguments(TypeApplyExpression begin, TypeExpression end) {
		createIndentation();
		ofs.println("<TypeApplyExpression_HasTypeArguments>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTypeArguments' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeApplyExpression_HasTypeArguments(TypeApplyExpression begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeApplyExpression_HasTypeArguments>");
	}

	/**
	 * Writes the XML representation of the 'hasTypeOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeCast_HasTypeOperand(TypeCast begin, TypeExpression end) {
		createIndentation();
		ofs.println("<TypeCast_HasTypeOperand>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTypeOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeCast_HasTypeOperand(TypeCast begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeCast_HasTypeOperand>");
	}

	/**
	 * Writes the XML representation of the 'hasAlternatives' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeUnionExpression_HasAlternatives(TypeUnionExpression begin, TypeExpression end) {
		createIndentation();
		ofs.println("<TypeUnionExpression_HasAlternatives>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasAlternatives' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeUnionExpression_HasAlternatives(TypeUnionExpression begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeUnionExpression_HasAlternatives>");
	}

	/**
	 * Writes the XML representation of the 'hasOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitUnary_HasOperand(Unary begin, Expression end) {
		createIndentation();
		ofs.println("<Unary_HasOperand>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasOperand' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndUnary_HasOperand(Unary begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Unary_HasOperand>");
	}

	/**
	 * Writes the XML representation of the 'hasBound' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitWildcardExpression_HasBound(WildcardExpression begin, TypeExpression end) {
		createIndentation();
		ofs.println("<WildcardExpression_HasBound>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasBound' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndWildcardExpression_HasBound(WildcardExpression begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</WildcardExpression_HasBound>");
	}

	/**
	 * Writes the XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitAssert_HasCondition(Assert begin, Expression end) {
		createIndentation();
		ofs.println("<Assert_HasCondition>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndAssert_HasCondition(Assert begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Assert_HasCondition>");
	}

	/**
	 * Writes the XML representation of the 'hasDetail' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitAssert_HasDetail(Assert begin, Expression end) {
		createIndentation();
		ofs.println("<Assert_HasDetail>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasDetail' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndAssert_HasDetail(Assert begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Assert_HasDetail>");
	}

	/**
	 * Writes the XML representation of the 'hasInitializers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitBasicFor_HasInitializers(BasicFor begin, Statement end) {
		createIndentation();
		ofs.println("<BasicFor_HasInitializers>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasInitializers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndBasicFor_HasInitializers(BasicFor begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</BasicFor_HasInitializers>");
	}

	/**
	 * Writes the XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitBasicFor_HasCondition(BasicFor begin, Expression end) {
		createIndentation();
		ofs.println("<BasicFor_HasCondition>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndBasicFor_HasCondition(BasicFor begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</BasicFor_HasCondition>");
	}

	/**
	 * Writes the XML representation of the 'hasUpdates' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitBasicFor_HasUpdates(BasicFor begin, Statement end) {
		createIndentation();
		ofs.println("<BasicFor_HasUpdates>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasUpdates' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndBasicFor_HasUpdates(BasicFor begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</BasicFor_HasUpdates>");
	}

	/**
	 * Writes the XML representation of the 'hasStatements' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitBlock_HasStatements(Block begin, Statement end) {
		createIndentation();
		ofs.println("<Block_HasStatements>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasStatements' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndBlock_HasStatements(Block begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</Block_HasStatements>");
	}

	/**
	 * Writes the XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitCase_HasExpression(Case begin, Expression end) {
		createIndentation();
		ofs.println("<Case_HasExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndCase_HasExpression(Case begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Case_HasExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitDo_HasCondition(Do begin, Expression end) {
		createIndentation();
		ofs.println("<Do_HasCondition>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndDo_HasCondition(Do begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Do_HasCondition>");
	}

	/**
	 * Writes the XML representation of the 'hasParameter' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEnhancedFor_HasParameter(EnhancedFor begin, Parameter end) {
		createIndentation();
		ofs.println("<EnhancedFor_HasParameter>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasParameter' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndEnhancedFor_HasParameter(EnhancedFor begin, Parameter end) {
		decDepth();
		createIndentation();
		ofs.println("</EnhancedFor_HasParameter>");
	}

	/**
	 * Writes the XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEnhancedFor_HasExpression(EnhancedFor begin, Expression end) {
		createIndentation();
		ofs.println("<EnhancedFor_HasExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndEnhancedFor_HasExpression(EnhancedFor begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</EnhancedFor_HasExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitExpressionStatement_HasExpression(ExpressionStatement begin, Expression end) {
		createIndentation();
		ofs.println("<ExpressionStatement_HasExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndExpressionStatement_HasExpression(ExpressionStatement begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</ExpressionStatement_HasExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasParameter' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitHandler_HasParameter(Handler begin, Parameter end) {
		createIndentation();
		ofs.println("<Handler_HasParameter>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasParameter' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndHandler_HasParameter(Handler begin, Parameter end) {
		decDepth();
		createIndentation();
		ofs.println("</Handler_HasParameter>");
	}

	/**
	 * Writes the XML representation of the 'hasBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitHandler_HasBlock(Handler begin, Block end) {
		createIndentation();
		ofs.println("<Handler_HasBlock>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndHandler_HasBlock(Handler begin, Block end) {
		decDepth();
		createIndentation();
		ofs.println("</Handler_HasBlock>");
	}

	/**
	 * Writes the XML representation of the 'hasSubstatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitIf_HasSubstatement(If begin, Statement end) {
		createIndentation();
		ofs.println("<If_HasSubstatement>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasSubstatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndIf_HasSubstatement(If begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</If_HasSubstatement>");
	}

	/**
	 * Writes the XML representation of the 'hasFalseSubstatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitIf_HasFalseSubstatement(If begin, Statement end) {
		createIndentation();
		ofs.println("<If_HasFalseSubstatement>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasFalseSubstatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndIf_HasFalseSubstatement(If begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</If_HasFalseSubstatement>");
	}

	/**
	 * Writes the XML representation of the 'hasSubstatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitIteration_HasSubstatement(Iteration begin, Statement end) {
		createIndentation();
		ofs.println("<Iteration_HasSubstatement>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasSubstatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndIteration_HasSubstatement(Iteration begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</Iteration_HasSubstatement>");
	}

	/**
	 * Writes the XML representation of the 'target' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitJump_Target(Jump begin, Statement end) {
		createIndentation();
		ofs.print("<Jump_Target ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'target' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndJump_Target(Jump begin, Statement end) {
	}

	/**
	 * Writes the XML representation of the 'hasStatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitLabeledStatement_HasStatement(LabeledStatement begin, Statement end) {
		createIndentation();
		ofs.println("<LabeledStatement_HasStatement>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasStatement' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndLabeledStatement_HasStatement(LabeledStatement begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</LabeledStatement_HasStatement>");
	}

	/**
	 * Writes the XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitReturn_HasExpression(Return begin, Expression end) {
		createIndentation();
		ofs.println("<Return_HasExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndReturn_HasExpression(Return begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Return_HasExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitSelection_HasCondition(Selection begin, Expression end) {
		createIndentation();
		ofs.println("<Selection_HasCondition>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndSelection_HasCondition(Selection begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Selection_HasCondition>");
	}

	/**
	 * Writes the XML representation of the 'hasCases' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitSwitch_HasCases(Switch begin, SwitchLabel end) {
		createIndentation();
		ofs.println("<Switch_HasCases>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCases' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndSwitch_HasCases(Switch begin, SwitchLabel end) {
		decDepth();
		createIndentation();
		ofs.println("</Switch_HasCases>");
	}

	/**
	 * Writes the XML representation of the 'hasStatements' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitSwitchLabel_HasStatements(SwitchLabel begin, Statement end) {
		createIndentation();
		ofs.println("<SwitchLabel_HasStatements>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasStatements' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndSwitchLabel_HasStatements(SwitchLabel begin, Statement end) {
		decDepth();
		createIndentation();
		ofs.println("</SwitchLabel_HasStatements>");
	}

	/**
	 * Writes the XML representation of the 'hasLock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitSynchronized_HasLock(Synchronized begin, Expression end) {
		createIndentation();
		ofs.println("<Synchronized_HasLock>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasLock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndSynchronized_HasLock(Synchronized begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Synchronized_HasLock>");
	}

	/**
	 * Writes the XML representation of the 'hasBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitSynchronized_HasBlock(Synchronized begin, Block end) {
		createIndentation();
		ofs.println("<Synchronized_HasBlock>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndSynchronized_HasBlock(Synchronized begin, Block end) {
		decDepth();
		createIndentation();
		ofs.println("</Synchronized_HasBlock>");
	}

	/**
	 * Writes the XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitThrow_HasExpression(Throw begin, Expression end) {
		createIndentation();
		ofs.println("<Throw_HasExpression>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasExpression' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndThrow_HasExpression(Throw begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Throw_HasExpression>");
	}

	/**
	 * Writes the XML representation of the 'hasResources' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTry_HasResources(Try begin, Variable end) {
		createIndentation();
		ofs.println("<Try_HasResources>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasResources' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTry_HasResources(Try begin, Variable end) {
		decDepth();
		createIndentation();
		ofs.println("</Try_HasResources>");
	}

	/**
	 * Writes the XML representation of the 'hasBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTry_HasBlock(Try begin, Block end) {
		createIndentation();
		ofs.println("<Try_HasBlock>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTry_HasBlock(Try begin, Block end) {
		decDepth();
		createIndentation();
		ofs.println("</Try_HasBlock>");
	}

	/**
	 * Writes the XML representation of the 'hasHandlers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTry_HasHandlers(Try begin, Handler end) {
		createIndentation();
		ofs.println("<Try_HasHandlers>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasHandlers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTry_HasHandlers(Try begin, Handler end) {
		decDepth();
		createIndentation();
		ofs.println("</Try_HasHandlers>");
	}

	/**
	 * Writes the XML representation of the 'hasFinallyBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTry_HasFinallyBlock(Try begin, Block end) {
		createIndentation();
		ofs.println("<Try_HasFinallyBlock>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasFinallyBlock' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTry_HasFinallyBlock(Try begin, Block end) {
		decDepth();
		createIndentation();
		ofs.println("</Try_HasFinallyBlock>");
	}

	/**
	 * Writes the XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitWhile_HasCondition(While begin, Expression end) {
		createIndentation();
		ofs.println("<While_HasCondition>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCondition' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndWhile_HasCondition(While begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</While_HasCondition>");
	}

	/**
	 * Writes the XML representation of the 'hasAnnotations' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitAnnotatedElement_HasAnnotations(AnnotatedElement begin, Annotation end) {
		createIndentation();
		ofs.println("<AnnotatedElement_HasAnnotations>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasAnnotations' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndAnnotatedElement_HasAnnotations(AnnotatedElement begin, Annotation end) {
		decDepth();
		createIndentation();
		ofs.println("</AnnotatedElement_HasAnnotations>");
	}

	/**
	 * Writes the XML representation of the 'hasDefaultValue' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitAnnotationTypeElement_HasDefaultValue(AnnotationTypeElement begin, Expression end) {
		createIndentation();
		ofs.println("<AnnotationTypeElement_HasDefaultValue>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasDefaultValue' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndAnnotationTypeElement_HasDefaultValue(AnnotationTypeElement begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</AnnotationTypeElement_HasDefaultValue>");
	}

	/**
	 * Writes the XML representation of the 'hasPackageDeclaration' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitCompilationUnit_HasPackageDeclaration(CompilationUnit begin, PackageDeclaration end) {
		createIndentation();
		ofs.println("<CompilationUnit_HasPackageDeclaration>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasPackageDeclaration' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndCompilationUnit_HasPackageDeclaration(CompilationUnit begin, PackageDeclaration end) {
		decDepth();
		createIndentation();
		ofs.println("</CompilationUnit_HasPackageDeclaration>");
	}

	/**
	 * Writes the XML representation of the 'hasImports' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitCompilationUnit_HasImports(CompilationUnit begin, Import end) {
		createIndentation();
		ofs.println("<CompilationUnit_HasImports>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasImports' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndCompilationUnit_HasImports(CompilationUnit begin, Import end) {
		decDepth();
		createIndentation();
		ofs.println("</CompilationUnit_HasImports>");
	}

	/**
	 * Writes the XML representation of the 'typeDeclarations' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitCompilationUnit_TypeDeclarations(CompilationUnit begin, TypeDeclaration end) {
		createIndentation();
		ofs.print("<CompilationUnit_TypeDeclarations ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'typeDeclarations' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndCompilationUnit_TypeDeclarations(CompilationUnit begin, TypeDeclaration end) {
	}

	/**
	 * Writes the XML representation of the 'hasOthers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitCompilationUnit_HasOthers(CompilationUnit begin, Positioned end) {
		createIndentation();
		ofs.println("<CompilationUnit_HasOthers>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasOthers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndCompilationUnit_HasOthers(CompilationUnit begin, Positioned end) {
		decDepth();
		createIndentation();
		ofs.println("</CompilationUnit_HasOthers>");
	}

	/**
	 * Writes the XML representation of the 'hasNewClass' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEnumConstant_HasNewClass(EnumConstant begin, NewClass end) {
		createIndentation();
		ofs.println("<EnumConstant_HasNewClass>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasNewClass' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndEnumConstant_HasNewClass(EnumConstant begin, NewClass end) {
		decDepth();
		createIndentation();
		ofs.println("</EnumConstant_HasNewClass>");
	}

	/**
	 * Writes the XML representation of the 'hasTypeParameters' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitGenericDeclaration_HasTypeParameters(GenericDeclaration begin, TypeParameter end) {
		createIndentation();
		ofs.println("<GenericDeclaration_HasTypeParameters>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTypeParameters' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndGenericDeclaration_HasTypeParameters(GenericDeclaration begin, TypeParameter end) {
		decDepth();
		createIndentation();
		ofs.println("</GenericDeclaration_HasTypeParameters>");
	}

	/**
	 * Writes the XML representation of the 'hasTarget' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitImport_HasTarget(Import begin, Expression end) {
		createIndentation();
		ofs.println("<Import_HasTarget>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasTarget' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndImport_HasTarget(Import begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Import_HasTarget>");
	}

	/**
	 * Writes the XML representation of the 'hasBody' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitInitializerBlock_HasBody(InitializerBlock begin, Block end) {
		createIndentation();
		ofs.println("<InitializerBlock_HasBody>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasBody' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndInitializerBlock_HasBody(InitializerBlock begin, Block end) {
		decDepth();
		createIndentation();
		ofs.println("</InitializerBlock_HasBody>");
	}

	/**
	 * Writes the XML representation of the 'hasReturnType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodDeclaration_HasReturnType(MethodDeclaration begin, TypeExpression end) {
		createIndentation();
		ofs.println("<MethodDeclaration_HasReturnType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasReturnType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodDeclaration_HasReturnType(MethodDeclaration begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</MethodDeclaration_HasReturnType>");
	}

	/**
	 * Writes the XML representation of the 'methodType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodDeclaration_MethodType(MethodDeclaration begin, MethodType end) {
		createIndentation();
		ofs.print("<MethodDeclaration_MethodType ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'methodType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodDeclaration_MethodType(MethodDeclaration begin, MethodType end) {
	}

	/**
	 * Writes the XML representation of the 'overrides' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodDeclaration_Overrides(MethodDeclaration begin, MethodDeclaration end) {
		createIndentation();
		ofs.print("<MethodDeclaration_Overrides ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'overrides' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodDeclaration_Overrides(MethodDeclaration begin, MethodDeclaration end) {
	}

	/**
	 * Writes the XML representation of the 'hasParameters' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNormalMethod_HasParameters(NormalMethod begin, Parameter end) {
		createIndentation();
		ofs.println("<NormalMethod_HasParameters>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasParameters' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNormalMethod_HasParameters(NormalMethod begin, Parameter end) {
		decDepth();
		createIndentation();
		ofs.println("</NormalMethod_HasParameters>");
	}

	/**
	 * Writes the XML representation of the 'hasBody' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNormalMethod_HasBody(NormalMethod begin, Block end) {
		createIndentation();
		ofs.println("<NormalMethod_HasBody>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasBody' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNormalMethod_HasBody(NormalMethod begin, Block end) {
		decDepth();
		createIndentation();
		ofs.println("</NormalMethod_HasBody>");
	}

	/**
	 * Writes the XML representation of the 'hasThrownExceptions' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitNormalMethod_HasThrownExceptions(NormalMethod begin, TypeExpression end) {
		createIndentation();
		ofs.println("<NormalMethod_HasThrownExceptions>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasThrownExceptions' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndNormalMethod_HasThrownExceptions(NormalMethod begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</NormalMethod_HasThrownExceptions>");
	}

	/**
	 * Writes the XML representation of the 'hasCompilationUnits' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitPackage_HasCompilationUnits(Package begin, CompilationUnit end) {
		createIndentation();
		ofs.println("<Package_HasCompilationUnits>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasCompilationUnits' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndPackage_HasCompilationUnits(Package begin, CompilationUnit end) {
		decDepth();
		createIndentation();
		ofs.println("</Package_HasCompilationUnits>");
	}

	/**
	 * Writes the XML representation of the 'hasPackageName' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitPackageDeclaration_HasPackageName(PackageDeclaration begin, Expression end) {
		createIndentation();
		ofs.println("<PackageDeclaration_HasPackageName>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasPackageName' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndPackageDeclaration_HasPackageName(PackageDeclaration begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</PackageDeclaration_HasPackageName>");
	}

	/**
	 * Writes the XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitPackageDeclaration_RefersTo(PackageDeclaration begin, Package end) {
		createIndentation();
		ofs.print("<PackageDeclaration_RefersTo ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndPackageDeclaration_RefersTo(PackageDeclaration begin, Package end) {
	}

	/**
	 * Writes the XML representation of the 'hasMembers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitScope_HasMembers(Scope begin, Member end) {
		createIndentation();
		ofs.println("<Scope_HasMembers>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasMembers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndScope_HasMembers(Scope begin, Member end) {
		decDepth();
		createIndentation();
		ofs.println("</Scope_HasMembers>");
	}

	/**
	 * Writes the XML representation of the 'isInCompilationUnit' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeDeclaration_IsInCompilationUnit(TypeDeclaration begin, CompilationUnit end) {
		createIndentation();
		ofs.print("<TypeDeclaration_IsInCompilationUnit ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'isInCompilationUnit' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeDeclaration_IsInCompilationUnit(TypeDeclaration begin, CompilationUnit end) {
	}

	/**
	 * Writes the XML representation of the 'hasSuperClass' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeDeclaration_HasSuperClass(TypeDeclaration begin, TypeExpression end) {
		createIndentation();
		ofs.println("<TypeDeclaration_HasSuperClass>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasSuperClass' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeDeclaration_HasSuperClass(TypeDeclaration begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeDeclaration_HasSuperClass>");
	}

	/**
	 * Writes the XML representation of the 'hasSuperInterfaces' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeDeclaration_HasSuperInterfaces(TypeDeclaration begin, TypeExpression end) {
		createIndentation();
		ofs.println("<TypeDeclaration_HasSuperInterfaces>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasSuperInterfaces' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeDeclaration_HasSuperInterfaces(TypeDeclaration begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeDeclaration_HasSuperInterfaces>");
	}

	/**
	 * Writes the XML representation of the 'hasOthers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeDeclaration_HasOthers(TypeDeclaration begin, Positioned end) {
		createIndentation();
		ofs.println("<TypeDeclaration_HasOthers>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasOthers' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeDeclaration_HasOthers(TypeDeclaration begin, Positioned end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeDeclaration_HasOthers>");
	}

	/**
	 * Writes the XML representation of the 'hasBounds' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeParameter_HasBounds(TypeParameter begin, TypeExpression end) {
		createIndentation();
		ofs.println("<TypeParameter_HasBounds>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasBounds' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeParameter_HasBounds(TypeParameter begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</TypeParameter_HasBounds>");
	}

	/**
	 * Writes the XML representation of the 'hasInitialValue' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitVariable_HasInitialValue(Variable begin, Expression end) {
		createIndentation();
		ofs.println("<Variable_HasInitialValue>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasInitialValue' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndVariable_HasInitialValue(Variable begin, Expression end) {
		decDepth();
		createIndentation();
		ofs.println("</Variable_HasInitialValue>");
	}

	/**
	 * Writes the XML representation of the 'hasType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitVariableDeclaration_HasType(VariableDeclaration begin, TypeExpression end) {
		createIndentation();
		ofs.println("<VariableDeclaration_HasType>");
		incDepth();
	}

	/**
	 * Writes the end part of XML representation of the 'hasType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndVariableDeclaration_HasType(VariableDeclaration begin, TypeExpression end) {
		decDepth();
		createIndentation();
		ofs.println("</VariableDeclaration_HasType>");
	}

	/**
	 * Writes the XML representation of the 'componentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitArrayType_ComponentType(ArrayType begin, Type end) {
		createIndentation();
		ofs.print("<ArrayType_ComponentType ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'componentType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndArrayType_ComponentType(ArrayType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitClassType_RefersTo(ClassType begin, TypeDeclaration end) {
		createIndentation();
		ofs.print("<ClassType_RefersTo ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndClassType_RefersTo(ClassType begin, TypeDeclaration end) {
	}

	/**
	 * Writes the XML representation of the 'returnType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodType_ReturnType(MethodType begin, Type end) {
		createIndentation();
		ofs.print("<MethodType_ReturnType ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'returnType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodType_ReturnType(MethodType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'parameterTypes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodType_ParameterTypes(MethodType begin, Type end) {
		createIndentation();
		ofs.print("<MethodType_ParameterTypes ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'parameterTypes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodType_ParameterTypes(MethodType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'thrownTypes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitMethodType_ThrownTypes(MethodType begin, Type end) {
		createIndentation();
		ofs.print("<MethodType_ThrownTypes ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'thrownTypes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndMethodType_ThrownTypes(MethodType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitPackageType_RefersTo(PackageType begin, Package end) {
		createIndentation();
		ofs.print("<PackageType_RefersTo ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndPackageType_RefersTo(PackageType begin, Package end) {
	}

	/**
	 * Writes the XML representation of the 'rawType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitParameterizedType_RawType(ParameterizedType begin, Type end) {
		createIndentation();
		ofs.print("<ParameterizedType_RawType ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'rawType' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndParameterizedType_RawType(ParameterizedType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'argumentTypes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitParameterizedType_ArgumentTypes(ParameterizedType begin, Type end) {
		createIndentation();
		ofs.print("<ParameterizedType_ArgumentTypes ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'argumentTypes' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndParameterizedType_ArgumentTypes(ParameterizedType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'owner' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitScopedType_Owner(ScopedType begin, Type end) {
		createIndentation();
		ofs.print("<ScopedType_Owner ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'owner' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndScopedType_Owner(ScopedType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitTypeVariable_RefersTo(TypeVariable begin, TypeParameter end) {
		createIndentation();
		ofs.print("<TypeVariable_RefersTo ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'refersTo' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndTypeVariable_RefersTo(TypeVariable begin, TypeParameter end) {
	}

	/**
	 * Writes the XML representation of the 'alternatives' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitUnionType_Alternatives(UnionType begin, Type end) {
		createIndentation();
		ofs.print("<UnionType_Alternatives ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'alternatives' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndUnionType_Alternatives(UnionType begin, Type end) {
	}

	/**
	 * Writes the XML representation of the 'bound' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitWildcardType_Bound(WildcardType begin, Type end) {
		createIndentation();
		ofs.print("<WildcardType_Bound ref='");
		if (!noId)
			ofs.print("id" + end.getId());
		ofs.println("'/>");
	}

	/**
	 * Writes the end part of XML representation of the 'bound' edge into the output file.
	 * @param begin The reference of the node the edge starts from.
	 * @param end   The reference of the node the edge points to.
	 */
	@Override
	public void visitEndWildcardType_Bound(WildcardType begin, Type end) {
	}

	/**
	 * Creates the indentation according to the depth.
	 */
	protected final void createIndentation() {
		for (int i = 0; i < depth; ++i) {
			ofs.print("	");
		}
	}

	/**
	 * Replaces the invalid characters for XML in the string.
	 */
	protected final String chk(String s) {
		return s
			.replaceAll("&", "&amp;")
			.replaceAll("<", "&lt;")
			.replaceAll(">", "&gt;")
			.replaceAll("'", "&apos;")
			.replaceAll("\"", "&quot;")
			.replaceAll("\r", "&#13;")
			.replaceAll("\n", "&#10;")
			.replaceAll("\t", "&#09;");
	}

	/**
	 * Writes out a Range attribute with name.
	 */
	protected void writeRange(String name, Range range) {
		incDepth();
		createIndentation();
		ofs.print("<" + name);
		ofs.print(" path='" + range.getPath() + "'");
		ofs.print(" line='" + range.getLine() + "'");
		ofs.print(" col='" + range.getCol() + "'");
		ofs.print(" endLine='" + range.getEndLine() + "'");
		ofs.print(" endCol='" + range.getEndCol() + "'");
		ofs.print(" wideLine='" + range.getWideLine() + "'");
		ofs.print(" wideCol='" + range.getWideCol() + "'");
		ofs.print(" wideEndLine='" + range.getWideEndLine() + "'");
		ofs.print(" wideEndCol='" + range.getWideEndCol() + "'");
		ofs.println("/>");
		decDepth();
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.Base Base} node.
	 */
	protected void writeAttributes(Base node, boolean callVirtualBase) {
		ofs.print(" id='");
		if (!noId)
			ofs.print("id" + node.getId());
		ofs.print("'");

		ofs.print(" parent='");
		if (!noId) {
			Base parent = node.getParent();
			ofs.print("id");
			ofs.print(parent == null ? 0 : parent.getId());
		}
		ofs.print("'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.BlockComment BlockComment} node.
	 */
	protected void writeAttributes(BlockComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		writeAttributes((NonJavadocComment)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.Comment Comment} node.
	 */
	protected void writeAttributes(Comment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		writeAttributes((PositionedWithoutComment)node, false);

		ofs.print(" text='" + chk(node.getText()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.Commentable Commentable} node.
	 */
	protected void writeAttributes(Commentable node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node.
	 */
	protected void writeAttributes(JavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		writeAttributes((Comment)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.LineComment LineComment} node.
	 */
	protected void writeAttributes(LineComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		writeAttributes((NonJavadocComment)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.Named Named} node.
	 */
	protected void writeAttributes(Named node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);

		ofs.print(" name='" + chk(node.getName()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.NonJavadocComment NonJavadocComment} node.
	 */
	protected void writeAttributes(NonJavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		writeAttributes((Comment)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.Positioned Positioned} node.
	 */
	protected void writeAttributes(Positioned node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((PositionedWithoutComment)node, false);

		ofs.print(" isCompilerGenerated='" + node.getIsCompilerGenerated() + "'");
		ofs.print(" isToolGenerated='" + node.getIsToolGenerated() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.base.PositionedWithoutComment PositionedWithoutComment} node.
	 */
	protected void writeAttributes(PositionedWithoutComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Annotation Annotation} node.
	 */
	protected void writeAttributes(Annotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node.
	 */
	protected void writeAttributes(ArrayAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Binary)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node.
	 */
	protected void writeAttributes(ArrayTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Assignment Assignment} node.
	 */
	protected void writeAttributes(Assignment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Binary)node, false);

		ofs.print(" operator='" + node.getOperator() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Binary Binary} node.
	 */
	protected void writeAttributes(Binary node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node.
	 */
	protected void writeAttributes(BooleanLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Literal)node, false);

		ofs.print(" booleanValue='" + node.getBooleanValue() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node.
	 */
	protected void writeAttributes(CharacterLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Literal)node, false);

		ofs.print(" charValue='" + (int)node.getCharValue() + "'");
		ofs.print(" formatString='" + chk(node.getFormatString()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node.
	 */
	protected void writeAttributes(ClassLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Conditional Conditional} node.
	 */
	protected void writeAttributes(Conditional node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node.
	 */
	protected void writeAttributes(DoubleLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((NumberLiteral)node, false);

		ofs.print(" doubleValue='" + node.getDoubleValue() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Erroneous Erroneous} node.
	 */
	protected void writeAttributes(Erroneous node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node.
	 */
	protected void writeAttributes(ErroneousTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Expression Expression} node.
	 */
	protected void writeAttributes(Expression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node.
	 */
	protected void writeAttributes(ExternalTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node.
	 */
	protected void writeAttributes(FieldAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Binary)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node.
	 */
	protected void writeAttributes(FloatLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((NumberLiteral)node, false);

		ofs.print(" floatValue='" + node.getFloatValue() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Identifier Identifier} node.
	 */
	protected void writeAttributes(Identifier node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

		ofs.print(" name='" + chk(node.getName()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node.
	 */
	protected void writeAttributes(InfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Binary)node, false);

		ofs.print(" operator='" + node.getOperator() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node.
	 */
	protected void writeAttributes(InstanceOf node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node.
	 */
	protected void writeAttributes(IntegerLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((NumberLiteral)node, false);

		ofs.print(" intValue='" + node.getIntValue() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Literal Literal} node.
	 */
	protected void writeAttributes(Literal node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node.
	 */
	protected void writeAttributes(LongLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((NumberLiteral)node, false);

		ofs.print(" longValue='" + node.getLongValue() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node.
	 */
	protected void writeAttributes(MarkerAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Annotation)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node.
	 */
	protected void writeAttributes(MethodInvocation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.NewArray NewArray} node.
	 */
	protected void writeAttributes(NewArray node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.NewClass NewClass} node.
	 */
	protected void writeAttributes(NewClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node.
	 */
	protected void writeAttributes(NormalAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Annotation)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node.
	 */
	protected void writeAttributes(NullLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.NumberLiteral NumberLiteral} node.
	 */
	protected void writeAttributes(NumberLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Literal)node, false);

		ofs.print(" value='" + chk(node.getValue()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node.
	 */
	protected void writeAttributes(ParenthesizedExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node.
	 */
	protected void writeAttributes(PostfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Unary)node, false);

		ofs.print(" operator='" + node.getOperator() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node.
	 */
	protected void writeAttributes(PrefixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Unary)node, false);

		ofs.print(" operator='" + node.getOperator() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node.
	 */
	protected void writeAttributes(PrimitiveTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

		ofs.print(" kind='" + node.getKind() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node.
	 */
	protected void writeAttributes(QualifiedTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node.
	 */
	protected void writeAttributes(SimpleTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

		ofs.print(" name='" + chk(node.getName()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node.
	 */
	protected void writeAttributes(SingleElementAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Annotation)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node.
	 */
	protected void writeAttributes(StringLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Literal)node, false);

		ofs.print(" value='" + chk(node.getValue()) + "'");
		ofs.print(" formatString='" + chk(node.getFormatString()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Super Super} node.
	 */
	protected void writeAttributes(Super node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.This This} node.
	 */
	protected void writeAttributes(This node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node.
	 */
	protected void writeAttributes(TypeApplyExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.TypeCast TypeCast} node.
	 */
	protected void writeAttributes(TypeCast node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.TypeExpression TypeExpression} node.
	 */
	protected void writeAttributes(TypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node.
	 */
	protected void writeAttributes(TypeUnionExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.Unary Unary} node.
	 */
	protected void writeAttributes(Unary node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node.
	 */
	protected void writeAttributes(WildcardExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((TypeExpression)node, false);

		ofs.print(" kind='" + node.getKind() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Assert Assert} node.
	 */
	protected void writeAttributes(Assert node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.BasicFor BasicFor} node.
	 */
	protected void writeAttributes(BasicFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((For)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Block Block} node.
	 */
	protected void writeAttributes(Block node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Break Break} node.
	 */
	protected void writeAttributes(Break node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Jump)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Case Case} node.
	 */
	protected void writeAttributes(Case node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((SwitchLabel)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Continue Continue} node.
	 */
	protected void writeAttributes(Continue node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Jump)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Default Default} node.
	 */
	protected void writeAttributes(Default node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((SwitchLabel)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Do Do} node.
	 */
	protected void writeAttributes(Do node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Iteration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Empty Empty} node.
	 */
	protected void writeAttributes(Empty node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node.
	 */
	protected void writeAttributes(EnhancedFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((For)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node.
	 */
	protected void writeAttributes(ExpressionStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.For For} node.
	 */
	protected void writeAttributes(For node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Iteration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Handler Handler} node.
	 */
	protected void writeAttributes(Handler node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.If If} node.
	 */
	protected void writeAttributes(If node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Selection)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Iteration Iteration} node.
	 */
	protected void writeAttributes(Iteration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Jump Jump} node.
	 */
	protected void writeAttributes(Jump node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

		ofs.print(" label='" + chk(node.getLabel()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node.
	 */
	protected void writeAttributes(LabeledStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

		ofs.print(" label='" + chk(node.getLabel()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Return Return} node.
	 */
	protected void writeAttributes(Return node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Selection Selection} node.
	 */
	protected void writeAttributes(Selection node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Statement Statement} node.
	 */
	protected void writeAttributes(Statement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Switch Switch} node.
	 */
	protected void writeAttributes(Switch node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Selection)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.SwitchLabel SwitchLabel} node.
	 */
	protected void writeAttributes(SwitchLabel node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Synchronized Synchronized} node.
	 */
	protected void writeAttributes(Synchronized node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Throw Throw} node.
	 */
	protected void writeAttributes(Throw node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.Try Try} node.
	 */
	protected void writeAttributes(Try node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.statm.While While} node.
	 */
	protected void writeAttributes(While node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Iteration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.AnnotatedElement AnnotatedElement} node.
	 */
	protected void writeAttributes(AnnotatedElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node.
	 */
	protected void writeAttributes(AnnotationType node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((TypeDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node.
	 */
	protected void writeAttributes(AnnotationTypeElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((MethodDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node.
	 */
	protected void writeAttributes(AnonymousClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((ClassDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Class Class} node.
	 */
	protected void writeAttributes(Class node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((ClassDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.ClassDeclaration ClassDeclaration} node.
	 */
	protected void writeAttributes(ClassDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((TypeDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node.
	 */
	protected void writeAttributes(ClassGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((ClassDeclaration)node, false);
		writeAttributes((GenericDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node.
	 */
	protected void writeAttributes(CompilationUnit node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		writeAttributes((PositionedWithoutComment)node, false);
		writeAttributes((Commentable)node, false);

		ofs.print(" fileEncoding='" + chk(node.getFileEncoding()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Declaration Declaration} node.
	 */
	protected void writeAttributes(Declaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Enum Enum} node.
	 */
	protected void writeAttributes(Enum node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((TypeDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node.
	 */
	protected void writeAttributes(EnumConstant node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((VariableDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.GenericDeclaration GenericDeclaration} node.
	 */
	protected void writeAttributes(GenericDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Import Import} node.
	 */
	protected void writeAttributes(Import node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Positioned)node, false);

		ofs.print(" isStatic='" + node.getIsStatic() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.InitializerBlock InitializerBlock} node.
	 */
	protected void writeAttributes(InitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((Declaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node.
	 */
	protected void writeAttributes(InstanceInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((InitializerBlock)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Interface Interface} node.
	 */
	protected void writeAttributes(Interface node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((InterfaceDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.InterfaceDeclaration InterfaceDeclaration} node.
	 */
	protected void writeAttributes(InterfaceDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((TypeDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node.
	 */
	protected void writeAttributes(InterfaceGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((InterfaceDeclaration)node, false);
		writeAttributes((GenericDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Member Member} node.
	 */
	protected void writeAttributes(Member node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((AnnotatedElement)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Method Method} node.
	 */
	protected void writeAttributes(Method node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((NormalMethod)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration} node.
	 */
	protected void writeAttributes(MethodDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((NamedDeclaration)node, false);

		ofs.print(" isAbstract='" + node.getIsAbstract() + "'");
		ofs.print(" isStrictfp='" + node.getIsStrictfp() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node.
	 */
	protected void writeAttributes(MethodGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((NormalMethod)node, false);
		writeAttributes((GenericDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.NamedDeclaration NamedDeclaration} node.
	 */
	protected void writeAttributes(NamedDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((Declaration)node, false);
		writeAttributes((Named)node, false);

		ofs.print(" accessibility='" + node.getAccessibility() + "'");
		ofs.print(" isStatic='" + node.getIsStatic() + "'");
		ofs.print(" isFinal='" + node.getIsFinal() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.NormalMethod NormalMethod} node.
	 */
	protected void writeAttributes(NormalMethod node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((MethodDeclaration)node, false);

		ofs.print(" methodKind='" + node.getMethodKind() + "'");
		ofs.print(" isSynchronized='" + node.getIsSynchronized() + "'");
		ofs.print(" isNative='" + node.getIsNative() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Package Package} node.
	 */
	protected void writeAttributes(Package node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((Named)node, false);
		writeAttributes((Scope)node, false);

		ofs.print(" qualifiedName='" + chk(node.getQualifiedName()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node.
	 */
	protected void writeAttributes(PackageDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Parameter Parameter} node.
	 */
	protected void writeAttributes(Parameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((VariableDeclaration)node, false);

		ofs.print(" isVarargs='" + node.getIsVarargs() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Scope Scope} node.
	 */
	protected void writeAttributes(Scope node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node.
	 */
	protected void writeAttributes(StaticInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((InitializerBlock)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration} node.
	 */
	protected void writeAttributes(TypeDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((NamedDeclaration)node, false);
		writeAttributes((Scope)node, false);

		ofs.print(" isAbstract='" + node.getIsAbstract() + "'");
		ofs.print(" isStrictfp='" + node.getIsStrictfp() + "'");
		ofs.print(" binaryName='" + chk(node.getBinaryName()) + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node.
	 */
	protected void writeAttributes(TypeParameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		writeAttributes((Positioned)node, false);
		writeAttributes((Named)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.Variable Variable} node.
	 */
	protected void writeAttributes(Variable node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((VariableDeclaration)node, false);

		ofs.print(" isTransient='" + node.getIsTransient() + "'");
		ofs.print(" isVolatile='" + node.getIsVolatile() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.struc.VariableDeclaration VariableDeclaration} node.
	 */
	protected void writeAttributes(VariableDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeAttributes((Base)node, false);
		if (callVirtualBase)
			writeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeAttributes((Member)node, false);
		writeAttributes((NamedDeclaration)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.ArrayType ArrayType} node.
	 */
	protected void writeAttributes(ArrayType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

		ofs.print(" size='" + node.getSize() + "'");
	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.BooleanType BooleanType} node.
	 */
	protected void writeAttributes(BooleanType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.BoundedWildcardType BoundedWildcardType} node.
	 */
	protected void writeAttributes(BoundedWildcardType node, boolean callVirtualBase) {
		writeAttributes((WildcardType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.ByteType ByteType} node.
	 */
	protected void writeAttributes(ByteType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.CharType CharType} node.
	 */
	protected void writeAttributes(CharType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.ClassType ClassType} node.
	 */
	protected void writeAttributes(ClassType node, boolean callVirtualBase) {
		writeAttributes((ScopedType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.DoubleType DoubleType} node.
	 */
	protected void writeAttributes(DoubleType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.ErrorType ErrorType} node.
	 */
	protected void writeAttributes(ErrorType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.FloatType FloatType} node.
	 */
	protected void writeAttributes(FloatType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.IntType IntType} node.
	 */
	protected void writeAttributes(IntType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.LongType LongType} node.
	 */
	protected void writeAttributes(LongType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node.
	 */
	protected void writeAttributes(LowerBoundedWildcardType node, boolean callVirtualBase) {
		writeAttributes((BoundedWildcardType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.MethodType MethodType} node.
	 */
	protected void writeAttributes(MethodType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.NoType NoType} node.
	 */
	protected void writeAttributes(NoType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.NullType NullType} node.
	 */
	protected void writeAttributes(NullType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.PackageType PackageType} node.
	 */
	protected void writeAttributes(PackageType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node.
	 */
	protected void writeAttributes(ParameterizedType node, boolean callVirtualBase) {
		writeAttributes((ScopedType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.PrimitiveType PrimitiveType} node.
	 */
	protected void writeAttributes(PrimitiveType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.ScopedType ScopedType} node.
	 */
	protected void writeAttributes(ScopedType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.ShortType ShortType} node.
	 */
	protected void writeAttributes(ShortType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.Type Type} node.
	 */
	protected void writeAttributes(Type node, boolean callVirtualBase) {
		writeAttributes((Base)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node.
	 */
	protected void writeAttributes(TypeVariable node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node.
	 */
	protected void writeAttributes(UnboundedWildcardType node, boolean callVirtualBase) {
		writeAttributes((WildcardType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.UnionType UnionType} node.
	 */
	protected void writeAttributes(UnionType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node.
	 */
	protected void writeAttributes(UpperBoundedWildcardType node, boolean callVirtualBase) {
		writeAttributes((BoundedWildcardType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.VoidType VoidType} node.
	 */
	protected void writeAttributes(VoidType node, boolean callVirtualBase) {
		writeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the attributes of the {@link columbus.java.asg.type.WildcardType WildcardType} node.
	 */
	protected void writeAttributes(WildcardType node, boolean callVirtualBase) {
		writeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.Base Base} node.
	 */
	protected void writeCompositeAttributes(Base node, boolean callVirtualBase) {
	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.BlockComment BlockComment} node.
	 */
	protected void writeCompositeAttributes(BlockComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		writeCompositeAttributes((NonJavadocComment)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.Comment Comment} node.
	 */
	protected void writeCompositeAttributes(Comment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		writeCompositeAttributes((PositionedWithoutComment)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.Commentable Commentable} node.
	 */
	protected void writeCompositeAttributes(Commentable node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.JavadocComment JavadocComment} node.
	 */
	protected void writeCompositeAttributes(JavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		writeCompositeAttributes((Comment)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.LineComment LineComment} node.
	 */
	protected void writeCompositeAttributes(LineComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		writeCompositeAttributes((NonJavadocComment)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.Named Named} node.
	 */
	protected void writeCompositeAttributes(Named node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);

		writeRange("NamePosition", node.getNamePosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.NonJavadocComment NonJavadocComment} node.
	 */
	protected void writeCompositeAttributes(NonJavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		writeCompositeAttributes((Comment)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.Positioned Positioned} node.
	 */
	protected void writeCompositeAttributes(Positioned node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((PositionedWithoutComment)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.base.PositionedWithoutComment PositionedWithoutComment} node.
	 */
	protected void writeCompositeAttributes(PositionedWithoutComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);

		writeRange("Position", node.getPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Annotation Annotation} node.
	 */
	protected void writeCompositeAttributes(Annotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.ArrayAccess ArrayAccess} node.
	 */
	protected void writeCompositeAttributes(ArrayAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Binary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.ArrayTypeExpression ArrayTypeExpression} node.
	 */
	protected void writeCompositeAttributes(ArrayTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Assignment Assignment} node.
	 */
	protected void writeCompositeAttributes(Assignment node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Binary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Binary Binary} node.
	 */
	protected void writeCompositeAttributes(Binary node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.BooleanLiteral BooleanLiteral} node.
	 */
	protected void writeCompositeAttributes(BooleanLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.CharacterLiteral CharacterLiteral} node.
	 */
	protected void writeCompositeAttributes(CharacterLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.ClassLiteral ClassLiteral} node.
	 */
	protected void writeCompositeAttributes(ClassLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Conditional Conditional} node.
	 */
	protected void writeCompositeAttributes(Conditional node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

		writeRange("ColonPosition", node.getColonPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.DoubleLiteral DoubleLiteral} node.
	 */
	protected void writeCompositeAttributes(DoubleLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((NumberLiteral)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Erroneous Erroneous} node.
	 */
	protected void writeCompositeAttributes(Erroneous node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node.
	 */
	protected void writeCompositeAttributes(ErroneousTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Expression Expression} node.
	 */
	protected void writeCompositeAttributes(Expression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.ExternalTypeExpression ExternalTypeExpression} node.
	 */
	protected void writeCompositeAttributes(ExternalTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.FieldAccess FieldAccess} node.
	 */
	protected void writeCompositeAttributes(FieldAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Binary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.FloatLiteral FloatLiteral} node.
	 */
	protected void writeCompositeAttributes(FloatLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((NumberLiteral)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Identifier Identifier} node.
	 */
	protected void writeCompositeAttributes(Identifier node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.InfixExpression InfixExpression} node.
	 */
	protected void writeCompositeAttributes(InfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Binary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node.
	 */
	protected void writeCompositeAttributes(InstanceOf node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.IntegerLiteral IntegerLiteral} node.
	 */
	protected void writeCompositeAttributes(IntegerLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((NumberLiteral)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Literal Literal} node.
	 */
	protected void writeCompositeAttributes(Literal node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.LongLiteral LongLiteral} node.
	 */
	protected void writeCompositeAttributes(LongLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((NumberLiteral)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.MarkerAnnotation MarkerAnnotation} node.
	 */
	protected void writeCompositeAttributes(MarkerAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Annotation)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.MethodInvocation MethodInvocation} node.
	 */
	protected void writeCompositeAttributes(MethodInvocation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.NewArray NewArray} node.
	 */
	protected void writeCompositeAttributes(NewArray node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

		writeRange("LeftBracePosition", node.getLeftBracePosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.NewClass NewClass} node.
	 */
	protected void writeCompositeAttributes(NewClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node.
	 */
	protected void writeCompositeAttributes(NormalAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Annotation)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.NullLiteral NullLiteral} node.
	 */
	protected void writeCompositeAttributes(NullLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.NumberLiteral NumberLiteral} node.
	 */
	protected void writeCompositeAttributes(NumberLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.ParenthesizedExpression ParenthesizedExpression} node.
	 */
	protected void writeCompositeAttributes(ParenthesizedExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.PostfixExpression PostfixExpression} node.
	 */
	protected void writeCompositeAttributes(PostfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.PrefixExpression PrefixExpression} node.
	 */
	protected void writeCompositeAttributes(PrefixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.PrimitiveTypeExpression PrimitiveTypeExpression} node.
	 */
	protected void writeCompositeAttributes(PrimitiveTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node.
	 */
	protected void writeCompositeAttributes(QualifiedTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression} node.
	 */
	protected void writeCompositeAttributes(SimpleTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.SingleElementAnnotation SingleElementAnnotation} node.
	 */
	protected void writeCompositeAttributes(SingleElementAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Annotation)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.StringLiteral StringLiteral} node.
	 */
	protected void writeCompositeAttributes(StringLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Literal)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Super Super} node.
	 */
	protected void writeCompositeAttributes(Super node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.This This} node.
	 */
	protected void writeCompositeAttributes(This node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node.
	 */
	protected void writeCompositeAttributes(TypeApplyExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.TypeCast TypeCast} node.
	 */
	protected void writeCompositeAttributes(TypeCast node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Unary)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.TypeExpression TypeExpression} node.
	 */
	protected void writeCompositeAttributes(TypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.TypeUnionExpression TypeUnionExpression} node.
	 */
	protected void writeCompositeAttributes(TypeUnionExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.Unary Unary} node.
	 */
	protected void writeCompositeAttributes(Unary node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Expression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node.
	 */
	protected void writeCompositeAttributes(WildcardExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((TypeExpression)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Assert Assert} node.
	 */
	protected void writeCompositeAttributes(Assert node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

		writeRange("ColonPosition", node.getColonPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.BasicFor BasicFor} node.
	 */
	protected void writeCompositeAttributes(BasicFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((For)node, false);

		writeRange("FirstSemiPosition", node.getFirstSemiPosition());

		writeRange("SecondSemiPosition", node.getSecondSemiPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Block Block} node.
	 */
	protected void writeCompositeAttributes(Block node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Break Break} node.
	 */
	protected void writeCompositeAttributes(Break node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Jump)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Case Case} node.
	 */
	protected void writeCompositeAttributes(Case node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((SwitchLabel)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Continue Continue} node.
	 */
	protected void writeCompositeAttributes(Continue node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Jump)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Default Default} node.
	 */
	protected void writeCompositeAttributes(Default node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((SwitchLabel)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Do Do} node.
	 */
	protected void writeCompositeAttributes(Do node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Iteration)node, false);

		writeRange("WhilePosition", node.getWhilePosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Empty Empty} node.
	 */
	protected void writeCompositeAttributes(Empty node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.EnhancedFor EnhancedFor} node.
	 */
	protected void writeCompositeAttributes(EnhancedFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((For)node, false);

		writeRange("ColonPosition", node.getColonPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node.
	 */
	protected void writeCompositeAttributes(ExpressionStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.For For} node.
	 */
	protected void writeCompositeAttributes(For node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Iteration)node, false);

		writeRange("LeftParenPosition", node.getLeftParenPosition());

		writeRange("RightParenPosition", node.getRightParenPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Handler Handler} node.
	 */
	protected void writeCompositeAttributes(Handler node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Positioned)node, false);

		writeRange("LeftParenPosition", node.getLeftParenPosition());

		writeRange("RightParenPosition", node.getRightParenPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.If If} node.
	 */
	protected void writeCompositeAttributes(If node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Selection)node, false);

		writeRange("ElsePosition", node.getElsePosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Iteration Iteration} node.
	 */
	protected void writeCompositeAttributes(Iteration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Jump Jump} node.
	 */
	protected void writeCompositeAttributes(Jump node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

		writeRange("LabelPosition", node.getLabelPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node.
	 */
	protected void writeCompositeAttributes(LabeledStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

		writeRange("ColonPosition", node.getColonPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Return Return} node.
	 */
	protected void writeCompositeAttributes(Return node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Selection Selection} node.
	 */
	protected void writeCompositeAttributes(Selection node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Statement Statement} node.
	 */
	protected void writeCompositeAttributes(Statement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Switch Switch} node.
	 */
	protected void writeCompositeAttributes(Switch node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Selection)node, false);

		writeRange("BlockStartPosition", node.getBlockStartPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.SwitchLabel SwitchLabel} node.
	 */
	protected void writeCompositeAttributes(SwitchLabel node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Positioned)node, false);

		writeRange("ColonPosition", node.getColonPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Synchronized Synchronized} node.
	 */
	protected void writeCompositeAttributes(Synchronized node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Throw Throw} node.
	 */
	protected void writeCompositeAttributes(Throw node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.Try Try} node.
	 */
	protected void writeCompositeAttributes(Try node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Statement)node, false);

		writeRange("ResourceLeftParenPosition", node.getResourceLeftParenPosition());

		writeRange("ResourceRightParenPosition", node.getResourceRightParenPosition());

		writeRange("FinallyPosition", node.getFinallyPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.statm.While While} node.
	 */
	protected void writeCompositeAttributes(While node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Iteration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.AnnotatedElement AnnotatedElement} node.
	 */
	protected void writeCompositeAttributes(AnnotatedElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.AnnotationType AnnotationType} node.
	 */
	protected void writeCompositeAttributes(AnnotationType node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((TypeDeclaration)node, false);

		writeRange("AtSignPosition", node.getAtSignPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node.
	 */
	protected void writeCompositeAttributes(AnnotationTypeElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((MethodDeclaration)node, false);

		writeRange("DefaultPosition", node.getDefaultPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.AnonymousClass AnonymousClass} node.
	 */
	protected void writeCompositeAttributes(AnonymousClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((ClassDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Class Class} node.
	 */
	protected void writeCompositeAttributes(Class node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((ClassDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.ClassDeclaration ClassDeclaration} node.
	 */
	protected void writeCompositeAttributes(ClassDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((TypeDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.ClassGeneric ClassGeneric} node.
	 */
	protected void writeCompositeAttributes(ClassGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((ClassDeclaration)node, false);
		writeCompositeAttributes((GenericDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node.
	 */
	protected void writeCompositeAttributes(CompilationUnit node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		writeCompositeAttributes((PositionedWithoutComment)node, false);
		writeCompositeAttributes((Commentable)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Declaration Declaration} node.
	 */
	protected void writeCompositeAttributes(Declaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((Statement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Enum Enum} node.
	 */
	protected void writeCompositeAttributes(Enum node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((TypeDeclaration)node, false);

		writeRange("SemiPosition", node.getSemiPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node.
	 */
	protected void writeCompositeAttributes(EnumConstant node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((VariableDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.GenericDeclaration GenericDeclaration} node.
	 */
	protected void writeCompositeAttributes(GenericDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Import Import} node.
	 */
	protected void writeCompositeAttributes(Import node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Positioned)node, false);

		writeRange("StaticPosition", node.getStaticPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.InitializerBlock InitializerBlock} node.
	 */
	protected void writeCompositeAttributes(InitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((Declaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.InstanceInitializerBlock InstanceInitializerBlock} node.
	 */
	protected void writeCompositeAttributes(InstanceInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((InitializerBlock)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Interface Interface} node.
	 */
	protected void writeCompositeAttributes(Interface node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((InterfaceDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.InterfaceDeclaration InterfaceDeclaration} node.
	 */
	protected void writeCompositeAttributes(InterfaceDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((TypeDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.InterfaceGeneric InterfaceGeneric} node.
	 */
	protected void writeCompositeAttributes(InterfaceGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((InterfaceDeclaration)node, false);
		writeCompositeAttributes((GenericDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Member Member} node.
	 */
	protected void writeCompositeAttributes(Member node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((AnnotatedElement)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Method Method} node.
	 */
	protected void writeCompositeAttributes(Method node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((NormalMethod)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration} node.
	 */
	protected void writeCompositeAttributes(MethodDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((NamedDeclaration)node, false);

		writeRange("AbstractPosition", node.getAbstractPosition());

		writeRange("StrictfpPosition", node.getStrictfpPosition());

		writeRange("ParametersStartPosition", node.getParametersStartPosition());

		writeRange("ParametersEndPosition", node.getParametersEndPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.MethodGeneric MethodGeneric} node.
	 */
	protected void writeCompositeAttributes(MethodGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((NormalMethod)node, false);
		writeCompositeAttributes((GenericDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.NamedDeclaration NamedDeclaration} node.
	 */
	protected void writeCompositeAttributes(NamedDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((Declaration)node, false);
		writeCompositeAttributes((Named)node, false);

		writeRange("AccessibilityPosition", node.getAccessibilityPosition());

		writeRange("StaticPosition", node.getStaticPosition());

		writeRange("FinalPosition", node.getFinalPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.NormalMethod NormalMethod} node.
	 */
	protected void writeCompositeAttributes(NormalMethod node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((MethodDeclaration)node, false);

		writeRange("SynchronizedPosition", node.getSynchronizedPosition());

		writeRange("NativePosition", node.getNativePosition());

		writeRange("ThrowsPosition", node.getThrowsPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Package Package} node.
	 */
	protected void writeCompositeAttributes(Package node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((Named)node, false);
		writeCompositeAttributes((Scope)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node.
	 */
	protected void writeCompositeAttributes(PackageDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Positioned)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Parameter Parameter} node.
	 */
	protected void writeCompositeAttributes(Parameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((VariableDeclaration)node, false);

		writeRange("VarargsPosition", node.getVarargsPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Scope Scope} node.
	 */
	protected void writeCompositeAttributes(Scope node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node.
	 */
	protected void writeCompositeAttributes(StaticInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((InitializerBlock)node, false);

		writeRange("BlockStartPosition", node.getBlockStartPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration} node.
	 */
	protected void writeCompositeAttributes(TypeDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((NamedDeclaration)node, false);
		writeCompositeAttributes((Scope)node, false);

		writeRange("TypeNamePosition", node.getTypeNamePosition());

		writeRange("AbstractPosition", node.getAbstractPosition());

		writeRange("StrictfpPosition", node.getStrictfpPosition());

		writeRange("ExtendsPosition", node.getExtendsPosition());

		writeRange("ImplementsPosition", node.getImplementsPosition());

		writeRange("BodyStartPosition", node.getBodyStartPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node.
	 */
	protected void writeCompositeAttributes(TypeParameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		writeCompositeAttributes((Positioned)node, false);
		writeCompositeAttributes((Named)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.Variable Variable} node.
	 */
	protected void writeCompositeAttributes(Variable node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((VariableDeclaration)node, false);

		writeRange("TransientPosition", node.getTransientPosition());

		writeRange("VolatilePosition", node.getVolatilePosition());

		writeRange("EqualSignPosition", node.getEqualSignPosition());

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.struc.VariableDeclaration VariableDeclaration} node.
	 */
	protected void writeCompositeAttributes(VariableDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			writeCompositeAttributes((Base)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Commentable)node, false);
		if (callVirtualBase)
			writeCompositeAttributes((Member)node, false);
		writeCompositeAttributes((NamedDeclaration)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.ArrayType ArrayType} node.
	 */
	protected void writeCompositeAttributes(ArrayType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.BooleanType BooleanType} node.
	 */
	protected void writeCompositeAttributes(BooleanType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.BoundedWildcardType BoundedWildcardType} node.
	 */
	protected void writeCompositeAttributes(BoundedWildcardType node, boolean callVirtualBase) {
		writeCompositeAttributes((WildcardType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.ByteType ByteType} node.
	 */
	protected void writeCompositeAttributes(ByteType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.CharType CharType} node.
	 */
	protected void writeCompositeAttributes(CharType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.ClassType ClassType} node.
	 */
	protected void writeCompositeAttributes(ClassType node, boolean callVirtualBase) {
		writeCompositeAttributes((ScopedType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.DoubleType DoubleType} node.
	 */
	protected void writeCompositeAttributes(DoubleType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.ErrorType ErrorType} node.
	 */
	protected void writeCompositeAttributes(ErrorType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.FloatType FloatType} node.
	 */
	protected void writeCompositeAttributes(FloatType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.IntType IntType} node.
	 */
	protected void writeCompositeAttributes(IntType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.LongType LongType} node.
	 */
	protected void writeCompositeAttributes(LongType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node.
	 */
	protected void writeCompositeAttributes(LowerBoundedWildcardType node, boolean callVirtualBase) {
		writeCompositeAttributes((BoundedWildcardType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.MethodType MethodType} node.
	 */
	protected void writeCompositeAttributes(MethodType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.NoType NoType} node.
	 */
	protected void writeCompositeAttributes(NoType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.NullType NullType} node.
	 */
	protected void writeCompositeAttributes(NullType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.PackageType PackageType} node.
	 */
	protected void writeCompositeAttributes(PackageType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node.
	 */
	protected void writeCompositeAttributes(ParameterizedType node, boolean callVirtualBase) {
		writeCompositeAttributes((ScopedType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.PrimitiveType PrimitiveType} node.
	 */
	protected void writeCompositeAttributes(PrimitiveType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.ScopedType ScopedType} node.
	 */
	protected void writeCompositeAttributes(ScopedType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.ShortType ShortType} node.
	 */
	protected void writeCompositeAttributes(ShortType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.Type Type} node.
	 */
	protected void writeCompositeAttributes(Type node, boolean callVirtualBase) {
		writeCompositeAttributes((Base)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.TypeVariable TypeVariable} node.
	 */
	protected void writeCompositeAttributes(TypeVariable node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node.
	 */
	protected void writeCompositeAttributes(UnboundedWildcardType node, boolean callVirtualBase) {
		writeCompositeAttributes((WildcardType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.UnionType UnionType} node.
	 */
	protected void writeCompositeAttributes(UnionType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node.
	 */
	protected void writeCompositeAttributes(UpperBoundedWildcardType node, boolean callVirtualBase) {
		writeCompositeAttributes((BoundedWildcardType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.VoidType VoidType} node.
	 */
	protected void writeCompositeAttributes(VoidType node, boolean callVirtualBase) {
		writeCompositeAttributes((PrimitiveType)node, false);

	}

	/**
	 * Writes out the composite attributes of the {@link columbus.java.asg.type.WildcardType WildcardType} node.
	 */
	protected void writeCompositeAttributes(WildcardType node, boolean callVirtualBase) {
		writeCompositeAttributes((Type)node, false);

	}

}
