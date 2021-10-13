using Microsoft.CodeAnalysis.CSharp;
using System.Collections.Generic;

namespace Columbus.CSAN.Metrics.Complexity
{
    internal sealed class Operands
    {
        public static readonly IEnumerable<SyntaxKind> All = new[]
        {
            SyntaxKind.IdentifierToken,
            SyntaxKind.StringLiteralToken,
            SyntaxKind.NumericLiteralToken,
            SyntaxKind.CharacterLiteralToken,
            SyntaxKind.InterpolatedStringStartToken,         // $"
            //SyntaxKind.InterpolatedStringEndToken,
            SyntaxKind.InterpolatedVerbatimStringStartToken //$@"
        };
    }
}