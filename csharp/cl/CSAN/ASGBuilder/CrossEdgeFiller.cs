using System.Collections.Generic;
using Columbus.CSAN.Contexts;

namespace Columbus.CSAN
{
    using CSHARP = Csharp.Asg;
    using ROSLYNCS = Microsoft.CodeAnalysis.CSharp;

    /// <summary>
    /// Class for setting semantic cross edges in the ASG, eg. method calls, type definitions, etc.
    /// </summary>
    class CrossEdgeFiller : BaseASGBuilder
    {
        public CrossEdgeFiller(FileContext fileContext) : base(fileContext)
        {
        }

        public void AccessorCallFiller(ROSLYNCS.Syntax.AccessorDeclarationSyntax node, ROSLYNCS.Syntax.ElementAccessExpressionSyntax reference)
        {
            if(reference != null)
            {
                var accessorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.AccessorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.ElementAccessExpressionSyntax>(reference).addAccessorCall(accessorDeclaration);           
            }
        }

        public void AccessorCallFiller(ROSLYNCS.Syntax.AccessorDeclarationSyntax node, ROSLYNCS.Syntax.IdentifierNameSyntax reference)
        {
            if(reference != null)
            {
                var accessorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.AccessorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.IdentifierNameSyntax>(reference).addAccessorCall(accessorDeclaration);
            }
        }

        public void ConstructorCallFiller(ROSLYNCS.Syntax.ConstructorDeclarationSyntax node, ROSLYNCS.Syntax.ConstructorInitializerSyntax reference)
        {
            if (reference != null)
            {
                var constructorDeclarartion = GetOrCreateNode<CSHARP.Nodes.Structure.ConstructorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Structure.ConstructorInitializerSyntax>(reference).setConstructorCall(constructorDeclarartion);
            }
        }

        public void ConstructorCallFiller(ROSLYNCS.Syntax.ConstructorDeclarationSyntax node, ROSLYNCS.Syntax.ObjectCreationExpressionSyntax reference)
        {
            if (reference != null)
            {
                var constructorDeclarartion = GetOrCreateNode<CSHARP.Nodes.Structure.ConstructorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.ObjectCreationExpressionSyntax>(reference).setConstructorCall(constructorDeclarartion);
            }
        }

        public void ConversionOperatorCallFiller(ROSLYNCS.Syntax.ConversionOperatorDeclarationSyntax node, ROSLYNCS.Syntax.CastExpressionSyntax reference)
        {
            if(reference != null)
            {
                var conversionOperatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.ConversionOperatorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.CastExpressionSyntax>(reference).setConversionOperatorCall(conversionOperatorDeclaration);
            }
        }

        /// <summary>
        /// Sets the Identifier's declaration
        /// </summary>
        /// <param name="node">A VariableDeclaration, Parameter, ForeachStatement, CatchDeclaration, MethodDeclaration,
        /// LocalFunctionStatement, DelegateDeclaration or SingleVariableDesignation</param>
        /// <param name="reference">The Identifier</param>
        public void DeclarationFiller(ROSLYNCS.CSharpSyntaxNode node, ROSLYNCS.Syntax.IdentifierNameSyntax reference)
        {
            if (reference != null)
            {
                if (!node.Kind().EqualsAny(ROSLYNCS.SyntaxKind.VariableDeclarator,
                    ROSLYNCS.SyntaxKind.Parameter,
                    ROSLYNCS.SyntaxKind.ForEachStatement,
                    ROSLYNCS.SyntaxKind.CatchDeclaration,
                    ROSLYNCS.SyntaxKind.MethodDeclaration,
                    ROSLYNCS.SyntaxKind.DelegateDeclaration,
                    ROSLYNCS.SyntaxKind.SingleVariableDesignation,
                    ROSLYNCS.SyntaxKind.LocalFunctionStatement))
                {
                    WriteMsg.WriteLine("Warning: Invalid node kind ({0}) given to CrossEdgeFiller.DeclarationFiller()", WriteMsg.MsgLevel.Warning, node.Kind());
                    return;
                }
                var declaration = GetOrCreateNode<CSHARP.Nodes.Base.Positioned>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.IdentifierNameSyntax>(reference).setDeclaration(declaration);
            }
        }

        public void EventAccessorCallFiller(ROSLYNCS.Syntax.AccessorDeclarationSyntax node, ROSLYNCS.Syntax.AssignmentExpressionSyntax reference)
        {
            if(reference != null)
            {
                var accessorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.AccessorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.AssignmentExpressionSyntax>(reference).setEventAccessorCall(accessorDeclaration);
            }
        }

        public void LocalFunctionCallFiller(ROSLYNCS.Syntax.LocalFunctionStatementSyntax node, ROSLYNCS.Syntax.InvocationExpressionSyntax reference)
        {
            if (reference != null)
            {
                var localFunction = GetOrCreateNode<CSHARP.Nodes.Statement.LocalFunctionStatementSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.InvocationExpressionSyntax>(reference).setLocalFunctionCall(localFunction);
            }
        }

        public void MethodCallFiller(ROSLYNCS.Syntax.MethodDeclarationSyntax node, ROSLYNCS.Syntax.InvocationExpressionSyntax reference)
        {
            if (reference != null)
            {
                var methodDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.MethodDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.InvocationExpressionSyntax>(reference).setMethodCall(methodDeclaration);
            }
        }

        public void OriginalDefinitionFiller(ROSLYNCS.Syntax.MemberDeclarationSyntax node, ROSLYNCS.Syntax.TypeSyntax reference)
        {
            if (reference != null)
            {
                var memberDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.MemberDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.TypeSyntax>(reference).setOriginalDefinition(memberDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.BinaryExpressionSyntax reference)
        {
            if(reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.BinaryExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.PostfixUnaryExpressionSyntax reference)
        {
            if (reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.PostfixUnaryExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.PrefixUnaryExpressionSyntax reference)
        {
            if (reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.PrefixUnaryExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.AssignmentExpressionSyntax reference)
        {
            if (reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node, true);
                GetOrCreateNode<CSHARP.Nodes.Expression.AssignmentExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }
    }
}
