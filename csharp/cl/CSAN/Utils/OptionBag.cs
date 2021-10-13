using System;
using System.IO;

namespace Columbus.CSAN.Utils
{
    class OptionBag
    {
        public string Stat { get; private set; }
        public string Input { get; private set; }
        public string Output { get; private set; }
        public string LimName { get; private set; }
        public string OutList { get; private set; }
        public string FxCopOut { get; private set; }
        public string FxCopPath { get; set; }
        public char CsvSeparator { get; private set; } = ';';
        public char CsvDecimalMark { get; private set; } = '.';
        public string ExternalHardFilter { get; private set; }
        public string ExternalSoftFilter { get; private set; }
        public bool BuildProject { get; private set; }
        public bool RunFxCop { get; private set; } = true;
        public string Platform { get; private set; }
        public string Configuration { get; private set; }
        public string ChangePathFrom { get; private set; }
        public string ChangePathTo { get; private set; } = string.Empty;
        public bool DumpLimml { get; private set; }
        public bool DumpCsharpml { get; private set; }
        public bool RunAnalyzers { get; private set; }
        public string AnalyzersOut { get; private set; }
        public bool RestorePackages { get; private set; } = true;

        private readonly Option[] optionsSpecifications;

        public OptionBag(string[] args)
        {
            optionsSpecifications = new[]
            {
                new Option
                {
                    Name = "-input",
                    NumberOfParameters = 1,
                    ParameterName = "file",
                    Needed = 1,
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "The input to analyze. A solution (.sln), project (.csproj), or source (.cs) file. This argument is required."
                },
                new Option
                {
                    Name = "-output",
                    NumberOfParameters = 1,
                    ParameterName = "directory",
                    Needed = 2,
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "The directory where result files will be created. This argument is required."
                },
                new Option
                {
                    Name = "-configuration",
                    NumberOfParameters = 1,
                    ParameterName = "configuration",
                    Needed = 0,
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "The configuration of project file(s)."
                },
                new Option
                {
                    Name = "-platform",
                    NumberOfParameters = 1,
                    ParameterName = "platform",
                    Needed = 0,
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "The targeted platform."
                },
                new Option
                {
                    Internal = true,
                    Name = "-stat",
                    NumberOfParameters = 1,
                    ParameterName = "file",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "Create runtime statistics file."
                },
                new Option
                {
                    Name = "-outList",
                    NumberOfParameters = 1,
                    ParameterName = "file",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "A list file where the generated ASG files' paths will be written out."
                },
                new Option
                {
                    Name = "-limName",
                    NumberOfParameters = 1,
                    ParameterName = "file",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "Name of the LIM file to be created."
                },
                new Option
                {
                    Name = "-fxCopOut",
                    NumberOfParameters = 1,
                    ParameterName = "path",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "Output path for FxCop."
                },
                new Option
                {
                    Name = "-fxCopPath",
                    NumberOfParameters = 1,
                    ParameterName = "path",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "Path of FxCop."
                },
                new Option
                {
                    Name = "-csvseparator",
                    NumberOfParameters = 1,
                    ParameterName = "character",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessCharOption,
                    Description = "Field separator character to be used in CSV outputs. It must be a single character, " +
                                  @"except for the special \t escape sequence which yields the tabulator character (ASCII 09)."
                },
                new Option
                {
                    Name = "-csvdecimalmark",
                    NumberOfParameters = 1,
                    ParameterName = "character",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessCharOption,
                    Description = "Decimal separator to be used in CSV outputs."
                },
                new Option
                {
                    Name = "-externalHardFilter",
                    NumberOfParameters = 1,
                    ParameterName = "file",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "External hardfilter file. See the documentation for usage."
                },
                new Option
                {
                    Name = "-externalSoftFilter",
                    NumberOfParameters = 1,
                    ParameterName = "file",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "External softfilter file. See the documentation for usage."
                },
                new Option
                {
                    Internal = true,
                    Name = "-buildProject",
                    NumberOfParameters = 1,
                    ParameterName = "(true|false)",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessBoolOption,
                    Description = "Try to build the project using Roslyn Emit API. Default is false."
                },
                new Option
                {
                    Name = "-runFxCop",
                    NumberOfParameters = 1,
                    ParameterName = "(true|false)",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessBoolOption,
                    Description = "Try to run FxCop analysis. If -fxCopPath is not given, we will search through installed VisualStudio folders."
                },
                new Option
                {
                    Internal = true,
                    Name = "-changepathfrom",
                    NumberOfParameters = 1,
                    ParameterName = "path",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "If given, this subpath will be replaced with -changepathto in all source positions, enabling you to write relative paths into ASGs."
                },
                new Option
                {
                    Internal = true,
                    Name = "-changepathto",
                    NumberOfParameters = 1,
                    ParameterName = "path",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "If used with -changepathfrom, this will be the replacement string in paths."
                },
                new Option
                {
                    Name = "-dlimml",
                    Type = ArgumentOptions.OT_NONE,
                    Process = ProcessBoolOption,
                    Description = "Make XML dump from LIM ASG."
                },
                new Option
                {
                    Name = "-dcsharpml",
                    Type = ArgumentOptions.OT_NONE,
                    Process = ProcessBoolOption,
                    Description = "Make XML dump from C# ASGs."
                },
                new Option
                {
                    Name = "-runAnalyzers",
                    NumberOfParameters = 1,
                    ParameterName = "(true|false)",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessBoolOption,
                    Description = "Run Roslyn Analyzers"
                },
                new Option
                {
                    Name = "-analyzersOut",
                    NumberOfParameters = 1,
                    ParameterName = "path",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessStringOption,
                    Description = "Output path for Roslyn Analyzers' results. Default is the same as -output."
                },
                new Option
                {
                    Name = "-restorePackages",
                    NumberOfParameters = 1,
                    ParameterName = "(true|false)",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = ProcessBoolOption,
                    Description = "Restore NuGet packages automatically before analysis. Default is true."
                },
                new Option
                {
                    Internal = true,
                    Name = "-developer",
                    Type = ArgumentOptions.OT_NONE,
                    Process = null, //processed separately
                    Description = "Does nothing currently."
                },
                new Option
                {
                    Name = "-ml",
                    NumberOfParameters = 1,
                    ParameterName = "level",
                    Type = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                    Process = null, //processed separately
                    Description = "Sets the message level of the program\n" +
                                  "0 (silent)  does not write any message\n" +
                                  "1 (error)   writes out error messages only\n" +
                                  "2 (warning) writes out error and warning messages\n" +
                                  "3 (normal)  writes out every normal informational messages as well - this is the default"
                },
                new Option
                {
                    Internal = true,
                    Name = "-helpi",
                    Type = ArgumentOptions.OT_NONE,
                    Process = WriteHelp,
                    Description = "Displays the list of command line options with the internal options included"
                },
                new Option
                {
                    Name = "-?",
                    Type = ArgumentOptions.OT_NONE,
                    Process = WriteHelp
                },
                new Option
                {
                    Name = "/?",
                    Type = ArgumentOptions.OT_NONE,
                    Process = WriteHelp
                },
                new Option
                {
                    Name = "-help",
                    Type = ArgumentOptions.OT_NONE,
                    Process = WriteHelp,
                    Description = "Displays the list of command line options"
                },
                new Option
                {
                    Name = "-ver",
                    Type = ArgumentOptions.OT_NONE,
                    Process = (o, a) => {
                        Environment.Exit(0);
                        return true;
                    },
                    Description = "Displays version information"
                }
            };

            if (!Arguments.ProcessArguments(args, optionsSpecifications, "-", UnknownOption))
            {
                WriteMsg.WriteLine("Error: No input and/or output specified!", WriteMsg.MsgLevel.Error);
                WriteMsg.WriteLine("", WriteMsg.MsgLevel.Error);
                WriteHelp();
            }
        }

