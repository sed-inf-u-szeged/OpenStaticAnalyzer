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

#include "java/inc/java.h"


namespace columbus { namespace java { namespace asg {

  /* ---------- Exception ---------- */

  JavaException::JavaException(const std::string &location, const std::string &message) : columbus::Exception(location, message) {
  }

  JavaException::~JavaException() {
  }

  const std::string JavaException::getClassName() const {
    return "java::JavaException";
  }


  /* ---------- JavaInvalidIteratorException ---------- */

  JavaInvalidIteratorException::JavaInvalidIteratorException(const std::string &location, const std::string &message) : JavaException(location, message) {
  }

  JavaInvalidIteratorException::~JavaInvalidIteratorException() {
  }

  const std::string JavaInvalidIteratorException::getClassName() const {
    return "java::JavaInvalidIteratorException";
  }


  /* ---------- JavaIllegalStateException ---------- */

  JavaIllegalStateException::JavaIllegalStateException(const std::string &location, const std::string &message) : JavaException(location, message) {
  }

  JavaIllegalStateException::~JavaIllegalStateException() {
  }

  const std::string JavaIllegalStateException::getClassName() const {
    return "java::JavaIllegalStateException";
  }


  /* ---------- JavaNoSuchElementException ---------- */

  JavaNoSuchElementException::JavaNoSuchElementException(const std::string &location, const std::string &message) : JavaException(location, message) {
  }

  JavaNoSuchElementException::~JavaNoSuchElementException() {
  }

  const std::string JavaNoSuchElementException::getClassName() const {
    return "java::JavaNoSuchElementException";
  }


}}}
