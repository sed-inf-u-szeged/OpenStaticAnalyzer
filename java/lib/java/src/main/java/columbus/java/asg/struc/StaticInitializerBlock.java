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

/**
 * Interface StaticInitializerBlock, which represents the {@link columbus.java.asg.struc.StaticInitializerBlock StaticInitializerBlock} node.
 * @columbus.node (missing)
 * @columbus.attr blockStartPosition (Range) : (missing)
 */
public interface StaticInitializerBlock extends InitializerBlock {

	/**
	 * Gives back the {@link columbus.java.asg.struc.StaticInitializerBlock#attributeBlockStartPosition blockStartPosition} of the node.
	 * @return Returns with the blockStartPosition.
	 */
	public Range getBlockStartPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.StaticInitializerBlock#attributeBlockStartPosition blockStartPosition} of the node.
	 * @param value The new value of the blockStartPosition.
	 */
	public void setBlockStartPosition(Range value);

}

