    using System;
    using System.Text;

namespace Columbus.Csharp.Asg.Algorithms {
    
    /// <summary>
    /// Common base class for all algorithm classes.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class Algorithm : Visitors.Visitor {

        /// <summary>
        /// Increases the depth of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The visitor class.</param>
        protected void incVisitorDepth(Visitors.Visitor visitor) {
            visitor.incDepth();
        }

        /// <summary>
        /// Decreases the depth of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The visitor class.</param>
        protected void decVisitorDepth(Visitors.Visitor visitor) {
            visitor.decDepth();
        }

    }

}
