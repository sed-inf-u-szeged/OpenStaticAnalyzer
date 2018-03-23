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

using Microsoft.CodeAnalysis;

namespace Columbus.CSAN.Extensions
{
    using Commons;

    using Lim.Asg;
    using Lim.Asg.Nodes.Physical;

    static class LocationExtension
    {
        /// <summary>
        /// Create File node from Location if it is possible
        /// </summary>
        /// <param name="roslynNode"></param>
        /// <returns>LIM File node</returns>
        public static File CreateFile(this Location roslynNode)
        {
            if (MainDeclaration.Instance.HardFilter != null)
            {
                try
                {

                    if (!MainDeclaration.Instance.HardFilter.IsNecessaryToAnalyse(roslynNode.SourceTree.FilePath))
                    {
                        return null;
                    }
                }
                catch (System.Exception){}
            }

            File file = MainDeclaration.Instance.LimFactory.createFile(Commons.Common.ProcessPath(roslynNode.SourceTree.FilePath));
            uint key = MainDeclaration.Instance.LimFactory.StringTable.set(Commons.Common.ProcessPath(roslynNode.SourceTree.FilePath));
            if (!MainDeclaration.Instance.FileMap.ContainsKey(key))
            {
                MainDeclaration.Instance.FileMap.Add(key, file.Id);
            }

            
            file.LOC = (uint)roslynNode.GetMappedLineSpan().EndLinePosition.Line + 1;

            return file;
        }

        /// <summary>
        /// Calculate Comment Lines for Comment node
        /// </summary>
        /// <param name="roslynNode"></param>
        public static void CalculateFileLevelCommentLines(this Location roslynNode)
        {
            File file = roslynNode.CreateFile();
            var isContainedInIterator = MainDeclaration.Instance.LimFactory.GetReverseEdges().constIteratorBegin(file.Id, Types.EdgeKind.edkMember_IsContainedIn);
            while (isContainedInIterator.getValue() != null)
            {
                var isContainedIn = isContainedInIterator.getValue();
                if (Lim.Asg.Common.getIsScope(isContainedIn))
                {
                    file.CLOC += ((Lim.Asg.Nodes.Logical.Scope)isContainedIn).CommentLines;
                }
                isContainedInIterator = isContainedInIterator.getNext();
            }
        }

        /// <summary>
        /// Calculate Number of branches for Comment node
        /// </summary>
        /// <param name="roslynNode"></param>
        public static void CalculateFileLevelNumberOfBranches(this Location roslynNode)
        {
            File file = roslynNode.CreateFile();
            var isContainedInIterator = MainDeclaration.Instance.LimFactory.GetReverseEdges().constIteratorBegin(file.Id, Types.EdgeKind.edkMember_IsContainedIn);
            while (isContainedInIterator.getValue() != null)
            {
                var isContainedIn = isContainedInIterator.getValue();
                if (Lim.Asg.Common.getIsMethod(isContainedIn))
                {
                    file.NumberOfBranches += ((Lim.Asg.Nodes.Logical.Method)isContainedIn).NumberOfBranches;
                }
                isContainedInIterator = isContainedInIterator.getNext();
            }

            
        }

    }
}