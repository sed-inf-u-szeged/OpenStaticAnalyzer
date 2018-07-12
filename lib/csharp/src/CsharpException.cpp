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

#include "csharp/inc/csharp.h"


namespace columbus { namespace csharp { namespace asg {

  /* ---------- Exception ---------- */

  CsharpException::CsharpException(const std::string &location, const std::string &message) : columbus::Exception(location, message) {
  }

  CsharpException::~CsharpException() {
  }

  const std::string CsharpException::getClassName() const {
    return "csharp::CsharpException";
  }


  /* ---------- CsharpInvalidIteratorException ---------- */

  CsharpInvalidIteratorException::CsharpInvalidIteratorException(const std::string &location, const std::string &message) : CsharpException(location, message) {
  }

  CsharpInvalidIteratorException::~CsharpInvalidIteratorException() {
  }

  const std::string CsharpInvalidIteratorException::getClassName() const {
    return "csharp::CsharpInvalidIteratorException";
  }


  /* ---------- CsharpIllegalStateException ---------- */

  CsharpIllegalStateException::CsharpIllegalStateException(const std::string &location, const std::string &message) : CsharpException(location, message) {
  }

  CsharpIllegalStateException::~CsharpIllegalStateException() {
  }

  const std::string CsharpIllegalStateException::getClassName() const {
    return "csharp::CsharpIllegalStateException";
  }


  /* ---------- CsharpNoSuchElementException ---------- */

  CsharpNoSuchElementException::CsharpNoSuchElementException(const std::string &location, const std::string &message) : CsharpException(location, message) {
  }

  CsharpNoSuchElementException::~CsharpNoSuchElementException() {
  }

  const std::string CsharpNoSuchElementException::getClassName() const {
    return "csharp::CsharpNoSuchElementException";
  }


}}}
