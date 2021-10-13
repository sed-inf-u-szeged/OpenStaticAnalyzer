using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis;

namespace Columbus.CSAN.Metrics.Size
{
    using Extensions;

    /// <summary>
    /// The number of statements to be found in the method, in which the 
    /// instructions of anonymous or local classes to be found in the 
    /// method are not calculated.
    /// </summary>
    static class NOS
    {
        public static int methodcnt = 1;
        private static SyntaxNode entryPoint;

        public static int Calculate(SyntaxNode node)
        {
            entryPoint = node;
            StatementVisitor mv = new StatementVisitor();
            mv.Visit(node);

            return mv.noscounter;
        }

        private class StatementVisitor : CSharpSyntaxWalker
        {
            public int noscounter = 0;

            public override void VisitLocalDeclarationStatement(LocalDeclarationStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitLocalDeclarationStatement(node);
            }

            public override void VisitExpressionStatement(ExpressionStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitExpressionStatement(node);
            }

            public override void VisitEmptyStatement(EmptyStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitEmptyStatement(node);
            }
             public override void VisitQueryExpression(QueryExpressionSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitQueryExpression(node);
            }

            public override void VisitLabeledStatement(LabeledStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitLabeledStatement(node);
            }

            public override void VisitGotoStatement(GotoStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitGotoStatement(node);
            }

            public override void VisitBreakStatement(BreakStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitBreakStatement(node);
            }

            public override void VisitContinueStatement(ContinueStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitContinueStatement(node);
            }

            public override void VisitReturnStatement(ReturnStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitReturnStatement(node);
            }

            public override void VisitThrowStatement(ThrowStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitThrowStatement(node);
            }

            public override void VisitYieldStatement(YieldStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitYieldStatement(node);
            }

            public override void VisitWhileStatement(WhileStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitWhileStatement(node);
            }

            public override void VisitDoStatement(DoStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitDoStatement(node);
            }

            public override void VisitForStatement(ForStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitForStatement(node);
            }

            public override void VisitForEachStatement(ForEachStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitForEachStatement(node);
            }

            public override void VisitUsingStatement(UsingStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitUsingStatement(node);
            }

            public override void VisitFixedStatement(FixedStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitFixedStatement(node);
            }

            public override void VisitCheckedStatement(CheckedStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitCheckedStatement(node);
            }

            public override void VisitUnsafeStatement(UnsafeStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitUnsafeStatement(node);
            }

            public override void VisitLockStatement(LockStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitLockStatement(node);
            }

            public override void VisitIfStatement(IfStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitIfStatement(node);
            }

            public override void VisitSwitchStatement(SwitchStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitSwitchStatement(node);
            }

            public override void VisitTryStatement(TryStatementSyntax node)
            {
                if (entryPoint.IsMethodLevel() && node.IsParent<AnonymousFunctionExpressionSyntax>()) return;
                noscounter++;
                base.VisitTryStatement(node);
            }

        }

    }
}

