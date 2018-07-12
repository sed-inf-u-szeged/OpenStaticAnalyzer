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

package columbus.java.asg.struc;

import columbus.java.asg.*;
import columbus.java.asg.statm.Block;
import columbus.java.asg.expr.TypeExpression;
import columbus.java.asg.enums.*;

/**
 * Interface NormalMethod, which represents the {@link columbus.java.asg.struc.NormalMethod NormalMethod} node.
 * @columbus.node (missing)
 * @columbus.attr methodKind ({@link columbus.java.asg.enums.MethodKind MethodKind}) : (missing)
 * @columbus.attr isSynchronized (boolean) : (missing)
 * @columbus.attr synchronizedPosition (Range) : (missing)
 * @columbus.attr isNative (boolean) : (missing)
 * @columbus.attr nativePosition (Range) : (missing)
 * @columbus.attr throwsPosition (Range) : (missing)
 * @columbus.edge hasParameters ({@link columbus.java.asg.struc.Parameter Parameter}, multiple) : (missing)
 * @columbus.edge hasBody ({@link columbus.java.asg.statm.Block Block}, single) : (missing)
 * @columbus.edge hasThrownExceptions ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, multiple) : (missing)
 */
public interface NormalMethod extends MethodDeclaration {

	/**
	 * Gives back the {@link columbus.java.asg.struc.NormalMethod#attributeMethodKind methodKind} of the node.
	 * @return Returns with the methodKind.
	 */
	public MethodKind getMethodKind();

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#attributeMethodKind methodKind} of the node.
	 * @param value The new value of the methodKind.
	 */
	public void setMethodKind(MethodKind value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NormalMethod#attributeIsSynchronized isSynchronized} of the node.
	 * @return Returns with the isSynchronized.
	 */
	public boolean getIsSynchronized();

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#attributeIsSynchronized isSynchronized} of the node.
	 * @param value The new value of the isSynchronized.
	 */
	public void setIsSynchronized(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NormalMethod#attributeSynchronizedPosition synchronizedPosition} of the node.
	 * @return Returns with the synchronizedPosition.
	 */
	public Range getSynchronizedPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#attributeSynchronizedPosition synchronizedPosition} of the node.
	 * @param value The new value of the synchronizedPosition.
	 */
	public void setSynchronizedPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NormalMethod#attributeIsNative isNative} of the node.
	 * @return Returns with the isNative.
	 */
	public boolean getIsNative();

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#attributeIsNative isNative} of the node.
	 * @param value The new value of the isNative.
	 */
	public void setIsNative(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NormalMethod#attributeNativePosition nativePosition} of the node.
	 * @return Returns with the nativePosition.
	 */
	public Range getNativePosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#attributeNativePosition nativePosition} of the node.
	 * @param value The new value of the nativePosition.
	 */
	public void setNativePosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.NormalMethod#attributeThrowsPosition throwsPosition} of the node.
	 * @return Returns with the throwsPosition.
	 */
	public Range getThrowsPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#attributeThrowsPosition throwsPosition} of the node.
	 * @param value The new value of the throwsPosition.
	 */
	public void setThrowsPosition(Range value);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.NormalMethod#edgeHasParameters hasParameters} edges.
	 * @return Returns an iterator for the hasParameters edges.
	 */
	public EdgeIterator<Parameter> getParametersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.NormalMethod#edgeHasParameters hasParameters} edges or not.
	 * @return Returns true if the node doesn't have any hasParameters edge.
	 */
	public boolean getParametersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.NormalMethod#edgeHasParameters hasParameters} edges the node has.
	 * @return Returns with the number of hasParameters edges.
	 */
	public int getParametersSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.NormalMethod#edgeHasParameters hasParameters} edge to the node.
	 * @param id The end point of the new hasParameters edge.
	 */
	public void addParameters(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.NormalMethod#edgeHasParameters hasParameters} edge to the node.
	 * @param node The end point of the new hasParameters edge.
	 */
	public void addParameters(Parameter node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.NormalMethod#edgeHasBody hasBody} edge points to.
	 * @return Returns the end point of the hasBody edge.
	 */
	public Block getBody();

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#edgeHasBody hasBody} edge.
	 * @param id The new end point of the hasBody edge.
	 */
	public void setBody(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.NormalMethod#edgeHasBody hasBody} edge.
	 * @param node The new end point of the hasBody edge.
	 */
	public void setBody(Block node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.NormalMethod#edgeHasThrownExceptions hasThrownExceptions} edges.
	 * @return Returns an iterator for the hasThrownExceptions edges.
	 */
	public EdgeIterator<TypeExpression> getThrownExceptionsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.NormalMethod#edgeHasThrownExceptions hasThrownExceptions} edges or not.
	 * @return Returns true if the node doesn't have any hasThrownExceptions edge.
	 */
	public boolean getThrownExceptionsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.NormalMethod#edgeHasThrownExceptions hasThrownExceptions} edges the node has.
	 * @return Returns with the number of hasThrownExceptions edges.
	 */
	public int getThrownExceptionsSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.NormalMethod#edgeHasThrownExceptions hasThrownExceptions} edge to the node.
	 * @param id The end point of the new hasThrownExceptions edge.
	 */
	public void addThrownExceptions(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.NormalMethod#edgeHasThrownExceptions hasThrownExceptions} edge to the node.
	 * @param node The end point of the new hasThrownExceptions edge.
	 */
	public void addThrownExceptions(TypeExpression node);

}

