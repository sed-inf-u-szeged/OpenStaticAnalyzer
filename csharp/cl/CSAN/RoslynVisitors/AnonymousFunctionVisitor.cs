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

using Columbus.CSAN.Commons;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.Metrics.Size;

using Columbus.Lim.Asg.Nodes.Logical;

using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.CSharp;

namespace Columbus.CSAN.RoslynVisitors
{
    internal partial class RoslynVisitor
    {
        public void BuildAnonymousMethod<T>(T node, VisitNode<T> visit)
           where T : AnonymousFunctionExpressionSyntax
        {
            MainDeclaration.Instance.RoslynWatch.Start();
            IMethodSymbol symbol = MainDeclaration.Instance.Model.GetSymbolInfo(node).Symbol as IMethodSymbol;
            MainDeclaration.Instance.RoslynWatch.Stop();

            Method limNode = null;
            if (symbol != null)
            {
                var anonymousObjectMemberDeclaration = node.GetParent<AnonymousObjectMemberDeclaratorSyntax>();
                limNode = SymbolBuilder.BuildDispatch<Method, IMethodSymbol>(symbol, anonymousObjectMemberDeclaration == null);
                MainDeclaration.Instance.LimOrigin.addCompIdCsharpIdLimIdToMap(MainDeclaration.Instance.Component.Id, _map[node], limNode.Id);
                node.CreateCommentNode(symbol);

                limNode.Name = _crossEdgeFiller.GetOrCreateNode<Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax>(node).Identifier;
                var temp = MainDeclaration.Instance.MethodStack.Pop();
                Scope parent = (Scope)MainDeclaration.Instance.LimFactory.getRef(MainDeclaration.Instance.MethodStack.Peek().Id);
                MainDeclaration.Instance.MethodStack.Push(temp);
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

            if (MainDeclaration.Instance.MethodStack.Count > 1)
            {
                Utils.Info.MethodInfo mi = MainDeclaration.Instance.MethodStack.Pop();
                if (node.Body.Kind() == SyntaxKind.Block)
                {
                    mi = Commons.Common.FillMethodMetrics(node.Body, mi);
                }
                else
                {
                    mi.NOB = 1;
                    mi.NOS = 1;
                }
                Commons.Common.FillFromMethodStack(mi);
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
