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

using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Metrics.Size;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void VisitNamedType<T>(BaseTypeDeclarationSyntax node, VisitNode<T> visitor)
            where T : CSharpSyntaxNode
        {
            MainDeclaration.Instance.RoslynWatch.Start();
            INamedTypeSymbol symbol = MainDeclaration.Instance.Model.GetDeclaredSymbol(node);
            MainDeclaration.Instance.RoslynWatch.Stop();

            Class limNode = SymbolBuilder.BuildDispatch<Class, INamedTypeSymbol>(symbol);

            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap(MainDeclaration.Instance.Component.Id, _map[node], limNode.Id);

            node.CreateCommentNode(symbol);

            visitor(node as T);


            if (MainDeclaration.Instance.ClassStack.Count > 0)
            {

                Commons.Common.FillFromClassStack();
            }

            limNode.SetCLOC(node);
        }

        public override void VisitClassDeclaration(ClassDeclarationSyntax node)
        {
            VisitNamedType<ClassDeclarationSyntax>(node, base.VisitClassDeclaration);
        }

        public override void VisitStructDeclaration(StructDeclarationSyntax node)
        {
            VisitNamedType<StructDeclarationSyntax>(node, base.VisitStructDeclaration);
        }

        public override void VisitInterfaceDeclaration(InterfaceDeclarationSyntax node)
        {
            VisitNamedType<InterfaceDeclarationSyntax>(node, base.VisitInterfaceDeclaration);
        }

        public override void VisitEnumDeclaration(EnumDeclarationSyntax node)
        {
            VisitNamedType<EnumDeclarationSyntax>(node, base.VisitEnumDeclaration);
        }

	    public override void VisitDelegateDeclaration( DelegateDeclarationSyntax node )
	    {
			MainDeclaration.Instance.RoslynWatch.Start();
			INamedTypeSymbol symbol = MainDeclaration.Instance.Model.GetDeclaredSymbol(node);
			MainDeclaration.Instance.RoslynWatch.Stop();

            Class limNode = SymbolBuilder.BuildDispatch<Class, INamedTypeSymbol>(symbol);
            
            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap(MainDeclaration.Instance.Component.Id, _map[node], limNode.Id);

            node.CreateCommentNode(symbol);

            base.VisitDelegateDeclaration(node);

            if (MainDeclaration.Instance.ClassStack.Count > 0)
            {

                Commons.Common.FillFromClassStack();
            }

            limNode.SetCLOC(node);
        }
    }
}