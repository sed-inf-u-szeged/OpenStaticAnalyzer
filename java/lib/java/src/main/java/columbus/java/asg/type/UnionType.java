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
 * Interface UnionType, which represents the {@link columbus.java.asg.type.UnionType UnionType} node.
 * @columbus.node (missing)
 * @columbus.edge alternatives ({@link columbus.java.asg.type.Type Type}, multiple) : (missing)
 */
public interface UnionType extends Type {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.type.UnionType#edgeAlternatives alternatives} edges.
	 * @return Returns an iterator for the alternatives edges.
	 */
	public EdgeIterator<Type> getAlternativesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.type.UnionType#edgeAlternatives alternatives} edges or not.
	 * @return Returns true if the node doesn't have any alternatives edge.
	 */
	public boolean getAlternativesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.type.UnionType#edgeAlternatives alternatives} edges the node has.
	 * @return Returns with the number of alternatives edges.
	 */
	public int getAlternativesSize();

	/**
	 * Adds a new {@link columbus.java.asg.type.UnionType#edgeAlternatives alternatives} edge to the node.
	 * @param id The end point of the new alternatives edge.
	 */
	public void addAlternatives(int id);

	/**
	 * Adds a new {@link columbus.java.asg.type.UnionType#edgeAlternatives alternatives} edge to the node.
	 * @param node The end point of the new alternatives edge.
	 */
	public void addAlternatives(Type node);

}

