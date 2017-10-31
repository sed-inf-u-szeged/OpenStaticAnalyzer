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

import columbus.java.asg.expr.NewClass;

/**
 * Interface EnumConstant, which represents the {@link columbus.java.asg.struc.EnumConstant EnumConstant} node.
 * @columbus.node (missing)
 * @columbus.edge hasNewClass ({@link columbus.java.asg.expr.NewClass NewClass}, single) : (missing)
 */
public interface EnumConstant extends VariableDeclaration {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.EnumConstant#edgeHasNewClass hasNewClass} edge points to.
	 * @return Returns the end point of the hasNewClass edge.
	 */
	public NewClass getNewClass();

	/**
	 * Sets the {@link columbus.java.asg.struc.EnumConstant#edgeHasNewClass hasNewClass} edge.
	 * @param id The new end point of the hasNewClass edge.
	 */
	public void setNewClass(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.EnumConstant#edgeHasNewClass hasNewClass} edge.
	 * @param node The new end point of the hasNewClass edge.
	 */
	public void setNewClass(NewClass node);

}

