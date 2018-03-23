/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

using System.Collections.Generic;
using System.Linq;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Transformation;
using Columbus.CSAN.Utils;
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
            MainDeclaration.Instance.RoslynWatch.Start( );
            ISymbol symbol = null;
            if ( node.Type.Kind( ) != SyntaxKind.NullableType )
            {
                MainDeclaration.Instance.RoslynWatch.Start( );
                symbol = MainDeclaration.Instance.Model.GetSymbolInfo( node.Type ).Symbol;
                MainDeclaration.Instance.RoslynWatch.Stop( );
            }
            else
            {
                MainDeclaration.Instance.RoslynWatch.Start( );
                symbol =
                    MainDeclaration.Instance.Model.GetSymbolInfo( ( node.Type as NullableTypeSyntax )?.ElementType )
                        .Symbol;
                MainDeclaration.Instance.RoslynWatch.Stop( );
            }

            MainDeclaration.Instance.RoslynWatch.Stop( );
            SyntaxNode synNode = null;
            if ( symbol != null && MainDeclaration.Instance.MethodStack.Count > 0 )
            {
                var calledSymbol = symbol.GetDefinition( out synNode );
                if ( calledSymbol != null && calledSymbol.Kind == symbol.Kind )
                {
                    uint id = 0;
                    if ( calledSymbol.Kind == SymbolKind.NamedType && ( calledSymbol as INamedTypeSymbol ).IsGenericType )
                        id = symbol.GetLimType( calledSymbol ).Id;
                    else
                        id = calledSymbol.GetLimType( ).Id;

                    var pair = new KeyValuePair< uint, bool >( id, false );
                    if ( !MainDeclaration.Instance.MethodStack.Peek( ).CanThrow.Contains( pair ) )
                        MainDeclaration.Instance.MethodStack.Peek( ).Instantiates.Add( pair );
                    if ( symbol.Kind == SymbolKind.NamedType && synNode.Kind( ) != SyntaxKind.DelegateDeclaration )
                    {
                        _crossEdgeFiller.OriginalDefinitionFiller( synNode as MemberDeclarationSyntax, node.Type );
                    }
                }
                else if ( symbol.IsInMetadata( ) )
                {
                    var namedTypeSymbol = symbol as INamedTypeSymbol;
                    if ( namedTypeSymbol != null )
                    {
                        var id = namedTypeSymbol.GetLimType( ).Id;
                        MainDeclaration.Instance.LimFactory.setFiltered( id );
                        var pair = new KeyValuePair< uint, bool >( id, true );
                        if ( !MainDeclaration.Instance.MethodStack.Peek( ).CanThrow.Contains( pair ) )
                            MainDeclaration.Instance.MethodStack.Peek( ).Instantiates.Add( pair );
                    }
                }
            }
            MainDeclaration.Instance.RoslynWatch.Start( );
            symbol = MainDeclaration.Instance.Model.GetSymbolInfo( node ).Symbol;
            MainDeclaration.Instance.RoslynWatch.Stop( );
            if ( symbol != null && MainDeclaration.Instance.MethodStack.Count > 0 )
            {
                var calledSymbol = symbol.GetDefinition( out synNode );
                if ( calledSymbol != null && calledSymbol.Kind == symbol.Kind )
                {
                    if ( calledSymbol.Kind == SymbolKind.Method )
                    {
                        var methodCall =
                            MainDeclaration.Instance.LimFactory.createMethodCall( calledSymbol.ConvertToLimNode( ).Id );
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, false ) );
                        _crossEdgeFiller.ConstructorCallFiller( ( ConstructorDeclarationSyntax ) synNode, node );
                    }
                }
                else if ( symbol.IsInMetadata( ) )
                {
                    var methodSymbol = symbol as IMethodSymbol;
                    if ( methodSymbol != null )
                    {
                        Method method = null;
                        if ( methodSymbol.IsGenericMethod )
                            method = SymbolBuilder.BuildDispatch< MethodGeneric, IMethodSymbol >( methodSymbol );
                        else
                            method = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( methodSymbol );

                        Commons.Common.FillFromMethodStack( MainDeclaration.Instance.MethodStack.Pop( ) );
                        MainDeclaration.Instance.LimFactory.setFiltered( method.Id );
                        var methodCall = MainDeclaration.Instance.LimFactory.createMethodCall( method.Id );
                        MainDeclaration.Instance.LimFactory.setFiltered( methodCall.Id );
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, true ) );
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
            MainDeclaration.Instance.RoslynWatch.Start( );
            var symbol = MainDeclaration.Instance.Model.GetSymbolInfo( node ).Symbol;
            MainDeclaration.Instance.RoslynWatch.Stop( );
            var acb = new AnonimClassBuilder( symbol.ContainingType, ref _map, node );
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
            if ( node.Expression != null && MainDeclaration.Instance.MethodStack.Count > 0 )
            {
                MainDeclaration.Instance.RoslynWatch.Start( );
                var symbol = MainDeclaration.Instance.Model.GetSymbolInfo( node.Expression ).Symbol;
                MainDeclaration.Instance.RoslynWatch.Stop( );
                if ( symbol != null && symbol.Kind == SymbolKind.Method &&
                     ( ( IMethodSymbol ) symbol ).MethodKind == MethodKind.Constructor )
                {
                    var returnType = symbol.ContainingType;
                    SyntaxNode _node = null;
                    var calledSymbol = returnType.GetDefinition( out _node );
                    if ( calledSymbol != null && calledSymbol.Kind == returnType.Kind )
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Throws.Add( new KeyValuePair< uint, bool >( calledSymbol.GetLimType( ).Id, false ) );
                    else if ( returnType != null )
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Throws.Add( new KeyValuePair< uint, bool >( returnType.GetLimType( ).Id, false ) );
                    else if ( returnType.IsInMetadata( ) )
                    {
                        Base throwType = calledSymbol.GetLimType( );
                        MainDeclaration.Instance.LimFactory.setFiltered( throwType.Id );
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Throws.Add( new KeyValuePair< uint, bool >( throwType.Id, true ) );
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
            if ( MainDeclaration.Instance.MethodStack.Count <= 0 ) return;
            if ( node.IsParent< ParameterSyntax >( ) ) return;
            if ( node.Identifier.Text != Constants.VAR && node.Identifier.Text != Constants.DYNAMIC )
            {
                MainDeclaration.Instance.RoslynWatch.Start( );
                var symbol = MainDeclaration.Instance.Model.GetSymbolInfo( node ).Symbol;
                MainDeclaration.Instance.RoslynWatch.Stop( );
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
                                var methodDef = symbol.GetDefinition( out dec );
                                _crossEdgeFiller.DeclarationFiller( ( CSharpSyntaxNode ) dec, node );
                                if ( methodDef != null && methodDef.Kind == symbol.Kind )
                                    MainDeclaration.Instance.UsesStack.Peek( )
                                        .Add( methodDef.ContainingType.GetLimType( ).Id );
                            }
                            break;
                        case SymbolKind.Field:
                            EdgeBuilder.CreateAttributeAccessEdge( node, symbol );
                            break;
                        case SymbolKind.Local:
                        case SymbolKind.Parameter:
                            if ( node.IsParent< ParameterListSyntax >( ) ) return;
                            if ( node.Identifier.Text == Constants.VALUE ) return;
                            if ( !symbol.IsInMetadata( ) )
                            {
                                MainDeclaration.Instance.RoslynWatch.Start( );
                                var iConversaitonOpOverLoad = MainDeclaration.Instance.Model.GetConversion( node );
                                MainDeclaration.Instance.RoslynWatch.Stop( );
                                if ( iConversaitonOpOverLoad.MethodSymbol != null )
                                {
                                    if ( iConversaitonOpOverLoad.MethodSymbol.IsInMetadata( ) )
                                        EdgeBuilder.CreateMethodCallEdge( symbol.ContainingSymbol,
                                            iConversaitonOpOverLoad.MethodSymbol,
                                            MainDeclaration.Instance.LimFactory.setFiltered );
                                    else
                                    {
                                        SyntaxNode _tmp;
                                        var calledSymbol = iConversaitonOpOverLoad.MethodSymbol.GetDefinition(
                                            out _tmp, true );
                                        EdgeBuilder.CreateMethodCallEdge( symbol.ContainingSymbol, calledSymbol );
                                    }
                                }
                                var declaration = symbol.DeclaringSyntaxReferences[ 0 ].GetSyntax( );
                                _crossEdgeFiller.DeclarationFiller( ( CSharpSyntaxNode ) declaration, node );
                            }
                            break;
                        case SymbolKind.NamedType:
                            EdgeBuilder.CreateUsesEdge( node, symbol, _crossEdgeFiller );
                            break;
                        case SymbolKind.Property:
                            var parent = node.GetParent< AnonymousObjectMemberDeclaratorSyntax >( );
                            var needToRun = true;
                            if ( parent != null )
                                needToRun =
                                    parent.Expression.IsEquivalentTo( node.GetParent< ExpressionStatementSyntax >( ) );

                            if ( needToRun ) EdgeBuilder.CreateMethodCallFromProperty( node, symbol, _crossEdgeFiller );
                            break;
                        default:
                            break;
                    }
                }
                EdgeBuilder.CreateMethodCallEdgeFromIdentifier( node, _crossEdgeFiller );
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
            MainDeclaration.Instance.RoslynWatch.Start( );
            var symbol = MainDeclaration.Instance.Model.GetSymbolInfo( node ).Symbol;
            MainDeclaration.Instance.RoslynWatch.Stop( );
            if ( symbol != null && MainDeclaration.Instance.MethodStack.Count > 0 )
            {
                SyntaxNode method;
                var calledSymbol = symbol.GetDefinition( out method );
                if ( calledSymbol != null && calledSymbol.Kind == symbol.Kind )
                {
                    EdgeBuilder.CreateMethodCallEdge( symbol, calledSymbol );
                    _crossEdgeFiller.MethodCallFiller( method as MethodDeclarationSyntax, node );
                }
                else if ( calledSymbol != null && calledSymbol.Kind == SymbolKind.NamedType )
                {
                    var possibleDelegateSymbol = ( INamedTypeSymbol ) calledSymbol;
                    if ( possibleDelegateSymbol.TypeKind == TypeKind.Delegate )
                    {
                        EdgeBuilder.CreateMethodCallEdgeFromDelegatePointer( node, possibleDelegateSymbol, _map );
                    }
                }
                else if ( symbol.IsInMetadata( ) && MainDeclaration.Instance.MethodStack.Count > 0 )
                {
                    var methodSymbol = symbol as IMethodSymbol;
                    if ( methodSymbol != null )
                    {
                        EdgeBuilder.CreateMethodCallEdge( methodSymbol, symbol,
                            MainDeclaration.Instance.LimFactory.setFiltered );
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
            MainDeclaration.Instance.RoslynWatch.Start( );
            var namedType = MainDeclaration.Instance.Model.GetTypeInfo( node.Expression ).Type;
            MainDeclaration.Instance.RoslynWatch.Stop( );
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
                                MainDeclaration.Instance.RoslynWatch.Start( );
                                var res = MainDeclaration.Instance.Model.GetTypeInfo( t.Expression ).Type;
                                MainDeclaration.Instance.RoslynWatch.Stop( );
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
                    EdgeBuilder.CreateMethodCallFromProperty( node, indexer, _crossEdgeFiller );
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
            MainDeclaration.Instance.RoslynWatch.Start( );
            var castedExpressionType = MainDeclaration.Instance.Model.GetTypeInfo( node.Type ).Type;
            var foundConversionOperatorOverload = MainDeclaration.Instance.Model.ClassifyConversion( node.Expression,
                castedExpressionType );
            MainDeclaration.Instance.RoslynWatch.Stop( );
            if ( foundConversionOperatorOverload.MethodSymbol != null )
            {
                SyntaxNode calledSyntax = null;
                if ( foundConversionOperatorOverload.MethodSymbol.IsInMetadata( ) )
                {
                    EdgeBuilder.CreateMethodCallEdge( foundConversionOperatorOverload.MethodSymbol,
                        foundConversionOperatorOverload.MethodSymbol, MainDeclaration.Instance.LimFactory.setFiltered );
                }
                else
                {
                    var calledSymbol = foundConversionOperatorOverload.MethodSymbol.GetDefinition( out calledSyntax,
                        true );
                    // e.x. (Func<int,int>)MethodIdentifier will be skipp
                    if ( calledSymbol.Kind != SymbolKind.NamedType &&
                         calledSyntax.Kind( ) != SyntaxKind.MethodDeclaration )
                    {
                        _crossEdgeFiller.ConversionOperatorCallFiller(
                            ( ConversionOperatorDeclarationSyntax ) calledSyntax.Parent, node );
                        EdgeBuilder.CreateMethodCallEdge( calledSymbol, calledSymbol );
                    }
                }
            }
            base.VisitCastExpression( node );
        }
    }
}