        private bool ProcessStringOption(Option option, string[] args)
        {
            string value = args[0];
            if (string.IsNullOrEmpty(value))
                return option.Needed == 0;

            switch (option.Name.ToLowerInvariant())
            {
                case "-stat":
                    Stat = value;
                    break;
                case "-input":
                    Input = value;
                    break;
                case "-output":
                    Output = value.TrimEnd('\\', '/') + Path.DirectorySeparatorChar;
                    if (!Directory.Exists(Output))
                        Directory.CreateDirectory(Output);
                    if (string.IsNullOrEmpty(FxCopOut))
                        FxCopOut = value;
                    if (string.IsNullOrEmpty(AnalyzersOut))
                        AnalyzersOut = value;
                    break;
                case "-limname":
                    LimName = value;
                    break;
                case "-outlist":
                    OutList = value;
                    break;
                case "-fxcopout":
                    FxCopOut = value.TrimEnd('\\', '/') + Path.DirectorySeparatorChar;
                    if (!Directory.Exists(FxCopOut))
                        Directory.CreateDirectory(FxCopOut);
                    break;
                case "-fxcoppath":
                    FxCopPath = value.TrimEnd('\\', '/') + (value.EndsWith(".exe") ? "" : Path.DirectorySeparatorChar.ToString());
                    break;
                case "-externalhardfilter":
                    ExternalHardFilter = value;
                    break;
                case "-externalsoftfilter":
                    ExternalSoftFilter = value;
                    break;
                case "-platform":
                    Platform = value;
                    break;
                case "-configuration":
                    Configuration = value;
                    break;
                case "-changepathfrom":
                    ChangePathFrom = value;
                    break;
                case "-changepathto":
                    ChangePathTo = value;
                    break;
                case "-analyzersout":
                    AnalyzersOut = value;
                    if (!Directory.Exists(AnalyzersOut))
                        Directory.CreateDirectory(AnalyzersOut);
                    break;
                default:
                    return false;
            }

            return true;
        }

