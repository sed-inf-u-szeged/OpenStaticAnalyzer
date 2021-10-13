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
import columbus.java.asg.base.Named;

/**
 * Interface Package, which represents the {@link columbus.java.asg.struc.Package Package} node.
 * @columbus.node (missing)
 * @columbus.attr qualifiedName (String) : (missing)
 * @columbus.edge hasCompilationUnits ({@link columbus.java.asg.struc.CompilationUnit CompilationUnit}, multiple) : (missing)
 * @columbus.edge isInModule ({@link columbus.java.asg.struc.Module Module}, multiple) : (missing)
 */
public interface Package extends Named, Scope {

	/**
	 * Gives back the {@link columbus.java.asg.struc.Package#attributeQualifiedName qualifiedName} of the node.
	 * @return Returns with the qualifiedName.
	 */
	public String getQualifiedName();

	/**
	 * Gives back the Key of {@link columbus.java.asg.struc.Package#attributeQualifiedName qualifiedName} of the node.
	 * @return Returns with the Key of the qualifiedName.
	 */
	public int getQualifiedNameKey();

	/**
	 * Sets the {@link columbus.java.asg.struc.Package#attributeQualifiedName qualifiedName} of the node.
	 * @param value The new value of the qualifiedName.
	 */
	public void setQualifiedName(String value);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.Package#edgeHasCompilationUnits hasCompilationUnits} edges.
	 * @return Returns an iterator for the hasCompilationUnits edges.
	 */
	public EdgeIterator<CompilationUnit> getCompilationUnitsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.Package#edgeHasCompilationUnits hasCompilationUnits} edges or not.
	 * @return Returns true if the node doesn't have any hasCompilationUnits edge.
	 */
	public boolean getCompilationUnitsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.Package#edgeHasCompilationUnits hasCompilationUnits} edges the node has.
	 * @return Returns with the number of hasCompilationUnits edges.
	 */
	public int getCompilationUnitsSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.Package#edgeHasCompilationUnits hasCompilationUnits} edge to the node.
	 * @param id The end point of the new hasCompilationUnits edge.
	 */
	public void addCompilationUnits(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.Package#edgeHasCompilationUnits hasCompilationUnits} edge to the node.
	 * @param node The end point of the new hasCompilationUnits edge.
	 */
	public void addCompilationUnits(CompilationUnit node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.Package#edgeIsInModule isInModule} edges.
	 * @return Returns an iterator for the isInModule edges.
	 */
	public EdgeIterator<Module> getIsInModuleIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.Package#edgeIsInModule isInModule} edges or not.
	 * @return Returns true if the node doesn't have any isInModule edge.
	 */
	public boolean getIsInModuleIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.Package#edgeIsInModule isInModule} edges the node has.
	 * @return Returns with the number of isInModule edges.
	 */
	public int getIsInModuleSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.Package#edgeIsInModule isInModule} edge to the node.
	 * @param id The end point of the new isInModule edge.
	 */
	public void addIsInModule(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.Package#edgeIsInModule isInModule} edge to the node.
	 * @param node The end point of the new isInModule edge.
	 */
	public void addIsInModule(Module node);

}

