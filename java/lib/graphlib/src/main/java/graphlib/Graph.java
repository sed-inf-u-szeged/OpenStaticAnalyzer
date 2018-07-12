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

import graphlib.Attribute.aType;
import graphlib.Edge.EdgeType;
import graphlib.Edge.EdgeTypeSet;
import graphlib.Edge.eDirectionType;
import graphlib.Node.NodeType;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeMap;

import columbus.ColumbusException;
import columbus.IO;
import columbus.IO.IOMode;
import columbus.StrTable;
import columbus.StrTable.StrType;
import columbus.WarningMessages;

public class Graph extends AttributeOwner {

	private final Map<String, String> header = new TreeMap<String, String>();
	private final StrTable strTable = new StrTable();
	private final Map<String, Node> nodeMap = new HashMap<String, Node>();
	private final Map<String, NodeType> nodeTypeMap = new HashMap<String, NodeType>();
	private final Map<String, EdgeType> edgeTypeMap = new HashMap<String, EdgeType>();
	private final Map<Edge, Edge> edgePairMap = new HashMap<Edge, Edge>();

	/**
	 * It return true if the node is exists with given UID in the graph.
	 */
	public boolean nodeIsExist(String UID) {
		return nodeMap.containsKey(UID);
	}

	/**
	 * It creates a node with the given UID and type.
	 * It throws GraphlibException if the node is already in the graph. 
	 * @throws GraphlibException If the given UID is not found exception will be thrown.
	 */
	public Node createNode(String UID, NodeType NTYPE) throws GraphlibException { // O(log(N))
		if (nodeIsExist(UID)) {
			throw new GraphlibException(WarningMessages.NODE_ALREADY_EXIST);
		}
		Node newNode = new Node(UID, NTYPE);
		return newNode;
	}

	/**
	 * It adds the node to the graph.
	 * It throws GraphlibException if the node is already in the graph. 
	 * 
	 * @param node The node we would like to add.
	 * @return The added node.
	 * @throws GraphlibException If the given UID is already in the graph exception will be thrown.
	 */
	public Node addNode(Node node) throws GraphlibException { // O(log(N))
		if (nodeMap.containsKey(node.getUID())) {
			throw new GraphlibException(WarningMessages.NODE_ALREADY_EXIST);
		}
		return nodeMap.put(node.getUID(), node);
	}

	/**
	 * It deletes the node from the graph with the given UID.
	 * 
	 * @param UID The UID of the node we would like to delete.
	 * @return If the deletion was success it returns true, otherwise false.
	 */
	public boolean deleteNode(String UID) { // O(log(N) + E))
		Node node = nodeMap.get(UID);
		if (node == null) {
			return false;
		}
		return deleteNode(nodeMap.get(UID));
	}

	/**
	 * It deletes the node from the graph.
	 * 
	 * @param node The node we would like to delete.
	 * @return If the deletion was success it returns true, otherwise false.
	 */
	public boolean deleteNode(Node node) {
		node = nodeMap.get(node.getUID());
		if (node == null) {
			return false;
		}
		for(Edge edge : node.getOutEdges()){
			deleteNode(edge.getToNode());
		}
		nodeMap.remove(node.getUID());
		return true;
	}
	
	/**
	 * 
	 * It deletes the node from the graph with the given NodeType..
	 * 
	 * @param NTYPE The NodeType of the nodes we would like to delete.
	 * @return If the deletion was success it returns true, otherwise false.
	 */
	
	public boolean deleteNode(Node.NodeType NTYPE) {
		boolean thereWasDelete = false;
		for (Node node : getNodes()) {
			if (node.getType().equals(NTYPE)) {
				thereWasDelete = true;
				nodeMap.remove(node.getUID());
			}
		}
		return thereWasDelete;
	}

