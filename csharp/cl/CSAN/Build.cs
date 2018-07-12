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
using System.IO;
using System.Threading.Tasks;
using System.Collections.Generic;

using Microsoft.CodeAnalysis;

namespace Columbus.CSAN
{
    using Lim.Asg;
    using Lim.Asg.Nodes.Base;

    using Utils;
    using Commons;
    using Metrics;
    using LimBuilder;
    using RoslynParser;
    using RoslynVisitors;

    using static Common;

    static class Build
    {
        /// <summary>
        /// List of cssi/lcssi files path.
        /// </summary>
        private static List<string> outfiles = new List<string>();

        /// <summary>
        /// UTF8 encoder to the XML file dump without BOM.
        /// </summary>
        private static System.Text.UTF8Encoding utf8Encoding = new System.Text.UTF8Encoding(false);

        /// <summary>
        /// Building main entry point.
        /// </summary>
        /// <param name="abstractOpen"></param>
        /// <param name="output"></param>
        /// <param name="fxCopPath">FxCopCmd.exe path</param>
        /// <param name="fXCopOut">FxCop result directory</param>
        /// <param name="row">CSV file second row</param>
        public static void Start(AbstractOpen abstractOpen, string output, string fxCopPath, string fXCopOut, string outListFilePath)
        {
            WriteMsg.WriteLine("Starting analysis...");
            MainDeclaration.Instance.CSSIExtension = (abstractOpen is FileOpen) ? Constants.CSSIEXTENSION : Constants.LCSSIEXTENSION;
            MainDeclaration.Instance.Solution = abstractOpen.Solution;

            foreach (Project project in abstractOpen.TopologicallySortedProjectDependencies)
            {
                if (Commons.Common.CheckOuterFilters(project.FilePath)) continue;

                WriteMsg.WriteWithBreak("Analyzing {0}...", WriteMsg.MsgLevel.Normal, 4, project.AssemblyName);
                Analyse(project, output, fxCopPath, fXCopOut);
            }

            MainDeclaration.Instance.Statistics[0].CSharpASGBuildingTime = MainDeclaration.Instance.CSSIWatch.ElapsedSeconds;
            MainDeclaration.Instance.Statistics[0].LIMASGBildingTime = MainDeclaration.Instance.LIMWatch.ElapsedSeconds;

            LineMetrics.Calculate();

            WriteMsg.WriteLine("Analysis finished");
            if (!string.IsNullOrEmpty(outListFilePath))
            {
                File.WriteAllText(outListFilePath, string.Join(Environment.NewLine, outfiles));
            }
            MainDeclaration.Instance.FxCopTasks.WaitAll();
        }

        /// <summary>
        /// Saving LIM file to the targeted path.
        /// </summary>
        /// <param name="intput">Input file with full path</param>
        /// <param name="output">Output file path</param>
        /// <param name="limName">Output LIM file name</param>
        public static void SaveLimASG(string intput, string output, string limName)
        {
            if (MainDeclaration.Instance.DumpLimml)
            {
                SaveLimML(intput, output, limName);
            }

            List<IHeaderData> headers = new List<IHeaderData>();

            headers.Add(MainDeclaration.Instance.LimOrigin);
            headers.Add(MainDeclaration.Instance.OverrideRelations);
            WriteMsg.WriteLine("LIM saving...");

            //Save LIM
            MainDeclaration.Instance.LimFactory.save(
                output
                + ((limName != string.Empty) ? Path.GetFileName(limName) : Path.GetFileNameWithoutExtension(intput))
                + Constants.LIMEXTENSION, headers);

            //Save Filtered LIM
            MainDeclaration.Instance.LimFactory.saveFilter(
                output
                + ((limName != string.Empty) ? Path.GetFileName(limName) : Path.GetFileNameWithoutExtension(intput))
                + Constants.FILTEREDLIMEXTENSION);
            WriteMsg.WriteLine("LIM saved");
        }

