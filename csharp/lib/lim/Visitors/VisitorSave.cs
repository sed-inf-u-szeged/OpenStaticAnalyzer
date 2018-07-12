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

using System;
using System.Text;

namespace Columbus.Lim.Asg.Visitors {

    /// <summary>
    /// Visitor for each non-abstract nodes and all edges of the graph.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class VisitorSave : VisitorAbstractNodes {

        /// <summary>
        /// Constructor for Visitor.
        /// </summary>
        /// <param name="ioForSaving">[in] The graph is saved into this IO.</param>
        public VisitorSave(IO ioForSaving) : base() {
            io = ioForSaving;
        }

        /// <summary>
        /// Visitor for saving node.
        /// </summary>
        /// <param name="node">[in] This node is being saved.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there's something wrong with the file.</exception>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.Base node, bool callVirtualBase) {
            node.save(io);
        }

        /// <summary>Pointer to the "output".</summary>
        protected IO io;

    }

}
