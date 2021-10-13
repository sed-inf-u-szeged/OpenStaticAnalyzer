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
import columbus.java.asg.base.Named;

/**
 * Interface Module, which represents the {@link columbus.java.asg.struc.Module Module} node.
 * @columbus.node (missing)
 * @columbus.edge packages ({@link columbus.java.asg.struc.Package Package}, multiple) : (missing)
 */
public interface Module extends Named {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.Module#edgePackages packages} edges.
	 * @return Returns an iterator for the packages edges.
	 */
	public EdgeIterator<Package> getPackagesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.Module#edgePackages packages} edges or not.
	 * @return Returns true if the node doesn't have any packages edge.
	 */
	public boolean getPackagesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.Module#edgePackages packages} edges the node has.
	 * @return Returns with the number of packages edges.
	 */
	public int getPackagesSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.Module#edgePackages packages} edge to the node.
	 * @param id The end point of the new packages edge.
	 */
	public void addPackages(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.Module#edgePackages packages} edge to the node.
	 * @param node The end point of the new packages edge.
	 */
	public void addPackages(Package node);

}

