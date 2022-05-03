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

#ifndef ZIPPEDIO_H
#define ZIPPEDIO_H

#include <io/inc/BinaryIO.h>
#include <boost/iostreams/filtering_stream.hpp>

namespace columbus {  namespace io {

    class ZippedIO : virtual public BinaryIO {
    private:
        bool zip;
        std::unique_ptr<boost::iostreams::filtering_stream<boost::iostreams::bidirectional>> filterstream;

    public:
        ZippedIO();
        ZippedIO(const std::string& filename, IOBase::eOpenMode mode, bool zipped = true);
        ZippedIO(const char *filename, IOBase::eOpenMode mode, bool zipped = true);

        virtual void setZip(bool zipmode);

    private:

        void addCompressorFilter();

        virtual void write(const char* data, const std::streampos size) override;
        virtual void read(char* data, const std::streampos size) override;
        virtual void get(std::streambuf& sb, char delim) override;


    public:

        /**
        * \brief open a file, if stream is open it will be colsed
        * \param filename [in] file name
        * \param mode [in] open mode
        * \throw IOException if a file already opened
        * \throw IOException if open is failed
        */
        virtual void open(const std::string& filename, eOpenMode mode, bool zipped = true);

        /**
        * \brief open a file, if stream is open it will be colsed
        * \param filename [in] file name
        * \param mode [in] open mode
        * \throw IOException if a file already opened
        * \throw IOException if open is failed
        */
        virtual void open(const char *filename, eOpenMode mode, bool zipped = true);

        /**
        * \brief close the opened file, after then we can open other file with open function
        * \throw IOException if the the file is already closed or not opened.
        * \throw IOException if can't close the file
        */
        virtual void close() override;

        /**
        \brief Write long long 0 size of the following block into the current file position
        * set the blockSizePosition to the current file position
        */
        virtual void writeStartSizeOfBlock() override;
         /**
        \brief Write the difference beetween the actual file positon and the BlockSizeposition as a file size to the storaged blockSizePosition
        */
        virtual void writeEndSizeOfBlock() override;

        /**
        \brief skip the next length long data.
        \param length of the data
        */
        virtual void skipNext(std::streamsize length) override;

        /**
         * \brief set position to read
         * \param startPos startposition to read
         */
         virtual void setStartReadPosition(std::streampos& startPos) override;

         virtual void setStartWritePosition( std::streampos& startPos) override;
    };
}}

#endif // ZIPPEDIO_H
