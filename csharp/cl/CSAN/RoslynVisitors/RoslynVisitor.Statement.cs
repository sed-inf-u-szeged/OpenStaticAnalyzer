using System.Collections.Generic;
using System.Linq;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Utils;
using Columbus.CSAN.Utils.Info;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        /// <summary>
        ///     In this section it'll be create:
        ///     - Instantiate edge from object creation expression
        ///     - MethodCall edge from object creation expression
        ///     These edges add to the acutal method from the MethodStack
        /// </summary>
        /// <param name="node"></param>
        public override void VisitObjectCreationExpression( ObjectCreationExpressionSyntax node )
        {
            base.VisitObjectCreationExpression( node );

            //if (node.IsParent<AnonymousObjectMemberDeclaratorSyntax>()) return;
            solutionContext.WatchBag.RoslynWatch.Start( );
            ISymbol symbol = null;
            if ( node.Type.Kind( ) != SyntaxKind.NullableType )
            {
                solutionContext.WatchBag.RoslynWatch.Start( );
                symbol = fileContext.SemanticModel.GetSymbolInfo( node.Type ).Symbol;
                solutionContext.WatchBag.RoslynWatch.Stop( );
            }
            else
            {
                solutionContext.WatchBag.RoslynWatch.Start( );
                symbol =
                    fileContext.SemanticModel.GetSymbolInfo( ( node.Type as NullableTypeSyntax )?.ElementType )
                        .Symbol;
                solutionContext.WatchBag.RoslynWatch.Stop( );
            }

            solutionContext.WatchBag.RoslynWatch.Stop( );
            SyntaxNode synNode = null;
            if ( symbol != null && fileContext.MethodStack.Count > 0 )
            {
                var calledSymbol = symbolConverter.GetDefinition(symbol, out synNode);
                if ( calledSymbol != null && calledSymbol.Kind == symbol.Kind )
                {
                    uint id = 0;
                    if ( calledSymbol.Kind == SymbolKind.NamedType && ( calledSymbol as INamedTypeSymbol ).IsGenericType )
                        id = symbolConverter.GetLimType(symbol, calledSymbol ).Id;
                    else
                        id = symbolConverter.GetLimType(calledSymbol).Id;

                    var pair = new KeyValuePair<uint, bool>( id, false );
                    if ( !fileContext.MethodStack.Peek( ).CanThrow.Contains( pair ) )
                        fileContext.MethodStack.Peek( ).Instantiates.Add( pair );
                    if ( symbol.Kind == SymbolKind.NamedType && synNode.Kind( ) != SyntaxKind.DelegateDeclaration )
                    {
                        fileContext.CrossEdgeFiller.OriginalDefinitionFiller( synNode as MemberDeclarationSyntax, node.Type );
                    }
                }
                else if ( symbol.IsInMetadata( ) )
                {
                    var namedTypeSymbol = symbol as INamedTypeSymbol;
                    if ( namedTypeSymbol != null )
                    {
                        var id = symbolConverter.GetLimType(namedTypeSymbol).Id;
                        solutionContext.LimFactory.setFiltered( id );
                        var pair = new KeyValuePair<uint, bool>( id, true );
                        if ( !fileContext.MethodStack.Peek( ).CanThrow.Contains( pair ) )
                            fileContext.MethodStack.Peek( ).Instantiates.Add( pair );
                    }
                }
            }
            solutionContext.WatchBag.RoslynWatch.Start( );
            symbol = fileContext.SemanticModel.GetSymbolInfo( node ).Symbol;
            solutionContext.WatchBag.RoslynWatch.Stop( );
            if ( symbol != null && fileContext.MethodStack.Count > 0 )
            {
                var calledSymbol = symbolConverter.GetDefinition(symbol, out synNode);
                if ( calledSymbol != null && calledSymbol.Kind == symbol.Kind )
                {
                    if ( calledSymbol.Kind == SymbolKind.Method )
                    {
                        var methodCall =
                            solutionContext.LimFactory.createMethodCall( symbolConverter.ConvertToLimNode(calledSymbol).Id );
                        fileContext.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, false ) );
                        fileContext.CrossEdgeFiller.ConstructorCallFiller( ( ConstructorDeclarationSyntax ) synNode, node );
                    }
                }
                else if ( symbol.IsInMetadata( ) )
                {
                    var methodSymbol = symbol as IMethodSymbol;
                    if ( methodSymbol != null )
                    {
                        Method method = null;
                        if ( methodSymbol.IsGenericMethod )
                            method = symbolBuilder.BuildDispatch< MethodGeneric, IMethodSymbol >( methodSymbol );
                        else
                            method = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( methodSymbol );

                        FillFromMethodStack( fileContext.MethodStack.Pop( ) );
                        solutionContext.LimFactory.setFiltered( method.Id );
                        var methodCall = solutionContext.LimFactory.createMethodCall( method.Id );
                        solutionContext.LimFactory.setFiltered( methodCall.Id );
                        fileContext.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, true ) );
                    }
                }
            }
        }

        /// <summary>
        ///     In this section it'll be create:
        ///     - HasMember edge
        ///     - logical::Class node
        ///     - logical::Method node(s) and HasMember edge to the logical::Class node
        ///     These edges add to the acutal method from
        /// </summary>
        /// <param name="node"></param>
        public override void VisitAnonymousObjectCreationExpression( AnonymousObjectCreationExpressionSyntax node )
        {
            solutionContext.WatchBag.RoslynWatch.Start( );
            var symbol = fileContext.SemanticModel.GetSymbolInfo( node ).Symbol;
            solutionContext.WatchBag.RoslynWatch.Stop( );
            var acb = new AnonimClassBuilder(symbol.ContainingType, node, fileContext);
            acb.Build( );
        }

        /// <summary>
        ///     In this section it'll be create:
        ///     - Throw edge from throw statement
        ///     These edges add to the acutal method from the MethodStack
        /// </summary>
        /// <param name="node"></param>
        public override void VisitThrowStatement( ThrowStatementSyntax node )
        {
            if ( node.Expression != null && fileContext.MethodStack.Count > 0 )
            {
                solutionContext.WatchBag.RoslynWatch.Start( );
                var symbol = fileContext.SemanticModel.GetSymbolInfo( node.Expression ).Symbol;
                solutionContext.WatchBag.RoslynWatch.Stop( );
                if ( symbol != null && symbol.Kind == SymbolKind.Method &&
                     ( ( IMethodSymbol ) symbol ).MethodKind == MethodKind.Constructor )
                {
                    var returnType = symbol.ContainingType;
                    SyntaxNode _node = null;
                    var calledSymbol = symbolConverter.GetDefinition(returnType, out _node);
                    if ( calledSymbol != null && calledSymbol.Kind == returnType.Kind )
                        fileContext.MethodStack.Peek( )
                            .Throws.Add( new KeyValuePair<uint, bool>( symbolConverter.GetLimType(calledSymbol).Id, false ) );
                    else if ( returnType != null )
                        fileContext.MethodStack.Peek( )
                            .Throws.Add( new KeyValuePair<uint, bool>( symbolConverter.GetLimType(returnType).Id, false ) );
                    else if ( returnType.IsInMetadata( ) )
                    {
                        Base throwType = symbolConverter.GetLimType(calledSymbol);
                        solutionContext.LimFactory.setFiltered( throwType.Id );
                        fileContext.MethodStack.Peek( )
                            .Throws.Add( new KeyValuePair<uint, bool>( throwType.Id, true ) );
                    }
                }
            }
            base.VisitThrowStatement( node );
        }

        /// <summary>
        ///     In this section it'll be create:
        ///     - MethodCall edge from identifier
        ///     - AttributeAccess edge from identifier
        ///     - Uses edge from identifier
        ///     These edges add to the acutal method from the MethodStack
        /// </summary>
        /// <param name="node"></param>
        public override void VisitIdentifierName( IdentifierNameSyntax node )
        {
            if ( fileContext.MethodStack.Count <= 0 ) return;
            if ( node.IsParent< ParameterSyntax >( ) ) return;
            if ( node.Identifier.Text != Constants.VAR && node.Identifier.Text != Constants.DYNAMIC )
            {
                solutionContext.WatchBag.RoslynWatch.Start( );
                var symbol = fileContext.SemanticModel.GetSymbolInfo( node ).Symbol;
                solutionContext.WatchBag.RoslynWatch.Stop( );
                if ( symbol != null )
                {
                    switch ( symbol.Kind )
                    {
                        case SymbolKind.Method:
                            if ( !symbol.IsInMetadata( ) &&
                                 ( node.IsParent< InvocationExpressionSyntax, AssignmentExpressionSyntax >( ) ||
                                   node.IsParent< InvocationExpressionSyntax, ArgumentSyntax >( ) ) )
                            {
                                SyntaxNode dec;
                                var methodDef = symbolConverter.GetDefinition(symbol, out dec);
                                fileContext.CrossEdgeFiller.DeclarationFiller( ( CSharpSyntaxNode ) dec, node );
                                if ( methodDef != null && methodDef.Kind == symbol.Kind )
                                    fileContext.UsesStack.Peek( )
                                        .Add( symbolConverter.GetLimType(methodDef.ContainingType).Id );
                            }
                            break;
                        case SymbolKind.Field:
                            CreateAttributeAccessEdge( node, symbol );
                            break;
                        case SymbolKind.Local:
                        case SymbolKind.Parameter:
                            if ( node.IsParent< ParameterListSyntax >( ) ) return;
                            if ( node.Identifier.Text == Constants.VALUE ) return;
                            if ( !symbol.IsInMetadata( ) )
                            {
                                solutionContext.WatchBag.RoslynWatch.Start( );
                                var iConversaitonOpOverLoad = fileContext.SemanticModel.GetConversion( node );
                                solutionContext.WatchBag.RoslynWatch.Stop( );
                                if ( iConversaitonOpOverLoad.MethodSymbol != null )
                                {
                                    if ( iConversaitonOpOverLoad.MethodSymbol.IsInMetadata( ) )
                                        CreateMethodCallEdge( symbol.ContainingSymbol,
                                            iConversaitonOpOverLoad.MethodSymbol,
                                            solutionContext.LimFactory.setFiltered );
                                    else
                                    {
                                        SyntaxNode _tmp;
                                        var calledSymbol = symbolConverter.GetDefinition(iConversaitonOpOverLoad.MethodSymbol, out _tmp, true);
                                        CreateMethodCallEdge( symbol.ContainingSymbol, calledSymbol );
                                    }
                                }
                                var declaration = symbol.DeclaringSyntaxReferences[ 0 ].GetSyntax( );
                                fileContext.CrossEdgeFiller.DeclarationFiller( ( CSharpSyntaxNode ) declaration, node );
                            }
                            break;
                        case SymbolKind.NamedType:
                            CreateUsesEdge( node, symbol, fileContext.CrossEdgeFiller );
                            break;
                        case SymbolKind.Property:
                            var parent = node.GetParent< AnonymousObjectMemberDeclaratorSyntax >( );
                            var needToRun = true;
                            if ( parent != null )
                                needToRun =
                                    parent.Expression.IsEquivalentTo( node.GetParent< ExpressionStatementSyntax >( ) );

                            if ( needToRun ) CreateMethodCallFromProperty( node, symbol, fileContext.CrossEdgeFiller );
                            break;
                        default:
                            break;
                    }
                }
                CreateMethodCallEdgeFromIdentifier( node, fileContext.CrossEdgeFiller );
            }

            base.VisitIdentifierName( node );
        }

        /// <summary>
        ///     In this sectio, it'll be create:
        ///     - MethodCall edge from invocation expression
        ///     These edges add to the acutal method from the MethodStack
        /// </summary>
        /// <param name="node"></param>
        public override void VisitInvocationExpression( InvocationExpressionSyntax node )
        {
            base.VisitInvocationExpression( node );

            //if (node.IsParent<AnonymousObjectMemberDeclaratorSyntax>()) return;
            solutionContext.WatchBag.RoslynWatch.Start( );
            var symbol = fileContext.SemanticModel.GetSymbolInfo( node ).Symbol;
            solutionContext.WatchBag.RoslynWatch.Stop( );
            if ( symbol != null && fileContext.MethodStack.Count > 0 )
            {
                SyntaxNode method;
                var calledSymbol = symbolConverter.GetDefinition(symbol, out method);
                if ( calledSymbol != null && calledSymbol.Kind == symbol.Kind )
                {
                    CreateMethodCallEdge( symbol, calledSymbol );
                    if (method is MethodDeclarationSyntax)
                        fileContext.CrossEdgeFiller.MethodCallFiller((MethodDeclarationSyntax)method, node);
                    else if (method is LocalFunctionStatementSyntax)
                        fileContext.CrossEdgeFiller.LocalFunctionCallFiller((LocalFunctionStatementSyntax)method, node);
                    else
                        throw new ColumbusException(nameof(VisitInvocationExpression), "Unknown InvocationExpression target type: " + method.GetType());
                }
                else if ( calledSymbol != null && calledSymbol.Kind == SymbolKind.NamedType )
                {
                    var possibleDelegateSymbol = ( INamedTypeSymbol ) calledSymbol;
                    if ( possibleDelegateSymbol.TypeKind == TypeKind.Delegate )
                    {
                        CreateMethodCallEdgeFromDelegatePointer( node, possibleDelegateSymbol, projectContext.CsharpMap );
                    }
                }
                else if ( symbol.IsInMetadata( ) && fileContext.MethodStack.Count > 0 )
                {
                    var methodSymbol = symbol as IMethodSymbol;
                    if ( methodSymbol != null )
                    {
                        CreateMethodCallEdge( methodSymbol, symbol,
                            solutionContext.LimFactory.setFiltered );
                    }
                }
            }
        }

        /// <summary>
        ///     In this sectio, it'll be create:
        ///     - MethodCall edge from element access expression (e.x.: a[i])
        ///     These edges add to the acutal method from the MethodStack
        /// </summary>
        /// <param name="node"></param>
        public override void VisitElementAccessExpression( ElementAccessExpressionSyntax node )
        {
            solutionContext.WatchBag.RoslynWatch.Start( );
            var namedType = fileContext.SemanticModel.GetTypeInfo( node.Expression ).Type;
            solutionContext.WatchBag.RoslynWatch.Stop( );
            if ( namedType != null )
            {
                var members = namedType.GetMembers( );
                IPropertySymbol indexer = null;
                foreach ( var member in members )
                {
                    if ( member.Kind != SymbolKind.Property ) continue;
                    var propertySymbol = ( IPropertySymbol ) member;
                    if ( propertySymbol.IsIndexer )
                    {
                        if ( propertySymbol.Parameters.Length == node.ArgumentList.Arguments.Count )
                        {
                            var assignmentExpressionArgumentTypes = node.ArgumentList.Arguments.Select( t =>
                            {
                                solutionContext.WatchBag.RoslynWatch.Start( );
                                var res = fileContext.SemanticModel.GetTypeInfo( t.Expression ).Type;
                                solutionContext.WatchBag.RoslynWatch.Stop( );
                                return res;
                            } ).ToArray( );
                            var propertySymbolParameterType = propertySymbol.Parameters.Select( t => t.Type ).ToArray( );
                            byte sameTypeCounter = 0;
                            for ( var i = 0; i < propertySymbolParameterType.Length; i++ )
                            {
                                if ( assignmentExpressionArgumentTypes[ i ] != null &&
                                     assignmentExpressionArgumentTypes[ i ].Equals( propertySymbolParameterType[ i ] ) )
                                {
                                    sameTypeCounter++;
                                }
                            }
                            if ( sameTypeCounter == propertySymbolParameterType.Length )
                            {
                                indexer = propertySymbol;
                                break;
                            }
                        }
                    }
                }
                if ( indexer != null )
                {
                    CreateMethodCallFromProperty( node, indexer, fileContext.CrossEdgeFiller );
                }
            }

            base.VisitElementAccessExpression( node );
        }

        /// <summary>
        ///     In this sectio, it'll be create:
        ///     - MethodCall edge from cast expression (e.x.: (float)intTypeVariable)
        ///     These edges add to the acutal method from the MethodStack
        /// </summary>
        /// <param name="node"></param>
        public override void VisitCastExpression( CastExpressionSyntax node )
        {
            solutionContext.WatchBag.RoslynWatch.Start( );
            var castedExpressionType = fileContext.SemanticModel.GetTypeInfo( node.Type ).Type;
            var foundConversionOperatorOverload = fileContext.SemanticModel.ClassifyConversion( node.Expression,
                castedExpressionType );
            solutionContext.WatchBag.RoslynWatch.Stop( );
            if ( foundConversionOperatorOverload.MethodSymbol != null )
            {
                if ( foundConversionOperatorOverload.MethodSymbol.IsInMetadata( ) )
                {
                    CreateMethodCallEdge( foundConversionOperatorOverload.MethodSymbol,
                        foundConversionOperatorOverload.MethodSymbol, solutionContext.LimFactory.setFiltered );
                }
                else
                {
                    SyntaxNode calledSyntax;
                    var calledSymbol = symbolConverter.GetDefinition(foundConversionOperatorOverload.MethodSymbol, out calledSyntax, true);
                    // e.x. (Func<int,int>)MethodIdentifier will be skipp
                    if ( calledSymbol.Kind != SymbolKind.NamedType &&
                         calledSyntax.Kind( ) != SyntaxKind.MethodDeclaration )
                    {
                        fileContext.CrossEdgeFiller.ConversionOperatorCallFiller(
                            ( ConversionOperatorDeclarationSyntax ) calledSyntax.Parent, node );
                        CreateMethodCallEdge( calledSymbol, calledSymbol );
                    }
                }
            }
            base.VisitCastExpression( node );
        }
    }
}
