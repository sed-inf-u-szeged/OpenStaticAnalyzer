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
import columbus.java.asg.expr.Annotation;
import columbus.java.asg.base.Base;

/**
 * Interface AnnotatedElement, which represents the {@link columbus.java.asg.struc.AnnotatedElement AnnotatedElement} node.
 * @columbus.node (missing)
 * @columbus.edge hasAnnotations ({@link columbus.java.asg.expr.Annotation Annotation}, multiple) : (missing)
 */
public interface AnnotatedElement extends Base {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.struc.AnnotatedElement#edgeHasAnnotations hasAnnotations} edges.
	 * @return Returns an iterator for the hasAnnotations edges.
	 */
	public EdgeIterator<Annotation> getAnnotationsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.struc.AnnotatedElement#edgeHasAnnotations hasAnnotations} edges or not.
	 * @return Returns true if the node doesn't have any hasAnnotations edge.
	 */
	public boolean getAnnotationsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.struc.AnnotatedElement#edgeHasAnnotations hasAnnotations} edges the node has.
	 * @return Returns with the number of hasAnnotations edges.
	 */
	public int getAnnotationsSize();

	/**
	 * Adds a new {@link columbus.java.asg.struc.AnnotatedElement#edgeHasAnnotations hasAnnotations} edge to the node.
	 * @param id The end point of the new hasAnnotations edge.
	 */
	public void addAnnotations(int id);

	/**
	 * Adds a new {@link columbus.java.asg.struc.AnnotatedElement#edgeHasAnnotations hasAnnotations} edge to the node.
	 * @param node The end point of the new hasAnnotations edge.
	 */
	public void addAnnotations(Annotation node);

}

