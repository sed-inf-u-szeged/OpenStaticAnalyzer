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

import columbus.java.asg.*;

/**
 * Interface NormalAnnotation, which represents the {@link columbus.java.asg.expr.NormalAnnotation NormalAnnotation} node.
 * @columbus.node (missing)
 * @columbus.edge hasArguments ({@link columbus.java.asg.expr.Expression Expression}, multiple) : (missing)
 */
public interface NormalAnnotation extends Annotation {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.NormalAnnotation#edgeHasArguments hasArguments} edges.
	 * @return Returns an iterator for the hasArguments edges.
	 */
	public EdgeIterator<Expression> getArgumentsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.NormalAnnotation#edgeHasArguments hasArguments} edges or not.
	 * @return Returns true if the node doesn't have any hasArguments edge.
	 */
	public boolean getArgumentsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.NormalAnnotation#edgeHasArguments hasArguments} edges the node has.
	 * @return Returns with the number of hasArguments edges.
	 */
	public int getArgumentsSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.NormalAnnotation#edgeHasArguments hasArguments} edge to the node.
	 * @param id The end point of the new hasArguments edge.
	 */
	public void addArguments(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.NormalAnnotation#edgeHasArguments hasArguments} edge to the node.
	 * @param node The end point of the new hasArguments edge.
	 */
	public void addArguments(Expression node);

}

