using System.Collections.Generic;
using System.IO;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Factory = Columbus.Csharp.Asg.Factory;

namespace Columbus.CSAN.Contexts
{
    class ProjectContext : AbstractContext
    {
        public SolutionContext SolutionContext { get; }
        public Project RoslynProject { get; }
        public Component Component { get; }


        public Factory CsharpFactory { get; }
        public Dictionary<CSharpSyntaxNode, uint> CsharpMap { get; }


        public ProjectContext(SolutionContext solutionContext, Project roslynProject)
        {
            SolutionContext = solutionContext;
            RoslynProject = roslynProject;

            var limFactory = solutionContext.LimFactory;
            Component = limFactory.createComponent(SolutionContext.ProcessPath(RoslynProject.OutputFilePath));

            SetNotFilteredComponentUp(Component);
            Component.ShortName = Path.GetFileName(RoslynProject.OutputFilePath);
            Commons.Common.Safe_Edge(limFactory.getRef(limFactory.Root), "BelongsTo", Component.Id);

            CsharpFactory = new Factory(new StrTable());
            CsharpMap = new Dictionary<CSharpSyntaxNode, uint>();
        }

        /// <summary>
        /// Set up the analysis time and the filter to the component.
        /// </summary>
        /// <param name="node">Actual component</param>
        private void SetNotFilteredComponentUp(Component node)
        {
            SolutionContext.LimFactory.setNotFilteredThisNodeOnly(node.Id);

            if (node.AnalysisTime == Types.AnalysisTimeKind.atkNever)
            {
                node.AnalysisTime = Types.AnalysisTimeKind.atkBefore;
            }

            for (var it = node.ContainsListIteratorBegin; it.getValue() != null; it = it.getNext())
                SetNotFilteredComponentUp(it.getValue());
        }
    }
}
