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

using System.Collections.Generic;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.Transformation
{
    internal static class EdgeBuilder
    {
        /// <summary>
        /// </summary>
        /// <param name="node"></param>
        /// <param name="crossEdgeFiller"></param>
        public static void CreateMethodCallEdgeFromIdentifier( IdentifierNameSyntax node,
            CrossEdgeFiller crossEdgeFiller )
        {
            CreateMethodCallFromExpression( node.GetParent< BinaryExpressionSyntax >( ), ExpressionKind.BinaryExpression,
                crossEdgeFiller );
            CreateMethodCallFromExpression( node.GetParent< PostfixUnaryExpressionSyntax >( ),
                ExpressionKind.PostfixUnaryExpression, crossEdgeFiller );
            CreateMethodCallFromExpression( node.GetParent< PrefixUnaryExpressionSyntax >( ),
                ExpressionKind.PrefixUnaryExpression, crossEdgeFiller );
            CreateMethodCallFromExpression( node.GetParent< AssignmentExpressionSyntax >( ),
                ExpressionKind.AssigmentExpression, crossEdgeFiller );
        }

        /// <summary>
        /// </summary>
        /// <param name="symbol"></param>
        /// <param name="calledSymbol"></param>
        /// <param name="nodeFilter"></param>
        public static void CreateMethodCallEdge( ISymbol symbol, ISymbol calledSymbol, NodeFilter nodeFilter = null )
        {
            var isNeedToFilter = nodeFilter != null;
            var methodSymbol = symbol as IMethodSymbol;
            Base node;
            if ( methodSymbol != null && methodSymbol.IsGenericMethod )
            {
                node = methodSymbol.GetMGI( calledSymbol as IMethodSymbol );
                var id = MainDeclaration.Instance.LimFactory.createTypeFormerType( node.Id ).Id;
                MainDeclaration.Instance.LimFactory.addTypeFormer( id );
                var type = MainDeclaration.Instance.LimFactory.endType( );
                if ( isNeedToFilter )
                {
                    nodeFilter( id );
                    nodeFilter( type.Id );
                }
            }
            else
            {
                if ( isNeedToFilter )
                {
                    node = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( ( IMethodSymbol ) calledSymbol );
                    ( ( Member ) node ).IsCompilerGenerated = true;
                    Commons.Common.FillFromMethodStack( MainDeclaration.Instance.MethodStack.Pop( ) );
                }
                else
                {
                    node = calledSymbol.ConvertToLimNode( );
                }
            }
            if ( isNeedToFilter ) nodeFilter( node.Id );
            var methodCall = MainDeclaration.Instance.LimFactory.createMethodCall( node.Id );
            if ( isNeedToFilter ) nodeFilter( methodCall.Id );
            MainDeclaration.Instance.MethodStack.Peek( )
                .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, isNeedToFilter ) );
        }

        /// <summary>
        ///     TODO separate
        /// </summary>
        /// <param name="node"></param>
        /// <param name="possibleDelegateSymbol"></param>
        /// <param name="map"></param>
        /// <param name="nodeFilter"></param>
        public static void CreateMethodCallEdgeFromDelegatePointer( InvocationExpressionSyntax node,
            INamedTypeSymbol possibleDelegateSymbol, Dictionary< CSharpSyntaxNode, uint > map,
            NodeFilter nodeFilter = null )
        {
            //var isNeedToFilter = false;
            Scope @class;
            if ( possibleDelegateSymbol.IsGenericType )
                @class = SymbolBuilder.BuildDispatch< ClassGeneric, INamedTypeSymbol >( possibleDelegateSymbol );
            else
                @class = SymbolBuilder.BuildDispatch< Class, INamedTypeSymbol >( possibleDelegateSymbol );

            @class.IsCompilerGenerated = true;
            Commons.Common.ChangeRealizationLevel( @class );
            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap( MainDeclaration.Instance.Component.Id,
                map[ node ], @class.Id );

            var member = possibleDelegateSymbol.DelegateInvokeMethod;
            Member calledMethod;
            if ( member.IsGenericMethod )
                calledMethod = SymbolBuilder.BuildDispatch< MethodGeneric, IMethodSymbol >( member );
            else
                calledMethod = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( member );
            calledMethod.IsCompilerGenerated = true;

            Commons.Common.ChangeRealizationLevel( ( Scope ) calledMethod );
            Commons.Common.Safe_Edge( @class, "HasMember", calledMethod.Id );

            possibleDelegateSymbol.DeclaringSyntaxReferences[ 0 ].GetSyntax( )
                .CreateCommentNode( possibleDelegateSymbol );
            possibleDelegateSymbol.DeclaringSyntaxReferences[ 0 ].GetSyntax( )
                .CreateCommentNode( possibleDelegateSymbol.DelegateInvokeMethod );

            if ( MainDeclaration.Instance.MethodStack.Count > 1 )
                Commons.Common.FillFromMethodStack( MainDeclaration.Instance.MethodStack.Pop( ) );
            if ( MainDeclaration.Instance.ClassStack.Count > 1 )
                Commons.Common.FillFromClassStack( );
            ( ( Method ) calledMethod ).NumberOfBranches = 0;

            //if ( isNeedToFilter ) nodeFilter( calledMethod.Id );
            var methodCall = MainDeclaration.Instance.LimFactory.createMethodCall( calledMethod.Id );
            //if ( isNeedToFilter ) nodeFilter( methodCall.Id );
            MainDeclaration.Instance.MethodStack.Peek( )
                .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, false ) );
            var id = possibleDelegateSymbol.GetLimType( ).Id;
            //if ( isNeedToFilter ) nodeFilter( id );
            MainDeclaration.Instance.MethodStack.Peek( )
                .Instantiates.Add( new KeyValuePair< uint, bool >( id, false ) );
        }

        /// <summary>
        ///     Create cross edge for Method through the MethodCall edge
        /// </summary>
        /// <param name="node"></param>
        /// <param name="symbol"></param>
        /// <param name="crossEdgeFiller"></param>
        public static void CreateMethodCallFromProperty( CSharpSyntaxNode node, ISymbol symbol,
            CrossEdgeFiller crossEdgeFiller )
        {
            SyntaxNode accessor;
            SyntaxNode property;
            var propertySymbol = symbol.GetDefinition( out property ) as IPropertySymbol;
            bool needAllAccessor;
            var method = GetCalledAccessor( node, symbol, out needAllAccessor );
            if ( needAllAccessor )
            {
                if ( propertySymbol != null && propertySymbol.Kind == symbol.Kind )
                {
                    var calledGetAccessor = propertySymbol.GetMethod;
                    if ( calledGetAccessor != null )
                    {
                        calledGetAccessor = ( IMethodSymbol ) calledGetAccessor.GetDefinition( out accessor );
                        var methodCall =
                            MainDeclaration.Instance.LimFactory.createMethodCall(
                                calledGetAccessor.ConvertToLimNode( ).Id );
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, false ) );
                        if ( node.Kind( ) == SyntaxKind.IdentifierName )
                            crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                                ( IdentifierNameSyntax ) node );
                        else
                            crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                                ( ElementAccessExpressionSyntax ) node );
                    }
                    var calledSetAccessor = propertySymbol.SetMethod;
                    if ( calledSetAccessor != null )
                    {
                        calledSetAccessor = ( IMethodSymbol ) calledSetAccessor.GetDefinition( out accessor );
                        var methodCall =
                            MainDeclaration.Instance.LimFactory.createMethodCall(
                                calledSetAccessor.ConvertToLimNode( ).Id );
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, false ) );
                        if ( node.Kind( ) == SyntaxKind.IdentifierName )
                            crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                                ( IdentifierNameSyntax ) node );
                        else
                            crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                                ( ElementAccessExpressionSyntax ) node );
                    }
                }
                else if ( symbol.IsInMetadata( ) && MainDeclaration.Instance.MethodStack.Count > 0 )
                {
                    var prop = symbol as IPropertySymbol;
                    Method getMethod = null;
                    if ( prop != null && prop.GetMethod != null )
                        getMethod = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( prop.GetMethod );

                    if ( getMethod != null )
                    {
                        MainDeclaration.Instance.LimFactory.setFiltered( getMethod.Id );
                        Commons.Common.FillFromMethodStack( MainDeclaration.Instance.MethodStack.Pop( ) );
                        var methodCall = MainDeclaration.Instance.LimFactory.createMethodCall( getMethod.Id );
                        MainDeclaration.Instance.LimFactory.setFiltered( methodCall.Id );
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, true ) );

                        Method setMethod = null;
                        if ( prop.SetMethod != null )
                            setMethod = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( prop.SetMethod );

                        if ( setMethod != null )
                        {
                            MainDeclaration.Instance.LimFactory.setFiltered( setMethod.Id );
                            Commons.Common.FillFromMethodStack( MainDeclaration.Instance.MethodStack.Pop( ) );
                            methodCall = MainDeclaration.Instance.LimFactory.createMethodCall( setMethod.Id );
                        }
                        MainDeclaration.Instance.LimFactory.setFiltered( methodCall.Id );
                        MainDeclaration.Instance.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, true ) );
                    }
                }
            }
            else if ( method != null )
            {
                var calledPropertyAccessor = method.GetDefinition( out accessor );
                if ( calledPropertyAccessor != null && calledPropertyAccessor.Kind == method.Kind )
                {
                    var methodCall =
                        MainDeclaration.Instance.LimFactory.createMethodCall(
                            calledPropertyAccessor.ConvertToLimNode( ).Id );
                    MainDeclaration.Instance.MethodStack.Peek( )
                        .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, false ) );
                    if ( node.Kind( ) == SyntaxKind.IdentifierName )
                        crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                            ( IdentifierNameSyntax ) node );
                    else
                        crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                            ( ElementAccessExpressionSyntax ) node );
                }
                else if ( method.IsInMetadata( ) && MainDeclaration.Instance.MethodStack.Count > 0 )
                {
                    var mth = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( method );
                    Commons.Common.FillFromMethodStack( MainDeclaration.Instance.MethodStack.Pop( ) );
                    mth.IsCompilerGenerated = true;
                    MainDeclaration.Instance.LimFactory.setFiltered( mth.Id );
                    var methodCall = MainDeclaration.Instance.LimFactory.createMethodCall( mth.Id );
                    MainDeclaration.Instance.LimFactory.setFiltered( methodCall.Id );
                    MainDeclaration.Instance.MethodStack.Peek( )
                        .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, true ) );
                }
            }
        }

        /// <summary>
        ///     Create crose edge for the Class through the Using edge
        /// </summary>
        /// <param name="node"></param>
        /// <param name="symbol"></param>
        /// <param name="crossEdgeFiller"></param>
        public static void CreateUsesEdge( TypeSyntax node, ISymbol symbol, CrossEdgeFiller crossEdgeFiller )
        {
            SyntaxNode tmpNode;
            var reference = symbol.GetDefinition( out tmpNode );
            if ( reference != null && reference.Kind == symbol.Kind )
            {
                MainDeclaration.Instance.UsesStack.Peek( ).Add( reference.GetLimType( ).Id );
            }
            else if ( symbol.IsInMetadata( ) )
            {
                var type = symbol.GetLimType( );
                MainDeclaration.Instance.LimFactory.setFiltered( type.Id );
                MainDeclaration.Instance.UsesStack.Peek( ).Add( type.Id );
            }
            var baseType = tmpNode as BaseTypeDeclarationSyntax;
            if ( baseType != null )
                crossEdgeFiller.OriginalDefinitionFiller( baseType, node );
        }

        /// <summary>
        ///     Create cross edge for Attribute through the AtrributeAccess edge
        /// </summary>
        /// <param name="node"></param>
        /// <param name="symbol"></param>
        public static void CreateAttributeAccessEdge( CSharpSyntaxNode node, ISymbol symbol )
        {
            SyntaxNode field;
            var calledSymbol = symbol.GetDefinition( out field );
            if ( calledSymbol != null && symbol.Kind == calledSymbol.Kind )
            {
                AttributeAccess attributeAccess;
                if ( node.SyntaxTree.IsEquivalentTo( field.SyntaxTree ) ) // is it in source?
                    attributeAccess =
                        MainDeclaration.Instance.LimFactory.createAttributeAccessNode( symbol.ConvertToLimNode( ).Id );
                else // is it out source?
                    attributeAccess =
                        MainDeclaration.Instance.LimFactory.createAttributeAccessNode(
                            calledSymbol.ConvertToLimNode( ).Id );

                MainDeclaration.Instance.MethodStack.Peek( )
                    .AccessAttribute.Add( new KeyValuePair< uint, bool >( attributeAccess.Id, false ) );
            }
        }

        /// <summary>
        ///     TODO separate
        /// </summary>
        /// <param name="node"></param>
        /// <param name="nodeSymbol"></param>
        /// <param name="getAndSet"></param>
        /// <returns></returns>
        private static IMethodSymbol GetCalledAccessor( CSharpSyntaxNode node, ISymbol nodeSymbol, out bool getAndSet )
        {
            IMethodSymbol calledMethod;
            getAndSet = false;
            var @ref = ( IPropertySymbol ) nodeSymbol;
            var isUnaryExprOrAssignmentExpr = false;
            calledMethod = null;
            if ( @ref.IsReadOnly )
            {
                calledMethod = @ref.GetMethod;
            }
            else if ( @ref.IsWriteOnly )
            {
                calledMethod = @ref.SetMethod;
            }
            else
            {
                var assignmentExpr = node.FirstAncestorOrSelf< AssignmentExpressionSyntax >( );
                var binaryExpr = node.FirstAncestorOrSelf< BinaryExpressionSyntax >( );
                var postUnaryExpr = node.FirstAncestorOrSelf< PostfixUnaryExpressionSyntax >( );
                var prefixUnaryExpr = node.FirstAncestorOrSelf< PrefixUnaryExpressionSyntax >( );
                if ( assignmentExpr != null && assignmentExpr.Left.Contains( node ) )
                {
                    var memberAccess = node.GetParent< MemberAccessExpressionSyntax >( );
                    if ( memberAccess != null )
                    {
                        if ( memberAccess.Expression.Contains( node ) )
                            calledMethod = @ref.GetMethod;
                        else
                            calledMethod = @ref.SetMethod;
                    }
                    else
                        calledMethod = @ref.SetMethod;
                }
                else if ( binaryExpr != null )
                {
                    //prop -= 5 or prop += 5 or other
                    switch ( binaryExpr.OperatorToken.Kind( ) )
                    {
                        case SyntaxKind.PlusEqualsToken:
                        case SyntaxKind.MinusEqualsToken:
                        case SyntaxKind.CaretEqualsToken:
                        case SyntaxKind.PercentEqualsToken:
                        case SyntaxKind.SlashEqualsToken:
                        case SyntaxKind.AsteriskEqualsToken:
                        case SyntaxKind.BarEqualsToken:
                        case SyntaxKind.AmpersandEqualsToken:
                        case SyntaxKind.GreaterThanGreaterThanEqualsToken:
                        case SyntaxKind.LessThanLessThanEqualsToken:
                            isUnaryExprOrAssignmentExpr = true;
                            break;
                        case SyntaxKind.EqualsToken:
                            var memberAccess = node.GetParent< MemberAccessExpressionSyntax >( );
                            if ( memberAccess != null )
                            {
                                if ( memberAccess.Expression.Contains( node ) )
                                    calledMethod = @ref.GetMethod;
                                else
                                    calledMethod = @ref.SetMethod;
                            }
                            else
                                calledMethod = @ref.SetMethod;
                            break;
                        default:
                            calledMethod = @ref.GetMethod;
                            break;
                    }
                }
                else
                {
                    //prop++ or ++prop (prop-- or --prop)
                    if ( postUnaryExpr != null || prefixUnaryExpr != null )
                        isUnaryExprOrAssignmentExpr = true;
                    else
                        calledMethod = @ref.GetMethod;
                }
                if ( isUnaryExprOrAssignmentExpr )
                {
                    getAndSet = true;
                }
            }
            return calledMethod;
        }

        /// <summary>
        ///     TODO separte
        /// </summary>
        /// <param name="expressionSyntax"></param>
        /// <param name="expressionKind"></param>
        /// <param name="crossEdgeFiller"></param>
        private static void CreateMethodCallFromExpression( ExpressionSyntax expressionSyntax,
            ExpressionKind expressionKind, CrossEdgeFiller crossEdgeFiller )
        {
            if ( expressionSyntax != null )
            {
                MainDeclaration.Instance.RoslynWatch.Start( );
                var symbol = MainDeclaration.Instance.Model.GetSymbolInfo( expressionSyntax ).Symbol;
                MainDeclaration.Instance.RoslynWatch.Stop( );
                if ( symbol != null )
                {
                    if ( symbol.IsInMetadata( ) )
                    {
                        CreateMethodCallEdge( symbol, symbol, MainDeclaration.Instance.LimFactory.setFiltered );
                    }
                    else
                    {
                        SyntaxNode method;
                        var calledSymbol = symbol.GetDefinition( out method );
                        if ( method != null && calledSymbol == null )
                        {
                            calledSymbol =
                                MainDeclaration.Instance.Solution.GetDocument( method.SyntaxTree )
                                    .GetSemanticModelAsync( )
                                    .Result.GetDeclaredSymbol( method.Parent );
                            method = method.Parent;
                            // conversation operator overloading has been handled another places
                            if ( method.Kind( ) == SyntaxKind.ConversionOperatorDeclaration ) return;
                        }
                        CreateMethodCallEdge( symbol, calledSymbol );
                        switch ( expressionKind )
                        {
                            case ExpressionKind.BinaryExpression:
                                crossEdgeFiller.OverloadedOperatorCallFiller( ( OperatorDeclarationSyntax ) method,
                                    ( BinaryExpressionSyntax ) expressionSyntax );
                                break;
                            case ExpressionKind.PrefixUnaryExpression:
                                crossEdgeFiller.OverloadedOperatorCallFiller( ( OperatorDeclarationSyntax ) method,
                                    ( PrefixUnaryExpressionSyntax ) expressionSyntax );
                                break;
                            case ExpressionKind.PostfixUnaryExpression:
                                crossEdgeFiller.OverloadedOperatorCallFiller( ( OperatorDeclarationSyntax ) method,
                                    ( PostfixUnaryExpressionSyntax ) expressionSyntax );
                                break;
                            case ExpressionKind.AssigmentExpression:
                                if ( method != null && method.Parent.Kind( ) == SyntaxKind.AccessorList )
                                    crossEdgeFiller.EventAccessorCallFiller( ( AccessorDeclarationSyntax ) method,
                                        ( AssignmentExpressionSyntax ) expressionSyntax );
                                else
                                    crossEdgeFiller.OverloadedOperatorCallFiller( ( OperatorDeclarationSyntax ) method,
                                        ( AssignmentExpressionSyntax ) expressionSyntax );
                                break;
                        }
                    }
                }
            }
        }

        internal delegate void NodeFilter( uint id );

        /// <summary>
        ///     Type of Expression
        /// </summary>
        private enum ExpressionKind : byte
        {
            BinaryExpression,
            PostfixUnaryExpression,
            PrefixUnaryExpression,
            AssigmentExpression
        }
    }
}