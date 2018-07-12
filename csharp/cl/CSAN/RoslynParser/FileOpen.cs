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

using System.Collections.Generic;
using System.Text;

namespace Columbus.CSAN.RoslynParser
{
    using System.IO;
    using Microsoft.CodeAnalysis;
    using Microsoft.CodeAnalysis.Text;
    using Microsoft.CodeAnalysis.MSBuild;
    using Microsoft.CodeAnalysis.CSharp;

    class FileOpen : AbstractOpen
    {

        public FileOpen(string path, string config, string platform) : base(path, config, platform) { }

        public override void Parse()
        {
            var projectId = ProjectId.CreateNewId();
            var docId = DocumentId.CreateNewId(projectId);
            Solution = msbuildWorkspace.CurrentSolution;
            string fileName = System.IO.Path.GetFileNameWithoutExtension(Path);

            Solution = Solution.AddProject(
                projectId,
                fileName,
                fileName + ".dll",
                LanguageNames.CSharp
            );

            Solution = Solution.AddDocument(
                docId,
                fileName, SourceText.
                From(File.ReadAllText(Path), new UTF8Encoding(false)),
                new[] { System.IO.Path.GetDirectoryName(Path) },
                Path
            );

            Solution = Solution.WithProjectFilePath(projectId, System.IO.Path.GetDirectoryName(Path));

            Solution = Solution.WithProjectCompilationOptions(projectId,
                new CSharpCompilationOptions(
                    OutputKind.DynamicallyLinkedLibrary,
                    optimizationLevel: OptimizationLevel.Debug,
                    platform: Platform.X64
                )
            );

            Solution = Solution.WithProjectOutputFilePath(
                projectId,
                System.IO.Path.Combine(System.IO.Path.GetDirectoryName(Path), fileName + ".dll")
            );

            Solution = Solution.AddMetadataReferences(projectId, Util.GetGlobalReferences());
            TopologicallySortedProjectDependencies.AddRange(Solution.Projects);
        }

        public override async System.Threading.Tasks.Task<bool> BuildSoulution()
        {
            var result = await EmitProject(TopologicallySortedProjectDependencies[0]);
            return result.Success;
        }
    }
}