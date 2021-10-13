using System;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Metrics.Size;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using System.Collections.Generic;
using System.Linq;
using Columbus.CSAN.Contexts;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Physical;

namespace Columbus.CSAN.RoslynVisitors
{
    internal delegate void VisitNode<T>(T node);

    internal partial class RoslynVisitor
    {
        public INamespaceSymbol GetActualNamespaceFromMergedNamespace(INamespaceSymbol namescpaceSymbol, NamespaceDeclarationSyntax node)
        {
            return Enumerable.FirstOrDefault( namescpaceSymbol.ConstituentNamespaces,
                @namespace =>
                    Enumerable.Any( @namespace.DeclaringSyntaxReferences,
                        @ref => @ref.SyntaxTree.IsEquivalentTo( node.SyntaxTree ) ) );
        }

        public override void VisitNamespaceDeclaration(NamespaceDeclarationSyntax node)
        {
            solutionContext.WatchBag.RoslynWatch.Start();
            INamespaceSymbol namescpaceSymbol = fileContext.SemanticModel.GetDeclaredSymbol(node);
            solutionContext.WatchBag.RoslynWatch.Stop();

            INamespaceSymbol actualNamespaceFromMergedNamespace = GetActualNamespaceFromMergedNamespace(namescpaceSymbol, node);

            Package limNode = symbolBuilder.BuildDispatch<Package, INamespaceSymbol>(actualNamespaceFromMergedNamespace);

            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, projectContext.CsharpMap[node], limNode.Id);

            symbolConverter.CreateCommentNode(node, actualNamespaceFromMergedNamespace);
            CreateCommentForCompilationUnit(node);

            base.VisitNamespaceDeclaration(node);

            if (fileContext.UsesStack.Count > 0)
            {
                Package package = (Package)solutionContext.LimFactory.getRef(
                    fileContext.NamespaceStack.Peek()
                );
                AddUses(package);
                fileContext.UsesStack.Pop();
            }

            limNode.SetCLOC(node);
            var location = node.GetLocation();
            CalculateFileLevelCommentLines(location);
            CalculateFileLevelNumberOfBranches(location);
        }

        /// <summary>
        /// Calculate Comment Lines for Comment node
        /// </summary>
        /// <param name="roslynNode"></param>
        private void CalculateFileLevelCommentLines(Location roslynNode)
        {
            File file = symbolConverter.CreateFile(roslynNode);
            var isContainedInIterator = solutionContext.LimFactory.GetReverseEdges().constIteratorBegin(file.Id, Types.EdgeKind.edkMember_IsContainedIn);
            while (isContainedInIterator.getValue() != null)
            {
                var isContainedIn = isContainedInIterator.getValue();
                if (Lim.Asg.Common.getIsScope(isContainedIn))
                {
                    file.CLOC += ((Scope)isContainedIn).CommentLines;
                }
                isContainedInIterator = isContainedInIterator.getNext();
            }
        }

        /// <summary>
        /// Calculate Number of branches for Comment node
        /// </summary>
        /// <param name="roslynNode"></param>
        private void CalculateFileLevelNumberOfBranches(Location roslynNode)
        {
            File file = symbolConverter.CreateFile(roslynNode);
            var isContainedInIterator = solutionContext.LimFactory.GetReverseEdges().constIteratorBegin(file.Id, Types.EdgeKind.edkMember_IsContainedIn);
            while (isContainedInIterator.getValue() != null)
            {
                var isContainedIn = isContainedInIterator.getValue();
                if (Lim.Asg.Common.getIsMethod(isContainedIn))
                {
                    file.NumberOfBranches += ((Method)isContainedIn).NumberOfBranches;
                }
                isContainedInIterator = isContainedInIterator.getNext();
            }


        }

        private void CreateCommentForCompilationUnit(SyntaxNode root)
        {
            string commentForCU = root.GetCommentForCU(root.SyntaxTree.GetText());
            File file = symbolConverter.CreateFile(root.GetLocation());
            if (String.IsNullOrEmpty(commentForCU)) return;
            Comment comment = solutionContext.LimFactory.createCommentNode(commentForCU.TrimEnd('\r', '\n'));
            Commons.Common.Safe_Edge(file, "HasComment", comment.Id);
        }
    }
}
