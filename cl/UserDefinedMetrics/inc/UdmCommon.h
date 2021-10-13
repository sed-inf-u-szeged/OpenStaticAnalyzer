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

#ifndef _UDM_COMMON_
#define _UDM_COMMON_

#include "exprtk.hpp"
#include "messages.h"
#include "common/inc/WriteMessage.h"
#include <Exception.h>

using namespace std;
using namespace columbus;

extern bool warning;

const string UDM_EXPANDED = "EXPANDED";

class InvalidChildTypeEx : public exception {

    const string invalidType;
public:

    InvalidChildTypeEx(const string invalidType) : exception(), invalidType(invalidType) {}
    virtual const char* what() const noexcept { return invalidType.c_str(); }
};

// Throw an Exception and write the loop elements to the message
void throwLoopEx(vector<string>& loopCheck, const string& metric);

#endif