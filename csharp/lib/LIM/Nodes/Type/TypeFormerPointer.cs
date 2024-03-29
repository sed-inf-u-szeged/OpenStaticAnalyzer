using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Type {

    /// <summary>
    /// TypeFormerPointer class, which represents the type::TypeFormerPointer node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class TypeFormerPointer : TypeFormer {

        /// <summary>The PointerKind of the node.</summary>
        protected Types.PointerKind m_pointerKind;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public TypeFormerPointer(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_pointerKind = Types.PointerKind.ptkPointer;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkTypeFormerPointer; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the pointerKind of the node.
        /// </summary>
        /// <returns>Returns with the pointerKind.</returns>
        public Types.PointerKind PointerKind
        {
            get
            {
                return m_pointerKind;
            }
            set
            {
                m_pointerKind = value;
            }
        }


        // ---------- Accept functions for Visitor ----------

        /// <summary>
        /// It calls the appropriate visit method of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The used visitor.</param>
        public override void accept(Visitors.Visitor visitor) {
            visitor.visit(this);
        }

        /// <summary>
        /// It calls the appropriate visitEnd method of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The used visitor.</param>
        public override void acceptEnd(Visitors.Visitor visitor) {
            visitor.visitEnd(this);
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);

            io.writeUByte1((byte)m_pointerKind);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_pointerKind = (Types.PointerKind)binIo.readUByte1();

        }

    }

}
