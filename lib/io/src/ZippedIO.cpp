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

#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/combine.hpp>
#include <iostream>
#include <sstream>

#include <io/inc/ZippedIO.h>
#include <io/inc/messages.h>
#include "Exception.h"


using namespace std;

namespace columbus {  namespace io {

    ZippedIO::ZippedIO() : BinaryIO(), zip(true), filterstream(nullptr) {
    }

    ZippedIO::ZippedIO(const string& filename, eOpenMode mode, bool zipped) : BinaryIO(filename, mode), zip(zipped), filterstream(nullptr) {
        open(filename, mode, zipped);
    }

    ZippedIO::ZippedIO(const char *filename, IOBase::eOpenMode mode, bool zipped) : BinaryIO(filename, mode), zip(zipped), filterstream(nullptr) {
        open(filename, mode, zipped);
    }

    void ZippedIO::open(const string& filename, eOpenMode mode, bool zipped) {
        if (!(mode == omRead || mode == omWrite || mode == omAppend))
            throw IOException(COLUMBUS_LOCATION, CMSG_EX_OPEN_ZIPPED_MODE);

        BinaryIO::open(filename, mode);

        if(filterstream != nullptr)
            close();

        try {
            zip = zipped;
            this->mode = mode;
            filterstream = make_unique<boost::iostreams::filtering_stream<boost::iostreams::bidirectional>>();

            if (zip)
                addCompressorFilter();

            filterstream->push(*stream, 0, 0);
            filterstream->exceptions(ios_base::failbit | ios_base::badbit);

        } catch(const exception& fail) {
            throw IOException(COLUMBUS_LOCATION, fail.what());
        }
    }

    void ZippedIO::open(const char *filename, eOpenMode mode, bool zipped) {
        open(string(filename), mode, zipped);
    }

    
    void ZippedIO::close() {
        if (filterstream == nullptr)
            return;

        try {
            filterstream->strict_sync();
            delete filterstream.release();
            BinaryIO::close();
        } catch(const exception& fail) {
            throw IOException(COLUMBUS_LOCATION, fail.what());
        }
    }

    void ZippedIO::setZip(bool zipmode) {
        if (!isOpen())
            return;

        if (zip != zipmode) {
            filterstream->sync();

            filterstream->pop();
            if (!zipmode)
                filterstream->pop();
            else
                addCompressorFilter();

            filterstream->push(*stream, 0, 0);
            zip = zipmode;
        }
    }

    // This empty_filter is needed since bidirectional filter_stream won't work properly
    // if the filestream is opened for reading only.
    struct empty_filter {
        typedef char                                        char_type;
        typedef boost::iostreams::bidirectional_filter_tag  category;

        template<typename Sink>
        bool put(Sink& snk, char c)  { return true; }

        template<typename Sink>
        streamsize write(Sink& snk, const char* s, streamsize n) { return n; }

        template<typename Source>
        int get(Source& src) { return EOF; }
    };

    void ZippedIO::addCompressorFilter()
    {
      switch (mode) {
        case omRead:
          filterstream->push(boost::iostreams::combine(boost::iostreams::zlib_decompressor(), empty_filter()));
          break;
        case omAppend:
        case omWrite:
          filterstream->push(boost::iostreams::combine(empty_filter(), boost::iostreams::zlib_compressor(boost::iostreams::zlib::best_speed)));
          break;
        case omReadWrite:
          filterstream->push(boost::iostreams::combine(boost::iostreams::zlib_decompressor(),
                                                       boost::iostreams::zlib_compressor(boost::iostreams::zlib::best_speed)), 0, 0);
          break;
      }
    }

    void ZippedIO::write(const char* data, const streampos size) {
        // There is deliberately no nullptr pointer check as it is used only internally
        // from the write methods, which already checks it.
        filterstream->write(data, size);
    }

    void ZippedIO::read(char* data, const streampos size) {
        // There is deliberately no nullptr pointer check as it is used only internally
        // from the read methods, which already checks it.
        filterstream->read(data, size);
    }

    void ZippedIO::get(streambuf& sb, char delim) {
        // There is deliberately no nullptr pointer check as it is used only internally
        // from the read methods, which already checks it.
        filterstream->get(sb, delim);
    }

    void ZippedIO::writeStartSizeOfBlock() {
        if (zip)
            throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_ZIPPED);

        BinaryIO::writeStartSizeOfBlock();
    }

    void ZippedIO::skipNext(streamsize length) {
        if (zip)
            throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_ZIPPED);

        BinaryIO::skipNext(length);
    }

    void ZippedIO::writeEndSizeOfBlock() {
        if (zip)
            throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_ZIPPED);

        BinaryIO::writeEndSizeOfBlock();
    }

    void ZippedIO::setStartReadPosition(streampos& startPos) {
        if (zip)
            throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_ZIPPED);

        BinaryIO::setStartReadPosition(startPos);
    }

    void ZippedIO::setStartWritePosition(streampos& startPos) {
        if (zip)
            throw IOException(COLUMBUS_LOCATION, CMSG_EX_FILE_ZIPPED);

        BinaryIO::setStartWritePosition(startPos);
    }

}}
