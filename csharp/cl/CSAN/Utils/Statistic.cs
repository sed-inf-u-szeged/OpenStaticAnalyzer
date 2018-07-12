/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
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
