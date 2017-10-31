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

import java.util.HashSet;
import java.util.TreeSet;

import columbus.StrTable.StrType;
import columbus.java.asg.*;
import columbus.java.asg.algorithms.AlgorithmPreorder;
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

public class VisitorSpecFilter extends VisitorAbstractNodes {

	private Factory factory;

	private AlgorithmPreorder ap;

	private boolean[] visited;

	private TreeSet<Integer> roots;

	private TreeSet<Integer> referred;

	private HashSet<Integer> keys;

	public VisitorSpecFilter(Factory factory) {
		this.factory = factory;
		this.ap = new AlgorithmPreorder();
		ap.setVisitSpecialNodes(false, false);
		visited = new boolean[factory.size()];
		roots = new TreeSet<Integer>();
		referred = new TreeSet<Integer>();
		keys = new HashSet<Integer>();
	}

	public void init() {
		visited = new boolean[factory.size()];
		roots = new TreeSet<Integer>();
		referred = new TreeSet<Integer>();
		restoreStrTable();
	}

	public void addRoot(Base node) {
		if (node != null) {
			roots.add(node.getId());
			addRef(node);
		}
	}

	public void run() {
		int nodeId;
		while (!roots.isEmpty() || !referred.isEmpty()) {
			while (!roots.isEmpty()) {
				nodeId = roots.first();
				roots.remove(nodeId);
				if (!visited[nodeId])
					ap.run(factory, this, nodeId);
			}

			while (!referred.isEmpty()) {
				if (!roots.isEmpty())
					break;
				nodeId = referred.first();
				referred.remove(nodeId);
				if (!visited[nodeId]) {
					Base node = factory.getRef(nodeId);
					switch (node.getNodeKind()) {
						case ndkBlockComment:
						case ndkJavadocComment:
						case ndkLineComment:
						case ndkArrayType:
						case ndkBooleanType:
						case ndkByteType:
						case ndkCharType:
						case ndkClassType:
						case ndkDoubleType:
						case ndkErrorType:
						case ndkFloatType:
						case ndkIntType:
						case ndkLongType:
						case ndkLowerBoundedWildcardType:
						case ndkMethodType:
						case ndkNoType:
						case ndkNullType:
						case ndkPackageType:
						case ndkParameterizedType:
						case ndkShortType:
						case ndkTypeVariable:
						case ndkUnboundedWildcardType:
						case ndkUnionType:
						case ndkUpperBoundedWildcardType:
						case ndkVoidType:
							ap.run(factory, this, node);
							break;
						default:
							node.accept(this);
							break;
					}
				}
			}
		}
	}

	public void createFilter() {
		factory.initializeFilter(); // reset filter

		for (int i = 0; i < visited.length; i++)
			if (!visited[i])
				factory.setFilteredThisNodeOnly(i);

		for (int i : keys)
			factory.getStringTable().setType(i, StrType.strToSave);
	}

	public void restoreStrTable() {
		for (int i : keys)
			factory.getStringTable().setType(i, StrType.strDefault);
		keys.clear();
	}

	public void addRef(Base node) {
		while (node != null && !visited[node.getId()]) {
			referred.add(node.getId());
			node = node.getParent();
		}
	}

	@Override
	public void visit(Base node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		visited[node.getId()] = true;
	}

