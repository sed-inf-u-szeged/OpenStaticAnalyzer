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
import columbus.java.asg.expr.Expression;
import columbus.java.asg.module.ModuleDirective;
import columbus.java.asg.type.ModuleType;
import columbus.java.asg.base.Positioned;
import columbus.java.asg.enums.*;

/**
 * Interface ModuleDeclaration, which represents the {@link columbus.java.asg.struc.ModuleDeclaration ModuleDeclaration} node.
 * @columbus.node (missing)
 * @columbus.attr moduleKind ({@link columbus.java.asg.enums.ModuleKind ModuleKind}) : (missing)
 * @columbus.edge hasName ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge hasDirectives ({@link columbus.java.asg.module.ModuleDirective ModuleDirective}, multiple) : (missing)
 * @columbus.edge moduleType ({@link columbus.java.asg.type.ModuleType ModuleType}, single) : (missing)
 * @columbus.edge refersTo ({@link columbus.java.asg.struc.Module Module}, single) : (missing)
 */
public interface ModuleDeclaration extends Positioned {

	/**
	 * Gives back the {@link columbus.java.asg.struc.ModuleDeclaration#attributeModuleKind moduleKind} of the node.
	 * @return Returns with the moduleKind.
	 */
	public ModuleKind getModuleKind();

	/**
	 * Sets the {@link columbus.java.asg.struc.ModuleDeclaration#attributeModuleKind moduleKind} of the node.
	 * @param value The new value of the moduleKind.
	 */
	public void setModuleKind(ModuleKind value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasName hasName} edge points to.
	 * @return Returns the end point of the hasName edge.
	 */
	public Expression getName();

	/**
	 * Sets the {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasName hasName} edge.
	 * @param id The new end point of the hasName edge.
	 */
	public void setName(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasName hasName} edge.
	 * @param node The new end point of the hasName edge.
	 */
	public void setName(Expression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasDirectives hasDirectives} edges.
	 * @return Returns an iterator for the hasDirectives edges.
	 */
	public EdgeIterator<ModuleDirective> getDirectivesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasDirectives hasDirectives} edges or not.
	 * @return Returns true if the node doesn't have any hasDirectives edge.
	 */
	public boolean getDirectivesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasDirectives hasDirectives} edges the node has.
	 * @return Returns with the number of hasDirectives edges.
	 */
	public int getDirectivesSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasDirectives hasDirectives} edge to the node.
	 * @param id The end point of the new hasDirectives edge.
	 */
	public void addDirectives(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.ModuleDeclaration#edgeHasDirectives hasDirectives} edge to the node.
	 * @param node The end point of the new hasDirectives edge.
	 */
	public void addDirectives(ModuleDirective node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.ModuleDeclaration#edgeModuleType moduleType} edge points to.
	 * @return Returns the end point of the moduleType edge.
	 */
	public ModuleType getModuleType();

	/**
	 * Sets the {@link columbus.java.asg.struc.ModuleDeclaration#edgeModuleType moduleType} edge.
	 * @param id The new end point of the moduleType edge.
	 */
	public void setModuleType(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.ModuleDeclaration#edgeModuleType moduleType} edge.
	 * @param node The new end point of the moduleType edge.
	 */
	public void setModuleType(ModuleType node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.ModuleDeclaration#edgeRefersTo refersTo} edge points to.
	 * @return Returns the end point of the refersTo edge.
	 */
	public Module getRefersTo();

	/**
	 * Sets the {@link columbus.java.asg.struc.ModuleDeclaration#edgeRefersTo refersTo} edge.
	 * @param id The new end point of the refersTo edge.
	 */
	public void setRefersTo(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.ModuleDeclaration#edgeRefersTo refersTo} edge.
	 * @param node The new end point of the refersTo edge.
	 */
	public void setRefersTo(Module node);

}

