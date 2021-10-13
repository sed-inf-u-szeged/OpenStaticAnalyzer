using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace Columbus
{
    public static partial class Common
    {
        /// <summary>
        /// Object is a number
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static bool IsNumber(this object value)
        {
            return value is sbyte
                    || value is byte
                    || value is short
                    || value is ushort
                    || value is int
                    || value is uint
                    || value is long
                    || value is ulong
                    || value is float
                    || value is double
                    || value is decimal;
        }

        public static bool EqualsAny(this object value, params object[] others)
        {
            return others.Contains(value);
        }

        public static void WaitAll(this IEnumerable<Task> tasks)
        {
            foreach (Task task in tasks)
            {
                task.Wait();
            }
        }

        public static void LogException(Exception e)
        {
            WriteMsg.WriteLine("", WriteMsg.MsgLevel.Error);
            WriteMsg.WriteLine("EXCEPTION: {0}", WriteMsg.MsgLevel.Error, e.GetType());
            WriteMsg.WriteLine(e.Message, WriteMsg.MsgLevel.Error);
            WriteMsg.WriteLine(e.StackTrace, WriteMsg.MsgLevel.Debug);

            if (e is AggregateException)
            {
                LogException((AggregateException)e);
            }

            if (e is ReflectionTypeLoadException)
            {
                LogException((ReflectionTypeLoadException)e);
            }
        }

        private static void LogException(AggregateException e)
        {
            WriteMsg.WriteLine("", WriteMsg.MsgLevel.Error);
            if (e.InnerExceptions.Count > 1)
            {
                foreach (var ie in e.InnerExceptions)
                {
                    LogException(ie);
                    WriteMsg.WriteLine("", WriteMsg.MsgLevel.Error);
                }
            }
            else if (e.InnerException != null)
            {
                LogException(e.InnerException);
            }
        }

        private static void LogException(ReflectionTypeLoadException e)
        {
            foreach (var le in e.LoaderExceptions)
            {
                LogException(le);
            }
        }

        public static void LogProgramInfo()
        {
            LogProductInfo();
            LogFrameworkInfo();
            LogEnvironmentInfo();
        }

        private static void LogProductInfo()
        {
            var assembly = Assembly.GetEntryAssembly();
            if (assembly == null)
            {
                WriteMsg.WriteLine("Could not determine product information, because Assembly.GetEntryAssembly() returned null.", WriteMsg.MsgLevel.Warning);
                return;
            }

            var versionInfo = FileVersionInfo.GetVersionInfo(assembly.Location);
            // Getting the Title property from the csproj as a AssemblyTitleAttribute did not work here.
            WriteMsg.WriteLine($"{assembly.GetCustomAttribute<AssemblyTitleAttribute>().Title} {versionInfo.ProductVersion} ({Common.Revision}) - {versionInfo.LegalCopyright}");
        }

        private static void LogFrameworkInfo()
        {
            var setupInformation = typeof(AppDomain).GetProperty("SetupInformation")?.GetValue(AppDomain.CurrentDomain);
            var targetFrameworkName = setupInformation?.GetType().GetProperty("TargetFrameworkName")?.GetValue(setupInformation);
            var frameworkDescription = typeof(RuntimeInformation).GetProperty("FrameworkDescription")?.GetValue(null)?.ToString(); // Only exists from .NET 4.7.1, Core and Standard

            WriteMsg.WriteLine($"Targeted framework name: {targetFrameworkName}", WriteMsg.MsgLevel.Debug);
            WriteMsg.WriteLine($"Running on CLR {RuntimeEnvironment.GetSystemVersion()}", WriteMsg.MsgLevel.Debug); // Not really useful
            if (frameworkDescription != null)
                WriteMsg.WriteLine($"Running on {frameworkDescription}", WriteMsg.MsgLevel.Debug);
            else
                WriteMsg.WriteLine("Running on .NET Framework version older than 4.7.1. We cannot determine the exact version number.", WriteMsg.MsgLevel.Debug);
        }

        private static void LogEnvironmentInfo()
        {
            WriteMsg.WriteLine("Current working directory: {0}", WriteMsg.MsgLevel.Debug, Environment.CurrentDirectory);
            var env = Environment.GetEnvironmentVariables();
            var orderedEnvKeys = from object k in env.Keys
                orderby k.ToString()
                select k;
            WriteMsg.WriteLine("Environment variables:", WriteMsg.MsgLevel.Debug);
            foreach (var key in orderedEnvKeys)
            {
                WriteMsg.WriteLine("  {0}: {1}", WriteMsg.MsgLevel.Debug, key, env[key]);
            }
        }
    }
}
