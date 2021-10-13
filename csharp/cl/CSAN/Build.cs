using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Columbus.CSAN.Contexts;
using Columbus.CSAN.Diagnostics;
using Columbus.CSAN.LimBuilder;
using Columbus.CSAN.Metrics;
using Columbus.CSAN.RoslynParser;
using Columbus.CSAN.Utils;
using Columbus.Csharp.Asg.Algorithms;
using Columbus.Csharp.Asg.Visitors;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;
using Columbus.Lim.Asg.Visitors;
using Microsoft.CodeAnalysis;

namespace Columbus.CSAN
{
    static class Build
    {
        /// <summary>
        /// List of cssi/lcssi files path.
        /// </summary>
        private static readonly List<string> CsharpAsgFiles = new List<string>();

        /// <summary>
        /// UTF8 encoder to the XML file dump without BOM.
        /// </summary>
        private static readonly UTF8Encoding Utf8Encoding = new UTF8Encoding(false);

        private const int RestoreTimeoutMs = 10 * 60 * 1000; // 10min

        /// <summary>
        /// C# and LIM ASG building entry point.
        /// </summary>
        /// <param name="abstractOpen">Input project</param>
        /// <param name="optionBag">Commandline options</param>
        /// <param name="watchBag">Stopwatches</param>
        /// <param name="buildTask">If the solution is being built to binaries, the task representing the building process, null otherwise.</param>
        /// <param name="statistic">Statistics</param>
        public static void Start(AbstractOpen abstractOpen, OptionBag optionBag, WatchBag watchBag, Task buildTask, Statistic statistic)
        {
            var asgBuildingWatch = Stopwatch.StartNew();

            WriteMsg.WriteLine("Starting analysis...");

            SolutionContext solutionContext = new SolutionContext(abstractOpen.Solution, optionBag, watchBag);
            DiagnosticsExporter diagnosticsExporter = new DiagnosticsExporter(solutionContext);
            ICollection<Task> diagnosticsExporterTasks = new LinkedList<Task>();

            int i = 0;
            foreach (Project project in abstractOpen.TopologicallySortedProjectDependencies)
            {
                i++;
                WriteMsg.Write($"    ({i}/{abstractOpen.TopologicallySortedProjectDependencies.Count}) ");
                if (!solutionContext.HardFilter.IsNecessaryToAnalyse(project.FilePath))
                {
                    WriteMsg.WriteLine($"Skipping {project.AssemblyName} because it is hard filtered");
                    continue;
                }
                if (!project.HasDocuments)
                {
                    WriteMsg.WriteLine($"Skipping empty project {project.AssemblyName}. This might be caused by an MsBuild loading error.");
                    continue;
                }
                if (project.OutputFilePath == null)
                {
                    WriteMsg.WriteLine($"Skipping project {project.AssemblyName} because its output path is not set. This might be caused by an MsBuild loading error.", WriteMsg.MsgLevel.Warning);
                    continue;
                }

                WriteMsg.Write($"Analyzing {project.AssemblyName}... ");
                ProjectContext projectContext = new ProjectContext(solutionContext, project);

                if (optionBag.RestorePackages)
                    RestorePackages(project);

                if (optionBag.RunAnalyzers)
                    diagnosticsExporterTasks.Add(Task.Run(async () =>
                        await diagnosticsExporter.ExportAnalyzerDiagnosticsAsync(project, Path.Combine(optionBag.AnalyzersOut, Path.GetFileName(project.OutputFilePath + ".xml")))
                    ));

                AnalyseProject(projectContext, optionBag, abstractOpen.CssiExtension, buildTask);
            }

            var lineMetrics = new LineMetrics(solutionContext);
            lineMetrics.Calculate();

            WriteMsg.WriteLine("Analysis finished");
            if (!string.IsNullOrEmpty(optionBag.OutList))
            {
                File.WriteAllLines(optionBag.OutList, CsharpAsgFiles);
            }

            statistic.ASGBuildingTime = asgBuildingWatch.ElapsedSeconds;

            var saveWatch = Stopwatch.StartNew();
            SaveLimAsg(optionBag, solutionContext);
            statistic.SaveTime = saveWatch.ElapsedSeconds;

            buildTask?.Wait();
            diagnosticsExporterTasks.WaitAll();
        }

