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

#ifndef _CSHARP_SourcePosition_H_
#define _CSHARP_SourcePosition_H_

#include "csharp/inc/csharp.h"

/**
* \file SourcePosition.h
* \brief Contains declaration of the SourcePosition class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief SourcePosition class, which represents the SourcePosition node.
  */
  class SourcePosition  {
    public:

      // ---------- constructors  ----------

      SourcePosition ( RefDistributorStrTable& strTable ,  unsigned p_endColumn ,  unsigned p_endLine ,  const std::string& p_fileName ,  unsigned p_startColumn ,  unsigned p_startLine) ;

      SourcePosition ( RefDistributorStrTable& strTable );

      // assignment operator
      SourcePosition& operator=(const SourcePosition& right);


      // ---------- Attribute getter function(s) ----------

      unsigned getEndColumn() const ;
      unsigned getEndLine() const ;
      const std::string& getFileName() const ;
      Key getFileNameKey() const ;
      unsigned getStartColumn() const ;
      unsigned getStartLine() const ;

      // ---------- Attribute setter function(s) ----------

      void setEndColumn(unsigned p_endColumn); 
      void setEndLine(unsigned p_endLine); 
      void setFileName(const std::string& p_fileName); 
      void setFileNameKey(Key key);
      void setStartColumn(unsigned p_startColumn); 
      void setStartLine(unsigned p_startLine); 
      /**
      * \internal
      * \brief Calculate SourcePosition type similarity.
      * \param nodeIf [in] The other node.
      */
      double getSimilarity(const SourcePosition& other) const;

      /**
      * \internal
      * \brief Calculate SourcePosition type hash.
      */
      NodeHashType getHash() const;
      // ---------- save function(s) ----------

      void save(io::BinaryIO &binIo) const ;
      // ---------- load function(s) ----------

      void load(io::BinaryIO &binIo);
      /**
      * \internal
      * \brief It is swap the string table ids to the other string table.
      * \param newStrTable [in] The new table
      * \param oldAndNewStrKeyMap [in] The map for fast serch.
      */
      void swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap );

      bool operator==(const SourcePosition& other) const;
      bool operator!=(const SourcePosition& other) const;
    protected:
       unsigned m_endColumn;
       unsigned m_endLine;
       unsigned m_startColumn;
       unsigned m_startLine;
       const StringReference* m_fileName;
  };


}}}
#endif

