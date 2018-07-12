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

package columbus.java.asg.base;

import columbus.java.asg.*;

/**
 * Interface Commentable, which represents the {@link columbus.java.asg.base.Commentable Commentable} node.
 * @columbus.node (missing)
 * @columbus.edge comments ({@link columbus.java.asg.base.Comment Comment}, multiple) : (missing)
 */
public interface Commentable extends Base {

	/**
	 * Gives back iterator for the {@link columbus.java.asg.base.Commentable#edgeComments comments} edges.
	 * @return Returns an iterator for the comments edges.
	 */
	public EdgeIterator<Comment> getCommentsIterator();

	/**
	 * Tells whether the node has {@link columbus.java.asg.base.Commentable#edgeComments comments} edges or not.
	 * @return Returns true if the node doesn't have any comments edge.
	 */
	public boolean getCommentsIsEmpty();

	/**
	 * Gives back how many {@link columbus.java.asg.base.Commentable#edgeComments comments} edges the node has.
	 * @return Returns with the number of comments edges.
	 */
	public int getCommentsSize();

	/**
	 * Adds a new {@link columbus.java.asg.base.Commentable#edgeComments comments} edge to the node.
	 * @param id The end point of the new comments edge.
	 */
	public void addComments(int id);

	/**
	 * Adds a new {@link columbus.java.asg.base.Commentable#edgeComments comments} edge to the node.
	 * @param node The end point of the new comments edge.
	 */
	public void addComments(Comment node);

}

