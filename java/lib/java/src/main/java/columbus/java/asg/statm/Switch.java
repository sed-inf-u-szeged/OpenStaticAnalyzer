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

/**
 * Interface Switch, which represents the {@link columbus.java.asg.statm.Switch Switch} node.
 * @columbus.node (missing)
 * @columbus.attr blockStartPosition (Range) : (missing)
 * @columbus.edge hasCases ({@link columbus.java.asg.statm.SwitchLabel SwitchLabel}, multiple) : (missing)
 */
public interface Switch extends Selection {

	/**
	 * Gives back the {@link columbus.java.asg.statm.Switch#attributeBlockStartPosition blockStartPosition} of the node.
	 * @return Returns with the blockStartPosition.
	 */
	public Range getBlockStartPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Switch#attributeBlockStartPosition blockStartPosition} of the node.
	 * @param value The new value of the blockStartPosition.
	 */
	public void setBlockStartPosition(Range value);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.statm.Switch#edgeHasCases hasCases} edges.
	 * @return Returns an iterator for the hasCases edges.
	 */
	public EdgeIterator<SwitchLabel> getCasesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.statm.Switch#edgeHasCases hasCases} edges or not.
	 * @return Returns true if the node doesn't have any hasCases edge.
	 */
	public boolean getCasesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.statm.Switch#edgeHasCases hasCases} edges the node has.
	 * @return Returns with the number of hasCases edges.
	 */
	public int getCasesSize();

	/**
	 * Adds a new {@link columbus.java.asg.statm.Switch#edgeHasCases hasCases} edge to the node.
	 * @param id The end point of the new hasCases edge.
	 */
	public void addCases(int id);

	/**
	 * Adds a new {@link columbus.java.asg.statm.Switch#edgeHasCases hasCases} edge to the node.
	 * @param node The end point of the new hasCases edge.
	 */
	public void addCases(SwitchLabel node);

}

