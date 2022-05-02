package columbus;

import graphlib.Edge;
import graphlib.Graph;
import graphlib.GraphlibException;
import graphlib.Node;
import graphlib.VisitorException;
import java.util.ArrayList;


class TestVisitor implements graphlib.Visitor
{
	
	@Override
	public void edgeVisitorFunc(Edge e) throws VisitorException {
		String s = e.getFromNode().getUID() + "-" + e.getToNode().getUID();
		System.out.println(s);
		history.add(s);
	}

	@Override
	public void postNodeVisitorFunc(Node node) throws VisitorException {
		String s = "-" + node.getUID();
		System.out.println(s);
		history.add(s);
	}

	@Override
	public void preNodeVisitorFunc(Node node) throws VisitorException {
		String s = "+" + node.getUID();
		System.out.println(s);
		history.add(s);
	}
	
	public ArrayList<String> history = new ArrayList<String>();	
};


public class GraphTest {
	private static boolean checkResult(String[] expectedResult, ArrayList<String> result)
	{
		boolean res = true;
        if (expectedResult.length != result.size())
        {
        	System.out.println("Length error. Found:" + result.size() + " Expected:" + expectedResult.length);
        	return false;
        }
        else
        {
        	for (int i = 0; i < expectedResult.length; ++i)
        	{
        		if (expectedResult[i].compareTo(result.get(i)) != 0) 
        		{
        			System.out.println("Error at:" + i + " Found:" +  result.get(i) + " Expected:" + expectedResult[i]);
        			res = false;
        		}
        	}
        }
        return res;
	}
	
	public static void main(String[] args) {

	    try {
	    	Graph graph = new Graph();
	    	Node node1 = graph.createNode("N1", new Node.NodeType("N"));
	    	Node node2 = graph.createNode("N2", new Node.NodeType("N"));
	    	Node node3 = graph.createNode("N3", new Node.NodeType("N"));
	    	Node node4 = graph.createNode("N4", new Node.NodeType("N"));
	    	Node node5 = graph.createNode("N5", new Node.NodeType("N"));
	    	
	    	graph.createDirectedEdge(node1, node2, "E", false);
	        graph.createDirectedEdge(node1, node3, "E", false);
	        graph.createDirectedEdge(node1, node2, "E", false);
	        graph.createDirectedEdge(node2, node4, "E", false);
	        graph.createDirectedEdge(node2, node4, "E", false);
	        graph.createDirectedEdge(node3, node1, "E", false);
	        graph.createDirectedEdge(node3, node4, "E", false);
	        graph.createDirectedEdge(node3, node4, "E", false);
	        graph.createDirectedEdge(node4, node1, "E", false);
	        graph.createDirectedEdge(node4, node5, "E", false);
	        graph.createDirectedEdge(node4, node1, "E", false);
	        graph.createDirectedEdge(node4, node5, "E", false);
	        graph.createDirectedEdge(node4, node1, "E", false);
	
	        graph.saveBinary("TestGraph.graph");
	        
	    	graphlib.Edge.EdgeTypeSet edges = new graphlib.Edge.EdgeTypeSet();
	    	edges.add(new Edge.EdgeType("E", Edge.eDirectionType.edtDirectional));
	    	TestVisitor tv = new TestVisitor();
	    	boolean testResultOK = true;
	    	System.out.println("--------------------- Breadth first-------------------");
	        graph.traverseBreadthFirst(node1, edges, tv);
	    	
	        String[] expectedBFResults = {
	        		"+N1",  		
	        		"N1-N2",
	        		"N1-N3",
	        		"N1-N2",
	        		"+N2",
	        		"N2-N4",
	        		"N2-N4",
	        		"+N3",
	        		"N3-N1",
	        		"N3-N4",
	        		"N3-N4",
	        		"+N4",
	        		"N4-N1",
	        		"N4-N5",
	        		"N4-N1",
	        		"N4-N5",
	        		"N4-N1",
	        		"+N5"        
	        };
	        		
	        testResultOK &= checkResult(expectedBFResults, tv.history);

	        System.out.println("--------------------- Depth first -------------------");
	        tv.history.clear();
	        graph.traverseDepthFirst(node1, edges, tv);

	        String[] expectedDFResults = {
	        		"+N1",
	        		"N1-N2",
	        		"N1-N2",
	        		"+N2",
	        		"N2-N4",
	        		"N2-N4",
	        		"+N4",
	        		"N4-N1",
	        		"N4-N1",
	        		"N4-N1",
	        		"N4-N5",
	        		"N4-N5",
	        		"+N5",
	        		"-N5",
	        		"-N4",
	        		"-N2",
	        		"N1-N3",
	        		"+N3",
	        		"N3-N1",
	        		"N3-N4",
	        		"N3-N4",
	        		"-N3",
	        		"-N1"
	        };
	        testResultOK &= checkResult(expectedDFResults, tv.history);
	        
	        System.out.println("--------------------- Depth first pre -------------------");
	    	tv.history.clear();
	        graph.traverseDepthFirstPreorder(node1, edges, tv);

	        String[] expectedDFPreResults = {
	        		"+N1",
	        		"N1-N2",
	        		"N1-N2",
	        		"+N2",
	        		"N2-N4",
	        		"N2-N4",
	        		"+N4",
	        		"N4-N1",
	        		"N4-N1",
	        		"N4-N1",
	        		"N4-N5",
	        		"N4-N5",
	        		"+N5",
	        		"N1-N3",
	        		"+N3",
	        		"N3-N1",
	        		"N3-N4",
	        		"N3-N4"
	        };
	        testResultOK &= checkResult(expectedDFPreResults, tv.history);
	        
	        System.out.println("--------------------- Depth first post -------------------");
	        tv.history.clear();
	        graph.traverseDepthFirstPostorder(node1, edges, tv);
	    	
	        String[] expectedDFPostResults = {
	        		"N4-N1",
	        		"N4-N1",
	        		"N4-N1",
	        		"-N5",
	        		"N4-N5",
	        		"N4-N5",
	        		"-N4",
	        		"N2-N4",
	        		"N2-N4",
	        		"-N2",
	        		"N1-N2",
	        		"N1-N2",
	        		"N3-N1",
	        		"N3-N4",
	        		"N3-N4",
	        		"-N3",
	        		"N1-N3",
	        		"-N1"
	        };
	        testResultOK &= checkResult(expectedDFPostResults, tv.history);
	        
	        
	        System.out.println("--------------------- Result -------------------");
	        if (!testResultOK) 
	        {
	        	System.out.println("Test failed!");
	        	System.exit(-1);
	        }
	        else
	        {
	        	System.out.println("Test OK!");
	        }
	    } catch (GraphlibException e) {
			e.printStackTrace();
	    } catch (VisitorException e) {
			e.printStackTrace();
		}
	}
}
