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

namespace Columbus.Lim.Asg {

    /// <summary>
    /// SourcePosition class, which represents the SourcePosition node.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class SourcePosition {

        // ---------- Members ----------

        private Types.RealizationLevel m_realizationLevel;
        private uint m_line;
        private uint m_column;
        private uint m_endLine;
        private uint m_endColumn;

        public SourcePosition (  Types.RealizationLevel _realizationLevel ,  uint _line ,  uint _column ,  uint _endLine ,  uint _endColumn) {
            m_realizationLevel = _realizationLevel;
            m_line = _line;
            m_column = _column;
            m_endLine = _endLine;
            m_endColumn = _endColumn;
        }

        public SourcePosition () {
            m_realizationLevel = 0;
            m_line = 0;
            m_column = 0;
            m_endLine = 0;
            m_endColumn = 0;
        }

        // ---------- Attribute getter function(s) ----------

        public Types.RealizationLevel RealizationLevel
        {
            get
            {
                return m_realizationLevel;
            }
            set
            {
                m_realizationLevel = value;
            }
        }

        public uint Line
        {
            get
            {
                return m_line;
            }
            set
            {
                m_line = value;
            }
        }

        public uint Column
        {
            get
            {
                return m_column;
            }
            set
            {
                m_column = value;
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


        // ---------- save and load functions ----------

        public void save(IO io) {
            io.writeUByte1((byte)m_realizationLevel);
            io.writeUInt4(m_line);
            io.writeUInt4(m_column);
            io.writeUInt4(m_endLine);
            io.writeUInt4(m_endColumn);
        }
        public void load(IO io) {
            m_realizationLevel = (Types.RealizationLevel)io.readUByte1();
            m_line = io.readUInt4();
            m_column = io.readUInt4();
            m_endLine = io.readUInt4();
            m_endColumn = io.readUInt4();
        }
}

}