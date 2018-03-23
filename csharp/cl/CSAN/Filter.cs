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

using System.Collections.Generic;
using System.IO;
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
        protected List<FilterLine> Lines;

        protected enum LineKind { Include, Exclude, None }

        public Filter(string path)
        {
            Lines = new List<FilterLine>();
            StreamReader file = null;
            try
            {
                file = new StreamReader(path);
                string line;
                while ((line = file.ReadLine()) != null)
                {
                    if (line[0] == '-' || line[0] == '+')
                    {
                        Lines.Add(ProcessLine(line));
                    }
                }
            }
            catch(FileNotFoundException)
            {
                WriteMsg.WriteWithBreak("Warning: filter file \"{0}\" not found!", WriteMsg.MsgLevel.Warning, 0, path);
            }
            finally
            {
                file?.Dispose();
            }
            Lines.Reverse(); //we will check from the last line, and the first match determines if the file is needed or not
        }

        /// <summary>
        /// Determines if the <paramref name="input"/> is included or excluded based on the filter rules
        /// </summary>
        /// <param name="input">The path of a file or folder</param>
        public bool IsNecessaryToAnalyse(string input)
        {
            foreach (var line in Lines)
            {
                if (Regex.IsMatch(input, line.Expression, RegexOptions.IgnoreCase))
                    return line.OpenMethod == LineKind.Include;
            }
            return true;
        }

        private FilterLine ProcessLine(string line)
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
                    data.OpenMethod = LineKind.None;
                    break;
            }
            data.Expression = ProcessEscapingAnchors(line.Substring(1, line.Length - 1));
            return data;
        }

        /// <summary>
        /// Processes the \Q and \E anchors in regular expressions
        /// </summary>
        private static string ProcessEscapingAnchors(string regex)
        {
            if (string.IsNullOrEmpty(regex))
                return regex;

            var sb = new StringBuilder();
            int i = 0, j = 0;
            bool open = false;
            for (; i < regex.Length - 1; i++)
            {
                if (!open && regex.Substring(i, 2) == "\\Q") //i a \-re mutat
                {
                    open = true;
                    if (i != 0)
                        sb.Append(regex.Substring(j, i - j));
                    i++; //i a Q-ra mutat, majd a ciklus végén lépteti egyel a for
                    j = i + 1; //emiatt, a j-t i+1re állítjuk
                }
                else if (regex.Substring(i, 2) == "\\E")
                {
                    if (!open)
                        WriteMsg.WriteWithBreak("Warning: \\E anchor found without opening \\Q in one of the filter files. Ignoring it.", WriteMsg.MsgLevel.Warning);
                    else
                    {
                        open = false;
                        sb.Append(Regex.Escape(regex.Substring(j, i - j)));
                        i++;
                        j = i + 1;
                    }
                }
            }
            if (i != j)
            {
                if (open)
                    sb.Append(Regex.Escape(regex.Substring(j, i - j + 1)));
                else
                    sb.Append(regex.Substring(j, i - j + 1));
            }

            return sb.ToString();
        }

        protected class FilterLine
        {
            public LineKind OpenMethod { get; set; }
            public string Expression { get; set; }

        }
    }
}
