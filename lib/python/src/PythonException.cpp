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

#include "python/inc/python.h"


namespace columbus { namespace python { namespace asg {

  /* ---------- Exception ---------- */

  PythonException::PythonException(const std::string &location, const std::string &message) : columbus::Exception(location, message) {
  }

  PythonException::~PythonException() {
  }

  const std::string PythonException::getClassName() const {
    return "python::PythonException";
  }


  /* ---------- PythonInvalidIteratorException ---------- */

  PythonInvalidIteratorException::PythonInvalidIteratorException(const std::string &location, const std::string &message) : PythonException(location, message) {
  }

  PythonInvalidIteratorException::~PythonInvalidIteratorException() {
  }

  const std::string PythonInvalidIteratorException::getClassName() const {
    return "python::PythonInvalidIteratorException";
  }


  /* ---------- PythonIllegalStateException ---------- */

  PythonIllegalStateException::PythonIllegalStateException(const std::string &location, const std::string &message) : PythonException(location, message) {
  }

  PythonIllegalStateException::~PythonIllegalStateException() {
  }

  const std::string PythonIllegalStateException::getClassName() const {
    return "python::PythonIllegalStateException";
  }


  /* ---------- PythonNoSuchElementException ---------- */

  PythonNoSuchElementException::PythonNoSuchElementException(const std::string &location, const std::string &message) : PythonException(location, message) {
  }

  PythonNoSuchElementException::~PythonNoSuchElementException() {
  }

  const std::string PythonNoSuchElementException::getClassName() const {
    return "python::PythonNoSuchElementException";
  }


}}}
