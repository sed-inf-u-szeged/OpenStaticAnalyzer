using System;
using System.Text;

namespace Columbus.Csharp.Asg.Visitors {

    /// <summary>
    /// Visitor for each non-abstract nodes and all edges of the graph.
    /// </summary>
#if (CSHARP_INTERNAL)
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
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Base.Base node, bool callVirtualBase) {
            node.save(io);
        }

        /// <summary>Pointer to the "output".</summary>
        protected IO io;

    }

}
