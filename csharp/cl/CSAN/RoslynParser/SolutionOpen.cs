using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text.RegularExpressions;
using Columbus.CSAN.Exceptions;
using Columbus.CSAN.Utils;

namespace Columbus.CSAN.RoslynParser
{
    using Microsoft.CodeAnalysis;
    using System.Threading.Tasks;

    class SolutionOpen : AbstractOpen
    {
        public SolutionOpen(string path, string configuration, string platform) : base(path, configuration, platform)
        {
            CssiExtension = Constants.LCSSIEXTENSION;
            msbuildWorkspace.WorkspaceFailed -= workspaceFailedHandler;
        }

        public override void Parse()
        {
            Solution = msbuildWorkspace.OpenSolutionAsync(Path).Result;

            foreach (var diagnostic in msbuildWorkspace.Diagnostics)
            {
                switch (diagnostic.Kind)
                {
                    case WorkspaceDiagnosticKind.Warning:
                        WriteMsg.WriteLine("MSBuild diagnostic warning: " + diagnostic.Message, WriteMsg.MsgLevel.Warning);
                        break;
                    case WorkspaceDiagnosticKind.Failure:
                        var match = Regex.Match(diagnostic.Message, @"Cannot open project '([^']+)' because the file extension '([^']+)' is not associated with a language");
                        if (match.Success)
                        {
                            if (match.Groups[2].EqualsAny(".csproj", ".xproj"))
                                throw new MsBuildException(diagnostic.Message + " Are the required workloads installed properly?");

                            WriteMsg.WriteLine($"Skipping project '{match.Groups[1]}'", WriteMsg.MsgLevel.Debug);
                        }
                        else if (msbuildWorkspace.CurrentSolution.ProjectIds.Count > 0)
                            WriteMsg.WriteLine("MSBuild diagnostic warning: " + diagnostic.Message, WriteMsg.MsgLevel.Warning);
                        else
                            throw new MsBuildException(diagnostic.Message);
                        break;
                    default:
                        throw new UnexpectedEnumValueException(diagnostic.Kind);
                }
            }

            if (!Solution.ProjectIds.Any())
                throw new EmptySolutionException("The opened solution does not contain any projects, there is nothing to analyze. This might be caused by an MsBuild loading error.");

            if (Solution.Projects.All(project => !project.HasDocuments))
                throw new EmptySolutionException("Every project in the opened solution seems to be empty, there is nothing to analyze. This might be caused by an MsBuild loading error.");

            if (Solution.Projects.All(project => project.MetadataReferences.Count < 1))
                throw new MsBuildException("Every project in the opened solution do not have metadata references. This might be caused by an MsBuild loading error.");

            var emptyMetadataProjects = string.Join(", ", Solution.Projects.Where(project => project.MetadataReferences.Count < 1).Select(project => project.AssemblyName));
            if (emptyMetadataProjects.Length > 0)
                WriteMsg.WriteLine($"Failed loading project(s) {emptyMetadataProjects}. Metadata references are empty.", WriteMsg.MsgLevel.Warning);

            ComputeTopologicallySortedProjectDependencies();
            // AddGlobalMetadataReferences();
        }

        public override async Task<bool> BuildSoulution()
        {
            var tasks = new Task<Microsoft.CodeAnalysis.Emit.EmitResult>[TopologicallySortedProjectDependencies.Count];
            for (int i = 0; i < TopologicallySortedProjectDependencies.Count; i++)
            {
                tasks[i] = EmitProject(TopologicallySortedProjectDependencies[i]);
            }

            await Task.WhenAll(tasks);
            return tasks.Any(x => !x.Result.Success);
        }

        static readonly IReadOnlyDictionary<string, int> TargetFrameworkPriorities = new ReadOnlyDictionary<string, int>(new Dictionary<string, int> {
            {"netstandard", 0},
            {"netcoreapp", 1},
            {"net", 2}
        });

        private void ComputeTopologicallySortedProjectDependencies()
        {
            TopologicallySortedProjectDependencies = Solution
                    .GetProjectDependencyGraph()
                    .GetTopologicallySortedProjects()
                    .Select(Solution.GetProject)
                    .Where(t => t.Language == "C#")
                    .GroupBy(project => project.FilePath)
                    .Select(projects =>
                    {
                        return projects.OrderBy(project =>
                        {
                            var match = Regex.Match(project.Name, @"\(([a-z]+)[^)]*\)$");
                            return match.Success ? TargetFrameworkPriorities.GetValueOrDefault(match.Groups[1].Captures[0].Value, 99) : 100;
                        }).First();
                    }) // TODO let the user select via command line argument
                    .ToList();
        }

        private void AddGlobalMetadataReferences()
        {
            var globalReferences = GetGlobalReferences();
            for (int i = 0; i < TopologicallySortedProjectDependencies.Count; i++)
            {
                var project = TopologicallySortedProjectDependencies[i];
                if (project.MetadataReferences.Count > 0)
                    continue;
                // ReSharper disable once PossibleMultipleEnumeration
                foreach (var globalReference in globalReferences)
                {
                    project = project.AddMetadataReference(globalReference);
                    TopologicallySortedProjectDependencies[i] = project;
                    Solution = project.Solution;
                }
            }
        }
    }
}
