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

using System.Collections.Generic;

namespace Columbus.CSAN.Utils.Info
{
    using IdAndHasFilteredType = KeyValuePair<uint, bool>;

    struct ClassInfo
    {
        public uint Id;
        public HashSet<IdAndHasFilteredType> IsSubclass;

        public ClassInfo(uint id = 0, HashSet<IdAndHasFilteredType> a = null)
        {
            Id = id;
            if (a != null)
                IsSubclass = a;
            else
                IsSubclass = new HashSet<IdAndHasFilteredType>();
        }
    }
}