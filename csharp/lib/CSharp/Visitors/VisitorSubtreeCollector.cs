using System;
using System.Collections.Generic;
using System.Text;

namespace Columbus.Csharp.Asg.Visitors {

    /// <summary>
    /// Visitor to collect all nodes from a subtree.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class VisitorSubtreeCollector : VisitorAbstractNodes {

        /// <summary>
        /// Constructor for Visitor.
        /// </summary>
        /// <param name="listOfNodes">[in, out] The list where the id of the visited nodes are inserted.</param>
        public VisitorSubtreeCollector(List<uint> listOfNodes) : base() {
            nodeList = listOfNodes;
        }

        /// <summary>
        /// Visitor for all nodes.
        /// </summary>
        /// <param name="node">[in] This node is being visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Base.Base node, bool callVirtualBase) {
            nodeList.Add(node.Id);
        }

        /// <summary>Reference to the list where the ids will be collected.</summary>
        private List<uint> nodeList;

    }

}
