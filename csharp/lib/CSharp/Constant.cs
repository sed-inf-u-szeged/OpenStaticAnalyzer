using System;
using System.Text;

namespace Columbus.Csharp.Asg {

    /// <summary>
    /// Contains some predefined constants.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class Constant {

        /// <summary>
        /// The API version of the schema.
        /// </summary>
        public static string APIVersion = "0.11";

        /// <summary>
        /// The binary version of the schema.
        /// </summary>
        public static string BinaryVersion = "0.11";

    }

}