        /// <summary>
        /// Analyse a Project
        /// </summary>
        /// <param name="projectContext">Context of the project being analysed</param>
        /// <param name="optionBag">Commandline options</param>
        /// <param name="cssiExtension">lcssi or cssi based on the type of analysis</param>
        /// <param name="buildTask">If the solution is being built to binaries, the task representing the building process, null otherwise.</param>
        private static void AnalyseProject(ProjectContext projectContext, OptionBag optionBag, string cssiExtension, Task buildTask)
        {
            Task<IEnumerable<KeyValuePair<WriteMsg.MsgLevel, string>>> fxCopTask = null;
            if (optionBag.RunFxCop)
                fxCopTask = Task.Run(() => StartFxCopAnalysis(projectContext.RoslynProject.OutputFilePath, optionBag.FxCopOut, optionBag.FxCopPath, buildTask));

            var progressDisplay = new WriteMsg.ProgressDisplay(projectContext.RoslynProject.Documents.Count(), true);

            foreach (var document in projectContext.RoslynProject.Documents)
            {
                progressDisplay.AdvanceAndPrint();
                if (!projectContext.SolutionContext.HardFilter.IsNecessaryToAnalyse(document.FilePath)) {
                    WriteMsg.WriteLine($"Skipping {document.FilePath} because it is hard filtered", WriteMsg.MsgLevel.Debug);
                    continue;
                }

                WriteMsg.WriteLine($"Analyzing {document.FilePath}", WriteMsg.MsgLevel.Debug);
                var fileContext = new FileContext(projectContext, document);

                projectContext.SolutionContext.WatchBag.CSSIWatch.Start();
                BuildCsharpAsg(fileContext);
                projectContext.SolutionContext.WatchBag.CSSIWatch.Stop();
                projectContext.SolutionContext.WatchBag.LIMWatch.Start();
                BuildLimAsg(fileContext);
                projectContext.SolutionContext.WatchBag.LIMWatch.Stop();
            }
            WriteMsg.WriteLine();

            SaveCsharpAsg(projectContext, optionBag.Output, optionBag.DumpCsharpml, cssiExtension);

            if (fxCopTask != null)
            {
                foreach (var pair in fxCopTask.Result)
                    WriteMsg.WriteLine("    " + pair.Value, pair.Key);
            }
        }

