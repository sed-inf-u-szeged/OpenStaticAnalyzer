using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Columbus.CSAN.Commons;
using Columbus.CSAN.LimBuilder;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Physical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.Text;

namespace Columbus.CSAN.Extensions
{
    /// <summary>
    /// Extension methods fot Microsoft.CodeAnalysis.SyntaxNode objects
    /// </summary>
    static class SyntaxNodeExtension
    {
        public static bool IsClassLevelVariable(this SyntaxNode roslynNode)
        {
            if (roslynNode.Kind() == SyntaxKind.VariableDeclaration || roslynNode.Kind() == SyntaxKind.EnumDeclaration)
            {
                SyntaxNode parent = roslynNode.Parent.Parent;
                if (SyntaxFacts.IsTypeDeclaration(parent.Kind())) return true;
            }
            return false;
        }

        public static bool IsParent<T>(this SyntaxNode node) where T : CSharpSyntaxNode
        {
            while (node != null)
            {
                if (node is T) return true;
                node = node.Parent;
            }
            return false;
        }

        public static bool IsParent<Restriction, UpperBound>(this SyntaxNode node)
        {
            while (node != null)
            {
                if (node is Restriction) return false;
                if (node is UpperBound) return true;
                node = node.Parent;
            }
            return false;
        }

        /// <summary>
        /// Gets the <paramref name="node"/>'s first parent of type <paramref name="T"/>
        /// </summary>
        public static T GetParent<T>(this SyntaxNode node) where T : CSharpSyntaxNode
        {
            while (node != null)
            {
                T n = node as T;
                if (n != null) return n;
                node = node.Parent;
            }
            return null;
        }

        /// <summary>
        /// Gets the <paramref name="node"/>'s first parent of type <paramref name="T"/> or <paramref name="E"/>
        /// </summary>
        public static SyntaxNode GetParent<T, E>(this SyntaxNode node)
            where T : CSharpSyntaxNode
            where E : CSharpSyntaxNode
        {
            var localNode = node;
            while (localNode != null && !(localNode is T) && !(localNode is E))
                localNode = localNode.Parent;
            return localNode;
        }

        public static T GetChild<T>(this SyntaxNode node)
            where T : CSharpSyntaxNode
        {
            T result = null;
            foreach (var childNode in node.ChildNodes())
            {
                if (childNode is T) return (T)childNode;
                result = childNode.GetChild<T>();
            }
            return result;
        }

        public static bool IsContains<T>(this SyntaxNode node) where T : CSharpSyntaxNode
        {
            bool result = false;
            foreach (var child in node.ChildNodes())
            {
                if (child is T) return true;
                result = IsContains<T>(child);
            }
            return result;
        }

        public static bool IsSibling<T>(this SyntaxNode node) where T : CSharpSyntaxNode
        {
            SyntaxNode parentNode = node.Parent;
            foreach (var child in node.ChildNodes())
            {
                if (child.IsEquivalentTo(node)) continue;
                if (child is T) return true;
                foreach (var item in child.ChildNodes())
                {
                    return IsSibling<T>(item);
                }
            }
            return false;
        }

        public static bool IsMethodParameter(this SyntaxNode roslynNode)
        {
            if (roslynNode.Kind() != SyntaxKind.Parameter)
                return false;

            SyntaxNode parent = roslynNode.Parent;
            if (parent != null && parent.Kind() != SyntaxKind.ParameterList)
            {
                parent = parent.Parent;
                if (parent == null || parent.Kind() != SyntaxKind.MethodDeclaration)
                    return false;
            }

            return true;
        }

