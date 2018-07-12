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

using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Physical;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Columbus.CSAN.Commons;

namespace Columbus.CSAN.Metrics.Size
{
    internal sealed class TLOC
    {
        public static ulong Calculate(Lim.Asg.Nodes.Logical.Scope limScope, ref List<Interval> intervals)
        {
            ulong TLOC = 0;

            if (limScope.Factory.getFilterState(limScope.Id) == Lim.Asg.Filter.FilterState.Filtered) return 0;

            // The root package does not have all the isContainedIn edges
            // So we calculate its TLOC by the sum of its child package's TLOC

            // Subpackages are not physically inside their parent Packages
            // ( unlike e.g. local or anonym classes inside other classes )
            // So the TLOC of a Package is computed recursively
            if (Lim.Asg.Common.getIsPackage(limScope))
            {
                ListIterator<Lim.Asg.Nodes.Logical.Member> subPackageIt = limScope.HasMemberListIteratorBegin;
                while (subPackageIt.getValue() != null)
                {
                    Lim.Asg.Nodes.Logical.Member subPackage = subPackageIt.getValue();
                    if (!Lim.Asg.Common.getIsPackage(subPackage))
                    {
                        subPackageIt = subPackageIt.getNext();
                        continue;
                    }
                    Lim.Asg.Nodes.Logical.Package _subPackage = subPackage as Lim.Asg.Nodes.Logical.Package;
                    TLOC += Calculate(_subPackage, ref intervals);
                    subPackageIt = subPackageIt.getNext();
                }
            }

            ListIteratorAssocSourcePosition<File> sourcePositionInFileBeginIt = limScope.IsContainedInListIteratorAssocBegin;

            for (var fileIt = sourcePositionInFileBeginIt.getValue(); fileIt != null; fileIt = sourcePositionInFileBeginIt.getNext().getValue())
            {
                var pos = sourcePositionInFileBeginIt.getAssocItem();
                var i = new Interval
                {
                    Key = limScope.Factory.StringTable.set(Lim.Asg.Common.GetFullPath(fileIt)),
                    From = pos.Line,
                    To = pos.EndLine
                };
                intervals.Add(i);

                TLOC += i.To - i.From + 1;
            }

            return TLOC;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void InsertComponentTLOCMap(uint NodeId, uint Key, ulong lastLineNumber)
        {
            if (MainDeclaration.Instance.ComponentTLOCMap.ContainsKey(NodeId))
            {
                if (!MainDeclaration.Instance.ComponentTLOCMap[NodeId].ContainsKey(Key))
                {
                    MainDeclaration.Instance.ComponentTLOCMap[NodeId].Add(Key, lastLineNumber);
                }
                else
                {
                    MainDeclaration.Instance.ComponentTLOCMap[NodeId][Key] = lastLineNumber;
                }
            }
            else
            {
                var loc = new Dictionary<uint, ulong> { { Key, lastLineNumber } };
                MainDeclaration.Instance.ComponentTLOCMap.Add(NodeId, loc);
            }
        }
    }
}
