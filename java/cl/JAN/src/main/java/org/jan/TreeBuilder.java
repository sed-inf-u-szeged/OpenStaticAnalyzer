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

package org.jan;

import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.lang.model.type.TypeKind;
import javax.tools.JavaFileObject;

import columbus.java.asg.Common;
import columbus.java.asg.Factory;
import columbus.java.asg.JavaException;
import columbus.java.asg.Range;
import columbus.java.asg.base.Base;
import columbus.java.asg.base.Named;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.enums.AssignmentOperatorKind;
import columbus.java.asg.enums.InfixOperatorKind;
import columbus.java.asg.enums.MethodKind;
import columbus.java.asg.enums.NodeKind;
import columbus.java.asg.enums.PostfixOperatorKind;
import columbus.java.asg.enums.PrefixOperatorKind;
import columbus.java.asg.enums.PrimitiveTypeKind;
import columbus.java.asg.enums.TypeBoundKind;
import columbus.java.asg.expr.Annotation;
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
import columbus.java.asg.expr.FieldAccess;
import columbus.java.asg.expr.FloatLiteral;
import columbus.java.asg.expr.Identifier;
import columbus.java.asg.expr.InfixExpression;
import columbus.java.asg.expr.InstanceOf;
import columbus.java.asg.expr.IntegerLiteral;
import columbus.java.asg.expr.LongLiteral;
import columbus.java.asg.expr.MarkerAnnotation;
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
import columbus.java.asg.statm.Jump;
import columbus.java.asg.statm.LabeledStatement;
import columbus.java.asg.statm.Return;
import columbus.java.asg.statm.Switch;
import columbus.java.asg.statm.SwitchLabel;
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
import columbus.java.asg.struc.GenericDeclaration;
import columbus.java.asg.struc.Import;
import columbus.java.asg.struc.InitializerBlock;
import columbus.java.asg.struc.InstanceInitializerBlock;
import columbus.java.asg.struc.Interface;
import columbus.java.asg.struc.InterfaceGeneric;
import columbus.java.asg.struc.Method;
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.struc.MethodGeneric;
import columbus.java.asg.struc.NamedDeclaration;
import columbus.java.asg.struc.NormalMethod;
import columbus.java.asg.struc.Package;
import columbus.java.asg.struc.PackageDeclaration;
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.struc.StaticInitializerBlock;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.struc.TypeParameter;
import columbus.java.asg.struc.Variable;
import columbus.java.asg.struc.VariableDeclaration;
import columbus.logger.LoggerHandler;

import com.sun.source.tree.Tree.Kind;
import com.sun.tools.javac.code.Symbol;
import com.sun.tools.javac.code.Symbol.ClassSymbol;
import com.sun.tools.javac.code.Symbol.MethodSymbol;
import com.sun.tools.javac.code.Symbol.PackageSymbol;
import com.sun.tools.javac.code.Symbol.VarSymbol;
import com.sun.tools.javac.code.Symtab;
import com.sun.tools.javac.code.Type;
import com.sun.tools.javac.parser.Tokens.TokenKind;
import com.sun.tools.javac.columbus.DuplicatedHack;
import com.sun.tools.javac.tree.JCTree;
import com.sun.tools.javac.tree.JCTree.JCAnnotation;
import com.sun.tools.javac.tree.JCTree.JCArrayAccess;
import com.sun.tools.javac.tree.JCTree.JCArrayTypeTree;
import com.sun.tools.javac.tree.JCTree.JCAssert;
import com.sun.tools.javac.tree.JCTree.JCAssign;
import com.sun.tools.javac.tree.JCTree.JCAssignOp;
import com.sun.tools.javac.tree.JCTree.JCBinary;
import com.sun.tools.javac.tree.JCTree.JCBlock;
import com.sun.tools.javac.tree.JCTree.JCBreak;
import com.sun.tools.javac.tree.JCTree.JCCase;
import com.sun.tools.javac.tree.JCTree.JCCatch;
import com.sun.tools.javac.tree.JCTree.JCClassDecl;
import com.sun.tools.javac.tree.JCTree.JCCompilationUnit;
import com.sun.tools.javac.tree.JCTree.JCConditional;
import com.sun.tools.javac.tree.JCTree.JCContinue;
import com.sun.tools.javac.tree.JCTree.JCDoWhileLoop;
import com.sun.tools.javac.tree.JCTree.JCEnhancedForLoop;
import com.sun.tools.javac.tree.JCTree.JCErroneous;
import com.sun.tools.javac.tree.JCTree.JCExpression;
import com.sun.tools.javac.tree.JCTree.JCExpressionStatement;
import com.sun.tools.javac.tree.JCTree.JCFieldAccess;
import com.sun.tools.javac.tree.JCTree.JCForLoop;
import com.sun.tools.javac.tree.JCTree.JCIdent;
import com.sun.tools.javac.tree.JCTree.JCIf;
import com.sun.tools.javac.tree.JCTree.JCImport;
import com.sun.tools.javac.tree.JCTree.JCInstanceOf;
import com.sun.tools.javac.tree.JCTree.JCLabeledStatement;
import com.sun.tools.javac.tree.JCTree.JCLiteral;
import com.sun.tools.javac.tree.JCTree.JCMethodDecl;
import com.sun.tools.javac.tree.JCTree.JCMethodInvocation;
import com.sun.tools.javac.tree.JCTree.JCModifiers;
import com.sun.tools.javac.tree.JCTree.JCNewArray;
import com.sun.tools.javac.tree.JCTree.JCNewClass;
import com.sun.tools.javac.tree.JCTree.JCParens;
import com.sun.tools.javac.tree.JCTree.JCPrimitiveTypeTree;
import com.sun.tools.javac.tree.JCTree.JCReturn;
import com.sun.tools.javac.tree.JCTree.JCStatement;
import com.sun.tools.javac.tree.JCTree.JCSwitch;
import com.sun.tools.javac.tree.JCTree.JCSynchronized;
import com.sun.tools.javac.tree.JCTree.JCThrow;
import com.sun.tools.javac.tree.JCTree.JCTry;
import com.sun.tools.javac.tree.JCTree.JCTypeApply;
import com.sun.tools.javac.tree.JCTree.JCTypeCast;
import com.sun.tools.javac.tree.JCTree.JCTypeParameter;
import com.sun.tools.javac.tree.JCTree.JCTypeUnion;
import com.sun.tools.javac.tree.JCTree.JCUnary;
import com.sun.tools.javac.tree.JCTree.JCVariableDecl;
import com.sun.tools.javac.tree.JCTree.JCWhileLoop;
import com.sun.tools.javac.tree.JCTree.JCWildcard;
import com.sun.tools.javac.util.Context;
import com.sun.tools.javac.util.Name;
import com.sun.tools.javac.util.Names;
import com.sun.tools.javac.util.Position;
import com.sun.tools.javac.util.Position.LineMap;

public class TreeBuilder {

	private static final LoggerHandler logger = new LoggerHandler(TreeBuilder.class,
			OptionParser.getLoggerPropertyFile());

	private Names names;
	private Symtab symtab;
	private Factory fact;
	private SymbolMaps symMaps;
	private Package rootNode;
	private Package unnamedPackage = null;

	private Set<Integer> defaultPackageChilds = new HashSet<>();

	private JCCompilationUnit actualJCCU;
	private CompilationUnit actualColumbusCU;
	private int actualColumbusCuPathKey;
	private LineMap lineMap;

	// flag variables, must reset them if an Exception occurred
	private JCBlock lastBlockNode;
	private VarDeclType varDeclType = VarDeclType.NONE;
	private BlockType blockType = BlockType.NORMAL;
	private MethodType methodType = MethodType.NORMAL;
	private JCTree generatedTreeRoot = null;
	private boolean isAnonymusClass = false;
	private Name duplicatedTypeDeclarationName = null;
	private boolean inImport = false;
	private JCExpression innerAnonymusClassSuperClass;

	public TreeBuilder(Factory fact, SymbolMaps symMaps, Context context) {
		this.names = Names.instance(context);
		this.symtab = Symtab.instance(context);
		this.fact = fact;
		this.symMaps = symMaps;
		rootNode = fact.getRoot();
	}

