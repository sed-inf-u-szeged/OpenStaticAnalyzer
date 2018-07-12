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

package columbus.java.asg.expr;

import columbus.java.asg.*;

/**
 * Interface Conditional, which represents the {@link columbus.java.asg.expr.Conditional Conditional} node.
 * @columbus.node (missing)
 * @columbus.attr colonPosition (Range) : (missing)
 * @columbus.edge hasCondition ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasTrueExpression ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasFalseExpression ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 */
public interface Conditional extends Expression {

	/**
	 * Gives back the {@link columbus.java.asg.expr.Conditional#attributeColonPosition colonPosition} of the node.
	 * @return Returns with the colonPosition.
	 */
	public Range getColonPosition();

	/**
	 * Sets the {@link columbus.java.asg.expr.Conditional#attributeColonPosition colonPosition} of the node.
	 * @param value The new value of the colonPosition.
	 */
	public void setColonPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.Conditional#edgeHasCondition hasCondition} edge points to.
	 * @return Returns the end point of the hasCondition edge.
	 */
	public Expression getCondition();

	/**
	 * Sets the {@link columbus.java.asg.expr.Conditional#edgeHasCondition hasCondition} edge.
	 * @param id The new end point of the hasCondition edge.
	 */
	public void setCondition(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.Conditional#edgeHasCondition hasCondition} edge.
	 * @param node The new end point of the hasCondition edge.
	 */
	public void setCondition(Expression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.Conditional#edgeHasTrueExpression hasTrueExpression} edge points to.
	 * @return Returns the end point of the hasTrueExpression edge.
	 */
	public Expression getTrueExpression();

	/**
	 * Sets the {@link columbus.java.asg.expr.Conditional#edgeHasTrueExpression hasTrueExpression} edge.
	 * @param id The new end point of the hasTrueExpression edge.
	 */
	public void setTrueExpression(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.Conditional#edgeHasTrueExpression hasTrueExpression} edge.
	 * @param node The new end point of the hasTrueExpression edge.
	 */
	public void setTrueExpression(Expression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.Conditional#edgeHasFalseExpression hasFalseExpression} edge points to.
	 * @return Returns the end point of the hasFalseExpression edge.
	 */
	public Expression getFalseExpression();

	/**
	 * Sets the {@link columbus.java.asg.expr.Conditional#edgeHasFalseExpression hasFalseExpression} edge.
	 * @param id The new end point of the hasFalseExpression edge.
	 */
	public void setFalseExpression(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.Conditional#edgeHasFalseExpression hasFalseExpression} edge.
	 * @param node The new end point of the hasFalseExpression edge.
	 */
	public void setFalseExpression(Expression node);

}

