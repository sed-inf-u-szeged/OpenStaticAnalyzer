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
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        private readonly Dictionary<string, uint> _createdAttribute = new Dictionary<string, uint>( );
        private bool _isAutoProperty;

        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        private void CreateAttributeWithAccessEdge(PropertyDeclarationSyntax node, ISymbol symbol, Method limNode)
        {
            var attrName = node.Identifier.Text;
            var mangleName = symbol.ToString( );
            mangleName = mangleName.Replace( attrName, "<" + attrName + ">k__BackingField" );
            if ( !_createdAttribute.ContainsKey( mangleName ) )
            {
                var attr = solutionContext.LimFactory.createAttributeNode( );
                attr.Name = "<" + attrName + ">k__BackingField";
                attr.IsCompilerGenerated = true;
                attr.IsStatic = symbol.IsStatic;
                _createdAttribute.Add( mangleName, attr.Id );
                attr.MangledName = attr.DemangledName = mangleName;
                attr.addBelongsTo( projectContext.Component );
                attr.Language = Types.LanguageKind.lnkCsharp;
                attr.Accessibility = Types.AccessibilityKind.ackPrivate;
                attr.addHasType( symbolConverter.GetLimType(( ( IPropertySymbol ) symbol ).Type).Id );
                ( ( Scope ) solutionContext.LimFactory.getRef( fileContext.ClassStack.Peek( ).Id ) )
                    .addHasMember( attr );

                // Setting the position of the backing field to the start of the property declaration, ending with
                // the identifier. If we have a property `public string Name { get; set; }`
                // then the position will be the span `public string Name`
                var roslynLocation = node.GetLocation();
                var nodeStartPosition = roslynLocation.GetLineSpan().StartLinePosition;
                var identifierEndPosition = node.Identifier.GetLocation().GetLineSpan().EndLinePosition;
                var limPos = new SourcePosition
                {
                    Line = (uint)nodeStartPosition.Line + 1,
                    Column = (uint)nodeStartPosition.Character + 1,
                    EndLine = (uint)identifierEndPosition.Line + 1,
                    EndColumn = (uint)identifierEndPosition.Character + 1,
                    RealizationLevel = Types.RealizationLevel.relDefines
                };
                edgeBuilder.AddIsContainedInEdge(attr, limPos, roslynLocation);
            }
            var attributeAccess =
                solutionContext.LimFactory.createAttributeAccessNode( _createdAttribute[ mangleName ] );
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
            solutionContext.WatchBag.RoslynWatch.Start( );
            var symbol = fileContext.SemanticModel.GetDeclaredSymbol( node );
            solutionContext.WatchBag.RoslynWatch.Stop( );

            HalsteadAnalyzer halsteadAnalyzer = new HalsteadAnalyzer(fileContext);
            var halstedMetrics = halsteadAnalyzer.Calculate( node );

            var nodeParent = node.GetParent< BasePropertyDeclarationSyntax >( );
            _isAutoProperty = nodeParent.Kind( ) == SyntaxKind.PropertyDeclaration &&
                              IsAutoProperty( nodeParent as PropertyDeclarationSyntax,
                                  symbol.AssociatedSymbol as IPropertySymbol );

            var limNode = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( symbol );
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
                    var overriddenMethodDefinition = symbolConverter.GetDefinition(symbol.OverriddenMethod, out dummyNode);
                    if ( overriddenMethodDefinition != null &&
                         overriddenMethodDefinition.Kind == symbol.OverriddenMethod.Kind )
                    {
                        var overriddenMethodSymbol = ( Method ) symbolConverter.ConvertToLimNode(overriddenMethodDefinition);
                        solutionContext.OverrideRelations.AddOverride(
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
                CreateAttributeWithAccessEdge((PropertyDeclarationSyntax)nodeParent, symbol.AssociatedSymbol, limNode);
            }

            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, projectContext.CsharpMap[ node ], limNode.Id);

            symbolConverter.CreateCommentNode(node, symbol );
            symbolConverter.CreateCommentNode(node.Parent.Parent, symbol );

            base.VisitAccessorDeclaration( node );

            if ( fileContext.MethodStack.Count > 0 )
            {
                SetMetrics( node );
            }
        }

        public override void VisitArrowExpressionClause( ArrowExpressionClauseSyntax node )
        {
            if ( node.Parent.Kind( ) != SyntaxKind.PropertyDeclaration ||
                 node.Parent.Kind( ) != SyntaxKind.IndexerDeclaration ) return;
            solutionContext.WatchBag.RoslynWatch.Start( );
            var propertySymbol = ( IPropertySymbol ) fileContext.SemanticModel.GetDeclaredSymbol( node.Parent );
            solutionContext.WatchBag.RoslynWatch.Stop( );
            var limNode = symbolBuilder.BuildDispatch< Method, IMethodSymbol >( propertySymbol.GetMethod );
            if ( propertySymbol.GetMethod.OverriddenMethod != null )
            {
                if ( propertySymbol.GetMethod.OverriddenMethod.IsInMetadata( ) )
                {
                    solutionContext.OverrideRelations.AddOverride(
                        (Method)symbolConverter.ConvertToLimNode(propertySymbol.GetMethod.OverriddenMethod),
                        limNode
                    );
                }
                else
                {
                    SyntaxNode dummyNode;
                    var overriddenMethodDefinition =
                        symbolConverter.GetDefinition(propertySymbol.GetMethod.OverriddenMethod, out dummyNode);
                    if ( overriddenMethodDefinition != null &&
                         overriddenMethodDefinition.Kind == propertySymbol.GetMethod.OverriddenMethod.Kind )
                    {
                        var overriddenMethodSymbol = ( Method ) symbolConverter.ConvertToLimNode(overriddenMethodDefinition);
                        solutionContext.OverrideRelations.AddOverride(
                            overriddenMethodSymbol,
                            limNode
                        );
                    }
                }
            }
            limNode.SetCLOC( node );

            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, projectContext.CsharpMap[node], limNode.Id);
            symbolConverter.CreateCommentNode(node, propertySymbol.GetMethod );

            base.VisitArrowExpressionClause( node );

            if ( fileContext.MethodStack.Count > 0 )
            {
                SetMetrics( node );
            }
        }
    }
}
