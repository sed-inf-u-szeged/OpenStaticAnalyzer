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

package columbus.java.asg.statm;

import columbus.java.asg.*;
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.base.Positioned;

/**
 * Interface Handler, which represents the {@link columbus.java.asg.statm.Handler Handler} node.
 * @columbus.node (missing)
 * @columbus.attr leftParenPosition (Range) : (missing)
 * @columbus.attr rightParenPosition (Range) : (missing)
 * @columbus.edge hasParameter ({@link columbus.java.asg.struc.Parameter Parameter}, single) : (missing)
 * @columbus.edge hasBlock ({@link columbus.java.asg.statm.Block Block}, single) : (missing)
 */
public interface Handler extends Positioned {

	/**
	 * Gives back the {@link columbus.java.asg.statm.Handler#attributeLeftParenPosition leftParenPosition} of the node.
	 * @return Returns with the leftParenPosition.
	 */
	public Range getLeftParenPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Handler#attributeLeftParenPosition leftParenPosition} of the node.
	 * @param value The new value of the leftParenPosition.
	 */
	public void setLeftParenPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.statm.Handler#attributeRightParenPosition rightParenPosition} of the node.
	 * @return Returns with the rightParenPosition.
	 */
	public Range getRightParenPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Handler#attributeRightParenPosition rightParenPosition} of the node.
	 * @param value The new value of the rightParenPosition.
	 */
	public void setRightParenPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Handler#edgeHasParameter hasParameter} edge points to.
	 * @return Returns the end point of the hasParameter edge.
	 */
	public Parameter getParameter();

	/**
	 * Sets the {@link columbus.java.asg.statm.Handler#edgeHasParameter hasParameter} edge.
	 * @param id The new end point of the hasParameter edge.
	 */
	public void setParameter(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Handler#edgeHasParameter hasParameter} edge.
	 * @param node The new end point of the hasParameter edge.
	 */
	public void setParameter(Parameter node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Handler#edgeHasBlock hasBlock} edge points to.
	 * @return Returns the end point of the hasBlock edge.
	 */
	public Block getBlock();

	/**
	 * Sets the {@link columbus.java.asg.statm.Handler#edgeHasBlock hasBlock} edge.
	 * @param id The new end point of the hasBlock edge.
	 */
	public void setBlock(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Handler#edgeHasBlock hasBlock} edge.
	 * @param node The new end point of the hasBlock edge.
	 */
	public void setBlock(Block node);

}

