using System;
using System.Collections.Generic;

namespace Columbus.CsvFiles
{
    public class CsvDefinition
    {
        public string Header { get; set; }
        public char FieldSeparator { get; set; }
        public char TextQualifier { get; set; }
        public string EndOfLine { get; set; }

        public char DecimalSeparator { get; set; }

        public CsvDefinition()
        {
            if (CsvFile.DefaultCsvDefinition != null)
            {
                FieldSeparator = CsvFile.DefaultCsvDefinition.FieldSeparator;
                TextQualifier = CsvFile.DefaultCsvDefinition.TextQualifier;
                EndOfLine = CsvFile.DefaultCsvDefinition.EndOfLine;
            }
        }
    }
}