        /// <summary>
        /// Binary file will be analysed by FxCop.
        /// </summary>
        /// <param name="inputBinary">Binary file location</param>
        /// <param name="resultOutputPath">FxCop result directory</param>
        /// <param name="fxCopPath">FxCopCmd.exe path</param>
        /// <param name="buildTask"></param>
        private static IEnumerable<KeyValuePair<WriteMsg.MsgLevel, string>> StartFxCopAnalysis(string inputBinary, string resultOutputPath, string fxCopPath, Task buildTask)
        {
            var messages = new List<KeyValuePair<WriteMsg.MsgLevel, string>>();
            if (string.IsNullOrEmpty(fxCopPath) || string.IsNullOrEmpty(inputBinary))
                return messages;
            string outputFilename = Path.GetFileNameWithoutExtension(inputBinary) + ".xml";
            string outputDirectory = Path.GetDirectoryName(inputBinary) ?? "/";
            string result = Path.Combine(outputDirectory, outputFilename);

            if (!string.IsNullOrEmpty(resultOutputPath) && resultOutputPath[resultOutputPath.Length - 1] != Path.DirectorySeparatorChar)
                resultOutputPath += Path.DirectorySeparatorChar;

            var startInfo = new ProcessStartInfo
            {
                CreateNoWindow = false,
                UseShellExecute = false,
                FileName = fxCopPath.EndsWith(".exe") ? fxCopPath : fxCopPath + "FxCopCmd.exe",
                WorkingDirectory = fxCopPath.EndsWith(".exe") ? (Path.GetDirectoryName(fxCopPath) ?? "/") : fxCopPath,
                WindowStyle = ProcessWindowStyle.Hidden,
                Arguments = string.Format("/f:\"{0}\" /d:\"{1}\" /r:\"{2}\" /o:\"{3}{4}\" /gac",
                    inputBinary,
                    outputDirectory,
                    (fxCopPath.Contains(".exe") ? Path.GetDirectoryName(fxCopPath) : fxCopPath) + "Rules",
                    resultOutputPath,
                    outputFilename
                ),
                RedirectStandardOutput = true,
                RedirectStandardError = true
            };

            buildTask?.Wait();

            if (!File.Exists(inputBinary))
            {
                messages.Add(new KeyValuePair<WriteMsg.MsgLevel, string>(WriteMsg.MsgLevel.Warning, $"[FxCopAnalysis] {inputBinary} is missing, skipped"));
                return messages;
            }

            messages.Add(new KeyValuePair<WriteMsg.MsgLevel, string>(WriteMsg.MsgLevel.Debug, $"[FxCopAnalysis] Starting FxCop analysis for {inputBinary}..."));
            try
            {
                string output = Path.Combine(resultOutputPath, outputFilename + ".log");

                using (Process exeProcess = new Process())
                using (StreamWriter sw = new StreamWriter(output, false))
                {
                    exeProcess.OutputDataReceived += (sender, e) =>
                    {
                        if (e.Data != null)
                            sw.WriteLine(e.Data);
                    };
                    exeProcess.ErrorDataReceived += (sender, e) =>
                    {
                        if (e.Data != null)
                            sw.WriteLine(e.Data);
                    };
                    exeProcess.StartInfo = startInfo;
                    exeProcess.Start();
                    exeProcess.BeginOutputReadLine();
                    exeProcess.BeginErrorReadLine();
                    exeProcess.WaitForExit();
                }
                messages.Add(new KeyValuePair<WriteMsg.MsgLevel, string>(WriteMsg.MsgLevel.Debug, $"[FxCopAnalysis] FxCop for {Path.GetFileName(inputBinary)} terminated"));
            }
            catch (Exception)
            {
                if (File.Exists(result))
                    File.Delete(result);
                throw;
            }

            return messages;
        }

