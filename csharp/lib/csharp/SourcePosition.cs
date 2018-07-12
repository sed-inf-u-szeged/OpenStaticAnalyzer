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

using System;
using System.Collections.Generic;
using System.Text;

namespace Columbus.Csharp.Asg {

    /// <summary>
    /// SourcePosition class, which represents the SourcePosition node.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class SourcePosition {

        // ---------- Members ----------

        private uint m_endColumn;
        private uint m_endLine;
        private uint m_startColumn;
        private uint m_startLine;
        private uint m_fileName;
    StrTable m_strTable;

        public SourcePosition ( StrTable strTable,  uint _endColumn ,  uint _endLine ,  string _fileName ,  uint _startColumn ,  uint _startLine) {
            m_endColumn = _endColumn;
            m_endLine = _endLine;
            m_fileName = strTable.set(_fileName);
            m_startColumn = _startColumn;
            m_startLine = _startLine;
            m_strTable = strTable;
        }

        public SourcePosition (StrTable strTable) {
            m_endColumn = 0;
            m_endLine = 0;
        m_fileName = strTable.set("");
            m_startColumn = 0;
            m_startLine = 0;
            m_strTable = strTable;
        }

        // ---------- Attribute getter function(s) ----------

        public uint EndColumn
        {
            get
            {
                return m_endColumn;
            }
            set
            {
                m_endColumn = value;
            }
        }

        public uint EndLine
        {
            get
            {
                return m_endLine;
            }
            set
            {
                m_endLine = value;
            }
        }

        public string FileName
        {
            get
            {
                return m_strTable.get(m_fileName);
            }
            set
            {
                m_strTable.set(value);
            }
        }

        public uint FileNameKey
        {
            get
            {
                return m_fileName;
            }
            set
            {
                m_fileName = value;
            }
        }

        public uint StartColumn
        {
            get
            {
                return m_startColumn;
            }
            set
            {
                m_startColumn = value;
            }
        }

        public uint StartLine
        {
            get
            {
                return m_startLine;
            }
            set
            {
                m_startLine = value;
            }
        }


        // ---------- save and load functions ----------

        public void save(IO io) {
            io.writeUInt4(m_endColumn);
            io.writeUInt4(m_endLine);
            io.writeUInt4(m_fileName);
            io.writeUInt4(m_startColumn);
            io.writeUInt4(m_startLine);
        }
        public void load(IO io) {
            m_endColumn = io.readUInt4();
            m_endLine = io.readUInt4();
            m_fileName = io.readUInt4();
            m_strTable.setType(m_fileName, StrTable.StrType.strToSave);
            m_startColumn = io.readUInt4();
            m_startLine = io.readUInt4();
        }
}

}