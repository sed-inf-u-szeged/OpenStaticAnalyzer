using System.Collections.Generic;

namespace Columbus.CsvFiles
{
    public static class CsvFileLinqExtensions
    {
        public static void ToCsv<T>(this IEnumerable<T> source, CsvDestination csvDestination)
        {
            source.ToCsv(csvDestination, null);
        }

        public static void ToCsv<T>(this IEnumerable<T> source, CsvDestination csvDestination, CsvDefinition csvDefinition)
        {
            using (var csvFile = new CsvFile<T>(csvDestination, csvDefinition))
            {
                foreach (var record in source)
                {
                    csvFile.Append(record);
                }
            }
        }

    }
}
