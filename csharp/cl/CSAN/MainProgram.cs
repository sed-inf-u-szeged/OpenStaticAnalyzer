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
using System.Diagnostics;
using System.IO;

namespace Columbus.CSAN
{
    using CsvFiles;
    using Commons;
    using RoslynParser;

    static partial class MainProgram
    {
        #region CSAN parameters
        private static string STAT = string.Empty;
        private static string INPUT;
        private static string OUTPUT;
        private static string LIMNAME = string.Empty;
        private static string OUTLIST = string.Empty;
        private static string FXCOPOUT = string.Empty;
        private static string FXCOPPATH;
        private static char CSVSEPARATOR = ';';
        private static char DECIMALSEPARATOR = '.';
        private static string EXTERNALHARDFILTER = string.Empty;
        private static string EXTERNALSOFTFILTER = string.Empty;
        private static bool BUILDPROJECT;
        private static bool RUNFXCOP = true;
        private static string PLATFORM = string.Empty;
        private static string CONFIGURATION = string.Empty;
        #endregion

        /// <summary>
        /// Checks FxCopPath and tries to find FxCop if not specified
        /// </summary>
        private static bool CheckFxCopPath()
        {
            if (string.IsNullOrEmpty(FXCOPPATH) && RUNFXCOP)
            {
                WriteMsg.WriteWithBreak("No FxCopPath specified, looking for it in installed Visual Studio directories...");
                string relativePath = @"Team Tools\Static Analysis Tools\FxCop\";
                string vsCommonTools = Environment.GetEnvironmentVariable("VS140COMNTOOLS");
                string version = "2015";
                if (string.IsNullOrEmpty(vsCommonTools))
                {
                    vsCommonTools = Environment.GetEnvironmentVariable("VS120COMNTOOLS");
                    version = "2013";
                    if (string.IsNullOrEmpty(vsCommonTools))
                    {
                        vsCommonTools = Environment.GetEnvironmentVariable("VS100COMNTOOLS");
                        version = "2010";
                    }
                }
                if (!string.IsNullOrEmpty(vsCommonTools))
                {
                    FXCOPPATH = Path.GetFullPath(vsCommonTools + ".." + Path.DirectorySeparatorChar + ".." + Path.DirectorySeparatorChar + relativePath);
                    if (File.Exists(FXCOPPATH + "FxCopCmd.exe"))
                    {
                        WriteMsg.WriteWithBreak("Found Visual Studio " + version);
                        WriteMsg.WriteWithBreak("FxCop static analysis tool will be used from: " + FXCOPPATH);
                    }
                    else
                    {
                        FXCOPPATH = null;
                        WriteMsg.WriteWithBreak("Could not find FxCop on your computer. FxCop analysis will be skipped.", WriteMsg.MsgLevel.Warning);
                    }
                }
                else
                {
                    WriteMsg.WriteWithBreak("Could not find FxCop on your computer. FxCop analysis will be skipped.", WriteMsg.MsgLevel.Warning);
                }
            }
			else if(RUNFXCOP && !File.Exists(FXCOPPATH.EndsWith(".exe") ? FXCOPPATH : FXCOPPATH + "FxCopCmd.exe"))
            {
				WriteMsg.WriteWithBreak("Could not find FxCop at the specified location: {0}", WriteMsg.MsgLevel.Error, 0, FXCOPPATH);
				return false;
			}
			return true;
        }

        /// <summary>
        /// Disable auxiliary stopwatches if -stat is not provided.
        /// </summary>
        private static void CheckStopwatches()
        {
            if(string.IsNullOrEmpty(STAT))
            {
                MainDeclaration.Instance.CSSIWatch.Enabled = false;
                MainDeclaration.Instance.LIMWatch.Enabled = false;
                MainDeclaration.Instance.RoslynWatch.Enabled = false;
            }
        }

        /// <summary>
        /// Write some statistics to the console and csv row.
        /// </summary>
        private static void WriteStatistics(Stopwatch stopwatch, long peakMemory)
        {
            WriteMsg.WriteLine("Statistics:");
            WriteMsg.WriteLine();
            WriteMsg.WriteLine("    Elapsed time: {0}", WriteMsg.MsgLevel.Normal, stopwatch.Elapsed);
            WriteMsg.WriteLine("    Used memory:  {0} Mb", WriteMsg.MsgLevel.Normal, peakMemory / 1048576f);  // 1024 * 1024
            MainDeclaration.Instance.Statistics[0].AnalyzeTime = stopwatch.ElapsedSeconds;
            MainDeclaration.Instance.Statistics[0].PeakMemory = peakMemory / 1048576f;
        }

