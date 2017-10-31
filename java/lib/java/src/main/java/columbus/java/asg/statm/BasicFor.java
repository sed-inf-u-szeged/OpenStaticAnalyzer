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

package columbus.java.asg.statm;

import columbus.java.asg.*;
import columbus.java.asg.expr.Expression;

/**
 * Interface BasicFor, which represents the {@link columbus.java.asg.statm.BasicFor BasicFor} node.
 * @columbus.node (missing)
 * @columbus.attr firstSemiPosition (Range) : (missing)
 * @columbus.attr secondSemiPosition (Range) : (missing)
 * @columbus.edge hasInitializers ({@link columbus.java.asg.statm.Statement Statement}, multiple) : (missing)
 * @columbus.edge hasCondition ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasUpdates ({@link columbus.java.asg.statm.Statement Statement}, multiple) : (missing)
 */
public interface BasicFor extends For {

	/**
	 * Gives back the {@link columbus.java.asg.statm.BasicFor#attributeFirstSemiPosition firstSemiPosition} of the node.
	 * @return Returns with the firstSemiPosition.
	 */
	public Range getFirstSemiPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.BasicFor#attributeFirstSemiPosition firstSemiPosition} of the node.
	 * @param value The new value of the firstSemiPosition.
	 */
	public void setFirstSemiPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.statm.BasicFor#attributeSecondSemiPosition secondSemiPosition} of the node.
	 * @return Returns with the secondSemiPosition.
	 */
	public Range getSecondSemiPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.BasicFor#attributeSecondSemiPosition secondSemiPosition} of the node.
	 * @param value The new value of the secondSemiPosition.
	 */
	public void setSecondSemiPosition(Range value);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.statm.BasicFor#edgeHasInitializers hasInitializers} edges.
	 * @return Returns an iterator for the hasInitializers edges.
	 */
	public EdgeIterator<Statement> getInitializersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.statm.BasicFor#edgeHasInitializers hasInitializers} edges or not.
	 * @return Returns true if the node doesn't have any hasInitializers edge.
	 */
	public boolean getInitializersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.statm.BasicFor#edgeHasInitializers hasInitializers} edges the node has.
	 * @return Returns with the number of hasInitializers edges.
	 */
	public int getInitializersSize();

	/**
	 * Adds a new {@link columbus.java.asg.statm.BasicFor#edgeHasInitializers hasInitializers} edge to the node.
	 * @param id The end point of the new hasInitializers edge.
	 */
	public void addInitializers(int id);

	/**
	 * Adds a new {@link columbus.java.asg.statm.BasicFor#edgeHasInitializers hasInitializers} edge to the node.
	 * @param node The end point of the new hasInitializers edge.
	 */
	public void addInitializers(Statement node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.BasicFor#edgeHasCondition hasCondition} edge points to.
	 * @return Returns the end point of the hasCondition edge.
	 */
	public Expression getCondition();

	/**
	 * Sets the {@link columbus.java.asg.statm.BasicFor#edgeHasCondition hasCondition} edge.
	 * @param id The new end point of the hasCondition edge.
	 */
	public void setCondition(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.BasicFor#edgeHasCondition hasCondition} edge.
	 * @param node The new end point of the hasCondition edge.
	 */
	public void setCondition(Expression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.statm.BasicFor#edgeHasUpdates hasUpdates} edges.
	 * @return Returns an iterator for the hasUpdates edges.
	 */
	public EdgeIterator<Statement> getUpdatesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.statm.BasicFor#edgeHasUpdates hasUpdates} edges or not.
	 * @return Returns true if the node doesn't have any hasUpdates edge.
	 */
	public boolean getUpdatesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.statm.BasicFor#edgeHasUpdates hasUpdates} edges the node has.
	 * @return Returns with the number of hasUpdates edges.
	 */
	public int getUpdatesSize();

	/**
	 * Adds a new {@link columbus.java.asg.statm.BasicFor#edgeHasUpdates hasUpdates} edge to the node.
	 * @param id The end point of the new hasUpdates edge.
	 */
	public void addUpdates(int id);

	/**
	 * Adds a new {@link columbus.java.asg.statm.BasicFor#edgeHasUpdates hasUpdates} edge to the node.
	 * @param node The end point of the new hasUpdates edge.
	 */
	public void addUpdates(Statement node);

}

