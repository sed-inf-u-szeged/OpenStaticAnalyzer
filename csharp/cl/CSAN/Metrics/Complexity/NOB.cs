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

using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

using Columbus.CSAN.Extensions;

namespace Columbus.CSAN.Metrics.Complexity
{
    /// <summary>
    /// McCC metrics expresses the complexity of a  method by the number of independent control 
    /// paths to be found in it. It is a lower bound for the number  of possible executable paths 
    /// in the source code and it is an upper bound for the minimum number of test cases needed for
    /// the complete branch  coverage. 
    /// 
    /// The value of McCC metrics for a method is the number of following instructions plus 1: if, for, 
    /// foreach, while, do-while, case label (label that belongs to a switch instruction), 
    /// catch (handler that belongs to the try block), conditional statement (?:). 
    /// 
    /// The following language elements do not increase  the value: else, try, switch, default 
    /// label (default label that belongs to a switch instruction), finally [2].
    /// </summary>
    sealed class NOB
    {
        private static CSharpSyntaxNode entryPoint;

        public static int Calculate(CSharpSyntaxNode node) 
        {
            entryPoint = node;
            MethodVisitor mv = new MethodVisitor();
            mv.Visit(node);
            return mv.nobcounter;
        }

        class MethodVisitor : CSharpSyntaxWalker
        {
            public int nobcounter = 1;

           public override void VisitWhileStatement(WhileStatementSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               base.VisitWhileStatement(node);
               nobcounter++;
              
           }

           public override void VisitForStatement(ForStatementSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               base.VisitForStatement(node);
               nobcounter++;
           }

           public override void VisitForEachStatement(ForEachStatementSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               base.VisitForEachStatement(node);
               nobcounter++;
           }

           public override void VisitDoStatement(DoStatementSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               base.VisitDoStatement(node);
               nobcounter++;
           }

           public override void VisitIfStatement(IfStatementSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               base.VisitIfStatement(node);
               nobcounter++;
           }

           public override void VisitCatchClause(CatchClauseSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               base.VisitCatchClause(node);
               nobcounter++;
           }

           public override void VisitConditionalExpression(ConditionalExpressionSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               base.VisitConditionalExpression(node);
               nobcounter++;
           }

           public override void VisitCaseSwitchLabel(CaseSwitchLabelSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               nobcounter++;
               base.VisitCaseSwitchLabel(node);
           }

           public override void VisitConditionalAccessExpression(ConditionalAccessExpressionSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               nobcounter++;
                
               base.VisitConditionalAccessExpression(node);
           }

           public override void VisitBinaryExpression(BinaryExpressionSyntax node)
           {
               if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
               if (node.Kind() == SyntaxKind.LogicalAndExpression || node.Kind() == SyntaxKind.LogicalOrExpression || node.Kind() == SyntaxKind.CoalesceExpression)
               {
                   nobcounter++;
               }
               base.VisitBinaryExpression(node);
           }
        }
    }
}
