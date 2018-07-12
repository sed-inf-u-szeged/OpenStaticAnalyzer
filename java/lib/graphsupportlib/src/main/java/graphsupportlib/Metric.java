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

package graphsupportlib;

import graphlib.Attribute;
import graphlib.AttributeComposite;
import graphlib.AttributeInt;
import graphlib.AttributeString;
import graphlib.Edge;
import graphlib.Edge.eDirectionType;
import graphlib.Node;

import java.util.ArrayList;
import java.util.List;

/**
 * The Graphsupportlib contains the OpenStaticAnalyzer specific constants and methods of the general Graphlib.
 *
 */
public class Metric {

	// Context constants
	public static final String CONTEXT_WARNING = "warning";
	public static final String CONTEXT_METRIC = "metric";
	public static final String CONTEXT_METRICGROUP = "metricgroup";
	public static final String CONTEXT_ATTRIBUTE = "attribute";
	public static final String CONTEXT_RUL = "rul";

	// Attribute name constants
	public static final String ATTR_WARNINGTEXT = "WarningText";
	public static final String ATTR_POSITION = "Position";
	public static final String ATTR_NAME = "Name";
	public static final String ATTR_LONGNAME = "LongName";
	public static final String ATTR_PATH = "Path";
	public static final String ATTR_LINE = "Line";
	public static final String ATTR_COLUMN = "Column";
	public static final String ATTR_ENDLINE = "EndLine";
	public static final String ATTR_ENDCOLUMN = "EndColumn";
	public static final String ATTR_REALIZATIONLEVEL = "RealizationLevel";

	public static final String ATTR_RUL_DESCRIPTION = "Description";
	public static final String ATTR_RUL_DISPLAYNAME = "DisplayName";
	public static final String ATTR_RUL_ENABLED = "Enabled";
	public static final String ATTR_RUL_GROUPTYPE = "GroupType";
	public static final String ATTR_RUL_HELPTEXT = "HelpText";
	public static final String ATTR_RUL_SETTINGS = "Settings";
	public static final String ATTR_RUL_PRIORITY = "Priority";
	public static final String ATTR_RUL_WARNING = "Warning";
	public static final String ATTR_RUL_CALCULATED = "Calculated";
	public static final String ATTR_RUL_CALCULATEDFOR = "CalculatedFor";

	public static final String ATTR_DCF_CLONESMELLTYPE = "CloneSmellType";

	public static final String ATTR_UUID = "UUID";
	public static final String ATTR_TUID = "TUID";

	// Node type constants
	public static final String NTYPE_ROOT = "TreeRoot";
	public static final String NTYPE_RUL_METRIC = "RulMetric";
	public static final String NTYPE_RUL_TOOL = "RulTool";

	public static final String NTYPE_LIM_COMPONENT = "Component";
	public static final String NTYPE_LIM_MODULE = "Module";
	public static final String NTYPE_LIM_NAMESPACE = "Namespace";
	public static final String NTYPE_LIM_PACKAGE = "Package";
	public static final String NTYPE_LIM_ROOT = "Root";
	public static final String NTYPE_LIM_CLASS = "Class";
	public static final String NTYPE_LIM_STRUCTURE = "Strucutre";
	public static final String NTYPE_LIM_UNION = "Union";
	public static final String NTYPE_LIM_INTERFACE = "Interface";
	public static final String NTYPE_LIM_ENUM = "Enum";
	public static final String NTYPE_LIM_ANNOTATION = "Annotation";
	public static final String NTYPE_LIM_SOURCEFILE = "SourceFile";
	public static final String NTYPE_LIM_CLASSDEF = "ClassDef";
	public static final String NTYPE_LIM_FUNCTION = "Function";
	public static final String NTYPE_LIM_METHOD = "Method";
	public static final String NTYPE_LIM_FUNCTIONMEMBER = "FunctionMember";
	public static final String NTYPE_LIM_PROCEDURE = "Procedure";
	public static final String NTYPE_LIM_FUNCTIONDEF = "FunctionDef";
	public static final String NTYPE_LIM_METHODDEF = "MethodDef";
	public static final String NTYPE_LIM_ATTRIBUTE = "Attribute";
	public static final String NTYPE_LIM_FILESYSTEM = "FileSystem";
	public static final String NTYPE_LIM_FOLDER = "Folder";
	public static final String NTYPE_LIM_FILE = "File";
	public static final String NTYPE_DCF_CLONECLASS = "CloneClass";
	public static final String NTYPE_DCF_CLONEINSTANCE = "CloneInstance";

