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

import columbus.java.asg.expr.Expression;

/**
 * Interface Synchronized, which represents the {@link columbus.java.asg.statm.Synchronized Synchronized} node.
 * @columbus.node (missing)
 * @columbus.edge hasLock ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasBlock ({@link columbus.java.asg.statm.Block Block}, single) : (missing)
 */
public interface Synchronized extends Statement {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Synchronized#edgeHasLock hasLock} edge points to.
	 * @return Returns the end point of the hasLock edge.
	 */
	public Expression getLock();

	/**
	 * Sets the {@link columbus.java.asg.statm.Synchronized#edgeHasLock hasLock} edge.
	 * @param id The new end point of the hasLock edge.
	 */
	public void setLock(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Synchronized#edgeHasLock hasLock} edge.
	 * @param node The new end point of the hasLock edge.
	 */
	public void setLock(Expression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Synchronized#edgeHasBlock hasBlock} edge points to.
	 * @return Returns the end point of the hasBlock edge.
	 */
	public Block getBlock();

	/**
	 * Sets the {@link columbus.java.asg.statm.Synchronized#edgeHasBlock hasBlock} edge.
	 * @param id The new end point of the hasBlock edge.
	 */
	public void setBlock(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Synchronized#edgeHasBlock hasBlock} edge.
	 * @param node The new end point of the hasBlock edge.
	 */
	public void setBlock(Block node);

}

