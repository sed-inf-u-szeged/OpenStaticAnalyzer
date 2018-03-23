/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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
        public static string APIVersion = "0.9";

        /// <summary>
        /// The binary version of the schema.
        /// </summary>
        public static string BinaryVersion = "0.9";

    }

}
