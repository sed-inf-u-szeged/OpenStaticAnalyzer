using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// LiteralExpressionSyntax class, which represents the expression::LiteralExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class LiteralExpressionSyntax : ExpressionSyntax {

        /// <summary>The Key of the `token`.</summary>
        protected uint m_token;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public LiteralExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_token = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkLiteralExpressionSyntax; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the token of the node.
        /// </summary>
        public string Token
        {
            get
            {
                return fact.StringTable.get(m_token);
            }
            set
            {
                m_token = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of token of the node.
        /// </summary>
        public uint TokenKey
        {
            get
            {
                return m_token;
            }
            set
            {
               m_token = value;
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

            fact.StringTable.setType(m_token, StrTable.StrType.strToSave);
            io.writeUInt4(m_token);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_token = binIo.readUInt4();

        }

    }

}
