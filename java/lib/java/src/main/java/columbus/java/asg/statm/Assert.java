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

package columbus.java.asg.statm;

import columbus.java.asg.*;
import columbus.java.asg.expr.Expression;

/**
 * Interface Assert, which represents the {@link columbus.java.asg.statm.Assert Assert} node.
 * @columbus.node (missing)
 * @columbus.attr colonPosition (Range) : (missing)
 * @columbus.edge hasCondition ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasDetail ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 */
public interface Assert extends Statement {

	/**
	 * Gives back the {@link columbus.java.asg.statm.Assert#attributeColonPosition colonPosition} of the node.
	 * @return Returns with the colonPosition.
	 */
	public Range getColonPosition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Assert#attributeColonPosition colonPosition} of the node.
	 * @param value The new value of the colonPosition.
	 */
	public void setColonPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Assert#edgeHasCondition hasCondition} edge points to.
	 * @return Returns the end point of the hasCondition edge.
	 */
	public Expression getCondition();

	/**
	 * Sets the {@link columbus.java.asg.statm.Assert#edgeHasCondition hasCondition} edge.
	 * @param id The new end point of the hasCondition edge.
	 */
	public void setCondition(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Assert#edgeHasCondition hasCondition} edge.
	 * @param node The new end point of the hasCondition edge.
	 */
	public void setCondition(Expression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.Assert#edgeHasDetail hasDetail} edge points to.
	 * @return Returns the end point of the hasDetail edge.
	 */
	public Expression getDetail();

	/**
	 * Sets the {@link columbus.java.asg.statm.Assert#edgeHasDetail hasDetail} edge.
	 * @param id The new end point of the hasDetail edge.
	 */
	public void setDetail(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.Assert#edgeHasDetail hasDetail} edge.
	 * @param node The new end point of the hasDetail edge.
	 */
	public void setDetail(Expression node);

}

