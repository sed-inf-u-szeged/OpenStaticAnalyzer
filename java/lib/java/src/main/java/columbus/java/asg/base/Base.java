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

package columbus.java.asg.base;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;

/**
 * Interface Base, which represents the {@link columbus.java.asg.base.Base Base} node.
 * @columbus.node (missing)
 * @columbus.attr id (int) : (missing)
 */
public interface Base {

	/**
	 * Gives back the NodeKind of the node.
	 * @return Returns with the NodeKind.
	 */
	public NodeKind getNodeKind();

	/**
	 * Gives back the Factory the node belongs to.
	 * @return Return with a reference to the Factory.
	 */
	public Factory getFactory();

	/**
	 * It calls the appropriate visit method of the given visitor.
	 * @param visitor The used visitor.
	 */
	public void accept(Visitor visitor);

	/**
	 * It calls the appropriate visitEnd method of the given visitor.
	 * @param visitor The used visitor.
	 */
	public void acceptEnd(Visitor visitor);

	/**
	 * Saves the node.
	 * @param io The node is written into io.
	 */
	public void save(IO io);

	/**
	 * Loads the node.
	 * @param io The node is read from io.
	 */
	public void load(IO io);

	/**
	 * Gives back the reference of the parent of this node.
	 * @return Return with the reference of the parent of this node or null if it does not have one.
	 */
	public Base getParent();

	/**
	 * Gives back the {@link columbus.java.asg.base.Base#attributeId id} of the node.
	 * @return Returns with the id.
	 */
	public int getId();

}

