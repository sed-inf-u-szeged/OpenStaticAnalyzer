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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.lang.model.type.TypeMirror;

import columbus.java.asg.Common;
import columbus.java.asg.Factory;
import columbus.java.asg.JavaException;
import columbus.java.asg.base.Base;
import columbus.java.asg.expr.Expression;
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.type.ArrayType;
import columbus.java.asg.type.BooleanType;
import columbus.java.asg.type.ByteType;
import columbus.java.asg.type.CharType;
import columbus.java.asg.type.DoubleType;
import columbus.java.asg.type.ErrorType;
import columbus.java.asg.type.FloatType;
import columbus.java.asg.type.IntType;
import columbus.java.asg.type.LongType;
import columbus.java.asg.type.MethodType;
import columbus.java.asg.type.NoType;
import columbus.java.asg.type.NullType;
import columbus.java.asg.type.PackageType;
import columbus.java.asg.type.ScopedType;
import columbus.java.asg.type.ShortType;
import columbus.java.asg.type.TypeVariable;
import columbus.java.asg.type.UnionType;
import columbus.java.asg.type.VoidType;
import columbus.java.asg.type.WildcardType;
import columbus.logger.LoggerHandler;

import com.sun.tools.javac.code.BoundKind;
import com.sun.tools.javac.code.Symbol;
import com.sun.tools.javac.code.Symbol.ClassSymbol;
import com.sun.tools.javac.code.Symbol.PackageSymbol;
import com.sun.tools.javac.code.Type;
import com.sun.tools.javac.code.Type.DelegatedType;
import com.sun.tools.javac.code.Type.UnknownType;

public class TypeBuilder {

	private static final LoggerHandler logger = new LoggerHandler(TypeBuilder.class,
			OptionParser.getLoggerPropertyFile());

	private Factory fact;
	private SymbolMaps symMaps;
	private Map<Symbol, Integer> classSymbolMap = new HashMap<>();
	private Map<Type, Integer> builtTypeSymbols = new HashMap<>();
	private Map<Integer, Integer> classAndPackageTypes = new HashMap<>();

	public TypeBuilder(Factory factory, SymbolMaps symMaps) {
		this.fact = factory;
		this.symMaps = symMaps;
		classSymbolMap.putAll(symMaps.getExternalTypeDeclarationMap());
		classSymbolMap.putAll(symMaps.getInnerTypeDeclarationMap());
	}

	public void build() {
		for (Map.Entry<Type, List<Integer>> entry : symMaps.getUsedTypesMap().entrySet()) {
			int typeId = visit(entry.getKey());
			if (typeId != 0) {
				for (Integer id : entry.getValue()) {
					Base b = fact.getRef(id);
					if (b instanceof Expression) {
						Expression expr = (Expression) b;
						columbus.java.asg.type.Type t = expr.getType();
						if (t == null) {
							expr.setType(typeId);
						} else if (t.getId() != typeId) {
							if (logger.isDebugEnabled()) {
								logger.debug("debug.jan.TypeBuilder.couldntSetExpTypeToAnother", id,
										expr.getNodeKind(), t.getId(), typeId);
							}
						}
					} else if (b instanceof MethodDeclaration) {
						MethodDeclaration m = (MethodDeclaration) b;
						m.setMethodType(typeId);
					} else {
						if (logger.isDebugEnabled()) {
							logger.debug("debug.jan.TypeBuilder.unexpectedNodeIdForType", id, b.getNodeKind(), typeId,
									fact.getNodeKind(typeId), entry.getKey());
						}
					}
				}
			} else {
				if (logger.isDebugEnabled()) {
					logger.debug("debug.jan.TypeBuilder.unknownType", entry.getKey());
				}
			}
		}

		// create ClassType node for each TypeDeclaration
		Factory.Iterator it = fact.iterator();
		while (it.hasNext()) {
			Base node = it.next();
			if (Common.getIsTypeDeclaration(node)) {
				createClassOrPackageType(node);
			}
		}
		classAndPackageTypes.clear();
	}

