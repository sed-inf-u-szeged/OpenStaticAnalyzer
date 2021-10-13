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

import columbus.java.asg.expr.Expression;

/**
 * Interface Requires, which represents the {@link columbus.java.asg.module.Requires Requires} node.
 * @columbus.node (missing)
 * @columbus.attr isTransitive (boolean) : (missing)
 * @columbus.attr isStatic (boolean) : (missing)
 * @columbus.edge hasModuleName ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 */
public interface Requires extends ModuleDirective {

	/**
	 * Gives back the {@link columbus.java.asg.module.Requires#attributeIsTransitive isTransitive} of the node.
	 * @return Returns with the isTransitive.
	 */
	public boolean getIsTransitive();

	/**
	 * Sets the {@link columbus.java.asg.module.Requires#attributeIsTransitive isTransitive} of the node.
	 * @param value The new value of the isTransitive.
	 */
	public void setIsTransitive(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.module.Requires#attributeIsStatic isStatic} of the node.
	 * @return Returns with the isStatic.
	 */
	public boolean getIsStatic();

	/**
	 * Sets the {@link columbus.java.asg.module.Requires#attributeIsStatic isStatic} of the node.
	 * @param value The new value of the isStatic.
	 */
	public void setIsStatic(boolean value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.module.Requires#edgeHasModuleName hasModuleName} edge points to.
	 * @return Returns the end point of the hasModuleName edge.
	 */
	public Expression getModuleName();

	/**
	 * Sets the {@link columbus.java.asg.module.Requires#edgeHasModuleName hasModuleName} edge.
	 * @param id The new end point of the hasModuleName edge.
	 */
	public void setModuleName(int id);

	/**
	 * Sets the {@link columbus.java.asg.module.Requires#edgeHasModuleName hasModuleName} edge.
	 * @param node The new end point of the hasModuleName edge.
	 */
	public void setModuleName(Expression node);

}