	public void visit(JCCompilationUnit jcCU) {

		actualJCCU = jcCU;
		JavaFileObject sourcefile = jcCU.sourcefile;
		lineMap = jcCU.lineMap;

		if (logger.isInfoEnabled()) {
			logger.info("info.jan.TreeBuilder.sourceFile", sourcefile.getName());
		}

		CompilationUnit cuNode = (CompilationUnit) fact.createNode(NodeKind.ndkCompilationUnit);
		cuNode.setFileEncoding(OptionParser.encoding);
		actualColumbusCU = cuNode;

		PackageSymbol pkgSym = jcCU.packge;

		int actualPackageId = createAndAddPackages(pkgSym);

		Package pkgNode = (Package) fact.getRef(actualPackageId);
		
 		// set position 
		int endline = 1, endcol = 1;
		int wideEndPos = jcCU.getEndPosition(actualJCCU.endPositions);
		if (wideEndPos != Position.NOPOS) {
			endline = lineMap.getLineNumber(wideEndPos);
			endcol = lineMap.getColumnNumber(wideEndPos);
		}
		Range range = new Range(fact.getStringTable(), jcCU.sourcefile.getName(), 1, 1, endline, endcol, 1, 1, endline, endcol);
		cuNode.setPosition(range);
		actualColumbusCuPathKey = actualColumbusCU.getPosition().getPathKey();
		
		pkgNode.addCompilationUnits(cuNode);

		if (jcCU.pid != null) {
			PackageDeclaration pkgDecLNode = (PackageDeclaration) fact.createNode(NodeKind.ndkPackageDeclaration);
			if (jcCU.packge.owner != null) {
				pkgDecLNode.setPackageName(visit(jcCU.packge, jcCU.pid));
			}
			pkgDecLNode.setRefersTo(actualPackageId);
			setPositionAndGenerated(jcCU.pid, pkgDecLNode.getId());

			cuNode.setPackageDeclaration(pkgDecLNode);
		}

		for (JCAnnotation a : jcCU.packageAnnotations) {
			pkgNode.addAnnotations(visit(a));
		}

		for (JCTree t : jcCU.defs) {
			Base node = fact.getRef(visit(t));
			duplicatedTypeDeclarationName = null;
			if (Common.getIsTypeDeclaration(node)) {
				cuNode.addTypeDeclarations((TypeDeclaration) node);
				pkgNode.addMembers((TypeDeclaration) node);
			} else if (Common.getIsEmpty(node)) {
				cuNode.addOthers((Empty) node);
			} else if (Common.getIsImport(node)) {
				cuNode.addImports((Import) node);
			} else if (Common.getIsErroneous(node)) {
				cuNode.addOthers((Erroneous) node);
			} else {
				throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.notHandledPackageMember",
						node.getNodeKind()));
			}
		}

		Main.updateMemoryUsage();

		// release some no more necessary "big" fields
		jcCU.endPositions = null;
		jcCU.lineMap = null;
	}

	private int visit(Symbol pkg, JCExpression pid) {
		int ret = 0;

		Identifier identifierNode = (Identifier) fact.createNode(NodeKind.ndkIdentifier);
		identifierNode.setName(pkg.name.toString());
		setPositionAndGenerated(pid, identifierNode.getId());
		ret = identifierNode.getId();
		symMaps.addToIdMap(ret, pkg);
		symMaps.addNodeType(pkg.type, identifierNode.getId());

		// "asdf.asdf"
		if (pkg.owner.owner != null) {
			FieldAccess fieldAccessNode = (FieldAccess) fact.createNode(NodeKind.ndkFieldAccess);
			setPositionAndGenerated(pid, fieldAccessNode.getId());
			ret = fieldAccessNode.getId();
			fieldAccessNode.setLeftOperand(visit(pkg.owner, ((JCFieldAccess) pid).selected));
			fieldAccessNode.setRightOperand(identifierNode);
			symMaps.addNodeType(pkg.owner.type, fieldAccessNode.getId());
		}

		return ret;
	}

	public int createAndAddPackages(PackageSymbol pkgSym) {
		int ret = 0;
		if (pkgSym == symtab.unnamedPackage) {
			if (unnamedPackage == null) {
				int unnamedPackageId = createUnnamedPackage();
				symMaps.getPackageMap().put(pkgSym, unnamedPackageId);
			}
			return unnamedPackage.getId();
		}
		ret = createPackageHierarchy(pkgSym);

		addToDefaultPackage(ret);
		return ret;
	}

	private int createUnnamedPackage() {
		Package pkg = (Package) fact.createNode(NodeKind.ndkPackage);
		pkg.setName("unnamed package");
		pkg.setQualifiedName("unnamed package");
		rootNode.addMembers(pkg);
		unnamedPackage = pkg;
		return pkg.getId();
	}

	private void addToDefaultPackage(int actualPkgId) {
		Package p = (Package) fact.getRef(actualPkgId);

		while (p.getParent() != null && p.getParent() != rootNode) {
			p = (Package) p.getParent();
		}

		if (!defaultPackageChilds.contains(p.getId())) {
			defaultPackageChilds.add(p.getId());
			rootNode.addMembers(p);
		}
	}

	private int createPackageHierarchy(PackageSymbol sym) {
		int pkgId = 0;
		if (sym.owner != null && !sym.owner.name.isEmpty()) {
			Integer key = symMaps.getPackageMap().get(sym);
			if (key != null) {
				pkgId = key;
			} else {
				PackageSymbol owner = (PackageSymbol) sym.owner;

				Package packageNode = (Package) fact.createNode(NodeKind.ndkPackage);
				packageNode.setName(sym.name.toString());

				packageNode.setQualifiedName(sym.type.toString());

				pkgId = packageNode.getId();

				symMaps.getPackageMap().put(sym, packageNode.getId());

				Package parentPkg = (Package) fact.getRef(createPackageHierarchy(owner));
				parentPkg.addMembers(packageNode);
			}
		} else {
			Integer key = symMaps.getPackageMap().get(sym);
			if (key != null) {
				pkgId = key;
			} else {

				Package packageNode = (Package) fact.createNode(NodeKind.ndkPackage);

				packageNode.setName(sym.toString());
				packageNode.setQualifiedName(sym.toString());

				pkgId = packageNode.getId();
				symMaps.getPackageMap().put(sym, pkgId);
			}
		}
		return pkgId;
	}

	private int visit(JCTree jcTree) {
		int ret = 0;

		if (jcTree == null) {
			throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.visitJCTreeGetANullNode"));
		}

		try {

			if (jcTree instanceof JCStatement) {
				ret = visit((JCStatement) jcTree);
			} else if (jcTree instanceof JCExpression) {
				ret = visit((JCExpression) jcTree);
			} else {
				switch (jcTree.getKind()) {
				// "TypeBoundKind is not part of a public API"
				// case COMPILATION_UNIT:
				// it has an own visit method
				case MODIFIERS:
					// we don't build a node from it
				case CATCH: {
					JCCatch jcCatch = (JCCatch) jcTree;
					Handler handlerNode = (Handler) fact.createNode(NodeKind.ndkHandler);
					ret = handlerNode.getId();

					varDeclType = VarDeclType.PARAMETER;

					handlerNode.setParameter(visit(jcCatch.param));
					handlerNode.setBlock(visit(jcCatch.body));

					break;
				}
				case TYPE_PARAMETER: {
					JCTypeParameter jcTypeParameter = (JCTypeParameter) jcTree;
					TypeParameter typeParameterNode = (TypeParameter) fact.createNode(NodeKind.ndkTypeParameter);
					ret = typeParameterNode.getId();

					typeParameterNode.setName(jcTypeParameter.name.toString());
					if (jcTypeParameter.bounds.isEmpty()) {
						if (jcTypeParameter.type != null && ((Type.TypeVar) jcTypeParameter.type).bound != null) {
							typeParameterNode
									.addBounds(createSimpleTypeExpression(((Type.TypeVar) jcTypeParameter.type).bound));
						}
					} else {
						for (JCExpression b : jcTypeParameter.bounds) {
							typeParameterNode.addBounds(visitTypeExpression(b));
						}
					}

					symMaps.getTypeParameterMap().put(jcTypeParameter.type, typeParameterNode.getId());
					break;
				}
				case IMPORT: {
					try {
						inImport = true;
						JCImport jcImport = (JCImport) jcTree;
						Import importNode = (Import) fact.createNode(NodeKind.ndkImport);
						ret = importNode.getId();

						importNode.setIsStatic(jcImport.staticImport);
						importNode.setTarget(visit(jcImport.qualid));
					} finally {
						inImport = false;
					}
					break;
				}
				case METHOD: {
					try {
						JCMethodDecl jcMethod = (JCMethodDecl) jcTree;

						if (generatedTreeRoot == null
								&& (JANFlags.hasAnonconstrFlag(jcMethod.mods.flags) || JANFlags
										.hasGeneratedConstrFlag(jcMethod.mods.flags))) {
							generatedTreeRoot = jcTree;
						}

						MethodDeclaration methodDecl = null;
						if (methodType == MethodType.ANNOTATION_ELEMENT) {
							AnnotationTypeElement annotTypeElemNode = (AnnotationTypeElement) fact
									.createNode(NodeKind.ndkAnnotationTypeElement);
							if (jcMethod.defaultValue != null) {
								annotTypeElemNode.setDefaultValue(visit(jcMethod.defaultValue));
							}

							methodDecl = annotTypeElemNode;
							ret = annotTypeElemNode.getId();
						} else {
							NormalMethod normalMethod = null;

							if (!jcMethod.typarams.isEmpty()) {
								MethodGeneric methodGenericNode = (MethodGeneric) fact
										.createNode(NodeKind.ndkMethodGeneric);
								ret = methodGenericNode.getId();

								for (JCTypeParameter typaram : jcMethod.typarams) {
									methodGenericNode.addTypeParameters(visit(typaram));
								}
								normalMethod = methodGenericNode;
							} else {
								Method methodNode = (Method) fact.createNode(NodeKind.ndkMethod);
								ret = methodNode.getId();
								normalMethod = methodNode;
							}
							if (jcMethod.body != null) {
								normalMethod.setBody(visit(jcMethod.body));
							}

							for (JCExpression thr : jcMethod.thrown) {
								normalMethod.addThrownExceptions(visitTypeExpression(thr));
							}

							for (JCVariableDecl param : jcMethod.params) {
								varDeclType = VarDeclType.PARAMETER;
								normalMethod.addParameters(visit(param));
							}
							methodDecl = normalMethod;
						}

						setModifiersAndAnnotations(jcMethod.mods, methodDecl);

						MethodSymbol sym = jcMethod.sym;
						if (sym != null && jcMethod.name == names.init) {
							NormalMethod normalMethod = (NormalMethod) methodDecl;
							if (normalMethod.getMethodKind() == MethodKind.mekNormal) {
								normalMethod.setMethodKind(MethodKind.mekConstructor);
							}

							if (sym.owner != null) {
								methodDecl.setName(sym.owner.name.toString());
							} else {
								methodDecl.setName(sym.toString());
							}
						} else {
							methodDecl.setName(jcMethod.name.toString());
						}

						if (duplicatedTypeDeclarationName != null && Common.getIsNormalMethod(methodDecl)
								&& ((NormalMethod) methodDecl).getMethodKind() != MethodKind.mekNormal && sym != null
								&& sym.owner != null) {
							methodDecl.setName(sym.owner.name.toString());
						}

						if (jcMethod.restype != null) {
							methodDecl.setReturnType(visitTypeExpression(jcMethod.restype));
						}

						if (jcMethod.sym != null) {
							symMaps.getMethodDeclarationMap().put(jcMethod.sym, ret);
						}

						symMaps.addNodeType(jcMethod.type, methodDecl.getId());
					} finally {
						methodType = MethodType.NORMAL;
					}
					break;
				}
				default:
					throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.invalidJCTreeKind",
							jcTree.getKind()));
				}

				if (ret == 0) {
					throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.visitJCTreeRetIsZero"));
				} else {
					setPositionAndGenerated(jcTree, ret);
				}
			}

		} finally {
			if (generatedTreeRoot != null && generatedTreeRoot == jcTree) {
				generatedTreeRoot = null;
			}

		}

		return ret;
	}

	private int visit(JCStatement jcStatement) {
		int ret = 0;

		if (jcStatement == null) {
			throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.visitStatementGetANullNode"));
		}

		try {

			if (generatedTreeRoot == null && lastBlockNode != null && jcStatement.pos == lastBlockNode.pos) {
				generatedTreeRoot = jcStatement;
			}

			if (jcStatement instanceof JCClassDecl) {
				try {
					JCClassDecl jcClassDecl = (JCClassDecl) jcStatement;
					TypeDeclaration typeDeclNode = null;

					if (isAnonymusClass) {
						typeDeclNode = (TypeDeclaration) fact.createNode(NodeKind.ndkAnonymousClass);
						isAnonymusClass = false;
					} else {
						switch (jcStatement.getKind()) {
						case CLASS:
							if (jcClassDecl.typarams.isEmpty()) {
								typeDeclNode = (Class) fact.createNode(NodeKind.ndkClass);
							} else {
								typeDeclNode = (ClassGeneric) fact.createNode(NodeKind.ndkClassGeneric);
							}
							break;
						case INTERFACE:
							if (jcClassDecl.typarams.isEmpty()) {
								typeDeclNode = (Interface) fact.createNode(NodeKind.ndkInterface);
							} else {
								typeDeclNode = (InterfaceGeneric) fact.createNode(NodeKind.ndkInterfaceGeneric);
							}
							break;
						case ENUM:
							typeDeclNode = (Enum) fact.createNode(NodeKind.ndkEnum);
							if (jcClassDecl.sym != null) {
								List<Symbol> elemList = jcClassDecl.sym.getEnclosedElements();
								for (Symbol s : elemList) {
									// the same name is not enough
									if (s instanceof MethodSymbol
											&& (s.toString().equals("values()") || s.toString().equals(
													"valueOf(java.lang.String)"))) {
										symMaps.getEnumFunctions().put((MethodSymbol) s, typeDeclNode.getId());
									}
								}
							}

							break;
						case ANNOTATION_TYPE:
							// methodType = MethodType.ANNOTATION_ELEMENT;
							typeDeclNode = (AnnotationType) fact.createNode(NodeKind.ndkAnnotationType);
							break;
						default:
							throw new JavaException(logger.formatMessage(
									"ex.jan.TreeBuilder.statementIsntHandledInVisitJCExpr", jcStatement.getKind()));
						}
						if (Common.getIsGenericDeclaration(typeDeclNode)) {
							GenericDeclaration genericDecl = (GenericDeclaration) typeDeclNode;
							for (JCTypeParameter typ : jcClassDecl.typarams) {
								genericDecl.addTypeParameters(visit(typ));
							}
						}
					}
					ret = typeDeclNode.getId();
					if (jcClassDecl.sym != null) {
						Name binaryName = null;
						if (duplicatedTypeDeclarationName != null) {
							String origName = jcClassDecl.sym.flatname.toString();
							// only search from the second character, because if the typedeclaration's name is bad, it
							// will be replaced with $ character
							int endOfTypeDeclName = origName.indexOf(duplicatedTypeDeclarationName.toString())+ duplicatedTypeDeclarationName.length();
							String postfix = origName.substring(origName.indexOf("$", endOfTypeDeclName));
							binaryName = names.fromString(duplicatedTypeDeclarationName.toString() + postfix);
						} else {
							Name name = jcClassDecl.sym.flatname;
							if (DuplicatedHack.duplicatedTypeDeclarations.containsKey(name)) {
								binaryName = DuplicatedHack.duplicatedTypeDeclarations.get(name);
								duplicatedTypeDeclarationName = binaryName;
							} else {
								binaryName = name;
							}
						}
						typeDeclNode.setBinaryName(binaryName.toString());
						symMaps.getInnerTypeDeclarationMap().put(jcClassDecl.sym, ret);
					} else {
						if (logger.isDebugEnabled()) {
							logger.debug("debug.jan.TreeBuilder.typeDeclSymIsNull", ret);
						}
					}

					for (JCTree def : jcClassDecl.defs) {
						if (def.getKind() == Kind.ERRONEOUS) {
							continue;
						} else if (def.getKind() == Kind.VARIABLE) {
							setVariableType(def);
						} else if (def.getKind() == Kind.BLOCK) {
							setBlockType(def);
						} else if (def.getKind() == Kind.METHOD) {
							setMethodType(jcClassDecl);
						} else if (def.getKind() == Kind.EMPTY_STATEMENT) {
							typeDeclNode.addOthers(visit(def));
							continue;
						}

						typeDeclNode.addMembers(visit(def));
					}
					if (jcClassDecl.name != null)
						typeDeclNode.setName(jcClassDecl.name.toString());

					typeDeclNode.setIsInCompilationUnit(actualColumbusCU);

					Type.ClassType classType = (Type.ClassType) jcClassDecl.type;
					if (jcClassDecl.extending != null) {
						if (innerAnonymusClassSuperClass != null) {
							try {
								typeDeclNode.setSuperClass(visitTypeExpression(innerAnonymusClassSuperClass));
							} finally {
								innerAnonymusClassSuperClass = null;
							}
						} else {
							typeDeclNode.setSuperClass(visitTypeExpression(jcClassDecl.extending));
						}
					} else {
						// classes where super class is not given in the declarations
						// interfaces and annotation don't have default super class
						// enums extend java.lang.Enum by default
						if (jcClassDecl.type != null && !jcClassDecl.type.isInterface()) {
							typeDeclNode.setSuperClass(createSimpleTypeExpression(classType.supertype_field));
						}
					}

					if (jcClassDecl.type != null && JANFlags.hasAnnotationFlag(jcClassDecl.type.tsym.flags_field)) {
						for (Type t : classType.interfaces_field) {
							typeDeclNode.addSuperInterfaces(createSimpleTypeExpression(t));
						}
					}
					for (JCExpression imp : jcClassDecl.implementing) {
						typeDeclNode.addSuperInterfaces(visitTypeExpression(imp));
					}

					// if we override an external class, we have to build it fully for method override edges
					if (OptionParser.buildAllParentForOverrides
							&& (jcClassDecl.extending != null || !jcClassDecl.implementing.isEmpty())) {
						symMaps.addAllParentToFullBuild(jcClassDecl.sym);
					}

					setModifiersAndAnnotations(jcClassDecl.mods, typeDeclNode);
				} finally {
					isAnonymusClass = false;
				}
			} else {
				switch (jcStatement.getKind()) {

				case ASSERT: {
					JCAssert jcAssert = (JCAssert) jcStatement;
					Assert assertNode = (Assert) fact.createNode(NodeKind.ndkAssert);
					ret = assertNode.getId();

					assertNode.setCondition(visit(jcAssert.cond));

					if (jcAssert.detail != null) {
						assertNode.setDetail(visit(jcAssert.detail));
					}
					break;
				}

				case BLOCK: {
					try {
						JCBlock jcBlock = (JCBlock) jcStatement;
						lastBlockNode = jcBlock;
						Block blockNode = (Block) fact.createNode(NodeKind.ndkBlock);
						ret = blockNode.getId();

						// to handle blocks inside init blocks correctly
						BlockType saveBlockType = blockType;
						blockType = BlockType.NORMAL;
						for (JCStatement s : jcBlock.stats) {
							if (s.getKind().equals(Kind.VARIABLE))
								setVariableType(s);
							blockNode.addStatements(visit(s));
						}
						blockType = saveBlockType;

						InitializerBlock initBlockNode;
						if (blockType.equals(BlockType.INSTANCE_INIT)) {
							setPositionAndGenerated(jcStatement, ret);
							initBlockNode = (InstanceInitializerBlock) fact
									.createNode(NodeKind.ndkInstanceInitializerBlock);
							ret = initBlockNode.getId();
							initBlockNode.setBody(blockNode.getId());
						} else if (blockType.equals(BlockType.STATIC_INIT)) {
							setPositionAndGenerated(jcStatement, ret);
							initBlockNode = (InitializerBlock) fact.createNode(NodeKind.ndkStaticInitializerBlock);
							ret = initBlockNode.getId();
							initBlockNode.setBody(blockNode.getId());
						}
					} finally {
						blockType = BlockType.NORMAL;
						lastBlockNode = null;
					}
					break;
				}
				case BREAK: {
					JCBreak jcBreak = (JCBreak) jcStatement;
					Break breakNode = (Break) fact.createNode(NodeKind.ndkBreak);
					ret = breakNode.getId();

					Name name = jcBreak.label;

					if (name != null) {
						breakNode.setLabel(name.toString());
					}
					break;
				}
				case CASE: {
					JCCase jcCase = (JCCase) jcStatement;
					SwitchLabel switchLabelNode;

					if (jcCase.pat == null) {
						switchLabelNode = (Default) fact.createNode(NodeKind.ndkDefault);
					} else {
						switchLabelNode = (Case) fact.createNode(NodeKind.ndkCase);
						((Case) switchLabelNode).setExpression(visit(jcCase.pat));
					}

					ret = switchLabelNode.getId();

					for (JCStatement stmt : jcCase.stats) {
						if (stmt.getKind() == Kind.VARIABLE) {
							varDeclType = VarDeclType.VARIABLE;
						}
						switchLabelNode.addStatements(visit(stmt));
					}
					break;
				}
				case CONTINUE: {
					JCContinue jcContinue = (JCContinue) jcStatement;
					Continue continueNode = (Continue) fact.createNode(NodeKind.ndkContinue);
					ret = continueNode.getId();

					Name name = jcContinue.label;

					if (name != null) {
						continueNode.setLabel(name.toString());
					}
					break;
				}
				case DO_WHILE_LOOP: {
					JCDoWhileLoop jcDoWhileLoop = (JCDoWhileLoop) jcStatement;
					Do doNode = (Do) fact.createNode(NodeKind.ndkDo);
					ret = doNode.getId();

					doNode.setCondition(visit(jcDoWhileLoop.cond));
					doNode.setSubstatement(visit(jcDoWhileLoop.body));

					break;
				}
				case ENHANCED_FOR_LOOP: {
					JCEnhancedForLoop jcEFor = (JCEnhancedForLoop) jcStatement;
					columbus.java.asg.statm.EnhancedFor enhancedForNode = (EnhancedFor) fact
							.createNode(NodeKind.ndkEnhancedFor);
					ret = enhancedForNode.getId();

					varDeclType = VarDeclType.PARAMETER;

					enhancedForNode.setParameter(visit(jcEFor.var));
					enhancedForNode.setExpression(visit(jcEFor.expr));
					enhancedForNode.setSubstatement(visit(jcEFor.body));

					break;
				}
				case EXPRESSION_STATEMENT: {
					JCExpressionStatement jcExpressionStatement = (JCExpressionStatement) jcStatement;
					ExpressionStatement expressionStatementNode = (ExpressionStatement) fact
							.createNode(NodeKind.ndkExpressionStatement);
					ret = expressionStatementNode.getId();

					expressionStatementNode.setExpression(visit(jcExpressionStatement.expr));

					break;
				}
				case FOR_LOOP: {
					JCForLoop jcForLoop = (JCForLoop) jcStatement;
					BasicFor basicForNode = (BasicFor) fact.createNode(NodeKind.ndkBasicFor);
					ret = basicForNode.getId();

					for (JCStatement stmt : jcForLoop.init) {
						if (stmt.getKind().equals(Kind.VARIABLE))
							varDeclType = VarDeclType.VARIABLE;
						basicForNode.addInitializers(visit(stmt));
					}

					if (jcForLoop.cond != null) {
						basicForNode.setCondition(visit(jcForLoop.cond));
					}

					for (JCExpressionStatement stmt : jcForLoop.step) {
						basicForNode.addUpdates(visit(stmt));
					}

					basicForNode.setSubstatement(visit(jcForLoop.body));

					break;
				}
				case IF: {
					JCIf jcIf = (JCIf) jcStatement;
					If ifNode = (If) fact.createNode(NodeKind.ndkIf);
					ret = ifNode.getId();

					ifNode.setCondition(visit(jcIf.cond));

					ifNode.setSubstatement(visit(jcIf.thenpart));

					if (jcIf.elsepart != null) {
						ifNode.setFalseSubstatement(visit(jcIf.elsepart));
					}

					break;
				}
				case LABELED_STATEMENT: {
					JCLabeledStatement jcLabeledStatement = (JCLabeledStatement) jcStatement;
					LabeledStatement labeledStatementNode = (LabeledStatement) fact
							.createNode(NodeKind.ndkLabeledStatement);
					ret = labeledStatementNode.getId();

					labeledStatementNode.setLabel(jcLabeledStatement.label.toString());
					labeledStatementNode.setStatement(visit(jcLabeledStatement.body));

					break;
				}
				case RETURN: {
					Return returnNode = (Return) fact.createNode(NodeKind.ndkReturn);
					JCReturn jcReturn = (JCReturn) jcStatement;
					ret = returnNode.getId();

					if (jcReturn.expr != null) {
						returnNode.setExpression(visit(jcReturn.expr));
					}

					break;
				}
				case EMPTY_STATEMENT: {
					Empty emptyNode = (Empty) fact.createNode(NodeKind.ndkEmpty);
					ret = emptyNode.getId();
					break;
				}
				case SWITCH: {
					JCSwitch jcSwitch = (JCSwitch) jcStatement;
					Switch switchNode = (Switch) fact.createNode(NodeKind.ndkSwitch);
					ret = switchNode.getId();

					switchNode.setCondition(visit(jcSwitch.selector));

					for (JCCase jcCase : jcSwitch.cases) {
						switchNode.addCases(visit(jcCase));
					}
					break;
				}
				case SYNCHRONIZED: {
					JCSynchronized jcSynchronized = (JCSynchronized) jcStatement;
					Synchronized synchronizedNode = (Synchronized) fact.createNode(NodeKind.ndkSynchronized);
					ret = synchronizedNode.getId();

					synchronizedNode.setLock(visit(jcSynchronized.lock));
					synchronizedNode.setBlock(visit(jcSynchronized.body));

					break;
				}
				case THROW: {
					JCThrow jcThrow = (JCThrow) jcStatement;
					Throw throwNode = (Throw) fact.createNode(NodeKind.ndkThrow);
					ret = throwNode.getId();

					throwNode.setExpression(visit(jcThrow.expr));

					break;
				}
				case TRY: {
					JCTry jcTry = (JCTry) jcStatement;
					Try tryNode = (Try) fact.createNode(NodeKind.ndkTry);
					ret = tryNode.getId();

					for (JCTree resource : jcTry.resources) {
						varDeclType = VarDeclType.VARIABLE;
						tryNode.addResources(visit(resource));
					}

					tryNode.setBlock(visit(jcTry.body));

					for (JCCatch catcher : jcTry.catchers) {
						tryNode.addHandlers(visit(catcher));
					}

					if (jcTry.finalizer != null) {
						tryNode.setFinallyBlock(visit(jcTry.finalizer));
					}
					break;
				}
				case VARIABLE: {
					try {
						JCVariableDecl jcVariableDecl = (JCVariableDecl) jcStatement;
						VariableDeclaration varDeclNode = null;
						switch (varDeclType) {
						case VARIABLE: {
							Variable variableNode = (Variable) fact.createNode(NodeKind.ndkVariable);
							varDeclNode = variableNode;

							if (jcVariableDecl.init != null) {
								variableNode.setInitialValue(visit(jcVariableDecl.init));
							}
							break;
						}
						case ENUMCONST: {
							columbus.java.asg.struc.EnumConstant enumConstantNode = (columbus.java.asg.struc.EnumConstant) fact
									.createNode(NodeKind.ndkEnumConstant);
							varDeclNode = enumConstantNode;

							if (jcVariableDecl.init != null) {
								if (jcVariableDecl.init.getKind().equals(Kind.NEW_CLASS)) {
									int id = visit(jcVariableDecl.init);
									enumConstantNode.setNewClass(id);

									NewClass newClass = enumConstantNode.getNewClass();
									newClass.getTypeName().setIsCompilerGenerated(true);
									AnonymousClass anonClass = newClass.getAnonymousClass();
									if (anonClass != null) {
										if(anonClass.getSuperClass() != null) {
											anonClass.getSuperClass().setIsCompilerGenerated(true);
										} else {
											logger.debug("debug.jan.TreeBuilder.anonymClassDontHaveSuperClass",newClass.getId());											
										}
									} else {
										newClass.setIsCompilerGenerated(true);
									}
								} else {
									if (logger.isDebugEnabled()) {
										logger.debug("debug.jan.TreeBuilder.unexpectedEnumConstInitType",
												jcVariableDecl.init.getKind());
									}
								}
							}
							break;
						}
						case PARAMETER: {
							Parameter parameterNode = (Parameter) fact.createNode(NodeKind.ndkParameter);
							varDeclNode = parameterNode;
							break;
						}
						case NONE:
						default:
							throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.varTypeIsNotGiven"));
						}

						if (jcVariableDecl.vartype != null) {
							int id = visitTypeExpression(jcVariableDecl.vartype);
							varDeclNode.setType(id);
							if (varDeclNode.getNodeKind() == NodeKind.ndkEnumConstant) {
								varDeclNode.getType().setIsCompilerGenerated(true);
							}
						}

						varDeclNode.setName(jcVariableDecl.name.toString());
						setModifiersAndAnnotations(jcVariableDecl.mods, varDeclNode);
						ret = varDeclNode.getId();

						if (jcVariableDecl.sym != null) {
							symMaps.getVariableDeclarationMap().put(jcVariableDecl.sym, ret);
							symMaps.addVarType(jcVariableDecl.sym);
						}
					} finally {
						varDeclType = VarDeclType.NONE;
					}
					break;
				}
				case WHILE_LOOP: {
					JCWhileLoop jcWhileLoop = (JCWhileLoop) jcStatement;
					While whileNode = (While) fact.createNode(NodeKind.ndkWhile);
					ret = whileNode.getId();

					whileNode.setCondition(visit(jcWhileLoop.cond));
					whileNode.setSubstatement(visit(jcWhileLoop.body));

					break;
				}

				default:
					throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.jcStatementIsNotHandled",
							jcStatement.getKind()));
				}
			}
			if (ret == 0) {
				throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.atTheEndOfVisitStmtRetIsZero"));
			} else {
				setPositionAndGenerated(jcStatement, ret);
			}

		} finally {
			if (generatedTreeRoot != null && generatedTreeRoot == jcStatement) {
				generatedTreeRoot = null;
			}
		}

		return ret;
	}

	// Expression
	private int visit(JCExpression jcExpr) {
		int ret = 0;

		if (jcExpr == null) {
			throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.visitExprGetANullNode"));
		}

		if (jcExpr instanceof JCAssignOp) {
			JCAssignOp jcAssignOp = (JCAssignOp) jcExpr;
			Assignment assignmentNode = (Assignment) fact.createNode(NodeKind.ndkAssignment);

			assignmentNode.setLeftOperand(visit(jcAssignOp.lhs));
			assignmentNode.setRightOperand(visit(jcAssignOp.rhs));

			switch (jcExpr.getKind()) {
			case MULTIPLY_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askTimesAssign);
				break;
			case DIVIDE_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askDivideAssign);
				break;
			case REMAINDER_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askRemainderAssign);
				break;
			case PLUS_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askPlusAssign);
				break;
			case MINUS_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askMinusAssign);
				break;
			case LEFT_SHIFT_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askLeftShiftAssign);
				break;
			case RIGHT_SHIFT_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askSignedRightShiftAssign);
				break;
			case UNSIGNED_RIGHT_SHIFT_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askUnsignedRightShiftAssign);
				break;
			case AND_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askAndAssign);
				break;
			case XOR_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askXorAssign);
				break;
			case OR_ASSIGNMENT:
				assignmentNode.setOperator(AssignmentOperatorKind.askOrAssign);
				break;
			default:
				throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.invalidOpKind", jcExpr.getKind()));
			}
			ret = assignmentNode.getId();
		} else if (jcExpr instanceof JCBinary) {
			JCBinary jcBinary = (JCBinary) jcExpr;
			InfixExpression infixExprNode = (InfixExpression) fact.createNode(NodeKind.ndkInfixExpression);

			infixExprNode.setLeftOperand(visit(jcBinary.lhs));
			infixExprNode.setRightOperand(visit(jcBinary.rhs));

			switch (jcExpr.getKind()) {
			case MULTIPLY:
				infixExprNode.setOperator(InfixOperatorKind.iokTimes);
				break;
			case DIVIDE:
				infixExprNode.setOperator(InfixOperatorKind.iokDivide);
				break;
			case REMAINDER:
				infixExprNode.setOperator(InfixOperatorKind.iokRemainder);
				break;
			case PLUS:
				infixExprNode.setOperator(InfixOperatorKind.iokPlus);
				break;
			case MINUS:
				infixExprNode.setOperator(InfixOperatorKind.iokMinus);
				break;
			case LEFT_SHIFT:
				infixExprNode.setOperator(InfixOperatorKind.iokLeftShift);
				break;
			case RIGHT_SHIFT:
				infixExprNode.setOperator(InfixOperatorKind.iokSignedRightShift);
				break;
			case UNSIGNED_RIGHT_SHIFT:
				infixExprNode.setOperator(InfixOperatorKind.iokUnsignedRightShift);
				break;
			case LESS_THAN:
				infixExprNode.setOperator(InfixOperatorKind.iokLessThan);
				break;
			case GREATER_THAN:
				infixExprNode.setOperator(InfixOperatorKind.iokGreaterThan);
				break;
			case LESS_THAN_EQUAL:
				infixExprNode.setOperator(InfixOperatorKind.iokLessThanOrEqualTo);
				break;
			case GREATER_THAN_EQUAL:
				infixExprNode.setOperator(InfixOperatorKind.iokGreaterThanOrEqualTo);
				break;
			case EQUAL_TO:
				infixExprNode.setOperator(InfixOperatorKind.iokEqualTo);
				break;
			case NOT_EQUAL_TO:
				infixExprNode.setOperator(InfixOperatorKind.iokNotEqualTo);
				break;
			case AND:
				infixExprNode.setOperator(InfixOperatorKind.iokBitwiseAndLogicalAnd);
				break;
			case XOR:
				infixExprNode.setOperator(InfixOperatorKind.iokBitwiseAndLogicalXor);
				break;
			case OR:
				infixExprNode.setOperator(InfixOperatorKind.iokBitwiseAndLogicalOr);
				break;
			case CONDITIONAL_AND:
				infixExprNode.setOperator(InfixOperatorKind.iokConditionalAnd);
				break;
			case CONDITIONAL_OR:
				infixExprNode.setOperator(InfixOperatorKind.iokConditionalOr);
				break;
			default:
				throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.invalidOpKind", jcExpr.getKind()));
			}

			ret = infixExprNode.getId();
		} else if (jcExpr instanceof JCLiteral) {
			JCLiteral jcLiteral = (JCLiteral) jcExpr;

			switch (jcExpr.getKind()) {
			case INT_LITERAL: {
				IntegerLiteral l = (IntegerLiteral) fact.createNode(NodeKind.ndkIntegerLiteral);
				l.setValue(jcLiteral.format);
				l.setIntValue((int) jcLiteral.value);
				ret = l.getId();
				break;
			}
			case LONG_LITERAL: {
				LongLiteral l = (LongLiteral) fact.createNode(NodeKind.ndkLongLiteral);
				l.setValue(jcLiteral.format);
				l.setLongValue((long) jcLiteral.value);
				ret = l.getId();
				break;
			}
			case FLOAT_LITERAL: {
				FloatLiteral l = (FloatLiteral) fact.createNode(NodeKind.ndkFloatLiteral);
				l.setValue(jcLiteral.format);
				l.setFloatValue((float) jcLiteral.value);
				ret = l.getId();
				break;
			}
			case DOUBLE_LITERAL: {
				DoubleLiteral l = (DoubleLiteral) fact.createNode(NodeKind.ndkDoubleLiteral);
				l.setValue(jcLiteral.format);
				l.setDoubleValue((double) jcLiteral.value);
				ret = l.getId();
				break;
			}
			case BOOLEAN_LITERAL: {
				BooleanLiteral l = (BooleanLiteral) fact.createNode(NodeKind.ndkBooleanLiteral);
				l.setBooleanValue((boolean) jcLiteral.getValue());
				ret = l.getId();
				break;
			}
			case CHAR_LITERAL: {
				CharacterLiteral l = (CharacterLiteral) fact.createNode(NodeKind.ndkCharacterLiteral);
				l.setCharValue((char) jcLiteral.getValue());
				l.setFormatString(jcLiteral.format);
				ret = l.getId();
				break;
			}
			case STRING_LITERAL: {
				StringLiteral l = (StringLiteral) fact.createNode(NodeKind.ndkStringLiteral);
				l.setValue(jcLiteral.format);
				l.setFormatString(jcLiteral.format);
				ret = l.getId();
				break;
			}
			case NULL_LITERAL: {
				NullLiteral l = (NullLiteral) fact.createNode(NodeKind.ndkNullLiteral);
				ret = l.getId();
				break;
			}

			default:
				throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.invalidLiteralKind", jcExpr.getKind()));
			}
		} else if (jcExpr instanceof JCUnary) {
			JCUnary jcUnary = (JCUnary) jcExpr;
			Unary unary = null;

			switch (jcExpr.getKind()) {
			case POSTFIX_INCREMENT:
			case POSTFIX_DECREMENT: {
				PostfixExpression postfixExprNode = (PostfixExpression) fact.createNode(NodeKind.ndkPostfixExpression);
				unary = postfixExprNode;

				if (jcExpr.getKind() == Kind.POSTFIX_INCREMENT) {
					postfixExprNode.setOperator(PostfixOperatorKind.pookIncrement);
				} else {
					postfixExprNode.setOperator(PostfixOperatorKind.pookDecrement);
				}
				break;
			}
			default: {
				PrefixExpression prefixExprNode = (PrefixExpression) fact.createNode(NodeKind.ndkPrefixExpression);
				unary = prefixExprNode;
				switch (jcExpr.getKind()) {
				case PREFIX_INCREMENT:
					prefixExprNode.setOperator(PrefixOperatorKind.peokIncrement);
					break;
				case PREFIX_DECREMENT:
					prefixExprNode.setOperator(PrefixOperatorKind.peokDecrement);
					break;
				case UNARY_PLUS:
					prefixExprNode.setOperator(PrefixOperatorKind.peokPlus);
					break;
				case UNARY_MINUS:
					prefixExprNode.setOperator(PrefixOperatorKind.peokMinus);
					break;
				case BITWISE_COMPLEMENT:
					prefixExprNode.setOperator(PrefixOperatorKind.peokComplement);
					break;
				case LOGICAL_COMPLEMENT:
					prefixExprNode.setOperator(PrefixOperatorKind.peokNot);
					break;
				case OTHER:
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.TreeBuilder.otherJCUnaryKind", jcExpr.toString());
					}
					break;
				default:
					throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.invalidUnaryKind",
							jcExpr.getKind()));
				}
				break;
			}
			}
			unary.setOperand(visit(jcUnary.arg));
			ret = unary.getId();
		} else {
			switch (jcExpr.getKind()) {
			case ARRAY_TYPE:
			case PRIMITIVE_TYPE:
			case PARAMETERIZED_TYPE:
			case UNION_TYPE:
			case ANNOTATED_TYPE:
			case INTERSECTION_TYPE:
				logger.error("ex.jan.TreeBuilder.erroneousInsteadOfExpr", jcExpr.getKind());
				ErroneousTypeExpression errr = (ErroneousTypeExpression) fact
						.createNode(NodeKind.ndkErroneousTypeExpression);
				ret = errr.getId();
				break;
			case IDENTIFIER: {
				JCIdent jcIdent = (JCIdent) jcExpr;

				Name name = jcIdent.name;

				if (name == names._this) {
					This thisNode = (This) fact.createNode(NodeKind.ndkThis);
					ret = thisNode.getId();
				} else if (name == names._super) {
					Super superNode = (Super) fact.createNode(NodeKind.ndkSuper);
					ret = superNode.getId();
				} else {
					Identifier identifierNode = (Identifier) fact.createNode(NodeKind.ndkIdentifier);
					identifierNode.setName(name.toString());

					ret = identifierNode.getId();

					if (jcIdent.sym != null) {
						symMaps.addClassAndInterfaceUsageSet(jcIdent.sym);
						symMaps.addClassAndInterfaceToFullBuildSet(jcIdent.sym.owner);
						symMaps.addToIdMap(ret, jcIdent.sym);
					}

				}
				break;
			}
			case MEMBER_SELECT: {
				JCFieldAccess jcFieldAccess = (JCFieldAccess) jcExpr;
				int rightOpId = 0;
				if (jcFieldAccess.name == names._class) {
					ClassLiteral classLiteralNode = (ClassLiteral) fact.createNode(NodeKind.ndkClassLiteral);
					classLiteralNode.setComponentType(visitTypeExpression(jcFieldAccess.selected));
					// adding the type of class literal to external class build set
					if (jcExpr.type != null) {
						if (jcExpr.type instanceof Type.ClassType) {
							for (Type t : ((Type.ClassType) jcExpr.type).typarams_field) {
								symMaps.addMemberToTypeSymbolSet(t.tsym);
							}
						}
					}
					ret = classLiteralNode.getId();
				} else {
					FieldAccess fieldAccessNode = (FieldAccess) fact.createNode(NodeKind.ndkFieldAccess);

					fieldAccessNode.setLeftOperand(visit(jcFieldAccess.selected));

					if (jcFieldAccess.sym != null) {
						if (jcFieldAccess.name == names._this) {
							This thisNode = (This) fact.createNode(NodeKind.ndkThis);
							rightOpId = thisNode.getId();
							symMaps.addNodeType(jcExpr.type, thisNode.getId());
							fieldAccessNode.setRightOperand(thisNode);
						} else if (jcFieldAccess.name == names._super) {
							Super superNode = (Super) fact.createNode(NodeKind.ndkSuper);
							rightOpId = superNode.getId();
							symMaps.addNodeType(jcExpr.type, superNode.getId());
							fieldAccessNode.setRightOperand(superNode);
						} else {
							Identifier identifierNode = (Identifier) fact.createNode(NodeKind.ndkIdentifier);
							identifierNode.setName(jcFieldAccess.name.toString());
							rightOpId = identifierNode.getId();
							fieldAccessNode.setRightOperand(identifierNode);

							symMaps.addClassAndInterfaceUsageSet(jcFieldAccess.sym);

							if (!jcFieldAccess.sym.type.isPrimitive()) {
								if ((jcFieldAccess.sym instanceof VarSymbol
										|| jcFieldAccess.sym instanceof MethodSymbol || jcFieldAccess.sym instanceof ClassSymbol)
										&& !(jcFieldAccess.sym.owner instanceof PackageSymbol)) {
									symMaps.addClassAndInterfaceToFullBuildSet(jcFieldAccess.sym.owner);
								}

							} else {
								// for example: array.length, where array is
								// boolean[]
								symMaps.addClassAndInterfaceToFullBuildSet(jcFieldAccess.selected.type.tsym);
							}
							symMaps.addNodeType(jcFieldAccess.sym.type, identifierNode.getId());
							symMaps.addToIdMap(identifierNode.getId(), jcFieldAccess.sym);
						}
						symMaps.addMemberToTypeSymbolSet(jcFieldAccess.sym.owner);
					} else {
						if (jcFieldAccess.name != null) {
							Identifier identifierNode = (Identifier) fact.createNode(NodeKind.ndkIdentifier);
							identifierNode.setName(jcFieldAccess.name.toString());
							rightOpId = identifierNode.getId();
							fieldAccessNode.setRightOperand(identifierNode);
							// the last part of the field accesses in imports dont have type nor symbol
							if (!inImport) {
								if (logger.isDebugEnabled()) {
									logger.debug("debug.jan.TreeBuilder.jcFieldAccesSymWasNull", jcFieldAccess);
								}
							}
						}
					}
					if (rightOpId != 0) {
						setPositionAndGenerated(jcFieldAccess, fieldAccessNode.getId());
						Positioned rightId = (Positioned) fact.getRef(rightOpId);
						setPositionOfRightExpr(fieldAccessNode, rightId, jcFieldAccess.name.toString().length());
					}
					ret = fieldAccessNode.getId();
				}
				break;
			}
			case ANNOTATION: {
				// 0 -> marker
				// 1( !Assign) -> single
				// 1(assign)\2.. ->normal
				JCAnnotation jcAnnotation = (JCAnnotation) jcExpr;
				Annotation annotationNode = null;

				switch (jcAnnotation.args.size()) {
				case 0:
					annotationNode = (MarkerAnnotation) fact.createNode(NodeKind.ndkMarkerAnnotation);
					break;
				case 1:
					// in dir analyze sometimes the javac don't create @AnnotName(value=XY.xy) from @AnnotName(XY.xy)
					JCExpression jcArgZero = jcAnnotation.args.get(0);

					if (jcArgZero instanceof JCAssign) {
						JCAssign jcAssign = (JCAssign) jcAnnotation.args.get(0);
						if (jcAssign.lhs.pos == jcAssign.rhs.pos) {
							annotationNode = (Annotation) fact.createNode(NodeKind.ndkSingleElementAnnotation);
							((SingleElementAnnotation) annotationNode).setArgument(visit(jcAssign.rhs));
							break;
						}
					} else {
						annotationNode = (Annotation) fact.createNode(NodeKind.ndkSingleElementAnnotation);
						((SingleElementAnnotation) annotationNode).setArgument(visit(jcArgZero));
						break;
					}

				default:
					annotationNode = (NormalAnnotation) fact.createNode(NodeKind.ndkNormalAnnotation);
					for (JCExpression a : jcAnnotation.args) {
						((NormalAnnotation) annotationNode).addArguments(visit(a));
					}
					break;
				}

				if (jcAnnotation.annotationType != null) {
					annotationNode.setAnnotationName(visitTypeExpression(jcAnnotation.annotationType));
				}

				ret = annotationNode.getId();
				break;
			}
			case ARRAY_ACCESS: {
				JCArrayAccess jcArrayAccess = (JCArrayAccess) jcExpr;
				ArrayAccess arrayAccessNode = (ArrayAccess) fact.createNode(NodeKind.ndkArrayAccess);

				arrayAccessNode.setLeftOperand(visit(jcArrayAccess.indexed));
				arrayAccessNode.setRightOperand(visit(jcArrayAccess.index));

				ret = arrayAccessNode.getId();
				break;
			}
			case ASSIGNMENT: {
				JCAssign jcAssign = (JCAssign) jcExpr;
				Assignment assignmentNode = (Assignment) fact.createNode(NodeKind.ndkAssignment);

				assignmentNode.setLeftOperand(visit(jcAssign.lhs));
				assignmentNode.setRightOperand(visit(jcAssign.rhs));

				assignmentNode.setOperator(AssignmentOperatorKind.askAssign);

				ret = assignmentNode.getId();
				break;
			}

			case CONDITIONAL_EXPRESSION: {
				JCConditional jcConditional = (JCConditional) jcExpr;
				Conditional conditionalNode = (Conditional) fact.createNode(NodeKind.ndkConditional);

				conditionalNode.setCondition(visit(jcConditional.cond));
				conditionalNode.setTrueExpression(visit(jcConditional.truepart));
				conditionalNode.setFalseExpression(visit(jcConditional.falsepart));

				ret = conditionalNode.getId();
				break;
			}
			case ERRONEOUS: {
				JCErroneous jcErroneus = (JCErroneous) jcExpr;
				Erroneous erroneousNode = (Erroneous) fact.createNode(NodeKind.ndkErroneous);

				if (jcErroneus.errs != null) {
					for (JCTree err : jcErroneus.errs) {
						if (err.getKind() != Kind.MODIFIERS) {
							erroneousNode.addErrors(visit(err));
						}
					}
				}

				ret = erroneousNode.getId();
				break;
			}
			case INSTANCE_OF: {
				JCInstanceOf jcInstanceOf = (JCInstanceOf) jcExpr;
				InstanceOf instanceOfNode = (InstanceOf) fact.createNode(NodeKind.ndkInstanceOf);

				instanceOfNode.setOperand(visit(jcInstanceOf.expr));
				instanceOfNode.setTypeOperand(visitTypeExpression(jcInstanceOf.clazz));

				ret = instanceOfNode.getId();
				break;
			}
			case METHOD_INVOCATION: {
				// public Type varargsElement;
				JCMethodInvocation jcMethodInvocation = (JCMethodInvocation) jcExpr;
				MethodInvocation methodInvocationNode = (MethodInvocation) fact
						.createNode(NodeKind.ndkMethodInvocation);
				ret = methodInvocationNode.getId();

				for (JCExpression exp : jcMethodInvocation.args) {
					methodInvocationNode.addArguments(visit(exp));
				}

				for (JCExpression typeargs : jcMethodInvocation.typeargs) {
					methodInvocationNode.addTypeArguments(visitTypeExpression(typeargs));
				}

				methodInvocationNode.setOperand(visit(jcMethodInvocation.meth));

				if (jcMethodInvocation.meth.getKind() == Kind.MEMBER_SELECT) {
					JCFieldAccess jcFieldAcess = (JCFieldAccess) jcMethodInvocation.meth;
					if (jcFieldAcess.sym != null) {
						if (jcFieldAcess.sym.owner != null) {
							symMaps.addMemberToTypeSymbolSet(jcFieldAcess.sym.owner);
						}
						symMaps.getMethodInvMap().put(ret, jcFieldAcess.sym);
					}
				} else if (jcMethodInvocation.meth.getKind() == Kind.IDENTIFIER) {
					JCIdent jcIdent = (JCIdent) jcMethodInvocation.meth;
					if (jcIdent.sym != null && jcIdent.sym.owner != null) {
						symMaps.getMethodInvMap().put(ret, jcIdent.sym);
						symMaps.addMemberToTypeSymbolSet(jcIdent.sym.owner);
						if (jcIdent.name == names._super) {
							symMaps.addClassAndInterfaceToFullBuildSet(jcIdent.sym.owner);
						}
					}
				} else {
					logger.debug("debug.jan.TreeBuilder.unexpectedMethKind");
				}

				if (jcMethodInvocation.type != null && jcMethodInvocation.type.tsym != null
						&& jcMethodInvocation.type.getKind() != TypeKind.VOID) {
					symMaps.addMethodReturnType(jcMethodInvocation.type.tsym);
				}

				break;
			}
			case NEW_ARRAY: {
				JCNewArray jcNewArray = (JCNewArray) jcExpr;
				NewArray newArrayNode = (NewArray) fact.createNode(NodeKind.ndkNewArray);
				ret = newArrayNode.getId();

				if (jcNewArray.elemtype != null) {
					newArrayNode.setComponentType(visitTypeExpression(jcNewArray.elemtype));
				}

				for (JCExpression dim : jcNewArray.dims) {
					newArrayNode.addDimensions(visit(dim));
				}
				if (jcNewArray.elems != null) {
					for (JCExpression elem : jcNewArray.elems) {
						newArrayNode.addInitializers(visit(elem));
					}
				}

				break;
			}
			case NEW_CLASS: {
				JCNewClass jcNewClass = (JCNewClass) jcExpr;
				NewClass newClassNode = (NewClass) fact.createNode(NodeKind.ndkNewClass);
				ret = newClassNode.getId();

				// to handle a.new XY(){};
				JCUnary moveArgToEncl = null;
				for (JCExpression exp : jcNewClass.args) {
					if (exp instanceof JCUnary) {
						JCUnary jcUnary = (JCUnary) exp;
						if (jcUnary.operator != null && jcUnary.operator == symtab.nullcheck) {
							moveArgToEncl = jcUnary;
						}
					}
				}

				if (moveArgToEncl == null) {
					if (jcNewClass.encl != null) {
						newClassNode.setEnclosingExpression(visit(jcNewClass.encl));
					}
				} else {
					newClassNode.setEnclosingExpression(visit(moveArgToEncl.arg));
				}

				if (moveArgToEncl != null) {
					innerAnonymusClassSuperClass = jcNewClass.clazz;
				}

				if (jcNewClass.clazz != null) {
					newClassNode.setTypeName(visitTypeExpression(jcNewClass.clazz));
				}

				if (jcNewClass.constructor != null) {
					symMaps.getNewClassConstructorMap().put(ret, jcNewClass.constructor);
					symMaps.addClassAndInterfaceToFullBuildSet(jcNewClass.constructor.owner);
				}

				for (JCExpression exp : jcNewClass.args) {
					if (!exp.equals(moveArgToEncl)) {
						newClassNode.addArguments(visit(exp));
					}
				}

				for (JCExpression exp : jcNewClass.typeargs) {
					newClassNode.addTypeArguments(visitTypeExpression(exp));
				}

				if (jcNewClass.def != null) {
					isAnonymusClass = true;
					newClassNode.setAnonymousClass(visit(jcNewClass.def));
				}
				break;
			}
			case PARENTHESIZED: {
				JCParens jcParens = (JCParens) jcExpr;
				ParenthesizedExpression parenthesizedNode = (ParenthesizedExpression) fact
						.createNode(NodeKind.ndkParenthesizedExpression);

				parenthesizedNode.setOperand(visit(jcParens.expr));

				ret = parenthesizedNode.getId();
				break;
			}
			case TYPE_CAST: {
				JCTypeCast jcTypeCast = (JCTypeCast) jcExpr;
				TypeCast typeCastNode = (TypeCast) fact.createNode(NodeKind.ndkTypeCast);

				typeCastNode.setOperand(visit(jcTypeCast.expr));
				typeCastNode.setTypeOperand(visitTypeExpression(jcTypeCast.clazz));

				ret = typeCastNode.getId();
				break;
			}
			// TODO java 1.8
			case LAMBDA_EXPRESSION:
			case MEMBER_REFERENCE:
			{
				logger.debug("ex.jan.TreeBuilder.erroneousInsteadOfJava18Expr", jcExpr.getKind());
				Erroneous erroneous = (Erroneous) fact.createNode(NodeKind.ndkErroneous);
				ret = erroneous.getId();
				break;
			}
			default:
				throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.jcExprNotHandledYet", jcExpr.getKind()));
			}
		}
		if (ret == 0) {
			throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.atTheEndOfVisitExprRetIsZero"));
		} else {
			setPositionAndGenerated(jcExpr, ret);
			if (jcExpr.type != null) {
				// TODO fix conditional expression's type building after schema changes.
				if (jcExpr.getKind() == Kind.CONDITIONAL_EXPRESSION
						&& (jcExpr.type.tsym == null || jcExpr.type.tsym.toString().equals("<anonymous >"))) {
					symMaps.addNodeType(((JCConditional) jcExpr).truepart.type, ret);
				} else {
					symMaps.addNodeType(jcExpr.type, ret);
				}
			} else {
				if (inImport) {
					// the last part of the field accesses in imports dont have type nor symbol
				} else {
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.TreeBuilder.exprDontHaveAType", ret);
					}
				}
			}
		}
		return ret;
	}

	private int visitTypeExpression(JCTree jcTree) {

		int ret = 0;

		if (jcTree == null) {
			throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.visitExprGetANullNode"));
		}

		if (jcTree instanceof JCWildcard) {
			JCWildcard jcWildcard = (JCWildcard) jcTree;
			WildcardExpression wildcardExpreesionNode = (WildcardExpression) fact
					.createNode(NodeKind.ndkWildcardExpression);

			if (jcWildcard.inner != null) {
				wildcardExpreesionNode.setBound(visitTypeExpression(jcWildcard.inner));
			}
			switch (jcTree.getKind()) {
			case UNBOUNDED_WILDCARD:
				wildcardExpreesionNode.setKind(TypeBoundKind.tbkWildcard);
				break;
			case EXTENDS_WILDCARD:
				wildcardExpreesionNode.setKind(TypeBoundKind.tbkExtends);
				break;
			case SUPER_WILDCARD:
				wildcardExpreesionNode.setKind(TypeBoundKind.tbkSuper);
				break;
			default:
				throw new JavaException(
						logger.formatMessage("ex.jan.TreeBuilder.invalidWildCardType", jcTree.getKind()));
			}
			ret = wildcardExpreesionNode.getId();
		} else {

			{
				switch (jcTree.getKind()) {
				case ARRAY_TYPE: {
					JCArrayTypeTree jcArrayType = (JCArrayTypeTree) jcTree;
					ArrayTypeExpression arrayTypeExprNode = (ArrayTypeExpression) fact
							.createNode(NodeKind.ndkArrayTypeExpression);

					if (jcArrayType.elemtype != null) {
						arrayTypeExprNode.setComponentType(visitTypeExpression(jcArrayType.elemtype));
					}

					if (jcArrayType.type != null) {
						symMaps.addClassAndInterfaceUsageSet(jcArrayType.type.tsym);
					}

					ret = arrayTypeExprNode.getId();
					break;
				}
				case PRIMITIVE_TYPE: {
					JCPrimitiveTypeTree jcPrimTypeTree = (JCPrimitiveTypeTree) jcTree;
					PrimitiveTypeExpression primTypeExprNode = (PrimitiveTypeExpression) fact
							.createNode(NodeKind.ndkPrimitiveTypeExpression);
					switch (jcPrimTypeTree.typetag) {
					case BOOLEAN:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkBoolean);
						break;
					case BYTE:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkByte);
						break;
					case SHORT:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkShort);
						break;
					case INT:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkInt);
						break;
					case LONG:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkLong);
						break;
					case CHAR:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkChar);
						break;
					case FLOAT:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkFloat);
						break;
					case DOUBLE:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkDouble);
						break;
					case VOID:
						primTypeExprNode.setKind(PrimitiveTypeKind.ptkVoid);
						break;
					case ERROR:
						// handled at the begining of the method to dont create unnecessary nodes
					default:
						if (logger.isDebugEnabled()) {
							logger.debug("debug.jan.TreeBuilder.unknownPrimitiveTypeKind", jcPrimTypeTree.typetag);
						}
					}

					ret = primTypeExprNode.getId();
					break;
				}
				case PARAMETERIZED_TYPE: {
					JCTypeApply jcTypeApply = (JCTypeApply) jcTree;
					TypeApplyExpression typeApplyExprNode = (TypeApplyExpression) fact
							.createNode(NodeKind.ndkTypeApplyExpression);

					typeApplyExprNode.setRawType(visitTypeExpression(jcTypeApply.clazz));

					for (JCExpression arg : jcTypeApply.arguments) {
						typeApplyExprNode.addTypeArguments(visitTypeExpression(arg));
					}

					ret = typeApplyExprNode.getId();
					break;
				}
				case UNION_TYPE: {
					JCTypeUnion jcTypeUninon = (JCTypeUnion) jcTree;
					TypeUnionExpression typeUnionExprNode = (TypeUnionExpression) fact
							.createNode(NodeKind.ndkTypeUnionExpression);

					for (JCExpression alt : jcTypeUninon.alternatives) {
						typeUnionExprNode.addAlternatives(visitTypeExpression(alt));
					}

					ret = typeUnionExprNode.getId();
					break;
				}
				case IDENTIFIER: {
					JCIdent jcIdent = (JCIdent) jcTree;

					SimpleTypeExpression simpleTypeExprNode = (SimpleTypeExpression) fact
							.createNode(NodeKind.ndkSimpleTypeExpression);
					simpleTypeExprNode.setName(jcIdent.name.toString());
					ret = simpleTypeExprNode.getId();

					if (OptionParser.isBuildExtFromSource()) {
						symMaps.addClassAndInterfaceToFullBuildSet(jcIdent.sym);
					}
					symMaps.addClassAndInterfaceUsageSet(jcIdent.sym);

					break;
				}
				case MEMBER_SELECT: {
					JCFieldAccess jcFieldAccess = (JCFieldAccess) jcTree;
					QualifiedTypeExpression qualiTypeExprNode = (QualifiedTypeExpression) fact
							.createNode(NodeKind.ndkQualifiedTypeExpression);

					// to build p1.p2.OuterClass.InnerClass instead of .p1.p2.OuterClass.InnerClass
					boolean stop = false;
					if (jcFieldAccess.selected instanceof JCFieldAccess) {
						JCFieldAccess jFA = (JCFieldAccess) jcFieldAccess.selected;
						if (jFA.selected instanceof JCIdent) {
							JCIdent jI = (JCIdent) jFA.selected;
							if (jI.sym == symtab.rootPackage) {
								stop = true;
								SimpleTypeExpression sTExprNode = (SimpleTypeExpression) fact
										.createNode(NodeKind.ndkSimpleTypeExpression);
								sTExprNode.setName(jFA.name.toString());
								setPositionOfRightExpr(qualiTypeExprNode, sTExprNode, jcFieldAccess.name.toString()
										.length());
								symMaps.addNodeType(jcFieldAccess.type, sTExprNode.getId());
								qualiTypeExprNode.setQualifierType(sTExprNode.getId());
							}
						}
					}
					if (!stop) {
						qualiTypeExprNode.setQualifierType(visitTypeExpression(jcFieldAccess.selected));
					}

					SimpleTypeExpression simpleTypeExprNode = (SimpleTypeExpression) fact
							.createNode(NodeKind.ndkSimpleTypeExpression);
					simpleTypeExprNode.setName(jcFieldAccess.name.toString());
					setPositionAndGenerated(jcFieldAccess, qualiTypeExprNode.getId());
					setPositionOfRightExpr(qualiTypeExprNode, simpleTypeExprNode, jcFieldAccess.name.toString()
							.length());
					symMaps.addNodeType(jcFieldAccess.type, simpleTypeExprNode.getId());

					qualiTypeExprNode.setSimpleType(simpleTypeExprNode.getId());

					if (jcFieldAccess.sym != null) {
						symMaps.addMemberToTypeSymbolSet(jcFieldAccess.sym);
					} else {
						if (logger.isDebugEnabled()) {
							logger.debug("debug.jan.TreeBuilder.jcFieldAccesSymWasNull", jcTree);
						}
					}
					ret = qualiTypeExprNode.getId();
					break;
				}
				case ERRONEOUS: {
					JCErroneous jcErroneous = (JCErroneous) jcTree;
					ErroneousTypeExpression erroneousTypeExprNode = (ErroneousTypeExpression) fact
							.createNode(NodeKind.ndkErroneousTypeExpression);

					for (JCTree err : jcErroneous.errs) {
						if (err.getKind() != Kind.MODIFIERS) {
							erroneousTypeExprNode.addErrors(visit(err));
						}
					}
					ret = erroneousTypeExprNode.getId();
					break;
				}
				// TODO java 1.8
				case ANNOTATED_TYPE:
				case INTERSECTION_TYPE:
				{
					logger.debug("ex.jan.TreeBuilder.erroneousInsteadOfJava18TypeExpr", jcTree.getKind());
					ErroneousTypeExpression erroneousTypeExprNode = (ErroneousTypeExpression) fact
							.createNode(NodeKind.ndkErroneousTypeExpression);
					ret = erroneousTypeExprNode.getId();
					break;
				}
				default:
					ErroneousTypeExpression erroneousTypeExprNode = (ErroneousTypeExpression) fact
							.createNode(NodeKind.ndkErroneousTypeExpression);
					ret = erroneousTypeExprNode.getId();
					logger.error("ex.jan.TreeBuilder.erroneousInsteadOfTypeExpr", jcTree.getKind());
				}
			}
		}

		if (ret == 0) {
			throw new JavaException(logger.formatMessage("ex.jan.TreeBuilder.atTheEndOfVisitTypeExprRetIsZero"));
		} else {
			setPositionAndGenerated(jcTree, ret);

			if (jcTree.type != null) {
				symMaps.addNodeType(jcTree.type, ret);
			} else {
				if (logger.isDebugEnabled()) {
					logger.debug("debug.jan.TreeBuilder.exprDontHaveAType", ret);
				}
			}
		}
		return ret;
	}

	private int createSimpleTypeExpression(Type t) {
		TypeExpression typeExprNode;
		
		if(t.tsym != null) {
			SimpleTypeExpression simpleTypeExprNode = (SimpleTypeExpression) fact
				.createNode(NodeKind.ndkSimpleTypeExpression);
			typeExprNode = simpleTypeExprNode;
			simpleTypeExprNode.setName(t.tsym.name.toString());
			if (OptionParser.isBuildExtFromSource()) {
				symMaps.addClassAndInterfaceToFullBuildSet(t.tsym);
			}
			symMaps.addClassAndInterfaceUsageSet(t.tsym);			
		} else {
			typeExprNode = (ErroneousTypeExpression) fact
					.createNode(NodeKind.ndkErroneousTypeExpression);
		}		
		typeExprNode.setIsCompilerGenerated(true);
		
		symMaps.addNodeType(t, typeExprNode.getId());
		return typeExprNode.getId();
	}

	private void setMethodType(JCClassDecl jcClassDecl) {
		if (JANFlags.hasAnnotationFlag(jcClassDecl.mods.flags))
			methodType = MethodType.ANNOTATION_ELEMENT;
	}

	private void setVariableType(JCTree jcTree) {
		JCVariableDecl var = (JCVariableDecl) jcTree;
		if (JANFlags.hasEnumFlag(var.mods.flags))
			varDeclType = VarDeclType.ENUMCONST;
		else
			varDeclType = VarDeclType.VARIABLE;

	}

	private void setBlockType(JCTree jcTree) {
		JCBlock block = (JCBlock) jcTree;
		if (JANFlags.hasStaticFlag(block.flags)) {
			blockType = BlockType.STATIC_INIT;
		} else {
			blockType = BlockType.INSTANCE_INIT;
		}
	}

	private void setModifiersAndAnnotations(JCModifiers jcMods, NamedDeclaration memberNode) {
		JANFlags.setModifiers(jcMods.flags, memberNode);

		for (JCAnnotation a : jcMods.annotations) {
			memberNode.addAnnotations(visit(a));
		}

		setOtherPositions(jcMods, memberNode);
	}
		
	private void setPositionAndGenerated(JCTree jcTree, int nodeId) {
		Positioned nodeC = (Positioned) fact.getRef(nodeId);

		if (generatedTreeRoot != null) {
			nodeC.setIsCompilerGenerated(true);
		} else {
			if (jcTree != null) {
				Range range = createRange(jcTree);
				nodeC.setPosition(range);
				setOtherPositions(jcTree, nodeC);
			}
		}
	}

	private Range createRange(JCTree jcTree) {
		Range range = new Range(fact.getStringTable());
		range.setPathKey(actualColumbusCuPathKey);

		int pos = jcTree.pos;
		int wideStartPos = jcTree.getStartPosition();
		int wideEndPos = jcTree.getEndPosition(actualJCCU.endPositions);

		if (pos != Position.NOPOS) {
			range.setLine(lineMap.getLineNumber(pos));
			range.setCol(lineMap.getColumnNumber(pos));
		}

		if (wideStartPos != Position.NOPOS) {
			range.setWideLine(lineMap.getLineNumber(wideStartPos));
			range.setWideCol(lineMap.getColumnNumber(wideStartPos));
		}

		if (wideEndPos != Position.NOPOS) {
			range.setEndLine(lineMap.getLineNumber(wideEndPos)); // TODO not exist in the javac schema
			range.setEndCol(lineMap.getColumnNumber(wideEndPos));
			range.setWideEndLine(lineMap.getLineNumber(wideEndPos));
			range.setWideEndCol(lineMap.getColumnNumber(wideEndPos));
		}
		return range;
	}

	private void setPositionOfRightExpr(Positioned fieldAccessNode, Positioned node, int length) {
		if (generatedTreeRoot != null) {
			node.setIsCompilerGenerated(true);

		} else {
			Range faRange = fieldAccessNode.getPosition();

			Range range = new Range(fact.getStringTable());
			range.setPathKey(actualColumbusCuPathKey);

			int line = faRange.getWideEndLine();
			int endCol = faRange.getWideEndCol();
			int startCol = endCol - length;
			
			if(startCol< 0) {
				startCol = 0;
			}

			range.setLine(line);
			range.setCol(startCol);
			range.setEndLine(line);
			range.setEndCol(endCol);
			range.setWideLine(line);
			range.setWideCol(startCol);
			range.setWideEndLine(line);
			range.setWideEndCol(endCol);

			node.setPosition(range);
		}
	}

	private Range getRangeFromOtherPosition(int pos, TokenKind token, Name name) {
		Range range = null;
		
		if (pos != Position.NOPOS) {
			int line = 0, col = 0, endLine = 0, endCol = 0;
			line = lineMap.getLineNumber(pos);
			col = lineMap.getColumnNumber(pos);
			endLine = line;
			if (token.name != null) {
				endCol = col + token.name.length();
			} else {
				if (name != null) {
					endCol = col + name.length();
				} else {
					endCol = col + 1; 
				}
			}
			
			range = new Range(fact.getStringTable());
			range.setPathKey(actualColumbusCuPathKey);
			range.setLine(line);
			range.setCol(col);
			range.setEndLine(endLine);
			range.setEndCol(endCol);
			range.setWideLine(line);
			range.setWideCol(col);
			range.setWideEndLine(endLine);
			range.setWideEndCol(endCol);
		}
		
		return range;
	}


	private void setOtherPositions(JCTree jcTree, Positioned node) {
		Map<TokenKind, Set<Integer>> tokenPositions = actualJCCU.otherPositions.get(jcTree);
		if (tokenPositions != null) {
			for (Map.Entry<TokenKind, Set<Integer>> tokenPos : tokenPositions.entrySet()) {
				TokenKind token = tokenPos.getKey();
				Set<Integer> positions = tokenPos.getValue();
				int pos = Position.NOPOS;
				
				if (positions.size() == 2) {
					if (token == TokenKind.SEMI && Common.getIsBasicFor(node)) {
						Iterator<Integer> it = positions.iterator();
						int firstPos = it.next();
						int secondPos = it.next();
						((BasicFor)node).setFirstSemiPosition(getRangeFromOtherPosition(firstPos, token, null));
						((BasicFor)node).setSecondSemiPosition(getRangeFromOtherPosition(secondPos, token, null));
					}
					continue;
					
				} else if (positions.size() != 1) {
					// should not happen
					continue;
					
				} else {
					pos = positions.iterator().next();
				}
				
				Name name = null;
				if (jcTree instanceof JCClassDecl) {
					name = ((JCClassDecl)jcTree).name;
				} else if (jcTree instanceof JCMethodDecl) {
					name = ((JCMethodDecl)jcTree).name;
				} else if (jcTree instanceof JCVariableDecl) {
					name = ((JCVariableDecl)jcTree).name;
				} else if (jcTree instanceof JCTypeParameter) {
					name = ((JCTypeParameter)jcTree).name;
				} else if (jcTree instanceof JCBreak) {
					name = ((JCBreak)jcTree).label;
				} else if (jcTree instanceof JCContinue) {
					name = ((JCContinue)jcTree).label;
				}
				
				Range range = getRangeFromOtherPosition(pos, token, name);
				if (range == null) {
					// should not happen
					continue;
				}
				
				boolean warnNodeType = false;
				boolean warnUnhandledToken = false;
				switch (tokenPos.getKey()) {
					case PUBLIC:
					case PROTECTED:
					case PRIVATE:
						if (Common.getIsNamedDeclaration(node)) {
							((NamedDeclaration)node).setAccessibilityPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case ABSTRACT:
						if (Common.getIsTypeDeclaration(node)) {
							((TypeDeclaration)node).setAbstractPosition(range);
						} else if (Common.getIsMethodDeclaration(node)) {
							((MethodDeclaration)node).setAbstractPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case STATIC:
						if (Common.getIsImport(node)) {
							((Import)node).setStaticPosition(range);
						} else if (Common.getIsNamedDeclaration(node)) {
							((NamedDeclaration)node).setStaticPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case FINAL:
						if (Common.getIsNamedDeclaration(node)) {
							((NamedDeclaration)node).setFinalPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case TRANSIENT:
						if (Common.getIsVariable(node)) {
							((Variable)node).setTransientPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case VOLATILE:
						if (Common.getIsVariable(node)) {
							((Variable)node).setVolatilePosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case SYNCHRONIZED:
						if (Common.getIsNormalMethod(node)) {
							((NormalMethod)node).setSynchronizedPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case NATIVE:
						if (Common.getIsNormalMethod(node)) {
							((NormalMethod)node).setNativePosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case STRICTFP:
						if (Common.getIsMethodDeclaration(node)) {
							((MethodDeclaration)node).setStrictfpPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case IDENTIFIER:
					//case ASSERT:
					//case ENUM:
					// 'assert' and 'enum' can also be used as identifiers in old java versions
					// but they are also stored as IDENTIFIER
						if (Common.getIsNamed(node)) {
							((Named)node).setNamePosition(range);
						} else if (Common.getIsJump(node)) {
							((Jump)node).setLabelPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case ELLIPSIS:
						if (Common.getIsParameter(node)) {
							((Parameter)node).setVarargsPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case CLASS:
					case INTERFACE:
					case ENUM:
						if (Common.getIsTypeDeclaration(node)) {
							((TypeDeclaration)node).setTypeNamePosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case MONKEYS_AT:
						if (Common.getIsAnnotationType(node)) {
							((AnnotationType)node).setAtSignPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case ELSE:
						if (Common.getIsIf(node)) {
							((If)node).setElsePosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case WHILE:
						if (Common.getIsDo(node)) {
							((Do)node).setWhilePosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case FINALLY:
						if (Common.getIsTry(node)) {
							((Try)node).setFinallyPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case COLON:
						if (Common.getIsSwitchLabel(node)) {
							((SwitchLabel)node).setColonPosition(range);
						} else if (Common.getIsAssert(node)) {
							((Assert)node).setColonPosition(range);
						} else if (Common.getIsConditional(node)) {
							((Conditional)node).setColonPosition(range);
						} else if (Common.getIsLabeledStatement(node)) {
							((LabeledStatement)node).setColonPosition(range);
						} else if (Common.getIsEnhancedFor(node)) {
							((EnhancedFor)node).setColonPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case EXTENDS:
						if (Common.getIsTypeDeclaration(node)) {
							((TypeDeclaration)node).setExtendsPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case IMPLEMENTS:
						if (Common.getIsTypeDeclaration(node)) {
							((TypeDeclaration)node).setImplementsPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case THROWS:
						if (Common.getIsNormalMethod(node)) {
							((NormalMethod)node).setThrowsPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case DEFAULT:
						if (Common.getIsAnnotationTypeElement(node)) {
							((AnnotationTypeElement)node).setDefaultPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case LPAREN:
						if (Common.getIsMethodDeclaration(node)) {
							((MethodDeclaration)node).setParametersStartPosition(range);
						} else if (Common.getIsTry(node)) {
							((Try)node).setResourceLeftParenPosition(range);
						} else if (Common.getIsHandler(node)) {
							((Handler)node).setLeftParenPosition(range);
						} else if (Common.getIsFor(node)) {
							((For)node).setLeftParenPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case RPAREN:
						if (Common.getIsMethodDeclaration(node)) {
							((MethodDeclaration)node).setParametersEndPosition(range);
						} else if (Common.getIsTry(node)) {
							((Try)node).setResourceRightParenPosition(range);
						} else if (Common.getIsHandler(node)) {
							((Handler)node).setRightParenPosition(range);
						} else if (Common.getIsFor(node)) {
							((For)node).setRightParenPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case LBRACE:
						if (Common.getIsSwitch(node)) {
							((Switch)node).setBlockStartPosition(range);
						} else if (Common.getIsTypeDeclaration(node)) {
							((TypeDeclaration)node).setBodyStartPosition(range);
						} else if (Common.getIsStaticInitializerBlock(node)) {
							((StaticInitializerBlock)node).setBlockStartPosition(range);
						} else if (Common.getIsBlock(node)) {
							// nothing to do, position is stored for static init block
						} else if (Common.getIsNewArray(node)) {
							((NewArray)node).setLeftBracePosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case EQ:
						if (Common.getIsVariable(node)) {
							((Variable)node).setEqualSignPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					case SEMI:
						if (Common.getIsEnum(node)) {
							((Enum)node).setSemiPosition(range);
						} else {
							warnNodeType = true;
						}
						break;
					default:
						warnUnhandledToken = true;
						break;
				}

			}
		}
	}

}

enum MethodType {
	NORMAL, ANNOTATION_ELEMENT,
}

enum BlockType {
	NORMAL, INSTANCE_INIT, STATIC_INIT;
}

enum VarDeclType {
	NONE, VARIABLE, ENUMCONST, PARAMETER
}