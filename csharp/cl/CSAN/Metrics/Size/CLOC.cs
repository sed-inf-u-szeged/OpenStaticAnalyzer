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

using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using System.Linq;

namespace Columbus.CSAN.Metrics.Size
{
    using Extensions;
    using Microsoft.CodeAnalysis.CSharp.Syntax;

    /// <summary>
    /// CLOC metrics for a method is the number of comment lines that belong to the method, 
    /// in which in addition to the comments to be found in the method, the document lines 
    /// that belong to the method are calculated; however, comment or document 
    /// lines of the anonymous or local classes to be found in the method are not.
    /// </summary>
    static class CLOC
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="limScope"></param>
        /// <param name="node"></param>
        public static void SetCLOC(this Scope limScope, SyntaxNode node)
        {
            limScope.CommentLines += (uint)CLOC.SumCommentLines(node);

        }


        /// <summary>
        /// Calculate node comment lines
        /// </summary>
        /// <param name="node"></param>
        /// <returns>Sum of comment lines</returns>
        private static int SumCommentLines(SyntaxNode node)
        {
            int tcloc = 0;
            var list = node.DescendantTrivia().Where(t => t.IsAcceptableCommentKind()).ToList();

            foreach (var trivia in list)
            {
                SyntaxNode localNode = trivia.Token.Parent;
                if (node.IsAcceptableToInsideNode(localNode)) continue;

                FileLinePositionSpan flps = trivia.GetLocation().GetLineSpan();
                switch (trivia.Kind())
                {
                    case SyntaxKind.MultiLineCommentTrivia:
                    case SyntaxKind.SingleLineCommentTrivia:
                    case SyntaxKind.MultiLineDocumentationCommentTrivia:
                        if (localNode.IsParent<BlockSyntax>())
                        {
                            tcloc += flps.EndLinePosition.Line - flps.StartLinePosition.Line + 1;
                        }
                        break;
                    case SyntaxKind.SingleLineDocumentationCommentTrivia:
                        if (localNode.IsParent<BlockSyntax>())
                        {
                            tcloc += flps.EndLinePosition.Line - flps.StartLinePosition.Line;
                        }
                        break;
                }
            }
            return tcloc;
        }

    }
}
