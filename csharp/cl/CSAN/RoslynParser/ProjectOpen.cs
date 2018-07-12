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

using System.Linq;
using System.Collections.Generic;

namespace Columbus.CSAN.RoslynParser
{
    using Microsoft.CodeAnalysis;
    using Microsoft.CodeAnalysis.MSBuild;

    class ProjectOpen : AbstractOpen
    {
        public ProjectOpen(string path, string configuration, string platform) : base(path, configuration, platform) { }

        public override void Parse()
        {
            var _project = msbuildWorkspace.OpenProjectAsync(Path).Result;
            _project = (_project.ProjectReferences.Count() != 0) ? _project.AddMetadataReferences(Util.GetGlobalReferences()) : _project;
            Solution = _project.Solution;
            TopologicallySortedProjectDependencies.Add(_project);
        }

        public override async System.Threading.Tasks.Task<bool> BuildSoulution()
        {
            var result = await EmitProject(TopologicallySortedProjectDependencies[0]);
            return result.Success;
        }


    }
}