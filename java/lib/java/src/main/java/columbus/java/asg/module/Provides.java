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

package columbus.java.asg.module;

import columbus.java.asg.*;
import columbus.java.asg.expr.Expression;

/**
 * Interface Provides, which represents the {@link columbus.java.asg.module.Provides Provides} node.
 * @columbus.node (missing)
 * @columbus.edge hasServiceName ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasImplementationNames ({@link columbus.java.asg.expr.Expression Expression}, multiple) : (missing)
 */
public interface Provides extends ModuleDirective {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.module.Provides#edgeHasServiceName hasServiceName} edge points to.
	 * @return Returns the end point of the hasServiceName edge.
	 */
	public Expression getServiceName();

	/**
	 * Sets the {@link columbus.java.asg.module.Provides#edgeHasServiceName hasServiceName} edge.
	 * @param id The new end point of the hasServiceName edge.
	 */
	public void setServiceName(int id);

	/**
	 * Sets the {@link columbus.java.asg.module.Provides#edgeHasServiceName hasServiceName} edge.
	 * @param node The new end point of the hasServiceName edge.
	 */
	public void setServiceName(Expression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.module.Provides#edgeHasImplementationNames hasImplementationNames} edges.
	 * @return Returns an iterator for the hasImplementationNames edges.
	 */
	public EdgeIterator<Expression> getImplementationNamesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.module.Provides#edgeHasImplementationNames hasImplementationNames} edges or not.
	 * @return Returns true if the node doesn't have any hasImplementationNames edge.
	 */
	public boolean getImplementationNamesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.module.Provides#edgeHasImplementationNames hasImplementationNames} edges the node has.
	 * @return Returns with the number of hasImplementationNames edges.
	 */
	public int getImplementationNamesSize();

	/**
	 * Adds a new {@link columbus.java.asg.module.Provides#edgeHasImplementationNames hasImplementationNames} edge to the node.
	 * @param id The end point of the new hasImplementationNames edge.
	 */
	public void addImplementationNames(int id);

	/**
	 * Adds a new {@link columbus.java.asg.module.Provides#edgeHasImplementationNames hasImplementationNames} edge to the node.
	 * @param node The end point of the new hasImplementationNames edge.
	 */
	public void addImplementationNames(Expression node);

}

