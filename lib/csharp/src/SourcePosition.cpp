/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#include "csharp/inc/csharp.h"
#include "common/inc/WriteMessage.h"

#include <string.h>
#include "common/inc/math/common.h"

namespace columbus { namespace csharp { namespace asg {

 typedef boost::crc_32_type  Crc_type;

  SourcePosition::SourcePosition (RefDistributorStrTable& strTable)
    : m_endColumn (0)
    , m_endLine (0)
    , m_startColumn (0)
    , m_startLine (0)
    , m_fileName (strTable.getRefByKey(0)){}

  SourcePosition::SourcePosition ( RefDistributorStrTable& strTable ,  unsigned p_endColumn ,  unsigned p_endLine ,  const std::string& p_fileName ,  unsigned p_startColumn ,  unsigned p_startLine) 
    : m_endColumn (p_endColumn)
    , m_endLine (p_endLine)
    , m_startColumn (p_startColumn)
    , m_startLine (p_startLine)
    , m_fileName (strTable.setStr(p_fileName)) {} 

  SourcePosition& SourcePosition::operator=(const SourcePosition& right) {
    m_endColumn = right.m_endColumn;
    m_endLine = right.m_endLine;
    m_startColumn = right.m_startColumn;
    m_startLine = right.m_startLine;
    StringReference::copy(m_fileName , right.m_fileName);
    return *this;
  }

  unsigned SourcePosition::getEndColumn() const {
    return  m_endColumn;
  }

  unsigned SourcePosition::getEndLine() const {
    return  m_endLine;
  }

  const std::string& SourcePosition::getFileName() const {
    return  m_fileName->get();
  }

  Key SourcePosition::getFileNameKey() const {
      return  m_fileName != NULL ? m_fileName->getKey():0;
  }

  unsigned SourcePosition::getStartColumn() const {
    return  m_startColumn;
  }

  unsigned SourcePosition::getStartLine() const {
    return  m_startLine;
  }

  void SourcePosition::setEndColumn(unsigned p_endColumn) {
    m_endColumn = p_endColumn;
  }

  void SourcePosition::setEndLine(unsigned p_endLine) {
    m_endLine = p_endLine;
  }

  void SourcePosition::setFileName(const std::string& p_fileName) {
    m_fileName = m_fileName->getTable().setStr(p_fileName);
  }

  void SourcePosition::setFileNameKey(Key key) {
    m_fileName = m_fileName->getTable().getRefByKey(key);
  }

  void SourcePosition::setStartColumn(unsigned p_startColumn) {
    m_startColumn = p_startColumn;
  }

  void SourcePosition::setStartLine(unsigned p_startLine) {
    m_startLine = p_startLine;
  }

  double SourcePosition::getSimilarity(const SourcePosition& other) const {
      double matchAttrs = 0;
      if(other.getEndColumn() == getEndColumn()) ++matchAttrs;
      if(other.getEndLine() == getEndLine()) ++matchAttrs;
      if(other.getStartColumn() == getStartColumn()) ++matchAttrs;
      if(other.getStartLine() == getStartLine()) ++matchAttrs;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getFileName();
      str2 = other.getFileName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (5 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
  }

  NodeHashType SourcePosition::getHash() const {
    Crc_type resultHash;
    resultHash.process_bytes( "SourcePosition",strlen("SourcePosition"));
    resultHash.process_bytes(&m_endColumn, sizeof(m_endColumn));
    resultHash.process_bytes(&m_endLine, sizeof(m_endLine));
    resultHash.process_bytes( m_fileName->get().c_str(),m_fileName->get().length() );
    resultHash.process_bytes(&m_startColumn, sizeof(m_startColumn));
    resultHash.process_bytes(&m_startLine, sizeof(m_startLine));
    return (NodeHashType)resultHash.checksum();
  }

  void SourcePosition::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_fileName->getKey());
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_fileName = newStrTable.getRefByKey(foundKeyId->second);
    } else {
      Key oldkey = m_fileName->getKey();
      m_fileName = newStrTable.setStr(m_fileName->get());
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_fileName->getKey()));
    }

  }

  bool SourcePosition::operator==(const SourcePosition& other) const {
    if (&other == this)
      return true;

    if (m_endColumn != other.m_endColumn)
      return false;

    if (m_endLine != other.m_endLine)
      return false;

    if (&m_fileName->getTable() != &other.m_fileName->getTable()) {
      if (m_fileName->get() != other.m_fileName->get())
        return false;
    } else
      if (m_fileName->getKey() != other.m_fileName->getKey())
        return false;

    if (m_startColumn != other.m_startColumn)
      return false;

    if (m_startLine != other.m_startLine)
      return false;

    return true;
  }

  bool SourcePosition::operator!=(const SourcePosition& other) const {
    return !operator==(other);
  }

  void SourcePosition::save(io::BinaryIO &binIo) const {
    binIo.writeUInt4(m_endColumn);
    binIo.writeUInt4(m_endLine);
    binIo.writeUInt4(m_fileName->getKey());
    binIo.writeUInt4(m_startColumn);
    binIo.writeUInt4(m_startLine);
  }

  void SourcePosition::load(io::BinaryIO &binIo) {
    m_endColumn = binIo.readUInt4();
    m_endLine = binIo.readUInt4();
    m_fileName = m_fileName->getTable().getRefByKey( binIo.readUInt4() );
    m_startColumn = binIo.readUInt4();
    m_startLine = binIo.readUInt4();
  }


}}}
