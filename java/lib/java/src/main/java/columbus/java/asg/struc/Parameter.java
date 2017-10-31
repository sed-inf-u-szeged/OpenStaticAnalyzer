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

package columbus.java.asg.struc;

import columbus.java.asg.*;

/**
 * Interface Parameter, which represents the {@link columbus.java.asg.struc.Parameter Parameter} node.
 * @columbus.node (missing)
 * @columbus.attr isVarargs (boolean) : (missing)
 * @columbus.attr varargsPosition (Range) : (missing)
 */
public interface Parameter extends VariableDeclaration {

	/**
	 * Gives back the {@link columbus.java.asg.struc.Parameter#attributeIsVarargs isVarargs} of the node.
	 * @return Returns with the isVarargs.
	 */
	public boolean getIsVarargs();

	/**
	 * Sets the {@link columbus.java.asg.struc.Parameter#attributeIsVarargs isVarargs} of the node.
	 * @param value The new value of the isVarargs.
	 */
	public void setIsVarargs(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.Parameter#attributeVarargsPosition varargsPosition} of the node.
	 * @return Returns with the varargsPosition.
	 */
	public Range getVarargsPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.Parameter#attributeVarargsPosition varargsPosition} of the node.
	 * @param value The new value of the varargsPosition.
	 */
	public void setVarargsPosition(Range value);

}

