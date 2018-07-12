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
import columbus.java.asg.expr.Expression;

/**
 * Interface AnnotationTypeElement, which represents the {@link columbus.java.asg.struc.AnnotationTypeElement AnnotationTypeElement} node.
 * @columbus.node (missing)
 * @columbus.attr defaultPosition (Range) : (missing)
 * @columbus.edge hasDefaultValue ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 */
public interface AnnotationTypeElement extends MethodDeclaration {

	/**
	 * Gives back the {@link columbus.java.asg.struc.AnnotationTypeElement#attributeDefaultPosition defaultPosition} of the node.
	 * @return Returns with the defaultPosition.
	 */
	public Range getDefaultPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.AnnotationTypeElement#attributeDefaultPosition defaultPosition} of the node.
	 * @param value The new value of the defaultPosition.
	 */
	public void setDefaultPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.AnnotationTypeElement#edgeHasDefaultValue hasDefaultValue} edge points to.
	 * @return Returns the end point of the hasDefaultValue edge.
	 */
	public Expression getDefaultValue();

	/**
	 * Sets the {@link columbus.java.asg.struc.AnnotationTypeElement#edgeHasDefaultValue hasDefaultValue} edge.
	 * @param id The new end point of the hasDefaultValue edge.
	 */
	public void setDefaultValue(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.AnnotationTypeElement#edgeHasDefaultValue hasDefaultValue} edge.
	 * @param node The new end point of the hasDefaultValue edge.
	 */
	public void setDefaultValue(Expression node);

}

