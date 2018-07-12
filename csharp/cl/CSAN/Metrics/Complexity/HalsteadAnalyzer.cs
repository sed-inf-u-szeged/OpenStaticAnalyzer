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
using System.Collections.Generic;
using System.Linq;
using Columbus.CSAN.Commons;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN.Metrics.Complexity
{
    internal sealed class HalsteadAnalyzer
    {
        private enum TokenKind
        {
            Operators,
            Operands    
        }

        private enum InnerSyntaxKind : ushort
        {
            ParenToken = 100,
            BraceToken = 101,
            BracketToken = 102
        }

        public HalsteadMetrics Calculate(SyntaxNode syntax)
        {
            var tokens = syntax.DescendantTokens().ToList();
            var operandsDictionary = ParseTokens(tokens, Operands.All, TokenKind.Operands);
            var operatirDictionary = ParseTokens(tokens, Operators.All, TokenKind.Operators);

            MergeTokens(operatirDictionary, (ushort)SyntaxKind.CloseParenToken,
                    (ushort)SyntaxKind.OpenParenToken, (ushort)InnerSyntaxKind.ParenToken);
            MergeTokens(operatirDictionary, (ushort)SyntaxKind.CloseBraceToken,
                    (ushort)SyntaxKind.OpenBraceToken, (ushort)InnerSyntaxKind.BraceToken);
            MergeTokens(operatirDictionary, (ushort)SyntaxKind.CloseBracketToken,
                   (ushort)SyntaxKind.OpenBracketToken, (ushort)InnerSyntaxKind.BracketToken);

            return new HalsteadMetrics(
                distinctOperands: (uint) operandsDictionary.Count,
                distinctOperators: (uint) operatirDictionary.Count,
                totalOperands: (uint) operandsDictionary.Values.Sum(operands => operands.Count),
                totalOperators: (uint) operatirDictionary.Values.Sum(operands => operands.Count)
            );
        }

        private void MergeTokens(IDictionary<ushort, IList<string>> dictionary2,ushort token1,
            ushort token2, ushort newToken)
        {
            IList<string> tokenList2;
            dictionary2.TryGetValue(token2, out tokenList2);
            IList<string> tokenList1;
            dictionary2.TryGetValue(token1, out tokenList1);
            if (tokenList2?.Count > 0 && tokenList1?.Count > 0)
            {
                dictionary2.Remove(token1);
                dictionary2.Remove(token2);
                dictionary2.Add(new KeyValuePair<ushort, IList<string>>(newToken, new List<string>()));
                for (int i = 0; i < tokenList2.Count; i++)
                {
                    dictionary2[newToken].Add(string.Format("{0}{1}", tokenList2[i], tokenList1[i]));
                }
            }
        }


        private IDictionary<ushort, IList<string>> ParseTokens(IEnumerable<SyntaxToken> tokens,
            IEnumerable<SyntaxKind> filter, TokenKind tokenKind)
        {
            IDictionary<ushort, IList<string>> dictionary = new Dictionary<ushort, IList<string>>();
            foreach (var token in tokens)
            {
                var kind = token.Kind();
                kind = IdentifierTokensKindDecision(tokenKind, kind, token);

                if (filter.Any(x => x == kind))
                {
                    IList<string> list;
                    var valueText = token.ValueText;
                    if (!dictionary.TryGetValue((ushort)kind, out list))
                    {
                        dictionary[(ushort)kind] = new List<string>();
                        list = dictionary[(ushort)kind];
                    }

                    list.Add(valueText);
                }
            }

            return dictionary;
        }

        private SyntaxKind IdentifierTokensKindDecision(TokenKind tokenKind, SyntaxKind kind, SyntaxToken token)
        {
            if (kind == SyntaxKind.IdentifierToken)
            {
                int symbols =
                    token.Parent.AncestorsAndSelf()
                        .Select(node =>
                        {
                            MainDeclaration.Instance.RoslynWatch.Start();
                            var symbol = MainDeclaration.Instance.Model.GetSymbolInfo(node).Symbol;
                            MainDeclaration.Instance.RoslynWatch.Stop();
                            return symbol;
                        })
                        .Where(symbol => symbol != null)
                        .OfType<INamedTypeSymbol>()
                        .Count();

                switch (tokenKind)
                {
                    case TokenKind.Operators:
                        if (symbols == 0)
                        {
                            kind = SyntaxKind.None;
                        }
                        break;
                    case TokenKind.Operands:
                        if (symbols > 0)
                        {
                            kind = SyntaxKind.None;
                        }
                        break;
                }
            }
            return kind;
        }
    }
}