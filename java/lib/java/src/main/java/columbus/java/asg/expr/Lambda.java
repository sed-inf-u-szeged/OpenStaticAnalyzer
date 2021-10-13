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
import columbus.java.asg.struc.Parameter;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.enums.*;

/**
 * Interface Lambda, which represents the {@link columbus.java.asg.expr.Lambda Lambda} node.
 * @columbus.node (missing)
 * @columbus.attr lloc (int) : (missing)
 * @columbus.attr paramKind ({@link columbus.java.asg.enums.LambdaParameterKind LambdaParameterKind}) : (missing)
 * @columbus.attr bodyKind ({@link columbus.java.asg.enums.LambdaBodyKind LambdaBodyKind}) : (missing)
 * @columbus.edge hasParameters ({@link columbus.java.asg.struc.Parameter Parameter}, multiple) : (missing)
 * @columbus.edge hasBody ({@link columbus.java.asg.base.Positioned Positioned}, single) : (missing)
 */
public interface Lambda extends FunctionalExpression {

	/**
	 * Gives back the {@link columbus.java.asg.expr.Lambda#attributeLloc lloc} of the node.
	 * @return Returns with the lloc.
	 */
	public int getLloc();

	/**
	 * Sets the {@link columbus.java.asg.expr.Lambda#attributeLloc lloc} of the node.
	 * @param value The new value of the lloc.
	 */
	public void setLloc(int value);

	/**
	 * Gives back the {@link columbus.java.asg.expr.Lambda#attributeParamKind paramKind} of the node.
	 * @return Returns with the paramKind.
	 */
	public LambdaParameterKind getParamKind();

	/**
	 * Sets the {@link columbus.java.asg.expr.Lambda#attributeParamKind paramKind} of the node.
	 * @param value The new value of the paramKind.
	 */
	public void setParamKind(LambdaParameterKind value);

	/**
	 * Gives back the {@link columbus.java.asg.expr.Lambda#attributeBodyKind bodyKind} of the node.
	 * @return Returns with the bodyKind.
	 */
	public LambdaBodyKind getBodyKind();

	/**
	 * Sets the {@link columbus.java.asg.expr.Lambda#attributeBodyKind bodyKind} of the node.
	 * @param value The new value of the bodyKind.
	 */
	public void setBodyKind(LambdaBodyKind value);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.Lambda#edgeHasParameters hasParameters} edges.
	 * @return Returns an iterator for the hasParameters edges.
	 */
	public EdgeIterator<Parameter> getParametersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.Lambda#edgeHasParameters hasParameters} edges or not.
	 * @return Returns true if the node doesn't have any hasParameters edge.
	 */
	public boolean getParametersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.Lambda#edgeHasParameters hasParameters} edges the node has.
	 * @return Returns with the number of hasParameters edges.
	 */
	public int getParametersSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.Lambda#edgeHasParameters hasParameters} edge to the node.
	 * @param id The end point of the new hasParameters edge.
	 */
	public void addParameters(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.Lambda#edgeHasParameters hasParameters} edge to the node.
	 * @param node The end point of the new hasParameters edge.
	 */
	public void addParameters(Parameter node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.Lambda#edgeHasBody hasBody} edge points to.
	 * @return Returns the end point of the hasBody edge.
	 */
	public Positioned getBody();

	/**
	 * Sets the {@link columbus.java.asg.expr.Lambda#edgeHasBody hasBody} edge.
	 * @param id The new end point of the hasBody edge.
	 */
	public void setBody(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.Lambda#edgeHasBody hasBody} edge.
	 * @param node The new end point of the hasBody edge.
	 */
	public void setBody(Positioned node);

}

