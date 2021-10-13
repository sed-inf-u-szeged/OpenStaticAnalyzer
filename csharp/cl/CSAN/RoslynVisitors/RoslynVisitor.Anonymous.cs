using Columbus.CSAN.Commons;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.Metrics.Size;
using Columbus.CSAN.Utils.Info;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Physical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.CSharp;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        private void BuildAnonymousMethod<T>(T node, VisitNode<T> visit)
           where T : AnonymousFunctionExpressionSyntax
        {
            solutionContext.WatchBag.RoslynWatch.Start();
            IMethodSymbol symbol = fileContext.SemanticModel.GetSymbolInfo(node).Symbol as IMethodSymbol;
            solutionContext.WatchBag.RoslynWatch.Stop();

            Method limNode = null;
            if (symbol != null)
            {
                var anonymousObjectMemberDeclaration = node.GetParent<AnonymousObjectMemberDeclaratorSyntax>();
                limNode = symbolBuilder.BuildDispatch<Method, IMethodSymbol>(symbol, anonymousObjectMemberDeclaration == null);
                solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, projectContext.CsharpMap[node], limNode.Id);
                symbolConverter.CreateCommentNode(node, symbol);

                limNode.Name = fileContext.CrossEdgeFiller.GetOrCreateNode<Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax>(node).Identifier;

                Scope parent;
                if (fileContext.MethodStack.Count > 1)
                {
                    var temp = fileContext.MethodStack.Pop();
                    parent = (Scope)solutionContext.LimFactory.getRef(fileContext.MethodStack.Peek().Id);
                    fileContext.MethodStack.Push(temp);
                }
                else
                {
                    parent = (Scope)solutionContext.LimFactory.getRef(fileContext.ClassStack.Peek().Id);
                }

                limNode.MangledName = parent.MangledName + "." + limNode.Name;
                if (anonymousObjectMemberDeclaration != null)
                {
                    Commons.Common.Safe_Edge(parent, "HasMember", limNode.Id);
                }

                limNode.DemangledName = limNode.MangledName;
                limNode.IsCompilerGenerated = true;
            }
            else
            {
                //TODO write warning/error
                return;
            }

            visit(node as T);

            if (fileContext.MethodStack.Count > 1)
            {
                MethodInfo mi = fileContext.MethodStack.Pop();
                if (node.Body.Kind() == SyntaxKind.Block)
                {
                    mi = Commons.Common.FillMethodMetrics(node.Body, mi);
                }
                else
                {
                    mi.NOB = 1;
                    mi.NOS = 1;
                }
                FillFromMethodStack(mi);
            }

            limNode.SetCLOC(node);
        }

        /// <summary>
        /// (x,y,z) => ......
        /// </summary>
        /// <param name="node"></param>
        public override void VisitParenthesizedLambdaExpression(ParenthesizedLambdaExpressionSyntax node)
        {
            BuildAnonymousMethod(node, base.VisitParenthesizedLambdaExpression);
        }

        /// <summary>
        /// x => ....
        /// </summary>
        /// <param name="node"></param>
        public override void VisitSimpleLambdaExpression(SimpleLambdaExpressionSyntax node)
        {
            BuildAnonymousMethod(node, base.VisitSimpleLambdaExpression);
        }

        /// <summary>
        /// delegate() {
        /// ....
        /// }
        /// </summary>
        /// <param name="node"></param>
        public override void VisitAnonymousMethodExpression(AnonymousMethodExpressionSyntax node)
        {
            BuildAnonymousMethod(node, base.VisitAnonymousMethodExpression);
        }
    }
}
