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

/**********************************************************************
Copyright (c) 2013 by Matt Swain <m.swain@me.com>

The MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

***********************************************************************/

#include <string>
#include "jsoncpp/inc/writer.h"

namespace Json {
    class JSON_API SarifWriter : public Writer
    {
    public:
        SarifWriter(std::string opencurly = "{",
                    std::string closecurly = "}",
                    std::string opensquare = "[",
                    std::string closesquare = "]",
                    std::string colon = ":",
                    std::string comma = ",",
                    std::string indent = "    ",
                    int maxWidth = 0);
        virtual ~SarifWriter() {}

    public: // overridden from Writer
        virtual std::string write(const Value &root);

    private:
        void writeValue(const Value &value, std::string &doc, bool forceSingleLine);
        bool isMultiline(const Value &value);
        void indent();
        void unindent();

        std::string document_;
        std::string indentString_;
        std::string opencurly_;
        std::string closecurly_;
        std::string opensquare_;
        std::string closesquare_;
        std::string colon_;
        std::string comma_;
        std::string indent_;
        int maxWidth_;
    };
}