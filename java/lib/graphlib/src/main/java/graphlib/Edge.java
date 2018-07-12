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

package graphlib;

import java.util.HashSet;

/**
 * The edge between the nodes.
 *
 */
public class Edge extends AttributeOwner {


	public static class EdgeTypeSet extends HashSet<EdgeType> {

		private static final long serialVersionUID = 3655474231108644180L;
	}

	private final Node fromNode;
	private final Node toNode;
	private final EdgeType type;
	private Graph graph;

	Edge(Node fromNode, Node toNode, EdgeType type) {
		super();
		this.fromNode = fromNode;
		this.toNode = toNode;
		this.type = type;
	}

	public Node getFromNode() {
		return fromNode;
	}

	public Node getToNode() {
		return toNode;
	}

	void setGraph(Graph graph) {
		this.graph = graph;
	}

	public String getName() {
		final String A = getFromNode().getUID();
		final String B = getToNode().getUID();
		switch (type.getDirectionType()) {
		case edtBidirectional: {
			return A + getType().getType() + B;
		}
		case edtDirectional: {
			return A + getType().getType() + B;
		}
		case edtReverse: {
			return B + getType().getType() + A;
		}
		default:
			return "";
		}
	}

	public EdgeType getType() {
		return type;
	}

	/**
	 * If the type of the edge is edtDirectional and it has a reverse pair, it will return the reverse pair.
	 * Otherwise it will return null.
	 */
	public Edge getReversePair() {
		return graph.getReversePair(this);
	}

	public static enum eDirectionType {
		/**
		 * it has one edge to each directions
		 */
		edtBidirectional,
		/**
		 * it has one edge to one direction
		 */		
		edtDirectional,
		/**
		 *  it belongs to a directional edge
		 */		
		edtReverse
	};

	public static class EdgeType {

		String type; // type of the edge

		eDirectionType direction; // direction of the edge

		/**
		 * Creates empty EdgeType object
		 */
		protected EdgeType() {
		}

		/**
		 * Creates EdgeType object
		 */
		protected EdgeType(String type, int dtype) {
			this.type = type;
			this.direction = eDirectionType.values()[dtype];
		}

		/**
		 * Creates EdgeType object
		 */
		public EdgeType(String type, eDirectionType dtype) {
			this.type = type;
			this.direction = dtype;
		}

		/**
		 * Gives back the type name of edge
		 */
		public String getType() {
			return this.type;
		}

		/**
		 * Gives back the direction of the edge
		 */
		public eDirectionType getDirectionType() {
			return this.direction;
		}

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + ((direction == null) ? 0 : direction.hashCode());
			result = prime * result + ((type == null) ? 0 : type.hashCode());
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			EdgeType other = (EdgeType) obj;
			if (direction != other.direction)
				return false;
			if (type == null) {
				if (other.type != null)
					return false;
			} else if (!type.equals(other.type))
				return false;
			return true;
		}
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = super.hashCode();
		result = prime * result	+ ((fromNode == null) ? 0 : fromNode.getUID().hashCode());
		result = prime * result + ((toNode == null) ? 0 : toNode.getUID().hashCode());
		result = prime * result + ((type == null) ? 0 : type.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!super.equals(obj))
			return false;
		if (getClass() != obj.getClass())
			return false;
		Edge other = (Edge) obj;
		if (fromNode == null) {
			if (other.fromNode.getUID() != null)
				return false;
		} else if (!fromNode.getUID().equals(other.fromNode.getUID()))
			return false;
		if (toNode == null) {
			if (other.toNode != null)
				return false;
		} else if (!toNode.getUID().equals(other.toNode.getUID()))
			return false;
		if (type == null) {
			if (other.type != null)
				return false;
		} else if (!type.equals(other.type))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Edge [fromNode=" + fromNode.getUID() + ", toNode=" + toNode.getUID() + ", type=" + type + "]";
	}

}
