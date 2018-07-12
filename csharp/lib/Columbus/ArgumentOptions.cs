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

namespace Columbus
{
    public enum ArgumentOptions : uint
    {
        OT_NONE = 0,

        /** With space (opt value). */
        OT_WS = 1,   // 0000000000000001  
 
        /** Without space (optvalue). */
        OT_WOS = 2,  // 0000000000000010

        /** With equal sign (opt=value). */
        OT_WE = 4,   // 0000000000000100

        /** With colon (opt:value). */
        OT_WC = 8,   // 0000000000001000 
 
        /** The unambiguous prefix is enough. */
        OT_PREFIX = 16,  // 0000000000010000 
 
        /** \brief The parameter is a filename which contains additional options.
        * The process function will be called before the options in the file are processed.
        * If the function return false then the file won't be processed.
        */
        OT_OPTION_FILE = 32,   // 0000000000100000

        /** The option has 1 parameter but not given then a default value used */
        OT_DEFAULT = 64   // 0000000001000000
    }
}
