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
import columbus.java.asg.expr.TypeExpression;
import columbus.java.asg.type.MethodType;

/**
 * Interface MethodDeclaration, which represents the {@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration} node.
 * @columbus.node (missing)
 * @columbus.attr lloc (int) : (missing)
 * @columbus.attr isAbstract (boolean) : (missing)
 * @columbus.attr abstractPosition (Range) : (missing)
 * @columbus.attr isStrictfp (boolean) : (missing)
 * @columbus.attr strictfpPosition (Range) : (missing)
 * @columbus.attr parametersStartPosition (Range) : (missing)
 * @columbus.attr parametersEndPosition (Range) : (missing)
 * @columbus.edge hasReturnType ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 * @columbus.edge methodType ({@link columbus.java.asg.type.MethodType MethodType}, single) : (missing)
 * @columbus.edge overrides ({@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration}, multiple) : (missing)
 */
public interface MethodDeclaration extends NamedDeclaration {

	/**
	 * Gives back the {@link columbus.java.asg.struc.MethodDeclaration#attributeLloc lloc} of the node.
	 * @return Returns with the lloc.
	 */
	public int getLloc();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#attributeLloc lloc} of the node.
	 * @param value The new value of the lloc.
	 */
	public void setLloc(int value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.MethodDeclaration#attributeIsAbstract isAbstract} of the node.
	 * @return Returns with the isAbstract.
	 */
	public boolean getIsAbstract();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#attributeIsAbstract isAbstract} of the node.
	 * @param value The new value of the isAbstract.
	 */
	public void setIsAbstract(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.MethodDeclaration#attributeAbstractPosition abstractPosition} of the node.
	 * @return Returns with the abstractPosition.
	 */
	public Range getAbstractPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#attributeAbstractPosition abstractPosition} of the node.
	 * @param value The new value of the abstractPosition.
	 */
	public void setAbstractPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.MethodDeclaration#attributeIsStrictfp isStrictfp} of the node.
	 * @return Returns with the isStrictfp.
	 */
	public boolean getIsStrictfp();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#attributeIsStrictfp isStrictfp} of the node.
	 * @param value The new value of the isStrictfp.
	 */
	public void setIsStrictfp(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.MethodDeclaration#attributeStrictfpPosition strictfpPosition} of the node.
	 * @return Returns with the strictfpPosition.
	 */
	public Range getStrictfpPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#attributeStrictfpPosition strictfpPosition} of the node.
	 * @param value The new value of the strictfpPosition.
	 */
	public void setStrictfpPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.MethodDeclaration#attributeParametersStartPosition parametersStartPosition} of the node.
	 * @return Returns with the parametersStartPosition.
	 */
	public Range getParametersStartPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#attributeParametersStartPosition parametersStartPosition} of the node.
	 * @param value The new value of the parametersStartPosition.
	 */
	public void setParametersStartPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.MethodDeclaration#attributeParametersEndPosition parametersEndPosition} of the node.
	 * @return Returns with the parametersEndPosition.
	 */
	public Range getParametersEndPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#attributeParametersEndPosition parametersEndPosition} of the node.
	 * @param value The new value of the parametersEndPosition.
	 */
	public void setParametersEndPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.MethodDeclaration#edgeHasReturnType hasReturnType} edge points to.
	 * @return Returns the end point of the hasReturnType edge.
	 */
	public TypeExpression getReturnType();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#edgeHasReturnType hasReturnType} edge.
	 * @param id The new end point of the hasReturnType edge.
	 */
	public void setReturnType(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#edgeHasReturnType hasReturnType} edge.
	 * @param node The new end point of the hasReturnType edge.
	 */
	public void setReturnType(TypeExpression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.MethodDeclaration#edgeMethodType methodType} edge points to.
	 * @return Returns the end point of the methodType edge.
	 */
	public MethodType getMethodType();

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#edgeMethodType methodType} edge.
	 * @param id The new end point of the methodType edge.
	 */
	public void setMethodType(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.MethodDeclaration#edgeMethodType methodType} edge.
	 * @param node The new end point of the methodType edge.
	 */
	public void setMethodType(MethodType node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.MethodDeclaration#edgeOverrides overrides} edges.
	 * @return Returns an iterator for the overrides edges.
	 */
	public EdgeIterator<MethodDeclaration> getOverridesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.MethodDeclaration#edgeOverrides overrides} edges or not.
	 * @return Returns true if the node doesn't have any overrides edge.
	 */
	public boolean getOverridesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.MethodDeclaration#edgeOverrides overrides} edges the node has.
	 * @return Returns with the number of overrides edges.
	 */
	public int getOverridesSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.MethodDeclaration#edgeOverrides overrides} edge to the node.
	 * @param id The end point of the new overrides edge.
	 */
	public void addOverrides(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.MethodDeclaration#edgeOverrides overrides} edge to the node.
	 * @param node The end point of the new overrides edge.
	 */
	public void addOverrides(MethodDeclaration node);

}

