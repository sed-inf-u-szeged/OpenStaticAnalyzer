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

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import javax.lang.model.element.ElementKind;
import javax.lang.model.type.TypeKind;

import columbus.java.asg.Common;
import columbus.java.asg.Factory;
import columbus.java.asg.JavaException;
import columbus.java.asg.base.Base;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.enums.MethodKind;
import columbus.java.asg.enums.NodeKind;
import columbus.java.asg.expr.Annotation;
import columbus.java.asg.expr.Assignment;
import columbus.java.asg.expr.BooleanLiteral;
import columbus.java.asg.expr.CharacterLiteral;
import columbus.java.asg.expr.ClassLiteral;
import columbus.java.asg.expr.DoubleLiteral;
import columbus.java.asg.expr.Erroneous;
import columbus.java.asg.expr.ExternalTypeExpression;
import columbus.java.asg.expr.FloatLiteral;
import columbus.java.asg.expr.Identifier;
import columbus.java.asg.expr.IntegerLiteral;
import columbus.java.asg.expr.LongLiteral;
import columbus.java.asg.expr.MarkerAnnotation;
import columbus.java.asg.expr.NewArray;
import columbus.java.asg.expr.NormalAnnotation;
import columbus.java.asg.expr.StringLiteral;
import columbus.java.asg.struc.AnnotationType;
import columbus.java.asg.struc.AnnotationTypeElement;
import columbus.java.asg.struc.ClassGeneric;
import columbus.java.asg.struc.Enum;
import columbus.java.asg.struc.EnumConstant;
import columbus.java.asg.struc.Interface;
import columbus.java.asg.struc.InterfaceGeneric;
import columbus.java.asg.struc.Method;
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.struc.MethodGeneric;
import columbus.java.asg.struc.NamedDeclaration;
import columbus.java.asg.struc.NormalMethod;
import columbus.java.asg.struc.Package;
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.struc.TypeParameter;
import columbus.java.asg.struc.Variable;
import columbus.java.asg.struc.VariableDeclaration;
import columbus.logger.LoggerHandler;

import com.sun.tools.javac.code.Attribute;
import com.sun.tools.javac.code.Attribute.Compound;
import com.sun.tools.javac.code.Attribute.Constant;
import com.sun.tools.javac.code.Symbol;
import com.sun.tools.javac.code.Symbol.ClassSymbol;
import com.sun.tools.javac.code.Symbol.MethodSymbol;
import com.sun.tools.javac.code.Symbol.PackageSymbol;
import com.sun.tools.javac.code.Symbol.TypeSymbol;
import com.sun.tools.javac.code.Symbol.TypeVariableSymbol;
import com.sun.tools.javac.code.Symbol.VarSymbol;
import com.sun.tools.javac.code.Symtab;
import com.sun.tools.javac.code.Type;
import com.sun.tools.javac.code.Type.ClassType;
import com.sun.tools.javac.util.Context;
import com.sun.tools.javac.util.Names;
import com.sun.tools.javac.util.Pair;

public class ExternalClassBuilder {

	private static final LoggerHandler logger = new LoggerHandler(ExternalClassBuilder.class,
			OptionParser.getLoggerPropertyFile());

	private TreeBuilder builder;
	private Factory fact;
	private SymbolMaps symMaps;
	private Set<Symbol> symbolsToBuild = new LinkedHashSet<>();
	private Set<Symbol> symbolsToBuild2 = new LinkedHashSet<>();
	private boolean even = true;
	private boolean innerPart = false;
	private boolean buildExtFromSource = OptionParser.isBuildExtFromSource();

	private Set<Symbol> typeDeclarationSymbolSet = new LinkedHashSet<>();
	private Map<Symbol, Integer> nestedClassMap = new LinkedHashMap<>();
	private boolean oneMoreRoundNeeded = false;

	// to check if the TypeDeclaration is already built
	private Map<Symbol, TypeDeclaration> builtTypeDeclarations = new HashMap<>();
	private Set<Symbol> partlyBuiltTypeDeclarations = new HashSet<>();

	private Names names;
	private Symtab symtab;

	public ExternalClassBuilder(Factory factory, TreeBuilder builder, SymbolMaps symMaps, Context context) {
		this.names = Names.instance(context);
		this.symtab = Symtab.instance(context);
		this.fact = factory;
		this.builder = builder;
		this.symMaps = symMaps;
	}

