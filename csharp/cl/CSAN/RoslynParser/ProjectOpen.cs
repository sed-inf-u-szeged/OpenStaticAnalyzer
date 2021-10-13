using System.Linq;
using System.Collections.Generic;
using Columbus.CSAN.Utils;

namespace Columbus.CSAN.RoslynParser
{
    using Microsoft.CodeAnalysis;
    using Microsoft.CodeAnalysis.MSBuild;

    class ProjectOpen : AbstractOpen
    {
        public ProjectOpen(string path, string configuration, string platform) : base(path, configuration, platform)
        {
            CssiExtension = Constants.LCSSIEXTENSION;
        }

        public override void Parse()
        {
            var _project = msbuildWorkspace.OpenProjectAsync(Path).Result;
            _project = (_project.ProjectReferences.Count() != 0) ? _project.AddMetadataReferences(GetGlobalReferences()) : _project;
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