        /// <summary>
        /// Project file analysis phase
        /// </summary>
        /// <param name="project">Porject file object</param>
        /// <param name="output">C# ASG output path</param>
        /// <param name="fxCopPath">FxCopCmd.exe path</param>
        /// <param name="fXCopOut">FxCop result directory</param>
        private static void Analyse(Project project, string output, string fxCopPath, string fXCopOut)
        {
            if (!string.IsNullOrEmpty(fxCopPath))
                MainDeclaration.Instance.FxCopTasks.Add(Task.Run(() => StartFxCopAnalysis(project.OutputFilePath, (string.IsNullOrEmpty(fXCopOut)) ? output : fXCopOut, fxCopPath)));
            CreateComponent(project);

            Csharp.Asg.Factory Factory = new Csharp.Asg.Factory(new StrTable());
            Dictionary<Microsoft.CodeAnalysis.CSharp.CSharpSyntaxNode, uint> CSharpMap = new Dictionary<Microsoft.CodeAnalysis.CSharp.CSharpSyntaxNode, uint>();
            NodeBuilder mapBuilder = new NodeBuilder(Factory, CSharpMap);
            TreeEdgeBuilder edgeBuilder = new TreeEdgeBuilder(Factory, CSharpMap);
            CrossEdgeFiller crossEdgeFiller = new CrossEdgeFiller(Factory, CSharpMap);

            foreach (var document in project.Documents)
            {
                if (Commons.Common.CheckOuterFilters(document.FilePath)) continue;

                MainDeclaration.Instance.RoslynWatch.Start();
                MainDeclaration.Instance.Model = document.GetSemanticModelAsync().Result;
                MainDeclaration.Instance.RoslynWatch.Stop();
                MainDeclaration.Instance.CSSIWatch.Start();
                BuildCSSIASG(document, mapBuilder, edgeBuilder);
                MainDeclaration.Instance.CSSIWatch.Stop();
                MainDeclaration.Instance.LIMWatch.Start();
                BuildLIMASG(CSharpMap, crossEdgeFiller);
                MainDeclaration.Instance.LIMWatch.Stop();
            }

            SaveCsharpASG(project, output, Factory);
        }

        /// <summary>
        /// Binary file will be analysed by FxCop.
        /// </summary>
        /// <param name="inputBinary">Binary file location</param>
        /// <param name="resultOutputPath">FxCop result directory</param>
        /// <param name="fxCopPath">FxCopCmd.exe path</param>
        private static void StartFxCopAnalysis(string inputBinary, string resultOutputPath, string fxCopPath)
        {
            if (string.IsNullOrEmpty(fxCopPath))
                return;
            string output_filename = Path.GetFileNameWithoutExtension(inputBinary) + ".xml";
            string output_directory = Path.GetDirectoryName(inputBinary);
            string result = Path.Combine(output_directory, output_filename);

            if (!string.IsNullOrEmpty(resultOutputPath) && resultOutputPath[resultOutputPath.Length - 1] != Path.DirectorySeparatorChar)
                resultOutputPath += Path.DirectorySeparatorChar;

            System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo()
            {
                CreateNoWindow = false,
                UseShellExecute = false,
                FileName = fxCopPath.EndsWith(".exe") ? fxCopPath : fxCopPath + "FxCopCmd.exe",
                WorkingDirectory = fxCopPath.EndsWith(".exe") ? Path.GetDirectoryName(fxCopPath) : fxCopPath,
                WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden,
                Arguments = string.Format("/f:\"{0}\" /d:\"{1}\" /r:\"{2}\" /o:\"{3}{4}\" /gac",
                                        inputBinary, output_directory, (fxCopPath.Contains(".exe") ? Path.GetDirectoryName(fxCopPath) : fxCopPath) + "Rules", resultOutputPath, output_filename),
                RedirectStandardOutput = true,
                RedirectStandardError = true
            };

            if (MainDeclaration.Instance.BuildTask != null)
                MainDeclaration.Instance.BuildTask.Wait();

            if (!File.Exists(inputBinary))
            {
                WriteMsg.WriteWithBreak("[FxCopAnalysis] {0} is missing, skipped", WriteMsg.MsgLevel.Warning, 4, inputBinary);
                return;
            }

            WriteMsg.WriteWithBreak("[FxCopAnalysis] Starting FxCop analysis for {0}...", WriteMsg.MsgLevel.Normal, 4, inputBinary);
            try
            {
                string output = string.Format("{0}{1}{2}.log", resultOutputPath, Path.DirectorySeparatorChar, output_filename);

                using (System.Diagnostics.Process exeProcess = new System.Diagnostics.Process())
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
                WriteMsg.WriteWithBreak("[FxCopAnalysis] FxCop for {0} terminated", WriteMsg.MsgLevel.Normal, 4, Path.GetFileName(inputBinary));
            }
            catch (FileNotFoundException e)
            {
                if (File.Exists(result))
                    File.Delete(result);
                WriteMsg.WriteWithBreak("[FxCopAnalysis][FileNotFoundException] {0}: {1}", WriteMsg.MsgLevel.Warning, 4, e.Message, startInfo.FileName);
            }
            catch (System.ComponentModel.Win32Exception e)
            {
                if (File.Exists(result))
                    File.Delete(result);
                WriteMsg.WriteWithBreak("[FxCopAnalysis][Win32Exception] " + e.Message, WriteMsg.MsgLevel.Warning, 4);
            }
            catch (System.IO.IOException e)
            {
                if (File.Exists(result))
                    File.Delete(result);
                WriteMsg.WriteWithBreak("[FxCopAnalysis][IOException] " + e.Message, WriteMsg.MsgLevel.Warning, 4);
            }
            catch (Exception e)
            {
                if (File.Exists(result))
                    File.Delete(result);
                WriteMsg.WriteWithBreak("[FxCopAnalysis][{0}] {1}", WriteMsg.MsgLevel.Warning, 4, e.GetType().ToString(), e.Message);
            }
        }

