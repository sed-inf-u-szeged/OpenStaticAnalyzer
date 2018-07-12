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

package columbus.java.asg.expr;

import columbus.java.asg.*;
import columbus.java.asg.base.Positioned;

/**
 * Interface ErroneousTypeExpression, which represents the {@link columbus.java.asg.expr.ErroneousTypeExpression ErroneousTypeExpression} node.
 * @columbus.node (missing)
 * @columbus.edge hasErrors ({@link columbus.java.asg.base.Positioned Positioned}, multiple) : (missing)
 */
public interface ErroneousTypeExpression extends TypeExpression {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.ErroneousTypeExpression#edgeHasErrors hasErrors} edges.
	 * @return Returns an iterator for the hasErrors edges.
	 */
	public EdgeIterator<Positioned> getErrorsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.ErroneousTypeExpression#edgeHasErrors hasErrors} edges or not.
	 * @return Returns true if the node doesn't have any hasErrors edge.
	 */
	public boolean getErrorsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.ErroneousTypeExpression#edgeHasErrors hasErrors} edges the node has.
	 * @return Returns with the number of hasErrors edges.
	 */
	public int getErrorsSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.ErroneousTypeExpression#edgeHasErrors hasErrors} edge to the node.
	 * @param id The end point of the new hasErrors edge.
	 */
	public void addErrors(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.ErroneousTypeExpression#edgeHasErrors hasErrors} edge to the node.
	 * @param node The end point of the new hasErrors edge.
	 */
	public void addErrors(Positioned node);

}

