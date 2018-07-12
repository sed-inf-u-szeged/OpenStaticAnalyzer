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
using System.Linq;
using Columbus.CSAN.Commons;

namespace Columbus.CSAN
{
    static partial class MainProgram
    {
        #region Arguments callbacks
        private static bool ppStat(Option o, string[] args)
        {
            STAT = args[0];
            return true;
        }

        private static bool ppInput(Option o, string[] args)
        {
            INPUT = args[0];
            return true;
        }

        private static bool ppOutList(Option o, string[] args)
        {
            OUTLIST = args[0];
            return true;
        }

        private static bool ppLimName(Option o, string[] args)
        {
            LIMNAME = args[0];
            return true;
        }

        private static bool ppFxCopOut(Option o, string[] args)
        {
            FXCOPOUT = args[0];
            return true;
        }

        private static bool ppExternalHardFilter(Option o, string[] args)
        {
            EXTERNALHARDFILTER = args[0];
            if (!string.IsNullOrEmpty(EXTERNALHARDFILTER))
                MainDeclaration.Instance.HardFilter = new Filter(EXTERNALHARDFILTER);

            return true;
        }

        private static bool ppCsvDecimalMark(Option o, string[] args)
        {
            DECIMALSEPARATOR = args[0][0];
            return true;
        }

        private static bool ppCsvSeparator(Option o, string[] args)
        {
            CSVSEPARATOR = args[0][0];
            return true;
        }

        private static bool ppFxCopPath(Option o, string[] args)
        {
            FXCOPPATH = args[0];
            if (!string.IsNullOrEmpty(FXCOPPATH) && FXCOPPATH[FXCOPPATH.Length - 1] != Path.DirectorySeparatorChar)
                FXCOPPATH += Path.DirectorySeparatorChar;
            return true;
        }

        private static bool ppChangePathTo(Option o, string[] args)
        {
            MainDeclaration.Instance.ChangePathTo = (args[0].Last() == Path.DirectorySeparatorChar ? args[0] : args[0] + Path.DirectorySeparatorChar);
            return true;
        }

        private static bool ppChangePathFrom(Option o, string[] args)
        {
            //Escaping backslashes, making sure last character is a DirSeparator and adding ^ to beginning because it will be used in regex
            MainDeclaration.Instance.ChangePathFrom = "^" + (args[0].Last() == Path.DirectorySeparatorChar ? args[0] : args[0] + Path.DirectorySeparatorChar).Replace(Path.DirectorySeparatorChar.ToString(), "\\" + Path.DirectorySeparatorChar);
            return true;
        }

        private static bool ppOutputFolder(Option o, string[] args)
        {
            OUTPUT = args[0];
            if (OUTPUT[OUTPUT.Length - 1] != Path.DirectorySeparatorChar)
                OUTPUT += Path.DirectorySeparatorChar;
            if (!Directory.Exists(OUTPUT))
            {
                Directory.CreateDirectory(OUTPUT);
            }
            return true;
        }

        private static bool ppExternalSoftFilter(Option o, string[] args)
        {
            EXTERNALSOFTFILTER = args[0];
            if (!string.IsNullOrEmpty(EXTERNALSOFTFILTER))
                MainDeclaration.Instance.SoftFilter = new Filter(EXTERNALSOFTFILTER);
            return true;
        }

        private static bool ppCSSILDump(Option o, string[] args)
        {
            MainDeclaration.Instance.DumpCsharpml = true;
            return true;
        }

        private static bool ppLimMLDump(Option o, string[] args)
        {
            MainDeclaration.Instance.DumpLimml = true;
            return true;
        }

        private static bool ppBuildProject(Option o, string[] args)
        {
            if (args.Length > 0 && args[0] == "true")
                BUILDPROJECT = true;
            else
                BUILDPROJECT = false;
            return true;
        }

        private static bool ppRunFxCop(Option o, string[] args)
        {
            if (args.Length > 0 && args[0] == "true")
                RUNFXCOP = true;
            else
                RUNFXCOP = false;
            return true;
        }

        private static bool ppHelp(Option o, string[] args)
        {
            WriteMsg.WriteWithBreak("Usage:", WriteMsg.MsgLevel.Silent, 2);
            WriteMsg.WriteWithBreak("", WriteMsg.MsgLevel.Silent);
            WriteMsg.WriteWithBreak("CSAN [options] -input:(file.cs|file.csproj|file.sln) -output:folder", WriteMsg.MsgLevel.Silent, 4);
            WriteMsg.WriteWithBreak("", WriteMsg.MsgLevel.Silent);
            Arguments.WriteHelp(OPTIONS_OBJ, o.Internal); //if called from -helpi, then this property will be true, so internals will be written out as well
            Environment.Exit(1);
            return true;
        }

        private static bool ppVer(Option o, string[] args)
        {
            Environment.Exit(0);
            return true;
        }

        private static void ppUnknownOption(string o)
        {
            WriteMsg.WriteLine("Error: Unrecognized option: {0}\n", WriteMsg.MsgLevel.Error, o);
            ppHelp(default(Option), null);
        }

        private static bool ppConfiguration(Option o, string[] args)
        {
            CONFIGURATION = args[0];
            return true;
        }

        private static bool ppPlatform(Option o, string[] args)
        {
            PLATFORM = args[0];
            return true;
        }
        #endregion

