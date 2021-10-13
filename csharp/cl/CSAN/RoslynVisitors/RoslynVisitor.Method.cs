using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Contexts;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Metrics.Complexity;
using Columbus.CSAN.Metrics.Size;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Physical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        private void visitMethod< T >( CSharpSyntaxNode node, VisitNode<T> visitor )
            where T : CSharpSyntaxNode
        {
            solutionContext.WatchBag.RoslynWatch.Start( );
            // downcast should always be safe, because node is either a MethodDeclaration or a LocalFunction
            var symbol = (IMethodSymbol)fileContext.SemanticModel.GetDeclaredSymbol( node );
            solutionContext.WatchBag.RoslynWatch.Stop( );

            HalsteadAnalyzer halsteadAnalyzer = new HalsteadAnalyzer(fileContext);
            var halstedMetrics = halsteadAnalyzer.Calculate(node);

            var limNode = symbolBuilder.BuildDispatch<Method, IMethodSymbol>(symbol);
            limNode.TotalOperands = halstedMetrics.TotalOperands;
            limNode.TotalOperators = halstedMetrics.TotalOperators;
            limNode.DistinctOperands = halstedMetrics.DistinctOperands;
            limNode.DistinctOperators = halstedMetrics.DistinctOperators;
            if ( symbol.OverriddenMethod != null )
            {
                if ( symbol.OverriddenMethod.IsInMetadata( ) )
                {
                    solutionContext.OverrideRelations.AddOverride(
                        (Method)symbolConverter.ConvertToLimNode(symbol.OverriddenMethod),
                        limNode
                    );
                }
                else
                {
                    SyntaxNode dummyNode;
                    var asd = symbolConverter.GetDefinition(symbol.OverriddenMethod, out dummyNode);
                    if ( asd != null && asd.Kind == symbol.OverriddenMethod.Kind )
                    {
                        var overriddenMethodSymbol = ( Method ) symbolConverter.ConvertToLimNode(asd);
                        solutionContext.OverrideRelations.AddOverride(
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
                    ? symbolBuilder.BuildDispatch< MethodGeneric, IMethodSymbol >( symbol.PartialImplementationPart )
                    : symbolBuilder.BuildDispatch< Method, IMethodSymbol >( symbol.PartialImplementationPart );
                method.NumberOfBranches = 0;
                limNode.setDeclares( method.Id );
                FillFromMethodStack( fileContext.MethodStack.Pop( ) );
            }

            if ( node.Kind( ) == SyntaxKind.ConstructorDeclaration )
            {
                var init = ( ( ConstructorDeclarationSyntax ) node ).Initializer;
                if ( init != null )
                {
                    solutionContext.WatchBag.RoslynWatch.Start( );
                    var calleeSymbol = fileContext.SemanticModel.GetSymbolInfo( init ).Symbol;
                    solutionContext.WatchBag.RoslynWatch.Stop( );
                    if ( calleeSymbol != null )
                    {
                        SyntaxNode calledCtor;
                        symbolConverter.GetDefinition(calleeSymbol, out calledCtor);
                        CreateMethodCallEdge( symbol, calleeSymbol );
                        if ( calledCtor != null && calledCtor.Kind( ) == SyntaxKind.ConstructorDeclaration )
                            // if the called constructor doesn't exist in the code e.x.: default constructor
                            fileContext.CrossEdgeFiller.ConstructorCallFiller( ( ConstructorDeclarationSyntax ) calledCtor, init );
                    }
                }
            }

            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(fileContext.ProjectContext.Component.Id, projectContext.CsharpMap[node], limNode.Id);
            symbolConverter.CreateCommentNode(node, symbol);

            visitor( node as T );

            if ( fileContext.MethodStack.Count > 0 )
                SetMetrics( node );

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

        public override void VisitLocalFunctionStatement(LocalFunctionStatementSyntax node)
        {
            visitMethod<LocalFunctionStatementSyntax>(node, base.VisitLocalFunctionStatement);
        }
    }
}
