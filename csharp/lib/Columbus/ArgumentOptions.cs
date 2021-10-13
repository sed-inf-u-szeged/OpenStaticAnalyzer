using System;

namespace Columbus
{
    [Flags]
    public enum ArgumentOptions : uint
    {
        OT_NONE = 0,

        /// <summary>
        /// With space (opt value).
        /// </summary>
        OT_WS = 1,   // 0000000000000001  
 
        /// <summary>
        /// Without space (optvalue).
        /// </summary>
        OT_WOS = 2,  // 0000000000000010

        /// <summary>
        /// With equal sign (opt=value).
        /// </summary>
        OT_WE = 4,   // 0000000000000100

        /// <summary>
        /// With colon (opt:value).
        /// </summary>
        OT_WC = 8,   // 0000000000001000 
 
        /// <summary>
        /// The unambiguous prefix is enough.
        /// </summary>
        OT_PREFIX = 16,  // 0000000000010000 
 
        /// <summary>
        /// The parameter is a filename which contains additional options.
        /// The process function will be called before the options in the file are processed.
        /// If the function return false then the file won't be processed.
        /// </summary>
        OT_OPTION_FILE = 32,   // 0000000000100000

        /// <summary>
        /// The option has 1 parameter but not given then a default value used
        /// </summary>
        OT_DEFAULT = 64   // 0000000001000000
    }
}
