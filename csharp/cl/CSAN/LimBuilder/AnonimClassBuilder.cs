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
using System.Linq;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.Metrics.Size;
using Columbus.CSAN.RoslynVisitors;
using Columbus.CSAN.Utils.Info;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Type;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.LimBuilder
{
    using AnonimClass = AnonymousObjectCreationExpressionSyntax;
    using AnonimClassMember = AnonymousObjectMemberDeclaratorSyntax;

    internal class AnonimClassBuilder
    {
        private readonly INamedTypeSymbol anonimClass;
        private readonly AnonimClass anonymousObjectCreastionExpression;
        private readonly Class limClass;
        private readonly Dictionary< CSharpSyntaxNode, uint > map;

        public AnonimClassBuilder( INamedTypeSymbol anonimClass, ref Dictionary< CSharpSyntaxNode, uint > map,
            AnonimClass anonymousObjectCreastionExpression )
        {
            this.map = map;
            this.anonimClass = anonimClass;
            this.anonymousObjectCreastionExpression = anonymousObjectCreastionExpression;
            limClass = FillClassProperties( anonimClass, anonymousObjectCreastionExpression );
        }

        /// <summary>
        ///     Anonymous class will be built
        /// </summary>
        /// <param name="anonimClass"></param>
        /// <param name="map">C# ASG and LIM ASG mop</param>
        /// <param name="anonymousObjectCreastionExpression"></param>
        public void Build( )
        {
            foreach ( var member in anonimClass.GetMembers( ) )
            {
                if ( member.Kind != SymbolKind.Method ) continue;
                var node = member.ConvertToLimNode( ) as Method;
                if ( ( ( IMethodSymbol ) member ).MethodKind != MethodKind.Constructor )
                    FillGetterMethodNodeProperties( member, node );
                else
                    FillCtorMethodNodeProperties( member, node );
            }
        }

        /// <summary>
        /// </summary>
        /// <param name="anonimClass"></param>
        /// <param name="anonymousObjectCreastionExpression"></param>
        /// <returns></returns>
        private Class FillClassProperties( INamedTypeSymbol anonimClass, AnonimClass anonymousObjectCreastionExpression )
        {
            var limClass = anonimClass.ConvertToLimNode( ) as Class;
            limClass.Accessibility = Types.AccessibilityKind.ackInternal;
            limClass.Name = anonimClass.ToString( );
            var parent =
                ( Scope ) MainDeclaration.Instance.LimFactory.getRef( MainDeclaration.Instance.MethodStack.Peek( ).Id );
            limClass.MangledName = limClass.DemangledName = parent.MangledName + "." + anonimClass;
            limClass.IsCompilerGenerated = true;
            limClass.IsAnonymous = true;
            limClass.ClassKind = Types.ClassKind.clkClass;

            Commons.Common.Safe_Edge( parent, "HasMember", limClass.Id );
            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap( MainDeclaration.Instance.Component.Id,
                map[ anonymousObjectCreastionExpression ], limClass.Id );
            MainDeclaration.Instance.ClassStack.Push( new ClassInfo( limClass.Id ) );
            LLOC.CollectLineInfos( anonymousObjectCreastionExpression );
            MainDeclaration.Instance.ClassStack.Pop( );
            limClass.SetCLOC( anonymousObjectCreastionExpression );
            Commons.Common.AddIsContainedInEdge( limClass, anonymousObjectCreastionExpression );
            Commons.Common.Safe_Edge( limClass, "BelongsTo", MainDeclaration.Instance.Component.Id );

            return limClass;
        }

        /// <summary>
        /// </summary>
        /// <param name="t"></param>
        /// <param name="member"></param>
        /// <returns></returns>
        private bool IsGetterMethod( AnonimClassMember t, ISymbol member )
        {
            if ( t.NameEquals == null ) return false;
            return member.Name.Contains( t.NameEquals.Name.Identifier.Text );
        }

        /// <summary>
        /// </summary>
        /// <param name="member"></param>
        /// <param name="limClass"></param>
        /// <param name="limType"></param>
        /// <returns></returns>
        private Attribute CreateCompilerGeneratedAttributeNode( ISymbol member, Type limType )
        {
            var limAttribute = MainDeclaration.Instance.LimFactory.createAttributeNode( );
            limAttribute.Name = member.Name.Substring( "get_".Length );
            limAttribute.MangledName = limClass.MangledName + "." + limAttribute.Name;
            limAttribute.DemangledName = limAttribute.MangledName;
            limAttribute.addHasType( limType );
            limAttribute.Language = Types.LanguageKind.lnkCsharp;
            limAttribute.IsCompilerGenerated = true;
            limAttribute.addBelongsTo( MainDeclaration.Instance.Component );

            return limAttribute;
        }

        /// <summary>
        ///     Common Method's properties filler
        /// </summary>
        /// <param name="member">Actual Method symbol</param>
        /// <param name="node">Actual</param>
        /// <param name="limClass"></param>
        private void CommonMethodProperties( ISymbol member, Method node )
        {
            node.Name = member.Name;
            node.MangledName = node.DemangledName = string.Format( "{0}.{1}", limClass.MangledName, node.Name );
            node.IsCompilerGenerated = true;
            node.NumberOfBranches = 1;
            node.Accessibility = Types.AccessibilityKind.ackPublic;
            node.addBelongsTo( MainDeclaration.Instance.Component );

            limClass.addHasMember( node );
        }

        /// <summary>
        ///     Fill anonymous class's method properties
        /// </summary>
        /// <param name="member">Method's symbol</param>
        /// <param name="node">Actual node from LIM</param>
        /// <param name="anonymousObjectMemberDeclarator">Symbol's declaring syntax reference</param>
        private void FillGetterMethodNodeProperties( ISymbol member, Method node )
        {
            var anonymousObjectMemberDeclarator =
                anonymousObjectCreastionExpression.Initializers.FirstOrDefault( t => IsGetterMethod( t, member ) );
            //determine the return type in LIM
            if ( anonymousObjectMemberDeclarator != null )
            {
                var returnType = ( ( IMethodSymbol ) member ).ReturnType;
                var limType = returnType.GetLimType( );
                GenerateAttributeAccess( member, node, limType );
                CommonMethodProperties( member, node );
                node.NumberOfStatements = 1;
                node.addReturns( limType );
                node.MethodKind = Types.MethodKind.mekGet;

                MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap(MainDeclaration.Instance.Component.Id, map[anonymousObjectMemberDeclarator], node.Id);
                node.SetCLOC(anonymousObjectMemberDeclarator);
                MainDeclaration.Instance.MethodStack.Push(new MethodInfo(node.Id));
                RoslynVisitors.RoslynVisitor.Instance.Visit(anonymousObjectMemberDeclarator.Expression);
                LLOC.CollectLineInfos(anonymousObjectMemberDeclarator);
                Commons.Common.FillFromMethodStack(MainDeclaration.Instance.MethodStack.Pop(), false);
                anonymousObjectMemberDeclarator.CreateCommentNode(member);
                Commons.Common.AddIsContainedInEdge(node, anonymousObjectMemberDeclarator);
            }
        }

        /// <summary>
        ///     Generate Attribute node and connect to the Method node
        /// </summary>
        /// <param name="member">Actual IMethodSymbol reference</param>
        /// <param name="node">Method node which connect to Attribute through AttributeAccess</param>
        /// <param name="limType">Attribute node's type</param>
        private void GenerateAttributeAccess( ISymbol member, Method node, Type limType )
        {
            var limAttribute = CreateCompilerGeneratedAttributeNode( member, limType );
            var ac = MainDeclaration.Instance.LimFactory.createAttributeAccessNode( limAttribute.Id );
            node.addAccessesAttribute( ac );
            limClass.addHasMember( limAttribute );
        }

        /// <summary>
        ///     Fill anonymous class's constructor properties
        /// </summary>
        /// <param name="member">Constructor smybol</param>
        /// <param name="node">Actual node</param>
        private void FillCtorMethodNodeProperties( ISymbol member, Method node )
        {
            var methodCall = MainDeclaration.Instance.LimFactory.createMethodCall( node.Id );
            MainDeclaration.Instance.MethodStack.Peek( )
                .Calls.Add( new KeyValuePair< uint, bool >( methodCall.Id, false ) );
            MainDeclaration.Instance.MethodStack.Peek( )
                .Instantiates.Add( new KeyValuePair< uint, bool >( member.ContainingType.GetLimType( ).Id, false ) );

            var limClassMembers = limClass.HasMemberListIteratorBegin;
            while ( limClassMembers.getValue( ) != null )
            {
                var limMember = limClassMembers.getValue( );
                if ( Lim.Asg.Common.getIsAttribute( limMember ) )
                {
                    var ac = MainDeclaration.Instance.LimFactory.createAttributeAccessNode( limMember.Id );
                    node.addAccessesAttribute( ac );
                    var p = MainDeclaration.Instance.LimFactory.createParameterNode( );
                    p.setHasType( ( ( Attribute ) limMember ).HasTypeListIteratorBegin.getValue( ) );
                    p.Name = limMember.Name;
                    node.addHasParameter( p );

                    node.NumberOfStatements++;
                }
                limClassMembers = limClassMembers.getNext( );
            }

            CommonMethodProperties( member, node );
            node.MethodKind = Types.MethodKind.mekConstructor;
            Commons.Common.Safe_Edge( node, "Returns", ( ( IMethodSymbol ) member ).ReturnType.GetLimType( ).Id );
        }
    }
}