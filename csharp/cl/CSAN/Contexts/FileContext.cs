using System;
using System.Collections.Generic;
using System.Linq;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Metrics.Size;
using Columbus.CSAN.RoslynVisitors;
using Columbus.CSAN.Utils.Info;
using Microsoft.CodeAnalysis;

namespace Columbus.CSAN.Contexts
{
    class FileContext : AbstractContext
    {
        public ProjectContext ProjectContext { get; }
        public Document Document { get; }
        public SemanticModel SemanticModel { get; }
        public LLOC LlocCalculator { get; }
        public RoslynVisitor RoslynVisitor { get; }

        public Stack<uint> NamespaceStack { get; }
        public Stack<ClassInfo> ClassStack { get; }
        public Stack<MethodInfo> MethodStack { get; }
        public Stack<HashSet<uint>> UsesStack { get; }

        public TreeBuilder TreeBuilder { get; }
        public CrossEdgeFiller CrossEdgeFiller { get; }

        public bool SoftFiltered { get; }

        public FileContext(ProjectContext projectContext, Document document)
        {
            ProjectContext = projectContext;
            Document = document;
            LlocCalculator = new LLOC(this);
            RoslynVisitor = new RoslynVisitor(this);

            NamespaceStack = new Stack<uint>();
            ClassStack = new Stack<ClassInfo>();
            MethodStack = new Stack<MethodInfo>();
            UsesStack = new Stack<HashSet<uint>>();

            NamespaceStack.Push(projectContext.SolutionContext.LimFactory.Root);

            // TODO better stopwatch handling
            projectContext.SolutionContext.WatchBag.RoslynWatch.Start();
            SemanticModel = document.GetSemanticModelAsync().Result; // TODO make async?
            projectContext.SolutionContext.WatchBag.RoslynWatch.Stop();
            LogSemanticModelDiagnostics();

            TreeBuilder = new TreeBuilder(this);
            CrossEdgeFiller = new CrossEdgeFiller(this);

            SoftFiltered = !projectContext.SolutionContext.SoftFilter.IsNecessaryToAnalyse(document.FilePath);
        }

        private void LogSemanticModelDiagnostics()
        {
            foreach (var diagnostic in SemanticModel.GetDiagnostics().Where(d => d.Severity >= DiagnosticSeverity.Warning))
            {
                WriteMsg.WriteLine(diagnostic.ToString(), WriteMsg.MsgLevel.Warning);
            }
        }
    }
}
