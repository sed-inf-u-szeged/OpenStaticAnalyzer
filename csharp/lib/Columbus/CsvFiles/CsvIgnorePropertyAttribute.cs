using System;

namespace Columbus.CsvFiles
{
    public class CsvIgnorePropertyAttribute : Attribute
    {
        public override string ToString()
        {
            return "Ignore Property";
        }
    }
}