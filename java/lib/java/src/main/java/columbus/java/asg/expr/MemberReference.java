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
import columbus.java.asg.struc.MethodDeclaration;
import columbus.java.asg.enums.*;

/**
 * Interface MemberReference, which represents the {@link columbus.java.asg.expr.MemberReference MemberReference} node.
 * @columbus.node (missing)
 * @columbus.attr name (String) : (missing)
 * @columbus.attr mode ({@link columbus.java.asg.enums.MemberReferenceModeKind MemberReferenceModeKind}) : (missing)
 * @columbus.attr referenceKind ({@link columbus.java.asg.enums.MemberReferenceKind MemberReferenceKind}) : (missing)
 * @columbus.attr overloadKind ({@link columbus.java.asg.enums.MemberReferenceOverloadKind MemberReferenceOverloadKind}) : (missing)
 * @columbus.edge hasQualifierExpression ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasTypeArguments ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, multiple) : (missing)
 * @columbus.edge referredMethod ({@link columbus.java.asg.struc.MethodDeclaration MethodDeclaration}, single) : (missing)
 */
public interface MemberReference extends FunctionalExpression {

	/**
	 * Gives back the {@link columbus.java.asg.expr.MemberReference#attributeName name} of the node.
	 * @return Returns with the name.
	 */
	public String getName();

	/**
	 * Gives back the Key of {@link columbus.java.asg.expr.MemberReference#attributeName name} of the node.
	 * @return Returns with the Key of the name.
	 */
	public int getNameKey();

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#attributeName name} of the node.
	 * @param value The new value of the name.
	 */
	public void setName(String value);

	/**
	 * Gives back the {@link columbus.java.asg.expr.MemberReference#attributeMode mode} of the node.
	 * @return Returns with the mode.
	 */
	public MemberReferenceModeKind getMode();

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#attributeMode mode} of the node.
	 * @param value The new value of the mode.
	 */
	public void setMode(MemberReferenceModeKind value);

	/**
	 * Gives back the {@link columbus.java.asg.expr.MemberReference#attributeReferenceKind referenceKind} of the node.
	 * @return Returns with the referenceKind.
	 */
	public MemberReferenceKind getReferenceKind();

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#attributeReferenceKind referenceKind} of the node.
	 * @param value The new value of the referenceKind.
	 */
	public void setReferenceKind(MemberReferenceKind value);

	/**
	 * Gives back the {@link columbus.java.asg.expr.MemberReference#attributeOverloadKind overloadKind} of the node.
	 * @return Returns with the overloadKind.
	 */
	public MemberReferenceOverloadKind getOverloadKind();

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#attributeOverloadKind overloadKind} of the node.
	 * @param value The new value of the overloadKind.
	 */
	public void setOverloadKind(MemberReferenceOverloadKind value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.MemberReference#edgeHasQualifierExpression hasQualifierExpression} edge points to.
	 * @return Returns the end point of the hasQualifierExpression edge.
	 */
	public Expression getQualifierExpression();

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#edgeHasQualifierExpression hasQualifierExpression} edge.
	 * @param id The new end point of the hasQualifierExpression edge.
	 */
	public void setQualifierExpression(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#edgeHasQualifierExpression hasQualifierExpression} edge.
	 * @param node The new end point of the hasQualifierExpression edge.
	 */
	public void setQualifierExpression(Expression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.expr.MemberReference#edgeHasTypeArguments hasTypeArguments} edges.
	 * @return Returns an iterator for the hasTypeArguments edges.
	 */
	public EdgeIterator<TypeExpression> getTypeArgumentsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.expr.MemberReference#edgeHasTypeArguments hasTypeArguments} edges or not.
	 * @return Returns true if the node doesn't have any hasTypeArguments edge.
	 */
	public boolean getTypeArgumentsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.expr.MemberReference#edgeHasTypeArguments hasTypeArguments} edges the node has.
	 * @return Returns with the number of hasTypeArguments edges.
	 */
	public int getTypeArgumentsSize();

	/**
	 * Adds a new {@link columbus.java.asg.expr.MemberReference#edgeHasTypeArguments hasTypeArguments} edge to the node.
	 * @param id The end point of the new hasTypeArguments edge.
	 */
	public void addTypeArguments(int id);

	/**
	 * Adds a new {@link columbus.java.asg.expr.MemberReference#edgeHasTypeArguments hasTypeArguments} edge to the node.
	 * @param node The end point of the new hasTypeArguments edge.
	 */
	public void addTypeArguments(TypeExpression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.MemberReference#edgeReferredMethod referredMethod} edge points to.
	 * @return Returns the end point of the referredMethod edge.
	 */
	public MethodDeclaration getReferredMethod();

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#edgeReferredMethod referredMethod} edge.
	 * @param id The new end point of the referredMethod edge.
	 */
	public void setReferredMethod(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.MemberReference#edgeReferredMethod referredMethod} edge.
	 * @param node The new end point of the referredMethod edge.
	 */
	public void setReferredMethod(MethodDeclaration node);

}

