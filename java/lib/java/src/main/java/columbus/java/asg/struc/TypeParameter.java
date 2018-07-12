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
import columbus.java.asg.base.Positioned;
import columbus.java.asg.base.Named;

/**
 * Interface TypeParameter, which represents the {@link columbus.java.asg.struc.TypeParameter TypeParameter} node.
 * @columbus.node (missing)
 * @columbus.edge hasBounds ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, multiple) : (missing)
 */
public interface TypeParameter extends Positioned, Named {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.TypeParameter#edgeHasBounds hasBounds} edges.
	 * @return Returns an iterator for the hasBounds edges.
	 */
	public EdgeIterator<TypeExpression> getBoundsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.TypeParameter#edgeHasBounds hasBounds} edges or not.
	 * @return Returns true if the node doesn't have any hasBounds edge.
	 */
	public boolean getBoundsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.TypeParameter#edgeHasBounds hasBounds} edges the node has.
	 * @return Returns with the number of hasBounds edges.
	 */
	public int getBoundsSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.TypeParameter#edgeHasBounds hasBounds} edge to the node.
	 * @param id The end point of the new hasBounds edge.
	 */
	public void addBounds(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.TypeParameter#edgeHasBounds hasBounds} edge to the node.
	 * @param node The end point of the new hasBounds edge.
	 */
	public void addBounds(TypeExpression node);

}