	private int createClassOrPackageType(Base node) {
		if (node == null) {
			return 0;
		}

		if (Common.getIsTypeDeclaration(node) || Common.getIsPackage(node)) {
			Integer type = classAndPackageTypes.get(node.getId());
			if (type != null) {
				return type;
			}
		}

		if (Common.getIsTypeDeclaration(node)) {
			int ownerTypeId = 0;
			if (node.getParent() != null) {
				ownerTypeId = createClassOrPackageType(node.getParent());
			}
			int typeId = fact.createClassType(ownerTypeId, node.getId()).getId();
			classAndPackageTypes.put(node.getId(), typeId);
			return typeId;

		} else if (Common.getIsPackage(node)) {
			int typeId = fact.createPackageType(node.getId()).getId();
			classAndPackageTypes.put(node.getId(), typeId);
			return typeId;

		} else {
			if (node.getParent() != null) {
				return createClassOrPackageType(node.getParent());
			}
		}

		return 0;
	}

	public static <RetType> RetType getValueFromTypeMap(Type type, Map<Type, RetType> map) {
		if (type == null) {
			return null;
		}

		return map.get(type);
	}

	private int visit(Type type) {
		int ret = 0;

		if (type == null)
			return 0;

		try {
			Integer typeId = getValueFromTypeMap(type, builtTypeSymbols);

			if (typeId != null) {
				ret = typeId;
			} else {
				switch (type.getKind()) {
				case INT: {
					IntType typeNode = fact.createIntType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case BOOLEAN: {
					BooleanType typeNode = fact.createBooleanType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case BYTE: {
					ByteType typeNode = fact.createByteType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case CHAR: {
					CharType typeNode = fact.createCharType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case DOUBLE: {
					DoubleType typeNode = fact.createDoubleType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case FLOAT: {
					FloatType typeNode = fact.createFloatType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case LONG: {
					LongType typeNode = fact.createLongType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case SHORT: {
					ShortType typeNode = fact.createShortType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case VOID: {
					VoidType typeNode = fact.createVoidType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case NULL: {
					NullType typeNode = fact.createNullType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case ARRAY: {
					String name = type.toString();
					int dim = (name.length() - name.indexOf('[')) / 2;
					int componentId = visit(((Type.ArrayType) type).elemtype);
					ArrayType typeNode = fact.createArrayType(dim, componentId);
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case ERROR: {
					ErrorType typeNode = fact.createErrorType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case PACKAGE: {
					int refersToId = 0;
					Integer ref = symMaps.getPackageMap().get(type.tsym);
					if (ref == null) {
						if (logger.isDebugEnabled()) {
							logger.debug("debug.jan.TypeBuilder.packageCouldntBeFound", type);
						}
					} else {
						refersToId = ref;
					}
					PackageType typeNode = fact.createPackageType(refersToId);
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case TYPEVAR: {
					if (type instanceof Type.CapturedType) {
						ret = visit(((Type.CapturedType) type).wildcard);
					} else {
						int refersToId = 0;
						Integer ref = symMaps.getTypeParameterMap().get(type);
						if (ref == null) {
							// if we reach this, than check the type parameters of the owner symbol
							// it should be a Symbol.MethodSymbol and its type should be Type.ForAll
							Type ownerType = type.tsym.owner.type;
							for (Type tv : ownerType.getTypeArguments()) {
								if (type.tsym.name.toString().equals(tv.tsym.name.toString())) {
									ref = symMaps.getTypeParameterMap().get(tv);
									break;
								}
							}
						}
						if (ref == null) {
							if (logger.isDebugEnabled()) {
								logger.debug("debug.jan.TypeBuilder.typeParamCouldntBeFound", type, type.tsym.owner);
							}
						} else {
							refersToId = ref;
						}
						TypeVariable typeNode = fact.createTypeVariable(refersToId);
						ret = typeNode.getId();
						builtTypeSymbols.put(type, ret);
					}
					break;
				}
				case UNION: {
					List<Integer> alternativeIds = new ArrayList<>();

					Type.UnionClassType t = (Type.UnionClassType) type;
					for (TypeMirror alt : t.getAlternatives()) {
						alternativeIds.add(visit((Type) alt));
					}

					UnionType typeNode = fact.createUnionType(alternativeIds);
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case WILDCARD: {
					com.sun.tools.javac.code.Type.WildcardType wildcardType = (com.sun.tools.javac.code.Type.WildcardType) type;
					WildcardType typeNode = null;
					int boundId = 0;

					if (wildcardType.kind == BoundKind.EXTENDS) {
						boundId = visit(wildcardType.getExtendsBound());
						typeNode = fact.createUpperBoundedWildcardType(boundId);
					} else if (wildcardType.kind == BoundKind.SUPER) {
						boundId = visit(wildcardType.getSuperBound());
						typeNode = fact.createLowerBoundedWildcardType(boundId);
					} else if (wildcardType.kind == BoundKind.UNBOUND) {
						boundId = visit(wildcardType.type);
						typeNode = fact.createUnboundedWildcardType(boundId);
					} else {
						throw new JavaException(logger.formatMessage("ex.jan.TypeBuilder.invalidWildcardType"));
					}
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case DECLARED: {
					ScopedType typeNode;

					int ownerId = 0;
					int refersToId = 0;
					List<Integer> argumentTypeIds = null;
					int rawTypeId = 0;

					if (type.getTypeArguments().isEmpty()) {
						for (Map.Entry<Symbol, Integer> entry : classSymbolMap.entrySet()) {
							if (type.tsym == entry.getKey().type.tsym) {
								refersToId = entry.getValue();
								break;
							}
						}
						if (refersToId == 0) {
							logger.debug("debug.jan.TypeBuilder.refIsntStored", type);
						}
					} else {
						Type erased = type.tsym.erasure_field;
						if (erased == null) {
							erased = new Type.ErasedClassType(type, type.tsym);
						}
						rawTypeId = visit(erased);

						argumentTypeIds = new ArrayList<>();
						for (Type type_arg : type.getTypeArguments()) {
							argumentTypeIds.add(visit(type_arg));
						}
					}

					Symbol sym = type.tsym.owner;
					while (!(sym instanceof ClassSymbol) && !(sym instanceof PackageSymbol)) {
						sym = sym.owner;
					}
					ownerId = visit(sym.type);

					if (type.getTypeArguments().isEmpty()) {
						typeNode = fact.createClassType(ownerId, refersToId);
					} else {
						typeNode = fact.createParameterizedType(ownerId, rawTypeId, argumentTypeIds);
					}
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case EXECUTABLE: {
					int returnTypeId = 0;
					List<Integer> parameterTypeIds = new ArrayList<>();
					List<Integer> thrownTypeIds = new ArrayList<>();

					returnTypeId = visit(type.getReturnType());
					for (Type t : type.getParameterTypes()) {
						parameterTypeIds.add(visit(t));
					}
					for (Type t : type.getThrownTypes()) {
						thrownTypeIds.add(visit(t));
					}

					MethodType typeNode = fact.createMethodType(returnTypeId, parameterTypeIds, thrownTypeIds);
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case NONE: {
					NoType typeNode = fact.createNoType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				case OTHER:
					if (logger.isDebugEnabled()) {
						logger.debug("debug.jan.TypeBuilder.otherType", type);
					}
					if (type instanceof DelegatedType) {
						DelegatedType delegated = ((DelegatedType) type);
						ret = visit(delegated.qtype);
					} else if (type instanceof UnknownType) {
						// TODO java 1.8
						// TODO Type.UnknownType e.g. <any?>
						logger.debug("ex.jan.TypeBuilder.errorTypeInsteadOfJava18Type", type.getKind());
						ErrorType typeNode = fact.createErrorType();
						ret = typeNode.getId();
						builtTypeSymbols.put(type, ret);
					} else {
						throw new JavaException(logger.formatMessage("ex.jan.TypeBuilder.unknownTypeKind", type.getKind()));
					}
					break;
				// TODO java 1.8
				case INTERSECTION: {
					logger.debug("ex.jan.TypeBuilder.errorTypeInsteadOfJava18Type", type.getKind());
					ErrorType typeNode = fact.createErrorType();
					ret = typeNode.getId();
					builtTypeSymbols.put(type, ret);
					break;
				}
				default:
					throw new JavaException(logger.formatMessage("ex.jan.TypeBuilder.unknownTypeKind", type.getKind()));
				}
			}
		} catch (NullPointerException e) {
			logger.error("error.jan.TypeBuilder.nodeTypeWasNull", e);
		} catch (Exception e) {
			logger.error("error.jan.TypeBuilder.couldntBuildTheType", type.getKind(), type, e);
		}

		return ret;
	}

}
