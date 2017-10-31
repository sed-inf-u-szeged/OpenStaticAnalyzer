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

package org.jan;

import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Map.Entry;

import javax.lang.model.type.TypeKind;

import org.jan.SymbolMaps.EdgeType;

import columbus.java.asg.Common;
import columbus.java.asg.Factory;
import columbus.java.asg.algorithms.AlgorithmPreorder;
import columbus.java.asg.base.Base;
import columbus.java.asg.enums.NodeKind;
import columbus.java.asg.expr.Identifier;
import columbus.java.asg.expr.MethodInvocation;
import columbus.java.asg.expr.NewClass;
import columbus.java.asg.statm.Break;
import columbus.java.asg.statm.Continue;
import columbus.java.asg.statm.Jump;
import columbus.java.asg.statm.LabeledStatement;
import columbus.java.asg.statm.Statement;
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

import com.sun.tools.javac.code.Kinds;
import com.sun.tools.javac.code.Symbol;
import com.sun.tools.javac.code.Symbol.ClassSymbol;
import com.sun.tools.javac.code.Symbol.MethodSymbol;
import com.sun.tools.javac.code.Type;
import com.sun.tools.javac.code.Types;
import com.sun.tools.javac.util.Context;

public class CrossEdges {

	private static final LoggerHandler logger = new LoggerHandler(CrossEdges.class,
			OptionParser.getLoggerPropertyFile());

	private Factory fact;
	private SymbolMaps symMaps;
	private Types types;

	public CrossEdges(Factory fact, SymbolMaps symMaps, Context context) {
		this.fact = fact;
		this.symMaps = symMaps;
		types = Types.instance(context);
	}

	public void setCrossEdges() {
		logger.debug("debug.jan.CrossEdges.setMethodInvsTarget");
		connectEdges(symMaps.getMethodDeclarationMap(), symMaps.getMethodInvMap(), EdgeType.METHOD);

		logger.debug("debug.jan.CrossEdges.setNewClassConstr");
		connectEdges(symMaps.getMethodDeclarationMap(), symMaps.getNewClassConstructorMap(), EdgeType.NEWCLASS);

		logger.debug("debug.jan.CrossEdges.setIdsTarget");
		Map<Symbol, Integer> idTargetMap = new LinkedHashMap<>(symMaps.getVariableDeclarationMap());
		idTargetMap.putAll(symMaps.getInnerTypeDeclarationMap());
		idTargetMap.putAll(symMaps.getExternalTypeDeclarationMap());
		idTargetMap.putAll(symMaps.getMethodDeclarationMap());
		idTargetMap.putAll(symMaps.getPackageMap());

		Map<Integer, Symbol> idRefMap = new LinkedHashMap<>();
		Iterator<Entry<Integer, Symbol>> iter = symMaps.getIdMapIterator();
		while (iter.hasNext()) {
			Entry<Integer, Symbol> entry = iter.next();
			idRefMap.put(entry.getKey(), entry.getValue());
		}

		connectEdges(idTargetMap, idRefMap, EdgeType.ID);

		logger.debug("debug.jan.CrossEdges.setJumpsTarget");
		connectJumps();

		logger.debug("debug.jan.CrossEdges.setOverrideEdges");
		connectOverrides();
	}

	private void connectOverrides() {
		for (Entry<Symbol, Integer> method : symMaps.getMethodDeclarationMap().entrySet()) {
			MethodSymbol methodSym = (MethodSymbol) method.getKey();
			ClassSymbol ownerClass = (ClassSymbol) methodSym.owner;

			if (logger.isDebugEnabled()) {
				logger.debug("debug.jan.CrossEdges.methodInfo", ownerClass.toString(), methodSym.toString());
			}
			HashSet<ClassSymbol> visitedInterfaces = new HashSet<ClassSymbol>();
			visitOverrideSuperClasses(methodSym, method.getValue(), ownerClass, visitedInterfaces);
		}
	}

