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
import columbus.java.asg.struc.Variable;

/**
 * Interface Try, which represents the {@link columbus.java.asg.statm.Try Try} node.
 * @columbus.node (missing)
 * @columbus.attr resourceLeftParenPosition (Range) : (missing)
 * @columbus.attr resourceRightParenPosition (Range) : (missing)
 * @columbus.attr finallyPosition (Range) : (missing)
 * @columbus.edge hasResources ({@link columbus.java.asg.struc.Variable Variable}, multiple) : (missing)
 * @columbus.edge hasBlock ({@link columbus.java.asg.statm.Block Block}, single) : (missing)
 * @columbus.edge hasHandlers ({@link columbus.java.asg.statm.Handler Handler}, multiple) : (missing)
 * @columbus.edge hasFinallyBlock ({@link columbus.java.asg.statm.Block Block}, single) : (missing)
 */
public interface Try extends Statement {

	/**
	 * Gives back the {@link columbus.java.asg.statm.Try#attributeResourceLeftParenPosition resourceLeftParenPosition} of the node.
	 * @return Returns with the resourceLeftParenPosition.
	 */
	public Range getResourceLeftParenPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Try#attributeResourceLeftParenPosition resourceLeftParenPosition} of the node.
	 * @param value The new value of the resourceLeftParenPosition.
	 */
	public void setResourceLeftParenPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.statm.Try#attributeResourceRightParenPosition resourceRightParenPosition} of the node.
	 * @return Returns with the resourceRightParenPosition.
	 */
	public Range getResourceRightParenPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Try#attributeResourceRightParenPosition resourceRightParenPosition} of the node.
	 * @param value The new value of the resourceRightParenPosition.
	 */
	public void setResourceRightParenPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.statm.Try#attributeFinallyPosition finallyPosition} of the node.
	 * @return Returns with the finallyPosition.
	 */
	public Range getFinallyPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Try#attributeFinallyPosition finallyPosition} of the node.
	 * @param value The new value of the finallyPosition.
	 */
	public void setFinallyPosition(Range value);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.statm.Try#edgeHasResources hasResources} edges.
	 * @return Returns an iterator for the hasResources edges.
	 */
	public EdgeIterator<Variable> getResourcesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.statm.Try#edgeHasResources hasResources} edges or not.
	 * @return Returns true if the node doesn't have any hasResources edge.
	 */
	public boolean getResourcesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.statm.Try#edgeHasResources hasResources} edges the node has.
	 * @return Returns with the number of hasResources edges.
	 */
	public int getResourcesSize();

	/**
	 * Adds a new {@link columbus.java.asg.statm.Try#edgeHasResources hasResources} edge to the node.
	 * @param id The end point of the new hasResources edge.
	 */
	public void addResources(int id);

	/**
	 * Adds a new {@link columbus.java.asg.statm.Try#edgeHasResources hasResources} edge to the node.
	 * @param node The end point of the new hasResources edge.
	 */
	public void addResources(Variable node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Try#edgeHasBlock hasBlock} edge points to.
	 * @return Returns the end point of the hasBlock edge.
	 */
	public Block getBlock();

	/**
	 * Sets the {@link columbus.java.asg.statm.Try#edgeHasBlock hasBlock} edge.
	 * @param id The new end point of the hasBlock edge.
	 */
	public void setBlock(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Try#edgeHasBlock hasBlock} edge.
	 * @param node The new end point of the hasBlock edge.
	 */
	public void setBlock(Block node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.statm.Try#edgeHasHandlers hasHandlers} edges.
	 * @return Returns an iterator for the hasHandlers edges.
	 */
	public EdgeIterator<Handler> getHandlersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.statm.Try#edgeHasHandlers hasHandlers} edges or not.
	 * @return Returns true if the node doesn't have any hasHandlers edge.
	 */
	public boolean getHandlersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.statm.Try#edgeHasHandlers hasHandlers} edges the node has.
	 * @return Returns with the number of hasHandlers edges.
	 */
	public int getHandlersSize();

	/**
	 * Adds a new {@link columbus.java.asg.statm.Try#edgeHasHandlers hasHandlers} edge to the node.
	 * @param id The end point of the new hasHandlers edge.
	 */
	public void addHandlers(int id);

	/**
	 * Adds a new {@link columbus.java.asg.statm.Try#edgeHasHandlers hasHandlers} edge to the node.
	 * @param node The end point of the new hasHandlers edge.
	 */
	public void addHandlers(Handler node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Try#edgeHasFinallyBlock hasFinallyBlock} edge points to.
	 * @return Returns the end point of the hasFinallyBlock edge.
	 */
	public Block getFinallyBlock();

	/**
	 * Sets the {@link columbus.java.asg.statm.Try#edgeHasFinallyBlock hasFinallyBlock} edge.
	 * @param id The new end point of the hasFinallyBlock edge.
	 */
	public void setFinallyBlock(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Try#edgeHasFinallyBlock hasFinallyBlock} edge.
	 * @param node The new end point of the hasFinallyBlock edge.
	 */
	public void setFinallyBlock(Block node);

}

