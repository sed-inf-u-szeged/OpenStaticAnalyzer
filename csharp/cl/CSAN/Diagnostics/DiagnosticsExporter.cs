using System.Collections.Generic;
using System.Collections.Immutable;
using System.Linq;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;
using Columbus.CSAN.Contexts;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.Diagnostics;

namespace Columbus.CSAN.Diagnostics
{
    class DiagnosticsExporter
    {
        private readonly SolutionContext solutionContext;

        public DiagnosticsExporter(SolutionContext solutionContext)
        {
            this.solutionContext = solutionContext;
        }

        public async Task ExportAnalyzerDiagnosticsAsync(Project project, string filePath)
        {
            var diagnostics = await GatherAnalyzerDiagnosticsAsync(project);
            WriteAnalyzerDiagnosticsToFile(filePath, diagnostics);
        }

        private static async Task<ImmutableArray<Microsoft.CodeAnalysis.Diagnostic>> GatherAnalyzerDiagnosticsAsync(Project project)
        {
            var compilation = await project.GetCompilationAsync();

            if (compilation == null)
                throw new ColumbusException(nameof(GatherAnalyzerDiagnosticsAsync), $"Could not get compilation for project {project}!");

            var analyzers = project.AnalyzerReferences
                .Select(reference => reference.GetAnalyzers("C#"))
                .Aggregate(new HashSet<DiagnosticAnalyzer>(), (hashSet, array) =>
                {
                    hashSet.UnionWith(array);
                    return hashSet;
                })
                .ToImmutableArray();

            if (!analyzers.Any())
                return ImmutableArray<Microsoft.CodeAnalysis.Diagnostic>.Empty;

            return await compilation
                .WithAnalyzers(analyzers)
                .GetAllDiagnosticsAsync();
        }

        private void WriteAnalyzerDiagnosticsToFile(string xmlPath, IEnumerable<Microsoft.CodeAnalysis.Diagnostic> diagnostics)
        {
            var list = (from diagnostic in diagnostics
                let lineSpan = diagnostic.Location.GetLineSpan()
                let filePath = solutionContext.ProcessPath(lineSpan.Path)
                where solutionContext.HardFilter.IsNecessaryToAnalyse(filePath) &&
                      solutionContext.SoftFilter.IsNecessaryToAnalyse(filePath)
                select new Diagnostic(diagnostic, lineSpan, filePath)).ToList();

            var serializer = new XmlSerializer(typeof(List<Diagnostic>), new XmlRootAttribute("Diagnostics"));
            using (var writer = XmlWriter.Create(xmlPath, new XmlWriterSettings {Indent = true}))
                serializer.Serialize(writer, list);
        }
    }
}
