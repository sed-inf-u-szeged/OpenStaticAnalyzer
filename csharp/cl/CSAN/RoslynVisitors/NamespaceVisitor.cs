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

namespace Columbus.CSAN.RoslynVisitors
{
    internal delegate void VisitNode<T>(T node);

    internal partial class RoslynVisitor : CSharpSyntaxWalker
    {
        public static RoslynVisitor Instance;
        private static Dictionary<CSharpSyntaxNode, uint> _map;
        private static CrossEdgeFiller _crossEdgeFiller;

        public static RoslynVisitor GetInstance(Dictionary<CSharpSyntaxNode, uint> csmap, CrossEdgeFiller crossEdgeFiller)
        {
            if (Instance == null) Instance = new RoslynVisitor();
            _map = csmap;
            _crossEdgeFiller = crossEdgeFiller;
            return Instance;
        }


        public INamespaceSymbol GetActualNamespaceFromMergedNamespace(INamespaceSymbol namescpaceSymbol, NamespaceDeclarationSyntax node)
        {
            return Enumerable.FirstOrDefault( namescpaceSymbol.ConstituentNamespaces,
                @namespace =>
                    Enumerable.Any( @namespace.DeclaringSyntaxReferences,
                        @ref => @ref.SyntaxTree.IsEquivalentTo( node.SyntaxTree ) ) );
        }

        public override void VisitNamespaceDeclaration(NamespaceDeclarationSyntax node)
        {
            MainDeclaration.Instance.RoslynWatch.Start();
            INamespaceSymbol namescpaceSymbol = MainDeclaration.Instance.Model.GetDeclaredSymbol(node);
            MainDeclaration.Instance.RoslynWatch.Stop();

            INamespaceSymbol actualNamespaceFromMergedNamespace = GetActualNamespaceFromMergedNamespace(namescpaceSymbol, node);

            Package limNode = SymbolBuilder.BuildDispatch<Package, INamespaceSymbol>(actualNamespaceFromMergedNamespace);

            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap(MainDeclaration.Instance.Component.Id, _map[node], limNode.Id);

            node.CreateCommentNode(actualNamespaceFromMergedNamespace);
            node.CreateCommentForCU();

            base.VisitNamespaceDeclaration(node);

            if (MainDeclaration.Instance.NamespaceStack.Peek() > 0 && MainDeclaration.Instance.UsesStack.Count > 0)
            {
                Package package = (Package)MainDeclaration.Instance.LimFactory.getRef(
                    MainDeclaration.Instance.NamespaceStack.Peek()
                );
                Commons.Common.AddUses(package);
                MainDeclaration.Instance.UsesStack.Pop();
            }

            limNode.SetCLOC(node);
            var location = node.GetLocation();
            location.CalculateFileLevelCommentLines();
            location.CalculateFileLevelNumberOfBranches();
        }
    }
}
