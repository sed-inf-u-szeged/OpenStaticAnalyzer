using System;

namespace Columbus.CsvFiles
{
    public class CsvColumnNameAttribute : Attribute
    {
        private string csvColumnName;

        public CsvColumnNameAttribute(string csvColumnName)
        {
            this.csvColumnName = csvColumnName;
        }

        public override string ToString()
        {
            return csvColumnName;
        }
    }
}