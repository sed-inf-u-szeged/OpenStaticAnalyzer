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

using System.Collections.Generic;
using System.Runtime.CompilerServices;

using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.CSAN.Commons;


namespace Columbus.CSAN.Metrics.Size
{
    internal sealed class TLLOC
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static long CollectTLLOC(ref Scope limScope)
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

        private static void MergeTLLOC(ref Scope limScope, ref Dictionary<uint, HashSet<uint>> TLLOC_Scope)
        {
            if (MainDeclaration.Instance.LLOCMap.ContainsKey(limScope.Id))
            {
                var TLLOC_ofScope = MainDeclaration.Instance.LLOCMap[limScope.Id];
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
