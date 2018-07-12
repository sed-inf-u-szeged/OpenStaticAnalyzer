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

#include "lim/inc/lim.h"
#include "common/inc/WriteMessage.h"

#include <string.h>
#include "common/inc/math/common.h"

namespace columbus { namespace lim { namespace asg {

 typedef boost::crc_32_type  Crc_type;

  SourcePosition::SourcePosition ()
    : m_realizationLevel ((RealizationLevel)0)
    , m_line (0)
    , m_column (0)
    , m_endLine (0)
    , m_endColumn (0){}

  SourcePosition::SourcePosition (  RealizationLevel p_realizationLevel ,  unsigned p_line ,  unsigned p_column ,  unsigned p_endLine ,  unsigned p_endColumn) 
    : m_realizationLevel (p_realizationLevel)
    , m_line (p_line)
    , m_column (p_column)
    , m_endLine (p_endLine)
    , m_endColumn (p_endColumn) {} 

  RealizationLevel SourcePosition::getRealizationLevel() const {
    return  m_realizationLevel;
  }

  unsigned SourcePosition::getLine() const {
    return  m_line;
  }

  unsigned SourcePosition::getColumn() const {
    return  m_column;
  }

  unsigned SourcePosition::getEndLine() const {
    return  m_endLine;
  }

  unsigned SourcePosition::getEndColumn() const {
    return  m_endColumn;
  }

  void SourcePosition::setRealizationLevel(RealizationLevel p_realizationLevel) {
    m_realizationLevel = p_realizationLevel;
  }

  void SourcePosition::setLine(unsigned p_line) {
    m_line = p_line;
  }

  void SourcePosition::setColumn(unsigned p_column) {
    m_column = p_column;
  }

  void SourcePosition::setEndLine(unsigned p_endLine) {
    m_endLine = p_endLine;
  }

  void SourcePosition::setEndColumn(unsigned p_endColumn) {
    m_endColumn = p_endColumn;
  }

  double SourcePosition::getSimilarity(const SourcePosition& other) const {
      double matchAttrs = 0;
      if(other.getRealizationLevel() == getRealizationLevel()) ++matchAttrs;
      if(other.getLine() == getLine()) ++matchAttrs;
      if(other.getColumn() == getColumn()) ++matchAttrs;
      if(other.getEndLine() == getEndLine()) ++matchAttrs;
      if(other.getEndColumn() == getEndColumn()) ++matchAttrs;
      return matchAttrs / (5 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
  }

  NodeHashType SourcePosition::getHash() const {
    Crc_type resultHash;
    resultHash.process_bytes( "SourcePosition",strlen("SourcePosition"));
    resultHash.process_bytes(&m_realizationLevel, sizeof(m_realizationLevel));
    resultHash.process_bytes(&m_line, sizeof(m_line));
    resultHash.process_bytes(&m_column, sizeof(m_column));
    resultHash.process_bytes(&m_endLine, sizeof(m_endLine));
    resultHash.process_bytes(&m_endColumn, sizeof(m_endColumn));
    return (NodeHashType)resultHash.checksum();
  }

  bool SourcePosition::operator==(const SourcePosition& other) const {
    if (&other == this)
      return true;

    if (m_realizationLevel != other.m_realizationLevel)
      return false;

    if (m_line != other.m_line)
      return false;

    if (m_column != other.m_column)
      return false;

    if (m_endLine != other.m_endLine)
      return false;

    if (m_endColumn != other.m_endColumn)
      return false;

    return true;
  }

  bool SourcePosition::operator!=(const SourcePosition& other) const {
    return !operator==(other);
  }

  void SourcePosition::save(io::BinaryIO &binIo) const {
    binIo.writeUByte1(m_realizationLevel);
    binIo.writeUInt4(m_line);
    binIo.writeUInt4(m_column);
    binIo.writeUInt4(m_endLine);
    binIo.writeUInt4(m_endColumn);
  }

  void SourcePosition::load(io::BinaryIO &binIo) {
    m_realizationLevel = (RealizationLevel)binIo.readUByte1();
    m_line = binIo.readUInt4();
    m_column = binIo.readUInt4();
    m_endLine = binIo.readUInt4();
    m_endColumn = binIo.readUInt4();
  }


}}}
