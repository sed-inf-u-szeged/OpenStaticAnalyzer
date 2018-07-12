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

package columbus.java.asg.type;


/**
 * Interface ArrayType, which represents the {@link columbus.java.asg.type.ArrayType ArrayType} node.
 * @columbus.node (missing)
 * @columbus.attr size (int) : (missing)
 * @columbus.edge componentType ({@link columbus.java.asg.type.Type Type}, single) : (missing)
 */
public interface ArrayType extends Type {

	/**
	 * Gives back the {@link columbus.java.asg.type.ArrayType#attributeSize size} of the node.
	 * @return Returns with the size.
	 */
	public int getSize();

	/**
	 * Sets the {@link columbus.java.asg.type.ArrayType#attributeSize size} of the node.
	 * @param value The new value of the size.
	 */
	public void setSize(int value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.type.ArrayType#edgeComponentType componentType} edge points to.
	 * @return Returns the end point of the componentType edge.
	 */
	public Type getComponentType();

	/**
	 * Sets the {@link columbus.java.asg.type.ArrayType#edgeComponentType componentType} edge.
	 * @param id The new end point of the componentType edge.
	 */
	public void setComponentType(int id);

	/**
	 * Sets the {@link columbus.java.asg.type.ArrayType#edgeComponentType componentType} edge.
	 * @param node The new end point of the componentType edge.
	 */
	public void setComponentType(Type node);

}

