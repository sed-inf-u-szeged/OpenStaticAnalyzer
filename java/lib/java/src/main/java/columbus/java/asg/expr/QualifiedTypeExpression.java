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


/**
 * Interface QualifiedTypeExpression, which represents the {@link columbus.java.asg.expr.QualifiedTypeExpression QualifiedTypeExpression} node.
 * @columbus.node (missing)
 * @columbus.edge hasQualifierType ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 * @columbus.edge hasSimpleType ({@link columbus.java.asg.expr.SimpleTypeExpression SimpleTypeExpression}, single) : (missing)
 */
public interface QualifiedTypeExpression extends TypeExpression {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.QualifiedTypeExpression#edgeHasQualifierType hasQualifierType} edge points to.
	 * @return Returns the end point of the hasQualifierType edge.
	 */
	public TypeExpression getQualifierType();

	/**
	 * Sets the {@link columbus.java.asg.expr.QualifiedTypeExpression#edgeHasQualifierType hasQualifierType} edge.
	 * @param id The new end point of the hasQualifierType edge.
	 */
	public void setQualifierType(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.QualifiedTypeExpression#edgeHasQualifierType hasQualifierType} edge.
	 * @param node The new end point of the hasQualifierType edge.
	 */
	public void setQualifierType(TypeExpression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.QualifiedTypeExpression#edgeHasSimpleType hasSimpleType} edge points to.
	 * @return Returns the end point of the hasSimpleType edge.
	 */
	public SimpleTypeExpression getSimpleType();

	/**
	 * Sets the {@link columbus.java.asg.expr.QualifiedTypeExpression#edgeHasSimpleType hasSimpleType} edge.
	 * @param id The new end point of the hasSimpleType edge.
	 */
	public void setSimpleType(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.QualifiedTypeExpression#edgeHasSimpleType hasSimpleType} edge.
	 * @param node The new end point of the hasSimpleType edge.
	 */
	public void setSimpleType(SimpleTypeExpression node);

}

