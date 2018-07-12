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

  JavaScriptException::JavaScriptException(const std::string &location, const std::string &message) : columbus::Exception(location, message) {
  }

  JavaScriptException::~JavaScriptException() {
  }

  const std::string JavaScriptException::getClassName() const {
    return "javascript::JavaScriptException";
  }


  /* ---------- JavaScriptInvalidIteratorException ---------- */

  JavaScriptInvalidIteratorException::JavaScriptInvalidIteratorException(const std::string &location, const std::string &message) : JavaScriptException(location, message) {
  }

  JavaScriptInvalidIteratorException::~JavaScriptInvalidIteratorException() {
  }

  const std::string JavaScriptInvalidIteratorException::getClassName() const {
    return "javascript::JavaScriptInvalidIteratorException";
  }


  /* ---------- JavaScriptIllegalStateException ---------- */

  JavaScriptIllegalStateException::JavaScriptIllegalStateException(const std::string &location, const std::string &message) : JavaScriptException(location, message) {
  }

  JavaScriptIllegalStateException::~JavaScriptIllegalStateException() {
  }

  const std::string JavaScriptIllegalStateException::getClassName() const {
    return "javascript::JavaScriptIllegalStateException";
  }


  /* ---------- JavaScriptNoSuchElementException ---------- */

  JavaScriptNoSuchElementException::JavaScriptNoSuchElementException(const std::string &location, const std::string &message) : JavaScriptException(location, message) {
  }

  JavaScriptNoSuchElementException::~JavaScriptNoSuchElementException() {
  }

  const std::string JavaScriptNoSuchElementException::getClassName() const {
    return "javascript::JavaScriptNoSuchElementException";
  }


}}}
