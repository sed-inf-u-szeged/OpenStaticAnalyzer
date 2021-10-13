using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Base {

    /// <summary>
    /// Positioned class, which represents the base::Positioned node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class Positioned : Base {

        /// <summary>Stores the `position` of the node.</summary>
        protected SourcePosition m_position;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Positioned(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_position = new SourcePosition(fact.StringTable);
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkPositioned; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the position of the node.
        /// </summary>
        /// <returns>Returns with the position.</returns>
        public SourcePosition Position
        {
            get
            {
                return m_position;
            }
            set
            {
                m_position = value;
            }
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);

            m_position.save(io);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_position.load(binIo);

        }

    }

}