	public void build() {
		typeDeclarationSymbolSet = symMaps.getExternalClassAndInterfaceSet();
		symMaps.clearInnerClassesFromFullBuildSet();

		boolean firstBuild = true;
		while (oneMoreRoundNeeded || firstBuild) {

			Set<Symbol> set = null;
			if (firstBuild) {
				logger.info("info.jan.ExternalClassBuilder.firstRound");
				set = typeDeclarationSymbolSet;
				firstBuild = false;
			} else {
				logger.info("info.jan.ExternalClassBuilder.nextRound");
				if (even) {
					set = symbolsToBuild;
					symbolsToBuild2.clear();
					even = !even;
				} else {
					set = symbolsToBuild2;
					symbolsToBuild.clear();
					even = !even;
				}
				typeDeclarationSymbolSet.addAll(set);
			}
			oneMoreRoundNeeded = false;

			for (Symbol sym : set) {
				if (sym.type != null && sym.type.getKind() == TypeKind.ERROR) {
					// should not happen
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.ExternalClassBuilder.symbolTypeIsError", sym);
					}
					continue;
				}

				if (sym == symtab.boundClass || sym == symtab.arrayClass || sym == symtab.methodClass || sym == symtab.unknownSymbol ||
						(sym.type != null && sym.type == symtab.botType)) {
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.ExternalClassBuilder.dontBuildBuiltinSymbol", sym.name);
					}
					continue;
				}

				if (typeDeclarationSymbolSet.contains(sym.owner) && symMaps.containsSymbolsToFullBuild(sym.owner)) {
					continue;
				}
				int id = 0;
				id = visitSymbol(sym);

				Base n = fact.getRef(id);
				if (n.getParent() == null) {
					if (sym.owner.getKind() == ElementKind.PACKAGE || sym.owner.getKind().isClass()
							|| sym.owner.getKind().isInterface()) {

						int parentId = createClassHierarchy(sym.owner);

						Base parentNode = fact.getRef(parentId);
						if (Common.getIsTypeDeclaration(parentNode)) {
							((TypeDeclaration) parentNode).addMembers(id);
						} else {
							((Package) parentNode).addMembers(id);
						}
					} else {
						fact.getRoot().addMembers(id);
					}
				}

			}
			buildExtFromSource = false;
		}

		// build the missing values and valueOf nodes from symbols
		innerPart = true;
		for (Entry<MethodSymbol, Integer> e : symMaps.getEnumFunctions().entrySet()) {
			int id = visitSymbol(e.getKey());
			Enum enumNode = (Enum) fact.getRef(e.getValue());
			enumNode.addMembers(id);
		}
		innerPart = false;
	}

	private int createClassHierarchy(Symbol sym) {
		int ret = 0;
		try {
			if (sym.getKind() == ElementKind.PACKAGE) {
				return builder.createAndAddPackages((PackageSymbol) sym);
			} else {
				if (nestedClassMap.containsKey(sym)) {
					ret = nestedClassMap.get(sym);
				} else {
					int actual = createClass((ClassSymbol) sym, symMaps.containsSymbolsToFullBuild(sym));
					TypeDeclaration td = (TypeDeclaration) fact.getRef(actual);
					if (td.getParent() != null)
						return actual;
					Base parentNode = fact.getRef(createClassHierarchy(sym.owner));
					if (Common.getIsTypeDeclaration(parentNode)) {
						((TypeDeclaration) parentNode).addMembers(actual);
					} else {
						((Package) parentNode).addMembers(actual);
					}
					nestedClassMap.put(sym, actual);
					ret = actual;
				}
			}
		} catch (Exception e) {
			logger.error("ex.jan.ExternalClassBuilder.errorCreatingOwnerOfTypeDecl", e);
		}

		return ret;
	}

	private int visitSymbol(Symbol sym) {
		NamedDeclaration member = null;
		try {
			if (sym == null) {
				throw new JavaException(logger.formatMessage("ex.jan.ExternalClassBuilder.symCantBeNull"));
			}

			boolean prevInnerPart = innerPart;

			if (sym instanceof ClassSymbol) {

				ClassSymbol classSym = (ClassSymbol) sym;
				boolean fullBuild = symMaps.containsSymbolsToFullBuild(sym);

				TypeDeclaration typeDeclNode = (TypeDeclaration) fact.getRef(createClass(classSym, fullBuild));
				if (typeDeclNode.getParent() != null)
					return typeDeclNode.getId();

				member = typeDeclNode;
			} else if (sym instanceof VarSymbol) {
				VarSymbol varSym = (VarSymbol) sym;

				if (sym.type instanceof Type.ArrayType) {
					Type t = ((Type.ArrayType) sym.type).elemtype;
					if (!t.isPrimitive()) {
						addToSymbolsToBuildSet(t.tsym);
					}
				}

				VariableDeclaration varDeclNode = null;
				switch (varSym.getKind()) {
				case PARAMETER:
					Parameter parameterNode = (Parameter) fact.createNode(NodeKind.ndkParameter);
					varDeclNode = parameterNode;
					addToSymbolsToBuildSet(sym.owner);
					break;
				case ENUM_CONSTANT:
					EnumConstant enumConstNode = (EnumConstant) fact.createNode(NodeKind.ndkEnumConstant);
					varDeclNode = enumConstNode;
					break;
				case FIELD:
					Variable variableNode = (Variable) fact.createNode(NodeKind.ndkVariable);
					varDeclNode = variableNode;
					addToSymbolsToBuildSet(sym.owner);
					break;

				case EXCEPTION_PARAMETER:
				case ENUM:
				case LOCAL_VARIABLE:
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.ExternalClassBuilder.unexpectedVarSym", varSym.getKind());
					}
					break;
				default:
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.ExternalClassBuilder.unknownVarSym");
					}
					break;
				}

				varDeclNode.setType(visitTypeExpression(varSym.type));

				symMaps.getVariableDeclarationMap().put(varSym, varDeclNode.getId());
				member = varDeclNode;
			} else if (sym instanceof MethodSymbol) {
				MethodSymbol methodSym = (MethodSymbol) sym;

				// for debug only, the condition should never be true
				if (methodSym.getKind() == ElementKind.STATIC_INIT) {
					return 0;
				}

				if (JANFlags.hasAnonconstrFlag(sym.flags()) || JANFlags.hasGeneratedConstrFlag(sym.flags())) {
					innerPart = true;
				}

				MethodDeclaration methodDecl = null;
				if (methodSym.getEnclosingElement() != null
						&& methodSym.getEnclosingElement().getKind() == ElementKind.ANNOTATION_TYPE) {
					AnnotationTypeElement annotTypeElem = (AnnotationTypeElement) fact
							.createNode(NodeKind.ndkAnnotationTypeElement);
					methodDecl = annotTypeElem;
				} else {
					NormalMethod methodNode = null;
					if (methodSym.getTypeParameters().size() != 0) {
						MethodGeneric methodGenericNode = (MethodGeneric) fact.createNode(NodeKind.ndkMethodGeneric);

						for (TypeSymbol typaram : methodSym.getTypeParameters()) {
							methodGenericNode.addTypeParameters(visitSymbol(typaram));
						}
						methodNode = methodGenericNode;
					} else {
						methodNode = (Method) fact.createNode(NodeKind.ndkMethod);
					}

					for (Type throwType : methodSym.getThrownTypes()) {
						methodNode.addThrownExceptions(visitTypeExpression(throwType));
					}

					for (VarSymbol param : methodSym.getParameters()) {
						methodNode.addParameters(visitSymbol(param));
					}

					methodDecl = methodNode;
				}
				symMaps.getMethodDeclarationMap().put(methodSym, methodDecl.getId());
				symMaps.addMethodType(methodSym.type, methodDecl.getId());

				if (methodSym.getKind() != ElementKind.CONSTRUCTOR) { // don't build return type for constructors
					if (methodSym.getReturnType() != null) {
						methodDecl.setReturnType(visitTypeExpression(methodSym.getReturnType()));
					}
				}

				member = methodDecl;
			} else if (sym instanceof TypeSymbol) {
				return visitType(sym.type);
			} else {
				if (logger.isDebugEnabled()) {
					logger.debug("debug.jan.ExternalClassBuilder.notHandledSymKind", sym.getKind());
				}
			}

			JANFlags.setModifiers(sym.flags(), member);

			if (sym.name == names.init) { // constructor
				member.setName(sym.owner.name.toString());
				NormalMethod meth = (NormalMethod) member;
				if (meth.getMethodKind() == MethodKind.mekNormal) {
					meth.setMethodKind(MethodKind.mekConstructor);
				}
			} else {
				member.setName(sym.name.toString());
			}

			for (Compound c : sym.getAnnotationMirrors()) {
				member.addAnnotations(visitCompound(c));
			}

			if (innerPart) {
				member.setIsCompilerGenerated(true);
			}
			innerPart = prevInnerPart;
		} catch (Exception e) {
			logger.error("error.jan.ExternalClassBuilder.errorVisitingSym", e);
		}

		return member.getId();
	}

	private int visitClassTypeParameter(Type t) {

		TypeParameter typeParameterNode = (TypeParameter) fact.createNode(NodeKind.ndkTypeParameter);
		try {
			typeParameterNode.addBounds(visitTypeExpression(t));
			typeParameterNode.setName(t.toString());

			Integer oldvalue = symMaps.getTypeParameterMap().put(t, typeParameterNode.getId());
			if (oldvalue != null) {
				// System.out.println("TypeParam " + t + " already added, old " + oldvalue + " new " +
				// typeParameterNode.getId());
			}

			if (innerPart) {
				typeParameterNode.setIsCompilerGenerated(true);
			}
		} catch (Exception e) {
			logger.error("error.jan.ExternalClassBuilder.errorVisitingTypeParam", e);
		}

		return typeParameterNode.getId();
	}

	private int createClass(ClassSymbol classSym, boolean fullBuild) {
		TypeDeclaration typeDeclNode = null;
		try {
			TypeDeclaration td = builtTypeDeclarations.get(classSym);

			if (td != null) {
				// if have to build fully a partly built class, we fill the missing parts
				if (partlyBuiltTypeDeclarations.remove(classSym) && fullBuild) {
					if (logger.isInfoEnabled()) {
						logger.info("info.jan.ExternalClassBuilder.fillExtTypeDecl", classSym.toString());
					}

					Type superClassType = classSym.getSuperclass();
					if (superClassType != null && superClassType.getKind() != TypeKind.NONE) {
						addToSymbolsToBuildSet(superClassType.tsym);
					}

					for (Type type : classSym.getInterfaces()) {
						addToSymbolsToBuildSet(type.tsym);
					}

					buildInnerPartsOfTypeDeclarations(classSym, td);
				}
				return td.getId();
			}

			if (logger.isInfoEnabled()) {
				logger.info("info.jan.ExternalClassBuilder.buildingExtTypeDecl", classSym.toString());
			}

			switch (classSym.getKind()) {
			case CLASS:
				if (classSym.type.getTypeArguments().size() == 0) {
					typeDeclNode = (TypeDeclaration) fact.createNode(NodeKind.ndkClass);
				} else {
					ClassGeneric classGenericNode = (ClassGeneric) fact.createNode(NodeKind.ndkClassGeneric);
					for (Type t : classSym.type.getTypeArguments()) {
						if (t.getKind() != TypeKind.TYPEVAR) {
							classGenericNode.addTypeParameters(visitClassTypeParameter(t));
						} else {
							classGenericNode.addTypeParameters(visitType(t));
						}
					}
					typeDeclNode = classGenericNode;
				}
				break;
			case INTERFACE:
				if (classSym.type.getTypeArguments().size() == 0) {
					typeDeclNode = (Interface) fact.createNode(NodeKind.ndkInterface);
				} else {
					InterfaceGeneric interfaceGenericNode = (InterfaceGeneric) fact
							.createNode(NodeKind.ndkInterfaceGeneric);

					for (Type t : classSym.type.getTypeArguments()) {
						if (t.getKind() != TypeKind.TYPEVAR) {
							interfaceGenericNode.addTypeParameters(visitClassTypeParameter(t));
						} else {
							interfaceGenericNode.addTypeParameters(visitType(t));
						}
					}
					typeDeclNode = interfaceGenericNode;
				}
				break;
			case ANNOTATION_TYPE:
				AnnotationType annotTypeNode = (AnnotationType) fact.createNode(NodeKind.ndkAnnotationType);
				typeDeclNode = annotTypeNode;
				break;
			case ENUM:
				Enum enumNode = (Enum) fact.createNode(NodeKind.ndkEnum);
				typeDeclNode = enumNode;
				break;
			default:
				throw new JavaException(logger.formatMessage("ex.jan.ExternalClassBuilder.incorrectClassSymKind"));
			}

			builtTypeDeclarations.put(classSym, typeDeclNode);

			typeDeclNode.setBinaryName(classSym.flatname.toString());
			typeDeclNode.setName(classSym.name.toString());

			symMaps.getExternalTypeDeclarationMap().put(classSym, typeDeclNode.getId());

			Type superClassType = classSym.getSuperclass();
			if (superClassType != null && superClassType.getKind() != TypeKind.NONE) {
				typeDeclNode.setSuperClass(visitTypeExpression(superClassType));
				addToSymbolsToBuildSet(superClassType.tsym);
			}

			for (Type type : classSym.getInterfaces()) {
				typeDeclNode.addSuperInterfaces(visitTypeExpression(type));
				addToSymbolsToBuildSet(type.tsym);
			}

			if (buildExtFromSource || OptionParser.isBuildAllExternal() || fullBuild) {
				// if we fully build an external class, we need to fully build all it's parents for override edges
				buildInnerPartsOfTypeDeclarations(classSym, typeDeclNode);
			} else {
				partlyBuiltTypeDeclarations.add(classSym);
			}
		} catch (Exception e) {
			logger.error("error.jan.ExternalClassBuilder.errorCreatingClass", e);
		}
		return typeDeclNode.getId();
	}

	private void buildInnerPartsOfTypeDeclarations(ClassSymbol classSym, TypeDeclaration typeDeclNode) {

		if (OptionParser.buildAllParentForOverrides) {
			symMaps.addAllParentToFullBuild(classSym);
		}

		for (Symbol m : classSym.getEnclosedElements()) {
			// symbols does not contains useful informations of static init blocks, so we skip them
			if (m.getKind() == ElementKind.STATIC_INIT) {
				continue;
			}
			typeDeclNode.addMembers(visitSymbol(m));
		}
	}

	private int visitCompound(Compound c) {
		Annotation annotationNode = null;
		try {
			switch (c.getElementValues().size()) {
			case 0:
				annotationNode = (MarkerAnnotation) fact.createNode(NodeKind.ndkMarkerAnnotation);
				break;
			case 1:
			default:
				NormalAnnotation normalAnnotationNode = (NormalAnnotation) fact
						.createNode(NodeKind.ndkNormalAnnotation);

				for (Pair<MethodSymbol, Attribute> value : c.values) {
					MethodSymbol methodSym = value.fst;
					Identifier identifierNode = (Identifier) fact.createNode(NodeKind.ndkIdentifier);
					symMaps.addNodeType(methodSym.type, identifierNode.getId());

					identifierNode.setName(methodSym.name.toString());
					symMaps.addToIdMap(identifierNode.getId(), methodSym);

					addToSymbolsToBuildSet(methodSym.owner);
					symMaps.addClassAndInterfaceToFullBuildSet(methodSym.owner);

					Assignment assignmentNode = (Assignment) fact.createNode(NodeKind.ndkAssignment);
					symMaps.addNodeType(methodSym.type, assignmentNode.getId());
					assignmentNode.setLeftOperand(identifierNode);

					int snd_id = createAnnotationElementValue(value.snd.getValue(), value.snd.type);
					assignmentNode.setRightOperand(snd_id);
					symMaps.addNodeType(value.snd.type, snd_id);

					normalAnnotationNode.addArguments(assignmentNode);
				}

				annotationNode = normalAnnotationNode;
				break;
			}
			if (c.type != null) {
				symMaps.addNodeType(c.type, annotationNode.getId());
				annotationNode.setAnnotationName(visitTypeExpression(c.type));
			}
			if (innerPart) {
				annotationNode.setIsCompilerGenerated(true);
			}
		} catch (Exception e) {
			logger.error("error.jan.ExternalClassBuilder.errorVisitingAnnot", e);
		}
		return annotationNode.getId();
	}

	private int createAnnotationElementValue(Object value, Type type) {
		int ret = 0;
		try {
			if (value instanceof String) {
				StringLiteral l = (StringLiteral) fact.createNode(NodeKind.ndkStringLiteral);
				l.setValue(value.toString());
				ret = l.getId();
			} else if (value instanceof Boolean) {
				BooleanLiteral l = (BooleanLiteral) fact.createNode(NodeKind.ndkBooleanLiteral);
				l.setBooleanValue((boolean) value);
				ret = l.getId();
			} else if (value instanceof Character) {
				CharacterLiteral l = (CharacterLiteral) fact.createNode(NodeKind.ndkCharacterLiteral);
				l.setCharValue((char) value);
				ret = l.getId();
			} else if (value instanceof Integer) {
				IntegerLiteral l = (IntegerLiteral) fact.createNode(NodeKind.ndkIntegerLiteral);
				l.setIntValue((int) value);
				l.setValue(value.toString());
				ret = l.getId();
			} else if (value instanceof Long) {
				LongLiteral l = (LongLiteral) fact.createNode(NodeKind.ndkLongLiteral);
				l.setLongValue(((long) value));
				l.setValue(value.toString());
				ret = l.getId();
			} else if (value instanceof Float) {
				FloatLiteral l = (FloatLiteral) fact.createNode(NodeKind.ndkFloatLiteral);
				l.setFloatValue(((float) value));
				l.setValue(value.toString());
				ret = l.getId();
			} else if (value instanceof Double) {
				DoubleLiteral l = (DoubleLiteral) fact.createNode(NodeKind.ndkDoubleLiteral);
				l.setDoubleValue(((double) value));
				l.setValue(value.toString());
				ret = l.getId();
			} else if (value instanceof Compound) {
				ret = visitCompound((Compound) value);
			} else if (value instanceof ClassType) {
				ClassLiteral l = (ClassLiteral) fact.createNode(NodeKind.ndkClassLiteral);
				l.setComponentType(visitTypeExpression(((ClassType) value).tsym.type));
				ret = l.getId();
			} else if (value instanceof List) {
				List<?> list = (List<?>) value;
				if (list.size() == 0) {
					ret = fact.createNode(NodeKind.ndkNewArray).getId();
				} else if (list.size() == 1) {
					ret = createAnnotationElementValue(list.get(0), type);
				} else if (list.size() > 1) {
					NewArray newArrayNode = (NewArray) fact.createNode(NodeKind.ndkNewArray);
					ret = newArrayNode.getId();
					for (Object o : list) {
						int init_id = createAnnotationElementValue(o, type);
						newArrayNode.addInitializers(init_id);
						symMaps.addNodeType(type, init_id);
					}
				} else {
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.ExternalClassBuilder.unexpectedListSize", list.size());
					}
				}
			} else if (value instanceof Constant) {
				Constant c = (Constant) value;
				ret = createAnnotationElementValue(c.value, type);
			} else if (value instanceof Attribute.Enum) {
				Attribute.Enum aEnum = (com.sun.tools.javac.code.Attribute.Enum) value;

				Identifier rightId = (Identifier) fact.createNode(NodeKind.ndkIdentifier);

				rightId.setName(aEnum.value.name.toString());
				ret = rightId.getId();
				symMaps.addToIdMap(rightId.getId(), aEnum.value);

				addToSymbolsToBuildSet(aEnum.value.owner);
				symMaps.addClassAndInterfaceToFullBuildSet(aEnum.value.owner);

			} else if (value instanceof Attribute.Class) {
				Attribute.Class aClass = (Attribute.Class) value;

				ClassLiteral l = (ClassLiteral) fact.createNode(NodeKind.ndkClassLiteral);
				l.setComponentType(visitTypeExpression(aClass.classType));
				ret = l.getId();

			} else if (value instanceof VarSymbol) {
				VarSymbol sym = (VarSymbol) value;

				Identifier identifierNode = (Identifier) fact.createNode(NodeKind.ndkIdentifier);

				ret = identifierNode.getId();
				identifierNode.setName(sym.name.toString());
				symMaps.addToIdMap(identifierNode.getId(), sym);

				addToSymbolsToBuildSet(sym.owner);
				symMaps.addClassAndInterfaceToFullBuildSet(sym.owner);

			} else {
				Erroneous err = (Erroneous) fact.createNode(NodeKind.ndkErroneous);
				ret = err.getId();
				if (logger.isDebugEnabled()) {
					logger.debug("debug.jan.ExternalClassBuilder.notHandledAnnotElemValue", value.getClass(),
							value.toString());
				}
			}
			if (innerPart) {
				((Positioned) fact.getRef(ret)).setIsCompilerGenerated(true);
			}
		} catch (Exception e) {
			logger.error("error.jan.ExternalClassBuilder.errorCreatingAnnotElem", e);
		}
		return ret;
	}

	private void addToSymbolsToBuildSet(Symbol sym) {
		if (sym == null || sym.type == null || sym.type.getKind() == TypeKind.ERROR) {
			return;
		}

		// we will build a typedeclaration in the next round if its not an inner class or its just partly builded
		if ((!typeDeclarationSymbolSet.contains(sym) || partlyBuiltTypeDeclarations.contains(sym))
				&& !symMaps.getInnerTypeDeclarationMap().containsKey(sym)
				&& (sym.getKind().isInterface() || sym.getKind().isClass())) {
			// we dont build type declaration for the primitives, or NULL, VOID, NONE symbol
			if (!sym.type.isPrimitive() && sym.type.getKind() != TypeKind.VOID && sym.type.getKind() != TypeKind.NULL
					&& sym.type.getKind() != javax.lang.model.type.TypeKind.NONE) {
				if (even) {
					symbolsToBuild.add(sym);
				} else {
					symbolsToBuild2.add(sym);
				}
				oneMoreRoundNeeded = true;
			}
		}
	}

	private int visitType(Type type) {
		int ret = 0;
		try {
			if (type == null) {
				throw new JavaException(logger.formatMessage("ex.jan.ExternalClassBuilder.typeCantBeNull"));
			}

			switch (type.getKind()) {
			case TYPEVAR:
				TypeParameter typeParamNode = (TypeParameter) fact.createNode(NodeKind.ndkTypeParameter);
				typeParamNode.setName(type.toString());
				if (type.tsym != null && type.tsym instanceof TypeVariableSymbol) {
					for (Type t : ((TypeVariableSymbol)type.tsym).getBounds()) {
						typeParamNode.addBounds(visitTypeExpression(t));
					}
				}

				Integer oldvalue = symMaps.getTypeParameterMap().put(type, typeParamNode.getId());
				if (oldvalue != null) {
					// System.out.println("TypeParam " + type + " already added, old " + oldvalue + " new " +
					// typeParamNode.getId());
				}

				ret = typeParamNode.getId();
				break;
			case DECLARED:
				ret = visitTypeExpression(type);
				break;
			case VOID:
				ret = visitTypeExpression(type);
				break;
			case INT:
				ret = visitTypeExpression(type);
				break;
			case NONE:
			default:
				if (logger.isDebugEnabled()) {
					logger.debug("debug.jan.ExternalClassBuilder.notHandledType", type.getKind(), type);
				}
				break;
			}

			if (innerPart) {
				((Positioned) fact.getRef(ret)).setIsCompilerGenerated(true);
			}
		} catch (Exception e) {
			logger.error("error.jan.ExternalClassBuilder.errorVisitingType", e);
		}
		return ret;
	}

	private int visitTypeExpression(Type type) {
		ExternalTypeExpression externalTypeExprNode = (ExternalTypeExpression) fact
				.createNode(NodeKind.ndkExternalTypeExpression);
		try {
			if (type == null) {
				throw new JavaException(logger.formatMessage("ex.jan.ExternalClassBuilder.typeCantBeNull"));
			}

			// building the stored class types of arrays, for example: java.lang.Object[]
			if (type.getKind() == TypeKind.ARRAY) {
				addToSymbolsToBuildSet(((Type.ArrayType) type).elemtype.tsym);
			}

			if (!type.getTypeArguments().isEmpty() && type.getTypeArguments() != type.tsym.type.getTypeArguments()) {
				for (Type t : type.getTypeArguments()) {
					if (t.getKind() == TypeKind.WILDCARD) {
						Type.WildcardType wt = (Type.WildcardType) t;
						if (wt.getExtendsBound() != null)
							addToSymbolsToBuildSet(wt.getExtendsBound().tsym);
						if (wt.getSuperBound() != null)
							addToSymbolsToBuildSet(wt.getSuperBound().tsym);
					}
					addToSymbolsToBuildSet(t.tsym);
				}
			}

			addToSymbolsToBuildSet(type.tsym);

			symMaps.addNodeType(type, externalTypeExprNode.getId());

			if (innerPart) {
				externalTypeExprNode.setIsCompilerGenerated(true);
			}
		} catch (Exception e) {
			logger.error("error.jan.ExternalClassBuilder.errorVisitinTypeExpr", e);
		}
		return externalTypeExprNode.getId();
	}

}
