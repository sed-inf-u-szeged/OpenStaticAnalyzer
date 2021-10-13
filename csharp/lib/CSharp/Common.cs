using System;
using System.Text;

namespace Columbus.Csharp.Asg {

    /// <summary>
    /// Contains general graph algorithms and common functions.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class Common {

        /// <summary>
        /// Decides whether the node is base::Positioned or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is base::Positioned.</returns>
        public static bool getIsPositioned(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Base.Positioned);
        }

        /// <summary>
        /// Decides whether the node is expression::AliasQualifiedNameSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::AliasQualifiedNameSyntax.</returns>
        public static bool getIsAliasQualifiedNameSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::AnonymousFunctionExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::AnonymousFunctionExpressionSyntax.</returns>
        public static bool getIsAnonymousFunctionExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::AnonymousMethodExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::AnonymousMethodExpressionSyntax.</returns>
        public static bool getIsAnonymousMethodExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::AnonymousObjectCreationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::AnonymousObjectCreationExpressionSyntax.</returns>
        public static bool getIsAnonymousObjectCreationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ArrayCreationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ArrayCreationExpressionSyntax.</returns>
        public static bool getIsArrayCreationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ArrayTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ArrayTypeSyntax.</returns>
        public static bool getIsArrayTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::AssignmentExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::AssignmentExpressionSyntax.</returns>
        public static bool getIsAssignmentExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::AwaitExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::AwaitExpressionSyntax.</returns>
        public static bool getIsAwaitExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::BaseExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::BaseExpressionSyntax.</returns>
        public static bool getIsBaseExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::BinaryExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::BinaryExpressionSyntax.</returns>
        public static bool getIsBinaryExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::CastExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::CastExpressionSyntax.</returns>
        public static bool getIsCastExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::CheckedExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::CheckedExpressionSyntax.</returns>
        public static bool getIsCheckedExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ConditionalAccessExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ConditionalAccessExpressionSyntax.</returns>
        public static bool getIsConditionalAccessExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ConditionalExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ConditionalExpressionSyntax.</returns>
        public static bool getIsConditionalExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::DeclarationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::DeclarationExpressionSyntax.</returns>
        public static bool getIsDeclarationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::DefaultExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::DefaultExpressionSyntax.</returns>
        public static bool getIsDefaultExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ElementAccessExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ElementAccessExpressionSyntax.</returns>
        public static bool getIsElementAccessExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ElementBindingExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ElementBindingExpressionSyntax.</returns>
        public static bool getIsElementBindingExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ExpressionSyntax.</returns>
        public static bool getIsExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::GenericNameSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::GenericNameSyntax.</returns>
        public static bool getIsGenericNameSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::IdentifierNameSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::IdentifierNameSyntax.</returns>
        public static bool getIsIdentifierNameSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ImplicitArrayCreationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ImplicitArrayCreationExpressionSyntax.</returns>
        public static bool getIsImplicitArrayCreationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ImplicitElementAccessSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ImplicitElementAccessSyntax.</returns>
        public static bool getIsImplicitElementAccessSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ImplicitStackAllocArrayCreationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ImplicitStackAllocArrayCreationExpressionSyntax.</returns>
        public static bool getIsImplicitStackAllocArrayCreationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::InitializerExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::InitializerExpressionSyntax.</returns>
        public static bool getIsInitializerExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::InstanceExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::InstanceExpressionSyntax.</returns>
        public static bool getIsInstanceExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::InterpolatedStringExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::InterpolatedStringExpressionSyntax.</returns>
        public static bool getIsInterpolatedStringExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::InvocationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::InvocationExpressionSyntax.</returns>
        public static bool getIsInvocationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::IsPatternExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::IsPatternExpressionSyntax.</returns>
        public static bool getIsIsPatternExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::LambdaExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::LambdaExpressionSyntax.</returns>
        public static bool getIsLambdaExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::LiteralExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::LiteralExpressionSyntax.</returns>
        public static bool getIsLiteralExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::MakeRefExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::MakeRefExpressionSyntax.</returns>
        public static bool getIsMakeRefExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::MemberAccessExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::MemberAccessExpressionSyntax.</returns>
        public static bool getIsMemberAccessExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::MemberBindingExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::MemberBindingExpressionSyntax.</returns>
        public static bool getIsMemberBindingExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::NameSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::NameSyntax.</returns>
        public static bool getIsNameSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.NameSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::NullableTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::NullableTypeSyntax.</returns>
        public static bool getIsNullableTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ObjectCreationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ObjectCreationExpressionSyntax.</returns>
        public static bool getIsObjectCreationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::OmittedArraySizeExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::OmittedArraySizeExpressionSyntax.</returns>
        public static bool getIsOmittedArraySizeExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::OmittedTypeArgumentSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::OmittedTypeArgumentSyntax.</returns>
        public static bool getIsOmittedTypeArgumentSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ParenthesizedExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ParenthesizedExpressionSyntax.</returns>
        public static bool getIsParenthesizedExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ParenthesizedLambdaExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ParenthesizedLambdaExpressionSyntax.</returns>
        public static bool getIsParenthesizedLambdaExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::PointerTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::PointerTypeSyntax.</returns>
        public static bool getIsPointerTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::PostfixUnaryExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::PostfixUnaryExpressionSyntax.</returns>
        public static bool getIsPostfixUnaryExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::PredefinedTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::PredefinedTypeSyntax.</returns>
        public static bool getIsPredefinedTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::PrefixUnaryExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::PrefixUnaryExpressionSyntax.</returns>
        public static bool getIsPrefixUnaryExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::QualifiedNameSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::QualifiedNameSyntax.</returns>
        public static bool getIsQualifiedNameSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::QueryExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::QueryExpressionSyntax.</returns>
        public static bool getIsQueryExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::RangeExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::RangeExpressionSyntax.</returns>
        public static bool getIsRangeExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::RefExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::RefExpressionSyntax.</returns>
        public static bool getIsRefExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::RefTypeExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::RefTypeExpressionSyntax.</returns>
        public static bool getIsRefTypeExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::RefTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::RefTypeSyntax.</returns>
        public static bool getIsRefTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::RefValueExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::RefValueExpressionSyntax.</returns>
        public static bool getIsRefValueExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::SimpleLambdaExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::SimpleLambdaExpressionSyntax.</returns>
        public static bool getIsSimpleLambdaExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::SimpleNameSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::SimpleNameSyntax.</returns>
        public static bool getIsSimpleNameSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::SizeOfExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::SizeOfExpressionSyntax.</returns>
        public static bool getIsSizeOfExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::StackAllocArrayCreationExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::StackAllocArrayCreationExpressionSyntax.</returns>
        public static bool getIsStackAllocArrayCreationExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::SwitchExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::SwitchExpressionSyntax.</returns>
        public static bool getIsSwitchExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ThisExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ThisExpressionSyntax.</returns>
        public static bool getIsThisExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::ThrowExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::ThrowExpressionSyntax.</returns>
        public static bool getIsThrowExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::TupleExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::TupleExpressionSyntax.</returns>
        public static bool getIsTupleExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::TupleTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::TupleTypeSyntax.</returns>
        public static bool getIsTupleTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::TypeOfExpressionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::TypeOfExpressionSyntax.</returns>
        public static bool getIsTypeOfExpressionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax);
        }

        /// <summary>
        /// Decides whether the node is expression::TypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is expression::TypeSyntax.</returns>
        public static bool getIsTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::BlockSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::BlockSyntax.</returns>
        public static bool getIsBlockSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::BreakStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::BreakStatementSyntax.</returns>
        public static bool getIsBreakStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::CheckedStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::CheckedStatementSyntax.</returns>
        public static bool getIsCheckedStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::CommonForEachStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::CommonForEachStatementSyntax.</returns>
        public static bool getIsCommonForEachStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::ContinueStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::ContinueStatementSyntax.</returns>
        public static bool getIsContinueStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::DoStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::DoStatementSyntax.</returns>
        public static bool getIsDoStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::EmptyStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::EmptyStatementSyntax.</returns>
        public static bool getIsEmptyStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::ExpressionStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::ExpressionStatementSyntax.</returns>
        public static bool getIsExpressionStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::FixedStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::FixedStatementSyntax.</returns>
        public static bool getIsFixedStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::ForEachStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::ForEachStatementSyntax.</returns>
        public static bool getIsForEachStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::ForEachVariableStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::ForEachVariableStatementSyntax.</returns>
        public static bool getIsForEachVariableStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::ForStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::ForStatementSyntax.</returns>
        public static bool getIsForStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::GotoStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::GotoStatementSyntax.</returns>
        public static bool getIsGotoStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::IfStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::IfStatementSyntax.</returns>
        public static bool getIsIfStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::LabeledStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::LabeledStatementSyntax.</returns>
        public static bool getIsLabeledStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::LocalDeclarationStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::LocalDeclarationStatementSyntax.</returns>
        public static bool getIsLocalDeclarationStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::LocalFunctionStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::LocalFunctionStatementSyntax.</returns>
        public static bool getIsLocalFunctionStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::LockStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::LockStatementSyntax.</returns>
        public static bool getIsLockStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::ReturnStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::ReturnStatementSyntax.</returns>
        public static bool getIsReturnStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::StatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::StatementSyntax.</returns>
        public static bool getIsStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::SwitchStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::SwitchStatementSyntax.</returns>
        public static bool getIsSwitchStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::ThrowStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::ThrowStatementSyntax.</returns>
        public static bool getIsThrowStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::TryStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::TryStatementSyntax.</returns>
        public static bool getIsTryStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::UnsafeStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::UnsafeStatementSyntax.</returns>
        public static bool getIsUnsafeStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::UsingStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::UsingStatementSyntax.</returns>
        public static bool getIsUsingStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::WhileStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::WhileStatementSyntax.</returns>
        public static bool getIsWhileStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is statement::YieldStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is statement::YieldStatementSyntax.</returns>
        public static bool getIsYieldStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AccessorDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AccessorDeclarationSyntax.</returns>
        public static bool getIsAccessorDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AccessorListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AccessorListSyntax.</returns>
        public static bool getIsAccessorListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AnonymousObjectMemberDeclaratorSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AnonymousObjectMemberDeclaratorSyntax.</returns>
        public static bool getIsAnonymousObjectMemberDeclaratorSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ArgumentListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ArgumentListSyntax.</returns>
        public static bool getIsArgumentListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ArgumentSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ArgumentSyntax.</returns>
        public static bool getIsArgumentSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ArrayRankSpecifierSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ArrayRankSpecifierSyntax.</returns>
        public static bool getIsArrayRankSpecifierSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ArrowExpressionClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ArrowExpressionClauseSyntax.</returns>
        public static bool getIsArrowExpressionClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AttributeArgumentListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AttributeArgumentListSyntax.</returns>
        public static bool getIsAttributeArgumentListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AttributeArgumentSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AttributeArgumentSyntax.</returns>
        public static bool getIsAttributeArgumentSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AttributeListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AttributeListSyntax.</returns>
        public static bool getIsAttributeListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AttributeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AttributeSyntax.</returns>
        public static bool getIsAttributeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::AttributeTargetSpecifierSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::AttributeTargetSpecifierSyntax.</returns>
        public static bool getIsAttributeTargetSpecifierSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseArgumentListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseArgumentListSyntax.</returns>
        public static bool getIsBaseArgumentListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseCrefParameterListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseCrefParameterListSyntax.</returns>
        public static bool getIsBaseCrefParameterListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseFieldDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseFieldDeclarationSyntax.</returns>
        public static bool getIsBaseFieldDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseListSyntax.</returns>
        public static bool getIsBaseListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseMethodDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseMethodDeclarationSyntax.</returns>
        public static bool getIsBaseMethodDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseParameterListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseParameterListSyntax.</returns>
        public static bool getIsBaseParameterListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BasePropertyDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BasePropertyDeclarationSyntax.</returns>
        public static bool getIsBasePropertyDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseTypeDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseTypeDeclarationSyntax.</returns>
        public static bool getIsBaseTypeDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BaseTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BaseTypeSyntax.</returns>
        public static bool getIsBaseTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BracketedArgumentListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BracketedArgumentListSyntax.</returns>
        public static bool getIsBracketedArgumentListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::BracketedParameterListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::BracketedParameterListSyntax.</returns>
        public static bool getIsBracketedParameterListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CasePatternSwitchLabelSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CasePatternSwitchLabelSyntax.</returns>
        public static bool getIsCasePatternSwitchLabelSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CaseSwitchLabelSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CaseSwitchLabelSyntax.</returns>
        public static bool getIsCaseSwitchLabelSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CatchClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CatchClauseSyntax.</returns>
        public static bool getIsCatchClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CatchDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CatchDeclarationSyntax.</returns>
        public static bool getIsCatchDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CatchFilterClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CatchFilterClauseSyntax.</returns>
        public static bool getIsCatchFilterClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ClassDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ClassDeclarationSyntax.</returns>
        public static bool getIsClassDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ClassOrStructConstraintSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ClassOrStructConstraintSyntax.</returns>
        public static bool getIsClassOrStructConstraintSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CompilationUnitSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CompilationUnitSyntax.</returns>
        public static bool getIsCompilationUnitSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ConstantPatternSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ConstantPatternSyntax.</returns>
        public static bool getIsConstantPatternSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ConstructorConstraintSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ConstructorConstraintSyntax.</returns>
        public static bool getIsConstructorConstraintSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ConstructorDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ConstructorDeclarationSyntax.</returns>
        public static bool getIsConstructorDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ConstructorInitializerSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ConstructorInitializerSyntax.</returns>
        public static bool getIsConstructorInitializerSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ConversionOperatorDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ConversionOperatorDeclarationSyntax.</returns>
        public static bool getIsConversionOperatorDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ConversionOperatorMemberCrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ConversionOperatorMemberCrefSyntax.</returns>
        public static bool getIsConversionOperatorMemberCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CrefBracketedParameterListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CrefBracketedParameterListSyntax.</returns>
        public static bool getIsCrefBracketedParameterListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CrefParameterListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CrefParameterListSyntax.</returns>
        public static bool getIsCrefParameterListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CrefParameterSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CrefParameterSyntax.</returns>
        public static bool getIsCrefParameterSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::CrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::CrefSyntax.</returns>
        public static bool getIsCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::DeclarationPatternSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::DeclarationPatternSyntax.</returns>
        public static bool getIsDeclarationPatternSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::DefaultSwitchLabelSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::DefaultSwitchLabelSyntax.</returns>
        public static bool getIsDefaultSwitchLabelSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::DelegateDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::DelegateDeclarationSyntax.</returns>
        public static bool getIsDelegateDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::DestructorDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::DestructorDeclarationSyntax.</returns>
        public static bool getIsDestructorDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::DiscardDesignationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::DiscardDesignationSyntax.</returns>
        public static bool getIsDiscardDesignationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::DiscardPatternSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::DiscardPatternSyntax.</returns>
        public static bool getIsDiscardPatternSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ElseClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ElseClauseSyntax.</returns>
        public static bool getIsElseClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::EnumDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::EnumDeclarationSyntax.</returns>
        public static bool getIsEnumDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::EnumMemberDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::EnumMemberDeclarationSyntax.</returns>
        public static bool getIsEnumMemberDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::EqualsValueClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::EqualsValueClauseSyntax.</returns>
        public static bool getIsEqualsValueClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::EventDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::EventDeclarationSyntax.</returns>
        public static bool getIsEventDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::EventFieldDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::EventFieldDeclarationSyntax.</returns>
        public static bool getIsEventFieldDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ExplicitInterfaceSpecifierSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ExplicitInterfaceSpecifierSyntax.</returns>
        public static bool getIsExplicitInterfaceSpecifierSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ExternAliasDirectiveSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ExternAliasDirectiveSyntax.</returns>
        public static bool getIsExternAliasDirectiveSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::FieldDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::FieldDeclarationSyntax.</returns>
        public static bool getIsFieldDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::FinallyClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::FinallyClauseSyntax.</returns>
        public static bool getIsFinallyClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::FromClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::FromClauseSyntax.</returns>
        public static bool getIsFromClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::GlobalStatementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::GlobalStatementSyntax.</returns>
        public static bool getIsGlobalStatementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::GroupClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::GroupClauseSyntax.</returns>
        public static bool getIsGroupClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::IncompleteMemberSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::IncompleteMemberSyntax.</returns>
        public static bool getIsIncompleteMemberSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::IndexerDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::IndexerDeclarationSyntax.</returns>
        public static bool getIsIndexerDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::IndexerMemberCrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::IndexerMemberCrefSyntax.</returns>
        public static bool getIsIndexerMemberCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::InterfaceDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::InterfaceDeclarationSyntax.</returns>
        public static bool getIsInterfaceDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::InterpolatedStringContentSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::InterpolatedStringContentSyntax.</returns>
        public static bool getIsInterpolatedStringContentSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::InterpolatedStringTextSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::InterpolatedStringTextSyntax.</returns>
        public static bool getIsInterpolatedStringTextSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::InterpolationAlignmentClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::InterpolationAlignmentClauseSyntax.</returns>
        public static bool getIsInterpolationAlignmentClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::InterpolationFormatClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::InterpolationFormatClauseSyntax.</returns>
        public static bool getIsInterpolationFormatClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::InterpolationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::InterpolationSyntax.</returns>
        public static bool getIsInterpolationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::JoinClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::JoinClauseSyntax.</returns>
        public static bool getIsJoinClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::JoinIntoClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::JoinIntoClauseSyntax.</returns>
        public static bool getIsJoinIntoClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::LetClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::LetClauseSyntax.</returns>
        public static bool getIsLetClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::MemberCrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::MemberCrefSyntax.</returns>
        public static bool getIsMemberCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::MemberDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::MemberDeclarationSyntax.</returns>
        public static bool getIsMemberDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::MethodDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::MethodDeclarationSyntax.</returns>
        public static bool getIsMethodDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::NameColonSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::NameColonSyntax.</returns>
        public static bool getIsNameColonSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::NameEqualsSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::NameEqualsSyntax.</returns>
        public static bool getIsNameEqualsSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::NameMemberCrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::NameMemberCrefSyntax.</returns>
        public static bool getIsNameMemberCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::NamespaceDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::NamespaceDeclarationSyntax.</returns>
        public static bool getIsNamespaceDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::OperatorDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::OperatorDeclarationSyntax.</returns>
        public static bool getIsOperatorDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::OperatorMemberCrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::OperatorMemberCrefSyntax.</returns>
        public static bool getIsOperatorMemberCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::OrderByClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::OrderByClauseSyntax.</returns>
        public static bool getIsOrderByClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::OrderingSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::OrderingSyntax.</returns>
        public static bool getIsOrderingSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ParameterListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ParameterListSyntax.</returns>
        public static bool getIsParameterListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ParameterSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ParameterSyntax.</returns>
        public static bool getIsParameterSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::ParenthesizedVariableDesignationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::ParenthesizedVariableDesignationSyntax.</returns>
        public static bool getIsParenthesizedVariableDesignationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::PatternSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::PatternSyntax.</returns>
        public static bool getIsPatternSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::PositionalPatternClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::PositionalPatternClauseSyntax.</returns>
        public static bool getIsPositionalPatternClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::PropertyDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::PropertyDeclarationSyntax.</returns>
        public static bool getIsPropertyDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::PropertyPatternClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::PropertyPatternClauseSyntax.</returns>
        public static bool getIsPropertyPatternClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::QualifiedCrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::QualifiedCrefSyntax.</returns>
        public static bool getIsQualifiedCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::QueryBodySyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::QueryBodySyntax.</returns>
        public static bool getIsQueryBodySyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::QueryClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::QueryClauseSyntax.</returns>
        public static bool getIsQueryClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::QueryContinuationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::QueryContinuationSyntax.</returns>
        public static bool getIsQueryContinuationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::RecursivePatternSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::RecursivePatternSyntax.</returns>
        public static bool getIsRecursivePatternSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SelectClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SelectClauseSyntax.</returns>
        public static bool getIsSelectClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SelectOrGroupClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SelectOrGroupClauseSyntax.</returns>
        public static bool getIsSelectOrGroupClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SimpleBaseTypeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SimpleBaseTypeSyntax.</returns>
        public static bool getIsSimpleBaseTypeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SingleVariableDesignationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SingleVariableDesignationSyntax.</returns>
        public static bool getIsSingleVariableDesignationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::StructDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::StructDeclarationSyntax.</returns>
        public static bool getIsStructDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SubpatternSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SubpatternSyntax.</returns>
        public static bool getIsSubpatternSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SwitchExpressionArmSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SwitchExpressionArmSyntax.</returns>
        public static bool getIsSwitchExpressionArmSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SwitchLabelSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SwitchLabelSyntax.</returns>
        public static bool getIsSwitchLabelSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SwitchSectionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SwitchSectionSyntax.</returns>
        public static bool getIsSwitchSectionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::SyntaxToken or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::SyntaxToken.</returns>
        public static bool getIsSyntaxToken(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken);
        }

        /// <summary>
        /// Decides whether the node is structure::TupleElementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TupleElementSyntax.</returns>
        public static bool getIsTupleElementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeArgumentListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeArgumentListSyntax.</returns>
        public static bool getIsTypeArgumentListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeConstraintSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeConstraintSyntax.</returns>
        public static bool getIsTypeConstraintSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeCrefSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeCrefSyntax.</returns>
        public static bool getIsTypeCrefSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeDeclarationSyntax.</returns>
        public static bool getIsTypeDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeParameterConstraintClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeParameterConstraintClauseSyntax.</returns>
        public static bool getIsTypeParameterConstraintClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeParameterConstraintSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeParameterConstraintSyntax.</returns>
        public static bool getIsTypeParameterConstraintSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeParameterListSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeParameterListSyntax.</returns>
        public static bool getIsTypeParameterListSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::TypeParameterSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::TypeParameterSyntax.</returns>
        public static bool getIsTypeParameterSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::UsingDirectiveSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::UsingDirectiveSyntax.</returns>
        public static bool getIsUsingDirectiveSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::VarPatternSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::VarPatternSyntax.</returns>
        public static bool getIsVarPatternSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::VariableDeclarationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::VariableDeclarationSyntax.</returns>
        public static bool getIsVariableDeclarationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::VariableDeclaratorSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::VariableDeclaratorSyntax.</returns>
        public static bool getIsVariableDeclaratorSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::VariableDesignationSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::VariableDesignationSyntax.</returns>
        public static bool getIsVariableDesignationSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::WhenClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::WhenClauseSyntax.</returns>
        public static bool getIsWhenClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::WhereClauseSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::WhereClauseSyntax.</returns>
        public static bool getIsWhereClauseSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlAttributeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlAttributeSyntax.</returns>
        public static bool getIsXmlAttributeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlCDataSectionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlCDataSectionSyntax.</returns>
        public static bool getIsXmlCDataSectionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlCommentSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlCommentSyntax.</returns>
        public static bool getIsXmlCommentSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlCrefAttributeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlCrefAttributeSyntax.</returns>
        public static bool getIsXmlCrefAttributeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlElementEndTagSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlElementEndTagSyntax.</returns>
        public static bool getIsXmlElementEndTagSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlElementStartTagSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlElementStartTagSyntax.</returns>
        public static bool getIsXmlElementStartTagSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlElementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlElementSyntax.</returns>
        public static bool getIsXmlElementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlEmptyElementSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlEmptyElementSyntax.</returns>
        public static bool getIsXmlEmptyElementSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlNameAttributeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlNameAttributeSyntax.</returns>
        public static bool getIsXmlNameAttributeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlNameSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlNameSyntax.</returns>
        public static bool getIsXmlNameSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlNodeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlNodeSyntax.</returns>
        public static bool getIsXmlNodeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlPrefixSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlPrefixSyntax.</returns>
        public static bool getIsXmlPrefixSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlProcessingInstructionSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlProcessingInstructionSyntax.</returns>
        public static bool getIsXmlProcessingInstructionSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlTextAttributeSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlTextAttributeSyntax.</returns>
        public static bool getIsXmlTextAttributeSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax);
        }

        /// <summary>
        /// Decides whether the node is structure::XmlTextSyntax or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is structure::XmlTextSyntax.</returns>
        public static bool getIsXmlTextSyntax(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax);
        }

        /// <summary>
        /// Decides whether the 'baseKind' is one of the base kinds (transitive) of 'what'.
        /// </summary>
        /// <param name="what">[in] The examined node kind.</param>
        /// <param name="baseKind">[in] The base node kind.</param>
        /// <returns>Returns true if 'baseKind' is a basekind of 'what'.</returns>
        public static bool getIsBaseClassKind(Types.NodeKind what, Types.NodeKind baseKind) {
            Types.NodeKind type = what;

            while (type != baseKind) {
                switch (type) {
                    case Types.NodeKind.ndkBase:
                        return false;
                    case Types.NodeKind.ndkPositioned:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkAliasQualifiedNameSyntax:
                        type = Types.NodeKind.ndkNameSyntax;
                        break;
                    case Types.NodeKind.ndkAnonymousFunctionExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkAnonymousMethodExpressionSyntax:
                        type = Types.NodeKind.ndkAnonymousFunctionExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkAnonymousObjectCreationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkArrayCreationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkArrayTypeSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkAssignmentExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkAwaitExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkBaseExpressionSyntax:
                        type = Types.NodeKind.ndkInstanceExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkBinaryExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkCastExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkCheckedExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkConditionalAccessExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkConditionalExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkDeclarationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkDefaultExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkElementAccessExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkElementBindingExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkExpressionSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkGenericNameSyntax:
                        type = Types.NodeKind.ndkSimpleNameSyntax;
                        break;
                    case Types.NodeKind.ndkIdentifierNameSyntax:
                        type = Types.NodeKind.ndkSimpleNameSyntax;
                        break;
                    case Types.NodeKind.ndkImplicitArrayCreationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkImplicitElementAccessSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkImplicitStackAllocArrayCreationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkInitializerExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkInstanceExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkInterpolatedStringExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkInvocationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkIsPatternExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkLambdaExpressionSyntax:
                        type = Types.NodeKind.ndkAnonymousFunctionExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkLiteralExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkMakeRefExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkMemberAccessExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkMemberBindingExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkNameSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkNullableTypeSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkObjectCreationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkOmittedArraySizeExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkOmittedTypeArgumentSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkParenthesizedExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkParenthesizedLambdaExpressionSyntax:
                        type = Types.NodeKind.ndkLambdaExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkPointerTypeSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkPostfixUnaryExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkPredefinedTypeSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkPrefixUnaryExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkQualifiedNameSyntax:
                        type = Types.NodeKind.ndkNameSyntax;
                        break;
                    case Types.NodeKind.ndkQueryExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkRangeExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkRefExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkRefTypeExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkRefTypeSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkRefValueExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkSimpleLambdaExpressionSyntax:
                        type = Types.NodeKind.ndkLambdaExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkSimpleNameSyntax:
                        type = Types.NodeKind.ndkNameSyntax;
                        break;
                    case Types.NodeKind.ndkSizeOfExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkStackAllocArrayCreationExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkSwitchExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkThisExpressionSyntax:
                        type = Types.NodeKind.ndkInstanceExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkThrowExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkTupleExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkTupleTypeSyntax:
                        type = Types.NodeKind.ndkTypeSyntax;
                        break;
                    case Types.NodeKind.ndkTypeOfExpressionSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkTypeSyntax:
                        type = Types.NodeKind.ndkExpressionSyntax;
                        break;
                    case Types.NodeKind.ndkBlockSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkBreakStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkCheckedStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkCommonForEachStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkContinueStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkDoStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkEmptyStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkExpressionStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkFixedStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkForEachStatementSyntax:
                        type = Types.NodeKind.ndkCommonForEachStatementSyntax;
                        break;
                    case Types.NodeKind.ndkForEachVariableStatementSyntax:
                        type = Types.NodeKind.ndkCommonForEachStatementSyntax;
                        break;
                    case Types.NodeKind.ndkForStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkGotoStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkIfStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkLabeledStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkLocalDeclarationStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkLocalFunctionStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkLockStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkReturnStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkStatementSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkSwitchStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkThrowStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkTryStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkUnsafeStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkUsingStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkWhileStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkYieldStatementSyntax:
                        type = Types.NodeKind.ndkStatementSyntax;
                        break;
                    case Types.NodeKind.ndkAccessorDeclarationSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkAccessorListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkAnonymousObjectMemberDeclaratorSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkArgumentListSyntax:
                        type = Types.NodeKind.ndkBaseArgumentListSyntax;
                        break;
                    case Types.NodeKind.ndkArgumentSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkArrayRankSpecifierSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkArrowExpressionClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkAttributeArgumentListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkAttributeArgumentSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkAttributeListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkAttributeSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkAttributeTargetSpecifierSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkBaseArgumentListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkBaseCrefParameterListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkBaseFieldDeclarationSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkBaseListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkBaseMethodDeclarationSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkBaseParameterListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkBasePropertyDeclarationSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkBaseTypeDeclarationSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkBaseTypeSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkBracketedArgumentListSyntax:
                        type = Types.NodeKind.ndkBaseArgumentListSyntax;
                        break;
                    case Types.NodeKind.ndkBracketedParameterListSyntax:
                        type = Types.NodeKind.ndkBaseParameterListSyntax;
                        break;
                    case Types.NodeKind.ndkCasePatternSwitchLabelSyntax:
                        type = Types.NodeKind.ndkSwitchLabelSyntax;
                        break;
                    case Types.NodeKind.ndkCaseSwitchLabelSyntax:
                        type = Types.NodeKind.ndkSwitchLabelSyntax;
                        break;
                    case Types.NodeKind.ndkCatchClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkCatchDeclarationSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkCatchFilterClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkClassDeclarationSyntax:
                        type = Types.NodeKind.ndkTypeDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkClassOrStructConstraintSyntax:
                        type = Types.NodeKind.ndkTypeParameterConstraintSyntax;
                        break;
                    case Types.NodeKind.ndkCompilationUnitSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkConstantPatternSyntax:
                        type = Types.NodeKind.ndkPatternSyntax;
                        break;
                    case Types.NodeKind.ndkConstructorConstraintSyntax:
                        type = Types.NodeKind.ndkTypeParameterConstraintSyntax;
                        break;
                    case Types.NodeKind.ndkConstructorDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseMethodDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkConstructorInitializerSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkConversionOperatorDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseMethodDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkConversionOperatorMemberCrefSyntax:
                        type = Types.NodeKind.ndkMemberCrefSyntax;
                        break;
                    case Types.NodeKind.ndkCrefBracketedParameterListSyntax:
                        type = Types.NodeKind.ndkBaseCrefParameterListSyntax;
                        break;
                    case Types.NodeKind.ndkCrefParameterListSyntax:
                        type = Types.NodeKind.ndkBaseCrefParameterListSyntax;
                        break;
                    case Types.NodeKind.ndkCrefParameterSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkCrefSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkDeclarationPatternSyntax:
                        type = Types.NodeKind.ndkPatternSyntax;
                        break;
                    case Types.NodeKind.ndkDefaultSwitchLabelSyntax:
                        type = Types.NodeKind.ndkSwitchLabelSyntax;
                        break;
                    case Types.NodeKind.ndkDelegateDeclarationSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkDestructorDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseMethodDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkDiscardDesignationSyntax:
                        type = Types.NodeKind.ndkVariableDesignationSyntax;
                        break;
                    case Types.NodeKind.ndkDiscardPatternSyntax:
                        type = Types.NodeKind.ndkPatternSyntax;
                        break;
                    case Types.NodeKind.ndkElseClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkEnumDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseTypeDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkEnumMemberDeclarationSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkEqualsValueClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkEventDeclarationSyntax:
                        type = Types.NodeKind.ndkBasePropertyDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkEventFieldDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseFieldDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkExplicitInterfaceSpecifierSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkExternAliasDirectiveSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkFieldDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseFieldDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkFinallyClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkFromClauseSyntax:
                        type = Types.NodeKind.ndkQueryClauseSyntax;
                        break;
                    case Types.NodeKind.ndkGlobalStatementSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkGroupClauseSyntax:
                        type = Types.NodeKind.ndkSelectOrGroupClauseSyntax;
                        break;
                    case Types.NodeKind.ndkIncompleteMemberSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkIndexerDeclarationSyntax:
                        type = Types.NodeKind.ndkBasePropertyDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkIndexerMemberCrefSyntax:
                        type = Types.NodeKind.ndkMemberCrefSyntax;
                        break;
                    case Types.NodeKind.ndkInterfaceDeclarationSyntax:
                        type = Types.NodeKind.ndkTypeDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkInterpolatedStringContentSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkInterpolatedStringTextSyntax:
                        type = Types.NodeKind.ndkInterpolatedStringContentSyntax;
                        break;
                    case Types.NodeKind.ndkInterpolationAlignmentClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkInterpolationFormatClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkInterpolationSyntax:
                        type = Types.NodeKind.ndkInterpolatedStringContentSyntax;
                        break;
                    case Types.NodeKind.ndkJoinClauseSyntax:
                        type = Types.NodeKind.ndkQueryClauseSyntax;
                        break;
                    case Types.NodeKind.ndkJoinIntoClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkLetClauseSyntax:
                        type = Types.NodeKind.ndkQueryClauseSyntax;
                        break;
                    case Types.NodeKind.ndkMemberCrefSyntax:
                        type = Types.NodeKind.ndkCrefSyntax;
                        break;
                    case Types.NodeKind.ndkMemberDeclarationSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkMethodDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseMethodDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkNameColonSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkNameEqualsSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkNameMemberCrefSyntax:
                        type = Types.NodeKind.ndkMemberCrefSyntax;
                        break;
                    case Types.NodeKind.ndkNamespaceDeclarationSyntax:
                        type = Types.NodeKind.ndkMemberDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkOperatorDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseMethodDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkOperatorMemberCrefSyntax:
                        type = Types.NodeKind.ndkMemberCrefSyntax;
                        break;
                    case Types.NodeKind.ndkOrderByClauseSyntax:
                        type = Types.NodeKind.ndkQueryClauseSyntax;
                        break;
                    case Types.NodeKind.ndkOrderingSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkParameterListSyntax:
                        type = Types.NodeKind.ndkBaseParameterListSyntax;
                        break;
                    case Types.NodeKind.ndkParameterSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkParenthesizedVariableDesignationSyntax:
                        type = Types.NodeKind.ndkVariableDesignationSyntax;
                        break;
                    case Types.NodeKind.ndkPatternSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkPositionalPatternClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkPropertyDeclarationSyntax:
                        type = Types.NodeKind.ndkBasePropertyDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkPropertyPatternClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkQualifiedCrefSyntax:
                        type = Types.NodeKind.ndkCrefSyntax;
                        break;
                    case Types.NodeKind.ndkQueryBodySyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkQueryClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkQueryContinuationSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkRecursivePatternSyntax:
                        type = Types.NodeKind.ndkPatternSyntax;
                        break;
                    case Types.NodeKind.ndkSelectClauseSyntax:
                        type = Types.NodeKind.ndkSelectOrGroupClauseSyntax;
                        break;
                    case Types.NodeKind.ndkSelectOrGroupClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkSimpleBaseTypeSyntax:
                        type = Types.NodeKind.ndkBaseTypeSyntax;
                        break;
                    case Types.NodeKind.ndkSingleVariableDesignationSyntax:
                        type = Types.NodeKind.ndkVariableDesignationSyntax;
                        break;
                    case Types.NodeKind.ndkStructDeclarationSyntax:
                        type = Types.NodeKind.ndkTypeDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkSubpatternSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkSwitchExpressionArmSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkSwitchLabelSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkSwitchSectionSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkSyntaxToken:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkTupleElementSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkTypeArgumentListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkTypeConstraintSyntax:
                        type = Types.NodeKind.ndkTypeParameterConstraintSyntax;
                        break;
                    case Types.NodeKind.ndkTypeCrefSyntax:
                        type = Types.NodeKind.ndkCrefSyntax;
                        break;
                    case Types.NodeKind.ndkTypeDeclarationSyntax:
                        type = Types.NodeKind.ndkBaseTypeDeclarationSyntax;
                        break;
                    case Types.NodeKind.ndkTypeParameterConstraintClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkTypeParameterConstraintSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkTypeParameterListSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkTypeParameterSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkUsingDirectiveSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkVarPatternSyntax:
                        type = Types.NodeKind.ndkPatternSyntax;
                        break;
                    case Types.NodeKind.ndkVariableDeclarationSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkVariableDeclaratorSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkVariableDesignationSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkWhenClauseSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkWhereClauseSyntax:
                        type = Types.NodeKind.ndkQueryClauseSyntax;
                        break;
                    case Types.NodeKind.ndkXmlAttributeSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkXmlCDataSectionSyntax:
                        type = Types.NodeKind.ndkXmlNodeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlCommentSyntax:
                        type = Types.NodeKind.ndkXmlNodeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlCrefAttributeSyntax:
                        type = Types.NodeKind.ndkXmlAttributeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlElementEndTagSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkXmlElementStartTagSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkXmlElementSyntax:
                        type = Types.NodeKind.ndkXmlNodeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlEmptyElementSyntax:
                        type = Types.NodeKind.ndkXmlNodeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlNameAttributeSyntax:
                        type = Types.NodeKind.ndkXmlAttributeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlNameSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkXmlNodeSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkXmlPrefixSyntax:
                        type = Types.NodeKind.ndkPositioned;
                        break;
                    case Types.NodeKind.ndkXmlProcessingInstructionSyntax:
                        type = Types.NodeKind.ndkXmlNodeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlTextAttributeSyntax:
                        type = Types.NodeKind.ndkXmlAttributeSyntax;
                        break;
                    case Types.NodeKind.ndkXmlTextSyntax:
                        type = Types.NodeKind.ndkXmlNodeSyntax;
                        break;
                }
            }

            return true;
        }

        /// <summary>
        /// Decides whether the node is compiste or not.
        /// </summary>
        /// <param name="node">[in] The node which is being examined.</param>
        /// <returns>Returns true if the node is composite.</returns>
        public static bool getIsComposite(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            return !getIsNotComposite(node);
        }

        /// <summary>
        /// Decides whether the node is compiste or not.
        /// </summary>
        /// <param name="node">[in] The node which is being examined.</param>
        /// <returns>Returns true if the node is not composite.</returns>
        public static bool getIsNotComposite(Columbus.Csharp.Asg.Nodes.Base.Base node) {
            Types.NodeKind ndk = node.NodeKind;
            return
                ndk == Types.NodeKind.ndkBase ||
                ndk == Types.NodeKind.ndkPositioned ||
                ndk == Types.NodeKind.ndkExpressionSyntax ||
                ndk == Types.NodeKind.ndkInstanceExpressionSyntax ||
                ndk == Types.NodeKind.ndkBaseExpressionSyntax ||
                ndk == Types.NodeKind.ndkThisExpressionSyntax ||
                ndk == Types.NodeKind.ndkLiteralExpressionSyntax ||
                ndk == Types.NodeKind.ndkOmittedArraySizeExpressionSyntax ||
                ndk == Types.NodeKind.ndkTypeSyntax ||
                ndk == Types.NodeKind.ndkNameSyntax ||
                ndk == Types.NodeKind.ndkSimpleNameSyntax ||
                ndk == Types.NodeKind.ndkIdentifierNameSyntax ||
                ndk == Types.NodeKind.ndkOmittedTypeArgumentSyntax ||
                ndk == Types.NodeKind.ndkPredefinedTypeSyntax ||
                ndk == Types.NodeKind.ndkAttributeTargetSpecifierSyntax ||
                ndk == Types.NodeKind.ndkCrefSyntax ||
                ndk == Types.NodeKind.ndkMemberCrefSyntax ||
                ndk == Types.NodeKind.ndkExternAliasDirectiveSyntax ||
                ndk == Types.NodeKind.ndkInterpolatedStringContentSyntax ||
                ndk == Types.NodeKind.ndkInterpolatedStringTextSyntax ||
                ndk == Types.NodeKind.ndkInterpolationFormatClauseSyntax ||
                ndk == Types.NodeKind.ndkJoinIntoClauseSyntax ||
                ndk == Types.NodeKind.ndkMemberDeclarationSyntax ||
                ndk == Types.NodeKind.ndkPatternSyntax ||
                ndk == Types.NodeKind.ndkDiscardPatternSyntax ||
                ndk == Types.NodeKind.ndkQueryClauseSyntax ||
                ndk == Types.NodeKind.ndkSelectOrGroupClauseSyntax ||
                ndk == Types.NodeKind.ndkSwitchLabelSyntax ||
                ndk == Types.NodeKind.ndkDefaultSwitchLabelSyntax ||
                ndk == Types.NodeKind.ndkSyntaxToken ||
                ndk == Types.NodeKind.ndkTypeParameterConstraintSyntax ||
                ndk == Types.NodeKind.ndkClassOrStructConstraintSyntax ||
                ndk == Types.NodeKind.ndkConstructorConstraintSyntax ||
                ndk == Types.NodeKind.ndkVariableDesignationSyntax ||
                ndk == Types.NodeKind.ndkDiscardDesignationSyntax ||
                ndk == Types.NodeKind.ndkSingleVariableDesignationSyntax ||
                ndk == Types.NodeKind.ndkXmlNodeSyntax ||
                ndk == Types.NodeKind.ndkXmlCDataSectionSyntax ||
                ndk == Types.NodeKind.ndkXmlCommentSyntax ||
                ndk == Types.NodeKind.ndkXmlTextSyntax ||
                ndk == Types.NodeKind.ndkXmlPrefixSyntax;
        }

        /// <summary>
        /// Returns true if the node exists and is not filtered out.
        /// </summary>
        /// <param name="id">[in] The examined node ID.</param>
        /// <returns>True if the node exists and is not filtered out.</returns>
        public static bool getIsValid(uint id) {
            return id > 1;
        }

    }

}
