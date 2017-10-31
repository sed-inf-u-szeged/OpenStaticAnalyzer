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

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import com.sun.tools.javac.util.Context;
import com.sun.tools.javac.util.Names;

import columbus.java.asg.Common;
import columbus.java.asg.Factory;
import columbus.java.asg.Range;
import columbus.java.asg.base.Base;
import columbus.java.asg.base.Named;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.enums.MethodKind;
import columbus.java.asg.expr.Expression;
import columbus.java.asg.expr.FieldAccess;
import columbus.java.asg.expr.Identifier;
import columbus.java.asg.expr.MethodInvocation;
import columbus.java.asg.expr.NewClass;
import columbus.java.asg.statm.Jump;
import columbus.java.asg.struc.Import;
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.struc.NormalMethod;
import columbus.java.asg.struc.PackageDeclaration;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.struc.TypeParameter;
import columbus.java.asg.type.ArrayType;
import columbus.java.asg.type.ClassType;
import columbus.java.asg.type.MethodType;
import columbus.java.asg.type.PackageType;
import columbus.java.asg.type.ParameterizedType;
import columbus.java.asg.type.ScopedType;
import columbus.java.asg.type.TypeVariable;
import columbus.java.asg.type.UnionType;
import columbus.java.asg.type.WildcardType;
import columbus.java.asg.visitors.VisitorAbstractNodes;
import columbus.logger.LoggerHandler;

public class Checker extends VisitorAbstractNodes {

	private static final LoggerHandler logger = new LoggerHandler(Checker.class, OptionParser.getLoggerPropertyFile());

	private Factory fact;

	private boolean checkDuplicatedTypeDeclarations = true;
	private Map<Integer, Set<Integer>> typeDeclarations = new HashMap<>();

	private Names names;

	public Checker(Factory fact, Context context) {
		this.fact = fact;
		this.names = Names.instance(context);
	}

	@Override
	public void finishVisit() {
		if (checkDuplicatedTypeDeclarations) {
			for (Entry<Integer, Set<Integer>> e : typeDeclarations.entrySet()) {
				Set<Integer> tds = e.getValue();
				if (tds.size() > 1) {
					logger.warn("warn.jan.Checker.duplicatedTypeDecl", fact.getStringTable().get(e.getKey()),
							tds.size());
					for (int td : tds) {
						logger.warn("warn.jan.Checker.printTypeDecl", getNodeInfo(fact.getRef(td)));
					}
				}
			}
		}
	}

	private static String getNodeInfo(Base node) {
		String str = "id" + node.getId() + " kind: " + node.getNodeKind();
		if (node instanceof Positioned) {
			Range p = ((Positioned) node).getPosition();
			str += ": " + p.getPath() + ": " + p.getLine() + ": " + p.getCol() + ": ";
		}
		if (node instanceof Named) {
			str += ": " + ((Named) node).getName();
		}
		return str;
	}

