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

import java.util.EnumSet;

import columbus.java.asg.Common;
import columbus.java.asg.EdgeIterator;
import columbus.java.asg.enums.AccessibilityKind;
import columbus.java.asg.enums.MethodKind;
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.struc.NamedDeclaration;
import columbus.java.asg.struc.NormalMethod;
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.struc.TypeDeclaration;
import columbus.java.asg.struc.Variable;
import columbus.logger.LoggerHandler;

import com.sun.tools.javac.code.Flags;
import com.sun.tools.javac.code.Flags.Flag;

public abstract class JANFlags {

	private static final LoggerHandler logger = new LoggerHandler(JANFlags.class, OptionParser.getLoggerPropertyFile());

	public static boolean hasStaticFlag(long flags) {
		if ((flags & Flags.STATIC) != 0)
			return true;
		return false;
	}

	public static boolean hasEnumFlag(long flags) {
		if ((flags & Flags.ENUM) != 0)
			return true;
		return false;
	}

	public static boolean hasAnnotationFlag(long flags) {
		if ((flags & Flags.ANNOTATION) != 0)
			return true;
		return false;
	}

	public static boolean hasAnonconstrFlag(long flags) {
		if ((flags & Flags.ANONCONSTR) != 0)
			return true;
		return false;
	}

	public static boolean hasGeneratedConstrFlag(long flags) {
		if ((flags & Flags.GENERATEDCONSTR) != 0)
			return true;
		return false;
	}

	public static void setModifiers(long flags, NamedDeclaration memberNode) {
		EnumSet<Flag> flagSet = Flags.asFlagSet(flags, false);
		for (Flag f : flagSet) {
			switch (f) {
			case ABSTRACT:
				if (Common.getIsMethodDeclaration(memberNode)) {
					((MethodDeclaration) memberNode).setIsAbstract(true);
				} else if (Common.getIsTypeDeclaration(memberNode)) {
					((TypeDeclaration) memberNode).setIsAbstract(true);
				} else {
					// syntax error
				}
				break;
			case FINAL:
				memberNode.setIsFinal(true);
				break;
			case STATIC:
				memberNode.setIsStatic(true);
				break;
			case STRICTFP:
				if (Common.getIsMethodDeclaration(memberNode)) {
					((MethodDeclaration) memberNode).setIsStrictfp(true);
				} else if (Common.getIsTypeDeclaration(memberNode)) {
					((TypeDeclaration) memberNode).setIsStrictfp(true);
				} else {
					// syntax error
				}
				break;
			case PRIVATE:
				memberNode.setAccessibility(AccessibilityKind.ackPrivate);
				break;
			case PROTECTED:
				memberNode.setAccessibility(AccessibilityKind.ackProtected);
				break;
			case PUBLIC:
				memberNode.setAccessibility(AccessibilityKind.ackPublic);
				break;
			case TRANSIENT:
				if (Common.getIsVariableDeclaration(memberNode)) {
					((Variable) memberNode).setIsTransient(true);
				} else {
					// syntax error
				}
				break;
			case VOLATILE:
				if (Common.getIsVariableDeclaration(memberNode)) {
					((Variable) memberNode).setIsVolatile(true);
				} else {
					// syntax error
				}
				break;
			case VARARGS:
				if (Common.getIsParameter(memberNode)) {
					((Parameter) memberNode).setIsVarargs(true);
				} else if (Common.getIsNormalMethod(memberNode)) {
					// MethodSymbol's flag can be VARARGS
					NormalMethod method = (NormalMethod) memberNode;
					if (!method.getParametersIsEmpty()) {
						Parameter lastParam = null;
						for (EdgeIterator<Parameter> pit = method.getParametersIterator(); pit.hasNext();) {
							lastParam = pit.next();
						}
						lastParam.setIsVarargs(true);
					}
				} else {
					// syntax error
				}
				break;
			case GENERATEDCONSTR:
				if (Common.getIsNormalMethod(memberNode)) {
					((NormalMethod) memberNode).setMethodKind(MethodKind.mekGeneratedDefaultConstructor);
				} else {
					// syntax error
				}
				break;
			case SYNCHRONIZED:
				if (Common.getIsNormalMethod(memberNode)) {
					((NormalMethod) memberNode).setIsSynchronized(true);
				} else {
					// syntax error
				}
				break;
			case NATIVE:
				if (Common.getIsNormalMethod(memberNode)) {
					((NormalMethod) memberNode).setIsNative(true);
				} else {
					// syntax error
				}
				break;
			case ENUM:
			case PARAMETER:
			case INTERFACE:
			case ANNOTATION:
			case HASINIT:
			case DEPRECATED:
				// dont used here
				break;
			case ANONCONSTR:
				// handled later
				break;
			case ACYCLIC:
			case ACYCLIC_ANN:
			case EFFECTIVELY_FINAL:
			case BRIDGE:
			case CLASS_SEEN:
				// dont needed
				break;
			// TODO java 1.8 new flags
			case DEFAULT:
			case MANDATED:
			case AUXILIARY:
			case NOT_IN_PROFILE:
			case BAD_OVERRIDE:
			case SIGNATURE_POLYMORPHIC:
			case THROWS:
			case LAMBDA_METHOD:
			case TYPE_TRANSLATED:
				break;
			default:
				logger.warn("warn.jan.JANFlags.modifierIsntHandled", f);
			}
		}

		if (flagSet.contains(Flag.ANONCONSTR)) {
			((NormalMethod) memberNode).setMethodKind(MethodKind.mekGeneratedAnonymousClassConstructor);
		}

		if (flagSet.contains(Flag.DEFAULT) && Common.getIsMethodDeclaration(memberNode)) {
			// Default methods read from class file both have default and abstract modifiers.
			// But according to JLS 9.4 it mustn't happen:
			//   It is a compile-time error if a method is declared with more than one of the modifiers
			//   abstract, default, or static.
			((MethodDeclaration) memberNode).setIsAbstract(false);
		}
	}
}