        public static bool IsAcceptableToInsideNode(this SyntaxNode sNode, SyntaxNode localNode)
        {
            switch (sNode.Kind())
            {
                case SyntaxKind.NamespaceDeclaration:
                    return localNode.IsParent<BaseTypeDeclarationSyntax>()
                           || localNode.IsParent<EnumDeclarationSyntax>()
                           || localNode.IsParent<DelegateDeclarationSyntax>();
                case SyntaxKind.ClassDeclaration:
                case SyntaxKind.InterfaceDeclaration:
                case SyntaxKind.EnumDeclaration:
                case SyntaxKind.StructDeclaration:
                    return localNode.IsParent<BasePropertyDeclarationSyntax>()
                           || localNode.IsParent<BaseMethodDeclarationSyntax>()
                           || localNode.IsParent<AnonymousObjectCreationExpressionSyntax>()
                           || localNode.IsParent<AnonymousFunctionExpressionSyntax>()
                           || (localNode.IsParent<BaseTypeDeclarationSyntax>() && !sNode.IsEquivalentTo(localNode))
                           || (localNode.IsParent<EnumDeclarationSyntax>() && !sNode.IsEquivalentTo(localNode))
                           || localNode.IsParent<BaseFieldDeclarationSyntax>();
                default:
                    if (sNode.IsMethodLevel())
                    {
                        return localNode.IsParent<AnonymousObjectCreationExpressionSyntax>()
                               || localNode.IsParent<AnonymousFunctionExpressionSyntax>();
                    }
                    if (sNode is BasePropertyDeclarationSyntax)
                    {
                        return localNode.IsParent<AccessorDeclarationSyntax>();
                    }
                    break;
            }
            return false;
        }

        public static bool IsParent( this SyntaxNode child, SyntaxNode parent, int depth )
        {
            int localDepth = 0;
            while ( child != null )
            {
                if ( parent.IsEquivalentTo( child ) && localDepth == depth)
                {
                    return true;
                }
                if ( localDepth > depth )
                {
                    break;
                }
                child = child.Parent;
                localDepth++;
            }
            return false;
        }

        public static string GetDocumentationComment(this SyntaxNode sNode)
        {
            var commentTrivias = 
                sNode.DescendantTrivia()
                    .Where(IsAcceptableCommentKind)
                    .Select(trivia => new { trivia, localNode = trivia.Token.Parent })
                    .Where(@t => @t.localNode.IsEquivalentTo(sNode))
                    .Select(@t => @t.trivia);

            return commentTrivias.CollectCommentLines( );
        }

        public static string GetCommentForCU(this SyntaxNode ns, SourceText syntaxTreeText)
        {
            var commentTrivias = 
                syntaxTreeText.Lines.Select( item => ns.SyntaxTree.GetLocation( item.Span ) )
                    .Select( commentLocation => ns.SyntaxTree.GetRoot( ).FindTrivia( commentLocation.SourceSpan.Start ) )
                    .Where( commentTrivia => !IsParent< NamespaceDeclarationSyntax >( commentTrivia.Token.Parent ) )
                    .Where( IsAcceptableCommentKind );

            return commentTrivias.CollectCommentLines( );
        }

        public static string CollectCommentLines( this IEnumerable< SyntaxTrivia > commentTrivias )
        {
            StringBuilder sb = new StringBuilder();
            bool appended = false;
            foreach ( var commentTrivia in commentTrivias )
            {
                if ( !appended )
                {
                    sb.Append( commentTrivia.ToFullString( ) );
                    appended = true;
                }
                else
                {
                    sb.Append( Environment.NewLine + commentTrivia.ToFullString( ) );
                }
            }
            return sb.ToString();
        }

        public static bool IsAcceptableCommentKind(this SyntaxTrivia trivia)
        {
            SyntaxKind knd = trivia.Kind();
            return knd == SyntaxKind.SingleLineCommentTrivia
                   || knd == SyntaxKind.MultiLineCommentTrivia
                   || knd == SyntaxKind.DocumentationCommentExteriorTrivia
                   || knd == SyntaxKind.SingleLineDocumentationCommentTrivia
                   || knd == SyntaxKind.MultiLineDocumentationCommentTrivia;
        }

        public static bool IsMethodLevel(this SyntaxNode node)
        {
            SyntaxKind knd = node.Kind();
            return knd == SyntaxKind.MethodDeclaration
                   || knd == SyntaxKind.ConstructorDeclaration
                   || knd == SyntaxKind.DestructorDeclaration
                   || knd == SyntaxKind.ConversionOperatorDeclaration
                   || knd == SyntaxKind.OperatorDeclaration
                   || knd == SyntaxKind.AddAccessorDeclaration
                   || knd == SyntaxKind.RemoveAccessorDeclaration
                   || knd == SyntaxKind.SetAccessorDeclaration
                   || knd == SyntaxKind.GetAccessorDeclaration;
        }

    }
}
