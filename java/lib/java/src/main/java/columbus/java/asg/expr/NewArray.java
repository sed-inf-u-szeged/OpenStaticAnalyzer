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
 * Interface NewArray, which represents the {@link columbus.java.asg.expr.NewArray NewArray} node.
 * @columbus.node (missing)
 * @columbus.attr leftBracePosition (Range) : (missing)
 * @columbus.edge hasComponentType ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 * @columbus.edge hasDimensions ({@link columbus.java.asg.expr.Expression Expression}, multiple) : (missing)
 * @columbus.edge hasInitializers ({@link columbus.java.asg.expr.Expression Expression}, multiple) : (missing)
 */
public interface NewArray extends Expression {

	/**
	 * Gives back the {@link columbus.java.asg.expr.NewArray#attributeLeftBracePosition leftBracePosition} of the node.
	 * @return Returns with the leftBracePosition.
	 */
	public Range getLeftBracePosition();

	/**
	 * Sets the {@link columbus.java.asg.expr.NewArray#attributeLeftBracePosition leftBracePosition} of the node.
	 * @param value The new value of the leftBracePosition.
	 */
	public void setLeftBracePosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.NewArray#edgeHasComponentType hasComponentType} edge points to.
	 * @return Returns the end point of the hasComponentType edge.
	 */
	public TypeExpression getComponentType();

	/**
	 * Sets the {@link columbus.java.asg.expr.NewArray#edgeHasComponentType hasComponentType} edge.
	 * @param id The new end point of the hasComponentType edge.
	 */
	public void setComponentType(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.NewArray#edgeHasComponentType hasComponentType} edge.
	 * @param node The new end point of the hasComponentType edge.
	 */
	public void setComponentType(TypeExpression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.NewArray#edgeHasDimensions hasDimensions} edges.
	 * @return Returns an iterator for the hasDimensions edges.
	 */
	public EdgeIterator<Expression> getDimensionsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.NewArray#edgeHasDimensions hasDimensions} edges or not.
	 * @return Returns true if the node doesn't have any hasDimensions edge.
	 */
	public boolean getDimensionsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.NewArray#edgeHasDimensions hasDimensions} edges the node has.
	 * @return Returns with the number of hasDimensions edges.
	 */
	public int getDimensionsSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewArray#edgeHasDimensions hasDimensions} edge to the node.
	 * @param id The end point of the new hasDimensions edge.
	 */
	public void addDimensions(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewArray#edgeHasDimensions hasDimensions} edge to the node.
	 * @param node The end point of the new hasDimensions edge.
	 */
	public void addDimensions(Expression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.NewArray#edgeHasInitializers hasInitializers} edges.
	 * @return Returns an iterator for the hasInitializers edges.
	 */
	public EdgeIterator<Expression> getInitializersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.NewArray#edgeHasInitializers hasInitializers} edges or not.
	 * @return Returns true if the node doesn't have any hasInitializers edge.
	 */
	public boolean getInitializersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.NewArray#edgeHasInitializers hasInitializers} edges the node has.
	 * @return Returns with the number of hasInitializers edges.
	 */
	public int getInitializersSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewArray#edgeHasInitializers hasInitializers} edge to the node.
	 * @param id The end point of the new hasInitializers edge.
	 */
	public void addInitializers(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewArray#edgeHasInitializers hasInitializers} edge to the node.
	 * @param node The end point of the new hasInitializers edge.
	 */
	public void addInitializers(Expression node);

}

