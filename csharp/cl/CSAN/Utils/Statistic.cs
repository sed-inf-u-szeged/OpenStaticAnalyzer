using Columbus.CsvFiles;

namespace Columbus.CSAN.Utils
{
    class Statistic
    {
        [CsvColumnName("Analyse time (s)")]
        public float AnalyzeTime { get; set; }

        [CsvColumnName("Peak memory usage (MByte)")]
        public float PeakMemory { get; set; }

        [CsvColumnName("File's parsing time (s)")]
        public float FilesParsingTime { get; set; }

        [CsvColumnName("Solution's building time (s)")]
        public float SolutionsBuildingTime { get; set; }

        [CsvColumnName("C# ASG building time (s)")]
        public float CSharpASGBuildingTime { get; set; }

        [CsvColumnName("LIM ASG building time (s)")]
        public float LIMASGBildingTime { get; set; }

        [CsvColumnName("ASG building time (s)")]
        public float ASGBuildingTime { get; set; }

        [CsvColumnName("Roslyn time (s)")]
        public float RoslynTime { get; set; }

        [CsvColumnName("Save time (s)")]
        public float SaveTime { get; set; }
    }
}
