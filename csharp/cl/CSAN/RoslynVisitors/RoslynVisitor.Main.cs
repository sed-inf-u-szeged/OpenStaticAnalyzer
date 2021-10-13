using System;
using System.Collections.Generic;
using System.Linq;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Contexts;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Utils.Info;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Type = Columbus.Lim.Asg.Nodes.Type.Type;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor : CSharpSyntaxWalker
    {
        private readonly FileContext fileContext;
        private readonly ProjectContext projectContext;
        private readonly SolutionContext solutionContext;
        private readonly SymbolBuilder symbolBuilder;
        private readonly SymbolConverter symbolConverter;
        private readonly EdgeBuilder edgeBuilder;

        public RoslynVisitor (FileContext fileContext)
        {
            this.fileContext = fileContext;
            projectContext = fileContext.ProjectContext;
            solutionContext = projectContext.SolutionContext;

            symbolBuilder = new SymbolBuilder(fileContext);
            symbolConverter = new SymbolConverter(fileContext);
            edgeBuilder = new EdgeBuilder(fileContext);
        }

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

        /// <summary>
        ///     TODO separate
        /// </summary>
        /// <param name="node"></param>
        /// <param name="nodeSymbol"></param>
        /// <param name="getAndSet"></param>
        /// <returns></returns>
        private IMethodSymbol GetCalledAccessor( CSharpSyntaxNode node, ISymbol nodeSymbol, out bool getAndSet )
        {
            getAndSet = false;
            var @ref = ( IPropertySymbol ) nodeSymbol;
            var isUnaryExprOrAssignmentExpr = false;
            IMethodSymbol calledMethod = null;
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
                    if (memberAccess != null)
                        calledMethod = memberAccess.Expression.Contains(node) ? @ref.GetMethod : @ref.SetMethod;
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
                            if (memberAccess != null)
                                calledMethod = memberAccess.Expression.Contains(node) ? @ref.GetMethod : @ref.SetMethod;
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
        /// </summary>
        /// <param name="node"></param>
        /// <param name="crossEdgeFiller"></param>
        private void CreateMethodCallEdgeFromIdentifier( IdentifierNameSyntax node,
            CrossEdgeFiller crossEdgeFiller )
        {  // TODO move these to their own visitor methods instead of fiddling with identifiers
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
        ///     Create crose edge for the Class through the Using edge
        /// </summary>
        /// <param name="node"></param>
        /// <param name="symbol"></param>
        /// <param name="crossEdgeFiller"></param>
        private void CreateUsesEdge( TypeSyntax node, ISymbol symbol, CrossEdgeFiller crossEdgeFiller )
        {
            SyntaxNode tmpNode;
            var reference = symbolConverter.GetDefinition(symbol, out tmpNode);
            if ( reference != null && reference.Kind == symbol.Kind )
            {
                fileContext.UsesStack.Peek( ).Add( symbolConverter.GetLimType(reference).Id );
            }
            else if ( symbol.IsInMetadata( ) )
            {
                var type = symbolConverter.GetLimType(symbol);
                solutionContext.LimFactory.setFiltered( type.Id );
                fileContext.UsesStack.Peek( ).Add( type.Id );
            }
            var baseType = tmpNode as BaseTypeDeclarationSyntax;
            if ( baseType != null )
                crossEdgeFiller.OriginalDefinitionFiller( baseType, node );
        }

        /// <summary>
        ///     Create cross edge for Method through the MethodCall edge
        /// </summary>
        /// <param name="node"></param>
        /// <param name="symbol"></param>
        /// <param name="crossEdgeFiller"></param>
        private void CreateMethodCallFromProperty( CSharpSyntaxNode node, ISymbol symbol,
            CrossEdgeFiller crossEdgeFiller )
        {
            SyntaxNode accessor;
            SyntaxNode property;
            var propertySymbol = symbolConverter.GetDefinition(symbol, out property) as IPropertySymbol;
            bool needAllAccessor;
            var method = GetCalledAccessor( node, symbol, out needAllAccessor );
            if ( needAllAccessor )
            {
                if ( propertySymbol != null && propertySymbol.Kind == symbol.Kind )
                {
                    var calledGetAccessor = propertySymbol.GetMethod;
                    if ( calledGetAccessor != null )
                    {
                        calledGetAccessor = ( IMethodSymbol ) symbolConverter.GetDefinition(calledGetAccessor, out accessor);
                        var methodCall =
                            solutionContext.LimFactory.createMethodCall(
                                symbolConverter.ConvertToLimNode(calledGetAccessor).Id );
                        fileContext.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, false ) );
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
                        calledSetAccessor = (IMethodSymbol)symbolConverter.GetDefinition(calledSetAccessor, out accessor);
                        var methodCall =
                            solutionContext.LimFactory.createMethodCall(
                                symbolConverter.ConvertToLimNode(calledSetAccessor).Id );
                        fileContext.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, false ) );
                        if ( node.Kind( ) == SyntaxKind.IdentifierName )
                            crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                                ( IdentifierNameSyntax ) node );
                        else
                            crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                                ( ElementAccessExpressionSyntax ) node );
                    }
                }
                else if ( symbol.IsInMetadata( ) && fileContext.MethodStack.Count > 0 )
                {
                    var prop = symbol as IPropertySymbol;
                    Method getMethod = null;
                    if ( prop != null && prop.GetMethod != null )
                        getMethod = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( prop.GetMethod );

                    if ( getMethod != null )
                    {
                        solutionContext.LimFactory.setFiltered( getMethod.Id );
                        FillFromMethodStack( fileContext.MethodStack.Pop( ) );
                        var methodCall = solutionContext.LimFactory.createMethodCall( getMethod.Id );
                        solutionContext.LimFactory.setFiltered( methodCall.Id );
                        fileContext.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, true ) );

                        Method setMethod = null;
                        if ( prop.SetMethod != null )
                            setMethod = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( prop.SetMethod );

                        if ( setMethod != null )
                        {
                            solutionContext.LimFactory.setFiltered( setMethod.Id );
                            FillFromMethodStack( fileContext.MethodStack.Pop( ) );
                            methodCall = solutionContext.LimFactory.createMethodCall( setMethod.Id );
                        }
                        solutionContext.LimFactory.setFiltered( methodCall.Id );
                        fileContext.MethodStack.Peek( )
                            .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, true ) );
                    }
                }
            }
            else if ( method != null )
            {
                var calledPropertyAccessor = symbolConverter.GetDefinition(method, out accessor);
                if ( calledPropertyAccessor != null && calledPropertyAccessor.Kind == method.Kind )
                {
                    var methodCall =
                        solutionContext.LimFactory.createMethodCall(
                            symbolConverter.ConvertToLimNode(calledPropertyAccessor).Id );
                    fileContext.MethodStack.Peek( )
                        .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, false ) );
                    if ( node.Kind( ) == SyntaxKind.IdentifierName )
                        crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                            ( IdentifierNameSyntax ) node );
                    else
                        crossEdgeFiller.AccessorCallFiller( ( AccessorDeclarationSyntax ) accessor,
                            ( ElementAccessExpressionSyntax ) node );
                }
                else if ( method.IsInMetadata() && fileContext.MethodStack.Count > 0 )
                {
                    var mth = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( method );
                    FillFromMethodStack( fileContext.MethodStack.Pop( ) );
                    mth.IsCompilerGenerated = true;
                    solutionContext.LimFactory.setFiltered( mth.Id );
                    var methodCall = solutionContext.LimFactory.createMethodCall( mth.Id );
                    solutionContext.LimFactory.setFiltered( methodCall.Id );
                    fileContext.MethodStack.Peek( )
                        .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, true ) );
                }
            }
        }

        /// <summary>
        ///     TODO separte
        /// </summary>
        /// <param name="expressionSyntax"></param>
        /// <param name="expressionKind"></param>
        /// <param name="crossEdgeFiller"></param>
        private void CreateMethodCallFromExpression( ExpressionSyntax expressionSyntax,
            ExpressionKind expressionKind, CrossEdgeFiller crossEdgeFiller )
        {
            if (expressionSyntax == null || expressionSyntax.IsKind(SyntaxKind.SuppressNullableWarningExpression))
                return;

            solutionContext.WatchBag.RoslynWatch.Start();
            var symbol = fileContext.SemanticModel.GetSymbolInfo(expressionSyntax).Symbol;
            solutionContext.WatchBag.RoslynWatch.Stop();
            if (symbol == null)
                return;

            if (symbol.IsInMetadata())
            {
                CreateMethodCallEdge( symbol, symbol, solutionContext.LimFactory.setFiltered );
                return;
            }

            SyntaxNode method;
            var calledSymbol = symbolConverter.GetDefinition(symbol, out method);
            if ( method != null && calledSymbol == null )
            {
                calledSymbol =
                    solutionContext.Solution.GetDocument( method.SyntaxTree )
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

        /// <summary>
        ///     TODO separate
        /// </summary>
        /// <param name="node"></param>
        /// <param name="possibleDelegateSymbol"></param>
        /// <param name="map"></param>
        private void CreateMethodCallEdgeFromDelegatePointer( InvocationExpressionSyntax node,
            INamedTypeSymbol possibleDelegateSymbol, Dictionary<CSharpSyntaxNode, uint> map )
        {
            //var isNeedToFilter = false;
            Scope @class;
            if ( possibleDelegateSymbol.IsGenericType )
                @class = symbolBuilder.BuildDispatch< ClassGeneric, INamedTypeSymbol >( possibleDelegateSymbol );
            else
                @class = symbolBuilder.BuildDispatch< Class, INamedTypeSymbol >( possibleDelegateSymbol );

            @class.IsCompilerGenerated = true;
            Commons.Common.ChangeRealizationLevel( @class );
            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(fileContext.ProjectContext.Component.Id, map[node], @class.Id);

            var member = possibleDelegateSymbol.DelegateInvokeMethod;
            Member calledMethod;
            if ( member.IsGenericMethod )
                calledMethod = symbolBuilder.BuildDispatch< MethodGeneric, IMethodSymbol >( member );
            else
                calledMethod = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( member );
            calledMethod.IsCompilerGenerated = true;

            Commons.Common.ChangeRealizationLevel( ( Scope ) calledMethod );
            Commons.Common.Safe_Edge( @class, "HasMember", calledMethod.Id );

            symbolConverter.CreateCommentNode(possibleDelegateSymbol.DeclaringSyntaxReferences[ 0 ].GetSyntax( ), possibleDelegateSymbol );
            symbolConverter.CreateCommentNode(possibleDelegateSymbol.DeclaringSyntaxReferences[ 0 ].GetSyntax( ), possibleDelegateSymbol.DelegateInvokeMethod );

            if ( fileContext.MethodStack.Count > 1 )
                FillFromMethodStack( fileContext.MethodStack.Pop( ) );
            if ( fileContext.ClassStack.Count > 1 )
                FillFromClassStack( );
            ( ( Method ) calledMethod ).NumberOfBranches = 0;

            //if ( isNeedToFilter ) nodeFilter( calledMethod.Id );
            var methodCall = solutionContext.LimFactory.createMethodCall( calledMethod.Id );
            //if ( isNeedToFilter ) nodeFilter( methodCall.Id );
            fileContext.MethodStack.Peek( )
                .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, false ) );
            var id = symbolConverter.GetLimType(possibleDelegateSymbol).Id;
            //if ( isNeedToFilter ) nodeFilter( id );
            fileContext.MethodStack.Peek( )
                .Instantiates.Add( new KeyValuePair<uint, bool>( id, false ) );
        }

        /// <summary>
        /// </summary>
        /// <param name="symbol"></param>
        /// <param name="calledSymbol"></param>
        /// <param name="nodeFilter"></param>
        private void CreateMethodCallEdge( ISymbol symbol, ISymbol calledSymbol, Action<uint> nodeFilter = null )
        {
            var isNeedToFilter = nodeFilter != null;
            var methodSymbol = symbol as IMethodSymbol;
            Base node;
            if ( methodSymbol != null && methodSymbol.IsGenericMethod )
            {
                node = symbolConverter.GetOrCreateMethodGenericInstance(methodSymbol, calledSymbol as IMethodSymbol );
                var id = solutionContext.LimFactory.createTypeFormerType( node.Id ).Id;
                solutionContext.LimFactory.addTypeFormer( id );
                var type = solutionContext.LimFactory.endType( );
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
                    node = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( ( IMethodSymbol ) calledSymbol );
                    ( ( Member ) node ).IsCompilerGenerated = true;
                    FillFromMethodStack( fileContext.MethodStack.Pop( ) );
                }
                else
                {
                    node = symbolConverter.ConvertToLimNode(calledSymbol);
                }
            }
            if ( isNeedToFilter )
                nodeFilter( node.Id );
            var methodCall = solutionContext.LimFactory.createMethodCall( node.Id );
            if ( isNeedToFilter )
                nodeFilter( methodCall.Id );
            fileContext.MethodStack.Peek( )
                .Calls.Add( new KeyValuePair<uint, bool>( methodCall.Id, isNeedToFilter ) );
        }

        /// <summary>
        ///     Create cross edge for Attribute through the AtrributeAccess edge
        /// </summary>
        /// <param name="node"></param>
        /// <param name="symbol"></param>
        private void CreateAttributeAccessEdge( CSharpSyntaxNode node, ISymbol symbol )
        {
            SyntaxNode field;
            var calledSymbol = symbolConverter.GetDefinition(symbol, out field);
            if (calledSymbol == null || symbol.Kind != calledSymbol.Kind)
                return;

            AttributeAccess attributeAccess;
            if ( node.SyntaxTree.IsEquivalentTo( field.SyntaxTree ) ) // is it in source?
                attributeAccess =
                    solutionContext.LimFactory.createAttributeAccessNode( symbolConverter.ConvertToLimNode(symbol).Id );
            else // is it out source?
                attributeAccess =
                    solutionContext.LimFactory.createAttributeAccessNode(
                        symbolConverter.ConvertToLimNode(calledSymbol).Id );

            fileContext.MethodStack.Peek( )
                .AccessAttribute.Add( new KeyValuePair<uint, bool>( attributeAccess.Id, false ) );
        }

        /// <summary>
        /// Fill Class properties by collection
        /// </summary>
        private void FillFromClassStack()
        {
            ClassInfo classInfo = fileContext.ClassStack.Peek();

            if (classInfo.Id > 0)
            {
                Class clazz = solutionContext.LimFactory.getRef(classInfo.Id) as Class;
                bool firstRun = clazz.IsSubclassIsEmpty;
                foreach (KeyValuePair<uint, bool> subClass in classInfo.IsSubclass)
                {
                    if (subClass.Value) solutionContext.LimFactory.setFiltered(subClass.Key);
                    if (firstRun) clazz.addIsSubclass(subClass.Key);
                    else Commons.Common.Safe_Edge(clazz, "IsSubclass", subClass.Key);
                }

                IEnumerable<uint> IsSubclass = classInfo.IsSubclass.Select(t => t.Key);
                Remove(ref IsSubclass);
                AddUses(clazz);
            }

            fileContext.ClassStack.Pop();
            fileContext.UsesStack.Pop();
        }

        /// <summary>
        /// Calculating metrics to the Method
        /// </summary>
        /// <param name="node">C# syntax node</param>
        private void SetMetrics(CSharpSyntaxNode node)
        {
            MethodInfo mi = fileContext.MethodStack.Pop();
            FillFromMethodStack(Commons.Common.FillMethodMetrics(node, mi));
        }

        /// <summary>
        /// Fill Method properties by collection
        /// </summary>
        /// <param name="methodInfo"></param>
        public void FillFromMethodStack(MethodInfo methodInfo, bool needToPopUsesStack = true)
        {
            Method method = (Method)solutionContext.LimFactory.getRef(methodInfo.Id);

            method.NestingLevel = (ushort)methodInfo.NL;
            method.NestingLevelElseIf = (ushort)methodInfo.NLE;
            method.NumberOfBranches = (ushort)methodInfo.NOB;
            method.NumberOfStatements = (ushort)methodInfo.NOS;

            foreach (KeyValuePair<uint, bool> call in methodInfo.Calls)
            {
                if (call.Value) solutionContext.LimFactory.setFiltered(call.Key);
                Commons.Common.Safe_Edge(method, "Calls", call.Key);
            }
            foreach (KeyValuePair<uint, bool> throws in methodInfo.Throws)
            {
                if (throws.Value) solutionContext.LimFactory.setFiltered(throws.Key);
                Commons.Common.Safe_Edge(method, "Throws", throws.Key);
            }
            foreach (KeyValuePair<uint, bool> canThrows in methodInfo.CanThrow)
            {
                if (canThrows.Value) solutionContext.LimFactory.setFiltered(canThrows.Key);
                Commons.Common.Safe_Edge(method, "CanThrow", canThrows.Key);
            }
            foreach (KeyValuePair<uint, bool> instantiates in methodInfo.Instantiates)
            {
                if (instantiates.Value) solutionContext.LimFactory.setFiltered(instantiates.Key);
                Commons.Common.Safe_Edge(method, "Instantiates", instantiates.Key);
            }
            foreach (KeyValuePair<uint, bool> accessAttribute in methodInfo.AccessAttribute)
            {
                if (accessAttribute.Value) solutionContext.LimFactory.setFiltered(accessAttribute.Key);
                Commons.Common.Safe_Edge(method, "AccessesAttribute", accessAttribute.Key);
            }

            if (!method.ReturnsIsEmpty)
            {
                Type returnType = method.ReturnsListIteratorBegin.getValue();
                if (returnType != null)
                {
                    fileContext.UsesStack.Peek().Remove(returnType.Id);
                }
            }

            if (!method.HasParameterIsEmpty)
            {
                ListIterator<Parameter> paramIt = method.HasParameterListIteratorBegin;
                while (paramIt.getValue() != null)
                {
                    fileContext.UsesStack.Peek().Remove(paramIt.getValue().getHasType());
                    paramIt = paramIt.getNext();
                }
            }

            IEnumerable<uint> _throws = methodInfo.Throws.Select(t => t.Key);
            IEnumerable<uint> _canThrows = methodInfo.CanThrow.Select(t => t.Key);
            IEnumerable<uint> _instantiates = methodInfo.Instantiates.Select(t => t.Key);
            Remove(ref _throws);
            Remove(ref _canThrows);
            Remove(ref _instantiates);

            AddUses(method);

            if (needToPopUsesStack)
                fileContext.UsesStack.Pop();
        }

        /// <summary>
        /// Add uses to the list
        /// </summary>
        /// <param name="member"></param>
        private void AddUses(Member member)
        {
            bool firstRun = member.UsesIsEmpty;
            foreach (uint id in fileContext.UsesStack.Peek())
            {
                if (firstRun)
                    member.addUses(id);
                else
                    Commons.Common.Safe_Edge(member, "Uses", id);
            }
        }

        /// <summary>
        /// Remove uses from the list
        /// </summary>
        /// <param name="ids"></param>
        private void Remove(ref IEnumerable<uint> ids)
        {
            if (fileContext.UsesStack.Count <= 0)
                return;
            foreach (uint id in ids)
                fileContext.UsesStack.Peek().Remove(id);
        }
    }
}
