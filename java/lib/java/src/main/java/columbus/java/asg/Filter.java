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

import columbus.IO;
import columbus.IO.IOMode;
import columbus.java.asg.algorithms.AlgorithmPreorder;
import columbus.java.asg.visitors.VisitorFilter;
import columbus.logger.LoggerHandler;

/**
 * Provides filtering mechanism.
 */
public class Filter {

	private static final LoggerHandler logger = new LoggerHandler(Filter.class, Constant.LoggerPropertyFile);
	/** Reference to the factory. */
	private Factory factory;

	/** Contains the states of the nodes. */
	private boolean[] container;

	/** Real size of the container array. */
	private int realSize;

	/**
	 * Constructor.
	 * @param factory Reference to the Factory.
	 */
	public Filter(Factory factory) {
		this.factory = factory;
		realSize = factory.size();
		container = new boolean[realSize];
	}

	/**
	 * Initializes the Filter.
	 */
	public void initializeFilter() {
		if (realSize == factory.size()) {
			for (int i = 0; i < realSize; i++)
				container[i] = false;
		} else {
			realSize = factory.size();
			container = new boolean[realSize];
		}
	}

	/**
	 * Gives back the size of the Filter.
	 * @return The size of the Filter.
	 */
	public int size() {
		return realSize;
	}

	/**
	 * Resizes the Filter to match the size of the Factory.
	 */
	public void resize() {
		realSize = factory.size();
		if (container.length >= realSize)
			return;

		int oldCapacity = container.length;
		int newCapacity = (oldCapacity * 3) / 2 + 1;
		if (newCapacity < realSize)
			newCapacity = realSize;
		boolean[] oldData = container;
		container = new boolean[newCapacity];
		System.arraycopy(oldData, 0, container, 0, oldCapacity);
	}

	/**
	 * Tells whether the node is filtered or not.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException if the id is too large (larger than the size of the Filter).
	 * @return Returns true if the node with the given id is filtered.
	 */
	public boolean getIsFiltered(int id) {
		if (realSize <= id)
			throw new JavaException(logger.formatMessage("ex.java.Filter.Invalid_id", id));
		return container[id];
	}

	/**
	 * Filters out the given node and all of its descendants.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setFiltered(int id) {
		if (Common.getIsValid(id)) {
			VisitorFilter v = new VisitorFilter();
			AlgorithmPreorder ap = new AlgorithmPreorder();
			ap.setVisitSpecialNodes(false, false);
			ap.run(factory, v, id);
		}
	}

	/**
	 * Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setNotFiltered(int id) {
		// TODO
		throw new JavaException(logger.formatMessage("ex.java.Factory.This_method_is_not_yet_supported"));
	}

	/**
	 * Filter out only the given node (without its children).
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setFilteredThisNodeOnly(int id) {
		if (realSize <= id)
			throw new JavaException(logger.formatMessage("ex.java.Filter.Invalid_id", id));
		// do not let filter the root node
		if (id == factory.getRoot().getId())
			return;
		container[id] = true;
	}

	/**
	 * Sets the state of the given node (without its children) to not filtered.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setNotFilteredThisNodeOnly(int id) {
		if (realSize <= id)
			throw new JavaException(logger.formatMessage("ex.java.Filter.Invalid_id", id));
		container[id] = false;
	}

	/**
	 * Saves the filter.
	 * @param filename Then name of the filter file.
	 */
	public void save(String filename) {
		IO io = new IO(filename, IOMode.WRITE);

		io.writeInt4(realSize);
		for (int i = 0; i < realSize; i++)
			io.writeByte1(container[i] ? 0 : (byte)1);

		io.close();
	}

	/**
	 * Loads the filter.
	 * @param filename Then name of the filter file.
	 */
	public void load(String filename) {
		IO io = new IO(filename, IOMode.READ);

		realSize = io.readInt4();
		container = new boolean[realSize];
		for (int i = 0; i < realSize; i++)
			container[i] = io.readByte1() == 0 ? true : false;

		io.close();
	}

}
