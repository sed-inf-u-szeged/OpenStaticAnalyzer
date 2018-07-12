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

#include "genealogy/inc/genealogy.h"


namespace columbus { namespace genealogy { 

  /* ---------- Exception ---------- */

  GenealogyException::GenealogyException(const std::string &location, const std::string &message) : columbus::Exception(location, message) {
  }

  GenealogyException::~GenealogyException() {
  }

  const std::string GenealogyException::getClassName() const {
    return "genealogy::GenealogyException";
  }


  /* ---------- GenealogyInvalidIteratorException ---------- */

  GenealogyInvalidIteratorException::GenealogyInvalidIteratorException(const std::string &location, const std::string &message) : GenealogyException(location, message) {
  }

  GenealogyInvalidIteratorException::~GenealogyInvalidIteratorException() {
  }

  const std::string GenealogyInvalidIteratorException::getClassName() const {
    return "genealogy::GenealogyInvalidIteratorException";
  }


  /* ---------- GenealogyIllegalStateException ---------- */

  GenealogyIllegalStateException::GenealogyIllegalStateException(const std::string &location, const std::string &message) : GenealogyException(location, message) {
  }

  GenealogyIllegalStateException::~GenealogyIllegalStateException() {
  }

  const std::string GenealogyIllegalStateException::getClassName() const {
    return "genealogy::GenealogyIllegalStateException";
  }


  /* ---------- GenealogyNoSuchElementException ---------- */

  GenealogyNoSuchElementException::GenealogyNoSuchElementException(const std::string &location, const std::string &message) : GenealogyException(location, message) {
  }

  GenealogyNoSuchElementException::~GenealogyNoSuchElementException() {
  }

  const std::string GenealogyNoSuchElementException::getClassName() const {
    return "genealogy::GenealogyNoSuchElementException";
  }


}}
