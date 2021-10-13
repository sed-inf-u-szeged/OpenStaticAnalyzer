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
            message += args.Length > 0 ? string.Format(format, args) : format;
            message += NewLine;
            Write(message);
        }

        /// <summary>
        /// Writes <paramref name="format"/> to the OutputStream with <paramref name="indent"/> characters
        /// of IndentationChars before and broke to new line after MaxLineLength characters.
        /// Format is processed by string.Format() with <paramref name="args"/> passed to it.
        /// </summary>
        /// <param name="format">The message/format string for string.Format().</param>
        /// <param name="level">The level of the message.</param>
        /// <param name="indent">Number of indentation to be inserted before every line.</param>
        /// <param name="args">List of parameters to be inserted in <paramref name="format"/> by string.Format()</param>
        public static void WriteWithBreak(string format, MsgLevel level = MsgLevel.Normal, int indent = 0, params object[] args)
        {
            if (MessageLevel == MsgLevel.Silent || level > MessageLevel || string.IsNullOrWhiteSpace(format))
                return;

            string indentStr = new string(IndentationChar, indent);
            string message = args.Length > 0 ? string.Format(format, args) : format;
            if (message.Length + indent <= MaxLineLength && !message.Contains("\n"))
            {
                Write(indentStr + message);
                return;
            }

            bool first = true;
            foreach (var line in message.Replace("\r", "").Split('\n'))
            {
                if (!first)
                    Write(NewLine);
                first = false;
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
            }
        }

        /// <summary>
        /// Writes <paramref name="format"/> to the OutputStream with <paramref name="indent"/> characters
        /// of IndentationChars before and broke to new line after MaxLineLength characters.
        /// Format is processed by string.Format() with <paramref name="args"/> passed to it.
        /// The message is terminated by a newline.
        /// </summary>
        /// <param name="format">The message/format string for string.Format().</param>
        /// <param name="level">The level of the message.</param>
        /// <param name="indent">Number of indentation to be inserted before every line.</param>
        /// <param name="args">List of parameters to be inserted in <paramref name="format"/> by string.Format()</param>
        public static void WriteLineWithBreak(string format = "", MsgLevel level = MsgLevel.Normal, int indent = 0, params object[] args)
        {
            if (MessageLevel == MsgLevel.Silent || level > MessageLevel)
                return;

            WriteWithBreak(format, level, indent, args);

            Write(NewLine);
        }

        /// <summary>
        /// Writes <paramref name="message"/> to the output stream using the set encoding
        /// </summary>
        public static void Write(string message, WriteMsg.MsgLevel level = MsgLevel.Normal)
        {
            if (MessageLevel == MsgLevel.Silent || level > MessageLevel)
                return;

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

        public class ProgressDisplay
        {
            private bool first;
            private readonly int width;
            private readonly string resetString;
            private readonly bool disabled;

            public int Current { get; set; }

            public int Max { get; }

            public bool ShowPercentage { get; }

            public ProgressDisplay(int max, bool showPercentage = false, MsgLevel level = MsgLevel.Normal)
            {
                Max = max;
                Current = 0;
                width = (int)Math.Log10(max) + 1 + (showPercentage ? 5 : 0);
                resetString = new string('\u0008', width * 2 + 1);
                disabled = Console.IsOutputRedirected || MessageLevel == MsgLevel.Silent || level > MessageLevel;
                first = true;
                ShowPercentage = showPercentage;
            }

            public void AdvanceAndPrint()
            {
                ++Current;
                Print();
            }

            public void Print()
            {
                if (disabled)
                    return;
                if (!first)
                    Write(resetString);
                first = false;

                Write(string.Format($"{{0,{width}}}/{{1}}", Current, Max));  //$"{current,width}/{Max}"));
                if (ShowPercentage)
                    Write($" {(double)Current / Max,4:P0}");
            }
        }
    }
}
