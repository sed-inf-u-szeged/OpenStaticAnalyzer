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

import columbus.java.asg.expr.Expression;

/**
 * Interface ExpressionStatement, which represents the {@link columbus.java.asg.statm.ExpressionStatement ExpressionStatement} node.
 * @columbus.node (missing)
 * @columbus.edge hasExpression ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 */
public interface ExpressionStatement extends Statement {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.statm.ExpressionStatement#edgeHasExpression hasExpression} edge points to.
	 * @return Returns the end point of the hasExpression edge.
	 */
	public Expression getExpression();

	/**
	 * Sets the {@link columbus.java.asg.statm.ExpressionStatement#edgeHasExpression hasExpression} edge.
	 * @param id The new end point of the hasExpression edge.
	 */
	public void setExpression(int id);

	/**
	 * Sets the {@link columbus.java.asg.statm.ExpressionStatement#edgeHasExpression hasExpression} edge.
	 * @param node The new end point of the hasExpression edge.
	 */
	public void setExpression(Expression node);

}