        #region Arguments specification
        static Option[] OPTIONS_OBJ = {
            new Option()
            {
                Name                 = "-input",
                NumberOfParameters   = 1,
                ParameterName        = "file",
                Needed               = 1,
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppInput,
                Description          = "The input to analyze. A solution (.sln), project (.csproj), or source (.cs) file. This argument is required."
            },
            new Option()
            {
                Name                 = "-output",
                NumberOfParameters   = 1,
                ParameterName        = "directory",
                Needed               = 2,
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppOutputFolder,
                Description          = "The directory where result files will be created. This argument is required."
            },
            new Option()
            {
                Name                 = "-configuration",
                NumberOfParameters   = 1,
                ParameterName        = "configuration",
                Needed               = 0,
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppConfiguration,
                Description          = "The configuration of project file(s)."
            },
            new Option()
            {
                Name                 = "-platform",
                NumberOfParameters   = 1,
                ParameterName        = "platform",
                Needed               = 0,
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppPlatform,
                Description          = "The targeted platform."
            },
            new Option()
            {
                Internal             = true,
                Name                 = "-stat",
                NumberOfParameters   = 1,
                ParameterName        = "file",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppStat,
                Description          = "Create runtime statistics file."
            },
            new Option()
            {
                Name                 = "-outList",
                NumberOfParameters   = 1,
                ParameterName        = "file",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppOutList,
                Description          = "A list file where the generated ASG files' paths will be written out."
            },
            new Option()
            {
                Name                 = "-limName",
                NumberOfParameters   = 1,
                ParameterName        = "file",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppLimName,
                Description          = "Name of the LIM file to be created."
            },
            new Option()
            {
                Name                 = "-fxCopOut",
                NumberOfParameters   = 1,
                ParameterName        = "path",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppFxCopOut,
                Description          = "Output path for FxCop."
            },
            new Option()
            {
                Name                 = "-fxCopPath",
                NumberOfParameters   = 1,
                ParameterName        = "path",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppFxCopPath,
                Description          = "Path of FxCop."
            },
            new Option()
            {
                Name                 = "-csvseparator",
                NumberOfParameters   = 1,
                ParameterName        = "character",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppCsvSeparator,
                Description          = "Field separator character to be used in CSV outputs."
            },
            new Option()
            {
                Name                 = "-csvdecimalmark",
                NumberOfParameters   = 1,
                ParameterName        = "character",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppCsvDecimalMark,
                Description          = "Decimal separator to be used in CSV outputs."
            },
            new Option()
            {
                Name                 = "-externalHardFilter",
                NumberOfParameters   = 1,
                ParameterName        = "file",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppExternalHardFilter,
                Description          = "External hardfilter file. See the documentation for usage."
            },
            new Option()
            {
                Name                 = "-externalSoftFilter",
                NumberOfParameters   = 1,
                ParameterName        = "file",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppExternalSoftFilter,
                Description          = "External softfilter file. See the documentation for usage."
            },
            new Option()
            {
                Internal             = true,
                Name                 = "-buildProject",
                NumberOfParameters   = 1,
                ParameterName        = "(true|false)",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppBuildProject,
                Description          = "Try to build the project using Roslyn Emit API. Default is false."
            },
            new Option()
            {
                Name                 = "-runFxCop",
                NumberOfParameters   = 1,
                ParameterName        = "(true|false)",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppRunFxCop,
                Description          = "Try to run FxCop analysis. If -fxCopPath is not given, we will search through installed VisualStudio folders."
            },
            new Option()
            {
                Internal             = true,
                Name                 = "-changepathfrom",
                NumberOfParameters   = 1,
                ParameterName        = "path",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppChangePathFrom,
                Description          = "If given, this subpath will be replaced with -changepathto in all source positions, enabling you to write relative paths into ASGs."
            },
            new Option()
            {
                Internal             = true,
                Name                 = "-changepathto",
                NumberOfParameters   = 1,
                ParameterName        = "path",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = ppChangePathTo,
                Description          = "If used with -changepathfrom, this will be the replacement string in paths."
            },
            new Option()
            {
                Name                 = "-dlimml",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = ppLimMLDump,
                Description          = "Make XML dump from LIM ASG."
            },
            new Option()
            {
                Name                 = "-dcsharpml",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = ppCSSILDump,
                Description          = "Make XML dump from C# ASGs."
            },
            new Option()
            {
                Internal             = true,
                Name                 = "-developer",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = null,                                                                        //processed separately
                Description          = "Does nothing currently."
            },
            new Option()
            {
                Name                 = "-ml",
                NumberOfParameters   = 1,
                ParameterName        = "level",
                Type                 = ArgumentOptions.OT_WC | ArgumentOptions.OT_WE,
                Process              = null,                                                                        //processed separately
                Description          = "Sets the message level of the program\n" +
                                       "0 (silent)  does not write any message\n" +
                                       "1 (error)   writes out error messages only\n" +
                                       "2 (warning) writes out error and warning messages\n" +
                                       "3 (normal)  writes out every normal informational messages as well - this is the default"
            },
            new Option()
            {
                Internal             = true,
                Name                 = "-helpi",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = ppHelp,
                Description          = "Displays the list of command line options with the internal options"
            },
            new Option()
            {
                Name                 = "-?",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = ppHelp
            },
            new Option()
            {
                Name                 = "/?",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = ppHelp
            },
            new Option()
            {
                Name                 = "-help",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = ppHelp,
                Description          = "Displays the list of command line options"
            },
            new Option()
            {
                Name                 = "-ver",
                Type                 = ArgumentOptions.OT_NONE,
                Process              = ppVer,
                Description          = "Displays version information"
            }
        };
        #endregion
    }
}
