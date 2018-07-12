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
 * Interface ScopedType, which represents the {@link columbus.java.asg.type.ScopedType ScopedType} node.
 * @columbus.node (missing)
 * @columbus.edge owner ({@link columbus.java.asg.type.Type Type}, single) : (missing)
 */
public interface ScopedType extends Type {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.type.ScopedType#edgeOwner owner} edge points to.
	 * @return Returns the end point of the owner edge.
	 */
	public Type getOwner();

	/**
	 * Sets the {@link columbus.java.asg.type.ScopedType#edgeOwner owner} edge.
	 * @param id The new end point of the owner edge.
	 */
	public void setOwner(int id);

	/**
	 * Sets the {@link columbus.java.asg.type.ScopedType#edgeOwner owner} edge.
	 * @param node The new end point of the owner edge.
	 */
	public void setOwner(Type node);

}