	@Override
	public void visit(Base node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getParent() == null && node != fact.getRoot() && !Common.getIsType(node) && !Common.getIsComment(node)) {
			logger.warn("warn.jan.Checker.missingParent", getNodeInfo(node));
		}
	}

	@Override
	public void visit(Named node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getNameKey() == 0) {
			if (!Common.getIsAnonymousClass(node)
					&& !(Common.getIsMethodDeclaration(node) && ((NormalMethod) node).getMethodKind() == MethodKind.mekGeneratedAnonymousClassConstructor)) {
				logger.warn("warn.jan.Checker.missingName", getNodeInfo(node));
			}
		}
	}

	@Override
	public void visit(columbus.java.asg.struc.Package node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getQualifiedNameKey() == 0) {
			logger.warn("warn.jan.Checker.missingQualifiedName", getNodeInfo(node));
		}
	}

	@Override
	public void visit(PackageDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getRefersTo() == null) {
			logger.warn("warn.jan.Checker.missingRefersTo", getNodeInfo(node));
		}
	}

	@Override
	public void visit(TypeDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		Range range = node.getPosition();
		if (range.getPathKey() != 0) {
			if (node.getIsInCompilationUnit() == null) {
				logger.warn("warn.jan.Checker.missingIsCompUnit", getNodeInfo(node));
			}
		}
		if (checkDuplicatedTypeDeclarations) {
			int binaryNameKey = node.getBinaryNameKey();
			Set<Integer> tds = typeDeclarations.get(binaryNameKey);
			if (tds == null) {
				tds = new HashSet<Integer>();
				typeDeclarations.put(binaryNameKey, tds);
			}
			tds.add(node.getId());
		}
	}

	@Override
	public void visit(TypeParameter node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getBoundsIsEmpty()) {
			logger.warn("warn.jan.Checker.missingBound", getNodeInfo(node));
		}
	}

	@Override
	public void visit(Positioned node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);

		Base parent = node.getParent();
		if (parent != null) {
			if (Common.getIsPositioned(parent)) {
				if (!node.getIsCompilerGenerated() && ((Positioned) parent).getIsCompilerGenerated()) {
					if (Common.getIsNewClass(parent) && Common.getIsEnumConstant(parent.getParent())) {
						// A("asdf) -> = new <enum name>("asdf")
						// here the StringLiteral is not compiler generated but the NewClass is
					} else {
						logger.warn("warn.jan.Checker.nonCompGenNodeHasCompGenParent", getNodeInfo(node),
								getNodeInfo(parent));
					}
				}
			}
		}

		if (node.getIsCompilerGenerated() || node.getPosition().getPathKey() == 0)
			return;

		Range range = node.getPosition();
		if (range.getLine() == 0 || range.getCol() == 0 || range.getEndLine() == 0 || range.getEndCol() == 0
				|| range.getWideLine() == 0 || range.getWideCol() == 0 || range.getWideEndLine() == 0
				|| range.getWideEndCol() == 0) {
			logger.warn("warn.jan.Checker.missingPos", getNodeInfo(node));
		}
	}

	@Override
	public void visit(NewClass node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getConstructor() == null) {
			logger.warn("warn.jan.Checker.missingConstructor", getNodeInfo(node));
		}
	}

	@Override
	public void visit(Jump node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getTarget() == null) {
			logger.warn("warn.jan.Checker.missingTarget", getNodeInfo(node));
		}
	}

	@Override
	public void visit(Identifier node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		boolean dontWarn = true;
		if (node.getRefersTo() == null) {
			if ((node.getParent().getParent() instanceof Import)) {
				dontWarn = true;
			}
		}
		if (node.getName().toString().equals(names.length.toString())
				|| node.getName().toString().equals(names.clone.toString())) {
			dontWarn = true;
		}

		if (!dontWarn) {
			logger.warn("warn.jan.Checker.missingRefersTo", getNodeInfo(node));
		}
	}

	@Override
	public void visit(MethodInvocation node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getInvokes() == null) {
			Expression op = node.getOperand();
			if (Common.getIsFieldAccess(op)){
				FieldAccess fa = (FieldAccess) op;
				if (!((Identifier) fa.getRightOperand()).getName().equals(names.clone.toString())){
					logger.warn("warn.jan.Checker.missingInvokes", getNodeInfo(node));	
				}
			}
		}
	}

	@Override
	public void visit(Expression node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getType() == null) {
			// import with *
			if (!(node instanceof FieldAccess && node.getParent() instanceof Import)
					&& !(node instanceof Identifier && node.getParent().getParent() instanceof Import)) {
				logger.warn("warn.jan.Checker.missingType", getNodeInfo(node));
			}
		}
	}

	@Override
	public void visit(MethodDeclaration node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getMethodType() == null) {
			logger.warn("warn.jan.Checker.missingType", getNodeInfo(node));
		}
	}

	// Types with edges

	@Override
	public void visit(WildcardType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getBound() == null) {
			logger.warn("warn.jan.Checker.missingBound", getNodeInfo(node));
		}
	}

	@Override
	public void visit(ScopedType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getOwner() == null) {
			logger.warn("warn.jan.Checker.missingOwner", getNodeInfo(node));
		}
	}

	@Override
	public void visit(ClassType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getRefersTo() == null) {
			logger.warn("warn.jan.Checker.missingRefersTo", getNodeInfo(node));
		}
	}

	@Override
	public void visit(ParameterizedType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getRawType() == null) {
			logger.warn("warn.jan.Checker.missingRawType", getNodeInfo(node));
		}
		if (node.getArgumentTypesIsEmpty()) {
			logger.warn("warn.jan.Checker.missingArgType", getNodeInfo(node));
		}
	}

	@Override
	public void visit(PackageType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getRefersTo() == null) {
			logger.warn("warn.jan.Checker.missingRefersTo", getNodeInfo(node));
		}
	}

	@Override
	public void visit(ArrayType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getSize() == 0) {
			logger.warn("warn.jan.Checker.sizeIsZero", getNodeInfo(node));
		}
		if (node.getComponentType() == null) {
			logger.warn("warn.jan.Checker.missingCompType", getNodeInfo(node));
		}
	}

	@Override
	public void visit(TypeVariable node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getRefersTo() == null) {
			logger.warn("warn.jan.Checker.missingRefersTo", getNodeInfo(node));
		}
	}

	@Override
	public void visit(MethodType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getReturnType() == null) {
			logger.warn("warn.jan.Checker.missingRetType", getNodeInfo(node));
		}
	}

	@Override
	public void visit(UnionType node, boolean callVirtualBase) {
		super.visit(node, callVirtualBase);
		if (node.getAlternativesIsEmpty()) {
			logger.warn("warn.jan.Checker.missingAlternative", getNodeInfo(node));
		}
	}

}
