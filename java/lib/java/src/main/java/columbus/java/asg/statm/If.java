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

package columbus.java.asg.statm;

import columbus.java.asg.*;

/**
 * Interface If, which represents the {@link columbus.java.asg.statm.If If} node.
 * @columbus.node (missing)
 * @columbus.attr elsePosition (Range) : (missing)
 * @columbus.edge hasSubstatement ({@link columbus.java.asg.statm.Statement Statement}, single) : (missing)
 * @columbus.edge hasFalseSubstatement ({@link columbus.java.asg.statm.Statement Statement}, single) : (missing)
 */
public interface If extends Selection {

	/**
	 * Gives back the {@link columbus.java.asg.statm.If#attributeElsePosition elsePosition} of the node.
	 * @return Returns with the elsePosition.
	 */
	public Range getElsePosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.If#attributeElsePosition elsePosition} of the node.
	 * @param value The new value of the elsePosition.
	 */
	public void setElsePosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.If#edgeHasSubstatement hasSubstatement} edge points to.
	 * @return Returns the end point of the hasSubstatement edge.
	 */
	public Statement getSubstatement();

	/**
	 * Sets the {@link columbus.java.asg.statm.If#edgeHasSubstatement hasSubstatement} edge.
	 * @param id The new end point of the hasSubstatement edge.
	 */
	public void setSubstatement(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.If#edgeHasSubstatement hasSubstatement} edge.
	 * @param node The new end point of the hasSubstatement edge.
	 */
	public void setSubstatement(Statement node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.If#edgeHasFalseSubstatement hasFalseSubstatement} edge points to.
	 * @return Returns the end point of the hasFalseSubstatement edge.
	 */
	public Statement getFalseSubstatement();

	/**
	 * Sets the {@link columbus.java.asg.statm.If#edgeHasFalseSubstatement hasFalseSubstatement} edge.
	 * @param id The new end point of the hasFalseSubstatement edge.
	 */
	public void setFalseSubstatement(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.If#edgeHasFalseSubstatement hasFalseSubstatement} edge.
	 * @param node The new end point of the hasFalseSubstatement edge.
	 */
	public void setFalseSubstatement(Statement node);

}

