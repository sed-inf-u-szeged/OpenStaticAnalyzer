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

package columbus.java.asg.type;

import columbus.java.asg.*;

/**
 * Interface ParameterizedType, which represents the {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node.
 * @columbus.node (missing)
 * @columbus.edge rawType ({@link columbus.java.asg.type.Type Type}, single) : (missing)
 * @columbus.edge argumentTypes ({@link columbus.java.asg.type.Type Type}, multiple) : (missing)
 */
public interface ParameterizedType extends ScopedType {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.type.ParameterizedType#edgeRawType rawType} edge points to.
	 * @return Returns the end point of the rawType edge.
	 */
	public Type getRawType();

	/**
	 * Sets the {@link columbus.java.asg.type.ParameterizedType#edgeRawType rawType} edge.
	 * @param id The new end point of the rawType edge.
	 */
	public void setRawType(int id);

	/**
	 * Sets the {@link columbus.java.asg.type.ParameterizedType#edgeRawType rawType} edge.
	 * @param node The new end point of the rawType edge.
	 */
	public void setRawType(Type node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.type.ParameterizedType#edgeArgumentTypes argumentTypes} edges.
	 * @return Returns an iterator for the argumentTypes edges.
	 */
	public EdgeIterator<Type> getArgumentTypesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.type.ParameterizedType#edgeArgumentTypes argumentTypes} edges or not.
	 * @return Returns true if the node doesn't have any argumentTypes edge.
	 */
	public boolean getArgumentTypesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.type.ParameterizedType#edgeArgumentTypes argumentTypes} edges the node has.
	 * @return Returns with the number of argumentTypes edges.
	 */
	public int getArgumentTypesSize();

	/**
	 * Adds a new {@link columbus.java.asg.type.ParameterizedType#edgeArgumentTypes argumentTypes} edge to the node.
	 * @param id The end point of the new argumentTypes edge.
	 */
	public void addArgumentTypes(int id);

	/**
	 * Adds a new {@link columbus.java.asg.type.ParameterizedType#edgeArgumentTypes argumentTypes} edge to the node.
	 * @param node The end point of the new argumentTypes edge.
	 */
	public void addArgumentTypes(Type node);

}

