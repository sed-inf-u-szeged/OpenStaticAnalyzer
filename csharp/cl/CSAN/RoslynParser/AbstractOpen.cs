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

using System;
using System.Collections.Generic;
using SysIO = System.IO;
using System.Threading.Tasks;
using Microsoft.CodeAnalysis.MSBuild;

namespace Columbus.CSAN.RoslynParser
{
    enum Type { None, File, Project, Solution }

    abstract class AbstractOpen : IDisposable
    {
        protected string filePath;
        protected MSBuildWorkspace msbuildWorkspace;
        private static AbstractOpen instance;
        private string ext;

        public string Path
        {
            get
            {
                var fullPath = SysIO.Path.GetFullPath(filePath);
                return string.IsNullOrWhiteSpace(fullPath) ? string.Empty : fullPath/*.ToLowerInvariant()*/;
            }
        }

        protected AbstractOpen(string path, string configuration, string platform)
        {
            if (string.IsNullOrEmpty(path))
            {
                throw new ArgumentNullException("path");
            }

            filePath = path;
            ext = SysIO.Path.GetExtension(path);
            msbuildWorkspace = MSBuildWorkspace.Create(new Dictionary<string, string> {
                { "CheckForSystemRuntimeDependency", "true" },
                { "DesignTimeBuild",                 "true" },
                { "BuildingInsideVisualStudio",      "true" },
                { "Configuration",                   configuration },
                { "Platform",                        platform }
            });
            msbuildWorkspace.SkipUnrecognizedProjects = true;
            msbuildWorkspace.LoadMetadataForReferencedProjects = true;
            TopologicallySortedProjectDependencies = new List<Microsoft.CodeAnalysis.Project>();

        }

        /// <summary>
        /// Factory method to create the appropriate instance for the path given (.cs/.csproj/.xproj/.sln)
        /// </summary>
        /// <param name="path">Path of the source, project or solution file</param>
        public static AbstractOpen CreateInstance(string path, string configuration, string platform)
        {
            string ext = SysIO.Path.GetExtension(path);
            switch (ext)
            {
                case ".sln":
                    instance = new SolutionOpen(path, configuration, platform);
                    break;
                case ".csproj":
                case ".xproj":
                    instance = new ProjectOpen(path, configuration, platform);
                    break;
                case ".cs":
                    instance = new FileOpen(path, configuration, platform);
                    break;
                default:
                    throw new Exception("Invalid file type!");
            }
            return instance;
        }

        protected async Task<Microsoft.CodeAnalysis.Emit.EmitResult> EmitProject(Microsoft.CodeAnalysis.Project project)
        {
            var compilation = await project.GetCompilationAsync();
            string pdbPath = SysIO.Path.Combine(SysIO.Path.GetDirectoryName(project.OutputFilePath), SysIO.Path.GetFileNameWithoutExtension(project.OutputFilePath) + ".pdb");

            using (var fileStream = SysIO.File.Create(project.OutputFilePath))
            using (var pdbStream = SysIO.File.Create(pdbPath))
                return compilation.Emit(fileStream, pdbStream);
        }

        public Microsoft.CodeAnalysis.Solution Solution { get; protected set; }

        public List<Microsoft.CodeAnalysis.Project> TopologicallySortedProjectDependencies { get; protected set; }

        public abstract Task<bool> BuildSoulution();

        public abstract void Parse();

        #region IDisposable Support
        private bool disposedValue = false; // To detect redundant calls

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    msbuildWorkspace.CloseSolution();
                }

                disposedValue = true;
            }
        }

        // override a finalizer only if Dispose(bool disposing) above has code to free unmanaged resources.
        ~AbstractOpen()
        {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(false);
        }

        // This code added to correctly implement the disposable pattern.
        public void Dispose()
        {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

    }
}
