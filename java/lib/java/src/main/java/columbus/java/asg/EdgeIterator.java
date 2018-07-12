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

package columbus.java.asg;

/**
 * Iterator interface, which can be used to iterate through the edges of the nodes.
 * @param <T> The base type of the nodes in this edge.
 */
public interface EdgeIterator<T> {

	/**
	 * Returns true if this list iterator has more elements when traversing the list in the forward direction.
	 * @return Returns true if the list iterator has more elements when traversing the list in the forward direction.
	 */
	boolean hasNext();

	/**
	 * Returns the next element in the list.
	 * @return Returns the next element in the list.
	 */
	T next();

}

