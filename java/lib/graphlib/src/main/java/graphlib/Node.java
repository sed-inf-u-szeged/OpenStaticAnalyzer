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

package graphlib;


import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;

public class Node extends AttributeOwner {

	class NodeTypeSet extends HashSet<NodeType> {
		private static final long serialVersionUID = 7379373638545944057L;
	}

	private final String UID;
	private NodeType type;
	private final List<Edge> edges = new LinkedList<Edge>();

	void addEdge(Edge edge) {
		edges.add(edge);
	}

	void deleteEdge(Edge edge) {
		edges.remove(edge);
	}

	public Node(String UID, NodeType nodeType) {
		super();
		this.type = nodeType;
		this.UID = UID;
	}

	public Node() {
		UID = null;
	}

	public NodeType getType() {
		return type;
	}

	void setType(NodeType nodeType) {
		this.type = nodeType;
	}

	public String getUID() {
		return UID;
	}

	public static class NodeType {

		private String type;

		/**
		 * Create empty NodeType
		 */
		protected NodeType() {

		}

		public NodeType(String type) {
			this.type = type;
		}

		public String getType() {
			return type;
		}

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
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
			NodeType other = (NodeType) obj;
			if (type == null) {
				if (other.type != null)
					return false;
			} else if (!type.equals(other.type))
				return false;
			return true;
		}

	}


	/**
	 * It returns every out edge of the graph in a List.
	 * 
	 * @return Out edges of the node.
	 */
	public List<Edge> getOutEdges() {
		List<Edge> ret = new ArrayList<Edge>();
		for (Edge edge : edges) {
			ret.add(edge);
		}
		return ret;
	}

	/**
	 * It returns every out edge of the graph in a List with the given EdgeType.
	 * 
	 * @param type Type of the outedges we would like to find.
	 * @return Out edges of the node with the given type.
	 */
	public List<Edge> findOutEdges(Edge.EdgeType type) {
		List<Edge> ret = new ArrayList<Edge>();
		for (Edge edge : edges) {
			if (edge.getType().equals(type)) {
				ret.add(edge);
			}
		}
		return ret;
	}

	/**
	 * It returns every outedge of the graph in a List with the given types.
	 * 
	 * @param typeset Types of the outedges we would like to find.
	 * @return Out edges of the node with the given type.
	 */
	public List<Edge> findOutEdges(Edge.EdgeTypeSet typeset) {
		List<Edge> ret = new ArrayList<Edge>();
		for (Edge edge : edges) {
			if (typeset.contains(edge.getType())) {
				ret.add(edge);
			}
		}
		return ret;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = super.hashCode();
		result = prime * result + ((UID == null) ? 0 : UID.hashCode());
		result = prime * result + ((edges == null) ? 0 : edges.hashCode());
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
		Node other = (Node) obj;
		if (UID == null) {
			if (other.UID != null)
				return false;
		} else if (!UID.equals(other.UID))
			return false;
		if (edges == null) {
			if (other.edges != null)
				return false;
		} else if (!edges.equals(other.edges))
			return false;
		if (type == null) {
			if (other.type != null)
				return false;
		} else if (!type.equals(other.type))
			return false;
		return true;
	}

}