	/**
	 * It creates an edge from 'fromNode' to 'toNode' with the given type.
	 * If createReverse parameter is true it will create the reverse edge as well.
	 * 
	 * @param fromNode The from node.
	 * @param toNode The to node.
	 * @param type The type of edge.
	 * @param createReverse If it is true it will create the reverse edge as well.
	 * @return The new edge.
	 */
	public Edge createDirectedEdge(Node fromNode, Node toNode, String type, boolean createReverse) {
		if (!edgeTypeMap.containsKey(type)) {
			edgeTypeMap.put(type, new EdgeType(type, eDirectionType.edtDirectional));
		}
		Edge edge = new Edge(fromNode, toNode, edgeTypeMap.get(type));
		fromNode.addEdge(edge);
		if (createReverse) {
			Edge reverseEdge = new Edge(toNode, fromNode, new EdgeType(type, eDirectionType.edtReverse));
			toNode.addEdge(reverseEdge);
		}
		return edge;
	}

	/**
	 * It creates an edge from 'fromUID' node to 'toUID' node with the given type.
	 * If createReverse parameter is true it will create the reverse edge as well.
	 * 
	 * 
	 * @param fromUID The UID of the from node.
	 * @param toUID The UID of the to node.
	 * @param type The type of edge.
	 * @param createReverse If it is true it will create the reverse edge as well.
	 * @return The new edge.
	 */
	public Edge createDirectedEdge(String fromUID, String toUID, String type, boolean createReverse) { // O(log(N))
		return createDirectedEdge(nodeMap.get(fromUID), nodeMap.get(toUID), type, createReverse);
	}

	/**
	 * It creates an edge from 'fromNode' to 'toNode' with the given type.
	 * It also creates the reverse edge.
	 * 
	 * @param fromNode The from node.
	 * @param toNode The to node.
	 * @param type The type of edge.
	 * @return The new edge.
	 */
	public Edge createBidirectedEdge(Node fromNode, Node toNode, String type) {
		return createDirectedEdge(fromNode, toNode, type, true);
	}

	/**
	 * It creates an edge from 'fromUID' node to 'toUID' node with the given type.
	 * It also creates the reverse edge.
	 * 
	 * @param fromUID The UID of the from node.
	 * @param toUID The UID of the to node.
	 * @param type The type of edge.
	 * @return The new edge.
	 */
	public Edge createBidirectedEdge(String fromUID, String toUID, String type) { // O(log(N))
		return createBidirectedEdge(nodeMap.get(fromUID), nodeMap.get(toUID), type);
	}

	
	/**
	 * 
	 * It returns the node with the given UID.
	 * If the node not exists, it will return null.
	 * 
	 * @param UID The UID of the node would like to find.
	 * @return The node if was found, otherwise null.
	 */
	public Node findNode(String UID) { // O(log(N))
		return nodeMap.get(UID);
	}

	
	/**
	 * Returns every node with the given NodeType.
	 * 
	 * @param NTYPE The type of the node.
	 * @return The nodes with the given type.
	 */
	public List<Node> findNodes(Node.NodeType NTYPE) { // O(N)
		List<Node> nodes = new ArrayList<Node>();
		for (Node node : nodeMap.values()) {
			if (node.getType().equals(NTYPE)) {
				nodes.add(node);
			}
		}
		return nodes;
	}

	
	/**
	 * Deletes the given edge from the graph.
	 * 
	 * @param edge The edge we would like to delete.
	 */
	public void deleteEdge(Edge edge) {
		edge.getFromNode().deleteEdge(edge);
	}

	/**
	 * Deletes the edges from the graph with the given type.
	 * 
	 * @param type The type of edges we would like to delete.
	 */
	public void deleteEdge(Edge.EdgeType type) {
		for (Node node : nodeMap.values()) {
			for (Edge edge : node.findOutEdges(type)) {
				deleteEdge(edge);
			}
		}
	}

