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

import columbus.java.asg.statm.Block;

/**
 * Interface InitializerBlock, which represents the {@link columbus.java.asg.struc.InitializerBlock InitializerBlock} node.
 * @columbus.node (missing)
 * @columbus.attr lloc (int) : (missing)
 * @columbus.edge hasBody ({@link columbus.java.asg.statm.Block Block}, single) : (missing)
 */
public interface InitializerBlock extends Declaration {

	/**
	 * Gives back the {@link columbus.java.asg.struc.InitializerBlock#attributeLloc lloc} of the node.
	 * @return Returns with the lloc.
	 */
	public int getLloc();

	/**
	 * Sets the {@link columbus.java.asg.struc.InitializerBlock#attributeLloc lloc} of the node.
	 * @param value The new value of the lloc.
	 */
	public void setLloc(int value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.InitializerBlock#edgeHasBody hasBody} edge points to.
	 * @return Returns the end point of the hasBody edge.
	 */
	public Block getBody();

	/**
	 * Sets the {@link columbus.java.asg.struc.InitializerBlock#edgeHasBody hasBody} edge.
	 * @param id The new end point of the hasBody edge.
	 */
	public void setBody(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.InitializerBlock#edgeHasBody hasBody} edge.
	 * @param node The new end point of the hasBody edge.
	 */
	public void setBody(Block node);

}

