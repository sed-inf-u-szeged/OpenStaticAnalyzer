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
 * Interface Variable, which represents the {@link columbus.java.asg.struc.Variable Variable} node.
 * @columbus.node (missing)
 * @columbus.attr isTransient (boolean) : (missing)
 * @columbus.attr transientPosition (Range) : (missing)
 * @columbus.attr isVolatile (boolean) : (missing)
 * @columbus.attr volatilePosition (Range) : (missing)
 * @columbus.attr equalSignPosition (Range) : (missing)
 * @columbus.edge hasInitialValue ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 */
public interface Variable extends VariableDeclaration {

	/**
	 * Gives back the {@link columbus.java.asg.struc.Variable#attributeIsTransient isTransient} of the node.
	 * @return Returns with the isTransient.
	 */
	public boolean getIsTransient();

	/**
	 * Sets the {@link columbus.java.asg.struc.Variable#attributeIsTransient isTransient} of the node.
	 * @param value The new value of the isTransient.
	 */
	public void setIsTransient(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.Variable#attributeTransientPosition transientPosition} of the node.
	 * @return Returns with the transientPosition.
	 */
	public Range getTransientPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.Variable#attributeTransientPosition transientPosition} of the node.
	 * @param value The new value of the transientPosition.
	 */
	public void setTransientPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.Variable#attributeIsVolatile isVolatile} of the node.
	 * @return Returns with the isVolatile.
	 */
	public boolean getIsVolatile();

	/**
	 * Sets the {@link columbus.java.asg.struc.Variable#attributeIsVolatile isVolatile} of the node.
	 * @param value The new value of the isVolatile.
	 */
	public void setIsVolatile(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.Variable#attributeVolatilePosition volatilePosition} of the node.
	 * @return Returns with the volatilePosition.
	 */
	public Range getVolatilePosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.Variable#attributeVolatilePosition volatilePosition} of the node.
	 * @param value The new value of the volatilePosition.
	 */
	public void setVolatilePosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.Variable#attributeEqualSignPosition equalSignPosition} of the node.
	 * @return Returns with the equalSignPosition.
	 */
	public Range getEqualSignPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.Variable#attributeEqualSignPosition equalSignPosition} of the node.
	 * @param value The new value of the equalSignPosition.
	 */
	public void setEqualSignPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.Variable#edgeHasInitialValue hasInitialValue} edge points to.
	 * @return Returns the end point of the hasInitialValue edge.
	 */
	public Expression getInitialValue();

	/**
	 * Sets the {@link columbus.java.asg.struc.Variable#edgeHasInitialValue hasInitialValue} edge.
	 * @param id The new end point of the hasInitialValue edge.
	 */
	public void setInitialValue(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.Variable#edgeHasInitialValue hasInitialValue} edge.
	 * @param node The new end point of the hasInitialValue edge.
	 */
	public void setInitialValue(Expression node);

}