        private bool ProcessBoolOption(Option option, string[] args)
        {
            bool value = option.Type == ArgumentOptions.OT_NONE || args.Length > 0 && args[0].ToLowerInvariant() == "true";
            switch (option.Name.ToLowerInvariant())
            {
                case "-buildproject":
                    BuildProject = value;
                    break;
                case "-runfxcop":
                    RunFxCop = value;
                    break;
                case "-dlimml":
                    DumpLimml = value;
                    break;
                case "-dcsharpml":
                    DumpCsharpml = value;
                    break;
                case "-runanalyzers":
                    RunAnalyzers = value;
                    break;
                case "-restorepackages":
                    RestorePackages = value;
                    break;
                default:
                    return false;
            }

            return true;
        }

        private bool ProcessCharOption(Option option, string[] args)
        {
            if (args[0].Length < 1 || args[0] != "\\t" && args[0].Length > 1)
                return false;
            char value = args[0] == "\\t" ? '\t' : args[0][0];
            switch (option.Name.ToLowerInvariant())
            {
                case "-csvseparator":
                    CsvSeparator = value;
                    break;
                case "-csvdecimalmark":
                    CsvDecimalMark = value;
                    break;
                default:
                    return false;
            }

            return true;
        }

        private bool WriteHelp(Option o, string[] args)
        {
            WriteHelp(o.Internal);
            return true;
        }

        private void WriteHelp(bool displayInternal = false)
        {
            WriteMsg.WriteLine("  Usage:", WriteMsg.MsgLevel.Silent);
            WriteMsg.WriteLine("", WriteMsg.MsgLevel.Silent);
            WriteMsg.WriteLine("    CSAN [options] -input:(file.cs|file.csproj|file.sln) -output:folder", WriteMsg.MsgLevel.Silent);
            WriteMsg.WriteLine("", WriteMsg.MsgLevel.Silent);
            Arguments.WriteHelp(optionsSpecifications, displayInternal); //if called from -helpi, then this property will be true, so internals will be written out as well
            Environment.Exit(1);
        }

        private void UnknownOption(string option)
        {
            WriteMsg.WriteLine("Error: Unrecognized option: " + option, WriteMsg.MsgLevel.Error);
            WriteMsg.WriteLine("", WriteMsg.MsgLevel.Error);
            WriteHelp();
        }
    }
}
