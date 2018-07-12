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

import columbus.java.asg.*;

/**
 * Interface MethodType, which represents the {@link columbus.java.asg.type.MethodType MethodType} node.
 * @columbus.node (missing)
 * @columbus.edge returnType ({@link columbus.java.asg.type.Type Type}, single) : (missing)
 * @columbus.edge parameterTypes ({@link columbus.java.asg.type.Type Type}, multiple) : (missing)
 * @columbus.edge thrownTypes ({@link columbus.java.asg.type.Type Type}, multiple) : (missing)
 */
public interface MethodType extends Type {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.type.MethodType#edgeReturnType returnType} edge points to.
	 * @return Returns the end point of the returnType edge.
	 */
	public Type getReturnType();

	/**
	 * Sets the {@link columbus.java.asg.type.MethodType#edgeReturnType returnType} edge.
	 * @param id The new end point of the returnType edge.
	 */
	public void setReturnType(int id);

	/**
	 * Sets the {@link columbus.java.asg.type.MethodType#edgeReturnType returnType} edge.
	 * @param node The new end point of the returnType edge.
	 */
	public void setReturnType(Type node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.type.MethodType#edgeParameterTypes parameterTypes} edges.
	 * @return Returns an iterator for the parameterTypes edges.
	 */
	public EdgeIterator<Type> getParameterTypesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.type.MethodType#edgeParameterTypes parameterTypes} edges or not.
	 * @return Returns true if the node doesn't have any parameterTypes edge.
	 */
	public boolean getParameterTypesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.type.MethodType#edgeParameterTypes parameterTypes} edges the node has.
	 * @return Returns with the number of parameterTypes edges.
	 */
	public int getParameterTypesSize();

	/**
	 * Adds a new {@link columbus.java.asg.type.MethodType#edgeParameterTypes parameterTypes} edge to the node.
	 * @param id The end point of the new parameterTypes edge.
	 */
	public void addParameterTypes(int id);

	/**
	 * Adds a new {@link columbus.java.asg.type.MethodType#edgeParameterTypes parameterTypes} edge to the node.
	 * @param node The end point of the new parameterTypes edge.
	 */
	public void addParameterTypes(Type node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.type.MethodType#edgeThrownTypes thrownTypes} edges.
	 * @return Returns an iterator for the thrownTypes edges.
	 */
	public EdgeIterator<Type> getThrownTypesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.type.MethodType#edgeThrownTypes thrownTypes} edges or not.
	 * @return Returns true if the node doesn't have any thrownTypes edge.
	 */
	public boolean getThrownTypesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.type.MethodType#edgeThrownTypes thrownTypes} edges the node has.
	 * @return Returns with the number of thrownTypes edges.
	 */
	public int getThrownTypesSize();

	/**
	 * Adds a new {@link columbus.java.asg.type.MethodType#edgeThrownTypes thrownTypes} edge to the node.
	 * @param id The end point of the new thrownTypes edge.
	 */
	public void addThrownTypes(int id);

	/**
	 * Adds a new {@link columbus.java.asg.type.MethodType#edgeThrownTypes thrownTypes} edge to the node.
	 * @param node The end point of the new thrownTypes edge.
	 */
	public void addThrownTypes(Type node);

}

