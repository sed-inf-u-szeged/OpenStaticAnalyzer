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

package columbus.java.asg.struc;

import columbus.java.asg.*;
import columbus.java.asg.base.Named;
import columbus.java.asg.enums.*;

/**
 * Interface NamedDeclaration, which represents the {@link columbus.java.asg.struc.NamedDeclaration NamedDeclaration} node.
 * @columbus.node (missing)
 * @columbus.attr accessibility ({@link columbus.java.asg.enums.AccessibilityKind AccessibilityKind}) : (missing)
 * @columbus.attr accessibilityPosition (Range) : (missing)
 * @columbus.attr isStatic (boolean) : (missing)
 * @columbus.attr staticPosition (Range) : (missing)
 * @columbus.attr isFinal (boolean) : (missing)
 * @columbus.attr finalPosition (Range) : (missing)
 */
public interface NamedDeclaration extends Declaration, Named {

	/**
	 * Gives back the {@link columbus.java.asg.struc.NamedDeclaration#attributeAccessibility accessibility} of the node.
	 * @return Returns with the accessibility.
	 */
	public AccessibilityKind getAccessibility();

	/**
	 * Sets the {@link columbus.java.asg.struc.NamedDeclaration#attributeAccessibility accessibility} of the node.
	 * @param value The new value of the accessibility.
	 */
	public void setAccessibility(AccessibilityKind value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NamedDeclaration#attributeAccessibilityPosition accessibilityPosition} of the node.
	 * @return Returns with the accessibilityPosition.
	 */
	public Range getAccessibilityPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.NamedDeclaration#attributeAccessibilityPosition accessibilityPosition} of the node.
	 * @param value The new value of the accessibilityPosition.
	 */
	public void setAccessibilityPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NamedDeclaration#attributeIsStatic isStatic} of the node.
	 * @return Returns with the isStatic.
	 */
	public boolean getIsStatic();

	/**
	 * Sets the {@link columbus.java.asg.struc.NamedDeclaration#attributeIsStatic isStatic} of the node.
	 * @param value The new value of the isStatic.
	 */
	public void setIsStatic(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NamedDeclaration#attributeStaticPosition staticPosition} of the node.
	 * @return Returns with the staticPosition.
	 */
	public Range getStaticPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.NamedDeclaration#attributeStaticPosition staticPosition} of the node.
	 * @param value The new value of the staticPosition.
	 */
	public void setStaticPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NamedDeclaration#attributeIsFinal isFinal} of the node.
	 * @return Returns with the isFinal.
	 */
	public boolean getIsFinal();

	/**
	 * Sets the {@link columbus.java.asg.struc.NamedDeclaration#attributeIsFinal isFinal} of the node.
	 * @param value The new value of the isFinal.
	 */
	public void setIsFinal(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NamedDeclaration#attributeFinalPosition finalPosition} of the node.
	 * @return Returns with the finalPosition.
	 */
	public Range getFinalPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.NamedDeclaration#attributeFinalPosition finalPosition} of the node.
	 * @param value The new value of the finalPosition.
	 */
	public void setFinalPosition(Range value);

}

