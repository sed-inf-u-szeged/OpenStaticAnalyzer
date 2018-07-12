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

import columbus.java.asg.expr.Expression;
import columbus.java.asg.base.Positioned;

/**
 * Interface PackageDeclaration, which represents the {@link columbus.java.asg.struc.PackageDeclaration PackageDeclaration} node.
 * @columbus.node (missing)
 * @columbus.edge hasPackageName ({@link columbus.java.asg.expr.Expression Expression}, single) : (missing)
 * @columbus.edge refersTo ({@link columbus.java.asg.struc.Package Package}, single) : (missing)
 */
public interface PackageDeclaration extends Positioned {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.PackageDeclaration#edgeHasPackageName hasPackageName} edge points to.
	 * @return Returns the end point of the hasPackageName edge.
	 */
	public Expression getPackageName();

	/**
	 * Sets the {@link columbus.java.asg.struc.PackageDeclaration#edgeHasPackageName hasPackageName} edge.
	 * @param id The new end point of the hasPackageName edge.
	 */
	public void setPackageName(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.PackageDeclaration#edgeHasPackageName hasPackageName} edge.
	 * @param node The new end point of the hasPackageName edge.
	 */
	public void setPackageName(Expression node);

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.PackageDeclaration#edgeRefersTo refersTo} edge points to.
	 * @return Returns the end point of the refersTo edge.
	 */
	public Package getRefersTo();

	/**
	 * Sets the {@link columbus.java.asg.struc.PackageDeclaration#edgeRefersTo refersTo} edge.
	 * @param id The new end point of the refersTo edge.
	 */
	public void setRefersTo(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.PackageDeclaration#edgeRefersTo refersTo} edge.
	 * @param node The new end point of the refersTo edge.
	 */
	public void setRefersTo(Package node);

}

