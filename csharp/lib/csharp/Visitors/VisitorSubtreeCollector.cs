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
