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
import columbus.java.asg.expr.TypeExpression;
import columbus.java.asg.base.Positioned;

/**
 * Interface TypeDeclaration, which represents the {@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration} node.
 * @columbus.node (missing)
 * @columbus.attr typeNamePosition (Range) : (missing)
 * @columbus.attr isAbstract (boolean) : (missing)
 * @columbus.attr abstractPosition (Range) : (missing)
 * @columbus.attr isStrictfp (boolean) : (missing)
 * @columbus.attr strictfpPosition (Range) : (missing)
 * @columbus.attr binaryName (String) : (missing)
 * @columbus.attr extendsPosition (Range) : (missing)
 * @columbus.attr implementsPosition (Range) : (missing)
 * @columbus.attr bodyStartPosition (Range) : (missing)
 * @columbus.edge isInCompilationUnit ({@link columbus.java.asg.struc.CompilationUnit CompilationUnit}, single) : (missing)
 * @columbus.edge hasSuperClass ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 * @columbus.edge hasSuperInterfaces ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, multiple) : (missing)
 * @columbus.edge hasOthers ({@link columbus.java.asg.base.Positioned Positioned}, multiple) : (missing)
 */
public interface TypeDeclaration extends NamedDeclaration, Scope {

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeTypeNamePosition typeNamePosition} of the node.
	 * @return Returns with the typeNamePosition.
	 */
	public Range getTypeNamePosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeTypeNamePosition typeNamePosition} of the node.
	 * @param value The new value of the typeNamePosition.
	 */
	public void setTypeNamePosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeIsAbstract isAbstract} of the node.
	 * @return Returns with the isAbstract.
	 */
	public boolean getIsAbstract();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeIsAbstract isAbstract} of the node.
	 * @param value The new value of the isAbstract.
	 */
	public void setIsAbstract(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeAbstractPosition abstractPosition} of the node.
	 * @return Returns with the abstractPosition.
	 */
	public Range getAbstractPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeAbstractPosition abstractPosition} of the node.
	 * @param value The new value of the abstractPosition.
	 */
	public void setAbstractPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeIsStrictfp isStrictfp} of the node.
	 * @return Returns with the isStrictfp.
	 */
	public boolean getIsStrictfp();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeIsStrictfp isStrictfp} of the node.
	 * @param value The new value of the isStrictfp.
	 */
	public void setIsStrictfp(boolean value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeStrictfpPosition strictfpPosition} of the node.
	 * @return Returns with the strictfpPosition.
	 */
	public Range getStrictfpPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeStrictfpPosition strictfpPosition} of the node.
	 * @param value The new value of the strictfpPosition.
	 */
	public void setStrictfpPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeBinaryName binaryName} of the node.
	 * @return Returns with the binaryName.
	 */
	public String getBinaryName();

	/**
	 * Gives back the Key of {@link columbus.java.asg.struc.TypeDeclaration#attributeBinaryName binaryName} of the node.
	 * @return Returns with the Key of the binaryName.
	 */
	public int getBinaryNameKey();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeBinaryName binaryName} of the node.
	 * @param value The new value of the binaryName.
	 */
	public void setBinaryName(String value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeExtendsPosition extendsPosition} of the node.
	 * @return Returns with the extendsPosition.
	 */
	public Range getExtendsPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeExtendsPosition extendsPosition} of the node.
	 * @param value The new value of the extendsPosition.
	 */
	public void setExtendsPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeImplementsPosition implementsPosition} of the node.
	 * @return Returns with the implementsPosition.
	 */
	public Range getImplementsPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeImplementsPosition implementsPosition} of the node.
	 * @param value The new value of the implementsPosition.
	 */
	public void setImplementsPosition(Range value);

	/**
	 * Gives back the {@link columbus.java.asg.struc.TypeDeclaration#attributeBodyStartPosition bodyStartPosition} of the node.
	 * @return Returns with the bodyStartPosition.
	 */
	public Range getBodyStartPosition();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#attributeBodyStartPosition bodyStartPosition} of the node.
	 * @param value The new value of the bodyStartPosition.
	 */
	public void setBodyStartPosition(Range value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.TypeDeclaration#edgeIsInCompilationUnit isInCompilationUnit} edge points to.
	 * @return Returns the end point of the isInCompilationUnit edge.
	 */
	public CompilationUnit getIsInCompilationUnit();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#edgeIsInCompilationUnit isInCompilationUnit} edge.
	 * @param id The new end point of the isInCompilationUnit edge.
	 */
	public void setIsInCompilationUnit(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#edgeIsInCompilationUnit isInCompilationUnit} edge.
	 * @param node The new end point of the isInCompilationUnit edge.
	 */
	public void setIsInCompilationUnit(CompilationUnit node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperClass hasSuperClass} edge points to.
	 * @return Returns the end point of the hasSuperClass edge.
	 */
	public TypeExpression getSuperClass();

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperClass hasSuperClass} edge.
	 * @param id The new end point of the hasSuperClass edge.
	 */
	public void setSuperClass(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperClass hasSuperClass} edge.
	 * @param node The new end point of the hasSuperClass edge.
	 */
	public void setSuperClass(TypeExpression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperInterfaces hasSuperInterfaces} edges.
	 * @return Returns an iterator for the hasSuperInterfaces edges.
	 */
	public EdgeIterator<TypeExpression> getSuperInterfacesIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperInterfaces hasSuperInterfaces} edges or not.
	 * @return Returns true if the node doesn't have any hasSuperInterfaces edge.
	 */
	public boolean getSuperInterfacesIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperInterfaces hasSuperInterfaces} edges the node has.
	 * @return Returns with the number of hasSuperInterfaces edges.
	 */
	public int getSuperInterfacesSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperInterfaces hasSuperInterfaces} edge to the node.
	 * @param id The end point of the new hasSuperInterfaces edge.
	 */
	public void addSuperInterfaces(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.TypeDeclaration#edgeHasSuperInterfaces hasSuperInterfaces} edge to the node.
	 * @param node The end point of the new hasSuperInterfaces edge.
	 */
	public void addSuperInterfaces(TypeExpression node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.TypeDeclaration#edgeHasOthers hasOthers} edges.
	 * @return Returns an iterator for the hasOthers edges.
	 */
	public EdgeIterator<Positioned> getOthersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.TypeDeclaration#edgeHasOthers hasOthers} edges or not.
	 * @return Returns true if the node doesn't have any hasOthers edge.
	 */
	public boolean getOthersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.TypeDeclaration#edgeHasOthers hasOthers} edges the node has.
	 * @return Returns with the number of hasOthers edges.
	 */
	public int getOthersSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.TypeDeclaration#edgeHasOthers hasOthers} edge to the node.
	 * @param id The end point of the new hasOthers edge.
	 */
	public void addOthers(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.TypeDeclaration#edgeHasOthers hasOthers} edge to the node.
	 * @param node The end point of the new hasOthers edge.
	 */
	public void addOthers(Positioned node);

}