	// Edge type constants
	public static final String ETYPE_RUL_GROUPCONTAINS = "RulGroupContains";
	public static final String ETYPE_RUL_TREE = "RulTree";

	public static final String ETYPE_LIM_LOGICALTREE = "LogicalTree";
	public static final String ETYPE_LIM_PHYSICALTREE = "PhysicalTree";
	public static final String ETYPE_LIM_COMPONENTTREE = "ComponentTree";
	public static final String ETYPE_LIM_COMPONENT = "Component";
	public static final String ETYPE_LIM_VARIANT = "Variant";
	public static final String ETYPE_LIM_AGGREGATED = "Aggregated";
	public static final String ETYPE_LIM_INSTANCE = "Instance";
	public static final String ETYPE_LIM_DECLARES = "Declares";

	public static final String ETYPE_DCF_CLONETREE = "CloneTree";
	public static final String ETYPE_DCF_HASCLONE = "Clone";

	// Attribute value constants
	public static final String ATTRVALUE_INVALID = "__INVALID__";
	public static final String ATTRVALUE_LIM_RELDECLARES = "declaration";
	public static final String ATTRVALUE_LIM_RELDEFINES = "definition";

	// Node UID constans
	public static final String UID_RUL_ROOT = "__RulRoot__";
	public static final String UID_CLONE_ROOT = "__CloneRoot__";
	public static final String UID_LOGICAL_ROOT = "__LogicalRoot__";
	public static final String UID_PHYSICAL_ROOT = "__PhysicalRoot__";

	// Header Attributes
	public static final String HEADER_ASG_KEY = "asg";
	public static final String HEADER_ASG_VALUE_JAVA = "java";
	public static final String HEADER_ASG_VALUE_CPP = "cpp";
	public static final String HEADER_ASG_VALUE_C = "c";

	/**
	 * Position of a specific SourceCodeElement like a method or warning.
	 * It has path, line, endline, column and endcolumn attributes.
	 *
	 */
	public static class Position {
		public Position(String path, int line, int col, int endline, int endcol) {
			this.path = path;
			this.line = line;
			this.col = col;
			this.endline = endline;
			this.endcol = endcol;
		}

