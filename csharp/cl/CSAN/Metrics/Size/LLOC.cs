using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Contexts;
using Columbus.CSAN.Extensions;
using Columbus.CSAN.Utils;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.Metrics.Size
{
    /// <summary>
    /// Method: 
    ///   LLOC metrics for a method means the number of non-empty and non-comment lines 
    ///   that belong to the method, in which the lines of anonymous and local classes of 
    ///   the given method are not calculated.
    /// Class: 
    ///   LLOC metrics for a class means the number of non-empty and non-comment lines, 
    ///   in which the non-empty and non-comment lines of the given class are calculated; 
    ///   however the anonymous and local classes that can be found and the nested classes 
    ///   in the given class are not calculated.
    /// Namespace: 
    ///   LLOC metrics for a package means the number of non-empty and non-comment lines 
    ///   that belong to the package; however the lines of the elements that can be found
    ///   in the subpackages of the package are not calculated.
    /// </summary>
    internal class LLOC
    {
        private readonly FileContext fileContext;

        public LLOC(FileContext fileContext)
        {
            this.fileContext = fileContext;
        }

        /// <summary>
        /// Node's line informations will be collected.
        /// </summary>
        /// <param name="node"></param>
        public void CollectLineInfos(SyntaxNode node)
        {
            if (node.Kind() != SyntaxKind.DelegateDeclaration && fileContext.MethodStack.Count == 0)
            {
                InsertLLOCMap(node.GetLocation());
            }

            if (node.Parent != null &&
                (node is BaseMethodDeclarationSyntax || node.Parent.Parent is BasePropertyDeclarationSyntax || node is AnonymousFunctionExpressionSyntax || node is LocalFunctionStatementSyntax))
            {
                var statementVisitor = new StatementVisitor(this);
                statementVisitor.Visit(node);
            }
            else if (node.Kind() == SyntaxKind.AnonymousObjectCreationExpression || node.Kind() == SyntaxKind.AnonymousObjectMemberDeclarator)
            {
                var anonymousVisitor = new AnonymousVisitor(this);
                anonymousVisitor.Visit(node);
            }
            else if (node.Kind() == SyntaxKind.EnumDeclaration)
            {
                var enumVisitor = new EnumVisitor(this);
                enumVisitor.Visit(node);
            }
            else if (node is TypeDeclarationSyntax)
            {
                var typeVisitor = new TypeVisitor(this);
                typeVisitor.Visit(node);
            }
            else if (node.Kind() == SyntaxKind.NamespaceDeclaration)
            {
                NamespaceDeclarationSyntax ns = node as NamespaceDeclarationSyntax;
                InsertLLOCMap(ns.OpenBraceToken.GetLocation());
            }
            else if ( node.Kind( ) == SyntaxKind.DelegateDeclaration )
            {
                var localNode = node as DelegateDeclarationSyntax;
                InsertLLOCMap(localNode.GetLocation());
                foreach (var modifier in localNode.Modifiers)
                {
                    InsertLLOCMap(modifier.GetLocation());
                }
                foreach (var attributeListSyntax in localNode.AttributeLists)
                {
                    InsertLLOCMap(attributeListSyntax.GetLocation());
                }
                foreach (var typeParameterConstraintClauseSyntax in localNode.ConstraintClauses)
                {
                    InsertLLOCMap(typeParameterConstraintClauseSyntax.GetLocation());
                }
                foreach (var parameterSyntax in localNode.ParameterList.Parameters)
                {
                    InsertLLOCMap(parameterSyntax.GetLocation());
                }
            }
        }

        /// <summary>
        /// Insert line information to the correct level
        /// </summary>
        /// <param name="location">SyntaxNode's location</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void InsertLLOCMap(Location location)
        {
            string path = fileContext.ProjectContext.SolutionContext.ProcessPath(location.SourceTree.FilePath);
            string lowerPath = path.ToLower();
            if (lowerPath.Contains(Constants.TEMP) && lowerPath.Contains(Constants.NET) && lowerPath.Contains(Constants.COMMA)) return;
            if (lowerPath.Contains(Constants.PROP) && lowerPath.Contains(Constants.ASSEMBLYINFO)) return;

            uint pathKey = fileContext.ProjectContext.SolutionContext.LimFactory.StringTable.set(path);

            uint line = (uint)location.GetMappedLineSpan().StartLinePosition.Line + 1;
            uint endLine = (uint)location.GetMappedLineSpan().EndLinePosition.Line + 1;

            if (line <= 0 || endLine <= 0) return;

            if (fileContext.MethodStack.Count > 0)
            {
                uint currentmethodId = fileContext.MethodStack.Peek().Id;
                if (!CheckAnonyumousEmbeddedness(currentmethodId))
                    AssignPathLineToNode(currentmethodId, pathKey, line, endLine);
            }

            if (fileContext.ClassStack.Count > 0)
            {
                uint currentClassId = fileContext.ClassStack.Peek().Id;
                AssignPathLineToNode(currentClassId, pathKey, line, endLine);
            }

            AssignPathLineToNode(fileContext.NamespaceStack.Peek(), pathKey, line, endLine);

            //Assign LLOC to the root node
            AssignPathLineToNode(fileContext.ProjectContext.SolutionContext.LimFactory.Root, pathKey, line, endLine);

            //Assign LLOC to the component
            AddLogicalLineOfComponent(fileContext.ProjectContext.Component.Id, pathKey, line);
            AddLogicalLineOfComponent(fileContext.ProjectContext.Component.Id, pathKey, endLine);
        }

        /// <summary>
        /// Method contains member(s)
        /// </summary>
        /// <param name="currentmethodId">LIM method node's id</param>
        /// <returns>Return true if method contains member(s)</returns>
        private bool CheckAnonyumousEmbeddedness(uint currentmethodId)
        {
            bool innerClass = false;
            if (fileContext.ClassStack.Count > 0)
            {
                uint step = fileContext.ClassStack.Peek().Id;
                while (true)
                {
                    ListIterator<Base> i = fileContext.ProjectContext.SolutionContext.ReverseEdges.constIteratorBegin(step, Types.EdgeKind.edkScope_HasMember);
                    if (i.getValue() == null) break;

                    step = i.getValue().Id;

                    if (step == currentmethodId)
                    {
                        innerClass = true;
                        break;
                    }
                }
            }
            return innerClass;
        }

        /// <summary>
        /// Aggregate LLOC to the component
        /// </summary>
        /// <param name="NodeId">LIM node id</param>
        /// <param name="pathKey">Path hash code</param>
        /// <param name="line">Start line position</param>
        private void AddLogicalLineOfComponent(uint NodeId, uint pathKey, uint line)
        {
            if (line > 0)
            {
                fileContext.ProjectContext.SolutionContext.LLOCMap.Add(NodeId, pathKey, line);
                ListIterator<Base> itBegin = fileContext.ProjectContext.SolutionContext.ReverseEdges.constIteratorBegin(NodeId, Types.EdgeKind.edkComponent_Contains);
                while (itBegin.getValue() != null)
                {
                    AddLogicalLineOfComponent(itBegin.getValue().Id, pathKey, line);
                    itBegin = itBegin.getNext();
                }
            }
        }


        /// <summary>
        /// <paramref name="pathKey"/> and <paramref name="line"/> will be assign to the <paramref name="nodeId"/>
        /// and also
        /// <paramref name="pathKey"/> and <paramref name="endLine"/> will be assign to the <paramref name="nodeId"/>
        /// </summary>
        /// <param name="nodeId">LIM node id</param>
        /// <param name="pathKey">Path hash code</param>
        /// <param name="line">Start line position</param>
        /// <param name="endLine">End line position</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void AssignPathLineToNode(uint nodeId, uint pathKey, uint line, uint endLine)
        {
            fileContext.ProjectContext.SolutionContext.LLOCMap.Add(nodeId, pathKey, line);
            fileContext.ProjectContext.SolutionContext.LLOCMap.Add(nodeId, pathKey, endLine);
        }

        #region Local utils
        private sealed class StatementVisitor : CSharpSyntaxWalker
        {
            private readonly LLOC parent;
            private SyntaxNode entryNode, embeddedNode;
            private bool _weInAnonymousMethod = false, _weComeFromMethod = false;
            private int _depthParenthesizedExpression = 0,
                        _depthSimpleLambdaExpression = 0,
                        _depthAnonymousMethodExpression = 0;

            public StatementVisitor(LLOC lloc)
            {
                parent = lloc;
            }

            public override void VisitAttributeList(AttributeListSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitAttributeList(node);
            }

            public override void VisitExpressionStatement(ExpressionStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (!node.IsParent<AnonymousObjectCreationExpressionSyntax>())
                {
                    parent.InsertLLOCMap(node.GetLocation());
                }
                base.VisitExpressionStatement(node);
            }

            public override void VisitConditionalExpression(ConditionalExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.ColonToken.GetLocation());
                parent.InsertLLOCMap(node.QuestionToken.GetLocation());
                base.VisitConditionalExpression(node);
            }

            public override void VisitLocalDeclarationStatement(LocalDeclarationStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                foreach (var variable in node.Declaration.Variables)
                {
                    parent.InsertLLOCMap(variable.GetLocation());
                }
                base.VisitLocalDeclarationStatement(node);
            }

            public override void VisitQueryExpression(QueryExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.FromClause.GetLocation());
                parent.InsertLLOCMap(node.Body.GetLocation());
                base.VisitQueryExpression(node);
            }

            public override void VisitDoStatement(DoStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.WhileKeyword.GetLocation());
                parent.InsertLLOCMap(node.OpenParenToken.GetLocation());
                parent.InsertLLOCMap(node.CloseParenToken.GetLocation());
                base.VisitDoStatement(node);
            }

            public override void VisitObjectCreationExpression(ObjectCreationExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectCreationExpressionSyntax>()) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitObjectCreationExpression(node);
            }

            public override void VisitInitializerExpression(InitializerExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectCreationExpressionSyntax>()) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitInitializerExpression(node);
            }

            public override void VisitIdentifierName(IdentifierNameSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectCreationExpressionSyntax>()) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitIdentifierName(node);
            }

            public override void VisitBreakStatement(BreakStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitBreakStatement(node);
            }

            public override void VisitThrowStatement(ThrowStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitThrowStatement(node);
            }

            public override void VisitUsingStatement(UsingStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitUsingStatement(node);
            }

            public override void VisitYieldStatement(YieldStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitYieldStatement(node);
            }

            public override void VisitEmptyStatement(EmptyStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (!node.IsParent<AnonymousObjectCreationExpressionSyntax>())
                    parent.InsertLLOCMap(node.GetLocation());
                base.VisitEmptyStatement(node);
            }

            public override void VisitWhileStatement(WhileStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.OpenParenToken.GetLocation());
                parent.InsertLLOCMap(node.CloseParenToken.GetLocation());
                base.VisitWhileStatement(node);
            }

            public override void VisitUnsafeStatement(UnsafeStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitUnsafeStatement(node);
            }

            public override void VisitCheckedExpression(CheckedExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitCheckedExpression(node);
            }

            public override void VisitLockStatement(LockStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitLockStatement(node);
            }

            public override void VisitFixedStatement(FixedStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitFixedStatement(node);
            }

            public override void VisitForEachStatement(ForEachStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.InKeyword.GetLocation());
                base.VisitForEachStatement(node);
            }

            public override void VisitForStatement(ForStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                if (node.Declaration != null)
                {
                    foreach (var variable in node.Declaration.Variables)
                    {
                        parent.InsertLLOCMap(variable.GetLocation());
                    }
                }
                parent.InsertLLOCMap(node.FirstSemicolonToken.GetLocation());
                if (node.Condition != null)
                    parent.InsertLLOCMap(node.Condition.GetLocation());
                parent.InsertLLOCMap(node.SecondSemicolonToken.GetLocation());
                foreach (var incrementor in node.Incrementors)
                {
                    parent.InsertLLOCMap(incrementor.GetLocation());
                }
                base.VisitForStatement(node);
            }

            public override void VisitBlock(BlockSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.OpenBraceToken.GetLocation());
                parent.InsertLLOCMap(node.CloseBraceToken.GetLocation());
                base.VisitBlock(node);
            }

            public override void VisitGotoStatement(GotoStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitGotoStatement(node);
            }

            public override void VisitLabeledStatement(LabeledStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.ColonToken.GetLocation());
                base.VisitLabeledStatement(node);
            }

            public override void VisitLiteralExpression(LiteralExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectMemberDeclaratorSyntax>()) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitLiteralExpression(node);
            }

            public override void VisitSwitchStatement(SwitchStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.OpenBraceToken.GetLocation());
                parent.InsertLLOCMap(node.CloseBraceToken.GetLocation());
                base.VisitSwitchStatement(node);
            }

            public override void VisitSwitchSection(SwitchSectionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                foreach (var statement in node.Statements)
                {
                    parent.InsertLLOCMap(statement.GetLocation());
                }
                foreach (var label in node.Labels)
                {
                    parent.InsertLLOCMap(label.GetLocation());
                }
                base.VisitSwitchSection(node);
            }

            public override void VisitTryStatement(TryStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                foreach (var catchClause in node.Catches)
                {
                    parent.InsertLLOCMap(catchClause.GetLocation());
                    if (catchClause.Declaration != null)
                    {
                        parent.InsertLLOCMap(catchClause.Declaration.OpenParenToken.GetLocation());
                        parent.InsertLLOCMap(catchClause.Declaration.CloseParenToken.GetLocation());
                    }
                }
                if (node.Finally != null)
                    parent.InsertLLOCMap(node.Finally.GetLocation());
                base.VisitTryStatement(node);
            }

            public override void VisitReturnStatement(ReturnStatementSyntax node)
            {
                if (node.IsContains<AnonymousObjectCreationExpressionSyntax>()) return;
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitReturnStatement(node);
            }

            public override void VisitIfStatement(IfStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                parent.InsertLLOCMap(node.GetLocation());
                if (node.Else != null)
                {
                    parent.InsertLLOCMap(node.Else.GetLocation());
                }
                parent.InsertLLOCMap(node.OpenParenToken.GetLocation());
                parent.InsertLLOCMap(node.CloseParenToken.GetLocation());
                base.VisitIfStatement(node);
            }

            public override void VisitAccessorDeclaration(AccessorDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;

                parent.InsertLLOCMap(node.GetLocation());
                foreach (var modifier in node.Modifiers)
                {
                    parent.InsertLLOCMap(modifier.GetLocation());
                }
                _weComeFromMethod = true;
                base.VisitAccessorDeclaration(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            private void CalculateMethodLines(BaseMethodDeclarationSyntax node)
            {
                foreach (var modifier in node.Modifiers)
                {
                    parent.InsertLLOCMap(modifier.GetLocation());
                }
                parent.InsertLLOCMap(node.ParameterList.OpenParenToken.GetLocation());
                foreach (var parameter in node.ParameterList.Parameters)
                {
                    parent.InsertLLOCMap(parameter.GetLocation());
                }
                parent.InsertLLOCMap(node.ParameterList.CloseParenToken.GetLocation());
                if (node.Body != null)
                {
                    parent.InsertLLOCMap(node.Body.OpenBraceToken.GetLocation());
                    parent.InsertLLOCMap(node.Body.CloseBraceToken.GetLocation());
                }
            }

            public override void VisitMethodDeclaration(MethodDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;
                foreach (var constraintClause in node.ConstraintClauses)
                {
                    parent.InsertLLOCMap(constraintClause.WhereKeyword.GetLocation());
                    parent.InsertLLOCMap(constraintClause.ColonToken.GetLocation());
                    foreach (var constraint in constraintClause.Constraints)
                    {
                        parent.InsertLLOCMap(constraint.GetLocation());
                    }
                    parent.InsertLLOCMap(constraintClause.GetLocation());
                }
                CalculateMethodLines(node);
                _weComeFromMethod = true;
                base.VisitMethodDeclaration(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            public override void VisitLocalFunctionStatement(LocalFunctionStatementSyntax node)
            {
                if (entryNode == null)
                    entryNode = node;
                foreach (var constraintClause in node.ConstraintClauses)
                {
                    parent.InsertLLOCMap(constraintClause.WhereKeyword.GetLocation());
                    parent.InsertLLOCMap(constraintClause.ColonToken.GetLocation());
                    foreach (var constraint in constraintClause.Constraints)
                        parent.InsertLLOCMap(constraint.GetLocation());
                    parent.InsertLLOCMap(constraintClause.GetLocation());
                }

                foreach (var modifier in node.Modifiers)
                    parent.InsertLLOCMap(modifier.GetLocation());

                parent.InsertLLOCMap(node.ParameterList.OpenParenToken.GetLocation());

                foreach (var parameter in node.ParameterList.Parameters)
                    parent.InsertLLOCMap(parameter.GetLocation());

                parent.InsertLLOCMap(node.ParameterList.CloseParenToken.GetLocation());

                if (node.Body != null)
                {
                    parent.InsertLLOCMap(node.Body.OpenBraceToken.GetLocation());
                    parent.InsertLLOCMap(node.Body.CloseBraceToken.GetLocation());
                }

                _weComeFromMethod = true;
                base.VisitLocalFunctionStatement(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            public override void VisitConstructorDeclaration(ConstructorDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;
                if (node.Initializer != null)
                {
                    parent.InsertLLOCMap(node.Initializer.ColonToken.GetLocation());
                    parent.InsertLLOCMap(node.Initializer.ThisOrBaseKeyword.GetLocation());
                    if (node.Initializer.ArgumentList != null)
                    {
                        foreach (var argument in node.Initializer.ArgumentList.Arguments)
                        {
                            parent.InsertLLOCMap(argument.GetLocation());
                        }
                    }
                }
                CalculateMethodLines(node);
                base.VisitConstructorDeclaration(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            public override void VisitDestructorDeclaration(DestructorDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;
                _weComeFromMethod = true;
                CalculateMethodLines(node);
                base.VisitDestructorDeclaration(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            public override void VisitConversionOperatorDeclaration(ConversionOperatorDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;
                _weComeFromMethod = true;
                CalculateMethodLines(node);
                base.VisitConversionOperatorDeclaration(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            public override void VisitOperatorDeclaration(OperatorDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;
                _weComeFromMethod = true;
                base.VisitOperatorDeclaration(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            #region VisitAnonymousFunction
            public override void VisitAnonymousMethodExpression(AnonymousMethodExpressionSyntax node)
            {
                var lastEmbeddedNode = embeddedNode;
                if (entryNode == null) entryNode = node;
                else embeddedNode = node;
                _depthAnonymousMethodExpression++;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.Block.GetLocation());
                if (node.ParameterList != null)
                {
                    foreach (var paramter in node.ParameterList.Parameters)
                    {
                        parent.InsertLLOCMap(paramter.GetLocation());
                    }
                }
                parent.InsertLLOCMap(node.DelegateKeyword.GetLocation());
                _weInAnonymousMethod = true;
                base.VisitAnonymousMethodExpression(node);
                _weInAnonymousMethod = false;
                _depthAnonymousMethodExpression--;
                embeddedNode = lastEmbeddedNode;
                if (_depthSimpleLambdaExpression == 0 && _depthParenthesizedExpression == 0 && _depthAnonymousMethodExpression == 0)
                {
                    entryNode = null;
                }
            }

            public override void VisitSimpleLambdaExpression(SimpleLambdaExpressionSyntax node)
            {
                var lastEmbeddedNode = embeddedNode;
                if (entryNode == null) entryNode = node;
                else embeddedNode = node;
                _depthSimpleLambdaExpression++;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.Body.GetLocation());
                if (node.AsyncKeyword.Text != "")
                    parent.InsertLLOCMap(node.AsyncKeyword.GetLocation());
                parent.InsertLLOCMap(node.Parameter.GetLocation());
                parent.InsertLLOCMap(node.ArrowToken.GetLocation());
                _weInAnonymousMethod = true;
                base.VisitSimpleLambdaExpression(node);
                _weInAnonymousMethod = false;
                _depthSimpleLambdaExpression--;
                embeddedNode = lastEmbeddedNode;
                if (_depthSimpleLambdaExpression == 0 && _depthParenthesizedExpression == 0 && _depthAnonymousMethodExpression == 0)
                {
                    entryNode = null;
                }
            }

            public override void VisitParenthesizedExpression(ParenthesizedExpressionSyntax node)
            {
                var lastEmbeddedNode = embeddedNode;
                if (entryNode == null) entryNode = node;
                else embeddedNode = node;
                _depthParenthesizedExpression++;
                parent.InsertLLOCMap(node.GetLocation());
                parent.InsertLLOCMap(node.OpenParenToken.GetLocation());
                parent.InsertLLOCMap(node.CloseParenToken.GetLocation());
                _weInAnonymousMethod = true;
                base.VisitParenthesizedExpression(node);
                _weInAnonymousMethod = false;
                _depthParenthesizedExpression--;
                embeddedNode = lastEmbeddedNode;
                if (_depthSimpleLambdaExpression == 0 && _depthParenthesizedExpression == 0 && _depthAnonymousMethodExpression == 0)
                {
                    entryNode = null;
                }
            }
            #endregion

            public override void VisitAnonymousObjectCreationExpression(AnonymousObjectCreationExpressionSyntax node)
            {
                parent.InsertLLOCMap(node.OpenBraceToken.GetLocation());
            }
        }

        private sealed class AnonymousVisitor : CSharpSyntaxWalker
        {
            private readonly LLOC parent;

            public AnonymousVisitor(LLOC parent)
            {
                this.parent = parent;
            }

            public override void VisitAnonymousObjectMemberDeclarator(AnonymousObjectMemberDeclaratorSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitAnonymousObjectMemberDeclarator(node);
            }

            public override void VisitAnonymousObjectCreationExpression(AnonymousObjectCreationExpressionSyntax node)
            {
                parent.InsertLLOCMap(node.OpenBraceToken.GetLocation());
                parent.InsertLLOCMap(node.GetLocation());
            }
        }

        private sealed class EnumVisitor : CSharpSyntaxWalker
        {
            private readonly LLOC parent;

            public EnumVisitor(LLOC parent)
            {
                this.parent = parent;
            }

            public override void VisitEnumMemberDeclaration(EnumMemberDeclarationSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitEnumMemberDeclaration(node);
            }
        }

        private sealed class TypeVisitor : CSharpSyntaxWalker
        {
            private bool _weAreInClassNode;
            private readonly LLOC parent;

            public TypeVisitor(LLOC parent)
            {
                this.parent = parent;
            }

            public override void VisitDelegateDeclaration( DelegateDeclarationSyntax node )
            {
                parent.InsertLLOCMap(node.GetLocation());
                foreach ( var modifier in node.Modifiers )
                {
                    parent.InsertLLOCMap(modifier.GetLocation());
                }
                foreach ( var attributeListSyntax in node.AttributeLists )
                {
                    parent.InsertLLOCMap(attributeListSyntax.GetLocation());
                }
                foreach ( var typeParameterConstraintClauseSyntax in node.ConstraintClauses )
                {
                    parent.InsertLLOCMap(typeParameterConstraintClauseSyntax.GetLocation());
                }
                foreach ( var parameterSyntax in node.ParameterList.Parameters )
                {
                    parent.InsertLLOCMap(parameterSyntax.GetLocation());
                }
            }

            public override void VisitFieldDeclaration(FieldDeclarationSyntax node)
            {
                foreach (var modifier in node.Modifiers)
                {
                    parent.InsertLLOCMap(modifier.GetLocation());
                }
                parent.InsertLLOCMap(node.GetLocation());
                foreach (var variable in node.Declaration.Variables)
                {
                    parent.InsertLLOCMap(variable.GetLocation());
                }
                base.VisitFieldDeclaration(node);
            }

            public override void VisitDefineDirectiveTrivia(DefineDirectiveTriviaSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitDefineDirectiveTrivia(node);
            }

            public override void VisitElifDirectiveTrivia(ElifDirectiveTriviaSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitElifDirectiveTrivia(node);
            }

            public override void VisitElseDirectiveTrivia(ElseDirectiveTriviaSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitElseDirectiveTrivia(node);
            }

            public override void VisitEndIfDirectiveTrivia(EndIfDirectiveTriviaSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitEndIfDirectiveTrivia(node);
            }

            public override void VisitEndRegionDirectiveTrivia(EndRegionDirectiveTriviaSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitEndRegionDirectiveTrivia(node);
            }

            public override void VisitIfDirectiveTrivia(IfDirectiveTriviaSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitIfDirectiveTrivia(node);
            }

            public override void VisitExternAliasDirective(ExternAliasDirectiveSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitExternAliasDirective(node);
            }

            public override void VisitArgument(ArgumentSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitArgument(node);
            }

            public override void VisitIdentifierName(IdentifierNameSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitIdentifierName(node);
            }

            public override void VisitLiteralExpression(LiteralExpressionSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitLiteralExpression(node);
            }

            public override void VisitInitializerExpression(InitializerExpressionSyntax node)
            {
                parent.InsertLLOCMap(node.GetLocation());
                base.VisitInitializerExpression(node);
            }


            private void calculateTypeLines(TypeDeclarationSyntax node)
            {
                foreach (var modifier in node.Modifiers)
                {
                    parent.InsertLLOCMap(modifier.GetLocation());
                }
                foreach (var constraintClause in node.ConstraintClauses)
                {
                    parent.InsertLLOCMap(constraintClause.WhereKeyword.GetLocation());
                    parent.InsertLLOCMap(constraintClause.ColonToken.GetLocation());
                    foreach (var constraint in constraintClause.Constraints)
                    {
                        parent.InsertLLOCMap(constraint.GetLocation());
                    }
                    parent.InsertLLOCMap(constraintClause.GetLocation());
                }
                parent.InsertLLOCMap(node.OpenBraceToken.GetLocation());
            }

            public override void VisitClassDeclaration(ClassDeclarationSyntax node)
            {
                if (_weAreInClassNode) return;
                _weAreInClassNode = true;
                calculateTypeLines(node);
                base.VisitClassDeclaration(node);
                _weAreInClassNode = false;
            }

            public override void VisitStructDeclaration(StructDeclarationSyntax node)
            {
                if (_weAreInClassNode) return;
                _weAreInClassNode = true;
                calculateTypeLines(node);
                base.VisitStructDeclaration(node);
                _weAreInClassNode = false;
            }

            public override void VisitInterfaceDeclaration(InterfaceDeclarationSyntax node)
            {
                if (_weAreInClassNode) return;
                _weAreInClassNode = true;
                calculateTypeLines(node);
                base.VisitInterfaceDeclaration(node);
                _weAreInClassNode = false;
            }
        }
        #endregion
    }
}
