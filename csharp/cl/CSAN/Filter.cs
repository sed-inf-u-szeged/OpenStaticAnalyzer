using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Columbus.CSAN
{
    /// <summary>
    /// Filter file specified with relative or absolute path, to filter out certain files from the 
    /// analysis based on their path names. Filtered files will not appear in the results. 
    /// The filter file is a simple text file containing lines starting with ’+’ or ’-’ characters 
    /// followed by a regular expression. During the analysis, each input file will be
    /// checked for these expressions. If the first character of the last matching expression 
    /// is ’-’, then the given file will be excluded from the analysis. If the first character of the
    /// last matching expression is ’+’, or there is no matching expression, then the file will 
    /// be analyzed. A line starting with a different character than ’-’ or ’+’ will be ignored.
    /// </summary>
    class Filter
    {
        /// <summary>
        /// The FilterLines in REVERSED order to speed up pattern matching a little.
        /// </summary>
        private readonly List<FilterLine> lines = new List<FilterLine>();

        private readonly Dictionary<string, bool> cache = new Dictionary<string, bool>();

        public Filter(string path)
        {
            if (!string.IsNullOrWhiteSpace(path))
                ProcessFile(path);
        }

        private void ProcessFile(string path)
        {
            StreamReader file = null;
            try
            {
                file = new StreamReader(path);
                int lineNo = 1;
                for (string line; (line = file.ReadLine()) != null; lineNo++)
                {
                    if (string.IsNullOrWhiteSpace(line))
                        continue;

                    if (line[0] == '-' || line[0] == '+')
                    {
                        if (line.Length < 2)
                        {
                            WriteMsg.WriteLine($"Warning: empty filter line at \"{path}\":{lineNo}");
                            continue;
                        }

                        lines.Add(ProcessLine(line));
                    }
                    else if (line[0] != '#')
                    {
                        WriteMsg.WriteLine(
                            $"Warning: skipped malformed filter line at \"{path}\":{lineNo}. The first character of every line should either be + - or #.",
                            WriteMsg.MsgLevel.Warning);
                    }
                }
            }
            catch (FileNotFoundException)
            {
                WriteMsg.WriteLine("Warning: filter file \"{0}\" not found!", WriteMsg.MsgLevel.Warning, path); // TODO shouldn't this be fatal and throw?
            }
            finally
            {
                file?.Dispose();
            }

            lines.Reverse(); //we will check from the last line, and the first match determines if the file is needed or not
        }

        /// <summary>
        /// Determines if the <paramref name="input"/> is included or excluded based on the filter rules
        /// </summary>
        /// <param name="input">The path of a file or folder</param>
        public bool IsNecessaryToAnalyse(string input)
        {
            if (string.IsNullOrEmpty(input))
                return true;
            if (cache.TryGetValue(input, out bool result))
                return result;

            result = true;
            foreach (var line in lines)
            {
                if (line.Expression.IsMatch(input))
                {
                    result = line.OpenMethod == LineKind.Include;
                    break;
                }
            }

            return cache[input] = result;
        }

        private static FilterLine ProcessLine(string line)
        {
            FilterLine data = new FilterLine();
            switch (line[0])
            {
                case '-':
                    data.OpenMethod = LineKind.Exclude;
                    break;
                case '+':
                    data.OpenMethod = LineKind.Include;
                    break;
                default:
                    throw new ArgumentException("A filter line must start with a - or +", nameof(line));
            }
            data.Expression = ProcessRegexPattern(line.Substring(1, line.Length - 1));
            return data;
        }

        /// <summary>
        /// Processes the \Q and \E tags providing Quoted Literals. This implementation aims to be on-par with Java's.
        /// After a \Q opening tag everything is treated literally until a closing \E or the end of the string.
        /// </summary>
        /// <remarks>
        /// <p>You cannot have \E or any other escape sequence appear inside a quoted literal, \Q\\E\E only matches the
        /// \ character, nothing else, \Q\\E also matches a single \ character, \Q\\\E matches \\, etc.</p>
        /// <p>A closing \E without an opening \Q is dropped, so it does not match anything, but a warning is issued.</p>
        /// </remarks>
        /// <param name="pattern">An otherwise C# compatible regular expression possibly containing \Q and \E tags</param>
        /// <returns>A constructed <see cref="Regex"/> object with \Q and \E tags stripped, the substrings inside them escaped.</returns>
        private static Regex ProcessRegexPattern(string pattern)
        {
            if (string.IsNullOrEmpty(pattern))
                throw new ArgumentException($"{nameof(pattern)} should not be empty");

            var sb = new StringBuilder();
            int i = 0, j = 0;
            bool open = false;
            bool oddBackslashes = false;

            for (; i < pattern.Length - 1; i++)
            {
                if (pattern[i] == '\\')
                    oddBackslashes = !oddBackslashes;
                else
                    oddBackslashes = false;

                bool atQ = pattern.Substring(i, 2) == @"\Q";
                bool atE = pattern.Substring(i, 2) == @"\E";

                if (!open && oddBackslashes && atQ) // i points to the \
                {
                    open = true;
                    if (i != 0)
                        sb.Append(pattern.Substring(j, i - j));
                    i++;       // i points to Q, then at the end of the loop it is incremented one more time
                    j = i + 1; // thus j has to be i+1
                    oddBackslashes = false;
                }
                else if (open && atE)
                {
                    open = false;
                    sb.Append(Regex.Escape(pattern.Substring(j, i - j)));
                    i++;
                    j = i + 1;
                    oddBackslashes = false;
                }
                else if (!open && oddBackslashes && atE)
                {
                    WriteMsg.WriteLine(@"Warning: \E anchor found without opening \Q which matches nothing.", WriteMsg.MsgLevel.Warning);
                    if (i != 0)
                        sb.Append(pattern.Substring(j, i - j));
                    i++;       // i points to E, then at the end of the loop it is incremented one more time
                    j = i + 1; // thus j has to be i+1
                    oddBackslashes = false;
                }
            }

            if (i != j)
            {
                var substr = pattern.Substring(j, i - j + 1);
                sb.Append(open ? Regex.Escape(substr) : substr); // It is valid for \Q to not have a closing \E, then the whole regex is quoted
            }

            return new Regex(sb.ToString(), RegexOptions.IgnoreCase); // TODO catch ArgumentException, throw something more informative
        }

        private enum LineKind
        {
            Include,
            Exclude
        }

        private struct FilterLine
        {
            public LineKind OpenMethod { get; set; }
            public Regex Expression { get; set; }
        }
    }
}
