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

using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;


namespace Columbus.Csharp.Asg.Visitors {

    /// <summary>
    /// Collects the inverse relation of any "one way" defined edges.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class VisitorReverseEdges : VisitorAbstractNodes {

        private ReverseEdges revEdges;
        public VisitorReverseEdges(ReverseEdges reverseEdges) : base() {
            revEdges = reverseEdges;
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Base.Base node, bool callVirtualBase) {
          uint id = node.Id;
          if (revEdges.reContainer[(int)id] == null) {
            revEdges.reContainer[(int)id] = new Dictionary<Types.EdgeKind, LinkedList<uint>>();
          }
        }

        public override void visitAliasQualifiedNameSyntax_Alias(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAliasQualifiedNameSyntax_Alias);
        }

        public override void visitAliasQualifiedNameSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAliasQualifiedNameSyntax_Name);
        }

        public override void visitAnonymousFunctionExpressionSyntax_Body(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAnonymousFunctionExpressionSyntax_Body);
        }

        public override void visitAnonymousMethodExpressionSyntax_ParameterList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAnonymousMethodExpressionSyntax_ParameterList);
        }

        public override void visitAnonymousObjectCreationExpressionSyntax_Initializers(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAnonymousObjectCreationExpressionSyntax_Initializers);
        }

        public override void visitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArrayCreationExpressionSyntax_Initializer);
        }

        public override void visitArrayCreationExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArrayCreationExpressionSyntax_Type);
        }

        public override void visitArrayTypeSyntax_ElementType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArrayTypeSyntax_ElementType);
        }

        public override void visitArrayTypeSyntax_RankSpecifiers(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArrayTypeSyntax_RankSpecifiers);
        }

        public override void visitAssignmentExpressionSyntax_EventAccessorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAssignmentExpressionSyntax_EventAccessorCall);
        }

        public override void visitAssignmentExpressionSyntax_Left(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAssignmentExpressionSyntax_Left);
        }

        public override void visitAssignmentExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAssignmentExpressionSyntax_OverloadedOperatorCall);
        }

        public override void visitAssignmentExpressionSyntax_Right(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAssignmentExpressionSyntax_Right);
        }

        public override void visitAwaitExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAwaitExpressionSyntax_Expression);
        }

        public override void visitBinaryExpressionSyntax_Left(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBinaryExpressionSyntax_Left);
        }

        public override void visitBinaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBinaryExpressionSyntax_OverloadedOperatorCall);
        }

        public override void visitBinaryExpressionSyntax_Right(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBinaryExpressionSyntax_Right);
        }

        public override void visitCastExpressionSyntax_ConversionOperatorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCastExpressionSyntax_ConversionOperatorCall);
        }

        public override void visitCastExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCastExpressionSyntax_Expression);
        }

        public override void visitCastExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCastExpressionSyntax_Type);
        }

        public override void visitCheckedExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCheckedExpressionSyntax_Expression);
        }

        public override void visitConditionalAccessExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConditionalAccessExpressionSyntax_Expression);
        }

        public override void visitConditionalAccessExpressionSyntax_WhenNotNull(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConditionalAccessExpressionSyntax_WhenNotNull);
        }

        public override void visitConditionalExpressionSyntax_Condition(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConditionalExpressionSyntax_Condition);
        }

        public override void visitConditionalExpressionSyntax_WhenFalse(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConditionalExpressionSyntax_WhenFalse);
        }

        public override void visitConditionalExpressionSyntax_WhenTrue(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConditionalExpressionSyntax_WhenTrue);
        }

        public override void visitDefaultExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkDefaultExpressionSyntax_Type);
        }

        public override void visitElementAccessExpressionSyntax_AccessorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkElementAccessExpressionSyntax_AccessorCall);
        }

        public override void visitElementAccessExpressionSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkElementAccessExpressionSyntax_ArgumentList);
        }

        public override void visitElementAccessExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkElementAccessExpressionSyntax_Expression);
        }

        public override void visitElementBindingExpressionSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkElementBindingExpressionSyntax_ArgumentList);
        }

        public override void visitGenericNameSyntax_TypeArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkGenericNameSyntax_TypeArgumentList);
        }

        public override void visitIdentifierNameSyntax_AccessorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIdentifierNameSyntax_AccessorCall);
        }

        public override void visitIdentifierNameSyntax_Declaration(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIdentifierNameSyntax_Declaration);
        }

        public override void visitImplicitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkImplicitArrayCreationExpressionSyntax_Initializer);
        }

        public override void visitImplicitElementAccessSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkImplicitElementAccessSyntax_ArgumentList);
        }

        public override void visitInitializerExpressionSyntax_Expressions(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInitializerExpressionSyntax_Expressions);
        }

        public override void visitInterpolatedStringExpressionSyntax_Contents(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInterpolatedStringExpressionSyntax_Contents);
        }

        public override void visitInvocationExpressionSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInvocationExpressionSyntax_ArgumentList);
        }

        public override void visitInvocationExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInvocationExpressionSyntax_Expression);
        }

        public override void visitInvocationExpressionSyntax_MethodCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInvocationExpressionSyntax_MethodCall);
        }

        public override void visitMakeRefExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMakeRefExpressionSyntax_Expression);
        }

        public override void visitMemberAccessExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMemberAccessExpressionSyntax_Expression);
        }

        public override void visitMemberAccessExpressionSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMemberAccessExpressionSyntax_Name);
        }

        public override void visitMemberBindingExpressionSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMemberBindingExpressionSyntax_Name);
        }

        public override void visitNullableTypeSyntax_ElementType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNullableTypeSyntax_ElementType);
        }

        public override void visitObjectCreationExpressionSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkObjectCreationExpressionSyntax_ArgumentList);
        }

        public override void visitObjectCreationExpressionSyntax_ConstructorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkObjectCreationExpressionSyntax_ConstructorCall);
        }

        public override void visitObjectCreationExpressionSyntax_Initializer(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkObjectCreationExpressionSyntax_Initializer);
        }

        public override void visitObjectCreationExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkObjectCreationExpressionSyntax_Type);
        }

        public override void visitParenthesizedExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkParenthesizedExpressionSyntax_Expression);
        }

        public override void visitParenthesizedLambdaExpressionSyntax_ParameterList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkParenthesizedLambdaExpressionSyntax_ParameterList);
        }

        public override void visitPointerTypeSyntax_ElementType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkPointerTypeSyntax_ElementType);
        }

        public override void visitPostfixUnaryExpressionSyntax_Operand(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkPostfixUnaryExpressionSyntax_Operand);
        }

        public override void visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall);
        }

        public override void visitPrefixUnaryExpressionSyntax_Operand(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkPrefixUnaryExpressionSyntax_Operand);
        }

        public override void visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall);
        }

        public override void visitQualifiedNameSyntax_Left(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQualifiedNameSyntax_Left);
        }

        public override void visitQualifiedNameSyntax_Right(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQualifiedNameSyntax_Right);
        }

        public override void visitQueryExpressionSyntax_Body(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQueryExpressionSyntax_Body);
        }

        public override void visitQueryExpressionSyntax_FromClause(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQueryExpressionSyntax_FromClause);
        }

        public override void visitRefTypeExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkRefTypeExpressionSyntax_Expression);
        }

        public override void visitRefValueExpressionSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkRefValueExpressionSyntax_Expression);
        }

        public override void visitRefValueExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkRefValueExpressionSyntax_Type);
        }

        public override void visitSimpleLambdaExpressionSyntax_Parameter(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkSimpleLambdaExpressionSyntax_Parameter);
        }

        public override void visitSizeOfExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkSizeOfExpressionSyntax_Type);
        }

        public override void visitStackAllocArrayCreationExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkStackAllocArrayCreationExpressionSyntax_Type);
        }

        public override void visitTypeOfExpressionSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeOfExpressionSyntax_Type);
        }

        public override void visitTypeSyntax_OriginalDefinition(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeSyntax_OriginalDefinition);
        }

        public override void visitBlockSyntax_Statements(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBlockSyntax_Statements);
        }

        public override void visitCheckedStatementSyntax_Block(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCheckedStatementSyntax_Block);
        }

        public override void visitDoStatementSyntax_Condition(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkDoStatementSyntax_Condition);
        }

        public override void visitDoStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkDoStatementSyntax_Statement);
        }

        public override void visitExpressionStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkExpressionStatementSyntax_Expression);
        }

        public override void visitFixedStatementSyntax_Declaration(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFixedStatementSyntax_Declaration);
        }

        public override void visitFixedStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFixedStatementSyntax_Statement);
        }

        public override void visitForEachStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForEachStatementSyntax_Expression);
        }

        public override void visitForEachStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForEachStatementSyntax_Statement);
        }

        public override void visitForEachStatementSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForEachStatementSyntax_Type);
        }

        public override void visitForStatementSyntax_Condition(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForStatementSyntax_Condition);
        }

        public override void visitForStatementSyntax_Declaration(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForStatementSyntax_Declaration);
        }

        public override void visitForStatementSyntax_Incrementors(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForStatementSyntax_Incrementors);
        }

        public override void visitForStatementSyntax_Initializers(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForStatementSyntax_Initializers);
        }

        public override void visitForStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkForStatementSyntax_Statement);
        }

        public override void visitGotoStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkGotoStatementSyntax_Expression);
        }

        public override void visitIfStatementSyntax_Condition(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIfStatementSyntax_Condition);
        }

        public override void visitIfStatementSyntax_Else(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIfStatementSyntax_Else);
        }

        public override void visitIfStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIfStatementSyntax_Statement);
        }

        public override void visitLabeledStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkLabeledStatementSyntax_Statement);
        }

        public override void visitLocalDeclarationStatementSyntax_Declaration(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkLocalDeclarationStatementSyntax_Declaration);
        }

        public override void visitLockStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkLockStatementSyntax_Expression);
        }

        public override void visitLockStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkLockStatementSyntax_Statement);
        }

        public override void visitReturnStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkReturnStatementSyntax_Expression);
        }

        public override void visitSwitchStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkSwitchStatementSyntax_Expression);
        }

        public override void visitSwitchStatementSyntax_Sections(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkSwitchStatementSyntax_Sections);
        }

        public override void visitThrowStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkThrowStatementSyntax_Expression);
        }

        public override void visitTryStatementSyntax_Block(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTryStatementSyntax_Block);
        }

        public override void visitTryStatementSyntax_Catches(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTryStatementSyntax_Catches);
        }

        public override void visitTryStatementSyntax_Finally(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTryStatementSyntax_Finally);
        }

        public override void visitUnsafeStatementSyntax_Block(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkUnsafeStatementSyntax_Block);
        }

        public override void visitUsingStatementSyntax_Declaration(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkUsingStatementSyntax_Declaration);
        }

        public override void visitUsingStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkUsingStatementSyntax_Expression);
        }

        public override void visitUsingStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkUsingStatementSyntax_Statement);
        }

        public override void visitWhileStatementSyntax_Condition(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkWhileStatementSyntax_Condition);
        }

        public override void visitWhileStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkWhileStatementSyntax_Statement);
        }

        public override void visitYieldStatementSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkYieldStatementSyntax_Expression);
        }

        public override void visitAccessorDeclarationSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAccessorDeclarationSyntax_AttributeLists);
        }

        public override void visitAccessorDeclarationSyntax_Body(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAccessorDeclarationSyntax_Body);
        }

        public override void visitAccessorListSyntax_Accessors(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAccessorListSyntax_Accessors);
        }

        public override void visitAnonymousObjectMemberDeclaratorSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAnonymousObjectMemberDeclaratorSyntax_Expression);
        }

        public override void visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAnonymousObjectMemberDeclaratorSyntax_NameEquals);
        }

        public override void visitArgumentSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArgumentSyntax_Expression);
        }

        public override void visitArgumentSyntax_NameColon(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArgumentSyntax_NameColon);
        }

        public override void visitArrayRankSpecifierSyntax_Sizes(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArrayRankSpecifierSyntax_Sizes);
        }

        public override void visitArrowExpressionClauseSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkArrowExpressionClauseSyntax_Expression);
        }

        public override void visitAttributeArgumentListSyntax_Arguments(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeArgumentListSyntax_Arguments);
        }

        public override void visitAttributeArgumentSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeArgumentSyntax_Expression);
        }

        public override void visitAttributeArgumentSyntax_NameColon(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeArgumentSyntax_NameColon);
        }

        public override void visitAttributeArgumentSyntax_NameEquals(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeArgumentSyntax_NameEquals);
        }

        public override void visitAttributeListSyntax_Attributes(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeListSyntax_Attributes);
        }

        public override void visitAttributeListSyntax_Target(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeListSyntax_Target);
        }

        public override void visitAttributeSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeSyntax_ArgumentList);
        }

        public override void visitAttributeSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeSyntax_Name);
        }

        public override void visitBaseArgumentListSyntax_Arguments(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseArgumentListSyntax_Arguments);
        }

        public override void visitBaseCrefParameterListSyntax_Parameters(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseCrefParameterListSyntax_Parameters);
        }

        public override void visitBaseFieldDeclarationSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseFieldDeclarationSyntax_AttributeLists);
        }

        public override void visitBaseFieldDeclarationSyntax_Declaration(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseFieldDeclarationSyntax_Declaration);
        }

        public override void visitBaseListSyntax_Types(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseListSyntax_Types);
        }

        public override void visitBaseMethodDeclarationSyntax_AccessedEnumMembers(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseMethodDeclarationSyntax_AccessedEnumMembers);
        }

        public override void visitBaseMethodDeclarationSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseMethodDeclarationSyntax_AttributeLists);
        }

        public override void visitBaseMethodDeclarationSyntax_Body(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseMethodDeclarationSyntax_Body);
        }

        public override void visitBaseMethodDeclarationSyntax_ParameterList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseMethodDeclarationSyntax_ParameterList);
        }

        public override void visitBaseParameterListSyntax_Parameters(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseParameterListSyntax_Parameters);
        }

        public override void visitBasePropertyDeclarationSyntax_AccessorList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBasePropertyDeclarationSyntax_AccessorList);
        }

        public override void visitBasePropertyDeclarationSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBasePropertyDeclarationSyntax_AttributeLists);
        }

        public override void visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
        }

        public override void visitBasePropertyDeclarationSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBasePropertyDeclarationSyntax_Type);
        }

        public override void visitBaseTypeDeclarationSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseTypeDeclarationSyntax_AttributeLists);
        }

        public override void visitBaseTypeDeclarationSyntax_BaseList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseTypeDeclarationSyntax_BaseList);
        }

        public override void visitBaseTypeSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkBaseTypeSyntax_Type);
        }

        public override void visitCaseSwitchLabelSyntax_Value(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCaseSwitchLabelSyntax_Value);
        }

        public override void visitCatchClauseSyntax_Block(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCatchClauseSyntax_Block);
        }

        public override void visitCatchClauseSyntax_Declaration(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCatchClauseSyntax_Declaration);
        }

        public override void visitCatchClauseSyntax_Filter(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCatchClauseSyntax_Filter);
        }

        public override void visitCatchDeclarationSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCatchDeclarationSyntax_Type);
        }

        public override void visitCatchFilterClauseSyntax_FilterExpression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCatchFilterClauseSyntax_FilterExpression);
        }

        public override void visitCompilationUnitSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCompilationUnitSyntax_AttributeLists);
        }

        public override void visitCompilationUnitSyntax_Externs(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCompilationUnitSyntax_Externs);
        }

        public override void visitCompilationUnitSyntax_Members(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCompilationUnitSyntax_Members);
        }

        public override void visitCompilationUnitSyntax_Usings(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCompilationUnitSyntax_Usings);
        }

        public override void visitConstructorDeclarationSyntax_Initializer(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConstructorDeclarationSyntax_Initializer);
        }

        public override void visitConstructorInitializerSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConstructorInitializerSyntax_ArgumentList);
        }

        public override void visitConstructorInitializerSyntax_ConstructorCall(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConstructorInitializerSyntax_ConstructorCall);
        }

        public override void visitConversionOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConversionOperatorDeclarationSyntax_ExpressionBody);
        }

        public override void visitConversionOperatorDeclarationSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConversionOperatorDeclarationSyntax_Type);
        }

        public override void visitConversionOperatorMemberCrefSyntax_Parameters(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConversionOperatorMemberCrefSyntax_Parameters);
        }

        public override void visitConversionOperatorMemberCrefSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkConversionOperatorMemberCrefSyntax_Type);
        }

        public override void visitCrefParameterSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkCrefParameterSyntax_Type);
        }

        public override void visitDelegateDeclarationSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkDelegateDeclarationSyntax_AttributeLists);
        }

        public override void visitDelegateDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkDelegateDeclarationSyntax_ConstraintClauses);
        }

        public override void visitDelegateDeclarationSyntax_ParameterList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkDelegateDeclarationSyntax_ParameterList);
        }

        public override void visitDelegateDeclarationSyntax_ReturnType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkDelegateDeclarationSyntax_ReturnType);
        }

        public override void visitElseClauseSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkElseClauseSyntax_Statement);
        }

        public override void visitEnumDeclarationSyntax_Members(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkEnumDeclarationSyntax_Members);
        }

        public override void visitEnumMemberDeclarationSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkEnumMemberDeclarationSyntax_AttributeLists);
        }

        public override void visitEnumMemberDeclarationSyntax_EqualsValue(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkEnumMemberDeclarationSyntax_EqualsValue);
        }

        public override void visitEqualsValueClauseSyntax_Value(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkEqualsValueClauseSyntax_Value);
        }

        public override void visitExplicitInterfaceSpecifierSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkExplicitInterfaceSpecifierSyntax_Name);
        }

        public override void visitFinallyClauseSyntax_Block(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFinallyClauseSyntax_Block);
        }

        public override void visitFromClauseSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFromClauseSyntax_Expression);
        }

        public override void visitFromClauseSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFromClauseSyntax_Type);
        }

        public override void visitGlobalStatementSyntax_Statement(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkGlobalStatementSyntax_Statement);
        }

        public override void visitGroupClauseSyntax_ByExpression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkGroupClauseSyntax_ByExpression);
        }

        public override void visitGroupClauseSyntax_GroupExpression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkGroupClauseSyntax_GroupExpression);
        }

        public override void visitIncompleteMemberSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIncompleteMemberSyntax_AttributeLists);
        }

        public override void visitIncompleteMemberSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIncompleteMemberSyntax_Type);
        }

        public override void visitIndexerDeclarationSyntax_ExpressionBody(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIndexerDeclarationSyntax_ExpressionBody);
        }

        public override void visitIndexerDeclarationSyntax_ParameterList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIndexerDeclarationSyntax_ParameterList);
        }

        public override void visitIndexerMemberCrefSyntax_Parameters(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkIndexerMemberCrefSyntax_Parameters);
        }

        public override void visitInterpolationAlignmentClauseSyntax_Value(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInterpolationAlignmentClauseSyntax_Value);
        }

        public override void visitInterpolationSyntax_AlignmentClause(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInterpolationSyntax_AlignmentClause);
        }

        public override void visitInterpolationSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInterpolationSyntax_Expression);
        }

        public override void visitInterpolationSyntax_FormatClause(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkInterpolationSyntax_FormatClause);
        }

        public override void visitJoinClauseSyntax_InExpression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkJoinClauseSyntax_InExpression);
        }

        public override void visitJoinClauseSyntax_Into(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkJoinClauseSyntax_Into);
        }

        public override void visitJoinClauseSyntax_LeftExpression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkJoinClauseSyntax_LeftExpression);
        }

        public override void visitJoinClauseSyntax_RightExpression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkJoinClauseSyntax_RightExpression);
        }

        public override void visitJoinClauseSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkJoinClauseSyntax_Type);
        }

        public override void visitLetClauseSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkLetClauseSyntax_Expression);
        }

        public override void visitMethodDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodDeclarationSyntax_ConstraintClauses);
        }

        public override void visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier);
        }

        public override void visitMethodDeclarationSyntax_ExpressionBody(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodDeclarationSyntax_ExpressionBody);
        }

        public override void visitMethodDeclarationSyntax_ReturnType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodDeclarationSyntax_ReturnType);
        }

        public override void visitNameColonSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNameColonSyntax_Name);
        }

        public override void visitNameEqualsSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNameEqualsSyntax_Name);
        }

        public override void visitNameMemberCrefSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNameMemberCrefSyntax_Name);
        }

        public override void visitNameMemberCrefSyntax_Parameters(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNameMemberCrefSyntax_Parameters);
        }

        public override void visitNamespaceDeclarationSyntax_Externs(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNamespaceDeclarationSyntax_Externs);
        }

        public override void visitNamespaceDeclarationSyntax_Members(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNamespaceDeclarationSyntax_Members);
        }

        public override void visitNamespaceDeclarationSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNamespaceDeclarationSyntax_Name);
        }

        public override void visitNamespaceDeclarationSyntax_Usings(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNamespaceDeclarationSyntax_Usings);
        }

        public override void visitOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkOperatorDeclarationSyntax_ExpressionBody);
        }

        public override void visitOperatorDeclarationSyntax_ReturnType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkOperatorDeclarationSyntax_ReturnType);
        }

        public override void visitOperatorMemberCrefSyntax_Parameters(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkOperatorMemberCrefSyntax_Parameters);
        }

        public override void visitOrderByClauseSyntax_Orderings(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkOrderByClauseSyntax_Orderings);
        }

        public override void visitOrderingSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkOrderingSyntax_Expression);
        }

        public override void visitParameterSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkParameterSyntax_AttributeLists);
        }

        public override void visitParameterSyntax_Default(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkParameterSyntax_Default);
        }

        public override void visitParameterSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkParameterSyntax_Type);
        }

        public override void visitPropertyDeclarationSyntax_ExpressionBody(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkPropertyDeclarationSyntax_ExpressionBody);
        }

        public override void visitPropertyDeclarationSyntax_Initializer(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkPropertyDeclarationSyntax_Initializer);
        }

        public override void visitQualifiedCrefSyntax_Container(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQualifiedCrefSyntax_Container);
        }

        public override void visitQualifiedCrefSyntax_Member(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQualifiedCrefSyntax_Member);
        }

        public override void visitQueryBodySyntax_Clauses(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQueryBodySyntax_Clauses);
        }

        public override void visitQueryBodySyntax_Continuation(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQueryBodySyntax_Continuation);
        }

        public override void visitQueryBodySyntax_SelectOrGroup(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQueryBodySyntax_SelectOrGroup);
        }

        public override void visitQueryContinuationSyntax_Body(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkQueryContinuationSyntax_Body);
        }

        public override void visitSelectClauseSyntax_Expression(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkSelectClauseSyntax_Expression);
        }

        public override void visitSwitchSectionSyntax_Labels(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkSwitchSectionSyntax_Labels);
        }

        public override void visitSwitchSectionSyntax_Statements(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkSwitchSectionSyntax_Statements);
        }

        public override void visitTypeArgumentListSyntax_Arguments(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeArgumentListSyntax_Arguments);
        }

        public override void visitTypeConstraintSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeConstraintSyntax_Type);
        }

        public override void visitTypeCrefSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeCrefSyntax_Type);
        }

        public override void visitTypeDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeDeclarationSyntax_ConstraintClauses);
        }

        public override void visitTypeDeclarationSyntax_Members(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeDeclarationSyntax_Members);
        }

        public override void visitTypeDeclarationSyntax_TypeParameterList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeDeclarationSyntax_TypeParameterList);
        }

        public override void visitTypeParameterConstraintClauseSyntax_Constraints(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Constraints);
        }

        public override void visitTypeParameterConstraintClauseSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Name);
        }

        public override void visitTypeParameterListSyntax_Parameters(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeParameterListSyntax_Parameters);
        }

        public override void visitTypeParameterSyntax_AttributeLists(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeParameterSyntax_AttributeLists);
        }

        public override void visitUsingDirectiveSyntax_Alias(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkUsingDirectiveSyntax_Alias);
        }

        public override void visitUsingDirectiveSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkUsingDirectiveSyntax_Name);
        }

        public override void visitVariableDeclarationSyntax_Type(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkVariableDeclarationSyntax_Type);
        }

        public override void visitVariableDeclarationSyntax_Variables(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkVariableDeclarationSyntax_Variables);
        }

        public override void visitVariableDeclaratorSyntax_ArgumentList(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkVariableDeclaratorSyntax_ArgumentList);
        }

        public override void visitVariableDeclaratorSyntax_Initializer(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkVariableDeclaratorSyntax_Initializer);
        }

        public override void visitWhereClauseSyntax_Condition(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkWhereClauseSyntax_Condition);
        }

        public override void visitXmlAttributeSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlAttributeSyntax_Name);
        }

        public override void visitXmlCrefAttributeSyntax_Cref(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlCrefAttributeSyntax_Cref);
        }

        public override void visitXmlElementEndTagSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlElementEndTagSyntax_Name);
        }

        public override void visitXmlElementStartTagSyntax_Attributes(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlElementStartTagSyntax_Attributes);
        }

        public override void visitXmlElementStartTagSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlElementStartTagSyntax_Name);
        }

        public override void visitXmlElementSyntax_Content(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlElementSyntax_Content);
        }

        public override void visitXmlElementSyntax_EndTag(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlElementSyntax_EndTag);
        }

        public override void visitXmlElementSyntax_StartTag(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlElementSyntax_StartTag);
        }

        public override void visitXmlEmptyElementSyntax_Attributes(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlEmptyElementSyntax_Attributes);
        }

        public override void visitXmlEmptyElementSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlEmptyElementSyntax_Name);
        }

        public override void visitXmlNameAttributeSyntax_Identifier(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlNameAttributeSyntax_Identifier);
        }

        public override void visitXmlNameSyntax_Prefix(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlNameSyntax_Prefix);
        }

        public override void visitXmlProcessingInstructionSyntax_Name(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkXmlProcessingInstructionSyntax_Name);
        }

        }
}