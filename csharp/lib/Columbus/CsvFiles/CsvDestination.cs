using System;
using System.IO;

namespace Columbus.CsvFiles
{
    public class CsvDestination
    {
        public StreamWriter StreamWriter;

        public static implicit operator CsvDestination(string path)
        {
            return new CsvDestination(path);
        }
        private CsvDestination(StreamWriter streamWriter)
        {
            this.StreamWriter = streamWriter;
        }

        private CsvDestination(Stream stream)
        {
            this.StreamWriter = new StreamWriter(stream);
        }

        public CsvDestination(string fullName)
        {
            FixCsvFileName(ref fullName);
            this.StreamWriter = new StreamWriter(fullName);
        }

        private static void FixCsvFileName(ref string fullName)
        {
            fullName = Path.GetFullPath(fullName);
            var path = Path.GetDirectoryName(fullName);
            if (path != null && !Directory.Exists(path))
                Directory.CreateDirectory(path);
            if (!String.Equals(Path.GetExtension(fullName), ".csv"))
                fullName += ".csv";
        }
    }
}