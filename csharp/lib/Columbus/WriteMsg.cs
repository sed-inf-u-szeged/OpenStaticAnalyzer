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
using System.IO;

namespace Columbus
{
    /// <summary>
    /// Class to write out every kind of messages.
    /// </summary>
    public static class WriteMsg
    {
        /// <summary>
        /// Possible levels of messages
        /// </summary>
        public enum MsgLevel : int
        {
            /// <summary>
            /// Do not write out any message.
            /// </summary>
            Silent,
            /// <summary>
            /// Only error messages can be written out. 
            /// </summary>
            Error,
            /// <summary>
            /// Error and warning messages can be written out.
            /// </summary>
            Warning,
            /// <summary>
            /// All but debug message are written out.
            /// </summary>
            Normal,
            /// <summary>
            /// Besides the error, warning and normal messages the debug level 1 messages are also written out.
            /// </summary>
            Debug,
            /// <summary>
            /// Besides the error, warning and normal messages the debug level 2 messages are also written out.
            /// </summary>
            DDebug,
            /// <summary>
            /// Besides the error, warning and normal messages the debug level 3 messages are also written out.
            /// </summary>
            DDDebug,
            /// <summary>
            /// Besides the error, warning and normal messages the debug level 4 messages are also written out.
            /// </summary>
            DDDDebug
        }

        private static MsgLevel messageLevel = MsgLevel.Normal;        
        private static bool developerMode;

        /// <summary>
        /// The stream to write to
        /// </summary>
        public static Stream OutputStream = Console.OpenStandardOutput();

        /// <summary>
        /// The encoding to use when writing to OutputStream
        /// </summary>
        public static System.Text.Encoding OutputEncoding = Console.OutputEncoding;

        /// <summary>
        /// If set to true, the output stream will be flushed after every write call
        /// </summary>
        public static bool AutomaticFlush = false;

        /// <summary>
        /// If set to false, MessageLevel will be locked
        /// </summary>
        public static bool MlCanBeChanged = true;

        /// <summary>
        /// If set to true, MessageLevels will be displayed in front of every message
        /// </summary>
        public static bool DisplayMessageLevel = false;

        /// <summary>
        /// If set to true, a timestamp will be displayed in front of every message
        /// </summary>
        public static bool DisplayTime = false;

        /// <summary>
        /// The maximum number of characters in a line when writing with auto line break
        /// </summary>
        public static int MaxLineLength = 80;

        /// <summary>
        /// The character to use for indentation
        /// </summary>
        public static char IndentationChar = ' ';

        /// <summary>
        /// Line separator
        /// </summary>
        public static string NewLine = Environment.NewLine;

        /// <summary>
        /// The current message level. Any message specified with greater level will not be written out.
        /// </summary>
        public static MsgLevel MessageLevel
        {
            get { return messageLevel; }
            set
            {
                if (MlCanBeChanged)
                    messageLevel = value; 
            }
        }

        /// <summary>
        /// Processes -ml, -developer and -silent arguments
        /// </summary>
        /// <param name="argv">Arguments passed to the program</param>
        public static void Initialize(string[] argv)
        {
            foreach(var arg in argv)
            {
                if(arg == "-silent")
                {
                    messageLevel = MsgLevel.Error;
                    MlCanBeChanged = false;
                    return;
                }
            }

            foreach(var arg in argv)
            {
                if (arg == "-developer")
                    developerMode = true;
            }
            foreach(var arg in argv)
            {
                if(arg.StartsWith("-ml") && arg.Length > 4) //-ml:NUM
                {
                    int ml;
                    if (!int.TryParse(arg.Substring(4), out ml))
                        continue;

                    MessageLevel = (MsgLevel)ml;
                    if (!developerMode && MessageLevel > MsgLevel.Normal)
                        MessageLevel = MsgLevel.Normal;
					break;
                }
            }
        }

        /// <summary>
        /// Writes message to the given output. Terminated by NewLine
        /// </summary>
        /// <param name="level">The level of the message.</param>
        /// <param name="format">The message/format string for string.Format().</param>
        /// <param name="args">List of parameters to be inserted in <paramref name="format"/> by string.Format()</param>
        public static void WriteLine(string format = "", MsgLevel level = MsgLevel.Normal, params object[] args)
        {
            if (MessageLevel == MsgLevel.Silent || level > MessageLevel)
                return;
            if(string.IsNullOrWhiteSpace(format))
            {
                Write(NewLine);
                return;
            }

            string message = string.Empty;
            if (DisplayTime)
                message += DateTime.Now.ToShortTimeString();
            if (DisplayMessageLevel)
                message += level.ToDisplayString();
            message += string.Format(format, args);
            message += NewLine;
            Write(message);
        }

        /// <summary>
        /// Writes <paramref name="format"/> to the OutputStream with <paramref name="indent"/> characters
        /// of IndentationChars before and broke to new line after MaxLineLength characters.
        /// Format is processed by string.Format() with <paramref name="args"/> passed to it.
        /// The message is always terminated by a newline.
        /// </summary>
        /// <param name="level">The level of the message.</param>
        /// <param name="format">The message/format string for string.Format().</param>
        /// <param name="indent">Number of indentation to be inserted before every line.</param>
        /// <param name="args">List of parameters to be inserted in <paramref name="format"/> by string.Format()</param>
        public static void WriteWithBreak(string format = "", MsgLevel level = MsgLevel.Normal, int indent = 0, params object[] args)
        {
            if (MessageLevel == MsgLevel.Silent || level > MessageLevel)
                return;
            if (string.IsNullOrWhiteSpace(format))
            {
                Write(NewLine);
                return;
            }

            string message = string.Format(format, args);
            if (message.Length + indent <= MaxLineLength && !message.Contains("\n"))
            {
                if (indent > 0)
                    Write(new string(IndentationChar, indent) + message + NewLine);
                else
                    Write(message + NewLine);
                return;
            }

            string indentStr = new string(IndentationChar, indent);
            foreach (var line in message.Replace("\r", "").Split('\n'))
            {
                int currentLength = 0;                
                if (indent > 0)
                {
                    Write(indentStr);
                    currentLength += indent;
                }
                foreach (var word in line.Split(' '))
                {
                    if (currentLength + word.Length + 1 <= MaxLineLength)
                    {
                        Write(word + " ");
                        currentLength += word.Length + 1;
                    }
                    else
                    {
                        currentLength = 0;
                        Write(NewLine);
                        if (indent > 0)
                        {
                            Write(indentStr);
                            currentLength += indent;
                        }
                        Write(word + " ");
                        currentLength += word.Length + 1;
                    }
                }
                Write(NewLine);
            }
        }

        /// <summary>
        /// Writes <paramref name="message"/> to the output stream using the set encoding
        /// </summary>
        private static void Write(string message)
        {
            var buffer = OutputEncoding.GetBytes(message);
            OutputStream.Write(buffer, 0, buffer.Length);
            if (AutomaticFlush)
                OutputStream.Flush();
        }

        private static string ToDisplayString(this MsgLevel level)
        {
            switch(level)
            {
                case MsgLevel.Error:
                    return "ERROR: ";
                case MsgLevel.Warning:
                    return "Warning: ";
                case MsgLevel.Normal:
                    return "Info: ";
                case MsgLevel.Debug:
                    return "Debug L1: ";
                case MsgLevel.DDebug:
                    return "Debug L2: ";
                case MsgLevel.DDDebug:
                    return "Debug L3: ";
                case MsgLevel.DDDDebug:
                    return "Debug L4: ";
                default:
                    return string.Empty;
            }
        }
    }
}
