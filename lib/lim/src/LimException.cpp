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

#include "lim/inc/lim.h"


namespace columbus { namespace lim { namespace asg {

  /* ---------- Exception ---------- */

  LimException::LimException(const std::string &location, const std::string &message) : columbus::Exception(location, message) {
  }

  LimException::~LimException() {
  }

  const std::string LimException::getClassName() const {
    return "lim::LimException";
  }


  /* ---------- LimInvalidIteratorException ---------- */

  LimInvalidIteratorException::LimInvalidIteratorException(const std::string &location, const std::string &message) : LimException(location, message) {
  }

  LimInvalidIteratorException::~LimInvalidIteratorException() {
  }

  const std::string LimInvalidIteratorException::getClassName() const {
    return "lim::LimInvalidIteratorException";
  }


  /* ---------- LimIllegalStateException ---------- */

  LimIllegalStateException::LimIllegalStateException(const std::string &location, const std::string &message) : LimException(location, message) {
  }

  LimIllegalStateException::~LimIllegalStateException() {
  }

  const std::string LimIllegalStateException::getClassName() const {
    return "lim::LimIllegalStateException";
  }


  /* ---------- LimNoSuchElementException ---------- */

  LimNoSuchElementException::LimNoSuchElementException(const std::string &location, const std::string &message) : LimException(location, message) {
  }

  LimNoSuchElementException::~LimNoSuchElementException() {
  }

  const std::string LimNoSuchElementException::getClassName() const {
    return "lim::LimNoSuchElementException";
  }


}}}
