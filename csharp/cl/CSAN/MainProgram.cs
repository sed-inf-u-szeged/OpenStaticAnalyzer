using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using Columbus.CSAN.Utils;

namespace Columbus.CSAN
{
    using CsvFiles;
    using RoslynParser;

    static class MainProgram
    {
        /// <summary>
        /// Checks FxCopPath and tries to find FxCop if not specified
        /// </summary>
        /// <returns>False if FxCopPath was specified but invalid, true otherwise.</returns>
        private static bool CheckFxCopPath(OptionBag optionBag)
        {
            if (string.IsNullOrEmpty(optionBag.FxCopPath))
            {
                WriteMsg.WriteLine("No FxCopPath specified, looking for it in installed Visual Studio directories...");
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
                    optionBag.FxCopPath = Path.GetFullPath(Path.Combine(vsCommonTools, "..", "..", relativePath));
                    if (File.Exists(optionBag.FxCopPath + "FxCopCmd.exe"))
                    {
                        WriteMsg.WriteLine("Found Visual Studio " + version);
                        WriteMsg.WriteLine("FxCop static analysis tool will be used from: " + optionBag.FxCopPath);
                    }
                    else
                    {
                        optionBag.FxCopPath = null;
                        WriteMsg.WriteLine("Could not find FxCop on your computer. FxCop analysis will be skipped.", WriteMsg.MsgLevel.Warning);
                    }
                }
                else
                {
                    WriteMsg.WriteLine("Could not find FxCop on your computer. FxCop analysis will be skipped.", WriteMsg.MsgLevel.Warning);
                }
            }
			else if(!File.Exists(optionBag.FxCopPath.EndsWith(".exe") ? optionBag.FxCopPath : Path.Combine(optionBag.FxCopPath, "FxCopCmd.exe")))
            {
				WriteMsg.WriteLine("Could not find FxCop at the specified location: {0}", WriteMsg.MsgLevel.Error, optionBag.FxCopPath);
				return false;
			}
			return true;
        }

        /// <summary>
        /// Disable auxiliary stopwatches if -stat is not provided.
        /// </summary>
        private static void DisableAuxStopwatches(WatchBag watchBag)
        {
            watchBag.CSSIWatch.Enabled = false;
            watchBag.LIMWatch.Enabled = false;
            watchBag.RoslynWatch.Enabled = false;
        }

        /// <summary>
        /// The program main entry point.
        /// </summary>
        /// <param name="args">Command line arguments</param>
        private static void Main(string[] args)
        {
            var watchBag = new WatchBag();
            watchBag.MainWatch.Start();

            WriteMsg.Initialize(args);  //this should be called first, before any output

#if !DEBUG
            // Handle unhandled exceptions, prevent .NET's default "stopped working" dialog from showing up
            // and blocking multiple processes waiting on this to exit in release builds
            AppDomain.CurrentDomain.UnhandledException += (sender, eventArgs) =>
            {
                if (eventArgs.ExceptionObject is Exception exception)
                    Common.LogException(exception);
                else
                {
                    // This will probably never happen.
                    WriteMsg.WriteLine("Unknown error happened.", WriteMsg.MsgLevel.Error);
                    WriteMsg.WriteLine($"Sender: {sender}", WriteMsg.MsgLevel.Error);
                    WriteMsg.WriteLine($"EventArgs: {eventArgs}", WriteMsg.MsgLevel.Error);
                }
                Environment.Exit(1);
            };
#endif

            Common.LogProgramInfo();
            var optionBag = new OptionBag(args);

            WriteMsg.WriteLine("Input: " + optionBag.Input);
            WriteMsg.WriteLine("Output: " + optionBag.Output);
            if (!string.IsNullOrEmpty(optionBag.FxCopPath))
                WriteMsg.WriteLine("FxCopPath: " + optionBag.FxCopPath);

            if (optionBag.RunFxCop && !CheckFxCopPath(optionBag))
				Environment.Exit(1);

            if (string.IsNullOrEmpty(optionBag.Stat))
                DisableAuxStopwatches(watchBag);

            if (!string.IsNullOrEmpty(optionBag.ExternalHardFilter))
                WriteMsg.WriteLine("Hardfilter: " + optionBag.ExternalHardFilter);
            if (!string.IsNullOrEmpty(optionBag.ExternalSoftFilter))
                WriteMsg.WriteLine("Softfilter: " + optionBag.ExternalSoftFilter);

            var statistic = new Statistic();

            WriteMsg.WriteLine("File parsing...");
            using (var file = AbstractOpen.CreateInstance(optionBag.Input, optionBag.Configuration, optionBag.Platform))
            {
                var fileParsingWatch = Stopwatch.StartNew();
                file.Parse();
                statistic.FilesParsingTime = fileParsingWatch.ElapsedSeconds;
                WriteMsg.WriteLine("File parsing finished.");

                Task buildTask = null;
                if (optionBag.BuildProject)
                {
                    WriteMsg.WriteLine("Build started");
                    Stopwatch buildWatch = Stopwatch.StartNew();
                    buildTask = file.BuildSoulution().ContinueWith(task =>
                    {
                        statistic.SolutionsBuildingTime = buildWatch.ElapsedSeconds;
                        WriteMsg.WriteLine(task.Result ? "Build succeeded" : "Build failed");
                    });
                }

                // Run on a new thread with a bigger stack than the default 1 MB for deep syntax trees
                var thread = new System.Threading.Thread(
                        () => Build.Start(file, optionBag, watchBag, buildTask, statistic),
                        16 * 1024 * 1024)
                    {
                        Name = "AnalyzerThread"
                    };
                thread.Start();
                thread.Join();
            }

            statistic.AnalyzeTime = watchBag.MainWatch.ElapsedSeconds;
            statistic.CSharpASGBuildingTime = watchBag.CSSIWatch.ElapsedSeconds;
            statistic.LIMASGBildingTime = watchBag.LIMWatch.ElapsedSeconds;
            statistic.RoslynTime = watchBag.RoslynWatch.ElapsedSeconds;
            statistic.PeakMemory = Process.GetCurrentProcess().PeakWorkingSet64 / 1048576f;

            if (!string.IsNullOrEmpty(optionBag.Stat))
                new[] {statistic}.ToCsv(new CsvDestination(optionBag.Stat), new CsvDefinition { FieldSeparator = optionBag.CsvSeparator, DecimalSeparator = optionBag.CsvDecimalMark });

            WriteMsg.WriteLine();
            WriteMsg.WriteLine("Statistics:");
            WriteMsg.WriteLine();
            WriteMsg.WriteLine("    Elapsed time: {0}", WriteMsg.MsgLevel.Normal, statistic.AnalyzeTime);
            WriteMsg.WriteLine("    Used memory:  {0} Mb", WriteMsg.MsgLevel.Normal, statistic.PeakMemory);  // 1024 * 1024
        }
    }
}
