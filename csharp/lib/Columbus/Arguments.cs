using System;
using System.Collections.Generic;
using System.Linq;
using static Columbus.Common;

namespace Columbus
{
    public static class Arguments
    {
        public static bool ProcessArguments(string[] argv, Option[] options, string optionPrefixes, DelegateOption unrecOption)
        {
            List<Option> defCallbacks = new List<Option>();
            var neededOptions = new Dictionary<int, ICollection<Option>>();

            if (options == null)
            {
                WriteMsg.WriteLine("Error: No option given", WriteMsg.MsgLevel.Error);
                return false;
            }

            foreach (var option in options)
            {
                if (option.Needed <= 0)
                    continue;

                ICollection<Option> list;
                if (neededOptions.TryGetValue(option.Needed, out list))
                    list.Add(option);
                else
                    neededOptions.Add(option.Needed, new List<Option> {option});
            }

            for (int pnum = 0; pnum < argv.Length; ++pnum)
            {
                Option? found_option = null;

                foreach (Option opt in options)
                {
                    bool match = false;
                    if (((opt.Type & ArgumentOptions.OT_PREFIX) != ArgumentOptions.OT_NONE) && (opt.Type & (ArgumentOptions.OT_WOS | ArgumentOptions.OT_WC | ArgumentOptions.OT_WE)) == ArgumentOptions.OT_NONE)
                    {
                        if (opt.Name.ToLower().IndexOf(argv[pnum].ToLower()) == 0) match = true;
                    }
                    else
                    {
                        if (argv[pnum].ToLower().IndexOf(opt.Name.ToLower()) == 0)
                        {
                            int oplen = opt.Name.Length;
                            try
                            {
                                if (
                                    (argv[pnum].Length == oplen && (((opt.NumberOfParameters == 0 && (opt.Type & ArgumentOptions.OT_OPTION_FILE) == ArgumentOptions.OT_NONE) || (opt.NumberOfParameters == 0 && (opt.Type & ArgumentOptions.OT_WS) != ArgumentOptions.OT_NONE && (opt.Type & ArgumentOptions.OT_DEFAULT) == ArgumentOptions.OT_NONE)))) ||
                                    (argv[pnum].Length == oplen && opt.NumberOfParameters == 1 && (opt.Type & ArgumentOptions.OT_DEFAULT) != ArgumentOptions.OT_NONE && (opt.Type & ArgumentOptions.OT_WS) == ArgumentOptions.OT_NONE && (opt.Type & ArgumentOptions.OT_OPTION_FILE) == ArgumentOptions.OT_NONE && (opt.Type & ArgumentOptions.OT_WOS) == ArgumentOptions.OT_NONE) ||
                                    (argv[pnum].Length != oplen && opt.NumberOfParameters == 1 && (opt.Type & ArgumentOptions.OT_WOS) != ArgumentOptions.OT_NONE && (opt.Type & ArgumentOptions.OT_DEFAULT) == ArgumentOptions.OT_NONE) ||
                                    (argv[pnum][oplen] == '=' && opt.NumberOfParameters == 1 && (opt.Type & ArgumentOptions.OT_WE) != ArgumentOptions.OT_NONE) ||
                                    (argv[pnum][oplen] == ':' && opt.NumberOfParameters == 1 && (opt.Type & ArgumentOptions.OT_WC) != ArgumentOptions.OT_NONE))
                                {
                                    match = true;
                                }
                            }
                            catch (ArgumentOutOfRangeException) { }
                        }
                    }

                    if (match)
                    {
                        if (found_option != null)
                        {
                            WriteMsg.WriteLine("Error: Parameter {0} specified more than once.", WriteMsg.MsgLevel.Error, opt);
                            return false;
                        }
                        found_option = opt;
                    }
                }

                if (found_option != null)
                {
                    if (found_option.Value.NumberOfParameters == 0)
                    {
                        if (found_option.Value.Process != null && !found_option.Value.Process(found_option.Value, null))
                        {
                            WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                            return false;
                        }
                    }
                    else if (found_option.Value.NumberOfParameters == 1)
                    {
                        if ((found_option.Value.Type & ArgumentOptions.OT_PREFIX) != ArgumentOptions.OT_NONE)
                        {
                            if (pnum + 1 >= argv.Length)
                            {
                                WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                                return false;
                            }

                            if (!processOptionFile(options, optionPrefixes, unrecOption, found_option.Value, new[] { argv[pnum + 1] }))
                            {
                                WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                                return false;
                            }
                            pnum++;
                        }
                        else if ((found_option.Value.Type & ArgumentOptions.OT_DEFAULT) != ArgumentOptions.OT_NONE)
                        {
                            bool needProcess = true;
                            int oplen = found_option.Value.Name.Length;
                            string prm = string.Empty;

                            if (argv[pnum][oplen] == '=')         //  -option=value (OT_WE)
                                prm = argv[pnum].Substring(oplen + 1, argv[pnum].Length - oplen - 1);
                            else if (argv[pnum][oplen] == ':')    //  -option:value (OT_WC)
                                prm = argv[pnum].Substring(oplen + 1, argv[pnum].Length - oplen - 1);
                            else
                            {

                                if (found_option.Value.DefaultProcess != null)
                                {
                                    defCallbacks.Add(found_option.Value);
                                    needProcess = false;
                                }
                                else
                                {
                                    WriteMsg.WriteLine("Error: The default value of '{0}' option is used but it does not have default value", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                                    return false;
                                }
                                prm = argv[pnum + 1];
                                pnum++;
                            }
                            if (needProcess)
                            {
                                if (!processOptionFile(options, optionPrefixes, unrecOption, found_option.Value, new[] { prm }))
                                {
                                    WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                                    return false;
                                }
                            }
                        }
                        else
                        {
                            int oplen = found_option.Value.Name.Length;
                            string prm = string.Empty;

                            if (argv[pnum][oplen] == '=')         //  -option=value (OT_WE)
                                prm = argv[pnum].Substring(oplen + 1, argv[pnum].Length - oplen - 1);
                            else if (argv[pnum][oplen] == ':')    //  -option:value (OT_WC)
                                prm = argv[pnum].Substring(oplen + 1, argv[pnum].Length - oplen - 1);
                            else if (argv[pnum][oplen] > 0)       //  -optionvalue (OT_WOS)
                                prm = argv[pnum].Substring(oplen, argv[pnum].Length - oplen);
                            else
                            {                                     // -option value (OT_WS)
                                if (pnum + 1 >= argv.Length)
                                {
                                    WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                                    return false;
                                }
                                prm = argv[pnum + 1];
                                pnum++;
                            }

                            if (!processOptionFile(options, optionPrefixes, unrecOption, found_option.Value, new[] { prm }))
                            {
                                WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                                return false;
                            }
                        }
                    }
                    else if (found_option.Value.NumberOfParameters > 1)
                    {
                        if (pnum + found_option.Value.NumberOfParameters >= argv.Length)
                        {
                            WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                            return false;
                        }

                        if (found_option.Value.Process != null && !found_option.Value.Process(found_option.Value, argv[pnum + 1].Split(' ')))
                        {
                            WriteMsg.WriteLine("Error: Cannot process the '{0}' option", WriteMsg.MsgLevel.Error, found_option.Value.Name);
                            return false;
                        }

                        pnum += found_option.Value.NumberOfParameters;
                    }

                    if (found_option.Value.Needed > 0)
                        neededOptions.Remove(found_option.Value.Needed);
                }
                else
                {
                    if (Strchr(optionPrefixes, argv[pnum][0]) != null)
                    {
                        if (unrecOption != null)
                        {
                            unrecOption(argv[pnum]);
                        }
                        else
                        {
                            WriteMsg.WriteLine("Warning: Unrecognized parameter: '{0}'", WriteMsg.MsgLevel.Warning, argv[pnum]);
                        }
                    }
                }
            }

            foreach (var opt in defCallbacks)
            {
                opt.DefaultProcess(opt);
            }

            foreach (var pair in neededOptions)
            {
                if (pair.Value.Count > 1)
                    WriteMsg.WriteLine($"Error: One of the options {string.Join(", ", pair.Value)} should be provided.", WriteMsg.MsgLevel.Error);
                else
                    WriteMsg.WriteLine($"Error: Option {pair.Value.First()} is needed", WriteMsg.MsgLevel.Error);
            }

            return neededOptions.Count == 0;
        }

        public static void WriteHelp(Option[] options, bool displayInternal = false)
        {
            WriteMsg.WriteLine("", WriteMsg.MsgLevel.Silent);
            WriteMsg.WriteLine("  Options:", WriteMsg.MsgLevel.Silent);
            WriteMsg.WriteLine(Environment.NewLine, WriteMsg.MsgLevel.Silent);
            foreach (var opt in options)
            {
                if (opt.Internal && !displayInternal)
                    continue;                

                if (opt.Type == ArgumentOptions.OT_NONE)
                    WriteMsg.WriteLine("  {0}", WriteMsg.MsgLevel.Silent, opt.Name);
                else
                {
                    if ((opt.Type & ArgumentOptions.OT_WE) != 0 || opt.Type == ArgumentOptions.OT_DEFAULT)
                        WriteMsg.WriteLine("  {0}={1}", WriteMsg.MsgLevel.Silent, opt.Name, opt.ParameterName);
                    if ((opt.Type & ArgumentOptions.OT_WC) != 0 || opt.Type == ArgumentOptions.OT_DEFAULT)
                        WriteMsg.WriteLine("  {0}:{1}", WriteMsg.MsgLevel.Silent, opt.Name, opt.ParameterName);                    
                    if ((opt.Type & ArgumentOptions.OT_WOS) != 0)
                        WriteMsg.WriteLine("  {0}{1}", WriteMsg.MsgLevel.Silent, opt.Name, opt.ParameterName);
                    if ((opt.Type & ArgumentOptions.OT_WS) != 0)
                        WriteMsg.WriteLine("  {0} {1}", WriteMsg.MsgLevel.Silent, opt.Name, opt.ParameterName);
                }
                if (!string.IsNullOrEmpty(opt.Description))
                {
                    WriteMsg.WriteLine("    " + opt.Description, WriteMsg.MsgLevel.Silent);
                    WriteMsg.WriteLine("", WriteMsg.MsgLevel.Silent);
                }
            }
        }

        private static int? Strchr(string originalString, char charToSearch)
        {
            int? found = originalString.IndexOf(charToSearch);
            return found > -1 ? found : null;
        }

        private static bool processOptionFile(Option[] options, string optionPrefixes, DelegateOption unrecOption, Option found_option, string[] found_option_args)
        {
            if ((found_option.Type & ArgumentOptions.OT_OPTION_FILE) != ArgumentOptions.OT_NONE)
            {
                bool ret = true;
                if (found_option.Process != null)
                    return found_option.Process(found_option, found_option_args);

                if (ret)
                {
                    List<string> @params = new List<string>();
                    string param = ""; ;
                    int qmc = 0;
                    string[] lines = System.IO.File.ReadAllLines(found_option_args[0]);
                    foreach (var line in lines)
                    {
                        if (qmc % 2 != 0)
                            param += " ";
                        qmc += countQuotationMarks(line);
                        param += line;

                        if (qmc % 2 == 0)
                        {
                            @params.Add(removeQuotationMarks(param));

                            qmc = 0;
                            param = "";
                        }
                        if (qmc % 2 != 0)
                            @params.Add(removeQuotationMarks(param));
                    }

                    return ProcessArguments(@params.ToArray(), options, optionPrefixes, unrecOption);
                }
            }
            else
            {
                if (found_option.Process != null) return found_option.Process(found_option, found_option_args);
            }

            return true;
        }

        private static string removeQuotationMarks(string param)
        {
            throw new NotImplementedException();
        }

        private static int countQuotationMarks(string line)
        {
            throw new NotImplementedException();
        }
    }
}
