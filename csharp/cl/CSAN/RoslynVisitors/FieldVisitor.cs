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

using System.Reflection;
using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        private void VisitField( BaseFieldDeclarationSyntax baseNode )
        {
            foreach ( var variable in baseNode.Declaration.Variables )
            {
                MainDeclaration.Instance.RoslynWatch.Start( );
                var symbol = MainDeclaration.Instance.Model.GetDeclaredSymbol( variable );
                variable.CreateCommentNode( symbol );
                MainDeclaration.Instance.RoslynWatch.Stop( );

                if ( symbol is IEventSymbol )
                {
                    var type = symbol.GetType( );
                    var property = type.GetProperty( "AssociatedField", BindingFlags.NonPublic |
                                                                        BindingFlags.Instance );
                    symbol = ( IFieldSymbol ) property.GetValue( symbol, null );
                }

                if ( symbol != null )
                {
                    var limNode = SymbolBuilder.BuildDispatch< Attribute, IFieldSymbol >( symbol as IFieldSymbol );
                    MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap(
                        MainDeclaration.Instance.Component.Id, _map[ variable ], limNode.Id );
                    MainDeclaration.Instance.UsesStack.Pop( );
                }
            }
        }

        public override void VisitEventFieldDeclaration( EventFieldDeclarationSyntax node )
        {
            VisitField( node );
        }

        public override void VisitFieldDeclaration( FieldDeclarationSyntax node )
        {
            VisitField( node );
        }

        public override void VisitEnumMemberDeclaration( EnumMemberDeclarationSyntax node )
        {
            MainDeclaration.Instance.RoslynWatch.Start( );
            var symbol = MainDeclaration.Instance.Model.GetDeclaredSymbol( node );
            MainDeclaration.Instance.RoslynWatch.Stop( );
            node.CreateCommentNode( symbol );
            var limNode = SymbolBuilder.BuildDispatch< Attribute, IFieldSymbol >( symbol );
            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap( MainDeclaration.Instance.Component.Id,
                _map[ node ], limNode.Id );
            MainDeclaration.Instance.UsesStack.Pop( );
        }
    }
}