	@Override
	public void visit(BlockComment node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Comment node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getTextKey());
	}

	@Override
	public void visit(Commentable node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		for (EdgeIterator<Comment> it = node.getCommentsIterator(); it.hasNext(); ) {
			addRef(it.next());
		}
	}

	@Override
	public void visit(JavadocComment node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(LineComment node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Named node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getNameKey());

		keys.add(node.getNamePosition().getPathKey());
	}

	@Override
	public void visit(NonJavadocComment node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Positioned node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(PositionedWithoutComment node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getPosition().getPathKey());
	}

	@Override
	public void visit(Annotation node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ArrayAccess node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ArrayTypeExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Assignment node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Binary node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(BooleanLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(CharacterLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getFormatStringKey());
	}

	@Override
	public void visit(ClassLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Conditional node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getColonPosition().getPathKey());
	}

	@Override
	public void visit(DoubleLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Erroneous node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ErroneousTypeExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Expression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getType());
	}

	@Override
	public void visit(ExternalTypeExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(FieldAccess node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(FloatLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Identifier node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getNameKey());

		addRef(node.getRefersTo());
	}

	@Override
	public void visit(InfixExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(InstanceOf node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(IntegerLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Literal node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(LongLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(MarkerAnnotation node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(MethodInvocation node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getInvokes());
	}

	@Override
	public void visit(NewArray node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getLeftBracePosition().getPathKey());
	}

	@Override
	public void visit(NewClass node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getConstructor());
	}

	@Override
	public void visit(NormalAnnotation node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(NullLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(NumberLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getValueKey());
	}

	@Override
	public void visit(ParenthesizedExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(PostfixExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(PrefixExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(PrimitiveTypeExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(QualifiedTypeExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(SimpleTypeExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getNameKey());
	}

	@Override
	public void visit(SingleElementAnnotation node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(StringLiteral node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getValueKey());

		keys.add(node.getFormatStringKey());
	}

	@Override
	public void visit(Super node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(This node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(TypeApplyExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(TypeCast node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(TypeExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(TypeUnionExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Unary node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(WildcardExpression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Assert node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getColonPosition().getPathKey());
	}

	@Override
	public void visit(BasicFor node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getFirstSemiPosition().getPathKey());

		keys.add(node.getSecondSemiPosition().getPathKey());
	}

	@Override
	public void visit(Block node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Break node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Case node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Continue node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Default node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Do node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getWhilePosition().getPathKey());
	}

	@Override
	public void visit(Empty node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(EnhancedFor node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getColonPosition().getPathKey());
	}

	@Override
	public void visit(ExpressionStatement node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(For node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getLeftParenPosition().getPathKey());

		keys.add(node.getRightParenPosition().getPathKey());
	}

	@Override
	public void visit(Handler node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getLeftParenPosition().getPathKey());

		keys.add(node.getRightParenPosition().getPathKey());
	}

	@Override
	public void visit(If node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getElsePosition().getPathKey());
	}

	@Override
	public void visit(Iteration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Jump node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getLabelKey());

		keys.add(node.getLabelPosition().getPathKey());
	}

	@Override
	public void visit(LabeledStatement node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getLabelKey());

		keys.add(node.getColonPosition().getPathKey());
	}

	@Override
	public void visit(Return node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Selection node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Statement node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Switch node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getBlockStartPosition().getPathKey());
	}

	@Override
	public void visit(SwitchLabel node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getColonPosition().getPathKey());
	}

	@Override
	public void visit(Synchronized node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Throw node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Try node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getResourceLeftParenPosition().getPathKey());

		keys.add(node.getResourceRightParenPosition().getPathKey());

		keys.add(node.getFinallyPosition().getPathKey());
	}

	@Override
	public void visit(While node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(AnnotatedElement node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(AnnotationType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getAtSignPosition().getPathKey());
	}

	@Override
	public void visit(AnnotationTypeElement node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getDefaultPosition().getPathKey());
	}

	@Override
	public void visit(AnonymousClass node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Class node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ClassDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ClassGeneric node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(CompilationUnit node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getFileEncodingKey());

		addRoot(node.getPackageDeclaration());

		for (EdgeIterator<Import> it = node.getImportsIterator(); it.hasNext(); ) {
			addRoot(it.next());
		}

		for (EdgeIterator<Positioned> it = node.getOthersIterator(); it.hasNext(); ) {
			addRoot(it.next());
		}
	}

	@Override
	public void visit(Declaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Enum node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getSemiPosition().getPathKey());
	}

	@Override
	public void visit(EnumConstant node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(GenericDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Import node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getStaticPosition().getPathKey());
	}

	@Override
	public void visit(InitializerBlock node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(InstanceInitializerBlock node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Interface node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(InterfaceDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(InterfaceGeneric node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Member node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Method node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(MethodDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getAbstractPosition().getPathKey());

		keys.add(node.getStrictfpPosition().getPathKey());

		keys.add(node.getParametersStartPosition().getPathKey());

		keys.add(node.getParametersEndPosition().getPathKey());

		addRef(node.getMethodType());

		for (EdgeIterator<MethodDeclaration> it = node.getOverridesIterator(); it.hasNext(); ) {
			addRef(it.next());
		}
	}

	@Override
	public void visit(MethodGeneric node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(NamedDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getAccessibilityPosition().getPathKey());

		keys.add(node.getStaticPosition().getPathKey());

		keys.add(node.getFinalPosition().getPathKey());
	}

	@Override
	public void visit(NormalMethod node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getSynchronizedPosition().getPathKey());

		keys.add(node.getNativePosition().getPathKey());

		keys.add(node.getThrowsPosition().getPathKey());
	}

	@Override
	public void visit(Package node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getQualifiedNameKey());
	}

	@Override
	public void visit(PackageDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Parameter node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getVarargsPosition().getPathKey());
	}

	@Override
	public void visit(Scope node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(StaticInitializerBlock node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getBlockStartPosition().getPathKey());
	}

	@Override
	public void visit(TypeDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getBinaryNameKey());

		keys.add(node.getTypeNamePosition().getPathKey());

		keys.add(node.getAbstractPosition().getPathKey());

		keys.add(node.getStrictfpPosition().getPathKey());

		keys.add(node.getExtendsPosition().getPathKey());

		keys.add(node.getImplementsPosition().getPathKey());

		keys.add(node.getBodyStartPosition().getPathKey());

		for (EdgeIterator<Positioned> it = node.getOthersIterator(); it.hasNext(); ) {
			addRoot(it.next());
		}
	}

	@Override
	public void visit(TypeParameter node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		for (EdgeIterator<TypeExpression> it = node.getBoundsIterator(); it.hasNext(); ) {
			addRoot(it.next());
		}
	}

	@Override
	public void visit(Variable node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		keys.add(node.getTransientPosition().getPathKey());

		keys.add(node.getVolatilePosition().getPathKey());

		keys.add(node.getEqualSignPosition().getPathKey());
	}

	@Override
	public void visit(VariableDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ArrayType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getComponentType());
	}

	@Override
	public void visit(BooleanType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(BoundedWildcardType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ByteType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(CharType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ClassType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getRefersTo());
	}

	@Override
	public void visit(DoubleType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ErrorType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(FloatType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(IntType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(LongType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(LowerBoundedWildcardType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(MethodType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getReturnType());

		for (EdgeIterator<Type> it = node.getParameterTypesIterator(); it.hasNext(); ) {
			addRef(it.next());
		}

		for (EdgeIterator<Type> it = node.getThrownTypesIterator(); it.hasNext(); ) {
			addRef(it.next());
		}
	}

	@Override
	public void visit(NoType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(NullType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(PackageType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getRefersTo());
	}

	@Override
	public void visit(ParameterizedType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getRawType());

		for (EdgeIterator<Type> it = node.getArgumentTypesIterator(); it.hasNext(); ) {
			addRef(it.next());
		}
	}

	@Override
	public void visit(PrimitiveType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(ScopedType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getOwner());
	}

	@Override
	public void visit(ShortType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(Type node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(TypeVariable node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getRefersTo());
	}

	@Override
	public void visit(UnboundedWildcardType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(UnionType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		for (EdgeIterator<Type> it = node.getAlternativesIterator(); it.hasNext(); ) {
			addRef(it.next());
		}
	}

	@Override
	public void visit(UpperBoundedWildcardType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(VoidType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
	}

	@Override
	public void visit(WildcardType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		addRef(node.getBound());
	}

}
