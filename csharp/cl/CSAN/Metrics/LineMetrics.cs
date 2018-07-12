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
using System.Threading.Tasks;

namespace Columbus.CSAN.Metrics
{
    using Size;
    using Commons;

    static class LineMetrics
    {

        /// <summary>
        /// Aggregate LLOC to the 
        ///  - File level
        ///  - Scope level
        ///  - Component level
        /// </summary>
        /// <returns></returns>
        private static Dictionary<uint, HashSet<uint>> GetFileLLOC()
        {
            Dictionary<uint, HashSet<uint>> fileLLOC = new Dictionary<uint, HashSet<uint>>();
            foreach (var idIt in MainDeclaration.Instance.LLOCMap)
            {
                Lim.Asg.Nodes.Base.Base @ref = MainDeclaration.Instance.LimFactory.getRef(idIt.Key);

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
        private static void CalculateTotalLineMetrics()
        {
            Lim.Asg.Factory.Iterator it = MainDeclaration.Instance.LimFactory.getIterator();
            while (it.hasNext())
            {
                Lim.Asg.Nodes.Base.Base baseIt = it.getNext();
                if (Lim.Asg.Common.getIsScope(baseIt))
                {
                    Lim.Asg.Nodes.Logical.Scope scope = baseIt as Lim.Asg.Nodes.Logical.Scope;
                    scope.TLLOC = (uint)TLLOC.CollectTLLOC(ref scope);
                    scope.SetLOC();
                }

                if (Lim.Asg.Common.getIsComponent(baseIt))
                {
                    ulong tloc = 0;

                    if (MainDeclaration.Instance.ComponentTLOCMap.ContainsKey(baseIt.Id))
                    {
                        foreach (var itFileKeys in MainDeclaration.Instance.ComponentTLOCMap[baseIt.Id])
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
        private static void CalculateFileLLOC(Dictionary<uint, HashSet<uint>> fileLLOC)
        {
            Parallel.ForEach(fileLLOC, fileIt =>
            {
                if (MainDeclaration.Instance.FileMap.ContainsKey(fileIt.Key))
                {
                    Lim.Asg.Nodes.Physical.File file = MainDeclaration.Instance.LimFactory.getRef(MainDeclaration.Instance.FileMap[fileIt.Key]) as Lim.Asg.Nodes.Physical.File;
                    file.LLOC = (uint)fileIt.Value.Count;
                }
            });
        }

        /// <summary>
        /// Calculate lines metrics to the LIM nodes
        /// </summary>
        public static void Calculate()
        {
            Dictionary<uint, HashSet<uint>> fileLLOC = GetFileLLOC();

            CalculateFileLLOC(fileLLOC);

            // TLLOC + (T)LOC
            CalculateTotalLineMetrics();

            MainDeclaration.Instance.LLOCMap.Clear();
        }
    }
}
