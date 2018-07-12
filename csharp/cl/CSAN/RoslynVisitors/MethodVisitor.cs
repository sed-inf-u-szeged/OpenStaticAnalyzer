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
using Columbus.CSAN.Metrics.Complexity;
using Columbus.CSAN.Metrics.Size;
using Columbus.CSAN.Transformation;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        private void visitMethod< T >( BaseMethodDeclarationSyntax node, VisitNode< T > visitor )
            where T : CSharpSyntaxNode
        {
            MainDeclaration.Instance.RoslynWatch.Start( );
            var symbol = MainDeclaration.Instance.Model.GetDeclaredSymbol( node );
            MainDeclaration.Instance.RoslynWatch.Stop( );

            HalsteadAnalyzer halsteadAnalyzer = new HalsteadAnalyzer();
            var halstedMetrics = halsteadAnalyzer.Calculate(node);

            var limNode = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( symbol );
            limNode.TotalOperands = halstedMetrics.TotalOperands;
            limNode.TotalOperators = halstedMetrics.TotalOperators;
            limNode.DistinctOperands = halstedMetrics.DistinctOperands;
            limNode.DistinctOperators = halstedMetrics.DistinctOperators;
            if ( symbol.OverriddenMethod != null )
            {
                if ( symbol.OverriddenMethod.IsInMetadata( ) )
                {
                    MainDeclaration.Instance
                        .OverrideRelations.AddOverride(
                            ( Method ) symbol.OverriddenMethod.ConvertToLimNode( ),
                            limNode
                        );
                }
                else
                {
                    SyntaxNode dummyNode;
                    var asd = symbol.OverriddenMethod.GetDefinition( out dummyNode );
                    if ( asd != null && asd.Kind == symbol.OverriddenMethod.Kind )
                    {
                        var overriddenMethodSymbol = ( Method ) asd.ConvertToLimNode( );
                        MainDeclaration.Instance
                            .OverrideRelations.AddOverride(
                                overriddenMethodSymbol,
                                limNode
                            );
                    }
                }
            }
            if ( symbol.ContainingType.TypeKind == TypeKind.Interface )
            {
                Commons.Common.ChangeRealizationLevel( limNode );
            }
            if ( symbol.PartialImplementationPart != null )
            {
                Commons.Common.ChangeRealizationLevel( limNode );
                var method = symbol.PartialImplementationPart.IsGenericMethod
                    ? SymbolBuilder.BuildDispatch< MethodGeneric, IMethodSymbol >( symbol.PartialImplementationPart )
                    : SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( symbol.PartialImplementationPart );
                method.NumberOfBranches = 0;
                limNode.setDeclares( method.Id );
                Commons.Common.FillFromMethodStack( MainDeclaration.Instance.MethodStack.Pop( ) );
            }

            if ( node.Kind( ) == SyntaxKind.ConstructorDeclaration )
            {
                var init = ( ( ConstructorDeclarationSyntax ) node ).Initializer;
                if ( init != null )
                {
                    MainDeclaration.Instance.RoslynWatch.Start( );
                    var calleeSymbol = MainDeclaration.Instance.Model.GetSymbolInfo( init ).Symbol;
                    MainDeclaration.Instance.RoslynWatch.Stop( );
                    if ( calleeSymbol != null )
                    {
                        SyntaxNode calledCtor;
                        calleeSymbol.GetDefinition( out calledCtor );
                        EdgeBuilder.CreateMethodCallEdge( symbol, calleeSymbol );
                        if ( calledCtor != null && calledCtor.Kind( ) == SyntaxKind.ConstructorDeclaration )
                            // if the called constructor doesn't exist in the code e.x.: default constructor
                            _crossEdgeFiller.ConstructorCallFiller( ( ConstructorDeclarationSyntax ) calledCtor, init );
                    }
                }
            }

            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap( MainDeclaration.Instance.Component.Id,
                _map[ node ], limNode.Id );
            node.CreateCommentNode( symbol );

            visitor( node as T );

            if ( MainDeclaration.Instance.MethodStack.Count > 0 )
                Commons.Common.SetMetrics( node );

            limNode.SetCLOC( node );
        }

        public override void VisitMethodDeclaration( MethodDeclarationSyntax node )
        {
            visitMethod< MethodDeclarationSyntax >( node, base.VisitMethodDeclaration );
        }

        public override void VisitOperatorDeclaration( OperatorDeclarationSyntax node )
        {
            visitMethod< OperatorDeclarationSyntax >( node, base.VisitOperatorDeclaration );
        }

        public override void VisitConversionOperatorDeclaration( ConversionOperatorDeclarationSyntax node )
        {
            visitMethod< ConversionOperatorDeclarationSyntax >( node, base.VisitConversionOperatorDeclaration );
        }

        public override void VisitConstructorDeclaration( ConstructorDeclarationSyntax node )
        {
            visitMethod< ConstructorDeclarationSyntax >( node, base.VisitConstructorDeclaration );
        }

        public override void VisitDestructorDeclaration( DestructorDeclarationSyntax node )
        {
            visitMethod< DestructorDeclarationSyntax >( node, base.VisitDestructorDeclaration );
        }
    }
}