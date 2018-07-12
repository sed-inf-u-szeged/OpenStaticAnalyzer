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
import columbus.java.asg.base.Positioned;
import columbus.java.asg.base.PositionedWithoutComment;
import columbus.java.asg.base.Commentable;

/**
 * Interface CompilationUnit, which represents the {@link columbus.java.asg.struc.CompilationUnit CompilationUnit} node.
 * @columbus.node (missing)
 * @columbus.attr fileEncoding (String) : (missing)
 * @columbus.edge hasPackageDeclaration ({@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration}, single) : (missing)
 * @columbus.edge hasImports ({@link columbus.java.asg.struc.Import Import}, multiple) : (missing)
 * @columbus.edge typeDeclarations ({@link columbus.java.asg.struc.TypeDeclaration TypeDeclaration}, multiple) : (missing)
 * @columbus.edge hasOthers ({@link columbus.java.asg.base.Positioned Positioned}, multiple) : (missing)
 */
public interface CompilationUnit extends PositionedWithoutComment, Commentable {

	/**
	 * Gives back the {@link columbus.java.asg.struc.CompilationUnit#attributeFileEncoding fileEncoding} of the node.
	 * @return Returns with the fileEncoding.
	 */
	public String getFileEncoding();

	/**
	 * Gives back the Key of {@link columbus.java.asg.struc.CompilationUnit#attributeFileEncoding fileEncoding} of the node.
	 * @return Returns with the Key of the fileEncoding.
	 */
	public int getFileEncodingKey();

	/**
	 * Sets the {@link columbus.java.asg.struc.CompilationUnit#attributeFileEncoding fileEncoding} of the node.
	 * @param value The new value of the fileEncoding.
	 */
	public void setFileEncoding(String value);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.CompilationUnit#edgeHasPackageDeclaration hasPackageDeclaration} edge points to.
	 * @return Returns the end point of the hasPackageDeclaration edge.
	 */
	public PackageDeclaration getPackageDeclaration();

	/**
	 * Sets the {@link columbus.java.asg.struc.CompilationUnit#edgeHasPackageDeclaration hasPackageDeclaration} edge.
	 * @param id The new end point of the hasPackageDeclaration edge.
	 */
	public void setPackageDeclaration(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.CompilationUnit#edgeHasPackageDeclaration hasPackageDeclaration} edge.
	 * @param node The new end point of the hasPackageDeclaration edge.
	 */
	public void setPackageDeclaration(PackageDeclaration node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.CompilationUnit#edgeHasImports hasImports} edges.
	 * @return Returns an iterator for the hasImports edges.
	 */
	public EdgeIterator<Import> getImportsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.CompilationUnit#edgeHasImports hasImports} edges or not.
	 * @return Returns true if the node doesn't have any hasImports edge.
	 */
	public boolean getImportsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.CompilationUnit#edgeHasImports hasImports} edges the node has.
	 * @return Returns with the number of hasImports edges.
	 */
	public int getImportsSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.CompilationUnit#edgeHasImports hasImports} edge to the node.
	 * @param id The end point of the new hasImports edge.
	 */
	public void addImports(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.CompilationUnit#edgeHasImports hasImports} edge to the node.
	 * @param node The end point of the new hasImports edge.
	 */
	public void addImports(Import node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.CompilationUnit#edgeTypeDeclarations typeDeclarations} edges.
	 * @return Returns an iterator for the typeDeclarations edges.
	 */
	public EdgeIterator<TypeDeclaration> getTypeDeclarationsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.CompilationUnit#edgeTypeDeclarations typeDeclarations} edges or not.
	 * @return Returns true if the node doesn't have any typeDeclarations edge.
	 */
	public boolean getTypeDeclarationsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.CompilationUnit#edgeTypeDeclarations typeDeclarations} edges the node has.
	 * @return Returns with the number of typeDeclarations edges.
	 */
	public int getTypeDeclarationsSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.CompilationUnit#edgeTypeDeclarations typeDeclarations} edge to the node.
	 * @param id The end point of the new typeDeclarations edge.
	 */
	public void addTypeDeclarations(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.CompilationUnit#edgeTypeDeclarations typeDeclarations} edge to the node.
	 * @param node The end point of the new typeDeclarations edge.
	 */
	public void addTypeDeclarations(TypeDeclaration node);

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.CompilationUnit#edgeHasOthers hasOthers} edges.
	 * @return Returns an iterator for the hasOthers edges.
	 */
	public EdgeIterator<Positioned> getOthersIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.CompilationUnit#edgeHasOthers hasOthers} edges or not.
	 * @return Returns true if the node doesn't have any hasOthers edge.
	 */
	public boolean getOthersIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.CompilationUnit#edgeHasOthers hasOthers} edges the node has.
	 * @return Returns with the number of hasOthers edges.
	 */
	public int getOthersSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.CompilationUnit#edgeHasOthers hasOthers} edge to the node.
	 * @param id The end point of the new hasOthers edge.
	 */
	public void addOthers(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.CompilationUnit#edgeHasOthers hasOthers} edge to the node.
	 * @param node The end point of the new hasOthers edge.
	 */
	public void addOthers(Positioned node);

}

