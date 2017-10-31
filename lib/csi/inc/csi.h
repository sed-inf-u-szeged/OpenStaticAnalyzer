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

#ifndef _CSI_H
#define _CSI_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include "Exception.h"
#include <io/inc/BinaryIO.h>

/*! \file csi.h
    \brief Contains the class `CsiHedaer' which can load/save the headers of the columbus schema instances.
*/

namespace columbus {

/**
* \brief CsiHeader class is responsible for storing/loading/saving the columbus schema instance headers.
*/
class CsiHeader {

  public:
    /**
    * \brief Constructor.
    */
    CsiHeader();

    /**
    * \brief Add a new (key,vale) pair to the header.
    * \param key [in] The key.
    * \param value [in] The string to store beside the key.
    * \returns Returns true if the insertion was success. In case an item with same key already exist the function returns false.
    */
    bool add(const std::string& key, const std::string& value);

    /**
    * \brief Add a new (key,vale) pair to the header. If the value is true than the value of the csih_True (if it is false than the value of the csih_False)
    * will be stored beside the key. 
    * \param key [in] The key.
    * \param value [in] The boolean.
    * \returns Returns true if the insertion was success. In case an item with same key already exist the function returns false.
    */

    bool addBool(const std::string& key, bool value);

    /**
    * \brief Add a new (key,vale) pair to the header where the value is an integer. The integer will be stored as a string in the header.
    * \param key [in] The key.
    * \param value [in] The integer.
    * \returns Returns true if the insertion was success. In case an item with same key already exist the function returns false.
    */
    bool addInt(const std::string& key, int value);
 
    /**
    * \brief It gives back the stored value beside the given key if it is exists.
    * \param key [in] Name of the key.
    * \param value [out] The stored value.
    * \returns Returns true if an item with the given key is exists.
    */
    bool get(const std::string& key, std::string& value) const;

    /**
    * \brief It gives back true in the value parameter only if the stored string was the same as the value of the csih_True.
    * \param key [in] Name of the key.
    * \param value [out] The stored logical value.
    * \returns Returns true if an item with the given key is exists.
    */
    bool getBool(const std::string& key, bool& value) const;

    /**
    * \brief It gives back the stored string converted to integer int the value parameter.
    * \param key [in] Name of the key.
    * \param value [out] The integer value.
    * \returns Returns true if an item with the given key is exists.
    */
    bool getInt(const std::string& key, int& value) const;

    /**
    * \brief It writes out the header into the given file. The file must be opened for writing.
    * \param io [in] The io::BinaryIO containing the file into the header will be written.
    * \throw IOException - if any error happen during the writing. 
    */
    void write(io::BinaryIO &io) const;

    /**
    * \brief It reads back the header from the given file. The file must be opened for reading.
    * \param io [in] The io::BinaryIO containing the file from the header will be read.
    * \throw IOException - if any error happen during the reading. 
    */
    void read(io::BinaryIO &io);

    /**
    * \brief It prints out the header for debuging.
    */
    void dump() const;

  protected:
    std::map<std::string, std::string> header;    ///< The map which contains the <key, value> pairs.

  public:
    
    static const std::string csih_True;
    static const std::string csih_False;
    static const std::string csih_Type;
    static const std::string csih_BinaryVersion;
    static const std::string csih_APIVersion;
    static const std::string csih_FullAnalysis;
    static const std::string csih_SchemaFilter;
    static const std::string csih_PrecompiledHeader;
    static const std::string csih_UsePrecompiledHeader;
    static const std::string csih_NumOfIncrLinked;
    static const std::string csih_PreanalyzedIncludesUsed;
    static const std::string csih_OriginalLocation;
    static const std::string csih_PsiKind;
    static const std::string csih_Language;
    static const std::string csih_ChangesetID;
};

} // namespace columbus

#endif
