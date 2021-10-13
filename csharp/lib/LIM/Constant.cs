using System;
using System.Text;

namespace Columbus.Lim.Asg {

    /// <summary>
    /// Contains some predefined constants.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Constant {

        /// <summary>
        /// The API version of the schema.
        /// </summary>
        public static string APIVersion = "3.0.31";

        /// <summary>
        /// The binary version of the schema.
        /// </summary>
        public static string BinaryVersion = "3.0.31";

    }

}
