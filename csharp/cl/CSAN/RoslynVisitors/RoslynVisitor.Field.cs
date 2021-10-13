using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Utils.Info;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Physical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Attribute = Columbus.Lim.Asg.Nodes.Logical.Attribute;
using MethodInfo = Columbus.CSAN.Utils.Info.MethodInfo;
using Type = Columbus.Lim.Asg.Nodes.Type.Type;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        [MethodImpl( MethodImplOptions.AggressiveInlining )]
        private void VisitField( BaseFieldDeclarationSyntax baseNode )
        {
            foreach ( var variable in baseNode.Declaration.Variables )
            {
                solutionContext.WatchBag.RoslynWatch.Start( );
                var symbol = fileContext.SemanticModel.GetDeclaredSymbol( variable );
                symbolConverter.CreateCommentNode(variable, symbol );
                solutionContext.WatchBag.RoslynWatch.Stop( );

                var limNode = symbolBuilder.BuildDispatch< Attribute, ISymbol >( symbol );
                solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, projectContext.CsharpMap[variable], limNode.Id);
                fileContext.UsesStack.Pop( );
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
            solutionContext.WatchBag.RoslynWatch.Start( );
            var symbol = fileContext.SemanticModel.GetDeclaredSymbol( node );
            solutionContext.WatchBag.RoslynWatch.Stop( );
            symbolConverter.CreateCommentNode(node, symbol );
            var limNode = symbolBuilder.BuildDispatch< Attribute, IFieldSymbol >( symbol );
            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap( projectContext.Component.Id, projectContext.CsharpMap[ node ], limNode.Id );
            fileContext.UsesStack.Pop( );
        }
    }
}
