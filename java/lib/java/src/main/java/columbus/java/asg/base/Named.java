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

package columbus.java.asg.base;

import columbus.java.asg.*;

/**
 * Interface Named, which represents the {@link columbus.java.asg.base.Named Named} node.
 * @columbus.node (missing)
 * @columbus.attr name (String) : (missing)
 * @columbus.attr namePosition (Range) : (missing)
 */
public interface Named extends Base {

	/**
	 * Gives back the {@link columbus.java.asg.base.Named#attributeName name} of the node.
	 * @return Returns with the name.
	 */
	public String getName();

	/**
	 * Gives back the Key of {@link columbus.java.asg.base.Named#attributeName name} of the node.
	 * @return Returns with the Key of the name.
	 */
	public int getNameKey();

	/**
	 * Sets the {@link columbus.java.asg.base.Named#attributeName name} of the node.
	 * @param value The new value of the name.
	 */
	public void setName(String value);

	/**
	 * Gives back the {@link columbus.java.asg.base.Named#attributeNamePosition namePosition} of the node.
	 * @return Returns with the namePosition.
	 */
	public Range getNamePosition();

	/**
	 * Sets the {@link columbus.java.asg.base.Named#attributeNamePosition namePosition} of the node.
	 * @param value The new value of the namePosition.
	 */
	public void setNamePosition(Range value);

}

