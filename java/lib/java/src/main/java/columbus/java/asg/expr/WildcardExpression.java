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

import columbus.java.asg.enums.*;

/**
 * Interface WildcardExpression, which represents the {@link columbus.java.asg.expr.WildcardExpression WildcardExpression} node.
 * @columbus.node (missing)
 * @columbus.attr kind ({@link columbus.java.asg.enums.TypeBoundKind TypeBoundKind}) : (missing)
 * @columbus.edge hasBound ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 */
public interface WildcardExpression extends TypeExpression {

	/**
	 * Gives back the {@link columbus.java.asg.expr.WildcardExpression#attributeKind kind} of the node.
	 * @return Returns with the kind.
	 */
	public TypeBoundKind getKind();

	/**
	 * Sets the {@link columbus.java.asg.expr.WildcardExpression#attributeKind kind} of the node.
	 * @param value The new value of the kind.
	 */
	public void setKind(TypeBoundKind value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.WildcardExpression#edgeHasBound hasBound} edge points to.
	 * @return Returns the end point of the hasBound edge.
	 */
	public TypeExpression getBound();

	/**
	 * Sets the {@link columbus.java.asg.expr.WildcardExpression#edgeHasBound hasBound} edge.
	 * @param id The new end point of the hasBound edge.
	 */
	public void setBound(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.WildcardExpression#edgeHasBound hasBound} edge.
	 * @param node The new end point of the hasBound edge.
	 */
	public void setBound(TypeExpression node);

}

