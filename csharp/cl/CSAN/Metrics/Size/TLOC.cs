using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Physical;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Columbus.CSAN.Contexts;

namespace Columbus.CSAN.Metrics.Size
{
    internal sealed class TLOC
    {
        private readonly SolutionContext solutionContext;

        public TLOC(SolutionContext solutionContext)
        {
            this.solutionContext = solutionContext;
        }

        public ulong Calculate(Lim.Asg.Nodes.Logical.Scope limScope, ref List<Interval> intervals)
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
        public void InsertComponentTLOCMap(uint nodeId, uint key, ulong lastLineNumber)
        {
            Dictionary<uint, ulong> dictionary;
            if (solutionContext.ComponentTLOCMap.TryGetValue(nodeId, out dictionary))
            {
                if (dictionary.ContainsKey(key))
                    dictionary[key] = lastLineNumber;
                else
                    dictionary.Add(key, lastLineNumber);
            }
            else
            {
                var loc = new Dictionary<uint, ulong> { { key, lastLineNumber } };
                solutionContext.ComponentTLOCMap.Add(nodeId, loc);
            }
        }
    }
}
