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

namespace Columbus.CSAN.Metrics.Complexity
{
    using Extensions;

    internal class AbstractNL
    {
        protected class MethodVisitor : CSharpSyntaxWalker
        {
            public int result;

            private bool nle;
            private int currentNL;
            private CSharpSyntaxNode entryPoint;
            private CSharpSyntaxNode embeddednessNode;
            private bool embeddednessHasBeenIncreased;
            private bool embeddednessHasBeenDecreased;

            public MethodVisitor(CSharpSyntaxNode entryPoint, bool nle)
            {
                this.nle = nle;
                currentNL = 0;
                embeddednessNode = null;
                this.entryPoint = entryPoint;
                embeddednessHasBeenIncreased = false;
                embeddednessHasBeenDecreased = false;
            }

#region The following instructions are taken into account
            public override void VisitIfStatement(IfStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;

                EligibleForNLE(node);

                if (node.Parent.Kind() != SyntaxKind.ElseClause) IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitIfStatement(node);
                if (node.Parent.Kind() != SyntaxKind.ElseClause) currentNL--;
                EmbeddednessConsideredToDecrease();
            }            
            public override void VisitForStatement(ForStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitForStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitForEachStatement(ForEachStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitForEachStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitDoStatement(DoStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitDoStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitSwitchSection(SwitchSectionSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitSwitchSection(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitConditionalAccessExpression(ConditionalAccessExpressionSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitConditionalAccessExpression(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitTryStatement(TryStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitTryStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitFinallyClause(FinallyClauseSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitFinallyClause(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitUsingStatement(UsingStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                if (node.Statement.Kind() != SyntaxKind.UsingStatement) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitUsingStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitFixedStatement(FixedStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitFixedStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitCheckedStatement(CheckedStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                if (node.Block == null) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitCheckedStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitLockStatement(LockStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                IncreaseHeight();
                EmbeddednessConsideredToIncrease();
                base.VisitLockStatement(node);
                currentNL--;
                EmbeddednessConsideredToDecrease();
            }
            public override void VisitBlock(BlockSyntax node)
            {
                if (node.Parent.Kind() == SyntaxKind.Block)
                {
                    IncreaseHeight();
                    EmbeddednessConsideredToIncrease();
                }
                base.VisitBlock(node);
                if (node.Parent.Kind() == SyntaxKind.Block)
                {
                    currentNL--;
                    EmbeddednessConsideredToDecrease();
                }
            }
#endregion
#region The following instructions don't increase the value by themselves
            public override void VisitElseClause(ElseClauseSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                embeddednessNode = node;
                embeddednessHasBeenIncreased = false;
                embeddednessHasBeenDecreased = false;
                base.VisitElseClause(node);
                embeddednessNode = null;
            }
            public override void VisitCaseSwitchLabel(CaseSwitchLabelSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                embeddednessNode = node;
                embeddednessHasBeenIncreased = false;
                embeddednessHasBeenDecreased = false;
                base.VisitCaseSwitchLabel(node);
                embeddednessNode = null;
            }
            public override void VisitDefaultSwitchLabel(DefaultSwitchLabelSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                embeddednessNode = node;
                embeddednessHasBeenIncreased = false;
                embeddednessHasBeenDecreased = false;
                base.VisitDefaultSwitchLabel(node);
                embeddednessNode = null;
            }
            public override void VisitCatchClause(CatchClauseSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                embeddednessNode = node;
                embeddednessHasBeenIncreased = false;
                embeddednessHasBeenDecreased = false;
                base.VisitCatchClause(node);
                embeddednessNode = null;
            }
#endregion
#region Utilties
            private void IncreaseHeight()
            {
                currentNL++;

                if (result < currentNL) result = currentNL;
            }
            private void EligibleForNLE(IfStatementSyntax node)
            {
                if (nle && node.Parent.Kind() == SyntaxKind.ElseClause)
                {
                    if ( embeddednessNode?.Kind( ) == SyntaxKind.ElseClause )
                    {
                        currentNL--;
                    }
                }
            }
            private void EmbeddednessConsideredToIncrease()
            {
                if (embeddednessHasBeenIncreased || embeddednessNode == null) return;
                switch (embeddednessNode.Kind())
                {
                    case SyntaxKind.ElseClause:
                    case SyntaxKind.CaseSwitchLabel:
                    case SyntaxKind.DefaultSwitchLabel:
                    case SyntaxKind.CatchClause:
                        IncreaseHeight();
                        embeddednessHasBeenIncreased = true;
                        break;
                }
            }
            private void EmbeddednessConsideredToDecrease()
            {
                if (embeddednessHasBeenDecreased || embeddednessNode == null) return;
                switch (embeddednessNode.Kind())
                {
                    case SyntaxKind.ElseClause:
                    case SyntaxKind.CaseSwitchLabel:
                    case SyntaxKind.DefaultSwitchLabel:
                    case SyntaxKind.CatchClause:
                        currentNL--;
                        embeddednessHasBeenDecreased = true;
                        break;
                }
            }
#endregion

        }
    }
}
