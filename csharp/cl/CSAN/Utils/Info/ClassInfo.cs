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