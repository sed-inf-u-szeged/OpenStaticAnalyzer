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

using System.IO;

namespace Columbus.CsvFiles
{
    public class CsvSource
    {
        public readonly TextReader TextReader;

        public static implicit operator CsvSource(CsvFile csvFile)
        {
            return new CsvSource(csvFile);
        }

        public static implicit operator CsvSource(string path)
        {
            return new CsvSource(path);
        }

        public static implicit operator CsvSource(TextReader textReader)
        {
            return new CsvSource(textReader);
        }

        public CsvSource(TextReader textReader)
        {
            this.TextReader = textReader;
        }

        public CsvSource(Stream stream)
        {
            this.TextReader = new StreamReader(stream);
        }

        public CsvSource(string path)
        {
            this.TextReader = new StreamReader(path);
        }

        public CsvSource(CsvFile csvFile)
        {
            this.TextReader = new StreamReader(csvFile.BaseStream);
        }
    }

}