        /// <summary>
        /// Create LIM component from the Project
        /// </summary>
        /// <param name="project">Project file object</param>
        private static void CreateComponent(Project project)
        {
            MainDeclaration.Instance.Component = MainDeclaration.Instance.LimFactory.createComponent(Commons.Common.ProcessPath(project.OutputFilePath));
            MainDeclaration.Instance.RevEdges = MainDeclaration.Instance.LimFactory.GetReverseEdges();

            SetNotFilteredComponentUp(MainDeclaration.Instance.Component, true);

            MainDeclaration.Instance.Component.ShortName = Path.GetFileName(project.OutputFilePath);
        }

        /// <summary>
        /// Check Root component node contains the actual component
        /// </summary>
        /// <returns></returns>
        private static bool GetAlreadyContain(Component node)
        {
            bool alreadyContain = false;
            ListIterator<Component> it = MainDeclaration.Instance.LimFactory.ComponentRootRef.ContainsListIteratorBegin;
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
        /// <param name="document">C# file's object</param>
        /// <param name="mapBuilder">Node builder reference</param>
        /// <param name="edgeBuilder">Edge builder reference</param>
        private static void BuildCSSIASG(Document document, NodeBuilder mapBuilder, TreeEdgeBuilder edgeBuilder)
        {
            MainDeclaration.Instance.RoslynWatch.Start();
            SyntaxNode root = document.GetSyntaxRootAsync().Result;
            MainDeclaration.Instance.RoslynWatch.Stop();

            mapBuilder.Visit(root);
            edgeBuilder.Visit(root);
        }

        /// <summary>
        /// LIM ASG building phase
        /// </summary>
        /// <param name="map">Roslyn node and C# ASG ids map</param>
        /// <param name="crossEdgeFiller">C# ASG cross edge filler object</param>
        private static void BuildLIMASG(Dictionary<Microsoft.CodeAnalysis.CSharp.CSharpSyntaxNode, uint> map, CrossEdgeFiller crossEdgeFiller)
        {
            if (!MainDeclaration.Instance.LocalMap.ContainsKey(MainDeclaration.Instance.Model.Compilation.Assembly.GlobalNamespace))
            {
                MainDeclaration.Instance.LocalMap.Add(MainDeclaration.Instance.Model.Compilation.Assembly.GlobalNamespace, MainDeclaration.Instance.LimFactory.Root);
                MainDeclaration.Instance.Root = MainDeclaration.Instance.LimFactory.getRef(MainDeclaration.Instance.LimFactory.Root) as Lim.Asg.Nodes.Logical.Package;
                SymbolBuilder.BuildDispatch<Lim.Asg.Nodes.Logical.Package, INamespaceSymbol>(MainDeclaration.Instance.Model.Compilation.Assembly.GlobalNamespace);
                MainDeclaration.Instance.UsesStack.Pop();
            }

            Commons.Common.Safe_Edge(MainDeclaration.Instance.Root, "BelongsTo", MainDeclaration.Instance.Component.Id);

            if (!GetAlreadyContain(MainDeclaration.Instance.Component))
            {
                MainDeclaration.Instance.LimFactory.ComponentRootRef.addContains(MainDeclaration.Instance.Component);
            }

            MainDeclaration.Instance.RoslynWatch.Start();
            var root = MainDeclaration.Instance.Model.SyntaxTree.GetRoot();
            MainDeclaration.Instance.RoslynWatch.Stop();
            //Visitor.Visit(root, ref map, crossEdgeFiller);
            RoslynVisitor.GetInstance(map, crossEdgeFiller).Visit(root);
        }

        /// <summary>
        /// Set up the analysis time and the filter to the component.
        /// </summary>
        /// <param name="node">Actual component</param>
        private static void SetNotFilteredComponentUp(Component node, bool hasStructureInfo)
        {
            MainDeclaration.Instance.LimFactory.setNotFilteredThisNodeOnly(node.Id);

            if (node.AnalysisTime == Types.AnalysisTimeKind.atkNever)
            {
                if (hasStructureInfo)
                {
                    node.AnalysisTime = Types.AnalysisTimeKind.atkBefore;
                }
                else
                {
                    node.AnalysisTime = Types.AnalysisTimeKind.atkNow;
                }
            }

            for (var it = node.ContainsListIteratorBegin; it.getValue() != null; it = it.getNext())
                SetNotFilteredComponentUp(it.getValue(), hasStructureInfo);
        }

        /// <summary>
        /// Saving C# ASG to the target path.
        /// </summary>
        /// <param name="project">Project file's object</param>
        /// <param name="output">Output file path</param>
        /// <param name="Factory">C# ASG's factory object</param>
        private static void SaveCsharpASG(Project project, string output, Csharp.Asg.Factory Factory)
        {
            List<IHeaderData> header = new List<IHeaderData>();
            PropertyData propertyData = new PropertyData();
            propertyData.add(PropertyData.csih_OriginalLocation, Commons.Common.ProcessPath(project.OutputFilePath));
            header.Add(propertyData);

            string basePath =
                string.IsNullOrEmpty( Path.GetDirectoryName( output ) )
                    ? output
                    : Path.GetDirectoryName( output )
                      + Path.DirectorySeparatorChar
                      + project.Name
                      + Constants.PROJECTEXTENSION;

            Factory.save(basePath + MainDeclaration.Instance.CSSIExtension, header);
            Factory.saveFilter(basePath + Constants.FILTEREDCSSIEXTENSION);
            outfiles.Add(basePath + MainDeclaration.Instance.CSSIExtension);
            if (MainDeclaration.Instance.DumpCsharpml)
            {
                using (StreamWriter sw = new StreamWriter(basePath + Constants.CSHARPDUMPEXTENSION, false, utf8Encoding))
                {
                    var visitor = new Csharp.Asg.Visitors.VisitorCSHARPML(sw, project.Name, true, x => { }, false);  //message writer seems to be unused
                    var ap = new Csharp.Asg.Algorithms.AlgorithmPreorder();
                    ap.run(Factory, visitor);
                }
            }
        }

        /// <summary>
        /// Saving LIM file to the target path.
        /// </summary>
        /// <param name="intput">Input file path</param>
        /// <param name="output">Output file path</param>
        /// <param name="limName">[Output LIM file name]</param>
        private static void SaveLimML(string intput, string output, string limName)
        {
            string path = output + ((limName != string.Empty) ? limName : Path.GetFileNameWithoutExtension(intput)) + Constants.LIMDUMPEXTENSION;
            using (System.IO.StreamWriter streamWriter = new System.IO.StreamWriter(path, false, utf8Encoding))
            {
                string solutionName = System.IO.Path.GetFileNameWithoutExtension(MainDeclaration.Instance.Solution.FilePath);
                Columbus.Lim.Asg.Visitors.VisitorLIMML visitorLimml = new Columbus.Lim.Asg.Visitors.VisitorLIMML(streamWriter, solutionName, true, m => { }, false);
                Columbus.Lim.Asg.Algorithms.AlgorithmPreorder ap = new Columbus.Lim.Asg.Algorithms.AlgorithmPreorder();
                ap.setVisitSpecialNodes(true, true);
                ap.setSafeMode();
                ap.run(MainDeclaration.Instance.LimFactory, visitorLimml);
            }
        }
    }
}