	/**
	 * Deletes the edges from the graph with the given type and direction.
	 * 
	 * @param type The type of edges we would like to delete.
	 * @param direction The direction of edges we would like to delete.
	 */
	protected void deleteEdge(String type, int direction) {
		deleteEdge(new EdgeType(type, direction));
	}

	
	/**
	 * Deletes the edges from the graph between the two nodes.
	 *  
	 * @param fromNode The from node of edges we would like to delete.
	 * @param toNode The to node of edges we would like to delete.
	 */
	public void deleteEdge(Node fromNode, Node toNode) {
		for (Edge edge : fromNode.getOutEdges()) {
			if (edge.getToNode().equals(toNode)) {
				deleteEdge(edge);
			}
		}
	}


	/**
	 * It saves the graph in binary format to the given path.
	 * 
	 * @param filename The path where we would like to save the binary graph file.
	 * @throws GraphlibException It throws exception if something went wrong during the io process.
	 */
	public void saveBinary(String filename) throws GraphlibException {
		IO io = null;
		try {
			io = new IO(filename, IOMode.WRITE);
			strTable.save(io, StrType.strDefault);

			// header
			io.writeInt4(header.size());
			for (Entry<String, String> e : header.entrySet()) {
				io.writeInt4(strTable.get(e.getKey()));
				io.writeInt4(strTable.get(e.getValue()));
			}
			// nodes
			for (Node node : nodeMap.values()) {
				io.writeInt4(strTable.get(node.getUID()));
				io.writeInt4(strTable.get(node.getType().getType()));
				io.writeInt4(node.attributes.size());
				for (Attribute att : node.getAttributes()) {
					saveAttribute(io, att);
				}

				// edges
				for (Edge edge : node.getOutEdges()) {
					if (!edge.getFromNode().getUID().equals(node.getUID())
							|| edge.getType().direction == eDirectionType.edtReverse) {
						continue;
					}

					io.writeInt4(strTable.get(edge.getType().getType()));
					io.writeInt4(edge.getType().getDirectionType().ordinal());
					io.writeInt4(strTable.get(edge.getToNode().getUID()));

					boolean pair = edgePairMap.containsKey(edge);
					io.writeBoolean1(pair);
					io.writeInt4(edge.attributes.size());
					for (Attribute att : edge.getAttributes()) {
						saveAttribute(io, att);
					}
					if (pair) {
						Edge edgePair = edgePairMap.get(edge);
						io.writeInt4(edgePair.attributes.size());
						for (Attribute att : edgePair.getAttributes()) {
							saveAttribute(io, att);
						}
					}
				}
				io.writeInt4(0);
				io.writeInt4(0);
				io.writeInt4(0);
			}
			io.writeInt4(0);
			io.writeInt4(0);
			io.close();
		} catch (ColumbusException e) {
			throw new GraphlibException(e);
		}
	}

	private void saveAttribute(IO io, Attribute attr) throws GraphlibException {
		try {
			int attrType = attr.getType().ordinal();
			io.writeInt4(attrType);
			io.writeInt4(strTable.get(attr.getName()));
			io.writeInt4(strTable.get(attr.getContext()));
			switch (attrType) {
			case 0:
				io.writeInt4(((AttributeInt) attr).getValue());
				break;
			case 1:
				io.writeFloat4(((AttributeFloat) attr).getValue());
				break;
			case 2:
				io.writeInt4(strTable.get(((AttributeString) attr).getValue()));
				break;
			case 3:
				List<Attribute> itA = attr.getAttributes();
				io.writeInt4(attr.attributes.size());
				for(Attribute att : itA) {
					saveAttribute(io, att);
				}
				break;
			default:
				break;
			}
		} catch (ColumbusException e) {
			throw new GraphlibException(e);
		}
	}

