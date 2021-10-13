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

#include "javascript/inc/javascript.h"


namespace columbus { namespace javascript { namespace asg {

  /* ---------- Exception ---------- */

  JavascriptException::JavascriptException(const std::string &location, const std::string &message) : columbus::Exception(location, message) {
  }

  JavascriptException::~JavascriptException() {
  }

  const std::string JavascriptException::getClassName() const {
    return "javascript::JavascriptException";
  }


  /* ---------- JavascriptInvalidIteratorException ---------- */

  JavascriptInvalidIteratorException::JavascriptInvalidIteratorException(const std::string &location, const std::string &message) : JavascriptException(location, message) {
  }

  JavascriptInvalidIteratorException::~JavascriptInvalidIteratorException() {
  }

  const std::string JavascriptInvalidIteratorException::getClassName() const {
    return "javascript::JavascriptInvalidIteratorException";
  }


  /* ---------- JavascriptIllegalStateException ---------- */

  JavascriptIllegalStateException::JavascriptIllegalStateException(const std::string &location, const std::string &message) : JavascriptException(location, message) {
  }

  JavascriptIllegalStateException::~JavascriptIllegalStateException() {
  }

  const std::string JavascriptIllegalStateException::getClassName() const {
    return "javascript::JavascriptIllegalStateException";
  }


  /* ---------- JavascriptNoSuchElementException ---------- */

  JavascriptNoSuchElementException::JavascriptNoSuchElementException(const std::string &location, const std::string &message) : JavascriptException(location, message) {
  }

  JavascriptNoSuchElementException::~JavascriptNoSuchElementException() {
  }

  const std::string JavascriptNoSuchElementException::getClassName() const {
    return "javascript::JavascriptNoSuchElementException";
  }


}}}
