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
import columbus.java.asg.struc.AnonymousClass;
import columbus.java.asg.struc.NormalMethod;

/**
 * Interface NewClass, which represents the {@link columbus.java.asg.expr.NewClass NewClass} node.
 * @columbus.node (missing)
 * @columbus.edge hasEnclosingExpression ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasTypeArguments ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, multiple) : (missing)
 * @columbus.edge hasTypeName ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 * @columbus.edge hasArguments ({@link columbus.java.asg.expr.Expression Expression}, multiple) : (missing)
 * @columbus.edge hasAnonymousClass ({@link columbus.java.asg.struc.AnonymousClass AnonymousClass}, single) : (missing)
 * @columbus.edge constructor ({@link columbus.java.asg.struc.NormalMethod NormalMethod}, single) : (missing)
 */
public interface NewClass extends Expression {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.NewClass#edgeHasEnclosingExpression hasEnclosingExpression} edge points to.
	 * @return Returns the end point of the hasEnclosingExpression edge.
	 */
	public Expression getEnclosingExpression();

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeHasEnclosingExpression hasEnclosingExpression} edge.
	 * @param id The new end point of the hasEnclosingExpression edge.
	 */
	public void setEnclosingExpression(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeHasEnclosingExpression hasEnclosingExpression} edge.
	 * @param node The new end point of the hasEnclosingExpression edge.
	 */
	public void setEnclosingExpression(Expression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.NewClass#edgeHasTypeArguments hasTypeArguments} edges.
	 * @return Returns an iterator for the hasTypeArguments edges.
	 */
	public EdgeIterator<TypeExpression> getTypeArgumentsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.NewClass#edgeHasTypeArguments hasTypeArguments} edges or not.
	 * @return Returns true if the node doesn't have any hasTypeArguments edge.
	 */
	public boolean getTypeArgumentsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.NewClass#edgeHasTypeArguments hasTypeArguments} edges the node has.
	 * @return Returns with the number of hasTypeArguments edges.
	 */
	public int getTypeArgumentsSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewClass#edgeHasTypeArguments hasTypeArguments} edge to the node.
	 * @param id The end point of the new hasTypeArguments edge.
	 */
	public void addTypeArguments(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewClass#edgeHasTypeArguments hasTypeArguments} edge to the node.
	 * @param node The end point of the new hasTypeArguments edge.
	 */
	public void addTypeArguments(TypeExpression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.NewClass#edgeHasTypeName hasTypeName} edge points to.
	 * @return Returns the end point of the hasTypeName edge.
	 */
	public TypeExpression getTypeName();

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeHasTypeName hasTypeName} edge.
	 * @param id The new end point of the hasTypeName edge.
	 */
	public void setTypeName(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeHasTypeName hasTypeName} edge.
	 * @param node The new end point of the hasTypeName edge.
	 */
	public void setTypeName(TypeExpression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.NewClass#edgeHasArguments hasArguments} edges.
	 * @return Returns an iterator for the hasArguments edges.
	 */
	public EdgeIterator<Expression> getArgumentsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.NewClass#edgeHasArguments hasArguments} edges or not.
	 * @return Returns true if the node doesn't have any hasArguments edge.
	 */
	public boolean getArgumentsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.NewClass#edgeHasArguments hasArguments} edges the node has.
	 * @return Returns with the number of hasArguments edges.
	 */
	public int getArgumentsSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewClass#edgeHasArguments hasArguments} edge to the node.
	 * @param id The end point of the new hasArguments edge.
	 */
	public void addArguments(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.NewClass#edgeHasArguments hasArguments} edge to the node.
	 * @param node The end point of the new hasArguments edge.
	 */
	public void addArguments(Expression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.NewClass#edgeHasAnonymousClass hasAnonymousClass} edge points to.
	 * @return Returns the end point of the hasAnonymousClass edge.
	 */
	public AnonymousClass getAnonymousClass();

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeHasAnonymousClass hasAnonymousClass} edge.
	 * @param id The new end point of the hasAnonymousClass edge.
	 */
	public void setAnonymousClass(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeHasAnonymousClass hasAnonymousClass} edge.
	 * @param node The new end point of the hasAnonymousClass edge.
	 */
	public void setAnonymousClass(AnonymousClass node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.NewClass#edgeConstructor constructor} edge points to.
	 * @return Returns the end point of the constructor edge.
	 */
	public NormalMethod getConstructor();

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeConstructor constructor} edge.
	 * @param id The new end point of the constructor edge.
	 */
	public void setConstructor(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.NewClass#edgeConstructor constructor} edge.
	 * @param node The new end point of the constructor edge.
	 */
	public void setConstructor(NormalMethod node);

}

