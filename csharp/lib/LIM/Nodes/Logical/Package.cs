using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// Package class, which represents the logical::Package node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, DemangledName=\"{DemangledName}\", Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Package : Scope {

        /// <summary>The PackageKind of the node.</summary>
        protected Types.PackageKind m_packageKind;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Package(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_packageKind = Types.PackageKind.pkPackage;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkPackage; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the packageKind of the node.
        /// </summary>
        /// <returns>Returns with the packageKind.</returns>
        public Types.PackageKind PackageKind
        {
            get
            {
                return m_packageKind;
            }
            set
            {
                m_packageKind = value;
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

            io.writeUByte1((byte)m_packageKind);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_packageKind = (Types.PackageKind)binIo.readUByte1();

        }

    }

}
