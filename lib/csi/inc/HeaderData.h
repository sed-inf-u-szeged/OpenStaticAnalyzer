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

#ifndef _HEADERDATA_H
#define _HEADERDATA_H

#include <string>
#include <io/inc/ZippedIO.h>

namespace columbus {
   enum HeaderDataTypeKind {
      hdkPropertyData,
      hdkIntervalData,
      hdkAnalysisData,
      hdkLinkerCompilationData,
      hdkLimOrigin,
      hdkOverride,
      hdkSymbolTable
  };
  
  class HeaderData {
  public:
    virtual ~HeaderData(){}

    /**
     * @brief Saves the header data to the given file.
     */
    virtual void save(io::BinaryIO &binIo) const = 0;

    /** 
     *@brief loading the header data
     *
     */
    virtual void load(io::BinaryIO &binIo) = 0;

    /**
     * @brief get headerdata type
     * @return the type of the header
     */
    virtual HeaderDataTypeKind getType() const = 0;
    
    /**
     * @brief Returns a string representation of the header data.
     */
    virtual std::string toString() const = 0;
  };

  
}

#endif
