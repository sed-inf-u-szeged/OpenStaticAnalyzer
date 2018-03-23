/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
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
    internal sealed class LLOC
    {
        /// <summary>
        /// Node's line informations will be collected.
        /// </summary>
        /// <param name="node"></param>
        public static void CollectLineInfos(SyntaxNode node)
        {
            if (node.Kind() != SyntaxKind.DelegateDeclaration && MainDeclaration.Instance.MethodStack.Count == 0)
            {
                InsertLLOCMap(node.GetLocation());
            }

            if (node.Parent != null && (node is BaseMethodDeclarationSyntax || node.Parent.Parent is BasePropertyDeclarationSyntax || node is AnonymousFunctionExpressionSyntax))
            {
                StatementVisitor.VisitStatement(node);
            }
            else if (node.Kind() == SyntaxKind.AnonymousObjectCreationExpression || node.Kind() == SyntaxKind.AnonymousObjectMemberDeclarator)
            {
                AnonymousVisitor.VisitAnonimClass(node);
            }
            else if (node.Kind() == SyntaxKind.EnumDeclaration)
            {
                EnumVisitor.VisitEnum(node);
            }
            else if (node is TypeDeclarationSyntax)
            {
                TypeVisitor.VisitType(node);
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
        private static void InsertLLOCMap(Location location)
        {
            string path = Commons.Common.ProcessPath(location.SourceTree.FilePath);
            if (path.Contains(Constants.TEMP) && path.Contains(Constants.NET) && path.Contains(Constants.COMMA)) return;
            if (path.Contains(Constants.PROP) && path.Contains(Constants.ASSEMBLYINFO)) return;

            uint pathKey = MainDeclaration.Instance.LimFactory.StringTable.set(path);

            uint line = (uint)location.GetMappedLineSpan().StartLinePosition.Line + 1;
            uint endLine = (uint)location.GetMappedLineSpan().EndLinePosition.Line + 1;

            if (line <= 0 || endLine <= 0) return;

            if (MainDeclaration.Instance.MethodStack.Count > 0)
            {
                uint currentmethodId = MainDeclaration.Instance.MethodStack.Peek().Id;
                if (!CheckAnonyumousEmbeddedness(currentmethodId))
                    AssignPathLineToNode(currentmethodId, pathKey, line, endLine);
            }

            if (MainDeclaration.Instance.ClassStack.Count > 0)
            {
                uint currentClassId = MainDeclaration.Instance.ClassStack.Peek().Id;
                AssignPathLineToNode(currentClassId, pathKey, line, endLine);
            }

            if (MainDeclaration.Instance.NamespaceStack.Peek() > 0)
                AssignPathLineToNode(MainDeclaration.Instance.NamespaceStack.Peek(), pathKey, line, endLine);

            //Assign LLOC to the root node
            AssignPathLineToNode(MainDeclaration.Instance.LimFactory.Root, pathKey, line, endLine);

            //Assign LLOC to the component
            AddLogicalLineOfComponent(MainDeclaration.Instance.Component.Id, pathKey, line);
            AddLogicalLineOfComponent(MainDeclaration.Instance.Component.Id, pathKey, endLine);
        }

        /// <summary>
        /// Method contains member(s)
        /// </summary>
        /// <param name="currentmethodId">LIM method node's id</param>
        /// <returns>Return true if method contains member(s)</returns>
        private static bool CheckAnonyumousEmbeddedness(uint currentmethodId)
        {
            bool innerClass = false;
            if (MainDeclaration.Instance.ClassStack.Count > 0)
            {
                uint step = MainDeclaration.Instance.ClassStack.Peek().Id;
                while (true)
                {
                    ListIterator<Base> i = MainDeclaration.Instance.RevEdges.constIteratorBegin(step, Types.EdgeKind.edkScope_HasMember);
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
        private static void AddLogicalLineOfComponent(uint NodeId, uint pathKey, uint line)
        {
            if (line > 0)
            {
                MainDeclaration.Instance.LLOCMap.Add(NodeId, pathKey, line);
                ListIterator<Base> itBegin = MainDeclaration.Instance.RevEdges.constIteratorBegin(NodeId, Types.EdgeKind.edkComponent_Contains);
                while (itBegin.getValue() != null)
                {
                    AddLogicalLineOfComponent(itBegin.getValue().Id, pathKey, line);
                    itBegin = itBegin.getNext();
                }
            }
        }


        /// <summary>
        /// <paramref name="pathKey"/> and <paramref name="line"/> will be assign to the <paramref name="NodeId"/>
        /// and also
        /// <paramref name="pathKey"/> and <paramref name="endLine"/> will be assign to the <paramref name="NodeId"/>
        /// </summary>
        /// <param name="NodeId">LIM node id</param>
        /// <param name="pathKey">Path hash code</param>
        /// <param name="line">Start line position</param>
        /// <param name="endLine">End line position</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static void AssignPathLineToNode(uint NodeId, uint pathKey, uint line, uint endLine)
        {
            MainDeclaration.Instance.LLOCMap.Add(NodeId, pathKey, line);
            MainDeclaration.Instance.LLOCMap.Add(NodeId, pathKey, endLine);
        }

        #region Local utils
        private sealed class StatementVisitor : CSharpSyntaxWalker
        {

            private static StatementVisitor instance;
            private SyntaxNode entryNode, embeddedNode;
            private bool _weInAnonymousMethod = false, _weComeFromMethod = false;
            private int _depthParenthesizedExpression = 0,
                        _depthSimpleLambdaExpression = 0,
                        _depthAnonymousMethodExpression = 0;

            private StatementVisitor() { }

            public static void VisitStatement(SyntaxNode node)
            {
                if (instance == null)
                    instance = new StatementVisitor();

                instance.Visit(node);
            }

            public override void VisitAttributeList(AttributeListSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitAttributeList(node);
            }

            public override void VisitExpressionStatement(ExpressionStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (!node.IsParent<AnonymousObjectCreationExpressionSyntax>())
                {
                    InsertLLOCMap(node.GetLocation());
                }
                base.VisitExpressionStatement(node);
            }

            public override void VisitConditionalExpression(ConditionalExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.ColonToken.GetLocation());
                InsertLLOCMap(node.QuestionToken.GetLocation());
                base.VisitConditionalExpression(node);
            }

            public override void VisitLocalDeclarationStatement(LocalDeclarationStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                foreach (var variable in node.Declaration.Variables)
                {
                    InsertLLOCMap(variable.GetLocation());
                }
                base.VisitLocalDeclarationStatement(node);
            }

            public override void VisitQueryExpression(QueryExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.FromClause.GetLocation());
                InsertLLOCMap(node.Body.GetLocation());
                base.VisitQueryExpression(node);
            }

            public override void VisitDoStatement(DoStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.WhileKeyword.GetLocation());
                InsertLLOCMap(node.OpenParenToken.GetLocation());
                InsertLLOCMap(node.CloseParenToken.GetLocation());
                base.VisitDoStatement(node);
            }

            public override void VisitObjectCreationExpression(ObjectCreationExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectCreationExpressionSyntax>()) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitObjectCreationExpression(node);
            }

            public override void VisitInitializerExpression(InitializerExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectCreationExpressionSyntax>()) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitInitializerExpression(node);
            }

            public override void VisitIdentifierName(IdentifierNameSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectCreationExpressionSyntax>()) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitIdentifierName(node);
            }

            public override void VisitBreakStatement(BreakStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitBreakStatement(node);
            }

            public override void VisitThrowStatement(ThrowStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitThrowStatement(node);
            }

            public override void VisitUsingStatement(UsingStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitUsingStatement(node);
            }

            public override void VisitYieldStatement(YieldStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitYieldStatement(node);
            }

            public override void VisitEmptyStatement(EmptyStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (!node.IsParent<AnonymousObjectCreationExpressionSyntax>())
                    InsertLLOCMap(node.GetLocation());
                base.VisitEmptyStatement(node);
            }

            public override void VisitWhileStatement(WhileStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.OpenParenToken.GetLocation());
                InsertLLOCMap(node.CloseParenToken.GetLocation());
                base.VisitWhileStatement(node);
            }

            public override void VisitUnsafeStatement(UnsafeStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitUnsafeStatement(node);
            }

            public override void VisitCheckedExpression(CheckedExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitCheckedExpression(node);
            }

            public override void VisitLockStatement(LockStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitLockStatement(node);
            }

            public override void VisitFixedStatement(FixedStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitFixedStatement(node);
            }

            public override void VisitForEachStatement(ForEachStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.InKeyword.GetLocation());
                base.VisitForEachStatement(node);
            }

            public override void VisitForStatement(ForStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                if (node.Declaration != null)
                {
                    foreach (var variable in node.Declaration.Variables)
                    {
                        InsertLLOCMap(variable.GetLocation());
                    }
                }
                InsertLLOCMap(node.FirstSemicolonToken.GetLocation());
                if (node.Condition != null)
                    InsertLLOCMap(node.Condition.GetLocation());
                InsertLLOCMap(node.SecondSemicolonToken.GetLocation());
                foreach (var incrementor in node.Incrementors)
                {
                    InsertLLOCMap(incrementor.GetLocation());
                }
                base.VisitForStatement(node);
            }

            public override void VisitBlock(BlockSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.OpenBraceToken.GetLocation());
                InsertLLOCMap(node.CloseBraceToken.GetLocation());
                base.VisitBlock(node);
            }

            public override void VisitGotoStatement(GotoStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitGotoStatement(node);
            }

            public override void VisitLabeledStatement(LabeledStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.ColonToken.GetLocation());
                base.VisitLabeledStatement(node);
            }

            public override void VisitLiteralExpression(LiteralExpressionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                if (node.IsParent<AnonymousObjectMemberDeclaratorSyntax>()) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitLiteralExpression(node);
            }

            public override void VisitSwitchStatement(SwitchStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.OpenBraceToken.GetLocation());
                InsertLLOCMap(node.CloseBraceToken.GetLocation());
                base.VisitSwitchStatement(node);
            }

            public override void VisitSwitchSection(SwitchSectionSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                foreach (var statement in node.Statements)
                {
                    InsertLLOCMap(statement.GetLocation());
                }
                foreach (var label in node.Labels)
                {
                    InsertLLOCMap(label.GetLocation());
                }
                base.VisitSwitchSection(node);
            }

            public override void VisitTryStatement(TryStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                foreach (var catchClause in node.Catches)
                {
                    InsertLLOCMap(catchClause.GetLocation());
                    if (catchClause.Declaration != null)
                    {
                        InsertLLOCMap(catchClause.Declaration.OpenParenToken.GetLocation());
                        InsertLLOCMap(catchClause.Declaration.CloseParenToken.GetLocation());
                    }
                }
                if (node.Finally != null)
                    InsertLLOCMap(node.Finally.GetLocation());
                base.VisitTryStatement(node);
            }

            public override void VisitReturnStatement(ReturnStatementSyntax node)
            {
                if (node.IsContains<AnonymousObjectCreationExpressionSyntax>()) return;
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                base.VisitReturnStatement(node);
            }

            public override void VisitIfStatement(IfStatementSyntax node)
            {
                if (entryNode is AnonymousFunctionExpressionSyntax && embeddedNode is AnonymousFunctionExpressionSyntax) return;
                if (_weComeFromMethod && _weInAnonymousMethod) return;
                InsertLLOCMap(node.GetLocation());
                if (node.Else != null)
                {
                    InsertLLOCMap(node.Else.GetLocation());
                }
                InsertLLOCMap(node.OpenParenToken.GetLocation());
                InsertLLOCMap(node.CloseParenToken.GetLocation());
                base.VisitIfStatement(node);
            }

            public override void VisitAccessorDeclaration(AccessorDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;

                InsertLLOCMap(node.GetLocation());
                foreach (var modifier in node.Modifiers)
                {
                    InsertLLOCMap(modifier.GetLocation());
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
                    InsertLLOCMap(modifier.GetLocation());
                }
                InsertLLOCMap(node.ParameterList.OpenParenToken.GetLocation());
                foreach (var parameter in node.ParameterList.Parameters)
                {
                    InsertLLOCMap(parameter.GetLocation());
                }
                InsertLLOCMap(node.ParameterList.CloseParenToken.GetLocation());
                if (node.Body != null)
                {
                    InsertLLOCMap(node.Body.OpenBraceToken.GetLocation());
                    InsertLLOCMap(node.Body.CloseBraceToken.GetLocation());
                }
            }

            public override void VisitMethodDeclaration(MethodDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;
                foreach (var constraintClause in node.ConstraintClauses)
                {
                    InsertLLOCMap(constraintClause.WhereKeyword.GetLocation());
                    InsertLLOCMap(constraintClause.ColonToken.GetLocation());
                    foreach (var constraint in constraintClause.Constraints)
                    {
                        InsertLLOCMap(constraint.GetLocation());
                    }
                    InsertLLOCMap(constraintClause.GetLocation());
                }
                CalculateMethodLines(node);
                _weComeFromMethod = true;
                base.VisitMethodDeclaration(node);
                _weComeFromMethod = false;
                entryNode = null;
            }

            public override void VisitConstructorDeclaration(ConstructorDeclarationSyntax node)
            {
                if (entryNode == null) entryNode = node;
                if (node.Initializer != null)
                {
                    InsertLLOCMap(node.Initializer.ColonToken.GetLocation());
                    InsertLLOCMap(node.Initializer.ThisOrBaseKeyword.GetLocation());
                    if (node.Initializer.ArgumentList != null)
                    {
                        foreach (var argument in node.Initializer.ArgumentList.Arguments)
                        {
                            InsertLLOCMap(argument.GetLocation());
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
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.Block.GetLocation());
                if (node.ParameterList != null)
                {
                    foreach (var paramter in node.ParameterList.Parameters)
                    {
                        InsertLLOCMap(paramter.GetLocation());
                    }
                }
                InsertLLOCMap(node.DelegateKeyword.GetLocation());
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
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.Body.GetLocation());
                if (node.AsyncKeyword.Text != "")
                    InsertLLOCMap(node.AsyncKeyword.GetLocation());
                InsertLLOCMap(node.Parameter.GetLocation());
                InsertLLOCMap(node.ArrowToken.GetLocation());
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
                InsertLLOCMap(node.GetLocation());
                InsertLLOCMap(node.OpenParenToken.GetLocation());
                InsertLLOCMap(node.CloseParenToken.GetLocation());
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
                InsertLLOCMap(node.OpenBraceToken.GetLocation());
            }
        }

        private sealed class AnonymousVisitor : CSharpSyntaxWalker
        {
            private static AnonymousVisitor instance;

            private AnonymousVisitor() { }

            public static void VisitAnonimClass(SyntaxNode node)
            {
                if (instance == null)
                    instance = new AnonymousVisitor();

                instance.Visit(node);
            }

            public override void VisitAnonymousObjectMemberDeclarator(AnonymousObjectMemberDeclaratorSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitAnonymousObjectMemberDeclarator(node);
            }

            public override void VisitAnonymousObjectCreationExpression(AnonymousObjectCreationExpressionSyntax node)
            {
                InsertLLOCMap(node.OpenBraceToken.GetLocation());
                InsertLLOCMap(node.GetLocation());
            }
        }

        private sealed class EnumVisitor : CSharpSyntaxWalker
        {
            private static EnumVisitor instance;
            public static void VisitEnum(SyntaxNode node)
            {
                if (instance == null) instance = new EnumVisitor();
                instance.Visit(node);
            }

            public override void VisitEnumMemberDeclaration(EnumMemberDeclarationSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitEnumMemberDeclaration(node);
            }
        }

        private sealed class TypeVisitor : CSharpSyntaxWalker
        {
            private static TypeVisitor _instance;
            private bool _weAreInClassNode;

            public static void VisitType(SyntaxNode node)
            {
                if (_instance == null) _instance = new TypeVisitor();
                _instance.Visit(node);
            }

            public override void VisitDelegateDeclaration( DelegateDeclarationSyntax node )
            {
                InsertLLOCMap(node.GetLocation());
                foreach ( var modifier in node.Modifiers )
                {
                    InsertLLOCMap(modifier.GetLocation());
                }
                foreach ( var attributeListSyntax in node.AttributeLists )
                {
                    InsertLLOCMap(attributeListSyntax.GetLocation());
                }
                foreach ( var typeParameterConstraintClauseSyntax in node.ConstraintClauses )
                {
                    InsertLLOCMap(typeParameterConstraintClauseSyntax.GetLocation());
                }
                foreach ( var parameterSyntax in node.ParameterList.Parameters )
                {
                    InsertLLOCMap(parameterSyntax.GetLocation());
                }
            }

            public override void VisitFieldDeclaration(FieldDeclarationSyntax node)
            {
                foreach (var modifier in node.Modifiers)
                {
                    InsertLLOCMap(modifier.GetLocation());
                }
                InsertLLOCMap(node.GetLocation());
                foreach (var variable in node.Declaration.Variables)
                {
                    InsertLLOCMap(variable.GetLocation());
                }
                base.VisitFieldDeclaration(node);
            }

            public override void VisitDefineDirectiveTrivia(DefineDirectiveTriviaSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitDefineDirectiveTrivia(node);
            }

            public override void VisitElifDirectiveTrivia(ElifDirectiveTriviaSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitElifDirectiveTrivia(node);
            }

            public override void VisitElseDirectiveTrivia(ElseDirectiveTriviaSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitElseDirectiveTrivia(node);
            }

            public override void VisitEndIfDirectiveTrivia(EndIfDirectiveTriviaSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitEndIfDirectiveTrivia(node);
            }

            public override void VisitEndRegionDirectiveTrivia(EndRegionDirectiveTriviaSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitEndRegionDirectiveTrivia(node);
            }

            public override void VisitIfDirectiveTrivia(IfDirectiveTriviaSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitIfDirectiveTrivia(node);
            }

            public override void VisitExternAliasDirective(ExternAliasDirectiveSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitExternAliasDirective(node);
            }

            public override void VisitArgument(ArgumentSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitArgument(node);
            }

            public override void VisitIdentifierName(IdentifierNameSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitIdentifierName(node);
            }

            public override void VisitLiteralExpression(LiteralExpressionSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitLiteralExpression(node);
            }

            public override void VisitInitializerExpression(InitializerExpressionSyntax node)
            {
                InsertLLOCMap(node.GetLocation());
                base.VisitInitializerExpression(node);
            }


            private void calculateTypeLines(TypeDeclarationSyntax node)
            {
                foreach (var modifier in node.Modifiers)
                {
                    InsertLLOCMap(modifier.GetLocation());
                }
                foreach (var constraintClause in node.ConstraintClauses)
                {
                    InsertLLOCMap(constraintClause.WhereKeyword.GetLocation());
                    InsertLLOCMap(constraintClause.ColonToken.GetLocation());
                    foreach (var constraint in constraintClause.Constraints)
                    {
                        InsertLLOCMap(constraint.GetLocation());
                    }
                    InsertLLOCMap(constraintClause.GetLocation());
                }
                InsertLLOCMap(node.OpenBraceToken.GetLocation());
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
