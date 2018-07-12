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

/**
 * Interface TypeApplyExpression, which represents the {@link columbus.java.asg.expr.TypeApplyExpression TypeApplyExpression} node.
 * @columbus.node (missing)
 * @columbus.edge hasRawType ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 * @columbus.edge hasTypeArguments ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, multiple) : (missing)
 */
public interface TypeApplyExpression extends TypeExpression {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasRawType hasRawType} edge points to.
	 * @return Returns the end point of the hasRawType edge.
	 */
	public TypeExpression getRawType();

	/**
	 * Sets the {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasRawType hasRawType} edge.
	 * @param id The new end point of the hasRawType edge.
	 */
	public void setRawType(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasRawType hasRawType} edge.
	 * @param node The new end point of the hasRawType edge.
	 */
	public void setRawType(TypeExpression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasTypeArguments hasTypeArguments} edges.
	 * @return Returns an iterator for the hasTypeArguments edges.
	 */
	public EdgeIterator<TypeExpression> getTypeArgumentsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasTypeArguments hasTypeArguments} edges or not.
	 * @return Returns true if the node doesn't have any hasTypeArguments edge.
	 */
	public boolean getTypeArgumentsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasTypeArguments hasTypeArguments} edges the node has.
	 * @return Returns with the number of hasTypeArguments edges.
	 */
	public int getTypeArgumentsSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasTypeArguments hasTypeArguments} edge to the node.
	 * @param id The end point of the new hasTypeArguments edge.
	 */
	public void addTypeArguments(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.TypeApplyExpression#edgeHasTypeArguments hasTypeArguments} edge to the node.
	 * @param node The end point of the new hasTypeArguments edge.
	 */
	public void addTypeArguments(TypeExpression node);

}