        /// <summary>
        /// The program main entry point.
        /// </summary>
        /// <param name="args">Command line arguments</param>
        private static void Main(string[] args)
        {
#if !DEBUG
            try
            {
#endif
            MainDeclaration.Instance.MainWatch.Start();

            //this should be called first, before any output
            WriteMsg.Initialize(args);

            WriteMsg.WriteLine(
				"C# Analyzer {0} ({1}) - {2}",
				WriteMsg.MsgLevel.Silent,
				0,
				System.Reflection.Assembly.GetExecutingAssembly().GetName().Version.ToString(3),  //we use 3 digit versions, eg 7.0.6
				Columbus.Common.Revision,
				Columbus.Common.CopyRightMessage);
            WriteMsg.WriteLine();

            Process myProcess = Process.GetCurrentProcess();

            if (Arguments.ProcessArguments(args, OPTIONS_OBJ, "-", ppUnknownOption) && !string.IsNullOrEmpty(INPUT) && !string.IsNullOrEmpty(OUTPUT))
            {
                WriteMsg.WriteLine("Input: " + INPUT);
                WriteMsg.WriteLine("Output: " + OUTPUT);
                if (!string.IsNullOrEmpty(FXCOPPATH))
                {
                    WriteMsg.WriteLine("FxCopPath: " + FXCOPPATH);
                }
            }
            else
            {
                WriteMsg.WriteLine("Error: No input and/or output specified!", WriteMsg.MsgLevel.Error);
                WriteMsg.WriteLine("", WriteMsg.MsgLevel.Error);
                ppHelp(default(Option), null);
                Environment.Exit(1);
            }

			if (!CheckFxCopPath())
				Environment.Exit(1);
            CheckStopwatches();

            if (MainDeclaration.Instance.HardFilter != null)
                WriteMsg.WriteLine("Hardfilter: " + EXTERNALHARDFILTER);
            if (MainDeclaration.Instance.SoftFilter != null)
                WriteMsg.WriteLine("Softfilter: " + EXTERNALSOFTFILTER);

            MainDeclaration.Instance.LimFactory.Language = Lim.Asg.Types.LanguageKind.lnkCsharp;

            WriteMsg.WriteLine("File parsing...");
            var timer = MainDeclaration.Instance.MainWatch.ElapsedSeconds;
            using (AbstractOpen file = AbstractOpen.CreateInstance(INPUT, CONFIGURATION, PLATFORM))
            {
                file.Parse();
                MainDeclaration.Instance.Statistics[0].FilesParsingTime = MainDeclaration.Instance.MainWatch.ElapsedSeconds - timer;
                WriteMsg.WriteLine("File parsing finished.");

                float buildTime = 0f;

                if (BUILDPROJECT)
                {
                    WriteMsg.WriteLine("Build started");
                    Stopwatch watch = Stopwatch.StartNew();
                    MainDeclaration.Instance.BuildTask = file.BuildSoulution().ContinueWith(task =>
                    {
                        buildTime = watch.ElapsedSeconds;
                        WriteMsg.WriteLine(task.Result ? "Build succeeded" : "Build failed");
                    });
                }

                timer = MainDeclaration.Instance.MainWatch.ElapsedSeconds;
                Build.Start(file, OUTPUT, RUNFXCOP ? FXCOPPATH : null, FXCOPOUT, OUTLIST);
                MainDeclaration.Instance.Statistics[0].ASGBuildingTime = MainDeclaration.Instance.MainWatch.ElapsedSeconds - timer;

                if (MainDeclaration.Instance.BuildTask != null)
                    MainDeclaration.Instance.BuildTask.Wait();

                MainDeclaration.Instance.Statistics[0].SolutionsBuildingTime = buildTime;
                MainDeclaration.Instance.Statistics[0].RoslynTime = MainDeclaration.Instance.RoslynWatch.ElapsedSeconds;

                timer = MainDeclaration.Instance.MainWatch.ElapsedSeconds;
                Build.SaveLimASG(INPUT, OUTPUT, LIMNAME);
                MainDeclaration.Instance.Statistics[0].SaveTime = MainDeclaration.Instance.MainWatch.ElapsedSeconds - timer;

                MainDeclaration.Instance.MainWatch.Stop();
                WriteMsg.WriteLine();
                WriteStatistics(MainDeclaration.Instance.MainWatch, myProcess.PeakWorkingSet64);
                if (!string.IsNullOrEmpty(STAT))
                    MainDeclaration.Instance.Statistics.ToCsv(new CsvDestination(STAT), new CsvDefinition() { FieldSeparator = CSVSEPARATOR, DecimalSeparator = DECIMALSEPARATOR });
            }
#if !DEBUG
            }
            /// Catch everything to prevent .NET's default "stopped working" dialog from showing up
            /// and blocking multiple processes waiting on this to exit
            catch (AggregateException e)
            {
                Console.Error.WriteLine();
                Console.Error.WriteLine("EXCEPTION: {0}", e.GetType());
                Console.Error.WriteLine();
                if (e.InnerExceptions.Count > 1)
                {
                    foreach (var error in e.InnerExceptions)
                    {
                        Console.Error.WriteLine("EXCEPTION: {0}", error.GetType());
                        Console.Error.WriteLine(error.Message);
                        Console.Error.WriteLine(error.StackTrace);
                        Console.Error.WriteLine();
                    }
                }
                else if (e.InnerException != null)
                {
                    Console.Error.WriteLine("EXCEPTION: {0}", e.InnerException.GetType());
                    Console.Error.WriteLine(e.InnerException.Message);
                    Console.Error.WriteLine(e.InnerException.StackTrace);
                }
                else
                {
                    Console.Error.WriteLine(e.Message);
                    Console.Error.WriteLine(e.StackTrace);
                }
                Environment.Exit(1);
            }
            catch (Exception e)
            {
                Console.Error.WriteLine();
                Console.Error.WriteLine("EXCEPTION: {0}", e.GetType());
                Console.Error.WriteLine(e.Message);
                Console.Error.WriteLine(e.StackTrace);
                Environment.Exit(1);
            }
#endif
        }
    }
}