		public String path;
		public int line;
		public int col;
		public int endline;
		public int endcol;

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + col;
			result = prime * result + endcol;
			result = prime * result + endline;
			result = prime * result + line;
			result = prime * result + ((path == null) ? 0 : path.hashCode());
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
			Position other = (Position) obj;
			if (col != other.col)
				return false;
			if (endcol != other.endcol)
				return false;
			if (endline != other.endline)
				return false;
			if (line != other.line)
				return false;
			if (path == null) {
				if (other.path != null)
					return false;
			} else if (!path.equals(other.path))
				return false;
			return true;
		}
	};

	/**
	 * gives back node Metrics attributes in the node
	 * 
	 * @param node the node
	 * @return the Metric attributes of the given node
	 */
	public static List<Attribute> getMetricAttributes(Node node) {
		return node.findAttributeByContext(CONTEXT_METRIC);
	}

	/**
	 * gives back node Warning attributes in the node
	 * 
	 * @param node the node
	 * @return the Metric attributes of the given node
	 */
	public static List<Attribute> getWarningAttributes(Node node) {
		return node.findAttributeByContext(CONTEXT_WARNING);

	}
	
	/**
	 * get a position composite attribute from a node.
	 * 
	 * @param node the node
	 * @return list of positions in the node
	 */
	public static ArrayList<Position> getPositionAttributes(Node node) {
		ArrayList<Position> positions = new ArrayList<Position>();
		int line = 0, col = 0, endline = 0, endcol = 0;
		String path = "";
		for (Attribute nodePositionAttributes : node.findAttribute(Attribute.aType.atComposite, ATTR_POSITION,
				CONTEXT_ATTRIBUTE)) {
			AttributeComposite nodePositionAttribute = (AttributeComposite) nodePositionAttributes;
			path = ((AttributeString) nodePositionAttribute.findAttributeByName(ATTR_PATH).get(0)).getValue();
			line = ((AttributeInt) nodePositionAttribute.findAttributeByName(ATTR_LINE).get(0)).getValue();
			col = ((AttributeInt) nodePositionAttribute.findAttributeByName(ATTR_COLUMN).get(0)).getValue();
			endline = ((AttributeInt) nodePositionAttribute.findAttributeByName(ATTR_ENDLINE).get(0)).getValue();
			endcol = ((AttributeInt) nodePositionAttribute.findAttributeByName(ATTR_ENDCOLUMN).get(0)).getValue();
			Position position = new Position(path, line, col, endline, endcol);
			positions.add(position);
		}
		return positions;
	}

    /**
     * Gives back an Attribute object of the node with the given attribute name
     * 
     * @param node The node.
     * @param attr The name of the attribute.
     * @return Attribute Teh attribute with the given name in the node, null if it was not found.
     */
    public static Attribute getNodeAttribute(Node node, String attr) {
        for (Attribute attribute : node.getAttributes()) {
            if (attribute.getName().equals(attr)) {
                return attribute;
            }
        }
        return null;
    }
    
    /**
     * Gives back the first position of a node.
     * 
     * @param node The node.
     * @return position The first position of the node.
     */
    public static Position getFirstPositionAttribute(Node node) {
        AttributeComposite posAttr = (AttributeComposite) getNodeAttribute(node, ATTR_POSITION);
        if (posAttr == null) {
            return null;
        } else {
            String path = null;
            int line = 0, col = 0, endline = 0, endcol = 0;

            for (Attribute attr : posAttr.getAttributes()) {
                if (ATTR_PATH.equals(attr.getName())) {
                    path = ((AttributeString) attr).getValue();
                } else if (ATTR_LINE.equals(attr.getName())) {
                    line = ((AttributeInt) attr).getValue();
                } else if (ATTR_COLUMN.equals(attr.getName())) {
                    col = ((AttributeInt) attr).getValue();
                } else if (ATTR_ENDLINE.equals(attr.getName())) {
                    endline = ((AttributeInt) attr).getValue();
                } else if (ATTR_ENDCOLUMN.equals(attr.getName())) {
                    endcol = ((AttributeInt) attr).getValue();
                }
            }
            return new Position(path, line, col, endline, endcol);
        }
    }
    
    /**
     * Gives back the first node by edgeType
     * 
     * @param node The node.
     * @param edgeType Default is LogicalTree
     * @return the first node by edgeType, null if cant find any node
     */
    public static Node getFirstNodeByEdgeType(Node node, String edgeType) {
        if (getNodesByEdgeType(node, edgeType, eDirectionType.edtDirectional).isEmpty()) {
            return null;
        } else {
            return getNodesByEdgeType(node, edgeType, eDirectionType.edtDirectional).get(0);
        }
    }

    /**
     * Gives back the first node by edgetype
     * 
     * @param node The node.
     * @param edgeType Default is LogicalTree
     * @return null if cant find any node
     */
    public static Node getFirstNodeByEdgeType(Node node, String edgeType, eDirectionType directionType) {
        if (getNodesByEdgeType(node, edgeType, directionType).isEmpty()) {
            return null;
        } else {
            return getNodesByEdgeType(node, edgeType, directionType).get(0);
        }
    }

    /**
     * Gives back the children of the node
     * 
     * @param node he node.
     * @param edgeType The types of the nodes.
     * @return list of children
     */
    public static List<Node> getNodesByEdgeType(Node node, String edgeType, eDirectionType directionType) {
        List<Node> result = new ArrayList<Node>();
        for (Edge cloneEdge : node.getOutEdges()) {
            if (cloneEdge.getType().getType().equals(edgeType) && cloneEdge.getType().getDirectionType().equals(directionType)) {
                result.add(cloneEdge.getToNode());
            }
        }
        return result;
    }
}
