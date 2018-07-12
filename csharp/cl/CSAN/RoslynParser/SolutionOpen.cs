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
using System.Linq;

namespace Columbus.CSAN.RoslynParser
{
    using Microsoft.CodeAnalysis;
    using System.Threading.Tasks;
    using System.Reflection;
    using Microsoft.CodeAnalysis.MSBuild;

    class SolutionOpen : AbstractOpen
    {
        private List<Assembly> loadedAssembly;

        public SolutionOpen(string path, string configuration, string platform) : base(path, configuration, platform) { }

        public override void Parse()
        {
            loadedAssembly = new List<Assembly>();

            Solution solution = msbuildWorkspace.OpenSolutionAsync(Path).Result;
            TopologicallySortedProjectDependencies = GetTopologicallySortedProjectDependencies(solution);
            Solution = solution;
        }

        public override async Task<bool> BuildSoulution()
        {
            bool[] results = new bool[TopologicallySortedProjectDependencies.Count];
            int j = 0;
            foreach (var project in TopologicallySortedProjectDependencies)
            {
                var er = await EmitProject(project);
                results[j++] = er.Success;
            }
            return results.Where(t => !t).Count() == 0;
        }

        private List<Project> GetTopologicallySortedProjectDependencies(Solution solution)
        {
            return solution
                    .GetProjectDependencyGraph()
                    .GetTopologicallySortedProjects()
                    .Select(solution.GetProject)
                    .Where(t => t.Language == "C#").ToList();

        }

        public IEnumerable<Assembly> LoadedAssembly { get { return this.loadedAssembly; } }

    }
}