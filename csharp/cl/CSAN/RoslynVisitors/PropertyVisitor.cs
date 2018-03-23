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
using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Metrics.Complexity;
using Columbus.CSAN.Metrics.Size;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        private readonly Dictionary< string, uint > _createdAttribute = new Dictionary< string, uint >( );
        private bool _isAutoProperty;

        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        private void CreateAttributeWithAccessEdge( BasePropertyDeclarationSyntax node, ISymbol symbol, Method limNode )
        {
            var attrName = ( ( PropertyDeclarationSyntax ) node ).Identifier.Text;
            var mangleName = symbol.ToString( );
            mangleName = mangleName.Replace( attrName, "<" + attrName + ">k__BackingField" );
            if ( !_createdAttribute.ContainsKey( mangleName ) )
            {
                var attr = MainDeclaration.Instance.LimFactory.createAttributeNode( );
                attr.Name = "<" + attrName + ">k__BackingField";
                attr.IsCompilerGenerated = true;
                attr.IsStatic = symbol.IsStatic;
                _createdAttribute.Add( mangleName, attr.Id );
                attr.MangledName = attr.DemangledName = mangleName;
                attr.addBelongsTo( MainDeclaration.Instance.Component );
                attr.Language = Types.LanguageKind.lnkCsharp;
                attr.Accessibility = Types.AccessibilityKind.ackPrivate;
                attr.addHasType( ( ( IPropertySymbol ) symbol ).Type.GetLimType( ).Id );
                ( ( Scope ) MainDeclaration.Instance.LimFactory.getRef( MainDeclaration.Instance.ClassStack.Peek( ).Id ) )
                    .addHasMember( attr );
            }
            var attributeAccess =
                MainDeclaration.Instance.LimFactory.createAttributeAccessNode( _createdAttribute[ mangleName ] );
            limNode.IsCompilerGenerated = true;
            limNode.addAccessesAttribute( attributeAccess );
        }

        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        private bool IsAutoProperty( PropertyDeclarationSyntax node, IPropertySymbol symbol )
        {
            var isAutoProperty = false;
            var hasAccessorList = node.AccessorList != null;
            var hasInitializer = !symbol.IsIndexer && node.Initializer != null;
            var notRegularProperty = !symbol.IsAbstract && !symbol.IsExtern && !symbol.IsIndexer && hasAccessorList;
            AccessorDeclarationSyntax getSyntax = null;
            if ( hasAccessorList )
            {
                foreach ( var accessor in node.AccessorList.Accessors )
                {
                    if ( accessor.Kind( ) == SyntaxKind.GetAccessorDeclaration &&
                         ( getSyntax == null || getSyntax.Keyword.Span.IsEmpty ) )
                    {
                        getSyntax = accessor;
                    }
                    else
                    {
                        continue;
                    }
                    if ( accessor.Body != null )
                    {
                        notRegularProperty = false;
                    }
                }
            }
            else
            {
                notRegularProperty = false;
            }
            if ( notRegularProperty || hasInitializer )
            {
                var hasGetSyntax = getSyntax != null;
                isAutoProperty = notRegularProperty && hasGetSyntax;
            }
            return isAutoProperty;
        }

        public override void VisitAccessorDeclaration( AccessorDeclarationSyntax node )
        {
            MainDeclaration.Instance.RoslynWatch.Start( );
            var symbol = MainDeclaration.Instance.Model.GetDeclaredSymbol( node );
            MainDeclaration.Instance.RoslynWatch.Stop( );

            HalsteadAnalyzer halsteadAnalyzer = new HalsteadAnalyzer( );
            var halstedMetrics = halsteadAnalyzer.Calculate( node );

            var nodeParent = node.GetParent< BasePropertyDeclarationSyntax >( );
            _isAutoProperty = nodeParent.Kind( ) == SyntaxKind.PropertyDeclaration &&
                              IsAutoProperty( nodeParent as PropertyDeclarationSyntax,
                                  symbol.AssociatedSymbol as IPropertySymbol );

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
                    var overriddenMethodDefinition = symbol.OverriddenMethod.GetDefinition( out dummyNode );
                    if ( overriddenMethodDefinition != null &&
                         overriddenMethodDefinition.Kind == symbol.OverriddenMethod.Kind )
                    {
                        var overriddenMethodSymbol = ( Method ) overriddenMethodDefinition.ConvertToLimNode( );
                        MainDeclaration.Instance
                            .OverrideRelations.AddOverride(
                                overriddenMethodSymbol,
                                limNode
                            );
                    }
                }
            }
            limNode.SetCLOC( node );
            limNode.SetCLOC( node.Parent.Parent );

            if ( _isAutoProperty )
            {
                CreateAttributeWithAccessEdge( nodeParent, symbol.AssociatedSymbol, limNode );
            }

            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap( MainDeclaration.Instance.Component.Id,
                _map[ node ], limNode.Id );

            node.CreateCommentNode( symbol );
            node.Parent.Parent.CreateCommentNode( symbol );

            base.VisitAccessorDeclaration( node );

            if ( MainDeclaration.Instance.MethodStack.Count > 0 )
            {
                Commons.Common.SetMetrics( node );
            }
        }

        public override void VisitArrowExpressionClause( ArrowExpressionClauseSyntax node )
        {
            if ( node.Parent.Kind( ) != SyntaxKind.PropertyDeclaration ||
                 node.Parent.Kind( ) != SyntaxKind.IndexerDeclaration ) return;
            MainDeclaration.Instance.RoslynWatch.Start( );
            var propertySymbol = ( IPropertySymbol ) MainDeclaration.Instance.Model.GetDeclaredSymbol( node.Parent );
            MainDeclaration.Instance.RoslynWatch.Stop( );
            var limNode = SymbolBuilder.BuildDispatch< Method, IMethodSymbol >( propertySymbol.GetMethod );
            if ( propertySymbol.GetMethod.OverriddenMethod != null )
            {
                if ( propertySymbol.GetMethod.OverriddenMethod.IsInMetadata( ) )
                {
                    MainDeclaration.Instance
                        .OverrideRelations.AddOverride(
                            ( Method ) propertySymbol.GetMethod.OverriddenMethod.ConvertToLimNode( ),
                            limNode
                        );
                }
                else
                {
                    SyntaxNode dummyNode;
                    var overriddenMethodDefinition =
                        propertySymbol.GetMethod.OverriddenMethod.GetDefinition( out dummyNode );
                    if ( overriddenMethodDefinition != null &&
                         overriddenMethodDefinition.Kind == propertySymbol.GetMethod.OverriddenMethod.Kind )
                    {
                        var overriddenMethodSymbol = ( Method ) overriddenMethodDefinition.ConvertToLimNode( );
                        MainDeclaration.Instance
                            .OverrideRelations.AddOverride(
                                overriddenMethodSymbol,
                                limNode
                            );
                    }
                }
            }
            limNode.SetCLOC( node );

            MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap( MainDeclaration.Instance.Component.Id,
                _map[ node ], limNode.Id );
            node.CreateCommentNode( propertySymbol.GetMethod );

            base.VisitArrowExpressionClause( node );

            if ( MainDeclaration.Instance.MethodStack.Count > 0 )
            {
                Commons.Common.SetMetrics( node );
            }
        }
    }
}