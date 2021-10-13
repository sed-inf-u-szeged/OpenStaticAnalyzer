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

package columbus.java.asg.algorithms;

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
import columbus.java.asg.expr.AnnotatedTypeExpression;
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
import columbus.java.asg.expr.FunctionalExpression;
import columbus.java.asg.expr.Identifier;
import columbus.java.asg.expr.InfixExpression;
import columbus.java.asg.expr.InstanceOf;
import columbus.java.asg.expr.IntegerLiteral;
import columbus.java.asg.expr.Lambda;
import columbus.java.asg.expr.Literal;
import columbus.java.asg.expr.LongLiteral;
import columbus.java.asg.expr.MarkerAnnotation;
import columbus.java.asg.expr.MemberReference;
import columbus.java.asg.expr.MethodInvocation;
import columbus.java.asg.expr.NewArray;
import columbus.java.asg.expr.NewClass;
import columbus.java.asg.expr.NormalAnnotation;
import columbus.java.asg.expr.NullLiteral;
import columbus.java.asg.expr.NumberLiteral;
import columbus.java.asg.expr.ParenthesizedExpression;
import columbus.java.asg.expr.PolyExpression;
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
import columbus.java.asg.expr.TypeIntersectionExpression;
import columbus.java.asg.expr.TypeUnionExpression;
import columbus.java.asg.expr.Unary;
import columbus.java.asg.expr.WildcardExpression;
import columbus.java.asg.module.Exports;
import columbus.java.asg.module.ModuleDirective;
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
import columbus.java.asg.struc.Module;
import columbus.java.asg.struc.ModuleDeclaration;
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
import columbus.java.asg.type.IntersectionType;
import columbus.java.asg.type.LongType;
import columbus.java.asg.type.LowerBoundedWildcardType;
import columbus.java.asg.type.MethodType;
import columbus.java.asg.type.ModuleType;
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
import columbus.java.asg.visitors.Visitor;

/**
 * Implements the preorder traversal.
 */
public class AlgorithmPreorder extends Algorithm {

	/** Reference to the Factory. */
	protected Factory fact;

	/** Reference to the Visitor. */
	protected Visitor visitor;

	/** Only a subgraph of a given node or each node will be traversed. */
	protected boolean apRoot = false;

	/** If it is true, each node is visited only once during preorder. */
	protected boolean safeMode = false;

	/** Stores the nodes that are already visited during the actual run. */
	protected boolean[] visitedNodes;

	/** Stores the nodes that are not yet visited during the actual run. */
	protected boolean[] unvisitedNodes;

	/** Determines whether special nodes will be visited or not. */
	protected boolean visitSpecialNodes = true;

	/** Determines whether only used special nodes will be visited or all of them. */
	protected boolean visitUsedSpecialNodesOnly = false;

	/**
	 * Constructor.
	 */
	public AlgorithmPreorder() {
	}

	/**
	 * Sets that a node will be visited only once in the visiting.
	 */
	public void setSafeMode() {
		safeMode = true;
	}

	/**
	 * Sets that the preorder is executed duly the graph (which means that a node can be visited more than once, even if there is a circle in the graph it will be an endless visiting).
	 */
	public void setUnsafeMode() {
		safeMode = false;
	}

	/**
	 * Sets whether special nodes (or only used of them) are visited or not.
	 * @param visit    If visit parameter is true, special nodes are visited as well, otherwise they are not visited.
	 * @param usedOnly If usedOnly parameter is true, only those special nodes are visited that were 'used' during preorder.
	 */
	public void setVisitSpecialNodes(boolean visit, boolean usedOnly) {
		visitSpecialNodes = visit;
		visitUsedSpecialNodesOnly = visit && usedOnly;
	}

	/**
	 * Starts a preorder traversal which visits all nodes of the parameter `fact', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
	 * @param fact    The factory.
	 * @param visitor The visitor which is called to visit the given node or edge.
	 */
	public void run(Factory fact, Visitor visitor) {
		mainRun(fact, visitor, null);
	}

	/**
	 * Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the node with the given id, then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
	 * @param fact    The factory.
	 * @param visitor The visitor which is called to visit the given node or edge.
	 * @param nodeId  The preorder visits only the subtree of this node.
	 */
	public void run(Factory fact, Visitor visitor, int nodeId) {
		mainRun(fact, visitor, fact.getRef(nodeId));
	}

	/**
	 * Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the parameter `node', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
	 * @param fact    The factory.
	 * @param visitor The visitor which is called to visit the given node or edge.
	 * @param node    The preorder visits only the subtree of this node.
	 */
	public void run(Factory fact, Visitor visitor, Base node) {
		mainRun(fact, visitor, node);
	}

	/**
	 * Main entry point of the traversal.
	 */
	protected void mainRun(Factory fact, Visitor visitor, Base node) {
		this.fact = fact;
		this.visitor = visitor;
		this.apRoot = (node != null);

		if (safeMode || visitSpecialNodes) {
			visitedNodes = new boolean[fact.size()];
		}

		if (visitSpecialNodes) {
			unvisitedNodes = new boolean[fact.size()];
		}

		visitor.beginVisit();

		if (!apRoot) { // traverse all nodes which have no parent
			Factory.Iterator factIt = fact.iterator();
			while (factIt.hasNext()) {
				Base b = factIt.next();
				if (b.getParent() == null) {
					recRun(b);
				}
			}

		} else { // traverse this node only
			recRun(node);

			if (visitSpecialNodes && !visitUsedSpecialNodesOnly) {
				Factory.Iterator factIt = fact.iterator();
				while (factIt.hasNext()) {
					Base b = factIt.next();
					if (!visitedNodes[b.getId()] && Common.getIsAPSpecNode(b)) {
						recRun(b);
					}
				}
			}

			if (visitUsedSpecialNodesOnly) {
				boolean wasNodeToTraversal = false;
				int factSize = fact.size();
				do {
					wasNodeToTraversal = false;
					for (int i = 0; i < factSize; ++i) {
						if (unvisitedNodes[i] && !visitedNodes[i]) {
							recRun(fact.getRef(i));
							wasNodeToTraversal = true;
							unvisitedNodes[i] = false;
						}
					}
				} while (wasNodeToTraversal);
			}

		}

		visitor.finishVisit();
	}

