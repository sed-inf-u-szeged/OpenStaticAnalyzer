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
 * Interface LabeledStatement, which represents the {@link columbus.java.asg.statm.LabeledStatement LabeledStatement} node.
 * @columbus.node (missing)
 * @columbus.attr label (String) : (missing)
 * @columbus.attr colonPosition (Range) : (missing)
 * @columbus.edge hasStatement ({@link columbus.java.asg.statm.Statement Statement}, single) : (missing)
 */
public interface LabeledStatement extends Statement {

	/**
	 * Gives back the {@link columbus.java.asg.statm.LabeledStatement#attributeLabel label} of the node.
	 * @return Returns with the label.
	 */
	public String getLabel();

	/**
	 * Gives back the Key of {@link columbus.java.asg.statm.LabeledStatement#attributeLabel label} of the node.
	 * @return Returns with the Key of the label.
	 */
	public int getLabelKey();

	/**
	 * Sets the {@link columbus.java.asg.statm.LabeledStatement#attributeLabel label} of the node.
	 * @param value The new value of the label.
	 */
	public void setLabel(String value);

	/**
	 * Gives back the {@link columbus.java.asg.statm.LabeledStatement#attributeColonPosition colonPosition} of the node.
	 * @return Returns with the colonPosition.
	 */
	public Range getColonPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.LabeledStatement#attributeColonPosition colonPosition} of the node.
	 * @param value The new value of the colonPosition.
	 */
	public void setColonPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.LabeledStatement#edgeHasStatement hasStatement} edge points to.
	 * @return Returns the end point of the hasStatement edge.
	 */
	public Statement getStatement();

	/**
	 * Sets the {@link columbus.java.asg.statm.LabeledStatement#edgeHasStatement hasStatement} edge.
	 * @param id The new end point of the hasStatement edge.
	 */
	public void setStatement(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.LabeledStatement#edgeHasStatement hasStatement} edge.
	 * @param node The new end point of the hasStatement edge.
	 */
	public void setStatement(Statement node);

}

