using System.Collections.Generic;
using Columbus.CSAN.Contexts;

namespace Columbus.CSAN.Metrics
{
    using Size;

    class LineMetrics
    {
        private readonly SolutionContext solutionContext;
        private readonly LOC loc;
        private readonly TLLOC tlloc;

        public LineMetrics(SolutionContext solutionContext)
        {
            this.solutionContext = solutionContext;
            loc = new LOC(solutionContext);
            tlloc = new TLLOC(solutionContext.LLOCMap);
        }

        /// <summary>
        /// Calculate lines metrics to the LIM nodes
        /// </summary>
        public void Calculate()
        {
            Dictionary<uint, HashSet<uint>> fileLLOC = GetFileLLOC();

            CalculateFileLLOC(fileLLOC);

            // TLLOC + (T)LOC
            CalculateTotalLineMetrics();
        }

        /// <summary>
        /// Aggregate LLOC to the 
        ///  - File level
        ///  - Scope level
        ///  - Component level
        /// </summary>
        /// <returns></returns>
        private Dictionary<uint, HashSet<uint>> GetFileLLOC()
        {
            Dictionary<uint, HashSet<uint>> fileLLOC = new Dictionary<uint, HashSet<uint>>();
            foreach (var idIt in solutionContext.LLOCMap)
            {
                Lim.Asg.Nodes.Base.Base @ref = solutionContext.LimFactory.getRef(idIt.Key);

                // File
                var TLLOC_ofScope = idIt.Value;
                TLLOC.MergePathLineMaps(ref fileLLOC, ref TLLOC_ofScope);

                // Scope
                if (Lim.Asg.Common.getIsScope(@ref))
                {
                    Lim.Asg.Nodes.Logical.Scope scope = @ref as Lim.Asg.Nodes.Logical.Scope;
                    foreach (var item in idIt.Value)
                    {
                        scope.LLOC += (uint)item.Value.Count;
                    }
                }
                // Component
                else if (Lim.Asg.Common.getIsComponent(@ref))
                {
                    Lim.Asg.Nodes.Base.Component component = @ref as Lim.Asg.Nodes.Base.Component;
                    foreach (var item in idIt.Value)
                    {
                        component.TLLOC += (uint)item.Value.Count;
                    }
                }
            }
            return fileLLOC;
        }

        /// <summary>
        /// TLLOC and TLOC calculation
        /// </summary>
        private void CalculateTotalLineMetrics()
        {
            Lim.Asg.Factory.Iterator it = solutionContext.LimFactory.getIterator();
            while (it.hasNext())
            {
                Lim.Asg.Nodes.Base.Base baseIt = it.getNext();
                if (Lim.Asg.Common.getIsScope(baseIt))
                {
                    Lim.Asg.Nodes.Logical.Scope scope = baseIt as Lim.Asg.Nodes.Logical.Scope;
                    scope.TLLOC = (uint)tlloc.CollectTLLOC(ref scope);
                    loc.SetLOC(scope);
                }

                if (Lim.Asg.Common.getIsComponent(baseIt))
                {
                    ulong tloc = 0;

                    if (solutionContext.ComponentTLOCMap.ContainsKey(baseIt.Id))
                    {
                        foreach (var itFileKeys in solutionContext.ComponentTLOCMap[baseIt.Id])
                        {
                            tloc += itFileKeys.Value;
                        }
                    }
                    (baseIt as Lim.Asg.Nodes.Base.Component).TLOC = (uint)tloc;
                }

            }
        }

        /// <summary>
        /// Set File level LOC
        /// </summary>
        /// <param name="fileLLOC"></param>
        private void CalculateFileLLOC(Dictionary<uint, HashSet<uint>> fileLLOC)
        {
            foreach (var fileIt in fileLLOC)
            {
                uint value;
                if (!solutionContext.FileMap.TryGetValue(fileIt.Key, out value))
                    continue;
                var file = solutionContext.LimFactory.getRef(value) as Lim.Asg.Nodes.Physical.File;
                file.LLOC = (uint)fileIt.Value.Count;
            }
        }
    }
}
