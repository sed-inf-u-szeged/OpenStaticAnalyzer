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
 * Interface InstanceOf, which represents the {@link columbus.java.asg.expr.InstanceOf InstanceOf} node.
 * @columbus.node (missing)
 * @columbus.edge hasTypeOperand ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 */
public interface InstanceOf extends Unary {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.expr.InstanceOf#edgeHasTypeOperand hasTypeOperand} edge points to.
	 * @return Returns the end point of the hasTypeOperand edge.
	 */
	public TypeExpression getTypeOperand();

	/**
	 * Sets the {@link columbus.java.asg.expr.InstanceOf#edgeHasTypeOperand hasTypeOperand} edge.
	 * @param id The new end point of the hasTypeOperand edge.
	 */
	public void setTypeOperand(int id);

	/**
	 * Sets the {@link columbus.java.asg.expr.InstanceOf#edgeHasTypeOperand hasTypeOperand} edge.
	 * @param node The new end point of the hasTypeOperand edge.
	 */
	public void setTypeOperand(TypeExpression node);

}