        private static void RestorePackages(Project project)
        {
            WriteMsg.WriteLine("Restoring packages", WriteMsg.MsgLevel.Debug);
            var info = new ProcessStartInfo
            {
                FileName = "dotnet",
                ArgumentList = {"restore", project.FilePath},
                RedirectStandardOutput = true,
                RedirectStandardError = true,
            };

            try
            {
                using (var restoreProcess = Process.Start(info))
                {
                    if (restoreProcess == null)
                    {
                        WriteMsg.WriteLine($"Could not start package restore for project file {project.FilePath}", WriteMsg.MsgLevel.Warning);
                    }
                    else
                    {
                        restoreProcess.WaitForExit(RestoreTimeoutMs);
                        if (!restoreProcess.HasExited)
                        {
                            WriteMsg.WriteLine($"Package restore timed out after {RestoreTimeoutMs / 1000 / 60} minutes.", WriteMsg.MsgLevel.Warning);
                            WriteMsg.WriteLine("Missing packages may cause the analysis to fail.", WriteMsg.MsgLevel.Warning);
                            restoreProcess.Kill(true);
                        }
                        else if (restoreProcess.ExitCode != 0)
                        {
                            WriteMsg.WriteLine($"Package restore exited with code {restoreProcess.ExitCode}", WriteMsg.MsgLevel.Warning);
                            WriteMsg.WriteLine("Standard output:", WriteMsg.MsgLevel.Debug);
                            WriteMsg.WriteLine(restoreProcess.StandardOutput.ReadToEnd(), WriteMsg.MsgLevel.Debug);
                            WriteMsg.WriteLine("Standard error:", WriteMsg.MsgLevel.Warning);
                            WriteMsg.WriteLine(restoreProcess.StandardError.ReadToEnd(), WriteMsg.MsgLevel.Warning);
                            WriteMsg.WriteLine("Missing packages may cause the analysis to fail.", WriteMsg.MsgLevel.Warning);
                        }
                        else
                        {
                            WriteMsg.WriteLine(restoreProcess.StandardOutput.ReadToEnd(), WriteMsg.MsgLevel.Debug);
                            WriteMsg.WriteLine(restoreProcess.StandardError.ReadToEnd(), WriteMsg.MsgLevel.Debug);
                        }
                    }
                }
            }
            catch (FileNotFoundException e)
            {
                WriteMsg.WriteLine("Error during package restore: 'dotnet' command not found.", WriteMsg.MsgLevel.Warning);
                WriteMsg.WriteLine("Make sure that you have installed the appropriate .NET Core SDK and the PATH environment variable is set up correctly.", WriteMsg.MsgLevel.Warning);
                WriteMsg.WriteLine("Missing packages may cause the analysis to fail.", WriteMsg.MsgLevel.Warning);
            }
            catch (Exception e)
            {
                WriteMsg.WriteLine($"Unexpected error occured during package restore: {e.Message}", WriteMsg.MsgLevel.Warning);
                WriteMsg.WriteLine("Missing packages may cause the analysis to fail.", WriteMsg.MsgLevel.Warning);
            }
        }

        /// <summary>
        /// Check Root component node contains the actual component
        /// </summary>
        /// <returns></returns>
        private static bool GetAlreadyContain(Component node, Component componentRoot)
        {
            bool alreadyContain = false;
            ListIterator<Component> it = componentRoot.ContainsListIteratorBegin;
            while (it.getValue() != null)
            {
                Component comp = it.getValue();
                if (comp.Id == node.Id)
                {
                    alreadyContain = true;
                    break;
                }
                it = it.getNext();
            }
            return alreadyContain;
        }

        /// <summary>
        /// C# ASG building phase
        /// </summary>
        private static void BuildCsharpAsg(FileContext fileContext)
        {
            fileContext.ProjectContext.SolutionContext.WatchBag.RoslynWatch.Start();
            SyntaxNode root = fileContext.Document.GetSyntaxRootAsync().Result;
            fileContext.ProjectContext.SolutionContext.WatchBag.RoslynWatch.Stop();

            fileContext.TreeBuilder.Visit(root);
        }

        /// <summary>
        /// LIM ASG building phase
        /// </summary>
        private static void BuildLimAsg(FileContext fileContext)
        {
            var solutionContext = fileContext.ProjectContext.SolutionContext;
            var globalNamespace = fileContext.SemanticModel.Compilation.Assembly.GlobalNamespace;

            // TODO move this global namespace creation to a more appropriate place
            if (!solutionContext.MainMap.ContainsKey(globalNamespace))
            {
                solutionContext.MainMap.Add(globalNamespace, solutionContext.LimFactory.Root);
                var symbolBuilder = new SymbolBuilder(fileContext);
                symbolBuilder.BuildDispatch<Package, INamespaceSymbol>(globalNamespace);
                fileContext.UsesStack.Pop();
            }

            if (!GetAlreadyContain(fileContext.ProjectContext.Component, solutionContext.LimFactory.ComponentRootRef))
            {
                solutionContext.LimFactory.ComponentRootRef.addContains(fileContext.ProjectContext.Component);
            }

            solutionContext.WatchBag.RoslynWatch.Start();
            var root = fileContext.SemanticModel.SyntaxTree.GetRoot();
            solutionContext.WatchBag.RoslynWatch.Stop();
            fileContext.RoslynVisitor.Visit(root);
        }

