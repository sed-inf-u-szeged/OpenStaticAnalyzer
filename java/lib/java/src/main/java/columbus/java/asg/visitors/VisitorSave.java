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

package columbus.java.asg.visitors;

import columbus.IO;
import columbus.java.asg.base.Base;

/**
 * Visitor for saving the graph.
 */
public class VisitorSave extends VisitorAbstractNodes {

	/** Reference to the "output". */
	protected IO io;

	/**
	 * Constructor for VisitorSave.
	 * @param io The graph is save into this IO.
	 */
	public VisitorSave(IO io) {
		this.io = io;
	}

	/**
	 * Visitor for saving node.
	 * @param node This node is being saved.
	 * @param callVirtualBase Helper flag which determines whether to call overloaded methods for virtual base classes. Methods for non-virtual base classes are called directly.
	 */
	@Override
	public void visitEnd(Base node, boolean callVirtualBase) {
		node.save(io);
	}

}