	private void visitOverrideSuperClasses(MethodSymbol methodSym, Integer id, ClassSymbol classSym,
			HashSet<ClassSymbol> visitedInterfaces) {
		boolean foundClassOverride = false;
		boolean foundInterfaceOverride;
		while (!foundClassOverride && classSym != null) {
			// super classes
			if (!foundClassOverride) {
				foundClassOverride = checkMethodOverrides(methodSym, id, (ClassSymbol) classSym.getSuperclass().tsym);
			}
			// super interfaces
			Iterator<Type> it = classSym.getInterfaces().iterator();

			while (it.hasNext()) {
				ClassSymbol interfaceSym = (ClassSymbol) it.next().tsym;
				if (!visitedInterfaces.add(interfaceSym)) {
					continue;
				}

				foundInterfaceOverride = checkMethodOverrides(methodSym, id, interfaceSym);
				if (!foundInterfaceOverride) {
					visitOverrideSuperClasses(methodSym, id, interfaceSym, visitedInterfaces);
				}
			}
			classSym = (ClassSymbol) classSym.getSuperclass().tsym;
		}
	}

	private boolean checkMethodOverrides(MethodSymbol methodSym, Integer id, ClassSymbol classSym) {
		// superclass of interface
		if (classSym == null) {
			return false;
		}

		for (Symbol enclosed : classSym.getEnclosedElements()) {
			if (enclosed.kind == Kinds.MTH && methodSym.name.toString().equals(enclosed.name.toString())) {
				if (methodSym.overrides(enclosed, classSym, types, true)) {

					MethodDeclaration methodDeclaration = (MethodDeclaration) fact.getRef(id);
					Integer overridedMethodId = symMaps.getMethodDeclarationMap().get(enclosed);
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.CrossEdges.setOverrideEdge", classSym.toString(), enclosed.toString());
					}
					// for example the method is not built when we don't need to fully build an external class
					if (overridedMethodId != null) {
						methodDeclaration.addOverrides(overridedMethodId);
					} else if (OptionParser.buildAllParentForOverrides) {
						if (logger.isDebugEnabled()) {
							logger.debug("debug.jan.CrossEdges.overridenMethodNotBuilded", methodSym.owner.toString(),
									classSym.toString(), enclosed.toString());
						}
					}

					return true;
				}
			}
		}
		return false;
	}

	private void connectEdges(Map<Symbol, Integer> declarationMap, Map<Integer, Symbol> referenceMap, EdgeType e) {

		for (Entry<Integer, Symbol> refEntry : referenceMap.entrySet()) {
			try {
				Symbol refSym = refEntry.getValue();
				Integer refId = refEntry.getKey();

				if (refSym == null || refId == 0) {
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.CrossEdges.refSymError", refSym, refId);
					}
					continue;
				}
				Integer declId = declarationMap.get(refSym);
				Symbol declSym = refSym;
				if (declId == null) {
					tryToConnectByName(declarationMap, refSym, refId, e);
					continue;
				}

				switch (e) {
				case METHOD:
					try {
						MethodInvocation methodInvocationNode = (MethodInvocation) fact.getRef(refId);
						methodInvocationNode.setInvokes(declarationMap.get(declSym));
						break;
					} catch (Exception ex) {
						logger.error("error.jan.CrossEdges.errorInCrossEdges", ex);
					}
				case NEWCLASS:
					NewClass newClassNode = (NewClass) fact.getRef(refId);
					newClassNode.setConstructor(declId);
					break;
				case ID:
					Base base = fact.getRef(refId);
					if (base.getNodeKind() == NodeKind.ndkIdentifier) {
						((Identifier) base).setRefersTo(declId);
					}
					break;
				default:
					logger.error("error.jan.CrossEdges.notHandledCrossEdgeType");
					break;
				}
			} catch (Exception ex) {
				logger.error("error.jan.CrossEdges.errorInCrossEdges", ex);
			}
		}
	}

	private void tryToConnectByName(Map<Symbol, Integer> declarationMap, Symbol refSym, Integer refId, EdgeType e) {
		Symbol decl = null;

		decl = visitSuperClassesForConnectByName(declarationMap, refSym, refSym.owner);

		if (decl == null) {
			if (logger.isDebugEnabled()) {
				logger.debug("debug.jan.CrossEdges.cantFindTheEndOfCrossedge", refId);
			}
			return;
		}
		Integer id = declarationMap.get(decl);

		if (id == null){
			// cant connect the crossedge
			return;
		}

		switch (e) {
		case METHOD:
			MethodInvocation methodInvocationNode = (MethodInvocation) fact.getRef(refId);
			methodInvocationNode.setInvokes(id);
			break;
		case NEWCLASS:
			NewClass newClassNode = (NewClass) fact.getRef(refId);
			newClassNode.setConstructor(id);
			break;
		case ID:
			Base base = fact.getRef(refId);
			if (base == null) {
				return;
			}
			if (base.getNodeKind() == NodeKind.ndkIdentifier) {
				((Identifier) base).setRefersTo(id);
			}
			break;
		default:
			logger.error("error.jan.CrossEdges.notHandledCrossEdgeType");
			break;
		}
	}

	public Symbol visitSuperClassesForConnectByName(Map<Symbol, Integer> declarationMap, Symbol refSym, Symbol parent) {

		Symbol decl = null;

		if (parent != null && parent.type.getKind() == TypeKind.DECLARED) {
			decl = tryConnectParentByName(declarationMap, refSym, parent);

			if (decl == null) {
				for (Type t : ((ClassSymbol) parent).getInterfaces()) {
					decl = tryConnectParentByName(declarationMap, refSym, t.tsym);
					if (decl != null) {
						break;
					} else {
						decl = visitSuperClassesForConnectByName(declarationMap, refSym, t.tsym);
					}
				}
			}

			if (decl == null) {
				decl = visitSuperClassesForConnectByName(declarationMap, refSym,
						((ClassSymbol) parent).getSuperclass().tsym);
			}
		}

		return decl;
	}

	public Symbol tryConnectParentByName(Map<Symbol, Integer> declarationMap, Symbol refSym, Symbol parent) {

		if (parent.type.getKind() == TypeKind.NONE) {
			if (logger.isDebugEnabled()) {
				logger.debug("debug.jan.CrossEdges.wrongTypeOfSymbol", parent.type);
			}
			return null;
		}

		Symbol decl = null;

		for (Symbol s : parent.getEnclosedElements()) {
			if (s.getQualifiedName().equals(refSym.getQualifiedName())) {
				decl = s;
			}
		}

		return decl;
	}

	private void connectJumps() {
		AlgorithmPreorder algPre = new AlgorithmPreorder();
		Visitor vis = new Visitor() {

			@Override
			public void visit(Break node, boolean callVirtualBase) {
				super.visit(node, callVirtualBase);
				connectToLoop((Jump) node);
			}

			@Override
			public void visit(Continue node, boolean callVirtualBase) {
				connectToLoop((Jump) node);
				super.visit(node, callVirtualBase);
			}

			private void connectToLoop(Jump jump) {
				Base parent = jump.getParent();

				while (true) {
					if (parent == null) {
						break;
					}

					if (jump.getLabelKey() != 0) {
						if (Common.getIsLabeledStatement(parent)) {
							LabeledStatement labeled = (LabeledStatement) parent;
							if (labeled.getLabelKey() == jump.getLabelKey()) {
								jump.setTarget(labeled);
								break;
							}
						}
					} else {
						if (Common.getIsIteration(parent) || Common.getIsSwitch(parent)) {
							jump.setTarget((Statement) parent);
							break;
						}
					}
					parent = parent.getParent();
				}
			}
		};
		algPre.run(fact, vis);
	}
}