	/**
	 * Traverse the given node and its subtree recursively.
	 */
	protected void recRun(Base node) {
		if (safeMode || visitSpecialNodes) {
			if (safeMode) {
				if (visitedNodes[node.getId()]) // for safemode
					return;
			}
			visitedNodes[node.getId()] = true;
		}

		node.accept(visitor);
		incVisitorDepth(visitor);

		switch (node.getNodeKind()) {
			// ndkBase is abstract

			case ndkBlockComment: // ndkBlockComment is visited at the end
				traverse((BlockComment)node, true);
				break;

			// ndkComment is abstract

			// ndkCommentable is abstract

			case ndkJavadocComment: // ndkJavadocComment is visited at the end
				traverse((JavadocComment)node, true);
				break;

			case ndkLineComment: // ndkLineComment is visited at the end
				traverse((LineComment)node, true);
				break;

			// ndkNamed is abstract

			// ndkNonJavadocComment is abstract

			// ndkPositioned is abstract

			// ndkPositionedWithoutComment is abstract

			case ndkAnnotatedTypeExpression:
				traverse((AnnotatedTypeExpression)node, true);
				break;

			// ndkAnnotation is abstract

			case ndkArrayAccess:
				traverse((ArrayAccess)node, true);
				break;

			case ndkArrayTypeExpression:
				traverse((ArrayTypeExpression)node, true);
				break;

			case ndkAssignment:
				traverse((Assignment)node, true);
				break;

			// ndkBinary is abstract

			case ndkBooleanLiteral:
				traverse((BooleanLiteral)node, true);
				break;

			case ndkCharacterLiteral:
				traverse((CharacterLiteral)node, true);
				break;

			case ndkClassLiteral:
				traverse((ClassLiteral)node, true);
				break;

			case ndkConditional:
				traverse((Conditional)node, true);
				break;

			case ndkDoubleLiteral:
				traverse((DoubleLiteral)node, true);
				break;

			case ndkErroneous:
				traverse((Erroneous)node, true);
				break;

			case ndkErroneousTypeExpression:
				traverse((ErroneousTypeExpression)node, true);
				break;

			// ndkExpression is abstract

			case ndkExternalTypeExpression:
				traverse((ExternalTypeExpression)node, true);
				break;

			case ndkFieldAccess:
				traverse((FieldAccess)node, true);
				break;

			case ndkFloatLiteral:
				traverse((FloatLiteral)node, true);
				break;

			// ndkFunctionalExpression is abstract

			case ndkIdentifier:
				traverse((Identifier)node, true);
				break;

			case ndkInfixExpression:
				traverse((InfixExpression)node, true);
				break;

			case ndkInstanceOf:
				traverse((InstanceOf)node, true);
				break;

			case ndkIntegerLiteral:
				traverse((IntegerLiteral)node, true);
				break;

			case ndkLambda:
				traverse((Lambda)node, true);
				break;

			// ndkLiteral is abstract

			case ndkLongLiteral:
				traverse((LongLiteral)node, true);
				break;

			case ndkMarkerAnnotation:
				traverse((MarkerAnnotation)node, true);
				break;

			case ndkMemberReference:
				traverse((MemberReference)node, true);
				break;

			case ndkMethodInvocation:
				traverse((MethodInvocation)node, true);
				break;

			case ndkNewArray:
				traverse((NewArray)node, true);
				break;

			case ndkNewClass:
				traverse((NewClass)node, true);
				break;

			case ndkNormalAnnotation:
				traverse((NormalAnnotation)node, true);
				break;

			case ndkNullLiteral:
				traverse((NullLiteral)node, true);
				break;

			// ndkNumberLiteral is abstract

			case ndkParenthesizedExpression:
				traverse((ParenthesizedExpression)node, true);
				break;

			// ndkPolyExpression is abstract

			case ndkPostfixExpression:
				traverse((PostfixExpression)node, true);
				break;

			case ndkPrefixExpression:
				traverse((PrefixExpression)node, true);
				break;

			case ndkPrimitiveTypeExpression:
				traverse((PrimitiveTypeExpression)node, true);
				break;

			case ndkQualifiedTypeExpression:
				traverse((QualifiedTypeExpression)node, true);
				break;

			case ndkSimpleTypeExpression:
				traverse((SimpleTypeExpression)node, true);
				break;

			case ndkSingleElementAnnotation:
				traverse((SingleElementAnnotation)node, true);
				break;

			case ndkStringLiteral:
				traverse((StringLiteral)node, true);
				break;

			case ndkSuper:
				traverse((Super)node, true);
				break;

			case ndkThis:
				traverse((This)node, true);
				break;

			case ndkTypeApplyExpression:
				traverse((TypeApplyExpression)node, true);
				break;

			case ndkTypeCast:
				traverse((TypeCast)node, true);
				break;

			// ndkTypeExpression is abstract

			case ndkTypeIntersectionExpression:
				traverse((TypeIntersectionExpression)node, true);
				break;

			case ndkTypeUnionExpression:
				traverse((TypeUnionExpression)node, true);
				break;

			// ndkUnary is abstract

			case ndkWildcardExpression:
				traverse((WildcardExpression)node, true);
				break;

			case ndkExports:
				traverse((Exports)node, true);
				break;

			// ndkModuleDirective is abstract

			case ndkOpens:
				traverse((Opens)node, true);
				break;

			case ndkProvides:
				traverse((Provides)node, true);
				break;

			case ndkRequires:
				traverse((Requires)node, true);
				break;

			case ndkUses:
				traverse((Uses)node, true);
				break;

			case ndkAssert:
				traverse((Assert)node, true);
				break;

			case ndkBasicFor:
				traverse((BasicFor)node, true);
				break;

			case ndkBlock:
				traverse((Block)node, true);
				break;

			case ndkBreak:
				traverse((Break)node, true);
				break;

			case ndkCase:
				traverse((Case)node, true);
				break;

			case ndkContinue:
				traverse((Continue)node, true);
				break;

			case ndkDefault:
				traverse((Default)node, true);
				break;

			case ndkDo:
				traverse((Do)node, true);
				break;

			case ndkEmpty:
				traverse((Empty)node, true);
				break;

			case ndkEnhancedFor:
				traverse((EnhancedFor)node, true);
				break;

			case ndkExpressionStatement:
				traverse((ExpressionStatement)node, true);
				break;

			// ndkFor is abstract

			case ndkHandler:
				traverse((Handler)node, true);
				break;

			case ndkIf:
				traverse((If)node, true);
				break;

			// ndkIteration is abstract

			// ndkJump is abstract

			case ndkLabeledStatement:
				traverse((LabeledStatement)node, true);
				break;

			case ndkReturn:
				traverse((Return)node, true);
				break;

			// ndkSelection is abstract

			// ndkStatement is abstract

			case ndkSwitch:
				traverse((Switch)node, true);
				break;

			// ndkSwitchLabel is abstract

			case ndkSynchronized:
				traverse((Synchronized)node, true);
				break;

			case ndkThrow:
				traverse((Throw)node, true);
				break;

			case ndkTry:
				traverse((Try)node, true);
				break;

			case ndkWhile:
				traverse((While)node, true);
				break;

			// ndkAnnotatedElement is abstract

			case ndkAnnotationType:
				traverse((AnnotationType)node, true);
				break;

			case ndkAnnotationTypeElement:
				traverse((AnnotationTypeElement)node, true);
				break;

			case ndkAnonymousClass:
				traverse((AnonymousClass)node, true);
				break;

			case ndkClass:
				traverse((Class)node, true);
				break;

			// ndkClassDeclaration is abstract

			case ndkClassGeneric:
				traverse((ClassGeneric)node, true);
				break;

			case ndkCompilationUnit:
				traverse((CompilationUnit)node, true);
				break;

			// ndkDeclaration is abstract

			case ndkEnum:
				traverse((Enum)node, true);
				break;

			case ndkEnumConstant:
				traverse((EnumConstant)node, true);
				break;

			// ndkGenericDeclaration is abstract

			case ndkImport:
				traverse((Import)node, true);
				break;

			// ndkInitializerBlock is abstract

			case ndkInstanceInitializerBlock:
				traverse((InstanceInitializerBlock)node, true);
				break;

			case ndkInterface:
				traverse((Interface)node, true);
				break;

			// ndkInterfaceDeclaration is abstract

			case ndkInterfaceGeneric:
				traverse((InterfaceGeneric)node, true);
				break;

			// ndkMember is abstract

			case ndkMethod:
				traverse((Method)node, true);
				break;

			// ndkMethodDeclaration is abstract

			case ndkMethodGeneric:
				traverse((MethodGeneric)node, true);
				break;

			case ndkModule:
				traverse((Module)node, true);
				break;

			case ndkModuleDeclaration:
				traverse((ModuleDeclaration)node, true);
				break;

			// ndkNamedDeclaration is abstract

			// ndkNormalMethod is abstract

			case ndkPackage:
				traverse((Package)node, true);
				break;

			case ndkPackageDeclaration:
				traverse((PackageDeclaration)node, true);
				break;

			case ndkParameter:
				traverse((Parameter)node, true);
				break;

			// ndkScope is abstract

			case ndkStaticInitializerBlock:
				traverse((StaticInitializerBlock)node, true);
				break;

			// ndkTypeDeclaration is abstract

			case ndkTypeParameter:
				traverse((TypeParameter)node, true);
				break;

			case ndkVariable:
				traverse((Variable)node, true);
				break;

			// ndkVariableDeclaration is abstract

			case ndkArrayType: // ndkArrayType is visited at the end
				traverse((ArrayType)node, true);
				break;

			case ndkBooleanType: // ndkBooleanType is visited at the end
				traverse((BooleanType)node, true);
				break;

			// ndkBoundedWildcardType is abstract

			case ndkByteType: // ndkByteType is visited at the end
				traverse((ByteType)node, true);
				break;

			case ndkCharType: // ndkCharType is visited at the end
				traverse((CharType)node, true);
				break;

			case ndkClassType: // ndkClassType is visited at the end
				traverse((ClassType)node, true);
				break;

			case ndkDoubleType: // ndkDoubleType is visited at the end
				traverse((DoubleType)node, true);
				break;

			case ndkErrorType: // ndkErrorType is visited at the end
				traverse((ErrorType)node, true);
				break;

			case ndkFloatType: // ndkFloatType is visited at the end
				traverse((FloatType)node, true);
				break;

			case ndkIntType: // ndkIntType is visited at the end
				traverse((IntType)node, true);
				break;

			case ndkIntersectionType:
				traverse((IntersectionType)node, true);
				break;

			case ndkLongType: // ndkLongType is visited at the end
				traverse((LongType)node, true);
				break;

			case ndkLowerBoundedWildcardType: // ndkLowerBoundedWildcardType is visited at the end
				traverse((LowerBoundedWildcardType)node, true);
				break;

			case ndkMethodType: // ndkMethodType is visited at the end
				traverse((MethodType)node, true);
				break;

			case ndkModuleType:
				traverse((ModuleType)node, true);
				break;

			case ndkNoType: // ndkNoType is visited at the end
				traverse((NoType)node, true);
				break;

			case ndkNullType: // ndkNullType is visited at the end
				traverse((NullType)node, true);
				break;

			case ndkPackageType: // ndkPackageType is visited at the end
				traverse((PackageType)node, true);
				break;

			case ndkParameterizedType: // ndkParameterizedType is visited at the end
				traverse((ParameterizedType)node, true);
				break;

			// ndkPrimitiveType is abstract

			// ndkScopedType is abstract

			case ndkShortType: // ndkShortType is visited at the end
				traverse((ShortType)node, true);
				break;

			// ndkType is abstract

			case ndkTypeVariable: // ndkTypeVariable is visited at the end
				traverse((TypeVariable)node, true);
				break;

			case ndkUnboundedWildcardType: // ndkUnboundedWildcardType is visited at the end
				traverse((UnboundedWildcardType)node, true);
				break;

			case ndkUnionType: // ndkUnionType is visited at the end
				traverse((UnionType)node, true);
				break;

			case ndkUpperBoundedWildcardType: // ndkUpperBoundedWildcardType is visited at the end
				traverse((UpperBoundedWildcardType)node, true);
				break;

			case ndkVoidType: // ndkVoidType is visited at the end
				traverse((VoidType)node, true);
				break;

			// ndkWildcardType is abstract

			default:
				break;
		} // switch

		decVisitorDepth(visitor);
		node.acceptEnd(visitor);

	} // recRun

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Base node, boolean callVirtualBase) {
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(BlockComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		traverse((NonJavadocComment)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Comment node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		traverse((PositionedWithoutComment)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Commentable node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);

		// edge: comments
		for (EdgeIterator<Comment> it = node.getCommentsIterator(); it.hasNext(); ) {
			Comment end = it.next();
			visitor.visitCommentable_Comments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndCommentable_Comments(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(JavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		traverse((Comment)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(LineComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		traverse((NonJavadocComment)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Named node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NonJavadocComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		traverse((Comment)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Positioned node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((PositionedWithoutComment)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PositionedWithoutComment node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(AnnotatedTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		Base genNodeRef;

		// edge: hasAnnotations
		for (EdgeIterator<Annotation> it = node.getAnnotationsIterator(); it.hasNext(); ) {
			Annotation end = it.next();
			visitor.visitAnnotatedTypeExpression_HasAnnotations(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndAnnotatedTypeExpression_HasAnnotations(node, end);
		}

		// edge: hasUnderlyingType
		genNodeRef = node.getUnderlyingType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitAnnotatedTypeExpression_HasUnderlyingType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndAnnotatedTypeExpression_HasUnderlyingType(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Annotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		Base genNodeRef;

		// edge: hasAnnotationName
		genNodeRef = node.getAnnotationName();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitAnnotation_HasAnnotationName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndAnnotation_HasAnnotationName(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ArrayAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Binary)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ArrayTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		Base genNodeRef;

		// edge: hasComponentType
		genNodeRef = node.getComponentType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitArrayTypeExpression_HasComponentType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndArrayTypeExpression_HasComponentType(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Assignment node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Binary)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Binary node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		Base genNodeRef;

		// edge: hasLeftOperand
		genNodeRef = node.getLeftOperand();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitBinary_HasLeftOperand(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndBinary_HasLeftOperand(node, end);
		}

		// edge: hasRightOperand
		genNodeRef = node.getRightOperand();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitBinary_HasRightOperand(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndBinary_HasRightOperand(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(BooleanLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Literal)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(CharacterLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Literal)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ClassLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Literal)node, false);

		Base genNodeRef;

		// edge: hasComponentType
		genNodeRef = node.getComponentType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitClassLiteral_HasComponentType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndClassLiteral_HasComponentType(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Conditional node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		Base genNodeRef;

		// edge: hasCondition
		genNodeRef = node.getCondition();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitConditional_HasCondition(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndConditional_HasCondition(node, end);
		}

		// edge: hasTrueExpression
		genNodeRef = node.getTrueExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitConditional_HasTrueExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndConditional_HasTrueExpression(node, end);
		}

		// edge: hasFalseExpression
		genNodeRef = node.getFalseExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitConditional_HasFalseExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndConditional_HasFalseExpression(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(DoubleLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((NumberLiteral)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Erroneous node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		// edge: hasErrors
		for (EdgeIterator<Positioned> it = node.getErrorsIterator(); it.hasNext(); ) {
			Positioned end = it.next();
			visitor.visitErroneous_HasErrors(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndErroneous_HasErrors(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ErroneousTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		// edge: hasErrors
		for (EdgeIterator<Positioned> it = node.getErrorsIterator(); it.hasNext(); ) {
			Positioned end = it.next();
			visitor.visitErroneousTypeExpression_HasErrors(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndErroneousTypeExpression_HasErrors(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Expression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);

		Base genNodeRef;

		// edge: type
		genNodeRef = node.getType();
		if (genNodeRef != null) {
			Type end = (Type)genNodeRef;
			visitor.visitExpression_Type(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndExpression_Type(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ExternalTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(FieldAccess node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Binary)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(FloatLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((NumberLiteral)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(FunctionalExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((PolyExpression)node, false);

		Base genNodeRef;

		// edge: target
		genNodeRef = node.getTarget();
		if (genNodeRef != null) {
			Type end = (Type)genNodeRef;
			visitor.visitFunctionalExpression_Target(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndFunctionalExpression_Target(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Identifier node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		Base genNodeRef;

		// edge: refersTo
		genNodeRef = node.getRefersTo();
		if (genNodeRef != null) {
			Named end = (Named)genNodeRef;
			visitor.visitIdentifier_RefersTo(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndIdentifier_RefersTo(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(InfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Binary)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(InstanceOf node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Unary)node, false);

		Base genNodeRef;

		// edge: hasTypeOperand
		genNodeRef = node.getTypeOperand();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitInstanceOf_HasTypeOperand(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndInstanceOf_HasTypeOperand(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(IntegerLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((NumberLiteral)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Lambda node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((FunctionalExpression)node, false);

		Base genNodeRef;

		// edge: hasParameters
		for (EdgeIterator<Parameter> it = node.getParametersIterator(); it.hasNext(); ) {
			Parameter end = it.next();
			visitor.visitLambda_HasParameters(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndLambda_HasParameters(node, end);
		}

		// edge: hasBody
		genNodeRef = node.getBody();
		if (genNodeRef != null) {
			Positioned end = (Positioned)genNodeRef;
			visitor.visitLambda_HasBody(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndLambda_HasBody(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Literal node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(LongLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((NumberLiteral)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(MarkerAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Annotation)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(MemberReference node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((FunctionalExpression)node, false);

		Base genNodeRef;

		// edge: hasQualifierExpression
		genNodeRef = node.getQualifierExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitMemberReference_HasQualifierExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndMemberReference_HasQualifierExpression(node, end);
		}

		// edge: hasTypeArguments
		for (EdgeIterator<TypeExpression> it = node.getTypeArgumentsIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitMemberReference_HasTypeArguments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndMemberReference_HasTypeArguments(node, end);
		}

		// edge: referredMethod
		genNodeRef = node.getReferredMethod();
		if (genNodeRef != null) {
			MethodDeclaration end = (MethodDeclaration)genNodeRef;
			visitor.visitMemberReference_ReferredMethod(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndMemberReference_ReferredMethod(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(MethodInvocation node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Unary)node, false);

		Base genNodeRef;

		// edge: hasTypeArguments
		for (EdgeIterator<TypeExpression> it = node.getTypeArgumentsIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitMethodInvocation_HasTypeArguments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndMethodInvocation_HasTypeArguments(node, end);
		}

		// edge: hasArguments
		for (EdgeIterator<Expression> it = node.getArgumentsIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitMethodInvocation_HasArguments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndMethodInvocation_HasArguments(node, end);
		}

		// edge: invokes
		genNodeRef = node.getInvokes();
		if (genNodeRef != null) {
			MethodDeclaration end = (MethodDeclaration)genNodeRef;
			visitor.visitMethodInvocation_Invokes(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndMethodInvocation_Invokes(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NewArray node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		Base genNodeRef;

		// edge: hasComponentType
		genNodeRef = node.getComponentType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitNewArray_HasComponentType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewArray_HasComponentType(node, end);
		}

		// edge: hasDimensions
		for (EdgeIterator<Expression> it = node.getDimensionsIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitNewArray_HasDimensions(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewArray_HasDimensions(node, end);
		}

		// edge: hasInitializers
		for (EdgeIterator<Expression> it = node.getInitializersIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitNewArray_HasInitializers(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewArray_HasInitializers(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NewClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		Base genNodeRef;

		// edge: hasEnclosingExpression
		genNodeRef = node.getEnclosingExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitNewClass_HasEnclosingExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewClass_HasEnclosingExpression(node, end);
		}

		// edge: hasTypeArguments
		for (EdgeIterator<TypeExpression> it = node.getTypeArgumentsIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitNewClass_HasTypeArguments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewClass_HasTypeArguments(node, end);
		}

		// edge: hasTypeName
		genNodeRef = node.getTypeName();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitNewClass_HasTypeName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewClass_HasTypeName(node, end);
		}

		// edge: hasArguments
		for (EdgeIterator<Expression> it = node.getArgumentsIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitNewClass_HasArguments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewClass_HasArguments(node, end);
		}

		// edge: hasAnonymousClass
		genNodeRef = node.getAnonymousClass();
		if (genNodeRef != null) {
			AnonymousClass end = (AnonymousClass)genNodeRef;
			visitor.visitNewClass_HasAnonymousClass(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNewClass_HasAnonymousClass(node, end);
		}

		// edge: constructor
		genNodeRef = node.getConstructor();
		if (genNodeRef != null) {
			NormalMethod end = (NormalMethod)genNodeRef;
			visitor.visitNewClass_Constructor(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndNewClass_Constructor(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NormalAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Annotation)node, false);

		// edge: hasArguments
		for (EdgeIterator<Expression> it = node.getArgumentsIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitNormalAnnotation_HasArguments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNormalAnnotation_HasArguments(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NullLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Literal)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NumberLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Literal)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ParenthesizedExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Unary)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PolyExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PostfixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Unary)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PrefixExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Unary)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PrimitiveTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(QualifiedTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		Base genNodeRef;

		// edge: hasQualifierType
		genNodeRef = node.getQualifierType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitQualifiedTypeExpression_HasQualifierType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndQualifiedTypeExpression_HasQualifierType(node, end);
		}

		// edge: hasSimpleType
		genNodeRef = node.getSimpleType();
		if (genNodeRef != null) {
			SimpleTypeExpression end = (SimpleTypeExpression)genNodeRef;
			visitor.visitQualifiedTypeExpression_HasSimpleType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndQualifiedTypeExpression_HasSimpleType(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(SimpleTypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(SingleElementAnnotation node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Annotation)node, false);

		Base genNodeRef;

		// edge: hasArgument
		genNodeRef = node.getArgument();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitSingleElementAnnotation_HasArgument(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndSingleElementAnnotation_HasArgument(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(StringLiteral node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Literal)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Super node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(This node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeApplyExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		Base genNodeRef;

		// edge: hasRawType
		genNodeRef = node.getRawType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitTypeApplyExpression_HasRawType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeApplyExpression_HasRawType(node, end);
		}

		// edge: hasTypeArguments
		for (EdgeIterator<TypeExpression> it = node.getTypeArgumentsIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitTypeApplyExpression_HasTypeArguments(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeApplyExpression_HasTypeArguments(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeCast node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Unary)node, false);

		Base genNodeRef;

		// edge: hasTypeOperand
		genNodeRef = node.getTypeOperand();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitTypeCast_HasTypeOperand(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeCast_HasTypeOperand(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeIntersectionExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		// edge: hasBounds
		for (EdgeIterator<TypeExpression> it = node.getBoundsIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitTypeIntersectionExpression_HasBounds(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeIntersectionExpression_HasBounds(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeUnionExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		// edge: hasAlternatives
		for (EdgeIterator<TypeExpression> it = node.getAlternativesIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitTypeUnionExpression_HasAlternatives(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeUnionExpression_HasAlternatives(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Unary node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Expression)node, false);

		Base genNodeRef;

		// edge: hasOperand
		genNodeRef = node.getOperand();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitUnary_HasOperand(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndUnary_HasOperand(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(WildcardExpression node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((TypeExpression)node, false);

		Base genNodeRef;

		// edge: hasBound
		genNodeRef = node.getBound();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitWildcardExpression_HasBound(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndWildcardExpression_HasBound(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Exports node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((ModuleDirective)node, false);

		Base genNodeRef;

		// edge: hasPackageName
		genNodeRef = node.getPackageName();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitExports_HasPackageName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndExports_HasPackageName(node, end);
		}

		// edge: hasModuleNames
		for (EdgeIterator<Expression> it = node.getModuleNamesIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitExports_HasModuleNames(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndExports_HasModuleNames(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ModuleDirective node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Opens node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((ModuleDirective)node, false);

		Base genNodeRef;

		// edge: hasPackageName
		genNodeRef = node.getPackageName();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitOpens_HasPackageName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndOpens_HasPackageName(node, end);
		}

		// edge: hasModuleNames
		for (EdgeIterator<Expression> it = node.getModuleNamesIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitOpens_HasModuleNames(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndOpens_HasModuleNames(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Provides node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((ModuleDirective)node, false);

		Base genNodeRef;

		// edge: hasServiceName
		genNodeRef = node.getServiceName();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitProvides_HasServiceName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndProvides_HasServiceName(node, end);
		}

		// edge: hasImplementationNames
		for (EdgeIterator<Expression> it = node.getImplementationNamesIterator(); it.hasNext(); ) {
			Expression end = it.next();
			visitor.visitProvides_HasImplementationNames(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndProvides_HasImplementationNames(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Requires node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((ModuleDirective)node, false);

		Base genNodeRef;

		// edge: hasModuleName
		genNodeRef = node.getModuleName();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitRequires_HasModuleName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndRequires_HasModuleName(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Uses node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((ModuleDirective)node, false);

		Base genNodeRef;

		// edge: hasServiceName
		genNodeRef = node.getServiceName();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitUses_HasServiceName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndUses_HasServiceName(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Assert node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasCondition
		genNodeRef = node.getCondition();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitAssert_HasCondition(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndAssert_HasCondition(node, end);
		}

		// edge: hasDetail
		genNodeRef = node.getDetail();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitAssert_HasDetail(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndAssert_HasDetail(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(BasicFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((For)node, false);

		Base genNodeRef;

		// edge: hasInitializers
		for (EdgeIterator<Statement> it = node.getInitializersIterator(); it.hasNext(); ) {
			Statement end = it.next();
			visitor.visitBasicFor_HasInitializers(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndBasicFor_HasInitializers(node, end);
		}

		// edge: hasCondition
		genNodeRef = node.getCondition();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitBasicFor_HasCondition(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndBasicFor_HasCondition(node, end);
		}

		// edge: hasUpdates
		for (EdgeIterator<Statement> it = node.getUpdatesIterator(); it.hasNext(); ) {
			Statement end = it.next();
			visitor.visitBasicFor_HasUpdates(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndBasicFor_HasUpdates(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Block node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		// edge: hasStatements
		for (EdgeIterator<Statement> it = node.getStatementsIterator(); it.hasNext(); ) {
			Statement end = it.next();
			visitor.visitBlock_HasStatements(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndBlock_HasStatements(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Break node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Jump)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Case node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((SwitchLabel)node, false);

		Base genNodeRef;

		// edge: hasExpression
		genNodeRef = node.getExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitCase_HasExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndCase_HasExpression(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Continue node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Jump)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Default node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((SwitchLabel)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Do node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Iteration)node, false);

		Base genNodeRef;

		// edge: hasCondition
		genNodeRef = node.getCondition();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitDo_HasCondition(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndDo_HasCondition(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Empty node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(EnhancedFor node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((For)node, false);

		Base genNodeRef;

		// edge: hasParameter
		genNodeRef = node.getParameter();
		if (genNodeRef != null) {
			Parameter end = (Parameter)genNodeRef;
			visitor.visitEnhancedFor_HasParameter(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndEnhancedFor_HasParameter(node, end);
		}

		// edge: hasExpression
		genNodeRef = node.getExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitEnhancedFor_HasExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndEnhancedFor_HasExpression(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ExpressionStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasExpression
		genNodeRef = node.getExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitExpressionStatement_HasExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndExpressionStatement_HasExpression(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(For node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Iteration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Handler node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);

		Base genNodeRef;

		// edge: hasParameter
		genNodeRef = node.getParameter();
		if (genNodeRef != null) {
			Parameter end = (Parameter)genNodeRef;
			visitor.visitHandler_HasParameter(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndHandler_HasParameter(node, end);
		}

		// edge: hasBlock
		genNodeRef = node.getBlock();
		if (genNodeRef != null) {
			Block end = (Block)genNodeRef;
			visitor.visitHandler_HasBlock(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndHandler_HasBlock(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(If node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Selection)node, false);

		Base genNodeRef;

		// edge: hasSubstatement
		genNodeRef = node.getSubstatement();
		if (genNodeRef != null) {
			Statement end = (Statement)genNodeRef;
			visitor.visitIf_HasSubstatement(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndIf_HasSubstatement(node, end);
		}

		// edge: hasFalseSubstatement
		genNodeRef = node.getFalseSubstatement();
		if (genNodeRef != null) {
			Statement end = (Statement)genNodeRef;
			visitor.visitIf_HasFalseSubstatement(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndIf_HasFalseSubstatement(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Iteration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasSubstatement
		genNodeRef = node.getSubstatement();
		if (genNodeRef != null) {
			Statement end = (Statement)genNodeRef;
			visitor.visitIteration_HasSubstatement(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndIteration_HasSubstatement(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Jump node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: target
		genNodeRef = node.getTarget();
		if (genNodeRef != null) {
			Statement end = (Statement)genNodeRef;
			visitor.visitJump_Target(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndJump_Target(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(LabeledStatement node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasStatement
		genNodeRef = node.getStatement();
		if (genNodeRef != null) {
			Statement end = (Statement)genNodeRef;
			visitor.visitLabeledStatement_HasStatement(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndLabeledStatement_HasStatement(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Return node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasExpression
		genNodeRef = node.getExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitReturn_HasExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndReturn_HasExpression(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Selection node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasCondition
		genNodeRef = node.getCondition();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitSelection_HasCondition(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndSelection_HasCondition(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Statement node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Switch node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Selection)node, false);

		// edge: hasCases
		for (EdgeIterator<SwitchLabel> it = node.getCasesIterator(); it.hasNext(); ) {
			SwitchLabel end = it.next();
			visitor.visitSwitch_HasCases(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndSwitch_HasCases(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(SwitchLabel node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);

		// edge: hasStatements
		for (EdgeIterator<Statement> it = node.getStatementsIterator(); it.hasNext(); ) {
			Statement end = it.next();
			visitor.visitSwitchLabel_HasStatements(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndSwitchLabel_HasStatements(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Synchronized node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasLock
		genNodeRef = node.getLock();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitSynchronized_HasLock(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndSynchronized_HasLock(node, end);
		}

		// edge: hasBlock
		genNodeRef = node.getBlock();
		if (genNodeRef != null) {
			Block end = (Block)genNodeRef;
			visitor.visitSynchronized_HasBlock(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndSynchronized_HasBlock(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Throw node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasExpression
		genNodeRef = node.getExpression();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitThrow_HasExpression(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndThrow_HasExpression(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Try node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Statement)node, false);

		Base genNodeRef;

		// edge: hasResources
		for (EdgeIterator<Base> it = node.getResourcesIterator(); it.hasNext(); ) {
			Base end = it.next();
			visitor.visitTry_HasResources(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTry_HasResources(node, end);
		}

		// edge: hasBlock
		genNodeRef = node.getBlock();
		if (genNodeRef != null) {
			Block end = (Block)genNodeRef;
			visitor.visitTry_HasBlock(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTry_HasBlock(node, end);
		}

		// edge: hasHandlers
		for (EdgeIterator<Handler> it = node.getHandlersIterator(); it.hasNext(); ) {
			Handler end = it.next();
			visitor.visitTry_HasHandlers(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTry_HasHandlers(node, end);
		}

		// edge: hasFinallyBlock
		genNodeRef = node.getFinallyBlock();
		if (genNodeRef != null) {
			Block end = (Block)genNodeRef;
			visitor.visitTry_HasFinallyBlock(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTry_HasFinallyBlock(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(While node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Iteration)node, false);

		Base genNodeRef;

		// edge: hasCondition
		genNodeRef = node.getCondition();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitWhile_HasCondition(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndWhile_HasCondition(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(AnnotatedElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);

		// edge: hasAnnotations
		for (EdgeIterator<Annotation> it = node.getAnnotationsIterator(); it.hasNext(); ) {
			Annotation end = it.next();
			visitor.visitAnnotatedElement_HasAnnotations(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndAnnotatedElement_HasAnnotations(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(AnnotationType node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((TypeDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(AnnotationTypeElement node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((MethodDeclaration)node, false);

		Base genNodeRef;

		// edge: hasDefaultValue
		genNodeRef = node.getDefaultValue();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitAnnotationTypeElement_HasDefaultValue(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndAnnotationTypeElement_HasDefaultValue(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(AnonymousClass node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((ClassDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Class node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((ClassDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ClassDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((TypeDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ClassGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((ClassDeclaration)node, false);
		traverse((GenericDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(CompilationUnit node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		traverse((PositionedWithoutComment)node, false);
		traverse((Commentable)node, false);

		Base genNodeRef;

		// edge: hasPackageDeclaration
		genNodeRef = node.getPackageDeclaration();
		if (genNodeRef != null) {
			PackageDeclaration end = (PackageDeclaration)genNodeRef;
			visitor.visitCompilationUnit_HasPackageDeclaration(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndCompilationUnit_HasPackageDeclaration(node, end);
		}

		// edge: hasImports
		for (EdgeIterator<Import> it = node.getImportsIterator(); it.hasNext(); ) {
			Import end = it.next();
			visitor.visitCompilationUnit_HasImports(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndCompilationUnit_HasImports(node, end);
		}

		// edge: hasOthers
		for (EdgeIterator<Positioned> it = node.getOthersIterator(); it.hasNext(); ) {
			Positioned end = it.next();
			visitor.visitCompilationUnit_HasOthers(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndCompilationUnit_HasOthers(node, end);
		}

		// edge: hasModuleDeclaration
		genNodeRef = node.getModuleDeclaration();
		if (genNodeRef != null) {
			ModuleDeclaration end = (ModuleDeclaration)genNodeRef;
			visitor.visitCompilationUnit_HasModuleDeclaration(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndCompilationUnit_HasModuleDeclaration(node, end);
		}

		// edge: typeDeclarations
		for (EdgeIterator<TypeDeclaration> it = node.getTypeDeclarationsIterator(); it.hasNext(); ) {
			TypeDeclaration end = it.next();
			visitor.visitCompilationUnit_TypeDeclarations(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndCompilationUnit_TypeDeclarations(node, end);
		}

		// edge: isInModule
		genNodeRef = node.getIsInModule();
		if (genNodeRef != null) {
			Module end = (Module)genNodeRef;
			visitor.visitCompilationUnit_IsInModule(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndCompilationUnit_IsInModule(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Declaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((Statement)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Enum node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((TypeDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(EnumConstant node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((VariableDeclaration)node, false);

		Base genNodeRef;

		// edge: hasNewClass
		genNodeRef = node.getNewClass();
		if (genNodeRef != null) {
			NewClass end = (NewClass)genNodeRef;
			visitor.visitEnumConstant_HasNewClass(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndEnumConstant_HasNewClass(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(GenericDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);

		// edge: hasTypeParameters
		for (EdgeIterator<TypeParameter> it = node.getTypeParametersIterator(); it.hasNext(); ) {
			TypeParameter end = it.next();
			visitor.visitGenericDeclaration_HasTypeParameters(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndGenericDeclaration_HasTypeParameters(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Import node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);

		Base genNodeRef;

		// edge: hasTarget
		genNodeRef = node.getTarget();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitImport_HasTarget(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndImport_HasTarget(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(InitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((Declaration)node, false);

		Base genNodeRef;

		// edge: hasBody
		genNodeRef = node.getBody();
		if (genNodeRef != null) {
			Block end = (Block)genNodeRef;
			visitor.visitInitializerBlock_HasBody(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndInitializerBlock_HasBody(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(InstanceInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((InitializerBlock)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Interface node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((InterfaceDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(InterfaceDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((TypeDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(InterfaceGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((InterfaceDeclaration)node, false);
		traverse((GenericDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Member node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((AnnotatedElement)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Method node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((NormalMethod)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(MethodDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((NamedDeclaration)node, false);

		Base genNodeRef;

		// edge: hasReturnType
		genNodeRef = node.getReturnType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitMethodDeclaration_HasReturnType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndMethodDeclaration_HasReturnType(node, end);
		}

		// edge: methodType
		genNodeRef = node.getMethodType();
		if (genNodeRef != null) {
			MethodType end = (MethodType)genNodeRef;
			visitor.visitMethodDeclaration_MethodType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndMethodDeclaration_MethodType(node, end);
		}

		// edge: overrides
		for (EdgeIterator<MethodDeclaration> it = node.getOverridesIterator(); it.hasNext(); ) {
			MethodDeclaration end = it.next();
			visitor.visitMethodDeclaration_Overrides(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndMethodDeclaration_Overrides(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(MethodGeneric node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((NormalMethod)node, false);
		traverse((GenericDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Module node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		traverse((Named)node, false);

		// edge: packages
		for (EdgeIterator<Package> it = node.getPackagesIterator(); it.hasNext(); ) {
			Package end = it.next();
			visitor.visitModule_Packages(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndModule_Packages(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ModuleDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);

		Base genNodeRef;

		// edge: hasName
		genNodeRef = node.getName();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitModuleDeclaration_HasName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndModuleDeclaration_HasName(node, end);
		}

		// edge: hasDirectives
		for (EdgeIterator<ModuleDirective> it = node.getDirectivesIterator(); it.hasNext(); ) {
			ModuleDirective end = it.next();
			visitor.visitModuleDeclaration_HasDirectives(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndModuleDeclaration_HasDirectives(node, end);
		}

		// edge: moduleType
		genNodeRef = node.getModuleType();
		if (genNodeRef != null) {
			ModuleType end = (ModuleType)genNodeRef;
			visitor.visitModuleDeclaration_ModuleType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndModuleDeclaration_ModuleType(node, end);
		}

		// edge: refersTo
		genNodeRef = node.getRefersTo();
		if (genNodeRef != null) {
			Module end = (Module)genNodeRef;
			visitor.visitModuleDeclaration_RefersTo(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndModuleDeclaration_RefersTo(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NamedDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((Declaration)node, false);
		traverse((Named)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NormalMethod node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((MethodDeclaration)node, false);

		Base genNodeRef;

		// edge: hasParameters
		for (EdgeIterator<Parameter> it = node.getParametersIterator(); it.hasNext(); ) {
			Parameter end = it.next();
			visitor.visitNormalMethod_HasParameters(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNormalMethod_HasParameters(node, end);
		}

		// edge: hasBody
		genNodeRef = node.getBody();
		if (genNodeRef != null) {
			Block end = (Block)genNodeRef;
			visitor.visitNormalMethod_HasBody(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNormalMethod_HasBody(node, end);
		}

		// edge: hasThrownExceptions
		for (EdgeIterator<TypeExpression> it = node.getThrownExceptionsIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitNormalMethod_HasThrownExceptions(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndNormalMethod_HasThrownExceptions(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Package node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((Named)node, false);
		traverse((Scope)node, false);

		// edge: hasCompilationUnits
		for (EdgeIterator<CompilationUnit> it = node.getCompilationUnitsIterator(); it.hasNext(); ) {
			CompilationUnit end = it.next();
			visitor.visitPackage_HasCompilationUnits(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndPackage_HasCompilationUnits(node, end);
		}

		// edge: isInModule
		for (EdgeIterator<Module> it = node.getIsInModuleIterator(); it.hasNext(); ) {
			Module end = it.next();
			visitor.visitPackage_IsInModule(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndPackage_IsInModule(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PackageDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);

		Base genNodeRef;

		// edge: hasPackageName
		genNodeRef = node.getPackageName();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitPackageDeclaration_HasPackageName(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndPackageDeclaration_HasPackageName(node, end);
		}

		// edge: refersTo
		genNodeRef = node.getRefersTo();
		if (genNodeRef != null) {
			Package end = (Package)genNodeRef;
			visitor.visitPackageDeclaration_RefersTo(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndPackageDeclaration_RefersTo(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Parameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((VariableDeclaration)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Scope node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);

		// edge: hasMembers
		for (EdgeIterator<Member> it = node.getMembersIterator(); it.hasNext(); ) {
			Member end = it.next();
			visitor.visitScope_HasMembers(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndScope_HasMembers(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(StaticInitializerBlock node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((InitializerBlock)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((NamedDeclaration)node, false);
		traverse((Scope)node, false);

		Base genNodeRef;

		// edge: hasSuperClass
		genNodeRef = node.getSuperClass();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitTypeDeclaration_HasSuperClass(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeDeclaration_HasSuperClass(node, end);
		}

		// edge: hasSuperInterfaces
		for (EdgeIterator<TypeExpression> it = node.getSuperInterfacesIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitTypeDeclaration_HasSuperInterfaces(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeDeclaration_HasSuperInterfaces(node, end);
		}

		// edge: hasOthers
		for (EdgeIterator<Positioned> it = node.getOthersIterator(); it.hasNext(); ) {
			Positioned end = it.next();
			visitor.visitTypeDeclaration_HasOthers(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeDeclaration_HasOthers(node, end);
		}

		// edge: isInCompilationUnit
		genNodeRef = node.getIsInCompilationUnit();
		if (genNodeRef != null) {
			CompilationUnit end = (CompilationUnit)genNodeRef;
			visitor.visitTypeDeclaration_IsInCompilationUnit(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndTypeDeclaration_IsInCompilationUnit(node, end);
		}

		// edge: isInModule
		genNodeRef = node.getIsInModule();
		if (genNodeRef != null) {
			Module end = (Module)genNodeRef;
			visitor.visitTypeDeclaration_IsInModule(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndTypeDeclaration_IsInModule(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeParameter node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		traverse((Positioned)node, false);
		traverse((Named)node, false);

		// edge: hasBounds
		for (EdgeIterator<TypeExpression> it = node.getBoundsIterator(); it.hasNext(); ) {
			TypeExpression end = it.next();
			visitor.visitTypeParameter_HasBounds(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndTypeParameter_HasBounds(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Variable node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((VariableDeclaration)node, false);

		Base genNodeRef;

		// edge: hasInitialValue
		genNodeRef = node.getInitialValue();
		if (genNodeRef != null) {
			Expression end = (Expression)genNodeRef;
			visitor.visitVariable_HasInitialValue(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndVariable_HasInitialValue(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(VariableDeclaration node, boolean callVirtualBase) {
		if (callVirtualBase)
			traverse((Base)node, false);
		if (callVirtualBase)
			traverse((Commentable)node, false);
		if (callVirtualBase)
			traverse((Member)node, false);
		traverse((NamedDeclaration)node, false);

		Base genNodeRef;

		// edge: hasType
		genNodeRef = node.getType();
		if (genNodeRef != null) {
			TypeExpression end = (TypeExpression)genNodeRef;
			visitor.visitVariableDeclaration_HasType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			} else {
				recRun(end);
			}
			visitor.visitEndVariableDeclaration_HasType(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ArrayType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		Base genNodeRef;

		// edge: componentType
		genNodeRef = node.getComponentType();
		if (genNodeRef != null) {
			Type end = (Type)genNodeRef;
			visitor.visitArrayType_ComponentType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndArrayType_ComponentType(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(BooleanType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(BoundedWildcardType node, boolean callVirtualBase) {
		traverse((WildcardType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ByteType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(CharType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ClassType node, boolean callVirtualBase) {
		traverse((ScopedType)node, false);

		Base genNodeRef;

		// edge: refersTo
		genNodeRef = node.getRefersTo();
		if (genNodeRef != null) {
			TypeDeclaration end = (TypeDeclaration)genNodeRef;
			visitor.visitClassType_RefersTo(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndClassType_RefersTo(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(DoubleType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ErrorType node, boolean callVirtualBase) {
		traverse((Type)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(FloatType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(IntType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(IntersectionType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		// edge: bounds
		for (EdgeIterator<Type> it = node.getBoundsIterator(); it.hasNext(); ) {
			Type end = it.next();
			visitor.visitIntersectionType_Bounds(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndIntersectionType_Bounds(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(LongType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(LowerBoundedWildcardType node, boolean callVirtualBase) {
		traverse((BoundedWildcardType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(MethodType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		Base genNodeRef;

		// edge: returnType
		genNodeRef = node.getReturnType();
		if (genNodeRef != null) {
			Type end = (Type)genNodeRef;
			visitor.visitMethodType_ReturnType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndMethodType_ReturnType(node, end);
		}

		// edge: parameterTypes
		for (EdgeIterator<Type> it = node.getParameterTypesIterator(); it.hasNext(); ) {
			Type end = it.next();
			visitor.visitMethodType_ParameterTypes(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndMethodType_ParameterTypes(node, end);
		}

		// edge: thrownTypes
		for (EdgeIterator<Type> it = node.getThrownTypesIterator(); it.hasNext(); ) {
			Type end = it.next();
			visitor.visitMethodType_ThrownTypes(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndMethodType_ThrownTypes(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ModuleType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		Base genNodeRef;

		// edge: refersTo
		genNodeRef = node.getRefersTo();
		if (genNodeRef != null) {
			Module end = (Module)genNodeRef;
			visitor.visitModuleType_RefersTo(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndModuleType_RefersTo(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NoType node, boolean callVirtualBase) {
		traverse((Type)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(NullType node, boolean callVirtualBase) {
		traverse((Type)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PackageType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		Base genNodeRef;

		// edge: refersTo
		genNodeRef = node.getRefersTo();
		if (genNodeRef != null) {
			Package end = (Package)genNodeRef;
			visitor.visitPackageType_RefersTo(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndPackageType_RefersTo(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ParameterizedType node, boolean callVirtualBase) {
		traverse((ScopedType)node, false);

		Base genNodeRef;

		// edge: rawType
		genNodeRef = node.getRawType();
		if (genNodeRef != null) {
			Type end = (Type)genNodeRef;
			visitor.visitParameterizedType_RawType(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndParameterizedType_RawType(node, end);
		}

		// edge: argumentTypes
		for (EdgeIterator<Type> it = node.getArgumentTypesIterator(); it.hasNext(); ) {
			Type end = it.next();
			visitor.visitParameterizedType_ArgumentTypes(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndParameterizedType_ArgumentTypes(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(PrimitiveType node, boolean callVirtualBase) {
		traverse((Type)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ScopedType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		Base genNodeRef;

		// edge: owner
		genNodeRef = node.getOwner();
		if (genNodeRef != null) {
			Type end = (Type)genNodeRef;
			visitor.visitScopedType_Owner(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndScopedType_Owner(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(ShortType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(Type node, boolean callVirtualBase) {
		traverse((Base)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(TypeVariable node, boolean callVirtualBase) {
		traverse((Type)node, false);

		Base genNodeRef;

		// edge: refersTo
		genNodeRef = node.getRefersTo();
		if (genNodeRef != null) {
			TypeParameter end = (TypeParameter)genNodeRef;
			visitor.visitTypeVariable_RefersTo(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndTypeVariable_RefersTo(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(UnboundedWildcardType node, boolean callVirtualBase) {
		traverse((WildcardType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(UnionType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		// edge: alternatives
		for (EdgeIterator<Type> it = node.getAlternativesIterator(); it.hasNext(); ) {
			Type end = it.next();
			visitor.visitUnionType_Alternatives(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndUnionType_Alternatives(node, end);
		}

	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(UpperBoundedWildcardType node, boolean callVirtualBase) {
		traverse((BoundedWildcardType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(VoidType node, boolean callVirtualBase) {
		traverse((PrimitiveType)node, false);
	}

	/**
	 * Traverse the given node.
	 * @param node            The node which is traversed.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	protected void traverse(WildcardType node, boolean callVirtualBase) {
		traverse((Type)node, false);

		Base genNodeRef;

		// edge: bound
		genNodeRef = node.getBound();
		if (genNodeRef != null) {
			Type end = (Type)genNodeRef;
			visitor.visitWildcardType_Bound(node, end);
			if (apRoot && visitUsedSpecialNodesOnly && Common.getIsAPSpecNode(end)) {
				unvisitedNodes[end.getId()] = true;
			}
			visitor.visitEndWildcardType_Bound(node, end);
		}

	}

}