	private void loadAttributes(IO io, AttributeOwner parent) throws GraphlibException {
		try{
			int attrTypeKey = (int) io.readUInt4();
			aType type = aType.values()[attrTypeKey];

			int attrNameKey = (int) io.readUInt4();
			String name = getFromStringTable(attrNameKey);

			int contextKey = (int) io.readUInt4();
			String context = getFromStringTable(contextKey);
			
			switch (attrTypeKey) {
			case 0: {
				int value = io.readInt4();
				AttributeInt attribute = new AttributeInt(name, type, context);
				attribute.setValue(value);
				parent.addAttribute(attribute);
				break;
			}
			case 1: {
				float value = io.readFloat4();
				AttributeFloat attribute = new AttributeFloat(name, type, context);
				attribute.setValue(value);
				parent.addAttribute(attribute);
				break;
			}
			case 2: {
				String value = getFromStringTable((int) io.readUInt4());
				AttributeString attribute = new AttributeString(name, type, context);
				attribute.setValue(value);
				parent.addAttribute(attribute);
				break;
			}
			case 3:
				AttributeComposite attribute = new AttributeComposite(name, type, context);
				parent.addAttribute(attribute);
				int numberOfComposites = (int) io.readUInt4();
				for (int i = 0; i < numberOfComposites; i++) {
					loadAttributes(io, attribute);
				}
				break;
			default:
			}
		} catch (ColumbusException e) {
			throw new GraphlibException(e);
		}
	}

	private String getFromStringTable(long value) {
		return strTable.get((int) value);
	}

	/**
	 * It loads the binary with the given filepath.
	 * 
	 * @param filename The name of the binary graph file.
	 * @throws GraphlibException It throws exception if something went wrong during the io process. 
	 */
	public void loadBinary(String filename) throws GraphlibException {
		File file = new File(filename);
		if (!file.exists()) {
			throw new GraphlibException("File " + filename + " not found!");
		}
		IO io = null;
		try {
			io = new IO(filename, IOMode.READ);
			strTable.load(io);
			int num = (int) io.readUInt4();
			for (int i = 0; i < num; i++) {
				header.put(getFromStringTable(io.readUInt4()), getFromStringTable(io.readUInt4()));
			}

			// read the nodes
			while (true) {
				long UIDKey = io.readUInt4();
				long nodeTypeKey = io.readUInt4();
				// finished reading nodes
				if (UIDKey == 0 && nodeTypeKey == 0) {
					break;
				}

				// store the node in the HashMap
				String nodeUID = getFromStringTable(UIDKey);
				Node node = nodeMap.get(nodeUID);
				if (node == null) {
					String nodeTypeString = getFromStringTable(nodeTypeKey);
					if (!nodeTypeMap.containsKey(nodeTypeString)) {
						nodeTypeMap.put(nodeTypeString, new NodeType(nodeTypeString));
					}
					node = createNode(nodeUID, nodeTypeMap.get(getFromStringTable(nodeTypeKey)));
					nodeMap.put(nodeUID, node);
				} else if (node.getType() == null) {
					String nodeTypeString = getFromStringTable(nodeTypeKey);
					if (!nodeTypeMap.containsKey(nodeTypeString)) {
						nodeTypeMap.put(nodeTypeString, new NodeType(nodeTypeString));
					}
					node.setType(nodeTypeMap.get(nodeTypeString));
				}

				// Read the attributes of the node
				int numberOfAttrs = (int) io.readUInt4();
				for (int i = 0; i < numberOfAttrs; i++) {
					loadAttributes(io, node);
				}

				while (true) {
					// Read the edges of the node

					int edgeTypeInt = (int) io.readUInt4();
					int dirTypeInt = (int) io.readUInt4();
					int toNodeInt = (int) io.readUInt4();

					// Finish reading the edges
					if (edgeTypeInt == 0 && dirTypeInt == 0 && toNodeInt == 0) {
						break;
					}
					String toNodeUID = getFromStringTable(toNodeInt);
					Node toNode = nodeMap.get(toNodeUID);
					if (toNode == null) {
						toNode = new Node(toNodeUID, null);
						nodeMap.put(toNodeUID, toNode);
					}
					String edgeType = getFromStringTable(edgeTypeInt);
					Edge edge = createDirectedEdge(node, toNode, edgeType,
							Edge.eDirectionType.edtReverse.ordinal() == dirTypeInt);

					boolean pair = io.readBoolean1();
					int numberOfEdgeAttributs = io.readInt4();
					for (int i = 0; i < numberOfEdgeAttributs; i++) {
						loadAttributes(io, edge);
					}

					if (pair) {
						createReversePair(edge);
						int numberOfEdgePairAttributes = io.readInt4();
						for (int i = 0; i < numberOfEdgePairAttributes; i++) {
							loadAttributes(io, edge);
						}
					}
				}
			}
			io.close();
		} catch (ColumbusException e) {
			throw new GraphlibException(e);
		}
	}

