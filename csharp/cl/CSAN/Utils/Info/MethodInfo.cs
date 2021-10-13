using System.Collections.Generic;

namespace Columbus.CSAN.Utils.Info
{
    using IdAndHasFilteredType = KeyValuePair<uint, bool>;

    struct MethodInfo
    {
        public uint Id;
        public int NOS;
        public int NL;
        public int NLE;
        public int NOB;
        public HashSet<IdAndHasFilteredType> Calls;
        public HashSet<IdAndHasFilteredType> Throws;
        public HashSet<IdAndHasFilteredType> CanThrow;
        public HashSet<IdAndHasFilteredType> Instantiates;
        public HashSet<IdAndHasFilteredType> AccessAttribute;

        public MethodInfo(
            uint id = 0, 
            int nos = 0, 
            int nl = 0, 
            int nle = 0, 
            int nob = 1,
            HashSet<IdAndHasFilteredType> a = null, 
            HashSet<IdAndHasFilteredType> b = null,
            HashSet<IdAndHasFilteredType> c = null,
            HashSet<IdAndHasFilteredType> d = null,
            HashSet<IdAndHasFilteredType> e = null)
        {
            Id = id;
            NOS = nos;
            NL = nl;
            NLE = nle;
            NOB = nob;

            if (a != null)
                Calls = a;
            else
                Calls = new HashSet<IdAndHasFilteredType>();
            if (b != null)
                Throws = b;
            else
                Throws = new HashSet<IdAndHasFilteredType>();
            if (c != null)
                CanThrow = c;
            else
                CanThrow = new HashSet<IdAndHasFilteredType>();
            if (d != null)
                Instantiates = d;
            else
                Instantiates = new HashSet<IdAndHasFilteredType>();
            if (e != null)
                AccessAttribute = e;
            else
                AccessAttribute = new HashSet<IdAndHasFilteredType>();
        }

        
    }
}