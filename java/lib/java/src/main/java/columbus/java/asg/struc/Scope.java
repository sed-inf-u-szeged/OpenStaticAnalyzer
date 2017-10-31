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

package columbus.java.asg.struc;

import columbus.java.asg.*;

/**
 * Interface Scope, which represents the {@link columbus.java.asg.struc.Scope Scope} node.
 * @columbus.node (missing)
 * @columbus.edge hasMembers ({@link columbus.java.asg.struc.Member Member}, multiple) : (missing)
 */
public interface Scope extends Member {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.Scope#edgeHasMembers hasMembers} edges.
	 * @return Returns an iterator for the hasMembers edges.
	 */
	public EdgeIterator<Member> getMembersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.Scope#edgeHasMembers hasMembers} edges or not.
	 * @return Returns true if the node doesn't have any hasMembers edge.
	 */
	public boolean getMembersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.Scope#edgeHasMembers hasMembers} edges the node has.
	 * @return Returns with the number of hasMembers edges.
	 */
	public int getMembersSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.Scope#edgeHasMembers hasMembers} edge to the node.
	 * @param id The end point of the new hasMembers edge.
	 */
	public void addMembers(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.Scope#edgeHasMembers hasMembers} edge to the node.
	 * @param node The end point of the new hasMembers edge.
	 */
	public void addMembers(Member node);

}

