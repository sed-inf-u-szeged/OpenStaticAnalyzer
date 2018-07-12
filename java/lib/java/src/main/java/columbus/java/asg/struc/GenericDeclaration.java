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
import columbus.java.asg.base.Base;

/**
 * Interface GenericDeclaration, which represents the {@link columbus.java.asg.struc.GenericDeclaration GenericDeclaration} node.
 * @columbus.node (missing)
 * @columbus.edge hasTypeParameters ({@link columbus.java.asg.struc.TypeParameter TypeParameter}, multiple) : (missing)
 */
public interface GenericDeclaration extends Base {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.GenericDeclaration#edgeHasTypeParameters hasTypeParameters} edges.
	 * @return Returns an iterator for the hasTypeParameters edges.
	 */
	public EdgeIterator<TypeParameter> getTypeParametersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.GenericDeclaration#edgeHasTypeParameters hasTypeParameters} edges or not.
	 * @return Returns true if the node doesn't have any hasTypeParameters edge.
	 */
	public boolean getTypeParametersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.GenericDeclaration#edgeHasTypeParameters hasTypeParameters} edges the node has.
	 * @return Returns with the number of hasTypeParameters edges.
	 */
	public int getTypeParametersSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.GenericDeclaration#edgeHasTypeParameters hasTypeParameters} edge to the node.
	 * @param id The end point of the new hasTypeParameters edge.
	 */
	public void addTypeParameters(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.GenericDeclaration#edgeHasTypeParameters hasTypeParameters} edge to the node.
	 * @param node The end point of the new hasTypeParameters edge.
	 */
	public void addTypeParameters(TypeParameter node);

}

