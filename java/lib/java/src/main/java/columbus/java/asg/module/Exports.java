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
 * Interface Exports, which represents the {@link columbus.java.asg.module.Exports Exports} node.
 * @columbus.node (missing)
 * @columbus.edge hasPackageName ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasModuleNames ({@link columbus.java.asg.expr.Expression Expression}, multiple) : (missing)
 */
public interface Exports extends ModuleDirective {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.module.Exports#edgeHasPackageName hasPackageName} edge points to.
	 * @return Returns the end point of the hasPackageName edge.
	 */
	public Expression getPackageName();

	/**
	 * Sets the {@link columbus.java.asg.module.Exports#edgeHasPackageName hasPackageName} edge.
	 * @param id The new end point of the hasPackageName edge.
	 */
	public void setPackageName(int id);

	/**
	 * Sets the {@link columbus.java.asg.module.Exports#edgeHasPackageName hasPackageName} edge.
	 * @param node The new end point of the hasPackageName edge.
	 */
	public void setPackageName(Expression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.module.Exports#edgeHasModuleNames hasModuleNames} edges.
	 * @return Returns an iterator for the hasModuleNames edges.
	 */
	public EdgeIterator<Expression> getModuleNamesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.module.Exports#edgeHasModuleNames hasModuleNames} edges or not.
	 * @return Returns true if the node doesn't have any hasModuleNames edge.
	 */
	public boolean getModuleNamesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.module.Exports#edgeHasModuleNames hasModuleNames} edges the node has.
	 * @return Returns with the number of hasModuleNames edges.
	 */
	public int getModuleNamesSize();

	/**
	 * Adds a new {@link columbus.java.asg.module.Exports#edgeHasModuleNames hasModuleNames} edge to the node.
	 * @param id The end point of the new hasModuleNames edge.
	 */
	public void addModuleNames(int id);

	/**
	 * Adds a new {@link columbus.java.asg.module.Exports#edgeHasModuleNames hasModuleNames} edge to the node.
	 * @param node The end point of the new hasModuleNames edge.
	 */
	public void addModuleNames(Expression node);

}

