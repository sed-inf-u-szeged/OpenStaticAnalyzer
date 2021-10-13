using System.Text;
using Columbus.CSAN.Utils;

namespace Columbus.CSAN.RoslynParser
{
    using System.IO;
    using Microsoft.CodeAnalysis;
    using Microsoft.CodeAnalysis.Text;
    using Microsoft.CodeAnalysis.CSharp;

    class FileOpen : AbstractOpen
    {

        public FileOpen(string path, string config, string platform) : base(path, config, platform)
        {
            CssiExtension = Constants.CSSIEXTENSION;
        }

        public override void Parse()
        {
            var projectId = ProjectId.CreateNewId();
            var docId = DocumentId.CreateNewId(projectId);
            string fileName = System.IO.Path.GetFileNameWithoutExtension(Path);
            Solution = msbuildWorkspace.CurrentSolution
                .AddProject(
                    projectId,
                    fileName,
                    fileName + ".dll",
                    LanguageNames.CSharp
                ).AddDocument(
                    docId,
                    fileName, SourceText.From(File.ReadAllText(Path), new UTF8Encoding(false)),
                    new[] {System.IO.Path.GetDirectoryName(Path)},
                    Path
                ).WithProjectFilePath(projectId, System.IO.Path.GetDirectoryName(Path))
                .WithProjectCompilationOptions(projectId,
                    new CSharpCompilationOptions(
                        OutputKind.DynamicallyLinkedLibrary,
                        optimizationLevel: OptimizationLevel.Debug,
                        platform: Platform.X64
                    )
                ).WithProjectOutputFilePath(
                    projectId,
                    System.IO.Path.Combine(System.IO.Path.GetDirectoryName(Path), fileName + ".dll")
                ).AddMetadataReferences(projectId, GetGlobalReferences());
            TopologicallySortedProjectDependencies.AddRange(Solution.Projects);
        }

        public override async System.Threading.Tasks.Task<bool> BuildSoulution()
        {
            var result = await EmitProject(TopologicallySortedProjectDependencies[0]);
            return result.Success;
        }
    }
}
