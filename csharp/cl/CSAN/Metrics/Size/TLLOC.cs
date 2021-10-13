using System.Collections.Generic;
using System.Runtime.CompilerServices;

using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Utils;


namespace Columbus.CSAN.Metrics.Size
{
    internal sealed class TLLOC
    {
        private readonly LLOCMapType llocMap;

        public TLLOC(LLOCMapType llocMap)
        {
            this.llocMap = llocMap;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public long CollectTLLOC(ref Scope limScope)
        {
            Dictionary<uint, HashSet<uint>> TLLOC_ofScope = new Dictionary<uint, HashSet<uint>>();
            MergeTLLOC(ref limScope, ref TLLOC_ofScope);

            int sum = 0;
            foreach (var TLLOC in TLLOC_ofScope)
            {
                sum += TLLOC.Value.Count;
            }

            return sum;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void MergePathLineMaps(ref Dictionary<uint, HashSet<uint>> result, ref Dictionary<uint, HashSet<uint>> other)
        {
            foreach (var item in other)
            {
                if (!result.ContainsKey(item.Key))
                {
                    result.Add(item.Key, item.Value);
                }
                else
                {
                    result[item.Key].UnionWith(item.Value);
                }
            }
        }

        private void MergeTLLOC(ref Scope limScope, ref Dictionary<uint, HashSet<uint>> TLLOC_Scope)
        {
            if (llocMap.ContainsKey(limScope.Id))
            {
                var TLLOC_ofScope = llocMap[limScope.Id];
                MergePathLineMaps(ref TLLOC_Scope, ref TLLOC_ofScope);
            }

            ListIterator<Member> it = limScope.HasMemberListIteratorBegin;
            while (it.getValue() != null)
            {
                Member memberIt = it.getValue();
                if (Lim.Asg.Common.getIsScope(memberIt))
                {
                    Scope memberItScope = memberIt as Scope;
                    MergeTLLOC(ref memberItScope, ref TLLOC_Scope);
                }
                it = it.getNext();
            }
        }
    }
}
