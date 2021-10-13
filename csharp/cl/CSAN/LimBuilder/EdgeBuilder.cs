using Columbus.CSAN.Contexts;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Nodes.Physical;
using Microsoft.CodeAnalysis;

namespace Columbus.CSAN.LimBuilder
{
    class EdgeBuilder
    {
        private readonly FileContext fileContext;
        private readonly SymbolConverter symbolConverter;

        public EdgeBuilder(FileContext fileContext)
        {
            this.fileContext = fileContext;
            symbolConverter = new SymbolConverter(fileContext);
        }

        /// <summary>
        /// Create association edge for the File node
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="roslynNode"></param>
        public void AddIsContainedInEdge(Member limNode, SyntaxNode roslynNode)
        {
            SourcePosition limPos = new SourcePosition();
            FileLinePositionSpan flps = roslynNode.GetLocation().GetLineSpan();
            limPos.Line = (uint)flps.StartLinePosition.Line + 1;
            limPos.Column = (uint)flps.StartLinePosition.Character + 1;
            limPos.EndLine = (uint)flps.EndLinePosition.Line + 1;
            limPos.EndColumn = (uint)flps.EndLinePosition.Character + 1;
            limPos.RealizationLevel = Types.RealizationLevel.relDefines;

            Location roslynLocation = roslynNode.GetLocation();

            AddIsContainedInEdge(limNode, limPos, roslynLocation);
        }

        /// <summary>
        /// Create association edge for the File node
        /// </summary>
        /// <param name="limNode"></param>
        /// <param name="limPos"></param>
        /// <param name="roslynLocation">Used to determine the source file only</param>
        public void AddIsContainedInEdge(Member limNode, SourcePosition limPos, Location roslynLocation)
        {
            string filePath = fileContext.ProjectContext.SolutionContext.ProcessPath(roslynLocation.SourceTree.FilePath);
            if (string.IsNullOrEmpty(filePath))
                return;

            File file = symbolConverter.CreateFile(roslynLocation);
            if (file == null)
                return;

            bool found = false;
            ListIteratorAssocSourcePosition<File> sourcePositionInFileBeginIt = limNode.IsContainedInListIteratorAssocBegin;

            for (File fileIt = sourcePositionInFileBeginIt.getValue(); fileIt != null; fileIt = sourcePositionInFileBeginIt.getNext().getValue())
            {
                SourcePosition oldSp = sourcePositionInFileBeginIt.getAssocItem();

                if (fileIt.Id != file.Id ||
                    oldSp.Line != limPos.Line ||
                    oldSp.Column != limPos.Column ||
                    oldSp.EndLine != limPos.EndLine ||
                    oldSp.EndColumn != limPos.EndColumn)
                    continue;

                found = true;
                break;
            }

            if (!found)
                limNode.addIsContainedIn(file, limPos);
        }
    }
}