        /// <summary>
        /// Saving C# ASG to the target path.
        /// </summary>
        /// <param name="projectContext">Project context</param>
        /// <param name="output">Output file path</param>
        /// <param name="dumpCsharpml">Make an XML dump of the ASG</param>
        /// <param name="cssiExtension">Extension of the saved ASG</param>
        private static void SaveCsharpAsg(ProjectContext projectContext, string output, bool dumpCsharpml, string cssiExtension)
        {
            List<IHeaderData> header = new List<IHeaderData>();
            PropertyData propertyData = new PropertyData();
            propertyData.add(PropertyData.csih_OriginalLocation, projectContext.SolutionContext.ProcessPath(projectContext.RoslynProject.OutputFilePath));
            header.Add(propertyData);

            string basePath =
                string.IsNullOrEmpty( Path.GetDirectoryName( output ) )
                    ? output
                    : Path.GetDirectoryName( output )
                      + Path.DirectorySeparatorChar
                      + projectContext.RoslynProject.Name
                      + Constants.PROJECTEXTENSION;

            var fileName = basePath + cssiExtension;
            projectContext.CsharpFactory.save(fileName, header);
            projectContext.CsharpFactory.saveFilter(basePath + Constants.FILTEREDCSSIEXTENSION);
            CsharpAsgFiles.Add(fileName);
            if (dumpCsharpml)
            {
                using (StreamWriter sw = new StreamWriter(basePath + Constants.CSHARPDUMPEXTENSION, false, Utf8Encoding))
                {
                    var visitor = new VisitorCSHARPML(sw, projectContext.RoslynProject.Name, true, x => { }, false);  //message writer seems to be unused
                    var ap = new AlgorithmPreorder();
                    ap.run(projectContext.CsharpFactory, visitor);
                }
            }
        }

        /// <summary>
        /// Saving LIM file to the targeted path.
        /// </summary>
        /// <param name="optionBag">Command line options</param>
        /// <param name="solutionContext">The solution context</param>
        private static void SaveLimAsg(OptionBag optionBag, SolutionContext solutionContext)
        {
            if (optionBag.DumpLimml)
                SaveLimml(optionBag.Input, optionBag.Output, optionBag.LimName, solutionContext);

            var headers = new List<IHeaderData> {solutionContext.LimOrigin, solutionContext.OverrideRelations};
            var baseName = optionBag.Output + (string.IsNullOrEmpty(optionBag.LimName) ? Path.GetFileNameWithoutExtension(optionBag.Input) : Path.GetFileName(optionBag.LimName));

            WriteMsg.WriteLine("LIM saving...");
            //Save LIM
            solutionContext.LimFactory.save(baseName + Constants.LIMEXTENSION, headers);
            //Save Filtered LIM
            solutionContext.LimFactory.saveFilter(baseName + Constants.FILTEREDLIMEXTENSION);
            WriteMsg.WriteLine("LIM saved");
        }

        /// <summary>
        /// Saving LIM file to the target path.
        /// </summary>
        /// <param name="input">Input file path</param>
        /// <param name="output">Output file path</param>
        /// <param name="limName">[Output LIM file name]</param>
        /// <param name="solutionContext"></param>
        private static void SaveLimml(string input, string output, string limName, SolutionContext solutionContext)
        {
            string path = output + (string.IsNullOrEmpty(limName) ? Path.GetFileNameWithoutExtension(input) : limName) + Constants.LIMDUMPEXTENSION;
            using (StreamWriter streamWriter = new StreamWriter(path, false, Utf8Encoding))
            {
                string solutionName = Path.GetFileNameWithoutExtension(solutionContext.Solution.FilePath);
                VisitorLIMML visitorLimml = new VisitorLIMML(streamWriter, solutionName, true, m => { }, false);
                Lim.Asg.Algorithms.AlgorithmPreorder ap = new Lim.Asg.Algorithms.AlgorithmPreorder();
                ap.setVisitSpecialNodes(true, true);
                ap.setSafeMode();
                ap.run(solutionContext.LimFactory, visitorLimml);
            }
        }
    }
}
