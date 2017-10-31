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

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import javax.lang.model.type.TypeKind;

import columbus.logger.LoggerHandler;

import com.sun.tools.javac.code.Symbol;
import com.sun.tools.javac.code.Symbol.ClassSymbol;
import com.sun.tools.javac.code.Symbol.MethodSymbol;
import com.sun.tools.javac.code.Symbol.PackageSymbol;
import com.sun.tools.javac.code.Symbol.VarSymbol;
import com.sun.tools.javac.code.Type;

public class SymbolMaps {

	private static final LoggerHandler logger = new LoggerHandler(SymbolMaps.class,
			OptionParser.getLoggerPropertyFile());

	// declarations
	private Map<Symbol, Integer> methodDeclarationMap = new LinkedHashMap<>();
	private Map<Symbol, Integer> packageMap = new LinkedHashMap<>();
	private Map<Symbol, Integer> externalTypeDeclarationMap = new LinkedHashMap<>();
	private Map<Symbol, Integer> innerTypeDeclarationMap = new LinkedHashMap<>();
	private Map<Symbol, Integer> variableDeclarationMap = new LinkedHashMap<>();

	// types
	private Map<Type, List<Integer>> usedTypesMap = new LinkedHashMap<>();
	private Map<Type, Integer> typeParameterMap = new LinkedHashMap<>();

	// references
	private Map<Integer, Symbol> idMap = new LinkedHashMap<>();
	private Map<Integer, Symbol> methodInvMap = new LinkedHashMap<>();
	private Map<Integer, Symbol> newClassConstructorMap = new LinkedHashMap<>();

	private Set<Symbol> symbolsToFullBuild = new LinkedHashSet<>();
	private Set<Symbol> memberSet = new LinkedHashSet<>();
	private Set<Symbol> retTypeSet = new LinkedHashSet<>();
	private Set<Symbol> varTypeSet = new LinkedHashSet<>();
	private Set<Symbol> classAndInterfaceUsageSet = new LinkedHashSet<>();
	private Map<MethodSymbol, Integer> enumFunctionMap = new LinkedHashMap<>();

	public Map<Type, List<Integer>> getUsedTypesMap() {
		return usedTypesMap;
	}

	public Map<Symbol, Integer> getVariableDeclarationMap() {
		return variableDeclarationMap;
	}

	public Map<Integer, Symbol> getNewClassConstructorMap() {
		return newClassConstructorMap;
	}

	public Map<Symbol, Integer> getExternalTypeDeclarationMap() {
		return externalTypeDeclarationMap;
	}

	public Map<Symbol, Integer> getPackageMap() {
		return packageMap;
	}

	public Set<Symbol> getExternalClassAndInterfaceSet() {
		Set<Symbol> set = new LinkedHashSet<Symbol>(classAndInterfaceUsageSet);
		set.addAll(memberSet);
		set.addAll(retTypeSet);
		set.addAll(varTypeSet);

		set.removeAll(innerTypeDeclarationMap.keySet());

		Iterator<Symbol> it = set.iterator();
		while (it.hasNext()) {
			if (it.next().type.getKind() == TypeKind.ERROR) {
				it.remove();
			}
		}

		return set;
	}

	public Map<Type, Integer> getTypeParameterMap() {
		return typeParameterMap;
	}

	public Map<Symbol, Integer> getMethodDeclarationMap() {
		return methodDeclarationMap;
	}

	public Map<Integer, Symbol> getMethodInvMap() {
		return methodInvMap;
	}

	public Map<Symbol, Integer> getInnerTypeDeclarationMap() {
		return innerTypeDeclarationMap;
	}

	public void addNodeType(Type type, int id) {
		List<Integer> ids = null;

		ids = TypeBuilder.getValueFromTypeMap(type, usedTypesMap);

		if (ids == null) {
			ids = new LinkedList<>();
			usedTypesMap.put(type, ids);
		}

		ids.add(new Integer(id));
	}

	public Iterator<Entry<Integer, Symbol>> getIdMapIterator() {
		return idMap.entrySet().iterator();
	}

	public void addToIdMap(Integer id, Symbol sym) {
		if (sym instanceof ClassSymbol || sym instanceof VarSymbol || sym instanceof MethodSymbol
				|| sym instanceof PackageSymbol) {
			idMap.put(id, sym);
		} else {
			if (logger.isDebugEnabled()) {
				logger.debug("debug.jan.SymbolMaps.notExpectedIdType", sym.getKind());
			}
		}
	}

	public void addVarType(Symbol sym) {
		if (sym != null && sym.type != null && !sym.type.isPrimitive() && sym.type.getKind() != TypeKind.ARRAY) {
			if ((sym.type.tsym instanceof ClassSymbol) && !sym.type.tsym.isAnonymous()) {
				varTypeSet.add(sym.type.tsym);
			}
		}
	}

	public void addMethodReturnType(Symbol sym) {
		if (sym != null && sym.type != null && !sym.type.isPrimitive()) {
			if ((sym instanceof ClassSymbol) && !sym.isAnonymous()) {
				retTypeSet.add(sym);
			}
		}
	}

	public void addClassAndInterfaceUsageSet(Symbol sym) {
		if (sym != null) {
			if (sym instanceof ClassSymbol) {
				classAndInterfaceUsageSet.add(sym);
			}
		}
	}

	public void addMemberToTypeSymbolSet(Symbol sym) {
		if (sym != null) {
			if ((sym instanceof ClassSymbol) && !sym.isAnonymous()) {
				memberSet.add(sym);
			}
		}
	}

	public void addClassAndInterfaceToFullBuildSet(Symbol sym) {
		if (sym != null) {
			if (sym instanceof ClassSymbol) {
				symbolsToFullBuild.add(sym);
			}
		}
	}

	public void addAllParentToFullBuild(ClassSymbol sym) {
		if (sym != null) {
			Type parent = sym.getSuperclass();

			if (parent.tsym != null) {
				addClassAndInterfaceToFullBuildSet(parent.tsym);
				addAllParentToFullBuild((ClassSymbol) parent.tsym);
			}
			for (Type interf : sym.getInterfaces()) {
				addClassAndInterfaceToFullBuildSet(interf.tsym);
				addAllParentToFullBuild((ClassSymbol) interf.tsym);
			}
		}
	}

	public void clearInnerClassesFromFullBuildSet() {
		symbolsToFullBuild.removeAll(innerTypeDeclarationMap.keySet());
	}

	public boolean containsSymbolsToFullBuild(Symbol sym) {
		return symbolsToFullBuild.contains(sym);
	}

	public Map<MethodSymbol, Integer> getEnumFunctions() {
		return enumFunctionMap;
	}

	enum EdgeType {
		METHOD, NEWCLASS, ID
	}

}
