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

using Microsoft.CodeAnalysis.CSharp;
using System.Collections.Generic;

namespace Columbus.CSAN.Metrics.Complexity
{
    internal sealed class Operators
    {
        public static readonly IEnumerable<SyntaxKind> All = new[]
        {
            SyntaxKind.CommaToken,                        // ,
            SyntaxKind.DotToken,                          // .
            SyntaxKind.EqualsToken,                       // =
            SyntaxKind.EqualsEqualsToken,                 // ==
            SyntaxKind.SemicolonToken,                    // ;
            SyntaxKind.PlusToken,                         // +
            SyntaxKind.PlusPlusToken,                     // ++
            SyntaxKind.PlusEqualsToken,                   // +=
            SyntaxKind.MinusToken,                        // -
            SyntaxKind.MinusMinusToken,                   // --
            SyntaxKind.MinusEqualsToken,                  // -=
            SyntaxKind.AsteriskToken,                     // *
            SyntaxKind.AsteriskEqualsToken,               // *=
            SyntaxKind.SlashToken,                        // /
            SyntaxKind.SlashEqualsToken,                  // /=
            SyntaxKind.PercentToken,                      // %
            SyntaxKind.PercentEqualsToken,                // %=
            SyntaxKind.AmpersandToken,                    // &
            SyntaxKind.AmpersandAmpersandToken,           // &&
            SyntaxKind.AmpersandEqualsToken,              // &=
            SyntaxKind.BarToken,                          // |
            SyntaxKind.BarBarToken,                       // ||
            SyntaxKind.BarEqualsToken,                    // |=
            SyntaxKind.CaretToken,                        // ^
            SyntaxKind.CaretEqualsToken,                  // ^=
            SyntaxKind.ColonToken,                        // :
            SyntaxKind.ColonColonToken,                   // ::
            SyntaxKind.TildeToken,                        // ~
            SyntaxKind.QuestionToken,                     // ?
            SyntaxKind.QuestionQuestionToken,             // ??
            SyntaxKind.ExclamationToken,                  // !
            SyntaxKind.ExclamationEqualsToken,            // !=
            SyntaxKind.GreaterThanToken,                  // >
            SyntaxKind.GreaterThanEqualsToken,            // >=
            SyntaxKind.LessThanToken,                     // <
            SyntaxKind.LessThanEqualsToken,               // <=
            SyntaxKind.MinusGreaterThanToken,             // ->
            SyntaxKind.EqualsGreaterThanToken,            // =>
            SyntaxKind.LeftShiftExpression,               // <<
            SyntaxKind.LessThanLessThanEqualsToken,       // <<=
            SyntaxKind.RightShiftExpression,              // >>
            SyntaxKind.GreaterThanGreaterThanEqualsToken, // >>=
            SyntaxKind.OpenParenToken,                    // (
            SyntaxKind.CloseParenToken,                   // )
            SyntaxKind.OpenBraceToken,                    // {
            SyntaxKind.CloseBraceToken,                   // }
            SyntaxKind.OpenBracketToken,                  // [
            SyntaxKind.CloseBracketToken,                 // ]
            SyntaxKind.HashToken,                         // #
            SyntaxKind.DollarToken,                       // $
            SyntaxKind.OmittedArraySizeExpressionToken,   //[,]
            SyntaxKind.OmittedTypeArgumentToken,          //<T>

            SyntaxKind.IdentifierToken,
            
            SyntaxKind.AddKeyword,
            SyntaxKind.AliasKeyword,
            SyntaxKind.AscendingKeyword,
            SyntaxKind.AsKeyword,
            SyntaxKind.AsyncKeyword,
            SyntaxKind.AwaitKeyword,
            SyntaxKind.BaseKeyword,
            SyntaxKind.BoolKeyword,
            SyntaxKind.BreakKeyword,
            SyntaxKind.ByKeyword,
            SyntaxKind.ByteKeyword,
            SyntaxKind.CaseKeyword,
            SyntaxKind.CatchKeyword,
            SyntaxKind.CharKeyword,
            SyntaxKind.CheckedKeyword,
            SyntaxKind.ChecksumKeyword,
            SyntaxKind.ClassKeyword,
            SyntaxKind.ConstKeyword,
            SyntaxKind.ContinueKeyword,
            SyntaxKind.DecimalKeyword,
            SyntaxKind.DefaultKeyword,
            SyntaxKind.DefineKeyword,
            SyntaxKind.DelegateKeyword,
            SyntaxKind.DescendingKeyword,
            SyntaxKind.DisableKeyword,
            SyntaxKind.DoKeyword,
            SyntaxKind.DoubleKeyword,
            SyntaxKind.ElifKeyword,
            SyntaxKind.ElseKeyword,
            SyntaxKind.EndIfKeyword,
            SyntaxKind.EndRegionKeyword,
            SyntaxKind.EnumKeyword,
            SyntaxKind.EqualsKeyword,
            SyntaxKind.ErrorKeyword,
            SyntaxKind.EventKeyword,
            SyntaxKind.ExplicitKeyword,
            SyntaxKind.ExternKeyword,
            SyntaxKind.FalseKeyword,
            SyntaxKind.FieldKeyword,
            SyntaxKind.FinallyKeyword,
            SyntaxKind.FixedKeyword,
            SyntaxKind.FloatKeyword,
            SyntaxKind.ForEachKeyword,
            SyntaxKind.ForKeyword,
            SyntaxKind.FromKeyword,
            SyntaxKind.GetKeyword,
            SyntaxKind.GlobalKeyword,
            SyntaxKind.GotoKeyword,
            SyntaxKind.GroupKeyword,
            SyntaxKind.HiddenKeyword,
            SyntaxKind.IfKeyword,
            SyntaxKind.ImplicitKeyword,
            SyntaxKind.InKeyword,
            SyntaxKind.InterfaceKeyword,
            SyntaxKind.InternalKeyword,
            SyntaxKind.IntKeyword,
            SyntaxKind.IntoKeyword,
            SyntaxKind.IsKeyword,
            SyntaxKind.JoinKeyword,
            SyntaxKind.LetKeyword,
            SyntaxKind.LineKeyword,
            SyntaxKind.LockKeyword,
            SyntaxKind.LongKeyword,
            SyntaxKind.MakeRefKeyword,
            SyntaxKind.MethodKeyword,
            SyntaxKind.ModuleKeyword,
            SyntaxKind.NamespaceKeyword,
            SyntaxKind.NullKeyword,
            SyntaxKind.ObjectKeyword,
            SyntaxKind.OnKeyword,
            SyntaxKind.OperatorKeyword,
            SyntaxKind.OrderByKeyword,
            SyntaxKind.OutKeyword,
            SyntaxKind.OverrideKeyword,
            SyntaxKind.ParamKeyword,
            SyntaxKind.ParamsKeyword,
            SyntaxKind.PartialKeyword,
            SyntaxKind.PragmaKeyword,
            SyntaxKind.PrivateKeyword,
            SyntaxKind.PropertyKeyword,
            SyntaxKind.ProtectedKeyword,
            SyntaxKind.PublicKeyword,
            SyntaxKind.ReadOnlyKeyword,
            SyntaxKind.ReferenceKeyword,
            SyntaxKind.RefKeyword,
            SyntaxKind.RefTypeKeyword,
            SyntaxKind.RefValueKeyword,
            SyntaxKind.RegionKeyword,
            SyntaxKind.RemoveKeyword,
            SyntaxKind.RestoreKeyword,
            SyntaxKind.ReturnKeyword,
            SyntaxKind.SByteKeyword,
            SyntaxKind.SealedKeyword,
            SyntaxKind.SelectKeyword,
            SyntaxKind.SetKeyword,
            SyntaxKind.ShortKeyword,
            SyntaxKind.SizeOfKeyword,
            SyntaxKind.StackAllocKeyword,
            SyntaxKind.StaticKeyword,
            SyntaxKind.StringKeyword,
            SyntaxKind.StructKeyword,
            SyntaxKind.SwitchKeyword,
            SyntaxKind.ThisKeyword,
            SyntaxKind.TrueKeyword,
            SyntaxKind.TryKeyword,
            SyntaxKind.TypeKeyword,
            SyntaxKind.TypeOfKeyword,
            SyntaxKind.TypeVarKeyword,
            SyntaxKind.UIntKeyword,
            SyntaxKind.ULongKeyword,
            SyntaxKind.UncheckedKeyword,
            SyntaxKind.UndefKeyword,
            SyntaxKind.UnsafeKeyword,
            SyntaxKind.UShortKeyword,
            SyntaxKind.UsingKeyword,
            SyntaxKind.VirtualKeyword,
            SyntaxKind.VoidKeyword,
            SyntaxKind.VolatileKeyword,
            SyntaxKind.WarningKeyword,
            SyntaxKind.WhereKeyword,
            SyntaxKind.WhileKeyword,
            SyntaxKind.YieldKeyword
        };
    }
}