	private Edge createReversePair(Edge edge) {
		String type = edge.getType().getType();
		if (!edgeTypeMap.containsKey(type)) {
			edgeTypeMap.put(type, new EdgeType(type, eDirectionType.edtDirectional.ordinal()));
		}
		Edge reverseEdge = new Edge(edge.getToNode(), edge.getFromNode(), new EdgeType(type,
				eDirectionType.edtReverse.ordinal()));
		for (Attribute att : edge.getAttributes()) {
			reverseEdge.addAttribute(att);
		}
		reverseEdge.setGraph(this);
		edge.getToNode().addEdge(reverseEdge);
		edgePairMap.put(edge, reverseEdge);
		edgePairMap.put(reverseEdge, edge);
		return reverseEdge;
	}
	
	/**
	 * Executes a Breadth-First Traversal for the graph from startNode along the edges with types in the EdgeTypeSet. 
	 * It will call edgeVisitorFunc function to every edge and the preNodeVisitorFunc to every node.
	 * 
	 * @param startNode The start node where we would like to start the traversing.
	 * @param edgetypeset Types of the edges we would like to traverse. 
	 * @param visitor The implemented visitor.
	 * @throws VisitorException Throws exception if something went wrong in the visitor.
	 */
	public void traverseBreadthFirst(Node startNode, EdgeTypeSet edgetypeset, Visitor visitor) throws VisitorException {
		List<Node> nodes = new ArrayList<Node>();
		nodes.add(startNode);
		while (!nodes.isEmpty()) {
			Node node = nodes.remove(0);
			visitor.preNodeVisitorFunc(node);
			for (Edge edge : node.getOutEdges()) {
				if (!edgetypeset.contains(edge.getType())) {
					continue;
				}
				visitor.edgeVisitorFunc(edge);
				nodes.add(edge.getToNode());
			}
		}
	}

	/**
	 * Executes a Depth-First Traversal for the graph from startNode along the edges with types in the EdgeTypeSet. 
	 * It will call edgeVisitorFunc function to every edge and the postNodeVisitorFunc to every node.
	 * 
	 * @param startNode The start node where we would like to start the traversing.
	 * @param edgetypeset Types of the edges we would like to traverse. 
	 * @param visitor The implemented visitor.
	 * @throws VisitorException Throws exception if something went wrong in the visitor.
	 */
	public void traverseDepthFirstPostorder(Node startNode, Edge.EdgeTypeSet edgetypeset, Visitor visitor) throws VisitorException  {
		for (Edge edge : startNode.getOutEdges()) {
			if (!edgetypeset.contains(edge.getType())) {
				continue;
			}
			visitor.edgeVisitorFunc(edge);
			traverseDepthFirstPostorder(edge.getToNode(), edgetypeset, visitor);
		}
		visitor.postNodeVisitorFunc(startNode);
	}

	/**
	 * Executes a Depth-First Traversal for the graph from startNode along the edges with types in the EdgeTypeSet. 
	 * It will call edgeVisitorFunc function to every edge and the preNodeVisitorFunc to every node.
	 * 
	 * @param startNode The start node where we would like to start the traversing.
	 * @param edgetypeset Types of the edges we would like to traverse. 
	 * @param visitor The implemented visitor.
	 * @throws VisitorException Throws exception if something went wrong in the visitor.
	 */
	public void traverseDepthFirstPreorder(Node startNode, Edge.EdgeTypeSet edgetypeset, Visitor visitor) throws VisitorException {
		visitor.preNodeVisitorFunc(startNode);
		for (Edge edge : startNode.getOutEdges()) {
			if (!edgetypeset.contains(edge.getType())) {
				continue;
			}
			visitor.edgeVisitorFunc(edge);
			traverseDepthFirstPreorder(edge.getToNode(), edgetypeset, visitor);
		}
	}

