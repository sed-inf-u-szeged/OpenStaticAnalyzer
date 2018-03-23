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
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Columbus.CsvFiles
{
    public class CsvFile : IDisposable
    {
        #region Static Members
        public static CsvDefinition DefaultCsvDefinition { get; set; }
        public static bool UseLambdas { get; set; }
        public static bool UseTasks { get; set; }
        public static bool FastIndexOfAny { get; set; }

        static CsvFile()
        {
            // Choosing default Field Separator is a hard decision
            // In theory the C of CSV means Comma separated 
            // In Windows though many people will try to open the csv with Excel which is horrid with real CSV.
            // As the target for this library is Windows we go for Semi Colon.
            DefaultCsvDefinition = new CsvDefinition
            {
                EndOfLine = "\r\n",
                FieldSeparator = ';',
                TextQualifier = '"'
            };
            UseLambdas = true;
            UseTasks = true;
            FastIndexOfAny = true;
        }

        #endregion

        internal protected Stream BaseStream;
        protected static DateTime DateTimeZero = new DateTime();


        public static IEnumerable<T> Read<T>(CsvSource csvSource) where T : new()
        {
            var csvFileReader = new CsvFileReader<T>(csvSource);
            return csvFileReader;
        }

        public char FieldSeparator { get; private set; }
        public char TextQualifier { get; private set; }
        public IEnumerable<string> Columns { get; private set; }

        public void Dispose()
        {
            Dispose(true);
        }

        protected virtual void Dispose(bool disposing){}
    }

    public class CsvFile<T> : CsvFile
    {
        private readonly char fieldSeparator;
        private readonly char decimalSeparator;
        private readonly string fieldSeparatorAsString;
        private readonly char[] invalidCharsInFields;
        private readonly StreamWriter streamWriter;
        private readonly char textQualifier;
        private readonly string[] columns;
        private readonly static Dictionary<string, string> propertiesName = new Dictionary<string, string>();
        private Func<T, object>[] getters;
        readonly bool[] isInvalidCharInFields;
        private int linesToWrite;
        private readonly BlockingCollection<string> csvLinesToWrite = new BlockingCollection<string>(5000);
        private readonly Thread writeCsvLinesTask;
        private Task addAsyncTask;


        public CsvFile(CsvDestination csvDestination)
            : this(csvDestination, null)
        {
        }

        public CsvFile()
        {
        }

        public CsvFile(CsvDestination csvDestination, CsvDefinition csvDefinition)
        {
            if (csvDefinition == null)
                csvDefinition = DefaultCsvDefinition;
            columns = InferColumns(typeof(T));
            fieldSeparator = csvDefinition.FieldSeparator;
            decimalSeparator = csvDefinition.DecimalSeparator;
            fieldSeparatorAsString = fieldSeparator.ToString(CultureInfo.InvariantCulture);
            textQualifier = csvDefinition.TextQualifier;
            streamWriter = csvDestination.StreamWriter;

            invalidCharsInFields = new[] { '\r', '\n', textQualifier, fieldSeparator };
            isInvalidCharInFields = new bool[256];

            foreach (var c in invalidCharsInFields)
            {
                isInvalidCharInFields[c] = true;
            }
            WriteHeader();
            CreateGetters();

            if (UseTasks)
            {
                writeCsvLinesTask = new Thread((o) => WriteCsvLines());
                writeCsvLinesTask.Start();
            }
            addAsyncTask = Task.Factory.StartNew(() => { });

        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                // free managed resources
                addAsyncTask.Wait();
                if (csvLinesToWrite != null)
                {
                    csvLinesToWrite.CompleteAdding();
                }
                if (writeCsvLinesTask != null)
                    writeCsvLinesTask.Join();
                streamWriter.Close();
            }
        }

        protected static string[] InferColumns(Type recordType)
        {
            var propName = recordType
                .GetProperties(BindingFlags.Public | BindingFlags.Instance)
                .Where(pi => pi.GetIndexParameters().Length == 0
                    && pi.GetSetMethod() != null
                    && !Attribute.IsDefined(pi, typeof(CsvIgnorePropertyAttribute)))
                .Select(pi => pi.Name)
                .Concat(recordType
                    .GetFields(BindingFlags.Public | BindingFlags.Instance)
                    .Where(fi => !Attribute.IsDefined(fi, typeof(CsvIgnorePropertyAttribute)))
                    .Select(fi => fi.Name))
                .ToList();

            var columns = recordType
                .GetProperties(BindingFlags.Public | BindingFlags.Instance)
                .Where(pi => pi.GetIndexParameters().Length == 0
                    && pi.GetSetMethod() != null
                    && !Attribute.IsDefined(pi, typeof(CsvIgnorePropertyAttribute)))
                .Select(pi => (pi.GetCustomAttributes(true)[0] as CsvColumnNameAttribute).ToString())
                .ToArray();

            for (int i = 0; i < columns.Length; i++)
            {
                propertiesName.Add(columns[i], propName[i]);
            }

            return columns;
        }

        private void WriteCsvLines()
        {
            int written = 0;
            foreach (var csvLine in csvLinesToWrite.GetConsumingEnumerable())
            {
                streamWriter.WriteLine(csvLine);
                written++;
            }
            Interlocked.Add(ref linesToWrite, -written);
        }


        public void Append(T record)
        {
            if (UseTasks)
            {
                var linesWaiting = Interlocked.Increment(ref linesToWrite);
                Action<Task> addRecord = (t) =>
                {
                    var csvLine = ToCsv(record);
                    csvLinesToWrite.Add(csvLine);
                };

                if (linesWaiting < 10000)
                    addAsyncTask = addAsyncTask.ContinueWith(addRecord);
                else
                    addRecord(null);
            }
            else
            {
                var csvLine = ToCsv(record);
                streamWriter.WriteLine(csvLine);
            }
        }

        private static Func<T, object> FindGetter(string c, bool staticMember)
        {
            var flags = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.IgnoreCase | (staticMember ? BindingFlags.Static : BindingFlags.Instance);
            Func<T, object> func = null;
            PropertyInfo pi = typeof(T).GetProperty(c, flags);
            FieldInfo fi = typeof(T).GetField(c, flags);

            if (UseLambdas)
            {
                Expression expr = null;
                ParameterExpression parameter = Expression.Parameter(typeof(T), "r");
                Type type = null;

                if (pi != null)
                {
                    type = pi.PropertyType;
                    expr = Expression.Property(parameter, pi.Name);
                }
                else if (fi != null)
                {
                    type = fi.FieldType;
                    expr = Expression.Field(parameter, fi.Name);
                }
                if (expr != null)
                {
                    Expression<Func<T, object>> lambda;
                    if (type.IsValueType)
                    {
                        lambda = Expression.Lambda<Func<T, object>>(Expression.TypeAs(expr, typeof(object)), parameter);
                    }
                    else
                    {
                        lambda = Expression.Lambda<Func<T, object>>(expr, parameter);
                    }
                    func = lambda.Compile();
                }
            }
            else
            {
                if (pi != null)
                    func = o => pi.GetValue(o, null);
                else if (fi != null)
                    func = o => fi.GetValue(o);
            }
            return func;
        }

        private void CreateGetters()
        {
            var list = new List<Func<T, object>>();

            foreach (var columnName in columns)
            {
                Func<T, object> func = null;
                var propertyName = (columnName.IndexOf(' ') < 0 ? columnName : columnName.Replace(" ", ""));
                func = FindGetter(propertiesName[columnName], false) ?? FindGetter(propertiesName[columnName], true);

                list.Add(func);
            }
            getters = list.ToArray();
        }

        private string ToCsv(T record)
        {
            if (record == null)
                throw new ArgumentException("Cannot be null", "record");

            string[] csvStrings = new string[getters.Length];

            for (int i = 0; i < getters.Length; i++)
            {
                var getter = getters[i];
                object fieldValue = getter == null ? null : getter(record);
                csvStrings[i] = ToCsvString(fieldValue);
            }
            return string.Join(fieldSeparatorAsString, csvStrings);

        }

        private string ToCsvString(object o)
        {
            if (o != null)
            {
                NumberFormatInfo nfi = null;
                string valueString = string.Empty;
                if (o.IsNumber())
                {
                    nfi = (NumberFormatInfo)CultureInfo.InvariantCulture.NumberFormat.Clone();
                    nfi.NumberDecimalSeparator = decimalSeparator.ToString();
                    valueString = Convert.ToString(o, nfi);
                }
                else
                    valueString = o as string ?? Convert.ToString(o, CultureInfo.CurrentUICulture);

                if (RequiresQuotes(valueString))
                {
                    var csvLine = new StringBuilder();
                    csvLine.Append(textQualifier);
                    foreach (char c in valueString)
                    {
                        if (c == textQualifier)
                            csvLine.Append(c); // double the double quotes
                        csvLine.Append(c);
                    }
                    csvLine.Append(textQualifier);
                    return csvLine.ToString();
                }
                else
                    return valueString;
            }
            return string.Empty;
        }

        private bool RequiresQuotes(string valueString)
        {
            if (FastIndexOfAny)
            {
                var len = valueString.Length;
                for (int i = 0; i < len; i++)
                {
                    char c = valueString[i];
                    if (c <= 255 && isInvalidCharInFields[c])
                        return true;
                }
                return false;
            }
            else
            {
                return valueString.IndexOfAny(invalidCharsInFields) >= 0;
            }
        }

        private void WriteHeader()
        {
            var csvLine = new StringBuilder();
            for (int i = 0; i < columns.Length; i++)
            {
                if (i > 0)
                    csvLine.Append(fieldSeparator);
                csvLine.Append(ToCsvString(columns[i]));
            }
            streamWriter.WriteLine(csvLine.ToString());
        }
    }
}
