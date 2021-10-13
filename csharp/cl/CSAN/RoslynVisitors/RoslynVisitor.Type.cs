using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Metrics.Size;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void VisitNamedType<T>(BaseTypeDeclarationSyntax node, VisitNode<T> visitor)
            where T : CSharpSyntaxNode
        {
            solutionContext.WatchBag.RoslynWatch.Start();
            INamedTypeSymbol symbol = fileContext.SemanticModel.GetDeclaredSymbol(node);
            solutionContext.WatchBag.RoslynWatch.Stop();

            Class limNode = symbolBuilder.BuildDispatch<Class, INamedTypeSymbol>(symbol);

            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(fileContext.ProjectContext.Component.Id, projectContext.CsharpMap[node], limNode.Id);

            symbolConverter.CreateCommentNode(node, symbol);

            visitor(node as T);


            if (fileContext.ClassStack.Count > 0)
                FillFromClassStack();

            limNode.SetCLOC(node);
        }

        public override void VisitClassDeclaration(ClassDeclarationSyntax node)
        {
            VisitNamedType<ClassDeclarationSyntax>(node, base.VisitClassDeclaration);
        }

        public override void VisitStructDeclaration(StructDeclarationSyntax node)
        {
            VisitNamedType<StructDeclarationSyntax>(node, base.VisitStructDeclaration);
        }

        public override void VisitInterfaceDeclaration(InterfaceDeclarationSyntax node)
        {
            VisitNamedType<InterfaceDeclarationSyntax>(node, base.VisitInterfaceDeclaration);
        }

        public override void VisitEnumDeclaration(EnumDeclarationSyntax node)
        {
            VisitNamedType<EnumDeclarationSyntax>(node, base.VisitEnumDeclaration);
        }

	    public override void VisitDelegateDeclaration( DelegateDeclarationSyntax node )
	    {
			solutionContext.WatchBag.RoslynWatch.Start();
			INamedTypeSymbol symbol = fileContext.SemanticModel.GetDeclaredSymbol(node);
			solutionContext.WatchBag.RoslynWatch.Stop();

            Class limNode = symbolBuilder.BuildDispatch<Class, INamedTypeSymbol>(symbol);
            
            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, projectContext.CsharpMap[node], limNode.Id);

            symbolConverter.CreateCommentNode(node, symbol);

            base.VisitDelegateDeclaration(node);

            if (fileContext.ClassStack.Count > 0)
                FillFromClassStack();

            limNode.SetCLOC(node);
        }
    }
}