	/**
	 * Executes a Depth-First Traversal for the graph from startNode along the edges with types in the EdgeTypeSet. 
	 * It will call edgeVisitorFunc function to every edge and the preNodeVisitorFunc and postNodeVisitorFunc to every node.
	 * 
	 * @param startNode The start node where we would like to start the traversing.
	 * @param edgetypeset Types of the edges we would like to traverse. 
	 * @param visitor The implemented visitor.
	 * @throws VisitorException Throws exception if something went wrong in the visitor.
	 */
	public void traverseDepthFirst(Node startNode, Edge.EdgeTypeSet edgetypeset, Visitor visitor) throws VisitorException {
		visitor.preNodeVisitorFunc(startNode);
		for (Edge edge : startNode.getOutEdges()) {
			if (!edgetypeset.contains(edge.getType())) {
				continue;
			}
			visitor.edgeVisitorFunc(edge);
			traverseDepthFirst(edge.getToNode(), edgetypeset, visitor);
		}
		visitor.postNodeVisitorFunc(startNode);
	}

	
	/**
	 * It finds every root node from the graph by edgeType
	 */
	public Set<Node> getRootByEdgeType(Edge.EdgeType edgeType) {
		Set<Node> rootNodes = new HashSet<Node>();
		Set<Node> toNodes = new HashSet<Node>();
		Set<Node> fromNodes = new HashSet<Node>();
		for (Node node : getNodes()) {
			List<Edge> edges = node.findOutEdges(edgeType);
			if (!edges.isEmpty()) {
				fromNodes.add(node);
			}
			for (Edge edge : edges) {
				toNodes.add(edge.getToNode());
			}
		}
		for (Node node : toNodes) {
			if (!fromNodes.contains(node)) {
				rootNodes.add(node);
			}
		}
		return rootNodes;
	}

	protected Set<Node> getRootByEdgeType(String type, int direction) {
		return getRootByEdgeType(new EdgeType(type, direction));
	}

	/**
	 * Add or update the headerinfo with the given key and value.
	 * 
	 * @param key The key of the headerinfo.
	 * @param value The value of the headerinfo.
	 * @throws GraphlibException Throws exception if we could not map the given String to to StringTable.
	 */
	public void setHeaderInfo(String key, String value) throws GraphlibException {
		try{
			strTable.set(key);
			strTable.set(value);
			header.put(key, value);
		} catch (ColumbusException e) {
			throw new GraphlibException(e);
		}
	}

	/**
	 * Get the headerinfo with the given key.
	 * 
	 * @param key The key of the headerinfo.
	 * @return The value of the headerinfo with the given key.
	 */
	public String getHeaderInfo(String key) {
		return header.get(key);
	}

	/**
	 * Delete information from the header with the given key.
	 * 
	 * @param key The key of the headerinfo
	 * @return True if the deletion was success, false otherwise.
	 */
	public boolean deleteHeaderInfo(String key) {
		if (header.remove(key) != null) {
			return true;
		}
		return false;
	}

	/**
	 * Delete all information from header
	 */
	public void clearHeaderInfo() {
		header.clear();
	}

	/**
	 * Get every node in the graph in a list.
	 * @return Every node in the graph in a list.
	 */
	public List<Node> getNodes() {
		List<Node> nodes = new ArrayList<Node>();
		for (Node node : nodeMap.values()) {
			nodes.add(node);
		}
		return nodes;
	}

	Edge getReversePair(Edge edge) {
		return edgePairMap.get(edge);
	}

}
