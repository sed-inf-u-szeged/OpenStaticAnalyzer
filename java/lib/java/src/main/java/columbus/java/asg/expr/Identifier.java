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

package columbus.java.asg.expr;

import columbus.java.asg.base.Named;

/**
 * Interface Identifier, which represents the {@link columbus.java.asg.expr.Identifier Identifier} node.
 * @columbus.node (missing)
 * @columbus.attr name (String) : (missing)
 * @columbus.edge refersTo ({@link columbus.java.asg.base.Named Named}, single) : (missing)
 */
public interface Identifier extends Expression {

	/**
	 * Gives back the {@link columbus.java.asg.expr.Identifier#attributeName name} of the node.
	 * @return Returns with the name.
	 */
	public String getName();

	/**
	 * Gives back the Key of {@link columbus.java.asg.expr.Identifier#attributeName name} of the node.
	 * @return Returns with the Key of the name.
	 */
	public int getNameKey();

	/**
	 * Sets the {@link columbus.java.asg.expr.Identifier#attributeName name} of the node.
	 * @param value The new value of the name.
	 */
	public void setName(String value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.Identifier#edgeRefersTo refersTo} edge points to.
	 * @return Returns the end point of the refersTo edge.
	 */
	public Named getRefersTo();

	/**
	 * Sets the {@link columbus.java.asg.expr.Identifier#edgeRefersTo refersTo} edge.
	 * @param id The new end point of the refersTo edge.
	 */
	public void setRefersTo(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.Identifier#edgeRefersTo refersTo} edge.
	 * @param node The new end point of the refersTo edge.
	 */
	public void setRefersTo(Named node);

}

