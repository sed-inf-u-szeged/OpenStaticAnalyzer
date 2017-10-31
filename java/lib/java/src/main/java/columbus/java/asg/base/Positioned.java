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


/**
 * Interface Positioned, which represents the {@link columbus.java.asg.base.Positioned Positioned} node.
 * @columbus.node (missing)
 * @columbus.attr isCompilerGenerated (boolean) : (missing)
 * @columbus.attr isToolGenerated (boolean) : (missing)
 */
public interface Positioned extends Commentable, PositionedWithoutComment {

	/**
	 * Gives back the {@link columbus.java.asg.base.Positioned#attributeIsCompilerGenerated isCompilerGenerated} of the node.
	 * @return Returns with the isCompilerGenerated.
	 */
	public boolean getIsCompilerGenerated();

	/**
	 * Sets the {@link columbus.java.asg.base.Positioned#attributeIsCompilerGenerated isCompilerGenerated} of the node.
	 * @param value The new value of the isCompilerGenerated.
	 */
	public void setIsCompilerGenerated(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.base.Positioned#attributeIsToolGenerated isToolGenerated} of the node.
	 * @return Returns with the isToolGenerated.
	 */
	public boolean getIsToolGenerated();

	/**
	 * Sets the {@link columbus.java.asg.base.Positioned#attributeIsToolGenerated isToolGenerated} of the node.
	 * @param value The new value of the isToolGenerated.
	 */
	public void setIsToolGenerated(boolean value);

}

